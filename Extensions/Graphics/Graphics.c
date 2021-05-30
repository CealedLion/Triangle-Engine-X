#pragma once
//C
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
//Third-Party
#include <atomic\atomic.h>
//OS Specific
#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#else
#endif
//ours
#include "Extension.h"
#include "Object.h"
#define TEX_EXPOSE_GRAPHICS
#include "Graphics.h"
#include "GraphicsShaders.h"


volatile struct
{
	uint64_t ExtensionsEnabledSize;
	char* ExtensionsEnabled[3];

	uint64_t ValidationLayersEnabledSize;
	char* ValidationLayersEnabled[1];

	uint64_t InitialElementsMax;
	uint64_t InitialHeadersMax;

	uint64_t InitialNativeGPUBufferSize;
	uint64_t InitialStagingGPUBufferSize;

	VkSampleCountFlagBits Samples;

	uint32_t MaxAnisotropy;
	bool AnisotropicFiltering;
}Config;

volatile GraphicsUtils Utils;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Misc Helper Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Normalize delta.
* takes 2 values and gets the difference from 0-1 between them based on a third variable.
*/
double normalize_d(double val, double max, double min){
	return (val - min) / (max - min);
}
/*
* Added in 1.0.0
*/
float CubicSplineInterpolation(float previousPoint, float previousTangent, float nextPoint, float nextTangent, float interpolationValue)
{
	float t2 = interpolationValue * interpolationValue;
	float t3 = t2 * interpolationValue;

	return ((2 * t3 - 3 * t2 + 1) * previousPoint) + ((t3 - 2 * t2 + interpolationValue) * previousTangent) + ((-2 * t3 + 3 * t2) * nextPoint) + ((t3 - t2) * nextTangent);
}
/*
* Added in 1.0.0
* Returns the priority of an attribute, as in the usefulness in drawing.
*/
float Get_AttributeTypePriority(Attribute attribute)
{
	switch (attribute.AttribType)
	{
	case AttributeType_TexCoord:
		return (float)attribute.TargetGroup + 0.2f;
	case AttributeType_Position:
		return (float)attribute.TargetGroup + 0.1f;
	case AttributeType_Normal:
		return (float)attribute.TargetGroup + 0.3f;
	case AttributeType_Tangent:
		return (float)attribute.TargetGroup + 0.4f;
	case AttributeType_Colour:
		return (float)attribute.TargetGroup + 0.5f;
	case AttributeType_Joints:
		return (float)attribute.TargetGroup + 0.6f;
	case AttributeType_SkinWeights:
		return (float)attribute.TargetGroup + 0.7f;
	}
	return 9999.0f;
}
/*
* Added in 1.0.0
*/
bool Get_AttributeTypeCompatibility(Attribute attribute)
{
	switch (attribute.AttribType)
	{
	case AttributeType_TexCoord: return (attribute.Accessor.Type == AccessorType_VEC2) ? true : false;
	case AttributeType_Position:return (attribute.Accessor.Type == AccessorType_VEC3) ? true : false;
	case AttributeType_Normal:return (attribute.Accessor.Type == AccessorType_VEC3) ? true : false;
	case AttributeType_Tangent:return (attribute.Accessor.Type == AccessorType_VEC4) ? true : false;
	case AttributeType_Colour:return (attribute.Accessor.Type == AccessorType_VEC4) ? true : false;
	case AttributeType_Joints:return (attribute.Accessor.Type == AccessorType_VEC4) ? true : false;
	case AttributeType_SkinWeights:return (attribute.Accessor.Type == AccessorType_VEC4) ? true : false;
	}
	return true;
}
/*
* Added in 1.0.0
* returns all details of format
*/
FormatDetails Get_FormatDetails(GraphicsFormat format)
{
	FormatDetails details;
	details.ChannelCount = GraphicsFormatChannelCounts[format];	
	details.ChannelTypes = (DataType*)GraphicsFormatDataType[format];
	details.ChannelNames = (char*)GraphicsFormatChannelIndentifiers[format];
	details.BitsPerChannel = (uint8_t*)GraphicsFormatBitsPerChannels[format];
	details.Stride = GraphicsFormatStrides[format];
	return details;
}
/*
* Added in 1.0.0
* calculates the total matrix of a object, animations and hierarchy and all.
* @param Parent is the allocation of the target parent of pPosition header to calculate the matrix from.
* @param pMatrix is a pointer to the resulting computed matrix.
*/
void Calculate_TotalMatrix(mat4* pMatrix, ObjectAllocation Parent)
{
#ifndef NDEBUG
	if (pMatrix == NULL)
	{
		Engine_Ref_ArgsError("Calculate_TotalMatrix()", "pMatrix == NULLPTR");
		return;
	}
	if (Object_Ref_Get_ObjectAllocationValidity(Parent) != Success)
	{
		Engine_Ref_ArgsError("Calculate_TotalMatrix()", "Parent Invalid.");
		return;
	}
#endif
	Object* pObject = Object_Ref_Get_ObjectPointer(Parent);

	for (size_t i = 0; i < pObject->Header.iResourceHeadersSize; i++)
	{
		if (pObject->Header.iResourceHeaders[i].Identifier == GraphicsHeader_Position)
		{
			RHeaderPosition* pPositionHeader = (RHeaderPosition*)Object_Ref_Get_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i]);
			mat4 temp;
			glm_mat4_copy(pPositionHeader->Matrix, temp);

			for (size_t i1 = 0; i1 < pObject->Header.iResourceHeadersSize; i1++)
			{
				if (pObject->Header.iResourceHeaders[i1].Identifier == GraphicsHeader_AnimationChannel)
				{
					RHeaderAnimationChannel* pAnimationChannelHeader = (RHeaderAnimationChannel*)Object_Ref_Get_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i1]);
					if (pAnimationChannelHeader != NULL &&
						((pAnimationChannelHeader->Target == AnimationTargetType_Rotation) || (pAnimationChannelHeader->Target == AnimationTargetType_Translation) || (pAnimationChannelHeader->Target == AnimationTargetType_Scale)))
					{

						RHeaderAnimation* pAnimation = (RHeaderAnimation*)Object_Ref_Get_ResourceHeaderPointer(pAnimationChannelHeader->iAnimation);

						RHeaderBuffer* pInputBuffer = (RHeaderBuffer*)Object_Ref_Get_ResourceHeaderPointer(pAnimationChannelHeader->Sampler.Input.iBuffer);
						RHeaderBuffer* pOutputBuffer = (RHeaderBuffer*)Object_Ref_Get_ResourceHeaderPointer(pAnimationChannelHeader->Sampler.Output.iBuffer);

						RHeaderBufferSource* pInputBufferSource = (RHeaderBufferSource*)Object_Ref_Get_ResourceHeaderPointer(pInputBuffer->iBufferSource);
						RHeaderBufferSource* pOutputBufferSource = (RHeaderBufferSource*)Object_Ref_Get_ResourceHeaderPointer(pOutputBuffer->iBufferSource);

						void* inputpointer = (void*)((uint64_t)pInputBufferSource->Data.pData + pAnimationChannelHeader->Sampler.Input.ByteOffset);
						void* outputpointer = (void*)((uint64_t)pOutputBufferSource->Data.pData + pAnimationChannelHeader->Sampler.Output.ByteOffset);

						float barrier = ((float*)inputpointer)[pAnimationChannelHeader->KeyFrame];
						float barrier1 = ((float*)inputpointer)[pAnimationChannelHeader->KeyFrame + 1];

						//every interpolation must start with 0 and end with 1
						double frametime = normalize_d(pAnimation->Time - barrier, barrier1 - barrier, 0.0);
						frametime = glm_clamp(frametime, 0.0f, 1.0f);

						float input[48];
						float input1[48];

						uint64_t size = pAnimationChannelHeader->Sampler.Output.Type;
						if (pAnimationChannelHeader->Sampler.Interpolation == InterpolationType_Cubicspline)
						{
							size = (pAnimationChannelHeader->Sampler.Output.Type * 3);
						}

						//convert pData from datatypes
						switch (pAnimationChannelHeader->Sampler.Output.Format)
						{
						case GraphicsFormat_R8G8B8_SINT:
							for (size_t i2 = 0; i2 < size; i2++)
							{
								input[i2] = max(((int8_t*)outputpointer)[((pAnimationChannelHeader->KeyFrame) * size) + i2] / (double)INT8_MAX, -1.0);
								input1[i2] = max(((int8_t*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * size) + i2] / (double)INT8_MAX, -1.0);
							}
							break;
						case GraphicsFormat_R8G8B8_UINT:
							for (size_t i2 = 0; i2 < size; i2++)
							{
								input[i2] = ((uint8_t*)outputpointer)[(pAnimationChannelHeader->KeyFrame * size) + i2] / (double)UINT8_MAX;
								input1[i2] = ((uint8_t*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * size) + i2] / (double)UINT8_MAX;
							}
							break;
						case GraphicsFormat_R16G16B16_SINT:
							for (size_t i2 = 0; i2 < size; i2++)
							{
								input[i2] = max(((int16_t*)outputpointer)[(pAnimationChannelHeader->KeyFrame * size) + i2] / (double)INT16_MAX, -1.0);
								input1[i2] = max(((int16_t*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * size) + i2] / (double)INT16_MAX, -1.0);
							}
							break;
						case GraphicsFormat_R16G16B16_UINT:
							for (size_t i2 = 0; i2 < size; i2++)
							{
								input[i2] = ((uint16_t*)outputpointer)[(pAnimationChannelHeader->KeyFrame * size) + i2] / (double)UINT16_MAX;
								input1[i2] = ((uint16_t*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * size) + i2] / (double)UINT16_MAX;
							}
							break;
						case GraphicsFormat_R32G32B32_SINT:
							for (size_t i2 = 0; i2 < size; i2++)
							{
								input[i2] = max(((int32_t*)outputpointer)[(pAnimationChannelHeader->KeyFrame * size) + i2] / (double)INT32_MAX, -1.0);
								input1[i2] = max(((int32_t*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * size) + i2] / (double)INT32_MAX, -1.0);
							}
							break;
						case GraphicsFormat_R32G32B32_UINT:
							for (size_t i2 = 0; i2 < size; i2++)
							{
								input[i2] = ((uint32_t*)outputpointer)[(pAnimationChannelHeader->KeyFrame * size) + i2] / (double)UINT32_MAX;
								input1[i2] = ((uint32_t*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * size) + i2] / (double)UINT32_MAX;
							}
							break;
						case GraphicsFormat_R64G64B64_SINT:
							for (size_t i2 = 0; i2 < size; i2++)
							{
								input[i2] = max(((int64_t*)outputpointer)[(pAnimationChannelHeader->KeyFrame * size) + i2] / (double)INT64_MAX, -1.0);
								input1[i2] = max(((int64_t*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * size) + i2] / (double)INT64_MAX, -1.0);
							}
							break;
						case GraphicsFormat_R64G64B64_UINT:
							for (size_t i2 = 0; i2 < size; i2++)
							{
								input[i2] = ((uint64_t*)outputpointer)[(pAnimationChannelHeader->KeyFrame * size) + i2] / (double)UINT64_MAX;
								input1[i2] = ((uint32_t*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * size) + i2] / (double)UINT32_MAX;
							}
							break;
						case GraphicsFormat_R32G32B32_SFLOAT:
							for (size_t i2 = 0; i2 < size; i2++)
							{
								input[i2] = ((float*)outputpointer)[(pAnimationChannelHeader->KeyFrame * size) + i2];
								input1[i2] = ((float*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * size) + i2];
							}
							break;
						case GraphicsFormat_R64G64B64_SFLOAT:
							for (size_t i2 = 0; i2 < size; i2++)
							{
								input[i2] = ((double*)outputpointer)[(pAnimationChannelHeader->KeyFrame * size) + i2];
								input1[i2] = ((double*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * size) + i2];
							}
							break;
						}

						/*
						Implementation Note: The first in-tangent a1 and last out-tangent bn should be zeros as they are not used in the spline calculations.

						Implementation Note: When writing out rotation output values, exporters should take care to not write out values which can result in an invalid quaternion with all zero values.
						This can be achieved by ensuring the output values never have both -q and q in the same spline.
						*/
						vec4 translation;
						glm_vec4_zero(translation);
						mat4 rotationmt;
						glm_mat4_zero(rotationmt);
						vec3 scale;
						glm_vec3_zero(scale);
						glm_decompose(temp, translation, rotationmt, scale);
						//vec4
						vec4 rotation;
						glm_vec4_zero(rotation);
						glm_mat4_quat(rotationmt, rotation);

						switch (pAnimationChannelHeader->Target)
						{
						case AnimationTargetType_Translation:
							switch (pAnimationChannelHeader->Sampler.Interpolation)
							{
							case InterpolationType_Linear:
								for (size_t i2 = 0; i2 < 3; i2++)
									translation[i2] = glm_lerp(input[i2], input1[i2], frametime);
								break;
							case InterpolationType_Step:
								for (size_t i2 = 0; i2 < 3; i2++)
									translation[i2] = input[i2];
								break;
							case InterpolationType_Cubicspline:
								
								float deltaTime = barrier1 - barrier;
								vec3 previousTangent;
								glm_vec3_zero(previousTangent);
								glm_vec3_scale(previousTangent, deltaTime, &input[3 * 2]);
								vec3 nextTangent;
								glm_vec3_zero(nextTangent);
								glm_vec3_scale(nextTangent, deltaTime, &input1[0]);

								for (size_t i2 = 0; i2 < 3; i2++)
									translation[i2] = CubicSplineInterpolation(input[(3 * 1) + i2], previousTangent[i2], input1[(3 * 1) + i2], nextTangent[i2], frametime);
								break;
							}
							break;
						case AnimationTargetType_Rotation:
							switch (pAnimationChannelHeader->Sampler.Interpolation)
							{
							case InterpolationType_Linear:
								glm_quat_slerp(input, input1, frametime, rotation);
								break;
							case InterpolationType_Step:
								for (size_t i2 = 0; i2 < 4; i2++)
									rotation[i2] = input[i2];
								break;
							case InterpolationType_Cubicspline:
								
								float deltaTime = barrier1 - barrier;
								vec4 previousTangent;
								glm_vec4_zero(previousTangent);
								glm_vec4_scale(previousTangent, deltaTime, &input[4 * 2]);
								vec4 nextTangent;
								glm_vec4_zero(nextTangent);
								glm_vec4_scale(nextTangent, deltaTime, &input1[0]);

								for (size_t i2 = 0; i2 < 4; i2++)
									rotation[i2] = CubicSplineInterpolation(input[(4 * 1) + i2], previousTangent[i2], input1[(4 * 1) + i2], nextTangent[i2], frametime);					
								glm_vec4_normalize(rotation);
								break;
							}
							break;
						case AnimationTargetType_Scale:
							switch (pAnimationChannelHeader->Sampler.Interpolation)
							{
							case InterpolationType_Linear:
								for (size_t i2 = 0; i2 < 3; i2++)
									scale[i2] = glm_lerp(input[i2], input1[i2], frametime);
								break;
							case InterpolationType_Step:
								for (size_t i2 = 0; i2 < 3; i2++)
									scale[i2] = input[i2];
								break;
							case InterpolationType_Cubicspline:

								float deltaTime = barrier1 - barrier;
								vec3 previousTangent;
								glm_vec3_zero(previousTangent);
								glm_vec3_scale(previousTangent, deltaTime, &input[3 * 2]);
								vec3 nextTangent;
								glm_vec3_zero(nextTangent);
								glm_vec3_scale(nextTangent, deltaTime, &input1[0]);

								for (size_t i2 = 0; i2 < 3; i2++)
									scale[i2] = CubicSplineInterpolation(input[(3 * 1) + i2], previousTangent[i2], input1[(3 * 1) + i2], nextTangent[i2], frametime);
								break;
							}
							break;
						}

						mat4 identitym;
						glm_mat4_identity(identitym);
						mat4 translationm;
						glm_mat4_identity(translationm);
						glm_translate(translationm, translation);
						mat4 rotationm;
						glm_mat4_identity(rotationm);
						glm_quat_rotate(identitym, rotation, rotationm);
						mat4 scalem;
						glm_mat4_identity(scalem);
						glm_scale(scalem, scale);

						glm_mul_sse2(translationm, rotationm, temp);
						glm_mul_sse2(temp, scalem, temp);
						glm_mul_sse2(temp, identitym, temp);
					}
				}
			}
			glm_mat4_mul_sse2(temp, *pMatrix, *pMatrix);
		}
	}
	if (Object_Ref_Get_ObjectAllocationValidity(pObject->Header.iParent) == Success)
	{
		Calculate_TotalMatrix(pMatrix, pObject->Header.iParent);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//GPU allocation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* returns index of compatible memory index of specified memory type filter
* @param pPhysicalDevice Pointer to a physicaldevice to check the memory of.
* @param TypeFilter is a bitmask of the required memory type to check.
* @param Properties is the required memory properties to check.
* @return @ref the index of the compatible memory on success. @ref UINT32_MAX on failure.
* @note Always Thread safe.
* @note Externally Synchronized.
*/
uint32_t Check_Memory(const PhysicalDevice* pPhysicalDevice, uint32_t TypeFilter, VkMemoryPropertyFlags Properties){
	for (uint32_t i1 = 0; i1 < pPhysicalDevice->MemoryProperties.memoryTypeCount; i1++)
		if ((TypeFilter & (1 << i1)) && (pPhysicalDevice->MemoryProperties.memoryTypes[i1].propertyFlags & Properties) == Properties)
			return i1;
	return UINT32_MAX;
}
/*
* Added in 1.0.0
* Creates a GPU memory arena allocater.
* @param pLogicalDevice Pointer to a logicaldevice to create the buffer on.
* @param pAllocater pointer to the allocater to create.
* @param Size size of buffer in bytes to allocate.
* @param Type type of buffer.
* @note Always Thread safe.
* @note Externally Synchronized.
*/
TEXRESULT Create_GPU_ArenaAllocater(LogicalDevice* pLogicalDevice, GPU_ArenaAllocater* pAllocater, uint64_t Size, TargetMemoryType Type)
{
#ifndef NDEBUG
	if (pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("Create_GPU_ArenaAllocater()", "pLogicalDevice == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pAllocater == NULL)
	{
		Engine_Ref_ArgsError("Create_GPU_ArenaAllocater()", "pAllocater == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Create_Mutex(pAllocater->mutex, MutexType_Plain);

	Resize_Array((void**)&pAllocater->Allocations, pAllocater->AllocationsSize, pAllocater->AllocationsSize + 2, sizeof(*pAllocater->Allocations));
	pAllocater->AllocationsSize += 2;
	pAllocater->Size = Size;
	GPU_Allocation alloc; //first cap
	alloc.Pointer = 0;
	alloc.SizeBytes = 0;
	//alloc.AllocationType = AllocationType_Linear;
	alloc.TargetMemory = Type;
	//alloc.VkMemory = VkMemory;
	pAllocater->Allocations[0] = alloc;
	//cap 2
	alloc.Pointer = Size;
	alloc.SizeBytes = 0;
	//alloc.AllocationType = AllocationType_Linear;
	alloc.TargetMemory = Type;
	//alloc.VkMemory = VkMemory;
	pAllocater->Allocations[pAllocater->AllocationsSize - 1] = alloc;

	pAllocater->VkBuffer = NULL;
	pAllocater->VkMemory = NULL;

	if (pAllocater->Size != NULL)
	{
		VkDeviceMemory NewVkMemory = NULL;
		VkBuffer NewVkBuffer = NULL;

		VkResult res = VK_SUCCESS;
		{
			VkBufferCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			Info.size = pAllocater->Size;
			Info.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT |
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
				VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
			Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			Info.pQueueFamilyIndices = NULL;
			Info.queueFamilyIndexCount = NULL;
			Info.flags = NULL;
			Info.pNext = NULL;
			if (vkCreateBuffer(pLogicalDevice->VkLogicalDevice, &Info, NULL, &NewVkBuffer) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("Create_GPU_MemoryBuffer()", "vkCreateBuffer Failed, VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(pLogicalDevice->VkLogicalDevice, NewVkBuffer, &memRequirements);

		VkMemoryPropertyFlags properties = NULL;

		switch (Type)
		{
		case TargetMemory_Src:
			properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
			break;
		case TargetMemory_Dst:
			properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			break;
		}
		{
			VkMemoryAllocateInfo AllocationInfo;
			AllocationInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			AllocationInfo.allocationSize = memRequirements.size;
			AllocationInfo.memoryTypeIndex = Check_Memory(pLogicalDevice->pPhysicalDevice, memRequirements.memoryTypeBits, properties);
			AllocationInfo.pNext = NULL;
			if (AllocationInfo.memoryTypeIndex == UINT32_MAX)
			{
				Engine_Ref_FunctionError("Create_GPU_MemoryBuffer()", "Failed To Find Suitable Memory, MemoryTypeIndex == ", AllocationInfo.memoryTypeIndex);
				return (TEXRESULT)(Out_Of_Memory_Result | Failure);
			}

			if ((res = vkAllocateMemory(pLogicalDevice->VkLogicalDevice, &AllocationInfo, NULL, &NewVkMemory)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("Create_GPU_MemoryBuffer()", "vkAllocateMemory Failed, VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}

		vkBindBufferMemory(pLogicalDevice->VkLogicalDevice, NewVkBuffer, NewVkMemory, 0);
		pAllocater->VkBuffer = NewVkBuffer;
		pAllocater->VkMemory = NewVkMemory;
		pAllocater->Alignment = memRequirements.alignment;
		if (Type == TargetMemory_Src)
			vkMapMemory(pLogicalDevice->VkLogicalDevice, pAllocater->VkMemory, 0, pAllocater->Size, 0, &pAllocater->MappedMemory);
	}
	return Success;
}
/*
* Added in 1.0.0
* Destroys a GPU memory arena allocater.
* @param pAllocater pointer to the allocater to destroy.
* @note Always Thread safe.
* @note Externally Synchronized.
*/
void Destroy_GPU_ArenaAllocater(LogicalDevice* pLogicalDevice, GPU_ArenaAllocater* pAllocater)
{
#ifndef NDEBUG
	if (pAllocater == NULL)
	{
		Engine_Ref_ArgsError("Destroy_GPU_ArenaAllocater()", "pAllocater == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif

	pAllocater->Size = NULL;
	pAllocater->Alignment = NULL;

	Engine_Ref_Destroy_Mutex(pAllocater->mutex);

	if (pAllocater->Allocations != NULL)
		free(pAllocater->Allocations);
	pAllocater->Allocations = NULL;
	pAllocater->AllocationsSize = NULL;

	if (pAllocater->VkBuffer != NULL)
		vkDestroyBuffer(pLogicalDevice->VkLogicalDevice, pAllocater->VkBuffer, NULL);

	if (pAllocater->MappedMemory != NULL)
		vkUnmapMemory(pLogicalDevice->VkLogicalDevice, pAllocater->VkMemory);

	if (pAllocater->VkMemory != NULL)
		vkFreeMemory(pLogicalDevice->VkLogicalDevice, pAllocater->VkMemory, NULL);
}
/*
*Added in 1.0.0
* ReCreates a GPU memory arena allocater and copies all the old data over to new.
* @param pLogicalDevice Pointer to a logicaldevice to create the buffer on.
* @param pAllocater pointer to the allocater to create.
* @param NewSize new size of buffer in bytes to allocate.
* @param Type type of buffer.
* @note Always Thread safe.
* @note Externally Synchronized.
*/
TEXRESULT ReCreate_GPU_ArenaAllocater(LogicalDevice * pLogicalDevice, GPU_ArenaAllocater * pAllocater, uint64_t NewSize, TargetMemoryType Type)
{
#ifndef NDEBUG
	if (pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_GPU_ArenaAllocater()", "pLogicalDevice == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pAllocater == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_GPU_ArenaAllocater()", "pAllocater == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif

	pAllocater->Allocations[pAllocater->AllocationsSize - 1].Pointer = NewSize;

	if (pAllocater->VkBuffer != NULL)
		vkDestroyBuffer(pLogicalDevice->VkLogicalDevice, pAllocater->VkBuffer, NULL);

	if (pAllocater->MappedMemory != NULL)
		vkUnmapMemory(pLogicalDevice->VkLogicalDevice, pAllocater->VkMemory);

	if (pAllocater->VkMemory != NULL)
		vkFreeMemory(pLogicalDevice->VkLogicalDevice, pAllocater->VkMemory, NULL);

	if (NewSize != NULL)
	{
		VkDeviceMemory NewVkMemory = NULL;
		VkBuffer NewVkBuffer = NULL;

		VkResult res = VK_SUCCESS;
		{
			VkBufferCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
			Info.size = NewSize;
			Info.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT |
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
				VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
			Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
			Info.pQueueFamilyIndices = NULL;
			Info.queueFamilyIndexCount = NULL;
			Info.flags = NULL;
			Info.pNext = NULL;
			if (vkCreateBuffer(pLogicalDevice->VkLogicalDevice, &Info, NULL, &NewVkBuffer) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_GPU_ArenaAllocater()", "vkCreateBuffer Failed, VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(pLogicalDevice->VkLogicalDevice, NewVkBuffer, &memRequirements);

		VkMemoryPropertyFlags properties = NULL;

		switch (Type)
		{
		case TargetMemory_Src:
			properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
			break;
		case TargetMemory_Dst:
			properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			break;
		}
		{
			VkMemoryAllocateInfo AllocationInfo;
			AllocationInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
			AllocationInfo.allocationSize = memRequirements.size;
			AllocationInfo.memoryTypeIndex = Check_Memory(pLogicalDevice->pPhysicalDevice, memRequirements.memoryTypeBits, properties);
			AllocationInfo.pNext = NULL;
			if (AllocationInfo.memoryTypeIndex == UINT32_MAX)
			{
				Engine_Ref_FunctionError("ReCreate_GPU_ArenaAllocater()", "Failed To Find Suitable Memory, MemoryTypeIndex == ", AllocationInfo.memoryTypeIndex);
				return (TEXRESULT)(Out_Of_Memory_Result | Failure);
			}

			if ((res = vkAllocateMemory(pLogicalDevice->VkLogicalDevice, &AllocationInfo, NULL, &NewVkMemory)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_GPU_ArenaAllocater()", "vkAllocateMemory Failed, VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}

		vkBindBufferMemory(pLogicalDevice->VkLogicalDevice, NewVkBuffer, NewVkMemory, 0);

		if (pAllocater->Size == NULL)
		{

		}
		else
		{
			VkCommandPool VkCmdPool = NULL;
			VkCommandBuffer VkCmdBuffer = NULL;
			{
				VkCommandPoolCreateInfo Info;
				memset(&Info, NULL, sizeof(Info));
				Info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
				Info.queueFamilyIndex = pLogicalDevice->MemoryQueueFamilyIndex;
				Info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
				if ((res = vkCreateCommandPool(pLogicalDevice->VkLogicalDevice, &Info, NULL, &VkCmdPool)) != VK_SUCCESS)
				{
					Engine_Ref_FunctionError("ReCreate_GPU_ArenaAllocater()", "vkCreateCommandPool Failed, VkResult == ", res);
					return;
				}
			}
			{
				VkCommandBufferAllocateInfo Info;
				memset(&Info, NULL, sizeof(Info));
				Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
				Info.commandPool = VkCmdPool;
				Info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
				Info.commandBufferCount = 1;
				Info.pNext = NULL;
				if ((res = vkAllocateCommandBuffers(pLogicalDevice->VkLogicalDevice, &Info, &VkCmdBuffer)) != VK_SUCCESS)
				{
					Engine_Ref_FunctionError("ReCreate_GPU_ArenaAllocater()", "vkAllocateCommandBuffers Failed, VkResult == ", res);
					return;
				}
			}
			{
				VkCommandBufferBeginInfo BeginInfo;
				memset(&BeginInfo, NULL, sizeof(BeginInfo));
				BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
				BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
				BeginInfo.pInheritanceInfo = NULL;
				BeginInfo.pNext = NULL;
				if ((res = vkBeginCommandBuffer(VkCmdBuffer, &BeginInfo)) != VK_SUCCESS)
				{
					Engine_Ref_FunctionError("ReCreate_GPU_ArenaAllocater()", "vkBeginCommandBuffer Failed, VkResult == ", res);
					return;
				}
			}

			VkBufferCopy region;
			region.srcOffset = 0;
			region.dstOffset = 0;
			region.size = min(pAllocater->Size, NewSize);

			vkCmdCopyBuffer(
				VkCmdBuffer,
				pAllocater->VkBuffer,
				NewVkBuffer,
				1,
				&region
			);
			vkEndCommandBuffer(VkCmdBuffer);

			uint32_t QueueIndex = 0;
			{
				bool found = false;
				while (found == false)
				{
					for (size_t i = 0; i < pLogicalDevice->MemoryQueueFamilySize; i++)
					{
						if (Engine_Ref_TryLock_Mutex(pLogicalDevice->MemoryQueueMutexes[i]) == Success)
						{
							QueueIndex = i;
							found = true;
							break;
						}
					}
				}
			}
			VkQueue Queue = NULL;
			vkGetDeviceQueue(pLogicalDevice->VkLogicalDevice, pLogicalDevice->MemoryQueueFamilyIndex, QueueIndex, &Queue);

			VkSubmitInfo SubmitInfo;
			memset(&SubmitInfo, NULL, sizeof(SubmitInfo));
			SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			SubmitInfo.commandBufferCount = (uint32_t)1;
			SubmitInfo.pCommandBuffers = &VkCmdBuffer;

			if ((res = vkQueueSubmit(Queue, 1, &SubmitInfo, VK_NULL_HANDLE)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_GPU_ArenaAllocater()", "vkQueueSubmit Failed, VkResult == ", res);
				return;
			}

			vkQueueWaitIdle(Queue);
			Engine_Ref_Unlock_Mutex(pLogicalDevice->MemoryQueueMutexes[QueueIndex]);

			vkFreeCommandBuffers(pLogicalDevice->VkLogicalDevice, VkCmdPool, 1, &VkCmdBuffer);
			vkDestroyCommandPool(pLogicalDevice->VkLogicalDevice, VkCmdPool, NULL);
		}

		pAllocater->VkBuffer = NewVkBuffer;
		pAllocater->VkMemory = NewVkMemory;
		pAllocater->Alignment = memRequirements.alignment;
		pAllocater->Size = NewSize;

		if (Type == TargetMemory_Src)
			vkMapMemory(pLogicalDevice->VkLogicalDevice, pAllocater->VkMemory, 0, pAllocater->Size, 0, &pAllocater->MappedMemory);
	}
	pAllocater->Size = NewSize;

	return Success;
}
/*
* Added in 1.0.0
* destroys fully.
* @param pBuffer pointer to the GPU_MemoryBuffer to destroy.
* @param pLogicalDevice pointer to the LogicalDevice the GPU_MemoryBuffer was created on.
* @note Thread Safe.
* @note Internally Synchronized.
*/
void Destroy_GPU_MemoryBuffer(GPU_MemoryBuffer* pBuffer, LogicalDevice* pLogicalDevice)
{
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Destroy_GPU_MemoryBuffer()", "pBuffer == NULLPTR");
		return;
	}
	if (pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("Destroy_GPU_MemoryBuffer()", "pLogicalDevice == NULLPTR");
		return;
	}
#endif
	if (pBuffer->ArenaAllocaters != NULL)
	{
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		{
			Engine_Ref_Lock_Mutex(pBuffer->ArenaAllocaters[i].mutex);
		}
	}

	if (pBuffer->Indexes != NULL)
		free(pBuffer->Indexes);
	pBuffer->Indexes = NULL;

	if (pBuffer->ArenaAllocaters != NULL)
	{
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
			Destroy_GPU_ArenaAllocater(pLogicalDevice, &pBuffer->ArenaAllocaters[i]);
		free(pBuffer->ArenaAllocaters);
	}
	pBuffer->ArenaAllocaters = NULL;

}
/*
* Added in 1.0.0
* Creates a GPU memory buffer of specified size and type.
* @param pBuffer pointer to the GPU_MemoryBuffer to create.
* @param pLogicalDevice pointer to the LogicalDevice to create the GPU_MemoryBuffer on.
* @param Size the initial size in bytes.
* @param Type the type of GPU_MemoryBuffer to create.
* @note Externally Synchronized.
*/
TEXRESULT Create_GPU_MemoryBuffer(GPU_MemoryBuffer* pBuffer, LogicalDevice* pLogicalDevice, uint64_t Size, TargetMemoryType Type)
{
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Create_GPU_MemoryBuffer()", "pBuffer == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("Create_GPU_MemoryBuffer()", "pLogicalDevice == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Size == NULL)
	{
		Engine_Ref_ArgsError("Create_GPU_MemoryBuffer()", "Size == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	pBuffer->ArenaAllocaters = calloc(((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads, sizeof(*pBuffer->ArenaAllocaters));
	pBuffer->Indexes = calloc(((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads, sizeof(*pBuffer->Indexes));
	if (pBuffer->ArenaAllocaters == NULL || pBuffer->Indexes == NULL)
	{
		Engine_Ref_FunctionError("Create_GPU_MemoryBuffer()", "Out Of Memory.", pBuffer->ArenaAllocaters);
		return (TEXRESULT)(Out_Of_Memory_Result);
	}
	
	//Create_GPU_ArenaAllocater(pLogicalDevice, &pBuffer->ArenaAllocaters[0], Size, Type);
	
	for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		Create_GPU_ArenaAllocater(pLogicalDevice, &pBuffer->ArenaAllocaters[i], (Size / ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads), Type);
	
	pBuffer->Size = Size;
	pBuffer->Alignment = pBuffer->ArenaAllocaters[0].Alignment;
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* ReCreates a GPU memory buffer of specified size and type, allocations are not copied over so they need to be refilled.
* @param pBuffer pointer to the GPU_MemoryBuffer to create.
* @param pLogicalDevice pointer to the LogicalDevice to create the GPU_MemoryBuffer on.
* @param NewSize the new size in bytes.
* @param Type the type of GPU_MemoryBuffer to create.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Resize_GPU_MemoryBuffer(GPU_MemoryBuffer* pBuffer, LogicalDevice* pLogicalDevice, uint64_t NewSize, TargetMemoryType Type)
{
	
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_GPU_MemoryBuffer()", "pBuffer == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_GPU_MemoryBuffer()", "pLogicalDevice == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (NewSize == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_GPU_MemoryBuffer()", "NewSize == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	/*
	for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
	{
		Engine_Ref_Lock_Mutex(pBuffer->ArenaAllocaters[i].mutex);
	}

	if (pBuffer->VkBuffer != NULL)
		vkDestroyBuffer(pLogicalDevice->VkLogicalDevice, pBuffer->VkBuffer, NULL);

	if (pLogicalDevice->DstBuffer.VkMemory != NULL)
		vkFreeMemory(pLogicalDevice->VkLogicalDevice, pBuffer->VkMemory, NULL);



	//create vk buffer
	VkDeviceMemory newmemory = NULL;
	VkBuffer newbuffer = NULL;

	VkResult res = VK_SUCCESS;
	{
		VkBufferCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		Info.size = NewSize;
		Info.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT |
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
			VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT | VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
		Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		Info.pQueueFamilyIndices = NULL;
		Info.queueFamilyIndexCount = NULL;
		Info.flags = NULL;
		Info.pNext = NULL;
		if (vkCreateBuffer(pLogicalDevice->VkLogicalDevice, &Info, NULL, &newbuffer) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("Create_GPU_MemoryBuffer()", "vkCreateBuffer Failed, VkResult == ", res);
			return (TEXRESULT)(Failure);
		}
	}
	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(pLogicalDevice->VkLogicalDevice, newbuffer, &memRequirements);

	VkMemoryPropertyFlags properties = NULL;

	switch (Type)
	{
	case TargetMemory_Src:
		properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		break;
	case TargetMemory_Dst:
		properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		break;
	}
	{
		VkMemoryAllocateInfo AllocationInfo;
		AllocationInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		AllocationInfo.allocationSize = memRequirements.size;
		AllocationInfo.memoryTypeIndex = Check_Memory(pLogicalDevice->pPhysicalDevice, memRequirements.memoryTypeBits, properties);
		AllocationInfo.pNext = NULL;
		if (AllocationInfo.memoryTypeIndex == UINT32_MAX)
		{
			Engine_Ref_FunctionError("Create_GPU_MemoryBuffer()", "Failed To Find Suitable Memory, MemoryTypeIndex == ", AllocationInfo.memoryTypeIndex);
			return (TEXRESULT)(Out_Of_Memory_Result | Failure);
		}

		if ((res = vkAllocateMemory(pLogicalDevice->VkLogicalDevice, &AllocationInfo, NULL, &newmemory)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("Create_GPU_MemoryBuffer()", "vkAllocateMemory Failed, VkResult == ", res);
			return (TEXRESULT)(Failure);
		}
	}

	vkBindBufferMemory(pLogicalDevice->VkLogicalDevice, newbuffer, newmemory, 0);

	pBuffer->Alignment = memRequirements.alignment;
	pBuffer->VkBuffer = newbuffer;
	pBuffer->VkMemory = newmemory;
	pBuffer->Size = NewSize;

	for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
	{
		Engine_Ref_Unlock_Mutex(pBuffer->ArenaAllocaters[i].mutex);
	}*/
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Allocates a buffer of specified size and type on the logicaldevice GPU buffers and returns the resulting struct refrencing the allocation.
* @param pLogicalDevice pointer to the LogicalDevice to create the GPU_MemoryBuffer on.
* @param MemoryRequirements vulkan memory requirements struct.
* @param TargetMemory The type of buffer to target in the logicaldevice.
* @param Type the type of allocation, AllocationType_Linear being in the preallocated buffer, AllocationType_Discrite being a completely new buffer and memory.
* @return @ref GPU_Allocation on success. @ref NULL object on failure.
* @note Internally Synchronized.
*/
GPU_Allocation GPUmalloc(LogicalDevice* pLogicalDevice, VkMemoryRequirements MemoryRequirements, TargetMemoryType TargetMemory, AllocationType Type, uint32_t ThreadIndex)
{
	GPU_Allocation newalloc;
	memset(&newalloc, NULL, sizeof(newalloc));
#ifndef NDEBUG
	if (pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("GPUmalloc()", "pLogicalDevice == NULLPTR");
		return newalloc;
	}
	if (MemoryRequirements.size == NULL)
	{
		Engine_Ref_ObjectError("GPUmalloc()", "MemoryRequirements.size", &MemoryRequirements, "MemoryRequirements.size == NULL");
		return newalloc;
	}
#endif
	uint64_t AlignedSize = AlignNumber(MemoryRequirements.size, MemoryRequirements.alignment);
	if (Type == AllocationType_Linear)
	{
		GPU_MemoryBuffer* TargetBuffer = NULL;
		switch (TargetMemory)
		{
		case TargetMemory_Src:
			TargetBuffer = &pLogicalDevice->SrcBuffer;
			break;
		case TargetMemory_Dst:
			TargetBuffer = &pLogicalDevice->DstBuffer;
			break;
		}
		if (TargetBuffer == NULL)
		{
			Engine_Ref_FunctionError("GPUmalloc()", "TargetBuffer == ", NULL);
			memset(&newalloc, NULL, sizeof(GPU_Allocation));
			return newalloc;
		}

		GPU_ArenaAllocater* pArenaAllocater = NULL;	
		
		if (Engine_Ref_TryLock_Mutex(TargetBuffer->ArenaAllocaters[TargetBuffer->Indexes[ThreadIndex]].mutex) != Success)
		{
			for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
			{
				if (Engine_Ref_TryLock_Mutex(TargetBuffer->ArenaAllocaters[i].mutex) == Success)
				{
					pArenaAllocater = &TargetBuffer->ArenaAllocaters[i];
					TargetBuffer->Indexes[ThreadIndex] = i;
					break;
				}
			}
		}
		else
		{
			pArenaAllocater = &TargetBuffer->ArenaAllocaters[TargetBuffer->Indexes[ThreadIndex]];
		}
		
	//	pArenaAllocater = &TargetBuffer->ArenaAllocaters[0];
	//	Engine_Ref_Lock_Mutex(pArenaAllocater->mutex);

		if (pArenaAllocater == NULL)
		{
			Engine_Ref_FunctionError("GPUmalloc()", "Arena Allocater could not be found. ", pArenaAllocater);
			memset(&newalloc, NULL, sizeof(GPU_Allocation));
			return newalloc;
		}
	label:

		uint64_t Pointer = 0;
		uint64_t sizeofblock = 0;
		uint64_t it = 0;
		for (it = 0; it < pArenaAllocater->AllocationsSize - 1; it++)
		{
			sizeofblock = (pArenaAllocater->Allocations[it + 1].Pointer - pArenaAllocater->Allocations[it].Pointer) - pArenaAllocater->Allocations[it].SizeBytes;
			Pointer = pArenaAllocater->Allocations[it].Pointer + pArenaAllocater->Allocations[it].SizeBytes;
			if (sizeofblock >= AlignedSize)
				break;
		}
		if (sizeofblock < AlignedSize)
		{
			Engine_Ref_Unlock_Mutex(pArenaAllocater->mutex);
			TargetBuffer->Indexes[ThreadIndex]++;
			if (TargetBuffer->Indexes[ThreadIndex] < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads)
			{
				pArenaAllocater = &TargetBuffer->ArenaAllocaters[TargetBuffer->Indexes[ThreadIndex]];
				Engine_Ref_Lock_Mutex(pArenaAllocater->mutex);
				goto label;
			}
			Engine_Ref_FunctionError("GPUmalloc()", "Not Enough Space In GPU Memory!, Resize buffer!, Blocksize == ", sizeofblock);
			memset(&newalloc, NULL, sizeof(GPU_Allocation));
			return newalloc;
		}
		newalloc.Allocater.pArenaAllocater = pArenaAllocater;
		newalloc.Allocater.VkMemory = pArenaAllocater->VkMemory;
		newalloc.TargetMemory = TargetMemory;
		newalloc.AllocationType = AllocationType_Linear;
		newalloc.Pointer = AlignNumber(Pointer, MemoryRequirements.alignment);
		newalloc.SizeBytes = AlignedSize;
		InsertMember_Array((void**)&pArenaAllocater->Allocations, pArenaAllocater->AllocationsSize, it + 1, sizeof(*pArenaAllocater->Allocations), &newalloc, 1);
		pArenaAllocater->AllocationsSize += 1;
		Engine_Ref_Unlock_Mutex(pArenaAllocater->mutex);
		return newalloc;
	}
	else if (Type == AllocationType_Discrite)
	{
		VkMemoryAllocateInfo AllocateInfo;
		AllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		AllocateInfo.allocationSize = AlignedSize;
		AllocateInfo.pNext = NULL;
		switch (TargetMemory)
		{
		case TargetMemory_Src:
			AllocateInfo.memoryTypeIndex = Check_Memory(pLogicalDevice->pPhysicalDevice, MemoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
			break;
		case TargetMemory_Dst:
			AllocateInfo.memoryTypeIndex = Check_Memory(pLogicalDevice->pPhysicalDevice, MemoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
			break;
		}

		if (AllocateInfo.memoryTypeIndex == UINT32_MAX)
		{
			Engine_Ref_FunctionError("GPUmalloc()", "Failed To Find Suitable Memory, MemoryTypeIndex == ", AllocateInfo.memoryTypeIndex);
			memset(&newalloc, NULL, sizeof(GPU_Allocation));
			return newalloc;
		}

		vkAllocateMemory(pLogicalDevice->VkLogicalDevice, &AllocateInfo, NULL, &newalloc.Allocater.VkMemory);
		newalloc.Pointer = 0;
		newalloc.SizeBytes = AlignedSize;
		newalloc.TargetMemory = TargetMemory;
		newalloc.AllocationType = AllocationType_Discrite;
		return newalloc;
	}
	return newalloc;
}
/*
* Added in 1.0.0
* ReCreates a GPU memory buffer of specified size and type.
* @param pLogicalDevice pointer to the LogicalDevice the GPU_MemoryBuffer was created on.
* @param pAllocation pointer to the GPU_Allocation to destroy.
* @note Internally Synchronized.
*/
void GPUfree(LogicalDevice* pLogicalDevice, GPU_Allocation* pAllocation)
{
#ifndef NDEBUG
	if (pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("GPUfree()", "pLogicalDevice == NULLPTR");
		return;
	}
#endif
	if (pAllocation->AllocationType == AllocationType_Linear)
	{
#ifndef NDEBUG
		if (pAllocation->Allocater.pArenaAllocater == NULL)
		{
			Engine_Ref_ObjectError("GPUfree()", "pAllocation.Allocater", pAllocation->Allocater.pArenaAllocater, "pAllocation.Allocater == NULLPTR");
			return;
		}
#endif

		GPU_MemoryBuffer* TargetBuffer = NULL;
		switch (pAllocation->TargetMemory)
		{
		case TargetMemory_Src:
			TargetBuffer = (GPU_MemoryBuffer*)&pLogicalDevice->SrcBuffer;
			break;
		case TargetMemory_Dst:
			TargetBuffer = (GPU_MemoryBuffer*)&pLogicalDevice->DstBuffer;
			break;
		}
		if (TargetBuffer == NULL)
		{
			Engine_Ref_FunctionError("GPUfree()", "TargetBuffer == ", NULL);
			return;
		}
		GPU_ArenaAllocater* pArenaAllocater = pAllocation->Allocater.pArenaAllocater;
		Engine_Ref_Lock_Mutex(pArenaAllocater->mutex);
		for (size_t i = 0; i < pArenaAllocater->AllocationsSize; i++)
		{
			if (pAllocation->Pointer == pArenaAllocater->Allocations[i].Pointer && pAllocation->SizeBytes == pArenaAllocater->Allocations[i].SizeBytes)
			{
				RemoveMember_Array((void**)&pArenaAllocater->Allocations, pArenaAllocater->AllocationsSize, i, sizeof(*pArenaAllocater->Allocations), 1);
				pArenaAllocater->AllocationsSize -= 1;
				memset(pAllocation, NULL, sizeof(*pAllocation));
				Engine_Ref_Unlock_Mutex(pArenaAllocater->mutex);
				return;
			}
		}
		Engine_Ref_FunctionError("GPUfree()", "Allocation Is Invalid.", NULL);
		memset(pAllocation, NULL, sizeof(*pAllocation));
		Engine_Ref_Unlock_Mutex(pArenaAllocater->mutex);
		return;
	}
	else if (pAllocation->AllocationType == AllocationType_Discrite)
	{
		vkFreeMemory(pLogicalDevice->VkLogicalDevice, pAllocation->Allocater.VkMemory, NULL);
		memset(pAllocation, NULL, sizeof(*pAllocation));
		return;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Converters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//common with audio
TEXRESULT Add_XtoTEXIconverter(ConvertXtoTEXI* Converter, uint32_t Identifier)
{
#ifndef NDEBUG
	if (Converter == NULL)
	{
		Engine_Ref_ArgsError("Add_XtoTEXIconverter()", "Converter == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Add_XtoTEXIconverter()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ConvertersToTEXIMutex);
	Resize_Array((void**)&Utils.ConvertersToTEXI, Utils.ConvertersToTEXISize, Utils.ConvertersToTEXISize + 1, sizeof(*Utils.ConvertersToTEXI));
	Utils.ConvertersToTEXI[Utils.ConvertersToTEXISize].pFunction = Converter;
	Utils.ConvertersToTEXI[Utils.ConvertersToTEXISize].Identifier = Identifier;
	Utils.ConvertersToTEXISize++;
	Engine_Ref_Unlock_Mutex(Utils.ConvertersToTEXIMutex);
	return (TEXRESULT)(Success);
}

TEXRESULT Add_TEXItoXconverter(ConvertTEXItoX* Converter, uint32_t Identifier)
{
#ifndef NDEBUG
	if (Converter == NULL)
	{
		Engine_Ref_ArgsError("Add_TEXItoXconverter()", "Converter == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Add_TEXItoXconverter()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ConvertersFromTEXIMutex);
	Resize_Array((void**)&Utils.ConvertersFromTEXI, Utils.ConvertersFromTEXISize, Utils.ConvertersFromTEXISize + 1, sizeof(*Utils.ConvertersFromTEXI));
	Utils.ConvertersFromTEXI[Utils.ConvertersFromTEXISize].pFunction = Converter;
	Utils.ConvertersFromTEXI[Utils.ConvertersFromTEXISize].Identifier = Identifier;
	Utils.ConvertersFromTEXISize++;
	Engine_Ref_Unlock_Mutex(Utils.ConvertersFromTEXIMutex);
	return (TEXRESULT)(Success);
}

TEXRESULT Remove_XtoTEXIconverter(uint32_t Identifier)
{
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Remove_XtoTEXIconverter()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ConvertersToTEXIMutex);
	for (size_t i = 0; i < Utils.ConvertersToTEXISize; i++)
	{
		if (Identifier == Utils.ConvertersToTEXI[i].Identifier)
		{
			RemoveMember_Array((void**)&Utils.ConvertersToTEXI, Utils.ConvertersToTEXISize, i, sizeof(*Utils.ConvertersToTEXI), 1);
			Utils.ConvertersToTEXISize--;
			Engine_Ref_Unlock_Mutex(Utils.ConvertersToTEXIMutex);
			return (TEXRESULT)(Success);
		}
	}
	Engine_Ref_ArgsError("Remove_XtoTEXIconverter()", "Identifier Invalid.");
	Engine_Ref_Unlock_Mutex(Utils.ConvertersToTEXIMutex);
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

TEXRESULT Remove_TEXItoXconverter(uint32_t Identifier)
{
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Remove_TEXItoXconverter()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ConvertersFromTEXIMutex);
	for (size_t i = 0; i < Utils.ConvertersFromTEXISize; i++)
	{
		if (Identifier == Utils.ConvertersFromTEXI[i].Identifier)
		{
			RemoveMember_Array((void**)&Utils.ConvertersFromTEXI, Utils.ConvertersFromTEXISize, i, sizeof(*Utils.ConvertersFromTEXI), 1);
			Utils.ConvertersFromTEXISize--;
			Engine_Ref_Unlock_Mutex(Utils.ConvertersFromTEXIMutex);
			return (TEXRESULT)(Success);
		}
	}
	Engine_Ref_ArgsError("Remove_TEXItoXconverter()", "Identifier Invalid.");
	Engine_Ref_Unlock_Mutex(Utils.ConvertersFromTEXIMutex);
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

TEXRESULT XtoTEXI(FileData* Src, TEXI_HEADER** Dst, uint32_t Identifier) //converts all supported formats to TEXI 
{
#ifndef NDEBUG
	if (Src == NULL)
	{
		Engine_Ref_ArgsError("XtoTEXI()", "Src == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Dst == NULL)
	{
		Engine_Ref_ArgsError("XtoTEXI()", "Dst == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("XtoTEXI()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < Utils.ConvertersToTEXISize; i++)
	{
		if (Identifier == Utils.ConvertersToTEXI[i].Identifier)
		{
			ConvertXtoTEXI* conv = *Utils.ConvertersToTEXI[i].pFunction;
			return conv(Src, Dst);
		}
	}
	Engine_Ref_ArgsError("XtoTEXI()", "Identifier Invalid.");
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

TEXRESULT TEXItoX(TEXI_HEADER* Src, FileData* Dst, uint32_t Identifier) //converts all supported formats from texi 
{
#ifndef NDEBUG
	if (Src == NULL)
	{
		Engine_Ref_ArgsError("TEXItoX()", "Src == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Dst == NULL)
	{
		Engine_Ref_ArgsError("TEXItoX()", "Dst == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("TEXItoX()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < Utils.ConvertersFromTEXISize; i++)
	{
		if (Identifier == Utils.ConvertersFromTEXI[i].Identifier)
		{
			ConvertTEXItoX* conv = *Utils.ConvertersFromTEXI[i].pFunction;
			return conv(Src, Dst);
		}
	}
	Engine_Ref_ArgsError("TEXItoX()", "Identifier Invalid.");
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//common with audio
TEXRESULT Register_GraphicsEffectSignature(GraphicsEffectSignature* pSignature)
{
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("Register_GraphicsEffectSignature()", "pSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif 
	Engine_Ref_Lock_Mutex(Utils.GraphicsEffectSignaturesMutex);
	for (size_t i = 0; i < Utils.GraphicsEffectSignaturesSize; i++)
	{
		if (Utils.GraphicsEffectSignatures[i]->Identifier == pSignature->Identifier)
		{
			Engine_Ref_ArgsError("Register_GraphicsEffectSignature()", "Signature->Identifier Already Used.");
			Engine_Ref_Unlock_Mutex(Utils.GraphicsEffectSignaturesMutex);
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
	}

	Resize_Array((void**)&Utils.GraphicsEffectSignatures, Utils.GraphicsEffectSignaturesSize, Utils.GraphicsEffectSignaturesSize + 1, sizeof(*Utils.GraphicsEffectSignatures));
	Utils.GraphicsEffectSignatures[Utils.GraphicsEffectSignaturesSize] = pSignature;
	Utils.GraphicsEffectSignaturesSize += 1;
	Engine_Ref_Unlock_Mutex(Utils.GraphicsEffectSignaturesMutex);
	return (TEXRESULT)(Success);
}

TEXRESULT DeRegister_GraphicsEffectSignature(GraphicsEffectSignature* pSignature)
{
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("DeRegister_GraphicsEffectSignature()", "pSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.GraphicsEffectSignaturesMutex);
	for (size_t i = 0; i < Utils.GraphicsEffectSignaturesSize; i++)
	{
		if ((uint64_t)Utils.GraphicsEffectSignatures[i]->Identifier == (uint64_t)pSignature->Identifier)
		{
			RemoveMember_Array((void**)&Utils.GraphicsEffectSignatures, Utils.GraphicsEffectSignaturesSize, i, sizeof(*Utils.GraphicsEffectSignatures), 1);
			Utils.GraphicsEffectSignaturesSize -= 1;
			Engine_Ref_Unlock_Mutex(Utils.GraphicsEffectSignaturesMutex);
			return (TEXRESULT)(Success);
		}
	}
	Engine_Ref_ArgsError("DeRegister_GraphicsEffectSignature()", "pSignature Not Found.");
	Engine_Ref_Unlock_Mutex(Utils.GraphicsEffectSignaturesMutex);
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

TEXRESULT Find_GraphicsEffectSignature(GraphicsEffectIdentifier Identifier, GraphicsEffectSignature** ppSignature, GraphicsEffectBufferIndex* pBufferIndex)
{
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Find_GraphicsEffectSignature()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (ppSignature == NULL)
	{
		Engine_Ref_ArgsError("Find_GraphicsEffectSignature()", "ppSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < Utils.GraphicsEffectSignaturesSize; i++)
	{
		if (Utils.GraphicsEffectSignatures[i]->Identifier == Identifier)
		{
			if (ppSignature != NULL)
				*ppSignature = Utils.GraphicsEffectSignatures[i];
			if (pBufferIndex != NULL)
				*pBufferIndex = i;
			return (TEXRESULT)(Success);
		}
	}
	Engine_Ref_ArgsError("Find_GraphicsEffectSignature()", "Identifier Invalid");
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

TEXRESULT Get_GraphicsEffect(ElementGraphics* pElement, GraphicsEffectIdentifier Identifier, void** pReturnEffect)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("Get_GraphicsEffect()", "pElement == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pReturnEffect == NULL)
	{
		Engine_Ref_ArgsError("Get_GraphicsEffect()", "pReturnEffect == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	uint64_t pointer = 0;
	for (size_t i2 = 0; i2 < pElement->EffectsSize; i2++)
	{
		GraphicsEffect* pEffect = (GraphicsEffect*)((void*)((uint64_t)pElement->Effects + pointer));
		if (pEffect->Header.Identifier == Identifier)
		{
			*pReturnEffect = pEffect;
			return (TEXRESULT)(Success);
		}
		pointer += pEffect->Header.AllocationSize;
	}
	Engine_Ref_ArgsError("Get_GraphicsEffect()", "Effect Not Found.");
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Textures & Buffers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* dummy TEXI aka empty object
*/
TEXRESULT Create_DummyTEXI(TEXI_HEADER** pDst, GraphicsFormat Format, uint64_t Width, uint64_t Height, uint64_t Depth, uint64_t MipmapCount, uint64_t InitialSize, uint64_t ImageSize)
{
	TEXI_HEADER* tempdstheader = (TEXI_HEADER*)malloc(sizeof(TEXI_HEADER) + InitialSize);
	memset(tempdstheader, NULL, sizeof(TEXI_HEADER) + InitialSize);

	tempdstheader->Format = Format;
	tempdstheader->Width = Width;
	tempdstheader->Height = Height;
	tempdstheader->Depth = Depth;
	tempdstheader->MipmapCount = MipmapCount;
	tempdstheader->ImageSize = ImageSize;
	tempdstheader->LinearSize = InitialSize;
	*pDst = tempdstheader;
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Texture Atlas Creation Function.
* No compressed formats.
* All images must be exact same format.
* MipMaps Not Supported.
*/
TEXRESULT Create_ImageAtlas(TEXI_HEADER** pSrcImages, uint64_t pSrcImagesSize, TEXI_HEADER** ppDstImage)
{
#ifndef NDEBUG
	if (pSrcImages == NULL)
	{
		Engine_Ref_ArgsError("Create_ImageAtlas()", "pSrcImages == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pSrcImagesSize == NULL)
	{
		Engine_Ref_ArgsError("Create_ImageAtlas()", "pSrcImagesSize == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (ppDstImage == NULL)
	{
		Engine_Ref_ArgsError("Create_ImageAtlas()", "ppDstImage == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	FormatDetails formatdetails = Get_FormatDetails(pSrcImages[0]->Format);

	uint64_t TotalWidth = 0;
	uint64_t TotalHeight = 0;

	uint64_t LargestImageHeight = 0;

	uint64_t* Pointers = (uint64_t*)calloc(pSrcImagesSize, sizeof(*Pointers));
	for (size_t i = 0; i < pSrcImagesSize; i++)
	{
		//image.texoffsets.push_back(glm::vec2(fwidth, textures[i]->Data.height));

		//uint64_t aheight = ((textures[i]->Data.height + 3) / 4);
		//uint64_t awidth = ((textures[i]->Data.width + 3) / 4) * 8;

		TotalWidth += pSrcImages[i]->Width;
		TotalHeight += pSrcImages[i]->Height;

		if (LargestImageHeight < pSrcImages[i]->Height)
			LargestImageHeight = pSrcImages[i]->Height;
	}

	//image.linearSize = ((fwidth + 3) / 4) * ((largtexheightR + 3) / 4) * 8;
	//image.format = VK_FORMAT_BC1_RGBA_UNORM_BLOCK;

	//image.Data.height = largtexheightR;
	//image.Data.width = fwidth;

	TEXRESULT res = Success;
	if ((res = Graphics_Ref_Create_DummyTEXI(ppDstImage, pSrcImages[0]->Format, TotalWidth, LargestImageHeight, 1, 1,
		(TotalWidth * LargestImageHeight) * (formatdetails.Stride / 8), (TotalWidth * LargestImageHeight) * (formatdetails.Stride / 8))) != Success)
		return res;
	TEXI_HEADER* pDstImage = *ppDstImage;

	uint64_t Pointer = 0;
	for (size_t i0 = 0; i0 < LargestImageHeight; i0++)
	{
		for (size_t i1 = 0; i1 < pSrcImagesSize; i1++)
		{
			if (i0 < pSrcImages[i1]->Height)
			{
				memcpy(pDstImage->Data + Pointer, pSrcImages[i1]->Data + Pointers[i1], pSrcImages[i1]->Width * (formatdetails.Stride / 8));
				Pointers[i1] += pSrcImages[i1]->Width * (formatdetails.Stride / 8);
			}
			else
			{
				memset(pDstImage->Data + Pointer, NULL, pSrcImages[i1]->Width * (formatdetails.Stride / 8));
			}
			Pointer += pSrcImages[i1]->Width * (formatdetails.Stride / 8);
		}
	}
	free(Pointers);

	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Converts image pData to a vulkan format, R64G64 -> R32 for example.
* Cant do compressed, decompress first.
* General rule is that it will work with all formats that have components that are under 64bit, even packed formats with variable bitcount work fine.
* Rearranges components correctly, BGRA to RGBA conversions do work properly, converting a depth format to R64 for example wont work.
*/
TEXRESULT Convert_ImageData(TEXI_HEADER** src, GraphicsFormat dstformat)
{
	TEXI_HEADER* psrc = *src;

	FormatDetails srcdetails = Get_FormatDetails(psrc->Format);
	FormatDetails dstdetails = Get_FormatDetails(dstformat);

	FileData filedata;
	filedata.pData = (unsigned char*)malloc(psrc->LinearSize);
	memcpy(filedata.pData, psrc->Data, psrc->LinearSize);
	filedata.LinearSize = psrc->LinearSize;


	Convert_Data(&filedata, &srcdetails, &dstdetails);


	TEXI_HEADER* tempdstheader = (TEXI_HEADER*)malloc(sizeof(TEXI_HEADER) + filedata.LinearSize);
	memcpy(tempdstheader, *src, sizeof(TEXI_HEADER)); //copy header
	free(psrc);
	memcpy(tempdstheader->Data, filedata.pData, filedata.LinearSize);
	free(filedata.pData);

	tempdstheader->Format = dstformat;
	tempdstheader->LinearSize = filedata.LinearSize;
	tempdstheader->Width;
	tempdstheader->Height;
	*src = tempdstheader;

	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* updates either buffer or texture.
*/
TEXRESULT Update_Descriptor(LogicalDevice* pLogicalDevice, VkDescriptorSet Set, uint64_t Binding, uint64_t DstArrayElement, VkDescriptorType Type, VkDescriptorBufferInfo* pBufferInfo, VkDescriptorImageInfo* pImageInfo)
{
#ifndef NDEBUG
	if (pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("Update_Descriptor()", "pLogicalDevice == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Set == NULL)
	{
		Engine_Ref_ArgsError("Update_Descriptor()", "Set == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	VkWriteDescriptorSet DescWrite;
	memset(&DescWrite, NULL, sizeof(DescWrite));
	DescWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	DescWrite.descriptorType = Type;
	DescWrite.dstSet = Set;
	DescWrite.dstBinding = Binding;
	DescWrite.dstArrayElement = DstArrayElement;
	DescWrite.descriptorCount = 1;
	if (pBufferInfo != NULL)
	{
		if (pBufferInfo->buffer == NULL)
		{
			//Engine_Ref_ArgsError("Update_Descriptor()", "pBufferInfo->buffer == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		DescWrite.pBufferInfo = pBufferInfo;
	}
	if (pImageInfo != NULL)
	{
		if (pImageInfo->imageView == NULL)
		{
			//Engine_Ref_ArgsError("Update_Descriptor()", "pImageInfo->imageView == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		DescWrite.pImageInfo = pImageInfo;
	}
	vkUpdateDescriptorSets(pLogicalDevice->VkLogicalDevice, 1, &DescWrite, 0, NULL);

	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
*/
void Destroy_GPU_Texture(LogicalDevice* pLogicalDevice, GPU_Texture* pGPU_Texture)
{
	//if (pGPU_Texture->SrcAllocation.SizeBytes != NULL)
	//	GPUfree(pLogicalDevice, &pGPU_Texture->SrcAllocation);
	if (pGPU_Texture->Allocation.SizeBytes != NULL)
		GPUfree(pLogicalDevice, &pGPU_Texture->Allocation);

	if (pGPU_Texture->VkSampler != NULL)
		vkDestroySampler(pLogicalDevice->VkLogicalDevice, pGPU_Texture->VkSampler, NULL);
	if (pGPU_Texture->VkImageView != NULL)
		vkDestroyImageView(pLogicalDevice->VkLogicalDevice, pGPU_Texture->VkImageView, NULL);
	if (pGPU_Texture->VkImage != NULL)
		vkDestroyImage(pLogicalDevice->VkLogicalDevice, pGPU_Texture->VkImage, NULL);
	memset(pGPU_Texture, 0, sizeof(*pGPU_Texture));
}
/*
* Added in 1.0.0
*/
void Destroy_GPU_Buffer(LogicalDevice* pLogicalDevice, GPU_Buffer* pGPU_Buffer)
{
	//if (pGPU_Buffer->SrcAllocation.SizeBytes != NULL)
	//	GPUfree(pLogicalDevice, &pGPU_Buffer->SrcAllocation);
	if (pGPU_Buffer->Allocation.SizeBytes != NULL)
		GPUfree(pLogicalDevice, &pGPU_Buffer->Allocation);

	if (pGPU_Buffer->VkBuffer != NULL)
		vkDestroyBuffer(pLogicalDevice->VkLogicalDevice, pGPU_Buffer->VkBuffer, NULL);
	memset(pGPU_Buffer, 0, sizeof(*pGPU_Buffer));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Devices
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
*/
uint64_t Get_DeviceIndex(const LogicalDevice* pLogicalDevice)
{
#ifndef NDEBUG
	if (pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("Get_DeviceIndex()", "pLogicalDevice == NULLPTR");
		return UINT64_MAX;
	}
#endif
	for (size_t i = 0; i < Utils.DevicesSize; i++)
	{
		if (&Utils.LogicalDevices[i] == pLogicalDevice)
		{
			return i;
		}
	}

	Engine_Ref_FunctionError("Get_DeviceIndex()", "Device Not Found.", pLogicalDevice);
	return UINT64_MAX;
}
/*
* Added in 1.0.0
*/
void Get_PhysicalDevices(PhysicalDevice** pPhysicalDevices, uint32_t* pPhysicalDevicesSize)
{
#ifndef NDEBUG
	if (pPhysicalDevices == NULL)
	{
		Engine_Ref_ArgsError("Get_PhysicalDevices()", "pPhysicalDevices == NULLPTR");
		return;
	}
	if (pPhysicalDevicesSize == NULL)
	{
		Engine_Ref_ArgsError("Get_PhysicalDevices()", "pPhysicalDevicesSize == NULLPTR");
		return;
	}
#endif

	PhysicalDevice* PhysicalDevices = NULL;
	uint32_t PhysicalDevicesSize = NULL;


	vkEnumeratePhysicalDevices(Utils.Instance, &PhysicalDevicesSize, NULL);
	VkPhysicalDevice* VkPhysicalDevices = (VkPhysicalDevice*)calloc(PhysicalDevicesSize, sizeof(VkPhysicalDevice));
	vkEnumeratePhysicalDevices(Utils.Instance, &PhysicalDevicesSize, VkPhysicalDevices);


	PhysicalDevices = (PhysicalDevice*)calloc(PhysicalDevicesSize, sizeof(PhysicalDevice));

	for (size_t i = 0; i < PhysicalDevicesSize; i++)
	{
		PhysicalDevices[i].VkPhysicalDevice = VkPhysicalDevices[i];

		//capabilities
		vkGetPhysicalDeviceProperties(PhysicalDevices[i].VkPhysicalDevice, &PhysicalDevices[i].Properties);
		vkGetPhysicalDeviceFeatures(PhysicalDevices[i].VkPhysicalDevice, &PhysicalDevices[i].Features);

		vkEnumerateDeviceExtensionProperties(PhysicalDevices[i].VkPhysicalDevice, NULL, (uint32_t*)&PhysicalDevices[i].ExtensionsAvailableSize, NULL);
		if (PhysicalDevices[i].ExtensionsAvailableSize != NULL)
		{
			PhysicalDevices[i].ExtensionsAvailable = (VkExtensionProperties*)calloc(PhysicalDevices[i].ExtensionsAvailableSize, sizeof(VkExtensionProperties));
			vkEnumerateDeviceExtensionProperties(PhysicalDevices[i].VkPhysicalDevice, NULL, (uint32_t*)&PhysicalDevices[i].ExtensionsAvailableSize,
				(VkExtensionProperties*)PhysicalDevices[i].ExtensionsAvailable);
		}

		vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevices[i].VkPhysicalDevice, &PhysicalDevices[i].QueueFamilyPropertiesSize, NULL);
		if (PhysicalDevices[i].QueueFamilyPropertiesSize != 0)
		{
			PhysicalDevices[i].QueueFamilyProperties = (VkQueueFamilyProperties*)calloc(PhysicalDevices[i].QueueFamilyPropertiesSize, sizeof(VkQueueFamilyProperties));
			vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevices[i].VkPhysicalDevice, &PhysicalDevices[i].QueueFamilyPropertiesSize,
				PhysicalDevices[i].QueueFamilyProperties);
		}
	}

	free(VkPhysicalDevices);

	*pPhysicalDevices = PhysicalDevices;
	*pPhysicalDevicesSize = PhysicalDevicesSize;
}
/*
* Added in 1.0.0
*/
void Clear_PhysicalDevice(PhysicalDevice* pPhysicalDevice)
{
#ifndef NDEBUG
	if (pPhysicalDevice == NULL)
	{
		Engine_Ref_ArgsError("Clear_PhysicalDevice()", "pPhysicalDevice == NULLPTR");
		return;
	}
#endif

	if (pPhysicalDevice->ExtensionsAvailable != NULL && pPhysicalDevice->ExtensionsAvailableSize != NULL)
		free(pPhysicalDevice->ExtensionsAvailable);

	if (pPhysicalDevice->QueueFamilyProperties != NULL && pPhysicalDevice->QueueFamilyPropertiesSize != NULL)
		free(pPhysicalDevice->QueueFamilyProperties);

	memset(pPhysicalDevice, NULL, sizeof(*pPhysicalDevice));
}
/*
* Added in 1.0.0
*/
void Destroy_LogicalDevice(LogicalDevice* pLogicalDevice)
{
#ifndef NDEBUG
	if (pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("Create_LogicalDevice()", "pLogicalDevice == NULLPTR");
		return;
	}
#endif

	for (size_t i = 0; i < pLogicalDevice->GraphicsQueueFamilySize; i++)
		Engine_Ref_Destroy_Mutex(pLogicalDevice->GraphicsQueueMutexes[i]);
	for (size_t i = 0; i < pLogicalDevice->MemoryQueueFamilySize; i++)
		Engine_Ref_Destroy_Mutex(pLogicalDevice->MemoryQueueMutexes[i]);
	for (size_t i = 0; i < pLogicalDevice->ComputeQueueFamilySize; i++)
		Engine_Ref_Destroy_Mutex(pLogicalDevice->ComputeQueueMutexes[i]);

	free(pLogicalDevice->GraphicsQueueMutexes);
	free(pLogicalDevice->MemoryQueueMutexes);
	free(pLogicalDevice->ComputeQueueMutexes);

	//allocating related
	Destroy_GPU_MemoryBuffer(&pLogicalDevice->SrcBuffer, pLogicalDevice);
	Destroy_GPU_MemoryBuffer(&pLogicalDevice->DstBuffer, pLogicalDevice);

	vkDestroyDevice(pLogicalDevice->VkLogicalDevice, NULL);

	memset(pLogicalDevice, NULL, sizeof(*pLogicalDevice));
}
/*
* Added in 1.0.0
*/
TEXRESULT Create_LogicalDevice(LogicalDevice* pLogicalDevice, const PhysicalDevice* pPhysicalDevice, char** ppValidationLayers, size_t ValidationLayersSize,
	char** ppDeviceExtensions, size_t DeviceExtensionsSize, const VkPhysicalDeviceFeatures* pEnabledFeatures, uint64_t InitialStagingGPUBufferSize, uint64_t InitialNativeGPUBufferSize)
{
#ifndef NDEBUG
	if (pPhysicalDevice == NULL)
	{
		Engine_Ref_ArgsError("Create_LogicalDevice()", "pPhysicalDevice == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("Create_LogicalDevice()", "pLogicalDevice == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif

	VkResult res = VK_SUCCESS;

	pLogicalDevice->pPhysicalDevice = pPhysicalDevice;

	uint32_t DeviceQueueCreateInfosSize = 3;
	VkDeviceQueueCreateInfo DeviceQueueCreateInfos[3];
	memset(DeviceQueueCreateInfos, NULL, sizeof(*DeviceQueueCreateInfos) * DeviceQueueCreateInfosSize);
	bool GraphicsQueueFamily_Found = false;
	bool MemoryQueueFamily_Found = false;
	bool ComputeQueueFamily_Found = false;

	for (size_t i1 = 0; i1 < pPhysicalDevice->QueueFamilyPropertiesSize; i1++)
	{
		if ((pPhysicalDevice->QueueFamilyProperties[i1].queueFlags & VK_QUEUE_GRAPHICS_BIT)
			&& GraphicsQueueFamily_Found == false)
		{
			DeviceQueueCreateInfos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			DeviceQueueCreateInfos[0].pQueuePriorities = NULL;
			DeviceQueueCreateInfos[0].queueFamilyIndex = i1;
			DeviceQueueCreateInfos[0].queueCount = pPhysicalDevice->QueueFamilyProperties[i1].queueCount;

			pLogicalDevice->GraphicsQueueFamilyIndex = i1;
			pLogicalDevice->GraphicsQueueFamilySize = pPhysicalDevice->QueueFamilyProperties[i1].queueCount;
			GraphicsQueueFamily_Found = true;
		}

		//primary memqueue
		if (((pPhysicalDevice->QueueFamilyProperties[i1].queueFlags == (VK_QUEUE_TRANSFER_BIT)) ||
			(pPhysicalDevice->QueueFamilyProperties[i1].queueFlags == (VK_QUEUE_TRANSFER_BIT | VK_QUEUE_SPARSE_BINDING_BIT)))
			&& MemoryQueueFamily_Found == false)
		{
			DeviceQueueCreateInfos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			DeviceQueueCreateInfos[1].pQueuePriorities = NULL;
			DeviceQueueCreateInfos[1].queueFamilyIndex = i1;
			DeviceQueueCreateInfos[1].queueCount = pPhysicalDevice->QueueFamilyProperties[i1].queueCount;

			pLogicalDevice->MemoryQueueFamilyIndex = i1;
			pLogicalDevice->MemoryQueueFamilySize = pPhysicalDevice->QueueFamilyProperties[i1].queueCount;
			MemoryQueueFamily_Found = true;
		}

		//backup memqueue
		if ((pPhysicalDevice->QueueFamilyProperties[i1].queueFlags & VK_QUEUE_TRANSFER_BIT)
			&& MemoryQueueFamily_Found == false)
		{
			DeviceQueueCreateInfos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			DeviceQueueCreateInfos[1].pQueuePriorities = NULL;
			DeviceQueueCreateInfos[1].queueFamilyIndex = i1;
			DeviceQueueCreateInfos[1].queueCount = pPhysicalDevice->QueueFamilyProperties[i1].queueCount;

			pLogicalDevice->MemoryQueueFamilyIndex = i1;
			pLogicalDevice->MemoryQueueFamilySize = pPhysicalDevice->QueueFamilyProperties[i1].queueCount;
		}

		//primary computequeue
		if (((pPhysicalDevice->QueueFamilyProperties[i1].queueFlags == (VK_QUEUE_COMPUTE_BIT)) ||
			(pPhysicalDevice->QueueFamilyProperties[i1].queueFlags == (VK_QUEUE_COMPUTE_BIT | VK_QUEUE_SPARSE_BINDING_BIT)))
			&& ComputeQueueFamily_Found == false)
		{
			DeviceQueueCreateInfos[2].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			DeviceQueueCreateInfos[2].pQueuePriorities = NULL;
			DeviceQueueCreateInfos[2].queueFamilyIndex = i1;
			DeviceQueueCreateInfos[2].queueCount = pPhysicalDevice->QueueFamilyProperties[i1].queueCount;

			pLogicalDevice->ComputeQueueFamilyIndex = i1;
			pLogicalDevice->ComputeQueueFamilySize = pPhysicalDevice->QueueFamilyProperties[i1].queueCount;
			MemoryQueueFamily_Found = true;
		}

		//backup computequeue
		if ((pPhysicalDevice->QueueFamilyProperties[i1].queueFlags & VK_QUEUE_COMPUTE_BIT)
			&& ComputeQueueFamily_Found == false)
		{
			DeviceQueueCreateInfos[2].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			DeviceQueueCreateInfos[2].pQueuePriorities = NULL;
			DeviceQueueCreateInfos[2].queueFamilyIndex = i1;
			DeviceQueueCreateInfos[2].queueCount = pPhysicalDevice->QueueFamilyProperties[i1].queueCount;

			pLogicalDevice->ComputeQueueFamilyIndex = i1;
			pLogicalDevice->ComputeQueueFamilySize = pPhysicalDevice->QueueFamilyProperties[i1].queueCount;
		}

	}

	DeviceQueueCreateInfos[0].pQueuePriorities = (float*)calloc(DeviceQueueCreateInfos[0].queueCount, sizeof(float));
	DeviceQueueCreateInfos[1].pQueuePriorities = (float*)calloc(DeviceQueueCreateInfos[1].queueCount, sizeof(float));
	DeviceQueueCreateInfos[2].pQueuePriorities = (float*)calloc(DeviceQueueCreateInfos[2].queueCount, sizeof(float));
	if (DeviceQueueCreateInfos[0].pQueuePriorities == NULL || DeviceQueueCreateInfos[1].pQueuePriorities == NULL || DeviceQueueCreateInfos[2].pQueuePriorities == NULL)
	{
		Engine_Ref_FunctionError("Create_LogicalDevice()", "Out Of Memory. ", NULL);
		return (TEXRESULT)(Out_Of_Memory_Result);
	}

	pLogicalDevice->GraphicsQueueMutexes = calloc(DeviceQueueCreateInfos[0].queueCount, sizeof(*pLogicalDevice->GraphicsQueueMutexes));
	pLogicalDevice->MemoryQueueMutexes = calloc(DeviceQueueCreateInfos[1].queueCount, sizeof(*pLogicalDevice->MemoryQueueMutexes));
	pLogicalDevice->ComputeQueueMutexes = calloc(DeviceQueueCreateInfos[2].queueCount, sizeof(*pLogicalDevice->ComputeQueueMutexes));
	if (pLogicalDevice->GraphicsQueueMutexes == NULL || pLogicalDevice->MemoryQueueMutexes == NULL || pLogicalDevice->ComputeQueueMutexes == NULL)
	{
		Engine_Ref_FunctionError("Create_LogicalDevice()", "Out Of Memory. ", NULL);
		return (TEXRESULT)(Out_Of_Memory_Result);
	}

	for (size_t i = 0; i < pLogicalDevice->GraphicsQueueFamilySize; i++)
		Engine_Ref_Create_Mutex(pLogicalDevice->GraphicsQueueMutexes[i], MutexType_Plain);
	for (size_t i = 0; i < pLogicalDevice->MemoryQueueFamilySize; i++)
		Engine_Ref_Create_Mutex(pLogicalDevice->MemoryQueueMutexes[i], MutexType_Plain);
	for (size_t i = 0; i < pLogicalDevice->ComputeQueueFamilySize; i++)
		Engine_Ref_Create_Mutex(pLogicalDevice->ComputeQueueMutexes[i], MutexType_Plain);

	vkGetPhysicalDeviceMemoryProperties(pLogicalDevice->pPhysicalDevice->VkPhysicalDevice, (VkPhysicalDeviceMemoryProperties*)&pLogicalDevice->pPhysicalDevice->MemoryProperties);
	{
		VkDeviceCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		Info.enabledLayerCount = (uint32_t)ValidationLayersSize;
		Info.ppEnabledLayerNames = ppValidationLayers;

		Info.enabledExtensionCount = (uint32_t)DeviceExtensionsSize;
		Info.ppEnabledExtensionNames = ppDeviceExtensions;

		Info.queueCreateInfoCount = DeviceQueueCreateInfosSize;
		Info.pQueueCreateInfos = DeviceQueueCreateInfos;

		Info.pEnabledFeatures = pEnabledFeatures;
		Info.flags = NULL;
		Info.pNext = NULL;
		
		if ((res = vkCreateDevice(pLogicalDevice->pPhysicalDevice->VkPhysicalDevice, &Info, NULL, &pLogicalDevice->VkLogicalDevice)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("Create_LogicalDevice()", "vkCreateDevice Failed With Error == ", res);
			return (TEXRESULT)(Failure);
		}
	}

	free((void*)DeviceQueueCreateInfos[0].pQueuePriorities);
	free((void*)DeviceQueueCreateInfos[1].pQueuePriorities);
	free((void*)DeviceQueueCreateInfos[2].pQueuePriorities);

	memset(&pLogicalDevice->SrcBuffer, NULL, sizeof(pLogicalDevice->SrcBuffer));
	memset(&pLogicalDevice->DstBuffer, NULL, sizeof(pLogicalDevice->DstBuffer));
	
	Create_GPU_MemoryBuffer(&pLogicalDevice->SrcBuffer, pLogicalDevice, InitialStagingGPUBufferSize, TargetMemory_Src);
	Create_GPU_MemoryBuffer(&pLogicalDevice->DstBuffer, pLogicalDevice, InitialNativeGPUBufferSize, TargetMemory_Dst);

	return (TEXRESULT)(Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Swapchain
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* FullDestruct destroys everything.
*/
void Destroy_SwapChain(RHeaderGraphicsWindow* pGraphicsWindow, bool FullDestruct)
{
#ifndef NDEBUG
	if (pGraphicsWindow == NULL)
	{
		Engine_Ref_ArgsError("Destroy_SwapChain()", "pGraphicsWindow == NULLPTR");
		return;
	}
#endif

	if (pGraphicsWindow->SwapChain.FrameBuffers != NULL && pGraphicsWindow->CurrentFrameBuffersSize != NULL)
	{
		c89atomic_flag_test_and_set(&pGraphicsWindow->CloseFlag);
		//pGraphicsWindow->Close_Flag = true;
		for (size_t i = 0; i < pGraphicsWindow->CurrentFrameBuffersSize; i++)
		{
			while (pGraphicsWindow->SwapChain.FrameBuffers[i].RenderingFlag == true)
			{
				struct timespec dur;
				memset(&dur, 0, sizeof(dur));
				dur.tv_nsec = 1;
				Engine_Ref_Sleep_Thread(&dur, NULL);
			}
		}
		//pGraphicsWindow->Close_Flag = false;
		c89atomic_flag_clear(&pGraphicsWindow->CloseFlag);


		for (size_t i = 0; i < pGraphicsWindow->CurrentFrameBuffersSize; i++)
		{
			if (pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderFinishedSemaphore != NULL)
				vkDestroySemaphore(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderFinishedSemaphore, NULL);
			pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderFinishedSemaphore = NULL;
			if (pGraphicsWindow->SwapChain.FrameBuffers[i].VkImageAvailableSemaphore != NULL)
				vkDestroySemaphore(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.FrameBuffers[i].VkImageAvailableSemaphore, NULL);
			pGraphicsWindow->SwapChain.FrameBuffers[i].VkImageAvailableSemaphore = NULL;
			if (pGraphicsWindow->SwapChain.FrameBuffers[i].VkFrameFence != NULL)
				vkDestroyFence(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.FrameBuffers[i].VkFrameFence, NULL);
			pGraphicsWindow->SwapChain.FrameBuffers[i].VkFrameFence = NULL;
			if (pGraphicsWindow->SwapChain.FrameBuffers[i].VkSwapChainImageView != NULL)
				vkDestroyImageView(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.FrameBuffers[i].VkSwapChainImageView, NULL);
			pGraphicsWindow->SwapChain.FrameBuffers[i].VkSwapChainImageView = NULL;
			if (pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderCommandBuffer != NULL)
				vkFreeCommandBuffers(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderCommandPool, 1, &pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderCommandBuffer);
			pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderCommandBuffer = NULL;

			for (size_t i1 = 0; i1 < DeferredImageCount; i1++)
			{
				if (pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].ImageView != NULL)
					vkDestroyImageView(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].ImageView, NULL);
				pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].ImageView = NULL;
				if (pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Image != NULL)
					vkDestroyImage(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Image, NULL);
				pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Image = NULL;
				if (pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Memory != NULL)
					vkFreeMemory(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Memory, NULL);
				pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Memory = NULL;
			}
			if (pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderCommandPool != NULL)
				vkDestroyCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderCommandPool, NULL);
			pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderCommandPool = NULL;
		}
	}


	if (FullDestruct == true)
	{
		free(pGraphicsWindow->SwapChain.FrameBuffers);
		pGraphicsWindow->SwapChain.FrameBuffers = NULL;
		pGraphicsWindow->CurrentFrameBuffersSize = NULL;
		//memset(&pGraphicsWindow->CurrentSurfaceColourSpace, NULL, sizeof(pGraphicsWindow->CurrentSurfaceColourSpace));
		//memset(&pGraphicsWindow->CurrentSurfaceFormat, NULL, sizeof(pGraphicsWindow->CurrentSurfaceFormat));
		//memset(&pGraphicsWindow->CurrentSurfacePresentMode, NULL, sizeof(pGraphicsWindow->CurrentSurfacePresentMode));
		//memset(&pGraphicsWindow->CurrentExtentHeight, NULL, sizeof(pGraphicsWindow->CurrentExtentHeight));
		//memset(&pGraphicsWindow->CurrentExtentWidth, NULL, sizeof(pGraphicsWindow->CurrentExtentWidth));


		if (pGraphicsWindow->SwapChain.VkSwapChain != NULL)
			vkDestroySwapchainKHR(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.VkSwapChain, NULL);
		pGraphicsWindow->SwapChain.VkSwapChain = NULL;
		memset(&pGraphicsWindow->SwapChain, NULL, sizeof(pGraphicsWindow->SwapChain));
	}
}
/*
* Added in 1.0.0
* FullDestruct when creating for first time.
*/
TEXRESULT ReCreate_SwapChain(RHeaderGraphicsWindow* pGraphicsWindow, bool FullDestruct)
{

#ifndef NDEBUG
	if (pGraphicsWindow == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_SwapChain()", "pGraphicsWindow == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	VkResult res = VK_SUCCESS;

	const PhysicalDevice* pPhysicalDevice = pGraphicsWindow->pLogicalDevice->pPhysicalDevice;

	//destroy prev
	Destroy_SwapChain(pGraphicsWindow, FullDestruct);

	//creation
	{
		VkSurfaceCapabilitiesKHR Capabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pPhysicalDevice->VkPhysicalDevice, pGraphicsWindow->VkSurface, &Capabilities);

		pGraphicsWindow->CurrentFrameBuffersSize = pGraphicsWindow->TargetFrameBuffersSize;
		pGraphicsWindow->CurrentFrameBuffersSize = (pGraphicsWindow->CurrentFrameBuffersSize > Capabilities.maxImageCount) ? Capabilities.maxImageCount : pGraphicsWindow->CurrentFrameBuffersSize;
		pGraphicsWindow->CurrentFrameBuffersSize = (pGraphicsWindow->CurrentFrameBuffersSize < Capabilities.minImageCount) ? Capabilities.minImageCount : pGraphicsWindow->CurrentFrameBuffersSize;

		pGraphicsWindow->CurrentExtentWidth = pGraphicsWindow->TargetExtentWidth;
		pGraphicsWindow->CurrentExtentWidth = (pGraphicsWindow->CurrentExtentWidth > Capabilities.maxImageExtent.width) ? Capabilities.maxImageExtent.width : pGraphicsWindow->CurrentExtentWidth;
		pGraphicsWindow->CurrentExtentWidth = (pGraphicsWindow->CurrentExtentWidth < Capabilities.minImageExtent.width) ? Capabilities.minImageExtent.width : pGraphicsWindow->CurrentExtentWidth;

		pGraphicsWindow->CurrentExtentHeight = pGraphicsWindow->TargetExtentHeight;
		pGraphicsWindow->CurrentExtentHeight = (pGraphicsWindow->CurrentExtentHeight > Capabilities.maxImageExtent.height) ? Capabilities.maxImageExtent.height : pGraphicsWindow->CurrentExtentHeight;
		pGraphicsWindow->CurrentExtentHeight = (pGraphicsWindow->CurrentExtentHeight < Capabilities.minImageExtent.height) ? Capabilities.minImageExtent.height : pGraphicsWindow->CurrentExtentHeight;

		if ((Capabilities.currentExtent.width = NULL) || (Capabilities.currentExtent.height == NULL))
		{
			return (TEXRESULT)(Invalid_Parameter);
		}


		VkSwapchainCreateInfoKHR Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		Info.surface = pGraphicsWindow->VkSurface;
		Info.minImageCount = pGraphicsWindow->CurrentFrameBuffersSize;
		Info.imageFormat = pGraphicsWindow->CurrentSurfaceFormat;
		Info.imageColorSpace = pGraphicsWindow->CurrentSurfaceColourSpace;
		Info.imageExtent.width = pGraphicsWindow->CurrentExtentWidth;
		Info.imageExtent.height = pGraphicsWindow->CurrentExtentHeight;
		Info.imageArrayLayers = 1;
		Info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		Info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; //mayby for compatibility???

		Info.queueFamilyIndexCount = 1;
		Info.pQueueFamilyIndices = &pGraphicsWindow->pLogicalDevice->GraphicsQueueFamilyIndex;

		Info.preTransform = Capabilities.currentTransform;
		Info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		Info.presentMode = pGraphicsWindow->CurrentSurfacePresentMode;
		Info.clipped = VK_TRUE;

		if (pGraphicsWindow->SwapChain.VkSwapChain != NULL)
			Info.oldSwapchain = pGraphicsWindow->SwapChain.VkSwapChain;
		else
			Info.oldSwapchain = NULL;
		if ((res = vkCreateSwapchainKHR(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGraphicsWindow->SwapChain.VkSwapChain)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_SwapChain()", "vkCreateSwapchainKHR Failed, VkResult == ", res);
			return (TEXRESULT)(Failure);
		}

		vkDestroySwapchainKHR(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, Info.oldSwapchain, NULL);
	}
	{//moving swapchain images to framebuffers
		vkGetSwapchainImagesKHR(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.VkSwapChain, &pGraphicsWindow->CurrentFrameBuffersSize, NULL);

		if (FullDestruct == true)
			pGraphicsWindow->SwapChain.FrameBuffers = (SwapChainFrameBuffer*)calloc(pGraphicsWindow->CurrentFrameBuffersSize, sizeof(SwapChainFrameBuffer));

		VkImage* TempSwapchainImages = (VkImage*)calloc(pGraphicsWindow->CurrentFrameBuffersSize, sizeof(VkImage));
		vkGetSwapchainImagesKHR(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.VkSwapChain, &pGraphicsWindow->CurrentFrameBuffersSize, TempSwapchainImages);

		for (size_t i = 0; i < pGraphicsWindow->CurrentFrameBuffersSize; i++) //do this to get into structs
			pGraphicsWindow->SwapChain.FrameBuffers[i].VkSwapChainImage = TempSwapchainImages[i];
		free(TempSwapchainImages);
	}

	//create swapchain image views
	for (size_t i = 0; i < pGraphicsWindow->CurrentFrameBuffersSize; i++)
	{
		{//semaphores
			VkSemaphoreCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
			Info.flags = NULL;
			Info.pNext = NULL;
			if ((res = vkCreateSemaphore(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGraphicsWindow->SwapChain.FrameBuffers[i].VkImageAvailableSemaphore)) ||
				vkCreateSemaphore(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderFinishedSemaphore) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_SwapChain()", "vkCreateSemaphore Failed, VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}

		{//fences
			VkFenceCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
			Info.flags = NULL;
			Info.pNext = NULL;
			if ((res = vkCreateFence(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGraphicsWindow->SwapChain.FrameBuffers[i].VkFrameFence)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_SwapChain()", "vkCreateFence Failed, VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}



		//create deferred images
		for (size_t i1 = 0; i1 < DeferredImageCount; i1++) //shared framebuffers
		{
			{ //image
				VkImageCreateInfo Info;
				memset(&Info, NULL, sizeof(Info));
				Info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
				Info.imageType = VK_IMAGE_TYPE_2D; //cubemap?
				Info.extent.width = pGraphicsWindow->CurrentExtentWidth;
				Info.extent.height = pGraphicsWindow->CurrentExtentHeight;
				Info.extent.depth = 1; //cubemap?
				Info.mipLevels = 1; //mipmap
				Info.arrayLayers = 1; //cubemap?
				Info.format = DeferredFormats[i1];
				Info.tiling = VK_IMAGE_TILING_OPTIMAL;
				Info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
				Info.usage = DeferredImageUsages[i1] | VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
				Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
				Info.samples = VK_SAMPLE_COUNT_1_BIT;
				Info.flags = NULL;
				if ((res = vkCreateImage(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Image)) != VK_SUCCESS)
				{
					Engine_Ref_FunctionError("ReCreate_SwapChain()", "vkCreateImage Failed, VkResult == ", res);
					return (TEXRESULT)(Failure);
				}
			}
			{//allocating memory
				VkMemoryRequirements memRequirements;
				vkGetImageMemoryRequirements(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Image, &memRequirements);

				VkMemoryAllocateInfo AllocationInfo;
				AllocationInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
				AllocationInfo.allocationSize = memRequirements.size;
				AllocationInfo.memoryTypeIndex = Check_Memory(pGraphicsWindow->pLogicalDevice->pPhysicalDevice, memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
				AllocationInfo.pNext = NULL;
				if (AllocationInfo.memoryTypeIndex == UINT32_MAX)
				{
					Engine_Ref_FunctionError("ReCreate_SwapChain()", "Suitable Memory Not Found. ", NULL);
					return (TEXRESULT)(Failure);
				}

				if ((res = vkAllocateMemory(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &AllocationInfo, NULL, &pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Memory)) != VK_SUCCESS)
				{
					Engine_Ref_FunctionError("ReCreate_SwapChain()", "vkAllocateMemory Failed, VkResult == ", res);
					return (TEXRESULT)(Failure);
				}


				vkBindImageMemory(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Image, pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Memory, 0);

			}
			{//image view
				VkImageViewCreateInfo Info;
				memset(&Info, NULL, sizeof(Info));
				Info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				Info.image = pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].Image;
				Info.viewType = VK_IMAGE_VIEW_TYPE_2D; //cubemap?
				Info.format = DeferredFormats[i1];

				Info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
				Info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
				Info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
				Info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

				Info.subresourceRange.aspectMask = DeferredImageAspects[i1]; //parameter?
				Info.subresourceRange.baseMipLevel = 0;
				Info.subresourceRange.levelCount = 1; //mipmap
				Info.subresourceRange.baseArrayLayer = 0;
				Info.subresourceRange.layerCount = 1;

				if ((res = vkCreateImageView(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGraphicsWindow->SwapChain.FrameBuffers[i].DeferredImages[i1].ImageView)) != VK_SUCCESS)
				{
					Engine_Ref_FunctionError("ReCreate_SwapChain()", "vkCreateImageView Failed, VkResult == ", res);
					return (TEXRESULT)(Failure);
				}
			}
		}

		{//swapchain image view
			VkImageViewCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			Info.image = pGraphicsWindow->SwapChain.FrameBuffers[i].VkSwapChainImage;

			Info.viewType = VK_IMAGE_VIEW_TYPE_2D;

			Info.format = pGraphicsWindow->CurrentSurfaceFormat;

			Info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			Info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			Info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			Info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			Info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Info.subresourceRange.baseMipLevel = 0;
			Info.subresourceRange.levelCount = 1;
			Info.subresourceRange.baseArrayLayer = 0;
			Info.subresourceRange.layerCount = 1;

			if ((res = vkCreateImageView(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGraphicsWindow->SwapChain.FrameBuffers[i].VkSwapChainImageView)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_SwapChain()", "vkCreateImageView Failed. VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}


		{//cmd pool
			VkCommandPoolCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
			Info.queueFamilyIndex = pGraphicsWindow->pLogicalDevice->GraphicsQueueFamilyIndex;
			Info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT; // Optional
			Info.pNext = NULL;
			if ((res = vkCreateCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderCommandPool)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_SwapChain()", "vkCreateCommandPool Failed. VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}

		{//render cmd buffer
			VkCommandBufferAllocateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
			Info.commandPool = pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderCommandPool;
			Info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
			Info.commandBufferCount = 1;
			Info.pNext = NULL;
			if ((res = vkAllocateCommandBuffers(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, &pGraphicsWindow->SwapChain.FrameBuffers[i].VkRenderCommandBuffer)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_SwapChain()", "vkAllocateCommandBuffers Failed. VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}
	}

	return (TEXRESULT)(Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Object Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Destroy_WeightsHeader(RHeaderWeights* pResourceHeader, bool Full, uint32_t ThreadIndex)
{

}

void Destroy_ImageSourceHeader(RHeaderImageSource* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	if (Full == true)
	{
		if (pResourceHeader->ImageData != NULL)
			free(pResourceHeader->ImageData);
	}
}

void Destroy_BufferSourceHeader(RHeaderBufferSource* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	if (Full == true)
	{
		if (pResourceHeader->Data.pData != NULL)
			free(pResourceHeader->Data.pData);
	}
}

void Destroy_GraphicsWindowHeader(RHeaderGraphicsWindow* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	if (pResourceHeader->VkPipelineDeferred != NULL)
		vkDestroyPipeline(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineDeferred, NULL);
	if (pResourceHeader->VkRenderPassDeferred != NULL)
		vkDestroyRenderPass(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkRenderPassDeferred, NULL);

	if (pResourceHeader->VkPipelineLayoutDeferred != NULL)
		vkDestroyPipelineLayout(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineLayoutDeferred, NULL);


	if (pResourceHeader->VkDescriptorSetLayoutInputAttachment != NULL)
		vkDestroyDescriptorSetLayout(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorSetLayoutInputAttachment, NULL);

	if (pResourceHeader->VkShaderVertexDeferred != NULL)
		vkDestroyShaderModule(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderVertexDeferred, NULL);
	if (pResourceHeader->VkShaderFragmentDeferred != NULL)
		vkDestroyShaderModule(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderFragmentDeferred, NULL);

	if (pResourceHeader->VkDescriptorSetsInputAttachment != NULL)
	{
		//vkFreeDescriptorSets(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkWindowDescriptorPool, pResourceHeader->CurrentFrameBuffersSize, pResourceHeader->VkDescriptorSetsInputAttachment);
		free(pResourceHeader->VkDescriptorSetsInputAttachment);
	}
	if (pResourceHeader->VkDescriptorPoolDeferred != NULL)
		vkDestroyDescriptorPool(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorPoolDeferred, NULL);

	Destroy_SwapChain(pResourceHeader, true);

	if (pResourceHeader->VkSurface != NULL)
		vkDestroySurfaceKHR(Utils.Instance, pResourceHeader->VkSurface, NULL);

	if (pResourceHeader->pWindow != NULL)
		Engine_Ref_Destroy_Window(pResourceHeader->pWindow, pResourceHeader->Header.Name);

	Engine_Ref_Destroy_Mutex(pResourceHeader->SwapChainAccessMutex);

	if (Full == true)
	{

	}
}

void Destroy_SceneHeader(RHeaderScene* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
}

void Destroy_CameraHeader(RHeaderCamera* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
}

void Destroy_LightHeader(RHeaderLight* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
}

void Destroy_SkinHeader(RHeaderSkin* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
}

void Destroy_PositionHeader(RHeaderPosition* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
}

void Destroy_AnimationChannelHeader(RHeaderAnimationChannel* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
}

void Destroy_AnimationHeader(RHeaderAnimation* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
}

void Destroy_MaterialHeader(RHeaderMaterial* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
	if (pResourceHeader->VkMaterialDescriptorSets != NULL)
	{
		//vkFreeDescriptorSets(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkMaterialDescriptorPool, pGraphicsWindow->CurrentFrameBuffersSize, pResourceHeader->VkMaterialDescriptorSets);
		free(pResourceHeader->VkMaterialDescriptorSets);
	}

	if (pResourceHeader->VkMaterialDescriptorPool != NULL)
		vkDestroyDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkMaterialDescriptorPool, NULL);

	if (Full == true)
	{

	}
}

void Destroy_TextureHeader(RHeaderTexture* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
	Destroy_GPU_Texture(pGraphicsWindow->pLogicalDevice, &pResourceHeader->GPU_Texture);
	if (Full == true)
	{

	}
}

void Destroy_BufferHeader(RHeaderBuffer* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
	Destroy_GPU_Buffer(pGraphicsWindow->pLogicalDevice, &pResourceHeader->GPU_Buffer);
	if (Full == true)
	{

	}
}

void Destroy_RenderHeader(RHeaderRender* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
	if (pResourceHeader->pFrameBuffers != NULL)
	{
		for (size_t i1 = 0; i1 < pResourceHeader->pFrameBuffersSize; i1++)
		{
			vkDestroyFramebuffer(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pResourceHeader->pFrameBuffers[i1], NULL);
		}
		free(pResourceHeader->pFrameBuffers);
	}

	if (Full == true)
	{

	}
}

void Destroy_ElementGraphics(ElementGraphics* pElement, bool Full, uint32_t ThreadIndex)
{
	uint64_t pointer = 0;
	for (size_t i = 0; i < pElement->EffectsSize; i++)
	{
		GraphicsEffect* pEffect = (GraphicsEffect*)((void*)((uint64_t)pElement->Effects + pointer));
		GraphicsEffectSignature* pSignature = NULL;
		uint64_t BufferIndex = NULL;
		Find_GraphicsEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
		if (pSignature->Destructor != NULL)
		{
			pSignature->Destructor(pElement, pEffect, Full, ThreadIndex);
		}
		pointer += pEffect->Header.AllocationSize;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Object ReCreation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ReCreate_GraphicsWindowHeader(RHeaderGraphicsWindow* pResourceHeader, uint32_t ThreadIndex)
{
	VkResult res = VK_SUCCESS;
	Engine_Ref_Create_Mutex(pResourceHeader->SwapChainAccessMutex, MutexType_Plain);
	Engine_Ref_Create_Window(&pResourceHeader->pWindow, pResourceHeader->TargetExtentWidth, pResourceHeader->TargetExtentHeight,
		pResourceHeader->Header.Name, NULL, NULL);

#ifdef _WIN32
	{
		VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo;
		memset(&SurfaceCreateInfo, 0, sizeof(SurfaceCreateInfo));
		SurfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		SurfaceCreateInfo.hinstance = (HINSTANCE)((EngineUtils*)EngineRes.pUtils)->win32.Instance;
		SurfaceCreateInfo.hwnd = (HWND)pResourceHeader->pWindow->Window;
		SurfaceCreateInfo.flags = 0;
		SurfaceCreateInfo.pNext = NULL;
		if ((res = vkCreateWin32SurfaceKHR(Utils.Instance, &SurfaceCreateInfo, NULL, &pResourceHeader->VkSurface)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_GraphicsWindowHeader()", "Surface Creation Failed. VkResult == ", res);
			return;
		}
	}
#endif

	//checking what device is most suitable
	size_t DeviceHighScore = 0;
	size_t DeviceHighScoreIndex = 0;
	for (size_t i = 0; i < Utils.DevicesSize; i++)
	{
		size_t CurrentDeviceScore = 0;
		const PhysicalDevice* pPhysicalDevice = &Utils.PhysicalDevices[i];

		VkSurfaceCapabilitiesKHR Capabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pPhysicalDevice->VkPhysicalDevice, pResourceHeader->VkSurface, &Capabilities);

		uint32_t AvailableSurfaceFormatsSize = 0;
		VkSurfaceFormatKHR* AvailableSurfaceFormats = NULL;
		vkGetPhysicalDeviceSurfaceFormatsKHR(pPhysicalDevice->VkPhysicalDevice, pResourceHeader->VkSurface, &AvailableSurfaceFormatsSize, NULL);
		if (AvailableSurfaceFormatsSize != 0)
		{
			AvailableSurfaceFormats = (VkSurfaceFormatKHR*)calloc(AvailableSurfaceFormatsSize, sizeof(VkSurfaceFormatKHR));
			vkGetPhysicalDeviceSurfaceFormatsKHR(pPhysicalDevice->VkPhysicalDevice, pResourceHeader->VkSurface, &AvailableSurfaceFormatsSize, AvailableSurfaceFormats);
		}

		uint32_t AvailableSurfacePresentModesSize = 0;
		VkPresentModeKHR* AvailableSurfacePresentModes = NULL;
		vkGetPhysicalDeviceSurfacePresentModesKHR(pPhysicalDevice->VkPhysicalDevice, pResourceHeader->VkSurface, &AvailableSurfacePresentModesSize, NULL);
		if (AvailableSurfacePresentModesSize != 0)
		{
			AvailableSurfacePresentModes = (VkPresentModeKHR*)calloc(AvailableSurfacePresentModesSize, sizeof(VkPresentModeKHR));
			vkGetPhysicalDeviceSurfacePresentModesKHR(pPhysicalDevice->VkPhysicalDevice, pResourceHeader->VkSurface, &AvailableSurfacePresentModesSize, AvailableSurfacePresentModes);
		}


		{//most important
			VkBool32 supported = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(pPhysicalDevice->VkPhysicalDevice, Utils.LogicalDevices[i].GraphicsQueueFamilyIndex, pResourceHeader->VkSurface, &supported);
			if (supported == true)
			{
				CurrentDeviceScore += 10000;
			}
			else
			{
				CurrentDeviceScore = 0;
			}
		}

		for (size_t i1 = 0; i1 < SwapChainFormatAndColourSpacePrioritySize; i1++)
		{
			for (size_t i2 = 0; i2 < AvailableSurfaceFormatsSize; i2++)
			{
				if (SwapChainFormatPriority[i1] == AvailableSurfaceFormats[i2].format && SwapChainColourSpacePriority[i1] == AvailableSurfaceFormats[i2].colorSpace)
				{
					CurrentDeviceScore += 100;
					break;
				}
			}
		}

		for (size_t i1 = 0; i1 < SwapChainPresentModePrioritySize; i1++)
		{
			for (size_t i2 = 0; i2 < AvailableSurfacePresentModesSize; i2++)
			{
				if (SwapChainPresentModePriority[i1] == AvailableSurfacePresentModes[i2])
				{
					CurrentDeviceScore += 100;
					break;
				}
			}
		}


		if (pResourceHeader->TargetFrameBuffersSize > Capabilities.maxImageCount || pResourceHeader->TargetFrameBuffersSize < Capabilities.minImageCount)
		{
			CurrentDeviceScore += 0;
		}
		else
		{
			CurrentDeviceScore += 10;
		}
		if (pResourceHeader->TargetExtentWidth < Capabilities.minImageExtent.width || pResourceHeader->TargetExtentWidth > Capabilities.maxImageExtent.width)
		{
			CurrentDeviceScore += 0;
		}
		else
		{
			CurrentDeviceScore += 10;
		}
		if (pResourceHeader->TargetExtentHeight < Capabilities.minImageExtent.height || pResourceHeader->TargetExtentHeight > Capabilities.maxImageExtent.height)
		{
			CurrentDeviceScore += 0;
		}
		else
		{
			CurrentDeviceScore += 10;
		}

		if (AvailableSurfaceFormats != NULL)
			free(AvailableSurfaceFormats);
		if (AvailableSurfacePresentModes != NULL)
			free(AvailableSurfacePresentModes);

		if (CurrentDeviceScore > DeviceHighScore)
		{
			DeviceHighScore = CurrentDeviceScore;
			DeviceHighScoreIndex = i;
		}
	}


	pResourceHeader->pLogicalDevice = (LogicalDevice*)&Utils.LogicalDevices[DeviceHighScoreIndex];

	VkSurfaceCapabilitiesKHR Capabilities;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(pResourceHeader->pLogicalDevice->pPhysicalDevice->VkPhysicalDevice, pResourceHeader->VkSurface, &Capabilities);

	uint32_t AvailableSurfaceFormatsSize = 0;
	VkSurfaceFormatKHR* AvailableSurfaceFormats = NULL;
	vkGetPhysicalDeviceSurfaceFormatsKHR(pResourceHeader->pLogicalDevice->pPhysicalDevice->VkPhysicalDevice, pResourceHeader->VkSurface, &AvailableSurfaceFormatsSize, NULL);
	AvailableSurfaceFormats = (VkSurfaceFormatKHR*)calloc(AvailableSurfaceFormatsSize, sizeof(VkSurfaceFormatKHR));
	vkGetPhysicalDeviceSurfaceFormatsKHR(pResourceHeader->pLogicalDevice->pPhysicalDevice->VkPhysicalDevice, pResourceHeader->VkSurface, &AvailableSurfaceFormatsSize, AvailableSurfaceFormats);

	uint32_t AvailableSurfacePresentModesSize = 0;
	VkPresentModeKHR* AvailableSurfacePresentModes = NULL;
	vkGetPhysicalDeviceSurfacePresentModesKHR(pResourceHeader->pLogicalDevice->pPhysicalDevice->VkPhysicalDevice, pResourceHeader->VkSurface, &AvailableSurfacePresentModesSize, NULL);
	AvailableSurfacePresentModes = (VkPresentModeKHR*)calloc(AvailableSurfacePresentModesSize, sizeof(VkPresentModeKHR));
	vkGetPhysicalDeviceSurfacePresentModesKHR(pResourceHeader->pLogicalDevice->pPhysicalDevice->VkPhysicalDevice, pResourceHeader->VkSurface, &AvailableSurfacePresentModesSize, AvailableSurfacePresentModes);



	pResourceHeader->CurrentFrameBuffersSize = pResourceHeader->TargetFrameBuffersSize;
	pResourceHeader->CurrentFrameBuffersSize = (pResourceHeader->CurrentFrameBuffersSize > Capabilities.maxImageCount) ? Capabilities.maxImageCount : pResourceHeader->CurrentFrameBuffersSize;		
	pResourceHeader->CurrentFrameBuffersSize = (pResourceHeader->CurrentFrameBuffersSize < Capabilities.minImageCount) ? Capabilities.minImageCount : pResourceHeader->CurrentFrameBuffersSize;
	
	pResourceHeader->CurrentExtentWidth = pResourceHeader->TargetExtentWidth;
	pResourceHeader->CurrentExtentWidth = (pResourceHeader->CurrentExtentWidth > Capabilities.maxImageExtent.width) ? Capabilities.maxImageExtent.width : pResourceHeader->CurrentExtentWidth;	
	pResourceHeader->CurrentExtentWidth = (pResourceHeader->CurrentExtentWidth < Capabilities.minImageExtent.width) ? Capabilities.minImageExtent.width : pResourceHeader->CurrentExtentWidth;
	
	pResourceHeader->CurrentExtentHeight = pResourceHeader->TargetExtentHeight;
	pResourceHeader->CurrentExtentHeight = (pResourceHeader->CurrentExtentHeight > Capabilities.maxImageExtent.height) ? Capabilities.maxImageExtent.height : pResourceHeader->CurrentExtentHeight;
	pResourceHeader->CurrentExtentHeight = (pResourceHeader->CurrentExtentHeight < Capabilities.minImageExtent.height) ? Capabilities.minImageExtent.height : pResourceHeader->CurrentExtentHeight;

	{
		bool found = false;
		for (size_t i1 = 0; i1 < SwapChainFormatAndColourSpacePrioritySize; i1++)
		{
			for (size_t i2 = 0; i2 < AvailableSurfaceFormatsSize; i2++)
			{
				if (SwapChainFormatPriority[i1] == AvailableSurfaceFormats[i2].format && SwapChainColourSpacePriority[i1] == AvailableSurfaceFormats[i2].colorSpace)
				{
					pResourceHeader->CurrentSurfaceFormat = AvailableSurfaceFormats[i2].format;
					pResourceHeader->CurrentSurfaceColourSpace = AvailableSurfaceFormats[i2].colorSpace;
					found = true;
					break;
				}
			}
		}
		if (found == false)
		{
			pResourceHeader->CurrentSurfaceFormat = AvailableSurfaceFormats[0].format;
			pResourceHeader->CurrentSurfaceColourSpace = AvailableSurfaceFormats[0].colorSpace;
		}
	}
	{
		bool found = false;
		for (size_t i1 = 0; i1 < SwapChainPresentModePrioritySize; i1++)
		{
			for (size_t i2 = 0; i2 < AvailableSurfacePresentModesSize; i2++)
			{
				if (SwapChainPresentModePriority[i1] == AvailableSurfacePresentModes[i2])
				{
					pResourceHeader->CurrentSurfacePresentMode = AvailableSurfacePresentModes[i2];
					found = true;
					break;
				}
			}
		}
		if (found == false)
		{
			pResourceHeader->CurrentSurfacePresentMode = AvailableSurfacePresentModes[0];
		}
	}
	free(AvailableSurfaceFormats);
	free(AvailableSurfacePresentModes);





	///////////////////////////////////////////////////////////////////////////////////////////////
	//Renderpass
	///////////////////////////////////////////////////////////////////////////////////////////////
	{
		uint32_t AttachmentDescsSize = 9;
		VkAttachmentDescription AttachmentDescs[9];

		VkAttachmentReference Albedo_Attachment;
		Albedo_Attachment.attachment = 0;
		Albedo_Attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[0].format = DeferredFormats[0]; //needs decent precision
		AttachmentDescs[0].samples = VK_SAMPLE_COUNT_1_BIT;
		AttachmentDescs[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		AttachmentDescs[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		AttachmentDescs[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		AttachmentDescs[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		AttachmentDescs[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		AttachmentDescs[0].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[0].flags = NULL;

		VkAttachmentReference Position_Attachment;
		Position_Attachment.attachment = 1;
		Position_Attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[1].format = DeferredFormats[1];  //needs ALOT of precision
		AttachmentDescs[1].samples = VK_SAMPLE_COUNT_1_BIT;
		AttachmentDescs[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		AttachmentDescs[1].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		AttachmentDescs[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		AttachmentDescs[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		AttachmentDescs[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		AttachmentDescs[1].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[1].flags = NULL;


		VkAttachmentReference Normal_Attachment;
		Normal_Attachment.attachment = 2;
		Normal_Attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[2].format = DeferredFormats[2]; //doesnt need much precision
		AttachmentDescs[2].samples = VK_SAMPLE_COUNT_1_BIT;
		AttachmentDescs[2].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		AttachmentDescs[2].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		AttachmentDescs[2].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		AttachmentDescs[2].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		AttachmentDescs[2].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		AttachmentDescs[2].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[2].flags = NULL;

		VkAttachmentReference PBR_Attachment;
		PBR_Attachment.attachment = 3;
		PBR_Attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[3].format = DeferredFormats[3]; //doesnt need much precision
		AttachmentDescs[3].samples = VK_SAMPLE_COUNT_1_BIT;
		AttachmentDescs[3].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		AttachmentDescs[3].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		AttachmentDescs[3].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		AttachmentDescs[3].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		AttachmentDescs[3].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		AttachmentDescs[3].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[3].flags = NULL;


		VkAttachmentReference Transperancy_Attachment;
		Transperancy_Attachment.attachment = 4;
		Transperancy_Attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[4].format = DeferredFormats[4];
		AttachmentDescs[4].samples = VK_SAMPLE_COUNT_1_BIT;
		AttachmentDescs[4].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		AttachmentDescs[4].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		AttachmentDescs[4].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		AttachmentDescs[4].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		AttachmentDescs[4].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		AttachmentDescs[4].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[4].flags = NULL;

		VkAttachmentReference Revealage_Attachment;
		Revealage_Attachment.attachment = 5;
		Revealage_Attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[5].format = DeferredFormats[5];
		AttachmentDescs[5].samples = VK_SAMPLE_COUNT_1_BIT;
		AttachmentDescs[5].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		AttachmentDescs[5].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		AttachmentDescs[5].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		AttachmentDescs[5].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		AttachmentDescs[5].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		AttachmentDescs[5].finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[5].flags = NULL;


		VkAttachmentReference Depth_Attachment;
		Depth_Attachment.attachment = 6;
		Depth_Attachment.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		AttachmentDescs[6].format = DeferredFormats[6];
		AttachmentDescs[6].samples = VK_SAMPLE_COUNT_1_BIT;
		AttachmentDescs[6].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		AttachmentDescs[6].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		AttachmentDescs[6].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		AttachmentDescs[6].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		AttachmentDescs[6].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		AttachmentDescs[6].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		AttachmentDescs[6].flags = NULL;

		VkAttachmentReference Lighting_Attachment;
		Lighting_Attachment.attachment = 7;
		Lighting_Attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[7].format = pResourceHeader->CurrentSurfaceFormat;
		AttachmentDescs[7].samples = VK_SAMPLE_COUNT_1_BIT;
		AttachmentDescs[7].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		AttachmentDescs[7].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		AttachmentDescs[7].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		AttachmentDescs[7].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		AttachmentDescs[7].initialLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		AttachmentDescs[7].finalLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		AttachmentDescs[7].flags = NULL;

		VkAttachmentReference FinalProduct_Attachment;
		FinalProduct_Attachment.attachment = 8;
		FinalProduct_Attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
		AttachmentDescs[8].format = pResourceHeader->CurrentSurfaceFormat;
		AttachmentDescs[8].samples = VK_SAMPLE_COUNT_1_BIT;
		AttachmentDescs[8].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		AttachmentDescs[8].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		AttachmentDescs[8].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		AttachmentDescs[8].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		AttachmentDescs[8].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		AttachmentDescs[8].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		AttachmentDescs[8].flags = NULL;

		uint32_t SubpassesSize = 3;
		VkSubpassDescription Subpasses[3];
		memset(Subpasses, NULL, sizeof(*Subpasses) * SubpassesSize);

		uint32_t SubpassDependanciesSize = 3;
		VkSubpassDependency SubpassDependancies[3];
		memset(SubpassDependancies, NULL, sizeof(*SubpassDependancies) * SubpassDependanciesSize);

		//opaque subpass

		VkAttachmentReference SubpassGeometryOutputs[4] = { Albedo_Attachment, Position_Attachment, Normal_Attachment, PBR_Attachment };
		Subpasses[0].pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS; //geometry pass
		Subpasses[0].colorAttachmentCount = 4;
		Subpasses[0].pColorAttachments = SubpassGeometryOutputs;
		Subpasses[0].pDepthStencilAttachment = &Depth_Attachment; //&Depth_Attachment
		//dependacy from opaque to transperancy


		SubpassDependancies[0].srcSubpass = 0;
		SubpassDependancies[0].dstSubpass = 1;
		SubpassDependancies[0].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		SubpassDependancies[0].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		SubpassDependancies[0].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		SubpassDependancies[0].dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		SubpassDependancies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;


		//transperancy subpass.

		VkAttachmentReference SubpassTransperancyOutputs[2] = { Transperancy_Attachment, Revealage_Attachment };

		Subpasses[1].pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS; //geometry pass
		Subpasses[1].colorAttachmentCount = 2;
		Subpasses[1].pColorAttachments = SubpassTransperancyOutputs;
		Subpasses[1].pDepthStencilAttachment = &Depth_Attachment;

		//end

		//transperancy and opaque to deferred subpass dependancies

		SubpassDependancies[1].srcSubpass = 0;
		SubpassDependancies[1].dstSubpass = 2;
		SubpassDependancies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		SubpassDependancies[1].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		SubpassDependancies[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		SubpassDependancies[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		SubpassDependancies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

		SubpassDependancies[2].srcSubpass = 1;
		SubpassDependancies[2].dstSubpass = 2;
		SubpassDependancies[2].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		SubpassDependancies[2].dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		SubpassDependancies[2].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
		SubpassDependancies[2].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		SubpassDependancies[2].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

		//deferred subpass

		VkAttachmentReference SubpassLightingOutputs[2] = { FinalProduct_Attachment, Lighting_Attachment };
		VkAttachmentReference SubpassLightingInputs[7];

		SubpassLightingInputs[0].attachment = 0;
		SubpassLightingInputs[0].layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		SubpassLightingInputs[1].attachment = 1;
		SubpassLightingInputs[1].layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		SubpassLightingInputs[2].attachment = 2;
		SubpassLightingInputs[2].layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		SubpassLightingInputs[3].attachment = 3;
		SubpassLightingInputs[3].layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		SubpassLightingInputs[4].attachment = 4;
		SubpassLightingInputs[4].layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		SubpassLightingInputs[5].attachment = 5;
		SubpassLightingInputs[5].layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

		SubpassLightingInputs[6].attachment = 6;
		SubpassLightingInputs[6].layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;


		Subpasses[2].pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS; //lighting pass
		Subpasses[2].inputAttachmentCount = 7;
		Subpasses[2].pInputAttachments = SubpassLightingInputs;
		Subpasses[2].colorAttachmentCount = 2;
		Subpasses[2].pColorAttachments = SubpassLightingOutputs;


		VkRenderPassCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		Info.attachmentCount = AttachmentDescsSize;
		Info.pAttachments = AttachmentDescs;
		Info.subpassCount = SubpassesSize;
		Info.pSubpasses = Subpasses;

		Info.dependencyCount = SubpassDependanciesSize;
		Info.pDependencies = SubpassDependancies;

		if ((res = vkCreateRenderPass(pResourceHeader->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkRenderPassDeferred)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_GraphicsWindowHeader()", "vkCreateRenderPass Failed, VkResult == ", res);
			return;
		}

	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//SwapChain
	///////////////////////////////////////////////////////////////////////////////////////////////

	if (ReCreate_SwapChain(pResourceHeader, true) != Success)
	{
		//Engine_Ref_FunctionError("ReCreate_GraphicsWindow()", "ReCreate_SwapChain Failed. VkResult == ", res);
		return;
	}


	///////////////////////////////////////////////////////////////////////////////////////////////
	//Descriptor Layouts
	///////////////////////////////////////////////////////////////////////////////////////////////

	{//bindings input attachments
		VkDescriptorSetLayoutBinding BindingsAttachments[DeferredImageCount];
		for (size_t i = 0; i < DeferredImageCount; i++)
		{
			BindingsAttachments[i].binding = i;
			BindingsAttachments[i].descriptorCount = 1;
			BindingsAttachments[i].descriptorType = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
			BindingsAttachments[i].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
			BindingsAttachments[i].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)DeferredImageCount;
		Info.pBindings = BindingsAttachments;
		Info.pNext = NULL;
		Info.flags = NULL;
		if ((res = vkCreateDescriptorSetLayout(pResourceHeader->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorSetLayoutInputAttachment)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("Create_LogicalDevice()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return (TEXRESULT)(Failure);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//PipelineLayouts
	///////////////////////////////////////////////////////////////////////////////////////////////

	{//layout deferred

		VkDescriptorSetLayout layouts[1] = { pResourceHeader->VkDescriptorSetLayoutInputAttachment };
		uint32_t layoutsSize = 1;

		VkPushConstantRange push_constant;
		push_constant.offset = 0;
		push_constant.size = pResourceHeader->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		push_constant.stageFlags = VK_SHADER_STAGE_ALL;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pushConstantRangeCount = 1;
		Info.pPushConstantRanges = &push_constant;
		Info.pNext = NULL;
		Info.flags = NULL;
		if ((res = vkCreatePipelineLayout(pResourceHeader->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkPipelineLayoutDeferred)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("Create_LogicalDevice()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return (TEXRESULT)(Failure);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Descriptor Pool
	///////////////////////////////////////////////////////////////////////////////////////////////

	{
		pResourceHeader->VkDescriptorSetsInputAttachment = (VkDescriptorSet*)calloc(pResourceHeader->CurrentFrameBuffersSize, sizeof(VkDescriptorSet));
		{
			uint32_t PoolSizesSize = 1;
			VkDescriptorPoolSize PoolSizes[1];

			PoolSizes[0].descriptorCount = DeferredImageCount * pResourceHeader->CurrentFrameBuffersSize;
			PoolSizes[0].type = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;

			VkDescriptorPoolCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			Info.maxSets = 1 * pResourceHeader->CurrentFrameBuffersSize;
			Info.poolSizeCount = PoolSizesSize;
			Info.pPoolSizes = PoolSizes;
			Info.flags = 0;

			if ((res = vkCreateDescriptorPool(pResourceHeader->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorPoolDeferred)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_GraphicsWindowHeader()", "vkCreateDescriptorPool, VkResult == ", res);
				return;
			}
		}
		for (size_t i = 0; i < pResourceHeader->CurrentFrameBuffersSize; i++)
		{
			uint32_t layoutsSize = 1;
			VkDescriptorSetLayout layouts[1] = {pResourceHeader->VkDescriptorSetLayoutInputAttachment };
			VkDescriptorSet sets[1];

			VkDescriptorSetAllocateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			Info.descriptorPool = pResourceHeader->VkDescriptorPoolDeferred;
			Info.descriptorSetCount = layoutsSize;
			Info.pSetLayouts = layouts;
			Info.pNext = NULL;
			if ((res = vkAllocateDescriptorSets(pResourceHeader->pLogicalDevice->VkLogicalDevice, &Info, sets)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_GraphicsWindowHeader()", "vkAllocateDescriptorSets, VkResult == ", res);
				return;
			}
			pResourceHeader->VkDescriptorSetsInputAttachment[i] = sets[0];
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Pipeline
	///////////////////////////////////////////////////////////////////////////////////////////////
	{
		const SPIRV Vertex[] = VertexShaderDeferred();
		const SPIRV Fragment[] = FragmentShaderDeferred();

		CompileVkShaderModule(pResourceHeader->pLogicalDevice, pResourceHeader->VkShaderVertexDeferred, Vertex, VertexShaderDeferredSize, "ReCreate_GraphicsWindowHeader()");
		CompileVkShaderModule(pResourceHeader->pLogicalDevice, pResourceHeader->VkShaderFragmentDeferred, Fragment, FragmentShaderDeferredSize, "ReCreate_GraphicsWindowHeader()");

		uint32_t ShaderStagesCount = 2;
		VkPipelineShaderStageCreateInfo ShaderStages[2];
		memset(&ShaderStages, NULL, sizeof(*ShaderStages) * ShaderStagesCount);

		ShaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		ShaderStages[0].module = pResourceHeader->VkShaderVertexDeferred;
		ShaderStages[0].pName = "main";

		ShaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		ShaderStages[1].module = pResourceHeader->VkShaderFragmentDeferred;
		ShaderStages[1].pName = "main";



		VkPipelineColorBlendAttachmentState ColourBlendAttachment;
		memset(&ColourBlendAttachment, NULL, sizeof(ColourBlendAttachment));
		ColourBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		ColourBlendAttachment.blendEnable = VK_FALSE;


		VkPipelineColorBlendAttachmentState attachments[2] = { ColourBlendAttachment, ColourBlendAttachment};


		VkPipelineColorBlendStateCreateInfo ColourBlendingDeffered;
		memset(&ColourBlendingDeffered, NULL, sizeof(ColourBlendingDeffered));
		ColourBlendingDeffered.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		ColourBlendingDeffered.logicOpEnable = VK_FALSE;
		ColourBlendingDeffered.logicOp = VK_LOGIC_OP_COPY; // Optional
		ColourBlendingDeffered.attachmentCount = 2;
		ColourBlendingDeffered.pAttachments = attachments;
		ColourBlendingDeffered.blendConstants[0] = 0.0f; // Optional
		ColourBlendingDeffered.blendConstants[1] = 0.0f; // Optional
		ColourBlendingDeffered.blendConstants[2] = 0.0f; // Optional
		ColourBlendingDeffered.blendConstants[3] = 0.0f; // Optional
		ColourBlendingDeffered.flags = NULL;
		ColourBlendingDeffered.pNext = NULL;

		uint32_t statesSize = 2;
		VkDynamicState states[2] = { VK_DYNAMIC_STATE_VIEWPORT , VK_DYNAMIC_STATE_SCISSOR };
		VkPipelineDynamicStateCreateInfo DynamicStates;
		memset(&DynamicStates, NULL, sizeof(DynamicStates));
		DynamicStates.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		DynamicStates.dynamicStateCount = statesSize;
		DynamicStates.pDynamicStates = states;

		VkPipelineVertexInputStateCreateInfo VertexInputState;
		memset(&VertexInputState, NULL, sizeof(VertexInputState));
		VertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		VkPipelineInputAssemblyStateCreateInfo InputAssemblyState;
		memset(&InputAssemblyState, NULL, sizeof(InputAssemblyState));
		InputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		InputAssemblyState.primitiveRestartEnable = VK_FALSE;


		VkViewport Viewport;
		memset(&Viewport, NULL, sizeof(Viewport));
		Viewport.x = 0.0f;
		Viewport.y = 0.0f;
		Viewport.width = (float)pResourceHeader->CurrentExtentWidth;
		Viewport.height = (float)pResourceHeader->CurrentExtentHeight;
		Viewport.minDepth = 0.0f;
		Viewport.maxDepth = 1.0f;

		VkRect2D Scissor;
		memset(&Scissor, NULL, sizeof(Scissor));
		Scissor.offset.x = 0;
		Scissor.offset.y = 0;
		Scissor.extent.width = pResourceHeader->CurrentExtentWidth;
		Scissor.extent.height = pResourceHeader->CurrentExtentHeight;

		VkPipelineViewportStateCreateInfo ViewportState;
		memset(&ViewportState, NULL, sizeof(ViewportState));
		ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		ViewportState.viewportCount = 1; //multi screeen~?!?!??!!?
		ViewportState.pViewports = &Viewport;
		ViewportState.scissorCount = 1;
		ViewportState.pScissors = &Scissor;

		VkPipelineRasterizationStateCreateInfo RasterizationState;
		memset(&RasterizationState, NULL, sizeof(RasterizationState));
		RasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		RasterizationState.depthClampEnable = VK_FALSE;
		RasterizationState.rasterizerDiscardEnable = VK_FALSE;
		RasterizationState.polygonMode = VK_POLYGON_MODE_FILL;
		RasterizationState.lineWidth = 1.0f;
		RasterizationState.cullMode = VK_CULL_MODE_NONE; //CULL MODE
		RasterizationState.frontFace = VK_FRONT_FACE_CLOCKWISE;
		RasterizationState.depthBiasEnable = VK_FALSE;
		RasterizationState.depthBiasConstantFactor = 0.0f; // Optional
		RasterizationState.depthBiasClamp = 0.0f; // Optional
		RasterizationState.depthBiasSlopeFactor = 0.0f; // Optional

		VkPipelineMultisampleStateCreateInfo MultisampleState;
		memset(&MultisampleState, NULL, sizeof(MultisampleState));
		MultisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		MultisampleState.sampleShadingEnable = VK_FALSE;
		MultisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		MultisampleState.minSampleShading = 1.0f; // Optional
		MultisampleState.pSampleMask = NULL; // Optional
		MultisampleState.alphaToCoverageEnable = VK_FALSE; // Optional
		MultisampleState.alphaToOneEnable = VK_FALSE; // Optional

		{
			VkGraphicsPipelineCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
			Info.stageCount = ShaderStagesCount;
			Info.pStages = ShaderStages;
			Info.pVertexInputState = &VertexInputState;
			Info.pInputAssemblyState = &InputAssemblyState;
			Info.pViewportState = &ViewportState;
			Info.pRasterizationState = &RasterizationState;
			Info.pMultisampleState = &MultisampleState;
			Info.pDepthStencilState = NULL; // Optional
			Info.pColorBlendState = &ColourBlendingDeffered;
			Info.pDynamicState = &DynamicStates; // Optional
			Info.layout = pResourceHeader->VkPipelineLayoutDeferred;
			Info.renderPass = pResourceHeader->VkRenderPassDeferred;
			Info.subpass = 2;
			Info.basePipelineHandle = VK_NULL_HANDLE; // Optional
			Info.basePipelineIndex = -1; // Optional

			if ((res = vkCreateGraphicsPipelines(pResourceHeader->pLogicalDevice->VkLogicalDevice, NULL, 1, &Info, NULL, &pResourceHeader->VkPipelineDeferred)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_GraphicsWindowHeader()", "vkCreateGraphicsPipelines Failed, VkResult == ", res);
				return;
			}
		}
	}

	for (size_t i = 0; i < pResourceHeader->CurrentFrameBuffersSize; i++)
	{
		for (size_t i1 = 0; i1 < DeferredImageCount; i1++)
		{
			VkDescriptorImageInfo ImageInfo;
			ImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			ImageInfo.imageView = pResourceHeader->SwapChain.FrameBuffers[i].DeferredImages[i1].ImageView;
			ImageInfo.sampler = NULL;
			Update_Descriptor(pResourceHeader->pLogicalDevice, pResourceHeader->VkDescriptorSetsInputAttachment[i], i1, 0, VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, NULL, &ImageInfo);
		}
	}
}

void ReCreate_MaterialHeader(RHeaderMaterial* pResourceHeader, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iGraphicsWindow) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_MaterialHeader()", "pResourceHeader->iGraphicsWindow Invalid");
		return;
	}
#endif

	VkResult res = VK_SUCCESS;
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
	{
		uint32_t PoolSizesSize = 2;
		VkDescriptorPoolSize PoolSizes[2];

		PoolSizes[0].descriptorCount = 1;
		PoolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;

		PoolSizes[1].descriptorCount = MaterialTextureBindings;
		PoolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

		VkDescriptorPoolCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		Info.maxSets = 1 * pGraphicsWindow->CurrentFrameBuffersSize;
		Info.poolSizeCount = PoolSizesSize;
		Info.pPoolSizes = PoolSizes;
		Info.flags = 0;
		if ((res = vkCreateDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkMaterialDescriptorPool)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_MaterialHeader()", "vkCreateDescriptorPool Failed, VkResult == ", res);
			return;
		}
	}

	pResourceHeader->VkMaterialDescriptorSets = (VkDescriptorSet*)calloc(pGraphicsWindow->CurrentFrameBuffersSize, sizeof(VkDescriptorSet));
	for (size_t i1 = 0; i1 < pGraphicsWindow->CurrentFrameBuffersSize; i1++)
	{
		uint32_t layoutsSize = 1;
		VkDescriptorSetLayout layouts[1] = { Utils.GenericResources[Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].VkDescriptorSetLayoutMaterial };
		VkDescriptorSet sets[1];

		VkDescriptorSetAllocateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		Info.descriptorPool = pResourceHeader->VkMaterialDescriptorPool;
		Info.descriptorSetCount = layoutsSize;
		Info.pSetLayouts = layouts;
		if ((res = vkAllocateDescriptorSets(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, sets)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_MaterialHeader()", "vkAllocateDescriptorSets Failed, VkResult == ", res);
			return;
		}
		pResourceHeader->VkMaterialDescriptorSets[i1] = sets[0];
	}
}

void ReCreate_TextureHeader(RHeaderTexture* pResourceHeader, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iImageSource) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_TextureHeader()", "pResourceHeader->iImageSource Invalid");
		return;
	}
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iGraphicsWindow) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_TextureHeader()", "pResourceHeader->iGraphicsWindow Invalid");
		return;
	}
#endif
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
	RHeaderImageSource* pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iImageSource);
//#ifndef NDEBUG
	if (pImageSource->ImageData->Width == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_TextureHeader()", "pImageSource->ImageData->Width == NULL, Width Must Be > 0.");
		return;
	}
	
	if (pImageSource->ImageData->Height == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_TextureHeader()", "pImageSource->ImageData->Height == NULL, Height Must Be > 0.");
		return;
	}
	if (pImageSource->ImageData->Depth == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_TextureHeader()", "pImageSource->ImageData->Depth == NULL, Depth Must Be > 0.");
		return;
	}
	/*
	if (pImageSource->ImageData->LinearSize == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_TextureHeader()", "pImageSource->ImageData->LinearSize == NULL, LinearSize Must Be > 0.");
		return;
	}
	if (pImageSource->ImageData->ImageSize == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_TextureHeader()", "pImageSource->ImageData->ImageSize == NULL, ImageSize Must Be > 0.");
		return;
	}*/
	
	if (pImageSource->ImageData->MipmapCount == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_TextureHeader()", "pImageSource->ImageData->MipmapCount == NULL, MipmapCount Must Be > 0.");
		return;
	}
	if (pImageSource->ImageData->Format == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_TextureHeader()", "Format == NULL, Format Must Not Be Undefined.");
		return;
	}
	if (pGraphicsWindow->pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_TextureHeader()", "pGraphicsWindow->pLogicalDevice == NULLPTR, Unitialized GraphicsWindow.");
		return;
	}
//#endif
	VkImageType ImageType = VK_IMAGE_TYPE_1D;
	if (pImageSource->ImageData->Height > 1)
		ImageType = VK_IMAGE_TYPE_2D;
	if (pImageSource->ImageData->Depth > 1)
		ImageType = VK_IMAGE_TYPE_3D;

	uint32_t MipLevels = pImageSource->ImageData->MipmapCount;
	bool GenerateMipmaps = false;
	bool SuitableFormatFound = false;
	uint32_t i = 0;
	GraphicsFormat NewFormat = pImageSource->ImageData->Format;
	VkSampleCountFlagBits SampleCount = VK_SAMPLE_COUNT_1_BIT;
	while (SuitableFormatFound == false){
		SuitableFormatFound = true;

		VkFormatProperties FormatProperties;
		vkGetPhysicalDeviceFormatProperties(pGraphicsWindow->pLogicalDevice->pPhysicalDevice->VkPhysicalDevice, (VkFormat)NewFormat, &FormatProperties);

		if ((FormatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)){
			//mipmaps are not supported to be generated.
			MipLevels = pImageSource->ImageData->MipmapCount;
			GenerateMipmaps = false;
		}
		else{
			//mipmaps are supported to be generated.
			if (MipLevels == 1) {
				//generate mipmaps to fill in gaps.
				MipLevels = (floor(log2(max(pImageSource->ImageData->Width, pImageSource->ImageData->Height))) + 1);
				GenerateMipmaps = true;
			}
			else{
				//dont generate mipmaps since already present and adequate. 
				MipLevels = pImageSource->ImageData->MipmapCount;
				GenerateMipmaps = false;
			}
		}

		VkImageFormatProperties ImageFormatProperties;
		vkGetPhysicalDeviceImageFormatProperties(pGraphicsWindow->pLogicalDevice->pPhysicalDevice->VkPhysicalDevice,
			(VkFormat)NewFormat, ImageType, VK_IMAGE_TILING_OPTIMAL, pResourceHeader->TextureUsage, NULL, &ImageFormatProperties);

		if (pImageSource->ImageData->Width > ImageFormatProperties.maxExtent.width)
			SuitableFormatFound = false;
		if (pImageSource->ImageData->Height > ImageFormatProperties.maxExtent.height)
			SuitableFormatFound = false;
		if (pImageSource->ImageData->Depth > ImageFormatProperties.maxExtent.depth)
			SuitableFormatFound = false;
		if (pImageSource->ImageData->MipmapCount > ImageFormatProperties.maxMipLevels)
			SuitableFormatFound = false;
		if (pImageSource->ImageData->LinearSize > ImageFormatProperties.maxResourceSize)
			SuitableFormatFound = false;
		if (1 > ImageFormatProperties.maxArrayLayers)
			SuitableFormatFound = false;
		if (!(Config.Samples & ImageFormatProperties.sampleCounts))
			SuitableFormatFound = false;
		if (!(FormatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT))
			SuitableFormatFound = false;

		NewFormat = TextureBackupFormatPriority[i];
		if ((i > TextureBackupFormatPrioritySize))
		{
			Engine_Ref_ArgsError("ReCreate_TextureHeader()", "No Compatible Formats Found.");
			return;
		}
		i++;
	}
	if (i > 1)
	{
		Engine_Ref_FunctionError("converting", "convert", NewFormat);
		//if (Convert_ImageData(&pImageSource->ImageData, NewFormat) != Success)
		//	return;
		//pImageSource->ImageData->Format = NewFormat;
	}


	VkResult res = VK_SUCCESS;
	{
		VkImageCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		Info.pNext = NULL;
		Info.flags = NULL;
		Info.imageType = ImageType;
		Info.format = (VkFormat)pImageSource->ImageData->Format;
		Info.extent.width = pImageSource->ImageData->Width;
		Info.extent.height = pImageSource->ImageData->Height;
		Info.extent.depth = pImageSource->ImageData->Depth;
		Info.mipLevels = pImageSource->ImageData->MipmapCount;
		Info.arrayLayers = 1;
		Info.samples = Config.Samples;
		Info.tiling = VK_IMAGE_TILING_OPTIMAL;
		Info.usage = pResourceHeader->TextureUsage;
		Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		Info.queueFamilyIndexCount = NULL;
		Info.pQueueFamilyIndices = NULL;
		Info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		if ((res = vkCreateImage(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->GPU_Texture.VkImage)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_TextureHeader()", "vkCreateImage Failed, VkResult == ", res);
			return;
		}
	}

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pResourceHeader->GPU_Texture.VkImage, &memRequirements);
	pResourceHeader->GPU_Texture.Allocation = GPUmalloc(pGraphicsWindow->pLogicalDevice, memRequirements, TargetMemory_Dst, pResourceHeader->AllocationType, ThreadIndex);
	if (pResourceHeader->GPU_Texture.Allocation.SizeBytes == NULL)
	{
		Engine_Ref_FunctionError("ReCreate_TextureHeader()", "Not Enough Space In GPU Memory!", NULL);
		return;
	}

	if ((res = vkBindImageMemory(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pResourceHeader->GPU_Texture.VkImage, pResourceHeader->GPU_Texture.Allocation.Allocater.VkMemory, pResourceHeader->GPU_Texture.Allocation.Pointer)) != VK_SUCCESS)
	{
		Engine_Ref_FunctionError("ReCreate_TextureHeader()", "vkBindImageMemory Failed, VkResult == ", res);
		return;
	}
	{
		VkImageViewCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		Info.image = pResourceHeader->GPU_Texture.VkImage;
		Info.viewType = (VkImageViewType)ImageType; //only supports 1d, 2d, 3d.
		Info.format = (VkFormat)pImageSource->ImageData->Format;

		Info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		Info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		Info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		Info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		Info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT; //parameter?
		Info.subresourceRange.baseMipLevel = 0;
		Info.subresourceRange.levelCount = pImageSource->ImageData->MipmapCount;
		Info.subresourceRange.baseArrayLayer = 0;
		Info.subresourceRange.layerCount = 1;

		if ((res = vkCreateImageView(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->GPU_Texture.VkImageView)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_TextureHeader()", "vkCreateImageView Failed, VkResult == ", res);
			return;
		}
	}
	{
		VkSamplerCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		switch (pResourceHeader->MagFilter)
		{
		case TextureFilterMode_Nearest:
			Info.magFilter = VK_FILTER_NEAREST;
			break;
		case TextureFilterMode_Linear:
			Info.magFilter = VK_FILTER_LINEAR;
			break;
		}
		switch (pResourceHeader->MinFilter)
		{
		case TextureFilterMode_Nearest:
			Info.minFilter = VK_FILTER_NEAREST;
			break;
		case TextureFilterMode_Linear:
			Info.minFilter = VK_FILTER_LINEAR;
			break;
		}
		switch (pResourceHeader->AddressModeU)
		{
		case TextureAddressMode_Repeat:
			Info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			break;
		case TextureAddressMode_MirroredRepeat:
			Info.addressModeU = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
			break;
		case TextureAddressMode_ClampToEdge:
			Info.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			break;
		case TextureAddressMode_ClampToBorder:
			Info.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
			break;
		case TextureAddressMode_MirrorClampToEdge:
			Info.addressModeU = VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
			break;
		}
		switch (pResourceHeader->AddressModeV)
		{
		case TextureAddressMode_Repeat:
			Info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			break;
		case TextureAddressMode_MirroredRepeat:
			Info.addressModeV = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
			break;
		case TextureAddressMode_ClampToEdge:
			Info.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			break;
		case TextureAddressMode_ClampToBorder:
			Info.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
			break;
		case TextureAddressMode_MirrorClampToEdge:
			Info.addressModeV = VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
			break;
		}
		switch (pResourceHeader->AddressModeW)
		{
		case TextureAddressMode_Repeat:
			Info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			break;
		case TextureAddressMode_MirroredRepeat:
			Info.addressModeW = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
			break;
		case TextureAddressMode_ClampToEdge:
			Info.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
			break;
		case TextureAddressMode_ClampToBorder:
			Info.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
			break;
		case TextureAddressMode_MirrorClampToEdge:
			Info.addressModeW = VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
			break;
		}

		Info.anisotropyEnable = Config.AnisotropicFiltering;
		Info.maxAnisotropy = Config.MaxAnisotropy;
		Info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		Info.unnormalizedCoordinates = VK_FALSE;
		Info.compareEnable = VK_FALSE;
		Info.compareOp = VK_COMPARE_OP_ALWAYS;
		Info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
		Info.mipLodBias = 0.0f; //mipmap
		Info.minLod = 0.0f;
		Info.maxLod = (float)MipLevels - 1.0f;

		if (vkCreateSampler(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->GPU_Texture.VkSampler) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_TextureHeader()", "vkCreateSampler Failed, VkResult == ", res);
			return;
		}
	}

	VkCommandPool VkCmdPool = NULL;
	VkCommandBuffer VkCmdBuffer = NULL;

	{
		VkCommandPoolCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		Info.queueFamilyIndex = pGraphicsWindow->pLogicalDevice->GraphicsQueueFamilyIndex;
		Info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
		if ((res = vkCreateCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &VkCmdPool)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_TextureHeader()", "vkCreateCommandPool Failed, VkResult == ", res);
			return;
		}
	}
	{
		VkCommandBufferAllocateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		Info.commandPool = VkCmdPool;
		Info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		Info.commandBufferCount = 1;
		Info.pNext = NULL;
		if ((res = vkAllocateCommandBuffers(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, &VkCmdBuffer)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_TextureHeader()", "vkAllocateCommandBuffers Failed, VkResult == ", res);
			return;
		}
	}
	{
		VkCommandBufferBeginInfo BeginInfo;
		memset(&BeginInfo, NULL, sizeof(BeginInfo));
		BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		BeginInfo.pInheritanceInfo = NULL;
		BeginInfo.pNext = NULL;
		if ((res = vkBeginCommandBuffer(VkCmdBuffer, &BeginInfo)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_TextureHeader()", "vkBeginCommandBuffer Failed, VkResult == ", res);
			return;
		}
	}

	GPU_Allocation SrcAllocation;
	memset(&SrcAllocation, 0, sizeof(SrcAllocation));
	if (pImageSource->ImageData->LinearSize == NULL && pImageSource->ImageData->ImageSize == NULL)
	{
		VkImageMemoryBarrier Barrier;
		Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		Barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		Barrier.image = pResourceHeader->GPU_Texture.VkImage;
		Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		Barrier.subresourceRange.baseMipLevel = 0;
		Barrier.subresourceRange.levelCount = MipLevels;
		Barrier.subresourceRange.baseArrayLayer = 0;
		Barrier.subresourceRange.layerCount = 1;
		Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		Barrier.srcAccessMask = 0;
		Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		Barrier.pNext = NULL;

		vkCmdPipelineBarrier(
			VkCmdBuffer,
			VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
			0,
			0, NULL,
			0, NULL,
			1, &Barrier
		);
	}
	else
	{
		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pResourceHeader->GPU_Texture.VkImage, &memRequirements);

		SrcAllocation = GPUmalloc(pGraphicsWindow->pLogicalDevice, memRequirements, TargetMemory_Src, AllocationType_Linear, ThreadIndex);
		if (SrcAllocation.SizeBytes == NULL)
		{
			Engine_Ref_FunctionError("ReCreate_TextureHeader()", "Not Enough Space In GPU Memory!", NULL);
			return;
		}

		VkImageMemoryBarrier Barrier0;
		Barrier0.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		Barrier0.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		Barrier0.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		Barrier0.image = pResourceHeader->GPU_Texture.VkImage;
		Barrier0.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		Barrier0.subresourceRange.baseMipLevel = 0;
		Barrier0.subresourceRange.levelCount = MipLevels;
		Barrier0.subresourceRange.baseArrayLayer = 0;
		Barrier0.subresourceRange.layerCount = 1;
		Barrier0.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		Barrier0.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		Barrier0.srcAccessMask = 0;
		Barrier0.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		Barrier0.pNext = NULL;

		vkCmdPipelineBarrier(
			VkCmdBuffer,
			VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
			0,
			0, NULL,
			0, NULL,
			1, &Barrier0
		);

		uint32_t regioncount = pImageSource->ImageData->MipmapCount;
		VkBufferImageCopy* regions = (VkBufferImageCopy*)calloc(regioncount, sizeof(VkBufferImageCopy));
		{
			uint64_t totalpointer = 0;

			int32_t mipWidth = pImageSource->ImageData->Width;
			int32_t mipHeight = pImageSource->ImageData->Height;
			int32_t mipDepth = pImageSource->ImageData->Depth;

			uint32_t size = pImageSource->ImageData->ImageSize;

			for (size_t i = 0; i < regioncount; i++)
			{
				memcpy((void*)((uint64_t)SrcAllocation.Allocater.pArenaAllocater->MappedMemory + SrcAllocation.Pointer + totalpointer), (void*)((uint64_t)pImageSource->ImageData->Data + (uint64_t)totalpointer), size);

				regions[i].bufferOffset = totalpointer + SrcAllocation.Pointer;
				regions[i].bufferRowLength = 0;
				regions[i].bufferImageHeight = 0;

				regions[i].imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				regions[i].imageSubresource.mipLevel = i; //mipmap
				regions[i].imageSubresource.baseArrayLayer = 0;
				regions[i].imageSubresource.layerCount = 1;

				regions[i].imageOffset.x = 0;
				regions[i].imageOffset.y = 0;
				regions[i].imageOffset.z = 0;
				regions[i].imageExtent.width = (uint32_t)mipWidth;
				regions[i].imageExtent.height = (uint32_t)mipHeight;
				regions[i].imageExtent.depth = (uint32_t)mipDepth;

				totalpointer += size;
				if ((mipWidth > 1))
					mipWidth /= 2;
				if ((mipHeight > 1) && (ImageType == VK_IMAGE_TYPE_2D || ImageType == VK_IMAGE_TYPE_3D))
					mipHeight /= 2;
				if ((mipDepth > 1) && (ImageType == VK_IMAGE_TYPE_3D))
					mipDepth /= 2;
				
				if (size > 8)
					size /= 4;
			}
		}

		vkCmdCopyBufferToImage(
			VkCmdBuffer,
			SrcAllocation.Allocater.pArenaAllocater->VkBuffer,
			pResourceHeader->GPU_Texture.VkImage,
			VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			regioncount,
			regions
		);
		free(regions);

		uint32_t mipmapc = MipLevels;
		if (GenerateMipmaps == true)
		{
			//generate mipmaps
			int32_t mipWidth = pImageSource->ImageData->Width;
			int32_t mipHeight = pImageSource->ImageData->Height;
			int32_t mipDepth = pImageSource->ImageData->Depth;

			for (size_t i = 1; i < mipmapc; i++)
			{
				VkImageMemoryBarrier Barrier1;
				Barrier1.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
				Barrier1.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
				Barrier1.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
				Barrier1.image = pResourceHeader->GPU_Texture.VkImage;
				Barrier1.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				Barrier1.subresourceRange.baseMipLevel = i - 1;
				Barrier1.subresourceRange.levelCount = 1;
				Barrier1.subresourceRange.baseArrayLayer = 0;
				Barrier1.subresourceRange.layerCount = 1;
				Barrier1.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				Barrier1.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				Barrier1.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
				Barrier1.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				Barrier1.pNext = NULL;
				vkCmdPipelineBarrier(
					VkCmdBuffer,
					VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
					0,
					0, NULL,
					0, NULL,
					1, &Barrier1
				);

				VkImageBlit blit;
				blit.srcOffsets[0].x = 0;
				blit.srcOffsets[0].y = 0;
				blit.srcOffsets[0].z = 0;
				blit.srcOffsets[1].x = mipWidth;
				blit.srcOffsets[1].y = mipHeight;
				blit.srcOffsets[1].z = mipDepth;

				blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				blit.srcSubresource.mipLevel = i - 1;
				blit.srcSubresource.baseArrayLayer = 0;
				blit.srcSubresource.layerCount = 1;

				blit.dstOffsets[0].x = 0;
				blit.dstOffsets[0].y = 0;
				blit.dstOffsets[0].z = 0;
				blit.dstOffsets[1].x = mipWidth > 1 ? mipWidth / 2 : 1;
				blit.dstOffsets[1].y = mipHeight > 1 ? mipHeight / 2 : 1;
				blit.dstOffsets[1].z = mipDepth > 1 ? mipDepth / 2 : 1;

				blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				blit.dstSubresource.mipLevel = i;
				blit.dstSubresource.baseArrayLayer = 0;
				blit.dstSubresource.layerCount = 1;

				vkCmdBlitImage(
					VkCmdBuffer,
					pResourceHeader->GPU_Texture.VkImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
					pResourceHeader->GPU_Texture.VkImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					1, &blit,
					VK_FILTER_LINEAR
				);


				VkImageMemoryBarrier Barrier2;
				Barrier2.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
				Barrier2.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
				Barrier2.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
				Barrier2.image = pResourceHeader->GPU_Texture.VkImage;
				Barrier2.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				Barrier2.subresourceRange.baseMipLevel = i - 1;
				Barrier2.subresourceRange.levelCount = 1;
				Barrier2.subresourceRange.baseArrayLayer = 0;
				Barrier2.subresourceRange.layerCount = 1;
				Barrier2.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				Barrier2.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
				Barrier2.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
				Barrier2.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
				Barrier2.pNext = NULL;

				vkCmdPipelineBarrier(
					VkCmdBuffer,
					VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
					0,
					0, NULL,
					0, NULL,
					1, &Barrier2
				);

				if ((mipWidth > 1))
					mipWidth /= 2;
				if ((mipHeight > 1) && (ImageType == VK_IMAGE_TYPE_2D || ImageType == VK_IMAGE_TYPE_3D))
					mipHeight /= 2;
				if ((mipDepth > 1) && (ImageType == VK_IMAGE_TYPE_3D))
					mipDepth /= 2;
			}
		}

		VkImageMemoryBarrier Barrier3;
		Barrier3.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		Barrier3.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		Barrier3.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		Barrier3.image = pResourceHeader->GPU_Texture.VkImage;
		Barrier3.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		Barrier3.subresourceRange.baseMipLevel = 0;
		Barrier3.subresourceRange.levelCount = regioncount;
		Barrier3.subresourceRange.baseArrayLayer = 0;
		Barrier3.subresourceRange.layerCount = 1;
		Barrier3.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		Barrier3.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		Barrier3.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		Barrier3.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		Barrier3.pNext = NULL;

		vkCmdPipelineBarrier(
			VkCmdBuffer,
			VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
			0,
			0, NULL,
			0, NULL,
			1, &Barrier3
		);
	}
	vkEndCommandBuffer(VkCmdBuffer);

	uint32_t QueueIndex = 0;
	{
		bool found = false;
		while (found == false)
		{
			for (size_t i = 0; i < pGraphicsWindow->pLogicalDevice->GraphicsQueueFamilySize; i++)
			{
				if (Engine_Ref_TryLock_Mutex(pGraphicsWindow->pLogicalDevice->GraphicsQueueMutexes[i]) == Success)
				{
					QueueIndex = i;
					found = true;
					break;
				}
			}
		}
	}
	VkQueue Queue = NULL;
	vkGetDeviceQueue(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->pLogicalDevice->GraphicsQueueFamilyIndex, QueueIndex, &Queue);

	VkSubmitInfo SubmitInfo;
	memset(&SubmitInfo, NULL, sizeof(SubmitInfo));
	SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.commandBufferCount = (uint32_t)1;
	SubmitInfo.pCommandBuffers = &VkCmdBuffer;

	if ((res = vkQueueSubmit(Queue, 1, &SubmitInfo, VK_NULL_HANDLE)) != VK_SUCCESS)
	{
		Engine_Ref_FunctionError("ReCreate_TextureHeader()", "vkQueueSubmit Failed, VkResult == ", res);
		return;
	}

	vkQueueWaitIdle(Queue);
	Engine_Ref_Unlock_Mutex(pGraphicsWindow->pLogicalDevice->GraphicsQueueMutexes[QueueIndex]);

	vkFreeCommandBuffers(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VkCmdPool, 1, &VkCmdBuffer);
	vkDestroyCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VkCmdPool, NULL);

	if (pImageSource->ImageData->LinearSize == NULL && pImageSource->ImageData->ImageSize == NULL)
	{

	}
	else
	{

		GPUfree(pGraphicsWindow->pLogicalDevice, &SrcAllocation);
	}
}

void ReCreate_BufferHeader(RHeaderBuffer* pResourceHeader, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iBufferSource) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_BufferHeader()", "pResourceHeader->iBufferSource Invalid");
		return;
	}
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iGraphicsWindow) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_BufferHeader()", "pResourceHeader->iGraphicsWindow Invalid");
		return;
	}
#endif
	RHeaderBufferSource* pBufferSource = (RHeaderBufferSource*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iBufferSource);
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
#ifndef NDEBUG
	if (pBufferSource->Data.LinearSize == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_BufferHeader()", "pBufferSource->Data.LinearSize == NULL");
		return;
	}
	if (pBufferSource->Data.pData == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_BufferHeader()", "pBufferSource->Data.pData == NULLPTR");
		return;
	}
	if (pGraphicsWindow->pLogicalDevice == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_BufferHeader()", "pGraphicsWindow->pLogicalDevice == NULLPTR, Unitialized GraphicsWindow.");
		return;
	}
#endif
	VkResult res = VK_SUCCESS;
	{
		VkBufferCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		Info.size = pBufferSource->Data.LinearSize;
		Info.usage = (VkBufferUsageFlags)((pResourceHeader->BufferUsage != NULL) ? pResourceHeader->BufferUsage : (VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT));
		Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		Info.pQueueFamilyIndices = NULL;
		Info.queueFamilyIndexCount = NULL;
		Info.flags = NULL;
		Info.pNext = NULL;
		if (vkCreateBuffer(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->GPU_Buffer.VkBuffer) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_BufferHeader()", "vkCreateBuffer Failed, VkResult == ", res);
			return;
		}
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pResourceHeader->GPU_Buffer.VkBuffer, &memRequirements);

	pResourceHeader->GPU_Buffer.Allocation = GPUmalloc(pGraphicsWindow->pLogicalDevice, memRequirements, TargetMemory_Dst, pResourceHeader->AllocationType, ThreadIndex);
	if (pResourceHeader->GPU_Buffer.Allocation.SizeBytes == NULL)
	{
		Engine_Ref_FunctionError("ReCreate_BufferHeader()", "Not Enough Space In GPU Memory!", NULL);
		return;
	}

	vkBindBufferMemory(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pResourceHeader->GPU_Buffer.VkBuffer, pResourceHeader->GPU_Buffer.Allocation.Allocater.VkMemory, pResourceHeader->GPU_Buffer.Allocation.Pointer);

	VkCommandPool VkCmdPool = NULL;
	VkCommandBuffer VkCmdBuffer = NULL;
	{
		VkCommandPoolCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		Info.queueFamilyIndex = pGraphicsWindow->pLogicalDevice->MemoryQueueFamilyIndex;
		Info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
		if ((res = vkCreateCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &VkCmdPool)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_BufferHeader()", "vkCreateCommandPool Failed, VkResult == ", res);
			return;
		}
	}
	{
		VkCommandBufferAllocateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		Info.commandPool = VkCmdPool;
		Info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		Info.commandBufferCount = 1;
		Info.pNext = NULL;
		if ((res = vkAllocateCommandBuffers(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, &VkCmdBuffer)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_BufferHeader()", "vkAllocateCommandBuffers Failed, VkResult == ", res);
			return;
		}
	}
	{
		VkCommandBufferBeginInfo BeginInfo;
		memset(&BeginInfo, NULL, sizeof(BeginInfo));
		BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		BeginInfo.pInheritanceInfo = NULL;
		BeginInfo.pNext = NULL;
		if ((res = vkBeginCommandBuffer(VkCmdBuffer, &BeginInfo)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_BufferHeader()", "vkBeginCommandBuffer Failed, VkResult == ", res);
			return;
		}
	}

	GPU_Allocation SrcAllocation;
	memset(&SrcAllocation, 0, sizeof(SrcAllocation));
	if (pBufferSource->Data.pData == NULL)
	{

	}
	else
	{
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pResourceHeader->GPU_Buffer.VkBuffer, &memRequirements);

		SrcAllocation = GPUmalloc(pGraphicsWindow->pLogicalDevice, memRequirements, TargetMemory_Src, AllocationType_Linear, ThreadIndex);
		if (SrcAllocation.SizeBytes == NULL)
		{
			Engine_Ref_FunctionError("ReCreate_BufferHeader()", "Not Enough Space In GPU Memory!", NULL);
			return;
		}

		memcpy((void*)((uint64_t)SrcAllocation.Allocater.pArenaAllocater->MappedMemory + SrcAllocation.Pointer), pBufferSource->Data.pData, pBufferSource->Data.LinearSize);

		VkBufferCopy region;
		region.srcOffset = SrcAllocation.Pointer;
		region.dstOffset = 0;
		region.size = pBufferSource->Data.LinearSize;

		vkCmdCopyBuffer(
			VkCmdBuffer,
			SrcAllocation.Allocater.pArenaAllocater->VkBuffer,
			pResourceHeader->GPU_Buffer.VkBuffer,
			1,
			&region
		);
	}

	vkEndCommandBuffer(VkCmdBuffer);

	uint32_t QueueIndex = 0;
	{
		bool found = false;
		while (found == false)
		{
			for (size_t i = 0; i < pGraphicsWindow->pLogicalDevice->MemoryQueueFamilySize; i++)
			{
				if (Engine_Ref_TryLock_Mutex(pGraphicsWindow->pLogicalDevice->MemoryQueueMutexes[i]) == Success)
				{
					QueueIndex = i;
					found = true;
					break;
				}
			}
		}
	}
	VkQueue Queue = NULL;
	vkGetDeviceQueue(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->pLogicalDevice->MemoryQueueFamilyIndex, QueueIndex, &Queue);

	VkSubmitInfo SubmitInfo;
	memset(&SubmitInfo, NULL, sizeof(SubmitInfo));
	SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.commandBufferCount = (uint32_t)1;
	SubmitInfo.pCommandBuffers = &VkCmdBuffer;

	if ((res = vkQueueSubmit(Queue, 1, &SubmitInfo, VK_NULL_HANDLE)) != VK_SUCCESS)
	{
		Engine_Ref_FunctionError("ReCreate_BufferHeader()", "vkQueueSubmit Failed, VkResult == ", res);
		return;
	}

	vkQueueWaitIdle(Queue);
	Engine_Ref_Unlock_Mutex(pGraphicsWindow->pLogicalDevice->MemoryQueueMutexes[QueueIndex]);


	vkFreeCommandBuffers(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VkCmdPool, 1, &VkCmdBuffer);
	vkDestroyCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VkCmdPool, NULL);

	if (pBufferSource->Data.pData == NULL)
	{

	}
	else
		GPUfree(pGraphicsWindow->pLogicalDevice, &SrcAllocation);
}

void ReCreate_RenderHeader(RHeaderRender* pResourceHeader, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iGraphicsWindow) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_RenderHeader()", "pResourceHeader->iGraphicsWindow Invalid");
		return;
	}
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iTextureTarget) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_RenderHeader()", "pResourceHeader->iTextureTarget Invalid");
		return;
	}
#endif
	VkResult res = VK_SUCCESS;
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
	RHeaderTexture* pTexture = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iTextureTarget);
	RHeaderImageSource* pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture->iImageSource);

#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pTexture->iImageSource) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_RenderHeader()", "pTexture->iImageSource Invalid");
		return;
	}
	if (pImageSource->ImageData == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_RenderHeader()", "pImageSource->ImageData == NULLPTR");
		return;
	}
#endif
	pImageSource->ImageData->Width = pGraphicsWindow->CurrentExtentWidth;
	pImageSource->ImageData->Height = pGraphicsWindow->CurrentExtentHeight;
	pImageSource->ImageData->Depth = 1;
	pImageSource->ImageData->Format = (GraphicsFormat)pGraphicsWindow->CurrentSurfaceFormat;
	pImageSource->ImageData->MipmapCount = 1;
	Object_Ref_ReCreate_ResourceHeader(pTexture->Header.Allocation, NULL, 0);
	pResourceHeader->pFrameBuffersSize = pGraphicsWindow->CurrentFrameBuffersSize;
	pResourceHeader->pFrameBuffers = (VkFramebuffer*)calloc(pGraphicsWindow->CurrentFrameBuffersSize, sizeof(*pResourceHeader->pFrameBuffers));
	for (size_t i1 = 0; i1 < pGraphicsWindow->CurrentFrameBuffersSize; i1++)
	{
		uint32_t Framebuffersize = TotalDeferredFramebufferCount;
		VkImageView Framebuffers[] = {
			pGraphicsWindow->SwapChain.FrameBuffers[i1].DeferredImages[0].ImageView,
			pGraphicsWindow->SwapChain.FrameBuffers[i1].DeferredImages[1].ImageView,
			pGraphicsWindow->SwapChain.FrameBuffers[i1].DeferredImages[2].ImageView,
			pGraphicsWindow->SwapChain.FrameBuffers[i1].DeferredImages[3].ImageView,
			pGraphicsWindow->SwapChain.FrameBuffers[i1].DeferredImages[4].ImageView,
			pGraphicsWindow->SwapChain.FrameBuffers[i1].DeferredImages[5].ImageView,
			pGraphicsWindow->SwapChain.FrameBuffers[i1].DeferredImages[6].ImageView,
			pTexture->GPU_Texture.VkImageView,
			pGraphicsWindow->SwapChain.FrameBuffers[i1].VkSwapChainImageView
		};

		VkFramebufferCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		Info.renderPass = pGraphicsWindow->VkRenderPassDeferred;
		Info.attachmentCount = Framebuffersize;
		Info.pAttachments = Framebuffers;
		Info.width = pGraphicsWindow->CurrentExtentWidth;
		Info.height = pGraphicsWindow->CurrentExtentHeight;
		Info.layers = 1;
		if ((res = vkCreateFramebuffer(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->pFrameBuffers[i1])) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_RenderHeader()", "vkCreateFramebuffer Failed. VkResult == ", res);
			return;
		}
	}

}

void ReCreate_ElementGraphics(ElementGraphics* pElement, uint32_t ThreadIndex)
{
	uint64_t pointer = 0;
	for (size_t i = 0; i < pElement->EffectsSize; i++)
	{
		GraphicsEffect* pEffect = (GraphicsEffect*)((void*)((uint64_t)pElement->Effects + pointer));
		GraphicsEffectSignature* pSignature = NULL;
		uint64_t BufferIndex = NULL;
		Find_GraphicsEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
		if (pSignature->ReConstructor != NULL)
		{
			pSignature->ReConstructor(pElement, pEffect, ThreadIndex);
		}
		pointer += pEffect->Header.AllocationSize;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Object Packers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Pack_WeightsHeader(const RHeaderWeights* pResourceHeader, RHeaderWeights* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{

	}
	else
	{

	}
}

void Pack_ImageSourceHeader(const RHeaderImageSource* pResourceHeader, RHeaderImageSource* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		if (pResourceHeader->ImageData != NULL)
		{
			memcpy(((void*)((uint64_t)pData + (uint64_t)*pBufferPointer)), pResourceHeader->ImageData, sizeof(TEXI_HEADER) + pResourceHeader->ImageData->LinearSize);
			pCopiedResourceHeader->ImageData = (TEXI_HEADER*)*pBufferPointer;
			*pBufferPointer += sizeof(TEXI_HEADER) + pResourceHeader->ImageData->LinearSize;
		}
	}
	else
	{
		if (pResourceHeader->ImageData != NULL)
			*pBufferPointer += sizeof(TEXI_HEADER) + pResourceHeader->ImageData->LinearSize;
	}
}

void Pack_BufferSourceHeader(const RHeaderBufferSource* pResourceHeader, RHeaderBufferSource* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		if (pResourceHeader->Data.pData != NULL && pResourceHeader->Data.LinearSize != NULL)
		{
			memcpy(((void*)((uint64_t)pData + (uint64_t)*pBufferPointer)), pResourceHeader->Data.pData, pResourceHeader->Data.LinearSize);
			pCopiedResourceHeader->Data.pData = (unsigned char*)*pBufferPointer;
			*pBufferPointer += pResourceHeader->Data.LinearSize;
		}
	}
	else
	{
		if (pResourceHeader->Data.pData != NULL && pResourceHeader->Data.LinearSize != NULL)
			*pBufferPointer += pResourceHeader->Data.LinearSize;
	}
}

void Pack_GraphicsWindowHeader(const RHeaderGraphicsWindow* pResourceHeader, RHeaderGraphicsWindow* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedResourceHeader->CurrentSurfaceFormat, NULL, sizeof(pCopiedResourceHeader->CurrentSurfaceFormat));
		memset(&pCopiedResourceHeader->CurrentSurfaceColourSpace, NULL, sizeof(pCopiedResourceHeader->CurrentSurfaceColourSpace));
		memset(&pCopiedResourceHeader->CurrentSurfacePresentMode, NULL, sizeof(pCopiedResourceHeader->CurrentSurfacePresentMode));

		memset(&pCopiedResourceHeader->CurrentFrameBuffersSize, NULL, sizeof(pCopiedResourceHeader->CurrentFrameBuffersSize));
		memset(&pCopiedResourceHeader->CurrentExtentHeight, NULL, sizeof(pCopiedResourceHeader->CurrentExtentHeight));
		memset(&pCopiedResourceHeader->CurrentExtentWidth, NULL, sizeof(pCopiedResourceHeader->CurrentExtentWidth));


		memset(&pCopiedResourceHeader->VkShaderVertexDeferred, NULL, sizeof(pCopiedResourceHeader->VkShaderVertexDeferred));
		memset(&pCopiedResourceHeader->VkShaderFragmentDeferred, NULL, sizeof(pCopiedResourceHeader->VkShaderFragmentDeferred));

		memset(&pCopiedResourceHeader->VkDescriptorSetsInputAttachment, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSetsInputAttachment));

		memset(&pCopiedResourceHeader->VkDescriptorSetLayoutInputAttachment, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSetLayoutInputAttachment));
		//memset(&pCopiedResourceHeader->VkDescriptorSetLayoutMaterial, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSetLayoutMaterial));


		memset(&pCopiedResourceHeader->VkPipelineLayoutDeferred, NULL, sizeof(pCopiedResourceHeader->VkPipelineLayoutDeferred));
		memset(&pCopiedResourceHeader->VkRenderPassDeferred, NULL, sizeof(pCopiedResourceHeader->VkRenderPassDeferred));
		memset(&pCopiedResourceHeader->VkPipelineDeferred, NULL, sizeof(pCopiedResourceHeader->VkPipelineDeferred));

		memset(&pCopiedResourceHeader->pLogicalDevice, NULL, sizeof(pCopiedResourceHeader->pLogicalDevice));

		memset(&pCopiedResourceHeader->VkSurface, NULL, sizeof(pCopiedResourceHeader->VkSurface));


		memset(&pCopiedResourceHeader->pWindow, NULL, sizeof(pCopiedResourceHeader->pWindow));

		memset(&pCopiedResourceHeader->SwapChain, NULL, sizeof(pCopiedResourceHeader->SwapChain));

		memset(&pCopiedResourceHeader->FrameIndex, NULL, sizeof(pCopiedResourceHeader->FrameIndex));
		memset(&pCopiedResourceHeader->FramesDone, NULL, sizeof(pCopiedResourceHeader->FramesDone));

		memset(&pCopiedResourceHeader->FramesDone, NULL, sizeof(pCopiedResourceHeader->FramesDone));

		memset(&pCopiedResourceHeader->RecreateFlag, NULL, sizeof(pCopiedResourceHeader->RecreateFlag));
		memset(&pCopiedResourceHeader->CloseFlag, NULL, sizeof(pCopiedResourceHeader->CloseFlag));
		memset(&pCopiedResourceHeader->SwapChainAccessMutex, NULL, sizeof(pCopiedResourceHeader->SwapChainAccessMutex));
	}
	else
	{

	}
}

void Pack_SceneHeader(const RHeaderScene* pResourceHeader, RHeaderScene* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{

	}
	else
	{
	}
}

void Pack_CameraHeader(const RHeaderCamera* pResourceHeader, RHeaderCamera* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
	}
	else
	{
	}
}

void Pack_LightHeader(const RHeaderLight* pResourceHeader, RHeaderLight* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
	}
	else
	{
	}
}

void Pack_SkinHeader(const RHeaderSkin* pResourceHeader, RHeaderSkin* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
	}
	else
	{
	}
}

void Pack_PositionHeader(const RHeaderPosition* pResourceHeader, RHeaderPosition* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
	}
	else
	{
	}
}

void Pack_AnimationChannelHeader(const RHeaderAnimationChannel* pResourceHeader, RHeaderAnimationChannel* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
	}
	else
	{
	}
}

void Pack_AnimationHeader(const RHeaderAnimation* pResourceHeader, RHeaderAnimation* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		pCopiedResourceHeader->LastTime = 0.0;
	}
	else
	{
	}
}

void Pack_MaterialHeader(const RHeaderMaterial* pResourceHeader, RHeaderMaterial* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedResourceHeader->VkMaterialDescriptorPool, NULL, sizeof(pCopiedResourceHeader->VkMaterialDescriptorPool));
		memset(&pCopiedResourceHeader->VkMaterialDescriptorSets, NULL, sizeof(pCopiedResourceHeader->VkMaterialDescriptorSets));
	}
	else
	{
	}
}

void Pack_TextureHeader(const RHeaderTexture* pResourceHeader, RHeaderTexture* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedResourceHeader->GPU_Texture, NULL, sizeof(pCopiedResourceHeader->GPU_Texture));
	}
	else
	{

	}
}

void Pack_BufferHeader(const RHeaderBuffer* pResourceHeader, RHeaderBuffer* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedResourceHeader->GPU_Buffer, NULL, sizeof(pCopiedResourceHeader->GPU_Buffer));
	}
	else
	{

	}
}

void Pack_RenderHeader(const RHeaderRender* pResourceHeader, RHeaderRender* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedResourceHeader->pFrameBuffersSize, NULL, sizeof(pCopiedResourceHeader->pFrameBuffersSize));
		memset(&pCopiedResourceHeader->pFrameBuffers, NULL, sizeof(pCopiedResourceHeader->pFrameBuffers));
	}
	else
	{

	}
}

void Pack_ElementGraphics(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	uint64_t pointer = 0;
	for (size_t i = 0; i < pElement->EffectsSize; i++)
	{
		GraphicsEffect* pEffect = (GraphicsEffect*)((void*)((uint64_t)pElement->Effects + pointer));
		GraphicsEffect* pCopiedEffect = (GraphicsEffect*)((void*)((uint64_t)pCopiedElement->Effects + pointer));
		GraphicsEffectSignature* pSignature = NULL;
		GraphicsEffectBufferIndex BufferIndex = NULL;
		Find_GraphicsEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
		if (pSignature->Packer != NULL)
		{
			pSignature->Packer(pElement, pCopiedElement, pEffect, pCopiedEffect, pBufferPointer, pData, ThreadIndex);
		}
		pointer += pEffect->Header.AllocationSize;
	}

	if (pData != NULL)
	{

	}
	else
	{

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Object UnPackers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UnPack_WeightsHeader(const RHeaderWeights* pResourceHeader, RHeaderWeights* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{

}

void UnPack_ImageSourceHeader(const RHeaderImageSource* pResourceHeader, RHeaderImageSource* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	if (pResourceHeader->ImageData != NULL)
	{
		TEXI_HEADER* pheader = (TEXI_HEADER*)((void*)((uint64_t)pData + (uint64_t)pResourceHeader->ImageData));

		pCopiedResourceHeader->ImageData = (TEXI_HEADER*)malloc(sizeof(TEXI_HEADER) + pheader->LinearSize);
		memcpy(pCopiedResourceHeader->ImageData, (void*)((uint64_t)pData + (uint64_t)pResourceHeader->ImageData), sizeof(TEXI_HEADER) + pheader->LinearSize);
	}
}

void UnPack_BufferSourceHeader(const RHeaderBufferSource* pResourceHeader, RHeaderBufferSource* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	if (pResourceHeader->Data.pData != NULL && pResourceHeader->Data.LinearSize != NULL)
	{
		pCopiedResourceHeader->Data.pData = (unsigned char*)malloc(pResourceHeader->Data.LinearSize);
		memcpy(pCopiedResourceHeader->Data.pData, (void*)((uint64_t)pData + (uint64_t)pResourceHeader->Data.pData), pResourceHeader->Data.LinearSize);
	}
}

void UnPack_GraphicsWindowHeader(const RHeaderGraphicsWindow* pResourceHeader, RHeaderGraphicsWindow* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	ReCreate_GraphicsWindowHeader(pCopiedResourceHeader, ThreadIndex);
}

void UnPack_SceneHeader(const RHeaderScene* pResourceHeader, RHeaderScene* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{

}

void UnPack_CameraHeader(const RHeaderCamera* pResourceHeader, RHeaderCamera* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{

}

void UnPack_LightHeader(const RHeaderLight* pResourceHeader, RHeaderLight* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{

}

void UnPack_SkinHeader(const RHeaderSkin* pResourceHeader, RHeaderSkin* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{

}

void UnPack_PositionHeader(const RHeaderPosition* pResourceHeader, RHeaderPosition* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{

}

void UnPack_AnimationChannelHeader(const RHeaderAnimationChannel* pResourceHeader, RHeaderAnimationChannel* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{

}

void UnPack_AnimationHeader(const RHeaderAnimation* pResourceHeader, RHeaderAnimation* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{

}

void UnPack_MaterialHeader(const RHeaderMaterial* pResourceHeader, RHeaderMaterial* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	ReCreate_MaterialHeader(pCopiedResourceHeader, ThreadIndex);
}

void UnPack_TextureHeader(const RHeaderTexture* pResourceHeader, RHeaderTexture* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	ReCreate_TextureHeader(pCopiedResourceHeader, ThreadIndex);
}

void UnPack_BufferHeader(const RHeaderBuffer* pResourceHeader, RHeaderBuffer* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	ReCreate_BufferHeader(pCopiedResourceHeader, ThreadIndex);
}

void UnPack_RenderHeader(const RHeaderRender* pResourceHeader, RHeaderRender* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	ReCreate_RenderHeader(pCopiedResourceHeader, ThreadIndex);
}

void UnPack_ElementGraphics(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, void* pData, uint32_t ThreadIndex)
{
	uint64_t pointer = 0;
	for (size_t i = 0; i < pElement->EffectsSize; i++)
	{
		GraphicsEffect* pEffect = (GraphicsEffect*)((void*)((uint64_t)pElement->Effects + pointer));
		GraphicsEffect* pCopiedEffect = (GraphicsEffect*)((void*)((uint64_t)pCopiedElement->Effects + pointer));
		GraphicsEffectSignature* pSignature = NULL;
		GraphicsEffectBufferIndex BufferIndex = NULL;
		Find_GraphicsEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
		if (pSignature->UnPacker != NULL)
		{
			pSignature->UnPacker(pElement, pCopiedElement, pEffect, pCopiedEffect, pData, ThreadIndex);
		}
		pointer += pEffect->Header.AllocationSize;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Object Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_WeightsHeader(RHeaderWeights* pResourceHeader, RHeaderWeightsCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_WeightsHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->Weights == NULL && pCreateInfo->WeightsSize != NULL)
		{
			Engine_Ref_ArgsError("Create_WeightsHeader()", "pCreateInfo->Weights == NULLPTR, while pCreateInfo->WeightsSize != NULL");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->WeightsSize = pCreateInfo->WeightsSize;
		for (size_t i = 0; i < pResourceHeader->WeightsSize; i++)
			pResourceHeader->Weights[i] = pCreateInfo->Weights[i];
	}
	*pAllocationSize = sizeof(RHeaderWeights) + (sizeof(float) * pCreateInfo->WeightsSize);
	return (TEXRESULT)(Success);
}

TEXRESULT Create_SceneHeader(RHeaderScene* pResourceHeader, RHeaderSceneCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_SceneHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->Active = pCreateInfo->InitialActive;
	}
	*pAllocationSize = sizeof(RHeaderScene);
	return (TEXRESULT)(Success);
}

TEXRESULT Create_ImageSourceHeader(RHeaderImageSource* pResourceHeader, RHeaderImageSourceCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_ImageSourceHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->ImageData == NULL)
		{
			Engine_Ref_ArgsError("Create_ImageSourceHeader()", "pCreateInfo->ImageData == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->ImageData = (TEXI_HEADER*)malloc(sizeof(*pResourceHeader->ImageData) + pCreateInfo->ImageData->LinearSize);
		memcpy(pResourceHeader->ImageData, pCreateInfo->ImageData, sizeof(*pResourceHeader->ImageData) + pCreateInfo->ImageData->LinearSize);
	}
	*pAllocationSize = sizeof(RHeaderImageSource);
	return (TEXRESULT)(Success);
}

TEXRESULT Create_BufferSourceHeader(RHeaderBufferSource* pResourceHeader, RHeaderBufferSourceCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_BufferSourceHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->Data.pData == NULL && pCreateInfo->Data.LinearSize != NULL)
		{
			Engine_Ref_ArgsError("Create_BufferSourceHeader()", "pCreateInfo->Data.pData == NULLPTR, while pCreateInfo->Data.LinearSize != NULL");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->Data.LinearSize = pCreateInfo->Data.LinearSize;
		pResourceHeader->Data.pData = malloc(pResourceHeader->Data.LinearSize);
		memcpy(pResourceHeader->Data.pData, pCreateInfo->Data.pData, pResourceHeader->Data.LinearSize);
	}
	*pAllocationSize = sizeof(RHeaderBufferSource);
	return (TEXRESULT)Success;
}

TEXRESULT Create_GraphicsWindowHeader(RHeaderGraphicsWindow* pResourceHeader, RHeaderGraphicsWindowCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_GraphicsWindowHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif

		//pResourceHeader->TargetSurfacePresentMode = pCreateInfo->TargetSurfacePresentMode;
		//pResourceHeader->TargetSurfaceFormat = pCreateInfo->TargetSurfaceFormat;
		pResourceHeader->TargetExtentWidth = pCreateInfo->TargetExtentWidth;
		pResourceHeader->TargetExtentHeight = pCreateInfo->TargetExtentHeight;
		pResourceHeader->TargetFrameBuffersSize = pCreateInfo->TargetFrameBuffersSize;

		ReCreate_GraphicsWindowHeader(pResourceHeader, ThreadIndex);
	}
	*pAllocationSize = sizeof(RHeaderGraphicsWindow);
	return (TEXRESULT)Success;
}

TEXRESULT Create_CameraHeader(RHeaderCamera* pResourceHeader, RHeaderCameraCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_CameraHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif

		memcpy(&pResourceHeader->CameraU, &pCreateInfo->CameraU, sizeof(pResourceHeader->CameraU));
		pResourceHeader->Type = pCreateInfo->Type;
	}
	*pAllocationSize = sizeof(RHeaderCamera);
	return (TEXRESULT)Success;
}

TEXRESULT Create_LightHeader(RHeaderLight* pResourceHeader, RHeaderLightCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_LightHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->Intensity = pCreateInfo->Intensity;
		pResourceHeader->Range = pCreateInfo->Range;
		pResourceHeader->Colour[0] = pCreateInfo->Colour[0];
		pResourceHeader->Colour[1] = pCreateInfo->Colour[1];
		pResourceHeader->Colour[2] = pCreateInfo->Colour[2];

		memcpy(&pResourceHeader->LightU, &pCreateInfo->LightU, sizeof(pResourceHeader->LightU));

		pResourceHeader->Type = pCreateInfo->Type;

	}
	*pAllocationSize = sizeof(RHeaderLight);
	return (TEXRESULT)Success;
}

TEXRESULT Create_SkinHeader(RHeaderSkin* pResourceHeader, RHeaderSkinCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_SkinHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->pJoints == NULL)
		{
			Engine_Ref_ArgsError("Create_SkinHeader()", "pCreateInfo->pJoints == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif

		pResourceHeader->InverseBindMatrices = pCreateInfo->InverseBindMatrices;
		pResourceHeader->iSkeleton = pCreateInfo->pSkeleton->Header.Allocation;

		pResourceHeader->JointsSize = pCreateInfo->JointsSize;
		for (size_t i = 0; i < pResourceHeader->JointsSize; i++)
			pResourceHeader->iJoints[i] = pCreateInfo->pJoints[i]->Header.Allocation;
	}
	*pAllocationSize = sizeof(RHeaderSkin) + (sizeof(ObjectAllocation) * pCreateInfo->JointsSize);
	return (TEXRESULT)Success;
}

TEXRESULT Create_PositionHeader(RHeaderPosition* pResourceHeader, RHeaderPositionCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_PositionHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		glm_mat4_copy(pCreateInfo->Matrix, pResourceHeader->Matrix);
	}
	*pAllocationSize = sizeof(RHeaderPosition);
	return (TEXRESULT)Success;
}

TEXRESULT Create_AnimationChannelHeader(RHeaderAnimationChannel* pResourceHeader, RHeaderAnimationChannelCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_AnimationChannelHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->pAnimation == NULL)
		{
			Engine_Ref_ArgsError("Create_AnimationChannelHeader()", "pCreateInfo->pAnimation == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif

		pResourceHeader->Sampler = pCreateInfo->Sampler;
		pResourceHeader->Target = pCreateInfo->Target;
		pResourceHeader->iAnimation = pCreateInfo->pAnimation->Header.Allocation;
	}
	*pAllocationSize = sizeof(RHeaderAnimationChannel);
	return (TEXRESULT)Success;
}

TEXRESULT Create_AnimationHeader(RHeaderAnimation* pResourceHeader, RHeaderAnimationCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_AnimationHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->PlaybackMode = pCreateInfo->PlaybackMode;
		pResourceHeader->Speed = pCreateInfo->Speed;

		pResourceHeader->iChannelsSize = pCreateInfo->pChannelsSize;
		if (pResourceHeader->iChannelsSize != NULL)
			for (size_t i = 0; i < pResourceHeader->iChannelsSize; i++)
				pResourceHeader->iChannels[i] = pCreateInfo->pChannels[i];


	}
	*pAllocationSize = sizeof(RHeaderAnimation) + (sizeof(*pResourceHeader->iChannels) * pCreateInfo->pChannelsSize);
	return (TEXRESULT)Success;
}

TEXRESULT Create_MaterialHeader(RHeaderMaterial* pResourceHeader, RHeaderMaterialCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_MaterialHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->pGraphicsWindow == NULL)
		{
			Engine_Ref_ArgsError("Create_MaterialHeader()", "pCreateInfo->pGraphicsWindow == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->iGraphicsWindow = pCreateInfo->pGraphicsWindow->Header.Allocation;

		pResourceHeader->MetallicFactor = pCreateInfo->MetallicFactor;
		pResourceHeader->RoughnessFactor = pCreateInfo->RoughnessFactor;
		pResourceHeader->AlphaCutoff = pCreateInfo->AlphaCutoff;

		pResourceHeader->OcclusionStrength = pCreateInfo->OcclusionStrength;
		pResourceHeader->NormalScale = pCreateInfo->NormalScale;

		pResourceHeader->AlphaMode = pCreateInfo->AlphaMode;
		pResourceHeader->DoubleSided = pCreateInfo->DoubleSided;

		pResourceHeader->BaseColourTexture = pCreateInfo->BaseColourTexture;
		pResourceHeader->MetallicRoughnessTexture = pCreateInfo->MetallicRoughnessTexture;
		pResourceHeader->EmissiveTexture = pCreateInfo->EmissiveTexture;
		pResourceHeader->NormalTexture = pCreateInfo->NormalTexture;
		pResourceHeader->OcclusionTexture = pCreateInfo->OcclusionTexture;

		pResourceHeader->BaseColourMode = pCreateInfo->BaseColourMode;

		pResourceHeader->BaseColourFactor[0] = pCreateInfo->BaseColourFactor[0];
		pResourceHeader->BaseColourFactor[1] = pCreateInfo->BaseColourFactor[1];
		pResourceHeader->BaseColourFactor[2] = pCreateInfo->BaseColourFactor[2];
		pResourceHeader->BaseColourFactor[3] = pCreateInfo->BaseColourFactor[3];

		pResourceHeader->EmissiveFactor[0] = pCreateInfo->EmissiveFactor[0];
		pResourceHeader->EmissiveFactor[1] = pCreateInfo->EmissiveFactor[1];
		pResourceHeader->EmissiveFactor[2] = pCreateInfo->EmissiveFactor[2];
		pResourceHeader->EmissiveFactor[3] = pCreateInfo->EmissiveFactor[3];
		//glm_vec4_copy(pCreateInfo->BaseColourFactor, pResourceHeader->BaseColourFactor);
		//glm_vec4_copy(pCreateInfo->EmissiveFactor, pResourceHeader->EmissiveFactor);

		ReCreate_MaterialHeader(pResourceHeader, ThreadIndex);
	}
	*pAllocationSize = sizeof(RHeaderMaterial);
	return (TEXRESULT)Success;
}

TEXRESULT Create_TextureHeader(RHeaderTexture* pResourceHeader, RHeaderTextureCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_TextureHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->pGraphicsWindow == NULL)
		{
			Engine_Ref_ArgsError("Create_TextureHeader()", "pCreateInfo->pGraphicsWindow == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->iGraphicsWindow = pCreateInfo->pGraphicsWindow->Header.Allocation;
		pResourceHeader->iImageSource = pCreateInfo->pImageSource->Header.Allocation;

		pResourceHeader->MinFilter = pCreateInfo->MinFilter;
		pResourceHeader->MagFilter = pCreateInfo->MagFilter;
		pResourceHeader->AddressModeU = pCreateInfo->AddressModeU;
		pResourceHeader->AddressModeV = pCreateInfo->AddressModeV;
		pResourceHeader->AddressModeW = pCreateInfo->AddressModeW;
		pResourceHeader->AllocationType = pCreateInfo->AllocationType;
		pResourceHeader->TextureUsage = pCreateInfo->TextureUsage;
		ReCreate_TextureHeader(pResourceHeader, ThreadIndex);
	}
	*pAllocationSize = sizeof(RHeaderTexture);
	return (TEXRESULT)Success;
}

TEXRESULT Create_BufferHeader(RHeaderBuffer* pResourceHeader, RHeaderBufferCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_BufferHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->pGraphicsWindow == NULL)
		{
			Engine_Ref_ArgsError("Create_BufferHeader()", "pCreateInfo->pGraphicsWindow == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->iGraphicsWindow = pCreateInfo->pGraphicsWindow->Header.Allocation;
		pResourceHeader->iBufferSource = pCreateInfo->pBufferSource->Header.Allocation;

		pResourceHeader->AllocationType = pCreateInfo->AllocationType;
		pResourceHeader->BufferUsage = pCreateInfo->BufferUsage;
		ReCreate_BufferHeader(pResourceHeader, ThreadIndex);
	}
	*pAllocationSize = sizeof(RHeaderBuffer);
	return (TEXRESULT)Success;
}

TEXRESULT Create_RenderHeader(RHeaderRender* pResourceHeader, RHeaderRenderCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_RenderHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->pGraphicsWindow == NULL)
		{
			Engine_Ref_ArgsError("Create_RenderHeader()", "pCreateInfo->pGraphicsWindow == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->Clear[0] = pCreateInfo->Clear[0];
		pResourceHeader->Clear[1] = pCreateInfo->Clear[1];
		pResourceHeader->Clear[2] = pCreateInfo->Clear[2];
		pResourceHeader->Clear[3] = pCreateInfo->Clear[3];
		pResourceHeader->iGraphicsWindow = pCreateInfo->pGraphicsWindow->Header.Allocation;
		pResourceHeader->iTextureTarget = pCreateInfo->pTextureTarget->Header.Allocation;

		pResourceHeader->iScenesSize = pCreateInfo->pScenesSize;
		if (pResourceHeader->iScenesSize != NULL)
			for (size_t i = 0; i < pResourceHeader->iScenesSize; i++)
				pResourceHeader->iScenes[i] = pCreateInfo->pScenes[i]->Header.Allocation;


		ReCreate_RenderHeader(pResourceHeader, ThreadIndex);
	}
	*pAllocationSize = sizeof(RHeaderRender) + (sizeof(*pResourceHeader->iScenes) * pCreateInfo->pScenesSize);
	return (TEXRESULT)Success;
}

TEXRESULT Create_ElementGraphics(ElementGraphics* pElement, ElementGraphicsCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	TEXRESULT res = (TEXRESULT)Success;

	uint64_t bytes = 0;
	for (size_t i = 0; i < pCreateInfo->EffectCreateInfosSize; i++)
	{
		GraphicsEffectSignature* pSignature = NULL;
		GraphicsEffectBufferIndex BufferIndex = NULL;
		Find_GraphicsEffectSignature(pCreateInfo->EffectCreateInfos[i].Identifier, &pSignature, &BufferIndex);

		uint64_t AllocationSize = 0;
		if (pSignature->Constructor != NULL)
		{
			if ((res = pSignature->Constructor(pElement, NULL, pCreateInfo->EffectCreateInfos[i].pEffectCreateInfo, &AllocationSize, ThreadIndex)) != (TEXRESULT)Success)
			{
				return res;
			}
		}
		bytes += AllocationSize;
	}

	if (pElement == NULL)
	{

	}
	else
	{
#ifdef NDEBUG
#else
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_ElementGraphics()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->pMaterial == NULL)
		{
			Engine_Ref_ArgsError("Create_ElementGraphics()", "pCreateInfo->pMaterial == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->pGraphicsWindow == NULL)
		{
			Engine_Ref_ArgsError("Create_ElementGraphics()", "pCreateInfo->pGraphicsWindow == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pElement->iGraphicsWindow = pCreateInfo->pGraphicsWindow->Header.Allocation;
		pElement->iMaterial = pCreateInfo->pMaterial->Header.Allocation;

		pElement->EffectsSize = pCreateInfo->EffectCreateInfosSize;
		uint64_t pointer = 0;
		for (size_t i = 0; i < pCreateInfo->EffectCreateInfosSize; i++)
		{
			GraphicsEffect* pEffect = (GraphicsEffect*)((void*)((uint64_t)pElement->Effects + pointer));

			GraphicsEffectSignature* pSignature = NULL;
			GraphicsEffectBufferIndex BufferIndex = NULL;
			Find_GraphicsEffectSignature(pCreateInfo->EffectCreateInfos[i].Identifier, &pSignature, &BufferIndex);

			pEffect->Header.Identifier = pCreateInfo->EffectCreateInfos[i].Identifier;

			uint64_t AllocationSize = 0;
			if (pSignature->Constructor != NULL)
			{
				if ((res = pSignature->Constructor(pElement, pEffect, pCreateInfo->EffectCreateInfos[i].pEffectCreateInfo, &AllocationSize, ThreadIndex)) != (TEXRESULT)Success)
				{
					return res;
				}
			}

			pEffect->Header.AllocationSize = AllocationSize;
			pointer += pEffect->Header.AllocationSize;
		}
	}
	*pAllocationSize = sizeof(ElementGraphics) + bytes;
	return (TEXRESULT)Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Stock Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Draw Effect Element
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Draw_Generic3D(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, GraphicsEffectGeneric3D* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers, RHeaderCamera* pCamera, mat4 CameraVP)
{
	VkDeviceSize offsets[256];
	VkBuffer buffers[256];
	size_t maxattribs = min(pEffect->AttributesSize, pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxVertexInputAttributes);

	RHeaderPosition* pPositionHeader = (RHeaderPosition*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Position);
	RHeaderSkin* pSkinHeader = (RHeaderSkin*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Skin);
	RHeaderWeights* pWeightsHeader = (RHeaderWeights*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Weights);
	RHeaderLight* pLightHeader = (RHeaderLight*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Light);


	PushConstantsGeneric3D PushConstants3D;
	memset(&PushConstants3D, NULL, sizeof(PushConstants3D));
	glm_mat4_copy(CameraVP, PushConstants3D.VP);


	PushConstants3D.InfosOffset = GPU_BufferPointers[0];
	GPU_BufferPointers[0] += maxattribs;

	if (pWeightsHeader != NULL)
	{
		PushConstants3D.WeightsOffset = GPU_BufferPointers[1];
		GPU_BufferPointers[1] += pWeightsHeader->WeightsSize;
	}
	if (pSkinHeader != NULL)
	{
		PushConstants3D.JointsOffset = GPU_BufferPointers[2];
		GPU_BufferPointers[2] += pSkinHeader->JointsSize;
	}
	if (pLightHeader != NULL)
	{
		GPU_BufferPointers[3] += 1;
	}
	if (pPositionHeader != NULL)
	{		
		PushConstants3D.MatrixsOffset = GPU_BufferPointers[4];
		GPU_BufferPointers[4] += 1;
	}

	vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pEffect->VkPipeline);

	vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, Utils.GenericResources[Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].PipelineLayout3D, VK_SHADER_STAGE_ALL, 0,
		pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstants3D);

	uint32_t buffersSize = maxattribs;
	for (size_t i3 = 0; i3 < maxattribs; i3++)
	{
		RHeaderBuffer* buffer = (RHeaderBuffer*)Object_Ref_Get_ResourceHeaderPointer(pEffect->UsedAttributes[i3].Accessor.iBuffer);	
		buffers[i3] = buffer->GPU_Buffer.VkBuffer;
		offsets[i3] = pEffect->UsedAttributes[i3].Accessor.ByteOffset; //  + (uint32_t)pElement->Attributes[i3]->byteOffset
	}

	VkDescriptorSet descriptorsets[2] = {
		pMaterialHeader->VkMaterialDescriptorSets[FrameIndex],
		Utils.GenericResources[Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].VkDescriptorSetsStorageBuffers[FrameIndex],
	};
	uint32_t descriptorsetSize = 2;

	vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
		Utils.GenericResources[Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].PipelineLayout3D, 0, descriptorsetSize, descriptorsets, 0, NULL);

	vkCmdBindVertexBuffers(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 0, buffersSize, buffers, offsets);

	if (pEffect->Indices.Count != NULL)
	{
		RHeaderBuffer* buffer = (RHeaderBuffer*)Object_Ref_Get_ResourceHeaderPointer(pEffect->Indices.iBuffer);

		VkIndexType indextype = VK_INDEX_TYPE_UINT16;
		switch (pEffect->Indices.Format)
		{
		case VK_FORMAT_R8G8B8_UINT:
			indextype = VK_INDEX_TYPE_UINT8_EXT;
			break;
		case VK_FORMAT_R16G16B16_UINT:
			indextype = VK_INDEX_TYPE_UINT16;
			break;
		case VK_FORMAT_R32G32B32_UINT:
			indextype = VK_INDEX_TYPE_UINT32;
			break;
		}
		vkCmdBindIndexBuffer(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, buffer->GPU_Buffer.VkBuffer, pEffect->Indices.ByteOffset, indextype);
		vkCmdDrawIndexed(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->Indices.Count, 1, 0, 0, 0);
	}
	else
	{
		vkCmdDraw(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->UsedAttributes[0].Accessor.Count, 1, 0, 0);
	}
}

void Draw_Generic2D(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, GraphicsEffectGeneric2D* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers, RHeaderCamera* pCamera, mat4 CameraVP)
{
	VkBuffer vkBuffer = GPU_Buffers[0].Allocater.pArenaAllocater->VkBuffer;
	VkDeviceSize VkOffset = GPU_Buffers[0].Pointer + GPU_BufferPointers[0];
	GPU_BufferPointers[0] += sizeof(GPU_GraphicsEffectGeneric2D);

	vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pEffect->VkPipeline);

	PushConstantsGeneric2D PushConstants2D;
	memset(&PushConstants2D, NULL, sizeof(PushConstants2D));
	glm_mat4_copy(CameraVP, PushConstants2D.VP);
	vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, Utils.GenericResources[Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].PipelineLayout2D, VK_SHADER_STAGE_ALL, 0,
		pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstants2D);

	VkDescriptorSet descriptorsets[1] = {
		pMaterialHeader->VkMaterialDescriptorSets[FrameIndex]
	};
	uint32_t descriptorsetSize = 1;

	vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
		Utils.GenericResources[Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].PipelineLayout2D, 0, descriptorsetSize, descriptorsets, 0, NULL);

	vkCmdBindVertexBuffers(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 0, 1, &vkBuffer, &VkOffset);

	vkCmdDraw(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 6, 1, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Update Effect Element
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Update_Generic3D(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, GraphicsEffectGeneric3D* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
	RHeaderPosition* pPositionHeader = (RHeaderPosition*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Position);
	RHeaderSkin* pSkinHeader = (RHeaderSkin*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Skin);
	RHeaderWeights* pWeightsHeader = (RHeaderWeights*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Weights);
	RHeaderLight* pLightHeader = (RHeaderLight*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Light);
	RHeaderAnimationChannel* pAnimationChannelHeader = (RHeaderAnimationChannel*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_AnimationChannel);

	size_t maxattribs = min(pEffect->AttributesSize, pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxVertexInputAttributes);

	if (GPU_Buffers == NULL)
	{
		GPU_BufferPointers[0] += maxattribs * sizeof(Generic3DInfo);
		if (pWeightsHeader != NULL)
		{
			GPU_BufferPointers[1] += pWeightsHeader->WeightsSize * sizeof(float);
		}
		if (pSkinHeader != NULL)
		{
			GPU_BufferPointers[2] += pSkinHeader->JointsSize * sizeof(mat4);
		}
		if (pLightHeader != NULL)
		{
			GPU_BufferPointers[3] += sizeof(GPU_RHeaderLight);
		}
		if (pPositionHeader != NULL)
		{
			GPU_BufferPointers[4] += sizeof(mat4);
		}
	}
	else
	{
		if (pWeightsHeader != NULL)
		{
			float* pWeights = (float*)((uint64_t)GPU_BufferPointers[1]);
			memcpy(pWeights, pWeightsHeader->Weights, pWeightsHeader->WeightsSize * sizeof(*pWeightsHeader->Weights));
			if (pAnimationChannelHeader != NULL && pAnimationChannelHeader->Target == AnimationTargetType_Weights)
			{
				RHeaderAnimation* pAnimation = (RHeaderAnimation*)Object_Ref_Get_ResourceHeaderPointer(pAnimationChannelHeader->iAnimation);

				RHeaderBuffer* pInputBuffer = (RHeaderBuffer*)Object_Ref_Get_ResourceHeaderPointer(pAnimationChannelHeader->Sampler.Input.iBuffer);
				RHeaderBuffer* pOutputBuffer = (RHeaderBuffer*)Object_Ref_Get_ResourceHeaderPointer(pAnimationChannelHeader->Sampler.Output.iBuffer);

				RHeaderBufferSource* pInputBufferSource = (RHeaderBufferSource*)Object_Ref_Get_ResourceHeaderPointer(pInputBuffer->iBufferSource);
				RHeaderBufferSource* pOutputBufferSource = (RHeaderBufferSource*)Object_Ref_Get_ResourceHeaderPointer(pOutputBuffer->iBufferSource);

				void* inputpointer = (void*)((uint64_t)pInputBufferSource->Data.pData + pAnimationChannelHeader->Sampler.Input.ByteOffset);
				void* outputpointer = (void*)((uint64_t)pOutputBufferSource->Data.pData + pAnimationChannelHeader->Sampler.Output.ByteOffset);

				float barrier = ((float*)inputpointer)[pAnimationChannelHeader->KeyFrame];
				float barrier1 = ((float*)inputpointer)[pAnimationChannelHeader->KeyFrame + 1];

				//every interpolation must start with 0 and end with 1
				double frametime = normalize_d(pAnimation->Time - barrier, barrier1 - barrier, 0.0);
				frametime = glm_clamp(frametime, 0.0f, 1.0f);

				switch (pAnimationChannelHeader->Sampler.Interpolation)
				{
				case InterpolationType_Linear:
					for (size_t i2 = 0; i2 < pWeightsHeader->WeightsSize - 1; i2++)
						pWeights[1 + i2] = glm_lerp(((float*)outputpointer)[((pAnimationChannelHeader->KeyFrame) * (pWeightsHeader->WeightsSize - 1)) + i2],
							((float*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * (pWeightsHeader->WeightsSize - 1)) + i2], (float)frametime);
					break;
				case InterpolationType_Step:
					for (size_t i2 = 0; i2 < pWeightsHeader->WeightsSize - 1; i2++)
						pWeights[1 + i2] = glm_smoothstep(((float*)outputpointer)[((pAnimationChannelHeader->KeyFrame) * (pWeightsHeader->WeightsSize - 1)) + i2],
							((float*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * (pWeightsHeader->WeightsSize - 1)) + i2], (float)frametime);
					break;
				case InterpolationType_Cubicspline:
					float deltaTime = barrier1 - barrier;
					for (size_t i2 = 0; i2 < pWeightsHeader->WeightsSize - 1; i2++)
					{
						//data should be interlaced intangent-spline-outtangent
						float* currentoutputpointer = &((float*)outputpointer)[((pAnimationChannelHeader->KeyFrame) * ((pWeightsHeader->WeightsSize - 1) * 3)) + (i2 * 3)];
						float* currentoutputpointer1 = &((float*)outputpointer)[((pAnimationChannelHeader->KeyFrame + 1) * ((pWeightsHeader->WeightsSize - 1) * 3)) + (i2 * 3)];

						float previousTangent = deltaTime * currentoutputpointer[2];
						float nextTangent = deltaTime * currentoutputpointer1[0];

						pWeights[1 + i2] = CubicSplineInterpolation(currentoutputpointer[1], previousTangent, currentoutputpointer1[1], nextTangent, frametime);
					}
					break;
				}
			}

			float prevmax = FLT_MAX;
			for (size_t i5 = 0; i5 < pEffect->AttributesSize; i5++)
			{
				float curmax = 0;
				for (size_t i6 = 0; i6 < pEffect->AttributesSize; i6++)
				{
					if (pEffect->UsedAttributes[i5].AttribType == pEffect->Attributes[i6].AttribType) //pElement->ActiveAccessors[i]->Attirbutetype == pElement->Attributes[i1]->Attirbutetype
					{
						if (pWeights[pEffect->Attributes[i6].TargetGroup] >= curmax &&
							pWeights[pEffect->Attributes[i6].TargetGroup] < prevmax &&
							pEffect->Attributes[i6].TargetGroup != 0 && pEffect->UsedAttributes[i5].TargetGroup != 0
							)
						{
							curmax = pWeights[pEffect->Attributes[i6].TargetGroup];
							pEffect->UsedAttributes[i5] = pEffect->Attributes[i6];
						}
					}
				}
				prevmax = pWeights[pEffect->UsedAttributes[i5].TargetGroup];
			}
			GPU_BufferPointers[1] += pWeightsHeader->WeightsSize * sizeof(float);
		}
		if (pSkinHeader != NULL)
		{
			mat4 skeleton;
			glm_mat4_identity(skeleton);
			if (Object_Ref_Get_ObjectAllocationValidity(pSkinHeader->iSkeleton) == (TEXRESULT)Success)
			{
				Calculate_TotalMatrix(&skeleton, pSkinHeader->iSkeleton);
			}
			mat4* pmats = (mat4*)((void*)((uint64_t)GPU_BufferPointers[2]));
			RHeaderBuffer* pBuffer = (RHeaderBuffer*)Object_Ref_Get_ResourceHeaderPointer(pSkinHeader->InverseBindMatrices.iBuffer);
			RHeaderBufferSource* pBufferSource = Object_Ref_Get_ResourceHeaderPointer(pBuffer->iBufferSource);
			mat4* pIBM = (mat4*)((void*)((uint64_t)pBufferSource->Data.pData + (uint64_t)pSkinHeader->InverseBindMatrices.ByteOffset));
			for (size_t i1 = 0; i1 < pSkinHeader->JointsSize; i1++)
			{
				mat4 temp;
				glm_mat4_identity(temp);
				Calculate_TotalMatrix(&temp, pSkinHeader->iJoints[i1]);
				mat4 inverseskeleton;
				glm_mat4_identity(inverseskeleton);
				glm_mat4_inv_sse2(skeleton, inverseskeleton);
				glm_mul_sse2(inverseskeleton, temp, pmats[i1]);
				glm_mul_sse2(pmats[i1], pIBM[i1], pmats[i1]);
			}
			GPU_BufferPointers[2] += pSkinHeader->JointsSize * sizeof(mat4);
		}
		if (pLightHeader != NULL)
		{
			GPU_RHeaderLight templight;
			memset(&templight, NULL, sizeof(templight));
			templight.Intensity = pLightHeader->Intensity;
			templight.Range = pLightHeader->Range;
			templight.InnerConeAngle = pLightHeader->LightU.Spot.InnerConeAngle;
			templight.OuterConeAngle = pLightHeader->LightU.Spot.OuterConeAngle;
			templight.Colour[0] = pLightHeader->Colour[0];
			templight.Colour[1] = pLightHeader->Colour[1];
			templight.Colour[2] = pLightHeader->Colour[2];
			templight.Colour[3] = 1.0;
			templight.Type = pLightHeader->Type;

			if (pPositionHeader != NULL)
			{
				vec4 translationf;
				mat4 temp;
				glm_mat4_identity(temp);
				Calculate_TotalMatrix(&temp, pObject->Header.Allocation);
				glm_vec4_copy(temp[3], translationf);
				templight.Position[0] = translationf[0];
				templight.Position[1] = translationf[1];
				templight.Position[2] = translationf[2];
				templight.Position[3] = translationf[3];
			}
			else
			{
				templight.Position[0];
				templight.Position[1];
				templight.Position[2];
				templight.Position[3];
			}

			memcpy((void*)((uint64_t)GPU_BufferPointers[3]), &templight, sizeof(templight));
			GPU_BufferPointers[3] += sizeof(GPU_RHeaderLight);
		}
		if (pPositionHeader != NULL)
		{
			mat4* pMatrix = (mat4*)(void*)((uint64_t)GPU_BufferPointers[4]);
			glm_mat4_identity(*pMatrix);
			Calculate_TotalMatrix(pMatrix, pObject->Header.Allocation);
			GPU_BufferPointers[4] += sizeof(mat4);
		}
		for (size_t i = 0; i < maxattribs; i++)
		{
			Generic3DInfo* pInfo = (GPU_GraphicsEffectGeneric2D*)((uint64_t)GPU_BufferPointers[0]);
			pInfo->TargetGroup = pEffect->UsedAttributes[i].TargetGroup;
			pInfo->Bits = 1;
			GPU_BufferPointers[0] += sizeof(Generic3DInfo);
		}
	}
}

void Update_Generic2D(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, GraphicsEffectGeneric2D* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
	if (GPU_Buffers == NULL)
	{
		GPU_BufferPointers[0] += sizeof(GPU_GraphicsEffectGeneric2D);
	}
	else
	{
		GPU_GraphicsEffectGeneric2D* pGPU_effect = (GPU_GraphicsEffectGeneric2D*)((uint64_t)GPU_BufferPointers[0]);
		
		glm_vec2_copy(pEffect->Size, pGPU_effect->Size);
		glm_vec3_copy(pEffect->Position, pGPU_effect->Position);

		glm_vec2_copy(pEffect->BoundingBoxSize, pGPU_effect->BoundingBoxSize);
		glm_vec2_copy(pEffect->BoundingBoxPosition, pGPU_effect->BoundingBoxPosition);

		pGPU_effect->TextureOffset[0] = pEffect->TextureOffset[0];
		pGPU_effect->TextureOffset[1] = pEffect->TextureOffset[1];

		pGPU_effect->TextureSize[0] = pEffect->TextureSize[0];
		pGPU_effect->TextureSize[1] = pEffect->TextureSize[1];

		GPU_BufferPointers[0] += sizeof(GPU_GraphicsEffectGeneric2D);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Signature Updates
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdateSignature_Generic3D(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
	//animations frame update
	for (size_t anim = 0; anim < Utils.RHeaderAnimationBuffer.Size;)
	{
		RHeaderAnimation* pAnimation = (RHeaderAnimation*)&Utils.RHeaderAnimationBuffer.Buffer[anim];
		if (pAnimation->Header.AllocationSize != NULL && pAnimation->Header.Allocation.Identifier == (uint32_t)GraphicsHeader_Animation)
		{
			pAnimation->Time += (((double)clock() / (double)CLOCKS_PER_SEC) - pAnimation->LastTime) * pAnimation->Speed;
			pAnimation->LastTime = ((double)clock() / (double)CLOCKS_PER_SEC);

			for (size_t i = 0; i < pAnimation->iChannelsSize; i++)
			{
				RHeaderAnimationChannel* pAnimationChannelHeader = (RHeaderAnimationChannel*)Object_Ref_Get_ResourceHeaderPointer(pAnimation->iChannels[i]);

				if (pAnimationChannelHeader->Sampler.Input.Count > pAnimation->longest)
				{
					pAnimation->longest = i;
				}
			}
			for (size_t i = 0; i < pAnimation->iChannelsSize; i++)
			{			
				RHeaderAnimationChannel* pAnimationChannelHeader = (RHeaderAnimationChannel*)Object_Ref_Get_ResourceHeaderPointer(pAnimation->iChannels[i]);

				RHeaderBuffer* pInputBuffer = (RHeaderBuffer*)Object_Ref_Get_ResourceHeaderPointer(pAnimationChannelHeader->Sampler.Input.iBuffer);
				RHeaderBuffer* pOutputBuffer = (RHeaderBuffer*)Object_Ref_Get_ResourceHeaderPointer(pAnimationChannelHeader->Sampler.Output.iBuffer);

				RHeaderBufferSource* pInputBufferSource = (RHeaderBufferSource*)Object_Ref_Get_ResourceHeaderPointer(pInputBuffer->iBufferSource);
				RHeaderBufferSource* pOutputBufferSource = (RHeaderBufferSource*)Object_Ref_Get_ResourceHeaderPointer(pOutputBuffer->iBufferSource);

				void* inputpointer = (void*)((uint64_t)pInputBufferSource->Data.pData + pAnimationChannelHeader->Sampler.Input.ByteOffset);
				void* outputpointer = (void*)((uint64_t)pOutputBufferSource->Data.pData + pAnimationChannelHeader->Sampler.Output.ByteOffset);

				float barrier = ((float*)inputpointer)[pAnimationChannelHeader->KeyFrame];
				float barrier1 = ((float*)inputpointer)[pAnimationChannelHeader->KeyFrame + 1];

				while (((pAnimation->Speed >= 0.0) ? false : (pAnimation->Time < barrier)) ||
					((pAnimation->Speed <= 0.0) ? false : (pAnimation->Time > barrier1))) // pAnimation->Time > barrier1 || (pAnimation->Time) <= barrier
				{
					pAnimationChannelHeader->KeyFrame += (pAnimation->Speed >= 0.0) ? 1 : -1;
					if (pAnimation->longest == i)
					{
						if (pAnimationChannelHeader->KeyFrame < 0) //end reached
						{
							pAnimationChannelHeader->KeyFrame = 0;
							switch (pAnimation->PlaybackMode)
							{
							case AnimationPlaybackMode_Once:
								break;
							case AnimationPlaybackMode_Repeat:
								pAnimation->Time = ((float*)inputpointer)[pAnimationChannelHeader->Sampler.Input.Count - 2];
								for (size_t i1 = 0; i1 < pAnimation->iChannelsSize; i1++)
								{
									RHeaderAnimationChannel* pAnimationChannelHeader1 = (RHeaderAnimationChannel*)Object_Ref_Get_ResourceHeaderPointer(pAnimation->iChannels[i1]);
									pAnimationChannelHeader1->KeyFrame = pAnimationChannelHeader1->Sampler.Input.Count - 2;
								}
								break;
							case AnimationPlaybackMode_BackToFront:
								pAnimation->Time = 0.0;
								pAnimation->Speed = pAnimation->Speed * -1;
								break;
							}
							break;
						}
						else if ((pAnimationChannelHeader->KeyFrame) > (pAnimationChannelHeader->Sampler.Input.Count - 2)) //end reached
						{
							pAnimationChannelHeader->KeyFrame = pAnimationChannelHeader->Sampler.Input.Count - 2;
							switch (pAnimation->PlaybackMode)
							{
							case AnimationPlaybackMode_Once:
								break;
							case AnimationPlaybackMode_Repeat:
								pAnimation->Time = 0.0;
								for (size_t i1 = 0; i1 < pAnimation->iChannelsSize; i1++)
								{
									RHeaderAnimationChannel* pAnimationChannelHeader1 = (RHeaderAnimationChannel*)Object_Ref_Get_ResourceHeaderPointer(pAnimation->iChannels[i1]);
									pAnimationChannelHeader1->KeyFrame = 0;
								}
								break;
							case AnimationPlaybackMode_BackToFront:
								pAnimation->Time = ((float*)inputpointer)[pAnimationChannelHeader->Sampler.Input.Count - 2];
								pAnimation->Speed = pAnimation->Speed * -1;
								break;
							}
							break;
						}
					}
					else
					{
						if (pAnimationChannelHeader->KeyFrame < 0) //end reached
						{
							pAnimationChannelHeader->KeyFrame = 0;
							break;
						}
						else if ((pAnimationChannelHeader->KeyFrame) > (pAnimationChannelHeader->Sampler.Input.Count - 2)) //end reached
						{
							pAnimationChannelHeader->KeyFrame = pAnimationChannelHeader->Sampler.Input.Count - 2;
							break;
						}
					}
	
					barrier = ((float*)inputpointer)[pAnimationChannelHeader->KeyFrame];
					barrier1 = ((float*)inputpointer)[pAnimationChannelHeader->KeyFrame + 1];
				}
			}	
			anim += pAnimation->Header.AllocationSize;
		}
		else
		{
			anim++;
		}
	}
	
	//descriptor binding = info 0 weights 1, joints 2, lights 3, matrixs 4
	//buffer indexes = amorphous 0, weights 1, joints 2, lights 3, matrixs 4
	for (size_t i = 0; i < StorageBufferBindings; i++)
	{
		if (GPU_Buffers[i].SizeBytes != NULL)
		{
			VkDescriptorBufferInfo BufferInfo;
			BufferInfo.buffer = GPU_Buffers[i].Allocater.pArenaAllocater->VkBuffer;
			BufferInfo.offset = GPU_Buffers[i].Pointer;
			BufferInfo.range = (GPU_Buffers[i].SizeBytes != NULL) ? GPU_Buffers[i].SizeBytes : VK_WHOLE_SIZE;
			Update_Descriptor(pGraphicsWindow->pLogicalDevice, Utils.GenericResources[Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].VkDescriptorSetsStorageBuffers[FrameIndex], i, 0, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &BufferInfo, NULL);
		}
	}
}

void UpdateSignature_Generic2D(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Destroy_Generic3D(ElementGraphics* pElement, GraphicsEffectGeneric3D* pEffect, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);

	if (pEffect->VkPipeline != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipeline, NULL);
	if (pEffect->UsedAttributes != NULL)
		free(pEffect->UsedAttributes);
	if (pEffect->VkShaderVertex != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderVertex, NULL);
	if (pEffect->VkShaderFragment != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderFragment, NULL);
}

void Destroy_Generic2D(ElementGraphics* pElement, GraphicsEffectGeneric2D* pEffect, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);

	if (pEffect->VkPipeline != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipeline, NULL);
	if (pEffect->VkShaderVertex != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderVertex, NULL);
	if (pEffect->VkShaderFragment != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderFragment, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Recreation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cmpfunction(const void* a, const void* b)
{
	if (Get_AttributeTypePriority(*((Attribute*)(a))) < Get_AttributeTypePriority(*((Attribute*)(b))))  return -1;
	if (Get_AttributeTypePriority(*((Attribute*)(a))) == Get_AttributeTypePriority(*((Attribute*)(b))))  return 0;
	if (Get_AttributeTypePriority(*((Attribute*)(a))) > Get_AttributeTypePriority(*((Attribute*)(b))))  return 1;
}

void ReCreate_Generic3D(ElementGraphics* pElement, GraphicsEffectGeneric3D* pEffect, uint32_t ThreadIndex)
{
	VkResult res = VK_SUCCESS;
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);
	RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);

	size_t sfloatc = 0;
	size_t ufloatc = 0;
	size_t sintc = 0;
	size_t uintc = 0;
	size_t totalc = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//sorting attriubs
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	size_t maxattribs = min(pEffect->AttributesSize, pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxVertexInputAttributes);
	pEffect->UsedAttributes = (Attribute*)calloc(pEffect->AttributesSize, sizeof(Attribute));
	memcpy(pEffect->UsedAttributes, pEffect->Attributes, pEffect->AttributesSize * sizeof(Attribute));
	qsort(pEffect->UsedAttributes, pEffect->AttributesSize, sizeof(*pEffect->UsedAttributes), cmpfunction);

	for (size_t i = 0; i < pEffect->AttributesSize; i++)
	{
		if (GraphicsFormatDataType[pEffect->Attributes[i].Accessor.Format][0] == SignedFloat)
		{
			pEffect->UsedAttributes[sfloatc] = pEffect->Attributes[i];
			sfloatc++;

		}
	}
	for (size_t i = 0; i < pEffect->AttributesSize; i++)
	{
		if (GraphicsFormatDataType[pEffect->Attributes[i].Accessor.Format][0] == UnsignedFloat)
		{
			pEffect->UsedAttributes[sfloatc + ufloatc] = pEffect->Attributes[i];
			ufloatc++;

		}
	}
	for (size_t i = 0; i < pEffect->AttributesSize; i++)
	{
		if (GraphicsFormatDataType[pEffect->Attributes[i].Accessor.Format][0] == SignedInt)
		{
			pEffect->UsedAttributes[sfloatc + ufloatc + sintc] = pEffect->Attributes[i];
			sintc++;

		}
	}
	for (size_t i = 0; i < pEffect->AttributesSize; i++)
	{
		if (GraphicsFormatDataType[pEffect->Attributes[i].Accessor.Format][0] == UnsignedInt)
		{
			pEffect->UsedAttributes[sfloatc + ufloatc + sintc + uintc] = pEffect->Attributes[i];
			uintc++;
		}
	}

	uint64_t PassthroughAttribsSize = 0;
	for (size_t i = 0; i < maxattribs; i++)
		if ((pEffect->UsedAttributes[i].AttribType == AttributeType_Colour) || (pEffect->UsedAttributes[i].AttribType == AttributeType_TexCoord))
			PassthroughAttribsSize++;

	uint64_t VertexShader3DCompiledPointer = 0;
	SPIRV* VertexShader3DCompiled = NULL;
	uint64_t FragmentShader3DCompiledPointer = 0;
	SPIRV* FragmentShader3DCompiled = NULL;

	const SPIRV Vertex_Main0[] = VertexShader3D_Main0(maxattribs, PassthroughAttribsSize);
	const SPIRV Fragment_Main0[] = FragmentShader3D_Main0(PassthroughAttribsSize);

	Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Main0_Size, 1);
	memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Main0, VertexShader3D_Main0_Size); //copy first part
	VertexShader3DCompiledPointer += VertexShader3D_Main0_Size;

	Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Main0_Size, 1);
	memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Main0, FragmentShader3D_Main0_Size); //copy first part
	FragmentShader3DCompiledPointer += FragmentShader3D_Main0_Size;


	for (size_t i = 0, PassthroughAttribsPointer = 0; i < maxattribs; i++)
	{
		const SPIRV Vertex_InterfaceInput[] = VertexShader3D_Interface_Attribute(i, 0);
		const SPIRV Vertex_InterfaceOutput[] = VertexShader3D_Interface_Attribute(i, 1);
		const SPIRV Fragment_InterfaceInput[] = FragmentShader3D_Interface_Attribute(PassthroughAttribsPointer);

		Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Interface_Attribute_Size, 1);
		memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_InterfaceInput, VertexShader3D_Interface_Attribute_Size);
		VertexShader3DCompiledPointer += VertexShader3D_Interface_Attribute_Size;

		if ((pEffect->UsedAttributes[i].AttribType == AttributeType_Colour) || (pEffect->UsedAttributes[i].AttribType == AttributeType_TexCoord))
		{
			Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Interface_Attribute_Size, 1);
			memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_InterfaceOutput, VertexShader3D_Interface_Attribute_Size);
			VertexShader3DCompiledPointer += VertexShader3D_Interface_Attribute_Size;

			Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Interface_Attribute_Size, 1);
			memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_InterfaceInput, FragmentShader3D_Interface_Attribute_Size);
			FragmentShader3DCompiledPointer += FragmentShader3D_Interface_Attribute_Size;
			PassthroughAttribsPointer++;
		}
	}

	const SPIRV Fragment_ExecutionMode[] = FragmentShader3D_ExecutionMode();
	Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_ExecutionMode_Size, 1);
	memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_ExecutionMode, FragmentShader3D_ExecutionMode_Size);
	FragmentShader3DCompiledPointer += FragmentShader3D_ExecutionMode_Size;


	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->EmissiveTexture.iTexture) == (TEXRESULT)Success) {
		const SPIRV Fragment_EmissiveTexture[] = FragmentShader3D_Decoration_TextureInput(1, Fragment3DVariable_UniformConstantPointer_Image_float32_Emissive);

		Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Decoration_TextureInput_Size, 1);
		memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_EmissiveTexture, FragmentShader3D_Decoration_TextureInput_Size);
		FragmentShader3DCompiledPointer += FragmentShader3D_Decoration_TextureInput_Size;
	}if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->NormalTexture.iTexture) == (TEXRESULT)Success) {
		const SPIRV Fragment_NormalTexture[] = FragmentShader3D_Decoration_TextureInput(2, Fragment3DVariable_UniformConstantPointer_Image_float32_Normal);

		Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Decoration_TextureInput_Size, 1);
		memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_NormalTexture, FragmentShader3D_Decoration_TextureInput_Size);
		FragmentShader3DCompiledPointer += FragmentShader3D_Decoration_TextureInput_Size;
	}if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->OcclusionTexture.iTexture) == (TEXRESULT)Success) {
		const SPIRV Fragment_OcclusionTexture[] = FragmentShader3D_Decoration_TextureInput(3, Fragment3DVariable_UniformConstantPointer_Image_float32_Occlusion);

		Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Decoration_TextureInput_Size, 1);
		memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_OcclusionTexture, FragmentShader3D_Decoration_TextureInput_Size);
		FragmentShader3DCompiledPointer += FragmentShader3D_Decoration_TextureInput_Size;
	}if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->BaseColourTexture.iTexture) == (TEXRESULT)Success) {
		const SPIRV Fragment_BaseColourTexture[] = FragmentShader3D_Decoration_TextureInput(4, Fragment3DVariable_UniformConstantPointer_Image_float32_BaseColour);

		Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Decoration_TextureInput_Size, 1);
		memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_BaseColourTexture, FragmentShader3D_Decoration_TextureInput_Size);
		FragmentShader3DCompiledPointer += FragmentShader3D_Decoration_TextureInput_Size;
	}if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->MetallicRoughnessTexture.iTexture) == (TEXRESULT)Success) {
		const SPIRV Fragment_MetallicRoughnessTexture[] = FragmentShader3D_Decoration_TextureInput(5, Fragment3DVariable_UniformConstantPointer_Image_float32_MetallicRoughness);

		Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Decoration_TextureInput_Size, 1);
		memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_MetallicRoughnessTexture, FragmentShader3D_Decoration_TextureInput_Size);
		FragmentShader3DCompiledPointer += FragmentShader3D_Decoration_TextureInput_Size;
	}

	for (size_t i = 0, PassthroughAttribsPointer = 0; i < maxattribs; i++)
	{
		//input pointer vert
		const SPIRV Vertex_Decoration_AttributeVariableInput[] = VertexShader3D_Decoration_Attribute(i, 0, i);
		const SPIRV Vertex_Decoration_AttributeVariableOutput[] = VertexShader3D_Decoration_Attribute(i, 1, PassthroughAttribsPointer + 3);
		const SPIRV Fragment_Decoration_AttributeVariableInput[] = FragmentShader3D_Decoration_Attribute(PassthroughAttribsPointer, PassthroughAttribsPointer + 3);
		

		Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Decoration_Attribute_Size, 1);
		memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Decoration_AttributeVariableInput, VertexShader3D_Decoration_Attribute_Size);
		VertexShader3DCompiledPointer += VertexShader3D_Decoration_Attribute_Size;

		if ((pEffect->UsedAttributes[i].AttribType == AttributeType_Colour) || (pEffect->UsedAttributes[i].AttribType == AttributeType_TexCoord))
		{
			Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Decoration_Attribute_Size, 1);
			memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Decoration_AttributeVariableOutput, VertexShader3D_Decoration_Attribute_Size);
			VertexShader3DCompiledPointer += VertexShader3D_Decoration_Attribute_Size;

			Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Decoration_Attribute_Size, 1);
			memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Decoration_AttributeVariableInput, FragmentShader3D_Decoration_Attribute_Size);
			FragmentShader3DCompiledPointer += FragmentShader3D_Decoration_Attribute_Size;
			PassthroughAttribsPointer++;
		}
	}	

	const SPIRV Vertex_Main1[] = VertexShader3D_Main1();
	const SPIRV Fragment_Main1[] = FragmentShader3D_Main1();

	Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Main1_Size, 1);
	memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Main1, VertexShader3D_Main1_Size); //copy second part
	VertexShader3DCompiledPointer += VertexShader3D_Main1_Size;

	Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Main1_Size, 1);
	memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Main1, FragmentShader3D_Main1_Size); //copy second part
	FragmentShader3DCompiledPointer += FragmentShader3D_Main1_Size;

	for (size_t i = 0, PassthroughAttribsPointer = 0; i < maxattribs; i++)
	{
		uint32_t VertexType = 0;
		uint32_t FragmentType = 0;

		switch (pEffect->UsedAttributes[i].AttribType)
		{
		case AttributeType_Position:
			VertexType = Vertex3DType_float32vec3;
			FragmentType = Fragment3DType_float32vec3;
			break;
		case AttributeType_Normal:
			VertexType = Vertex3DType_float32vec3;
			FragmentType = Fragment3DType_float32vec3;
			break;
		case AttributeType_Tangent:
			VertexType = Vertex3DType_float32vec4;
			FragmentType = Fragment3DType_float32vec4;
			break;
		case AttributeType_Joints:
			VertexType = Vertex3DType_int32vec4;
			FragmentType = Fragment3DType_int32vec4;
			break;
		case AttributeType_SkinWeights:
			VertexType = Vertex3DType_float32vec4;
			FragmentType = Fragment3DType_float32vec4;
			break;
		case AttributeType_Colour:
			VertexType = Vertex3DType_float32vec4;
			FragmentType = Fragment3DType_float32vec4;
			break;
		case AttributeType_TexCoord:
			VertexType = Vertex3DType_float32vec2;
			FragmentType = Fragment3DType_float32vec2;
			break;
		}

		const SPIRV Vertex_Variable_AttributeVariableInput[] = VertexShader3D_Variable_AttributeInput(i, VertexType);
		const SPIRV Vertex_Variable_AttributeVariableOutput[] = VertexShader3D_Variable_AttributeOutput(i, VertexType);
		const SPIRV Fragment_Variable_AttributeVariableInput[] = FragmentShader3D_Variable_AttributeInput(PassthroughAttribsPointer, FragmentType);

		Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Variable_AttributeInput_Size, 1);
		memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Variable_AttributeVariableInput, VertexShader3D_Variable_AttributeInput_Size);
		VertexShader3DCompiledPointer += VertexShader3D_Variable_AttributeInput_Size;

		if ((pEffect->UsedAttributes[i].AttribType == AttributeType_Colour) || (pEffect->UsedAttributes[i].AttribType == AttributeType_TexCoord))
		{
			Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Variable_AttributeOutput_Size, 1);
			memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Variable_AttributeVariableOutput, VertexShader3D_Variable_AttributeOutput_Size);
			VertexShader3DCompiledPointer += VertexShader3D_Variable_AttributeOutput_Size;

			Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Variable_AttributeInput_Size, 1);
			memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Variable_AttributeVariableInput, FragmentShader3D_Variable_AttributeInput_Size);
			FragmentShader3DCompiledPointer += FragmentShader3D_Variable_AttributeInput_Size;
			PassthroughAttribsPointer++;
		}
	}

	const SPIRV Vertex_Main2[] = VertexShader3D_Main2();
	const SPIRV Fragment_Main2[] = FragmentShader3D_Main2();

	Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Main2_Size, 1);
	memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Main2, VertexShader3D_Main2_Size); //copy second part
	VertexShader3DCompiledPointer += VertexShader3D_Main2_Size;

	Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Main2_Size, 1);
	memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Main2, FragmentShader3D_Main2_Size); //copy second part
	FragmentShader3DCompiledPointer += FragmentShader3D_Main2_Size;

	uint32_t JointsPair = 0;
	uint32_t SkinWeightsPair = 0;
	uint32_t TextureCoordsPair = 0;
	//function
	for (size_t i = 0, PassthroughAttribsPointer = 0; i < maxattribs; i++)
	{
		const SPIRV Vertex_Function_AttributePosition[] = VertexShader3D_Function_AttributeWeighted(i, Vertex3DType_float32vec3, Vertex3DVariable_OutputPointer_float32vec3_FinalPosition);
		const SPIRV Vertex_Function_AttributeNormal[] = VertexShader3D_Function_AttributeWeighted(i, Vertex3DType_float32vec3, Vertex3DVariable_OutputPointer_float32vec3_FinalNormal);
		const SPIRV Vertex_Function_AttributeTangent[] = VertexShader3D_Function_AttributeWeighted(i, Vertex3DType_float32vec4, Vertex3DVariable_OutputPointer_float32vec4_FinalTangent);
		const SPIRV Vertex_Function_AttributeColour[] = VertexShader3D_Function_AttributePass(i, Vertex3DType_float32vec4, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 1);
		const SPIRV Vertex_Function_AttributeTexCoord[] = VertexShader3D_Function_AttributePass(i, Vertex3DType_float32vec2, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 1);
		const SPIRV Vertex_Function_AttributeJoints[] = VertexShader3D_Function_AttributePass(i, Vertex3DType_int32vec4, Vertex3DVariable_FunctionPointer_int32vec4_Joints);
		const SPIRV Vertex_Function_AttributeSkinWeights[] = VertexShader3D_Function_AttributePass(i, Vertex3DType_float32vec4, Vertex3DVariable_FunctionPointer_float32vec4_SkinWeights);
		/* inplement this fragment
		//colour
		outTransperancy = outTransperancy.rgba  * Mtl.BaseColourFactor;
		//monochrome
		outTransperancy =  vec4(1, 1, 1, outTransperancy.r) * Mtl.BaseColourFactor;
		//solid
		outTransperancy = Mtl.BaseColourFactor;
		*/
		const SPIRV Fragment_Function_AttributeTexCoordEmissive[] = FragmentShader3D_Function_AttributeTexCoord(0, PassthroughAttribsPointer, Fragment3DVariable_UniformConstantPointer_Image_float32_Emissive, Fragment3DVariable_FunctionPointer_float32vec4_Emissive);
		const SPIRV Fragment_Function_AttributeTexCoordNormal[] = FragmentShader3D_Function_AttributeTexCoord(5, PassthroughAttribsPointer, Fragment3DVariable_UniformConstantPointer_Image_float32_Normal, Fragment3DVariable_FunctionPointer_float32vec4_Normal);
		const SPIRV Fragment_Function_AttributeTexCoordOcclusion[] = FragmentShader3D_Function_AttributeTexCoord(10, PassthroughAttribsPointer, Fragment3DVariable_UniformConstantPointer_Image_float32_Occlusion, Fragment3DVariable_FunctionPointer_float32vec4_Occlusion);
		const SPIRV Fragment_Function_AttributeTexCoordBaseColour[] = FragmentShader3D_Function_AttributeTexCoord(15, PassthroughAttribsPointer, Fragment3DVariable_UniformConstantPointer_Image_float32_BaseColour, Fragment3DVariable_FunctionPointer_float32vec4_Colour);
		const SPIRV Fragment_Function_AttributeTexCoordMetallicRoughness[] = FragmentShader3D_Function_AttributeTexCoord(20, PassthroughAttribsPointer, Fragment3DVariable_UniformConstantPointer_Image_float32_MetallicRoughness, Fragment3DVariable_FunctionPointer_float32vec4_MetallicRoughness);

		const SPIRV Fragment_Function_AttributeColour[] = FragmentShader3D_Function_AttributeColour(PassthroughAttribsPointer);

		switch (pEffect->UsedAttributes[i].AttribType)
		{
		case AttributeType_Position:
			Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Function_AttributeWeighted_Size, 1);
			memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Function_AttributePosition, VertexShader3D_Function_AttributeWeighted_Size);
			VertexShader3DCompiledPointer += VertexShader3D_Function_AttributeWeighted_Size;
			break;
		case AttributeType_Normal:
			Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Function_AttributeWeighted_Size, 1);
			memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Function_AttributeNormal, VertexShader3D_Function_AttributeWeighted_Size);
			VertexShader3DCompiledPointer += VertexShader3D_Function_AttributeWeighted_Size;
			break;
		case AttributeType_Tangent:
			Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Function_AttributeWeighted_Size, 1);
			memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Function_AttributeTangent, VertexShader3D_Function_AttributeWeighted_Size);
			VertexShader3DCompiledPointer += VertexShader3D_Function_AttributeWeighted_Size;
			break;
		case AttributeType_Colour:
			Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Function_AttributePass_Size, 1);
			memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Function_AttributeColour, VertexShader3D_Function_AttributePass_Size);
			VertexShader3DCompiledPointer += VertexShader3D_Function_AttributePass_Size;

			Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_AttributeColour_Size, 1);
			memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_AttributeColour, FragmentShader3D_Function_AttributeColour_Size);
			FragmentShader3DCompiledPointer += FragmentShader3D_Function_AttributeColour_Size;
			PassthroughAttribsPointer++;
			break;
		case AttributeType_TexCoord:
			Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Function_AttributePass_Size, 1);
			memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Function_AttributeTexCoord, VertexShader3D_Function_AttributePass_Size);
			VertexShader3DCompiledPointer += VertexShader3D_Function_AttributePass_Size;

			if (pMaterial->EmissiveTexture.UVIndex == TextureCoordsPair && (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->EmissiveTexture.iTexture) == (TEXRESULT)Success)) {
				Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_AttributeTexCoord_Size, 1);
				memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_AttributeTexCoordEmissive, FragmentShader3D_Function_AttributeTexCoord_Size);
				FragmentShader3DCompiledPointer += FragmentShader3D_Function_AttributeTexCoord_Size;
			}if (pMaterial->NormalTexture.UVIndex == TextureCoordsPair && (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->NormalTexture.iTexture) == (TEXRESULT)Success)) {
				Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_AttributeTexCoord_Size, 1);
				memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_AttributeTexCoordNormal, FragmentShader3D_Function_AttributeTexCoord_Size);
				FragmentShader3DCompiledPointer += FragmentShader3D_Function_AttributeTexCoord_Size;
			}if (pMaterial->OcclusionTexture.UVIndex == TextureCoordsPair && (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->OcclusionTexture.iTexture) == (TEXRESULT)Success)) {
				Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_AttributeTexCoord_Size, 1);
				memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_AttributeTexCoordOcclusion, FragmentShader3D_Function_AttributeTexCoord_Size);
				FragmentShader3DCompiledPointer += FragmentShader3D_Function_AttributeTexCoord_Size;
			}if (pMaterial->BaseColourTexture.UVIndex == TextureCoordsPair && (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->BaseColourTexture.iTexture) == (TEXRESULT)Success)) {
				Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_AttributeTexCoord_Size, 1);
				memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_AttributeTexCoordBaseColour, FragmentShader3D_Function_AttributeTexCoord_Size);
				FragmentShader3DCompiledPointer += FragmentShader3D_Function_AttributeTexCoord_Size;
			}if (pMaterial->MetallicRoughnessTexture.UVIndex == TextureCoordsPair && (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->MetallicRoughnessTexture.iTexture) == (TEXRESULT)Success)) {
				Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_AttributeTexCoord_Size, 1);
				memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_AttributeTexCoordMetallicRoughness, FragmentShader3D_Function_AttributeTexCoord_Size);
				FragmentShader3DCompiledPointer += FragmentShader3D_Function_AttributeTexCoord_Size;
			}

			TextureCoordsPair++;
			PassthroughAttribsPointer++;
			break;
		case AttributeType_Joints:
			Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Function_AttributePass_Size, 1);
			memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Function_AttributeJoints, VertexShader3D_Function_AttributePass_Size);
			VertexShader3DCompiledPointer += VertexShader3D_Function_AttributePass_Size;
			JointsPair++;
			break;
		case AttributeType_SkinWeights:
			Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Function_AttributePass_Size, 1);
			memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Function_AttributeSkinWeights, VertexShader3D_Function_AttributePass_Size);
			VertexShader3DCompiledPointer += VertexShader3D_Function_AttributePass_Size;
			SkinWeightsPair++;
			break;
		}

		if (SkinWeightsPair == JointsPair && SkinWeightsPair != 0 && JointsPair != 0)
		{
			const SPIRV VertexShader3D_AttributeFunctionSkin[] = VertexShader3D_Function_AttributeSkin(i);
			Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Function_AttributeSkin_Size, 1);
			memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), VertexShader3D_AttributeFunctionSkin, VertexShader3D_Function_AttributeSkin_Size);
			VertexShader3DCompiledPointer += VertexShader3D_Function_AttributeSkin_Size;
		}
	}
	
	const SPIRV Fragment_Function_Colour[] = FragmentShader3D_Function_Colour();
	const SPIRV Fragment_Function_Alpha[] = FragmentShader3D_Function_Alpha();
	const SPIRV Fragment_Function_Solid[] = FragmentShader3D_Function_Solid();

	switch (pMaterial->BaseColourMode)
	{
	case MaterialMode_Colour:
		Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_Colour_Size, 1);
		memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_Colour, FragmentShader3D_Function_Colour_Size);
		FragmentShader3DCompiledPointer += FragmentShader3D_Function_Colour_Size;
		break;
	case MaterialMode_Alpha:
		Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_Alpha_Size, 1);
		memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_Alpha, FragmentShader3D_Function_Alpha_Size);
		FragmentShader3DCompiledPointer += FragmentShader3D_Function_Alpha_Size;
		break;
	case MaterialMode_Solid:
		Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_Solid_Size, 1);
		memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_Solid, FragmentShader3D_Function_Solid_Size);
		FragmentShader3DCompiledPointer += FragmentShader3D_Function_Solid_Size;
		break;
	}


	const SPIRV Fragment_Function_Opaque[] = FragmentShader3D_Function_Opaque();
	const SPIRV Fragment_Function_Mask[] = FragmentShader3D_Function_Mask();
	const SPIRV Fragment_Function_Blend[] = FragmentShader3D_Function_Blend();

	switch (pMaterial->AlphaMode)
	{
	case AlphaMode_Opaque:
		Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_Opaque_Size, 1);
		memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_Opaque, FragmentShader3D_Function_Opaque_Size);
		FragmentShader3DCompiledPointer += FragmentShader3D_Function_Opaque_Size;
		break;
	case AlphaMode_Mask:
		Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_Mask_Size, 1);
		memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_Mask, FragmentShader3D_Function_Mask_Size);
		FragmentShader3DCompiledPointer += FragmentShader3D_Function_Mask_Size;
		break;
	case AlphaMode_Blend:
		Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Function_Blend_Size, 1);
		memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Function_Blend, FragmentShader3D_Function_Blend_Size);
		FragmentShader3DCompiledPointer += FragmentShader3D_Function_Blend_Size;
		break;
	}

	
	const SPIRV Vertex_Main3[] = VertexShader3D_Main3();
	const SPIRV Fragment_Main3[] = FragmentShader3D_Main3();

	Resize_Array((void**)&VertexShader3DCompiled, VertexShader3DCompiledPointer, VertexShader3DCompiledPointer + VertexShader3D_Main3_Size, 1);
	memcpy((void*)((uint64_t)VertexShader3DCompiled + (uint64_t)VertexShader3DCompiledPointer), Vertex_Main3, VertexShader3D_Main3_Size); //copy third part
	VertexShader3DCompiledPointer += VertexShader3D_Main3_Size;

	Resize_Array((void**)&FragmentShader3DCompiled, FragmentShader3DCompiledPointer, FragmentShader3DCompiledPointer + FragmentShader3D_Main3_Size, 1);
	memcpy((void*)((uint64_t)FragmentShader3DCompiled + (uint64_t)FragmentShader3DCompiledPointer), Fragment_Main3, FragmentShader3D_Main3_Size);  //copy third part
	FragmentShader3DCompiledPointer += FragmentShader3D_Main3_Size;


	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderVertex, VertexShader3DCompiled, VertexShader3DCompiledPointer, "ReCreate_Generic3D()");
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderFragment, FragmentShader3DCompiled, FragmentShader3DCompiledPointer, "ReCreate_Generic3D()");
	
	free(VertexShader3DCompiled);
	free(FragmentShader3DCompiled);

	uint32_t ShaderCount = 2;
	VkPipelineShaderStageCreateInfo ShaderStages[2];
	memset(ShaderStages, NULL, sizeof(*ShaderStages) * ShaderCount);

	ShaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	ShaderStages[0].module = pEffect->VkShaderVertex;
	ShaderStages[0].pName = "main";

	ShaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	ShaderStages[1].module = pEffect->VkShaderFragment;
	ShaderStages[1].pName = "main";


	uint64_t InputBindingDescsSize = maxattribs;
	VkVertexInputBindingDescription* InputBindingDescs = (VkVertexInputBindingDescription*)calloc(InputBindingDescsSize, sizeof(VkVertexInputBindingDescription));
	uint64_t InputAttribDescsSize = maxattribs;
	VkVertexInputAttributeDescription* InputAttribDescs = (VkVertexInputAttributeDescription*)calloc(InputAttribDescsSize, sizeof(VkVertexInputAttributeDescription));

	for (size_t i = 0, PassthroughAttribsPointer = 0; i < maxattribs; i++)
	{
		if (Get_AttributeTypeCompatibility(pEffect->UsedAttributes[i]) != true)
		{
			Engine_Ref_FunctionError("ReCreate_Generic3D()", "Attribute type not compatible with accessor type == ", pEffect->UsedAttributes[i].Accessor.Type);
			return;
		}

		InputBindingDescs[i].binding = i;
		switch (pEffect->UsedAttributes[i].Accessor.Inputrate)
		{
		case AttributeInputRate_Vertex:
			InputBindingDescs[i].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
			break;
		case AttributeInputRate_Instance:
			InputBindingDescs[i].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
			break;
		}

		if (pEffect->UsedAttributes[i].Accessor.ByteStride != NULL)
			InputBindingDescs[i].stride = pEffect->UsedAttributes[i].Accessor.ByteStride;
		else
			InputBindingDescs[i].stride = ((GraphicsFormatBitsPerChannels[(uint32_t)pEffect->UsedAttributes[i].Accessor.Format][0] / 8) * (uint32_t)pEffect->UsedAttributes[i].Accessor.Type);

		InputAttribDescs[i].binding = i;
		InputAttribDescs[i].format = (VkFormat)pEffect->UsedAttributes[i].Accessor.Format;

		InputAttribDescs[i].location = i;
		InputAttribDescs[i].offset = 0; //mayby use accessor offset????
	}

	VkPipelineVertexInputStateCreateInfo VertexInputInfo;
	memset(&VertexInputInfo, NULL, sizeof(VertexInputInfo));
	VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	VertexInputInfo.vertexBindingDescriptionCount = (uint32_t)InputBindingDescsSize;
	VertexInputInfo.pVertexBindingDescriptions = InputBindingDescs; // Optional
	VertexInputInfo.vertexAttributeDescriptionCount = (uint32_t)InputAttribDescsSize;
	VertexInputInfo.pVertexAttributeDescriptions = InputAttribDescs; // Optional


	VkPipelineColorBlendAttachmentState ColourBlendAttachment;
	memset(&ColourBlendAttachment, NULL, sizeof(ColourBlendAttachment));
	ColourBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	ColourBlendAttachment.blendEnable = VK_TRUE;
	ColourBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	ColourBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	ColourBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	ColourBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	ColourBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	ColourBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendAttachmentState ColourBlendAttachmentDeffered;
	memset(&ColourBlendAttachmentDeffered, NULL, sizeof(ColourBlendAttachmentDeffered));
	ColourBlendAttachmentDeffered.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	VkPipelineColorBlendAttachmentState attachments[4] = { ColourBlendAttachment, ColourBlendAttachment, ColourBlendAttachment, ColourBlendAttachment };
	VkPipelineColorBlendStateCreateInfo ColourBlending;
	memset(&ColourBlending, NULL, sizeof(ColourBlending));
	ColourBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColourBlending.pAttachments = attachments;

	VkPipelineDepthStencilStateCreateInfo DepthStencil;
	memset(&DepthStencil, NULL, sizeof(DepthStencil));
	DepthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	DepthStencil.depthTestEnable = VK_TRUE;
	DepthStencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
	DepthStencil.depthBoundsTestEnable = VK_FALSE;
	DepthStencil.minDepthBounds = 0.0f;
	DepthStencil.maxDepthBounds = 1.0f;
	DepthStencil.stencilTestEnable = VK_FALSE;


	uint32_t statesSize = 2;
	VkDynamicState states[2] = { VK_DYNAMIC_STATE_VIEWPORT , VK_DYNAMIC_STATE_SCISSOR };
	VkPipelineDynamicStateCreateInfo DynamicStates;
	memset(&DynamicStates, NULL, sizeof(DynamicStates));
	DynamicStates.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	DynamicStates.dynamicStateCount = statesSize;
	DynamicStates.pDynamicStates = states;


	VkPipelineInputAssemblyStateCreateInfo InputAssemblyState;
	memset(&InputAssemblyState, NULL, sizeof(InputAssemblyState));
	InputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	InputAssemblyState.primitiveRestartEnable = VK_FALSE;

	VkViewport Viewport;
	Viewport.x = 0.0f;
	Viewport.y = 0.0f;
	Viewport.width = (float)pGraphicsWindow->CurrentExtentWidth;
	Viewport.height = (float)pGraphicsWindow->CurrentExtentHeight;
	Viewport.minDepth = 0.0f;
	Viewport.maxDepth = 1.0f;

	VkRect2D Scissor;
	Scissor.offset.x = 0;
	Scissor.offset.y = 0;
	Scissor.extent.width = pGraphicsWindow->CurrentExtentWidth;
	Scissor.extent.height = pGraphicsWindow->CurrentExtentHeight;

	VkPipelineViewportStateCreateInfo ViewportState;
	memset(&ViewportState, NULL, sizeof(ViewportState));
	ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportState.viewportCount = 1; //multi screeen~?!?!??!!?
	ViewportState.pViewports = &Viewport;
	ViewportState.scissorCount = 1;
	ViewportState.pScissors = &Scissor;

	VkPipelineMultisampleStateCreateInfo MultisampleState;
	memset(&MultisampleState, NULL, sizeof(MultisampleState));
	MultisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	MultisampleState.sampleShadingEnable = VK_FALSE;
	MultisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	MultisampleState.minSampleShading = 1.0f; // Optional
	MultisampleState.pSampleMask = NULL; // Optional
	MultisampleState.alphaToCoverageEnable = VK_FALSE; // Optional
	MultisampleState.alphaToOneEnable = VK_FALSE; // Optional

	VkPipelineRasterizationStateCreateInfo RasterizationState;
	memset(&RasterizationState, NULL, sizeof(RasterizationState));
	RasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	RasterizationState.depthClampEnable = VK_FALSE;
	RasterizationState.rasterizerDiscardEnable = VK_FALSE;
	RasterizationState.polygonMode = VK_POLYGON_MODE_FILL;
	RasterizationState.lineWidth = 1.0f;
	RasterizationState.frontFace = VK_FRONT_FACE_CLOCKWISE;
	RasterizationState.depthBiasEnable = VK_FALSE;
	RasterizationState.depthBiasConstantFactor = 0.0f; // Optional
	RasterizationState.depthBiasClamp = 0.0f; // Optional
	RasterizationState.depthBiasSlopeFactor = 0.0f; // Optional
	switch (pMaterial->DoubleSided)
	{
	case false:
		RasterizationState.cullMode = VK_CULL_MODE_BACK_BIT;
		break;
	case true:
		RasterizationState.cullMode = VK_CULL_MODE_NONE;
		break;
	}

	{
		VkGraphicsPipelineCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		switch (pMaterial->AlphaMode)
		{
		case AlphaMode_Opaque:
			Info.subpass = 0;
			DepthStencil.depthWriteEnable = VK_TRUE;
			ColourBlending.attachmentCount = 4;
			break;
		case AlphaMode_Mask:
			Info.subpass = 0;
			DepthStencil.depthWriteEnable = VK_TRUE;
			ColourBlending.attachmentCount = 4;
			break;
		case AlphaMode_Blend:
			Info.subpass = 1;
			DepthStencil.depthWriteEnable = VK_FALSE;
			ColourBlending.attachmentCount = 2;
			break;
		}
		Info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		Info.stageCount = ShaderCount;
		Info.pStages = ShaderStages;
		Info.pVertexInputState = &VertexInputInfo;
		Info.pInputAssemblyState = &InputAssemblyState;
		Info.pViewportState = &ViewportState;
		Info.pRasterizationState = &RasterizationState;
		Info.pMultisampleState = &MultisampleState;
		Info.pDepthStencilState = &DepthStencil; // Optional
		Info.pColorBlendState = &ColourBlending;
		Info.pDynamicState = &DynamicStates; // Optional
		Info.layout = Utils.GenericResources[Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].PipelineLayout3D;
		Info.renderPass = pGraphicsWindow->VkRenderPassDeferred;
		Info.basePipelineHandle = VK_NULL_HANDLE; // Optional
		Info.basePipelineIndex = -1; // Optional

		if ((res = vkCreateGraphicsPipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipeline)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_Generic3D()", "vkCreateGraphicsPipelines Failed. VkResult == ", res);
			return;
		}

	}
	free(InputAttribDescs);
	free(InputBindingDescs);
}

void ReCreate_Generic2D(ElementGraphics* pElement, GraphicsEffectGeneric2D* pEffect, uint32_t ThreadIndex)
{
	VkResult res = VK_SUCCESS;
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);
	RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
	
	uint64_t FragmentShader2DCompiledPointer = 0;
	SPIRV FragmentShader2DCompiled[FragmentShader2D_MaxSize];
	memset(FragmentShader2DCompiled, 0, FragmentShader2D_MaxSize * sizeof(*FragmentShader2DCompiled));

	const SPIRV Fragment_Main0[] = FragmentShader2D_Main();
	memcpy((void*)((uint64_t)FragmentShader2DCompiled + (uint64_t)FragmentShader2DCompiledPointer), Fragment_Main0, FragmentShader2D_MainSize); //copy first part
	FragmentShader2DCompiledPointer += FragmentShader2D_MainSize;
	{
		const SPIRV Fragment_TextureSampling_Default[] = FragmentShader2D_TextureSampling_Default();

		if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->BaseColourTexture.iTexture) == (TEXRESULT)Success)
		{
			memcpy((void*)((uint64_t)FragmentShader2DCompiled + (uint64_t)FragmentShader2DCompiledPointer), Fragment_TextureSampling_Default, FragmentShader2D_TextureSampling_DefaultSize);
			FragmentShader2DCompiledPointer += FragmentShader2D_TextureSampling_DefaultSize;
		}

		const SPIRV Fragment_TextureMode_Colour[] = FragmentShader2D_TextureMode_Colour();
		const SPIRV Fragment_TextureMode_Alpha[] = FragmentShader2D_TextureMode_Alpha();
		const SPIRV Fragment_TextureMode_Solid[] = FragmentShader2D_TextureMode_Solid();

		switch (pMaterial->BaseColourMode)
		{
		case MaterialMode_Colour:
			memcpy((void*)((uint64_t)FragmentShader2DCompiled + (uint64_t)FragmentShader2DCompiledPointer), Fragment_TextureMode_Colour, FragmentShader2D_TextureMode_ColourSize);
			FragmentShader2DCompiledPointer += FragmentShader2D_TextureMode_ColourSize;
			break;
		case MaterialMode_Alpha:
			memcpy((void*)((uint64_t)FragmentShader2DCompiled + (uint64_t)FragmentShader2DCompiledPointer), Fragment_TextureMode_Alpha, FragmentShader2D_TextureMode_AlphaSize);
			FragmentShader2DCompiledPointer += FragmentShader2D_TextureMode_AlphaSize;
			break;
		case MaterialMode_Solid:
			memcpy((void*)((uint64_t)FragmentShader2DCompiled + (uint64_t)FragmentShader2DCompiledPointer), Fragment_TextureMode_Solid, FragmentShader2D_TextureMode_SolidSize);
			FragmentShader2DCompiledPointer += FragmentShader2D_TextureMode_SolidSize;
			break;
		}

		const SPIRV Fragment_AlphaMode_Opaque[] = FragmentShader2D_AlphaMode_Opaque();
		const SPIRV Fragment_AlphaMode_Mask[] = FragmentShader2D_AlphaMode_Mask();
		const SPIRV Fragment_AlphaMode_Blend[] = FragmentShader2D_AlphaMode_Blend();

		switch (pMaterial->AlphaMode)
		{
		case AlphaMode_Opaque:
			memcpy((void*)((uint64_t)FragmentShader2DCompiled + (uint64_t)FragmentShader2DCompiledPointer), Fragment_AlphaMode_Opaque, FragmentShader2D_AlphaMode_OpaqueSize);
			FragmentShader2DCompiledPointer += FragmentShader2D_AlphaMode_OpaqueSize;
			break;
		case AlphaMode_Mask:
			memcpy((void*)((uint64_t)FragmentShader2DCompiled + (uint64_t)FragmentShader2DCompiledPointer), Fragment_AlphaMode_Mask, FragmentShader2D_AlphaMode_MaskSize);
			FragmentShader2DCompiledPointer += FragmentShader2D_AlphaMode_MaskSize;
			break;
		case AlphaMode_Blend:
			memcpy((void*)((uint64_t)FragmentShader2DCompiled + (uint64_t)FragmentShader2DCompiledPointer), Fragment_AlphaMode_Blend , FragmentShader2D_AlphaMode_BlendSize);
			FragmentShader2DCompiledPointer += FragmentShader2D_AlphaMode_BlendSize;
			break;
		}
	}
	const SPIRV Vertex[] = VertexShader2D();

	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderVertex, Vertex, VertexShader2DSize, "ReCreate_Generic2D()");
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderFragment, FragmentShader2DCompiled, FragmentShader2DCompiledPointer, "ReCreate_Generic2D()");
	
	uint32_t ShaderCount = 2;
	VkPipelineShaderStageCreateInfo ShaderStages[2];
	memset(ShaderStages, NULL, sizeof(*ShaderStages) * ShaderCount);
	ShaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	ShaderStages[0].module = pEffect->VkShaderVertex;
	ShaderStages[0].pName = "main";

	ShaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	ShaderStages[1].module = pEffect->VkShaderFragment;
	ShaderStages[1].pName = "main";

	uint64_t InputBindingDescsSize = 1;
	VkVertexInputBindingDescription InputBindingDescs[1];
	uint64_t InputAttribDescsSize = 6;
	VkVertexInputAttributeDescription InputAttribDescs[6];

	//Buffer Binding Main
	InputBindingDescs[0].binding = 0;
	InputBindingDescs[0].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
	InputBindingDescs[0].stride = sizeof(GPU_GraphicsEffectGeneric2D);
	//Attributes
	//size
	InputAttribDescs[0].binding = 0;
	InputAttribDescs[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	InputAttribDescs[0].location = 0;
	InputAttribDescs[0].offset = offsetof(GPU_GraphicsEffectGeneric2D, Size);
	//position
	InputAttribDescs[1].binding = 0;
	InputAttribDescs[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	InputAttribDescs[1].location = 1;
	InputAttribDescs[1].offset = offsetof(GPU_GraphicsEffectGeneric2D, Position);

	//bboxsize
	InputAttribDescs[2].binding = 0;
	InputAttribDescs[2].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	InputAttribDescs[2].location = 2;
	InputAttribDescs[2].offset = offsetof(GPU_GraphicsEffectGeneric2D, BoundingBoxSize);
	//bboxposition
	InputAttribDescs[3].binding = 0;
	InputAttribDescs[3].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	InputAttribDescs[3].location = 3;
	InputAttribDescs[3].offset = offsetof(GPU_GraphicsEffectGeneric2D, BoundingBoxPosition);
	//textureoffset
	InputAttribDescs[4].binding = 0;
	InputAttribDescs[4].format = VK_FORMAT_R32G32B32A32_SINT;
	InputAttribDescs[4].location = 4;
	InputAttribDescs[4].offset = offsetof(GPU_GraphicsEffectGeneric2D, TextureOffset);
	//texturesize
	InputAttribDescs[5].binding = 0;
	InputAttribDescs[5].format = VK_FORMAT_R32G32B32A32_SINT;
	InputAttribDescs[5].location = 5;
	InputAttribDescs[5].offset = offsetof(GPU_GraphicsEffectGeneric2D, TextureSize);

	//pipeline

	VkPipelineVertexInputStateCreateInfo VertexInputInfo;
	memset(&VertexInputInfo, NULL, sizeof(VertexInputInfo));
	VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	VertexInputInfo.vertexBindingDescriptionCount = (uint32_t)InputBindingDescsSize;
	VertexInputInfo.pVertexBindingDescriptions = InputBindingDescs; // Optional

	VertexInputInfo.vertexAttributeDescriptionCount = (uint32_t)InputAttribDescsSize;
	VertexInputInfo.pVertexAttributeDescriptions = InputAttribDescs; // Optional


	VkPipelineInputAssemblyStateCreateInfo InputAssemblyState;
	memset(&InputAssemblyState, NULL, sizeof(InputAssemblyState));
	InputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	InputAssemblyState.primitiveRestartEnable = VK_FALSE;

	VkViewport Viewport;
	Viewport.x = 0.0f;
	Viewport.y = 0.0f;
	Viewport.width = (float)pGraphicsWindow->CurrentExtentWidth;
	Viewport.height = (float)pGraphicsWindow->CurrentExtentHeight;
	Viewport.minDepth = 0.0f;
	Viewport.maxDepth = 1.0f;

	VkRect2D Scissor;
	Scissor.offset.x = 0;
	Scissor.offset.y = 0;
	Scissor.extent.width = pGraphicsWindow->CurrentExtentWidth;
	Scissor.extent.height = pGraphicsWindow->CurrentExtentHeight;

	VkPipelineViewportStateCreateInfo ViewportState;
	memset(&ViewportState, NULL, sizeof(ViewportState));
	ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportState.viewportCount = 1; //multi screeen~?!?!??!!?
	ViewportState.pViewports = &Viewport;
	ViewportState.scissorCount = 1;
	ViewportState.pScissors = &Scissor;

	VkPipelineRasterizationStateCreateInfo RasterizationState;
	memset(&RasterizationState, NULL, sizeof(RasterizationState));
	RasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	RasterizationState.depthClampEnable = VK_FALSE;
	RasterizationState.rasterizerDiscardEnable = VK_FALSE;
	RasterizationState.polygonMode = VK_POLYGON_MODE_FILL;
	RasterizationState.lineWidth = 1.0f;
	RasterizationState.cullMode = VK_CULL_MODE_NONE; //CULL MODE
	RasterizationState.frontFace = VK_FRONT_FACE_CLOCKWISE;
	RasterizationState.depthBiasEnable = VK_FALSE;
	RasterizationState.depthBiasConstantFactor = 0.0f; // Optional
	RasterizationState.depthBiasClamp = 0.0f; // Optional
	RasterizationState.depthBiasSlopeFactor = 0.0f; // Optional

	VkPipelineMultisampleStateCreateInfo MultisampleState;
	memset(&MultisampleState, NULL, sizeof(MultisampleState));
	MultisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	MultisampleState.sampleShadingEnable = VK_FALSE;
	MultisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	MultisampleState.minSampleShading = 1.0f; // Optional
	MultisampleState.pSampleMask = NULL; // Optional
	MultisampleState.alphaToCoverageEnable = VK_FALSE; // Optional
	MultisampleState.alphaToOneEnable = VK_FALSE; // Optional

	VkPipelineColorBlendAttachmentState ColourBlendAttachment;
	memset(&ColourBlendAttachment, NULL, sizeof(ColourBlendAttachment));
	ColourBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	ColourBlendAttachment.blendEnable = VK_TRUE;
	ColourBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	ColourBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	ColourBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	ColourBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	ColourBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_DST_ALPHA;
	ColourBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendAttachmentState ColourBlendAttachmentDeffered;
	memset(&ColourBlendAttachmentDeffered, NULL, sizeof(ColourBlendAttachmentDeffered));
	ColourBlendAttachmentDeffered.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	VkPipelineColorBlendAttachmentState attachments[4] = { ColourBlendAttachment, ColourBlendAttachment, ColourBlendAttachment, ColourBlendAttachment };
	VkPipelineColorBlendStateCreateInfo ColourBlending;
	memset(&ColourBlending, NULL, sizeof(ColourBlending));
	ColourBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColourBlending.attachmentCount = 2;
	ColourBlending.pAttachments = attachments;

	VkPipelineDepthStencilStateCreateInfo DepthStencil;
	memset(&DepthStencil, NULL, sizeof(DepthStencil));
	DepthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	DepthStencil.depthTestEnable = VK_TRUE;
	DepthStencil.depthWriteEnable = VK_TRUE;
	DepthStencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
	DepthStencil.depthBoundsTestEnable = VK_FALSE;
	DepthStencil.minDepthBounds = 0.0f;
	DepthStencil.maxDepthBounds = 1.0f;
	DepthStencil.stencilTestEnable = VK_FALSE;


	uint32_t statesSize = 2;
	VkDynamicState states[2] = { VK_DYNAMIC_STATE_VIEWPORT , VK_DYNAMIC_STATE_SCISSOR };
	VkPipelineDynamicStateCreateInfo DynamicStates;
	memset(&DynamicStates, NULL, sizeof(DynamicStates));
	DynamicStates.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	DynamicStates.dynamicStateCount = statesSize;
	DynamicStates.pDynamicStates = states;


	{
		VkGraphicsPipelineCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		switch (pMaterial->AlphaMode)
		{
		case AlphaMode_Opaque:
			Info.subpass = 0;
			ColourBlending.attachmentCount = 4;
			break;
		case AlphaMode_Mask:
			Info.subpass = 0;
			ColourBlending.attachmentCount = 4;
			break;
		case AlphaMode_Blend:
			Info.subpass = 1;
			ColourBlending.attachmentCount = 2;
			break;
		}
		Info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		Info.stageCount = ShaderCount;
		Info.pStages = ShaderStages;
		Info.pVertexInputState = &VertexInputInfo;
		Info.pInputAssemblyState = &InputAssemblyState;
		Info.pViewportState = &ViewportState;
		Info.pRasterizationState = &RasterizationState;
		Info.pMultisampleState = &MultisampleState;
		Info.pDepthStencilState = &DepthStencil; // Optional
		Info.pColorBlendState = &ColourBlending;
		Info.pDynamicState = &DynamicStates; // Optional
		Info.layout = Utils.GenericResources[Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].PipelineLayout2D;
		Info.renderPass = pGraphicsWindow->VkRenderPassDeferred;
		//Info.subpass = 1;
		Info.basePipelineHandle = VK_NULL_HANDLE; // Optional
		Info.basePipelineIndex = -1; // Optional

		if ((res = vkCreateGraphicsPipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipeline)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_Generic2D()", "vkCreateGraphicsPipelines Failed. VkResult == ", res);
			return;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Packers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Pack_Generic3D(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const GraphicsEffectGeneric3D* pEffect, GraphicsEffectGeneric3D* pCopiedEffect, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedEffect->VkPipeline, NULL, sizeof(pCopiedEffect->VkPipeline));
		memset(&pCopiedEffect->UsedAttributes, NULL, sizeof(pCopiedEffect->UsedAttributes));
		memset(&pCopiedEffect->VkShaderVertex, NULL, sizeof(pCopiedEffect->VkShaderVertex));
		memset(&pCopiedEffect->VkShaderFragment, NULL, sizeof(pCopiedEffect->VkShaderFragment));
	}
	else
	{

	}
}

void Pack_Generic2D(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const GraphicsEffectGeneric2D* pEffect, GraphicsEffectGeneric2D* pCopiedEffect, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedEffect->VkPipeline, NULL, sizeof(pCopiedEffect->VkPipeline));
		memset(&pCopiedEffect->VkShaderVertex, NULL, sizeof(pCopiedEffect->VkShaderVertex));
		memset(&pCopiedEffect->VkShaderFragment, NULL, sizeof(pCopiedEffect->VkShaderFragment));
	}
	else
	{

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect UnPackers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UnPack_Generic3D(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const GraphicsEffectGeneric3D* pEffect, GraphicsEffectGeneric3D* pCopiedEffect, const void* pData, uint32_t ThreadIndex)
{
	ReCreate_Generic3D(pCopiedElement, pCopiedEffect, ThreadIndex);
}

void UnPack_Generic2D(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const GraphicsEffectGeneric2D* pEffect, GraphicsEffectGeneric2D* pCopiedEffect, const void* pData, uint32_t ThreadIndex)
{
	ReCreate_Generic2D(pCopiedElement, pCopiedEffect, ThreadIndex);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_Generic3D(ElementGraphics* pElement, GraphicsEffectGeneric3D* pEffect, GraphicsEffectCreateInfoGeneric3D* pEffectCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pEffect == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pEffectCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_Generic3D()", "pEffectCreateInfo == NULLPTR");
			return (TEXRESULT)Invalid_Parameter;
		}
#endif
		pEffect->Indices = pEffectCreateInfo->Indices;

		pEffect->AttributesSize = pEffectCreateInfo->AttributesSize;
		memcpy(pEffect->Attributes, pEffectCreateInfo->Attributes, sizeof(*pEffect->Attributes) * pEffect->AttributesSize);

		ReCreate_Generic3D(pElement, pEffect, ThreadIndex);

	}
	*pAllocationSize = sizeof(GraphicsEffectGeneric3D) + (pEffectCreateInfo->AttributesSize * sizeof(*pEffectCreateInfo->Attributes));
	return (TEXRESULT)Success;
}

TEXRESULT Create_Generic2D(ElementGraphics* pElement, GraphicsEffectGeneric2D* pEffect, GraphicsEffectCreateInfoGeneric2D* pEffectCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pEffect == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pEffectCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_Generic2D()", "pEffectCreateInfo == NULLPTR");
			return (TEXRESULT)Invalid_Parameter;
		}
#endif
		glm_vec2_copy(pEffectCreateInfo->Size, pEffect->Size);
		glm_vec3_copy(pEffectCreateInfo->Position, pEffect->Position);

		glm_vec2_copy(pEffectCreateInfo->BoundingBoxSize, pEffect->BoundingBoxSize);
		glm_vec2_copy(pEffectCreateInfo->BoundingBoxPosition, pEffect->BoundingBoxPosition);

		pEffect->TextureOffset[0] = pEffectCreateInfo->TextureOffset[0];
		pEffect->TextureOffset[1] = pEffectCreateInfo->TextureOffset[1];

		pEffect->TextureSize[0] = pEffectCreateInfo->TextureSize[0];
		pEffect->TextureSize[1] = pEffectCreateInfo->TextureSize[1];

		ReCreate_Generic2D(pElement, pEffect, ThreadIndex);
	}
	*pAllocationSize = sizeof(GraphicsEffectGeneric2D);
	return (TEXRESULT)Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Validators
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Check_Extension_Validately(const char* extension, VkExtensionProperties* ExtensionsAvailable, size_t ExtensionsAvailableSize)
{
	for (size_t i1 = 0; i1 < ExtensionsAvailableSize; i1++)
	{
		if (strcmp(extension, ExtensionsAvailable[i1].extensionName) == 0)
		{
			return true;
		}
	}
	return false;
}

bool Check_Layer_Validately(const char* layer, VkLayerProperties* ValidationLayersAvailable, size_t ValidationLayersAvailableSize)
{
	for (size_t i1 = 0; i1 < ValidationLayersAvailableSize; i1++)
	{
		if (strcmp(layer, ValidationLayersAvailable[i1].layerName) == 0)
		{
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Update Loop Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//these three functions must match exactly apart from function it triggers
void Size_ElementGraphics(ElementGraphics* pElement, RHeaderMaterial* pMaterialHeader, RHeaderGraphicsWindow* pGraphicsWindow, RHeaderRender* pRender, uint32_t FrameIndex,
	GPU_Allocation** ppAllocations, uint64_t** ppPointers){
	for (size_t i0 = 0; i0 < pElement->Header.iParentsSize; i0++)
	{
		ResourceHeader* pParentHeader = Object_Ref_Get_ResourceHeaderPointer(pElement->Header.iParents[i0]);
		for (size_t i1 = 0; i1 < pParentHeader->Header.iParentsSize; i1++)
		{
			Object* pObject = Object_Ref_Get_ObjectPointer(pParentHeader->Header.iParents[i1]);
			RHeaderScene* pSceneHeader = (RHeaderScene*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Scene);
			for (size_t i2 = 0; i2 < pRender->iScenesSize; i2++)
			{
				if (pSceneHeader->Active == true && Object_Ref_Compare_ResourceHeaderAllocation(pRender->iScenes[i2], pSceneHeader->Header.Allocation) == Success)
				{
					uint64_t pointer = 0;
					for (size_t i3 = 0; i3 < pElement->EffectsSize; i3++)
					{
						GraphicsEffect* pEffect = (GraphicsEffect*)((void*)((uint64_t)pElement->Effects + pointer));
						GraphicsEffectSignature* pSignature = NULL;
						GraphicsEffectBufferIndex BufferIndex = NULL;
						Find_GraphicsEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
						if (pSignature->Update != NULL)
						{
							pSignature->Update(pElement, pParentHeader, pObject, pEffect, pGraphicsWindow, FrameIndex, pMaterialHeader,
								NULL, ppPointers[BufferIndex]);
						}
						pointer += pEffect->Header.AllocationSize;
					}
				}
			}
		}
	}
}

void Fill_ElementGraphics(ElementGraphics* pElement, RHeaderMaterial* pMaterialHeader, RHeaderGraphicsWindow* pGraphicsWindow, RHeaderRender* pRender, uint32_t FrameIndex,
	GPU_Allocation** ppAllocations, uint64_t** ppPointers){
	for (size_t i0 = 0; i0 < pElement->Header.iParentsSize; i0++)
	{
		ResourceHeader* pParentHeader = Object_Ref_Get_ResourceHeaderPointer(pElement->Header.iParents[i0]);
		for (size_t i1 = 0; i1 < pParentHeader->Header.iParentsSize; i1++)
		{
			Object* pObject = Object_Ref_Get_ObjectPointer(pParentHeader->Header.iParents[i1]);
			RHeaderScene* pSceneHeader = (RHeaderScene*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Scene);
			for (size_t i2 = 0; i2 < pRender->iScenesSize; i2++)
			{
				if (pSceneHeader->Active == true && Object_Ref_Compare_ResourceHeaderAllocation(pRender->iScenes[i2], pSceneHeader->Header.Allocation) == Success)
				{
					uint64_t pointer = 0;
					for (size_t i3 = 0; i3 < pElement->EffectsSize; i3++)
					{
						GraphicsEffect* pEffect = (GraphicsEffect*)((void*)((uint64_t)pElement->Effects + pointer));
						GraphicsEffectSignature* pSignature = NULL;
						GraphicsEffectBufferIndex BufferIndex = NULL;
						Find_GraphicsEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
						if (pSignature->Update != NULL)
						{
							pSignature->Update(pElement, pParentHeader, pObject, pEffect, pGraphicsWindow, FrameIndex, pMaterialHeader,
								ppAllocations[BufferIndex], ppPointers[BufferIndex]);
						}
						pointer += pEffect->Header.AllocationSize;
					}
				}
			}
		}
	}
}

void Draw_ElementGraphics(ElementGraphics* pElement, RHeaderMaterial* pMaterialHeader, RHeaderGraphicsWindow* pGraphicsWindow, RHeaderRender* pRender, uint32_t FrameIndex,
	GPU_Allocation** ppAllocations, uint64_t** ppPointers, RHeaderCamera* pCamera, mat4 CameraVP){
	for (size_t i0 = 0; i0 < pElement->Header.iParentsSize; i0++)
	{
		ResourceHeader* pParentHeader = Object_Ref_Get_ResourceHeaderPointer(pElement->Header.iParents[i0]);
		for (size_t i1 = 0; i1 < pParentHeader->Header.iParentsSize; i1++)
		{
			Object* pObject = Object_Ref_Get_ObjectPointer(pParentHeader->Header.iParents[i1]);
			RHeaderScene* pSceneHeader = (RHeaderScene*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Scene);
			for (size_t i2 = 0; i2 < pRender->iScenesSize; i2++)
			{
				if (pSceneHeader->Active == true && Object_Ref_Compare_ResourceHeaderAllocation(pRender->iScenes[i2], pSceneHeader->Header.Allocation) == Success)
				{
					uint64_t pointer = 0;
					for (size_t i3 = 0; i3 < pElement->EffectsSize; i3++)
					{
						GraphicsEffect* pEffect = (GraphicsEffect*)((void*)((uint64_t)pElement->Effects + pointer));
						GraphicsEffectSignature* pSignature = NULL;
						GraphicsEffectBufferIndex BufferIndex = NULL;
						Find_GraphicsEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
						if (pSignature->Draw != NULL)
						{
							pSignature->Draw(pElement, pParentHeader, pObject, pEffect, pGraphicsWindow, FrameIndex, pMaterialHeader,
								ppAllocations[BufferIndex], ppPointers[BufferIndex], pCamera, CameraVP);
						}
						pointer += pEffect->Header.AllocationSize;
					}
				}
			}
		}
	}
}

void Render_GraphicsWindow(SwapChainFrameBuffer* pFrameBuffer)
{
	RHeaderGraphicsWindow* pGraphicsWindow = pFrameBuffer->pGraphicsWindow;
	//uint32_t FrameIndex = pFrameBuffer->FrameIndex;
	//uint32_t QueueIndex = pFrameBuffer->QueueIndex;
	//uint32_t SwapChainIndex = pFrameBuffer->SwapChainIndex;

	while (pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].RenderingFlag == true)
	{
		VkResult res = VK_SUCCESS;
		GPU_Allocation** ppTotalAllocations = calloc(Utils.GraphicsEffectSignaturesSize, sizeof(*ppTotalAllocations));
		uint64_t** ppPointers = calloc(Utils.GraphicsEffectSignaturesSize, sizeof(*ppPointers));
		for (size_t i = 0; i < Utils.GraphicsEffectSignaturesSize; i++)
		{
			GraphicsEffectSignature* pSignature = Utils.GraphicsEffectSignatures[i];
			ppTotalAllocations[i] = (GPU_Allocation*)calloc(pSignature->SignatureGPUBuffersSize, sizeof(**ppTotalAllocations));
			ppPointers[i] = (uint64_t*)calloc(pSignature->SignatureGPUBuffersSize, sizeof(**ppPointers));
		}

		//////////////////////////////////////////////////////////////////////////
		//Size Pass
		//////////////////////////////////////////////////////////////////////////

		for (size_t i1 = 0; i1 < Utils.RHeaderRenderBuffer.Size;)
		{
			RHeaderRender* pRenderHeader = ((RHeaderRender*)&Utils.RHeaderRenderBuffer.Buffer[i1]);
			if (pRenderHeader->Header.AllocationSize != NULL && pRenderHeader->Header.Allocation.Identifier == (uint32_t)GraphicsHeader_Render)
			{
				if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pRenderHeader->iGraphicsWindow) == (TEXRESULT)Success)
				{
					for (size_t i2 = 0; i2 < pRenderHeader->Header.iParentsSize; i2++)
					{
						Object* pObject = Object_Ref_Get_ObjectPointer(pRenderHeader->Header.iParents[i2]);
						for (size_t i2 = 0; i2 < Utils.ElementGraphicsBuffer.Size;)
						{
							ElementGraphics* pElement = (Element*)&Utils.ElementGraphicsBuffer.Buffer[i2];
							if (pElement->Header.AllocationSize != NULL && pElement->Header.Allocation.Identifier == (uint32_t)GraphicsElement_ElementGraphics)
							{
								RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
								ElementGraphics* pElementInstance = NULL;
								RHeaderMaterial* pMaterialInstace = NULL;
								Object_Ref_StartThread_Element(pElement->Header.Allocation, pFrameBuffer->ThreadIndex, &pElementInstance);
								Object_Ref_StartThread_ResourceHeader(pMaterial->Header.Allocation, pFrameBuffer->ThreadIndex, &pMaterialInstace);

								if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pElement->iGraphicsWindow) == (TEXRESULT)Success)
									if (pMaterialInstace->AlphaMode == AlphaMode_Opaque || pMaterialInstace->AlphaMode == AlphaMode_Mask)
										Size_ElementGraphics(pElementInstance, pMaterialInstace, pGraphicsWindow, pRenderHeader, pFrameBuffer->FrameIndex, ppTotalAllocations, ppPointers);
								i2 += pElement->Header.AllocationSize;
							}
							else
							{
								i2++;
							}
						}
						//TRANSPERANCY PASS			
						for (size_t i2 = 0; i2 < Utils.ElementGraphicsBuffer.Size;)
						{
							ElementGraphics* pElement = (Element*)&Utils.ElementGraphicsBuffer.Buffer[i2];
							if (pElement->Header.AllocationSize != NULL && pElement->Header.Allocation.Identifier == (uint32_t)GraphicsElement_ElementGraphics)
							{
								RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
								ElementGraphics* pElementInstance = NULL;
								RHeaderMaterial* pMaterialInstace = NULL;
								Object_Ref_StartThread_Element(pElement->Header.Allocation, pFrameBuffer->ThreadIndex, &pElementInstance);
								Object_Ref_StartThread_ResourceHeader(pMaterial->Header.Allocation, pFrameBuffer->ThreadIndex, &pMaterialInstace);

								if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pElement->iGraphicsWindow) == (TEXRESULT)Success)
									if (pMaterialInstace->AlphaMode == AlphaMode_Blend)
										Size_ElementGraphics(pElementInstance, pMaterialInstace, pGraphicsWindow, pRenderHeader, pFrameBuffer->FrameIndex, ppTotalAllocations, ppPointers);
								i2 += pElement->Header.AllocationSize;
							}
							else
							{
								i2++;
							}
						}
					}
				}
				i1 += pRenderHeader->Header.AllocationSize;
			}
			else
			{
				i1++;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//Buffer Allocation
		//////////////////////////////////////////////////////////////////////////

		for (size_t i = 0; i < Utils.GraphicsEffectSignaturesSize; i++)
		{
			GraphicsEffectSignature* pSignature = Utils.GraphicsEffectSignatures[i];
			for (size_t i1 = 0; i1 < pSignature->SignatureGPUBuffersSize; i1++)
			{
				VkMemoryRequirements requirements;
				requirements.size = ppPointers[i][i1];
				requirements.alignment = pGraphicsWindow->pLogicalDevice->SrcBuffer.Alignment;
				requirements.memoryTypeBits = NULL;
				if (requirements.size != NULL)
				{
					ppTotalAllocations[i][i1] = GPUmalloc(pGraphicsWindow->pLogicalDevice, requirements, TargetMemory_Src, AllocationType_Linear, pFrameBuffer->ThreadIndex);
					ppPointers[i][i1] = (uint64_t)ppTotalAllocations[i][i1].Allocater.pArenaAllocater->MappedMemory + ppTotalAllocations[i][i1].Pointer;
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//Additional Update Functions
		//////////////////////////////////////////////////////////////////////////

		for (size_t i = 0; i < Utils.GraphicsEffectSignaturesSize; i++)
		{
			if (Utils.GraphicsEffectSignatures[i]->UpdateSignature != NULL)
				Utils.GraphicsEffectSignatures[i]->UpdateSignature(Utils.GraphicsEffectSignatures[i], pGraphicsWindow, pFrameBuffer->FrameIndex, ppTotalAllocations[i], ppPointers[i]);
		}
		for (size_t i = 0; i < Utils.GraphicsEffectSignaturesSize; i++)
		{
			GraphicsEffectSignature* pSignature = Utils.GraphicsEffectSignatures[i];
			for (size_t i1 = 0; i1 < pSignature->SignatureGPUBuffersSize; i1++)
			{
				ppPointers[i][i1] = 0;
				if (ppTotalAllocations[i][i1].SizeBytes != NULL)
				{
					ppPointers[i][i1] = (uint64_t)ppTotalAllocations[i][i1].Allocater.pArenaAllocater->MappedMemory + ppTotalAllocations[i][i1].Pointer;
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//Data Fill Pass
		//////////////////////////////////////////////////////////////////////////

		for (size_t i1 = 0; i1 < Utils.RHeaderRenderBuffer.Size;)
		{
			RHeaderRender* pRenderHeader = ((RHeaderRender*)&Utils.RHeaderRenderBuffer.Buffer[i1]);
			if (pRenderHeader->Header.AllocationSize != NULL && pRenderHeader->Header.Allocation.Identifier == (uint32_t)GraphicsHeader_Render)
			{
				if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pRenderHeader->iGraphicsWindow) == (TEXRESULT)Success)
				{
					for (size_t i2 = 0; i2 < pRenderHeader->Header.iParentsSize; i2++)
					{
						Object* pObject = Object_Ref_Get_ObjectPointer(pRenderHeader->Header.iParents[i2]);
						for (size_t i2 = 0; i2 < Utils.ElementGraphicsBuffer.Size;)
						{
							ElementGraphics* pElement = (Element*)&Utils.ElementGraphicsBuffer.Buffer[i2];
							if (pElement->Header.AllocationSize != NULL && pElement->Header.Allocation.Identifier == (uint32_t)GraphicsElement_ElementGraphics)
							{
								RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
								ElementGraphics* pElementInstance = NULL;
								RHeaderMaterial* pMaterialInstace = NULL;
								Object_Ref_StartThread_Element(pElement->Header.Allocation, pFrameBuffer->ThreadIndex, &pElementInstance);
								Object_Ref_StartThread_ResourceHeader(pMaterial->Header.Allocation, pFrameBuffer->ThreadIndex, &pMaterialInstace);

								if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pElement->iGraphicsWindow) == (TEXRESULT)Success)
									if (pMaterialInstace->AlphaMode == AlphaMode_Opaque || pMaterialInstace->AlphaMode == AlphaMode_Mask)
										Fill_ElementGraphics(pElementInstance, pMaterialInstace, pGraphicsWindow, pRenderHeader, pFrameBuffer->FrameIndex, ppTotalAllocations, ppPointers);
								i2 += pElement->Header.AllocationSize;
							}
							else
							{
								i2++;
							}
						}
						//TRANSPERANCY PASS
						for (size_t i2 = 0; i2 < Utils.ElementGraphicsBuffer.Size;)
						{
							ElementGraphics* pElement = (Element*)&Utils.ElementGraphicsBuffer.Buffer[i2];
							if (pElement->Header.AllocationSize != NULL && pElement->Header.Allocation.Identifier == (uint32_t)GraphicsElement_ElementGraphics)
							{
								RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
								ElementGraphics* pElementInstance = NULL;
								RHeaderMaterial* pMaterialInstace = NULL;
								Object_Ref_StartThread_Element(pElement->Header.Allocation, pFrameBuffer->ThreadIndex, &pElementInstance);
								Object_Ref_StartThread_ResourceHeader(pMaterial->Header.Allocation, pFrameBuffer->ThreadIndex, &pMaterialInstace);

								if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pElement->iGraphicsWindow) == (TEXRESULT)Success)
									if (pMaterialInstace->AlphaMode == AlphaMode_Blend)
										Fill_ElementGraphics(pElementInstance, pMaterialInstace, pGraphicsWindow, pRenderHeader, pFrameBuffer->FrameIndex, ppTotalAllocations, ppPointers);
								i2 += pElement->Header.AllocationSize;
							}
							else
							{
								i2++;
							}
						}
					}
				}
				i1 += pRenderHeader->Header.AllocationSize;
			}
			else
			{
				i1++;
			}
		}
		for (size_t i = 0; i < Utils.GraphicsEffectSignaturesSize; i++)
		{
			GraphicsEffectSignature* pSignature = Utils.GraphicsEffectSignatures[i];
			for (size_t i1 = 0; i1 < pSignature->SignatureGPUBuffersSize; i1++)
			{
				ppPointers[i][i1] = 0;
			}
		}

		//material
		GPU_Allocation MaterialsAllocation;
		memset(&MaterialsAllocation, NULL, sizeof(MaterialsAllocation));
		{
			uint64_t MaterialsSize = 0;
			for (size_t i = 0; i < Utils.RHeaderMaterialBuffer.Size;)
			{
				RHeaderMaterial* pMaterialHeader = (RHeaderMaterial*)&Utils.RHeaderMaterialBuffer.Buffer[i];
				if (pMaterialHeader->Header.AllocationSize != NULL && pMaterialHeader->Header.Allocation.Identifier == (uint32_t)GraphicsHeader_Material)
				{
					MaterialsSize += AlignNumber(sizeof(GPU_RHeaderMaterial), pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.minUniformBufferOffsetAlignment);
					i += pMaterialHeader->Header.AllocationSize;
				}
				else
				{
					i++;
				}
			}
			VkMemoryRequirements Materialsrequirements;
			Materialsrequirements.size = MaterialsSize;
			Materialsrequirements.alignment = pGraphicsWindow->pLogicalDevice->SrcBuffer.Alignment;
			Materialsrequirements.memoryTypeBits = NULL;
			if (MaterialsSize != NULL)
				MaterialsAllocation = GPUmalloc(pGraphicsWindow->pLogicalDevice, Materialsrequirements, TargetMemory_Src, AllocationType_Linear, pFrameBuffer->ThreadIndex);

			uint64_t MaterialsPointer = 0;
			for (size_t i = 0; i < Utils.RHeaderMaterialBuffer.Size;)
			{
				RHeaderMaterial* pMaterial = (RHeaderMaterial*)&Utils.RHeaderMaterialBuffer.Buffer[i];
				if (pMaterial->Header.AllocationSize != NULL && pMaterial->Header.Allocation.Identifier == (uint32_t)GraphicsHeader_Material)
				{
					RHeaderMaterial* pMaterialInstace = Object_Ref_Get_ResourceHeaderPointer(pMaterial->Header.Allocation);
					Object_Ref_StartThread_ResourceHeader(pMaterial->Header.Allocation, pFrameBuffer->ThreadIndex, &pMaterialInstace);

					if (Object_Ref_Compare_ResourceHeaderAllocation(pMaterialInstace->iGraphicsWindow, pGraphicsWindow->Header.Allocation) == (TEXRESULT)Success)
					{
						GPU_RHeaderMaterial GPU_Material;
						glm_vec4_copy(pMaterialInstace->BaseColourFactor, GPU_Material.BaseColourFactor);
						glm_vec4_copy(pMaterialInstace->EmissiveFactor, GPU_Material.EmissiveFactor);

						GPU_Material.MetallicFactor = pMaterialInstace->MetallicFactor;
						GPU_Material.RoughnessFactor = pMaterialInstace->RoughnessFactor;
						GPU_Material.AlphaCutoff = pMaterialInstace->AlphaCutoff;
						GPU_Material.reservedf0 = 0.0f;

						GPU_Material.OcclusionStrength = pMaterialInstace->OcclusionStrength;
						GPU_Material.NormalScale = pMaterialInstace->NormalScale;
						GPU_Material.reservedf1 = 0.0f;
						GPU_Material.reservedf2 = 0.0f;

						GPU_Material.AlphaMode = pMaterialInstace->AlphaMode;
						GPU_Material.DoubleSided = pMaterialInstace->DoubleSided;
						GPU_Material.reservedi0 = 0;
						GPU_Material.reservedi1 = 0;

						GPU_Material.BaseColourTextureIndex = pMaterialInstace->BaseColourTexture.UVIndex;
						GPU_Material.MetallicRoughnessTextureIndex = pMaterialInstace->MetallicRoughnessTexture.UVIndex;
						GPU_Material.EmissiveTextureIndex = pMaterialInstace->EmissiveTexture.UVIndex;
						GPU_Material.NormalTextureIndex = pMaterialInstace->NormalTexture.UVIndex;
						GPU_Material.OcclusionTextureIndex = pMaterialInstace->OcclusionTexture.UVIndex;

						memcpy((void*)(((uint64_t)MaterialsAllocation.Allocater.pArenaAllocater->MappedMemory + MaterialsAllocation.Pointer + MaterialsPointer)), &GPU_Material, sizeof(GPU_RHeaderMaterial));

						VkDescriptorBufferInfo BufferInfo;
						BufferInfo.buffer = MaterialsAllocation.Allocater.pArenaAllocater->VkBuffer;
						BufferInfo.offset = MaterialsAllocation.Pointer + MaterialsPointer;
						BufferInfo.range = AlignNumber(sizeof(GPU_RHeaderMaterial), pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.minUniformBufferOffsetAlignment);
						Update_Descriptor(pGraphicsWindow->pLogicalDevice, pMaterialInstace->VkMaterialDescriptorSets[pFrameBuffer->FrameIndex], 0, 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, &BufferInfo, NULL);

						if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialInstace->EmissiveTexture.iTexture) == (TEXRESULT)Success)
						{
							RHeaderTexture* pTextureInstance = Object_Ref_Get_ResourceHeaderPointer(pMaterialInstace->EmissiveTexture.iTexture);
							Object_Ref_StartThread_ResourceHeader(pMaterialInstace->EmissiveTexture.iTexture, pFrameBuffer->ThreadIndex, &pTextureInstance);
#ifndef NDEBUG
							if (Object_Ref_Compare_ResourceHeaderAllocation(pMaterialInstace->iGraphicsWindow, pTextureInstance->iGraphicsWindow) != (TEXRESULT)Success)
							{
								Engine_Ref_FunctionError("ReCreate_TextureHeader()", "pTexture->iGraphicsWindow Does Not Match pMaterialHeader->iGraphicsWindow, Material Texture Index == ", 0);
							}
#endif
							VkDescriptorImageInfo ImageInfo;
							ImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
							ImageInfo.imageView = pTextureInstance->GPU_Texture.VkImageView;
							ImageInfo.sampler = pTextureInstance->GPU_Texture.VkSampler;
							Update_Descriptor(pGraphicsWindow->pLogicalDevice, pMaterialInstace->VkMaterialDescriptorSets[pFrameBuffer->FrameIndex], 1, 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, NULL, &ImageInfo);
						}
						if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialInstace->NormalTexture.iTexture) == (TEXRESULT)Success)
						{
							RHeaderTexture* pTextureInstance = Object_Ref_Get_ResourceHeaderPointer(pMaterialInstace->NormalTexture.iTexture);
							Object_Ref_StartThread_ResourceHeader(pMaterialInstace->NormalTexture.iTexture, pFrameBuffer->ThreadIndex, &pTextureInstance);
#ifndef NDEBUG
							if (Object_Ref_Compare_ResourceHeaderAllocation(pMaterialInstace->iGraphicsWindow, pTextureInstance->iGraphicsWindow) != (TEXRESULT)Success)
							{
								Engine_Ref_FunctionError("ReCreate_TextureHeader()", "pTexture->iGraphicsWindow Does Not Match pMaterialHeader->iGraphicsWindow, Material Texture Index == ", 1);
							}
#endif
							VkDescriptorImageInfo ImageInfo;
							ImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
							ImageInfo.imageView = pTextureInstance->GPU_Texture.VkImageView;
							ImageInfo.sampler = pTextureInstance->GPU_Texture.VkSampler;
							Update_Descriptor(pGraphicsWindow->pLogicalDevice, pMaterialInstace->VkMaterialDescriptorSets[pFrameBuffer->FrameIndex], 2, 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, NULL, &ImageInfo);
						}
						if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialInstace->OcclusionTexture.iTexture) == (TEXRESULT)Success)
						{
							RHeaderTexture* pTextureInstance = Object_Ref_Get_ResourceHeaderPointer(pMaterialInstace->OcclusionTexture.iTexture);
							Object_Ref_StartThread_ResourceHeader(pMaterialInstace->OcclusionTexture.iTexture, pFrameBuffer->ThreadIndex, &pTextureInstance);
#ifndef NDEBUG
							if (Object_Ref_Compare_ResourceHeaderAllocation(pMaterialInstace->iGraphicsWindow, pTextureInstance->iGraphicsWindow) != (TEXRESULT)Success)
							{
								Engine_Ref_FunctionError("ReCreate_TextureHeader()", "pTexture->iGraphicsWindow Does Not Match pMaterialHeader->iGraphicsWindow, Material Texture Index == ", 2);
							}
#endif
							VkDescriptorImageInfo ImageInfo;
							ImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
							ImageInfo.imageView = pTextureInstance->GPU_Texture.VkImageView;
							ImageInfo.sampler = pTextureInstance->GPU_Texture.VkSampler;
							Update_Descriptor(pGraphicsWindow->pLogicalDevice, pMaterialInstace->VkMaterialDescriptorSets[pFrameBuffer->FrameIndex], 3, 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, NULL, &ImageInfo);
						}
						if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialInstace->BaseColourTexture.iTexture) == (TEXRESULT)Success)
						{
							RHeaderTexture* pTextureInstance = Object_Ref_Get_ResourceHeaderPointer(pMaterialInstace->BaseColourTexture.iTexture);
							Object_Ref_StartThread_ResourceHeader(pMaterialInstace->BaseColourTexture.iTexture, pFrameBuffer->ThreadIndex, &pTextureInstance);
#ifndef NDEBUG
							if (Object_Ref_Compare_ResourceHeaderAllocation(pMaterialInstace->iGraphicsWindow, pTextureInstance->iGraphicsWindow) != (TEXRESULT)Success)
							{
								Engine_Ref_FunctionError("ReCreate_TextureHeader()", "pTexture->iGraphicsWindow Does Not Match pMaterialHeader->iGraphicsWindow, Material Texture Index == ", 3);
							}
#endif
							VkDescriptorImageInfo ImageInfo;
							ImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
							ImageInfo.imageView = pTextureInstance->GPU_Texture.VkImageView;
							ImageInfo.sampler = pTextureInstance->GPU_Texture.VkSampler;
							Update_Descriptor(pGraphicsWindow->pLogicalDevice, pMaterialInstace->VkMaterialDescriptorSets[pFrameBuffer->FrameIndex], 4, 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, NULL, &ImageInfo);
						}
						if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialInstace->MetallicRoughnessTexture.iTexture) == (TEXRESULT)Success)
						{
							RHeaderTexture* pTextureInstance = Object_Ref_Get_ResourceHeaderPointer(pMaterialInstace->MetallicRoughnessTexture.iTexture);
							Object_Ref_StartThread_ResourceHeader(pMaterialInstace->MetallicRoughnessTexture.iTexture, pFrameBuffer->ThreadIndex, &pTextureInstance);
#ifndef NDEBUG
							if (Object_Ref_Compare_ResourceHeaderAllocation(pMaterialInstace->iGraphicsWindow, pTextureInstance->iGraphicsWindow) != (TEXRESULT)Success)
							{
								Engine_Ref_FunctionError("ReCreate_TextureHeader()", "pTexture->iGraphicsWindow Does Not Match pMaterialHeader->iGraphicsWindow, Material Texture Index == ", 4);
							}
#endif
							VkDescriptorImageInfo ImageInfo;
							ImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
							ImageInfo.imageView = pTextureInstance->GPU_Texture.VkImageView;
							ImageInfo.sampler = pTextureInstance->GPU_Texture.VkSampler;
							Update_Descriptor(pGraphicsWindow->pLogicalDevice, pMaterialInstace->VkMaterialDescriptorSets[pFrameBuffer->FrameIndex], 5, 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, NULL, &ImageInfo);
						}
						MaterialsPointer += AlignNumber(sizeof(GPU_RHeaderMaterial), pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.minUniformBufferOffsetAlignment);
					}
					i += pMaterialInstace->Header.AllocationSize;
				}
				else
				{
					i++;
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////
		//CommandBuffer Creation
		//////////////////////////////////////////////////////////////////////////

		VkCommandBufferBeginInfo BeginInfo;
		BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.flags = NULL;
		BeginInfo.pInheritanceInfo = NULL;
		BeginInfo.pNext = NULL;
		if ((res = vkBeginCommandBuffer(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer, &BeginInfo)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("Display_Graphics()", "vkBeginCommandBuffer Failed, VkResult == ", res);
		}

		VkViewport Viewport;
		Viewport.x = 0.0f;
		Viewport.y = 0.0f;
		Viewport.width = (float)pGraphicsWindow->CurrentExtentWidth;
		Viewport.height = (float)pGraphicsWindow->CurrentExtentHeight;
		Viewport.minDepth = 0.0f;
		Viewport.maxDepth = 1.0f;

		VkRect2D Scissor;
		Scissor.offset.x = 0;
		Scissor.offset.y = 0;
		Scissor.extent.width = pGraphicsWindow->CurrentExtentWidth;
		Scissor.extent.height = pGraphicsWindow->CurrentExtentHeight;

		vkCmdSetViewport(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer, 0, 1, &Viewport);
		vkCmdSetScissor(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer, 0, 1, &Scissor);

		//////////////////////////////////////////////////////////////////////////
		//Additional Draw Functions
		//////////////////////////////////////////////////////////////////////////

		for (size_t i = 0; i < Utils.GraphicsEffectSignaturesSize; i++)
		{
			if (Utils.GraphicsEffectSignatures[i]->DrawSignature != NULL)
				Utils.GraphicsEffectSignatures[i]->DrawSignature(Utils.GraphicsEffectSignatures[i], pGraphicsWindow, pFrameBuffer->FrameIndex, ppTotalAllocations[i], ppPointers[i]);
		}

		Engine_Ref_Lock_Mutex(pGraphicsWindow->SwapChainAccessMutex);
		if ((res = vkAcquireNextImageKHR(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->SwapChain.VkSwapChain,
			UINT64_MAX, pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkImageAvailableSemaphore, NULL, &pFrameBuffer->SwapChainIndex)) == VK_TIMEOUT)
		{
			return;
		}

		for (size_t i1 = 0; i1 < Utils.RHeaderRenderBuffer.Size;)
		{
			RHeaderRender* pRenderHeader = ((RHeaderRender*)&Utils.RHeaderRenderBuffer.Buffer[i1]);
			if (pRenderHeader->Header.AllocationSize != NULL && pRenderHeader->Header.Allocation.Identifier == (uint32_t)GraphicsHeader_Render)
			{
				if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pRenderHeader->iGraphicsWindow) == (TEXRESULT)Success)
				{
					for (size_t i2 = 0; i2 < pRenderHeader->Header.iParentsSize; i2++)
					{
						Object* pObject = Object_Ref_Get_ObjectPointer(pRenderHeader->Header.iParents[i2]);

						VkRenderPassBeginInfo BeginRenderPassInfo;
						memset(&BeginRenderPassInfo, NULL, sizeof(BeginRenderPassInfo));
						BeginRenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
						BeginRenderPassInfo.renderPass = pGraphicsWindow->VkRenderPassDeferred;
						BeginRenderPassInfo.framebuffer = pRenderHeader->pFrameBuffers[pFrameBuffer->SwapChainIndex];
						BeginRenderPassInfo.renderArea.offset.x = 0;
						BeginRenderPassInfo.renderArea.offset.y = 0;
						BeginRenderPassInfo.renderArea.extent.width = pGraphicsWindow->CurrentExtentWidth;
						BeginRenderPassInfo.renderArea.extent.height = pGraphicsWindow->CurrentExtentHeight;
						BeginRenderPassInfo.clearValueCount = TotalDeferredFramebufferCount;

						VkClearValue clears[TotalDeferredFramebufferCount];

						clears[0].color.float32[0] = pRenderHeader->Clear[0];
						clears[0].color.float32[1] = pRenderHeader->Clear[1];
						clears[0].color.float32[2] = pRenderHeader->Clear[2];
						clears[0].color.float32[3] = pRenderHeader->Clear[3];
						clears[1].color.float32[0] = 0.0f;
						clears[1].color.float32[1] = 0.0f;
						clears[1].color.float32[2] = 0.0f;
						clears[1].color.float32[3] = 0.0f;
						clears[2].color.float32[0] = 0.0f;
						clears[2].color.float32[1] = 0.0f;
						clears[2].color.float32[2] = 0.0f;
						clears[2].color.float32[3] = 0.0f;
						clears[3].color.float32[0] = 0.0f;
						clears[3].color.float32[1] = 0.0f;
						clears[3].color.float32[2] = 0.0f;
						clears[3].color.float32[3] = 0.0f;
						clears[4].color.float32[0] = 0.0f;
						clears[4].color.float32[1] = 0.0f;
						clears[4].color.float32[2] = 0.0f;
						clears[4].color.float32[3] = 0.0f;
						clears[5].color.float32[0] = pRenderHeader->Clear[0];
						clears[5].color.float32[1] = pRenderHeader->Clear[1];
						clears[5].color.float32[2] = pRenderHeader->Clear[2];
						clears[5].color.float32[3] = pRenderHeader->Clear[3];

						clears[6].depthStencil.depth = 1.0f;
						clears[6].depthStencil.stencil = 1;
						memset(&clears[7], NULL, sizeof(VkClearValue));
						memset(&clears[8], NULL, sizeof(VkClearValue));


						BeginRenderPassInfo.pClearValues = clears;
						vkCmdBeginRenderPass(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer, &BeginRenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

						PushConstantsDeferred DeferredPushConstants;
						memset(&DeferredPushConstants, NULL, sizeof(DeferredPushConstants));

						RHeaderCamera* pCameraHeader = (RHeaderCamera*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Camera);
						
						mat4 VP;
						mat4 CameraPositionMatrix;
						glm_mat4_identity(CameraPositionMatrix);
						Calculate_TotalMatrix(&CameraPositionMatrix, pObject->Header.Allocation);
						//multiple position headers is undefined

						mat4 vmat;
						mat4 pmat;
						glm_mat4_identity(vmat);
						glm_mat4_identity(pmat);
						glm_mat4_inv_precise_sse2(CameraPositionMatrix, vmat);

						if (pCameraHeader != NULL)
						{
							switch (pCameraHeader->Type)
							{
							case CameraType_Perspective:
								glm_perspective((float)pCameraHeader->CameraU.Perspective.y_fov, (float)pCameraHeader->CameraU.Perspective.AspectRatio,
									(float)pCameraHeader->CameraU.Perspective.z_near, (float)pCameraHeader->CameraU.Perspective.z_far, pmat);
								break;
							case CameraType_Orthographic:
								glm_ortho(-(float)pCameraHeader->CameraU.Orthographic.x_mag, (float)pCameraHeader->CameraU.Orthographic.x_mag,
									-(float)pCameraHeader->CameraU.Orthographic.y_mag, (float)pCameraHeader->CameraU.Orthographic.y_mag,
									(float)pCameraHeader->CameraU.Orthographic.z_near, (float)pCameraHeader->CameraU.Orthographic.z_far, pmat);
								break;
							}
						}
						else
						{
							glm_mat4_identity(pmat);
						}
						glm_mul_sse2(pmat, vmat, VP);

						for (size_t i = 0; i < Utils.GraphicsEffectSignaturesSize; i++)
						{
							GraphicsEffectSignature* pSignature = Utils.GraphicsEffectSignatures[i];
							for (size_t i1 = 0; i1 < pSignature->SignatureGPUBuffersSize; i1++)
							{
								ppPointers[i][i1] = 0;
							}
						}

						for (size_t i2 = 0; i2 < Utils.ElementGraphicsBuffer.Size;)
						{
							ElementGraphics* pElement = (Element*)&Utils.ElementGraphicsBuffer.Buffer[i2];
							if (pElement->Header.AllocationSize != NULL && pElement->Header.Allocation.Identifier == (uint32_t)GraphicsElement_ElementGraphics)
							{
								RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
								ElementGraphics* pElementInstance = NULL;
								RHeaderMaterial* pMaterialInstace = NULL;
								Object_Ref_StartThread_Element(pElement->Header.Allocation, pFrameBuffer->ThreadIndex, &pElementInstance);
								Object_Ref_StartThread_ResourceHeader(pMaterial->Header.Allocation, pFrameBuffer->ThreadIndex, &pMaterialInstace);

								if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pElement->iGraphicsWindow) == (TEXRESULT)Success)
									if (pMaterialInstace->AlphaMode == AlphaMode_Opaque || pMaterialInstace->AlphaMode == AlphaMode_Mask)
										Draw_ElementGraphics(pElementInstance, pMaterialInstace, pGraphicsWindow, pRenderHeader, pFrameBuffer->FrameIndex, ppTotalAllocations, ppPointers, pCameraHeader, VP);
								i2 += pElement->Header.AllocationSize;
							}
							else
							{
								i2++;
							}
						}
						vkCmdNextSubpass(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer, VK_SUBPASS_CONTENTS_INLINE);
						//TRANSPERANCY PASS							
						for (size_t i2 = 0; i2 < Utils.ElementGraphicsBuffer.Size;)
						{
							ElementGraphics* pElement = (Element*)&Utils.ElementGraphicsBuffer.Buffer[i2];
							if (pElement->Header.AllocationSize != NULL && pElement->Header.Allocation.Identifier == (uint32_t)GraphicsElement_ElementGraphics)
							{
								RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
								ElementGraphics* pElementInstance = NULL;
								RHeaderMaterial* pMaterialInstace = NULL;
								Object_Ref_StartThread_Element(pElement->Header.Allocation, pFrameBuffer->ThreadIndex, &pElementInstance);
								Object_Ref_StartThread_ResourceHeader(pMaterial->Header.Allocation, pFrameBuffer->ThreadIndex, &pMaterialInstace);

								if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pElement->iGraphicsWindow) == (TEXRESULT)Success)
									if (pMaterialInstace->AlphaMode == AlphaMode_Blend)
										Draw_ElementGraphics(pElementInstance, pMaterialInstace, pGraphicsWindow, pRenderHeader, pFrameBuffer->FrameIndex, ppTotalAllocations, ppPointers, pCameraHeader, VP);
								i2 += pElement->Header.AllocationSize;
							}
							else
							{
								i2++;
							}
						}

						vkCmdNextSubpass(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer, VK_SUBPASS_CONTENTS_INLINE);

						vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pGraphicsWindow->VkPipelineDeferred);

						uint8_t pushconstantbuffer[sizeof(PushConstantsDeferred)];
						memcpy(pushconstantbuffer, &DeferredPushConstants, sizeof(DeferredPushConstants));
						vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer, pGraphicsWindow->VkPipelineLayoutDeferred, VK_SHADER_STAGE_ALL, 0,
							pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, pushconstantbuffer);

						vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
							pGraphicsWindow->VkPipelineLayoutDeferred, 0, 1, &pGraphicsWindow->VkDescriptorSetsInputAttachment[pFrameBuffer->SwapChainIndex], 0, NULL);

						vkCmdDraw(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer, 6, 1, 0, 0);

						vkCmdEndRenderPass(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer);
					}
				}
				i1 += pRenderHeader->Header.AllocationSize;
			}
			else
			{
				i1++;
			}
		}

		vkEndCommandBuffer(pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer);

		//alternate break point
		if (pGraphicsWindow->RecreateFlag != false || pGraphicsWindow->CloseFlag != false)
		{
			Engine_Ref_Unlock_Mutex(pGraphicsWindow->SwapChainAccessMutex);
		}
		else
		{
			uint32_t QueueIndex1 = 0;
			{
				bool found = false;
				while (found == false)
				{
					for (size_t i = 0; i < pGraphicsWindow->pLogicalDevice->GraphicsQueueFamilySize; i++)
					{
						if (Engine_Ref_TryLock_Mutex(pGraphicsWindow->pLogicalDevice->GraphicsQueueMutexes[i]) == Success)
						{
							QueueIndex1 = i;
							found = true;
							break;
						}
					}
				}
			}

			VkQueue Queue = NULL;
			vkGetDeviceQueue(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->pLogicalDevice->GraphicsQueueFamilyIndex, QueueIndex1, &Queue);

			uint32_t WaitSemaphoresSize = 1;
			VkPipelineStageFlags WaitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
			VkSemaphore WaitSemaphores[] = { pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkImageAvailableSemaphore };

			uint32_t SignalSemaphoresSize = 1;
			VkSemaphore SignalSemaphores[] = { pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderFinishedSemaphore };

			VkSubmitInfo SubmitInfo;
			memset(&SubmitInfo, NULL, sizeof(SubmitInfo));
			SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			SubmitInfo.pWaitSemaphores = WaitSemaphores;
			SubmitInfo.pWaitDstStageMask = WaitStages;
			SubmitInfo.waitSemaphoreCount = WaitSemaphoresSize;
			SubmitInfo.pSignalSemaphores = SignalSemaphores;
			SubmitInfo.signalSemaphoreCount = SignalSemaphoresSize;
			SubmitInfo.pCommandBuffers = &pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkRenderCommandBuffer;
			SubmitInfo.commandBufferCount = 1;
			if ((res = vkQueueSubmit(Queue, 1, &SubmitInfo, pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkFrameFence)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("Display_Graphics()", "vkQueueSubmit Failed, VkResult == ", res);
			}

			uint32_t SwapChainsSize = 1;
			VkSwapchainKHR SwapChains[] = { pGraphicsWindow->SwapChain.VkSwapChain };

			VkPresentInfoKHR PresentInfo;
			memset(&PresentInfo, NULL, sizeof(PresentInfo));
			PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			PresentInfo.waitSemaphoreCount = WaitSemaphoresSize;
			PresentInfo.pWaitSemaphores = SignalSemaphores;
			PresentInfo.swapchainCount = SwapChainsSize;
			PresentInfo.pSwapchains = SwapChains;
			PresentInfo.pImageIndices = &pFrameBuffer->SwapChainIndex;
			PresentInfo.pResults = NULL;

			if ((res = vkQueuePresentKHR(Queue, &PresentInfo)) != VK_SUCCESS)
			{
				if (res == VK_ERROR_OUT_OF_DATE_KHR)
				{
					Engine_Ref_FunctionError("Display_Graphics()", "Recreate Flag Set. ", res);
					c89atomic_flag_test_and_set(&pGraphicsWindow->RecreateFlag);
				}
				else
				{
					Engine_Ref_FunctionError("Display_Graphics()", "vkQueuePresentKHR Failed, VkResult == ", res);
				}
			}
			pGraphicsWindow->FramesDone++;
			Engine_Ref_Unlock_Mutex(pGraphicsWindow->SwapChainAccessMutex);
		
			vkWaitForFences(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, 1, &pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkFrameFence, VK_TRUE, UINT64_MAX);
			vkResetFences(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, 1, &pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].VkFrameFence);
			Engine_Ref_Unlock_Mutex(pGraphicsWindow->pLogicalDevice->GraphicsQueueMutexes[QueueIndex1]);
		}

		for (size_t i1 = 0; i1 < Utils.RHeaderRenderBuffer.Size;)
		{
			RHeaderRender* pRenderHeader = ((RHeaderRender*)&Utils.RHeaderRenderBuffer.Buffer[i1]);
			if (pRenderHeader->Header.AllocationSize != NULL && pRenderHeader->Header.Allocation.Identifier == (uint32_t)GraphicsHeader_Render)
			{
				if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pRenderHeader->iGraphicsWindow) == (TEXRESULT)Success)
				{
					for (size_t i2 = 0; i2 < pRenderHeader->Header.iParentsSize; i2++)
					{
						Object* pObject = Object_Ref_Get_ObjectPointer(pRenderHeader->Header.iParents[i2]);
						for (size_t i2 = 0; i2 < Utils.ElementGraphicsBuffer.Size;)
						{
							ElementGraphics* pElement = (Element*)&Utils.ElementGraphicsBuffer.Buffer[i2];
							if (pElement->Header.AllocationSize != NULL && pElement->Header.Allocation.Identifier == (uint32_t)GraphicsElement_ElementGraphics)
							{
								RHeaderMaterial* pMaterialHeader = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
								if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pElement->iGraphicsWindow) == (TEXRESULT)Success)
								{
									Object_Ref_EndThread_Element(pElement->Header.Allocation, pFrameBuffer->ThreadIndex);
									Object_Ref_EndThread_ResourceHeader(pMaterialHeader->Header.Allocation, pFrameBuffer->ThreadIndex);
									if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialHeader->BaseColourTexture.iTexture) == Success)
										Object_Ref_EndThread_ResourceHeader(pMaterialHeader->BaseColourTexture.iTexture, pFrameBuffer->ThreadIndex);
									if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialHeader->MetallicRoughnessTexture.iTexture) == Success)
										Object_Ref_EndThread_ResourceHeader(pMaterialHeader->MetallicRoughnessTexture.iTexture, pFrameBuffer->ThreadIndex);
									if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialHeader->EmissiveTexture.iTexture) == Success)
										Object_Ref_EndThread_ResourceHeader(pMaterialHeader->EmissiveTexture.iTexture, pFrameBuffer->ThreadIndex);
									if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialHeader->NormalTexture.iTexture) == Success)
										Object_Ref_EndThread_ResourceHeader(pMaterialHeader->NormalTexture.iTexture, pFrameBuffer->ThreadIndex);
									if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialHeader->OcclusionTexture.iTexture) == Success)
										Object_Ref_EndThread_ResourceHeader(pMaterialHeader->OcclusionTexture.iTexture, pFrameBuffer->ThreadIndex);
								}
								i2 += pElement->Header.AllocationSize;
							}
							else
							{
								i2++;
							}
						}
						//TRANSPERANCY PASS
						for (size_t i2 = 0; i2 < Utils.ElementGraphicsBuffer.Size;)
						{
							ElementGraphics* pElement = (Element*)&Utils.ElementGraphicsBuffer.Buffer[i2];
							if (pElement->Header.AllocationSize != NULL && pElement->Header.Allocation.Identifier == (uint32_t)GraphicsElement_ElementGraphics)
							{
								RHeaderMaterial* pMaterialHeader = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
								if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pElement->iGraphicsWindow) == (TEXRESULT)Success)
								{
									Object_Ref_EndThread_Element(pElement->Header.Allocation, pFrameBuffer->ThreadIndex);
									Object_Ref_EndThread_ResourceHeader(pMaterialHeader->Header.Allocation, pFrameBuffer->ThreadIndex);
									if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialHeader->BaseColourTexture.iTexture) == Success)
										Object_Ref_EndThread_ResourceHeader(pMaterialHeader->BaseColourTexture.iTexture, pFrameBuffer->ThreadIndex);
									if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialHeader->MetallicRoughnessTexture.iTexture) == Success)
										Object_Ref_EndThread_ResourceHeader(pMaterialHeader->MetallicRoughnessTexture.iTexture, pFrameBuffer->ThreadIndex);
									if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialHeader->EmissiveTexture.iTexture) == Success)
										Object_Ref_EndThread_ResourceHeader(pMaterialHeader->EmissiveTexture.iTexture, pFrameBuffer->ThreadIndex);
									if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialHeader->NormalTexture.iTexture) == Success)
										Object_Ref_EndThread_ResourceHeader(pMaterialHeader->NormalTexture.iTexture, pFrameBuffer->ThreadIndex);
									if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterialHeader->OcclusionTexture.iTexture) == Success)
										Object_Ref_EndThread_ResourceHeader(pMaterialHeader->OcclusionTexture.iTexture, pFrameBuffer->ThreadIndex);
								}
								i2 += pElement->Header.AllocationSize;
							}
							else
							{
								i2++;
							}
						}
					}
				}
				i1 += pRenderHeader->Header.AllocationSize;
			}
			else
			{
				i1++;
			}
		}

		if (MaterialsAllocation.SizeBytes != NULL)
			GPUfree(pGraphicsWindow->pLogicalDevice, &MaterialsAllocation);

		for (size_t i = 0; i < Utils.GraphicsEffectSignaturesSize; i++)
		{
			GraphicsEffectSignature* pSignature = Utils.GraphicsEffectSignatures[i];
			for (size_t i1 = 0; i1 < pSignature->SignatureGPUBuffersSize; i1++)
			{
				if (ppTotalAllocations[i][i1].SizeBytes != NULL)
					GPUfree(pGraphicsWindow->pLogicalDevice, &ppTotalAllocations[i][i1]);
			}
			free(ppTotalAllocations[i]);
			free(ppPointers[i]);
		}
		free(ppTotalAllocations);
		free(ppPointers);

		if (pGraphicsWindow->RecreateFlag == false && pGraphicsWindow->CloseFlag == false)
		{
			//c89atomic_flag_test_and_set(&pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].RenderingFlag);
		}
		else
		{
			c89atomic_flag_clear(&pGraphicsWindow->SwapChain.FrameBuffers[pFrameBuffer->FrameIndex].RenderingFlag);
		}

	}
	Engine_Ref_Exit_Thread(0);
}

TEXRESULT Update_Graphics()
{
	size_t windowcount = 0;
	for (size_t iWindow = 0; iWindow < Utils.RHeaderGraphicsWindowBuffer.Size;)
	{
		RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)&Utils.RHeaderGraphicsWindowBuffer.Buffer[iWindow];
		if (pGraphicsWindow->Header.AllocationSize != NULL && pGraphicsWindow->Header.Allocation.Identifier == (uint32_t)GraphicsHeader_GraphicsWindow)
		{
			VkResult res = VK_SUCCESS;

			if (pGraphicsWindow->RecreateFlag == true)
			{		
				if (ReCreate_SwapChain(pGraphicsWindow, false) == Invalid_Parameter)
				{
					return;
				}

				for (size_t i1 = 0; i1 < Utils.RHeaderRenderBuffer.Size;)
				{
					RHeaderRender* pRenderHeader = ((RHeaderRender*)&Utils.RHeaderRenderBuffer.Buffer[i1]);
					if (pRenderHeader->Header.AllocationSize != NULL && pRenderHeader->Header.Allocation.Identifier == (uint32_t)GraphicsHeader_Render)
					{
						if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pRenderHeader->iGraphicsWindow) == (TEXRESULT)Success)
							ReCreate_RenderHeader(pRenderHeader, 0);
						i1 += pRenderHeader->Header.AllocationSize;
					}
					else
					{
						i1++;
					}
				}

				for (size_t i1 = 0; i1 < pGraphicsWindow->CurrentFrameBuffersSize; i1++)
				{
					for (size_t i2 = 0; i2 < DeferredImageCount; i2++)
					{
						VkDescriptorImageInfo ImageInfo;
						ImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
						ImageInfo.imageView = pGraphicsWindow->SwapChain.FrameBuffers[i1].DeferredImages[i2].ImageView;
						ImageInfo.sampler = NULL;
						Update_Descriptor(pGraphicsWindow->pLogicalDevice, pGraphicsWindow->VkDescriptorSetsInputAttachment[i1], i2, 0, VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, NULL, &ImageInfo);
					}
				}
				c89atomic_flag_clear(&pGraphicsWindow->RecreateFlag);
			}

			for (size_t i = 0; i < pGraphicsWindow->CurrentFrameBuffersSize; i++)
			{
				if (pGraphicsWindow->SwapChain.FrameBuffers[pGraphicsWindow->FrameIndex].RenderingFlag == false)
				{
					pGraphicsWindow->SwapChain.FrameBuffers[pGraphicsWindow->FrameIndex].pGraphicsWindow = pGraphicsWindow;
					pGraphicsWindow->SwapChain.FrameBuffers[pGraphicsWindow->FrameIndex].FrameIndex = pGraphicsWindow->FrameIndex;
					pGraphicsWindow->SwapChain.FrameBuffers[pGraphicsWindow->FrameIndex].ThreadIndex = (1 + windowcount + pGraphicsWindow->FrameIndex) % ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads;
					pGraphicsWindow->SwapChain.FrameBuffers[pGraphicsWindow->FrameIndex].QueueIndex = (windowcount + pGraphicsWindow->FrameIndex) % pGraphicsWindow->pLogicalDevice->GraphicsQueueFamilySize;
					pGraphicsWindow->SwapChain.FrameBuffers[pGraphicsWindow->FrameIndex].RenderingFlag = true;

					Thread* pThread = NULL;
					Engine_Ref_Create_Thread(&pThread, Render_GraphicsWindow, &pGraphicsWindow->SwapChain.FrameBuffers[pGraphicsWindow->FrameIndex]);
					Engine_Ref_Detach_Thread(pThread);

					pGraphicsWindow->FrameIndex = (pGraphicsWindow->FrameIndex + 1) % pGraphicsWindow->CurrentFrameBuffersSize;
				}
			}
			windowcount += pGraphicsWindow->CurrentFrameBuffersSize;
			iWindow += pGraphicsWindow->Header.AllocationSize;
		}
		else
		{
			iWindow++;
		}
	}
	return Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Initialise_Graphics()
{
	memset(&Utils, NULL, sizeof(Utils));
	memset(&Config, NULL, sizeof(Config));

	//config 
	Config.ExtensionsEnabledSize = 3;
	Config.ExtensionsEnabled[0] = (char*)VK_KHR_SURFACE_EXTENSION_NAME;
	Config.ExtensionsEnabled[1] = (char*)"VK_KHR_win32_surface";
	Config.ExtensionsEnabled[2] = (char*)VK_EXT_DEBUG_UTILS_EXTENSION_NAME;

#ifndef NDEBUG
	Config.ValidationLayersEnabledSize = 1;
#else
	Config.ValidationLayersEnabledSize = 0;
#endif

	Config.ValidationLayersEnabled[0] = (char*)"VK_LAYER_KHRONOS_validation";

	Config.InitialElementsMax = 1024;
	Config.InitialHeadersMax = 1024;

	Config.InitialStagingGPUBufferSize = MebiBytes(100);
	Config.InitialNativeGPUBufferSize = MebiBytes(200);

	Config.Samples = VK_SAMPLE_COUNT_1_BIT;
	Config.MaxAnisotropy = 16;
	Config.AnisotropicFiltering = true;

	Engine_Ref_Create_Mutex(Utils.ConvertersToTEXIMutex, MutexType_Plain);
	Engine_Ref_Create_Mutex(Utils.ConvertersFromTEXIMutex, MutexType_Plain);
	Engine_Ref_Create_Mutex(Utils.GraphicsEffectSignaturesMutex, MutexType_Plain);


	///////////////////////////////////////////////////////////////////////////////////////////////
	//buffer
	///////////////////////////////////////////////////////////////////////////////////////////////


	Utils.RHeaderWeightsSig.Buffer = &Utils.RHeaderWeightsBuffer;
	Utils.RHeaderImageSourceSig.Buffer = &Utils.RHeaderImageSourceBuffer;
	Utils.RHeaderBufferSourceSig.Buffer = &Utils.RHeaderBufferSourceBuffer;
	Utils.RHeaderGraphicsWindowSig.Buffer = &Utils.RHeaderGraphicsWindowBuffer;
	Utils.RHeaderSceneSig.Buffer = &Utils.RHeaderSceneBuffer;
	Utils.RHeaderCameraSig.Buffer = &Utils.RHeaderCameraBuffer;
	Utils.RHeaderLightSig.Buffer = &Utils.RHeaderLightBuffer;
	Utils.RHeaderSkinSig.Buffer = &Utils.RHeaderSkinBuffer;
	Utils.RHeaderPositionSig.Buffer = &Utils.RHeaderPositionBuffer;
	Utils.RHeaderAnimationChannelSig.Buffer = &Utils.RHeaderAnimationChannelBuffer;
	Utils.RHeaderAnimationSig.Buffer = &Utils.RHeaderAnimationBuffer;
	Utils.RHeaderMaterialSig.Buffer = &Utils.RHeaderMaterialBuffer;
	Utils.RHeaderTextureSig.Buffer = &Utils.RHeaderTextureBuffer;
	Utils.RHeaderBufferSig.Buffer = &Utils.RHeaderBufferBuffer;
	Utils.RHeaderRenderSig.Buffer = &Utils.RHeaderRenderBuffer;

	Utils.ElementGraphicsSig.Buffer = &Utils.ElementGraphicsBuffer;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//bytelength
	///////////////////////////////////////////////////////////////////////////////////////////////


	Utils.RHeaderWeightsSig.ByteLength = sizeof(RHeaderWeights);
	Utils.RHeaderImageSourceSig.ByteLength = sizeof(RHeaderImageSource);
	Utils.RHeaderBufferSourceSig.ByteLength = sizeof(RHeaderBufferSource);
	Utils.RHeaderGraphicsWindowSig.ByteLength = sizeof(RHeaderGraphicsWindow);
	Utils.RHeaderSceneSig.ByteLength = sizeof(RHeaderScene);
	Utils.RHeaderCameraSig.ByteLength = sizeof(RHeaderCamera);
	Utils.RHeaderLightSig.ByteLength = sizeof(RHeaderLight);
	Utils.RHeaderSkinSig.ByteLength = sizeof(RHeaderSkin);
	Utils.RHeaderPositionSig.ByteLength = sizeof(RHeaderPosition);
	Utils.RHeaderAnimationChannelSig.ByteLength = sizeof(RHeaderAnimationChannel);
	Utils.RHeaderAnimationSig.ByteLength = sizeof(RHeaderAnimation);
	Utils.RHeaderMaterialSig.ByteLength = sizeof(RHeaderMaterial);
	Utils.RHeaderTextureSig.ByteLength = sizeof(RHeaderTexture);
	Utils.RHeaderBufferSig.ByteLength = sizeof(RHeaderBuffer);
	Utils.RHeaderRenderSig.ByteLength = sizeof(RHeaderRender);

	Utils.ElementGraphicsSig.ByteLength = sizeof(ElementGraphics);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//identifiers
	///////////////////////////////////////////////////////////////////////////////////////////////


	Utils.RHeaderWeightsSig.Identifier = (uint32_t)GraphicsHeader_Weights;
	Utils.RHeaderImageSourceSig.Identifier = (uint32_t)GraphicsHeader_ImageSource;
	Utils.RHeaderBufferSourceSig.Identifier = (uint32_t)GraphicsHeader_BufferSource;
	Utils.RHeaderGraphicsWindowSig.Identifier = (uint32_t)GraphicsHeader_GraphicsWindow;
	Utils.RHeaderSceneSig.Identifier = (uint32_t)GraphicsHeader_Scene;
	Utils.RHeaderCameraSig.Identifier = (uint32_t)GraphicsHeader_Camera;
	Utils.RHeaderLightSig.Identifier = (uint32_t)GraphicsHeader_Light;
	Utils.RHeaderSkinSig.Identifier = (uint32_t)GraphicsHeader_Skin;
	Utils.RHeaderPositionSig.Identifier = (uint32_t)GraphicsHeader_Position;
	Utils.RHeaderAnimationChannelSig.Identifier = (uint32_t)GraphicsHeader_AnimationChannel;
	Utils.RHeaderAnimationSig.Identifier = (uint32_t)GraphicsHeader_Animation;
	Utils.RHeaderMaterialSig.Identifier = (uint32_t)GraphicsHeader_Material;
	Utils.RHeaderTextureSig.Identifier = (uint32_t)GraphicsHeader_Texture;
	Utils.RHeaderBufferSig.Identifier = (uint32_t)GraphicsHeader_Buffer;
	Utils.RHeaderRenderSig.Identifier = (uint32_t)GraphicsHeader_Render;

	Utils.ElementGraphicsSig.Identifier = (uint32_t)GraphicsElement_ElementGraphics;


	///////////////////////////////////////////////////////////////////////////////////////////////
	//destructors
	///////////////////////////////////////////////////////////////////////////////////////////////


	Utils.RHeaderWeightsSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_WeightsHeader;
	Utils.RHeaderImageSourceSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_ImageSourceHeader;
	Utils.RHeaderBufferSourceSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_BufferSourceHeader;
	Utils.RHeaderGraphicsWindowSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_GraphicsWindowHeader;
	Utils.RHeaderSceneSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_SceneHeader;
	Utils.RHeaderCameraSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_CameraHeader;
	Utils.RHeaderLightSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_LightHeader;
	Utils.RHeaderSkinSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_SkinHeader;
	Utils.RHeaderPositionSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_PositionHeader;
	Utils.RHeaderAnimationChannelSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_AnimationChannelHeader;
	Utils.RHeaderAnimationSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_AnimationHeader;
	Utils.RHeaderMaterialSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_MaterialHeader;
	Utils.RHeaderTextureSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_TextureHeader;
	Utils.RHeaderBufferSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_BufferHeader;
	Utils.RHeaderRenderSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_RenderHeader;

	Utils.ElementGraphicsSig.Destructor = (Destroy_ElementTemplate*)&Destroy_ElementGraphics;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//constructors
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderWeightsSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_WeightsHeader;
	Utils.RHeaderImageSourceSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_ImageSourceHeader;
	Utils.RHeaderBufferSourceSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_BufferSourceHeader;
	Utils.RHeaderGraphicsWindowSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_GraphicsWindowHeader;
	Utils.RHeaderSceneSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_SceneHeader;
	Utils.RHeaderCameraSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_CameraHeader;
	Utils.RHeaderLightSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_LightHeader;
	Utils.RHeaderSkinSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_SkinHeader;
	Utils.RHeaderPositionSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_PositionHeader;
	Utils.RHeaderAnimationChannelSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_AnimationChannelHeader;
	Utils.RHeaderAnimationSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_AnimationHeader;
	Utils.RHeaderMaterialSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_MaterialHeader;
	Utils.RHeaderTextureSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_TextureHeader;
	Utils.RHeaderBufferSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_BufferHeader;
	Utils.RHeaderRenderSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_RenderHeader;

	Utils.ElementGraphicsSig.Constructor = (Create_ElementTemplate*)&Create_ElementGraphics;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//ReCreate
	///////////////////////////////////////////////////////////////////////////////////////////////

	//Utils.RHeaderWeightsSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_WeightsHeader;
	//Utils.RHeaderImageSourceSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_ImageSourceHeader;
	//Utils.RHeaderBufferSourceSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_BufferSourceHeader;
	Utils.RHeaderGraphicsWindowSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_GraphicsWindowHeader;
	//Utils.RHeaderSceneSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_SceneHeader;
	//Utils.RHeaderCameraSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_CameraHeader;
	//Utils.RHeaderLightSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_LightHeader;
	//Utils.RHeaderSkinSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_SkinHeader;
	//Utils.RHeaderPositionSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_PositionHeader;
	//Utils.RHeaderAnimationChannelSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_AnimationChannelHeader;
	//Utils.RHeaderAnimationSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_AnimationHeader;
	Utils.RHeaderMaterialSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_MaterialHeader;
	Utils.RHeaderTextureSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_TextureHeader;
	Utils.RHeaderBufferSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_BufferHeader;
	Utils.RHeaderRenderSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_RenderHeader;

	Utils.ElementGraphicsSig.ReConstructor = (ReCreate_ElementTemplate*)&ReCreate_ElementGraphics;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//packers
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderWeightsSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_WeightsHeader;
	Utils.RHeaderImageSourceSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_ImageSourceHeader;
	Utils.RHeaderBufferSourceSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_BufferSourceHeader;
	Utils.RHeaderGraphicsWindowSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_GraphicsWindowHeader;
	Utils.RHeaderSceneSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_SceneHeader;
	Utils.RHeaderCameraSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_CameraHeader;
	Utils.RHeaderLightSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_LightHeader;
	Utils.RHeaderSkinSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_SkinHeader;
	Utils.RHeaderPositionSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_PositionHeader;
	Utils.RHeaderAnimationChannelSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_AnimationChannelHeader;
	Utils.RHeaderAnimationSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_AnimationHeader;
	Utils.RHeaderMaterialSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_MaterialHeader;
	Utils.RHeaderTextureSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_TextureHeader;
	Utils.RHeaderBufferSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_BufferHeader;
	Utils.RHeaderRenderSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_RenderHeader;

	Utils.ElementGraphicsSig.Packer = (Pack_ElementTemplate*)&Pack_ElementGraphics;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//unpackers
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderWeightsSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_WeightsHeader;
	Utils.RHeaderImageSourceSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_ImageSourceHeader;
	Utils.RHeaderBufferSourceSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_BufferSourceHeader;
	Utils.RHeaderGraphicsWindowSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_GraphicsWindowHeader;
	Utils.RHeaderSceneSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_SceneHeader;
	Utils.RHeaderCameraSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_CameraHeader;
	Utils.RHeaderLightSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_LightHeader;
	Utils.RHeaderSkinSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_SkinHeader;
	Utils.RHeaderPositionSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_PositionHeader;
	Utils.RHeaderAnimationChannelSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_AnimationChannelHeader;
	Utils.RHeaderAnimationSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_AnimationHeader;
	Utils.RHeaderMaterialSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_MaterialHeader;
	Utils.RHeaderTextureSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_TextureHeader;
	Utils.RHeaderBufferSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_BufferHeader;
	Utils.RHeaderRenderSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_RenderHeader;

	Utils.ElementGraphicsSig.UnPacker = (UnPack_ElementTemplate*)&UnPack_ElementGraphics;


	///////////////////////////////////////////////////////////////////////////////////////////////
	//create buffer
	///////////////////////////////////////////////////////////////////////////////////////////////


	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderWeightsBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderImageSourceBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderBufferSourceBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderGraphicsWindowBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderSceneBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderCameraBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderLightBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderSkinBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderPositionBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderAnimationChannelBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderAnimationBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderMaterialBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderTextureBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderBufferBuffer, Config.InitialHeadersMax);
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderRenderBuffer, Config.InitialHeadersMax);

	Object_Ref_Create_ElementBuffer(&Utils.ElementGraphicsBuffer, Config.InitialElementsMax);


	///////////////////////////////////////////////////////////////////////////////////////////////
	//register
	///////////////////////////////////////////////////////////////////////////////////////////////


	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderWeightsSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderImageSourceSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderBufferSourceSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderGraphicsWindowSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderSceneSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderCameraSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderLightSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderSkinSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderPositionSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderAnimationChannelSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderAnimationSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderMaterialSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderTextureSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderBufferSig);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderRenderSig);

	Object_Ref_Register_ElementSignature(&Utils.ElementGraphicsSig);


	///////////////////////////////////////////////////////////////////////////////////////////////
	//effects
	///////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////
	//identifiers
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.Generic3DSig.Identifier = (uint32_t)GraphicsEffect_Generic3D;
	Utils.Generic2DSig.Identifier = (uint32_t)GraphicsEffect_Generic2D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Create effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.Generic3DSig.Constructor = (Create_GraphicsEffectTemplate*)&Create_Generic3D;
	Utils.Generic2DSig.Constructor = (Create_GraphicsEffectTemplate*)&Create_Generic2D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Destroy Effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.Generic3DSig.Destructor = (Destroy_GraphicsEffectTemplate*)&Destroy_Generic3D;
	Utils.Generic2DSig.Destructor = (Destroy_GraphicsEffectTemplate*)&Destroy_Generic2D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//ReCreate Effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.Generic3DSig.ReConstructor = (ReCreate_GraphicsEffectTemplate*)&ReCreate_Generic3D;
	Utils.Generic2DSig.ReConstructor = (ReCreate_GraphicsEffectTemplate*)&ReCreate_Generic2D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Pack Effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.Generic3DSig.Packer = (Pack_GraphicsEffectTemplate*)&Pack_Generic3D;
	Utils.Generic2DSig.Packer = (Pack_GraphicsEffectTemplate*)&Pack_Generic2D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//UnPack Effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.Generic3DSig.UnPacker = (UnPack_GraphicsEffectTemplate*)&UnPack_Generic3D;
	Utils.Generic2DSig.UnPacker = (UnPack_GraphicsEffectTemplate*)&UnPack_Generic2D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Draw Effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.Generic3DSig.Draw = (Draw_GraphicsEffectTemplate*)&Draw_Generic3D;
	Utils.Generic2DSig.Draw = (Draw_GraphicsEffectTemplate*)&Draw_Generic2D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Update Effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.Generic3DSig.Update = (Update_GraphicsEffectTemplate*)&Update_Generic3D;
	Utils.Generic2DSig.Update = (Update_GraphicsEffectTemplate*)&Update_Generic2D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Update Effect Signature
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.Generic3DSig.UpdateSignature = &UpdateSignature_Generic3D;
	Utils.Generic2DSig.UpdateSignature = &UpdateSignature_Generic2D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Effects Buffers/Pointers
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.Generic3DSig.SignatureGPUBuffersSize = StorageBufferBindings; //info, weights, joints, lights, matrix
	Utils.Generic2DSig.SignatureGPUBuffersSize = 1; //param2d

	///////////////////////////////////////////////////////////////////////////////////////////////
	//effects registration
	///////////////////////////////////////////////////////////////////////////////////////////////

	Register_GraphicsEffectSignature(&Utils.Generic3DSig);
	Register_GraphicsEffectSignature(&Utils.Generic2DSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Graphics Initialisation
	///////////////////////////////////////////////////////////////////////////////////////////////

	VkResult res = VK_SUCCESS;
	TEXRESULT tres = (TEXRESULT)Success;
	{//instance startup

		//instance extensions
		size_t ExtensionsAvailableSize = NULL;
		VkExtensionProperties* ExtensionsAvailable = NULL;
		//instance validation layers
		size_t ValidationLayersAvailableSize = NULL;
		VkLayerProperties* ValidationLayersAvailable = NULL;


		//enumerating extensions/layers
		vkEnumerateInstanceExtensionProperties(NULL, (uint32_t*)&ExtensionsAvailableSize, NULL);
		if (ExtensionsAvailableSize != NULL)
		{
			ExtensionsAvailable = (VkExtensionProperties*)calloc(ExtensionsAvailableSize, sizeof(*ExtensionsAvailable));
			vkEnumerateInstanceExtensionProperties(NULL, (uint32_t*)&ExtensionsAvailableSize, (VkExtensionProperties*)ExtensionsAvailable);
		}

		vkEnumerateInstanceLayerProperties((uint32_t*)&ValidationLayersAvailableSize, NULL);
		if (ExtensionsAvailableSize != NULL)
		{
			ValidationLayersAvailable = (VkLayerProperties*)calloc(ValidationLayersAvailableSize, sizeof(*ValidationLayersAvailable));
			vkEnumerateInstanceLayerProperties((uint32_t*)&ValidationLayersAvailableSize, (VkLayerProperties*)ValidationLayersAvailable);
		}

		//checking for validaty 
		for (size_t i = 0; i < Config.ExtensionsEnabledSize; i++)
		{
			if (Check_Extension_Validately(Config.ExtensionsEnabled[i], ExtensionsAvailable, ExtensionsAvailableSize) == false)
			{
				Engine_Ref_FunctionError("Initialise_Graphics()", "Extension Is Not Available.", Config.ExtensionsEnabled[i]);
				return (TEXRESULT)Invalid_Parameter;
			}
		}

		for (size_t i = 0; i < Config.ValidationLayersEnabledSize; i++)
		{
			if (Check_Layer_Validately(Config.ValidationLayersEnabled[i], ValidationLayersAvailable, ValidationLayersAvailableSize) == false)
			{
				Engine_Ref_FunctionError("Initialise_Graphics()", "Layer Is Not Available.", Config.ValidationLayersEnabled[i]);
				return (TEXRESULT)Invalid_Parameter;
			}
		}
		//printing pData
		/*
#ifdef NDEBUG
#else
		printf("\nDevelopment Version Of Graphics Extension\n");

		printf("\nInstance Extensions Available\n");
		for (size_t i = 0; i < Utils.ExtensionsAvailableSize; i++)
		{
			printf("\t%s\n", Utils.ExtensionsAvailable[i]);
		}
		printf("\nInstance Extensions Enabled\n");
		for (size_t i = 0; i < Config.ExtensionsEnabledSize; i++)
		{
			printf("\t%s\n", Config.ExtensionsEnabled[i]);
		}
		printf("\nInstance Validation Layers Available\n");
		for (size_t i = 0; i < Utils.ValidationLayersAvailableSize; i++)
		{
			printf("\t%s\n", Utils.ValidationLayersAvailable[i]);
		}
		printf("\nInstance Validation Layers Enabled\n");
		for (size_t i = 0; i < Config.ValidationLayersEnabledSize; i++)
		{
			printf("\t%s\n", Config.ValidationLayersEnabled[i]);
		}
#endif
*/
		{//instance creation
			VkApplicationInfo ApplicationInfo;
			memset(&ApplicationInfo, NULL, sizeof(ApplicationInfo));
			ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			ApplicationInfo.pApplicationName = "Triangle Engine X";
			ApplicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
			ApplicationInfo.pEngineName = "Triangle Engine X";
			ApplicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
			ApplicationInfo.apiVersion = VK_API_VERSION_1_2;

			VkInstanceCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			Info.pApplicationInfo = &ApplicationInfo;

			Info.enabledExtensionCount = Config.ExtensionsEnabledSize;
			Info.ppEnabledExtensionNames = Config.ExtensionsEnabled;

			Info.enabledLayerCount = Config.ValidationLayersEnabledSize;
			Info.ppEnabledLayerNames = Config.ValidationLayersEnabled;

			if ((res = vkCreateInstance(&Info, NULL, &Utils.Instance)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("Initialise_Graphics()", "Vulkan Instance Creation Failed. VkResult == ", res);
				return (TEXRESULT)Failure;
			}
		}

		if (ExtensionsAvailable)
			free(ExtensionsAvailable);
		if (ValidationLayersAvailable)
			free(ValidationLayersAvailable);
	}

	/////////////////////////////////////////////////////////////////////
	//DEVICES
	/////////////////////////////////////////////////////////////////////

	Get_PhysicalDevices((PhysicalDevice**)&Utils.PhysicalDevices, (uint32_t*)&Utils.DevicesSize);
	if (Utils.DevicesSize == NULL)
	{
		Engine_Ref_FunctionError("Initialise_Graphics()", "No Graphics Devices Were Found. Instance == ", Utils.Instance);
		return (TEXRESULT)Failure;
	}

	Utils.LogicalDevices = (LogicalDevice*)calloc(Utils.DevicesSize, sizeof(*Utils.LogicalDevices));
	for (size_t i = 0; i < Utils.DevicesSize; i++)
	{
		if ((tres = Create_LogicalDevice((LogicalDevice*)&Utils.LogicalDevices[i], (PhysicalDevice*)&Utils.PhysicalDevices[i], (char**)Config.ValidationLayersEnabled, Config.ValidationLayersEnabledSize,
			(char**)LogicalDeviceExtensions, LogicalDeviceExtensionsSize, &Utils.PhysicalDevices[i].Features, Config.InitialStagingGPUBufferSize, Config.InitialNativeGPUBufferSize)) != (TEXRESULT)Success)
		{
			Engine_Ref_FunctionError("Initialise_Graphics()", "Create_LogicalDevice, TEXRESULT == ", tres);
			return (TEXRESULT)Failure;
		}
	}

	/////////////////////////////////////////////////////////////////////
	//MISC
	/////////////////////////////////////////////////////////////////////

	Utils.GenericResources = calloc(Utils.DevicesSize, sizeof(*Utils.GenericResources));
	for (size_t i = 0; i < Utils.DevicesSize; i++)
	{
		{//material textures bindings
			VkDescriptorSetLayoutBinding BindingsMaterialTextures[MaterialTextureBindings + 1];
			{
				BindingsMaterialTextures[0].binding = 0;
				BindingsMaterialTextures[0].descriptorCount = 1;
				BindingsMaterialTextures[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
				BindingsMaterialTextures[0].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
				BindingsMaterialTextures[0].pImmutableSamplers = NULL;
			}
			for (size_t i = 1; i < MaterialTextureBindings + 1; i++)
			{
				BindingsMaterialTextures[i].binding = i;
				BindingsMaterialTextures[i].descriptorCount = 1;
				BindingsMaterialTextures[i].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
				BindingsMaterialTextures[i].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
				BindingsMaterialTextures[i].pImmutableSamplers = NULL;
			}
			VkDescriptorSetLayoutCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			Info.bindingCount = (uint32_t)MaterialTextureBindings + 1;
			Info.pBindings = BindingsMaterialTextures;
			Info.pNext = NULL;
			Info.flags = NULL;
			if ((res = vkCreateDescriptorSetLayout(Utils.LogicalDevices[i].VkLogicalDevice, &Info, NULL, &Utils.GenericResources[i].VkDescriptorSetLayoutMaterial)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("Create_LogicalDevice()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}
		{//storagebuffer bindings
			VkDescriptorSetLayoutBinding BindingsStorageBuffers[StorageBufferBindings];
			for (size_t i = 0; i < StorageBufferBindings; i++)
			{
				BindingsStorageBuffers[i].binding = i;
				BindingsStorageBuffers[i].descriptorCount = 1;
				BindingsStorageBuffers[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
				BindingsStorageBuffers[i].stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
				BindingsStorageBuffers[i].pImmutableSamplers = NULL;
			}
			VkDescriptorSetLayoutCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			Info.bindingCount = (uint32_t)StorageBufferBindings;
			Info.pBindings = BindingsStorageBuffers;
			Info.pNext = NULL;
			Info.flags = NULL;
			if ((res = vkCreateDescriptorSetLayout(Utils.LogicalDevices[i].VkLogicalDevice, &Info, NULL, &Utils.GenericResources[i].VkDescriptorSetLayoutStorageBuffers)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("Create_LogicalDevice()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}
		{//layout 3D
			VkDescriptorSetLayout layouts[2] = { Utils.GenericResources[i].VkDescriptorSetLayoutMaterial, Utils.GenericResources[i].VkDescriptorSetLayoutStorageBuffers };
			uint32_t layoutsSize = 2;

			VkPushConstantRange push_constant;
			push_constant.offset = 0;
			push_constant.size = Utils.LogicalDevices[i].pPhysicalDevice->Properties.limits.maxPushConstantsSize;
			push_constant.stageFlags = VK_SHADER_STAGE_ALL;

			VkPipelineLayoutCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			Info.setLayoutCount = layoutsSize;
			Info.pSetLayouts = layouts;
			Info.pushConstantRangeCount = 1;
			Info.pPushConstantRanges = &push_constant;
			Info.flags = NULL;
			Info.pNext = NULL;
			if ((res = vkCreatePipelineLayout(Utils.LogicalDevices[i].VkLogicalDevice, &Info, NULL, &Utils.GenericResources[i].PipelineLayout3D)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("Create_LogicalDevice()", "vkCreatePipelineLayout Failed, VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}
		{//layout 2D

			VkDescriptorSetLayout layouts[1] = { Utils.GenericResources[i].VkDescriptorSetLayoutMaterial };
			uint32_t layoutsSize = 1;

			VkPushConstantRange push_constant;
			push_constant.offset = 0;
			push_constant.size = Utils.LogicalDevices[i].pPhysicalDevice->Properties.limits.maxPushConstantsSize;
			push_constant.stageFlags = VK_SHADER_STAGE_ALL;

			VkPipelineLayoutCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));
			Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
			Info.setLayoutCount = layoutsSize;
			Info.pSetLayouts = layouts;
			Info.pushConstantRangeCount = 1;
			Info.pPushConstantRanges = &push_constant;
			Info.flags = NULL;
			Info.pNext = NULL;
			if ((res = vkCreatePipelineLayout(Utils.LogicalDevices[i].VkLogicalDevice, &Info, NULL, &Utils.GenericResources[i].PipelineLayout2D)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("Create_LogicalDevice()", "vkCreatePipelineLayout Failed, VkResult == ", res);
				return (TEXRESULT)(Failure);
			}
		}
		{
			Utils.GenericResources[i].VkDescriptorSetsStorageBuffers = (VkDescriptorSet*)calloc(Utils.LogicalDevices[i].GraphicsQueueFamilySize, sizeof(VkDescriptorSet));
			{
				uint32_t PoolSizesSize = 1;
				VkDescriptorPoolSize PoolSizes[1];

				PoolSizes[0].descriptorCount = DeferredImageCount * Utils.LogicalDevices[i].GraphicsQueueFamilySize;
				PoolSizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

				VkDescriptorPoolCreateInfo Info;
				memset(&Info, NULL, sizeof(Info));
				Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
				Info.maxSets = 1 * Utils.LogicalDevices[i].GraphicsQueueFamilySize;
				Info.poolSizeCount = PoolSizesSize;
				Info.pPoolSizes = PoolSizes;
				Info.flags = 0;

				if ((res = vkCreateDescriptorPool(Utils.LogicalDevices[i].VkLogicalDevice, &Info, NULL, &Utils.GenericResources[i].VkDescriptorPool3D)) != VK_SUCCESS)
				{
					Engine_Ref_FunctionError("ReCreate_GraphicsWindowHeader()", "vkCreateDescriptorPool, VkResult == ", res);
					return;
				}
			}
			for (size_t i1 = 0; i1 < Utils.LogicalDevices[i].GraphicsQueueFamilySize; i1++)
			{
				uint32_t layoutsSize = 1;
				VkDescriptorSetLayout layouts[1] = { Utils.GenericResources[i].VkDescriptorSetLayoutStorageBuffers };
				VkDescriptorSet sets[1];

				VkDescriptorSetAllocateInfo Info;
				memset(&Info, NULL, sizeof(Info));
				Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
				Info.descriptorPool = Utils.GenericResources[i].VkDescriptorPool3D;
				Info.descriptorSetCount = layoutsSize;
				Info.pSetLayouts = layouts;
				Info.pNext = NULL;
				if ((res = vkAllocateDescriptorSets(Utils.LogicalDevices[i].VkLogicalDevice, &Info, sets)) != VK_SUCCESS)
				{
					Engine_Ref_FunctionError("ReCreate_GraphicsWindowHeader()", "vkAllocateDescriptorSets, VkResult == ", res);
					return;
				}
				Utils.GenericResources[i].VkDescriptorSetsStorageBuffers[i1] = sets[0];
			}
		}
	}
	return (TEXRESULT)Success;
}

TEXRESULT Destroy_Graphics()
{
	//to destroy all rendering threads.
	for (size_t iWindow = 0; iWindow < Utils.RHeaderGraphicsWindowBuffer.Size;)
	{
		RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)&Utils.RHeaderGraphicsWindowBuffer.Buffer[iWindow];
		if (pGraphicsWindow->Header.AllocationSize != NULL && pGraphicsWindow->Header.Allocation.Identifier == (uint32_t)GraphicsHeader_GraphicsWindow)
		{
			Destroy_SwapChain(pGraphicsWindow, true);
			iWindow += pGraphicsWindow->Header.AllocationSize;
		}
		else
		{
			iWindow++;
		}
	}

	Object_Ref_Destroy_ElementBuffer(&Utils.ElementGraphicsBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderWeightsBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderImageSourceBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderBufferSourceBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderSceneBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderCameraBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderLightBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderSkinBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderPositionBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderAnimationChannelBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderAnimationBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderMaterialBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderTextureBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderBufferBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderRenderBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderGraphicsWindowBuffer);


	Object_Ref_DeRegister_ElementSignature(&Utils.ElementGraphicsSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderWeightsSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderImageSourceSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderBufferSourceSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderSceneSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderCameraSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderLightSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderSkinSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderPositionSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderAnimationChannelSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderAnimationSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderMaterialSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderTextureSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderBufferSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderRenderSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderGraphicsWindowSig);


	DeRegister_GraphicsEffectSignature(&Utils.Generic2DSig);
	DeRegister_GraphicsEffectSignature(&Utils.Generic3DSig);
	DeRegister_GraphicsEffectSignature(&Utils.ReflectionSig);

	if (Utils.GraphicsEffectSignatures != NULL)
		free(Utils.GraphicsEffectSignatures);
	Utils.GraphicsEffectSignaturesSize = NULL;

	if (Utils.ConvertersToTEXISize != NULL)
		free(Utils.ConvertersToTEXI);
	Utils.ConvertersToTEXISize = NULL;

	if (Utils.ConvertersFromTEXISize != NULL)
		free(Utils.ConvertersFromTEXI);
	Utils.ConvertersFromTEXISize = NULL;

	Engine_Ref_Destroy_Mutex(Utils.ConvertersToTEXIMutex, MutexType_Plain);
	Engine_Ref_Destroy_Mutex(Utils.ConvertersFromTEXIMutex, MutexType_Plain);
	Engine_Ref_Destroy_Mutex(Utils.GraphicsEffectSignaturesMutex, MutexType_Plain);

	for (size_t i = 0; i < Utils.DevicesSize; i++)
	{
		if (Utils.GenericResources[i].PipelineLayout3D != NULL)
			vkDestroyPipelineLayout(Utils.LogicalDevices[i].VkLogicalDevice, Utils.GenericResources[i].PipelineLayout3D, NULL);
		if (Utils.GenericResources[i].PipelineLayout2D != NULL)
			vkDestroyPipelineLayout(Utils.LogicalDevices[i].VkLogicalDevice, Utils.GenericResources[i].PipelineLayout2D, NULL);
		if (Utils.GenericResources[i].VkDescriptorSetLayoutStorageBuffers != NULL)
			vkDestroyDescriptorSetLayout(Utils.LogicalDevices[i].VkLogicalDevice, Utils.GenericResources[i].VkDescriptorSetLayoutStorageBuffers, NULL);
		if (Utils.GenericResources[i].VkDescriptorSetLayoutMaterial != NULL)
			vkDestroyDescriptorSetLayout(Utils.LogicalDevices[i].VkLogicalDevice, Utils.GenericResources[i].VkDescriptorSetLayoutMaterial, NULL);
		if (Utils.GenericResources[i].VkDescriptorSetsStorageBuffers != NULL)
		{
			free(Utils.GenericResources[i].VkDescriptorSetsStorageBuffers);
		}
		if (Utils.GenericResources[i].VkDescriptorPool3D != NULL)
			vkDestroyDescriptorPool(Utils.LogicalDevices[i].VkLogicalDevice, Utils.GenericResources[i].VkDescriptorPool3D, NULL);
		Destroy_LogicalDevice((LogicalDevice*)&Utils.LogicalDevices[i]);
		Clear_PhysicalDevice((PhysicalDevice*)&Utils.PhysicalDevices[i]);
	}
	if (Utils.DevicesSize != NULL)
	{
		free(Utils.LogicalDevices);
		free(Utils.PhysicalDevices);
		free(Utils.GenericResources);
	}

	vkDestroyInstance(Utils.Instance, NULL);

	memset(&Config, NULL, sizeof(Config));
	memset(&Utils, NULL, sizeof(Utils));


	return Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Extension Information
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//entry point to the extension
//this functions purpose is to register everything with the application. One time only.
__declspec(dllexport) void Initialise_Resources(ExtensionCreateInfo* ReturnInfo)
{
#ifdef NDEBUG
	ReturnInfo->BinType = Release;
#else
	ReturnInfo->BinType = Debug;
#endif

	MakeVersion(ReturnInfo->ExtensionVersion, 1, 0, 0);
	MakeVersion(ReturnInfo->MinRequiredVersion, 1, 0, 0);
	MakeVersion(ReturnInfo->MaxRequiredVersion, UINT32_MAX, UINT32_MAX, UINT32_MAX);

	Engine_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	Object_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);


	//Config
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Graphics::ExtensionsEnabled"), &Config.ExtensionsEnabled, Config.ExtensionsEnabledSize, sizeof(*Config.ExtensionsEnabled));
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Graphics::ExtensionsEnabledSize"), &Config.ExtensionsEnabledSize, 1, sizeof(Config.ExtensionsEnabledSize));
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Graphics::ValidationLayersEnabled"), &Config.ValidationLayersEnabled, Config.ValidationLayersEnabledSize, sizeof(*Config.ValidationLayersEnabled));
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Graphics::ValidationLayersEnabledSize"), &Config.ValidationLayersEnabledSize, 1, sizeof(Config.ValidationLayersEnabledSize));

	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Graphics::InitialHeadersMax"), &Config.InitialHeadersMax, 1, sizeof(Config.InitialHeadersMax));
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Graphics::InitialElementsMax"), &Config.InitialElementsMax, 1, sizeof(Config.InitialElementsMax));

	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Graphics::InitialStagingGPUBufferSize"), &Config.InitialStagingGPUBufferSize, 1, sizeof(Config.InitialStagingGPUBufferSize));
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Graphics::InitialNativeGPUBufferSize"), &Config.InitialNativeGPUBufferSize, 1, sizeof(Config.InitialNativeGPUBufferSize));

	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Graphics::Samples"), &Config.Samples, 1, sizeof(Config.Samples));
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Graphics::MaxAnisotropy"), &Config.MaxAnisotropy, 1, sizeof(Config.MaxAnisotropy));
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Graphics::AnisotropicFiltering"), &Config.AnisotropicFiltering, 1, sizeof(Config.AnisotropicFiltering));


	//Resources
	ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData((void*)"Graphics::Utils"), &GraphicsRes.pUtils, &Utils);

	//Functions
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Initialise_Graphics"), &GraphicsRes.pInitialise_Graphics, &Initialise_Graphics, Construct, 0.01f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Destroy_Graphics"), &GraphicsRes.pDestroy_Graphics, &Destroy_Graphics, Destruct, 1000.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Update_Graphics"), &GraphicsRes.pUpdate_Graphics, &Update_Graphics, EveryFrame, 101.0f, 0, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Get_AttributeTypePriority"), &GraphicsRes.pGet_AttributeTypePriority, &Get_AttributeTypePriority, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Get_FormatDetails"), &GraphicsRes.pGet_FormatDetails, &Get_FormatDetails, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Calculate_TotalMatrix"), &GraphicsRes.pCalculate_TotalMatrix, &Calculate_TotalMatrix, (CallFlagBits)NULL, 0.0f, NULL, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Check_Memory"), &GraphicsRes.pCheck_Memory, &Check_Memory, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Destroy_GPU_MemoryBuffer"), &GraphicsRes.pDestroy_GPU_MemoryBuffer, &Destroy_GPU_MemoryBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Create_GPU_MemoryBuffer"), &GraphicsRes.pCreate_GPU_MemoryBuffer, &Create_GPU_MemoryBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Resize_GPU_MemoryBuffer"), &GraphicsRes.pResize_GPU_MemoryBuffer, &Resize_GPU_MemoryBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::GPUmalloc"), &GraphicsRes.pGPUmalloc, &GPUmalloc, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::GPUfree"), &GraphicsRes.pGPUfree, &GPUfree, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Convert::Add_XtoTEXIconverter"), &GraphicsRes.pAdd_XtoTEXIconverter, &Add_XtoTEXIconverter, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Convert::Add_TEXItoXconverter"), &GraphicsRes.pAdd_TEXItoXconverter, &Add_TEXItoXconverter, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Convert::Remove_XtoTEXIconverter"), &GraphicsRes.pRemove_XtoTEXIconverter, &Remove_XtoTEXIconverter, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Convert::Remove_TEXItoXconverter"), &GraphicsRes.pRemove_TEXItoXconverter, &Remove_TEXItoXconverter, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Convert::XtoTEXI"), &GraphicsRes.pXtoTEXI, &XtoTEXI, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Convert::TEXItoX"), &GraphicsRes.pTEXItoX, &TEXItoX, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Effects::Register_GraphicsEffectSignature"), &GraphicsRes.pRegister_GraphicsEffectSignature, &Register_GraphicsEffectSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Effects::DeRegister_GraphicsEffectSignature"), &GraphicsRes.pDeRegister_GraphicsEffectSignature, &DeRegister_GraphicsEffectSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Effects::Find_GraphicsEffectSignature"), &GraphicsRes.pFind_GraphicsEffectSignature, &Find_GraphicsEffectSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Effects::Get_GraphicsEffect"), &GraphicsRes.pGet_GraphicsEffect, &Get_GraphicsEffect, (CallFlagBits)NULL, 0.0f, NULL, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Create_DummyTEXI"), &GraphicsRes.pCreate_DummyTEXI, &Create_DummyTEXI, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Create_ImageAtlas"), &GraphicsRes.pCreate_ImageAtlas, &Create_ImageAtlas, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Convert_ImageData"), &GraphicsRes.pConvert_ImageData, &Convert_ImageData, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Update_Descriptor"), &GraphicsRes.pUpdate_Descriptor, &Update_Descriptor, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Destroy_GPU_Texture"), &GraphicsRes.pDestroy_GPU_Texture, &Destroy_GPU_Texture, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Destroy_GPU_Buffer"), &GraphicsRes.pDestroy_GPU_Buffer, &Destroy_GPU_Buffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Get_DeviceIndex"), &GraphicsRes.pGet_DeviceIndex, &Get_DeviceIndex, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::Destroy_SwapChain"), &GraphicsRes.pDestroy_SwapChain, &Destroy_SwapChain, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Graphics::ReCreate_SwapChain"), &GraphicsRes.pReCreate_SwapChain, &ReCreate_SwapChain, (CallFlagBits)NULL, 0.0f, NULL, NULL);
}
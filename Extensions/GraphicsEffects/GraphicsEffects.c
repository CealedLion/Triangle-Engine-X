#pragma once
//C
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//Third-Party
#include <atomic\atomic.h>
//OS Specific
#ifdef _WIN32
//#include <process.h>
#else

#endif
//ours
#include "Extension.h"
#include "Object.h"
#include <vulkan/vulkan.h>
#include <vulkan/spirv.h>
#define TEX_EXPOSE_GRAPHICS
#include "Graphics.h"
#include "GraphicsShaders.h"
#define TEX_EXPOSE_GRAPHICSEFFECTS
#include "GraphicsEffects.h"


volatile struct{
	uint64_t InitialHeadersMax;
}Config;

volatile GraphicsEffectsUtils Utils;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Misc
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_WaterTexture(GPU_Texture* pGPU_Texture, LogicalDevice* pLogicalDevice, uint32_t Width, uint32_t Height, GraphicsFormat Format, AllocationType Type, uint32_t ThreadIndex)
{
	VkResult res = VK_SUCCESS;
	{
		VkImageCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		Info.pNext = NULL;
		Info.flags = NULL;
		Info.imageType = VK_IMAGE_TYPE_2D;
		Info.format = (VkFormat)Format;
		Info.extent.width = Width;
		Info.extent.height = Height;
		Info.extent.depth = 1;
		Info.mipLevels = 1;
		Info.arrayLayers = 1;
		Info.samples = VK_SAMPLE_COUNT_1_BIT;
		Info.tiling = VK_IMAGE_TILING_OPTIMAL;
		Info.usage = VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		Info.queueFamilyIndexCount = NULL;
		Info.pQueueFamilyIndices = NULL;
		Info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		if ((res = vkCreateImage(pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGPU_Texture->VkImage)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("Create_WaterTexture()", "vkCreateImage Failed, VkResult == ", res);
			return (TEXRESULT)(Failure);
		}
	}
	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(pLogicalDevice->VkLogicalDevice, pGPU_Texture->VkImage, &memRequirements);
	pGPU_Texture->Allocation = Graphics_Ref_GPUmalloc(pLogicalDevice, memRequirements, TargetMemory_Dst, Type, ThreadIndex);
	if (pGPU_Texture->Allocation.VkMemory == NULL)
	{
		Engine_Ref_FunctionError("Create_WaterTexture()", "Not Enough Space In GPU Memory!", NULL);
		return (TEXRESULT)(Failure);
	}

	if ((res = vkBindImageMemory(pLogicalDevice->VkLogicalDevice, pGPU_Texture->VkImage, pGPU_Texture->Allocation.VkMemory, pGPU_Texture->Allocation.Pointer)) != VK_SUCCESS)
	{
		Engine_Ref_FunctionError("Create_WaterTexture()", "vkBindImageMemory Failed, VkResult == ", res);
		return (TEXRESULT)(Failure);
	}
	{
		VkImageViewCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		Info.image = pGPU_Texture->VkImage;
		Info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		Info.format = (VkFormat)Format;

		Info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		Info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		Info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		Info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		Info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		Info.subresourceRange.baseMipLevel = 0;
		Info.subresourceRange.levelCount = 1;
		Info.subresourceRange.baseArrayLayer = 0;
		Info.subresourceRange.layerCount = 1;

		if ((res = vkCreateImageView(pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGPU_Texture->VkImageView)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("Create_WaterTexture()", "vkCreateImageView Failed, VkResult == ", res);
			return (TEXRESULT)(Failure);
		}
	}
	return (TEXRESULT)(Success);
}

unsigned char reverse(unsigned char n, size_t b){
	unsigned char rv = 0;
	for (size_t i = 0; i < b; ++i, n >>= 1) {
		rv = (rv << 1) | (n & 0x01);
	}
	return rv;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Destroy_WaterRenderHeader(RHeaderWaterRender* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	//every reinit
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);

	LogicalDevice* pLogicalDevice = pGraphicsWindow->pLogicalDevice;
	Graphics_Ref_GPUfree(pLogicalDevice, &pResourceHeader->AllocationBitReversedIndices);
	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->Textureh0k);
	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->TextureTwiddleFactors);
	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->Texturehkt_dy);
	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->Texturehkt_dx);
	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->Texturehkt_dz);
	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->TexturePingPong);
	if (pResourceHeader->VkShaderh0k != NULL)
		vkDestroyShaderModule(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderh0k, NULL);
	if (pResourceHeader->VkShaderTwiddleFactors != NULL)
		vkDestroyShaderModule(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderTwiddleFactors, NULL);
	if (pResourceHeader->VkShaderhkt != NULL)
		vkDestroyShaderModule(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderhkt, NULL);
	if (pResourceHeader->VkShaderButterfly != NULL)
		vkDestroyShaderModule(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderButterfly, NULL);
	if (pResourceHeader->VkShaderInversion != NULL)
		vkDestroyShaderModule(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderInversion, NULL);
	if (pResourceHeader->VkDescriptorSetLayouth0k != NULL)
		vkDestroyDescriptorSetLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorSetLayouth0k, NULL);
	if (pResourceHeader->VkDescriptorSetLayoutTwiddleFactors != NULL)
		vkDestroyDescriptorSetLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorSetLayoutTwiddleFactors, NULL);
	if (pResourceHeader->VkDescriptorSetLayouthkt != NULL)
		vkDestroyDescriptorSetLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorSetLayouthkt, NULL);
	if (pResourceHeader->VkDescriptorSetLayoutButterfly != NULL)
		vkDestroyDescriptorSetLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorSetLayoutButterfly, NULL);
	if (pResourceHeader->VkDescriptorSetLayoutInversion != NULL)
		vkDestroyDescriptorSetLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorSetLayoutInversion, NULL);
	if (pResourceHeader->VkPipelineLayouth0k != NULL)
		vkDestroyPipelineLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineLayouth0k, NULL);
	if (pResourceHeader->VkPipelineLayoutTwiddleFactors != NULL)
		vkDestroyPipelineLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineLayoutTwiddleFactors, NULL);
	if (pResourceHeader->VkPipelineLayouthkt != NULL)
		vkDestroyPipelineLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineLayouthkt, NULL);
	if (pResourceHeader->VkPipelineLayoutButterfly != NULL)
		vkDestroyPipelineLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineLayoutButterfly, NULL);
	if (pResourceHeader->VkPipelineLayoutInversion != NULL)
		vkDestroyPipelineLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineLayoutInversion, NULL);
	if (pResourceHeader->VkPipelineh0k != NULL)
		vkDestroyPipeline(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineh0k, NULL);
	if (pResourceHeader->VkPipelineTwiddleFactors != NULL)
		vkDestroyPipeline(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineTwiddleFactors, NULL);
	if (pResourceHeader->VkPipelinehkt != NULL)
		vkDestroyPipeline(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelinehkt, NULL);
	if (pResourceHeader->VkPipelineButterfly != NULL)
		vkDestroyPipeline(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineButterfly, NULL);
	if (pResourceHeader->VkPipelineInversion != NULL)
		vkDestroyPipeline(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineInversion, NULL);
	//if (pResourceHeader->VkDescriptorSeth0k != NULL)
	//	free(pResourceHeader->VkDescriptorSeth0k);
	//if (pResourceHeader->VkDescriptorSetTwiddleFactors != NULL)
	//	free(pResourceHeader->VkDescriptorSetTwiddleFactors);
	//if (pResourceHeader->VkDescriptorSethkt != NULL)
	//	free(pResourceHeader->VkDescriptorSethkt);
	//if (pResourceHeader->VkDescriptorSetButterfly != NULL)
	//	free(pResourceHeader->VkDescriptorSetButterfly);
	//if (pResourceHeader->VkDescriptorSetInversion != NULL)
	//	free(pResourceHeader->VkDescriptorSetInversion);
	if (pResourceHeader->VkDescriptorPoolWater != NULL)
		vkDestroyDescriptorPool(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorPoolWater, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ReCreate
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ReCreate_WaterRenderHeader(RHeaderWaterRender* pResourceHeader, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iGraphicsWindow) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_WaterRenderHeader()", "pResourceHeader->iGraphicsWindow Invalid");
		return;
	}
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iTextureTarget) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_WaterRenderHeader()", "pResourceHeader->iTextureTarget Invalid");
		return;
	}
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iNoise) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_WaterRenderHeader()", "pResourceHeader->iNoise Invalid");
		return;
	}
#endif
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
	RHeaderTexture* pTexture = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iTextureTarget);
	RHeaderTexture* pNoise = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iNoise);

	RHeaderImageSource* pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture->iImageSource);

#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pTexture->iImageSource) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_WaterRenderHeader()", "pTexture->iImageSource Invalid");
		return;
	}
	if (pImageSource->ImageData == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_WaterRenderHeader()", "pImageSource->ImageData == NULLPTR");
		return;
	}
#endif
	pImageSource->ImageData->Width = pResourceHeader->WaterResolution;
	pImageSource->ImageData->Height = pResourceHeader->WaterResolution;
	pImageSource->ImageData->Depth = 1;
	pImageSource->ImageData->Format = GraphicsFormat_R32G32B32A32_SFLOAT;
	pImageSource->ImageData->MipmapCount = 1;
	Object_Ref_ReCreate_ResourceHeader(pTexture->Header.Allocation, NULL, 0);

	TEXRESULT tres = Success;
	VkResult res = VK_SUCCESS;


	const SPIRV Shaderh0k[] = ComputeShaderh0k();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkShaderh0k, Shaderh0k, ComputeShaderh0kSize, "ReCreate_WaterRenderHeader()");
	const SPIRV ShaderTwiddleFactors[] = ComputeShaderTwiddleFactors();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkShaderTwiddleFactors, ShaderTwiddleFactors, ComputeShaderTwiddleFactorsSize, "ReCreate_WaterRenderHeader()");
	const SPIRV Shaderhkt[] = ComputeShaderhkt();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkShaderhkt, Shaderhkt, ComputeShaderhktSize, "ReCreate_WaterRenderHeader()");
	const SPIRV ShaderButterfly[] = ComputeShaderButterfly();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkShaderButterfly, ShaderButterfly, ComputeShaderButterflySize, "ReCreate_WaterRenderHeader()");
	const SPIRV ShaderInversion[] = ComputeShaderInversion();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkShaderInversion, ShaderInversion, ComputeShaderInversionSize, "ReCreate_WaterRenderHeader()");


	uint64_t log_2_N = (int)(log(pResourceHeader->WaterResolution) / log(2));

	if ((tres = Create_WaterTexture(&pResourceHeader->Textureh0k, pGraphicsWindow->pLogicalDevice, pResourceHeader->WaterResolution, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return;
	if ((tres = Create_WaterTexture(&pResourceHeader->Texturehkt_dy, pGraphicsWindow->pLogicalDevice, pResourceHeader->WaterResolution, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return;
	if ((tres = Create_WaterTexture(&pResourceHeader->Texturehkt_dx, pGraphicsWindow->pLogicalDevice, pResourceHeader->WaterResolution, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return;
	if ((tres = Create_WaterTexture(&pResourceHeader->Texturehkt_dz, pGraphicsWindow->pLogicalDevice, pResourceHeader->WaterResolution, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return;
	if ((tres = Create_WaterTexture(&pResourceHeader->TextureTwiddleFactors, pGraphicsWindow->pLogicalDevice, log_2_N, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return;
	if ((tres = Create_WaterTexture(&pResourceHeader->TexturePingPong, pGraphicsWindow->pLogicalDevice, pResourceHeader->WaterResolution, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//DescriptorLayout
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	{//Layout h0k
#define Bindingsh0kCount 2
		VkDescriptorSetLayoutBinding Bindings[Bindingsh0kCount];
		{
			Bindings[0].binding = 0;
			Bindings[0].descriptorCount = 1;
			Bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[0].pImmutableSamplers = NULL;
		}
		{
			Bindings[1].binding = 1;
			Bindings[1].descriptorCount = 1;
			Bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			Bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[1].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)Bindingsh0kCount;
		Info.pBindings = Bindings;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorSetLayouth0k)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return;
		}
	}
	{//Layout twiddlefactors
#define BindingsTwiddleFactorsCount 2
		VkDescriptorSetLayoutBinding Bindings[BindingsTwiddleFactorsCount];
		{
			Bindings[0].binding = 0;
			Bindings[0].descriptorCount = 1;
			Bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[0].pImmutableSamplers = NULL;
		}
		{
			Bindings[1].binding = 1;
			Bindings[1].descriptorCount = 1;
			Bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			Bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[1].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)BindingsTwiddleFactorsCount;
		Info.pBindings = Bindings;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorSetLayoutTwiddleFactors)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return;
		}
	}
	{//Layout hkt
#define BindingshktCount 4
		VkDescriptorSetLayoutBinding Bindings[BindingshktCount];
		{
			Bindings[0].binding = 0;
			Bindings[0].descriptorCount = 1;
			Bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[0].pImmutableSamplers = NULL;
		}
		{
			Bindings[1].binding = 1;
			Bindings[1].descriptorCount = 1;
			Bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[1].pImmutableSamplers = NULL;
		}
		{
			Bindings[2].binding = 2;
			Bindings[2].descriptorCount = 1;
			Bindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[2].pImmutableSamplers = NULL;
		}
		{
			Bindings[3].binding = 3;
			Bindings[3].descriptorCount = 1;
			Bindings[3].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[3].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[3].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)BindingshktCount;
		Info.pBindings = Bindings;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorSetLayouthkt)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return;
		}
	}
	{//Layout butterfly
#define BindingsButterflyCount 3
		VkDescriptorSetLayoutBinding Bindings[BindingsButterflyCount];
		{
			Bindings[0].binding = 0;
			Bindings[0].descriptorCount = 1;
			Bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[0].pImmutableSamplers = NULL;
		}
		{
			Bindings[1].binding = 1;
			Bindings[1].descriptorCount = 1;
			Bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[1].pImmutableSamplers = NULL;
		}
		{
			Bindings[2].binding = 2;
			Bindings[2].descriptorCount = 1;
			Bindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[2].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)BindingsButterflyCount;
		Info.pBindings = Bindings;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorSetLayoutButterfly)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return;
		}
	}
	{//Layout inversion
#define BindingsInversionCount 3
		VkDescriptorSetLayoutBinding Bindings[BindingsInversionCount];
		{
			Bindings[0].binding = 0;
			Bindings[0].descriptorCount = 1;
			Bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[0].pImmutableSamplers = NULL;
		}
		{
			Bindings[1].binding = 1;
			Bindings[1].descriptorCount = 1;
			Bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[1].pImmutableSamplers = NULL;
		}
		{
			Bindings[2].binding = 2;
			Bindings[2].descriptorCount = 1;
			Bindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[2].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)BindingsInversionCount;
		Info.pBindings = Bindings;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorSetLayoutInversion)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipeline Layouts
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{//layout h0k
		VkDescriptorSetLayout layouts[1] = { pResourceHeader->VkDescriptorSetLayouth0k };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkPipelineLayouth0k)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return;
		}
	}
	{//layout twiddlefactors
		VkDescriptorSetLayout layouts[1] = { pResourceHeader->VkDescriptorSetLayoutTwiddleFactors };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkPipelineLayoutTwiddleFactors)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return;
		}
	}
	{//layout hkt
		VkDescriptorSetLayout layouts[1] = { pResourceHeader->VkDescriptorSetLayouthkt };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkPipelineLayouthkt)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return;
		}
	}
	{//layout butterfly
		VkDescriptorSetLayout layouts[1] = { pResourceHeader->VkDescriptorSetLayoutButterfly };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkPipelineLayoutButterfly)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return;
		}
	}
	{//layout inversion
		VkDescriptorSetLayout layouts[1] = { pResourceHeader->VkDescriptorSetLayoutInversion };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkPipelineLayoutInversion)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipelines
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{//pipeline h0k
		VkComputePipelineCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pResourceHeader->VkShaderh0k;
		Info.stage.pName = "main";
		Info.layout = pResourceHeader->VkPipelineLayouth0k;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pResourceHeader->VkPipelineh0k)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return;
		}
	}
	{//pipeline TwiddleFactors
		VkComputePipelineCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pResourceHeader->VkShaderTwiddleFactors;
		Info.stage.pName = "main";
		Info.layout = pResourceHeader->VkPipelineLayoutTwiddleFactors;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pResourceHeader->VkPipelineTwiddleFactors)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return;
		}
	}
	{//pipeline hkt
		VkComputePipelineCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pResourceHeader->VkShaderhkt;
		Info.stage.pName = "main";
		Info.layout = pResourceHeader->VkPipelineLayouthkt;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pResourceHeader->VkPipelinehkt)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return;
		}
	}
	{//pipeline Butterfly
		VkComputePipelineCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pResourceHeader->VkShaderButterfly;
		Info.stage.pName = "main";
		Info.layout = pResourceHeader->VkPipelineLayoutButterfly;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pResourceHeader->VkPipelineButterfly)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return;
		}
	}
	{//pipeline Inversion
		VkComputePipelineCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pResourceHeader->VkShaderInversion;
		Info.stage.pName = "main";
		Info.layout = pResourceHeader->VkPipelineLayoutInversion;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pResourceHeader->VkPipelineInversion)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Sets
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{//pool
		uint32_t PoolSizesSize = 3;
		VkDescriptorPoolSize PoolSizes[3];

		PoolSizes[0].descriptorCount = 1;
		PoolSizes[0].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

		PoolSizes[1].descriptorCount = 1 + 1 + 4 + 3 + 3;
		PoolSizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;

		PoolSizes[2].descriptorCount = 1;
		PoolSizes[2].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

		VkDescriptorPoolCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		Info.maxSets = 5;
		Info.poolSizeCount = PoolSizesSize;
		Info.pPoolSizes = PoolSizes;
		if ((res = vkCreateDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorPoolWater)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_GraphicsWindowHeader()", "vkCreateDescriptorPool, VkResult == ", res);
			return;
		}
	}
	{//sets
		uint32_t layoutsSize = 5;
		VkDescriptorSetLayout layouts[5] = { pResourceHeader->VkDescriptorSetLayouth0k, pResourceHeader->VkDescriptorSetLayoutTwiddleFactors,
		pResourceHeader->VkDescriptorSetLayouthkt, pResourceHeader->VkDescriptorSetLayoutButterfly, pResourceHeader->VkDescriptorSetLayoutInversion };
		VkDescriptorSet sets[5];

		VkDescriptorSetAllocateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		Info.descriptorPool = pResourceHeader->VkDescriptorPoolWater;
		Info.descriptorSetCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pNext = NULL;
		if ((res = vkAllocateDescriptorSets(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, sets)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_GraphicsWindowHeader()", "vkAllocateDescriptorSets, VkResult == ", res);
			return;
		}
		pResourceHeader->VkDescriptorSeth0k = sets[0];
		pResourceHeader->VkDescriptorSetTwiddleFactors = sets[1];
		pResourceHeader->VkDescriptorSethkt = sets[2];
		pResourceHeader->VkDescriptorSetButterfly = sets[3];
		pResourceHeader->VkDescriptorSetInversion = sets[4];
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Updating Descriptor Sets
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{	
		VkMemoryRequirements requirements;
		requirements.size = AlignNumber(pResourceHeader->WaterResolution * sizeof(int), pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.minStorageBufferOffsetAlignment);
		requirements.alignment = pGraphicsWindow->pLogicalDevice->SrcBuffer.Alignment;
		requirements.memoryTypeBits = NULL;
		pResourceHeader->AllocationBitReversedIndices = Graphics_Ref_GPUmalloc(pGraphicsWindow->pLogicalDevice, requirements, TargetMemory_Src, AllocationType_Linear, ThreadIndex);

		int* targetbits = (int*)((void*)(((uint64_t)pGraphicsWindow->pLogicalDevice->SrcBufPointer + pResourceHeader->AllocationBitReversedIndices.Pointer)));
		for (int i = 0; i < pResourceHeader->WaterResolution; i++)
		{
			unsigned char x = reverse((unsigned char)i, 8);
			targetbits[i] = x;
		}
	}

	{//h0k
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Textureh0k.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSeth0k, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		ImageInfo.imageView = pNoise->GPU_Texture.VkImageView;
		ImageInfo.sampler = pNoise->GPU_Texture.VkSampler;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSeth0k, 1, 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, NULL, &ImageInfo);
	}
		
	{//TwiddleFactors
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->TextureTwiddleFactors.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetTwiddleFactors, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorBufferInfo BufferInfo;
		BufferInfo.buffer = pGraphicsWindow->pLogicalDevice->SrcBuffer.VkBuffer;
		BufferInfo.offset = pResourceHeader->AllocationBitReversedIndices.Pointer;
		BufferInfo.range = AlignNumber(pResourceHeader->WaterResolution * sizeof(int), pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.minStorageBufferOffsetAlignment);
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetTwiddleFactors, 1, 0, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &BufferInfo, NULL);
	}

	{//hkt
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Texturehkt_dy.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSethkt, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Texturehkt_dx.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSethkt, 1, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Texturehkt_dz.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSethkt, 2, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Textureh0k.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSethkt, 3, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	}

	{//butterfly
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->TextureTwiddleFactors.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetButterfly, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Texturehkt_dy.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetButterfly, 1, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->TexturePingPong.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetButterfly, 2, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	}

	{//inversion
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pTexture->GPU_Texture.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetInversion, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Texturehkt_dy.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetInversion, 1, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->TexturePingPong.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetInversion, 2, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Rendering
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	VkCommandPool VkCmdPool = NULL;
	VkCommandBuffer VkCmdBuffer = NULL;
	{
		VkCommandPoolCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		Info.queueFamilyIndex = pGraphicsWindow->pLogicalDevice->ComputeQueueFamilyIndex;
		Info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
		if ((res = vkCreateCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &VkCmdPool)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateCommandPool Failed, VkResult == ", res);
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
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkAllocateCommandBuffers Failed, VkResult == ", res);
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
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkBeginCommandBuffer Failed, VkResult == ", res);
			return;
		}
	}

	{//h0k
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pResourceHeader->Textureh0k.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = 0;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}
		vkCmdBindPipeline(VkCmdBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pResourceHeader->VkPipelineh0k);

		uint8_t pushconstantbuffer[sizeof(WaterPushConstants)];
		WaterPushConstants PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		glm_vec2_copy(pResourceHeader->FlowDirection, PushConstants.FlowDirection);
		PushConstants.WaterResolution = pResourceHeader->WaterResolution;
		PushConstants.WaterL = pResourceHeader->WaterL;
		PushConstants.WaterAmplitude = pResourceHeader->WaterAmplitude;
		PushConstants.WaterIntensity = pResourceHeader->WaterIntensity;
		PushConstants.Waterl = pResourceHeader->Waterl;
		PushConstants.Time = pResourceHeader->Time;
		PushConstants.ButterflyStage = 0;
		PushConstants.ButterflyDirection = 0;
		PushConstants.PingPongIndex = 0;

		memcpy(pushconstantbuffer, &PushConstants, sizeof(PushConstants));
		vkCmdPushConstants(VkCmdBuffer, pResourceHeader->VkPipelineLayouth0k, VK_SHADER_STAGE_COMPUTE_BIT, 0,
			pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &pushconstantbuffer);

		vkCmdBindDescriptorSets(VkCmdBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
			pResourceHeader->VkPipelineLayouth0k, 0, 1, &pResourceHeader->VkDescriptorSeth0k, 0, NULL);
		vkCmdDispatch(VkCmdBuffer, pResourceHeader->WaterResolution / 16, pResourceHeader->WaterResolution / 16, 1);
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pResourceHeader->Textureh0k.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}
	}
	{//twiddlefactors
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pResourceHeader->TextureTwiddleFactors.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = 0;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}

		vkCmdBindPipeline(VkCmdBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pResourceHeader->VkPipelineTwiddleFactors);

		uint8_t pushconstantbuffer[sizeof(WaterPushConstants)];
		WaterPushConstants PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		glm_vec2_copy(pResourceHeader->FlowDirection, PushConstants.FlowDirection);
		PushConstants.WaterResolution = pResourceHeader->WaterResolution;
		PushConstants.WaterL = pResourceHeader->WaterL;
		PushConstants.WaterAmplitude = pResourceHeader->WaterAmplitude;
		PushConstants.WaterIntensity = pResourceHeader->WaterIntensity;
		PushConstants.Waterl = pResourceHeader->Waterl;
		PushConstants.Time = pResourceHeader->Time;
		PushConstants.ButterflyStage = 0;
		PushConstants.ButterflyDirection = 0;
		PushConstants.PingPongIndex = 0;

		memcpy(pushconstantbuffer, &PushConstants, sizeof(PushConstants));
		vkCmdPushConstants(VkCmdBuffer, pResourceHeader->VkPipelineLayoutTwiddleFactors, VK_SHADER_STAGE_COMPUTE_BIT, 0,
			pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &pushconstantbuffer);

		vkCmdBindDescriptorSets(VkCmdBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
			pResourceHeader->VkPipelineLayoutTwiddleFactors, 0, 1, &pResourceHeader->VkDescriptorSetTwiddleFactors, 0, NULL);
		vkCmdDispatch(VkCmdBuffer, log_2_N, pResourceHeader->WaterResolution / 16, 1);
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pResourceHeader->TextureTwiddleFactors.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}
	}

	//end
	vkEndCommandBuffer(VkCmdBuffer);

	uint32_t QueueIndex = 0;
	{
		bool found = false;
		while (found == false)
		{
			for (size_t i = 0; i < pGraphicsWindow->pLogicalDevice->ComputeQueueFamilySize; i++)
			{
				if (Engine_Ref_TryLock_Mutex(pGraphicsWindow->pLogicalDevice->ComputeQueueMutexes[i]) == Success)
				{
					QueueIndex = i;
					found = true;
					break;
				}
			}
		}
	}
	VkQueue Queue = NULL;
	vkGetDeviceQueue(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->pLogicalDevice->ComputeQueueFamilyIndex, QueueIndex, &Queue);

	VkSubmitInfo SubmitInfo;
	memset(&SubmitInfo, NULL, sizeof(SubmitInfo));
	SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.commandBufferCount = (uint32_t)1;
	SubmitInfo.pCommandBuffers = &VkCmdBuffer;

	if ((res = vkQueueSubmit(Queue, 1, &SubmitInfo, VK_NULL_HANDLE)) != VK_SUCCESS)
	{
		Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkQueueSubmit Failed, VkResult == ", res);
		return;
	}

	vkQueueWaitIdle(Queue);
	Engine_Ref_Unlock_Mutex(pGraphicsWindow->pLogicalDevice->ComputeQueueMutexes[QueueIndex]);

	vkFreeCommandBuffers(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VkCmdPool, 1, &VkCmdBuffer);
	vkDestroyCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VkCmdPool, NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Packers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Pack_WaterRenderHeader(const RHeaderWaterRender* pResourceHeader, RHeaderWaterRender* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedResourceHeader->AllocationBitReversedIndices, NULL, sizeof(pCopiedResourceHeader->AllocationBitReversedIndices));

		memset(&pCopiedResourceHeader->Textureh0k, NULL, sizeof(pCopiedResourceHeader->Textureh0k));
		memset(&pCopiedResourceHeader->TextureTwiddleFactors, NULL, sizeof(pCopiedResourceHeader->TextureTwiddleFactors));
		memset(&pCopiedResourceHeader->Texturehkt_dy, NULL, sizeof(pCopiedResourceHeader->Texturehkt_dy));
		memset(&pCopiedResourceHeader->Texturehkt_dx, NULL, sizeof(pCopiedResourceHeader->Texturehkt_dx));
		memset(&pCopiedResourceHeader->Texturehkt_dz, NULL, sizeof(pCopiedResourceHeader->Texturehkt_dz));
		memset(&pCopiedResourceHeader->TexturePingPong, NULL, sizeof(pCopiedResourceHeader->TexturePingPong));

		memset(&pCopiedResourceHeader->VkShaderh0k, NULL, sizeof(pCopiedResourceHeader->VkShaderh0k));
		memset(&pCopiedResourceHeader->VkShaderTwiddleFactors, NULL, sizeof(pCopiedResourceHeader->VkShaderTwiddleFactors));
		memset(&pCopiedResourceHeader->VkShaderhkt, NULL, sizeof(pCopiedResourceHeader->VkShaderhkt));
		memset(&pCopiedResourceHeader->VkShaderButterfly, NULL, sizeof(pCopiedResourceHeader->VkShaderButterfly));
		memset(&pCopiedResourceHeader->VkShaderInversion, NULL, sizeof(pCopiedResourceHeader->VkShaderInversion));

		memset(&pCopiedResourceHeader->VkDescriptorSetLayouth0k, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSetLayouth0k));
		memset(&pCopiedResourceHeader->VkDescriptorSetLayoutTwiddleFactors, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSetLayoutTwiddleFactors));
		memset(&pCopiedResourceHeader->VkDescriptorSetLayouthkt, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSetLayouthkt));
		memset(&pCopiedResourceHeader->VkDescriptorSetLayoutButterfly, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSetLayoutButterfly));
		memset(&pCopiedResourceHeader->VkDescriptorSetLayoutInversion, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSetLayoutInversion));

		memset(&pCopiedResourceHeader->VkPipelineLayouth0k, NULL, sizeof(pCopiedResourceHeader->VkPipelineLayouth0k));
		memset(&pCopiedResourceHeader->VkPipelineLayoutTwiddleFactors, NULL, sizeof(pCopiedResourceHeader->VkPipelineLayoutTwiddleFactors));
		memset(&pCopiedResourceHeader->VkPipelineLayouthkt, NULL, sizeof(pCopiedResourceHeader->VkPipelineLayouthkt));
		memset(&pCopiedResourceHeader->VkPipelineLayoutButterfly, NULL, sizeof(pCopiedResourceHeader->VkPipelineLayoutButterfly));
		memset(&pCopiedResourceHeader->VkPipelineLayoutInversion, NULL, sizeof(pCopiedResourceHeader->VkPipelineLayoutInversion));

		memset(&pCopiedResourceHeader->VkPipelineh0k, NULL, sizeof(pCopiedResourceHeader->VkPipelineh0k));
		memset(&pCopiedResourceHeader->VkPipelineTwiddleFactors, NULL, sizeof(pCopiedResourceHeader->VkPipelineTwiddleFactors));
		memset(&pCopiedResourceHeader->VkPipelinehkt, NULL, sizeof(pCopiedResourceHeader->VkPipelinehkt));
		memset(&pCopiedResourceHeader->VkPipelineButterfly, NULL, sizeof(pCopiedResourceHeader->VkPipelineButterfly));
		memset(&pCopiedResourceHeader->VkPipelineInversion, NULL, sizeof(pCopiedResourceHeader->VkPipelineInversion));


		memset(&pCopiedResourceHeader->VkDescriptorPoolWater, NULL, sizeof(pCopiedResourceHeader->VkDescriptorPoolWater));

		memset(&pCopiedResourceHeader->VkDescriptorSeth0k, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSeth0k));
		memset(&pCopiedResourceHeader->VkDescriptorSetTwiddleFactors, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSetTwiddleFactors));
		memset(&pCopiedResourceHeader->VkDescriptorSethkt, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSethkt));
		memset(&pCopiedResourceHeader->VkDescriptorSetButterfly, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSetButterfly));
		memset(&pCopiedResourceHeader->VkDescriptorSetInversion, NULL, sizeof(pCopiedResourceHeader->VkDescriptorSetInversion));
	}
	else
	{
	
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Unpackers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UnPack_WaterRenderHeader(const RHeaderWaterRender* pResourceHeader, RHeaderWaterRender* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	ReCreate_WaterRenderHeader(pCopiedResourceHeader, ThreadIndex);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_WaterRenderHeader(RHeaderWaterRender* pResourceHeader, RHeaderWaterRenderCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_WaterRenderHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->iGraphicsWindow = pCreateInfo->pGraphicsWindow->Header.Allocation;
		pResourceHeader->iTextureTarget = pCreateInfo->pTextureTarget->Header.Allocation;
		pResourceHeader->WaterResolution = pCreateInfo->WaterResolution;
		pResourceHeader->WaterL = pCreateInfo->WaterL;
		pResourceHeader->WaterAmplitude = pCreateInfo->WaterAmplitude;
		pResourceHeader->WaterIntensity = pCreateInfo->WaterIntensity;
		pResourceHeader->Waterl = pCreateInfo->Waterl;

		glm_vec2_copy(pCreateInfo->FlowDirection, pResourceHeader->FlowDirection);

		pResourceHeader->iNoise = pCreateInfo->pNoise->Header.Allocation;

		ReCreate_WaterRenderHeader(pResourceHeader, ThreadIndex);
	}
	*pAllocationSize = sizeof(RHeaderWaterRender);
	return (TEXRESULT)(Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Graphics Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawSignature_Water(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex)
{
	for (size_t i = 0; i < Utils.RHeaderWaterRenderBuffer.Size;)
	{
		RHeaderWaterRender* pResourceHeader = (RHeaderWaterRender*)&Utils.RHeaderWaterRenderBuffer.Buffer[i];
		if (pResourceHeader->Header.AllocationSize != NULL && pResourceHeader->Header.Allocation.Identifier == (uint32_t)GraphicsEffectsHeader_WaterRender)
		{
			RHeaderGraphicsWindow* pGraphicsWindow1 = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
			if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pGraphicsWindow1->Header.Allocation) == Success)
			{
				pResourceHeader->Time = ((EngineUtils*)EngineRes.pUtils)->CurrentTime;
				RHeaderTexture* pTexture = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iTextureTarget);
				RHeaderImageSource* pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture->iImageSource);

				VkResult res = VK_SUCCESS;

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Rendering
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				uint8_t PingPongIndex = 0;
				{//hkt
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->Texturehkt_dy.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = 0;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
							0,
							0, NULL,
							0, NULL,
							1, &Barrier
						);
					}
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->Texturehkt_dx.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = 0;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
							0,
							0, NULL,
							0, NULL,
							1, &Barrier
						);
					}
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->Texturehkt_dz.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = 0;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
							0,
							0, NULL,
							0, NULL,
							1, &Barrier
						);
					}

					vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pResourceHeader->VkPipelinehkt);

					uint8_t pushconstantbuffer[sizeof(WaterPushConstants)];
					WaterPushConstants PushConstants;
					memset(&PushConstants, 0, sizeof(PushConstants));
					glm_vec2_copy(pResourceHeader->FlowDirection, PushConstants.FlowDirection);
					PushConstants.WaterResolution = pResourceHeader->WaterResolution;
					PushConstants.WaterL = pResourceHeader->WaterL;
					PushConstants.WaterAmplitude = pResourceHeader->WaterAmplitude;
					PushConstants.WaterIntensity = pResourceHeader->WaterIntensity;
					PushConstants.Waterl = pResourceHeader->Waterl;
					PushConstants.Time = pResourceHeader->Time;
					PushConstants.ButterflyStage = 0;
					PushConstants.ButterflyDirection = 0;
					PushConstants.PingPongIndex = 0;

					memcpy(pushconstantbuffer, &PushConstants, sizeof(PushConstants));
					vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->VkPipelineLayouthkt, VK_SHADER_STAGE_COMPUTE_BIT, 0,
						pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &pushconstantbuffer);

					vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
						pResourceHeader->VkPipelineLayouthkt, 0, 1, &pResourceHeader->VkDescriptorSethkt, 0, NULL);
					vkCmdDispatch(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->WaterResolution / 16, pResourceHeader->WaterResolution / 16, 1);

					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->Texturehkt_dy.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
							0,
							0, NULL,
							0, NULL,
							1, &Barrier
						);
					}
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->Texturehkt_dx.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
							0,
							0, NULL,
							0, NULL,
							1, &Barrier
						);
					}
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->Texturehkt_dz.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
							0,
							0, NULL,
							0, NULL,
							1, &Barrier
						);
					}
				}
				{//butterfly		
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->TexturePingPong.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = 0;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
							0,
							0, NULL,
							0, NULL,
							1, &Barrier
						);
					}

					vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pResourceHeader->VkPipelineButterfly);
					vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
						pResourceHeader->VkPipelineLayoutButterfly, 0, 1, &pResourceHeader->VkDescriptorSetButterfly, 0, NULL);

					uint64_t log_2_N = (int)(log(pResourceHeader->WaterResolution) / log(2));
					for (size_t i = 0; i < log_2_N; i++)
					{
						for (size_t i1 = 0; i1 < 2; i1++)
						{					
							{
								VkImageMemoryBarrier Barrier;
								Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
								Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
								Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
								Barrier.image = pResourceHeader->Texturehkt_dy.VkImage;
								Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
								Barrier.subresourceRange.baseMipLevel = 0;
								Barrier.subresourceRange.levelCount = 1;
								Barrier.subresourceRange.baseArrayLayer = 0;
								Barrier.subresourceRange.layerCount = 1;
								Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
								Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
								switch (PingPongIndex)
								{
								case 0:
									Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
									Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
									break;
								case 1:
									Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
									Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
									break;
								}
								Barrier.pNext = NULL;


								vkCmdPipelineBarrier(
									pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
									VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
									0,
									0, NULL,
									0, NULL,
									1, &Barrier
								);
							}
							{
								VkImageMemoryBarrier Barrier;
								Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
								Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
								Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
								Barrier.image = pResourceHeader->TexturePingPong.VkImage;
								Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
								Barrier.subresourceRange.baseMipLevel = 0;
								Barrier.subresourceRange.levelCount = 1;
								Barrier.subresourceRange.baseArrayLayer = 0;
								Barrier.subresourceRange.layerCount = 1;
								Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
								Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
								switch (PingPongIndex)
								{
								case 0:
									Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
									Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
									break;
								case 1:
									Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
									Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
									break;
								}
								Barrier.pNext = NULL;


								vkCmdPipelineBarrier(
									pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
									VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
									0,
									0, NULL,
									0, NULL,
									1, &Barrier
								);
							}

							

							uint8_t pushconstantbuffer[sizeof(WaterPushConstants)];
							WaterPushConstants PushConstants;
							memset(&PushConstants, 0, sizeof(PushConstants));
							glm_vec2_copy(pResourceHeader->FlowDirection, PushConstants.FlowDirection);
							PushConstants.WaterResolution = pResourceHeader->WaterResolution;
							PushConstants.WaterL = pResourceHeader->WaterL;
							PushConstants.WaterAmplitude = pResourceHeader->WaterAmplitude;
							PushConstants.WaterIntensity = pResourceHeader->WaterIntensity;
							PushConstants.Waterl = pResourceHeader->Waterl;
							PushConstants.Time = pResourceHeader->Time;
							PushConstants.ButterflyStage = i;
							PushConstants.ButterflyDirection = i1;
							PushConstants.PingPongIndex = PingPongIndex;

							memcpy(pushconstantbuffer, &PushConstants, sizeof(PushConstants));
							vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->VkPipelineLayouthkt, VK_SHADER_STAGE_COMPUTE_BIT, 0,
								pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &pushconstantbuffer);

							vkCmdDispatch(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->WaterResolution / 16, pResourceHeader->WaterResolution / 16, 1);

							PingPongIndex++;
							PingPongIndex %= 2;

							{
								VkImageMemoryBarrier Barrier;
								Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
								Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
								Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
								Barrier.image = pResourceHeader->Texturehkt_dy.VkImage;
								Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
								Barrier.subresourceRange.baseMipLevel = 0;
								Barrier.subresourceRange.levelCount = 1;
								Barrier.subresourceRange.baseArrayLayer = 0;
								Barrier.subresourceRange.layerCount = 1;
								Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
								Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
								switch (PingPongIndex)
								{
								case 0:
									Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
									Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
									break;
								case 1:
									Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
									Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
									break;
								}
								Barrier.pNext = NULL;


								vkCmdPipelineBarrier(
									pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
									VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
									0,
									0, NULL,
									0, NULL,
									1, &Barrier
								);
							}
							{
								VkImageMemoryBarrier Barrier;
								Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
								Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
								Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
								Barrier.image = pResourceHeader->TexturePingPong.VkImage;
								Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
								Barrier.subresourceRange.baseMipLevel = 0;
								Barrier.subresourceRange.levelCount = 1;
								Barrier.subresourceRange.baseArrayLayer = 0;
								Barrier.subresourceRange.layerCount = 1;
								Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
								Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
								switch (PingPongIndex)
								{
								case 0:
									Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
									Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
									break;
								case 1:
									Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
									Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
									break;
								}
								Barrier.pNext = NULL;


								vkCmdPipelineBarrier(
									pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
									VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
									0,
									0, NULL,
									0, NULL,
									1, &Barrier
								);
							}
						}
					}
				}
				{//inversion
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pTexture->GPU_Texture.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
							0,
							0, NULL,
							0, NULL,
							1, &Barrier
						);
					}

					vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pResourceHeader->VkPipelineInversion);

					uint8_t pushconstantbuffer[sizeof(WaterPushConstants)];
					WaterPushConstants PushConstants;
					memset(&PushConstants, 0, sizeof(PushConstants));
					glm_vec2_copy(pResourceHeader->FlowDirection, PushConstants.FlowDirection);
					PushConstants.WaterResolution = pResourceHeader->WaterResolution;
					PushConstants.WaterL = pResourceHeader->WaterL;
					PushConstants.WaterAmplitude = pResourceHeader->WaterAmplitude;
					PushConstants.WaterIntensity = pResourceHeader->WaterIntensity;
					PushConstants.Waterl = pResourceHeader->Waterl;
					PushConstants.Time = pResourceHeader->Time;
					PushConstants.ButterflyStage = 0;
					PushConstants.ButterflyDirection = 0;
					PushConstants.PingPongIndex = PingPongIndex;

					memcpy(pushconstantbuffer, &PushConstants, sizeof(PushConstants));
					vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->VkPipelineLayouth0k, VK_SHADER_STAGE_COMPUTE_BIT, 0,
						pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &pushconstantbuffer);

					vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
						pResourceHeader->VkPipelineLayoutInversion, 0, 1, &pResourceHeader->VkDescriptorSetInversion, 0, NULL);
					vkCmdDispatch(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->WaterResolution / 16, pResourceHeader->WaterResolution / 16, 1);

					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
						Barrier.image = pTexture->GPU_Texture.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
							0,
							0, NULL,
							0, NULL,
							1, &Barrier
						);
					}
				}
			}

			i += pResourceHeader->Header.AllocationSize;
		}
		else
		{
			i++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Update_GraphicsEffects()
{


}

TEXRESULT Initialise_GraphicsEffects()
{
	memset(&Utils, NULL, sizeof(Utils));
	memset(&Config, NULL, sizeof(Config));

	//Config
	Config.InitialHeadersMax = 512;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Signatures
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderWaterRenderSig.Buffer = &Utils.RHeaderWaterRenderBuffer;
	Utils.RHeaderWaterRenderSig.ByteLength = sizeof(RHeaderWaterRender);
	Utils.RHeaderWaterRenderSig.Identifier = (uint32_t)GraphicsEffectsHeader_WaterRender;
	Utils.RHeaderWaterRenderSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_WaterRenderHeader;
	Utils.RHeaderWaterRenderSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_WaterRenderHeader;
	Utils.RHeaderWaterRenderSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_WaterRenderHeader;
	Utils.RHeaderWaterRenderSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_WaterRenderHeader;
	Utils.RHeaderWaterRenderSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_WaterRenderHeader;
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderWaterRenderBuffer, Config.InitialHeadersMax);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderWaterRenderSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Effects
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.WaterSig.Identifier = (uint32_t)GraphicsEffectsEffect_Water;
	//Utils.WaterSig.Constructor = (Create_GraphicsEffectTemplate*)&Create_Water;
	//Utils.WaterSig.ReConstructor = (ReCreate_GraphicsEffectTemplate*)&ReCreate_Water;
	//Utils.WaterSig.Destructor = (Destroy_GraphicsEffectTemplate*)&Destroy_Water;
	//Utils.WaterSig.Packer = (Pack_GraphicsEffectTemplate*)&Pack_Text;
	//Utils.WaterSig.UnPacker = (UnPack_GraphicsEffectTemplate*)&UnPack_Text;
	//Utils.WaterSig.Update = (Update_GraphicsEffectTemplate*)&Update_Text;
	//Utils.WaterSig.UpdateSignature = &UpdateSignature_Water;
	//Utils.WaterSig.Draw = (Draw_GraphicsEffectTemplate*)&Draw_Text;
	Utils.WaterSig.DrawSignature = &DrawSignature_Water;
	Utils.WaterSig.SignatureGPUBuffersSize = 0;
	Graphics_Effects_Ref_Register_GraphicsEffectSignature(&Utils.WaterSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//other
	///////////////////////////////////////////////////////////////////////////////////////////////

	return (TEXRESULT)(Success);
}

void Destroy_GraphicsEffects()
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//Signatures
	///////////////////////////////////////////////////////////////////////////////////////////////

	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderWaterRenderBuffer);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderWaterRenderSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//other
	///////////////////////////////////////////////////////////////////////////////////////////////

	Graphics_Effects_Ref_DeRegister_GraphicsEffectSignature(&Utils.WaterSig);

	memset(&Utils, NULL, sizeof(Utils));
	memset(&Config, NULL, sizeof(Config));
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
	Graphics_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);

	//Config
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"GraphicsEffects::InitialHeadersMax"), &Config.InitialHeadersMax, 1, sizeof(Config.InitialHeadersMax));

	//Resources
	ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData((void*)"GraphicsEffects::Utils"), &GraphicsEffectsRes.pUtils, &Utils);

	//Functions
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"GraphicsEffects::Initialise_GraphicsEffects"), &GraphicsEffectsRes.pInitialise_GraphicsEffects, &Initialise_GraphicsEffects, Construct, Single_Thread, 10.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"GraphicsEffects::Destroy_GraphicsEffects"), &GraphicsEffectsRes.pDestroy_GraphicsEffects, &Destroy_GraphicsEffects, Destruct, Single_Thread, 100.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"GraphicsEffects::Update_GraphicsEffects"), &GraphicsEffectsRes.pUpdate_GraphicsEffects, &Update_GraphicsEffects, EveryFrame, Single_Thread, 10.0f, 0, NULL);
}
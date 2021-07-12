#pragma once
//C
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//Third-Party
#include <atomic\atomic.h>
//Ours
#include "Extension.h"
#include "Object.h"

volatile struct {
	uint64_t InitialParametersMax;
}Config;

volatile ObjectUtils Utils;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Check Allocation Validatey Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Tests is allocation is valid or not.
* Returns Success when allocation is valid. Failure otherwise.
* @param Allocation, allocation of the desired object to get pointer of.
* @note Thread Safe always.
* @note Externally Synchronized.
*/
TEXRESULT Get_ObjectAllocationValidity(ObjectAllocation Allocation)
{
	return (Allocation.Identifier != 0) ? Success : Failure;
}
/*
* Added in 1.0.0
* Tests is allocation is valid or not.
* Returns Success when allocation is valid. Failure otherwise.
* @param Allocation, allocation of the desired object to get pointer of.
* @note Thread Safe always.
* @note Externally Synchronized.
*/
TEXRESULT Get_ResourceHeaderAllocationValidity(ResourceHeaderAllocation Allocation)
{
	return (Allocation.Identifier != 0) ? Success : Failure;
}
/*
* Added in 1.0.0
* Tests is allocation is valid or not.
* Returns Success when allocation is valid. Failure otherwise.
* @param Allocation, allocation of the desired object to get pointer of.
* @note Thread Safe always.
* @note Externally Synchronized.
*/
TEXRESULT Get_ElementAllocationValidity(ElementAllocation Allocation)
{
	return (Allocation.Identifier != 0) ? Success : Failure;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Compare Allocation Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Returns Success when allocations are identical. Failure otherwise.
* @param Allocation0, first allocation to compare agaisnt.
* @param Allocation1, second allocation to compare agaisnt.
* @note Thread Safe always.
* @note Externally Synchronized.
*/
TEXRESULT Compare_ObjectAllocation(ObjectAllocation Allocation0, ObjectAllocation Allocation1)
{
	return (((Allocation0.Pointer == Allocation1.Pointer) && (Allocation0.Identifier == Allocation1.Identifier))) ? Success : Failure;
}
/*
* Added in 1.0.0
* Returns Success when allocations are identical. Failure otherwise.
* @param Allocation0, first allocation to compare agaisnt.
* @param Allocation1, second allocation to compare agaisnt.
* @note Thread Safe always.
* @note Externally Synchronized.
*/
TEXRESULT Compare_ResourceHeaderAllocation(ResourceHeaderAllocation Allocation0, ResourceHeaderAllocation Allocation1)
{
	return (((Allocation0.Pointer == Allocation1.Pointer) && (Allocation0.Identifier == Allocation1.Identifier))) ? Success : Failure;
}
/*
* Added in 1.0.0
* Returns Success when allocations are identical. Failure otherwise.
* @param Allocation0, first allocation to compare agaisnt.
* @param Allocation1, second allocation to compare agaisnt.
* @note Thread Safe always.
* @note Externally Synchronized.
*/
TEXRESULT Compare_ElementAllocation(ElementAllocation Allocation0, ElementAllocation Allocation1)
{
	return (((Allocation0.Pointer == Allocation1.Pointer) && (Allocation0.Identifier == Allocation1.Identifier))) ? Success : Failure;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Find Signature Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Uses Identifier to find the signature that the object is associated with.
* @param Identifier, desired signature identifier to find.
* @param ppSignature is a pointer to a pointer of a signature to return.
* @param pBufferIndex is a pointer to a bufferindex value to return.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Find_ObjectSignature(ObjectIdentifier Identifier, ObjectSignature** ppSignature, ObjectBufferIndex* pBufferIndex)
{
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Find_ObjectSignature()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif

	for (uint64_t i = 0; i < Utils.ObjectSignaturesSize; i++)
	{
		if (Utils.ObjectSignatures[i]->Identifier == Identifier)
		{
			if (ppSignature != NULL)
				*ppSignature = Utils.ObjectSignatures[i];
			if (pBufferIndex != NULL)
				*pBufferIndex = i;
			return (TEXRESULT)(Success);
		}
	}
	*ppSignature = NULL;
	*pBufferIndex = NULL;
	Engine_Ref_ArgsError("Find_ObjectSignature()", "Identifier Invalid");
	return (TEXRESULT)(Invalid_Parameter | Failure);
}
/*
* Added in 1.0.0
* Uses Identifier to find the signature that the object is associated with.
* @param Identifier, desired signature identifier to find.
* @param ppSignature is a pointer to a pointer of a signature to return.
* @param pBufferIndex is a pointer to a bufferindex value to return.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Find_ResourceHeaderSignature(ResourceHeaderIdentifier Identifier, ResourceHeaderSignature** ppSignature, ResourceHeaderBufferIndex* pBufferIndex)
{
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Find_ResourceHeaderSignature()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	for (uint64_t i = 0; i < Utils.ResourceHeaderSignaturesSize; i++)
	{
		if (Utils.ResourceHeaderSignatures[i]->Identifier == Identifier)
		{
			if (ppSignature != NULL)
				*ppSignature = Utils.ResourceHeaderSignatures[i];
			if (pBufferIndex != NULL)
				*pBufferIndex = i;
			return (TEXRESULT)(Success);
		}
	}
	*ppSignature = NULL;
	*pBufferIndex = NULL;
	Engine_Ref_ArgsError("Find_ResourceHeaderSignature()", "Identifier Invalid");
	return (TEXRESULT)(Invalid_Parameter | Failure);
}
/*
* Added in 1.0.0
* Uses Identifier to find the signature that the object is associated with.
* @param Identifier, desired signature identifier to find.
* @param ppSignature is a pointer to a pointer of a signature to return.
* @param pBufferIndex is a pointer to a bufferindex value to return.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Find_ElementSignature(ElementIdentifier Identifier, ElementSignature** ppSignature, ElementBufferIndex* pBufferIndex)
{
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Find_ElementSignature()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	for (uint64_t i = 0; i < Utils.ElementSignaturesSize; i++)
	{
		if (Utils.ElementSignatures[i]->Identifier == Identifier)
		{
			if (ppSignature != NULL)
				*ppSignature = Utils.ElementSignatures[i];
			if (pBufferIndex != NULL)
				*pBufferIndex = i;
			return (TEXRESULT)(Success);
		}
	}
	*ppSignature = NULL;
	*pBufferIndex = NULL;
	Engine_Ref_ArgsError("Find_ElementSignature()", "Identifier Invalid");
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Get Pointer Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Gets a pointer from an allocation.
* Returns Success when allocation is valid. Failure otherwise.
* @param Allocation, allocation of the desired object to get pointer of.
* @note Thread Safe always.
* @note Externally Synchronized.
*/
Object* Get_ObjectPointer(ObjectAllocation Allocation)
{
#ifndef NDEBUG
	if (Allocation.Identifier == NULL)
	{
		Engine_Ref_ArgsError("Get_ObjectPointer()", "Identifier == NULL, This is invalid");
		return NULL;
	}
#endif
	ObjectSignature* pSignature = NULL;
	ObjectBufferIndex BufferIndex = 0;
	Find_ObjectSignature(Allocation.Identifier, &pSignature, &BufferIndex);

	if (BufferIndex == NULL)
	{
		Engine_Ref_ArgsError("Get_ObjectPointer()", "BufferIndex == NULL, Identifier Invalid.");
		return NULL;
	}
	else
	{
		return &Utils.ObjectSignatures[BufferIndex]->Buffer->Buffer[Allocation.Pointer];
	}
}
/*
* Added in 1.0.0
* Gets a pointer from an allocation.
* Returns Success when allocation is valid. Failure otherwise.
* @param Allocation, allocation of the desired object to get pointer of.
* @note Thread Safe always.
* @note Externally Synchronized.
*/
ResourceHeader* Get_ResourceHeaderPointer(ResourceHeaderAllocation Allocation)
{
#ifndef NDEBUG
	if (Allocation.Identifier == NULL)
	{
		Engine_Ref_ArgsError("Get_ResourceHeaderPointer()", "Identifier == NULL, This is invalid");
		return NULL;
	}
#endif
	ResourceHeaderSignature* pSignature = NULL;
	ResourceHeaderBufferIndex BufferIndex = 0;
	Find_ResourceHeaderSignature(Allocation.Identifier, &pSignature, &BufferIndex);

	if (BufferIndex == NULL)
	{
		Engine_Ref_ArgsError("Get_ResourceHeaderPointer()", "BufferIndex == NULL, Identifier Invalid.");
		return NULL;
	}
	else
	{
		return &Utils.ResourceHeaderSignatures[BufferIndex]->Buffer->Buffer[Allocation.Pointer];
	}
}
/*
* Added in 1.0.0
* Gets a pointer from an allocation.
* Returns Success when allocation is valid. Failure otherwise.
* @param Allocation, allocation of the desired object to get pointer of.
* @note Thread Safe always.
* @note Externally Synchronized.
*/
Element* Get_ElementPointer(ElementAllocation Allocation)
{
#ifndef NDEBUG
	if (Allocation.Identifier == NULL)
	{
		Engine_Ref_ArgsError("Get_ElementPointer()", "Identifier == NULL, This is invalid");
		return NULL;
	}
#endif
	ElementSignature* pSignature = NULL;
	ElementBufferIndex BufferIndex = 0;
	Find_ElementSignature(Allocation.Identifier, &pSignature, &BufferIndex);

	if (BufferIndex == NULL)
	{
		Engine_Ref_ArgsError("Get_ElementPointer()", "BufferIndex == NULL, Identifier Invalid.");
		return NULL;
	}
	else
	{
		return &Utils.ElementSignatures[BufferIndex]->Buffer->Buffer[Allocation.Pointer];
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Arena Allocater Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Creates a object arena allocater.
* @param pAllocater pointer to the allocater to create.
* @param StartPtr offset from the start of the gpu buffer to reserve for this arena, arena size = (EndPtr - StartPtr)
* @param EndPtr offset from the start of the gpu buffer to reserve for this arena, arena size = (EndPtr - StartPtr)
* @note Always Thread safe.
* @note Externally Synchronized.
*/
TEXRESULT Create_ArenaAllocater(ArenaAllocater* pAllocater, uint64_t StartPtr, uint64_t EndPtr)
{
#ifndef NDEBUG
	if (pAllocater == NULL)
	{
		Engine_Ref_ArgsError("Create_ArenaAllocater()", "pAllocater == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Create_Mutex(pAllocater->mutex, MutexType_Plain);
	pAllocater->StartPtr = StartPtr;
	pAllocater->EndPtr = EndPtr;
	pAllocater->Size = (pAllocater->EndPtr - pAllocater->StartPtr);
	return Success;
}
/*
* Added in 1.0.0
* Destroys a object arena allocater.
* @param pAllocater pointer to the allocater to destroy.
* @note Always Thread safe.
* @note Externally Synchronized.
*/
void Destroy_ArenaAllocater(ArenaAllocater* pAllocater)
{
#ifndef NDEBUG
	if (pAllocater == NULL)
	{
		Engine_Ref_ArgsError("Destroy_ArenaAllocater()", "pAllocater == NULLPTR");
		return;
	}
#endif
	Engine_Ref_Destroy_Mutex(pAllocater->mutex);

	pAllocater->StartPtr = 0;
	pAllocater->EndPtr = 0;
	pAllocater->Size = 0;
	pAllocater->PrevPointer = 0;
	memset(pAllocater, 0, sizeof(*pAllocater));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Construct Buffer Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Creates a buffer for objects to be stored, to be used in a signature.
* @param pBuffer pointer to a buffer object to initialize.
* @param Size is in allocation chunks. (1 Object == 1 chunk).
* @note Thread Safe always.
* @note Externally Synchronized.
*/
TEXRESULT Create_ObjectBuffer(ObjectBuffer* pBuffer, uint64_t InitialSize)
{
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Create_ObjectBuffer()", "pBuffer == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (InitialSize == NULL)
	{
		Engine_Ref_ArgsError("Create_ObjectBuffer()", "InitialSize == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	memset(pBuffer, 0, sizeof(*pBuffer));
	pBuffer->Buffer = (Object*)calloc(InitialSize, sizeof(*pBuffer->Buffer));
	pBuffer->Size = InitialSize;

	pBuffer->ArenaAllocaters = calloc(((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads, sizeof(*pBuffer->ArenaAllocaters));
	pBuffer->Indexes = calloc(((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads, sizeof(*pBuffer->Indexes));
	if (pBuffer->ArenaAllocaters == NULL || pBuffer->Indexes == NULL)
	{
		Engine_Ref_FunctionError("Create_ObjectBuffer()", "Out Of Memory.", pBuffer->ArenaAllocaters);
		return (TEXRESULT)(Out_Of_Memory_Result);
	}

	Create_ArenaAllocater(&pBuffer->ArenaAllocaters[0], 0, InitialSize);
	for (size_t i = 1; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		Create_ArenaAllocater(&pBuffer->ArenaAllocaters[i], 0, 0);
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Creates a buffer for objects to be stored, to be used in a signature.
* @param pBuffer pointer to a buffer object to initialize.
* @param Size is in allocation chunks. (1 Object == 1 chunk).
* @note Thread Safe always.
* @note Externally Synchronized.
*/
TEXRESULT Create_ResourceHeaderBuffer(ResourceHeaderBuffer* pBuffer, uint64_t InitialSize)
{
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Create_ResourceHeaderBuffer()", "pBuffer == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (InitialSize == NULL)
	{
		Engine_Ref_ArgsError("Create_ResourceHeaderBuffer()", "InitialSize == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	memset(pBuffer, 0, sizeof(*pBuffer));
	pBuffer->Buffer = (ResourceHeader*)calloc(InitialSize, sizeof(*pBuffer->Buffer));
	pBuffer->Size = InitialSize;

	pBuffer->ArenaAllocaters = calloc(((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads, sizeof(*pBuffer->ArenaAllocaters));
	pBuffer->Indexes = calloc(((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads, sizeof(*pBuffer->Indexes));
	if (pBuffer->ArenaAllocaters == NULL || pBuffer->Indexes == NULL)
	{
		Engine_Ref_FunctionError("Create_ResourceHeaderBuffer()", "Out Of Memory.", pBuffer->ArenaAllocaters);
		return (TEXRESULT)(Out_Of_Memory_Result);
	}

	Create_ArenaAllocater(&pBuffer->ArenaAllocaters[0], 0, InitialSize);
	for (size_t i = 1; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		Create_ArenaAllocater(&pBuffer->ArenaAllocaters[i], 0, 0);
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Creates a buffer for objects to be stored, to be used in a signature.
* @param pBuffer pointer to a buffer object to initialize.
* @param Size is in allocation chunks. (1 Object == 1 chunk).
* @note Thread Safe always.
* @note Externally Synchronized.
*/
TEXRESULT Create_ElementBuffer(ElementBuffer* pBuffer, uint64_t InitialSize)
{
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Create_ElementBuffer()", "pBuffer == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (InitialSize == NULL)
	{
		Engine_Ref_ArgsError("Create_ElementBuffer()", "InitialSize == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	memset(pBuffer, 0, sizeof(*pBuffer));
	pBuffer->Buffer = (Element*)calloc(InitialSize, sizeof(*pBuffer->Buffer));
	pBuffer->Size = InitialSize;

	pBuffer->ArenaAllocaters = calloc(((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads, sizeof(*pBuffer->ArenaAllocaters));
	pBuffer->Indexes = calloc(((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads, sizeof(*pBuffer->Indexes));
	if (pBuffer->ArenaAllocaters == NULL || pBuffer->Indexes == NULL)
	{
		Engine_Ref_FunctionError("Create_ElementBuffer()", "Out Of Memory.", pBuffer->ArenaAllocaters);
		return (TEXRESULT)(Out_Of_Memory_Result);
	}

	Create_ArenaAllocater(&pBuffer->ArenaAllocaters[0], 0, InitialSize);
	for (size_t i = 1; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		Create_ArenaAllocater(&pBuffer->ArenaAllocaters[i], 0, 0);
	return (TEXRESULT)(Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Resizes Buffer Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Resizes specified buffer to newsize.
* doesnt compact, there will be excess space in the vector and still elements cut off when downsizing.
* resize functions are super expensive and shouldnt be done often.
* remember downsizing cuts everything off and makes alot of errors if any pointers point towards invalid memory
* @param pBuffer pointer to a buffer object to resize.
* @param Size is in allocation chunks. (1 Object == 1 chunk).
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Resize_ObjectBuffer(ObjectBuffer* pBuffer, uint64_t NewSize)
{
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Resize_ObjectBuffer()", "pBuffer == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (NewSize == NULL)
	{
		Engine_Ref_ArgsError("Resize_ObjectBuffer()", "NewSize == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif

	for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
	{
		Engine_Ref_Lock_Mutex(pBuffer->ArenaAllocaters[i].mutex);
	}

	Resize_Array((void**)&pBuffer->Buffer, pBuffer->Size, NewSize, sizeof(*pBuffer->Buffer));
	pBuffer->Size = NewSize;

	for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
	{
		Engine_Ref_Unlock_Mutex(pBuffer->ArenaAllocaters[i].mutex);
	}
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Resizes specified buffer to newsize.
* doesnt compact, there will be excess space in the vector and still elements cut off when downsizing.
* resize functions are super expensive and shouldnt be done often.
* remember downsizing cuts everything off and makes alot of errors if any pointers point towards invalid memory
* @param pBuffer pointer to a buffer object to resize.
* @param Size is in allocation chunks. (1 Object == 1 chunk).
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Resize_ResourceHeaderBuffer(ResourceHeaderBuffer* pBuffer, uint64_t NewSize)
{
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Resize_ResourceHeaderBuffer()", "pBuffer == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (NewSize == NULL)
	{
		Engine_Ref_ArgsError("Resize_ResourceHeaderBuffer()", "NewSize == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
	{
		Engine_Ref_Lock_Mutex(pBuffer->ArenaAllocaters[i].mutex);
	}

	Resize_Array((void**)&pBuffer->Buffer, pBuffer->Size, NewSize, sizeof(*pBuffer->Buffer));
	pBuffer->Size = NewSize;

	for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
	{
		Engine_Ref_Unlock_Mutex(pBuffer->ArenaAllocaters[i].mutex);
	}
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Resizes specified buffer to newsize.
* doesnt compact, there will be excess space in the vector and still elements cut off when downsizing.
* resize functions are super expensive and shouldnt be done often.
* remember downsizing cuts everything off and makes alot of errors if any pointers point towards invalid memory
* @param pBuffer pointer to a buffer object to resize.
* @param Size is in allocation chunks. (1 Object == 1 chunk).
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Resize_ElementBuffer(ElementBuffer* pBuffer, uint64_t NewSize)
{
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Resize_ElementBuffer()", "pBuffer == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (NewSize == NULL)
	{
		Engine_Ref_ArgsError("Resize_ElementBuffer()", "NewSize == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
	{
		Engine_Ref_Lock_Mutex(pBuffer->ArenaAllocaters[i].mutex);
	}

	Resize_Array((void**)&pBuffer->Buffer, pBuffer->Size, NewSize, sizeof(*pBuffer->Buffer));
	pBuffer->Size = NewSize;

	for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
	{
		Engine_Ref_Unlock_Mutex(pBuffer->ArenaAllocaters[i].mutex);
	}
	return (TEXRESULT)(Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Find Allocation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Finds allocation in the specified buffer of specified size.
* @param pBuffer pointer to a buffer object to find allocation from.
* @param Type of buffer.
* @param RequiredSize in chunks.
* @param pReturnPointer returned index in buffer in chunks of a space larger then RequiredSize.
* @note Thread safe.
* @note Internally Synchronized.
*/
TEXRESULT Find_Allocation(pObjectBuffer pBuffer, ObjectBufferType Type, uint64_t RequiredSize, uint64_t* pReturnPointer, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (pReturnPointer == NULL)
	{
		Engine_Ref_ArgsError("Find_Allocation()", "pReturnPointer == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (RequiredSize == NULL)
	{
		Engine_Ref_ArgsError("Find_Allocation()", "RequiredSize == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	GenericBuffer* pGenericBuffer = NULL;
	switch (Type)
	{
	case ObjectBufferType_Object:
#ifndef NDEBUG
		if (pBuffer.Object == NULL)
		{
			Engine_Ref_ArgsError("Find_Allocation()", "Type is ObjectBufferType_Object but pBuffer.Object == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pGenericBuffer = pBuffer.Object;
		break;
	case ObjectBufferType_ResourceHeader:
#ifndef NDEBUG
		if (pBuffer.ResourceHeader == NULL)
		{
			Engine_Ref_ArgsError("Find_Allocation()", "Type is ObjectBufferType_ResourceHeader but pBuffer.ResourceHeader == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pGenericBuffer = pBuffer.ResourceHeader;
		break;
	case ObjectBufferType_Element:
#ifndef NDEBUG
		if (pBuffer.Element == NULL)
		{
			Engine_Ref_ArgsError("Find_Allocation()", "Type is ObjectBufferType_Element but pBuffer.Element == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pGenericBuffer = pBuffer.Element;
		break;
	default:
		Engine_Ref_ArgsError("Find_Allocation()", "Type Invalid.");
		return (TEXRESULT)(Invalid_Parameter | Failure);
		break;
	}
	ArenaAllocater* pArenaAllocater = NULL;
	if (Engine_Ref_TryLock_Mutex(pGenericBuffer->ArenaAllocaters[pGenericBuffer->Indexes[ThreadIndex]].mutex) != Success)
	{
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		{
			if (Engine_Ref_TryLock_Mutex(pGenericBuffer->ArenaAllocaters[i].mutex) == Success)
			{
				pArenaAllocater = &pGenericBuffer->ArenaAllocaters[i];
				pGenericBuffer->Indexes[ThreadIndex] = i;
				break;
			}
		}
	}
	else
	{
		pArenaAllocater = &pGenericBuffer->ArenaAllocaters[pGenericBuffer->Indexes[ThreadIndex]];
	}
	if (pArenaAllocater == NULL)
	{
		Engine_Ref_FunctionError("Find_Allocation()", "Arena Allocater could not be found. ", pArenaAllocater);
		return Failure;
	}

	//dynamic halfing
	if (pArenaAllocater->Size == 0)
	{
		Engine_Ref_FunctionError("Find_Allocation()", "HALFING", pArenaAllocater);
		//take half of largest mutex remaining capacity and assign to this arena allocater.
		ArenaAllocater* pArenaAllocaterLargest = &pGenericBuffer->ArenaAllocaters[0];
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
			if (pGenericBuffer->ArenaAllocaters[i].Size > pArenaAllocaterLargest->Size)
				pArenaAllocaterLargest = &pGenericBuffer->ArenaAllocaters[i];

		Engine_Ref_Lock_Mutex(pArenaAllocaterLargest->mutex);

		uint64_t pointer = 0;
		switch (Type)
		{
		case ObjectBufferType_Object:
			for (size_t i = 0; i < pArenaAllocaterLargest->Size;)
			{
				Object* pObject = (Object*)&pBuffer.Object->Buffer[i];
				if (pObject->Header.AllocationSize != NULL)
				{
					pointer = i + pObject->Header.AllocationSize;
					i += pObject->Header.AllocationSize;
				}
				else
				{
					i++;
				}
			}
			break;
		case ObjectBufferType_ResourceHeader:
			for (size_t i = 0; i < pArenaAllocaterLargest->Size;)
			{
				ResourceHeader* pResourceHeader = (ResourceHeader*)&pBuffer.ResourceHeader->Buffer[i];
				if (pResourceHeader->Header.AllocationSize != NULL)
				{
					pointer = i + pResourceHeader->Header.AllocationSize;
					i += pResourceHeader->Header.AllocationSize;
				}
				else
				{
					i++;
				}
			}
			break;
		case ObjectBufferType_Element:
			for (size_t i = 0; i < pArenaAllocaterLargest->Size;)
			{
				Element* pElement = (Element*)&pBuffer.Element->Buffer[i];
				if (pElement->Header.AllocationSize != NULL)
				{
					pointer = i + pElement->Header.AllocationSize;
					i += pElement->Header.AllocationSize;
				}
				else
				{
					i++;
				}
			}
			break;
		}
		uint64_t size = (pointer < (pArenaAllocaterLargest->Size / 2)) ? (pArenaAllocaterLargest->Size / 2) : (pArenaAllocaterLargest->Size - (pointer));

		pArenaAllocater->StartPtr = pArenaAllocaterLargest->EndPtr - size;
		pArenaAllocater->EndPtr = pArenaAllocaterLargest->EndPtr;
		pArenaAllocater->Size = pArenaAllocater->EndPtr - pArenaAllocater->StartPtr;

		//pArenaAllocaterLargest->StartPtr = ;
		pArenaAllocaterLargest->EndPtr = pArenaAllocaterLargest->EndPtr - size;
		pArenaAllocaterLargest->Size = pArenaAllocaterLargest->EndPtr - pArenaAllocaterLargest->StartPtr;

		Engine_Ref_Unlock_Mutex(pArenaAllocaterLargest->mutex);
	}

	uint64_t ResetCount = 0;
	uint64_t FoundChunksCount = 0;
	switch (Type)
	{
	case ObjectBufferType_Object:
		while (FoundChunksCount != RequiredSize)
		{
			FoundChunksCount = pBuffer.Object->Buffer[pArenaAllocater->PrevPointer + pArenaAllocater->StartPtr].Header.AllocationSize == NULL ? FoundChunksCount + 1 : 0;
			pArenaAllocater->PrevPointer++;
			if (pArenaAllocater->PrevPointer > pArenaAllocater->Size)
			{
				pArenaAllocater->PrevPointer = 0;
				ResetCount++;
				if (ResetCount > 1)
				{
					Engine_Ref_FunctionError("Find_Allocation()", "Not Enough Space In Array, Resize Array ", NULL);
					return (TEXRESULT)(Resize_Array_Result | Failure);
				}
			}
		}
		break;
	case ObjectBufferType_ResourceHeader:
		while (FoundChunksCount != RequiredSize)
		{
			FoundChunksCount = pBuffer.ResourceHeader->Buffer[pArenaAllocater->PrevPointer + pArenaAllocater->StartPtr].Header.AllocationSize == NULL ? FoundChunksCount + 1 : 0;
			pArenaAllocater->PrevPointer++;
			if (pArenaAllocater->PrevPointer > pArenaAllocater->Size)
			{
				pArenaAllocater->PrevPointer = 0;
				ResetCount++;
				if (ResetCount > 1)
				{
					Engine_Ref_FunctionError("Find_Allocation()", "Not Enough Space In Array, Resize Array ", NULL);
					return (TEXRESULT)(Resize_Array_Result | Failure);
				}
			}
		}
		break;
	case ObjectBufferType_Element:
		while (FoundChunksCount != RequiredSize)
		{
			FoundChunksCount = pBuffer.Element->Buffer[pArenaAllocater->PrevPointer + pArenaAllocater->StartPtr].Header.AllocationSize == NULL ? FoundChunksCount + 1 : 0;
			pArenaAllocater->PrevPointer++;
			if (pArenaAllocater->PrevPointer > pArenaAllocater->Size)
			{
				pArenaAllocater->PrevPointer = 0;
				ResetCount++;
				if (ResetCount > 1)
				{
					Engine_Ref_FunctionError("Find_Allocation()", "Not Enough Space In Array, Resize Array ", NULL);
					return (TEXRESULT)(Resize_Array_Result | Failure);
				}
			}
		}
		break;
	}
	*pReturnPointer = (pArenaAllocater->PrevPointer - RequiredSize) + pArenaAllocater->StartPtr;
	Engine_Ref_Unlock_Mutex(pArenaAllocater->mutex);
	return (TEXRESULT)(Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Create Instance Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Creates an instance of an Object to be used for multithread safety.
* @param Allocation refrencing the desired Object to create instance of.
* @param ppReturn pointer to a pointer of the resulting instance. (non malloced)
* @note Externally Synchronized.
*/
TEXRESULT CreateInstance_Object(ObjectAllocation Allocation, ObjectInstance* pReturn, uint32_t ThreadIndex)
{
	Object* pObject = Get_ObjectPointer(Allocation);

	TEXRESULT res = Success;
	uint64_t Pointer = 0;
	pObjectBuffer pBuffer;
	memset(&pBuffer, 0, sizeof(pBuffer));
	pBuffer.Object = &Utils.InternalObjectBuffer;
	if ((res = Find_Allocation(pBuffer, ObjectBufferType_Object, pObject->Header.AllocationSize, &Pointer, ThreadIndex)) != Success)
	{
		Engine_Ref_FunctionError("CreateInstance_Object()", "Find_Allocation() Failed, TEXRESULT == ", res);
		return res;
	}
	pReturn->Pointer = Pointer;
	pReturn->pInstance = &Utils.InternalObjectBuffer.Buffer[Pointer];

#ifdef OBJECT_MUTEX
	Engine_Ref_Lock_Mutex(pObject->Header.mutex);
#endif
	for (size_t i = 0; i < DelayedInstanceSize; i++)
	{
		if (pObject->Header.pDelayedInstances[i].Latest == 1)
		{
			Object* pTarget = (pObject->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pObject->Header.pDelayedInstances[ThreadIndex].Pointer] : pObject;
			memcpy(pReturn->pInstance, pTarget, sizeof(*pTarget) * pTarget->Header.AllocationSize);
			break;
		}
	}
#ifdef OBJECT_MUTEX
	Engine_Ref_Unlock_Mutex(pObject->Header.mutex);
#endif
	return Success;
}
/*
* Added in 1.0.0
* Creates an instance of an ResourceHeader to be used for multithread safety.
* @param Allocation refrencing the desired ResourceHeader to create instance of.
* @param ppReturn pointer to a pointer of the resulting instance. (non malloced)
* @note Externally Synchronized.
*/
TEXRESULT CreateInstance_ResourceHeader(ResourceHeaderAllocation Allocation, ResourceHeaderInstance* pReturn, uint32_t ThreadIndex)
{
	ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation);

	TEXRESULT res = Success;
	uint64_t Pointer = 0;
	pObjectBuffer pBuffer;
	memset(&pBuffer, 0, sizeof(pBuffer));
	pBuffer.ResourceHeader = &Utils.InternalResourceHeaderBuffer;
	if ((res = Find_Allocation(pBuffer, ObjectBufferType_ResourceHeader, pResourceHeader->Header.AllocationSize, &Pointer, ThreadIndex)) != Success)
	{
		Engine_Ref_FunctionError("CreateInstance_ResourceHeader()", "Find_Allocation() Failed, TEXRESULT == ", res);
		return res;
	}
	pReturn->Pointer = Pointer;
	pReturn->pInstance = &Utils.InternalResourceHeaderBuffer.Buffer[Pointer];
#ifdef OBJECT_MUTEX
	Engine_Ref_Lock_Mutex(pResourceHeader->Header.mutex);
#endif
	for (size_t i = 0; i < DelayedInstanceSize; i++)
	{
		if (pResourceHeader->Header.pDelayedInstances[i].Latest == 1)
		{
			ResourceHeader* pTarget = (pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX) ? &Utils.InternalResourceHeaderBuffer.Buffer[pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer] : pResourceHeader;
			memcpy(pReturn->pInstance, pTarget, sizeof(*pTarget) * pTarget->Header.AllocationSize);
			break;
		}
	}
#ifdef OBJECT_MUTEX
	Engine_Ref_Unlock_Mutex(pResourceHeader->Header.mutex);
#endif
	return Success;
}
/*
* Added in 1.0.0
* Creates an instance of an Element to be used for multithread safety.
* @param Allocation refrencing the desired Element to create instance of.
* @param ppReturn pointer to a pointer of the resulting instance. (non malloced)
* @note Externally Synchronized.
*/
TEXRESULT CreateInstance_Element(ElementAllocation Allocation, ElementInstance* pReturn, uint32_t ThreadIndex)
{
	Element* pElement = Get_ElementPointer(Allocation);

	TEXRESULT res = Success;
	uint64_t Pointer = 0;
	pObjectBuffer pBuffer;
	memset(&pBuffer, 0, sizeof(pBuffer));
	pBuffer.Element = &Utils.InternalElementBuffer;
	if ((res = Find_Allocation(pBuffer, ObjectBufferType_Element, pElement->Header.AllocationSize, &Pointer, ThreadIndex)) != Success)
	{
		Engine_Ref_FunctionError("CreateInstance_Element()", "Find_Allocation() Failed, TEXRESULT == ", res);
		return res;
	}
	pReturn->Pointer = Pointer;
	pReturn->pInstance = &Utils.InternalElementBuffer.Buffer[Pointer];
#ifdef OBJECT_MUTEX
	Engine_Ref_Lock_Mutex(pElement->Header.mutex);
#endif
	for (size_t i = 0; i < DelayedInstanceSize; i++)
	{
		if (pElement->Header.pDelayedInstances[i].Latest == 1)
		{
			Element* pTarget = (pElement->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX) ? &Utils.InternalElementBuffer.Buffer[pElement->Header.pDelayedInstances[ThreadIndex].Pointer] : pElement;
			memcpy(pReturn->pInstance, pTarget, sizeof(*pTarget) * pTarget->Header.AllocationSize);
			break;
		}
	}
#ifdef OBJECT_MUTEX
	Engine_Ref_Unlock_Mutex(pElement->Header.mutex);
#endif
	return Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Construct Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Allocates and calls construct on an object from CreateInfo.Identifier Signature.
* if CreateInfo.name = null it will be defaulted.
* @param pAllocation pointer to allocation to return.
* @param CreateInfo of the object.
* @param pCreateInfo is specialized createinfo for the signature.
* @note Thread safe.
* @note Internally Synchronized.
*/
TEXRESULT Create_Object(ObjectAllocation* pAllocation, ObjectCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex)
{
	ObjectSignature* pObjectSignature = NULL;
	ObjectBufferIndex BufferIndex = 0;
	Find_ObjectSignature(CreateInfo.Identifier, &pObjectSignature, &BufferIndex);
#ifndef NDEBUG
	if (pAllocation == NULL)
	{
		Engine_Ref_ArgsError("Create_Object()", "pAllocation == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (BufferIndex == NULL)
	{
		Engine_Ref_ArgsError("Create_Object()", "BufferIndex == NULL, No Associated Signature Was Found For The Identifier");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pObjectSignature == NULL)
	{
		Engine_Ref_ArgsError("Create_Object()", "pObjectSignature == NULL, No Associated Signature Was Found For The Identifier");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pObjectSignature->Buffer == NULL)
	{
		Engine_Ref_ObjectError("Create_Object()", "pObjectSignature", &pObjectSignature, "pObjectSignature.Buffer == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pObjectSignature->ByteLength == NULL)
	{
		Engine_Ref_ObjectError("Create_Object()", "pObjectSignature", &pObjectSignature, "pObjectSignature.ByteLength == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pObjectSignature->Identifier == NULL)
	{
		Engine_Ref_ObjectError("Create_Object()", "pObjectSignature", &pObjectSignature, "pObjectSignature.Identifer == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	Object* pObject = NULL;
	uint64_t RequiredSizeBytes = NULL;
	if (pObjectSignature->Constructor != NULL)
	{
		Create_ObjectTemplate* pFunction = *pObjectSignature->Constructor;
		if ((tres = pFunction(NULL, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	uint64_t RequiredSizeChunks = (RequiredSizeBytes != NULL) ?
		RequiredSizeBytes / sizeof(Object) + ((RequiredSizeBytes % sizeof(Object)) != 0) :
		pObjectSignature->ByteLength / sizeof(Object) + ((pObjectSignature->ByteLength % sizeof(Object)) != 0);
	uint64_t Pointer = 0;
	pObjectBuffer pBuffer;
	memset(&pBuffer, 0, sizeof(pBuffer));
	pBuffer.Object = pObjectSignature->Buffer;
	if ((tres = Find_Allocation(pBuffer, ObjectBufferType_Object, RequiredSizeChunks, &Pointer, ThreadIndex)) != Success)
	{
		Engine_Ref_FunctionError("Create_Object()", "Find_Allocation() Failed, TEXRESULT == ", tres);
		return tres;
	}
	pObject = &pObjectSignature->Buffer->Buffer[Pointer];
	memset(pObject, 0, sizeof(Object) * RequiredSizeChunks);
	pObject->Header.AllocationSize = RequiredSizeChunks;
	pObject->Header.Allocation.Pointer = Pointer;
	pObject->Header.Allocation.Identifier = CreateInfo.Identifier;
#ifdef OBJECT_MUTEX
	Engine_Ref_Create_Mutex(pObject->Header.mutex, MutexType_Plain);
#endif
	for (size_t i = 0; i < DelayedInstanceSize; i++)
	{
		pObject->Header.pDelayedInstances[i].Pointer = UINT32_MAX;
		pObject->Header.pDelayedInstances[i].Latest = 1;
	}
	if (CreateInfo.Name != NULL)
		pObject->Header.Name = (UTF8*)CopyData((void*)CreateInfo.Name);
	else
	{
		UTF8 TempBuffer[12 + 65 + 65 + 1];
		memset(TempBuffer, 0, 12 + 65 + 65 + 1);
		sprintf((char*)TempBuffer, "Object_%i_%i", pObject->Header.Allocation.Identifier, pObject->Header.Allocation.Pointer);
		pObject->Header.Name = (UTF8*)CopyData((void*)TempBuffer);
	}
	if (pObjectSignature->Constructor != NULL)
	{
		Create_ObjectTemplate* pFunction = *pObjectSignature->Constructor;
		if ((tres = pFunction(pObject, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	*pAllocation = pObject->Header.Allocation;
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Allocates and calls construct on an object from CreateInfo.Identifier Signature.
* if CreateInfo.name = null it will be defaulted.
* @param pAllocation pointer to allocation to return.
* @param CreateInfo of the object.
* @param pCreateInfo is specialized createinfo for the signature.
* @note Thread safe.
* @note Internally Synchronized.
*/
TEXRESULT Create_ResourceHeader(ResourceHeaderAllocation* pAllocation, ResourceHeaderCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex)
{
	ResourceHeaderSignature* pResourceHeaderSignature = NULL;
	ResourceHeaderBufferIndex BufferIndex = 0;
	Find_ResourceHeaderSignature(CreateInfo.Identifier, &pResourceHeaderSignature, &BufferIndex);
#ifndef NDEBUG
	if (pAllocation == NULL)
	{
		Engine_Ref_ArgsError("Create_ResourceHeader()", "pAllocation == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (BufferIndex == NULL)
	{
		Engine_Ref_ArgsError("Create_ResourceHeader()", "BufferIndex == NULL, No Associated Signature Was Found For The Identifier");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pResourceHeaderSignature == NULL)
	{
		Engine_Ref_ArgsError("Create_ResourceHeader()", "pResourceHeaderSignature == NULL, No Associated Signature Was Found For The Identifier");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pResourceHeaderSignature->Buffer == NULL)
	{
		Engine_Ref_ObjectError("Create_ResourceHeader()", "pResourceHeaderSignature", &pResourceHeaderSignature, "pResourceHeaderSignature.Buffer == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pResourceHeaderSignature->ByteLength == NULL)
	{
		Engine_Ref_ObjectError("Create_ResourceHeader()", "pResourceHeaderSignature", &pResourceHeaderSignature, "pResourceHeaderSignature.ByteLength == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pResourceHeaderSignature->Identifier == NULL)
	{
		Engine_Ref_ObjectError("Create_ResourceHeader()", "pResourceHeaderSignature", &pResourceHeaderSignature, "pResourceHeaderSignature.Identifer == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	ResourceHeader* pResourceHeader = NULL;
	uint64_t RequiredSizeBytes = NULL;
	if (pResourceHeaderSignature->Constructor != NULL)
	{
		Create_ResourceHeaderTemplate* pFunction = *pResourceHeaderSignature->Constructor;
		if ((tres = pFunction(NULL, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	uint64_t RequiredSizeChunks = (RequiredSizeBytes != NULL) ?
		RequiredSizeBytes / sizeof(ResourceHeader) + ((RequiredSizeBytes % sizeof(ResourceHeader)) != 0) :
		pResourceHeaderSignature->ByteLength / sizeof(ResourceHeader) + ((pResourceHeaderSignature->ByteLength % sizeof(ResourceHeader)) != 0);
	uint64_t Pointer = 0;
	pObjectBuffer pBuffer;
	memset(&pBuffer, 0, sizeof(pBuffer));
	pBuffer.ResourceHeader = pResourceHeaderSignature->Buffer;
	if ((tres = Find_Allocation(pBuffer, ObjectBufferType_ResourceHeader, RequiredSizeChunks, &Pointer, ThreadIndex)) != Success)
	{
		Engine_Ref_FunctionError("Create_ResourceHeader()", "Find_Allocation() Failed, TEXRESULT == ", tres);
		return tres;
	}
	pResourceHeader = &pResourceHeaderSignature->Buffer->Buffer[Pointer];
	memset(pResourceHeader, 0, sizeof(ResourceHeader) * RequiredSizeChunks);
	pResourceHeader->Header.AllocationSize = RequiredSizeChunks;
	pResourceHeader->Header.Allocation.Pointer = Pointer;
	pResourceHeader->Header.Allocation.Identifier = CreateInfo.Identifier;
#ifdef OBJECT_MUTEX
	Engine_Ref_Create_Mutex(pResourceHeader->Header.mutex, MutexType_Plain);
#endif
	for (size_t i = 0; i < DelayedInstanceSize; i++)
	{
		pResourceHeader->Header.pDelayedInstances[i].Pointer = UINT32_MAX;
		pResourceHeader->Header.pDelayedInstances[i].Latest = 1;
	}
	if (CreateInfo.Name != NULL)
		pResourceHeader->Header.Name = (UTF8*)CopyData((void*)CreateInfo.Name);
	else
	{
		UTF8 TempBuffer[16 + 65 + 65 + 1];
		memset(TempBuffer, 0, 16 + 65 + 65 + 1);
		sprintf((char*)TempBuffer, "ResourceHeader_%i_%i", pResourceHeader->Header.Allocation.Identifier, pResourceHeader->Header.Allocation.Pointer);
		pResourceHeader->Header.Name = (UTF8*)CopyData((void*)TempBuffer);
	}
	if (pResourceHeaderSignature->Constructor != NULL)
	{
		Create_ResourceHeaderTemplate* pFunction = *pResourceHeaderSignature->Constructor;
		if ((tres = pFunction(pResourceHeader, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	*pAllocation = pResourceHeader->Header.Allocation;
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Allocates and calls construct on an object from CreateInfo.Identifier Signature.
* if CreateInfo.name = null it will be defaulted.
* @param pAllocation pointer to allocation to return.
* @param CreateInfo of the object.
* @param pCreateInfo is specialized createinfo for the signature.
* @note Thread safe.
* @note Internally Synchronized.
*/
TEXRESULT Create_Element(ElementAllocation* pAllocation, ElementCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex)
{
	ElementSignature* pElementSignature = NULL;
	ElementBufferIndex BufferIndex = 0;
	Find_ElementSignature(CreateInfo.Identifier, &pElementSignature, &BufferIndex);
#ifndef NDEBUG
	if (pAllocation == NULL)
	{
		Engine_Ref_ArgsError("Create_Element()", "pAllocation == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (BufferIndex == NULL)
	{
		Engine_Ref_ArgsError("Create_Element()", "BufferIndex == NULL, No Associated Signature Was Found For The Identifier");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pElementSignature == NULL)
	{
		Engine_Ref_ArgsError("Create_Element()", "pElementSignature == NULL, No Associated Signature Was Found For The Identifier");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pElementSignature->Buffer == NULL)
	{
		Engine_Ref_ObjectError("Create_Element()", "pElementSignature", &pElementSignature, "pElementSignature.Buffer == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pElementSignature->ByteLength == NULL)
	{
		Engine_Ref_ObjectError("Create_Element()", "pElementSignature", &pElementSignature, "pElementSignature.ByteLength == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pElementSignature->Identifier == NULL)
	{
		Engine_Ref_ObjectError("Create_Element()", "pElementSignature", &pElementSignature, "pElementSignature.Identifer == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	Element* pElement = NULL;
	uint64_t RequiredSizeBytes = NULL;
	if (pElementSignature->Constructor != NULL)
	{
		Create_ElementTemplate* pFunction = *pElementSignature->Constructor;
		if ((tres = pFunction(NULL, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	uint32_t RequiredSizeChunks = (RequiredSizeBytes != NULL) ?
		RequiredSizeBytes / sizeof(Element) + ((RequiredSizeBytes % sizeof(Element)) != 0) :
		pElementSignature->ByteLength / sizeof(Element) + ((pElementSignature->ByteLength % sizeof(Element)) != 0);
	uint64_t Pointer = 0;
	pObjectBuffer pBuffer;
	memset(&pBuffer, 0, sizeof(pBuffer));
	pBuffer.Element = pElementSignature->Buffer;
	if ((tres = Find_Allocation(pBuffer, ObjectBufferType_Element, RequiredSizeChunks, &Pointer, ThreadIndex)) != Success)
	{
		Engine_Ref_FunctionError("Create_Element()", "Find_Allocation() Failed, TEXRESULT == ", tres);
		return tres;
	}
	pElement = &pElementSignature->Buffer->Buffer[Pointer];
	memset(pElement, 0, sizeof(Element) * RequiredSizeChunks);
	pElement->Header.AllocationSize = RequiredSizeChunks;
	pElement->Header.Allocation.Pointer = Pointer;
	pElement->Header.Allocation.Identifier = CreateInfo.Identifier;
#ifdef OBJECT_MUTEX
	Engine_Ref_Create_Mutex(pElement->Header.mutex, MutexType_Plain);
#endif
	for (size_t i = 0; i < DelayedInstanceSize; i++)
	{
		pElement->Header.pDelayedInstances[i].Pointer = UINT32_MAX;
		pElement->Header.pDelayedInstances[i].Latest = 1;
	}
	if (CreateInfo.Name != NULL)
		pElement->Header.Name = (UTF8*)CopyData((void*)CreateInfo.Name);
	else
	{
		UTF8 TempBuffer[9 + 65 + 65 + 1];
		memset(TempBuffer, 0, 9 + 65 + 65 + 1);
		sprintf((char*)TempBuffer, "Element_%i_%i", pElement->Header.Allocation.Identifier, pElement->Header.Allocation.Pointer);
		pElement->Header.Name = (UTF8*)CopyData((void*)TempBuffer);
	}
	if (pElementSignature->Constructor != NULL)
	{
		Create_ElementTemplate* pFunction = *pElementSignature->Constructor;
		if ((tres = pFunction(pElement, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	*pAllocation = pElement->Header.Allocation;
	return (TEXRESULT)(Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Destruct Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Does not destroy child objects only itself, although it removes refrences of itself from all child/parent objects.
* all allocations of the object to be deleted will be invalid and you have to deal with them.
* @param Allocation refrencing the desired object to destruct.
* @param Full means full destruct, as in everything is destroyed, non full destruct is for recreation mainly.
* @param ThreadIndex Index of the thread that is calling this.
* @note Multithread safe when threadindex is unique on each thread calling.
* @note Externally Synchronized.
*/
TEXRESULT Destroy_Object(ObjectAllocation Allocation, bool Full, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Get_ObjectAllocationValidity(Allocation) != Success)
	{
		Engine_Ref_ArgsError("Destroy_Object()", "Allocation Invalid.");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	ObjectSignature* pSignature = NULL;
	ObjectBufferIndex BufferIndex = 0;
	Find_ObjectSignature(Allocation.Identifier, &pSignature, &BufferIndex);

	Object* pObject = Get_ObjectPointer(Allocation);
	Object* pInstance = (pObject->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pObject->Header.pDelayedInstances[ThreadIndex].Pointer] : pObject;

	if (pSignature->Destructor != NULL)
	{
		Destroy_ObjectTemplate* func = *pSignature->Destructor;
		if ((tres = func(pInstance, Full, ThreadIndex)) != Success)
			return tres;
	}

	if (pObject->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX)
	{
		ArenaAllocater* pAllocater = NULL;
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		{
			if (Utils.InternalObjectBuffer.ArenaAllocaters[i].StartPtr <= pObject->Header.pDelayedInstances[ThreadIndex].Pointer &&
				Utils.InternalObjectBuffer.ArenaAllocaters[i].EndPtr >= (pObject->Header.pDelayedInstances[ThreadIndex].Pointer + pObject->Header.AllocationSize))
			{
				pAllocater = &Utils.InternalObjectBuffer.ArenaAllocaters[i];
			}
		}
		if (pAllocater == NULL)
		{
			Engine_Ref_FunctionError("Destroy_Object()", "Arena Allocater could not be found. ", pAllocater);
			return (TEXRESULT)(Failure);
		}
		Engine_Ref_Lock_Mutex(pAllocater->mutex);
		memset(&Utils.InternalObjectBuffer.Buffer[pObject->Header.pDelayedInstances[ThreadIndex].Pointer], 0, sizeof(*pObject) * pObject->Header.AllocationSize);
		Engine_Ref_Unlock_Mutex(pAllocater->mutex);
	}

	c89atomic_store_32(&pObject->Header.pDelayedInstances[ThreadIndex].Pointer, UINT32_MAX);
	c89atomic_store_8(&pObject->Header.pDelayedInstances[ThreadIndex].Latest, 0);

	if (Full == true)
	{
		ArenaAllocater* pAllocater = NULL;
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		{
			if (pSignature->Buffer->ArenaAllocaters[i].StartPtr <= pObject->Header.Allocation.Pointer &&
				pSignature->Buffer->ArenaAllocaters[i].EndPtr >= (pObject->Header.Allocation.Pointer + pObject->Header.AllocationSize))
			{
				pAllocater = &pSignature->Buffer->ArenaAllocaters[i];
			}
		}
		if (pAllocater == NULL)
		{
			Engine_Ref_FunctionError("Destroy_Object()", "Arena Allocater could not be found. ", pAllocater);
			return (TEXRESULT)(Failure);
		}
		Engine_Ref_Lock_Mutex(pAllocater->mutex);

		for (size_t i = 0; i < DelayedInstanceSize; i++)
		{
			if (pObject->Header.pDelayedInstances[i].Pointer != UINT32_MAX)
			{
				Destroy_Object(Allocation, false, i);
				pObject->Header.pDelayedInstances[i].Pointer = UINT32_MAX;
				pObject->Header.pDelayedInstances[i].Latest = 1;
			}
		}

		for (size_t i = 0; i < pObject->Header.iResourceHeadersSize; i++)
		{
			ResourceHeader* pChild = Get_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i]);

			if (pChild != NULL)
			{
				uint64_t index = 0;
				bool found = false;
				for (size_t i = 0; i < pChild->Header.iParentsSize; i++)
				{
					if (pChild->Header.iParents[i].Pointer == Allocation.Pointer)
					{
						index = i;
						found = true;
					}
				}
				if (found == false)
					break;

				RemoveMember_Array((void**)&pChild->Header.iParents, pChild->Header.iParentsSize, index, sizeof(*pChild->Header.iParents), 1);
				pChild->Header.iParentsSize = pChild->Header.iParentsSize - 1;
			}
		}

		for (size_t i = 0; i < pObject->Header.iChildrenSize; i++)
		{
			Object* pChild = Get_ObjectPointer(pObject->Header.iChildren[i]);
			if (pChild != NULL)
			{
				memset(&pChild->Header.iParent, 0, sizeof(pChild->Header.iParent));
			}
		}


		if (pObject->Header.iResourceHeaders != NULL && pObject->Header.iResourceHeadersSize != NULL)
			free(pObject->Header.iResourceHeaders);
		if (pObject->Header.iChildren != NULL  && pObject->Header.iChildrenSize != NULL)
			free(pObject->Header.iChildren);
		if (pObject->Header.Name != NULL)
			free(pObject->Header.Name);

		memset(pObject, 0, sizeof(*pObject) * pObject->Header.AllocationSize);
		Engine_Ref_Unlock_Mutex(pAllocater->mutex);
	}
	return Success;
}
/*
* Added in 1.0.0
* Does not destroy child objects only itself, although it removes refrences of itself from all child/parent objects.
* all allocations of the object to be deleted will be invalid and you have to deal with them.
* @param Allocation refrencing the desired object to destruct.
* @param Full means full destruct, as in everything is destroyed, non full destruct is for recreation mainly.
* @param ThreadIndex Index of the thread that is calling this.
* @note Multithread safe when threadindex is unique on each thread calling.
* @note Externally Synchronized.
*/
TEXRESULT Destroy_ResourceHeader(ResourceHeaderAllocation Allocation, bool Full, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Get_ResourceHeaderAllocationValidity(Allocation) != Success)
	{
		Engine_Ref_ArgsError("Destroy_ResourceHeader()", "Allocation Invalid.");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	ResourceHeaderSignature* pSignature = NULL;
	ResourceHeaderBufferIndex BufferIndex = 0;
	Find_ResourceHeaderSignature(Allocation.Identifier, &pSignature, &BufferIndex);

	ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation);
	ResourceHeader* pInstance = (pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX) ? &Utils.InternalResourceHeaderBuffer.Buffer[pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer] : pResourceHeader;

	if (pSignature->Destructor != NULL)
	{
		Destroy_ResourceHeaderTemplate* func = *pSignature->Destructor;
		if ((tres = func(pInstance, Full, ThreadIndex)) != Success)
			return tres;
	}
	
	if (pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX)
	{
		ArenaAllocater* pAllocater = NULL;
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		{
			if (Utils.InternalResourceHeaderBuffer.ArenaAllocaters[i].StartPtr <= pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer &&
				Utils.InternalResourceHeaderBuffer.ArenaAllocaters[i].EndPtr >= (pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer + pResourceHeader->Header.AllocationSize))
			{
				pAllocater = &Utils.InternalResourceHeaderBuffer.ArenaAllocaters[i];
			}
		}
		if (pAllocater == NULL)
		{
			Engine_Ref_FunctionError("Destroy_ResourceHeader()", "Arena Allocater could not be found. ", pAllocater);
			return (TEXRESULT)(Failure);
		}
		Engine_Ref_Lock_Mutex(pAllocater->mutex);
		memset(&Utils.InternalResourceHeaderBuffer.Buffer[pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer], 0, sizeof(*pResourceHeader) * pResourceHeader->Header.AllocationSize);
		Engine_Ref_Unlock_Mutex(pAllocater->mutex);
	}

	c89atomic_store_32(&pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer, UINT32_MAX);
	c89atomic_store_8(&pResourceHeader->Header.pDelayedInstances[ThreadIndex].Latest, 0);

	if (Full == true)
	{
		ArenaAllocater* pAllocater = NULL;
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		{
			if (pSignature->Buffer->ArenaAllocaters[i].StartPtr <= pResourceHeader->Header.Allocation.Pointer &&
				pSignature->Buffer->ArenaAllocaters[i].EndPtr >= (pResourceHeader->Header.Allocation.Pointer + pResourceHeader->Header.AllocationSize))
			{
				pAllocater = &pSignature->Buffer->ArenaAllocaters[i];
			}
		}
		if (pAllocater == NULL)
		{
			Engine_Ref_FunctionError("Destroy_ResourceHeader()", "Arena Allocater could not be found. ", pAllocater);
			return (TEXRESULT)(Failure);
		}
		Engine_Ref_Lock_Mutex(pAllocater->mutex);

		for (size_t i = 0; i < DelayedInstanceSize; i++)
		{
			if (pResourceHeader->Header.pDelayedInstances[i].Pointer != UINT32_MAX)
			{
				Destroy_ResourceHeader(Allocation, false, i);
				pResourceHeader->Header.pDelayedInstances[i].Pointer = UINT32_MAX;
				pResourceHeader->Header.pDelayedInstances[i].Latest = 1;
			}
		}

		for (size_t i = 0; i < pResourceHeader->Header.iElementsSize; i++)
		{
			Element* pChild = Get_ElementPointer(pResourceHeader->Header.iElements[i]);
			if (pChild != NULL)
			{
				uint64_t index = 0;
				bool found = false;
				for (size_t i = 0; i < pChild->Header.iParentsSize; i++)
				{
					if (pChild->Header.iParents[i].Pointer == Allocation.Pointer)
					{
						index = i;
						found = true;
					}
				}
				if (found == false)
					break;

				RemoveMember_Array((void**)&pChild->Header.iParents, pChild->Header.iParentsSize, index, sizeof(*pChild->Header.iParents), 1);
				pChild->Header.iParentsSize = pChild->Header.iParentsSize - 1;
			}
		}

		for (size_t i = 0; i < pResourceHeader->Header.iParentsSize; i++)
		{
			Object* pParent = Get_ObjectPointer(pResourceHeader->Header.iParents[i]);
			if (pParent != NULL)
			{
				uint64_t index = 0;
				bool found = false;
				for (size_t i = 0; i < pParent->Header.iResourceHeadersSize; i++)
				{
					if (pParent->Header.iResourceHeaders[i].Pointer == Allocation.Pointer)
					{
						index = i;
						found = true;
					}
				}
				if (found == false)
					break;

				RemoveMember_Array((void**)&pParent->Header.iResourceHeaders, pParent->Header.iResourceHeadersSize, index, sizeof(*pParent->Header.iResourceHeaders), 1);
				pParent->Header.iResourceHeadersSize = pParent->Header.iResourceHeadersSize - 1;
			}
		}

		if (pResourceHeader->Header.iParents != NULL && pResourceHeader->Header.iParentsSize != NULL)
			free(pResourceHeader->Header.iParents);
		if (pResourceHeader->Header.iElements != NULL && pResourceHeader->Header.iElementsSize != NULL)
			free(pResourceHeader->Header.iElements);
		if (pResourceHeader->Header.Name != NULL)
			free(pResourceHeader->Header.Name);

		memset(pResourceHeader, 0, sizeof(ResourceHeader) * pResourceHeader->Header.AllocationSize);
		Engine_Ref_Unlock_Mutex(pAllocater->mutex);
	}
	return Success;
}
/*
* Added in 1.0.0
* Does not destroy child objects only itself, although it removes refrences of itself from all child/parent objects.
* all allocations of the object to be deleted will be invalid and you have to deal with them.
* @param Allocation refrencing the desired object to destruct.
* @param Full means full destruct, as in everything is destroyed, non full destruct is for recreation mainly, when Full destruct and is used on other threads it will block until fully destructed as well.
* @param ThreadIndex Index of the thread that is calling this.
* @note Multithread safe when threadindex is unique on each thread calling.
* @note Externally Synchronized.
*/
TEXRESULT Destroy_Element(ElementAllocation Allocation, bool Full, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Get_ElementAllocationValidity(Allocation) != Success)
	{
		Engine_Ref_ArgsError("Destroy_Element()", "Allocation Invalid.");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	ElementSignature* pSignature = NULL;
	ElementBufferIndex BufferIndex = 0;
	Find_ElementSignature(Allocation.Identifier, &pSignature, &BufferIndex);

	Element* pElement = Get_ElementPointer(Allocation);
	Element* pInstance = (pElement->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX) ? &Utils.InternalElementBuffer.Buffer[pElement->Header.pDelayedInstances[ThreadIndex].Pointer] : pElement;

	if (pSignature->Destructor != NULL)
	{
		Destroy_ElementTemplate* func = *pSignature->Destructor;
		if ((tres = func(pInstance, Full, ThreadIndex)) != Success)
			return tres;
	}
	
	if (pElement->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX)
	{
		ArenaAllocater* pAllocater = NULL;
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		{
			if (Utils.InternalElementBuffer.ArenaAllocaters[i].StartPtr <= pElement->Header.pDelayedInstances[ThreadIndex].Pointer &&
				Utils.InternalElementBuffer.ArenaAllocaters[i].EndPtr >= (pElement->Header.pDelayedInstances[ThreadIndex].Pointer + pElement->Header.AllocationSize))
			{
				pAllocater = &Utils.InternalElementBuffer.ArenaAllocaters[i];
			}
		}
		if (pAllocater == NULL)
		{
			Engine_Ref_FunctionError("Destroy_Element()", "Arena Allocater could not be found. ", pAllocater);
			return (TEXRESULT)(Failure);
		}
		Engine_Ref_Lock_Mutex(pAllocater->mutex);
		memset(&Utils.InternalElementBuffer.Buffer[pElement->Header.pDelayedInstances[ThreadIndex].Pointer], 0, sizeof(*pElement) * pElement->Header.AllocationSize);
		Engine_Ref_Unlock_Mutex(pAllocater->mutex);
	}

	c89atomic_store_32(&pElement->Header.pDelayedInstances[ThreadIndex].Pointer, UINT32_MAX);
	c89atomic_store_8(&pElement->Header.pDelayedInstances[ThreadIndex].Latest, 0);

	if (Full == true)
	{
		ArenaAllocater* pAllocater = NULL;
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
		{
			if (pSignature->Buffer->ArenaAllocaters[i].StartPtr <= pElement->Header.Allocation.Pointer &&
				pSignature->Buffer->ArenaAllocaters[i].EndPtr >= (pElement->Header.Allocation.Pointer + pElement->Header.AllocationSize))
			{
				pAllocater = &pSignature->Buffer->ArenaAllocaters[i];
			}
		}
		if (pAllocater == NULL)
		{
			Engine_Ref_FunctionError("Destroy_Element()", "Arena Allocater could not be found. ", pAllocater);
			return (TEXRESULT)(Failure);
		}
		Engine_Ref_Lock_Mutex(pAllocater->mutex);

		for (size_t i = 0; i < DelayedInstanceSize; i++)
		{
			if (pElement->Header.pDelayedInstances[i].Pointer != UINT32_MAX)
			{
				Destroy_Element(Allocation, false, i);
				pElement->Header.pDelayedInstances[i].Pointer = UINT32_MAX;
				pElement->Header.pDelayedInstances[i].Latest = 1;
			}
		}

		for (size_t i = 0; i < pElement->Header.iParentsSize; i++)
		{
			ResourceHeader* pParent = Get_ResourceHeaderPointer(pElement->Header.iParents[i]);
			if (pParent != NULL)
			{
				uint64_t index = 0;
				bool found = false;
				for (size_t i = 0; i < pParent->Header.iElementsSize; i++)
				{
					if (pParent->Header.iElements[i].Pointer == Allocation.Pointer)
					{
						index = i;
						found = true;
					}
				}
				if (found == false)
					break;

				RemoveMember_Array((void**)&pParent->Header.iElements, pParent->Header.iElementsSize, index, sizeof(*pParent->Header.iElements), 1);
				pParent->Header.iElementsSize = pParent->Header.iElementsSize - 1;
			}
		}
		if (pElement->Header.iParents != NULL && pElement->Header.iParentsSize != NULL)
			free(pElement->Header.iParents);
		if (pElement->Header.Name != NULL)
			free(pElement->Header.Name);

		memset(pElement, 0, sizeof(Element) * pElement->Header.AllocationSize);
		Engine_Ref_Unlock_Mutex(pAllocater->mutex);
	}
	return Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Recreate Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Recreate Object with new data.
* @param Allocation refrencing the desired Object to update.
* @param pInstance pointer to Object created by CreateInstance_Object(), if its null recreate will be not multithreaded safe.
* @param ThreadIndex Index of the thread that is calling this.
* @note Externally Synchronized.
*/
TEXRESULT ReCreate_Object(ObjectAllocation Allocation, ObjectInstance* pInstance, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Get_ObjectAllocationValidity(Allocation) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_Object()", "Allocation Invalid.");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	ObjectSignature* pSignature = NULL;
	ObjectBufferIndex BufferIndex = 0;
	Find_ObjectSignature(Allocation.Identifier, &pSignature, &BufferIndex);
	Object* pObject = Get_ObjectPointer(Allocation);
	if (pInstance != NULL)
	{
#ifdef OBJECT_MUTEX
		Engine_Ref_Lock_Mutex(pObject->Header.mutex);
#endif
		size_t foundcount = 0;
		for (size_t i = 0; i < DelayedInstanceSize; i++)
			if (pObject->Header.pDelayedInstances[i].Pointer == pObject->Header.pDelayedInstances[ThreadIndex].Pointer)
				foundcount++;
		if (foundcount == 1)
			Destroy_Object(Allocation, false, ThreadIndex);
		if (pSignature->ReConstructor != NULL)
		{
			ReCreate_ObjectTemplate* func = *pSignature->ReConstructor;
			func(pInstance->pInstance, ThreadIndex);
		}
		c89atomic_store_32(&pObject->Header.pDelayedInstances[ThreadIndex].Pointer, pInstance->Pointer);
		for (size_t i = 0; i < DelayedInstanceSize; i++)
		{		
			if (pObject->Header.pDelayedInstances[i].Pointer == UINT32_MAX)
			{
				c89atomic_store_32(&pObject->Header.pDelayedInstances[i].Pointer, pInstance->Pointer);
			}
			c89atomic_store_8(&pObject->Header.pDelayedInstances[i].Latest, 0);
		}
		c89atomic_store_8(&pObject->Header.pDelayedInstances[ThreadIndex].Latest, 1);
#ifdef OBJECT_MUTEX
		Engine_Ref_Unlock_Mutex(pObject->Header.mutex);
#endif
	}
	else
	{
		if (pSignature->ReConstructor != NULL)
		{
			ReCreate_ObjectTemplate* pFunction = *pSignature->ReConstructor;
			if ((tres = pFunction(pObject, ThreadIndex)) != Success)
				return tres;
		}
	}
	return Success;
}
/*
* Added in 1.0.0
* Recreate ResourceHeader with new data.
* @param Allocation refrencing the desired ResourceHeader to update.
* @param pInstance pointer to ResourceHeader created by CreateInstance_ResourceHeader(), if its null recreate will be not multithreaded safe.
* @param ThreadIndex Index of the thread that is calling this.
* @note Externally Synchronized.
*/
TEXRESULT ReCreate_ResourceHeader(ResourceHeaderAllocation Allocation, ResourceHeaderInstance* pInstance, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Get_ResourceHeaderAllocationValidity(Allocation) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_ResourceHeader()", "Allocation Invalid.");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	ResourceHeaderSignature* pSignature = NULL;
	ResourceHeaderBufferIndex BufferIndex = 0;
	Find_ResourceHeaderSignature(Allocation.Identifier, &pSignature, &BufferIndex);
	ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation);
	if (pInstance != NULL)
	{
#ifdef OBJECT_MUTEX
		Engine_Ref_Lock_Mutex(pResourceHeader->Header.mutex);
#endif
		size_t foundcount = 0;
		for (size_t i = 0; i < DelayedInstanceSize; i++)
			if (pResourceHeader->Header.pDelayedInstances[i].Pointer == pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer)
				foundcount++;
		if (foundcount == 1)
			Destroy_ResourceHeader(Allocation, false, ThreadIndex);
		if (pSignature->ReConstructor != NULL)
		{
			ReCreate_ResourceHeaderTemplate* func = *pSignature->ReConstructor;
			func(pInstance->pInstance, ThreadIndex);
		}
		c89atomic_store_32(&pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer, pInstance->Pointer);
		for (size_t i = 0; i < DelayedInstanceSize; i++)
		{
			if (pResourceHeader->Header.pDelayedInstances[i].Pointer == UINT32_MAX)
			{
				c89atomic_store_32(&pResourceHeader->Header.pDelayedInstances[i].Pointer, pInstance->Pointer);
			}
			c89atomic_store_8(&pResourceHeader->Header.pDelayedInstances[i].Latest, 0);
		}
		c89atomic_store_8(&pResourceHeader->Header.pDelayedInstances[ThreadIndex].Latest, 1);
#ifdef OBJECT_MUTEX
		Engine_Ref_Unlock_Mutex(pResourceHeader->Header.mutex);
#endif
	}
	else
	{
		if (pSignature->ReConstructor != NULL)
		{
			ReCreate_ResourceHeaderTemplate* pFunction = *pSignature->ReConstructor;
			if ((tres = pFunction(pResourceHeader, ThreadIndex)) != Success)
				return tres;
		}
	}
	return Success;
}
/*
* Added in 1.0.0
* Recreate Element with new data.
* @param Allocation refrencing the desired Element to update.
* @param pInstance pointer to Element created by CreateInstance_Element(), if its null recreate will be not multithreaded safe.
* @param ThreadIndex Index of the thread that is calling this.
* @note Externally Synchronized.
*/
TEXRESULT ReCreate_Element(ElementAllocation Allocation, ElementInstance* pInstance, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Get_ElementAllocationValidity(Allocation) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_Element()", "Allocation Invalid.");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	ElementSignature* pSignature = NULL;
	ElementBufferIndex BufferIndex = 0;
	Find_ElementSignature(Allocation.Identifier, &pSignature, &BufferIndex);
	Element* pElement = Get_ElementPointer(Allocation);
	if (pInstance != NULL)
	{
#ifdef OBJECT_MUTEX
		Engine_Ref_Lock_Mutex(pElement->Header.mutex);
#endif
		size_t foundcount = 0;
		for (size_t i = 0; i < DelayedInstanceSize; i++)
			if (pElement->Header.pDelayedInstances[i].Pointer == pElement->Header.pDelayedInstances[ThreadIndex].Pointer)
				foundcount++;
		if (foundcount == 1)
			Destroy_Element(Allocation, false, ThreadIndex);
		if (pSignature->ReConstructor != NULL)
		{
			ReCreate_ElementTemplate* func = *pSignature->ReConstructor;
			func(pInstance->pInstance, ThreadIndex);
		}
		c89atomic_store_32(&pElement->Header.pDelayedInstances[ThreadIndex].Pointer, pInstance->Pointer);
		for (size_t i = 0; i < DelayedInstanceSize; i++)
		{
			if (pElement->Header.pDelayedInstances[i].Pointer == UINT32_MAX)
			{
				c89atomic_store_32(&pElement->Header.pDelayedInstances[i].Pointer, pInstance->Pointer);
			}
			c89atomic_store_8(&pElement->Header.pDelayedInstances[i].Latest, 0);
		}
		c89atomic_store_8(&pElement->Header.pDelayedInstances[ThreadIndex].Latest, 1);
#ifdef OBJECT_MUTEX
		Engine_Ref_Unlock_Mutex(pElement->Header.mutex);
#endif
	}
	else
	{
		if (pSignature->ReConstructor != NULL)
		{
			ReCreate_ElementTemplate* pFunction = *pSignature->ReConstructor;
			if ((tres = pFunction(pElement, ThreadIndex)) != Success)
				return tres;
		}
	}
	return Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Start Thread
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Get the designated Object's data for a threadindex.
* @param pObject refrencing the desired Object to get data from.
* @param ThreadIndex threadindex global.
* @param ppReturn pointer to a pointer of a Object that will contain the thread specific data. (non malloced)
* @note Always Thread safe.
* @note Externally Synchronized.
*/
TEXRESULT StartThread_Object(ObjectAllocation Allocation, uint32_t ThreadIndex, Object** ppReturn){
	Object* pObject = Get_ObjectPointer(Allocation);
	*ppReturn = (pObject->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pObject->Header.pDelayedInstances[ThreadIndex].Pointer] : pObject;
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Get the designated Object's data for a threadindex.
* @param pObject refrencing the desired Object to get data from.
* @param ThreadIndex threadindex global.
* @param ppReturn pointer to a pointer of a Object that will contain the thread specific data. (non malloced)
* @note Always Thread safe.
* @note Externally Synchronized.
*/
TEXRESULT StartThread_ResourceHeader(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex, ResourceHeader** ppReturn){
	ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation);
	*ppReturn = (pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX) ? &Utils.InternalResourceHeaderBuffer.Buffer[pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer] : pResourceHeader;
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Get the designated Object's data for a threadindex.
* @param pObject refrencing the desired Object to get data from.
* @param ThreadIndex threadindex global.
* @param ppReturn pointer to a pointer of a Object that will contain the thread specific data. (non malloced)
* @note Always Thread safe.
* @note Externally Synchronized.
*/
TEXRESULT StartThread_Element(ElementAllocation Allocation, uint32_t ThreadIndex, Element** ppReturn){
	Element* pElement = Get_ElementPointer(Allocation);
	*ppReturn = (pElement->Header.pDelayedInstances[ThreadIndex].Pointer != UINT32_MAX) ? &Utils.InternalElementBuffer.Buffer[pElement->Header.pDelayedInstances[ThreadIndex].Pointer] : pElement;
	return (TEXRESULT)(Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//End Thread
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Signals that thread is done with Object.
* @param pObject refrencing the desired Object to signal done.
* @param ThreadIndex threadindex global.
* @note Always Thread safe.
* @note Externally Synchronized.
*/
TEXRESULT EndThread_Object(ObjectAllocation Allocation, uint32_t ThreadIndex){
	Object* pObject = Get_ObjectPointer(Allocation);
	//if its the last of its pointer and non latest then delete.
#ifdef OBJECT_MUTEX
	Engine_Ref_Lock_Mutex(pObject->Header.mutex);
#endif
	if (pObject->Header.pDelayedInstances[ThreadIndex].Latest == 0)
	{
		size_t foundcount = 0;
		for (size_t i = 0; i < DelayedInstanceSize; i++)
			if (pObject->Header.pDelayedInstances[i].Pointer == pObject->Header.pDelayedInstances[ThreadIndex].Pointer)
				foundcount++;
		if (foundcount == 1)
			Destroy_Object(Allocation, false, ThreadIndex);
	}
	//swap this thread to most recent instance
	for (size_t i = 0; i < DelayedInstanceSize; i++)
	{
		if (pObject->Header.pDelayedInstances[i].Latest == 1)
		{
			c89atomic_store_32(&pObject->Header.pDelayedInstances[ThreadIndex].Pointer, pObject->Header.pDelayedInstances[i].Pointer);
			c89atomic_store_8(&pObject->Header.pDelayedInstances[ThreadIndex].Latest, 1);
		}
	}
#ifdef OBJECT_MUTEX
	Engine_Ref_Unlock_Mutex(pObject->Header.mutex);
#endif
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Signals that thread is done with ResourceHeader.
* @param pResourceHeader refrencing the desired ResourceHeader to signal done.
* @param ThreadIndex threadindex global.
* @note Always Thread safe.
* @note Externally Synchronized.
*/
TEXRESULT EndThread_ResourceHeader(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex){
	ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation);
	//if its the last of its pointer and non latest then delete.
#ifdef OBJECT_MUTEX
	Engine_Ref_Lock_Mutex(pResourceHeader->Header.mutex);
#endif
	if (pResourceHeader->Header.pDelayedInstances[ThreadIndex].Latest == 0)
	{
		size_t foundcount = 0;
		for (size_t i = 0; i < DelayedInstanceSize; i++)
			if (pResourceHeader->Header.pDelayedInstances[i].Pointer == pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer)
				foundcount++;
		if (foundcount == 1)
			Destroy_ResourceHeader(Allocation, false, ThreadIndex);
	}
	//swap this thread to most recent instance
	for (size_t i = 0; i < DelayedInstanceSize; i++)
	{
		if (pResourceHeader->Header.pDelayedInstances[i].Latest == 1)
		{
			c89atomic_store_32(&pResourceHeader->Header.pDelayedInstances[ThreadIndex].Pointer, pResourceHeader->Header.pDelayedInstances[i].Pointer);
			c89atomic_store_8(&pResourceHeader->Header.pDelayedInstances[ThreadIndex].Latest, 1);
		}
	}
#ifdef OBJECT_MUTEX
	Engine_Ref_Unlock_Mutex(pResourceHeader->Header.mutex);
#endif
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Signals that thread is done with Element.
* @param pElement refrencing the desired Element to signal done.
* @param ThreadIndex threadindex global.
* @note Always Thread safe.
* @note Externally Synchronized.
*/
TEXRESULT EndThread_Element(ElementAllocation Allocation, uint32_t ThreadIndex){
	Element* pElement = Get_ElementPointer(Allocation);
	//if its the last of its pointer and non latest then delete.
#ifdef OBJECT_MUTEX
	Engine_Ref_Lock_Mutex(pElement->Header.mutex);
#endif
	if (pElement->Header.pDelayedInstances[ThreadIndex].Latest == 0)
	{
		size_t foundcount = 0;
		for (size_t i = 0; i < DelayedInstanceSize; i++)
			if (pElement->Header.pDelayedInstances[i].Pointer == pElement->Header.pDelayedInstances[ThreadIndex].Pointer)
				foundcount++;
		if (foundcount == 1)
			Destroy_Element(Allocation, false, ThreadIndex);
	}
	//swap this thread to most recent instance
	for (size_t i = 0; i < DelayedInstanceSize; i++)
	{
		if (pElement->Header.pDelayedInstances[i].Latest == 1)
		{
			c89atomic_store_32(&pElement->Header.pDelayedInstances[ThreadIndex].Pointer, pElement->Header.pDelayedInstances[i].Pointer);
			c89atomic_store_8(&pElement->Header.pDelayedInstances[ThreadIndex].Latest, 1);
		}
	}
#ifdef OBJECT_MUTEX
	Engine_Ref_Unlock_Mutex(pElement->Header.mutex);
#endif
	return (TEXRESULT)(Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Destruct Buffers Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
* @param pBuffer refrencing the desired buffer to destroy.
* @note Thread Safe.
* @note Internally Synchronized.
*/
void Destroy_ObjectBuffer(ObjectBuffer* pBuffer)
{
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Destroy_ObjectBuffer", "pBuffer == NULLPTR");
		return;
	}
#endif
	for (size_t i = 0; i < pBuffer->Size;)
	{
		Object* pObject = (Object*)&pBuffer->Buffer[i];
		if (pObject->Header.AllocationSize != NULL)
		{
			Destroy_Object(pObject->Header.Allocation, true, 0);
			i += pObject->Header.AllocationSize;
		}
		else
		{
			i++;
		}
	}

	if (pBuffer->Indexes != NULL)
		free(pBuffer->Indexes);
	pBuffer->Indexes = NULL;

	pBuffer->Size = 0;
	if (pBuffer->Buffer != NULL)
		free(pBuffer->Buffer);

	if (pBuffer->ArenaAllocaters != NULL)
	{
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
			Destroy_ArenaAllocater(&pBuffer->ArenaAllocaters[i]);
		free(pBuffer->ArenaAllocaters);
	}
	pBuffer->ArenaAllocaters = NULL;

	memset(pBuffer, 0, sizeof(*pBuffer));
}
/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
* @param pBuffer refrencing the desired buffer to destroy.
* @note Thread Safe.
* @note Internally Synchronized.
*/
void Destroy_ResourceHeaderBuffer(ResourceHeaderBuffer* pBuffer)
{
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Destroy_ResourceHeaderBuffer", "pBuffer == NULLPTR");
		return;
	}
#endif
	for (size_t i = 0; i < pBuffer->Size;)
	{
		ResourceHeader* pResourceHeader = (ResourceHeader*)&pBuffer->Buffer[i];
		if (pResourceHeader->Header.AllocationSize != NULL)
		{
			Destroy_ResourceHeader(pResourceHeader->Header.Allocation, true, 0);
			i += pResourceHeader->Header.AllocationSize;
		}
		else
		{
			i++;
		}
	}

	if (pBuffer->Indexes != NULL)
		free(pBuffer->Indexes);
	pBuffer->Indexes = NULL;

	pBuffer->Size = 0;
	if (pBuffer->Buffer != NULL)
		free(pBuffer->Buffer);

	if (pBuffer->ArenaAllocaters != NULL)
	{
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
			Destroy_ArenaAllocater(&pBuffer->ArenaAllocaters[i]);
		free(pBuffer->ArenaAllocaters);
	}
	pBuffer->ArenaAllocaters = NULL;

	memset(pBuffer, 0, sizeof(*pBuffer));
}
/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
* @param pBuffer refrencing the desired buffer to destroy.
* @note Thread Safe.
* @note Internally Synchronized.
*/
void Destroy_ElementBuffer(ElementBuffer* pBuffer)
{
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Destroy_ElementBuffer", "pBuffer == NULLPTR");
		return;
	}
#endif
	for (size_t i = 0; i < pBuffer->Size;)
	{
		Element* pElement = (Element*)&pBuffer->Buffer[i];
		if (pElement->Header.AllocationSize != NULL)
		{
			Destroy_Element(pElement->Header.Allocation, true, 0);
			i += pElement->Header.AllocationSize;
		}
		else
		{
			i++;
		}
	}

	if (pBuffer->Indexes != NULL)
		free(pBuffer->Indexes);
	pBuffer->Indexes = NULL;

	pBuffer->Size = 0;
	if (pBuffer->Buffer != NULL)
		free(pBuffer->Buffer);

	if (pBuffer->ArenaAllocaters != NULL) {
		for (size_t i = 0; i < ((EngineUtils*)EngineRes.pUtils)->CPU.MaxThreads; i++)
			Destroy_ArenaAllocater(&pBuffer->ArenaAllocaters[i]);
		free(pBuffer->ArenaAllocaters);
	}	
	pBuffer->ArenaAllocaters = NULL;

	memset(pBuffer, 0, sizeof(*pBuffer));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Add New Children Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Macro for adding childs to objects.
* @param Allocation refrencing the desired object to make child of.
* @param Parent refrencing the desired object to make parent of Allocation.
* @note Externally Synchronized.
*/
void Add_ObjectChild(ObjectAllocation Allocation, ObjectAllocation Parent)
{
#ifndef NDEBUG
	if (Get_ObjectAllocationValidity(Allocation) == Failure)
	{
		Engine_Ref_ArgsError("Add_ObjectChild", "Allocation Invalid.");
		return;
	}
	if (Get_ObjectAllocationValidity(Parent) == Failure)
	{
		Engine_Ref_ArgsError("Add_ObjectChild", "Parent Invalid.");
		return;
	}
#endif
	{
		Object* pParent = Get_ObjectPointer(Parent);

		Resize_Array((void**)&pParent->Header.iChildren, pParent->Header.iChildrenSize, pParent->Header.iChildrenSize + 1, sizeof(*pParent->Header.iChildren));
		pParent->Header.iChildrenSize = pParent->Header.iChildrenSize + 1;

		pParent->Header.iChildren[pParent->Header.iChildrenSize - 1] = Allocation;
	}

	{
		Object* pChild = Get_ObjectPointer(Allocation);

		pChild->Header.iParent = Parent;
	}

}
/*
* Added in 1.0.0
* Macro for adding childs to objects.
* @param Allocation refrencing the desired resourceheader to make child of.
* @param Parent refrencing the desired object to make parent of Allocation.
* @note Externally Synchronized.
*/
void Add_Object_ResourceHeaderChild(ResourceHeaderAllocation Allocation, ObjectAllocation Parent)
{
#ifndef NDEBUG
	if (Get_ResourceHeaderAllocationValidity(Allocation) == Failure)
	{
		Engine_Ref_ArgsError("Add_Object_ResourceHeaderChild", "Allocation Invalid.");
		return;
	}
	if (Get_ObjectAllocationValidity(Parent) == Failure)
	{
		Engine_Ref_ArgsError("Add_Object_ResourceHeaderChild", "Parent Invalid.");
		return;
	}
#endif
	{
		Object* pParent = Get_ObjectPointer(Parent);

		Resize_Array((void**)&pParent->Header.iResourceHeaders, pParent->Header.iResourceHeadersSize, pParent->Header.iResourceHeadersSize + 1, sizeof(*pParent->Header.iResourceHeaders));
		pParent->Header.iResourceHeadersSize = pParent->Header.iResourceHeadersSize + 1;

		pParent->Header.iResourceHeaders[pParent->Header.iResourceHeadersSize - 1] = Allocation;
	}

	{
		ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation);

		Resize_Array((void**)&pResourceHeader->Header.iParents, pResourceHeader->Header.iParentsSize, pResourceHeader->Header.iParentsSize + 1, sizeof(*pResourceHeader->Header.iParents));
		pResourceHeader->Header.iParentsSize = pResourceHeader->Header.iParentsSize + 1;

		pResourceHeader->Header.iParents[pResourceHeader->Header.iParentsSize - 1] = Parent;

	}
}
/*
* Added in 1.0.0
* Macro for adding childs to objects.
* @param Allocation refrencing the desired element to make child of.
* @param Parent refrencing the desired resourceheader to make parent of Allocation.
* @note Externally Synchronized.
*/
void Add_ResourceHeader_ElementChild(ElementAllocation Allocation, ResourceHeaderAllocation Parent)
{
#ifndef NDEBUG
	if (Get_ElementAllocationValidity(Allocation) == Failure)
	{
		Engine_Ref_ArgsError("Add_ResourceHeader_ElementChild", "Allocation Invalid.");
		return;
	}
	if (Get_ResourceHeaderAllocationValidity(Parent) == Failure)
	{
		Engine_Ref_ArgsError("Add_ResourceHeader_ElementChild", "Parent Invalid.");
		return;
	}
#endif
	{
		ResourceHeader* pParent = Get_ResourceHeaderPointer(Parent);

		Resize_Array((void**)&pParent->Header.iElements, pParent->Header.iElementsSize, pParent->Header.iElementsSize + 1, sizeof(*pParent->Header.iElements));
		pParent->Header.iElementsSize = pParent->Header.iElementsSize + 1;

		pParent->Header.iElements[pParent->Header.iElementsSize - 1] = Allocation;
	}

	{
		Element* pElement = Get_ElementPointer(Allocation);

		Resize_Array((void**)&pElement->Header.iParents, pElement->Header.iParentsSize, pElement->Header.iParentsSize + 1, sizeof(*pElement->Header.iParents));
		pElement->Header.iParentsSize = pElement->Header.iParentsSize + 1;

		pElement->Header.iParents[pElement->Header.iParentsSize - 1] = Parent;

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Remove Children Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Macro for removing childs from objects.
* @param Allocation refrencing the desired object to remove child of.
* @param Parent refrencing the desired object to remove parent of Allocation.
* @note Externally Synchronized.
*/
void Remove_ObjectChild(ObjectAllocation Allocation, ObjectAllocation Parent)
{
#ifndef NDEBUG
	if (Get_ObjectAllocationValidity(Allocation) == Failure)
	{
		Engine_Ref_ArgsError("Remove_ObjectChild", "Allocation Invalid.");
		return;
	}
	if (Get_ObjectAllocationValidity(Parent) == Failure)
	{
		Engine_Ref_ArgsError("Remove_ObjectChild", "Parent Invalid.");
		return;
	}
#endif
	{
		Object* pParent = Get_ObjectPointer(Parent);

		uint64_t index = 0;
		bool found = false;
		for (size_t i = 0; i < pParent->Header.iChildrenSize; i++)
		{
			if (pParent->Header.iChildren[i].Pointer == Allocation.Pointer)
			{
				index = i;
				found = true;
			}
		}
		if (found == false)
			return;

		RemoveMember_Array((void**)&pParent->Header.iChildren, pParent->Header.iChildrenSize, index, sizeof(*pParent->Header.iChildren), 1);
		pParent->Header.iChildrenSize = pParent->Header.iChildrenSize - 1;
	}

	{
		Object* pChild = Get_ObjectPointer(Allocation);
		memset(&pChild->Header.iParent, 0, sizeof(pChild->Header.iParent));
	}
}
/*
* Added in 1.0.0
* Macro for removing childs from objects.
* @param Allocation refrencing the desired resourceheader to remove child of.
* @param Parent refrencing the desired object to remove parent of Allocation.
* @note Externally Synchronized.
*/
void Remove_Object_ResourceHeaderChild(ResourceHeaderAllocation Allocation, ObjectAllocation Parent)
{
#ifndef NDEBUG
	if (Get_ResourceHeaderAllocationValidity(Allocation) == Failure)
	{
		Engine_Ref_ArgsError("Remove_Object_ResourceHeaderChild", "Allocation Invalid.");
		return;
	}
	if (Get_ObjectAllocationValidity(Parent) == Failure)
	{
		Engine_Ref_ArgsError("Remove_Object_ResourceHeaderChild", "Parent Invalid.");
		return;
	}
#endif
	{
		Object* pParent = Get_ObjectPointer(Parent);

		Resize_Array((void**)&pParent->Header.iResourceHeaders, pParent->Header.iResourceHeadersSize, pParent->Header.iResourceHeadersSize + 1, sizeof(*pParent->Header.iResourceHeaders));
		pParent->Header.iResourceHeadersSize = pParent->Header.iResourceHeadersSize + 1;

		pParent->Header.iResourceHeaders[pParent->Header.iResourceHeadersSize - 1] = Allocation;
	}
	{
		ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation);

		Resize_Array((void**)&pResourceHeader->Header.iParents, pResourceHeader->Header.iParentsSize, pResourceHeader->Header.iParentsSize + 1, sizeof(*pResourceHeader->Header.iParents));
		pResourceHeader->Header.iParentsSize = pResourceHeader->Header.iParentsSize + 1;

		pResourceHeader->Header.iParents[pResourceHeader->Header.iParentsSize - 1] = Parent;
	}
}
/*
* Added in 1.0.0
* Macro for removing childs from objects.
* @param Allocation refrencing the desired element to remove child of.
* @param Parent refrencing the desired resourceheader to remove parent of Allocation.
* @note Externally Synchronized.
*/
void Remove_ResourceHeader_ElementChild(ElementAllocation Allocation, ResourceHeaderAllocation Parent)
{
#ifndef NDEBUG
	if (Get_ElementAllocationValidity(Allocation) == Failure)
	{
		Engine_Ref_ArgsError("Remove_ResourceHeader_ElementChild", "Allocation Invalid.");
		return;
	}
	if (Get_ResourceHeaderAllocationValidity(Parent) == Failure)
	{
		Engine_Ref_ArgsError("Remove_ResourceHeader_ElementChild", "Parent Invalid.");
		return;
	}
#endif
	{
		ResourceHeader* pParent = Get_ResourceHeaderPointer(Parent);

		uint64_t index = 0;
		bool found = false;
		for (size_t i = 0; i < pParent->Header.iElementsSize; i++)
		{
			if (pParent->Header.iElements[i].Pointer == Allocation.Pointer)
			{
				index = i;
				found = true;
			}
		}
		if (found == false)
			return;

		RemoveMember_Array((void**)&pParent->Header.iElements, pParent->Header.iElementsSize, index, sizeof(*pParent->Header.iElements), 1);
		pParent->Header.iElementsSize = pParent->Header.iElementsSize - 1;
	}
	{
		Element* pElement = Get_ElementPointer(Allocation);

		uint64_t index = 0;
		bool found = false;
		for (size_t i = 0; i < pElement->Header.iParentsSize; i++)
		{
			if (pElement->Header.iParents[i].Pointer == Parent.Pointer)
			{
				index = i;
				found = true;
			}
		}
		if (found == false)
			return;

		RemoveMember_Array((void**)&pElement->Header.iParents, pElement->Header.iParentsSize, index, sizeof(*pElement->Header.iParents), 1);
		pElement->Header.iParentsSize = pElement->Header.iParentsSize - 1;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Misc object Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Macro for scanning all childs of an object including childs of their childs.
* @param pChilds is a pointer to an array of allocations to return.
* @param pChildsSize is a pointer to size of the array to return.
* @note Externally Synchronized.
*/
void Scan_ObjectChilds(ObjectAllocation Allocation, ObjectAllocation** pChilds, uint64_t* pChildsSize) //scans all recursive childs of a gameobject. Returns a array of childs
{
#ifndef NDEBUG
	if (Get_ObjectAllocationValidity(Allocation) == Failure)
	{
		Engine_Ref_ArgsError("Scan_ObjectChilds", "Allocation Invalid.");
		return;
	}
	if (pChilds == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectChilds()", "pChilds == NULLPTR");
		return;
	}
	if (pChildsSize == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectChilds()", "pChildsSize == NULLPTR");
		return;
	}
#endif
	Object* pObject = Get_ObjectPointer(Allocation);
	for (size_t i = 0; i < pObject->Header.iChildrenSize; i++)
	{
		ObjectSignature* pSignature = NULL;
		ObjectBufferIndex BufferIndex = 0;
		Find_ObjectSignature(pObject->Header.iChildren[i].Identifier, &pSignature, &BufferIndex);


		uint64_t ChildsSize = *pChildsSize;
		Resize_Array((void**)pChilds, ChildsSize, ChildsSize + 1, sizeof(ObjectAllocation));
		ObjectAllocation* Childs = *pChilds;
		Childs[ChildsSize] = Utils.ObjectSignatures[BufferIndex]->Buffer->Buffer[pObject->Header.iChildren[i].Pointer].Header.Allocation;
		*pChildsSize += 1;
		Scan_ObjectChilds(Allocation, pChilds, pChildsSize);
	}

}
/*
* Added in 1.0.0
* Macro for scanning all parents of an object including parents of their parents
* @param pParents is a pointer to an array of allocations to return.
* @param pParentsSize is a pointer to size of the array to return.
* @note Externally Synchronized.
*/
void Scan_ObjectParents(ObjectAllocation Allocation, ObjectAllocation** pParents, uint64_t* pParentsSize) //scans all recursive parents of a gameobject. Returns a array of parents
{
#ifndef NDEBUG
	if (Get_ObjectAllocationValidity(Allocation) == Failure)
	{
		Engine_Ref_ArgsError("Scan_ObjectParents", "Allocation Invalid.");
		return;
	}
	if (pParents == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectParents()", "pParents == NULLPTR");
		return;
	}
	if (pParentsSize == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectParents()", "pParentsSize == NULLPTR");
		return;
	}
#endif
	Object* pObject = Get_ObjectPointer(Allocation);

	if (Get_ObjectAllocationValidity(pObject->Header.iParent) == Success)
	{
		ObjectSignature* pSignature = NULL;
		ObjectBufferIndex BufferIndex = 0;
		Find_ObjectSignature(pObject->Header.iParent.Identifier, &pSignature, &BufferIndex);

		uint64_t ParentsSize = *pParentsSize;
		Resize_Array((void**)pParents, ParentsSize, ParentsSize + 1, sizeof(ObjectAllocation));
		ObjectAllocation* Parents = *pParents;
		Parents[ParentsSize] = pSignature->Buffer->Buffer[pObject->Header.iParent.Pointer].Header.Allocation;
		*pParentsSize += 1;
		Scan_ObjectParents(pSignature->Buffer->Buffer[pObject->Header.iParent.Pointer].Header.Allocation, pParents, pParentsSize);
	}
}
/*
* Added in 1.0.0
* Macro for scanning all resourceheader childs of specified identifier of a gameobject. 
* @param pHeaders is a pointer to an array of allocations to return.
* @param pHeadersSize is a pointer to size of the array to return.
* @note Externally Synchronized.
*/
void Scan_ObjectHeaders(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, ResourceHeaderAllocation** pHeaders, uint64_t* pHeadersSize) //finds the requested header
{
#ifndef NDEBUG
	if (Get_ObjectAllocationValidity(Allocation) == Failure)
	{
		Engine_Ref_ArgsError("Scan_ObjectHeaders", "Allocation Invalid.");
		return;
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectHeaders", "Identifier Invalid.");
		return;
	}
	if (pHeaders == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectHeaders()", "pHeaders == NULLPTR");
		return;
	}
	if (pHeadersSize == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectHeaders()", "pHeadersSize == NULLPTR");
		return;
	}
#endif
	Object* pObject = Get_ObjectPointer(Allocation);
	for (size_t i = 0; i < pObject->Header.iResourceHeadersSize; i++)
	{
		if (Get_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i])->Header.Allocation.Identifier == Identifier)
		{		
			uint64_t HeadersSize = *pHeadersSize;
			Resize_Array((void**)pHeaders, HeadersSize, HeadersSize + 1, sizeof(ResourceHeaderAllocation));
			ResourceHeaderAllocation* Headers = *pHeaders;
			Headers[HeadersSize] = pObject->Header.iResourceHeaders[i];
			*pHeadersSize += 1;
		}
	}
}
/*
* Added in 1.0.0
* Macro for scanning all resourceheader childs of specified identifier of a gameobject, 
* except unlike Scan_ObjectHeaders() it only returns the first found of specified identifier. 
* @param pHeaders is a pointer to an array of allocations to return.
* @param pHeadersSize is a pointer to size of the array to return.
* @note Externally Synchronized.
*/
ResourceHeader* Scan_ObjectHeadersSingle(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier)
{
#ifndef NDEBUG
	if (Get_ObjectAllocationValidity(Allocation) == Failure)
	{
		Engine_Ref_ArgsError("Scan_ObjectHeadersSingle", "Allocation Invalid.");
		return NULL;
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectHeadersSingle", "Identifier Invalid.");
		return NULL;
	}
#endif
	Object* pObject = Get_ObjectPointer(Allocation);
	for (size_t i = 0; i < pObject->Header.iResourceHeadersSize; i++)
		if (Get_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i])->Header.Allocation.Identifier == Identifier)
			return Get_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i]);

	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Registration Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Registers a Signature struct with the API so you can create objects of that type, This creates an internal refrence to the signature in the API, so do not modify!
* @param pSignature is a pointer to the signature to register.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Register_ObjectSignature(ObjectSignature* pSignature)
{
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("Register_ObjectSignature()", "pSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ObjectSignaturesMutex);
	for (size_t i = 0; i < Utils.ObjectSignaturesSize; i++)
	{
		if (Utils.ObjectSignatures[i]->Identifier == pSignature->Identifier)
		{
			Engine_Ref_ArgsError("Register_ObjectSignature()", "pSignature->Identifier Already Used.");
			Engine_Ref_Unlock_Mutex(Utils.ObjectSignaturesMutex);
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
	}
	Resize_Array((void**)&Utils.ObjectSignatures, Utils.ObjectSignaturesSize, Utils.ObjectSignaturesSize + 1, sizeof(*Utils.ObjectSignatures));
	Utils.ObjectSignatures[Utils.ObjectSignaturesSize] = pSignature;
	Utils.ObjectSignaturesSize++;
	Engine_Ref_Unlock_Mutex(Utils.ObjectSignaturesMutex);
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Registers a Signature struct with the API so you can create objects of that type, This creates an internal refrence to the signature in the API, so do not modify!
* @param pSignature is a pointer to the signature to register.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Register_ResourceHeaderSignature(ResourceHeaderSignature* pSignature)
{
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("Register_ResourceHeaderSignature()", "pSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ResourceHeaderSignaturesMutex);
	for (size_t i = 0; i < Utils.ResourceHeaderSignaturesSize; i++)
	{
		if (Utils.ResourceHeaderSignatures[i]->Identifier == pSignature->Identifier)
		{
			Engine_Ref_ArgsError("Register_ResourceHeaderSignature()", "pSignature->Identifier Already Used.");
			Engine_Ref_Unlock_Mutex(Utils.ResourceHeaderSignaturesMutex);
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
	}
	Resize_Array((void**)&Utils.ResourceHeaderSignatures, Utils.ResourceHeaderSignaturesSize, Utils.ResourceHeaderSignaturesSize + 1, sizeof(*Utils.ResourceHeaderSignatures));
	Utils.ResourceHeaderSignatures[Utils.ResourceHeaderSignaturesSize] = pSignature;
	Utils.ResourceHeaderSignaturesSize++;
	Engine_Ref_Unlock_Mutex(Utils.ResourceHeaderSignaturesMutex);
	return (TEXRESULT)(Success);
}
/*
* Added in 1.0.0
* Registers a Signature struct with the API so you can create objects of that type, This creates an internal refrence to the signature in the API, so do not modify!
* @param pSignature is a pointer to the signature to register.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Register_ElementSignature(ElementSignature* pSignature)
{
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("Register_ElementSignature()", "pSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ElementSignaturesMutex);
	for (size_t i = 0; i < Utils.ElementSignaturesSize; i++)
	{
		if (Utils.ElementSignatures[i]->Identifier == pSignature->Identifier)
		{
			Engine_Ref_ArgsError("Register_ElementSignature()", "pSignature->Identifier Already Used.");
			Engine_Ref_Unlock_Mutex(Utils.ElementSignaturesMutex);
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
	}
	Resize_Array((void**)&Utils.ElementSignatures, Utils.ElementSignaturesSize, Utils.ElementSignaturesSize + 1, sizeof(*Utils.ElementSignatures));
	Utils.ElementSignatures[Utils.ElementSignaturesSize] = pSignature;
	Utils.ElementSignaturesSize++;
	Engine_Ref_Unlock_Mutex(Utils.ElementSignaturesMutex);
	return (TEXRESULT)(Success);
} 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//De-Registration Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Removes the internal refrence to the signature in the API.
* @param pSignature is a pointer to the signature to deregister.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT DeRegister_ObjectSignature(ObjectSignature* pSignature)
{
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ObjectSignature()", "pSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ObjectSignaturesMutex);
	for (size_t i = 0; i < Utils.ObjectSignaturesSize; i++)
	{
		if (Utils.ObjectSignatures[i] == pSignature)
		{
			RemoveMember_Array((void**)&Utils.ObjectSignatures, Utils.ObjectSignaturesSize, i, sizeof(*Utils.ObjectSignatures), 1);
			Utils.ObjectSignaturesSize--;
			Engine_Ref_Unlock_Mutex(Utils.ObjectSignaturesMutex);
			return (TEXRESULT)(Success);
		}
	}
	Engine_Ref_ArgsError("DeRegister_ObjectSignature()", "pSignature Not Found.");
	Engine_Ref_Unlock_Mutex(Utils.ObjectSignaturesMutex);
	return (TEXRESULT)(Invalid_Parameter | Failure);
}
/*
* Added in 1.0.0
* Removes the internal refrence to the signature in the API.
* @param pSignature is a pointer to the signature to deregister.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT DeRegister_ResourceHeaderSignature(ResourceHeaderSignature* pSignature)
{
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ResourceHeaderSignature()", "pSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ResourceHeaderSignaturesMutex);
	for (size_t i = 0; i < Utils.ResourceHeaderSignaturesSize; i++)
	{
		if (Utils.ResourceHeaderSignatures[i] == pSignature)
		{
			RemoveMember_Array((void**)&Utils.ResourceHeaderSignatures, Utils.ResourceHeaderSignaturesSize, i, sizeof(*Utils.ResourceHeaderSignatures), 1);
			Utils.ResourceHeaderSignaturesSize--;
			Engine_Ref_Unlock_Mutex(Utils.ResourceHeaderSignaturesMutex);
			return (TEXRESULT)(Success);
		}
	}
	Engine_Ref_ArgsError("DeRegister_ResourceHeaderSignature()", "pSignature Not Found.");
	Engine_Ref_Unlock_Mutex(Utils.ResourceHeaderSignaturesMutex);
	return (TEXRESULT)(Invalid_Parameter | Failure);
}
/*
* Added in 1.0.0
* Removes the internal refrence to the signature in the API.
* @param pSignature is a pointer to the signature to deregister.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT DeRegister_ElementSignature(ElementSignature* pSignature)
{
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ElementSignature()", "pSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ElementSignaturesMutex);
	for (size_t i = 0; i < Utils.ElementSignaturesSize; i++)
	{
		if (Utils.ElementSignatures[i] == pSignature)
		{
			RemoveMember_Array((void**)&Utils.ElementSignatures, Utils.ElementSignaturesSize, i, sizeof(*Utils.ElementSignatures), 1);
			Utils.ElementSignaturesSize--;
			Engine_Ref_Unlock_Mutex(Utils.ElementSignaturesMutex);
			return (TEXRESULT)(Success);
		}
	}
	Engine_Ref_ArgsError("DeRegister_ElementSignature()", "pSignature Not Found.");
	Engine_Ref_Unlock_Mutex(Utils.ElementSignaturesMutex);
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BIN Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Documentation Incomplete
*/
TEXRESULT Write_TEIF(const UTF8* Path, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Path == NULL)
	{
		Engine_Ref_ArgsError("Read_TEIF()", "Path == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	FILE* file = fopen((char*)Path, "wb"); //open file
	if (file == NULL)
	{
		Engine_Ref_ArgsError("Write_TEIF()", "Failed to open file.");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}

	uint64_t FinalObjectSize = 0;
	uint64_t FinalResourceHeaderSize = 0;
	uint64_t FinalElementSize = 0;
	uint64_t FinalBufferSize = 0;

	for (size_t i = 0; i < Utils.ObjectSignaturesSize; i++)
	{
		ObjectSignature* pSignature = Utils.ObjectSignatures[i];
		if (pSignature->Buffer != NULL)
		{
			for (size_t i1 = 0; i1 < pSignature->Buffer->Size;)
			{
				Object* pObject = &pSignature->Buffer->Buffer[i1];
				if (pObject->Header.AllocationSize != NULL && pObject->Header.Allocation.Identifier == pSignature->Identifier)
				{
					if (pSignature->Packer != NULL)
					{
						Pack_ObjectTemplate* func = *pSignature->Packer;
						func(pObject, NULL, &FinalBufferSize, NULL, ThreadIndex);
					}

					FinalBufferSize += sizeof(*pObject->Header.iResourceHeaders) * pObject->Header.iResourceHeadersSize;
					FinalBufferSize += sizeof(*pObject->Header.iChildren) * pObject->Header.iChildrenSize;

					if (pObject->Header.Name != NULL)
						FinalBufferSize += strlen((const char*)pObject->Header.Name) + 1;

					FinalObjectSize += pObject->Header.AllocationSize;
					i1 += pObject->Header.AllocationSize;
				}
				else
				{
					i1++;
				}
			}
		}
	}
	for (size_t i = 0; i < Utils.ResourceHeaderSignaturesSize; i++)
	{
		ResourceHeaderSignature* pSignature = Utils.ResourceHeaderSignatures[i];
		if (pSignature->Buffer != NULL)
		{
			for (size_t i1 = 0; i1 < pSignature->Buffer->Size;)
			{
				ResourceHeader* pResourceHeader = &pSignature->Buffer->Buffer[i1];
				if (pResourceHeader->Header.AllocationSize != NULL && pResourceHeader->Header.Allocation.Identifier == pSignature->Identifier)
				{
					if (pSignature->Packer != NULL)
					{
						Pack_ResourceHeaderTemplate* func = *pSignature->Packer;
						func(pResourceHeader, NULL, &FinalBufferSize, NULL, ThreadIndex);
					}

					FinalBufferSize += sizeof(*pResourceHeader->Header.iElements) * pResourceHeader->Header.iElementsSize;
					FinalBufferSize += sizeof(*pResourceHeader->Header.iParents) * pResourceHeader->Header.iParentsSize;

					if (pResourceHeader->Header.Name != NULL)
						FinalBufferSize += strlen((const char*)pResourceHeader->Header.Name) + 1;

					FinalResourceHeaderSize += pResourceHeader->Header.AllocationSize;
					i1 += pResourceHeader->Header.AllocationSize;
				}
				else
				{
					i1++;
				}
			}
		}
	}
	for (size_t i = 0; i < Utils.ElementSignaturesSize; i++)
	{
		ElementSignature* pSignature = Utils.ElementSignatures[i];
		if (pSignature->Buffer != NULL)
		{
			for (size_t i1 = 0; i1 < pSignature->Buffer->Size;)
			{
				Element* pElement = &pSignature->Buffer->Buffer[i1];
				if (pElement->Header.AllocationSize != NULL && pElement->Header.Allocation.Identifier == pSignature->Identifier)
				{
					if (pSignature->Packer != NULL)
					{
						Pack_ElementTemplate* func = *pSignature->Packer;
						func(pElement, NULL, &FinalBufferSize, NULL, ThreadIndex);
					}

					FinalBufferSize += sizeof(*pElement->Header.iParents) * pElement->Header.iParentsSize;

					if (pElement->Header.Name != NULL)
						FinalBufferSize += strlen((const char*)pElement->Header.Name) + 1;

					FinalElementSize += pElement->Header.AllocationSize;
					i1 += pElement->Header.AllocationSize;
				}
				else
				{
					i1++;
				}
			}
		}
	}

	TEIF_HEADER header;
	memset(&header, 0, sizeof(header));
	header.filecode[0] = 'T'; header.filecode[1] = 'E'; header.filecode[2] = 'I'; header.filecode[3] = 'F';

	Object* ObjectsData = NULL;
	uint64_t FinalObjectPointer = 0;
	if (FinalObjectSize != NULL)
	{
		ObjectsData = (Object*)malloc(FinalObjectSize * sizeof(Object));
		if (ObjectsData == NULL)
		{
			Engine_Ref_ArgsError("Write_TEIF()", "Out Of Memory.");
			return (TEXRESULT)(Out_Of_Memory_Result | Failure);
		}
	}
	ResourceHeader* ResourceHeadersData = NULL;
	uint64_t FinalResourceHeaderPointer = 0;
	if (FinalResourceHeaderSize != NULL)
	{
		ResourceHeadersData = (ResourceHeader*)malloc(FinalResourceHeaderSize * sizeof(ResourceHeader));
		if (ResourceHeadersData == NULL)
		{
			Engine_Ref_ArgsError("Write_TEIF()", "Out Of Memory.");
			return (TEXRESULT)(Out_Of_Memory_Result | Failure);
		}
	}
	Element* ElementsData = NULL;
	uint64_t FinalElementPointer = 0;
	if (FinalElementSize != NULL)
	{
		ElementsData = (Element*)malloc(FinalElementSize * sizeof(Element));
		if (ElementsData == NULL)
		{
			Engine_Ref_ArgsError("Write_TEIF()", "Out Of Memory.");
			return (TEXRESULT)(Out_Of_Memory_Result | Failure);
		}
	}
	uint8_t* MiscDataBuffer = NULL;
	uint64_t FinalBufferPointer = 0;
	if (FinalBufferSize != NULL)
	{
		MiscDataBuffer = (uint8_t*)malloc(FinalBufferSize);
		if (MiscDataBuffer == NULL)
		{
			Engine_Ref_ArgsError("Write_TEIF()", "Out Of Memory.");
			return (TEXRESULT)(Out_Of_Memory_Result | Failure);
		}
	}

	for (size_t i = 0; i < Utils.ObjectSignaturesSize; i++)
	{
		ObjectSignature* pSignature = Utils.ObjectSignatures[i];
		if (pSignature->Buffer != NULL)
		{
			for (size_t i1 = 0; i1 < pSignature->Buffer->Size;)
			{
				Object* pObject = &pSignature->Buffer->Buffer[i1];
				if (pObject->Header.AllocationSize != NULL && pObject->Header.Allocation.Identifier == pSignature->Identifier)
				{
					memcpy(&ObjectsData[FinalObjectPointer], pObject, pObject->Header.AllocationSize * sizeof(Object));
					Object* pCopiedObject = &ObjectsData[FinalObjectPointer];
					if (pSignature->Packer != NULL)
					{
						Pack_ObjectTemplate* func = *pSignature->Packer;
						func(pObject, pCopiedObject, &FinalBufferPointer, MiscDataBuffer, ThreadIndex);
					}
					if (pObject->Header.iResourceHeadersSize != NULL)
					{
						memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pObject->Header.iResourceHeaders, sizeof(*pObject->Header.iResourceHeaders) * pObject->Header.iResourceHeadersSize);
						pCopiedObject->Header.iResourceHeaders = (ResourceHeaderAllocation*)FinalBufferPointer;
						FinalBufferPointer += sizeof(*pObject->Header.iResourceHeaders) * pObject->Header.iResourceHeadersSize;
					}
					if (pObject->Header.iChildrenSize != NULL)
					{
						memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pObject->Header.iChildren, sizeof(*pObject->Header.iChildren) * pObject->Header.iChildrenSize);
						pCopiedObject->Header.iChildren = (ObjectAllocation*)FinalBufferPointer;
						FinalBufferPointer += sizeof(*pObject->Header.iChildren) * pObject->Header.iChildrenSize;
					}
					if (pObject->Header.Name != NULL)
					{
						memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pObject->Header.Name, strlen((char*)pObject->Header.Name) + 1);
						pCopiedObject->Header.Name = (UTF8*)FinalBufferPointer;
						FinalBufferPointer += strlen((char*)pObject->Header.Name) + 1;
					}
					FinalObjectPointer += pObject->Header.AllocationSize;
					i1 += pObject->Header.AllocationSize;
				}
				else
				{
					i1++;
				}
			}
		}
	}
	for (size_t i = 0; i < Utils.ResourceHeaderSignaturesSize; i++)
	{
		ResourceHeaderSignature* pSignature = Utils.ResourceHeaderSignatures[i];
		if (pSignature->Buffer != NULL)
		{
			for (size_t i1 = 0; i1 < pSignature->Buffer->Size;)
			{
				ResourceHeader* pResourceHeader = &pSignature->Buffer->Buffer[i1];
				if (pResourceHeader->Header.AllocationSize != NULL && pResourceHeader->Header.Allocation.Identifier == pSignature->Identifier)
				{
					memcpy(&ResourceHeadersData[FinalResourceHeaderPointer], pResourceHeader, pResourceHeader->Header.AllocationSize * sizeof(ResourceHeader));
					ResourceHeader* pCopiedResourceHeader = &ResourceHeadersData[FinalResourceHeaderPointer];
					if (pSignature->Packer != NULL)
					{
						Pack_ResourceHeaderTemplate* func = *pSignature->Packer;
						func(pResourceHeader, pCopiedResourceHeader, &FinalBufferPointer, MiscDataBuffer, ThreadIndex);
					}
					if (pResourceHeader->Header.iElementsSize != NULL)
					{
						memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pResourceHeader->Header.iElements, sizeof(*pResourceHeader->Header.iElements) * pResourceHeader->Header.iElementsSize);
						pCopiedResourceHeader->Header.iElements = (ElementAllocation*)FinalBufferPointer;
						FinalBufferPointer += sizeof(*pResourceHeader->Header.iElements) * pResourceHeader->Header.iElementsSize;
					}
					if (pResourceHeader->Header.iParentsSize != NULL)
					{
						memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pResourceHeader->Header.iParents, sizeof(*pResourceHeader->Header.iParents) * pResourceHeader->Header.iParentsSize);
						pCopiedResourceHeader->Header.iParents = (ObjectAllocation*)FinalBufferPointer;
						FinalBufferPointer += sizeof(*pResourceHeader->Header.iParents) * pResourceHeader->Header.iParentsSize;
					}
					if (pResourceHeader->Header.Name != NULL)
					{
						memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pResourceHeader->Header.Name, strlen((char*)pResourceHeader->Header.Name) + 1);
						pCopiedResourceHeader->Header.Name = (UTF8*)FinalBufferPointer;
						FinalBufferPointer += strlen((char*)pResourceHeader->Header.Name) + 1;
					}
					FinalResourceHeaderPointer += pResourceHeader->Header.AllocationSize;
					i1 += pResourceHeader->Header.AllocationSize;
				}
				else
				{
					i1++;
				}
			}
		}
	}
	for (size_t i = 0; i < Utils.ElementSignaturesSize; i++)
	{
		ElementSignature* pSignature = Utils.ElementSignatures[i];
		if (pSignature->Buffer != NULL)
		{
			for (size_t i1 = 0; i1 < pSignature->Buffer->Size;)
			{
				Element* pElement = &pSignature->Buffer->Buffer[i1];
				if (pElement->Header.AllocationSize != NULL && pElement->Header.Allocation.Identifier == pSignature->Identifier)
				{
					memcpy(&ElementsData[FinalElementPointer], pElement, pElement->Header.AllocationSize * sizeof(Element));
					Element* pCopiedElement = &ElementsData[FinalElementPointer];
					if (pSignature->Packer != NULL)
					{
						Pack_ElementTemplate* func = *pSignature->Packer;
						func(pElement, pCopiedElement, &FinalBufferPointer, MiscDataBuffer, ThreadIndex);
					}
					if (pElement->Header.iParentsSize != NULL)
					{
						memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pElement->Header.iParents, sizeof(*pElement->Header.iParents) * pElement->Header.iParentsSize);
						pCopiedElement->Header.iParents = (ResourceHeaderAllocation*)FinalBufferPointer;
						FinalBufferPointer += sizeof(*pElement->Header.iParents) * pElement->Header.iParentsSize;
					}
					if (pElement->Header.Name != NULL)
					{
						memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pElement->Header.Name, strlen((char*)pElement->Header.Name) + 1);
						pCopiedElement->Header.Name = (UTF8*)FinalBufferPointer;
						FinalBufferPointer += strlen((char*)pElement->Header.Name) + 1;
					}
					FinalElementPointer += pElement->Header.AllocationSize;
					i1 += pElement->Header.AllocationSize;
				}
				else
				{
					i1++;
				}
			}
		}
	}

	header.DataBufferOffset = sizeof(TEIF_HEADER);
	header.DataBufferSize = FinalBufferSize;

	header.ObjectsOffset = sizeof(TEIF_HEADER) + (FinalBufferSize);
	header.ObjectsSize = FinalObjectSize;

	header.ResourceHeadersOffset = sizeof(TEIF_HEADER) + (FinalBufferSize + (FinalObjectSize * sizeof(Object)));
	header.ResourceHeadersSize = FinalResourceHeaderSize;

	header.ElementsOffset = sizeof(TEIF_HEADER) + (FinalBufferSize + (FinalObjectSize * sizeof(Object)) + (FinalResourceHeaderSize * sizeof(ResourceHeader)));
	header.ElementsSize = FinalElementSize;


	fwrite(&header, sizeof(TEIF_HEADER), 1, file);

	if (FinalBufferSize != NULL)
		fwrite(MiscDataBuffer, sizeof(uint8_t), FinalBufferSize, file);
	if (FinalObjectSize != NULL)
		fwrite(ObjectsData, sizeof(Object), FinalObjectSize, file);
	if (FinalResourceHeaderSize != NULL)
		fwrite(ResourceHeadersData, sizeof(ResourceHeader), FinalResourceHeaderSize, file);
	if (FinalElementSize != NULL)
		fwrite(ElementsData, sizeof(Element), FinalElementSize, file);

	if (FinalBufferSize != NULL)
		free(MiscDataBuffer);
	if (FinalObjectSize != NULL)
		free(ObjectsData);
	if (FinalResourceHeaderSize != NULL)
		free(ResourceHeadersData);
	if (FinalElementSize != NULL)
		free(ElementsData);
	
	fclose(file);
	return Success;
}
/*
* Added in 1.0.0
* Documentation Incomplete
*/
TEXRESULT Read_TEIF(const UTF8* Path, uint32_t ThreadIndex)
{
	TEXRESULT tres = Success;
#ifndef NDEBUG
	if (Path == NULL)
	{
		Engine_Ref_ArgsError("Read_TEIF()", "Path == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	FileData data = { 0, 0 };
	Open_Data(&data, Path);
	if (data.pData == NULL)
	{
		Engine_Ref_ArgsError("Read_TEIF()", "Failed to open file.");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}

	TEIF_HEADER* pHeader = (TEIF_HEADER*)data.pData;
	if (strncmp(pHeader->filecode, "TEIF", 4) != 0)
	{
		Engine_Ref_ArgsError("Read_TEIF()", "Filecode Not Equal To TEIF, Invalid File Format!");
		return (TEXRESULT)(Invalid_Format | Failure);
	}

	Object* pObjects = (Object*)((void*)((uint64_t)data.pData + (uint64_t)pHeader->ObjectsOffset));
	uint64_t ObjectsSize = pHeader->ObjectsSize;

	ResourceHeader* pResourceHeaders = (ResourceHeader*)((void*)((uint64_t)data.pData + (uint64_t)pHeader->ResourceHeadersOffset));
	uint64_t ResourceHeadersSize = pHeader->ResourceHeadersSize;

	Element* pElements = (Element*)((void*)((uint64_t)data.pData + (uint64_t)pHeader->ElementsOffset));
	uint64_t ElementsSize = pHeader->ElementsSize;

	uint8_t* pDataBuffer = (uint8_t*)((void*)((uint64_t)data.pData + (uint64_t)pHeader->DataBufferOffset));

	//place items in the buffers and unpack them
	for (size_t i = 0; i < ObjectsSize;)
	{
		Object* pObject = &pObjects[i];

		ObjectSignature* pSignature = NULL;
		Find_ObjectSignature(pObject->Header.Allocation.Identifier, &pSignature, NULL);

		Object* pCopiedObject = &pSignature->Buffer->Buffer[pObject->Header.Allocation.Pointer];
		memcpy(pCopiedObject, pObject, pObject->Header.AllocationSize * sizeof(*pObject));
		if (pObject->Header.iResourceHeadersSize != NULL)
		{
			pCopiedObject->Header.iResourceHeaders = (ResourceHeaderAllocation*)malloc(sizeof(*pCopiedObject->Header.iResourceHeaders) * pObject->Header.iResourceHeadersSize);
			memcpy(pCopiedObject->Header.iResourceHeaders, (void*)((uint64_t)pDataBuffer + (uint64_t)pObject->Header.iResourceHeaders), sizeof(*pCopiedObject->Header.iResourceHeaders) * pObject->Header.iResourceHeadersSize);
		}
		if (pObject->Header.iChildrenSize != NULL)
		{
			pCopiedObject->Header.iChildren = (ObjectAllocation*)malloc(sizeof(*pCopiedObject->Header.iChildren) * pObject->Header.iChildrenSize);
			memcpy(pCopiedObject->Header.iChildren, (void*)((uint64_t)pDataBuffer + (uint64_t)pObject->Header.iChildren), sizeof(*pCopiedObject->Header.iChildren) * pObject->Header.iChildrenSize);
		}
		if (pObject->Header.Name != NULL)
		{
			const UTF8* pName = (UTF8*)((void*)((uint64_t)pDataBuffer + (uint64_t)pObject->Header.Name));
			pCopiedObject->Header.Name = (UTF8*)malloc(strlen((char*)pName) + 1);
			memcpy((void*)pCopiedObject->Header.Name, pName, strlen((char*)pName) + 1);
		}
		if (pSignature->UnPacker != NULL)
		{
			UnPack_ObjectTemplate* func = *pSignature->UnPacker;
			func(pObject, pCopiedObject, pDataBuffer, ThreadIndex);
		}
		if (pSignature->ReConstructor != NULL)
		{
			ReCreate_ObjectTemplate* pFunction = *pSignature->ReConstructor;
			if ((tres = pFunction(pObject, ThreadIndex)) != Success)
				return tres;
		}
		i += pObject->Header.AllocationSize;
	}
	for (size_t i = 0; i < ResourceHeadersSize;)
	{
		ResourceHeader* pResourceHeader = &pResourceHeaders[i];

		ResourceHeaderSignature* pSignature = NULL;
		Find_ResourceHeaderSignature(pResourceHeader->Header.Allocation.Identifier, &pSignature, NULL);

		ResourceHeader* pCopiedResourceHeader = &pSignature->Buffer->Buffer[pResourceHeader->Header.Allocation.Pointer];
		memcpy(pCopiedResourceHeader, pResourceHeader, pResourceHeader->Header.AllocationSize * sizeof(*pResourceHeader));
		if (pResourceHeader->Header.iElementsSize != NULL)
		{
			pCopiedResourceHeader->Header.iElements = (ElementAllocation*)malloc(sizeof(*pResourceHeader->Header.iElements) * pResourceHeader->Header.iElementsSize);
			memcpy(pCopiedResourceHeader->Header.iElements, (void*)((uint64_t)pDataBuffer + (uint64_t)pResourceHeader->Header.iElements), sizeof(*pResourceHeader->Header.iElements) * pResourceHeader->Header.iElementsSize);
		}
		if (pResourceHeader->Header.iParentsSize != NULL)
		{
			pCopiedResourceHeader->Header.iParents = (ObjectAllocation*)malloc(sizeof(*pResourceHeader->Header.iParents) * pResourceHeader->Header.iParentsSize);
			memcpy(pCopiedResourceHeader->Header.iParents, (void*)((uint64_t)pDataBuffer + (uint64_t)pResourceHeader->Header.iParents), sizeof(*pResourceHeader->Header.iParents) * pResourceHeader->Header.iParentsSize);
		}
		if (pResourceHeader->Header.Name != NULL)
		{
			const UTF8* pName = (UTF8*)((void*)((uint64_t)pDataBuffer + (uint64_t)pResourceHeader->Header.Name));
			pCopiedResourceHeader->Header.Name = (UTF8*)malloc(strlen((char*)pName) + 1);
			memcpy((void*)pCopiedResourceHeader->Header.Name, pName, strlen((char*)pName) + 1);
		}
		if (pSignature->UnPacker != NULL)
		{
			UnPack_ResourceHeaderTemplate* func = *pSignature->UnPacker;
			func(pResourceHeader, pCopiedResourceHeader, pDataBuffer, ThreadIndex);
		}
		if (pSignature->ReConstructor != NULL)
		{
			ReCreate_ResourceHeaderTemplate* pFunction = *pSignature->ReConstructor;
			if ((tres = pFunction(pResourceHeader, ThreadIndex)) != Success)
				return tres;
		}
		i += pResourceHeader->Header.AllocationSize;
	}
	for (size_t i = 0; i < ElementsSize;)
	{
		Element* pElement = &pElements[i];	

		ElementSignature* pSignature = NULL;
		Find_ElementSignature(pElement->Header.Allocation.Identifier, &pSignature, NULL);

		Element* pCopiedElement = &pSignature->Buffer->Buffer[pElement->Header.Allocation.Pointer];
		memcpy(pCopiedElement, pElement, pElement->Header.AllocationSize * sizeof(*pElement));
		if (pElement->Header.iParentsSize != NULL)
		{
			pCopiedElement->Header.iParents = (ResourceHeaderAllocation*)malloc(sizeof(*pElement->Header.iParents) * pElement->Header.iParentsSize);
			memcpy(pCopiedElement->Header.iParents, (void*)((uint64_t)pDataBuffer + (uint64_t)pElement->Header.iParents), sizeof(*pElement->Header.iParents) * pElement->Header.iParentsSize);
		}
		if (pElement->Header.Name != NULL)
		{
			const UTF8* pName = (UTF8*)((void*)((uint64_t)pDataBuffer + (uint64_t)pElement->Header.Name));
			pCopiedElement->Header.Name = (UTF8*)malloc(strlen((char*)pName) + 1);
			memcpy((void*)pCopiedElement->Header.Name, pName, strlen((char*)pName) + 1);
		}
		if (pSignature->UnPacker != NULL)
		{
			UnPack_ElementTemplate* func = *pSignature->UnPacker;
			func(pElement, pCopiedElement, pDataBuffer, ThreadIndex);
		}
		if (pSignature->ReConstructor != NULL)
		{
			ReCreate_ElementTemplate* pFunction = *pSignature->ReConstructor;
			if ((tres = pFunction(pElement, ThreadIndex)) != Success)
				return tres;
		}
		i += pElement->Header.AllocationSize;
	}
	free(data.pData);
	return Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Initialise_Objects()
{
	memset(&Utils, 0, sizeof(Utils));
	memset(&Config, 0, sizeof(Config));
	Config.InitialParametersMax = 1024;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Signatures
	///////////////////////////////////////////////////////////////////////////////////////////////

	Engine_Ref_Create_Mutex(Utils.ObjectSignaturesMutex, MutexType_Plain);
	Engine_Ref_Create_Mutex(Utils.ResourceHeaderSignaturesMutex, MutexType_Plain);
	Engine_Ref_Create_Mutex(Utils.ElementSignaturesMutex, MutexType_Plain);


	Utils.InternalElementSig.Identifier = NULL;
	Utils.InternalResourceHeaderSig.Identifier = NULL;
	Utils.InternalObjectSig.Identifier = NULL;

	Utils.InternalElementSig.ByteLength = sizeof(Element);
	Utils.InternalResourceHeaderSig.ByteLength = sizeof(ResourceHeader);
	Utils.InternalObjectSig.ByteLength = sizeof(Object);

	Create_ElementBuffer(&Utils.InternalElementBuffer, Config.InitialParametersMax);
	Create_ResourceHeaderBuffer(&Utils.InternalResourceHeaderBuffer, Config.InitialParametersMax);
	Create_ObjectBuffer(&Utils.InternalObjectBuffer, Config.InitialParametersMax);

	Utils.InternalElementSig.Buffer = &Utils.InternalElementBuffer;
	Utils.InternalResourceHeaderSig.Buffer = &Utils.InternalResourceHeaderBuffer;
	Utils.InternalObjectSig.Buffer = &Utils.InternalObjectBuffer;

	Register_ElementSignature(&Utils.InternalElementSig);
	Register_ResourceHeaderSignature(&Utils.InternalResourceHeaderSig);
	Register_ObjectSignature(&Utils.InternalObjectSig);

	Create_ElementBuffer(&Utils.GenericElementBuffer, Config.InitialParametersMax);
	Create_ResourceHeaderBuffer(&Utils.GenericResourceHeaderBuffer, Config.InitialParametersMax);
	Create_ObjectBuffer(&Utils.GenericObjectBuffer, Config.InitialParametersMax);

	Utils.GenericElementSig.Identifier = (uint32_t)Element_Generic;
	Utils.GenericResourceHeaderSig.Identifier = (uint32_t)ResourceHeader_Generic;
	Utils.GenericObjectSig.Identifier = (uint32_t)Object_Generic;

	Utils.GenericElementSig.ByteLength = sizeof(Element);
	Utils.GenericResourceHeaderSig.ByteLength = sizeof(ResourceHeader);
	Utils.GenericObjectSig.ByteLength = sizeof(Object);

	Utils.GenericElementSig.Buffer = &Utils.GenericElementBuffer;
	Utils.GenericResourceHeaderSig.Buffer = &Utils.GenericResourceHeaderBuffer;
	Utils.GenericObjectSig.Buffer = &Utils.GenericObjectBuffer;

	Register_ElementSignature(&Utils.GenericElementSig);
	Register_ResourceHeaderSignature(&Utils.GenericResourceHeaderSig);
	Register_ObjectSignature(&Utils.GenericObjectSig);

	return Success;
}

TEXRESULT Destroy_Objects()
{
	Destroy_ElementBuffer(&Utils.GenericElementBuffer);
	Destroy_ResourceHeaderBuffer(&Utils.GenericResourceHeaderBuffer);
	Destroy_ObjectBuffer(&Utils.GenericObjectBuffer);

	DeRegister_ElementSignature(&Utils.GenericElementSig);
	DeRegister_ResourceHeaderSignature(&Utils.GenericResourceHeaderSig);
	DeRegister_ObjectSignature(&Utils.GenericObjectSig);

	//Destroy_ElementBuffer(&Utils.InternalElementBuffer);
	//Destroy_ResourceHeaderBuffer(&Utils.InternalResourceHeaderBuffer);
	//Destroy_ObjectBuffer(&Utils.InternalObjectBuffer);

	DeRegister_ElementSignature(&Utils.InternalElementSig);
	DeRegister_ResourceHeaderSignature(&Utils.InternalResourceHeaderSig);
	DeRegister_ObjectSignature(&Utils.InternalObjectSig);


	if (Utils.ObjectSignatures != NULL && Utils.ObjectSignaturesSize != NULL)
		free(Utils.ObjectSignatures);
	Utils.ObjectSignatures = NULL;
	Utils.ObjectSignaturesSize = NULL;

	if (Utils.ResourceHeaderSignatures != NULL && Utils.ResourceHeaderSignaturesSize != NULL)
		free(Utils.ResourceHeaderSignatures);
	Utils.ResourceHeaderSignatures = NULL;
	Utils.ResourceHeaderSignaturesSize = NULL;

	if (Utils.ElementSignatures != NULL && Utils.ElementSignaturesSize != NULL)
		free(Utils.ElementSignatures);
	Utils.ElementSignatures = NULL;
	Utils.ElementSignaturesSize = NULL;


	Engine_Ref_Destroy_Mutex(Utils.ObjectSignaturesMutex, MutexType_Plain);
	Engine_Ref_Destroy_Mutex(Utils.ResourceHeaderSignaturesMutex, MutexType_Plain);
	Engine_Ref_Destroy_Mutex(Utils.ElementSignaturesMutex, MutexType_Plain);


	memset(&Utils, 0, sizeof(Utils));
	memset(&Config, 0, sizeof(Config));
	return Success;
}

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
	
	//Config
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData("Object::InitialParametersMax"), &Config.InitialParametersMax, 1, sizeof(Config.InitialParametersMax));


	//Resources
	ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData("Object::Utils"), &ObjectsRes.pUtils, &Utils);

	//Functions
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Initialise_Objects"), &ObjectsRes.pInitialise_Objects, &Initialise_Objects, Construct, 0.001f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_Objects"), &ObjectsRes.pDestroy_Objects, &Destroy_Objects, Destruct, 10000.0f, 0, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Find_ObjectSignature"), &ObjectsRes.pFind_ObjectSignature, &Find_ObjectSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Find_ResourceHeaderSignature"), &ObjectsRes.pFind_ResourceHeaderSignature, &Find_ResourceHeaderSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Find_ElementSignature"), &ObjectsRes.pFind_ElementSignature, &Find_ElementSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Get_ObjectPointer"), &ObjectsRes.pGet_ObjectPointer, &Get_ObjectPointer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Get_ResourceHeaderPointer"), &ObjectsRes.pGet_ResourceHeaderPointer, &Get_ResourceHeaderPointer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Get_ElementPointer"), &ObjectsRes.pGet_ElementPointer, &Get_ElementPointer, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_ObjectBuffer"), &ObjectsRes.pCreate_ObjectBuffer, &Create_ObjectBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_ResourceHeaderBuffer"), &ObjectsRes.pCreate_ResourceHeaderBuffer, &Create_ResourceHeaderBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_ElementBuffer"), &ObjectsRes.pCreate_ElementBuffer, &Create_ElementBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Resize_ObjectBuffer"), &ObjectsRes.pResize_ObjectBuffer, &Resize_ObjectBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Resize_ResourceHeaderBuffer"), &ObjectsRes.pResize_ResourceHeaderBuffer, &Resize_ResourceHeaderBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Resize_ElementBuffer"), &ObjectsRes.pResize_ElementBuffer, &Resize_ElementBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_ObjectBuffer"), &ObjectsRes.pDestroy_ObjectBuffer, &Destroy_ObjectBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_ResourceHeaderBuffer"), &ObjectsRes.pDestroy_ResourceHeaderBuffer, &Destroy_ResourceHeaderBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_ElementBuffer"), &ObjectsRes.pDestroy_ElementBuffer, &Destroy_ElementBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::CreateInstance_Object"), &ObjectsRes.pCreateInstance_Object, &CreateInstance_Object, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::CreateInstance_ResourceHeader"), &ObjectsRes.pCreateInstance_ResourceHeader, &CreateInstance_ResourceHeader, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::CreateInstance_Element"), &ObjectsRes.pCreateInstance_Element, &CreateInstance_Element, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_Object"), &ObjectsRes.pCreate_Object, &Create_Object, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_ResourceHeader"), &ObjectsRes.pCreate_ResourceHeader, &Create_ResourceHeader, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_Element"), &ObjectsRes.pCreate_Element, &Create_Element, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_Object"), &ObjectsRes.pDestroy_Object, &Destroy_Object, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_ResourceHeader"), &ObjectsRes.pDestroy_ResourceHeader, &Destroy_ResourceHeader, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_Element"), &ObjectsRes.pDestroy_Element, &Destroy_Element, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::ReCreate_Object"), &ObjectsRes.pReCreate_Object, &ReCreate_Object, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::ReCreate_ResourceHeader"), &ObjectsRes.pReCreate_ResourceHeader, &ReCreate_ResourceHeader, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::ReCreate_Element"), &ObjectsRes.pReCreate_Element, &ReCreate_Element, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::StartThread_Object"), &ObjectsRes.pStartThread_Object, &StartThread_Object, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::StartThread_ResourceHeader"), &ObjectsRes.pStartThread_ResourceHeader, &StartThread_ResourceHeader, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::StartThread_Element"), &ObjectsRes.pStartThread_Element, &StartThread_Element, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::EndThread_Object"), &ObjectsRes.pEndThread_Object, &EndThread_Object, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::EndThread_ResourceHeader"), &ObjectsRes.pEndThread_ResourceHeader, &EndThread_ResourceHeader, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::EndThread_Element"), &ObjectsRes.pEndThread_Element, &EndThread_Element, (CallFlagBits)NULL, 0.0f, NULL, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Add_ObjectChild"), &ObjectsRes.pAdd_ObjectChild, &Add_ObjectChild, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Add_Object_ResourceHeaderChild"), &ObjectsRes.pAdd_Object_ResourceHeaderChild, &Add_Object_ResourceHeaderChild, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Add_ResourceHeader_ElementChild"), &ObjectsRes.pAdd_ResourceHeader_ElementChild, &Add_ResourceHeader_ElementChild, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Remove_ObjectChild"), &ObjectsRes.pRemove_ObjectChild, &Remove_ObjectChild, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Remove_Object_ResourceHeaderChild"), &ObjectsRes.pRemove_Object_ResourceHeaderChild, &Remove_Object_ResourceHeaderChild, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Remove_ResourceHeader_ElementChild"), &ObjectsRes.pRemove_ResourceHeader_ElementChild, &Remove_ResourceHeader_ElementChild, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Register_ObjectSignature"), &ObjectsRes.pRegister_ObjectSignature, &Register_ObjectSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Register_ResourceHeaderSignature"), &ObjectsRes.pRegister_ResourceHeaderSignature, &Register_ResourceHeaderSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Register_ElementSignature"), &ObjectsRes.pRegister_ElementSignature, &Register_ElementSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::DeRegister_ObjectSignature"), &ObjectsRes.pDeRegister_ObjectSignature, &DeRegister_ObjectSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::DeRegister_ResourceHeaderSignature"), &ObjectsRes.pDeRegister_ResourceHeaderSignature, &DeRegister_ResourceHeaderSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::DeRegister_ElementSignature"), &ObjectsRes.pDeRegister_ElementSignature, &DeRegister_ElementSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Scan_ObjectChilds"), &ObjectsRes.pScan_ObjectChilds, &Scan_ObjectChilds, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Scan_ObjectParents"), &ObjectsRes.pScan_ObjectParents, &Scan_ObjectParents, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Scan_ObjectHeaders"), &ObjectsRes.pScan_ObjectHeaders, &Scan_ObjectHeaders, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Scan_ObjectHeadersSingle"), &ObjectsRes.pScan_ObjectHeadersSingle, &Scan_ObjectHeadersSingle, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Write_TEIF"), &ObjectsRes.pWrite_TEIF, &Write_TEIF, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Read_TEIF"), &ObjectsRes.pRead_TEIF, &Read_TEIF, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	
	

}
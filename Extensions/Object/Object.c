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
#include "Common.h"
#include "Extension.h"
#define TEX_EXPOSE_OBJECTS
#include "Object.h"

volatile ObjectUtils Utils;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Arena Allocater Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Creates a object arena allocater.
* @param pArenaAllocater pointer to the allocater to create.
* @param StartPtr offset from the start of the gpu buffer to reserve for this arena, arena size = (EndPtr - StartPtr)
* @param EndPtr offset from the start of the gpu buffer to reserve for this arena, arena size = (EndPtr - StartPtr)
* @note Always Thread safe.
* @note Externally Synchronized.
*/
TEXRESULT Create_ArenaAllocater(ArenaAllocater* pArenaAllocater, uint64_t StartPtr, uint64_t EndPtr) {
#ifndef NDEBUG
	if (pArenaAllocater == NULL)
	{
		Engine_Ref_ArgsError("Create_ArenaAllocater()", "pArenaAllocater == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	memset(pArenaAllocater, 0, sizeof(*pArenaAllocater));
	Engine_Ref_Create_Mutex(&pArenaAllocater->Mutex, MutexType_Plain);
	pArenaAllocater->StartPtr = StartPtr;
	pArenaAllocater->EndPtr = EndPtr;
	return (Success);
}
/*
* Added in 1.0.0
* Destroys a object arena allocater.
* @param pArenaAllocater pointer to the allocater to destroy.
* @note Always Thread safe.
* @note Externally Synchronized.
*/
void Destroy_ArenaAllocater(ArenaAllocater* pArenaAllocater) {
#ifndef NDEBUG
	if (pArenaAllocater == NULL)
	{
		Engine_Ref_ArgsError("Destroy_ArenaAllocater()", "pArenaAllocater == NULLPTR");
		return;
	}
#endif
	if (TestNULL(&pArenaAllocater->Mutex, sizeof(pArenaAllocater->Mutex)))
		Engine_Ref_Destroy_Mutex(&pArenaAllocater->Mutex);
	pArenaAllocater->StartPtr = 0;
	pArenaAllocater->EndPtr = 0;
	memset(pArenaAllocater, 0, sizeof(*pArenaAllocater));
	return;
}
/*
* Added in 1.0.0
* ReCreates a object arena allocater, destroys previous and then creates again.
* @param pArenaAllocater pointer to the allocater to recreate.
* @param StartPtr offset from the start of the gpu buffer to reserve for this arena, arena size = (EndPtr - StartPtr)
* @param EndPtr offset from the start of the gpu buffer to reserve for this arena, arena size = (EndPtr - StartPtr)
* @note Always Thread safe.
* @note Externally Synchronized.
*/
TEXRESULT ReCreate_ArenaAllocater(ArenaAllocater* pArenaAllocater, uint64_t StartPtr, uint64_t EndPtr) {
#ifndef NDEBUG
	if (pArenaAllocater == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_ArenaAllocater()", "pArenaAllocater == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	Destroy_ArenaAllocater(pArenaAllocater);
	Create_ArenaAllocater(pArenaAllocater, StartPtr, EndPtr);
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Allocate Allocation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Allocate_ObjectAllocationData(ObjectSignature* pSignature, uint32_t Identifier, ObjectAllocation* pAllocation, uint32_t ThreadIndex) {
	ArenaAllocater* pArenaAllocater = NULL;
	uint64_t Pointer = 0;
	uint64_t SizeOfBlock = 0;
	uint64_t ResetCount = 0;
	uint64_t i = 0;
	while (true)
	{
		if (ResetCount < EngineRes.pUtils->CPU.MaxThreads)
		{
			if (Engine_Ref_TryLock_Mutex(&Utils.InternalObjectBuffer.AllocationDatas.ArenaAllocaters[Utils.InternalObjectBuffer.AllocationDatas.Indexes[ThreadIndex]].Mutex) == Success)
			{
				pArenaAllocater = &Utils.InternalObjectBuffer.AllocationDatas.ArenaAllocaters[Utils.InternalObjectBuffer.AllocationDatas.Indexes[ThreadIndex]];
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, (TargetBuffer->Size > AlignedSize) ? (TargetBuffer->Size) : (TargetBuffer->Size + AlignedSize), TargetMemory);
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_ArenaAllocater(pArenaAllocater, TargetBuffer->Size, TargetMemory);

				uint64_t prevendindex = pArenaAllocater->StartPtr;
				for (i = pArenaAllocater->StartPtr; i < pArenaAllocater->EndPtr;)
				{
					SizeOfBlock = i - prevendindex;
					Pointer = prevendindex;
					if (!(SizeOfBlock < 1)) //if is large enough break out of loop
						break;
					if (Utils.InternalObjectBuffer.AllocationDatas.Buffer[i].Allocation.Object.Identifier != 0)
					{
						i++;
						prevendindex = i;
					}
					else
					{
						i++;
					}
				}
				if (!(SizeOfBlock < 1)) //if is large enough break out of loop
					break;
				else
					Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
			}
			Utils.InternalObjectBuffer.AllocationDatas.Indexes[ThreadIndex] = (Utils.InternalObjectBuffer.AllocationDatas.Indexes[ThreadIndex] + 1) % EngineRes.pUtils->CPU.MaxThreads;
			ResetCount++;
		}
		else
		{
			if (Utils.Config.ActiveMemoryResizing == true)
			{
				Engine_Ref_FunctionError("Allocate_ObjectAllocationData()", "AAAAAAAAAAAAAA resizing main", SizeOfBlock);
				//ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, pArenaAllocater->Size + AlignedSize, TargetMemory);
				//ResetCount = 0;
			}
			else
			{
				Engine_Ref_FunctionError("Allocate_ObjectAllocationData()", "Not Enough Space In Allocation Memory!, Resize buffer!, Blocksize == ", SizeOfBlock);
				return (Failure);
			}
		}
	}
	//Engine_Ref_FunctionError("Allocate_ObjectAllocationData()", "PTR == ", Pointer);
	AllocationData* pAllocationData = &Utils.InternalObjectBuffer.AllocationDatas.Buffer[Pointer];
	memset(pAllocationData, 0, sizeof(*pAllocationData));
	//set all internal data to invalid number
	for (size_t i = 0; i < maxthreads; i++)
	{
		c89atomic_store_32(&pAllocationData->Threads[i].Pointer, UINT32_MAX);
		c89atomic_store_32(&pAllocationData->Threads[i].Count, 0);
	}
	c89atomic_store_32(&pAllocationData->LatestPointer, UINT32_MAX);
	//setting values to make allocation valid.
	c89atomic_fetch_add_32(&Utils.InternalObjectBuffer.AllocationDatas.AllocationsCount, 1);
	c89atomic_fetch_add_32(&pSignature->AllocationsCount, 1);
	c89atomic_store_32(&pAllocationData->Allocation.Object.Pointer, Pointer);
	c89atomic_store_32(&pAllocationData->Allocation.Object.Identifier, Identifier);
	Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
	pAllocation->Pointer = Pointer;
	pAllocation->Identifier = Identifier;
	return (Success);
}

TEXRESULT Allocate_ResourceHeaderAllocationData(ResourceHeaderSignature* pSignature, uint32_t Identifier, ResourceHeaderAllocation* pAllocation, uint32_t ThreadIndex) {
	ArenaAllocater* pArenaAllocater = NULL;
	uint64_t Pointer = 0;
	uint64_t SizeOfBlock = 0;
	uint64_t ResetCount = 0;
	uint64_t i = 0;
	while (true)
	{
		if (ResetCount < EngineRes.pUtils->CPU.MaxThreads)
		{
			if (Engine_Ref_TryLock_Mutex(&Utils.InternalResourceHeaderBuffer.AllocationDatas.ArenaAllocaters[Utils.InternalResourceHeaderBuffer.AllocationDatas.Indexes[ThreadIndex]].Mutex) == Success)
			{
				pArenaAllocater = &Utils.InternalResourceHeaderBuffer.AllocationDatas.ArenaAllocaters[Utils.InternalResourceHeaderBuffer.AllocationDatas.Indexes[ThreadIndex]];
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, (TargetBuffer->Size > AlignedSize) ? (TargetBuffer->Size) : (TargetBuffer->Size + AlignedSize), TargetMemory);
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_ArenaAllocater(pArenaAllocater, TargetBuffer->Size, TargetMemory);

				uint64_t prevendindex = pArenaAllocater->StartPtr;
				for (i = pArenaAllocater->StartPtr; i < pArenaAllocater->EndPtr;)
				{
					SizeOfBlock = i - prevendindex;
					Pointer = prevendindex;
					if (!(SizeOfBlock < 1)) //if is large enough break out of loop
						break;
					if (Utils.InternalResourceHeaderBuffer.AllocationDatas.Buffer[i].Allocation.ResourceHeader.Identifier != 0)
					{
						i++;
						prevendindex = i;
					}
					else
					{
						i++;
					}
				}
				if (!(SizeOfBlock < 1)) //if is large enough break out of loop
					break;
				else
					Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
			}
			Utils.InternalResourceHeaderBuffer.AllocationDatas.Indexes[ThreadIndex] = (Utils.InternalResourceHeaderBuffer.AllocationDatas.Indexes[ThreadIndex] + 1) % EngineRes.pUtils->CPU.MaxThreads;
			ResetCount++;
		}
		else
		{
			if (Utils.Config.ActiveMemoryResizing == true)
			{
				Engine_Ref_FunctionError("Allocate_ResourceHeaderAllocationData()", "AAAAAAAAAAAAAA resizing main", SizeOfBlock);
				//ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, pArenaAllocater->Size + AlignedSize, TargetMemory);
				//ResetCount = 0;
			}
			else
			{
				Engine_Ref_FunctionError("Allocate_ResourceHeaderAllocationData()", "Not Enough Space In Allocation Memory!, Resize buffer!, Blocksize == ", SizeOfBlock);
				return (Failure);
			}
		}
	}
	//Engine_Ref_FunctionError("Allocate_ResourceHeaderAllocationData()", "PTR == ", Pointer);
	AllocationData* pAllocationData = &Utils.InternalResourceHeaderBuffer.AllocationDatas.Buffer[Pointer];
	memset(pAllocationData, 0, sizeof(*pAllocationData));
	//set all internal data to invalid number
	for (size_t i = 0; i < maxthreads; i++)
	{
		c89atomic_store_32(&pAllocationData->Threads[i].Pointer, UINT32_MAX);
		c89atomic_store_32(&pAllocationData->Threads[i].Count, 0);
	}
	c89atomic_store_32(&pAllocationData->LatestPointer, UINT32_MAX);
	//setting values to make allocation valid.
	c89atomic_fetch_add_32(&Utils.InternalResourceHeaderBuffer.AllocationDatas.AllocationsCount, 1);
	c89atomic_fetch_add_32(&pSignature->AllocationsCount, 1);
	c89atomic_store_32(&pAllocationData->Allocation.ResourceHeader.Pointer, Pointer);
	c89atomic_store_32(&pAllocationData->Allocation.ResourceHeader.Identifier, Identifier);
	Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
	pAllocation->Pointer = Pointer;
	pAllocation->Identifier = Identifier;
	return (Success);
}

TEXRESULT Allocate_ElementAllocationData(ElementSignature* pSignature, uint32_t Identifier, ElementAllocation* pAllocation, uint32_t ThreadIndex) {
	ArenaAllocater* pArenaAllocater = NULL;
	uint64_t Pointer = 0;
	uint64_t SizeOfBlock = 0;
	uint64_t ResetCount = 0;
	uint64_t i = 0;
	while (true)
	{
		if (ResetCount < EngineRes.pUtils->CPU.MaxThreads)
		{
			if (Engine_Ref_TryLock_Mutex(&Utils.InternalElementBuffer.AllocationDatas.ArenaAllocaters[Utils.InternalElementBuffer.AllocationDatas.Indexes[ThreadIndex]].Mutex) == Success)
			{
				pArenaAllocater = &Utils.InternalElementBuffer.AllocationDatas.ArenaAllocaters[Utils.InternalElementBuffer.AllocationDatas.Indexes[ThreadIndex]];
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, (TargetBuffer->Size > AlignedSize) ? (TargetBuffer->Size) : (TargetBuffer->Size + AlignedSize), TargetMemory);
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_ArenaAllocater(pArenaAllocater, TargetBuffer->Size, TargetMemory);

				uint64_t prevendindex = pArenaAllocater->StartPtr;
				for (i = pArenaAllocater->StartPtr; i < pArenaAllocater->EndPtr;)
				{
					SizeOfBlock = i - prevendindex;
					Pointer = prevendindex;
					if (!(SizeOfBlock < 1)) //if is large enough break out of loop
						break;
					if (Utils.InternalElementBuffer.AllocationDatas.Buffer[i].Allocation.Element.Identifier != 0)
					{
						i++;
						prevendindex = i;
					}
					else
					{
						i++;
					}
				}
				if (!(SizeOfBlock < 1)) //if is large enough break out of loop
					break;
				else
					Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
			}
			Utils.InternalElementBuffer.AllocationDatas.Indexes[ThreadIndex] = (Utils.InternalElementBuffer.AllocationDatas.Indexes[ThreadIndex] + 1) % EngineRes.pUtils->CPU.MaxThreads;
			ResetCount++;
		}
		else
		{
			if (Utils.Config.ActiveMemoryResizing == true)
			{
				Engine_Ref_FunctionError("Allocate_ElementAllocationData()", "AAAAAAAAAAAAAA resizing main", SizeOfBlock);
				//ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, pArenaAllocater->Size + AlignedSize, TargetMemory);
				//ResetCount = 0;
			}
			else
			{
				Engine_Ref_FunctionError("Allocate_ElementAllocationData()", "Not Enough Space In Allocation Memory!, Resize buffer!, Blocksize == ", SizeOfBlock);
				return (Failure);
			}
		}
	}
	//Engine_Ref_FunctionError("Allocate_ElementAllocationData()", "PTR == ", Pointer);
	AllocationData* pAllocationData = &Utils.InternalElementBuffer.AllocationDatas.Buffer[Pointer];
	memset(pAllocationData, 0, sizeof(*pAllocationData));
	//set all internal data to invalid number
	for (size_t i = 0; i < maxthreads; i++)
	{
		c89atomic_store_32(&pAllocationData->Threads[i].Pointer, UINT32_MAX);
		c89atomic_store_32(&pAllocationData->Threads[i].Count, 0);
	}
	c89atomic_store_32(&pAllocationData->LatestPointer, UINT32_MAX);
	//setting values to make allocation valid.
	c89atomic_fetch_add_32(&Utils.InternalElementBuffer.AllocationDatas.AllocationsCount, 1);
	c89atomic_fetch_add_32(&pSignature->AllocationsCount, 1);
	c89atomic_store_32(&pAllocationData->Allocation.Element.Pointer, Pointer);
	c89atomic_store_32(&pAllocationData->Allocation.Element.Identifier, Identifier);
	Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
	pAllocation->Pointer = Pointer;
	pAllocation->Identifier = Identifier;
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DeAllocate Allocation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DeAllocate_ObjectAllocationData(ObjectSignature* pSignature, ObjectAllocation Allocation) {
	/*ArenaAllocater* pArenaAllocater = NULL;
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)
	{
		pArenaAllocater = &pBuffer->ArenaAllocaters[i];
		if (Pointer >= pArenaAllocater->StartPtr &&
			Pointer < pArenaAllocater->EndPtr)
		{
			break;
		}
	}
	if (pArenaAllocater == NULL)
	{
		Engine_Ref_FunctionError("DeAllocate_ObjectAllocationData()", "ArenaAllocater Not Found. == ", NULL);
		return;
	}
	Engine_Ref_Lock_Mutex(pArenaAllocater->Mutex);*/
	//set the allocation validaters to null atomically so no mutex is needed.
	c89atomic_store_32(&Utils.InternalObjectBuffer.AllocationDatas.Buffer[Allocation.Pointer].Allocation.Object.Identifier, 0);
	c89atomic_store_32(&Utils.InternalObjectBuffer.AllocationDatas.Buffer[Allocation.Pointer].Allocation.Object.Pointer, 0);
	memset(&Utils.InternalObjectBuffer.AllocationDatas.Buffer[Allocation.Pointer], 0, sizeof(*Utils.InternalObjectBuffer.AllocationDatas.Buffer));
	c89atomic_fetch_sub_32(&Utils.InternalObjectBuffer.AllocationDatas.AllocationsCount, 1);
	c89atomic_fetch_sub_32(&pSignature->AllocationsCount, 1);
	//Engine_Ref_Unlock_Mutex(pArenaAllocater->Mutex);
}

void DeAllocate_ResourceHeaderAllocationData(ResourceHeaderSignature* pSignature, ResourceHeaderAllocation Allocation) {
	/*ArenaAllocater* pArenaAllocater = NULL;
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)
	{
		pArenaAllocater = &pBuffer->ArenaAllocaters[i];
		if (Pointer >= pArenaAllocater->StartPtr &&
			Pointer < pArenaAllocater->EndPtr)
		{
			break;
		}
	}
	if (pArenaAllocater == NULL)
	{
		Engine_Ref_FunctionError("DeAllocate_ResourceHeaderAllocationData()", "ArenaAllocater Not Found. == ", NULL);
		return;
	}
	Engine_Ref_Lock_Mutex(pArenaAllocater->Mutex);*/
	//set the allocation validaters to null atomically so no mutex is needed.
	c89atomic_store_32(&Utils.InternalResourceHeaderBuffer.AllocationDatas.Buffer[Allocation.Pointer].Allocation.ResourceHeader.Identifier, 0);
	c89atomic_store_32(&Utils.InternalResourceHeaderBuffer.AllocationDatas.Buffer[Allocation.Pointer].Allocation.ResourceHeader.Pointer, 0);
	memset(&Utils.InternalResourceHeaderBuffer.AllocationDatas.Buffer[Allocation.Pointer], 0, sizeof(*Utils.InternalResourceHeaderBuffer.AllocationDatas.Buffer));
	c89atomic_fetch_sub_32(&Utils.InternalResourceHeaderBuffer.AllocationDatas.AllocationsCount, 1);
	c89atomic_fetch_sub_32(&pSignature->AllocationsCount, 1);
	//Engine_Ref_Unlock_Mutex(pArenaAllocater->Mutex);
}

void DeAllocate_ElementAllocationData(ElementSignature* pSignature, ElementAllocation Allocation) {
	/*ArenaAllocater* pArenaAllocater = NULL;
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)
	{
		pArenaAllocater = &pBuffer->ArenaAllocaters[i];
		if (Pointer >= pArenaAllocater->StartPtr &&
			Pointer < pArenaAllocater->EndPtr)
		{
			break;
		}
	}
	if (pArenaAllocater == NULL)
	{
		Engine_Ref_FunctionError("DeAllocate_ElementAllocationData()", "ArenaAllocater Not Found. == ", NULL);
		return;
	}
	Engine_Ref_Lock_Mutex(pArenaAllocater->Mutex);*/
	//set the allocation validaters to null atomically so no mutex is needed.
	c89atomic_store_32(&Utils.InternalElementBuffer.AllocationDatas.Buffer[Allocation.Pointer].Allocation.Element.Identifier, 0);
	c89atomic_store_32(&Utils.InternalElementBuffer.AllocationDatas.Buffer[Allocation.Pointer].Allocation.Element.Pointer, 0);
	memset(&Utils.InternalElementBuffer.AllocationDatas.Buffer[Allocation.Pointer], 0, sizeof(*Utils.InternalElementBuffer.AllocationDatas.Buffer));
	c89atomic_fetch_sub_32(&Utils.InternalElementBuffer.AllocationDatas.AllocationsCount, 1);
	c89atomic_fetch_sub_32(&pSignature->AllocationsCount, 1);
	//Engine_Ref_Unlock_Mutex(pArenaAllocater->Mutex);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Allocatie Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Allocate_Object(ObjectSignature* pSignature, uint32_t AllocationSize, uint32_t Identifier, ObjectAllocation Allocation, uint32_t* pPointer, uint32_t ThreadIndex) {
	ArenaAllocater* pArenaAllocater = NULL;
	uint64_t Pointer = 0;
	uint64_t SizeOfBlock = 0;
	uint64_t ResetCount = 0;
	uint64_t i = 0;
	while (true)
	{
		if (ResetCount < EngineRes.pUtils->CPU.MaxThreads)
		{
			if (Engine_Ref_TryLock_Mutex(&Utils.InternalObjectBuffer.ArenaAllocaters[Utils.InternalObjectBuffer.Indexes[ThreadIndex]].Mutex) == Success)
			{
				pArenaAllocater = &Utils.InternalObjectBuffer.ArenaAllocaters[Utils.InternalObjectBuffer.Indexes[ThreadIndex]];
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, (TargetBuffer->Size > AlignedSize) ? (TargetBuffer->Size) : (TargetBuffer->Size + AlignedSize), TargetMemory);
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_ArenaAllocater(pArenaAllocater, TargetBuffer->Size, TargetMemory);

				uint64_t prevendindex = pArenaAllocater->StartPtr;
				for (i = pArenaAllocater->StartPtr; i < pArenaAllocater->EndPtr;)
				{
					SizeOfBlock = i - prevendindex;
					Pointer = prevendindex;
					if (SizeOfBlock >= AllocationSize) //if is large enough break out of loop
						break;
					if (Utils.InternalObjectBuffer.Buffer[i].Header.AllocationSize != NULL)
					{
						i += Utils.InternalObjectBuffer.Buffer[i].Header.AllocationSize;
						prevendindex = i;
					}
					else
					{
						i++;
					}
				}
				if (SizeOfBlock >= AllocationSize) //if is large enough break out of loop
					break;
				else
					Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
			}
			Utils.InternalObjectBuffer.Indexes[ThreadIndex] = (Utils.InternalObjectBuffer.Indexes[ThreadIndex] + 1) % EngineRes.pUtils->CPU.MaxThreads;
			ResetCount++;
		}
		else
		{
			if (Utils.Config.ActiveMemoryResizing == true)
			{
				Engine_Ref_FunctionError("Allocate_Object()", "AAAAAAAAAAAAAA resizing main", SizeOfBlock);
				//ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, pArenaAllocater->Size + AlignedSize, TargetMemory);
				//ResetCount = 0;
			}
			else
			{
				Engine_Ref_FunctionError("Allocate_Object()", "Not Enough Space In Allocation Memory!, Resize buffer!, Blocksize == ", SizeOfBlock);
				return (Failure);
			}
		}
	}
	//Engine_Ref_FunctionError("Allocate_Object()", "PTR == ", Pointer);
	//Engine_Ref_FunctionError("Allocate_Object()", "Size == ", AllocationSize);

	Object* pObject = &Utils.InternalObjectBuffer.Buffer[Pointer];
	memset(pObject, 0, sizeof(*pObject) * AllocationSize);
	//setting values to make allocation valid.
	c89atomic_fetch_add_32(&Utils.InternalObjectBuffer.AllocationsCount, 1);
	c89atomic_fetch_add_32(&pSignature->ObjectsCount, 1);
	c89atomic_store_8(&pObject->Header.UseCount, 0);
	c89atomic_store_32(&pObject->Header.OverlayPointer, UINT32_MAX);
	pObject->Header.Allocation = Allocation;
	//c89atomic_store_32(&pObject->Header.Allocation, Allocation);
	c89atomic_store_32(&pObject->Header.AllocationSize, AllocationSize);
	Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
	*pPointer = Pointer;
	return (Success);
}

TEXRESULT Allocate_ResourceHeader(ResourceHeaderSignature* pSignature, uint32_t AllocationSize, uint32_t Identifier, ResourceHeaderAllocation Allocation, uint32_t* pPointer, uint32_t ThreadIndex) {
	ArenaAllocater* pArenaAllocater = NULL;
	uint64_t Pointer = 0;
	uint64_t SizeOfBlock = 0;
	uint64_t ResetCount = 0;
	uint64_t i = 0;
	while (true)
	{
		if (ResetCount < EngineRes.pUtils->CPU.MaxThreads)
		{
			if (Engine_Ref_TryLock_Mutex(&Utils.InternalResourceHeaderBuffer.ArenaAllocaters[Utils.InternalResourceHeaderBuffer.Indexes[ThreadIndex]].Mutex) == Success)
			{
				pArenaAllocater = &Utils.InternalResourceHeaderBuffer.ArenaAllocaters[Utils.InternalResourceHeaderBuffer.Indexes[ThreadIndex]];
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, (TargetBuffer->Size > AlignedSize) ? (TargetBuffer->Size) : (TargetBuffer->Size + AlignedSize), TargetMemory);
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_ArenaAllocater(pArenaAllocater, TargetBuffer->Size, TargetMemory);

				uint64_t prevendindex = pArenaAllocater->StartPtr;
				for (i = pArenaAllocater->StartPtr; i < pArenaAllocater->EndPtr;)
				{
					SizeOfBlock = i - prevendindex;
					Pointer = prevendindex;
					if (SizeOfBlock >= AllocationSize) //if is large enough break out of loop
						break;
					if (Utils.InternalResourceHeaderBuffer.Buffer[i].Header.AllocationSize != NULL)
					{
						i += Utils.InternalResourceHeaderBuffer.Buffer[i].Header.AllocationSize;
						prevendindex = i;
					}
					else
					{
						i++;
					}
				}
				if (SizeOfBlock >= AllocationSize) //if is large enough break out of loop
					break;
				else
					Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
			}
			Utils.InternalResourceHeaderBuffer.Indexes[ThreadIndex] = (Utils.InternalResourceHeaderBuffer.Indexes[ThreadIndex] + 1) % EngineRes.pUtils->CPU.MaxThreads;
			ResetCount++;
		}
		else
		{
			if (Utils.Config.ActiveMemoryResizing == true)
			{
				Engine_Ref_FunctionError("Allocate_ResourceHeader()", "AAAAAAAAAAAAAA resizing main", SizeOfBlock);
				//ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, pArenaAllocater->Size + AlignedSize, TargetMemory);
				//ResetCount = 0;
			}
			else
			{
				Engine_Ref_FunctionError("Allocate_ResourceHeader()", "Not Enough Space In Allocation Memory!, Resize buffer!, Blocksize == ", SizeOfBlock);
				return (Failure);
			}
		}
	}
//	Engine_Ref_FunctionError("Allocate_ResourceHeader()", "PTR == ", Pointer);
	//Engine_Ref_FunctionError("Allocate_ResourceHeader()", "Size == ", AllocationSize);

	ResourceHeader* pResourceHeader = &Utils.InternalResourceHeaderBuffer.Buffer[Pointer];
	memset(pResourceHeader, 0, sizeof(*pResourceHeader) * AllocationSize);
	//setting values to make allocation valid.
	c89atomic_fetch_add_32(&Utils.InternalResourceHeaderBuffer.AllocationsCount, 1);
	c89atomic_fetch_add_32(&pSignature->ResourceHeadersCount, 1);
	c89atomic_store_8(&pResourceHeader->Header.UseCount, 0);
	c89atomic_store_32(&pResourceHeader->Header.OverlayPointer, UINT32_MAX);
	pResourceHeader->Header.Allocation = Allocation;
	//c89atomic_store_32(&pResourceHeader->Header.Allocation, AllocationPointer);
	c89atomic_store_32(&pResourceHeader->Header.AllocationSize, AllocationSize);
	Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
	*pPointer = Pointer;
	return (Success);
}

TEXRESULT Allocate_Element(ElementSignature* pSignature, uint32_t AllocationSize, uint32_t Identifier, ElementAllocation Allocation, uint32_t* pPointer, uint32_t ThreadIndex)
{
	ArenaAllocater* pArenaAllocater = NULL;
	uint64_t Pointer = 0;
	uint64_t SizeOfBlock = 0;
	uint64_t ResetCount = 0;
	uint64_t i = 0;
	while (true)
	{
		if (ResetCount < EngineRes.pUtils->CPU.MaxThreads)
		{
			if (Engine_Ref_TryLock_Mutex(&Utils.InternalElementBuffer.ArenaAllocaters[Utils.InternalElementBuffer.Indexes[ThreadIndex]].Mutex) == Success)
			{
				pArenaAllocater = &Utils.InternalElementBuffer.ArenaAllocaters[Utils.InternalElementBuffer.Indexes[ThreadIndex]];
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, (TargetBuffer->Size > AlignedSize) ? (TargetBuffer->Size) : (TargetBuffer->Size + AlignedSize), TargetMemory);
				//if (pArenaAllocater->Size == 0)
				//	ReCreate_ArenaAllocater(pArenaAllocater, TargetBuffer->Size, TargetMemory);

				uint64_t prevendindex = pArenaAllocater->StartPtr;
				for (i = pArenaAllocater->StartPtr; i < pArenaAllocater->EndPtr;)
				{
					SizeOfBlock = i - prevendindex;
					Pointer = prevendindex;
					if (SizeOfBlock >= AllocationSize) //if is large enough break out of loop
						break;
					if (Utils.InternalElementBuffer.Buffer[i].Header.AllocationSize != NULL)
					{
						i += Utils.InternalElementBuffer.Buffer[i].Header.AllocationSize;
						prevendindex = i;
					}
					else
					{
						i++;
					}
				}
				if (SizeOfBlock >= AllocationSize) //if is large enough break out of loop
					break;
				else
					Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
			}
			Utils.InternalElementBuffer.Indexes[ThreadIndex] = (Utils.InternalElementBuffer.Indexes[ThreadIndex] + 1) % EngineRes.pUtils->CPU.MaxThreads;
			ResetCount++;
		}
		else
		{
			if (Utils.Config.ActiveMemoryResizing == true)
			{
				Engine_Ref_FunctionError("Allocate_Element()", "AAAAAAAAAAAAAA resizing main", SizeOfBlock);
				//ReCreate_GPU_ArenaAllocater(pLogicalDevice, pArenaAllocater, pArenaAllocater->Size + AlignedSize, TargetMemory);
				//ResetCount = 0;
			}
			else
			{
				Engine_Ref_FunctionError("Allocate_Element()", "Not Enough Space In Allocation Memory!, Resize buffer!, Blocksize == ", SizeOfBlock);
				return (Failure);
			}
		}
	}
	//Engine_Ref_FunctionError("Allocate_Element()", "PTR == ", Pointer);
	//Engine_Ref_FunctionError("Allocate_Element()", "Size == ", AllocationSize);

	Element* pElement = &Utils.InternalElementBuffer.Buffer[Pointer];
	memset(pElement, 0, sizeof(*pElement) * AllocationSize);
	//setting values to make allocation valid.
	c89atomic_fetch_add_32(&Utils.InternalElementBuffer.AllocationsCount, 1);
	c89atomic_fetch_add_32(&pSignature->ElementsCount, 1);
	c89atomic_store_8(&pElement->Header.UseCount, 0);
	c89atomic_store_32(&pElement->Header.OverlayPointer, UINT32_MAX);
	pElement->Header.Allocation = Allocation;
	//c89atomic_store_32(&pElement->Header.Allocation, AllocationPointer);
	c89atomic_store_32(&pElement->Header.AllocationSize, AllocationSize);
	Engine_Ref_Unlock_Mutex(&pArenaAllocater->Mutex);
	*pPointer = Pointer;
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Deallocate Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DeAllocate_Object(ObjectSignature* pSignature, uint32_t Pointer) {
	/*ArenaAllocater* pArenaAllocater = NULL;
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)
	{
		pArenaAllocater = &Utils.InternalObjectBuffer.ArenaAllocaters[i];
		if (Pointer >= pArenaAllocater->StartPtr &&
			Pointer < pArenaAllocater->EndPtr)
		{
			break;
		}
	}
	if (pArenaAllocater == NULL)
	{
		Engine_Ref_FunctionError("DeAllocate_Object()", "ArenaAllocater Not Found. == ", NULL);
		return;
	}
	Engine_Ref_Lock_Mutex(pArenaAllocater->Mutex);*/
	uint32_t AllocationSize = Utils.InternalObjectBuffer.Buffer[Pointer].Header.AllocationSize;
	c89atomic_store_32(&Utils.InternalObjectBuffer.Buffer[Pointer].Header.AllocationSize, 0);
	c89atomic_store_8(&Utils.InternalObjectBuffer.Buffer[Pointer].Header.UseCount, 0);
	memset(&Utils.InternalObjectBuffer.Buffer[Pointer], 0, sizeof(*Utils.InternalObjectBuffer.Buffer) * AllocationSize);
	c89atomic_fetch_sub_32(&Utils.InternalObjectBuffer.AllocationsCount, 1);
	c89atomic_fetch_sub_32(&pSignature->ObjectsCount, 1);
	//Engine_Ref_Unlock_Mutex(pArenaAllocater->Mutex);
}

void DeAllocate_ResourceHeader(ResourceHeaderSignature* pSignature, uint32_t Pointer) {
	/*
	ArenaAllocater* pArenaAllocater = NULL;
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)
	{
		pArenaAllocater = &Utils.InternalResourceHeaderBuffer.ArenaAllocaters[i];
		if (Pointer >= pArenaAllocater->StartPtr &&
			Pointer < pArenaAllocater->EndPtr)
		{
			break;
		}
	}
	if (pArenaAllocater == NULL)
	{
		Engine_Ref_FunctionError("DeAllocate_ResourceHeader()", "ArenaAllocater Not Found. == ", NULL);
		return;
	}
	Engine_Ref_Lock_Mutex(pArenaAllocater->Mutex);*/
	uint32_t AllocationSize = Utils.InternalResourceHeaderBuffer.Buffer[Pointer].Header.AllocationSize;
	c89atomic_store_32(&Utils.InternalResourceHeaderBuffer.Buffer[Pointer].Header.AllocationSize, 0);
	c89atomic_store_8(&Utils.InternalResourceHeaderBuffer.Buffer[Pointer].Header.UseCount, 0);
	memset(&Utils.InternalResourceHeaderBuffer.Buffer[Pointer], 0, sizeof(*Utils.InternalResourceHeaderBuffer.Buffer) * AllocationSize);
	c89atomic_fetch_sub_32(&Utils.InternalResourceHeaderBuffer.AllocationsCount, 1);
	c89atomic_fetch_sub_32(&pSignature->ResourceHeadersCount, 1);
	//Engine_Ref_Unlock_Mutex(pArenaAllocater->Mutex);
}

void DeAllocate_Element(ElementSignature* pSignature, uint32_t Pointer) {
	/*ArenaAllocater* pArenaAllocater = NULL;
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)
	{
		pArenaAllocater = &Utils.InternalElementBuffer.ArenaAllocaters[i];
		if (Pointer >= pArenaAllocater->StartPtr &&
			Pointer < pArenaAllocater->EndPtr)
		{
			break;
		}
	}
	if (pArenaAllocater == NULL)
	{
		Engine_Ref_FunctionError("DeAllocate_Element()", "ArenaAllocater Not Found. == ", NULL);
		return;
	}
	//Engine_Ref_Lock_Mutex(pArenaAllocater->Mutex);*/
	uint32_t AllocationSize = Utils.InternalElementBuffer.Buffer[Pointer].Header.AllocationSize;
	c89atomic_store_32(&Utils.InternalElementBuffer.Buffer[Pointer].Header.AllocationSize, 0);
	c89atomic_store_8(&Utils.InternalElementBuffer.Buffer[Pointer].Header.UseCount, 0);
	memset(&Utils.InternalElementBuffer.Buffer[Pointer], 0, sizeof(*Utils.InternalElementBuffer.Buffer) * AllocationSize);
	c89atomic_fetch_sub_32(&Utils.InternalElementBuffer.AllocationsCount, 1);
	c89atomic_fetch_sub_32(&pSignature->ElementsCount, 1);
	//Engine_Ref_Unlock_Mutex(pArenaAllocater->Mutex);
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
TEXRESULT Compare_ObjectAllocation(ObjectAllocation Allocation0, ObjectAllocation Allocation1) {
	return (Allocation0.Pointer == Allocation1.Pointer && Allocation0.Identifier == Allocation1.Identifier) ? Success : Failure;
}
/*
* Added in 1.0.0
* Returns Success when allocations are identical. Failure otherwise.
* @param Allocation0, first allocation to compare agaisnt.
* @param Allocation1, second allocation to compare agaisnt.
* @note Thread Safe always.
* @note Externally Synchronized.
*/
TEXRESULT Compare_ResourceHeaderAllocation(ResourceHeaderAllocation Allocation0, ResourceHeaderAllocation Allocation1) {
	return (Allocation0.Pointer == Allocation1.Pointer && Allocation0.Identifier == Allocation1.Identifier) ? Success : Failure;
}
/*
* Added in 1.0.0
* Returns Success when allocations are identical. Failure otherwise.
* @param Allocation0, first allocation to compare agaisnt.
* @param Allocation1, second allocation to compare agaisnt.
* @note Thread Safe always.
* @note Externally Synchronized.
*/
TEXRESULT Compare_ElementAllocation(ElementAllocation Allocation0, ElementAllocation Allocation1) {
	return (Allocation0.Pointer == Allocation1.Pointer && Allocation0.Identifier == Allocation1.Identifier) ? Success : Failure;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Get AllocationData Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Returns AllocationData, also used to check if allocation is valid.
* @return @ref return pointer to AllocationData if valid. @ref NULL if invalid.
* @param Allocation, Allocation to get the AllocationData of. (required)
* @note Thread Safe always.
* @note Not Synchronized but doesnt matter.
*/
AllocationData* Get_ObjectAllocationData(ObjectAllocation Allocation) {
	return (Allocation.Identifier != NULL) ? &Utils.InternalObjectBuffer.AllocationDatas.Buffer[Allocation.Pointer] : NULL;
}
/*
* Added in 1.0.0
* Returns AllocationData, also used to check if allocation is valid.
* @return @ref return pointer to AllocationData if valid. @ref NULL if invalid.
* @param Allocation, Allocation to get the AllocationData of. (required)
* @note Thread Safe always.
* @note Not Synchronized but doesnt matter.
*/
AllocationData* Get_ResourceHeaderAllocationData(ResourceHeaderAllocation Allocation) {
	return (Allocation.Identifier != NULL) ? &Utils.InternalResourceHeaderBuffer.AllocationDatas.Buffer[Allocation.Pointer] : NULL;
}
/*
* Added in 1.0.0
* Returns AllocationData, also used to check if allocation is valid.
* @return @ref return pointer to AllocationData if valid. @ref NULL if invalid.
* @param Allocation, Allocation to get the AllocationData of. (required)
* @note Thread Safe always.
* @note Not Synchronized but doesnt matter.
*/
AllocationData* Get_ElementAllocationData(ElementAllocation Allocation) {
	return (Allocation.Identifier != NULL) ? &Utils.InternalElementBuffer.AllocationDatas.Buffer[Allocation.Pointer] : NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Find Signature Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Uses Identifier to find the signature that the object is associated with.
* @param Identifier, desired signature identifier to find.
* @param ppSignature is a pointer to a pointer of a signature to return.
* @param pIndex is a pointer to a signatureindex value to return, signature index being the index of the signature in the signatures buffer.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Find_ObjectSignature(ObjectIdentifier Identifier, ObjectSignature** ppSignature) {
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Find_ObjectSignature()", "Identifier == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	//why no sync;
	for (uint64_t i = 0; i < Utils.ObjectSignaturesSize; i++)
	{
		if (Utils.ObjectSignatures[i]->Identifier == Identifier)
		{
			if (ppSignature != NULL)
				*ppSignature = Utils.ObjectSignatures[i];
			return (Success);
		}
	}
	*ppSignature = NULL;
	Engine_Ref_ArgsError("Find_ObjectSignature()", "Identifier Invalid");
	return (Invalid_Parameter | Failure);
}
/*
* Added in 1.0.0
* Uses Identifier to find the signature that the object is associated with.
* @param Identifier, desired signature identifier to find.
* @param ppSignature is a pointer to a pointer of a signature to return.
* @param pIndex is a pointer to a signatureindex value to return, signature index being the index of the signature in the signatures buffer.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Find_ResourceHeaderSignature(ResourceHeaderIdentifier Identifier, ResourceHeaderSignature** ppSignature) {
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Find_ResourceHeaderSignature()", "Identifier == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	for (uint64_t i = 0; i < Utils.ResourceHeaderSignaturesSize; i++)
	{
		if (Utils.ResourceHeaderSignatures[i]->Identifier == Identifier)
		{
			if (ppSignature != NULL)
				*ppSignature = Utils.ResourceHeaderSignatures[i];
			return (Success);
		}
	}
	*ppSignature = NULL;
	Engine_Ref_ArgsError("Find_ResourceHeaderSignature()", "Identifier Invalid");
	return (Invalid_Parameter | Failure);
}
/*
* Added in 1.0.0
* Uses Identifier to find the signature that the object is associated with.
* @param Identifier, desired signature identifier to find.
* @param ppSignature is a pointer to a pointer of a signature to return.
* @param pIndex is a pointer to a signatureindex value to return, signature index being the index of the signature in the signatures buffer.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Find_ElementSignature(ElementIdentifier Identifier, ElementSignature** ppSignature) {
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Find_ElementSignature()", "Identifier == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	for (uint64_t i = 0; i < Utils.ElementSignaturesSize; i++)
	{
		if (Utils.ElementSignatures[i]->Identifier == Identifier)
		{
			if (ppSignature != NULL)
				*ppSignature = Utils.ElementSignatures[i];
			return (Success);
		}
	}
	*ppSignature = NULL;
	Engine_Ref_ArgsError("Find_ElementSignature()", "Identifier Invalid");
	return (Invalid_Parameter | Failure);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Get Pointer Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Destroy_ObjectInstance(uint32_t Pointer, ObjectSignature* pSignature, bool Full, uint32_t ThreadIndex) {
	TEXRESULT tres = Success;
	Object* pObject = &Utils.InternalObjectBuffer.Buffer[Pointer];
	Object* pObjectOverlay = pObject->Header.OverlayPointer != UINT32_MAX ? &Utils.InternalObjectBuffer.Buffer[pObject->Header.OverlayPointer] : NULL;
	if (pSignature->Destructor != NULL)
	{
		Destroy_ObjectTemplate* func = *pSignature->Destructor;
		if ((tres = func(pObject, pObjectOverlay, Full, ThreadIndex)) != Success)
			return tres;
	}
	if (((pObjectOverlay != NULL) ? (pObject->Header.iResourceHeaders != pObjectOverlay->Header.iResourceHeaders) : true) && pObject->Header.iResourceHeaders != NULL) {
		free(pObject->Header.iResourceHeaders);
		pObject->Header.iResourceHeaders = NULL;
		pObject->Header.iResourceHeadersSize = NULL;
	}
	if (((pObjectOverlay != NULL) ? (pObject->Header.iChildren != pObjectOverlay->Header.iChildren) : true) && pObject->Header.iChildren != NULL) {
		free(pObject->Header.iChildren);
		pObject->Header.iChildren = NULL;
		pObject->Header.iChildrenSize = NULL;
	}
	if (((pObjectOverlay != NULL) ? (pObject->Header.Name != pObjectOverlay->Header.Name) : true) && pObject->Header.Name != NULL) {
		free(pObject->Header.Name);
		pObject->Header.Name = NULL;
	}
	return (Success);
}
TEXRESULT Destroy_ResourceHeaderInstance(uint32_t Pointer, ResourceHeaderSignature* pSignature, bool Full, uint32_t ThreadIndex) {
	TEXRESULT tres = Success;
	ResourceHeader* pResourceHeader = &Utils.InternalResourceHeaderBuffer.Buffer[Pointer];
	ResourceHeader* pResourceHeaderOverlay = pResourceHeader->Header.OverlayPointer != UINT32_MAX ? &Utils.InternalResourceHeaderBuffer.Buffer[pResourceHeader->Header.OverlayPointer] : NULL;
	if (pSignature->Destructor != NULL)
	{
		Destroy_ResourceHeaderTemplate* func = *pSignature->Destructor;
		if ((tres = func(pResourceHeader, pResourceHeaderOverlay, Full, ThreadIndex)) != Success)
			return tres;
	}
	if (((pResourceHeaderOverlay != NULL) ? (pResourceHeader->Header.iObjects != pResourceHeaderOverlay->Header.iObjects) : true) && pResourceHeader->Header.iObjects != NULL) {
		free(pResourceHeader->Header.iObjects);
		pResourceHeader->Header.iObjects = NULL;
		pResourceHeader->Header.iObjectsSize = NULL;
	}
	if (((pResourceHeaderOverlay != NULL) ? (pResourceHeader->Header.iElements != pResourceHeaderOverlay->Header.iElements) : true) && pResourceHeader->Header.iElements != NULL) {
		free(pResourceHeader->Header.iElements);
		pResourceHeader->Header.iElements = NULL;
		pResourceHeader->Header.iElementsSize = NULL;
	}
	if (((pResourceHeaderOverlay != NULL) ? (pResourceHeader->Header.Name != pResourceHeaderOverlay->Header.Name) : true) && pResourceHeader->Header.Name != NULL) {
		free(pResourceHeader->Header.Name);
		pResourceHeader->Header.Name = NULL;
	}
	return (Success);
}
TEXRESULT Destroy_ElementInstance(uint32_t Pointer, ElementSignature* pSignature, bool Full, uint32_t ThreadIndex) {
	TEXRESULT tres = Success;
	Element* pElement = &Utils.InternalElementBuffer.Buffer[Pointer];
	Element* pElementOverlay = pElement->Header.OverlayPointer != UINT32_MAX ? &Utils.InternalElementBuffer.Buffer[pElement->Header.OverlayPointer] : NULL;
	if (pSignature->Destructor != NULL)
	{
		Destroy_ElementTemplate* func = *pSignature->Destructor;
		if ((tres = func(pElement, pElementOverlay, Full, ThreadIndex)) != Success)
			return tres;
	}
	if (((pElementOverlay != NULL) ? (pElement->Header.iResourceHeaders != pElementOverlay->Header.iResourceHeaders) : true) && pElement->Header.iResourceHeaders != NULL) {
		free(pElement->Header.iResourceHeaders);
		pElement->Header.iResourceHeaders = NULL;
		pElement->Header.iResourceHeadersSize = NULL;
	}
	if (((pElementOverlay != NULL) ? (pElement->Header.Name != pElementOverlay->Header.Name) : true) && pElement->Header.Name != NULL) {
		free(pElement->Header.Name);
		pElement->Header.Name = NULL;
	}
	return (Success);
}

#define DestroyAndDeAllocate_ObjectInstance(Pointer, pSignature, Full, ThreadIndex)\
{\
	Destroy_ObjectInstance(Pointer, pSignature, Full, ThreadIndex);\
	DeAllocate_Object(pSignature, Pointer);\
}
#define DestroyAndDeAllocate_ResourceHeaderInstance(Pointer, pSignature, Full, ThreadIndex)\
{\
	Destroy_ResourceHeaderInstance(Pointer, pSignature, Full, ThreadIndex);\
	DeAllocate_ResourceHeader(pSignature, Pointer);\
}
#define DestroyAndDeAllocate_ElementInstance(Pointer, pSignature, Full, ThreadIndex)\
{\
	Destroy_ElementInstance(Pointer, pSignature, Full, ThreadIndex);\
	DeAllocate_Element(pSignature, Pointer);\
}

#define DestroyAndDeAllocate_Object(Pointer, pSignature)\
{\
	Object* pObject = &Utils.InternalObjectBuffer.Buffer[Pointer];\
	if (pObject->Header.OverlayPointer != UINT32_MAX)\
		DestroyAndDeAllocate_ObjectInstance(pObject->Header.OverlayPointer, pSignature, false, ThreadIndex)\
	c89atomic_store_32(&pObject->Header.OverlayPointer, UINT32_MAX);\
	for (size_t i = 0; i < pObject->Header.iResourceHeadersSize; i++)\
	{\
		ResourceHeader* pChild = Get_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i], true, false, ThreadIndex);\
		if (pChild != NULL)\
		{\
			for (size_t i = 0; i < pChild->Header.iObjectsSize; i++)\
			{\
				if (Compare_ObjectAllocation(pChild->Header.iObjects[i], Allocation) == Success)\
				{\
					RemoveMember_Array((void**)&pChild->Header.iObjects, pChild->Header.iObjectsSize, i, sizeof(*pChild->Header.iObjects), 1);\
					pChild->Header.iObjectsSize = pChild->Header.iObjectsSize - 1;\
				}\
			}\
		}\
		End_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i], true, false, ThreadIndex);\
	}\
	for (size_t i = 0; i < pObject->Header.iChildrenSize; i++)\
	{\
		Object* pChild = Get_ObjectPointer(pObject->Header.iChildren[i], true, false, ThreadIndex);\
		if (pChild != NULL)\
		{\
			memset(&pChild->Header.iParent, 0, sizeof(pChild->Header.iParent));\
		}\
		End_ObjectPointer(pObject->Header.iChildren[i], true, false, ThreadIndex);\
	}\
	if (pObject->Header.iResourceHeaders != NULL && pObject->Header.iResourceHeadersSize != NULL)\
		free(pObject->Header.iResourceHeaders);\
	if (pObject->Header.iChildren != NULL && pObject->Header.iChildrenSize != NULL)\
		free(pObject->Header.iChildren);\
	if (pObject->Header.Name != NULL)\
		free(pObject->Header.Name);\
	DestroyAndDeAllocate_ObjectInstance(Pointer, pSignature, true, ThreadIndex)\
	ObjectSignature* pSignature = NULL;\
	Find_ObjectSignature(pObject->Header.Allocation.Identifier, &pSignature);\
	DeAllocate_ObjectAllocationData(pSignature, Allocation);\
}
#define DestroyAndDeAllocate_ResourceHeader(Pointer, pSignature)\
{\
	ResourceHeader* pResourceHeader = &Utils.InternalResourceHeaderBuffer.Buffer[Pointer];\
	if (pResourceHeader->Header.OverlayPointer != UINT32_MAX)\
		DestroyAndDeAllocate_ResourceHeaderInstance(pResourceHeader->Header.OverlayPointer, pSignature, false, ThreadIndex)\
	c89atomic_store_32(&pResourceHeader->Header.OverlayPointer, UINT32_MAX);\
	for (size_t i = 0; i < pResourceHeader->Header.iObjectsSize; i++)\
	{\
		Object* pParent = Get_ObjectPointer(pResourceHeader->Header.iObjects[i], true, false, ThreadIndex);\
		if (pParent != NULL)\
		{\
			for (size_t i = 0; i < pParent->Header.iResourceHeadersSize; i++)\
			{\
				if (Compare_ResourceHeaderAllocation(pParent->Header.iResourceHeaders[i], Allocation) == Success)\
				{\
					RemoveMember_Array((void**)&pParent->Header.iResourceHeaders, pParent->Header.iResourceHeadersSize, i, sizeof(*pParent->Header.iResourceHeaders), 1);\
					pParent->Header.iResourceHeadersSize = pParent->Header.iResourceHeadersSize - 1;\
				}\
			}\
		}\
		End_ObjectPointer(pResourceHeader->Header.iObjects[i], true, false, ThreadIndex);\
	}\
	for (size_t i = 0; i < pResourceHeader->Header.iElementsSize; i++)\
	{\
		Element* pChild = Get_ElementPointer(pResourceHeader->Header.iElements[i], true, false, ThreadIndex);\
		if (pChild != NULL)\
		{\
			for (size_t i = 0; i < pChild->Header.iResourceHeadersSize; i++)\
			{\
				if (Compare_ResourceHeaderAllocation(pChild->Header.iResourceHeaders[i], Allocation) == Success)\
				{\
					RemoveMember_Array((void**)&pChild->Header.iResourceHeaders, pChild->Header.iResourceHeadersSize, i, sizeof(*pChild->Header.iResourceHeaders), 1);\
					pChild->Header.iResourceHeadersSize = pChild->Header.iResourceHeadersSize - 1;\
				}\
			}\
		}\
		End_ElementPointer(pResourceHeader->Header.iElements[i], true, false, ThreadIndex);\
	}\
	if (pResourceHeader->Header.iObjects != NULL && pResourceHeader->Header.iObjectsSize != NULL)\
		free(pResourceHeader->Header.iObjects);\
	if (pResourceHeader->Header.iElements != NULL && pResourceHeader->Header.iElementsSize != NULL)\
		free(pResourceHeader->Header.iElements);\
	if (pResourceHeader->Header.Name != NULL)\
		free(pResourceHeader->Header.Name);\
	DestroyAndDeAllocate_ResourceHeaderInstance(Pointer, pSignature, true, ThreadIndex)\
	ResourceHeaderSignature* pSignature = NULL;\
	Find_ResourceHeaderSignature(pResourceHeader->Header.Allocation.Identifier, &pSignature);\
	DeAllocate_ResourceHeaderAllocationData(pSignature, Allocation);\
}
#define DestroyAndDeAllocate_Element(Pointer, pSignature)\
{\
	Element* pElement = &Utils.InternalElementBuffer.Buffer[Pointer];\
	if (pElement->Header.OverlayPointer != UINT32_MAX)\
		DestroyAndDeAllocate_ElementInstance(pElement->Header.OverlayPointer, pSignature, false, ThreadIndex)\
	c89atomic_store_32(&pElement->Header.OverlayPointer, UINT32_MAX);\
	for (size_t i = 0; i < pElement->Header.iResourceHeadersSize; i++)\
	{\
		ResourceHeader* pParent = Get_ResourceHeaderPointer(pElement->Header.iResourceHeaders[i], true, false, ThreadIndex);\
		if (pParent != NULL)\
		{\
			for (size_t i = 0; i < pParent->Header.iElementsSize; i++)\
			{\
				if (Compare_ElementAllocation(pParent->Header.iElements[i], Allocation) == Success)\
				{\
					RemoveMember_Array((void**)&pParent->Header.iElements, pParent->Header.iElementsSize, i, sizeof(*pParent->Header.iElements), 1);\
					pParent->Header.iElementsSize = pParent->Header.iElementsSize - 1;\
				}\
			}\
		}\
		End_ResourceHeaderPointer(pElement->Header.iResourceHeaders[i], true, false, ThreadIndex);\
	}\
	if (pElement->Header.iResourceHeaders != NULL && pElement->Header.iResourceHeadersSize != NULL)\
		free(pElement->Header.iResourceHeaders);\
	if (pElement->Header.Name != NULL)\
		free(pElement->Header.Name);\
	DestroyAndDeAllocate_ElementInstance(Pointer, pSignature, true, ThreadIndex)\
	ElementSignature* pSignature = NULL;\
	Find_ElementSignature(pElement->Header.Allocation.Identifier, &pSignature);\
	DeAllocate_ElementAllocationData(pSignature, Allocation);\
}

#define CreateAndAllocate_ObjectInstance(Pointer)\
{\
	Object* pOldObject = &Utils.InternalObjectBuffer.Buffer[LatestPointer];\
	Allocate_Object(pSignature, pOldObject->Header.AllocationSize, pAllocationData->Allocation.Object.Identifier, Allocation, &Pointer, ThreadIndex);\
	Object* pObject = &Utils.InternalObjectBuffer.Buffer[Pointer];\
	memcpy(pObject, pOldObject, sizeof(Object) * pOldObject->Header.AllocationSize);\
	pObject->Header.UseCount = 0;\
	pObject->Header.OverlayPointer = UINT32_MAX;\
}
#define CreateAndAllocate_ResourceHeaderInstance(Pointer)\
{\
	ResourceHeader* pOldResourceHeader = &Utils.InternalResourceHeaderBuffer.Buffer[LatestPointer]; \
	Allocate_ResourceHeader(pSignature, pOldResourceHeader->Header.AllocationSize, pAllocationData->Allocation.ResourceHeader.Identifier, Allocation, &Pointer, ThreadIndex); \
	ResourceHeader* pResourceHeader = &Utils.InternalResourceHeaderBuffer.Buffer[Pointer]; \
	memcpy(pResourceHeader, pOldResourceHeader, sizeof(ResourceHeader) * pOldResourceHeader->Header.AllocationSize); \
	pResourceHeader->Header.UseCount = 0; \
	pResourceHeader->Header.OverlayPointer = UINT32_MAX;\
}
#define CreateAndAllocate_ElementInstance(Pointer)\
{\
	Element* pOldElement = &Utils.InternalElementBuffer.Buffer[LatestPointer];\
	Allocate_Element(pSignature, pOldElement->Header.AllocationSize, pAllocationData->Allocation.Element.Identifier, Allocation, &Pointer, ThreadIndex);\
	Element* pElement = &Utils.InternalElementBuffer.Buffer[Pointer];\
	memcpy(pElement, pOldElement, sizeof(Element) * pOldElement->Header.AllocationSize);\
	pElement->Header.UseCount = 0;\
	pElement->Header.OverlayPointer = UINT32_MAX;\
}
//attempts to destroy itself and then its overlay pointer.
void TryDestruct_Object(AllocationData* pAllocationData, uint32_t Pointer, ObjectSignature* pSignature, uint32_t ThreadIndex) {
	if (pAllocationData->LatestPointer != Pointer &&
		c89atomic_fetch_add_8(&Utils.InternalObjectBuffer.Buffer[Pointer].Header.UseCount, UINT16_MAX) == 0) {
		uint32_t OverlayPointer = Utils.InternalObjectBuffer.Buffer[Pointer].Header.OverlayPointer;
		Object* pObject = &Utils.InternalObjectBuffer.Buffer[Pointer];
		DestroyAndDeAllocate_ObjectInstance(Pointer, pSignature, false, ThreadIndex);
		if (OverlayPointer != UINT32_MAX) {
			c89atomic_fetch_sub_8(&Utils.InternalObjectBuffer.Buffer[OverlayPointer].Header.UseCount, 1);
			if (pAllocationData->LatestPointer != OverlayPointer && 
				c89atomic_fetch_add_8(&Utils.InternalObjectBuffer.Buffer[OverlayPointer].Header.UseCount, UINT16_MAX) == 0) {
				Object* pObject = &Utils.InternalObjectBuffer.Buffer[OverlayPointer];
				DestroyAndDeAllocate_ObjectInstance(OverlayPointer, pSignature, false, ThreadIndex);
			}
			else {
				c89atomic_fetch_sub_8(&Utils.InternalObjectBuffer.Buffer[OverlayPointer].Header.UseCount, UINT16_MAX);
			}
		}
	}
	else {
		c89atomic_fetch_sub_8(&Utils.InternalObjectBuffer.Buffer[Pointer].Header.UseCount, UINT16_MAX);
	}
}
void TryDestruct_ResourceHeader(AllocationData* pAllocationData, uint32_t Pointer, ResourceHeaderSignature* pSignature, uint32_t ThreadIndex) {
	if (pAllocationData->LatestPointer != Pointer &&
		c89atomic_fetch_add_8(&Utils.InternalResourceHeaderBuffer.Buffer[Pointer].Header.UseCount, UINT16_MAX) == 0) {
		uint32_t OverlayPointer = Utils.InternalResourceHeaderBuffer.Buffer[Pointer].Header.OverlayPointer;
		ResourceHeader* pResourceHeader = &Utils.InternalResourceHeaderBuffer.Buffer[Pointer];
		DestroyAndDeAllocate_ResourceHeaderInstance(Pointer, pSignature, false, ThreadIndex);
		if (OverlayPointer != UINT32_MAX) {
			c89atomic_fetch_sub_8(&Utils.InternalResourceHeaderBuffer.Buffer[OverlayPointer].Header.UseCount, 1);
			if (pAllocationData->LatestPointer != OverlayPointer &&
				c89atomic_fetch_add_8(&Utils.InternalResourceHeaderBuffer.Buffer[OverlayPointer].Header.UseCount, UINT16_MAX) == 0) {
				ResourceHeader* pResourceHeader = &Utils.InternalResourceHeaderBuffer.Buffer[OverlayPointer];
				DestroyAndDeAllocate_ResourceHeaderInstance(OverlayPointer, pSignature, false, ThreadIndex);
			}
			else {
				c89atomic_fetch_sub_8(&Utils.InternalResourceHeaderBuffer.Buffer[OverlayPointer].Header.UseCount, UINT16_MAX);
			}
		}
	}
	else {
		c89atomic_fetch_sub_8(&Utils.InternalResourceHeaderBuffer.Buffer[Pointer].Header.UseCount, UINT16_MAX);
	}
}
void TryDestruct_Element(AllocationData* pAllocationData, uint32_t Pointer, ElementSignature* pSignature, uint32_t ThreadIndex) {
	if (pAllocationData->LatestPointer != Pointer &&
		c89atomic_fetch_add_8(&Utils.InternalElementBuffer.Buffer[Pointer].Header.UseCount, UINT16_MAX) == 0) {
		uint32_t OverlayPointer = Utils.InternalElementBuffer.Buffer[Pointer].Header.OverlayPointer;
		Element* pElement = &Utils.InternalElementBuffer.Buffer[Pointer];
		DestroyAndDeAllocate_ElementInstance(Pointer, pSignature, false, ThreadIndex);
		if (OverlayPointer != UINT32_MAX) {
			c89atomic_fetch_sub_8(&Utils.InternalElementBuffer.Buffer[OverlayPointer].Header.UseCount, 1);
			if (pAllocationData->LatestPointer != OverlayPointer &&
				c89atomic_fetch_add_8(&Utils.InternalElementBuffer.Buffer[OverlayPointer].Header.UseCount, UINT16_MAX) == 0) {
				Element* pElement = &Utils.InternalElementBuffer.Buffer[OverlayPointer];
				DestroyAndDeAllocate_ElementInstance(OverlayPointer, pSignature, false, ThreadIndex);
			}
			else {
				c89atomic_fetch_sub_8(&Utils.InternalElementBuffer.Buffer[OverlayPointer].Header.UseCount, UINT16_MAX);
			}
		}
	}
	else {
		c89atomic_fetch_sub_8(&Utils.InternalElementBuffer.Buffer[Pointer].Header.UseCount, UINT16_MAX);
	} 
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Get Pointer Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Gets a pointer from an allocation for that threadindex that is an instance.
* Always call End_ObjectPointer after done.
* @param Allocation, allocation of the desired object to get pointer of.
* @param Write, intended use of the instance that will be retrieved, true means its allocates a new instance so its quite slow.
* @param Consistent, Consistent == true means that the pointer wont be modified since the last time get_pointer was called on this threadindex on this allocation,
  useful for making sure when reading allocation buffers that no new allocations will appear in second parsing, so it omits the requirement of a buffer per thread or such.
* @param ThreadIndex threadindex global.
* @note Thread Safe always.
* @note Not Synchronized but doesnt matter.
*/
Object* Get_ObjectPointer(ObjectAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) {
	TEXRESULT tres = Success;
	AllocationData* pAllocationData = Get_ObjectAllocationData(Allocation);
	if (pAllocationData == NULL)
	{
		//Engine_Ref_FunctionError("Get_ObjectPointer()", "pAllocationData == ", 0);
		return NULL;
	}
	//if latest instance UINT32_MAX it is invalid to read or write.
	if (pAllocationData->LatestPointer == UINT32_MAX)
	{
		Engine_Ref_FunctionError("Get_ObjectPointer()", "LatestPointer Invalid. ", 0);
		return;
	}
	if (pAllocationData->ScheduleDestruct == true)
		return NULL;

	if (Consistent == false && c89atomic_fetch_add_32(&pAllocationData->Threads[ThreadIndex].Count, 1) == 0)
	{
		if (Write == true)
		{
			//Engine_Ref_FunctionError("Get_ResourceHeaderPointer", "Begin Write On Pointer == ", Allocation.Pointer);
			//LOCK SO ONLY 1 WRITE AT A TIME OR FIX THE PROBLEMS ASSOCIATED WITH MULTIPLE WRITES CONCURRENTLY;
			if (c89atomic_test_and_set_8(&pAllocationData->WriteLock) == 0)
			{
				//get new data.
				ObjectSignature* pSignature = NULL;
				Find_ObjectSignature(pAllocationData->Allocation.Object.Identifier, &pSignature);

				uint32_t LatestPointer = pAllocationData->LatestPointer;
				//refresh pointer
				if (c89atomic_fetch_add_8(&Utils.InternalObjectBuffer.Buffer[LatestPointer].Header.UseCount, 1) >= UINT16_MAX) {
					c89atomic_fetch_sub_8(&Utils.InternalObjectBuffer.Buffer[LatestPointer].Header.UseCount, 1);
					LatestPointer = pAllocationData->LatestPointer;
					c89atomic_fetch_add_8(&Utils.InternalObjectBuffer.Buffer[LatestPointer].Header.UseCount, 1);
				}
				uint32_t Pointer = 0;
				CreateAndAllocate_ObjectInstance(Pointer);
				c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, Pointer);
				//save pointer of latest;
				c89atomic_store_32(&Utils.InternalObjectBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.OverlayPointer, LatestPointer);
				c89atomic_fetch_add_8(&Utils.InternalObjectBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);

				c89atomic_clear_8(&pAllocationData->WriteLock);
			}
			else
			{
				c89atomic_fetch_sub_32(&pAllocationData->Threads[ThreadIndex].Count, 1);
				Engine_Ref_FunctionError("Get_ObjectPointer()", "Concurrent Write. ", 0);
				return NULL;
			}
		}
		else
		{
			//Engine_Ref_FunctionError("Get_ResourceHeaderPointer", "Begin Read On Pointer == ", Allocation.Pointer);
			//get new pointer
			uint32_t LatestPointer = pAllocationData->LatestPointer;
			//refresh pointer
			if (c89atomic_fetch_add_8(&Utils.InternalObjectBuffer.Buffer[LatestPointer].Header.UseCount, 1) >= UINT16_MAX) {
				c89atomic_fetch_sub_8(&Utils.InternalObjectBuffer.Buffer[LatestPointer].Header.UseCount, 1);
				LatestPointer = pAllocationData->LatestPointer;
				c89atomic_fetch_add_8(&Utils.InternalObjectBuffer.Buffer[LatestPointer].Header.UseCount, 1);
			}
			c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, LatestPointer);
		}
	}
	if (pAllocationData->Threads[ThreadIndex].Pointer == UINT32_MAX)
	{
		c89atomic_fetch_sub_32(&pAllocationData->Threads[ThreadIndex].Count, 1);
		Engine_Ref_FunctionError("Get_ObjectPointer()", "POINTER INVALID  ", Allocation.Pointer);
		return NULL;
	}
	return &Utils.InternalObjectBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer];
}
/*
* Added in 1.0.0
* Gets a pointer from an allocation for that threadindex that is an instance.
* Always call End_ResourceHeaderPointer after done.
* @param Allocation, allocation of the desired object to g/et pointer of.
* @param Write, intended use of the instance that will be retrieved, true means its allocates a new instance so its quite slow.
* @param Consistent, Consistent == true means that the pointer wont be modified since the last time get_pointer was called on this threadindex on this allocation,
  useful for making sure when reading allocation buffers that no new allocations will appear in second parsing, so it omits the requirement of a buffer per thread or such.
* @param ThreadIndex threadindex global.
* @note Thread Safe always.
* @note Not Synchronized but doesnt matter.
*/
ResourceHeader* Get_ResourceHeaderPointer(ResourceHeaderAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) {
	TEXRESULT tres = Success;
	AllocationData* pAllocationData = Get_ResourceHeaderAllocationData(Allocation);
	if (pAllocationData == NULL)
	{
		//Engine_Ref_FunctionError("Get_ResourceHeaderPointer()", "pAllocationData == ", 0);
		return NULL;
	}
	//if latest instance UINT32_MAX it is invalid to read or write.
	if (pAllocationData->LatestPointer == UINT32_MAX)
	{
		Engine_Ref_FunctionError("Get_ResourceHeaderPointer()", "LatestPointer Invalid. ", 0);
		return;
	}
	if (pAllocationData->ScheduleDestruct == true)
		return NULL;

	if (Consistent == false && c89atomic_fetch_add_32(&pAllocationData->Threads[ThreadIndex].Count, 1) == 0)
	{
		if (Write == true)
		{
			//Engine_Ref_FunctionError("Get_ResourceHeaderPointer", "Begin Write On Pointer == ", Allocation.Pointer);
			//LOCK SO ONLY 1 WRITE AT A TIME OR FIX THE PROBLEMS ASSOCIATED WITH MULTIPLE WRITES CONCURRENTLY;
			if (c89atomic_test_and_set_8(&pAllocationData->WriteLock) == 0)
			{
				//get new data.
				ResourceHeaderSignature* pSignature = NULL;
				Find_ResourceHeaderSignature(pAllocationData->Allocation.ResourceHeader.Identifier, &pSignature);

				uint32_t LatestPointer = pAllocationData->LatestPointer;
				//refresh pointer
				if (c89atomic_fetch_add_8(&Utils.InternalResourceHeaderBuffer.Buffer[LatestPointer].Header.UseCount, 1) >= UINT16_MAX) {
					c89atomic_fetch_sub_8(&Utils.InternalResourceHeaderBuffer.Buffer[LatestPointer].Header.UseCount, 1);
					LatestPointer = pAllocationData->LatestPointer;
					c89atomic_fetch_add_8(&Utils.InternalResourceHeaderBuffer.Buffer[LatestPointer].Header.UseCount, 1);
				}
				uint32_t Pointer = 0;
				CreateAndAllocate_ResourceHeaderInstance(Pointer);
				c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, Pointer);
				//save pointer of latest;
				c89atomic_store_32(&Utils.InternalResourceHeaderBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.OverlayPointer, LatestPointer);
				c89atomic_fetch_add_8(&Utils.InternalResourceHeaderBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);

				c89atomic_clear_8(&pAllocationData->WriteLock);
			}
			else
			{
				c89atomic_fetch_sub_32(&pAllocationData->Threads[ThreadIndex].Count, 1);
				Engine_Ref_FunctionError("Get_ResourceHeaderPointer()", "Concurrent Write. ", 0);
				return NULL;
			}
		}
		else
		{
			//Engine_Ref_FunctionError("Get_ResourceHeaderPointer", "Begin Read On Pointer == ", Allocation.Pointer);
			//get new pointer
			uint32_t LatestPointer = pAllocationData->LatestPointer;
			//refresh pointer
			if (c89atomic_fetch_add_8(&Utils.InternalResourceHeaderBuffer.Buffer[LatestPointer].Header.UseCount, 1) >= UINT16_MAX) {
				c89atomic_fetch_sub_8(&Utils.InternalResourceHeaderBuffer.Buffer[LatestPointer].Header.UseCount, 1);
				LatestPointer = pAllocationData->LatestPointer;
				c89atomic_fetch_add_8(&Utils.InternalResourceHeaderBuffer.Buffer[LatestPointer].Header.UseCount, 1);
			}
			c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, LatestPointer);
		}
	}	
	if (pAllocationData->Threads[ThreadIndex].Pointer == UINT32_MAX)
	{
		c89atomic_fetch_sub_32(&pAllocationData->Threads[ThreadIndex].Count, 1);
		Engine_Ref_FunctionError("Get_ResourceHeaderPointer()", "POINTER INVALID  ", Allocation.Pointer);
		return NULL;
	}
	return &Utils.InternalResourceHeaderBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer];
}
/*
* Added in 1.0.0
* Gets a pointer from an allocation for that threadindex that is an instance.
* Always call End_ElementPointer after done.
* @param Allocation, allocation of the desired object to get pointer of.
* @param Write, intended use of the instance that will be retrieved, true means its allocates a new instance so its quite slow.
* @param Consistent, Consistent == true means that the pointer wont be modified since the last time get_pointer was called on this threadindex on this allocation,
  useful for making sure when reading allocation buffers that no new allocations will appear in second parsing, so it omits the requirement of a buffer per thread or such.
* @param ThreadIndex threadindex global.
* @note Thread Safe always.
* @note Not Synchronized but doesnt matter.
*/
Element* Get_ElementPointer(ElementAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) {
	TEXRESULT tres = Success;
	AllocationData* pAllocationData = Get_ElementAllocationData(Allocation);
	if (pAllocationData == NULL)
	{
		//Engine_Ref_FunctionError("Get_ElementPointer()", "pAllocationData == ", 0);
		return NULL;
	}
	//if latest instance UINT32_MAX it is invalid to read or write.
	if (pAllocationData->LatestPointer == UINT32_MAX)
	{
		Engine_Ref_FunctionError("Get_ElementPointer()", "LatestPointer Invalid. ", 0);
		return;
	}
	if (pAllocationData->ScheduleDestruct == true)
		return NULL;

	if (Consistent == false && c89atomic_fetch_add_32(&pAllocationData->Threads[ThreadIndex].Count, 1) == 0)
	{
		if (Write == true)
		{
			//Engine_Ref_FunctionError("Get_ResourceHeaderPointer", "Begin Write On Pointer == ", Allocation.Pointer);
			//LOCK SO ONLY 1 WRITE AT A TIME OR FIX THE PROBLEMS ASSOCIATED WITH MULTIPLE WRITES CONCURRENTLY;
			if (c89atomic_test_and_set_8(&pAllocationData->WriteLock) == 0)
			{
				//get new data.
				ElementSignature* pSignature = NULL;
				Find_ElementSignature(pAllocationData->Allocation.Element.Identifier, &pSignature);

				uint32_t LatestPointer = pAllocationData->LatestPointer;
				//refresh pointer
				if (c89atomic_fetch_add_8(&Utils.InternalElementBuffer.Buffer[LatestPointer].Header.UseCount, 1) >= UINT16_MAX) {
					c89atomic_fetch_sub_8(&Utils.InternalElementBuffer.Buffer[LatestPointer].Header.UseCount, 1);
					LatestPointer = pAllocationData->LatestPointer;
					c89atomic_fetch_add_8(&Utils.InternalElementBuffer.Buffer[LatestPointer].Header.UseCount, 1);
				}
				uint32_t Pointer = 0;
				CreateAndAllocate_ElementInstance(Pointer);
				c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, Pointer);
				//save pointer of latest;
				c89atomic_store_32(&Utils.InternalElementBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.OverlayPointer, LatestPointer);
				c89atomic_fetch_add_8(&Utils.InternalElementBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);

				c89atomic_clear_8(&pAllocationData->WriteLock);
			}
			else
			{
				c89atomic_fetch_sub_32(&pAllocationData->Threads[ThreadIndex].Count, 1);
				Engine_Ref_FunctionError("Get_ElementPointer()", "Concurrent Write. ", 0);
				return NULL;
			}
		}
		else
		{
			//Engine_Ref_FunctionError("Get_ResourceHeaderPointer", "Begin Read On Pointer == ", Allocation.Pointer);
			//get new pointer
			uint32_t LatestPointer = pAllocationData->LatestPointer;
			//refresh pointer
			if (c89atomic_fetch_add_8(&Utils.InternalElementBuffer.Buffer[LatestPointer].Header.UseCount, 1) >= UINT16_MAX) {
				c89atomic_fetch_sub_8(&Utils.InternalElementBuffer.Buffer[LatestPointer].Header.UseCount, 1);
				LatestPointer = pAllocationData->LatestPointer;
				c89atomic_fetch_add_8(&Utils.InternalElementBuffer.Buffer[LatestPointer].Header.UseCount, 1);
			}
			c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, LatestPointer);
		}
	}
	if (pAllocationData->Threads[ThreadIndex].Pointer == UINT32_MAX)
	{
		c89atomic_fetch_sub_32(&pAllocationData->Threads[ThreadIndex].Count, 1);
		Engine_Ref_FunctionError("Get_ElementPointer()", "POINTER INVALID  ", Allocation.Pointer);
		return NULL;
	}
	return &Utils.InternalElementBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//End Write
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void End_ElementPointer(ElementAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex);
void End_ResourceHeaderPointer(ResourceHeaderAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex);
/*
* Added in 1.0.0
* Ends a Get_Pointer function and applies the results.
* Always call Get_Pointer before.
* @param Allocation, allocation of the desired object to end read/write of.
* @param Write, (MUST MATCH GET_POINTER THAT THIS IS PAIRED WITH)
* @param Consistent, (MUST MATCH GET_POINTER THAT THIS IS PAIRED WITH)
* @param ThreadIndex threadindex global.
* @note Thread Safe always.
* @note Not Synchronized but doesnt matter.
*/
void End_ObjectPointer(ObjectAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) {	
	TEXRESULT tres = Success;
	AllocationData* pAllocationData = Get_ObjectAllocationData(Allocation);
	if (pAllocationData == NULL)
	{
		//Engine_Ref_FunctionError("End_ObjectPointer()", "pAllocationData == ", 0);
		return;
	}
	if (pAllocationData->Threads[ThreadIndex].Pointer == UINT32_MAX)
	{
		Engine_Ref_FunctionError("End_ObjectPointer()", "Invalid Call. ", 0);
		return;
	}
	if (pAllocationData->LatestPointer == UINT32_MAX)
	{
		Engine_Ref_FunctionError("End_ObjectPointer()", "LatestPointer Invalid. ", 0);
		return;
	}
	if (pAllocationData->Threads[ThreadIndex].Count == 0)
	{
		Engine_Ref_FunctionError("End_ObjectPointer()", "Count == ", 0);
		return;
	}

	if (Consistent == false && c89atomic_fetch_sub_32(&pAllocationData->Threads[ThreadIndex].Count, 1) == 1) {
		if (Write == true) {
			//Engine_Ref_FunctionError("End_ElementPointer", "End Write On Pointer == ", Allocation.Pointer);
			uint32_t LatestPointer = Utils.InternalObjectBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.OverlayPointer;
			c89atomic_store_32(&Utils.InternalObjectBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.OverlayPointer, UINT32_MAX);

			c89atomic_store_32(&Utils.InternalObjectBuffer.Buffer[LatestPointer].Header.OverlayPointer, pAllocationData->Threads[ThreadIndex].Pointer);
			//lock usedcount for threadindex because its used as overlayand it might be destructed before;
			c89atomic_fetch_add_8(&Utils.InternalObjectBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);


			c89atomic_fetch_sub_8(&Utils.InternalObjectBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);
			c89atomic_fetch_sub_8(&Utils.InternalObjectBuffer.Buffer[LatestPointer].Header.UseCount, 1);

			c89atomic_store_32(&pAllocationData->LatestPointer, pAllocationData->Threads[ThreadIndex].Pointer);

			//every decrement of use count must have oppurtunity to destruct. (in this case overlaypointer aka latestpointer at allocate time);
			ObjectSignature* pSignature = NULL;
			Find_ObjectSignature(Allocation.Identifier, &pSignature);
			TryDestruct_Object(pAllocationData, LatestPointer, pSignature, ThreadIndex);
		}
		else {
			//Engine_Ref_FunctionError("End_ElementPointer", "End Read On Pointer == ", Allocation.Pointer);
			c89atomic_fetch_sub_8(&Utils.InternalObjectBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);
		}
		if (pAllocationData->Threads[ThreadIndex].Pointer != pAllocationData->LatestPointer) {
			ObjectSignature* pSignature = NULL;
			Find_ObjectSignature(Allocation.Identifier, &pSignature);
			TryDestruct_Object(pAllocationData, pAllocationData->Threads[ThreadIndex].Pointer, pSignature, ThreadIndex);
			//this is fine because it doesnt destroy only if its not used and any other thread would call this after too.
			c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, UINT32_MAX);
		}
		if (pAllocationData->ScheduleDestruct == true) {
			bool found = false;
			for (size_t i = 0; i < maxthreads; i++)
				if (pAllocationData->Threads[ThreadIndex].Pointer != UINT32_MAX && pAllocationData->Threads[ThreadIndex].Pointer != pAllocationData->LatestPointer)
					found = true;
			if (Utils.InternalObjectBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount == 0 && found == false) {
				uint32_t Pointer = pAllocationData->Threads[ThreadIndex].Pointer;
				c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, UINT32_MAX);

				ObjectSignature* pSignature = NULL;
				Find_ObjectSignature(Allocation.Identifier, &pSignature);
				DestroyAndDeAllocate_Object(Pointer, pSignature);
			}
		}
	}
	return;
}
/*
* Added in 1.0.0
* Ends a Get_Pointer function and applies the results.
* Always call Get_Pointer before.
* @param Allocation, allocation of the desired object to end read/write of.
* @param Write, (MUST MATCH GET_POINTER THAT THIS IS PAIRED WITH)
* @param Consistent, (MUST MATCH GET_POINTER THAT THIS IS PAIRED WITH)
* @param ThreadIndex threadindex global.
* @note Thread Safe always.
* @note Not Synchronized but doesnt matter.
*/
void End_ResourceHeaderPointer(ResourceHeaderAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) {
	TEXRESULT tres = Success;
	AllocationData* pAllocationData = Get_ResourceHeaderAllocationData(Allocation);
	if (pAllocationData == NULL)
	{
		//Engine_Ref_FunctionError("End_ResourceHeaderPointer()", "pAllocationData == ", 0);
		return;
	}
	if (pAllocationData->Threads[ThreadIndex].Pointer == UINT32_MAX)
	{
		Engine_Ref_FunctionError("End_ResourceHeaderPointer()", "Invalid Call. ", 0);
		return;
	}
	if (pAllocationData->LatestPointer == UINT32_MAX)
	{
		Engine_Ref_FunctionError("End_ResourceHeaderPointer()", "LatestPointer Invalid. ", 0);
		return;
	}
	if (pAllocationData->Threads[ThreadIndex].Count == 0)
	{
		Engine_Ref_FunctionError("End_ResourceHeaderPointer()", "Count == ", 0);
		return;
	}

	if (Consistent == false && c89atomic_fetch_sub_32(&pAllocationData->Threads[ThreadIndex].Count, 1) == 1) {
		if (Write == true) {
			//Engine_Ref_FunctionError("End_ResourceHeaderPointer", "End Write On Pointer == ", Allocation.Pointer);
			uint32_t LatestPointer = Utils.InternalResourceHeaderBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.OverlayPointer;
			c89atomic_store_32(&Utils.InternalResourceHeaderBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.OverlayPointer, UINT32_MAX);

			c89atomic_store_32(&Utils.InternalResourceHeaderBuffer.Buffer[LatestPointer].Header.OverlayPointer, pAllocationData->Threads[ThreadIndex].Pointer);
			//lock usedcount for threadindex because its used as overlayand it might be destructed before;
			c89atomic_fetch_add_8(&Utils.InternalResourceHeaderBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);

			c89atomic_fetch_sub_8(&Utils.InternalResourceHeaderBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);
			c89atomic_fetch_sub_8(&Utils.InternalResourceHeaderBuffer.Buffer[LatestPointer].Header.UseCount, 1);

			c89atomic_store_32(&pAllocationData->LatestPointer, pAllocationData->Threads[ThreadIndex].Pointer);

			//every decrement of use count must have oppurtunity to destruct. (in this case overlaypointer aka latestpointer at allocate time);
			ResourceHeaderSignature* pSignature = NULL;
			Find_ResourceHeaderSignature(Allocation.Identifier, &pSignature);
			TryDestruct_ResourceHeader(pAllocationData, LatestPointer, pSignature, ThreadIndex);
		}
		else {
			//Engine_Ref_FunctionError("End_ResourceHeaderPointer", "End Read On Pointer == ", Allocation.Pointer);
			c89atomic_fetch_sub_8(&Utils.InternalResourceHeaderBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);
		}
		if (pAllocationData->Threads[ThreadIndex].Pointer != pAllocationData->LatestPointer) {
			ResourceHeaderSignature* pSignature = NULL;
			Find_ResourceHeaderSignature(Allocation.Identifier, &pSignature);
			TryDestruct_ResourceHeader(pAllocationData, pAllocationData->Threads[ThreadIndex].Pointer, pSignature, ThreadIndex);
			//this is fine because it doesnt destroy only if its not used and any other thread would call this after too.
			c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, UINT32_MAX);
		}
		if (pAllocationData->ScheduleDestruct == true) {
			bool found = false;
			for (size_t i = 0; i < maxthreads; i++)
				if (pAllocationData->Threads[ThreadIndex].Pointer != UINT32_MAX && pAllocationData->Threads[ThreadIndex].Pointer != pAllocationData->LatestPointer)
					found = true;
			if (Utils.InternalResourceHeaderBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount == 0 && found == false) {
				uint32_t Pointer = pAllocationData->Threads[ThreadIndex].Pointer;
				c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, UINT32_MAX);

				ResourceHeaderSignature* pSignature = NULL;
				Find_ResourceHeaderSignature(Allocation.Identifier, &pSignature);
				DestroyAndDeAllocate_ResourceHeader(Pointer, pSignature);
			}
		}
	}
	return;
}
/*
* Added in 1.0.0
* Ends a Get_Pointer function and applies the results.
* Always call Get_Pointer before.
* @param Allocation, allocation of the desired object to end read/write of.
* @param Write, (MUST MATCH GET_POINTER THAT THIS IS PAIRED WITH)
* @param Consistent, (MUST MATCH GET_POINTER THAT THIS IS PAIRED WITH)
* @param ThreadIndex threadindex global.
* @note Thread Safe always.
* @note Not Synchronized but doesnt matter.
*/
void End_ElementPointer(ElementAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) {
	TEXRESULT tres = Success;
	AllocationData* pAllocationData = Get_ElementAllocationData(Allocation);
	if (pAllocationData == NULL)
	{
		//Engine_Ref_FunctionError("End_ElementPointer()", "pAllocationData == ", 0);
		return;
	}
	if (pAllocationData->Threads[ThreadIndex].Pointer == UINT32_MAX)
	{
		Engine_Ref_FunctionError("End_ElementPointer()", "Invalid Call. ", 0);
		return;
	}
	if (pAllocationData->LatestPointer == UINT32_MAX)
	{
		Engine_Ref_FunctionError("End_ElementPointer()", "LatestPointer Invalid. ", 0);
		return;
	}
	if (pAllocationData->Threads[ThreadIndex].Count == 0)
	{
		Engine_Ref_FunctionError("End_ElementPointer()", "Count == ", 0);
		return;
	}

	if (Consistent == false && c89atomic_fetch_sub_32(&pAllocationData->Threads[ThreadIndex].Count, 1) == 1) {
		if (Write == true) {
			//Engine_Ref_FunctionError("End_ElementPointer", "End Write On Pointer == ", Allocation.Pointer);
			uint32_t LatestPointer = Utils.InternalElementBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.OverlayPointer;
			c89atomic_store_32(&Utils.InternalElementBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.OverlayPointer, UINT32_MAX);

			c89atomic_store_32(&Utils.InternalElementBuffer.Buffer[LatestPointer].Header.OverlayPointer, pAllocationData->Threads[ThreadIndex].Pointer);
			//lock usedcount for threadindex because its used as overlayand it might be destructed before;
			c89atomic_fetch_add_8(&Utils.InternalElementBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);

			c89atomic_fetch_sub_8(&Utils.InternalElementBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);
			c89atomic_fetch_sub_8(&Utils.InternalElementBuffer.Buffer[LatestPointer].Header.UseCount, 1);

			c89atomic_store_32(&pAllocationData->LatestPointer, pAllocationData->Threads[ThreadIndex].Pointer);

			//every decrement of use count must have oppurtunity to destruct. (in this case overlaypointer aka latestpointer at allocate time);
			ElementSignature* pSignature = NULL;
			Find_ElementSignature(Allocation.Identifier, &pSignature);
			TryDestruct_Element(pAllocationData, LatestPointer, pSignature, ThreadIndex);
		}
		else {
			//Engine_Ref_FunctionError("End_ElementPointer", "End Read On Pointer == ", Allocation.Pointer);
			c89atomic_fetch_sub_8(&Utils.InternalElementBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount, 1);
		}
		if (pAllocationData->Threads[ThreadIndex].Pointer != pAllocationData->LatestPointer) {
			ElementSignature* pSignature = NULL;
			Find_ElementSignature(Allocation.Identifier, &pSignature);
			TryDestruct_Element(pAllocationData, pAllocationData->Threads[ThreadIndex].Pointer, pSignature, ThreadIndex);
			//this is fine because it doesnt destroy only if its not used and any other thread would call this after too.
			c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, UINT32_MAX);
		}
		if (pAllocationData->ScheduleDestruct == true) {
			bool found = false;
			for (size_t i = 0; i < maxthreads; i++)
				if (pAllocationData->Threads[ThreadIndex].Pointer != UINT32_MAX && pAllocationData->Threads[ThreadIndex].Pointer != pAllocationData->LatestPointer)
					found = true;
			if (Utils.InternalElementBuffer.Buffer[pAllocationData->Threads[ThreadIndex].Pointer].Header.UseCount == 0 && found == false) {
				uint32_t Pointer = pAllocationData->Threads[ThreadIndex].Pointer;
				c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, UINT32_MAX);

				ElementSignature* pSignature = NULL;
				Find_ElementSignature(Allocation.Identifier, &pSignature);
				DestroyAndDeAllocate_Element(Pointer, pSignature);
			}
		}
	}
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Construct Buffer Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define Create_Buffer(name)\
{\
	pBuffer->BufferSize = InitialSize;\
	pBuffer->Buffer = calloc(pBuffer->BufferSize, sizeof(*pBuffer->Buffer));\
	pBuffer->ArenaAllocaters = calloc(EngineRes.pUtils->CPU.MaxThreads, sizeof(*pBuffer->ArenaAllocaters));\
	pBuffer->Indexes = calloc(EngineRes.pUtils->CPU.MaxThreads, sizeof(*pBuffer->Indexes));\
	if (pBuffer->ArenaAllocaters == NULL || pBuffer->Indexes == NULL || pBuffer->Buffer == NULL) {\
		Engine_Ref_FunctionError(name, "Out Of Memory.", 0);\
		return (Out_Of_Memory_Result | Failure);\
	}\
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)\
		Create_ArenaAllocater(&pBuffer->ArenaAllocaters[i], (i)*InitialSize, (i + 1) * InitialSize);\
}
#define Create_AllocationDataBuffer(name)\
{\
	pBuffer->AllocationDatas.BufferSize = InitialSize;\
	pBuffer->AllocationDatas.Buffer = calloc(pBuffer->AllocationDatas.BufferSize, sizeof(*pBuffer->AllocationDatas.Buffer));\
	pBuffer->AllocationDatas.ArenaAllocaters = calloc(EngineRes.pUtils->CPU.MaxThreads, sizeof(*pBuffer->AllocationDatas.ArenaAllocaters));\
	pBuffer->AllocationDatas.Indexes = calloc(EngineRes.pUtils->CPU.MaxThreads, sizeof(*pBuffer->AllocationDatas.Indexes));\
	if (pBuffer->AllocationDatas.ArenaAllocaters == NULL || pBuffer->AllocationDatas.Indexes == NULL || pBuffer->AllocationDatas.Buffer == NULL) {\
		Engine_Ref_FunctionError(name, "Out Of Memory.", 0);\
		return (Out_Of_Memory_Result | Failure);\
	}\
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)\
		Create_ArenaAllocater(&pBuffer->AllocationDatas.ArenaAllocaters[i], (i)*InitialSize, (i + 1) * InitialSize);\
}

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
		return (Invalid_Parameter | Failure);
	}
	if (InitialSize == NULL)
	{
		Engine_Ref_ArgsError("Create_ObjectBuffer()", "InitialSize == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	memset(pBuffer, 0, sizeof(*pBuffer));
	Create_Buffer("Create_ObjectBuffer()");
	Create_AllocationDataBuffer("Create_ObjectBuffer()");
	return (Success);
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
		return (Invalid_Parameter | Failure);
	}
	if (InitialSize == NULL)
	{
		Engine_Ref_ArgsError("Create_ResourceHeaderBuffer()", "InitialSize == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	memset(pBuffer, 0, sizeof(*pBuffer));
	Create_Buffer("Create_ResourceHeaderBuffer()");
	Create_AllocationDataBuffer("Create_ResourceHeaderBuffer()");
	return (Success);
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
		return (Invalid_Parameter | Failure);
	}
	if (InitialSize == NULL)
	{
		Engine_Ref_ArgsError("Create_ElementBuffer()", "InitialSize == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	memset(pBuffer, 0, sizeof(*pBuffer));
	Create_Buffer("Create_ElementBuffer()");
	Create_AllocationDataBuffer("Create_ElementBuffer()");
	return (Success);
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
TEXRESULT Create_Object(ObjectAllocation* pAllocation, ObjectCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex) {
	ObjectSignature* pSignature = NULL;
	Find_ObjectSignature(CreateInfo.Identifier, &pSignature);
#ifndef NDEBUG
	if (pAllocation == NULL)
	{
		Engine_Ref_ArgsError("Create_Object()", "pAllocation == NULL");
		return (Invalid_Parameter | Failure);
	}
	if (CreateInfo.Identifier == NULL)
	{
		Engine_Ref_ArgsError("Create_Object()", "CreateInfo.Identifier == NULL");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("Create_Object()", "pSignature == NULL, No Associated Signature Was Found For The Identifier");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->ByteLength == NULL)
	{
		Engine_Ref_ObjectError("Create_Object()", "pSignature", &pSignature, "pSignature.ByteLength == NULL");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->Identifier == NULL)
	{
		Engine_Ref_ObjectError("Create_Object()", "pSignature", &pSignature, "pSignature.Identifer == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;	
	uint64_t RequiredSizeBytes = NULL;
	if (pSignature->Constructor != NULL)
	{
		Create_ObjectTemplate* pFunction = *pSignature->Constructor;
		if ((tres = pFunction(NULL, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	uint64_t RequiredSizeChunks = (RequiredSizeBytes != NULL) ?
		RequiredSizeBytes / sizeof(Object) + ((RequiredSizeBytes % sizeof(Object)) != 0) :
		pSignature->ByteLength / sizeof(Object) + ((pSignature->ByteLength % sizeof(Object)) != 0);
	ObjectAllocation Allocation = {sizeof(Allocation)};
	uint32_t Pointer = 0;

	if ((tres = Allocate_ObjectAllocationData(pSignature, CreateInfo.Identifier, &Allocation, ThreadIndex)) != Success)
		return tres;
	if ((tres = Allocate_Object(pSignature, RequiredSizeChunks, CreateInfo.Identifier, Allocation, &Pointer, ThreadIndex)) != Success)
		return tres;


	Object* pObject = &Utils.InternalObjectBuffer.Buffer[Pointer];
	if (CreateInfo.Name != NULL)
		pObject->Header.Name = (UTF8*)CopyData((void*)CreateInfo.Name);
	else
	{
		UTF8 TempBuffer[20 + 65 + 65 + 1];
		memset(TempBuffer, 0, 20 + 65 + 65 + 1);
		sprintf((char*)TempBuffer, "Object_%i_%llu", CreateInfo.Identifier, RequiredSizeChunks);
		pObject->Header.Name = (UTF8*)CopyData((void*)TempBuffer);
	}
	if (pSignature->Constructor != NULL)
	{
		Create_ObjectTemplate* pFunction = *pSignature->Constructor;
		if ((tres = pFunction(pObject, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	AllocationData* pAllocationData = Get_ObjectAllocationData(Allocation);
	c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, Pointer);
	c89atomic_store_32(&pAllocationData->LatestPointer, Pointer);
	*pAllocation = Allocation;
	return (Success);
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
TEXRESULT Create_ResourceHeader(ResourceHeaderAllocation* pAllocation, ResourceHeaderCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex) {
	ResourceHeaderSignature* pSignature = NULL;
	Find_ResourceHeaderSignature(CreateInfo.Identifier, &pSignature);
#ifndef NDEBUG
	if (pAllocation == NULL)
	{
		Engine_Ref_ArgsError("Create_ResourceHeader()", "pAllocation == NULL");
		return (Invalid_Parameter | Failure);
	}
	if (CreateInfo.Identifier == NULL)
	{
		Engine_Ref_ArgsError("Create_ResourceHeader()", "CreateInfo.Identifier == NULL");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("Create_ResourceHeader()", "pSignature == NULL, No Associated Signature Was Found For The Identifier");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->ByteLength == NULL)
	{
		Engine_Ref_ObjectError("Create_ResourceHeader()", "pSignature", &pSignature, "pSignature.ByteLength == NULL");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->Identifier == NULL)
	{
		Engine_Ref_ObjectError("Create_ResourceHeader()", "pSignature", &pSignature, "pSignature.Identifer == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	uint64_t RequiredSizeBytes = NULL;
	if (pSignature->Constructor != NULL)
	{
		Create_ResourceHeaderTemplate* pFunction = *pSignature->Constructor;
		if ((tres = pFunction(NULL, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	uint64_t RequiredSizeChunks = (RequiredSizeBytes != NULL) ?
		RequiredSizeBytes / sizeof(ResourceHeader) + ((RequiredSizeBytes % sizeof(ResourceHeader)) != 0) :
		pSignature->ByteLength / sizeof(ResourceHeader) + ((pSignature->ByteLength % sizeof(ResourceHeader)) != 0);
	ResourceHeaderAllocation Allocation = { sizeof(Allocation) };
	uint32_t Pointer = 0;

	if ((tres = Allocate_ResourceHeaderAllocationData(pSignature, CreateInfo.Identifier, &Allocation, ThreadIndex)) != Success)
		return tres;
	if ((tres = Allocate_ResourceHeader(pSignature, RequiredSizeChunks, CreateInfo.Identifier, Allocation, &Pointer, ThreadIndex)) != Success)
		return tres;

	ResourceHeader* pResourceHeader = &Utils.InternalResourceHeaderBuffer.Buffer[Pointer];
	if (CreateInfo.Name != NULL)
		pResourceHeader->Header.Name = (UTF8*)CopyData((void*)CreateInfo.Name);
	else
	{
		UTF8 TempBuffer[20 + 65 + 65 + 1];
		memset(TempBuffer, 0, 20 + 65 + 65 + 1);
		sprintf((char*)TempBuffer, "ResourceHeader_%i_%llu", CreateInfo.Identifier, RequiredSizeChunks);
		pResourceHeader->Header.Name = (UTF8*)CopyData((void*)TempBuffer);
	}
	if (pSignature->Constructor != NULL)
	{
		Create_ResourceHeaderTemplate* pFunction = *pSignature->Constructor;
		if ((tres = pFunction(pResourceHeader, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	AllocationData* pAllocationData = Get_ResourceHeaderAllocationData(Allocation);
	c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, Pointer);
	c89atomic_store_32(&pAllocationData->LatestPointer, Pointer);
	*pAllocation = Allocation;
	return (Success);
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
TEXRESULT Create_Element(ElementAllocation* pAllocation, ElementCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex) {
	ElementSignature* pSignature = NULL;
	Find_ElementSignature(CreateInfo.Identifier, &pSignature);
#ifndef NDEBUG
	if (pAllocation == NULL)
	{
		Engine_Ref_ArgsError("Create_Element()", "pAllocation == NULL");
		return (Invalid_Parameter | Failure);
	}
	if (CreateInfo.Identifier == NULL)
	{
		Engine_Ref_ArgsError("Create_Element()", "CreateInfo.Identifier == NULL");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("Create_Element()", "pSignature == NULL, No Associated Signature Was Found For The Identifier");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->ByteLength == NULL)
	{
		Engine_Ref_ObjectError("Create_Element()", "pSignature", &pSignature, "pSignature.ByteLength == NULL");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->Identifier == NULL)
	{
		Engine_Ref_ObjectError("Create_Element()", "pSignature", &pSignature, "pSignature.Identifer == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	uint64_t RequiredSizeBytes = NULL;
	if (pSignature->Constructor != NULL)
	{
		Create_ElementTemplate* pFunction = *pSignature->Constructor;
		if ((tres = pFunction(NULL, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	uint64_t RequiredSizeChunks = (RequiredSizeBytes != NULL) ?
		RequiredSizeBytes / sizeof(Element) + ((RequiredSizeBytes % sizeof(Element)) != 0) :
		pSignature->ByteLength / sizeof(Element) + ((pSignature->ByteLength % sizeof(Element)) != 0);
	ElementAllocation Allocation = { sizeof(Allocation) };
	uint32_t Pointer = 0;

	if ((tres = Allocate_ElementAllocationData(pSignature, CreateInfo.Identifier, &Allocation, ThreadIndex)) != Success)
		return tres;
	if ((tres = Allocate_Element(pSignature, RequiredSizeChunks, CreateInfo.Identifier, Allocation, &Pointer, ThreadIndex)) != Success)
		return tres;

	Element* pElement = &Utils.InternalElementBuffer.Buffer[Pointer];	
	if (CreateInfo.Name != NULL)
		pElement->Header.Name = (UTF8*)CopyData((void*)CreateInfo.Name);
	else
	{
		UTF8 TempBuffer[20 + 65 + 65 + 1];
		memset(TempBuffer, 0, 20 + 65 + 65 + 1);
		sprintf((char*)TempBuffer, "Element_%i_%llu", CreateInfo.Identifier, RequiredSizeChunks);
		pElement->Header.Name = (UTF8*)CopyData((void*)TempBuffer);
	}
	if (pSignature->Constructor != NULL)
	{
		Create_ElementTemplate* pFunction = *pSignature->Constructor;
		if ((tres = pFunction(pElement, pCreateInfo, &RequiredSizeBytes, ThreadIndex)) != Success)
			return tres;
	}
	AllocationData* pAllocationData = Get_ElementAllocationData(Allocation);
	c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, Pointer);
	c89atomic_store_32(&pAllocationData->LatestPointer, Pointer);
	*pAllocation = Allocation;
	return (Success);
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
TEXRESULT Destroy_Object(ObjectAllocation Allocation, bool Full, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ObjectAllocationData(Allocation);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Destroy_Object()", "Allocation Invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	//destroy should destroy anything it can via overlay pointer (which is the previous latest pointer for it?), and then set rest to NULL ? ;
	//if overlay == UINT32_MAX then it has full ownerhsip otherwise usual destruct regime;
	//overlay pointer is just the latest pointer during this stage;
	//if pointer is uint32_t max it means that it hasnt been aquirred yet, otherwise make consistent.
	TEXRESULT tres = Success;
	Object* pObject = Get_ObjectPointer(Allocation, true, false, ThreadIndex);
	if (pObject == NULL)
		return (Failure);

	ObjectSignature* pSignature = NULL;
	Find_ObjectSignature(pObject->Header.Allocation.Identifier, &pSignature);
	Destroy_ObjectInstance(pAllocationData->Threads[ThreadIndex].Pointer, pSignature, false, ThreadIndex);
	if (Full == true)
	{
		pAllocationData->ScheduleDestruct = true;
	}
	End_ObjectPointer(Allocation, true, false, ThreadIndex);
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
TEXRESULT Destroy_ResourceHeader(ResourceHeaderAllocation Allocation, bool Full, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ResourceHeaderAllocationData(Allocation);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Destroy_ResourceHeader()", "Allocation Invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	//destroy should destroy anything it can via overlay pointer (which is the previous latest pointer for it?), and then set rest to NULL ? ;
	//if overlay == UINT32_MAX then it has full ownerhsip otherwise usual destruct regime;
	//overlay pointer is just the latest pointer during this stage;
	//if pointer is uint32_t max it means that it hasnt been aquirred yet, otherwise make consistent.
	TEXRESULT tres = Success;
	ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation, true, false, ThreadIndex);
	if (pResourceHeader == NULL)
		return (Failure);

	ResourceHeaderSignature* pSignature = NULL;
	Find_ResourceHeaderSignature(pResourceHeader->Header.Allocation.Identifier, &pSignature);
	Destroy_ResourceHeaderInstance(pAllocationData->Threads[ThreadIndex].Pointer, pSignature, false, ThreadIndex);
	if (Full == true)
	{
		pAllocationData->ScheduleDestruct = true;
	}
	End_ResourceHeaderPointer(Allocation, true, false, ThreadIndex);
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
TEXRESULT Destroy_Element(ElementAllocation Allocation, bool Full, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ElementAllocationData(Allocation);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Destroy_Element()", "Allocation Invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	//destroy should destroy anything it can via overlay pointer (which is the previous latest pointer for it?), and then set rest to NULL ? ;
	//if overlay == UINT32_MAX then it has full ownerhsip otherwise usual destruct regime;
	//overlay pointer is just the latest pointer during this stage;
	//if pointer is uint32_t max it means that it hasnt been aquirred yet, otherwise make consistent.
	TEXRESULT tres = Success;
	Element* pElement = Get_ElementPointer(Allocation, true, false, ThreadIndex);
	if (pElement == NULL)
		return (Failure);

	ElementSignature* pSignature = NULL;
	Find_ElementSignature(pElement->Header.Allocation.Identifier, &pSignature);
	Destroy_ElementInstance(pAllocationData->Threads[ThreadIndex].Pointer, pSignature, false, ThreadIndex);
	if (Full == true)
	{
		pAllocationData->ScheduleDestruct = true;
	}
	End_ElementPointer(Allocation, true, false, ThreadIndex);
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
TEXRESULT ReCreate_Object(ObjectAllocation Allocation, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ObjectAllocationData(Allocation);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_Object()", "Allocation Invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	Object* pObject = Get_ObjectPointer(Allocation, true, false, ThreadIndex);
	if (pObject == NULL)
		return (Failure);

	ObjectSignature* pSignature = NULL;
	Find_ObjectSignature(pObject->Header.Allocation.Identifier, &pSignature);
	//destruct everything;
	Destroy_Object(Allocation, false, ThreadIndex);
	//sort out recreate;
	if (pSignature->ReConstructor != NULL)
	{
		ReCreate_ObjectTemplate* pFunction = *pSignature->ReConstructor;
		if ((tres = pFunction(pObject, ThreadIndex)) != Success)
			return tres;
	}
	End_ObjectPointer(Allocation, true, false, ThreadIndex);
	return (Success);
}
/*
* Added in 1.0.0
* Recreate ResourceHeader with new data.
* @param Allocation refrencing the desired ResourceHeader to update.
* @param pInstance pointer to ResourceHeader created by CreateInstance_ResourceHeader(), if its null recreate will be not multithreaded safe.
* @param ThreadIndex Index of the thread that is calling this.
* @note Externally Synchronized.
*/
TEXRESULT ReCreate_ResourceHeader(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ResourceHeaderAllocationData(Allocation);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_ResourceHeader()", "Allocation Invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation, true, false, ThreadIndex);
	if (pResourceHeader == NULL)
		return (Failure);

	ResourceHeaderSignature* pSignature = NULL;
	Find_ResourceHeaderSignature(pResourceHeader->Header.Allocation.Identifier, &pSignature);
	//destruct everything;
	Destroy_ResourceHeader(Allocation, false, ThreadIndex);
	//sort out recreate;
	if (pSignature->ReConstructor != NULL)
	{
		ReCreate_ResourceHeaderTemplate* pFunction = *pSignature->ReConstructor;
		if ((tres = pFunction(pResourceHeader, ThreadIndex)) != Success)
			return tres;
	}
	End_ResourceHeaderPointer(Allocation, true, false, ThreadIndex);
	return (Success);
}
/*
* Added in 1.0.0
* Recreate Element with new data.
* @param Allocation refrencing the desired Element to update.
* @param pInstance pointer to Element created by CreateInstance_Element(), if its null recreate will be not multithreaded safe.
* @param ThreadIndex Index of the thread that is calling this.
* @note Externally Synchronized.
*/
TEXRESULT ReCreate_Element(ElementAllocation Allocation, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ElementAllocationData(Allocation);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_Element()", "Allocation Invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	Element* pElement = Get_ElementPointer(Allocation, true, false, ThreadIndex);
	if (pElement == NULL)
		return (Failure);

	ElementSignature* pSignature = NULL;
	Find_ElementSignature(pElement->Header.Allocation.Identifier, &pSignature);
	//destruct everything;
	Destroy_Element(Allocation, false, ThreadIndex);
	//sort out recreate;
	if (pSignature->ReConstructor != NULL)
	{
		ReCreate_ElementTemplate* pFunction = *pSignature->ReConstructor;
		if ((tres = pFunction(pElement, ThreadIndex)) != Success)
			return tres;
	}
	End_ElementPointer(Allocation, true, false, ThreadIndex);
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Resizes Buffer Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define Resize_Buffer(name)\
{\
	Resize_Array((void**)&pBuffer->Buffer, pBuffer->BufferSize, NewSize, sizeof(*pBuffer->Buffer));\
	pBuffer->BufferSize = NewSize;\
	Resize_Array((void**)&pBuffer->AllocationDatas.Buffer, pBuffer->AllocationDatas.BufferSize, NewSize, sizeof(*pBuffer->AllocationDatas.Buffer));\
	pBuffer->AllocationDatas.BufferSize = NewSize;\
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {\
		pBuffer->ArenaAllocaters[i].StartPtr = (i)*NewSize;\
		pBuffer->ArenaAllocaters[i].EndPtr = (i + 1) * NewSize;\
		pBuffer->AllocationDatas.ArenaAllocaters[i].StartPtr = (i)*NewSize;\
		pBuffer->AllocationDatas.ArenaAllocaters[i].EndPtr = (i + 1) * NewSize;\
	}\
}

/*
* Added in 1.0.0
* Resizes specified buffer to newsize.
* doesnt compact, there will be excess space in the array.
* resize functions are super expensive and shouldnt be done often.
* destroys all objects that are no longer in range.
* @param pBuffer pointer to a buffer object to resize.
* @param NewSize is in allocation chunks. (1 Object == 1 chunk).
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Resize_ObjectBuffer(ObjectBuffer* pBuffer, uint64_t NewSize, uint32_t ThreadIndex) {
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Resize_ObjectBuffer()", "pBuffer == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (NewSize == NULL)
	{
		Engine_Ref_ArgsError("Resize_ObjectBuffer()", "NewSize == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Lock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Lock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	uint32_t AllocationsToCut = 0;
	uint32_t AllocationBufferSize = pBuffer->AllocationDatas.BufferSize;
	uint32_t ObjectBufferSize = pBuffer->BufferSize;
	if (NewSize < pBuffer->AllocationDatas.BufferSize)
	{
		//set all allocations that are out of range to destruct.
		for (size_t i = NewSize; i < pBuffer->AllocationDatas.BufferSize; i++) {
			AllocationData* pAllocationData = &pBuffer->AllocationDatas.Buffer[i];
			if (pAllocationData->Allocation.Object.Identifier != 0) {
				Destroy_Object(pAllocationData->Allocation.Object, true, ThreadIndex);
				AllocationsToCut++;
			}
		}
	}
	if (NewSize < pBuffer->BufferSize)
	{
		//set all items that are out of range to destruct.
		//the problem is you arent supposed to destruct allocation instances like this;
		for (size_t i = NewSize; i < pBuffer->BufferSize;) {
			Object* pObject = &pBuffer->Buffer[i];
			if (pObject->Header.AllocationSize != NULL) {
				//if it is under newsize then we can assure that  it hasnt been counted yet, otherwise it has.
				if ((pObject->Header.Allocation.Pointer < NewSize))
				{
					Destroy_Object(pObject->Header.Allocation, true, ThreadIndex);
					AllocationsToCut++;
				}
				i += pObject->Header.AllocationSize;
			}
			else {
				i++;
			}
		}
	}
	//wait for them to destruct
	while (pBuffer->AllocationDatas.AllocationsCount > (AllocationBufferSize - AllocationsToCut)) {

	}
	Resize_Buffer("Resize_ObjectBuffer()");

	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Unlock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Unlock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	return (Success);
}
/*
* Added in 1.0.0
* Resizes specified buffer to newsize.
* doesnt compact, there will be excess space in the array.
* resize functions are super expensive and shouldnt be done often.
* destroys all objects that are no longer in range.
* @param pBuffer pointer to a buffer object to resize.
* @param NewSize is in allocation chunks. (1 Object == 1 chunk).
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Resize_ResourceHeaderBuffer(ResourceHeaderBuffer* pBuffer, uint64_t NewSize, uint32_t ThreadIndex) {
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Resize_ResourceHeaderBuffer()", "pBuffer == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (NewSize == NULL)
	{
		Engine_Ref_ArgsError("Resize_ResourceHeaderBuffer()", "NewSize == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Lock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Lock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	uint32_t AllocationsToCut = 0;
	uint32_t AllocationBufferSize = pBuffer->AllocationDatas.BufferSize;
	uint32_t ResourceHeaderBufferSize = pBuffer->BufferSize;
	if (NewSize < pBuffer->AllocationDatas.BufferSize)
	{
		//set all allocations that are out of range to destruct.
		for (size_t i = NewSize; i < pBuffer->AllocationDatas.BufferSize; i++) {
			AllocationData* pAllocationData = &pBuffer->AllocationDatas.Buffer[i];
			if (pAllocationData->Allocation.ResourceHeader.Identifier != 0) {
				Destroy_ResourceHeader(pAllocationData->Allocation.ResourceHeader, true, ThreadIndex);
				AllocationsToCut++;
			}
		}
	}
	if (NewSize < pBuffer->BufferSize)
	{
		//set all items that are out of range to destruct.
		//the problem is you arent supposed to destruct allocation instances like this;
		for (size_t i = NewSize; i < pBuffer->BufferSize;) {
			ResourceHeader* pResourceHeader = &pBuffer->Buffer[i];
			if (pResourceHeader->Header.AllocationSize != NULL) {
				//if it is under newsize then we can assure that  it hasnt been counted yet, otherwise it has.
				if ((pResourceHeader->Header.Allocation.Pointer < NewSize))
				{
					Destroy_ResourceHeader(pResourceHeader->Header.Allocation, true, ThreadIndex);
					AllocationsToCut++;
				}
				i += pResourceHeader->Header.AllocationSize;
			}
			else {
				i++;
			}
		}
	}
	//wait for them to destruct
	while (pBuffer->AllocationDatas.AllocationsCount > (AllocationBufferSize - AllocationsToCut)) {

	}
	Resize_Buffer("Resize_ResourceHeaderBuffer()");

	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Unlock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Unlock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	return (Success);
}
/*
* Added in 1.0.0
* Resizes specified buffer to newsize.
* doesnt compact, there will be excess space in the array.
* resize functions are super expensive and shouldnt be done often.
* destroys all objects that are no longer in range.
* @param pBuffer pointer to a buffer object to resize.
* @param NewSize is in allocation chunks. (1 Object == 1 chunk).
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Resize_ElementBuffer(ElementBuffer* pBuffer, uint64_t NewSize, uint32_t ThreadIndex) {
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Resize_ElementBuffer()", "pBuffer == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (NewSize == NULL)
	{
		Engine_Ref_ArgsError("Resize_ElementBuffer()", "NewSize == NULL");
		return (Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Lock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Lock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	uint32_t AllocationsToCut = 0;
	uint32_t AllocationBufferSize = pBuffer->AllocationDatas.BufferSize;
	uint32_t ElementBufferSize = pBuffer->BufferSize;
	if (NewSize < pBuffer->AllocationDatas.BufferSize)
	{
		//set all allocations that are out of range to destruct.
		for (size_t i = NewSize; i < pBuffer->AllocationDatas.BufferSize; i++) {
			AllocationData* pAllocationData = &pBuffer->AllocationDatas.Buffer[i];
			if (pAllocationData->Allocation.Element.Identifier != 0) {
				Destroy_Element(pAllocationData->Allocation.Element, true, ThreadIndex);
				AllocationsToCut++;
			}
		}
	}
	if (NewSize < pBuffer->BufferSize)
	{
		//set all items that are out of range to destruct.
		//the problem is you arent supposed to destruct allocation instances like this;
		for (size_t i = NewSize; i < pBuffer->BufferSize;) {
			Element* pElement = &pBuffer->Buffer[i];
			if (pElement->Header.AllocationSize != NULL) {
				//if it is under newsize then we can assure that  it hasnt been counted yet, otherwise it has.
				if ((pElement->Header.Allocation.Pointer < NewSize))
				{
					Destroy_Element(pElement->Header.Allocation, true, ThreadIndex);
					AllocationsToCut++;
				}
				i += pElement->Header.AllocationSize;
			}
			else {
				i++;
			}
		}
	}
	//wait for them to destruct
	while (pBuffer->AllocationDatas.AllocationsCount > (AllocationBufferSize - AllocationsToCut)) {

	}
	Resize_Buffer("Resize_ElementBuffer()");

	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Unlock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Unlock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Destruct Buffers Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define Destroy_Buffer()\
{\
	if (pBuffer->Indexes != NULL)\
		free(pBuffer->Indexes);\
	pBuffer->Indexes = NULL;\
	pBuffer->BufferSize = 0;\
	if (pBuffer->Buffer != NULL)\
		free(pBuffer->Buffer);\
	if (pBuffer->ArenaAllocaters != NULL) {\
		for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)\
			Destroy_ArenaAllocater(&pBuffer->ArenaAllocaters[i]);\
		free(pBuffer->ArenaAllocaters);\
	}\
	pBuffer->ArenaAllocaters = NULL;\
	if (pBuffer->AllocationDatas.Indexes != NULL)\
		free(pBuffer->AllocationDatas.Indexes);\
	pBuffer->AllocationDatas.Indexes = NULL;\
	pBuffer->AllocationDatas.BufferSize = 0;\
	if (pBuffer->AllocationDatas.Buffer != NULL)\
		free(pBuffer->AllocationDatas.Buffer);\
	if (pBuffer->AllocationDatas.ArenaAllocaters != NULL) {\
		for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)\
			Destroy_ArenaAllocater(&pBuffer->AllocationDatas.ArenaAllocaters[i]);\
		free(pBuffer->AllocationDatas.ArenaAllocaters);\
	}\
	pBuffer->AllocationDatas.ArenaAllocaters = NULL;\
	memset(pBuffer, 0, sizeof(*pBuffer));\
}

/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
* @param pBuffer refrencing the desired buffer to destroy.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Destroy_ObjectBuffer(ObjectBuffer* pBuffer, uint32_t ThreadIndex) {
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Destroy_ObjectBuffer", "pBuffer == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Lock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Lock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	//set all items in buffer to destruct.
	for (size_t i = 0; i < pBuffer->AllocationDatas.BufferSize; i++) {
		AllocationData* pAllocationData = &pBuffer->AllocationDatas.Buffer[i];
		if (pAllocationData->Allocation.Object.Identifier != 0) {
			Destroy_Object(pAllocationData->Allocation.Object, true, ThreadIndex);
		}
	}
	//wait for all in the buffer to destruct.
	while (pBuffer->AllocationDatas.AllocationsCount > 0) {
		 
	}
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Unlock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Unlock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	//period between unlock and destruct that is unsafe;
	//mayby fix it by adding checks in the allocaters;
	//cleanup.
	Destroy_Buffer();
	return (Success);
}
/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
* @param pBuffer refrencing the desired buffer to destroy.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Destroy_ResourceHeaderBuffer(ResourceHeaderBuffer* pBuffer, uint32_t ThreadIndex) {
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Destroy_ResourceHeaderBuffer", "pBuffer == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Lock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Lock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	//set all items in buffer to destruct.
	for (size_t i = 0; i < pBuffer->AllocationDatas.BufferSize; i++) {
		AllocationData* pAllocationData = &pBuffer->AllocationDatas.Buffer[i];
		if (pAllocationData->Allocation.ResourceHeader.Identifier != 0) {
			Destroy_ResourceHeader(pAllocationData->Allocation.ResourceHeader, true, ThreadIndex);
		}
	}
	//wait for all in the buffer to destruct.
	while (pBuffer->AllocationDatas.AllocationsCount > 0) {

	}
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Unlock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Unlock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	//cleanup.
	Destroy_Buffer();
	return (Success);
}
/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
* @param pBuffer refrencing the desired buffer to destroy.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Destroy_ElementBuffer(ElementBuffer* pBuffer, uint32_t ThreadIndex) {
#ifndef NDEBUG
	if (pBuffer == NULL)
	{
		Engine_Ref_ArgsError("Destroy_ElementBuffer", "pBuffer == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Lock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Lock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	//set all items in buffer to destruct.
	for (size_t i = 0; i < pBuffer->AllocationDatas.BufferSize; i++) {
		AllocationData* pAllocationData = &pBuffer->AllocationDatas.Buffer[i];
		if (pAllocationData->Allocation.Element.Identifier != 0) {
			Destroy_Element(pAllocationData->Allocation.Element, true, ThreadIndex);
		}
	}
	//wait for all in the buffer to destruct.
	while (pBuffer->AllocationDatas.AllocationsCount > 0) {

	}
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++) {
		Engine_Ref_Unlock_Mutex(&pBuffer->ArenaAllocaters[i].Mutex);
		Engine_Ref_Unlock_Mutex(&pBuffer->AllocationDatas.ArenaAllocaters[i].Mutex);
	}
	//cleanup.
	Destroy_Buffer();
	return (Success);
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
void Add_ObjectChild(ObjectAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ObjectAllocationData(Allocation);
	AllocationData* pParentAllocationData = Get_ObjectAllocationData(Parent);
#ifndef NDEBUG
	if (pAllocationData == NULL) {
		Engine_Ref_ArgsError("Add_ObjectChild()", "Allocation Invalid");
		return;
	}
	if (pParentAllocationData == NULL) {
		Engine_Ref_ArgsError("Add_ObjectChild()", "Parent Invalid.");
		return;
	}
#endif
	{
		Object* pParent = Get_ObjectPointer(Parent, true, false, ThreadIndex);
		if (pParent == NULL)
			return (Failure);
		Object* pParentOverlay = (pParent->Header.OverlayPointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pParent->Header.OverlayPointer] : NULL;

		if (((pParentOverlay != NULL) ? (pParent->Header.iChildren == pParentOverlay->Header.iChildren) : false)) {
			//copy new
			pParent->Header.iChildren = CopyDataN(pParent->Header.iChildren, sizeof(*pParent->Header.iChildren) * pParent->Header.iChildrenSize);
		}

		Resize_Array((void**)&pParent->Header.iChildren, pParent->Header.iChildrenSize, pParent->Header.iChildrenSize + 1, sizeof(*pParent->Header.iChildren));
		pParent->Header.iChildrenSize = pParent->Header.iChildrenSize + 1;
		pParent->Header.iChildren[pParent->Header.iChildrenSize - 1] = Allocation;
		End_ObjectPointer(Parent, true, false, ThreadIndex);
	}
	{
		Object* pChild = Get_ObjectPointer(Allocation, true, false, ThreadIndex);
		if (pChild == NULL)
			return (Failure);
		pChild->Header.iParent = Parent;
		End_ObjectPointer(Allocation, true, false, ThreadIndex);
	}
}
/*
* Added in 1.0.0
* Macro for adding childs to objects.
* @param Allocation refrencing the desired resourceheader to make child of.
* @param Parent refrencing the desired object to make parent of Allocation.
* @note Externally Synchronized.
*/
void Add_Object_ResourceHeaderChild(ResourceHeaderAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ResourceHeaderAllocationData(Allocation);
	AllocationData* pParentAllocationData = Get_ObjectAllocationData(Parent);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Add_Object_ResourceHeaderChild()", "Allocation Invalid");
		return;
	}
	if (pParentAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Add_Object_ResourceHeaderChild()", "Parent Invalid.");
		return;
	}
#endif
	{
		Object* pParent = Get_ObjectPointer(Parent, true, false, ThreadIndex);
		if (pParent == NULL)
			return (Failure);
		Object* pParentOverlay = (pParent->Header.OverlayPointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pParent->Header.OverlayPointer] : NULL;

		if (((pParentOverlay != NULL) ? (pParent->Header.iResourceHeaders == pParentOverlay->Header.iResourceHeaders) : false)) {
			//copy new
			pParent->Header.iResourceHeaders = CopyDataN(pParent->Header.iResourceHeaders, sizeof(*pParent->Header.iResourceHeaders) * pParent->Header.iResourceHeadersSize);
		}

		Resize_Array((void**)&pParent->Header.iResourceHeaders, pParent->Header.iResourceHeadersSize, pParent->Header.iResourceHeadersSize + 1, sizeof(*pParent->Header.iResourceHeaders));
		pParent->Header.iResourceHeadersSize = pParent->Header.iResourceHeadersSize + 1;
		pParent->Header.iResourceHeaders[pParent->Header.iResourceHeadersSize - 1] = Allocation;
		End_ObjectPointer(Parent, true, false, ThreadIndex);
	}
	{
		ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation, true, false, ThreadIndex);
		if (pResourceHeader == NULL)
			return (Failure);
		ResourceHeader* pResourceHeaderOverlay = (pResourceHeader->Header.OverlayPointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pResourceHeader->Header.OverlayPointer] : NULL;

		if (((pResourceHeaderOverlay != NULL) ? (pResourceHeader->Header.iObjects == pResourceHeaderOverlay->Header.iObjects) : false)) {
			//copy new
			pResourceHeader->Header.iObjects = CopyDataN(pResourceHeader->Header.iObjects, sizeof(*pResourceHeader->Header.iObjects) * pResourceHeader->Header.iObjectsSize);
		}

		Resize_Array((void**)&pResourceHeader->Header.iObjects, pResourceHeader->Header.iObjectsSize, pResourceHeader->Header.iObjectsSize + 1, sizeof(*pResourceHeader->Header.iObjects));
		pResourceHeader->Header.iObjectsSize = pResourceHeader->Header.iObjectsSize + 1;
		pResourceHeader->Header.iObjects[pResourceHeader->Header.iObjectsSize - 1] = Parent;
		End_ResourceHeaderPointer(Allocation, true, false, ThreadIndex);
	}
}
/*
* Added in 1.0.0
* Macro for adding childs to objects.
* @param Allocation refrencing the desired element to make child of.
* @param Parent refrencing the desired resourceheader to make parent of Allocation.
* @note Externally Synchronized.
*/
void Add_ResourceHeader_ElementChild(ElementAllocation Allocation, ResourceHeaderAllocation Parent, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ElementAllocationData(Allocation);
	AllocationData* pParentAllocationData = Get_ResourceHeaderAllocationData(Parent);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Add_ResourceHeader_ElementChild()", "Allocation Invalid");
		return;
	}
	if (pParentAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Add_ResourceHeader_ElementChild()", "Parent Invalid.");
		return;
	}
#endif
	{
		ResourceHeader* pParent = Get_ResourceHeaderPointer(Parent, true, false, ThreadIndex);
		if (pParent == NULL)
			return (Failure);
		ResourceHeader* pParentOverlay = (pParent->Header.OverlayPointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pParent->Header.OverlayPointer] : NULL;

		if (((pParentOverlay != NULL) ? (pParent->Header.iElements == pParentOverlay->Header.iElements) : false)) {
			//copy new
			pParent->Header.iElements = CopyDataN(pParent->Header.iElements, sizeof(*pParent->Header.iElements) * pParent->Header.iElementsSize);
		}

		Resize_Array((void**)&pParent->Header.iElements, pParent->Header.iElementsSize, pParent->Header.iElementsSize + 1, sizeof(*pParent->Header.iElements));
		pParent->Header.iElementsSize = pParent->Header.iElementsSize + 1;
		pParent->Header.iElements[pParent->Header.iElementsSize - 1] = Allocation;
		End_ResourceHeaderPointer(Parent, true, false, ThreadIndex);
	}
	{
		Element* pElement = Get_ElementPointer(Allocation, true, false, ThreadIndex);
		if (pElement == NULL)
			return (Failure);
		Element* pElementOverlay = (pElement->Header.OverlayPointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pElement->Header.OverlayPointer] : NULL;

		if (((pElementOverlay != NULL) ? (pElement->Header.iResourceHeaders == pElementOverlay->Header.iResourceHeaders) : false)) {
			//copy new
			pElement->Header.iResourceHeaders = CopyDataN(pElement->Header.iResourceHeaders, sizeof(*pElement->Header.iResourceHeaders) * pElement->Header.iResourceHeadersSize);
		}

		Resize_Array((void**)&pElement->Header.iResourceHeaders, pElement->Header.iResourceHeadersSize, pElement->Header.iResourceHeadersSize + 1, sizeof(*pElement->Header.iResourceHeaders));
		pElement->Header.iResourceHeadersSize = pElement->Header.iResourceHeadersSize + 1;
		pElement->Header.iResourceHeaders[pElement->Header.iResourceHeadersSize - 1] = Parent;
		End_ElementPointer(Allocation, true, false, ThreadIndex);
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
void Remove_ObjectChild(ObjectAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ObjectAllocationData(Allocation);
	AllocationData* pParentAllocationData = Get_ObjectAllocationData(Parent);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Remove_ObjectChild()", "Allocation Invalid");
		return;
	}
	if (pParentAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Remove_ObjectChild", "Parent Invalid.");
		return;
	}
#endif
	{
		Object* pParent = Get_ObjectPointer(Parent, true, false, ThreadIndex);
		if (pParent == NULL)
			return (Failure);
		Object* pParentOverlay = (pParent->Header.OverlayPointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pParent->Header.OverlayPointer] : NULL;

		if (((pParentOverlay != NULL) ? (pParent->Header.iChildren == pParentOverlay->Header.iChildren) : false)) {
			//copy new
			pParent->Header.iChildren = CopyDataN(pParent->Header.iChildren, sizeof(*pParent->Header.iChildren) * pParent->Header.iChildrenSize);
		}

		for (size_t i = 0; i < pParent->Header.iChildrenSize; i++)
		{
			if (Compare_ObjectAllocation(pParent->Header.iChildren[i], Allocation) == Success)
			{
				RemoveMember_Array((void**)&pParent->Header.iChildren, pParent->Header.iChildrenSize, i, sizeof(*pParent->Header.iChildren), 1);
				pParent->Header.iChildrenSize = pParent->Header.iChildrenSize - 1;
			}
		}
		End_ObjectPointer(Parent, true, false, ThreadIndex);
	}
	{
		Object* pChild = Get_ObjectPointer(Allocation, true, false, ThreadIndex);
		if (pChild == NULL)
			return (Failure);
		memset(&pChild->Header.iParent, 0, sizeof(pChild->Header.iParent));
		End_ObjectPointer(Allocation, true, false, ThreadIndex);
	}
}
/*
* Added in 1.0.0
* Macro for removing childs from objects.
* @param Allocation refrencing the desired resourceheader to remove child of.
* @param Parent refrencing the desired object to remove parent of Allocation.
* @note Externally Synchronized.
*/
void Remove_Object_ResourceHeaderChild(ResourceHeaderAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ResourceHeaderAllocationData(Allocation);
	AllocationData* pParentAllocationData = Get_ObjectAllocationData(Parent);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Remove_ResourceHeader_ElementChild()", "Allocation Invalid");
		return;
	}
	if (pParentAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Remove_Object_ResourceHeaderChild", "Parent Invalid.");
		return;
	}
#endif
	{
		Object* pParent = Get_ObjectPointer(Parent, true, false, ThreadIndex);
		if (pParent == NULL)
			return (Failure);
		Object* pParentOverlay = (pParent->Header.OverlayPointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pParent->Header.OverlayPointer] : NULL;

		if (((pParentOverlay != NULL) ? (pParent->Header.iResourceHeaders == pParentOverlay->Header.iResourceHeaders) : false)) {
			//copy new
			pParent->Header.iResourceHeaders = CopyDataN(pParent->Header.iResourceHeaders, sizeof(*pParent->Header.iResourceHeaders) * pParent->Header.iResourceHeadersSize);
		}

		for (size_t i = 0; i < pParent->Header.iResourceHeadersSize; i++)
		{
			if (Compare_ResourceHeaderAllocation(pParent->Header.iResourceHeaders[i], Allocation) == Success)
			{
				RemoveMember_Array((void**)&pParent->Header.iResourceHeaders, pParent->Header.iResourceHeadersSize, i, sizeof(*pParent->Header.iResourceHeaders), 1);
				pParent->Header.iResourceHeadersSize = pParent->Header.iResourceHeadersSize - 1;
			}
		}
		End_ObjectPointer(Parent, true, false, ThreadIndex);
	}
	{
		ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation, true, false, ThreadIndex);
		if (pResourceHeader == NULL)
			return (Failure);
		ResourceHeader* pResourceHeaderOverlay = (pResourceHeader->Header.OverlayPointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pResourceHeader->Header.OverlayPointer] : NULL;

		if (((pResourceHeaderOverlay != NULL) ? (pResourceHeader->Header.iObjects == pResourceHeaderOverlay->Header.iObjects) : false)) {
			//copy new
			pResourceHeader->Header.iObjects = CopyDataN(pResourceHeader->Header.iObjects, sizeof(*pResourceHeader->Header.iObjects) * pResourceHeader->Header.iObjectsSize);
		}

		for (size_t i = 0; i < pResourceHeader->Header.iObjectsSize; i++)
		{
			if (Compare_ObjectAllocation(pResourceHeader->Header.iObjects[i], Parent) == Success)
			{
				RemoveMember_Array((void**)&pResourceHeader->Header.iObjects, pResourceHeader->Header.iObjectsSize, i, sizeof(*pResourceHeader->Header.iObjects), 1);
				pResourceHeader->Header.iObjectsSize = pResourceHeader->Header.iObjectsSize - 1;
			}
		}
		End_ResourceHeaderPointer(Allocation, true, false, ThreadIndex);
	}
}
/*
* Added in 1.0.0
* Macro for removing childs from objects.
* @param Allocation refrencing the desired element to remove child of.
* @param Parent refrencing the desired resourceheader to remove parent of Allocation.
* @note Externally Synchronized.
*/
void Remove_ResourceHeader_ElementChild(ElementAllocation Allocation, ResourceHeaderAllocation Parent, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ElementAllocationData(Allocation);
	AllocationData* pParentAllocationData = Get_ResourceHeaderAllocationData(Parent);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Remove_ResourceHeader_ElementChild()", "Allocation Invalid");
		return;
	}
	if (pParentAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Remove_ResourceHeader_ElementChild", "Parent Invalid.");
		return;
	}
#endif
	{
		ResourceHeader* pParent = Get_ResourceHeaderPointer(Parent, true, false, ThreadIndex);
		if (pParent == NULL)
			return (Failure);
		ResourceHeader* pParentOverlay = (pParent->Header.OverlayPointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pParent->Header.OverlayPointer] : NULL;

		if (((pParentOverlay != NULL) ? (pParent->Header.iElements == pParentOverlay->Header.iElements) : false)) {
			//copy new
			pParent->Header.iElements = CopyDataN(pParent->Header.iElements, sizeof(*pParent->Header.iElements) * pParent->Header.iElementsSize);
		}

		for (size_t i = 0; i < pParent->Header.iElementsSize; i++)
		{
			if (Compare_ElementAllocation(pParent->Header.iElements[i], Allocation) == Success)
			{
				RemoveMember_Array((void**)&pParent->Header.iElements, pParent->Header.iElementsSize, i, sizeof(*pParent->Header.iElements), 1);
				pParent->Header.iElementsSize = pParent->Header.iElementsSize - 1;
			}
		}
		End_ResourceHeaderPointer(Parent, true, false, ThreadIndex);
	}
	{
		Element* pElement = Get_ElementPointer(Allocation, true, false, ThreadIndex);
		if (pElement == NULL)
			return (Failure);
		Element* pElementOverlay = (pElement->Header.OverlayPointer != UINT32_MAX) ? &Utils.InternalObjectBuffer.Buffer[pElement->Header.OverlayPointer] : NULL;

		if (((pElementOverlay != NULL) ? (pElement->Header.iResourceHeaders == pElementOverlay->Header.iResourceHeaders) : false)) {
			//copy new
			pElement->Header.iResourceHeaders = CopyDataN(pElement->Header.iResourceHeaders, sizeof(*pElement->Header.iResourceHeaders) * pElement->Header.iResourceHeadersSize);
		}

		for (size_t i = 0; i < pElement->Header.iResourceHeadersSize; i++)
		{
			if (Compare_ResourceHeaderAllocation(pElement->Header.iResourceHeaders[i], Parent) == Success)
			{
				RemoveMember_Array((void**)&pElement->Header.iResourceHeaders, pElement->Header.iResourceHeadersSize, i, sizeof(*pElement->Header.iResourceHeaders), 1);
				pElement->Header.iResourceHeadersSize = pElement->Header.iResourceHeadersSize - 1;
			}
		}
		End_ElementPointer(Allocation, true, false, ThreadIndex);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Scan Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Macro for scanning all childs of an object including childs of their childs.
* @param pChilds is a pointer to an array of allocations to return.
* @param pChildsSize is a pointer to size of the array to return.
* @note Externally Synchronized.
*/
void Scan_ObjectChilds(ObjectAllocation Allocation, ObjectAllocation** pChilds, uint64_t* pChildsSize, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ObjectAllocationData(Allocation);
#ifndef NDEBUG
	if (pAllocationData == NULL)
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
	Object* pObject = Get_ObjectPointer(Allocation, false, false, ThreadIndex);
	if (pObject == NULL)
		return;
	for (size_t i = 0; i < pObject->Header.iChildrenSize; i++)
	{
		uint64_t ChildsSize = *pChildsSize;
		Resize_Array((void**)pChilds, ChildsSize, ChildsSize + 1, sizeof(ObjectAllocation));
		ObjectAllocation* Childs = *pChilds;
		Childs[ChildsSize] = pObject->Header.iChildren[i];
		*pChildsSize += 1;
		Scan_ObjectChilds(Allocation, pChilds, pChildsSize, ThreadIndex);
	}
	End_ObjectPointer(Allocation, false, false, ThreadIndex);
}
/*
* Added in 1.0.0
* Macro for scanning all parents of an object including parents of their parents
* @param pParents is a pointer to an array of allocations to return.
* @param pParentsSize is a pointer to size of the array to return.
* @note Externally Synchronized.
*/
void Scan_ObjectParents(ObjectAllocation Allocation, ObjectAllocation** pParents, uint64_t* pParentsSize, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ObjectAllocationData(Allocation);
#ifndef NDEBUG
	if (pAllocationData == NULL)
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
	Object* pObject = Get_ObjectPointer(Allocation, false, false, ThreadIndex);
	if (pObject == NULL)
		return;
	if (Get_ObjectAllocationData(pObject->Header.iParent) != NULL)
	{
		uint64_t ParentsSize = *pParentsSize;
		Resize_Array((void**)pParents, ParentsSize, ParentsSize + 1, sizeof(ObjectAllocation));
		ObjectAllocation* Parents = *pParents;
		Parents[ParentsSize] = pObject->Header.iParent;
		*pParentsSize += 1;
		Scan_ObjectParents(pObject->Header.iParent, pParents, pParentsSize, ThreadIndex);
	}
	End_ObjectPointer(Allocation, false, false, ThreadIndex);
}
/*
* Added in 1.0.0
* Macro for scanning all resourceheader childs of specified identifier of a object. 
* @param Allocation Allocation to scan from.
* @param Identifier desired Identifier to find.
* @param pResourceHeaders is a pointer to an array of allocations to return.
* @param pResourceHeadersSize is a pointer to size of the array to return.
* @note Externally Synchronized.
*/
void Scan_ObjectResourceHeaders(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, ResourceHeaderAllocation** pResourceHeaders, uint64_t* pResourceHeadersSize, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ObjectAllocationData(Allocation);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectResourceHeaders", "Allocation Invalid.");
		return;
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectResourceHeaders", "Identifier Invalid.");
		return;
	}
	if (pResourceHeaders == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectResourceHeaders()", "pResourceHeaders == NULLPTR");
		return;
	}
	if (pResourceHeadersSize == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectResourceHeaders()", "pResourceHeadersSize == NULLPTR");
		return;
	}
#endif
	Object* pObject = Get_ObjectPointer(Allocation, false, false, ThreadIndex);
	if (pObject == NULL)
		return;
	for (size_t i = 0; i < pObject->Header.iResourceHeadersSize; i++)
	{		
		if (pObject->Header.iResourceHeaders[i].Identifier == Identifier)
		{		
			uint64_t ResourceHeadersSize = *pResourceHeadersSize;
			Resize_Array((void**)pResourceHeaders, ResourceHeadersSize, ResourceHeadersSize + 1, sizeof(ResourceHeaderAllocation));
			ResourceHeaderAllocation* ResourceHeaders = *pResourceHeaders;
			ResourceHeaders[ResourceHeadersSize] = pObject->Header.iResourceHeaders[i];
			*pResourceHeadersSize += 1;
		}
	}
	End_ObjectPointer(Allocation, false, false, ThreadIndex);
}
/*
* Added in 1.0.0
* Macro for scanning all element childs of specified identifier of a resourceheader.
* @param Allocation Allocation to scan from.
* @param Identifier desired Identifier to find.
* @param pElements is a pointer to an array of allocations to return.
* @param pElementsSize is a pointer to size of the array to return.
* @note Externally Synchronized.
*/
void Scan_ResourceHeaderElements(ResourceHeaderAllocation Allocation, ElementIdentifier Identifier, ElementAllocation** pElements, uint64_t* pElementsSize, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ResourceHeaderAllocationData(Allocation);
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Scan_ResourceHeaderElements", "Allocation Invalid.");
		return;
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Scan_ResourceHeaderElements", "Identifier Invalid.");
		return;
	}
	if (pElements == NULL)
	{
		Engine_Ref_ArgsError("Scan_ResourceHeaderElements()", "pElements == NULLPTR");
		return;
	}
	if (pElementsSize == NULL)
	{
		Engine_Ref_ArgsError("Scan_ResourceHeaderElements()", "pElementsSize == NULLPTR");
		return;
	}
#endif
	ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation, false, false, ThreadIndex);
	if (pResourceHeader == NULL)
		return;
	for (size_t i = 0; i < pResourceHeader->Header.iElementsSize; i++)
	{
		if (pResourceHeader->Header.iElements[i].Identifier == Identifier)
		{
			uint64_t ElementsSize = *pElementsSize;
			Resize_Array((void**)pElements, ElementsSize, ElementsSize + 1, sizeof(ElementAllocation));
			ElementAllocation* Elements = *pElements;
			Elements[ElementsSize] = pResourceHeader->Header.iElements[i];
			*pElementsSize += 1;
		}
	}
	End_ResourceHeaderPointer(Allocation, false, false, ThreadIndex);
}
/*
* Added in 1.0.0
* Macro for scanning all resourceheader childs of specified identifier of a object, 
* except unlike Scan_ObjectHeaders() it only returns the first found of specified identifier. 
* @param Allocation Allocation to scan from.
* @param Identifier desired Identifier to find.
* @note Externally Synchronized.
*/
ResourceHeaderAllocation Scan_ObjectResourceHeadersSingle(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ObjectAllocationData(Allocation);
	ResourceHeaderAllocation Return = { sizeof(Return) };
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectResourceHeadersSingle", "Allocation Invalid.");
		return Return;
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Scan_ObjectResourceHeadersSingle", "Identifier Invalid.");
		return Return;
	}
#endif
	Object* pObject = Get_ObjectPointer(Allocation, false, false, ThreadIndex);
	if (pObject == NULL)
		return;
	for (size_t i = 0; i < pObject->Header.iResourceHeadersSize; i++) {
		if (pObject->Header.iResourceHeaders[i].Identifier == Identifier)
			return pObject->Header.iResourceHeaders[i];
	}
	End_ObjectPointer(Allocation, false, false, ThreadIndex);
	return Return;
}
/*
* Added in 1.0.0
* Macro for scanning all element childs of specified identifier of a resourceheader.
* except unlike Scan_ResourceHeaderElements() it only returns the first found of specified identifier.
* @param Allocation Allocation to scan from.
* @param Identifier desired Identifier to find.
* @note Externally Synchronized.
*/
ElementAllocation Scan_ResourceHeaderElementsSingle(ResourceHeaderAllocation Allocation, ElementIdentifier Identifier, uint32_t ThreadIndex) {
	AllocationData* pAllocationData = Get_ResourceHeaderAllocationData(Allocation);
	ElementAllocation Return = { sizeof(Return) };
#ifndef NDEBUG
	if (pAllocationData == NULL)
	{
		Engine_Ref_ArgsError("Scan_ResourceHeaderElementsSingle", "Allocation Invalid.");
		return Return;
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Scan_ResourceHeaderElementsSingle", "Identifier Invalid.");
		return Return;
	}
#endif
	ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(Allocation, false, false, ThreadIndex);
	if (pResourceHeader == NULL)
		return;
	for (size_t i = 0; i < pResourceHeader->Header.iElementsSize; i++) {
		if (pResourceHeader->Header.iElements[i].Identifier == Identifier)
			return pResourceHeader->Header.iElements[i];
	}
	End_ResourceHeaderPointer(Allocation, false, false, ThreadIndex);
	return Return;
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
TEXRESULT Register_ObjectSignature(ObjectSignature* pSignature) {
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("Register_ObjectSignature()", "pSignature == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->Identifier == NULL)
	{
		Engine_Ref_ArgsError("Register_ObjectSignature()", "pSignature->Identifier == NULL, This is invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(&Utils.ObjectSignaturesMutex);
	for (size_t i = 0; i < Utils.ObjectSignaturesSize; i++)
	{
		if (Utils.ObjectSignatures[i]->Identifier == pSignature->Identifier)
		{
			Engine_Ref_ArgsError("Register_ObjectSignature()", "pSignature->Identifier Already Used.");
			Engine_Ref_Unlock_Mutex(&Utils.ObjectSignaturesMutex);
			return (Invalid_Parameter | Failure);
		}
	}
	Resize_Array((void**)&Utils.ObjectSignatures, Utils.ObjectSignaturesSize, Utils.ObjectSignaturesSize + 1, sizeof(*Utils.ObjectSignatures));
	Utils.ObjectSignatures[Utils.ObjectSignaturesSize] = pSignature;
	Utils.ObjectSignaturesSize++;
	Engine_Ref_Unlock_Mutex(&Utils.ObjectSignaturesMutex);
	return (Success);
}
/*
* Added in 1.0.0
* Registers a Signature struct with the API so you can create objects of that type, This creates an internal refrence to the signature in the API, so do not modify!
* @param pSignature is a pointer to the signature to register.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Register_ResourceHeaderSignature(ResourceHeaderSignature* pSignature) {
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("Register_ResourceHeaderSignature()", "pSignature == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->Identifier == NULL)
	{
		Engine_Ref_ArgsError("Register_ResourceHeaderSignature()", "pSignature->Identifier == NULL, This is invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(&Utils.ResourceHeaderSignaturesMutex);
	for (size_t i = 0; i < Utils.ResourceHeaderSignaturesSize; i++)
	{
		if (Utils.ResourceHeaderSignatures[i]->Identifier == pSignature->Identifier)
		{
			Engine_Ref_ArgsError("Register_ResourceHeaderSignature()", "pSignature->Identifier Already Used.");
			Engine_Ref_Unlock_Mutex(&Utils.ResourceHeaderSignaturesMutex);
			return (Invalid_Parameter | Failure);
		}
	}
	Resize_Array((void**)&Utils.ResourceHeaderSignatures, Utils.ResourceHeaderSignaturesSize, Utils.ResourceHeaderSignaturesSize + 1, sizeof(*Utils.ResourceHeaderSignatures));
	Utils.ResourceHeaderSignatures[Utils.ResourceHeaderSignaturesSize] = pSignature;
	Utils.ResourceHeaderSignaturesSize++;
	Engine_Ref_Unlock_Mutex(&Utils.ResourceHeaderSignaturesMutex);
	return (Success);
}
/*
* Added in 1.0.0
* Registers a Signature struct with the API so you can create objects of that type, This creates an internal refrence to the signature in the API, so do not modify!
* @param pSignature is a pointer to the signature to register.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT Register_ElementSignature(ElementSignature* pSignature) {
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("Register_ElementSignature()", "pSignature == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->Identifier == NULL)
	{
		Engine_Ref_ArgsError("Register_ElementSignature()", "pSignature->Identifier == NULL, This is invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(&Utils.ElementSignaturesMutex);
	for (size_t i = 0; i < Utils.ElementSignaturesSize; i++)
	{
		if (Utils.ElementSignatures[i]->Identifier == pSignature->Identifier)
		{
			Engine_Ref_ArgsError("Register_ElementSignature()", "pSignature->Identifier Already Used.");
			Engine_Ref_Unlock_Mutex(&Utils.ElementSignaturesMutex);
			return (Invalid_Parameter | Failure);
		}
	}
	Resize_Array((void**)&Utils.ElementSignatures, Utils.ElementSignaturesSize, Utils.ElementSignaturesSize + 1, sizeof(*Utils.ElementSignatures));
	Utils.ElementSignatures[Utils.ElementSignaturesSize] = pSignature;
	Utils.ElementSignaturesSize++;
	Engine_Ref_Unlock_Mutex(&Utils.ElementSignaturesMutex);
	return (Success);
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
TEXRESULT DeRegister_ObjectSignature(ObjectSignature* pSignature) {
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ObjectSignature()", "pSignature == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->AllocationsCount != NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ObjectSignature()", "pSignature still has allocations, this is invalid.");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->ObjectsCount != NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ObjectSignature()", "pSignature still has objects, this is invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(&Utils.ObjectSignaturesMutex);
	for (size_t i = 0; i < Utils.ObjectSignaturesSize; i++)
	{
		if (Utils.ObjectSignatures[i] == pSignature)
		{
			RemoveMember_Array((void**)&Utils.ObjectSignatures, Utils.ObjectSignaturesSize, i, sizeof(*Utils.ObjectSignatures), 1);
			Utils.ObjectSignaturesSize--;
			Engine_Ref_Unlock_Mutex(&Utils.ObjectSignaturesMutex);
			return (Success);
		}
	}
	Engine_Ref_ArgsError("DeRegister_ObjectSignature()", "pSignature Not Found.");
	Engine_Ref_Unlock_Mutex(&Utils.ObjectSignaturesMutex);
	return (Invalid_Parameter | Failure);
}
/*
* Added in 1.0.0
* Removes the internal refrence to the signature in the API.
* @param pSignature is a pointer to the signature to deregister.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT DeRegister_ResourceHeaderSignature(ResourceHeaderSignature* pSignature) {
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ResourceHeaderSignature()", "pSignature == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->AllocationsCount != NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ResourceHeaderSignature()", "pSignature still has allocations, this is invalid.");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->ResourceHeadersCount != NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ResourceHeaderSignature()", "pSignature still has resourceheaders, this is invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(&Utils.ResourceHeaderSignaturesMutex);
	for (size_t i = 0; i < Utils.ResourceHeaderSignaturesSize; i++)
	{
		if (Utils.ResourceHeaderSignatures[i] == pSignature)
		{
			RemoveMember_Array((void**)&Utils.ResourceHeaderSignatures, Utils.ResourceHeaderSignaturesSize, i, sizeof(*Utils.ResourceHeaderSignatures), 1);
			Utils.ResourceHeaderSignaturesSize--;
			Engine_Ref_Unlock_Mutex(&Utils.ResourceHeaderSignaturesMutex);
			return (Success);
		}
	}
	Engine_Ref_ArgsError("DeRegister_ResourceHeaderSignature()", "pSignature Not Found.");
	Engine_Ref_Unlock_Mutex(&Utils.ResourceHeaderSignaturesMutex);
	return (Invalid_Parameter | Failure);
}
/*
* Added in 1.0.0
* Removes the internal refrence to the signature in the API.
* @param pSignature is a pointer to the signature to deregister.
* @note Thread Safe.
* @note Internally Synchronized.
*/
TEXRESULT DeRegister_ElementSignature(ElementSignature* pSignature) {
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ElementSignature()", "pSignature == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->AllocationsCount != NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ElementSignature()", "pSignature still has allocations, this is invalid.");
		return (Invalid_Parameter | Failure);
	}
	if (pSignature->ElementsCount != NULL)
	{
		Engine_Ref_ArgsError("DeRegister_ElementSignature()", "pSignature still has elements, this is invalid.");
		return (Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(&Utils.ElementSignaturesMutex);
	for (size_t i = 0; i < Utils.ElementSignaturesSize; i++)
	{
		if (Utils.ElementSignatures[i] == pSignature)
		{
			RemoveMember_Array((void**)&Utils.ElementSignatures, Utils.ElementSignaturesSize, i, sizeof(*Utils.ElementSignatures), 1);
			Utils.ElementSignaturesSize--;
			Engine_Ref_Unlock_Mutex(&Utils.ElementSignaturesMutex);
			return (Success);
		}
	}
	Engine_Ref_ArgsError("DeRegister_ElementSignature()", "pSignature Not Found.");
	Engine_Ref_Unlock_Mutex(&Utils.ElementSignaturesMutex);
	return (Invalid_Parameter | Failure);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Binary Export/Import Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* writes all objects into file, regardless of anything.
* @param Path file path to save to, C format.
* @note Thread Safe.
*/
TEXRESULT Write_TEIF(const UTF8* Path, uint32_t ThreadIndex) {
#ifndef NDEBUG
	if (Path == NULL)
	{
		Engine_Ref_ArgsError("Read_TEIF()", "Path == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	FILE* file = fopen((char*)Path, "wb"); //open file
	if (file == NULL)
	{
		Engine_Ref_ArgsError("Write_TEIF()", "Failed to open file.");
		return (Invalid_Parameter | Failure);
	}

	uint64_t FinalObjectSize = 0;
	uint64_t FinalResourceHeaderSize = 0;
	uint64_t FinalElementSize = 0;
	uint64_t FinalBufferSize = 0;
	for (size_t i = 0; i < Utils.InternalObjectBuffer.AllocationDatas.BufferSize; i++)
	{
		AllocationData* pAllocationData = &Utils.InternalObjectBuffer.AllocationDatas.Buffer[i];
		if (pAllocationData->Allocation.Object.Identifier != 0)
		{
			Object* pObject = Get_ObjectPointer(pAllocationData->Allocation.Object, false, false, ThreadIndex);
			if (pObject != NULL)
			{
				ObjectSignature* pSignature = NULL;
				Find_ObjectSignature(pObject->Header.Allocation.Identifier, &pSignature);
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
			}
			//End_ObjectPointer(i, false, ThreadIndex);
		}
	}
	for (size_t i = 0; i < Utils.InternalResourceHeaderBuffer.AllocationDatas.BufferSize; i++)
	{
		AllocationData* pAllocationData = &Utils.InternalResourceHeaderBuffer.AllocationDatas.Buffer[i];
		if (pAllocationData->Allocation.ResourceHeader.Identifier != 0)
		{
			ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(pAllocationData->Allocation.ResourceHeader, false, false, ThreadIndex);
			if (pResourceHeader != NULL)
			{
				ResourceHeaderSignature* pSignature = NULL;
				Find_ResourceHeaderSignature(pResourceHeader->Header.Allocation.Identifier, &pSignature);
				if (pSignature->Packer != NULL)
				{
					Pack_ResourceHeaderTemplate* func = *pSignature->Packer;
					func(pResourceHeader, NULL, &FinalBufferSize, NULL, ThreadIndex);
				}

				FinalBufferSize += sizeof(*pResourceHeader->Header.iElements) * pResourceHeader->Header.iElementsSize;
				FinalBufferSize += sizeof(*pResourceHeader->Header.iObjects) * pResourceHeader->Header.iObjectsSize;

				if (pResourceHeader->Header.Name != NULL)
					FinalBufferSize += strlen((const char*)pResourceHeader->Header.Name) + 1;

				FinalResourceHeaderSize += pResourceHeader->Header.AllocationSize;
			}
			//End_ResourceHeaderPointer(i, false, ThreadIndex);
		}
	}
	for (size_t i = 0; i < Utils.InternalElementBuffer.AllocationDatas.BufferSize; i++)
	{
		AllocationData* pAllocationData = &Utils.InternalElementBuffer.AllocationDatas.Buffer[i];
		if (pAllocationData->Allocation.Element.Identifier != 0)
		{
			Element* pElement = Get_ElementPointer(pAllocationData->Allocation.Element, false, false, ThreadIndex);
			if (pElement != NULL)
			{
				ElementSignature* pSignature = NULL;
				Find_ElementSignature(pElement->Header.Allocation.Identifier, &pSignature);
				if (pSignature->Packer != NULL)
				{
					Pack_ElementTemplate* func = *pSignature->Packer;
					func(pElement, NULL, &FinalBufferSize, NULL, ThreadIndex);
				}

				FinalBufferSize += sizeof(*pElement->Header.iResourceHeaders) * pElement->Header.iResourceHeadersSize;

				if (pElement->Header.Name != NULL)
					FinalBufferSize += strlen((const char*)pElement->Header.Name) + 1;

				FinalElementSize += pElement->Header.AllocationSize;
			}
			//End_ElementPointer(i, false, ThreadIndex);
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
			return (Out_Of_Memory_Result | Failure);
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
			return (Out_Of_Memory_Result | Failure);
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
			return (Out_Of_Memory_Result | Failure);
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
			return (Out_Of_Memory_Result | Failure);
		}
	}

	for (size_t i = 0; i < Utils.InternalObjectBuffer.AllocationDatas.BufferSize; i++)
	{
		AllocationData* pAllocationData = &Utils.InternalObjectBuffer.AllocationDatas.Buffer[i];
		if (pAllocationData->Allocation.Object.Identifier != 0)
		{
			Object* pObject = Get_ObjectPointer(pAllocationData->Allocation.Object, false, true, ThreadIndex);
			if (pObject != NULL)
			{
				memcpy(&ObjectsData[FinalObjectPointer], pObject, pObject->Header.AllocationSize * sizeof(Object));
				Object* pCopiedObject = &ObjectsData[FinalObjectPointer];
				ObjectSignature* pSignature = NULL;
				Find_ObjectSignature(pObject->Header.Allocation.Identifier, &pSignature);
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
				End_ObjectPointer(pAllocationData->Allocation.Object, false, true, ThreadIndex);
				End_ObjectPointer(pAllocationData->Allocation.Object, false, false, ThreadIndex);
			}
		}
	}
	for (size_t i = 0; i < Utils.InternalResourceHeaderBuffer.AllocationDatas.BufferSize; i++)
	{
		AllocationData* pAllocationData = &Utils.InternalResourceHeaderBuffer.AllocationDatas.Buffer[i];
		if (pAllocationData->Allocation.ResourceHeader.Identifier != 0)
		{
			ResourceHeader* pResourceHeader = Get_ResourceHeaderPointer(pAllocationData->Allocation.ResourceHeader, false, true, ThreadIndex);
			if (pResourceHeader != NULL)
			{
				memcpy(&ResourceHeadersData[FinalResourceHeaderPointer], pResourceHeader, pResourceHeader->Header.AllocationSize * sizeof(ResourceHeader));
				ResourceHeader* pCopiedResourceHeader = &ResourceHeadersData[FinalResourceHeaderPointer];
				ResourceHeaderSignature* pSignature = NULL;
				Find_ResourceHeaderSignature(pResourceHeader->Header.Allocation.Identifier, &pSignature);
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
				if (pResourceHeader->Header.iObjectsSize != NULL)
				{
					memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pResourceHeader->Header.iObjects, sizeof(*pResourceHeader->Header.iObjects) * pResourceHeader->Header.iObjectsSize);
					pCopiedResourceHeader->Header.iObjects = (ObjectAllocation*)FinalBufferPointer;
					FinalBufferPointer += sizeof(*pResourceHeader->Header.iObjects) * pResourceHeader->Header.iObjectsSize;
				}
				if (pResourceHeader->Header.Name != NULL)
				{
					memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pResourceHeader->Header.Name, strlen((char*)pResourceHeader->Header.Name) + 1);
					pCopiedResourceHeader->Header.Name = (UTF8*)FinalBufferPointer;
					FinalBufferPointer += strlen((char*)pResourceHeader->Header.Name) + 1;
				}
				FinalResourceHeaderPointer += pResourceHeader->Header.AllocationSize;
				End_ResourceHeaderPointer(pAllocationData->Allocation.ResourceHeader, false, true, ThreadIndex);
				End_ResourceHeaderPointer(pAllocationData->Allocation.ResourceHeader, false, false, ThreadIndex);
			}
		}
	}
	for (size_t i = 0; i < Utils.InternalElementBuffer.AllocationDatas.BufferSize; i++)
	{
		AllocationData* pAllocationData = &Utils.InternalElementBuffer.AllocationDatas.Buffer[i];
		if (pAllocationData->Allocation.Element.Identifier != 0)
		{
			Element* pElement = Get_ElementPointer(pAllocationData->Allocation.Element, false, true, ThreadIndex);
			if (pElement != NULL)
			{
				memcpy(&ElementsData[FinalElementPointer], pElement, pElement->Header.AllocationSize * sizeof(Element));
				Element* pCopiedElement = &ElementsData[FinalElementPointer];
				ElementSignature* pSignature = NULL;
				Find_ElementSignature(pElement->Header.Allocation.Identifier, &pSignature);
				if (pSignature->Packer != NULL)
				{
					Pack_ElementTemplate* func = *pSignature->Packer;
					func(pElement, pCopiedElement, &FinalBufferPointer, MiscDataBuffer, ThreadIndex);
				}
				if (pElement->Header.iResourceHeadersSize != NULL)
				{
					memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pElement->Header.iResourceHeaders, sizeof(*pElement->Header.iResourceHeaders) * pElement->Header.iResourceHeadersSize);
					pCopiedElement->Header.iResourceHeaders = (ResourceHeaderAllocation*)FinalBufferPointer;
					FinalBufferPointer += sizeof(*pElement->Header.iResourceHeaders) * pElement->Header.iResourceHeadersSize;
				}
				if (pElement->Header.Name != NULL)
				{
					memcpy((void*)((uint64_t)MiscDataBuffer + FinalBufferPointer), pElement->Header.Name, strlen((char*)pElement->Header.Name) + 1);
					pCopiedElement->Header.Name = (UTF8*)FinalBufferPointer;
					FinalBufferPointer += strlen((char*)pElement->Header.Name) + 1;
				}
				FinalElementPointer += pElement->Header.AllocationSize;
				End_ElementPointer(pAllocationData->Allocation.Element, false, true, ThreadIndex);
				End_ElementPointer(pAllocationData->Allocation.Element, false, false, ThreadIndex);
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
* reads objects from file and imparts them
* cant do partial load (Yet), whole system will be overwrriten. 
* @param Path file path to load from, C format.
* @note Thread Safe.
*/
TEXRESULT Read_TEIF(const UTF8* Path, uint32_t ThreadIndex) {
	TEXRESULT tres = Success;
#ifndef NDEBUG
	if (Path == NULL)
	{
		Engine_Ref_ArgsError("Read_TEIF()", "Path == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	FileData data = { 0, 0 };
	Open_Data(&data, Path);
	if (data.pData == NULL)
	{
		Engine_Ref_ArgsError("Read_TEIF()", "Failed to open file.");
		return (Invalid_Parameter | Failure);
	}
	TEIF_HEADER* pHeader = (TEIF_HEADER*)data.pData;
	if (strncmp(pHeader->filecode, "TEIF", 4) != 0)
	{
		Engine_Ref_ArgsError("Read_TEIF()", "Filecode Not Equal To TEIF, Invalid File Format!");
		return (Invalid_Format | Failure);
	}

	Object* pObjects = (Object*)((void*)((uint64_t)data.pData + (uint64_t)pHeader->ObjectsOffset));
	uint64_t ObjectsSize = pHeader->ObjectsSize;

	ResourceHeader* pResourceHeaders = (ResourceHeader*)((void*)((uint64_t)data.pData + (uint64_t)pHeader->ResourceHeadersOffset));
	uint64_t ResourceHeadersSize = pHeader->ResourceHeadersSize;

	Element* pElements = (Element*)((void*)((uint64_t)data.pData + (uint64_t)pHeader->ElementsOffset));
	uint64_t ElementsSize = pHeader->ElementsSize;

	uint8_t* pDataBuffer = (uint8_t*)((void*)((uint64_t)data.pData + (uint64_t)pHeader->DataBufferOffset));

	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)
	{
		Engine_Ref_Lock_Mutex(&Utils.InternalObjectBuffer.AllocationDatas.ArenaAllocaters[i].Mutex);
		Engine_Ref_Lock_Mutex(&Utils.InternalResourceHeaderBuffer.AllocationDatas.ArenaAllocaters[i].Mutex);
		Engine_Ref_Lock_Mutex(&Utils.InternalElementBuffer.AllocationDatas.ArenaAllocaters[i].Mutex);
	}

	//place items in the buffers and unpack them
	for (size_t i = 0; i < ObjectsSize;)
	{
		Object* pObject = &pObjects[i];

		ObjectSignature* pSignature = NULL;
		Find_ObjectSignature(pObject->Header.Allocation.Identifier, &pSignature);

		AllocationData* pAllocationData = &Utils.InternalObjectBuffer.AllocationDatas.Buffer[pObject->Header.Allocation.Pointer];
		//check if that pointer is already used. 
		if (pAllocationData->Allocation.Object.Identifier != 0) {
			//figure out what to do if pointer is used.;
			Engine_Ref_FunctionError("Read_TEIF()", "Object Pointer Conflict, Can't Read TEIF file if its gonna overwrite existing allocations. Pointer == ", pObject->Header.Allocation.Pointer);
		}
		memset(pAllocationData, 0, sizeof(*pAllocationData));
		//set all internal data to invalid number
		for (size_t i = 0; i < maxthreads; i++)
			c89atomic_store_32(&pAllocationData->Threads[i].Pointer, UINT32_MAX);
		c89atomic_store_32(&pAllocationData->LatestPointer, UINT32_MAX);
		//setting values to make allocation valid.
		c89atomic_fetch_add_32(&Utils.InternalObjectBuffer.AllocationsCount, 1);
		c89atomic_store_32(&pAllocationData->Allocation.Object.Identifier, pObject->Header.Allocation.Identifier);
		c89atomic_store_32(&pAllocationData->Allocation.Object.Pointer, pObject->Header.Allocation.Pointer);

		uint32_t Pointer = 0;
		if ((tres = Allocate_Object(pSignature, pObject->Header.AllocationSize, pObject->Header.Allocation.Identifier, pObject->Header.Allocation, &Pointer, ThreadIndex)) != Success)
			return tres;

		Object* pCopiedObject = &Utils.InternalObjectBuffer.Buffer[Pointer];
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
		c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, Pointer);
		c89atomic_store_32(&pAllocationData->LatestPointer, Pointer);
		i += pObject->Header.AllocationSize;
	}
	for (size_t i = 0; i < ResourceHeadersSize;)
	{
		ResourceHeader* pResourceHeader = &pResourceHeaders[i];

		ResourceHeaderSignature* pSignature = NULL;
		Find_ResourceHeaderSignature(pResourceHeader->Header.Allocation.Identifier, &pSignature);

		AllocationData* pAllocationData = &Utils.InternalResourceHeaderBuffer.AllocationDatas.Buffer[pResourceHeader->Header.Allocation.Pointer];
		//check if that pointer is already used. 
		if (pAllocationData->Allocation.ResourceHeader.Identifier != 0) {
			//figure out what to do if pointer is used.;
			Engine_Ref_FunctionError("Read_TEIF()", "ResourceHeader Pointer Conflict, Can't Read TEIF file if its gonna overwrite existing allocations. Pointer == ", pResourceHeader->Header.Allocation.Pointer);
		}
		memset(pAllocationData, 0, sizeof(*pAllocationData));
		//set all internal data to invalid number
		for (size_t i = 0; i < maxthreads; i++)
			c89atomic_store_32(&pAllocationData->Threads[i].Pointer, UINT32_MAX);
		c89atomic_store_32(&pAllocationData->LatestPointer, UINT32_MAX);
		//setting values to make allocation valid.
		c89atomic_fetch_add_32(&Utils.InternalResourceHeaderBuffer.AllocationsCount, 1);
		c89atomic_store_32(&pAllocationData->Allocation.ResourceHeader.Identifier, pResourceHeader->Header.Allocation.Identifier);
		c89atomic_store_32(&pAllocationData->Allocation.ResourceHeader.Pointer, pResourceHeader->Header.Allocation.Pointer);

		uint32_t Pointer = 0;
		if ((tres = Allocate_ResourceHeader(pSignature, pResourceHeader->Header.AllocationSize, pResourceHeader->Header.Allocation.Identifier, pResourceHeader->Header.Allocation, &Pointer, ThreadIndex)) != Success)
			return tres;

		ResourceHeader* pCopiedResourceHeader = &Utils.InternalResourceHeaderBuffer.Buffer[Pointer];
		memcpy(pCopiedResourceHeader, pResourceHeader, pResourceHeader->Header.AllocationSize * sizeof(*pResourceHeader));
		if (pResourceHeader->Header.iElementsSize != NULL)
		{
			pCopiedResourceHeader->Header.iElements = (ElementAllocation*)malloc(sizeof(*pResourceHeader->Header.iElements) * pResourceHeader->Header.iElementsSize);
			memcpy(pCopiedResourceHeader->Header.iElements, (void*)((uint64_t)pDataBuffer + (uint64_t)pResourceHeader->Header.iElements), sizeof(*pResourceHeader->Header.iElements) * pResourceHeader->Header.iElementsSize);
		}
		if (pResourceHeader->Header.iObjectsSize != NULL)
		{
			pCopiedResourceHeader->Header.iObjects = (ObjectAllocation*)malloc(sizeof(*pResourceHeader->Header.iObjects) * pResourceHeader->Header.iObjectsSize);
			memcpy(pCopiedResourceHeader->Header.iObjects, (void*)((uint64_t)pDataBuffer + (uint64_t)pResourceHeader->Header.iObjects), sizeof(*pResourceHeader->Header.iObjects) * pResourceHeader->Header.iObjectsSize);
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
		c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, Pointer);
		c89atomic_store_32(&pAllocationData->LatestPointer, Pointer);
		i += pResourceHeader->Header.AllocationSize;
	}
	for (size_t i = 0; i < ElementsSize;)
	{
		Element* pElement = &pElements[i];	

		ElementSignature* pSignature = NULL;
		Find_ElementSignature(pElement->Header.Allocation.Identifier, &pSignature);
		
		AllocationData* pAllocationData = &Utils.InternalElementBuffer.AllocationDatas.Buffer[pElement->Header.Allocation.Pointer];
		//check if that pointer is already used. 
		if (pAllocationData->Allocation.Element.Identifier != 0) {
			//figure out what to do if pointer is used.;
			Engine_Ref_FunctionError("Read_TEIF()", "Element Pointer Conflict, Can't Read TEIF file if its gonna overwrite existing allocations. Pointer == ", pElement->Header.Allocation.Pointer);
		}
		memset(pAllocationData, 0, sizeof(*pAllocationData));
		//set all internal data to invalid number
		for (size_t i = 0; i < maxthreads; i++)
			c89atomic_store_32(&pAllocationData->Threads[i].Pointer, UINT32_MAX);
		c89atomic_store_32(&pAllocationData->LatestPointer, UINT32_MAX);
		//setting values to make allocation valid.
		c89atomic_fetch_add_32(&Utils.InternalElementBuffer.AllocationsCount, 1);
		c89atomic_store_32(&pAllocationData->Allocation.Element.Identifier, pElement->Header.Allocation.Identifier);
		c89atomic_store_32(&pAllocationData->Allocation.Element.Pointer, pElement->Header.Allocation.Pointer);

		uint32_t Pointer = 0;
		if ((tres = Allocate_Element(pSignature, pElement->Header.AllocationSize, pElement->Header.Allocation.Identifier, pElement->Header.Allocation, &Pointer, ThreadIndex)) != Success)
			return tres;

		Element* pCopiedElement = &Utils.InternalElementBuffer.Buffer[Pointer];
		memcpy(pCopiedElement, pElement, pElement->Header.AllocationSize * sizeof(*pElement));
		if (pElement->Header.iResourceHeadersSize != NULL)
		{
			pCopiedElement->Header.iResourceHeaders = (ResourceHeaderAllocation*)malloc(sizeof(*pElement->Header.iResourceHeaders) * pElement->Header.iResourceHeadersSize);
			memcpy(pCopiedElement->Header.iResourceHeaders, (void*)((uint64_t)pDataBuffer + (uint64_t)pElement->Header.iResourceHeaders), sizeof(*pElement->Header.iResourceHeaders) * pElement->Header.iResourceHeadersSize);
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
		c89atomic_store_32(&pAllocationData->Threads[ThreadIndex].Pointer, Pointer);
		c89atomic_store_32(&pAllocationData->LatestPointer, Pointer);
		i += pElement->Header.AllocationSize;
	} 
	for (size_t i = 0; i < EngineRes.pUtils->CPU.MaxThreads; i++)
	{
		Engine_Ref_Unlock_Mutex(&Utils.InternalObjectBuffer.AllocationDatas.ArenaAllocaters[i].Mutex);
		Engine_Ref_Unlock_Mutex(&Utils.InternalResourceHeaderBuffer.AllocationDatas.ArenaAllocaters[i].Mutex);
		Engine_Ref_Unlock_Mutex(&Utils.InternalElementBuffer.AllocationDatas.ArenaAllocaters[i].Mutex);
	}

	free(data.pData);
	return Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ResourceHeaders
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


TEXRESULT Destroy_SceneHeader(RHeaderScene* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	if (Full == true)
	{

	}
	return (Success);
}


TEXRESULT Pack_SceneHeader(const RHeaderScene* pResourceHeader, RHeaderScene* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{

	}
	else
	{

	}
	return (Success);
}

TEXRESULT UnPack_SceneHeader(const RHeaderScene* pResourceHeader, RHeaderScene* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	return (Success);
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
			return (Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->Active = pCreateInfo->InitialActive;
	}
	*pAllocationSize = sizeof(RHeaderScene);
	return (Success);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main Functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Initialise_Objects()
{
	memset(&Utils, 0, sizeof(Utils));

	//config 
	Utils.Config.InitialItemsMax = 10024;
	Utils.Config.ActiveMemoryResizing = true;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Signatures
	///////////////////////////////////////////////////////////////////////////////////////////////

	Engine_Ref_Create_Mutex(&Utils.ObjectSignaturesMutex, MutexType_Plain);
	Engine_Ref_Create_Mutex(&Utils.ResourceHeaderSignaturesMutex, MutexType_Plain);
	Engine_Ref_Create_Mutex(&Utils.ElementSignaturesMutex, MutexType_Plain);

	Create_ElementBuffer(&Utils.InternalElementBuffer, Utils.Config.InitialItemsMax);
	Create_ResourceHeaderBuffer(&Utils.InternalResourceHeaderBuffer, Utils.Config.InitialItemsMax);
	Create_ObjectBuffer(&Utils.InternalObjectBuffer, Utils.Config.InitialItemsMax);


	Utils.GenericElementSig.Identifier = (uint32_t)Element_Generic;
	Utils.GenericResourceHeaderSig.Identifier = (uint32_t)ResourceHeader_Generic;
	Utils.GenericObjectSig.Identifier = (uint32_t)Object_Generic;

	Utils.GenericElementSig.ByteLength = sizeof(Element);
	Utils.GenericResourceHeaderSig.ByteLength = sizeof(ResourceHeader);
	Utils.GenericObjectSig.ByteLength = sizeof(Object);

	Register_ElementSignature(&Utils.GenericElementSig);
	Register_ResourceHeaderSignature(&Utils.GenericResourceHeaderSig);
	Register_ObjectSignature(&Utils.GenericObjectSig);

	Utils.RHeaderSceneSig.ByteLength = sizeof(RHeaderScene);
	Utils.RHeaderSceneSig.Identifier = (uint32_t)ResourceHeader_Scene;
	Utils.RHeaderSceneSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_SceneHeader;
	Utils.RHeaderSceneSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_SceneHeader;
	//Utils.RHeaderSceneSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_SceneHeader;
	Utils.RHeaderSceneSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_SceneHeader;
	Utils.RHeaderSceneSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_SceneHeader;
	Register_ResourceHeaderSignature(&Utils.RHeaderSceneSig);

	return Success;
}

TEXRESULT Destroy_Objects()
{
	DeRegister_ElementSignature(&Utils.GenericElementSig);
	DeRegister_ResourceHeaderSignature(&Utils.GenericResourceHeaderSig);
	DeRegister_ObjectSignature(&Utils.GenericObjectSig);

	DeRegister_ResourceHeaderSignature(&Utils.RHeaderSceneSig);

	Destroy_ElementBuffer(&Utils.InternalElementBuffer, 0);
	Destroy_ResourceHeaderBuffer(&Utils.InternalResourceHeaderBuffer, 0);
	Destroy_ObjectBuffer(&Utils.InternalObjectBuffer, 0);

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

	Engine_Ref_Destroy_Mutex(&Utils.ObjectSignaturesMutex);
	Engine_Ref_Destroy_Mutex(&Utils.ResourceHeaderSignaturesMutex);
	Engine_Ref_Destroy_Mutex(&Utils.ElementSignaturesMutex);

	memset(&Utils, 0, sizeof(Utils));
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
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData("Object::InitialItemsMax"), &Utils.Config.InitialItemsMax, 1, sizeof(Utils.Config.InitialItemsMax));

	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"Object::ActiveMemoryResizing"), &Utils.Config.ActiveMemoryResizing, 1, sizeof(Utils.Config.ActiveMemoryResizing));


	//Resources
	ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData("Object::Utils"), &ObjectsRes.pUtils, &Utils);

	//Functions
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Initialise_Objects"), &ObjectsRes.pInitialise_Objects, &Initialise_Objects, Construct, 0.001f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_Objects"), &ObjectsRes.pDestroy_Objects, &Destroy_Objects, Destruct, 10000.0f, 0, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Compare_ObjectAllocation"), &ObjectsRes.pCompare_ObjectAllocation, &Compare_ObjectAllocation, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Compare_ResourceHeaderAllocation"), &ObjectsRes.pCompare_ResourceHeaderAllocation, &Compare_ResourceHeaderAllocation, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Compare_ElementAllocation"), &ObjectsRes.pCompare_ElementAllocation, &Compare_ElementAllocation, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Get_ObjectAllocationData"), &ObjectsRes.pGet_ObjectAllocationData, &Get_ObjectAllocationData, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Get_ResourceHeaderAllocationData"), &ObjectsRes.pGet_ResourceHeaderAllocationData, &Get_ResourceHeaderAllocationData, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Get_ElementAllocationData"), &ObjectsRes.pGet_ElementAllocationData, &Get_ElementAllocationData, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Get_ObjectPointer"), &ObjectsRes.pGet_ObjectPointer, &Get_ObjectPointer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Get_ResourceHeaderPointer"), &ObjectsRes.pGet_ResourceHeaderPointer, &Get_ResourceHeaderPointer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Get_ElementPointer"), &ObjectsRes.pGet_ElementPointer, &Get_ElementPointer, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::End_ObjectPointer"), &ObjectsRes.pEnd_ObjectPointer, &End_ObjectPointer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::End_ResourceHeaderPointer"), &ObjectsRes.pEnd_ResourceHeaderPointer, &End_ResourceHeaderPointer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::End_ElementPointer"), &ObjectsRes.pEnd_ElementPointer, &End_ElementPointer, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Find_ObjectSignature"), &ObjectsRes.pFind_ObjectSignature, &Find_ObjectSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Find_ResourceHeaderSignature"), &ObjectsRes.pFind_ResourceHeaderSignature, &Find_ResourceHeaderSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Find_ElementSignature"), &ObjectsRes.pFind_ElementSignature, &Find_ElementSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_ObjectBuffer"), &ObjectsRes.pCreate_ObjectBuffer, &Create_ObjectBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_ResourceHeaderBuffer"), &ObjectsRes.pCreate_ResourceHeaderBuffer, &Create_ResourceHeaderBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_ElementBuffer"), &ObjectsRes.pCreate_ElementBuffer, &Create_ElementBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Resize_ObjectBuffer"), &ObjectsRes.pResize_ObjectBuffer, &Resize_ObjectBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Resize_ResourceHeaderBuffer"), &ObjectsRes.pResize_ResourceHeaderBuffer, &Resize_ResourceHeaderBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Resize_ElementBuffer"), &ObjectsRes.pResize_ElementBuffer, &Resize_ElementBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_ObjectBuffer"), &ObjectsRes.pDestroy_ObjectBuffer, &Destroy_ObjectBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_ResourceHeaderBuffer"), &ObjectsRes.pDestroy_ResourceHeaderBuffer, &Destroy_ResourceHeaderBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_ElementBuffer"), &ObjectsRes.pDestroy_ElementBuffer, &Destroy_ElementBuffer, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_Object"), &ObjectsRes.pCreate_Object, &Create_Object, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_ResourceHeader"), &ObjectsRes.pCreate_ResourceHeader, &Create_ResourceHeader, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Create_Element"), &ObjectsRes.pCreate_Element, &Create_Element, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_Object"), &ObjectsRes.pDestroy_Object, &Destroy_Object, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_ResourceHeader"), &ObjectsRes.pDestroy_ResourceHeader, &Destroy_ResourceHeader, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Destroy_Element"), &ObjectsRes.pDestroy_Element, &Destroy_Element, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::ReCreate_Object"), &ObjectsRes.pReCreate_Object, &ReCreate_Object, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::ReCreate_ResourceHeader"), &ObjectsRes.pReCreate_ResourceHeader, &ReCreate_ResourceHeader, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::ReCreate_Element"), &ObjectsRes.pReCreate_Element, &ReCreate_Element, (CallFlagBits)NULL, 0.0f, NULL, NULL);

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
	

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Scan_ObjectResourceHeaders"), &ObjectsRes.pScan_ObjectResourceHeaders, &Scan_ObjectResourceHeaders, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Scan_ResourceHeaderElements"), &ObjectsRes.pScan_ResourceHeaderElements, &Scan_ResourceHeaderElements, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Scan_ObjectResourceHeadersSingle"), &ObjectsRes.pScan_ObjectResourceHeadersSingle, &Scan_ObjectResourceHeadersSingle, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Scan_ResourceHeaderElementsSingle"), &ObjectsRes.pScan_ResourceHeaderElementsSingle, &Scan_ResourceHeaderElementsSingle, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Write_TEIF"), &ObjectsRes.pWrite_TEIF, &Write_TEIF, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Object::Read_TEIF"), &ObjectsRes.pRead_TEIF, &Read_TEIF, (CallFlagBits)NULL, 0.0f, NULL, NULL);
}
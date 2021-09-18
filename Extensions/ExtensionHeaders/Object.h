/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Standard Triangle Engine X Objects.

SPECIFICATION:

* Each API can make it's own version of the 3 basic objects, Objects, ResourceHeaders, Elements.

* C style Pointers to the three buffered objects, Objects, ResourceHeaders, Elements,
  are always unreliable and you should never store them, only use them for refrences within a function,
  anything outside always store the ALLOCATION!, not the C-pointer.

* enum identifier spacing, 0 is invalid, 1-999 reserved only for Objects API, 1000s reserved for graphics 2000s for audio
  3000s for gui, 4000s for network, 5000s for GraphicsEffects
  enums over 1000000 free to use for extensions

* CreateInfos will always contain temporary objects, delete them after creating the object, unless explictly stated so.

* the system works as follows, An allocation is an index to a main "Allocations" buffer that stores refrences to all instances of a given object,
  each of these refrences is stored in their respective buffer, objects, resourceheaders, elements.

* Multithreading is handled by the objects system, where it uses a instnace-based system to preserve data coherantcy
  between threads, further details are in their respective functions.

* resourceheaders & elements can have multiple parent objects.
  Objects follow a strict hierachy of only 1 parent.

* Destruction of objects will not destroy objects lower in hierachy.

* All objeccts can be instanced by refrencing in multiple places which is valid.

* Free floating resourceheaders & elements are perfectly legal.

* set "TEX_EXPOSE_OBJECTS" define to expose more of the API.

THEORY:

* you have a base gameobject and can drag and drop "resourceheaders"
  that each influence eachother in a defined behaviour.

* ResourceHeaders and Elements can be free floating (no parent) but they often wont do anything..

* Utils can be imported. Object::Utils

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
#define TEX_OBJECTS_API
/*
* Added in 1.0.0
* Objects API Generic.
*/
typedef enum ObjectType {
	Object_Generic = 1
}ObjectType;
/*
* Added in 1.0.0
* Objects API Generic.
*/
typedef enum ResourceHeaderType {
	ResourceHeader_Generic = 1,
	ResourceHeader_Scene = 2,
}ResourceHeaderType;
/*
* Added in 1.0.0
* Objects API Generic.
*/
typedef enum ElementType {
	Element_Generic = 1
}ElementType;
/*
* Added in 1.0.0
* Identifier enum.
* Identifier 0 is invalid.
*/
typedef uint32_t ObjectIdentifier;
typedef uint32_t ResourceHeaderIdentifier;
typedef uint32_t ElementIdentifier;
/*
* Added in 1.0.0
* Allocation Enum.
* The Maxinium Allocatable size is 137.4 GB
  From (2 ^ 32) (size of uint32_t) * 32 (mininium size of allocation).
* to check if allocation is valid, identifier must not be 0.
*/
typedef struct { uint32_t Pointer; ObjectIdentifier Identifier; } ObjectAllocation;
typedef struct { uint32_t Pointer; ResourceHeaderIdentifier Identifier; } ResourceHeaderAllocation;
typedef struct { uint32_t Pointer; ElementIdentifier Identifier; } ElementAllocation;
/*
* Added in 1.0.0
* AllocationData Thread Dependant Part.
*/
typedef struct AllocationThreadData {
	c89atomic_uint32 Pointer;
	c89atomic_uint32 Count;
}AllocationThreadData;
#define maxthreads 12
/*
* Added in 1.0.0
* Universal for all three types.
* AllocationData is the object that is meant to be the "frontend" of items, storing refrences to its actual data in Threads[].
* AllocationData stored in its respective buffer.
* to check is AllocationData is valid, Identifier must not be 0.
*/
typedef struct AllocationData {
	union {
		ObjectAllocation Object;
		ResourceHeaderAllocation ResourceHeader;
		ElementAllocation Element;
	}Allocation;
	
	AllocationThreadData Threads[maxthreads];
	c89atomic_uint32 LatestPointer;
	c89atomic_bool ScheduleDestruct;
	c89atomic_bool WriteLock;
}AllocationData;

/*
* Added in 1.0.0
* The Universal Hierarchal object, used for creating hierarchies between resources, basicially only use.

* To check if valid in a buffer ONLY use AllocationSize, as it is the last one being atomically written.
* When a gameobject is destroyed, it is not responsible for destroying it's resourceheaders or childs, but it removes 
  all refrences of it itself from it's children and parents and resourceheaders.
* Objects cant be physically instanced.
*/
typedef struct ObjectCreateInfo {
	const UTF8* Name;
	ObjectIdentifier Identifier;
}ObjectCreateInfo;
typedef struct ObjectTEMPLATE {
	ObjectAllocation Allocation;
	uint32_t AllocationSize;

	c89atomic_uint8 UseCount; //amount of uses by threads.
	c89atomic_uint32 OverlayPointer; //pointer to item to overlay with when destructing.

	ObjectAllocation iParent;

	uint32_t iResourceHeadersSize;
	ResourceHeaderAllocation* iResourceHeaders;

	uint32_t iChildrenSize;
	ObjectAllocation* iChildren;

	const UTF8* Name;
}ObjectTEMPLATE;
typedef struct Object{
	ObjectTEMPLATE Header;
}Object;
/*
* Added in 1.0.0
* ResourceHeaders are just what they sound like, headers for resources that can be
  attached to gameobjects and can have elements as childs.

* To check if valid in a buffer ONLY use AllocationSize, as it is the last one being atomically written.
* When a resourceheader is destroyed it is not responsible for destroying its elements, but it removes 
  all refrences of itself from its elemants and parents.
* ResourceHeaders can be instanced by refrencing them in multiple objects.
*/
typedef struct ResourceHeaderCreateInfo {
	const UTF8* Name;
	ResourceHeaderIdentifier Identifier;
}ResourceHeaderCreateInfo;
typedef struct ResourceHeaderTEMPLATE {
	ResourceHeaderAllocation Allocation;
	uint32_t AllocationSize;

	c89atomic_uint8 UseCount; //amount of uses by threads.
	c89atomic_uint32 OverlayPointer; //pointer to item to overlay with when destructing.

	uint32_t iObjectsSize;
	ObjectAllocation* iObjects;

	uint32_t iElementsSize;
	ElementAllocation* iElements;

	const UTF8* Name;
}ResourceHeaderTEMPLATE;
typedef struct ResourceHeader{
	ResourceHeaderTEMPLATE Header;
}ResourceHeader;
/*
* Added in 1.0.0
* Elements are the lowest level of object, they do frame by frame functions,
  like being 3d objects, or being audio objects.
* To check if valid in a buffer ONLY use AllocationSize, as it is the last one being atomically written.
* When a element is destroyed it removes all refrences of itself from its parents.
* Elements can be instanced by refrencing them in multiple resourceheaders.
*/
typedef struct ElementCreateInfo {
	const UTF8* Name;
	ElementIdentifier Identifier;
}ElementCreateInfo;
typedef struct ElementTEMPLATE {
	ElementAllocation Allocation;
	uint32_t AllocationSize;

	c89atomic_uint8 UseCount; //amount of uses by threads.
	c89atomic_uint32 OverlayPointer; //pointer to item to overlay with when destructing.

	uint32_t iResourceHeadersSize;
	ResourceHeaderAllocation* iResourceHeaders;

	const UTF8* Name;
}ElementTEMPLATE;
typedef struct Element{
	ElementTEMPLATE Header;
}Element;
/*
* Added in 1.0.0
* when an object has a scene header it becomes scene root, as in all objects that are descendants of that
  object will be part of the scene.
* multiple scenes per object doesnt really work. (incluing having a scene on a object that has a parent that has a scene).
* Scenes can be toggled active or inactive.
* Scenes are used to toggle objects on and off, all APIS in triangle engine use scenes to control what is used.
*/
typedef struct RHeaderSceneCreateInfo {
	bool InitialActive;
}RHeaderSceneCreateInfo;
typedef struct RHeaderScene {
	ResourceHeaderTEMPLATE Header;
	bool Active;
}RHeaderScene;

/*
* Added in 1.0.0
*/
typedef struct ArenaAllocater {
	uint64_t StartPtr;
	uint64_t EndPtr; //endptr = startptr of next allocater.
	Mutex Mutex;
}ArenaAllocater;
/*
* Added in 1.0.0
*/
typedef struct AllocationDatasBuffer {
	ArenaAllocater* ArenaAllocaters; //size of CPU.MaxThreads
	uint32_t* Indexes; //size of CPU.MaxThreads
	uint64_t BufferSize; //size in allocation units
	AllocationData* Buffer;
	c89atomic_uint32 AllocationsCount; //amount of allocations that have been allocated.
}AllocationDatasBuffer;
/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
*/
typedef struct ObjectBuffer {	
	ArenaAllocater* ArenaAllocaters; //size of CPU.MaxThreads
	uint32_t* Indexes; //size of CPU.MaxThreads
	uint64_t BufferSize; //size in allocation units
	Object* Buffer;
	c89atomic_uint32 AllocationsCount; //amount of allocations that have been allocated.

	AllocationDatasBuffer AllocationDatas;
}ObjectBuffer;
/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
*/
typedef struct ResourceHeaderBuffer {
	ArenaAllocater* ArenaAllocaters; //size of CPU.MaxThreads
	uint32_t* Indexes; //size of CPU.MaxThreads
	uint64_t BufferSize; //size in allocation units
	ResourceHeader* Buffer;
	c89atomic_uint32 AllocationsCount; //amount of allocations that have been allocated.

	AllocationDatasBuffer AllocationDatas;
}ResourceHeaderBuffer;
/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
*/
typedef struct ElementBuffer {
	ArenaAllocater* ArenaAllocaters; //size of CPU.MaxThreads
	uint32_t* Indexes; //size of CPU.MaxThreads
	uint64_t BufferSize; //size in allocation units
	Element* Buffer;
	c89atomic_uint32 AllocationsCount; //amount of allocations that have been allocated.

	AllocationDatasBuffer AllocationDatas;
}ElementBuffer;
/*
* Added in 1.0.0
* Triangle Engine Interchange Format.
*/
typedef struct TEIF_HEADER {
	char filecode[4]; //TEIF
	uint32_t reserved;

	uint64_t ObjectsOffset; //offset in bytes from start of file to first object
	uint64_t ObjectsSize; //size of objects buffer in object segments.

	uint64_t ResourceHeadersOffset; //offset in bytes from start of file to first object
	uint64_t ResourceHeadersSize; //size of objects buffer in object segments.

	uint64_t ElementsOffset; //offset in bytes from start of file to first object
	uint64_t ElementsSize; //size of objects buffer in object segments.

	uint64_t DataBufferOffset; //offset in bytes to the start of the databuffer.
	uint64_t DataBufferSize;
}TEIF_HEADER;


/*
* create is for initializing permenant objects, recreate is for initialize per run objects,

* There is 2 phases, one to return object size and the other to fill it with data.
*
* Code Template For Creation Function Passes

	if (pResourceHeader != NULL)
	{
		//fill header with data of choice
	}
	*pAllocationSize = [your_size_of_choice];

* pAllocationSize is in bytes


*/

/*
* For Destructors you are only meant to destroy all dependant objects, like [free([stringinobject])].

* Destroy has 2 items, the original item to destroy, and the overlay, the specification is that you compare
  every value between the item and the overlay, this tells you what items have changed over the course of an instance,
  every item that has changed, should be destructed.

* full destruct is for destructing things made in create, non full is for recreate in general.
*/

/*
* ReCreate will automatically destroy the previous object. So dont call it in the function!
*/

/*
* This is the same with Create_ElementTemplate & Create_ObjectTemplate.

* Packers work similarly to constructors, where there is 2 phases, one returns size and the second one fills the object with data.

* However, the return size and data is not of the object itself, it is of all dependant objects (like a char* to a name or something),
  So for a [char* name] the first pass would be adding [strlen(name)] to [uint64_t* pBufferPointer] and the second pass would be to
  fill [void* pData] with the string's contents. If you have more then 1 dependant object you should put them all in [void* pData],

* You should also cast the pointers of all dependant objects to a unsigned int that has the value of

* pObject is the original object that you source your data from and DO NOT MODIFY!, pCopiedObject is the object you should write to
  such as changing the pointers to offsets.

* Code Template For Function Passes
}
	if (pData != NULL)
	{
		//fill header with data of choice like as follows
		memcpy(pData, [string], strlen([string]));
		[string] = (void*)(0); //set it to a offset
		//following data fills should be like:
		memcpy(pData + strlen([string]), [string2], strlen([string2]));
		[string] = (void*)(strlen([string])); //set it to a offset
	}
	*pBufferPointer += [your_size_of_choice];
}
*/

/*
* UnPackers on the other hand, will get passed a refrence to the current object thats being unpacked and a pointer to the stored data.
  And then you do whatever you want to restore the data to its original state, be it pointers or whatever.

* when unpacking recreate will be called.

* Code Example For Unpacking.

void UnPack_Element2D(const Element2D* pElement, Element2D* pCopiedElement, void* pData)
{
	if (pElement->ex != NULL)
	{
		pCopiedElement->ex = (Element2Dex*)malloc(sizeof(*pElement->ex));
		memcpy(pCopiedElement->ex, (void*)((uint64_t)pData + (uint64_t)pElement->ex), sizeof(*pElement->ex));
	}
}

*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Object Signature
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef TEXRESULT(Create_ObjectTemplate)(Object* pObject, void* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex);
typedef TEXRESULT(Destroy_ObjectTemplate)(Object* pObject, Object* pObjectOverlay, bool Full, uint32_t ThreadIndex);

typedef TEXRESULT(ReCreate_ObjectTemplate)(Object* pObject, uint32_t ThreadIndex);

typedef TEXRESULT(Pack_ObjectTemplate)(const Object* pObject, Object* pCopiedObject, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex);
typedef TEXRESULT(UnPack_ObjectTemplate)(const Object* pObject, Object* pCopiedObject, const void* pData, uint32_t ThreadIndex);

/*
* Added in 1.0.0
*/
typedef struct ObjectSignature {
	Pack_ObjectTemplate* Packer;
	UnPack_ObjectTemplate* UnPacker;

	Create_ObjectTemplate* Constructor;
	Destroy_ObjectTemplate* Destructor;
	ReCreate_ObjectTemplate* ReConstructor;
	ObjectIdentifier Identifier;
	uint64_t ByteLength; //default if none specified in function/function doesnt exist

	c89atomic_uint32 AllocationsCount; //amount of allocations with specified identifier
	c89atomic_uint32 ObjectsCount; //amount of objects with specified identifier
}ObjectSignature;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ResourceHeader Signature
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef TEXRESULT(Create_ResourceHeaderTemplate)(ResourceHeader* pResourceHeader, void* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex);
typedef TEXRESULT(Destroy_ResourceHeaderTemplate)(ResourceHeader* pResourceHeader, ResourceHeader* pResourceHeaderOverlay, bool Full, uint32_t ThreadIndex);

typedef TEXRESULT(ReCreate_ResourceHeaderTemplate)(ResourceHeader* pResourceHeader, uint32_t ThreadIndex);

typedef TEXRESULT(Pack_ResourceHeaderTemplate)(const ResourceHeader* pResourceHeader, ResourceHeader* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex);
typedef TEXRESULT(UnPack_ResourceHeaderTemplate)(const ResourceHeader* pResourceHeader, ResourceHeader* pCopiedResourceHeader, const void* pData, uint32_t ThreadIndex);

/*
* Added in 1.0.0
*/
typedef struct ResourceHeaderSignature {
	Pack_ResourceHeaderTemplate* Packer;
	UnPack_ResourceHeaderTemplate* UnPacker;

	Create_ResourceHeaderTemplate* Constructor;
	Destroy_ResourceHeaderTemplate* Destructor;
	ReCreate_ResourceHeaderTemplate* ReConstructor;
	ResourceHeaderIdentifier Identifier;
	uint64_t ByteLength; //default if none specified in function/function doesnt exist

	c89atomic_uint32 AllocationsCount; //amount of allocations with specified identifier
	c89atomic_uint32 ResourceHeadersCount; //amount of resourceheaders with specified identifier
}ResourceHeaderSignature;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Element Signature
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef TEXRESULT(Create_ElementTemplate)(Element* pElement, void* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex);
typedef TEXRESULT(Destroy_ElementTemplate)(Element* pElement, Element* pElementOverlay, bool Full, uint32_t ThreadIndex);

typedef TEXRESULT(ReCreate_ElementTemplate)(Element* pElement, uint32_t ThreadIndex);

typedef TEXRESULT(Pack_ElementTemplate)(const Element* pElement, Element* pCopiedElement, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex);
typedef TEXRESULT(UnPack_ElementTemplate)(const Element* pElement, Element* pCopiedElement, const void* pData, uint32_t ThreadIndex);

/*
* Added in 1.0.0
*/
typedef struct ElementSignature {
	Pack_ElementTemplate* Packer;
	UnPack_ElementTemplate* UnPacker;

	Create_ElementTemplate* Constructor;
	Destroy_ElementTemplate* Destructor;
	ReCreate_ElementTemplate* ReConstructor;
	ElementIdentifier Identifier;
	uint64_t ByteLength; //default if none specified in function/function doesnt exist

	c89atomic_uint32 AllocationsCount; //amount of allocations with specified identifier
	c89atomic_uint32 ElementsCount; //amount of elements with specified identifier
}ElementSignature;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//API utils
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//utils
typedef struct ObjectUtils {
	struct {
		uint64_t InitialItemsMax; //initial size of the internal buffers to be set in create time.
		bool ActiveMemoryResizing; //set to true for buffers to be automatically managed.
	}Config;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Internal
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//signatures
	uint64_t ObjectSignaturesSize;
	ObjectSignature** ObjectSignatures;
	//the mutexes only really protect from concurrent writes
	Mutex ObjectSignaturesMutex;

	uint64_t ResourceHeaderSignaturesSize;
	ResourceHeaderSignature** ResourceHeaderSignatures;
	Mutex ResourceHeaderSignaturesMutex;

	uint64_t ElementSignaturesSize;
	ElementSignature** ElementSignatures;
	Mutex ElementSignaturesMutex;

	//Internal Buffers
	ObjectBuffer InternalObjectBuffer;
	ResourceHeaderBuffer InternalResourceHeaderBuffer;
	ElementBuffer InternalElementBuffer;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Default signatures
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Generic Signatures
	ObjectSignature GenericObjectSig;
	ResourceHeaderSignature GenericResourceHeaderSig;
	ElementSignature GenericElementSig;

	//Signatures
	ResourceHeaderSignature RHeaderSceneSig;
}ObjectUtils;

struct ObjectResStruct {
	ObjectUtils* pUtils;

	void* pInitialise_Objects;
	void* pDestroy_Objects;

	void* pCompare_ObjectAllocation;
	void* pCompare_ResourceHeaderAllocation;
	void* pCompare_ElementAllocation;

	void* pGet_ObjectAllocationData;
	void* pGet_ResourceHeaderAllocationData;
	void* pGet_ElementAllocationData;

	void* pGet_ObjectPointer;
	void* pGet_ResourceHeaderPointer;
	void* pGet_ElementPointer;

	void* pEnd_ObjectPointer;
	void* pEnd_ResourceHeaderPointer;
	void* pEnd_ElementPointer;

	void* pFind_ObjectSignature;
	void* pFind_ResourceHeaderSignature;
	void* pFind_ElementSignature;

	void* pCreate_ObjectBuffer;
	void* pCreate_ResourceHeaderBuffer;
	void* pCreate_ElementBuffer;

	void* pResize_ObjectBuffer;
	void* pResize_ResourceHeaderBuffer;
	void* pResize_ElementBuffer;

	void* pDestroy_ObjectBuffer;
	void* pDestroy_ResourceHeaderBuffer;
	void* pDestroy_ElementBuffer;

	void* pCreate_Object;
	void* pCreate_ResourceHeader;
	void* pCreate_Element;

	void* pDestroy_Object;
	void* pDestroy_ResourceHeader;
	void* pDestroy_Element;

	void* pReCreate_Object;
	void* pReCreate_ResourceHeader;
	void* pReCreate_Element;

	void* pAdd_ObjectChild;
	void* pAdd_Object_ResourceHeaderChild;
	void* pAdd_ResourceHeader_ElementChild;

	void* pRemove_ObjectChild;
	void* pRemove_Object_ResourceHeaderChild;
	void* pRemove_ResourceHeader_ElementChild;

	void* pRegister_ObjectSignature;
	void* pRegister_ResourceHeaderSignature;
	void* pRegister_ElementSignature;

	void* pDeRegister_ObjectSignature;
	void* pDeRegister_ResourceHeaderSignature;
	void* pDeRegister_ElementSignature;


	void* pScan_ObjectChilds;
	void* pScan_ObjectParents;

	void* pScan_ObjectResourceHeaders;
	void* pScan_ResourceHeaderElements;

	void* pScan_ObjectResourceHeadersSingle;
	void* pScan_ResourceHeaderElementsSingle;


	void* pWrite_TEIF;
	void* pRead_TEIF;
}ObjectsRes;

void Object_Initialise_Resources(FunctionInfo*** pExternFunctions, uint64_t* pExternFunctionsSize, ResourceInfo*** pExternResources, uint64_t* pExternResourcesSize) {
	memset(&ObjectsRes, 0, sizeof(ObjectsRes));

	ResourceImport(pExternResources, pExternResourcesSize, (const UTF8*)CopyData((void*)"Object::Utils"), &ObjectsRes.pUtils);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Compare_ObjectAllocation"), &ObjectsRes.pCompare_ObjectAllocation);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Compare_ResourceHeaderAllocation"), &ObjectsRes.pCompare_ResourceHeaderAllocation);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Compare_ElementAllocation"), &ObjectsRes.pCompare_ElementAllocation);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Get_ObjectAllocationData"), &ObjectsRes.pGet_ObjectAllocationData);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Get_ResourceHeaderAllocationData"), &ObjectsRes.pGet_ResourceHeaderAllocationData);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Get_ElementAllocationData"), &ObjectsRes.pGet_ElementAllocationData);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Get_ObjectPointer"), &ObjectsRes.pGet_ObjectPointer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Get_ResourceHeaderPointer"), &ObjectsRes.pGet_ResourceHeaderPointer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Get_ElementPointer"), &ObjectsRes.pGet_ElementPointer);
	
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::End_ObjectPointer"), &ObjectsRes.pEnd_ObjectPointer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::End_ResourceHeaderPointer"), &ObjectsRes.pEnd_ResourceHeaderPointer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::End_ElementPointer"), &ObjectsRes.pEnd_ElementPointer);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Find_ObjectSignature"), &ObjectsRes.pFind_ObjectSignature);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Find_ResourceHeaderSignature"), &ObjectsRes.pFind_ResourceHeaderSignature);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Find_ElementSignature"), &ObjectsRes.pFind_ElementSignature);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Create_ObjectBuffer"), &ObjectsRes.pCreate_ObjectBuffer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Create_ResourceHeaderBuffer"), &ObjectsRes.pCreate_ResourceHeaderBuffer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Create_ElementBuffer"), &ObjectsRes.pCreate_ElementBuffer);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Resize_ObjectBuffer"), &ObjectsRes.pResize_ObjectBuffer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Resize_ResourceHeaderBuffer"), &ObjectsRes.pResize_ResourceHeaderBuffer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Resize_ElementBuffer"), &ObjectsRes.pResize_ElementBuffer);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Destroy_ObjectBuffer"), &ObjectsRes.pDestroy_ObjectBuffer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Destroy_ResourceHeaderBuffer"), &ObjectsRes.pDestroy_ResourceHeaderBuffer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Destroy_ElementBuffer"), &ObjectsRes.pDestroy_ElementBuffer);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Create_Object"), &ObjectsRes.pCreate_Object);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Create_ResourceHeader"), &ObjectsRes.pCreate_ResourceHeader);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Create_Element"), &ObjectsRes.pCreate_Element);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Destroy_Object"), &ObjectsRes.pDestroy_Object);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Destroy_ResourceHeader"), &ObjectsRes.pDestroy_ResourceHeader);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Destroy_Element"), &ObjectsRes.pDestroy_Element);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::ReCreate_Object"), &ObjectsRes.pReCreate_Object);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::ReCreate_ResourceHeader"), &ObjectsRes.pReCreate_ResourceHeader);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::ReCreate_Element"), &ObjectsRes.pReCreate_Element);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Add_ObjectChild"), &ObjectsRes.pAdd_ObjectChild);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Add_Object_ResourceHeaderChild"), &ObjectsRes.pAdd_Object_ResourceHeaderChild);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Add_ResourceHeader_ElementChild"), &ObjectsRes.pAdd_ResourceHeader_ElementChild);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Remove_ObjectChild"), &ObjectsRes.pRemove_ObjectChild);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Remove_Object_ResourceHeaderChild"), &ObjectsRes.pRemove_Object_ResourceHeaderChild);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Remove_ResourceHeader_ElementChild"), &ObjectsRes.pRemove_ResourceHeader_ElementChild);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Register_ObjectSignature"), &ObjectsRes.pRegister_ObjectSignature);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Register_ResourceHeaderSignature"), &ObjectsRes.pRegister_ResourceHeaderSignature);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Register_ElementSignature"), &ObjectsRes.pRegister_ElementSignature);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::DeRegister_ObjectSignature"), &ObjectsRes.pDeRegister_ObjectSignature);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::DeRegister_ResourceHeaderSignature"), &ObjectsRes.pDeRegister_ResourceHeaderSignature);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::DeRegister_ElementSignature"), &ObjectsRes.pDeRegister_ElementSignature);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Scan_ObjectChilds"), &ObjectsRes.pScan_ObjectChilds);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Scan_ObjectParents"), &ObjectsRes.pScan_ObjectParents);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Scan_ObjectResourceHeaders"), &ObjectsRes.pScan_ObjectResourceHeaders);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Scan_ResourceHeaderElements"), &ObjectsRes.pScan_ResourceHeaderElements);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Scan_ObjectResourceHeadersSingle"), &ObjectsRes.pScan_ObjectResourceHeadersSingle);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Scan_ResourceHeaderElementsSingle"), &ObjectsRes.pScan_ResourceHeaderElementsSingle);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Write_TEIF"), &ObjectsRes.pWrite_TEIF);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Read_TEIF"), &ObjectsRes.pRead_TEIF);
}

TEXRESULT Object_Ref_Compare_ObjectAllocation(ObjectAllocation Allocation0, ObjectAllocation Allocation1)
{
	TEXRESULT(*function)(ObjectAllocation Allocation0, ObjectAllocation Allocation1) =
		(TEXRESULT(*)(ObjectAllocation Allocation0, ObjectAllocation Allocation1))ObjectsRes.pCompare_ObjectAllocation;
	return function(Allocation0, Allocation1);
}
TEXRESULT Object_Ref_Compare_ResourceHeaderAllocation(ResourceHeaderAllocation Allocation0, ResourceHeaderAllocation Allocation1)
{
	TEXRESULT(*function)(ResourceHeaderAllocation Allocation0, ResourceHeaderAllocation Allocation1) =
		(TEXRESULT(*)(ResourceHeaderAllocation Allocation0, ResourceHeaderAllocation Allocation1))ObjectsRes.pCompare_ResourceHeaderAllocation;
	return function(Allocation0, Allocation1);
}
TEXRESULT Object_Ref_Compare_ElementAllocation(ElementAllocation Allocation0, ElementAllocation Allocation1)
{
	TEXRESULT(*function)(ElementAllocation Allocation0, ElementAllocation Allocation1) =
		(TEXRESULT(*)(ElementAllocation Allocation0, ElementAllocation Allocation1))ObjectsRes.pCompare_ElementAllocation;
	return function(Allocation0, Allocation1);
}

AllocationData* Object_Ref_Get_ObjectAllocationData(ObjectAllocation Allocation)
{
	AllocationData* (*function)(ObjectAllocation Allocation) =
		(AllocationData* (*)(ObjectAllocation Allocation))ObjectsRes.pGet_ObjectAllocationData;
	return function(Allocation);
}
AllocationData* Object_Ref_Get_ResourceHeaderAllocationData(ResourceHeaderAllocation Allocation)
{
	AllocationData* (*function)(ResourceHeaderAllocation Allocation) =
		(AllocationData* (*)(ResourceHeaderAllocation Allocation))ObjectsRes.pGet_ResourceHeaderAllocationData;

	return function(Allocation);
}
AllocationData* Object_Ref_Get_ElementAllocationData(ElementAllocation Allocation)
{
	AllocationData* (*function)(ElementAllocation Allocation) =
		(AllocationData* (*)(ElementAllocation Allocation))ObjectsRes.pGet_ElementAllocationData;

	return function(Allocation);
}

Object* Object_Ref_Get_ObjectPointer(ObjectAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex)
{
	Object* (*function)(ObjectAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) =
		(Object* (*)(ObjectAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex))ObjectsRes.pGet_ObjectPointer;

	return function(Allocation, Write, Consistent, ThreadIndex);
}
ResourceHeader* Object_Ref_Get_ResourceHeaderPointer(ResourceHeaderAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex)
{
	ResourceHeader* (*function)(ResourceHeaderAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) =
		(ResourceHeader* (*)(ResourceHeaderAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex))ObjectsRes.pGet_ResourceHeaderPointer;

	return function(Allocation, Write, Consistent, ThreadIndex);
}
Element* Object_Ref_Get_ElementPointer(ElementAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex)
{
	Element* (*function)(ElementAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) =
		(Element* (*)(ElementAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex))ObjectsRes.pGet_ElementPointer;

	return function(Allocation, Write, Consistent, ThreadIndex);
}

void Object_Ref_End_ObjectPointer(ObjectAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex)
{
	void(*function)(ObjectAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) =
		(void(*)(ObjectAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex))ObjectsRes.pEnd_ObjectPointer;
	function(Allocation, Write, Consistent, ThreadIndex);
}

void Object_Ref_End_ResourceHeaderPointer(ResourceHeaderAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex)
{
	void(*function)(ResourceHeaderAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) =
		(void(*)(ResourceHeaderAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex))ObjectsRes.pEnd_ResourceHeaderPointer;
	function(Allocation, Write, Consistent, ThreadIndex);
}

void Object_Ref_End_ElementPointer(ElementAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex)
{
	void(*function)(ElementAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex) =
		(void(*)(ElementAllocation Allocation, bool Write, bool Consistent, uint32_t ThreadIndex))ObjectsRes.pEnd_ElementPointer;
	function(Allocation, Write, Consistent, ThreadIndex);
}


TEXRESULT Object_Ref_Find_ObjectSignature(ObjectIdentifier Identifier, ObjectSignature** ppSignature)
{
	TEXRESULT(*function)(ObjectIdentifier Identifier, ObjectSignature * *ppSignature) =
		(TEXRESULT(*)(ObjectIdentifier Identifier, ObjectSignature * *ppSignature))ObjectsRes.pFind_ObjectSignature;

	return function(Identifier, ppSignature);
}
TEXRESULT Object_Ref_Find_ResourceHeaderSignature(ResourceHeaderIdentifier Identifier, ResourceHeaderSignature** ppSignature)
{
	TEXRESULT(*function)(ResourceHeaderIdentifier Identifier, ResourceHeaderSignature * *ppSignature) =
		(TEXRESULT(*)(ResourceHeaderIdentifier Identifier, ResourceHeaderSignature * *ppSignature))ObjectsRes.pFind_ResourceHeaderSignature;

	return function(Identifier, ppSignature);
}
TEXRESULT Object_Ref_Find_ElementSignature(ElementIdentifier Identifier, ElementSignature** ppSignature)
{
	TEXRESULT(*function)(ElementIdentifier Identifier, ElementSignature * *ppSignature) =
		(TEXRESULT(*)(ElementIdentifier Identifier, ElementSignature * *ppSignature))ObjectsRes.pFind_ElementSignature;

	return function(Identifier, ppSignature);
}

TEXRESULT Object_Ref_Create_ObjectBuffer(ObjectBuffer* pBuffer, uint64_t InitialSize)
{
	TEXRESULT(*function)(ObjectBuffer * pBuffer, uint64_t InitialSize) =
		(TEXRESULT(*)(ObjectBuffer * pBuffer, uint64_t InitialSize))ObjectsRes.pCreate_ObjectBuffer;

	return function(pBuffer, InitialSize);
}
TEXRESULT Object_Ref_Create_ResourceHeaderBuffer(ResourceHeaderBuffer* pBuffer, uint64_t InitialSize)
{
	TEXRESULT(*function)(ResourceHeaderBuffer * pBuffer, uint64_t InitialSize) =
		(TEXRESULT(*)(ResourceHeaderBuffer * pBuffer, uint64_t InitialSize))ObjectsRes.pCreate_ResourceHeaderBuffer;

	return function(pBuffer, InitialSize);
}
TEXRESULT Object_Ref_Create_ElementBuffer(ElementBuffer* pBuffer, uint64_t InitialSize)
{
	TEXRESULT(*function)(ElementBuffer * pBuffer, uint64_t InitialSize) =
		(TEXRESULT(*)(ElementBuffer * pBuffer, uint64_t InitialSize))ObjectsRes.pCreate_ElementBuffer;

	return function(pBuffer, InitialSize);
}

TEXRESULT Object_Ref_Resize_ObjectBuffer(ObjectBuffer* pBuffer, uint64_t NewSize, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ObjectBuffer * pBuffer, uint64_t NewSize, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ObjectBuffer * pBuffer, uint64_t NewSize, uint32_t ThreadIndex))ObjectsRes.pResize_ObjectBuffer;

	return function(pBuffer, NewSize, ThreadIndex);
}
TEXRESULT Object_Ref_Resize_ResourceHeaderBuffer(ResourceHeaderBuffer* pBuffer, uint64_t NewSize, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ResourceHeaderBuffer * pBuffer, uint64_t NewSize, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ResourceHeaderBuffer * pBuffer, uint64_t NewSize, uint32_t ThreadIndex))ObjectsRes.pResize_ResourceHeaderBuffer;

	return function(pBuffer, NewSize, ThreadIndex);
}
TEXRESULT Object_Ref_Resize_ElementBuffer(ElementBuffer* pBuffer, uint64_t NewSize, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ElementBuffer * pBuffer, uint64_t NewSize, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ElementBuffer * pBuffer, uint64_t NewSize, uint32_t ThreadIndex))ObjectsRes.pResize_ElementBuffer;

	return function(pBuffer, NewSize, ThreadIndex);
}

TEXRESULT Object_Ref_Create_Object(ObjectAllocation* pAllocation, ObjectCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ObjectAllocation * pAllocation, ObjectCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ObjectAllocation * pAllocation, ObjectCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex))ObjectsRes.pCreate_Object;

	return function(pAllocation, CreateInfo, pCreateInfo, ThreadIndex);
}
TEXRESULT Object_Ref_Create_ResourceHeader(ResourceHeaderAllocation* pAllocation, ResourceHeaderCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ResourceHeaderAllocation * pAllocation, ResourceHeaderCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ResourceHeaderAllocation * pAllocation, ResourceHeaderCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex))ObjectsRes.pCreate_ResourceHeader;

	return function(pAllocation, CreateInfo, pCreateInfo, ThreadIndex);
}
TEXRESULT Object_Ref_Create_Element(ElementAllocation* pAllocation, ElementCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ElementAllocation * pAllocation, ElementCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ElementAllocation * pAllocation, ElementCreateInfo CreateInfo, void* pCreateInfo, uint32_t ThreadIndex))ObjectsRes.pCreate_Element;

	return function(pAllocation, CreateInfo, pCreateInfo, ThreadIndex);
}

TEXRESULT Object_Ref_Destroy_Object(ObjectAllocation Allocation, bool Full, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ObjectAllocation Allocation, bool Full, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ObjectAllocation Allocation, bool Full, uint32_t ThreadIndex))ObjectsRes.pDestroy_Object;

	return function(Allocation, Full, ThreadIndex);
}
TEXRESULT Object_Ref_Destroy_ResourceHeader(ResourceHeaderAllocation Allocation, bool Full, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ResourceHeaderAllocation Allocation, bool Full, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ResourceHeaderAllocation Allocation, bool Full, uint32_t ThreadIndex))ObjectsRes.pDestroy_ResourceHeader;

	return function(Allocation, Full, ThreadIndex);
}
TEXRESULT Object_Ref_Destroy_Element(ElementAllocation Allocation, bool Full, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ElementAllocation Allocation, bool Full, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ElementAllocation Allocation, bool Full, uint32_t ThreadIndex))ObjectsRes.pDestroy_Element;

	return function(Allocation, Full, ThreadIndex);
}

TEXRESULT Object_Ref_ReCreate_Object(ObjectAllocation Allocation, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ObjectAllocation Allocation, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ObjectAllocation Allocation, uint32_t ThreadIndex))ObjectsRes.pReCreate_Object;

	return function(Allocation, ThreadIndex);
}
TEXRESULT Object_Ref_ReCreate_ResourceHeader(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex))ObjectsRes.pReCreate_ResourceHeader;

	return function(Allocation, ThreadIndex);
}
TEXRESULT Object_Ref_ReCreate_Element(ElementAllocation Allocation, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ElementAllocation Allocation, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ElementAllocation Allocation, uint32_t ThreadIndex))ObjectsRes.pReCreate_Element;

	return function(Allocation, ThreadIndex);
}

TEXRESULT Object_Ref_Destroy_ObjectBuffer(ObjectBuffer* pBuffer, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ObjectBuffer * pBuffer, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ObjectBuffer * pBuffer, uint32_t ThreadIndex))ObjectsRes.pDestroy_ObjectBuffer;

	return function(pBuffer, ThreadIndex);
}
TEXRESULT Object_Ref_Destroy_ResourceHeaderBuffer(ResourceHeaderBuffer* pBuffer, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ResourceHeaderBuffer * pBuffer, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ResourceHeaderBuffer * pBuffer, uint32_t ThreadIndex))ObjectsRes.pDestroy_ResourceHeaderBuffer;

	return function(pBuffer, ThreadIndex);
}
TEXRESULT Object_Ref_Destroy_ElementBuffer(ElementBuffer* pBuffer, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ElementBuffer * pBuffer, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ElementBuffer * pBuffer, uint32_t ThreadIndex))ObjectsRes.pDestroy_ElementBuffer;

	return function(pBuffer, ThreadIndex);
}

void Object_Ref_Add_ObjectChild(ObjectAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex)
{
	void (*function)(ObjectAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex) =
		(void (*)(ObjectAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex))ObjectsRes.pAdd_ObjectChild;

	function(Allocation, Parent, ThreadIndex);
}
void Object_Ref_Add_Object_ResourceHeaderChild(ResourceHeaderAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex)
{
	void (*function)(ResourceHeaderAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex) =
		(void (*)(ResourceHeaderAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex))ObjectsRes.pAdd_Object_ResourceHeaderChild;

	function(Allocation, Parent, ThreadIndex);
}
void Object_Ref_Add_ResourceHeader_ElementChild(ElementAllocation Allocation, ResourceHeaderAllocation Parent, uint32_t ThreadIndex)
{
	void (*function)(ElementAllocation Allocation, ResourceHeaderAllocation Parent, uint32_t ThreadIndex) =
		(void (*)(ElementAllocation Allocation, ResourceHeaderAllocation Parent, uint32_t ThreadIndex))ObjectsRes.pAdd_ResourceHeader_ElementChild;

	function(Allocation, Parent, ThreadIndex);
}
void Object_Ref_Remove_ObjectChild(ObjectAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex)
{
	void (*function)(ObjectAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex) =
		(void (*)(ObjectAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex))ObjectsRes.pRemove_ObjectChild;

	function(Allocation, Parent, ThreadIndex);
}
void Object_Ref_Remove_Object_ResourceHeaderChild(ResourceHeaderAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex)
{
	void (*function)(ResourceHeaderAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex) =
		(void (*)(ResourceHeaderAllocation Allocation, ObjectAllocation Parent, uint32_t ThreadIndex))ObjectsRes.pRemove_Object_ResourceHeaderChild;

	function(Allocation, Parent, ThreadIndex);
}
void Object_Ref_Remove_ResourceHeader_ElementChild(ElementAllocation Allocation, ResourceHeaderAllocation Parent, uint32_t ThreadIndex)
{
	void (*function)(ElementAllocation Allocation, ResourceHeaderAllocation Parent, uint32_t ThreadIndex) =
		(void (*)(ElementAllocation Allocation, ResourceHeaderAllocation Parent, uint32_t ThreadIndex))ObjectsRes.pRemove_ResourceHeader_ElementChild;

	function(Allocation, Parent, ThreadIndex);
}
void Object_Ref_Scan_ObjectChilds(ObjectAllocation Allocation, ObjectAllocation** pChilds, uint64_t* pChildsSize, uint32_t ThreadIndex)
{
	void (*function)(ObjectAllocation Allocation, ObjectAllocation * *pChilds, uint64_t * pChildsSize, uint32_t ThreadIndex) =
		(void (*)(ObjectAllocation Allocation, ObjectAllocation * *pChilds, uint64_t * pChildsSize, uint32_t ThreadIndex))ObjectsRes.pScan_ObjectChilds;

	function(Allocation, pChilds, pChildsSize, ThreadIndex);
}
void Object_Ref_Scan_ObjectParents(ObjectAllocation Allocation, ObjectAllocation** pParents, uint64_t* pParentsSize, uint32_t ThreadIndex)
{
	void (*function)(ObjectAllocation Allocation, ObjectAllocation * *pParents, uint64_t * pParentsSize, uint32_t ThreadIndex) =
		(void (*)(ObjectAllocation Allocation, ObjectAllocation * *pParents, uint64_t * pParentsSize, uint32_t ThreadIndex))ObjectsRes.pScan_ObjectParents;

	function(Allocation, pParents, pParentsSize, ThreadIndex);
}
void Object_Ref_Scan_ObjectResourceHeaders(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, ResourceHeaderAllocation** pResourceHeaders, uint64_t* pResourceHeadersSize, uint32_t ThreadIndex)
{
	void (*function)(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, ResourceHeaderAllocation * *pResourceHeaders, uint64_t * pResourceHeadersSize, uint32_t ThreadIndex) =
		(void (*)(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, ResourceHeaderAllocation * *pResourceHeaders, uint64_t * pResourceHeadersSize, uint32_t ThreadIndex))ObjectsRes.pScan_ObjectResourceHeaders;

	function(Allocation, Identifier, pResourceHeaders, pResourceHeadersSize, ThreadIndex);
}
void Object_Ref_Scan_ResourceHeaderElements(ResourceHeaderAllocation Allocation, ElementIdentifier Identifier, ElementAllocation** pElements, uint64_t* pElementsSize, uint32_t ThreadIndex)
{
	void (*function)(ResourceHeaderAllocation Allocation, ElementIdentifier Identifier, ElementAllocation * *pElements, uint64_t * pElementsSize, uint32_t ThreadIndex) =
		(void (*)(ResourceHeaderAllocation Allocation, ElementIdentifier Identifier, ElementAllocation * *pElements, uint64_t * pElementsSize, uint32_t ThreadIndex))ObjectsRes.pScan_ResourceHeaderElements;

	function(Allocation, Identifier, pElements, pElementsSize, ThreadIndex);
}
ResourceHeaderAllocation Object_Ref_Scan_ObjectResourceHeadersSingle(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, uint32_t ThreadIndex)
{
	ResourceHeaderAllocation(*function)(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, uint32_t ThreadIndex) =
		(ResourceHeaderAllocation(*)(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, uint32_t ThreadIndex))ObjectsRes.pScan_ObjectResourceHeadersSingle;

	return function(Allocation, Identifier, ThreadIndex);
}
ElementAllocation Object_Ref_Scan_ResourceHeaderElementsSingle(ResourceHeaderAllocation Allocation, ElementIdentifier Identifier, uint32_t ThreadIndex)
{
	ElementAllocation(*function)(ResourceHeaderAllocation Allocation, ElementIdentifier Identifier, uint32_t ThreadIndex) =
		(ElementAllocation(*)(ResourceHeaderAllocation Allocation, ElementIdentifier Identifier, uint32_t ThreadIndex))ObjectsRes.pScan_ResourceHeaderElementsSingle;

	return function(Allocation, Identifier, ThreadIndex);
}


TEXRESULT Object_Ref_Register_ObjectSignature(ObjectSignature* pSignature)
{
	TEXRESULT(*function)(ObjectSignature * pSignature) =
		(TEXRESULT(*)(ObjectSignature * pSignature))ObjectsRes.pRegister_ObjectSignature;

	return function(pSignature);
}
TEXRESULT Object_Ref_Register_ResourceHeaderSignature(ResourceHeaderSignature* pSignature)
{
	TEXRESULT(*function)(ResourceHeaderSignature * pSignature) =
		(TEXRESULT(*)(ResourceHeaderSignature * pSignature))ObjectsRes.pRegister_ResourceHeaderSignature;

	return function(pSignature);
}
TEXRESULT Object_Ref_Register_ElementSignature(ElementSignature* pSignature)
{
	TEXRESULT(*function)(ElementSignature * pSignature) =
		(TEXRESULT(*)(ElementSignature * pSignature))ObjectsRes.pRegister_ElementSignature;

	return function(pSignature);
}

TEXRESULT Object_Ref_DeRegister_ObjectSignature(ObjectSignature* pSignature)
{
	TEXRESULT(*function)(ObjectSignature * pSignature) =
		(TEXRESULT(*)(ObjectSignature * pSignature))ObjectsRes.pDeRegister_ObjectSignature;

	return function(pSignature);
}
TEXRESULT Object_Ref_DeRegister_ResourceHeaderSignature(ResourceHeaderSignature* pSignature)
{
	TEXRESULT(*function)(ResourceHeaderSignature * pSignature) =
		(TEXRESULT(*)(ResourceHeaderSignature * pSignature))ObjectsRes.pDeRegister_ResourceHeaderSignature;

	return function(pSignature);
}
TEXRESULT Object_Ref_DeRegister_ElementSignature(ElementSignature* pSignature)
{
	TEXRESULT(*function)(ElementSignature * pSignature) =
		(TEXRESULT(*)(ElementSignature * pSignature))ObjectsRes.pDeRegister_ElementSignature;

	return function(pSignature);
}

TEXRESULT Object_Ref_Write_TEIF(const UTF8* Path, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(const UTF8 * Path, uint32_t ThreadIndex) =
		(TEXRESULT(*)(const UTF8 * Path, uint32_t ThreadIndex))ObjectsRes.pWrite_TEIF;

	return function(Path, ThreadIndex);
}
TEXRESULT Object_Ref_Read_TEIF(const UTF8* Path, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(const UTF8 * Path, uint32_t ThreadIndex) =
		(TEXRESULT(*)(const UTF8 * Path, uint32_t ThreadIndex))ObjectsRes.pRead_TEIF;

	return function(Path, ThreadIndex);
}

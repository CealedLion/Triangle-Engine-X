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
typedef enum ObjectType
{
	Object_Generic = 1
}ObjectType;
/*
* Added in 1.0.0
* Objects API Generic.
*/
typedef enum ResourceHeaderType
{
	ResourceHeader_Generic = 1,
}ResourceHeaderType;
/*
* Added in 1.0.0
* Objects API Generic.
*/
typedef enum ElementType
{
	Element_Generic = 1
}ElementType;

/*
* Added in 1.0.0
* Iterator through pointer of Signatures in the API
*/
typedef uint64_t ObjectBufferIndex;
typedef uint64_t ResourceHeaderBufferIndex;
typedef uint64_t ElementBufferIndex;
/*
* Added in 1.0.0
* Identifier enum.
*/
typedef uint32_t ObjectIdentifier;
typedef uint32_t ResourceHeaderIdentifier;
typedef uint32_t ElementIdentifier;

/*
* The Maxinium Allocatable size is 137.4 GB
  From (2 ^ 32) (size of uint32_t) * 32 (mininium size of allocation).
* Identifier 0 is invalid.
*
*/
/*
* Added in 1.0.0
*/
typedef struct ObjectAllocation{
	uint32_t Pointer;
	ObjectIdentifier Identifier;
}ObjectAllocation;
/*
* Added in 1.0.0
*/
typedef struct ResourceHeaderAllocation{
	uint32_t Pointer;
	ResourceHeaderIdentifier Identifier;
}ResourceHeaderAllocation;
/*
* Added in 1.0.0
*/
typedef struct ElementAllocation{
	uint32_t Pointer;
	ElementIdentifier Identifier;
}ElementAllocation;

typedef struct DelayedInstance{
	c89atomic_uint32 Pointer; //only read from current thread index never read/write to others!!!
	c89atomic_bool Latest;
}DelayedInstance;
#define DelayedInstanceSize 12

/*
* Added in 1.0.0
* resourceheaders & elements can have multiple parent objects.
  Objects follow a strict hierachy of only 1 parent.
* When a gameobject is destroyed, it is not responsible for destroying it's resourceheaders.
* When a gameobject is destroyed it also removes all refrences of it itself from it's children and
  resourceheaders.
*/
typedef struct ObjectCreateInfo{
	const UTF8* Name;
	ObjectIdentifier Identifier;
}ObjectCreateInfo;
typedef struct ObjectTEMPLATE{
	ObjectAllocation Allocation;
	ObjectAllocation iParent;

	uint64_t AllocationSize;

	uint64_t iResourceHeadersSize;
	ResourceHeaderAllocation* iResourceHeaders;

	uint64_t iChildrenSize;
	ObjectAllocation* iChildren;

	const UTF8* Name;

#ifdef OBJECT_MUTEX
	Mutex mutex; //temp
#endif
	DelayedInstance pDelayedInstances[DelayedInstanceSize];

}ObjectTEMPLATE;
typedef struct Object{
	ObjectTEMPLATE Header;
}Object;

/*
* Added in 1.0.0
* ResourceHeaders are just what they sound like, headers for resources that can be
  attached to gameobjects and can have elements as childs.
* Free floating resourceheaders & elements are perfectly legal.
* When a resourceheader is destroyed it is not responsible for destroying its elements.
* When a resourceheader is destroyed it will remove all refrences of itself from its parents,
and from its elements.
*/
typedef struct ResourceHeaderCreateInfo{
	const UTF8* Name;
	ResourceHeaderIdentifier Identifier;
}ResourceHeaderCreateInfo;
typedef struct ResourceHeaderTEMPLATE{
	ResourceHeaderAllocation Allocation;

	uint64_t AllocationSize;

	uint64_t iParentsSize;
	ObjectAllocation* iParents;

	uint64_t iElementsSize;
	ElementAllocation* iElements;

	const UTF8* Name;

#ifdef OBJECT_MUTEX
	Mutex mutex; //temp
#endif
	DelayedInstance pDelayedInstances[DelayedInstanceSize];

}ResourceHeaderTEMPLATE;
typedef struct ResourceHeader{
	ResourceHeaderTEMPLATE Header;
}ResourceHeader;

/*
* Added in 1.0.0
* Elements are the lowest level of object, they do frame by frame functions,
  like being 3d objects, or being audio objects.
* Elements can be instanced by refrencing them in multiple resourceheaders.
*/
typedef struct ElementCreateInfo{
	const UTF8* Name;
	ElementIdentifier Identifier;
}ElementCreateInfo;
typedef struct ElementTEMPLATE{
	ElementAllocation Allocation;

	uint64_t AllocationSize;

	uint64_t iParentsSize;
	ResourceHeaderAllocation* iParents;

	const UTF8* Name;

#ifdef OBJECT_MUTEX
	Mutex mutex; //temp
#endif
	DelayedInstance pDelayedInstances[DelayedInstanceSize];

}ElementTEMPLATE;
typedef struct Element{
	ElementTEMPLATE Header;
}Element;


typedef struct ObjectInstance {
	Object* pInstance;
	uint32_t Pointer;
}ObjectInstance;

typedef struct ResourceHeaderInstance {
	ResourceHeader* pInstance;
	uint32_t Pointer;
}ResourceHeaderInstance;

typedef struct ElementInstance {
	Element* pInstance;
	uint32_t Pointer;
}ElementInstance;


/*
* Added in 1.0.0
*/
typedef struct ArenaAllocater {
	uint64_t StartPtr;
	uint64_t EndPtr;
	uint64_t Size;
	uint64_t PrevPointer;
	Mutex mutex;
}ArenaAllocater;

/*
* Added in 1.0.0
*/
typedef struct GenericBuffer {
	ArenaAllocater* ArenaAllocaters; //size of CPU.MaxThreads
	uint32_t* Indexes; //size of CPU.MaxThreads
	uint64_t Size;
	void* Buffer;
}GenericBuffer;

/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
*/
typedef struct ObjectBuffer{
	ArenaAllocater* ArenaAllocaters; //size of CPU.MaxThreads
	uint32_t* Indexes; //size of CPU.MaxThreads
	uint64_t Size;
	Object* Buffer;
}ObjectBuffer;
/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
*/
typedef struct ResourceHeaderBuffer{
	ArenaAllocater* ArenaAllocaters; //size of CPU.MaxThreads
	uint32_t* Indexes; //size of CPU.MaxThreads
	uint64_t Size;
	ResourceHeader* Buffer;
}ResourceHeaderBuffer;
/*
* Added in 1.0.0
* When a buffer is destroyed all objects within it are also destroyed, you can circumvent this by moving the object.
*/
typedef struct ElementBuffer{
	ArenaAllocater* ArenaAllocaters; //size of CPU.MaxThreads
	uint32_t* Indexes; //size of CPU.MaxThreads
	uint64_t Size;
	Element* Buffer;
}ElementBuffer;

/*
* Added in 1.0.0
*/
typedef enum ObjectBufferType{
	ObjectBufferType_Object = 0,
	ObjectBufferType_ResourceHeader = 1,
	ObjectBufferType_Element = 2,
}ObjectBufferType;
/*
* Added in 1.0.0
* object for representing either one of the 3 types of buffer pointers, used with ObjectBufferType.
*/
typedef union pObjectBuffer{
	ObjectBuffer* Object;
	ResourceHeaderBuffer* ResourceHeader;
	ElementBuffer* Element;
}pObjectBuffer;




/*
* There is 2 phases, one to return object size and the other to fill it with data.
* Code Template For Creation Function Passes
* pAllocationSize is in bytes
}
	if (pResourceHeader != NULL)
	{
		//fill header with data of choice
	}
	*pAllocationSize = [your_size_of_choice];
}
* For Destructors you are only meant to destroy all dependant objects, like [free([stringinobject])].


* This is the same with Create_ElementTemplate & Create_ObjectTemplate.
*/

/*
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

* UnPackers on the other hand, will get passed a refrence to the current object thats being unpacked and a pointer to the stored data.
  And then you do whatever you want to restore the data to its original state, be it pointers or whatever.


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
/*
* ReCreate will automatically destroy the previous object. So dont call it in the function!
*/
//full == true destruct destroys everything, full == false destruct only destroys per init variables.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Object Signature
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef TEXRESULT(Create_ObjectTemplate)(Object* pObject, void* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex);
typedef void(Destroy_ObjectTemplate)(Object* pObject, bool Full, uint32_t ThreadIndex);

typedef void(ReCreate_ObjectTemplate)(Object* pObject, uint32_t ThreadIndex);

typedef void(Pack_ObjectTemplate)(const Object* pObject, Object* pCopiedObject, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex);
typedef void(UnPack_ObjectTemplate)(const Object* pObject, Object* pCopiedObject, const void* pData, uint32_t ThreadIndex);

/*
* Added in 1.0.0
*/
typedef struct ObjectSignature{
	Pack_ObjectTemplate* Packer;
	UnPack_ObjectTemplate* UnPacker;

	Create_ObjectTemplate* Constructor;
	Destroy_ObjectTemplate* Destructor;
	ReCreate_ObjectTemplate* ReConstructor;
	ObjectBuffer* Buffer;
	ObjectIdentifier Identifier;
	uint64_t ByteLength; //default if none specified in function/function doesnt exist
} ObjectSignature;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ResourceHeader Signature
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef TEXRESULT(Create_ResourceHeaderTemplate)(ResourceHeader* pResourceHeader, void* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex);
typedef void(Destroy_ResourceHeaderTemplate)(ResourceHeader* pResourceHeader, bool Full, uint32_t ThreadIndex);

typedef void(ReCreate_ResourceHeaderTemplate)(ResourceHeader* pResourceHeader, uint32_t ThreadIndex);

typedef void(Pack_ResourceHeaderTemplate)(const ResourceHeader* pResourceHeader, ResourceHeader* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex);
typedef void(UnPack_ResourceHeaderTemplate)(const ResourceHeader* pResourceHeader, ResourceHeader* pCopiedResourceHeader, const void* pData, uint32_t ThreadIndex);

/*
* Added in 1.0.0
*/
typedef struct ResourceHeaderSignature{
	Pack_ResourceHeaderTemplate* Packer;
	UnPack_ResourceHeaderTemplate* UnPacker;

	Create_ResourceHeaderTemplate* Constructor;
	Destroy_ResourceHeaderTemplate* Destructor;
	ReCreate_ResourceHeaderTemplate* ReConstructor;
	ResourceHeaderBuffer* Buffer;
	ResourceHeaderIdentifier Identifier;
	uint64_t ByteLength; //default if none specified in function/function doesnt exist
}ResourceHeaderSignature;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Element Signature
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef TEXRESULT(Create_ElementTemplate)(Element* pElement, void* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex);
typedef void(Destroy_ElementTemplate)(Element* pElement, bool Full, uint32_t ThreadIndex);

typedef void(ReCreate_ElementTemplate)(Element* pElement, uint32_t ThreadIndex);

typedef void(Pack_ElementTemplate)(const Element* pElement, Element* pCopiedElement, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex);
typedef void(UnPack_ElementTemplate)(const Element* pElement, Element* pCopiedElement, const void* pData, uint32_t ThreadIndex);

/*
* Added in 1.0.0
*/
typedef struct ElementSignature{
	Pack_ElementTemplate* Packer;
	UnPack_ElementTemplate* UnPacker;

	Create_ElementTemplate* Constructor;
	Destroy_ElementTemplate* Destructor;
	ReCreate_ElementTemplate* ReConstructor;
	ElementBuffer* Buffer;
	ElementIdentifier Identifier;
	uint64_t ByteLength; //default if none specified in function/function doesnt exist
}ElementSignature;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//API utils
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Triangle Engine Interchange Format.
*/
typedef struct TEIF_HEADER
{
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


//utils

typedef struct ObjectUtils{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Internal
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	uint64_t ObjectSignaturesSize;
	ObjectSignature** ObjectSignatures;
	Mutex ObjectSignaturesMutex;

	uint64_t ResourceHeaderSignaturesSize;
	ResourceHeaderSignature** ResourceHeaderSignatures;
	Mutex ResourceHeaderSignaturesMutex;

	uint64_t ElementSignaturesSize;
	ElementSignature** ElementSignatures;
	Mutex ElementSignaturesMutex;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//default signatures
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Internal Buffers
	ObjectSignature InternalObjectSig;
	ObjectBuffer InternalObjectBuffer;

	ResourceHeaderSignature InternalResourceHeaderSig;
	ResourceHeaderBuffer InternalResourceHeaderBuffer;

	ElementSignature InternalElementSig;
	ElementBuffer InternalElementBuffer;

	//Generic Buffers
	ObjectSignature GenericObjectSig;
	ObjectBuffer GenericObjectBuffer;

	ResourceHeaderSignature GenericResourceHeaderSig;
	ResourceHeaderBuffer GenericResourceHeaderBuffer;

	ElementSignature GenericElementSig;
	ElementBuffer GenericElementBuffer;
}ObjectUtils;


struct ObjectResStruct
{
	void* pUtils;

	void* pInitialise_Objects;
	void* pDestroy_Objects;

	void* pCreate_ObjectBuffer;
	void* pCreate_ResourceHeaderBuffer;
	void* pCreate_ElementBuffer;

	void* pResize_ObjectBuffer;
	void* pResize_ResourceHeaderBuffer;
	void* pResize_ElementBuffer;

	void* pDestroy_ObjectBuffer;
	void* pDestroy_ResourceHeaderBuffer;
	void* pDestroy_ElementBuffer;

	void* pFind_ObjectSignature;
	void* pFind_ResourceHeaderSignature;
	void* pFind_ElementSignature;


	void* pCreateInstance_Object;
	void* pCreateInstance_ResourceHeader;
	void* pCreateInstance_Element;

	void* pCreate_Object;
	void* pCreate_ResourceHeader;
	void* pCreate_Element;

	void* pDestroy_Object;
	void* pDestroy_ResourceHeader;
	void* pDestroy_Element;

	void* pReCreate_Object;
	void* pReCreate_ResourceHeader;
	void* pReCreate_Element;

	void* pStartThread_Object;
	void* pStartThread_ResourceHeader;
	void* pStartThread_Element;

	void* pEndThread_Object;
	void* pEndThread_ResourceHeader;
	void* pEndThread_Element;

	void* pGet_ObjectPointer;
	void* pGet_ResourceHeaderPointer;
	void* pGet_ElementPointer;

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
	void* pScan_ObjectHeaders;
	void* pScan_ObjectHeadersSingle;

	void* pWrite_TEIF;
	void* pRead_TEIF;
}ObjectsRes;

void Object_Initialise_Resources(FunctionInfo*** pExternFunctions, uint64_t* pExternFunctionsSize, ResourceInfo*** pExternResources, uint64_t* pExternResourcesSize)
{
	memset(&ObjectsRes, NULL, sizeof(ObjectsRes));

	ResourceImport(pExternResources, pExternResourcesSize, (const UTF8*)CopyData((void*)"Object::Utils"), &ObjectsRes.pUtils);

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


	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::CreateInstance_Object"), &ObjectsRes.pCreateInstance_Object);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::CreateInstance_ResourceHeader"), &ObjectsRes.pCreateInstance_ResourceHeader);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::CreateInstance_Element"), &ObjectsRes.pCreateInstance_Element);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Create_Object"), &ObjectsRes.pCreate_Object);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Create_ResourceHeader"), &ObjectsRes.pCreate_ResourceHeader);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Create_Element"), &ObjectsRes.pCreate_Element);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Destroy_Object"), &ObjectsRes.pDestroy_Object);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Destroy_ResourceHeader"), &ObjectsRes.pDestroy_ResourceHeader);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Destroy_Element"), &ObjectsRes.pDestroy_Element);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::ReCreate_Object"), &ObjectsRes.pReCreate_Object);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::ReCreate_ResourceHeader"), &ObjectsRes.pReCreate_ResourceHeader);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::ReCreate_Element"), &ObjectsRes.pReCreate_Element);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::StartThread_Object"), &ObjectsRes.pStartThread_Object);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::StartThread_ResourceHeader"), &ObjectsRes.pStartThread_ResourceHeader);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::StartThread_Element"), &ObjectsRes.pStartThread_Element);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::EndThread_Object"), &ObjectsRes.pEndThread_Object);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::EndThread_ResourceHeader"), &ObjectsRes.pEndThread_ResourceHeader);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::EndThread_Element"), &ObjectsRes.pEndThread_Element);


	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Get_ObjectPointer"), &ObjectsRes.pGet_ObjectPointer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Get_ResourceHeaderPointer"), &ObjectsRes.pGet_ResourceHeaderPointer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Get_ElementPointer"), &ObjectsRes.pGet_ElementPointer);

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
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Scan_ObjectHeaders"), &ObjectsRes.pScan_ObjectHeaders);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Scan_ObjectHeadersSingle"), &ObjectsRes.pScan_ObjectHeadersSingle);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Write_TEIF"), &ObjectsRes.pWrite_TEIF);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Object::Read_TEIF"), &ObjectsRes.pRead_TEIF);
}


TEXRESULT Object_Ref_Find_ObjectSignature(ObjectIdentifier Identifier, ObjectSignature** ppSignature, ObjectBufferIndex* pBufferIndex)
{
	TEXRESULT(*function)(ObjectIdentifier Identifier, ObjectSignature * *ppSignature, ObjectBufferIndex * pBufferIndex) =
		(TEXRESULT(*)(ObjectIdentifier Identifier, ObjectSignature * *ppSignature, ObjectBufferIndex * pBufferIndex))ObjectsRes.pFind_ObjectSignature;

	return function(Identifier, ppSignature, pBufferIndex);
}
TEXRESULT Object_Ref_Find_ResourceHeaderSignature(ResourceHeaderIdentifier Identifier, ResourceHeaderSignature** ppSignature, ResourceHeaderBufferIndex* pBufferIndex)
{
	TEXRESULT(*function)(ResourceHeaderIdentifier Identifier, ResourceHeaderSignature * *ppSignature, ResourceHeaderBufferIndex * pBufferIndex) =
		(TEXRESULT(*)(ResourceHeaderIdentifier Identifier, ResourceHeaderSignature * *ppSignature, ResourceHeaderBufferIndex * pBufferIndex))ObjectsRes.pFind_ResourceHeaderSignature;

	return function(Identifier, ppSignature, pBufferIndex);
}
TEXRESULT Object_Ref_Find_ElementSignature(ElementIdentifier Identifier, ElementSignature** ppSignature, ElementBufferIndex* pBufferIndex)
{
	TEXRESULT(*function)(ElementIdentifier Identifier, ElementSignature * *ppSignature, ElementBufferIndex * pBufferIndex) =
		(TEXRESULT(*)(ElementIdentifier Identifier, ElementSignature * *ppSignature, ElementBufferIndex * pBufferIndex))ObjectsRes.pFind_ElementSignature;

	return function(Identifier, ppSignature, pBufferIndex);
}

TEXRESULT Object_Ref_Get_ObjectAllocationValidity(ObjectAllocation Allocation)
{
	return (TEXRESULT)((Allocation.Identifier != 0) ? Success : Failure);
}
TEXRESULT Object_Ref_Get_ResourceHeaderAllocationValidity(ResourceHeaderAllocation Allocation)
{
	return (TEXRESULT)((Allocation.Identifier != 0) ? Success : Failure);
}
TEXRESULT Object_Ref_Get_ElementAllocationValidity(ElementAllocation Allocation)
{
	return (TEXRESULT)((Allocation.Identifier != 0) ? Success : Failure);
}

TEXRESULT Object_Ref_Compare_ObjectAllocation(ObjectAllocation Allocation0, ObjectAllocation Allocation1)
{
	return (TEXRESULT)((((Allocation0.Pointer == Allocation1.Pointer) && (Allocation0.Identifier == Allocation1.Identifier))) ? Success : Failure);
}
TEXRESULT Object_Ref_Compare_ResourceHeaderAllocation(ResourceHeaderAllocation Allocation0, ResourceHeaderAllocation Allocation1)
{
	return (TEXRESULT)((((Allocation0.Pointer == Allocation1.Pointer) && (Allocation0.Identifier == Allocation1.Identifier))) ? Success : Failure);
}
TEXRESULT Object_Ref_Compare_ElementAllocation(ElementAllocation Allocation0, ElementAllocation Allocation1)
{
	return (TEXRESULT)((((Allocation0.Pointer == Allocation1.Pointer) && (Allocation0.Identifier == Allocation1.Identifier))) ? Success : Failure);
}

Object* Object_Ref_Get_ObjectPointer(ObjectAllocation Allocation)
{
	Object* (*function)(ObjectAllocation Allocation) =
		(Object * (*)(ObjectAllocation Allocation))ObjectsRes.pGet_ObjectPointer;

	return function(Allocation);
}
ResourceHeader* Object_Ref_Get_ResourceHeaderPointer(ResourceHeaderAllocation Allocation)
{
	ResourceHeader* (*function)(ResourceHeaderAllocation Allocation) =
		(ResourceHeader * (*)(ResourceHeaderAllocation Allocation))ObjectsRes.pGet_ResourceHeaderPointer;

	return function(Allocation);
}
Element* Object_Ref_Get_ElementPointer(ElementAllocation Allocation)
{
	Element* (*function)(ElementAllocation Allocation) =
		(Element * (*)(ElementAllocation Allocation))ObjectsRes.pGet_ElementPointer;

	return function(Allocation);
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

TEXRESULT Object_Ref_Resize_ObjectBuffer(ObjectBuffer* pBuffer, uint64_t NewSize)
{
	TEXRESULT(*function)(ObjectBuffer * pBuffer, uint64_t NewSize) =
		(TEXRESULT(*)(ObjectBuffer * pBuffer, uint64_t NewSize))ObjectsRes.pResize_ObjectBuffer;

	return function(pBuffer, NewSize);
}
TEXRESULT Object_Ref_Resize_ResourceHeaderBuffer(ResourceHeaderBuffer* pBuffer, uint64_t NewSize)
{
	TEXRESULT(*function)(ResourceHeaderBuffer * pBuffer, uint64_t NewSize) =
		(TEXRESULT(*)(ResourceHeaderBuffer * pBuffer, uint64_t NewSize))ObjectsRes.pResize_ResourceHeaderBuffer;

	return function(pBuffer, NewSize);
}
TEXRESULT Object_Ref_Resize_ElementBuffer(ElementBuffer* pBuffer, uint64_t NewSize)
{
	TEXRESULT(*function)(ElementBuffer * pBuffer, uint64_t NewSize) =
		(TEXRESULT(*)(ElementBuffer * pBuffer, uint64_t NewSize))ObjectsRes.pResize_ElementBuffer;

	return function(pBuffer, NewSize);
}

void Object_Ref_Destroy_ObjectBuffer(ObjectBuffer* pBuffer)
{
	void (*function)(ObjectBuffer * pBuffer) =
		(void (*)(ObjectBuffer * pBuffer))ObjectsRes.pDestroy_ObjectBuffer;

	function(pBuffer);
}
void Object_Ref_Destroy_ResourceHeaderBuffer(ResourceHeaderBuffer* pBuffer)
{
	void (*function)(ResourceHeaderBuffer * pBuffer) =
		(void (*)(ResourceHeaderBuffer * pBuffer))ObjectsRes.pDestroy_ResourceHeaderBuffer;

	function(pBuffer);
}
void Object_Ref_Destroy_ElementBuffer(ElementBuffer* pBuffer)
{
	void (*function)(ElementBuffer * pBuffer) =
		(void (*)(ElementBuffer * pBuffer))ObjectsRes.pDestroy_ElementBuffer;

	function(pBuffer);
}

TEXRESULT Object_Ref_CreateInstance_Object(ObjectAllocation Allocation, ObjectInstance* pReturn, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ObjectAllocation Allocation, ObjectInstance * pReturn, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ObjectAllocation Allocation, ObjectInstance * pReturn, uint32_t ThreadIndex))ObjectsRes.pCreateInstance_Object;
	return function(Allocation, pReturn, ThreadIndex);
}

TEXRESULT Object_Ref_CreateInstance_ResourceHeader(ResourceHeaderAllocation Allocation, ResourceHeaderInstance* pReturn, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ResourceHeaderAllocation Allocation, ResourceHeaderInstance * pReturn, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ResourceHeaderAllocation Allocation, ResourceHeaderInstance * pReturn, uint32_t ThreadIndex))ObjectsRes.pCreateInstance_ResourceHeader;
	return function(Allocation, pReturn, ThreadIndex);
}

TEXRESULT Object_Ref_CreateInstance_Element(ElementAllocation Allocation, ElementInstance* pReturn, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ElementAllocation Allocation, ElementInstance * pReturn, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ElementAllocation Allocation, ElementInstance * pReturn, uint32_t ThreadIndex))ObjectsRes.pCreateInstance_Element;
	return function(Allocation, pReturn, ThreadIndex);
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

void Object_Ref_Destroy_Object(ObjectAllocation Allocation, bool Full, uint32_t ThreadIndex)
{
	void (*function)(ObjectAllocation Allocation, bool Full, uint32_t ThreadIndex) =
		(void (*)(ObjectAllocation Allocation, bool Full, uint32_t ThreadIndex))ObjectsRes.pDestroy_Object;

	function(Allocation, Full, ThreadIndex);
}
void Object_Ref_Destroy_ResourceHeader(ResourceHeaderAllocation Allocation, bool Full, uint32_t ThreadIndex)
{
	void (*function)(ResourceHeaderAllocation Allocation, bool Full, uint32_t ThreadIndex) =
		(void (*)(ResourceHeaderAllocation Allocation, bool Full, uint32_t ThreadIndex))ObjectsRes.pDestroy_ResourceHeader;

	function(Allocation, Full, ThreadIndex);
}
void Object_Ref_Destroy_Element(ElementAllocation Allocation, bool Full, uint32_t ThreadIndex)
{
	void (*function)(ElementAllocation Allocation, bool Full, uint32_t ThreadIndex) =
		(void (*)(ElementAllocation Allocation, bool Full, uint32_t ThreadIndex))ObjectsRes.pDestroy_Element;

	function(Allocation, Full, ThreadIndex);
}

void Object_Ref_ReCreate_Object(ObjectAllocation Allocation, ObjectInstance* pInstance, uint32_t ThreadIndex)
{
	void (*function)(ObjectAllocation Allocation, ObjectInstance * pInstance, uint32_t ThreadIndex) =
		(void (*)(ObjectAllocation Allocation, ObjectInstance * pInstance, uint32_t ThreadIndex))ObjectsRes.pReCreate_Object;

	function(Allocation, pInstance, ThreadIndex);
}
void Object_Ref_ReCreate_ResourceHeader(ResourceHeaderAllocation Allocation, ResourceHeaderInstance* pInstance, uint32_t ThreadIndex)
{
	void (*function)(ResourceHeaderAllocation Allocation, ResourceHeaderInstance * pInstance, uint32_t ThreadIndex) =
		(void (*)(ResourceHeaderAllocation Allocation, ResourceHeaderInstance * pInstance, uint32_t ThreadIndex))ObjectsRes.pReCreate_ResourceHeader;

	function(Allocation, pInstance, ThreadIndex);
}
void Object_Ref_ReCreate_Element(ElementAllocation Allocation, ElementInstance* pInstance, uint32_t ThreadIndex)
{
	void (*function)(ElementAllocation Allocation, ElementInstance * pInstance, uint32_t ThreadIndex) =
		(void (*)(ElementAllocation Allocation, ElementInstance * pInstance, uint32_t ThreadIndex))ObjectsRes.pReCreate_Element;

	function(Allocation, pInstance, ThreadIndex);
}


TEXRESULT Object_Ref_StartThread_Object(ObjectAllocation Allocation, uint32_t ThreadIndex, Object** ppReturn)
{
	TEXRESULT(*function)(ObjectAllocation Allocation, uint32_t ThreadIndex, Object * *ppReturn) =
		(TEXRESULT(*)(ObjectAllocation Allocation, uint32_t ThreadIndex, Object * *ppReturn))ObjectsRes.pStartThread_Object;
	return function(Allocation, ThreadIndex, ppReturn);
}

TEXRESULT Object_Ref_StartThread_ResourceHeader(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex, ResourceHeader** ppReturn)
{
	TEXRESULT(*function)(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex, ResourceHeader * *ppReturn) =
		(TEXRESULT(*)(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex, ResourceHeader * *ppReturn))ObjectsRes.pStartThread_ResourceHeader;
	return function(Allocation, ThreadIndex, ppReturn);
}

TEXRESULT Object_Ref_StartThread_Element(ElementAllocation Allocation, uint32_t ThreadIndex, Element** ppReturn)
{
	TEXRESULT(*function)(ElementAllocation Allocation, uint32_t ThreadIndex, Element * *ppReturn) =
		(TEXRESULT(*)(ElementAllocation Allocation, uint32_t ThreadIndex, Element * *ppReturn))ObjectsRes.pStartThread_Element;
	return function(Allocation, ThreadIndex, ppReturn);
}

TEXRESULT Object_Ref_EndThread_Object(ObjectAllocation Allocation, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ObjectAllocation Allocation, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ObjectAllocation Allocation, uint32_t ThreadIndex))ObjectsRes.pEndThread_Object;
	return function(Allocation, ThreadIndex);
}

TEXRESULT Object_Ref_EndThread_ResourceHeader(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ResourceHeaderAllocation Allocation, uint32_t ThreadIndex))ObjectsRes.pEndThread_ResourceHeader;
	return function(Allocation, ThreadIndex);
}

TEXRESULT Object_Ref_EndThread_Element(ElementAllocation Allocation, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(ElementAllocation Allocation, uint32_t ThreadIndex) =
		(TEXRESULT(*)(ElementAllocation Allocation, uint32_t ThreadIndex))ObjectsRes.pEndThread_Element;
	return function(Allocation, ThreadIndex);
}



void Object_Ref_Add_ObjectChild(ObjectAllocation Allocation, ObjectAllocation Parent)
{
	void (*function)(ObjectAllocation Allocation, ObjectAllocation Parent) =
		(void (*)(ObjectAllocation Allocation, ObjectAllocation Parent))ObjectsRes.pAdd_ObjectChild;

	function(Allocation, Parent);
}
void Object_Ref_Add_Object_ResourceHeaderChild(ResourceHeaderAllocation Allocation, ObjectAllocation Parent)
{
	void (*function)(ResourceHeaderAllocation Allocation, ObjectAllocation Parent) =
		(void (*)(ResourceHeaderAllocation Allocation, ObjectAllocation Parent))ObjectsRes.pAdd_Object_ResourceHeaderChild;

	function(Allocation, Parent);
}
void Object_Ref_Add_ResourceHeader_ElementChild(ElementAllocation Allocation, ResourceHeaderAllocation Parent)
{
	void (*function)(ElementAllocation Allocation, ResourceHeaderAllocation Parent) =
		(void (*)(ElementAllocation Allocation, ResourceHeaderAllocation Parent))ObjectsRes.pAdd_ResourceHeader_ElementChild;

	function(Allocation, Parent);
}

void Object_Ref_Remove_ObjectChild(ObjectAllocation Allocation, ObjectAllocation Parent)
{
	void (*function)(ObjectAllocation Allocation, ObjectAllocation Parent) =
		(void (*)(ObjectAllocation Allocation, ObjectAllocation Parent))ObjectsRes.pRemove_ObjectChild;

	function(Allocation, Parent);
}
void Object_Ref_Remove_Object_ResourceHeaderChild(ResourceHeaderAllocation Allocation, ObjectAllocation Parent)
{
	void (*function)(ResourceHeaderAllocation Allocation, ObjectAllocation Parent) =
		(void (*)(ResourceHeaderAllocation Allocation, ObjectAllocation Parent))ObjectsRes.pRemove_Object_ResourceHeaderChild;

	function(Allocation, Parent);
}
void Object_Ref_Remove_ResourceHeader_ElementChild(ElementAllocation Allocation, ResourceHeaderAllocation Parent)
{
	void (*function)(ElementAllocation Allocation, ResourceHeaderAllocation Parent) =
		(void (*)(ElementAllocation Allocation, ResourceHeaderAllocation Parent))ObjectsRes.pRemove_ResourceHeader_ElementChild;

	function(Allocation, Parent);
}

void Object_Ref_Scan_ObjectChilds(ObjectAllocation Allocation, ObjectAllocation** pChilds, uint64_t* pChildsSize) //scans all recursive childs of a gameobject. Returns a array of childs
{
	void (*function)(ObjectAllocation Allocation, ObjectAllocation * *pChilds, uint64_t * pChildsSize) =
		(void (*)(ObjectAllocation Allocation, ObjectAllocation * *pChilds, uint64_t * pChildsSize))ObjectsRes.pScan_ObjectChilds;

	function(Allocation, pChilds, pChildsSize);
}
void Object_Ref_Scan_ObjectParents(ObjectAllocation Allocation, ObjectAllocation** pParents, uint64_t* pParentsSize) //scans all recursive parents of a gameobject. Returns a array of parents
{
	void (*function)(ObjectAllocation Allocation, ObjectAllocation * *pParents, uint64_t * pParentsSize) =
		(void (*)(ObjectAllocation Allocation, ObjectAllocation * *pParents, uint64_t * pParentsSize))ObjectsRes.pScan_ObjectParents;

	function(Allocation, pParents, pParentsSize);
}
void Object_Ref_Scan_ObjectHeaders(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, ResourceHeaderAllocation** pHeaders, uint64_t* pHeadersSize) //finds the requested header
{
	void (*function)(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, ResourceHeaderAllocation * *pHeaders, uint64_t * pHeadersSize) =
		(void (*)(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier, ResourceHeaderAllocation * *pHeaders, uint64_t * pHeadersSize))ObjectsRes.pScan_ObjectHeaders;

	function(Allocation, Identifier, pHeaders, pHeadersSize);
}
ResourceHeader* Object_Ref_Scan_ObjectHeadersSingle(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier) //finds the requested header
{
	ResourceHeader* (*function)(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier) =
		(ResourceHeader * (*)(ObjectAllocation Allocation, ResourceHeaderIdentifier Identifier))ObjectsRes.pScan_ObjectHeadersSingle;

	return function(Allocation, Identifier);
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

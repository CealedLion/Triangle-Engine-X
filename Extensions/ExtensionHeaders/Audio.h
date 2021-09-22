/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Standard Triangle Engine X Audio API.

SPECIFICATION:

 * set "TEX_EXPOSE_AUDIO" define to expose native if you are into that.


 * Utils can be imported. Audio::Utils

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once
#define TEX_AUDIO_API

#ifdef TEX_EXPOSE_AUDIO
#include <soundio/soundio.h>
#endif

/*
* Added in 1.0.0
* big endian is not actually supported so pls dont use.
*/
typedef enum AudioFormat {
	AudioFormat_Undefined,
	AudioFormat_int8,			///< Signed 8 bit
	AudioFormat_uint8,			///< Unsigned 8 bit
	AudioFormat_int16LE,		///< Signed 16 bit Little Endian
	AudioFormat_int16BE,		///< Signed 16 bit Big Endian
	AudioFormat_uint16LE,		///< Unsigned 16 bit Little Endian
	AudioFormat_uint16BE,		///< Unsigned 16 bit Little Endian
	AudioFormat_int24LE,		///< Signed 24 bit Little Endian using low three bytes in 32-bit word
	AudioFormat_int24BE,		///< Signed 24 bit Big Endian using low three bytes in 32-bit word
	AudioFormat_uint24LE,		///< Unsigned 24 bit Little Endian using low three bytes in 32-bit word
	AudioFormat_uint24BE,		///< Unsigned 24 bit Big Endian using low three bytes in 32-bit word
	AudioFormat_int32LE,		///< Signed 32 bit Little Endian
	AudioFormat_int32BE,		///< Signed 32 bit Big Endian
	AudioFormat_uint32LE,		///< Unsigned 32 bit Little Endian
	AudioFormat_uint32BE,		///< Unsigned 32 bit Big Endian
	AudioFormat_float32LE,		///< Float 32 bit Little Endian, Range -1.0 to 1.0
	AudioFormat_float32BE,		///< Float 32 bit Big Endian, Range -1.0 to 1.0
	AudioFormat_float64LE,		///< Float 64 bit Little Endian, Range -1.0 to 1.0
	AudioFormat_float64BE		///< Float 64 bit Big Endian, Range -1.0 to 1.0
}AudioFormat;
/*
* Added in 1.0.0
* amount of bits each channel in format is
* compressed are undefined
*/
const uint8_t AudioFormatBitsPerChannels[][4] = {
	{0, 0, 0, 0},		//UNDEFEIND
	{8, 0, 0, 0},		///< Signed 8 bit
	{8, 0, 0, 0},		///< Unsigned 8 bit
	{16, 0, 0, 0},		///< Signed 16 bit Little Endian
	{16, 0, 0, 0},		///< Signed 16 bit Big Endian
	{16, 0, 0, 0},		///< Unsigned 16 bit Little Endian
	{16, 0, 0, 0},		///< Unsigned 16 bit Little Endian
	{24, 0, 0, 0},		///< Signed 24 bit Little Endian using low three bytes in 32-bit word
	{24, 0, 0, 0},		///< Signed 24 bit Big Endian using low three bytes in 32-bit word
	{24, 0, 0, 0},		///< Unsigned 24 bit Little Endian using low three bytes in 32-bit word
	{24, 0, 0, 0},		///< Unsigned 24 bit Big Endian using low three bytes in 32-bit word
	{32, 0, 0, 0},		///< Signed 32 bit Little Endian
	{32, 0, 0, 0},		///< Signed 32 bit Big Endian
	{32, 0, 0, 0},		///< Unsigned 32 bit Little Endian
	{32, 0, 0, 0},		///< Unsigned 32 bit Big Endian
	{32, 0, 0, 0},		///< Float 32 bit Little Endian, Range -1.0 to 1.0
	{32, 0, 0, 0},		///< Float 32 bit Big Endian, Range -1.0 to 1.0
	{64, 0, 0, 0},		///< Float 64 bit Little Endian, Range -1.0 to 1.0
	{64, 0, 0, 0}		///< Float 64 bit Big Endian, Range -1.0 to 1.0
};
/*
* Added in 1.0.0
* ChannelIndentifiers format has
*/
const char AudioFormatChannelIndentifiers[][4] = {
	{'R', 0, 0, 0}, //UNDEFEIND
	{'R', 0, 0, 0},			///< Signed 8 bit
	{'R', 0, 0, 0},			///< Unsigned 8 bit
	{'R', 0, 0, 0},		///< Signed 16 bit Little Endian
	{'R', 0, 0, 0},		///< Signed 16 bit Big Endian
	{'R', 0, 0, 0},		///< Unsigned 16 bit Little Endian
	{'R', 0, 0, 0},		///< Unsigned 16 bit Little Endian
	{'R', 0, 0, 0},		///< Signed 24 bit Little Endian using low three bytes in 32-bit word
	{'R', 0, 0, 0},		///< Signed 24 bit Big Endian using low three bytes in 32-bit word
	{'R', 0, 0, 0},		///< Unsigned 24 bit Little Endian using low three bytes in 32-bit word
	{'R', 0, 0, 0},		///< Unsigned 24 bit Big Endian using low three bytes in 32-bit word
	{'R', 0, 0, 0},		///< Signed 32 bit Little Endian
	{'R', 0, 0, 0},		///< Signed 32 bit Big Endian
	{'R', 0, 0, 0},		///< Unsigned 32 bit Little Endian
	{'R', 0, 0, 0},		///< Unsigned 32 bit Big Endian
	{'R', 0, 0, 0},		///< Float 32 bit Little Endian, Range -1.0 to 1.0
	{'R', 0, 0, 0},		///< Float 32 bit Big Endian, Range -1.0 to 1.0
	{'R', 0, 0, 0},		///< Float 64 bit Little Endian, Range -1.0 to 1.0
	{'R', 0, 0, 0}		///< Float 64 bit Big Endian, Range -1.0 to 1.0
};
/*
* Added in 1.0.0
* amount of bit stride each format has
*/
const uint8_t AudioFormatStrides[] = {

	0, //UNDEFEIND
	8,			///< Signed 8 bit
	8,			///< Unsigned 8 bit
	16,		///< Signed 16 bit Little Endian
	16,		///< Signed 16 bit Big Endian
	16,		///< Unsigned 16 bit Little Endian
	16,		///< Unsigned 16 bit Little Endian
	24,		///< Signed 24 bit Little Endian using low three bytes in 32-bit word
	24,		///< Signed 24 bit Big Endian using low three bytes in 32-bit word
	24,		///< Unsigned 24 bit Little Endian using low three bytes in 32-bit word
	24,		///< Unsigned 24 bit Big Endian using low three bytes in 32-bit word
	32,		///< Signed 32 bit Little Endian
	32,		///< Signed 32 bit Big Endian
	32,		///< Unsigned 32 bit Little Endian
	32,		///< Unsigned 32 bit Big Endian
	32,		///< Float 32 bit Little Endian, Range -1.0 to 1.0
	32,		///< Float 32 bit Big Endian, Range -1.0 to 1.0
	64,		///< Float 64 bit Little Endian, Range -1.0 to 1.0
	64		///< Float 64 bit Big Endian, Range -1.0 to 1.0

};
/*
* Added in 1.0.0
* amount of components each format has
*/
const uint8_t AudioFormatChannelCounts[] = {
	0, //UNDEFEIND
	1,			///< Signed 8 bit
	1,			///< Unsigned 8 bit
	1,		///< Signed 16 bit Little Endian
	1,		///< Signed 16 bit Big Endian
	1,		///< Unsigned 16 bit Little Endian
	1,		///< Unsigned 16 bit Little Endian
	1,		///< Signed 24 bit Little Endian using low three bytes in 32-bit word
	1,		///< Signed 24 bit Big Endian using low three bytes in 32-bit word
	1,		///< Unsigned 24 bit Little Endian using low three bytes in 32-bit word
	1,		///< Unsigned 24 bit Big Endian using low three bytes in 32-bit word
	1,		///< Signed 32 bit Little Endian
	1,		///< Signed 32 bit Big Endian
	1,		///< Unsigned 32 bit Little Endian
	1,		///< Unsigned 32 bit Big Endian
	1,		///< Float 32 bit Little Endian, Range -1.0 to 1.0
	1,		///< Float 32 bit Big Endian, Range -1.0 to 1.0
	1,		///< Float 64 bit Little Endian, Range -1.0 to 1.0
	1		///< Float 64 bit Big Endian, Range -1.0 to 1.0
};
/*
* Added in 1.0.0
* datatype of each vkformat
*/
const DataType AudioFormatDataType[][4] = {

	{Undefined, Undefined, Undefined, Undefined}, //UNDEFEIND
	{SignedInt, Undefined, Undefined, Undefined},			///< Signed 8 bit
	{UnsignedInt, Undefined, Undefined, Undefined},			///< Unsigned 8 bit
	{SignedInt, Undefined, Undefined, Undefined},		///< Signed 16 bit Little Endian
	{SignedInt, Undefined, Undefined, Undefined},		///< Signed 16 bit Big Endian
	{UnsignedInt, Undefined, Undefined, Undefined},		///< Unsigned 16 bit Little Endian
	{UnsignedInt, Undefined, Undefined, Undefined},		///< Unsigned 16 bit Little Endian
	{SignedInt, Undefined, Undefined, Undefined},		///< Signed 24 bit Little Endian using low three bytes in 32-bit word
	{SignedInt, Undefined, Undefined, Undefined},		///< Signed 24 bit Big Endian using low three bytes in 32-bit word
	{UnsignedInt, Undefined, Undefined, Undefined},		///< Unsigned 24 bit Little Endian using low three bytes in 32-bit word
	{UnsignedInt, Undefined, Undefined, Undefined},		///< Unsigned 24 bit Big Endian using low three bytes in 32-bit word
	{SignedInt, Undefined, Undefined, Undefined},		///< Signed 32 bit Little Endian
	{SignedInt, Undefined, Undefined, Undefined},		///< Signed 32 bit Big Endian
	{UnsignedInt, Undefined, Undefined, Undefined},		///< Unsigned 32 bit Little Endian
	{UnsignedInt, Undefined, Undefined, Undefined},		///< Unsigned 32 bit Big Endian
	{SignedFloat, Undefined, Undefined, Undefined},		///< Float 32 bit Little Endian, Range -1.0 to 1.0
	{SignedFloat, Undefined, Undefined, Undefined},		///< Float 32 bit Big Endian, Range -1.0 to 1.0
	{SignedFloat, Undefined, Undefined, Undefined},		///< Float 64 bit Little Endian, Range -1.0 to 1.0
	{SignedFloat, Undefined, Undefined, Undefined}		///< Float 64 bit Big Endian, Range -1.0 to 1.0
};
/*
* Added in 1.0.0
*/
typedef enum AudioEffectsType
{
	AudioEffect_Undefined = 0,
	AudioEffect_Volume = 1,
	AudioEffect_Audio3D = 2
}AudioEffectsType;
/*
* Added in 1.0.0
* audio use enum from 2000
*/
typedef enum AudioElementType
{
	AudioElement_ElementAudio = 2000
}AudioElementType;
/*
* Added in 1.0.0
* audio use enum from 2000
*/
typedef enum AudioHeaderType
{
	AudioHeader_AudioSource = 2000
}AudioHeaderType;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Flags
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
*/
typedef enum AudioElementUsageFlags {
	AudioElementUsage_Playback = 0x00000001,
	AudioElementUsage_Recording = 0x00000002,
}AudioElementUsageFlags;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Structs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef uint64_t AudioEffectBufferIndex;
typedef uint32_t AudioEffectIdentifier;
/*
* Added in 1.0.0
*/
typedef struct TEXA_HEADER {
	uint64_t LinearSize; //size of data in bytes //required
	uint32_t ChannelCount; //required
	uint32_t SampleRate; //required 44100 is popular
	uint32_t ByteRate; //SampleRate * channels * (BitsPerSample / 8)
	uint32_t BlockAlign; //channels * (BitsPerSample / 8)

	uint64_t FrameCount; //amount of frames in the file = linearSize / ((BitsPerSample / 8) * channels) //required

	AudioFormat Format; //required
	//FormatDetails formatDetails;
	unsigned char Data[]; //null terminated //required
}TEXA_HEADER;
/*
* Added in 1.0.0
* converter template
*/
typedef TEXRESULT(ConvertXtoTEXA)(FileData*, TEXA_HEADER**);
/*
* Added in 1.0.0
* converter template
*/
typedef TEXRESULT(ConvertTEXAtoX)(TEXA_HEADER*, FileData*);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ResourceHeaders
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
*/
typedef struct RHeaderAudioSourceCreateInfo {
	TEXA_HEADER* AudioData;
}RHeaderAudioSourceCreateInfo;
typedef struct RHeaderAudioSource{
	ResourceHeaderTEMPLATE Header;
	//custom
	TEXA_HEADER* AudioData;
}RHeaderAudioSource;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Elements
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
*/
typedef struct ElementAudioCreateInfoEffect
{
	AudioEffectIdentifier Identifier;
	void* pEffectCreateInfo; //pointer to an effect create info of the corrosponding identifier.
}ElementAudioCreateInfoEffect;
/*
* Added in 1.0.0
*/
typedef struct ElementAudioCreateInfo {
	ResourceHeaderAllocation iAudioSource; //required

	AudioElementUsageFlags UsageFlags; //specifies desired usage.

	uint64_t RingBufferSize_Seconds; //optional
	uint64_t StartFrame; //optional

	uint64_t EffectCreateInfosSize;
	ElementAudioCreateInfoEffect* EffectCreateInfos;
}ElementAudioCreateInfo;
typedef struct ElementAudio {
	ElementTEMPLATE Header;

	ResourceHeaderAllocation iAudioSource;

	AudioElementUsageFlags UsageFlags;

	uint64_t RingBufferSize_Seconds;
	uint64_t CurrentFrame;

	//per init
	double LastTime;

#ifdef TEX_EXPOSE_AUDIO
	struct SoundIoOutStream* OutStream;
	struct SoundIoInStream* InStream;
	struct SoundIoDevice* OutDevice;
	struct SoundIoDevice* InDevice;
	struct SoundIoRingBuffer* RingBuffer;
#else
	void* OutStream;
	void* InStream;
	void* OutDevice;
	void* InDevice;
	void* RingBuffer;
#endif

	uint64_t EffectsSize; //size in effects
	uint8_t Effects[]; //raw data array / struct extension
}ElementAudio;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef TEXRESULT(Create_AudioEffectTemplate)(ElementAudio* pElement, void* pEffect, const void* pEffectCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex);
typedef TEXRESULT(Destroy_AudioEffectTemplate)(ElementAudio* pElement, ElementAudio* pElementOverlay, void* pEffect, void* pEffectOverlay, bool Full, uint32_t ThreadIndex);

typedef TEXRESULT(ReCreate_AudioEffectTemplate)(ElementAudio* pElement, void* pEffect, uint32_t ThreadIndex);

typedef TEXRESULT(Pack_AudioEffectTemplate)(const ElementAudio* pElement, ElementAudio* pCopiedElement, const void* pEffect, void* pCopiedEffect, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex);
typedef TEXRESULT(UnPack_AudioEffectTemplate)(const ElementAudio* pElement, ElementAudio* pCopiedElement, const void* pEffect, void* pCopiedEffect, const void* pData, uint32_t ThreadIndex);


struct AudioEffectSignature;

typedef void(UpdateSignature_AudioEffectTemplate)(struct AudioEffectSignature* pSignature, uint32_t ThreadIndex);

typedef void(Draw_AudioEffectTemplate)(ElementAudio* pElement, ResourceHeader* pHeader, Object* pGameObject,
	void* pEffect, uint32_t FrameCountMin, uint32_t FrameCountMax, AudioElementUsageFlags Usage, uint32_t ThreadIndex);

/*
* Added in 1.0.0
*/
typedef struct AudioEffectSignature {
	AudioEffectIdentifier Identifier;

	Create_AudioEffectTemplate* Constructor; //required
	Destroy_AudioEffectTemplate* Destructor; //required
	ReCreate_AudioEffectTemplate* ReConstructor; //optional
	Pack_AudioEffectTemplate* Packer; //required
	UnPack_AudioEffectTemplate* UnPacker; //required

	Draw_AudioEffectTemplate* Draw; //required

	UpdateSignature_AudioEffectTemplate* UpdateSignature; //before rendering 1 update for updating buffers descriptors etc. after element update loop //required
}AudioEffectSignature;
/*
* Added in 1.0.0
*/
typedef struct AudioEffectTemplate {
	AudioEffectIdentifier Identifier; //required
	uint64_t AllocationSize; //size of the full struct
}AudioEffectTemplate;
/*
* Added in 1.0.0
*/
typedef struct AudioEffect {
	AudioEffectTemplate Header; //required
}AudioEffect;
/*
* Added in 1.0.0
*/
typedef struct AudioEffectCreateInfoVolume {
	double Volume;  // recommended to be 0 - 1.0
}AudioEffectCreateInfoVolume;
typedef struct AudioEffectVolume {
	AudioEffectTemplate Header; //required
	double Volume;  // recommended to be 0 - 1.0
}AudioEffectVolume;
/*
* Added in 1.0.0
*/
typedef struct AudioEffectCreateInfoAudio3D {
	float Position;
}AudioEffectCreateInfoAudio3D;
typedef struct AudioEffectAudio3D {
	AudioEffectTemplate Header; //required
	float Position;
}AudioEffectAudio3D;



typedef struct ConverterXtoTEXA
{
	ConvertXtoTEXA* pFunction;
	uint32_t Identifier;
}ConverterXtoTEXA;
typedef struct ConverterTEXAtoX
{
	ConvertTEXAtoX* pFunction;
	uint32_t Identifier;
}ConverterTEXAtoX;
typedef struct AudioUtils {

	struct {
		uint64_t pad;
	}Config;

#ifdef TEX_EXPOSE_AUDIO
	struct SoundIo* AudioHandle;
#else
	void* AudioHandle;
#endif

	//Signatures
	ResourceHeaderSignature RHeaderAudioSourceSig;
	ElementSignature ElementAudioSig;

	//Effects
	AudioEffectSignature VolumeSig;
	AudioEffectSignature Audio3DSig;

	//Internal
	ConverterXtoTEXA* ConvertersToTEXA;
	uint64_t ConvertersToTEXASize;
	Mutex ConvertersToTEXAMutex;

	ConverterTEXAtoX* ConvertersFromTEXA;
	uint64_t ConvertersFromTEXASize;
	Mutex ConvertersFromTEXAMutex;

	AudioEffectSignature** AudioEffectSignatures;
	uint64_t AudioEffectSignaturesSize;
	Mutex AudioEffectSignaturesMutex;

}AudioUtils;


struct AudioResStruct {
	AudioUtils* pUtils;

	void* pInitialise_Audio;
	void* pDestroy_Audio;
	void* pUpdate_Audio;

	void* pAdd_XtoTEXAconverter;
	void* pAdd_TEXAtoXconverter;
	void* pRemove_XtoTEXAconverter;
	void* pRemove_TEXAtoXconverter;
	void* pXtoTEXA;
	void* pTEXAtoX;

	void* pRegister_AudioEffectSignature;
	void* pDeRegister_AudioEffectSignature;
	void* pFind_AudioEffectSignature;
	void* pGet_AudioEffect;

	void* pGet_FormatDetails;

	void* pStart_InputStream;
	void* pStart_OutputStream;

	void* pPause_InputStream;
	void* pPause_OutputStream;

	void* pConvert_AudioData;

	void* pCreate_DummyTEXA;

}AudioRes;

//Initialise_Resources MUST be called to use the library in your dll
void Audio_Initialise_Resources(FunctionInfo*** pExternFunctions, uint64_t* pExternFunctionsSize, ResourceInfo*** pExternResources, uint64_t* pExternResourcesSize) {
	memset(&AudioRes, 0, sizeof(AudioRes));

	ResourceImport(pExternResources, pExternResourcesSize, (const UTF8*)CopyData((void*)"Audio::Utils"), &AudioRes.pUtils);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Convert::Add_XtoTEXAconverter"), &AudioRes.pAdd_XtoTEXAconverter);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Convert::Add_TEXAtoXconverter"), &AudioRes.pAdd_TEXAtoXconverter);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Convert::Remove_XtoTEXAconverter"), &AudioRes.pRemove_XtoTEXAconverter);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Convert::Remove_TEXAtoXconverter"), &AudioRes.pRemove_TEXAtoXconverter);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Convert::XtoTEXA"), &AudioRes.pXtoTEXA);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Convert::TEXAtoX"), &AudioRes.pTEXAtoX);


	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Effects::Register_AudioEffectSignature"), &AudioRes.pRegister_AudioEffectSignature);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Effects::DeRegister_AudioEffectSignature"), &AudioRes.pDeRegister_AudioEffectSignature);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Effects::Find_AudioEffectSignature"), &AudioRes.pFind_AudioEffectSignature);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Effects::Get_AudioEffect"), &AudioRes.pGet_AudioEffect);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Get_FormatDetails"), &AudioRes.pGet_FormatDetails);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Start_InputStream"), &AudioRes.pStart_InputStream);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Start_OutputStream"), &AudioRes.pStart_OutputStream);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Pause_InputStream"), &AudioRes.pPause_InputStream);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Pause_OutputStream"), &AudioRes.pPause_OutputStream);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Convert_AudioData"), &AudioRes.pConvert_AudioData);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Audio::Create_DummyTEXA"), &AudioRes.pCreate_DummyTEXA);


}

TEXRESULT Audio_Convert_Ref_Add_XtoTEXAconverter(ConvertXtoTEXA* Converter, uint32_t Identifier)
{
	TEXRESULT(*function)(ConvertXtoTEXA * Converter, uint32_t Identifier) =
		(TEXRESULT(*)(ConvertXtoTEXA * Converter, uint32_t Identifier))AudioRes.pAdd_XtoTEXAconverter;

	return function(Converter, Identifier);
}

TEXRESULT Audio_Convert_Ref_Add_TEXAtoXconverter(ConvertTEXAtoX* Converter, uint32_t Identifier)
{
	TEXRESULT(*function)(ConvertTEXAtoX * Converter, uint32_t Identifier) =
		(TEXRESULT(*)(ConvertTEXAtoX * Converter, uint32_t Identifier))AudioRes.pAdd_TEXAtoXconverter;

	return function(Converter, Identifier);
}

TEXRESULT Audio_Convert_Ref_Remove_XtoTEXAconverter(uint32_t Identifier)
{
	TEXRESULT(*function)(uint32_t Identifier) =
		(TEXRESULT(*)(uint32_t Identifier))AudioRes.pRemove_XtoTEXAconverter;

	return function(Identifier);
}

TEXRESULT Audio_Convert_Ref_Remove_TEXAtoXconverter(uint32_t Identifier)
{
	TEXRESULT(*function)(uint32_t Identifier) =
		(TEXRESULT(*)(uint32_t Identifier))AudioRes.pRemove_TEXAtoXconverter;

	return  function(Identifier);
}

TEXRESULT Audio_Convert_Ref_XtoTEXA(FileData* src, TEXA_HEADER** dst, uint32_t Identifier)
{
	TEXRESULT(*function)(FileData * src, TEXA_HEADER * *dst, uint32_t Identifier) =
		(TEXRESULT(*)(FileData * src, TEXA_HEADER * *dst, uint32_t Identifier))AudioRes.pXtoTEXA;

	return function(src, dst, Identifier);
}

TEXRESULT Audio_Convert_Ref_TEXAtoX(TEXA_HEADER* src, FileData* dst, uint32_t Identifier)
{
	TEXRESULT(*function)(TEXA_HEADER * src, FileData* dst, uint32_t Identifier) =
		(TEXRESULT(*)(TEXA_HEADER * src, FileData* dst, uint32_t Identifier))AudioRes.pTEXAtoX;

	return function(src, dst, Identifier);
}




TEXRESULT Audio_Effects_Ref_Register_AudioEffectSignature(AudioEffectSignature* pSignature)
{
	TEXRESULT(*function)(AudioEffectSignature * pSignature) =
		(TEXRESULT(*)(AudioEffectSignature * pSignature))AudioRes.pRegister_AudioEffectSignature;

	return function(pSignature);
}

TEXRESULT Audio_Effects_Ref_DeRegister_AudioEffectSignature(AudioEffectSignature* pSignature)
{
	TEXRESULT(*function)(AudioEffectSignature * pSignature) =
		(TEXRESULT(*)(AudioEffectSignature * pSignature))AudioRes.pDeRegister_AudioEffectSignature;

	return function(pSignature);
}

TEXRESULT Audio_Effects_Ref_Find_AudioEffectSignature(AudioEffectIdentifier Identifier, AudioEffectSignature** ppSignature, AudioEffectBufferIndex* pBufferIndex)
{
	TEXRESULT(*function)(AudioEffectIdentifier Identifier, AudioEffectSignature * *ppSignature, AudioEffectBufferIndex * pBufferIndex) =
		(TEXRESULT(*)(AudioEffectIdentifier Identifier, AudioEffectSignature * *ppSignature, AudioEffectBufferIndex * pBufferIndex))AudioRes.pFind_AudioEffectSignature;

	return function(Identifier, ppSignature, pBufferIndex);
}

TEXRESULT Audio_Effects_Ref_Get_AudioEffect(ElementAudio* pElement, ElementType Type, uint32_t Identifier, void** pReturnEffect)
{
	TEXRESULT(*function)(ElementAudio * pElement, ElementType Type, uint32_t Identifier, void** pReturnEffect) =
		(TEXRESULT(*)(ElementAudio * pElement, ElementType Type, uint32_t Identifier, void** pReturnEffect))AudioRes.pGet_AudioEffect;

	return function(pElement, Type, Identifier, pReturnEffect);
}





FormatDetails Audio_Ref_Get_FormatDetails(AudioFormat format)
{
	FormatDetails(*function)(AudioFormat format) =
		(FormatDetails(*)(AudioFormat format))AudioRes.pGet_FormatDetails;

	return function(format);
}

void Audio_Ref_Start_InputStream(ElementAudio* pElement)
{
	void (*function)(ElementAudio * pElement) =
		(void (*)(ElementAudio * pElement))AudioRes.pStart_InputStream;

	function(pElement);
}

void Audio_Ref_Start_OutputStream(ElementAudio* pElement)
{
	void (*function)(ElementAudio * pElement) =
		(void (*)(ElementAudio * pElement))AudioRes.pStart_OutputStream;

	function(pElement);
}

void Audio_Ref_Pause_InputStream(ElementAudio* pElement, bool pause)
{
	void (*function)(ElementAudio * pElement, bool pause) =
		(void (*)(ElementAudio * pElement, bool pause))AudioRes.pPause_InputStream;

	function(pElement, pause);
}

void Audio_Ref_Pause_OutputStream(ElementAudio* pElement, bool pause)
{
	void (*function)(ElementAudio * pElement, bool pause) =
		(void (*)(ElementAudio * pElement, bool pause))AudioRes.pPause_OutputStream;

	function(pElement, pause);
}

TEXRESULT Audio_Ref_Convert_AudioData(TEXA_HEADER* src, TEXA_HEADER** dst, AudioFormat dstformat)
{
	TEXRESULT(*function)(TEXA_HEADER * src, TEXA_HEADER * *dst, AudioFormat dstformat) =
		(TEXRESULT(*)(TEXA_HEADER * src, TEXA_HEADER * *dst, AudioFormat dstformat))AudioRes.pConvert_AudioData;

	return function(src, dst, dstformat);
}

TEXRESULT Audio_Ref_Create_DummyTEXA(TEXA_HEADER** pDst, AudioFormat Format, uint32_t SampleRate, uint32_t ChannelCount,
	uint32_t ByteRate, uint32_t BlockAlign, uint64_t FrameCount, uint64_t InitialSize)
{
	TEXRESULT(*function)(TEXA_HEADER * *pDst, AudioFormat Format, uint32_t SampleRate, uint32_t ChannelCount,
		uint32_t ByteRate, uint32_t BlockAlign, uint64_t FrameCount, uint64_t InitialSize) =
		(TEXRESULT(*)(TEXA_HEADER * *pDst, AudioFormat Format, uint32_t SampleRate, uint32_t ChannelCount,
			uint32_t ByteRate, uint32_t BlockAlign, uint64_t FrameCount, uint64_t InitialSize))AudioRes.pCreate_DummyTEXA;

	return function(pDst, Format, SampleRate, ChannelCount, ByteRate, BlockAlign, FrameCount, InitialSize);
}




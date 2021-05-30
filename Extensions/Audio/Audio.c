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
//ours
#include "Extension.h"
#include "Object.h"
#define TEX_EXPOSE_AUDIO
#include "Audio.h"


volatile struct{
	uint64_t InitialElementsMax;
	uint64_t InitialHeadersMax;
}Config;

volatile AudioUtils Utils;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Converters
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//common with graphics
TEXRESULT Add_XtoTEXAconverter(ConvertXtoTEXA* Converter, uint32_t Identifier)
{
#ifndef NDEBUG
	if (Converter == NULL)
	{
		Engine_Ref_ArgsError("Add_XtoTEXAconverter()", "Converter == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Add_XtoTEXAconverter()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ConvertersToTEXAMutex);
	Resize_Array((void**)&Utils.ConvertersToTEXA, Utils.ConvertersToTEXASize, Utils.ConvertersToTEXASize + 1, sizeof(*Utils.ConvertersToTEXA));
	Utils.ConvertersToTEXA[Utils.ConvertersToTEXASize].pFunction = Converter;
	Utils.ConvertersToTEXA[Utils.ConvertersToTEXASize].Identifier = Identifier;
	Utils.ConvertersToTEXASize++;
	Engine_Ref_Unlock_Mutex(Utils.ConvertersToTEXAMutex);
	return (TEXRESULT)(Success);
}

TEXRESULT Add_TEXAtoXconverter(ConvertTEXAtoX* Converter, uint32_t Identifier)
{
#ifndef NDEBUG
	if (Converter == NULL)
	{
		Engine_Ref_ArgsError("Add_TEXAtoXconverter()", "Converter == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Add_TEXAtoXconverter()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ConvertersFromTEXAMutex);
	Resize_Array((void**)&Utils.ConvertersFromTEXA, Utils.ConvertersFromTEXASize, Utils.ConvertersFromTEXASize + 1, sizeof(*Utils.ConvertersFromTEXA));
	Utils.ConvertersFromTEXA[Utils.ConvertersFromTEXASize].pFunction = Converter;
	Utils.ConvertersFromTEXA[Utils.ConvertersFromTEXASize].Identifier = Identifier;
	Utils.ConvertersFromTEXASize++;
	Engine_Ref_Unlock_Mutex(Utils.ConvertersFromTEXAMutex);
	return (TEXRESULT)(Success);
}

TEXRESULT Remove_XtoTEXAconverter(uint32_t Identifier)
{
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Remove_XtoTEXAconverter()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ConvertersToTEXAMutex);
	for (size_t i = 0; i < Utils.ConvertersToTEXASize; i++)
	{
		if (Identifier == Utils.ConvertersToTEXA[i].Identifier)
		{
			RemoveMember_Array((void**)&Utils.ConvertersToTEXA, Utils.ConvertersToTEXASize, i, sizeof(*Utils.ConvertersToTEXA) , 1);
			Utils.ConvertersToTEXASize--;
			Engine_Ref_Unlock_Mutex(Utils.ConvertersToTEXAMutex);
			return (TEXRESULT)(Success);
		}
	}
	Engine_Ref_ArgsError("Remove_XtoTEXAconverter()", "Identifier Invalid.");
	Engine_Ref_Unlock_Mutex(Utils.ConvertersToTEXAMutex);
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

TEXRESULT Remove_TEXAtoXconverter(uint32_t Identifier)
{
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Remove_TEXAtoXconverter()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.ConvertersFromTEXAMutex);
	for (size_t i = 0; i < Utils.ConvertersFromTEXASize; i++)
	{
		if (Identifier == Utils.ConvertersFromTEXA[i].Identifier)
		{
			RemoveMember_Array((void**)&Utils.ConvertersFromTEXA, Utils.ConvertersFromTEXASize, i, sizeof(*Utils.ConvertersFromTEXA), 1);
			Utils.ConvertersFromTEXASize--;
			Engine_Ref_Unlock_Mutex(Utils.ConvertersFromTEXAMutex);
			return (TEXRESULT)(Success);
		}
	}
	Engine_Ref_ArgsError("Remove_TEXAtoXconverter()", "Identifier Invalid.");
	Engine_Ref_Unlock_Mutex(Utils.ConvertersFromTEXAMutex);
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

TEXRESULT XtoTEXA(FileData* Src, TEXA_HEADER** Dst, uint32_t Identifier) //converts all supported formats to TEXI 
{
#ifndef NDEBUG
	if (Src == NULL)
	{
		Engine_Ref_ArgsError("XtoTEXA()", "Src == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Dst == NULL)
	{
		Engine_Ref_ArgsError("XtoTEXA()", "Dst == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("XtoTEXA()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < Utils.ConvertersToTEXASize; i++)
	{
		if (Identifier == Utils.ConvertersToTEXA[i].Identifier)
		{
			ConvertXtoTEXA* conv = *Utils.ConvertersToTEXA[i].pFunction;
			return conv(Src, Dst);
		}
	}
	Engine_Ref_ArgsError("XtoTEXA()", "Identifier Invalid.");
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

TEXRESULT TEXAtoX(TEXA_HEADER* Src, FileData* Dst, uint32_t Identifier) //converts all supported formats from texi 
{
#ifndef NDEBUG
	if (Src == NULL)
	{
		Engine_Ref_ArgsError("TEXAtoX()", "Src == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Dst == NULL)
	{
		Engine_Ref_ArgsError("TEXAtoX()", "Dst == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("TEXAtoX()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < Utils.ConvertersFromTEXASize; i++)
	{
		if (Identifier == Utils.ConvertersFromTEXA[i].Identifier)
		{
			ConvertTEXAtoX* conv = *Utils.ConvertersFromTEXA[i].pFunction;
			return conv(Src, Dst);
		}
	}
	Engine_Ref_ArgsError("TEXAtoX()", "Identifier Invalid.");
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//common with graphics
TEXRESULT Register_AudioEffectSignature(AudioEffectSignature* pSignature)
{
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("Register_AudioEffectSignature()", "pSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif 
	Engine_Ref_Lock_Mutex(Utils.AudioEffectSignaturesMutex);
	for (size_t i = 0; i < Utils.AudioEffectSignaturesSize; i++)
	{
		if (Utils.AudioEffectSignatures[i]->Identifier == pSignature->Identifier)
		{
			Engine_Ref_ArgsError("Register_AudioEffectSignature()", "Signature->Identifier Already Used.");
			Engine_Ref_Unlock_Mutex(Utils.AudioEffectSignaturesMutex);
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
	}

	Resize_Array((void**)&Utils.AudioEffectSignatures, Utils.AudioEffectSignaturesSize, Utils.AudioEffectSignaturesSize + 1, sizeof(*Utils.AudioEffectSignatures));
	Utils.AudioEffectSignatures[Utils.AudioEffectSignaturesSize] = pSignature;
	Utils.AudioEffectSignaturesSize += 1;
	Engine_Ref_Unlock_Mutex(Utils.AudioEffectSignaturesMutex);
	return (TEXRESULT)(Success);
}

TEXRESULT DeRegister_AudioEffectSignature(AudioEffectSignature* pSignature)
{
#ifndef NDEBUG
	if (pSignature == NULL)
	{
		Engine_Ref_ArgsError("DeRegister_AudioEffectSignature()", "pSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	Engine_Ref_Lock_Mutex(Utils.AudioEffectSignaturesMutex);
	for (size_t i = 0; i < Utils.AudioEffectSignaturesSize; i++)
	{
		if ((uint64_t)Utils.AudioEffectSignatures[i]->Identifier == (uint64_t)pSignature->Identifier)
		{
			RemoveMember_Array((void**)&Utils.AudioEffectSignatures, Utils.AudioEffectSignaturesSize, i, sizeof(*Utils.AudioEffectSignatures), 1);
			Utils.AudioEffectSignaturesSize -= 1;
			Engine_Ref_Unlock_Mutex(Utils.AudioEffectSignaturesMutex);
			return (TEXRESULT)(Success);
		}
	}
	Engine_Ref_ArgsError("DeRegister_AudioEffectSignature()", "pSignature Not Found.");
	Engine_Ref_Unlock_Mutex(Utils.AudioEffectSignaturesMutex);
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

TEXRESULT Find_AudioEffectSignature(AudioEffectIdentifier Identifier, AudioEffectSignature** ppSignature, AudioEffectBufferIndex* pBufferIndex)
{
#ifndef NDEBUG
	if (Identifier == NULL)
	{
		Engine_Ref_ArgsError("Find_AudioEffectSignature()", "Identifier == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (ppSignature == NULL)
	{
		Engine_Ref_ArgsError("Find_AudioEffectSignature()", "ppSignature == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	for (size_t i = 0; i < Utils.AudioEffectSignaturesSize; i++)
	{
		if (Utils.AudioEffectSignatures[i]->Identifier == Identifier)
		{
			if (ppSignature != NULL)
				*ppSignature = Utils.AudioEffectSignatures[i];
			if (pBufferIndex != NULL)
				*pBufferIndex = i;
			return (TEXRESULT)(Success);
		}
	}
	Engine_Ref_ArgsError("Find_AudioEffectSignature()", "Identifier Invalid");
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

TEXRESULT Get_AudioEffect(ElementAudio* pElement, AudioEffectIdentifier Identifier, void** pReturnEffect)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("Get_AudioEffect()", "pElement == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (pReturnEffect == NULL)
	{
		Engine_Ref_ArgsError("Get_AudioEffect()", "pReturnEffect == NULLPTR");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif
	uint64_t pointer = 0;
	for (size_t i2 = 0; i2 < pElement->EffectsSize; i2++)
	{
		AudioEffect* pEffect = (AudioEffect*)((void*)((uint64_t)pElement->Effects + pointer));
		if (pEffect->Header.Identifier == Identifier)
		{
			*pReturnEffect = pEffect;
			return (TEXRESULT)(Success);
		}
		pointer += pEffect->Header.AllocationSize;
	}
	Engine_Ref_ArgsError("Get_AudioEffect()", "Effect Not Found.");
	return (TEXRESULT)(Invalid_Parameter | Failure);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Misc
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FormatDetails Get_FormatDetails(AudioFormat format)
{
	FormatDetails details;
	memset(&details, 0, sizeof(details));

	details.ChannelCount = AudioFormatChannelCounts[(uint32_t)format];
	details.Stride = AudioFormatStrides[(uint32_t)format];

	details.ChannelTypes = (DataType*)AudioFormatDataType[(uint32_t)format];
	details.ChannelNames = (char*)AudioFormatChannelIndentifiers[(uint32_t)format];
	details.BitsPerChannel = (uint8_t*)AudioFormatBitsPerChannels[(uint32_t)format];
	return details;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Draw
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Draw_ElementAudio(ElementAudio* pElement, uint32_t FrameCountMin, uint32_t FrameCountMax, AudioElementUsageFlags Usage) {
	for (size_t i0 = 0; i0 < pElement->Header.iParentsSize; i0++)
	{
		ResourceHeader* pParentHeader = Object_Ref_Get_ResourceHeaderPointer(pElement->Header.iParents[i0]);
		for (size_t i1 = 0; i1 < pParentHeader->Header.iParentsSize; i1++)
		{
			Object* pObject = Object_Ref_Get_ObjectPointer(pParentHeader->Header.iParents[i1]);
			uint64_t pointer = 0;
			for (size_t i3 = 0; i3 < pElement->EffectsSize; i3++)
			{
				AudioEffect* pEffect = (AudioEffect*)((void*)((uint64_t)pElement->Effects + pointer));
				AudioEffectSignature* pSignature = NULL;
				AudioEffectBufferIndex BufferIndex = NULL;
				Find_AudioEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
				if (pSignature->Draw != NULL)
				{
					pSignature->Draw(pElement, pParentHeader, pObject, pEffect, FrameCountMin, FrameCountMax,Usage);
				}
				pointer += pEffect->Header.AllocationSize;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//soundio callback callback
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void write_callback(struct SoundIoOutStream* outStream, int frame_count_min, int frame_count_max)
{
	ElementAudio* pElement = (ElementAudio*)Object_Ref_Get_ElementPointer(*((ElementAllocation*)outStream->userdata));
	Draw_ElementAudio(pElement, frame_count_min, frame_count_max, AudioElementUsage_Playback);
}
static void underflow_callback(struct SoundIoOutStream* inStream)
{
#ifndef NDEBUG
	static int count = 0;
	//fprintf(stderr, "underflow %d\n", ++count);
	//printf("underflow %d\n", count);
#endif
}

static void read_callback(struct SoundIoInStream* inStream, int frame_count_min, int frame_count_max)
{
	ElementAudio* pElement = (ElementAudio*)Object_Ref_Get_ElementPointer(*((ElementAllocation*)inStream->userdata));
	Draw_ElementAudio(pElement, frame_count_min, frame_count_max, AudioElementUsage_Recording);
}
static void overflow_callback(struct SoundIoInStream* inStream)
{
#ifndef NDEBUG
	static int count = 0;
	//fprintf(stderr, "overflow %d\n", ++count);
	//printf("overflow %d\n", count);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Stream
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Start_InputStream(ElementAudio* pElement)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("Start_InputStream()", "pElement == NULLPTR");
		return;
	}
	if (pElement->OutStream == NULL)
	{
		Engine_Ref_ArgsError("Start_InputStream()", "pElement->InStream == NULLPTR");
		return;
	}
	if (!(pElement->UsageFlags & AudioElementUsage_Recording))
	{
		Engine_Ref_ArgsError("Start_InputStream()", "pElement->UsageFlags Dont Mention AudioElementUsage_Recording.");
	}
#endif
	soundio_instream_start(pElement->InStream);
}

void Start_OutputStream(ElementAudio* pElement)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("Start_OutputStream()", "pElement == NULLPTR");
		return;
	}
	if (pElement->OutStream == NULL)
	{
		Engine_Ref_ArgsError("Start_OutputStream()", "pElement->OutStream == NULLPTR");
		return;
	}
	if (!(pElement->UsageFlags & AudioElementUsage_Playback))
	{
		Engine_Ref_ArgsError("Start_OutputStream()", "pElement->UsageFlags Dont Mention AudioElementUsage_Playback.");
	}
#endif
	soundio_outstream_start(pElement->OutStream);
}

void Pause_InputStream(ElementAudio* pElement, bool pause)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("Pause_InputStream()", "pElement == NULLPTR");
		return;
	}
	if (pElement->OutStream == NULL)
	{
		Engine_Ref_ArgsError("Pause_InputStream()", "pElement->InStream == NULLPTR");
		return;
	}
	if (!(pElement->UsageFlags & AudioElementUsage_Recording))
	{
		Engine_Ref_ArgsError("Pause_InputStream()", "pElement->UsageFlags Dont Mention AudioElementUsage_Recording.");
	}
#endif
	soundio_instream_pause(pElement->InStream, pause);
}

void Pause_OutputStream(ElementAudio* pElement, bool pause)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("Pause_OutputStream()", "pElement == NULLPTR");
		return;
	}
	if (pElement->OutStream == NULL)
	{
		Engine_Ref_ArgsError("Pause_OutputStream()", "pElement->OutStream == NULLPTR");
		return;
	}
	if (!(pElement->UsageFlags & AudioElementUsage_Playback))
	{
		Engine_Ref_ArgsError("Pause_OutputStream()", "pElement->UsageFlags Dont Mention AudioElementUsage_Playback.");
	}
#endif
	soundio_outstream_pause(pElement->OutStream, pause);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Convert
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Convert_AudioData(TEXA_HEADER** src, AudioFormat dstformat) //do floating point in future
{
#ifndef NDEBUG
	if ((uint32_t)dstformat == NULL)
	{
		Engine_Ref_ArgsError("Convert_AudioData()", "dstformat == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	if (src == NULL)
	{
		Engine_Ref_ArgsError("Convert_AudioData()", "src == NULL");
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
#endif

	TEXA_HEADER* psrc = *src;

	FormatDetails srcdetails = Get_FormatDetails(psrc->Format);
	FormatDetails dstdetails = Get_FormatDetails(dstformat);

	FileData filedata = {NULL, 0};
	filedata.pData = (unsigned char*)malloc(psrc->LinearSize);
	memcpy(filedata.pData, psrc->Data, psrc->LinearSize);
	filedata.LinearSize = psrc->LinearSize;

	Convert_Data(&filedata, &srcdetails, &dstdetails);


	TEXA_HEADER* tempdstheader = (TEXA_HEADER*)malloc(sizeof(TEXA_HEADER) + filedata.LinearSize);
	memcpy(tempdstheader, *src, sizeof(TEXA_HEADER)); //copy header
	free(psrc);
	memcpy(tempdstheader->Data, filedata.pData, filedata.LinearSize);
	free(filedata.pData);

	tempdstheader->Format = dstformat;

	tempdstheader->LinearSize = filedata.LinearSize;
	tempdstheader->ByteRate = tempdstheader->SampleRate * tempdstheader->ChannelCount * (dstdetails.BitsPerChannel[0] / 8);
	tempdstheader->BlockAlign = tempdstheader->ChannelCount * (dstdetails.BitsPerChannel[0] / 8);
	*src = tempdstheader;

	return (TEXRESULT)(Success);
}

TEXRESULT Create_DummyTEXA(TEXA_HEADER** pDst, AudioFormat Format, uint32_t SampleRate, uint32_t ChannelCount,
	uint32_t ByteRate, uint32_t BlockAlign, uint64_t FrameCount, uint64_t InitialSize)
{

	TEXA_HEADER* tempdstheader = (TEXA_HEADER*)malloc(sizeof(TEXA_HEADER) + InitialSize);
	memset(tempdstheader, 0L, sizeof(TEXA_HEADER) + InitialSize);

	tempdstheader->Format = Format;

	tempdstheader->LinearSize = InitialSize;
	tempdstheader->SampleRate = SampleRate;
	tempdstheader->ChannelCount = ChannelCount;
	tempdstheader->ByteRate = ByteRate;
	tempdstheader->BlockAlign = BlockAlign;
	tempdstheader->FrameCount = FrameCount;
	*pDst = tempdstheader;

	return (TEXRESULT)(Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//printing
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#else

void print_channel_layout(const struct SoundIoChannelLayout* layout) {
	if (layout->name)
	{
		fprintf(stderr, "%s", layout->name);
	}
	else
	{
		fprintf(stderr, "%s", soundio_get_channel_name(layout->channels[0]));
		for (int i = 1; i < layout->channel_count; i += 1)
		{
			fprintf(stderr, ", %s", soundio_get_channel_name(layout->channels[i]));
		}
	}
}

void print_device(struct SoundIoDevice* device, bool is_default) {
	const char* default_str = is_default ? " (default)" : "";
	const char* raw_str = device->is_raw ? " (raw)" : "";
	fprintf(stderr, "%s%s%s\n", device->name, default_str, raw_str);

	fprintf(stderr, "  id: %s\n", device->id);
	if (device->probe_error)
	{
		fprintf(stderr, "  probe error: %s\n", soundio_strerror(device->probe_error));
	}
	else
	{
		fprintf(stderr, "  channel layouts:\n");
		for (int i = 0; i < device->layout_count; i += 1)
		{
			fprintf(stderr, "    ");
			print_channel_layout(&device->layouts[i]);
			fprintf(stderr, "\n");
		}
		if (device->current_layout.channel_count > 0)
		{
			fprintf(stderr, "  current layout: ");
			print_channel_layout(&device->current_layout);
			fprintf(stderr, "\n");
		}
		fprintf(stderr, "  sample rates:\n");
		for (int i = 0; i < device->sample_rate_count; i += 1)
		{
			struct SoundIoSampleRateRange* range = &device->sample_rates[i];
			fprintf(stderr, "    %d - %d\n", range->min, range->max);
		}
		if (device->sample_rate_current)
			fprintf(stderr, "  current sample rate: %d\n", device->sample_rate_current);
		fprintf(stderr, "  formats: ");
		for (int i = 0; i < device->format_count; i += 1)
		{
			const char* comma = (i == device->format_count - 1) ? "" : ", ";
			fprintf(stderr, "%s%s", soundio_format_string(device->formats[i]), comma);
		}
		fprintf(stderr, "\n");
		if (device->current_format != SoundIoFormatInvalid)
			fprintf(stderr, "  current format: %s\n", soundio_format_string(device->current_format));
		fprintf(stderr, "  min software latency: %0.8f sec\n", device->software_latency_min);
		fprintf(stderr, "  max software latency: %0.8f sec\n", device->software_latency_max);
		if (device->software_latency_current != 0.0)
			fprintf(stderr, "  current software latency: %0.8f sec\n", device->software_latency_current);
	}
	fprintf(stderr, "\n");
}

int list_devices(struct SoundIo* soundio) {
	int output_count = soundio_output_device_count(soundio);
	int input_count = soundio_input_device_count(soundio);
	int default_output = soundio_default_output_device_index(soundio);
	int default_input = soundio_default_input_device_index(soundio);
	fprintf(stderr, "--------Input Devices--------\n\n");
	for (int i = 0; i < input_count; i += 1)
	{
		struct SoundIoDevice* device = soundio_get_input_device(soundio, i);
		print_device(device, default_input == i);
		soundio_device_unref(device);
	}
	fprintf(stderr, "\n--------Output Devices--------\n\n");
	for (int i = 0; i < output_count; i += 1)
	{
		struct SoundIoDevice* device = soundio_get_output_device(soundio, i);
		print_device(device, default_output == i);
		soundio_device_unref(device);
	}
	fprintf(stderr, "\n%d devices found\n", input_count + output_count);
	return 0;
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Destroy_AudioSourceHeader(RHeaderAudioSource* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	if (Full == true)
	{
		free(pResourceHeader->AudioData);
	}
}

void Destroy_ElementAudio(ElementAudio* pElement, bool Full, uint32_t ThreadIndex)
{
	uint64_t pointer = 0;
	for (size_t i = 0; i < pElement->EffectsSize; i++)
	{
		AudioEffect* pEffect = (AudioEffect*)((void*)((uint64_t)pElement->Effects + pointer));
		AudioEffectSignature* pSignature = NULL;
		AudioEffectBufferIndex BufferIndex = NULL;
		Find_AudioEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
		if (pSignature->Destructor != NULL)
		{
			pSignature->Destructor(pElement, pEffect, Full, ThreadIndex);
		}
		pointer += pEffect->Header.AllocationSize;
	}

	if (pElement->InStream != NULL)
		soundio_instream_destroy(pElement->InStream);
	if (pElement->OutStream != NULL)
		soundio_outstream_destroy(pElement->OutStream);
	if (pElement->InDevice != NULL)
		soundio_device_unref(pElement->InDevice);
	if (pElement->OutDevice != NULL)
		soundio_device_unref(pElement->OutDevice);
	if (pElement->RingBuffer != NULL)
		soundio_ring_buffer_destroy(pElement->RingBuffer);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Object ReCreation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ReCreate_ElementAudio(ElementAudio* pElement, uint32_t ThreadIndex)
{
	int SoundIoError = SoundIoErrorNone;
	RHeaderAudioSource* pAudioHeader = (RHeaderAudioSource*)Object_Ref_Get_ResourceHeaderPointer(pElement->iAudioSource);

	soundio_flush_events(Utils.AudioHandle);

	if (pElement->UsageFlags & AudioElementUsage_Playback)
	{
		int default_out_device_index = soundio_default_output_device_index(Utils.AudioHandle);
		if (default_out_device_index < 0)
		{
			Engine_Ref_FunctionError("Create_ElementAudio()", "No output device found and AudioElementUsage_Playback set to true.", default_out_device_index);
			return;
		}

		pElement->OutDevice = soundio_get_output_device(Utils.AudioHandle, default_out_device_index);
		if (!pElement->OutDevice)
		{
			Engine_Ref_FunctionError("Create_ElementAudio()", "Failure Creating Output Device.", pElement->OutDevice);
			return;
		}

		{
			bool foundf = false;
			for (size_t i = 0; i < pElement->OutDevice->format_count; i++)
			{
				if ((AudioFormat)pElement->OutDevice->formats[i] == pAudioHeader->AudioData->Format)
				{
					foundf = true;
					break;
				}
			}
			if (foundf == false)
			{
				Engine_Ref_ArgsError("Create_ElementAudio()", "Format Not Supported, Converting To Backup Format.");
				Convert_AudioData(&pAudioHeader->AudioData, AudioFormat_int16LE);
			}
		}

		{
			bool founds = false;
			for (size_t i = 0; i < pElement->OutDevice->sample_rate_count; i++)
			{
				if ((uint32_t)pElement->OutDevice->sample_rates[i].min <= pAudioHeader->AudioData->SampleRate &&
					(uint32_t)pElement->OutDevice->sample_rates[i].max >= pAudioHeader->AudioData->SampleRate)
				{
					founds = true;
					break;
				}
			}
			if (founds == false)
			{
				Engine_Ref_ArgsError("Create_ElementAudio()", "Samplerate Not Supported, Critical Error");
				return;
			}
		}

		pElement->OutStream = soundio_outstream_create(pElement->OutDevice);
		if (!pElement->OutStream) {
			Engine_Ref_FunctionError("Create_ElementAudio()", "Failure Creating Output Stream.", pElement->OutDevice);
			return;
		}
		if (pElement->OutStream->layout_error)
			Engine_Ref_FunctionError("Create_ElementAudio()", "Unable To Set Channel Layout", pElement->OutStream->layout_error);

		pElement->OutStream->format = pAudioHeader->AudioData->Format;
		pElement->OutStream->write_callback = write_callback;
		pElement->OutStream->underflow_callback = underflow_callback;
		pElement->OutStream->sample_rate = pAudioHeader->AudioData->SampleRate;
		pElement->OutStream->userdata = &pElement->Header.Allocation;
		if ((SoundIoError = soundio_outstream_open(pElement->OutStream)) != SoundIoErrorNone)
		{
			Engine_Ref_FunctionError("Create_ElementAudio()", "soundio_outstream_open Failed, SoundIoError == ", SoundIoError);
			return;
		}
	}
	if (pElement->UsageFlags & AudioElementUsage_Recording)
	{
		int default_in_device_index = soundio_default_input_device_index(Utils.AudioHandle);
		if (default_in_device_index < 0)
		{
			Engine_Ref_FunctionError("Create_ElementAudio()", "No input device found and AudioElementUsage_Recording set to true.", default_in_device_index);
			return;
		}

		pElement->InDevice = soundio_get_input_device(Utils.AudioHandle, default_in_device_index);
		if (!pElement->InDevice)
		{
			Engine_Ref_FunctionError("Create_ElementAudio()", "Failure Creating Input Device.", pElement->InDevice);
			return;
		}

		{
			bool foundf = false;
			for (size_t i = 0; i < pElement->InDevice->format_count; i++)
			{
				if ((AudioFormat)pElement->InDevice->formats[i] == pAudioHeader->AudioData->Format)
				{
					foundf = true;
					break;
				}
			}
			if (foundf == false)
			{
				Engine_Ref_ArgsError("Create_ElementAudio()", "Format Not Supported, Converting To Backup Format.");
				pAudioHeader->AudioData->Format = AudioFormat_int16LE;
			}
		}

		{
			bool founds = false;
			for (size_t i = 0; i < pElement->InDevice->sample_rate_count; i++)
			{
				if (pElement->InDevice->sample_rates[i].min <= pAudioHeader->AudioData->SampleRate &&
					pElement->InDevice->sample_rates[i].max >= pAudioHeader->AudioData->SampleRate)
				{
					founds = true;
					break;
				}
			}
			if (founds == false)
			{
				Engine_Ref_ArgsError("Create_ElementAudio()", "Samplerate Not Supported, Critical Error");
				return;
			}
		}



		pElement->InStream = soundio_instream_create(pElement->InDevice);
		if (!pElement->InStream) {
			Engine_Ref_FunctionError("Create_ElementAudio()", "Failure Creating Input Stream.", pElement->InDevice);
			return;
		}
		if (pElement->InStream->layout_error)
			Engine_Ref_FunctionError("Create_ElementAudio()", "Unable To Set Channel Layout", ((void*)pElement->InStream->layout_error));

		FormatDetails formatDetails = Get_FormatDetails(pAudioHeader->AudioData->Format);
		pElement->InStream->format = pAudioHeader->AudioData->Format;
		pElement->InStream->read_callback = read_callback;
		pElement->InStream->overflow_callback = overflow_callback;
		pElement->InStream->sample_rate = pAudioHeader->AudioData->SampleRate;
		pElement->InStream->userdata = &pElement->Header.Allocation;
		pElement->RingBufferSize_Seconds = pElement->RingBufferSize_Seconds;
		pElement->RingBuffer = soundio_ring_buffer_create(Utils.AudioHandle,
			(pElement->RingBufferSize_Seconds * pAudioHeader->AudioData->SampleRate) * ((formatDetails.Stride / 8) * pAudioHeader->AudioData->ChannelCount));
		if ((SoundIoError = soundio_instream_open(pElement->InStream)) != SoundIoErrorNone)
		{
			Engine_Ref_FunctionError("Create_ElementAudio()", "soundio_instream_open Failed, SoundIoError == ", SoundIoError);
			return;
		}
	}

	uint64_t pointer = 0;
	for (size_t i = 0; i < pElement->EffectsSize; i++)
	{
		AudioEffect* pEffect = (AudioEffect*)((void*)((uint64_t)pElement->Effects + pointer));
		AudioEffectSignature* pSignature = NULL;
		AudioEffectBufferIndex BufferIndex = NULL;
		Find_AudioEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
		if (pSignature->ReConstructor != NULL)
		{
			pSignature->ReConstructor(pElement, pEffect, ThreadIndex);
		}
		pointer += pEffect->Header.AllocationSize;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Packers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Pack_AudioSourceHeader(const RHeaderAudioSource* pResourceHeader, RHeaderAudioSource* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		if (pResourceHeader->AudioData != NULL)
		{
			memcpy(((void*)((uint64_t)pData + (uint64_t)*pBufferPointer)), pResourceHeader->AudioData, sizeof(TEXA_HEADER) + pResourceHeader->AudioData->LinearSize);
			pCopiedResourceHeader->AudioData = (TEXA_HEADER*) * pBufferPointer;
			*pBufferPointer += sizeof(TEXA_HEADER) + pResourceHeader->AudioData->LinearSize;
		}
	}
	else
	{
		*pBufferPointer += sizeof(TEXA_HEADER) + pResourceHeader->AudioData->LinearSize;
	}
}

void Pack_ElementAudio(const ElementAudio* pElement, ElementAudio* pCopiedElement, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	uint64_t pointer = 0;
	for (size_t i = 0; i < pElement->EffectsSize; i++)
	{
		AudioEffect* pEffect = (AudioEffect*)((void*)((uint64_t)pElement->Effects + pointer));
		AudioEffect* pCopiedEffect = (AudioEffect*)((void*)((uint64_t)pCopiedElement->Effects + pointer));
		AudioEffectSignature* pSignature = NULL;
		AudioEffectBufferIndex BufferIndex = NULL;
		Find_AudioEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
		if (pSignature->Destructor != NULL)
		{
			pSignature->Packer(pElement, pCopiedElement, pEffect, pCopiedEffect, pBufferPointer, pData, ThreadIndex);
		}
		pointer += pEffect->Header.AllocationSize;
	}

	if (pData != NULL)
	{
		memset(&pCopiedElement->OutStream, 0, sizeof(pCopiedElement->OutStream));
		memset(&pCopiedElement->InStream, 0, sizeof(pCopiedElement->InStream));
		memset(&pCopiedElement->OutDevice, 0, sizeof(pCopiedElement->OutDevice));
		memset(&pCopiedElement->InDevice, 0, sizeof(pCopiedElement->InDevice));
		memset(&pCopiedElement->RingBuffer, 0, sizeof(pCopiedElement->RingBuffer));
	}
	else
	{

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//UnPackers	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UnPack_AudioSourceHeader(const RHeaderAudioSource* pResourceHeader, RHeaderAudioSource* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	if (pResourceHeader->AudioData != NULL)
	{
		TEXA_HEADER* pheader = (TEXA_HEADER*)((void*)((uint64_t)pData + (uint64_t)pResourceHeader->AudioData));

		pCopiedResourceHeader->AudioData = (TEXA_HEADER*)malloc(sizeof(TEXA_HEADER) + pheader->LinearSize);
		memcpy(pCopiedResourceHeader->AudioData, (void*)((uint64_t)pData + (uint64_t)pResourceHeader->AudioData), sizeof(TEXA_HEADER) + pheader->LinearSize);
	}
}

void UnPack_ElementAudio(const ElementAudio* pElement, ElementAudio* pCopiedElement, const void* pData, uint32_t ThreadIndex)
{
	ReCreate_ElementAudio(pCopiedElement, ThreadIndex);

	uint64_t pointer = 0;
	for (size_t i = 0; i < pElement->EffectsSize; i++)
	{
		AudioEffect* pEffect = (AudioEffect*)((void*)((uint64_t)pElement->Effects + pointer));
		AudioEffect* pCopiedEffect = (AudioEffect*)((void*)((uint64_t)pCopiedElement->Effects + pointer));
		AudioEffectSignature* pSignature = NULL;
		AudioEffectBufferIndex BufferIndex = NULL;
		Find_AudioEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
		if (pSignature->UnPacker != NULL)
		{
			pSignature->UnPacker(pElement, pCopiedElement, pEffect, pCopiedEffect, pData, ThreadIndex);
		}
		pointer += pEffect->Header.AllocationSize;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Constructors	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_AudioSourceHeader(RHeaderAudioSource* pResourceHeader, RHeaderAudioSourceCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_AudioSourceHeader()", "pCreateInfo == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->AudioData == NULL)
		{
			Engine_Ref_ArgsError("Create_AudioSourceHeader()", "pCreateInfo->AudioData == NULLPTR");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->AudioData = (TEXA_HEADER*)malloc(sizeof(*pResourceHeader->AudioData) + pCreateInfo->AudioData->LinearSize);
		memcpy(pResourceHeader->AudioData, pCreateInfo->AudioData, sizeof(*pResourceHeader->AudioData) + pCreateInfo->AudioData->LinearSize);
	}
	*pAllocationSize = sizeof(RHeaderAudioSource);
	return (TEXRESULT)(Success);
}

TEXRESULT Create_ElementAudio(ElementAudio* pElement, ElementAudioCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	TEXRESULT res = (TEXRESULT)Success;

	uint64_t bytes = 0;
	for (size_t i = 0; i < pCreateInfo->EffectCreateInfosSize; i++)
	{
		AudioEffectSignature* pSignature = NULL;
		AudioEffectBufferIndex BufferIndex = NULL;
		Find_AudioEffectSignature(pCreateInfo->EffectCreateInfos[i].Identifier, &pSignature, &BufferIndex);

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
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_ElementAudioInput()", "pCreateInfo == NULL");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
		if (pCreateInfo->pAudioSource == NULL)
		{
			Engine_Ref_ObjectError("Create_ElementAudioInput()", "pCreateInfo", &pCreateInfo, "pCreateInfo->pAudioSource == NULL");
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
#endif
		pElement->iAudioSource = pCreateInfo->pAudioSource->Header.Allocation;
		pElement->RingBufferSize_Seconds = (pCreateInfo->RingBufferSize_Seconds <= 10) ? pCreateInfo->RingBufferSize_Seconds + 10 : pCreateInfo->RingBufferSize_Seconds;
		pElement->CurrentFrame = pCreateInfo->StartFrame;
		pElement->UsageFlags = pCreateInfo->UsageFlags;

		ReCreate_ElementAudio(pElement, ThreadIndex);

		pElement->EffectsSize = pCreateInfo->EffectCreateInfosSize;
		uint64_t pointer = 0;
		for (size_t i = 0; i < pCreateInfo->EffectCreateInfosSize; i++)
		{
			AudioEffect* pEffect = (AudioEffect*)((void*)((uint64_t)pElement->Effects + pointer));

			AudioEffectSignature* pSignature = NULL;
			AudioEffectBufferIndex BufferIndex = NULL;
			Find_AudioEffectSignature(pCreateInfo->EffectCreateInfos[i].Identifier, &pSignature, &BufferIndex);

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
	*pAllocationSize = sizeof(ElementAudio) + bytes;
	return (TEXRESULT)(Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Stock Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Draw Effect Element
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Draw_Volume(ElementAudio* pElement, ResourceHeader* pHeader, Object* pObject, AudioEffectVolume* pEffect, uint32_t FrameCountMin, uint32_t FrameCountMax, AudioElementUsageFlags Usage)
{
	if (Usage & AudioElementUsage_Playback)
	{
#ifndef NDEBUG
		if (!(pElement->UsageFlags & AudioElementUsage_Playback))
		{
			Engine_Ref_ArgsError("Draw_Volume()", "pElement->UsageFlags Dont Mention AudioElementUsage_Playback, But Yet it is used.");
		}
#endif
		RHeaderAudioSource* pAudioSource = (RHeaderAudioSource*)Object_Ref_Get_ResourceHeaderPointer(pElement->iAudioSource);

		int SoundIoError = SoundIoErrorNone;
		struct SoundIoChannelLayout* layout = &pElement->OutStream->layout;
		struct SoundIoChannelArea* areas;
		uint32_t frames_left = FrameCountMax; //This is recommended in the documentation

		while (frames_left > 0)
		{
			int frame_count = frames_left;

			if ((SoundIoError = soundio_outstream_begin_write(pElement->OutStream, &areas, &frame_count)))
			{
				Engine_Ref_FunctionError("Draw_Volume()", "soundio_outstream_begin_write Failed, SoundIoError == ", SoundIoError);
				return;
			}

			if (!frame_count)
				break;

			uint32_t framestodo = min((uint32_t)frame_count, (uint32_t)max((int64_t)pAudioSource->AudioData->FrameCount - (int64_t)pElement->CurrentFrame, (int64_t)0));
			uint32_t channelstodo = min((uint32_t)layout->channel_count, (uint32_t)pAudioSource->AudioData->ChannelCount);

			FormatDetails formatdetails = Get_FormatDetails(pElement->OutStream->format);

			uint64_t srcbitmask = 0;

			switch (formatdetails.ChannelTypes[0])
			{
			case SignedInt:
				srcbitmask = (uint64_t)1 << (uint64_t)(formatdetails.BitsPerChannel[0] - 1);
				break;
			case UnsignedInt:
				srcbitmask = 0;
				break;
			case SignedFloat:
				break;
			}
			uint32_t dstcopysize = formatdetails.BitsPerChannel[0];

			uint64_t endbuffer = 0;
			uint64_t previousbuffer = 0;
			uint64_t tempbuffer4 = 0;
			uint64_t tempbuffer5 = 0;
			uint64_t startbuffer = 0;
			double result = 0.0;

			switch (formatdetails.ChannelTypes[0])
			{
			case UnsignedInt:


				for (uint32_t frame = 0; frame < framestodo; frame++)
				{
					for (uint32_t channel = 0; channel < channelstodo; channel++)
					{
						memcpy(&startbuffer, &pAudioSource->AudioData->Data[(((frame + pElement->CurrentFrame) * layout->channel_count) + channel) * (formatdetails.BitsPerChannel[0] / 8)], (formatdetails.BitsPerChannel[0] / 8));
						result = *((uint64_t*)&startbuffer); //add data
						result *= pEffect->Volume;
						*((uint64_t*)&endbuffer) = result;
						memcpy((char*)((uint64_t)areas[channel].ptr + (uint64_t)areas[channel].step * (uint64_t)frame), &endbuffer, (dstcopysize / 8));
					}
				}
				break;
			case SignedInt:
				for (uint32_t frame = 0; frame < framestodo; frame++)
				{
					for (uint32_t channel = 0; channel < channelstodo; channel++)
					{
						memcpy(&startbuffer, &pAudioSource->AudioData->Data[(((frame + pElement->CurrentFrame) * layout->channel_count) + channel) * (formatdetails.BitsPerChannel[0] / 8)], (formatdetails.BitsPerChannel[0] / 8));
						tempbuffer4 = UINT64_MAX * ((startbuffer & srcbitmask) >> ((uint64_t)formatdetails.BitsPerChannel[0] - (uint64_t)1)); //get sign and make it compatible or whatever
						tempbuffer5 = tempbuffer4 << ((uint64_t)formatdetails.BitsPerChannel[0]); //move sign to end
						tempbuffer5 |= startbuffer; //add rest of data
						result = *((int64_t*)&tempbuffer5);
						result *= pEffect->Volume;
						*((int64_t*)&endbuffer) = result;
						memcpy((char*)((uint64_t)areas[channel].ptr + (uint64_t)areas[channel].step * (uint64_t)frame), &endbuffer, (dstcopysize / 8));
					}
				}
				break;
			case SignedFloat:
				for (uint32_t frame = 0; frame < framestodo; frame++)
				{
					for (uint32_t channel = 0; channel < channelstodo; channel++)
					{
						memcpy(&startbuffer, &pAudioSource->AudioData->Data[(((frame + pElement->CurrentFrame) * layout->channel_count) + channel) * (formatdetails.BitsPerChannel[0] / 8)], (formatdetails.BitsPerChannel[0] / 8));
						switch (formatdetails.BitsPerChannel[0])
						{
						case 32:
							result = *((float*)&startbuffer);
							break;
						case 64:
							result = *((double*)&startbuffer);
							break;
						}
						result *= pEffect->Volume;
						switch (formatdetails.BitsPerChannel[0])
						{
						case 32:
							*((float*)&endbuffer) = result;
							break;
						case 64:
							*((double*)&endbuffer) = result;
							break;
						}
						//memcpy off the last bits if needed to avoid overflows
						memcpy((char*)((uint64_t)areas[channel].ptr + (uint64_t)areas[channel].step * (uint64_t)frame), &endbuffer, (dstcopysize / 8));
					}
				}
				break;
			}

			pElement->CurrentFrame += framestodo;

			if ((SoundIoError = soundio_outstream_end_write(pElement->OutStream)))
			{
				Engine_Ref_FunctionError("Draw_Volume()", "soundio_outstream_end_write Failed, SoundIoError == ", SoundIoError);
				return;
			}

			frames_left -= frame_count;
		}
	}
	if (Usage & AudioElementUsage_Recording)
	{
#ifndef NDEBUG
		if (!(pElement->UsageFlags & AudioElementUsage_Playback))
		{
			Engine_Ref_ArgsError("Draw_Volume()", "pElement->UsageFlags Dont Mention AudioElementUsage_Recording, But Yet it is used.");
		}
#endif
		struct SoundIoChannelLayout* layout = &pElement->InStream->layout;
		struct SoundIoChannelArea* areas;

		int SoundIoError = SoundIoErrorNone;
		char* writeptr = soundio_ring_buffer_write_ptr(pElement->RingBuffer);
		uint32_t free_bytes = soundio_ring_buffer_free_count(pElement->RingBuffer);
		uint32_t free_count = free_bytes / pElement->InStream->bytes_per_frame;

		if (free_count < FrameCountMin)
		{
			Engine_Ref_FunctionError("Draw_Volume()", "Ring Buffer Overflow. Value == ", free_count < FrameCountMin);
			//return;
		}

		int write_frames = min(free_count, FrameCountMax);
		int frames_left = write_frames;
		for (;;)
		{
			int frame_count = frames_left;

			if ((SoundIoError = soundio_instream_begin_read(pElement->InStream, &areas, &frame_count)))
			{
				Engine_Ref_FunctionError("Draw_Volume()", "soundio_instream_begin_read Failed, SoundIoError == ", SoundIoError);
				return;
			}


			if (!frame_count)
				break;
			if (!areas)
			{
				// Due to an overflow there is a hole. Fill the ring buffer with
				// silence for the size of the hole.
				memset(writeptr, 0, (uint64_t)frame_count * (uint64_t)pElement->InStream->bytes_per_frame);
			}
			else
			{
				uint32_t framestodo = frame_count;
				uint32_t channelstodo = layout->channel_count;

				FormatDetails formatdetails = Get_FormatDetails(pElement->InStream->format);

				uint64_t srcbitmask = 0;

				switch (formatdetails.ChannelTypes[0])
				{
				case SignedInt:
					srcbitmask = (uint64_t)1 << (uint64_t)(formatdetails.BitsPerChannel[0] - 1);
					break;
				case UnsignedInt:
					srcbitmask = 0;
					break;
				case SignedFloat:
					break;
				}

				uint32_t dstcopysize = formatdetails.BitsPerChannel[0];

				uint64_t endbuffer = 0;
				uint64_t previousbuffer = 0;
				uint64_t tempbuffer4 = 0;
				uint64_t tempbuffer5 = 0;
				uint64_t startbuffer = 0;
				double result = 0.0;

				switch (formatdetails.ChannelTypes[0])
				{
				case UnsignedInt:
					for (uint32_t frame = 0; frame < framestodo; frame++)
					{
						for (uint32_t channel = 0; channel < channelstodo; channel++)
						{
							memcpy(&startbuffer, areas[channel].ptr, (formatdetails.BitsPerChannel[0] / 8));
							result = *((uint64_t*)&startbuffer); //add data
							result *= pEffect->Volume;
							*((uint64_t*)&endbuffer) = result;
							memcpy(writeptr, &endbuffer, (dstcopysize / 8));
							areas[channel].ptr += areas[channel].step;
							writeptr += pElement->InStream->bytes_per_sample;
						}
					}
					break;
				case SignedInt:
					for (uint32_t frame = 0; frame < framestodo; frame++)
					{
						for (uint32_t channel = 0; channel < channelstodo; channel++)
						{
							memcpy(&startbuffer, areas[channel].ptr, (formatdetails.BitsPerChannel[0] / 8));
							tempbuffer4 = UINT64_MAX * ((startbuffer & srcbitmask) >> ((uint64_t)formatdetails.BitsPerChannel[0] - (uint64_t)1)); //get sign and make it compatible or whatever
							tempbuffer5 = tempbuffer4 << ((uint64_t)formatdetails.BitsPerChannel[0]); //move sign to end
							tempbuffer5 |= startbuffer; //add rest of data
							result = *((int64_t*)&tempbuffer5);
							result *= pEffect->Volume;
							*((int64_t*)&endbuffer) = result;
							memcpy(writeptr, &endbuffer, (dstcopysize / 8));
							areas[channel].ptr += areas[channel].step;
							writeptr += pElement->InStream->bytes_per_sample;
						}
					}
					break;
				case SignedFloat:
					for (uint32_t frame = 0; frame < framestodo; frame++)
					{
						for (uint32_t channel = 0; channel < channelstodo; channel++)
						{
							memcpy(&startbuffer, areas[channel].ptr, (formatdetails.BitsPerChannel[0] / 8));
							switch (formatdetails.BitsPerChannel[0])
							{
							case 32:
								result = *((float*)&startbuffer);
								break;
							case 64:
								result = *((double*)&startbuffer);
								break;
							}
							result *= pEffect->Volume;
							switch (formatdetails.BitsPerChannel[0])
							{
							case 32:
								*((float*)&endbuffer) = result;
								break;
							case 64:
								*((double*)&endbuffer) = result;
								break;
							}
							//memcpy off the last bits if needed to avoid overflows
							memcpy(writeptr, &endbuffer, (dstcopysize / 8));

							areas[channel].ptr += areas[channel].step;
							writeptr += pElement->InStream->bytes_per_sample;
						}
					}
					break;
				}

				pElement->CurrentFrame += framestodo;

			}
			if ((SoundIoError = soundio_instream_end_read(pElement->InStream)))
			{
				Engine_Ref_FunctionError("Draw_Volume()", "soundio_instream_end_read Failed, SoundIoError == ", SoundIoError);
				return;
			}

			frames_left -= frame_count;
			if (frames_left <= 0)
				break;
		}
		int advance_bytes = write_frames * pElement->InStream->bytes_per_frame;
		soundio_ring_buffer_advance_write_ptr(pElement->RingBuffer, advance_bytes);
	}
}

void Draw_Audio3D(ElementAudio* pElement, ResourceHeader* pHeader, Object* pObject, AudioEffectAudio3D* pEffect, uint32_t FrameCountMin, uint32_t FrameCountMax, AudioElementUsageFlags Usage)
{

}
/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Update Effect Element
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Update_Volume(ElementAudio* pElement, ResourceHeader* pHeader, Object* pObject, AudioEffectVolume* pEffect)
{

}

void Update_Audio3D(ElementAudio* pElement, ResourceHeader* pHeader, Object* pObject, AudioEffectAudio3D* pEffect)
{

}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Signature Updates
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdateSignature_Volume(AudioEffectSignature* pSignature)
{
	for (size_t i = 0; i < Utils.ElementAudioBuffer.Size;)
	{
		ElementAudio* pElement = (ElementAudio*)&Utils.ElementAudioBuffer.Buffer[i];
		if (pElement->Header.AllocationSize != (uint64_t)NULL && pElement->Header.Allocation.Identifier == (uint32_t)AudioElement_ElementAudio)
		{
			if (pElement->UsageFlags & AudioElementUsage_Recording)
			{

				if ((((double)clock() / (double)CLOCKS_PER_SEC) - pElement->LastTime) >= ((double)pElement->RingBufferSize_Seconds / (double)4))
				{
					uint32_t ReadBufferSize = soundio_ring_buffer_fill_count(pElement->RingBuffer);
					const char* ReadBuffer = soundio_ring_buffer_read_ptr(pElement->RingBuffer);
					soundio_ring_buffer_advance_read_ptr(pElement->RingBuffer, ReadBufferSize);
					if (ReadBufferSize != (uint32_t)NULL)
					{
						RHeaderAudioSource* pAudioProduct = (RHeaderAudioSource*)Object_Ref_Get_ResourceHeaderPointer(pElement->iAudioSource);

						FormatDetails formatDetails = Get_FormatDetails(pAudioProduct->AudioData->Format);

						//resizing audiosource
						TEXA_HEADER* tempdstheader = (TEXA_HEADER*)malloc(sizeof(TEXA_HEADER) + pAudioProduct->AudioData->LinearSize + ReadBufferSize);
						memset(tempdstheader, 0, sizeof(TEXA_HEADER) + pAudioProduct->AudioData->LinearSize + ReadBufferSize);
						memcpy(tempdstheader, pAudioProduct->AudioData, sizeof(TEXA_HEADER) + pAudioProduct->AudioData->LinearSize); //copy header

						free(pAudioProduct->AudioData);
						pAudioProduct->AudioData = tempdstheader;

						//filling the new spots with data and updating parameters
						unsigned char* ptr = &pAudioProduct->AudioData->Data[pAudioProduct->AudioData->LinearSize];
						memcpy(ptr, ReadBuffer, ReadBufferSize);
						pAudioProduct->AudioData->LinearSize = pAudioProduct->AudioData->LinearSize + ReadBufferSize;
						pAudioProduct->AudioData->Data[pAudioProduct->AudioData->LinearSize - 1] = '\0';
						pAudioProduct->AudioData->ChannelCount = pElement->InStream->layout.channel_count;
						pAudioProduct->AudioData->BlockAlign = pAudioProduct->AudioData->ChannelCount * (formatDetails.BitsPerChannel[0] / 8);
						pAudioProduct->AudioData->ByteRate = pAudioProduct->AudioData->SampleRate * pAudioProduct->AudioData->ChannelCount * (formatDetails.BitsPerChannel[0] / 8);
						pAudioProduct->AudioData->FrameCount = pAudioProduct->AudioData->LinearSize / (((uint64_t)formatDetails.BitsPerChannel[0] / (uint64_t)8) * (uint64_t)pAudioProduct->AudioData->ChannelCount);
					}
					pElement->LastTime += (double)pElement->RingBufferSize_Seconds / (double)4;
				}
			}
			i += pElement->Header.AllocationSize;
		}
		else
		{
			i++;
		}
	}
}

void UpdateSignature_Audio3D(AudioEffectSignature* pSignature)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Destroy_Volume(ElementAudio* pElement, AudioEffectVolume* pEffect, bool Full, uint32_t ThreadIndex)
{

}

void Destroy_Audio3D(ElementAudio* pElement, AudioEffectAudio3D* pEffect, bool Full, uint32_t ThreadIndex)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Recreation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ReCreate_Volume(ElementAudio* pElement, AudioEffectVolume* pEffect, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_Volume()", "pElement == NULLPTR");
		return (TEXRESULT)Invalid_Parameter;
	}
	if (pEffect == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_Volume()", "pEffect == NULLPTR");
		return (TEXRESULT)Invalid_Parameter;
	}
#endif
	return (TEXRESULT)Success;
}

void ReCreate_Audio3D(ElementAudio* pElement, AudioEffectAudio3D* pEffect, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_Audio3D()", "pElement == NULLPTR");
		return (TEXRESULT)Invalid_Parameter;
	}
	if (pEffect == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_Audio3D()", "pEffect == NULLPTR");
		return (TEXRESULT)Invalid_Parameter;
	}
#endif
	return (TEXRESULT)Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Packers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Pack_Volume(const ElementAudio* pElement, ElementAudio* pCopiedElement, const AudioEffectVolume* pEffect, AudioEffectVolume* pCopiedEffect, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{

	}
	else
	{

	}
}

void Pack_Audio3D(const ElementAudio* pElement, ElementAudio* pCopiedElement, const  AudioEffectAudio3D* pEffect, AudioEffectAudio3D* pCopiedEffect, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{

	}
	else
	{

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect UnPackers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UnPack_Volume(const ElementAudio* pElement, ElementAudio* pCopiedElement, const AudioEffectVolume* pEffect, AudioEffectVolume* pCopiedEffect, const void* pData, uint32_t ThreadIndex)
{
	ReCreate_Volume(pCopiedElement, pCopiedEffect, ThreadIndex);
}

void UnPack_Audio3D(const ElementAudio* pElement, ElementAudio* pCopiedElement, const  AudioEffectAudio3D* pEffect, AudioEffectAudio3D* pCopiedEffect, const void* pData, uint32_t ThreadIndex)
{
	ReCreate_Audio3D(pCopiedElement, pCopiedEffect, ThreadIndex);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_Volume(ElementAudio* pElement, AudioEffectVolume* pEffect, const AudioEffectCreateInfoVolume* pEffectCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
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
		pEffect->Volume = pEffectCreateInfo->Volume;
		ReCreate_Volume(pElement, pEffect, ThreadIndex);
	}
	*pAllocationSize = sizeof(AudioEffectVolume);
	return (TEXRESULT)Success;
}

TEXRESULT Create_Audio3D(ElementAudio* pElement, AudioEffectAudio3D* pEffect, const AudioEffectCreateInfoAudio3D* pEffectCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
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
		ReCreate_Audio3D(pElement, pEffect, ThreadIndex);
	}
	*pAllocationSize = sizeof(AudioEffectAudio3D);
	return (TEXRESULT)Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//main 3 funcs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Update_Audio()
{
	soundio_flush_events(Utils.AudioHandle);

	for (size_t i = 0; i < Utils.AudioEffectSignaturesSize; i++)
	{
		if (Utils.AudioEffectSignatures[i]->UpdateSignature != NULL)
			Utils.AudioEffectSignatures[i]->UpdateSignature(Utils.AudioEffectSignatures[i]);
	}
}

TEXRESULT Initialise_Audio()
{
	memset(&Utils, 0, sizeof(Utils));
	memset(&Config, 0, sizeof(Config));

	Config.InitialElementsMax = 1024;
	Config.InitialHeadersMax = 1024;



	Engine_Ref_Create_Mutex(Utils.ConvertersToTEXAMutex, MutexType_Plain);
	Engine_Ref_Create_Mutex(Utils.ConvertersFromTEXAMutex, MutexType_Plain);
	Engine_Ref_Create_Mutex(Utils.AudioEffectSignaturesMutex, MutexType_Plain);


	///////////////////////////////////////////////////////////////////////////////////////////////
	//buffer
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderAudioSourceSig.Buffer = &Utils.RHeaderAudioSourceBuffer;

	Utils.ElementAudioSig.Buffer = &Utils.ElementAudioBuffer;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//bytelength
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderAudioSourceSig.ByteLength = sizeof(RHeaderAudioSource);

	Utils.ElementAudioSig.ByteLength = sizeof(ElementAudio);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//identifiers
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderAudioSourceSig.Identifier = (uint32_t)AudioHeader_AudioSource;

	Utils.ElementAudioSig.Identifier = (uint32_t)AudioElement_ElementAudio;


	///////////////////////////////////////////////////////////////////////////////////////////////
	//constructors
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderAudioSourceSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_AudioSourceHeader;

	Utils.ElementAudioSig.Constructor = (Create_ElementTemplate*)&Create_ElementAudio;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//packers
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderAudioSourceSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_AudioSourceHeader;

	Utils.ElementAudioSig.Packer = (Pack_ElementTemplate*)&Pack_ElementAudio;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//unpackers
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderAudioSourceSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_AudioSourceHeader;

	Utils.ElementAudioSig.UnPacker = (UnPack_ElementTemplate*)&UnPack_ElementAudio;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//destructors
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderAudioSourceSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_AudioSourceHeader;

	Utils.ElementAudioSig.Destructor = (Destroy_ElementTemplate*)&Destroy_ElementAudio;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//ReCreate
	///////////////////////////////////////////////////////////////////////////////////////////////

	//Utils.RHeaderAudioSourceSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_AudioSourceHeader;

	Utils.ElementAudioSig.ReConstructor = (ReCreate_ElementTemplate*)&ReCreate_ElementAudio;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//create buffer
	///////////////////////////////////////////////////////////////////////////////////////////////

	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderAudioSourceBuffer, Config.InitialHeadersMax);

	Object_Ref_Create_ElementBuffer(&Utils.ElementAudioBuffer, Config.InitialElementsMax);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//registration
	///////////////////////////////////////////////////////////////////////////////////////////////

	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderAudioSourceSig);

	Object_Ref_Register_ElementSignature(&Utils.ElementAudioSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//effects
	///////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////////////////////
	//identifiers
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.VolumeSig.Identifier = (uint32_t)AudioEffect_Volume;
	Utils.Audio3DSig.Identifier = (uint32_t)AudioEffect_Audio3D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Create effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.VolumeSig.Constructor = (Create_AudioEffectTemplate*)&Create_Volume;
	Utils.Audio3DSig.Constructor = (Create_AudioEffectTemplate*)&Create_Audio3D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Destroy Effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.VolumeSig.Destructor = (Destroy_AudioEffectTemplate*)&Destroy_Volume;
	Utils.Audio3DSig.Destructor = (Destroy_AudioEffectTemplate*)&Destroy_Audio3D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//ReCreate effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.VolumeSig.ReConstructor = (ReCreate_AudioEffectTemplate*)&ReCreate_Volume;
	Utils.Audio3DSig.ReConstructor = (ReCreate_AudioEffectTemplate*)&ReCreate_Audio3D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Pack Effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.VolumeSig.Packer = (Pack_AudioEffectTemplate*)&Pack_Volume;
	Utils.Audio3DSig.Packer = (Pack_AudioEffectTemplate*)&Pack_Audio3D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//UnPack Effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.VolumeSig.UnPacker = (UnPack_AudioEffectTemplate*)&UnPack_Volume;
	Utils.Audio3DSig.UnPacker = (UnPack_AudioEffectTemplate*)&UnPack_Audio3D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Draw Effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.VolumeSig.Draw = (Draw_AudioEffectTemplate*)&Draw_Volume;
	Utils.Audio3DSig.Draw = (Draw_AudioEffectTemplate*)&Draw_Audio3D;
	/*
	///////////////////////////////////////////////////////////////////////////////////////////////
	//Update Effect
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.VolumeSig.Update = (AudioEffectUpdateElementTemplate*)&Update_Volume;
	Utils.Audio3DSig.Update = (AudioEffectUpdateElementTemplate*)&Update_Audio3D;
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////
	//Update Effect Signature
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.VolumeSig.UpdateSignature = &UpdateSignature_Volume;
	Utils.Audio3DSig.UpdateSignature = &UpdateSignature_Audio3D;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//effects registration
	///////////////////////////////////////////////////////////////////////////////////////////////

	Register_AudioEffectSignature(&Utils.VolumeSig);
	Register_AudioEffectSignature(&Utils.Audio3DSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//soundio creation
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.AudioHandle = soundio_create();

	int SoundIoError = 0;
	if ((SoundIoError = soundio_connect(Utils.AudioHandle)) != SoundIoErrorNone)
	{
		Engine_Ref_FunctionError("Initialise_Audio()", "soundio_connect Failed. SoundIoError == ", SoundIoError);
		return (TEXRESULT)(Failure);
	}
	soundio_flush_events(Utils.AudioHandle);
	return (TEXRESULT)(Success);
}

void Destroy_Audio()
{
	Object_Ref_Destroy_ElementBuffer(&Utils.ElementAudioBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderAudioSourceBuffer);

	Object_Ref_DeRegister_ElementSignature(&Utils.ElementAudioSig);
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderAudioSourceSig);

	DeRegister_AudioEffectSignature(&Utils.VolumeSig);
	DeRegister_AudioEffectSignature(&Utils.Audio3DSig);

	if (Utils.AudioEffectSignatures != NULL && Utils.AudioEffectSignaturesSize != NULL)
		free(Utils.AudioEffectSignatures);
	Utils.AudioEffectSignatures = NULL;
	Utils.AudioEffectSignaturesSize = NULL;

	if (Utils.ConvertersToTEXA != NULL && Utils.ConvertersToTEXASize != NULL)
		free(Utils.ConvertersToTEXA);
	Utils.ConvertersToTEXA = NULL;
	Utils.ConvertersToTEXASize = NULL;

	if (Utils.ConvertersFromTEXA != NULL && Utils.ConvertersFromTEXASize != NULL)
		free(Utils.ConvertersFromTEXA);
	Utils.ConvertersFromTEXA = NULL;
	Utils.ConvertersFromTEXASize = NULL;

	Engine_Ref_Destroy_Mutex(Utils.ConvertersToTEXAMutex, MutexType_Plain);
	Engine_Ref_Destroy_Mutex(Utils.ConvertersFromTEXAMutex, MutexType_Plain);
	Engine_Ref_Destroy_Mutex(Utils.AudioEffectSignaturesMutex, MutexType_Plain);

	soundio_destroy(Utils.AudioHandle);

	memset(&Utils, 0, sizeof(Utils));
	memset(&Config, 0, sizeof(Config));
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
	Object_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);

	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData("Audio::InitialHeadersMax"), &Config.InitialHeadersMax, 1, sizeof(Config.InitialHeadersMax));
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData("Audio::InitialElementsMax"), &Config.InitialElementsMax, 1, sizeof(Config.InitialElementsMax));


	ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData("Audio::Utils"), &AudioRes.pUtils, &Utils);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Initialise_Audio"), &AudioRes.pInitialise_Audio, &Initialise_Audio, Construct, 0.1f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Destroy_Audio"), &AudioRes.pDestroy_Audio, &Destroy_Audio, Destruct, 100.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Update_Audio"), &AudioRes.pUpdate_Audio, &Update_Audio, EveryFrame, 100.00f, 0, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Convert::Add_XtoTEXAconverter"), &AudioRes.pAdd_XtoTEXAconverter, &Add_XtoTEXAconverter, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Convert::Add_TEXAtoXconverter"), &AudioRes.pAdd_TEXAtoXconverter, &Add_TEXAtoXconverter, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Convert::Remove_XtoTEXAconverter"), &AudioRes.pRemove_XtoTEXAconverter, &Remove_XtoTEXAconverter, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Convert::Remove_TEXAtoXconverter"), &AudioRes.pRemove_TEXAtoXconverter, &Remove_TEXAtoXconverter, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Convert::XtoTEXA"), &AudioRes.pXtoTEXA, &XtoTEXA, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Convert::TEXAtoX"), &AudioRes.pTEXAtoX, &TEXAtoX, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Effects::Register_AudioEffectSignature"), &AudioRes.pRegister_AudioEffectSignature, &Register_AudioEffectSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Effects::DeRegister_AudioEffectSignature"), &AudioRes.pDeRegister_AudioEffectSignature, &DeRegister_AudioEffectSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Effects::Find_AudioEffectSignature"), &AudioRes.pFind_AudioEffectSignature, &Find_AudioEffectSignature, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Effects::Get_AudioEffect"), &AudioRes.pGet_AudioEffect, &Get_AudioEffect, (CallFlagBits)NULL, 0.0f, NULL, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Get_FormatDetails"), &AudioRes.pGet_FormatDetails, &Get_FormatDetails, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Start_InputStream"), &AudioRes.pStart_InputStream, &Start_InputStream, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Start_OutputStream"), &AudioRes.pStart_OutputStream, &Start_OutputStream, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Pause_InputStream"), &AudioRes.pPause_InputStream, &Pause_InputStream, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Pause_OutputStream"), &AudioRes.pPause_OutputStream, &Pause_OutputStream, (CallFlagBits)NULL, 0.0f, NULL, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Convert_AudioData"), &AudioRes.pConvert_AudioData, &Convert_AudioData, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Audio::Create_DummyTEXA"), &AudioRes.pCreate_DummyTEXA, &Create_DummyTEXA, (CallFlagBits)NULL, 0.0f, NULL, NULL);
}





#pragma once
//C
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//Third-Party
#include <atomic\atomic.h>
#include <json/zzzjson.h>
//ours
#include "Extension.h"
#include "Object.h"
#define TEX_EXPOSE_GRAPHICS
#include "Graphics.h"
#include "GraphicsEffects.h"
#include "Audio.h"
#include "GUI.h"
#define TEX_EXPOSE_FORMATS
#include "Formats.h"

volatile FormatUtils Utils;

GraphicsFormat Convert_ComponentType(GL_ComponentType componenttype) {
	switch (componenttype)
	{
	case GL_ComponentType_BYTE: //BYTE
		return GraphicsFormat_R8G8B8_SINT;
	case GL_ComponentType_UNSIGNED_BYTE: //UNSIGNED_BYTE
		return GraphicsFormat_R8G8B8_UINT;
	case GL_ComponentType_SHORT: //SHORT
		return GraphicsFormat_R16G16B16_SINT;
	case GL_ComponentType_UNSIGNED_SHORT: //UNSIGNED_SHORT
		return GraphicsFormat_R16G16B16_UINT;
	case GL_ComponentType_INT: //SIGNED_INT:
		return GraphicsFormat_R32G32B32_SINT;
	case GL_ComponentType_UNSIGNED_INT: //UNSIGNED_INT:
		return GraphicsFormat_R32G32B32_UINT;
	case GL_ComponentType_FLOAT: //FLOAT
		return GraphicsFormat_R32G32B32_SFLOAT;
	}
}

const char base64_map[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
					 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
					 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
					 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' 
};

char* base64_encode(char* plain) {
	char counts = 0;
	char buffer[3] = { sizeof(*buffer) * 3};
	char* cipher = malloc(strlen(plain) * 4 / 3 + 4);
	int i = 0, c = 0;

	for (i = 0; plain[i] != '\0'; i++) {
		buffer[counts++] = plain[i];
		if (counts == 3) {
			cipher[c++] = base64_map[buffer[0] >> 2];
			cipher[c++] = base64_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
			cipher[c++] = base64_map[((buffer[1] & 0x0f) << 2) + (buffer[2] >> 6)];
			cipher[c++] = base64_map[buffer[2] & 0x3f];
			counts = 0;
		}
	}

	if (counts > 0) {
		cipher[c++] = base64_map[buffer[0] >> 2];
		if (counts == 1) {
			cipher[c++] = base64_map[(buffer[0] & 0x03) << 4];
			cipher[c++] = '=';
		}
		else {                      // if counts == 2
			cipher[c++] = base64_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
			cipher[c++] = base64_map[(buffer[1] & 0x0f) << 2];
		}
		cipher[c++] = '=';
	}

	cipher[c] = '\0';   /* string padding character */
	return cipher;
}

TEXRESULT Decode_URI(FileData* filedata, const UTF8* URI, const UTF8* basefileloc, UTF8** returnmimetype)
{
	if (strncmp((char*)URI, "data", 4) == 0)
	{
		uint64_t mimetypestartindex = Find_First_Of(URI, "/") + (uint64_t)1;
		uint64_t mimetypesize = Find_First_Of(URI, ";") - mimetypestartindex;

		uint64_t base64startindex = Find_First_Of(URI, ",") + (uint64_t)1;
		uint64_t base64size = strlen(URI) - base64startindex;

		UTF8* base64pointer = (URI + base64startindex);

		char counts = 0;
		char buffer[4] = { sizeof(*buffer) * 4 };
		char* plain = malloc((strlen(base64pointer) * 3 / 4) + 1);
		if (plain == NULL)
			return Out_Of_Memory_Result;
		int i = 0, p = 0;

		for (i = 0; base64pointer[i] != '\0'; i++) {
			char k;
			for (k = 0; k < 64 && base64_map[k] != base64pointer[i]; k++);
			buffer[counts++] = k;
			if (counts == 4) {
				plain[p++] = (buffer[0] << 2) + (buffer[1] >> 4);
				if (buffer[2] != 64)
					plain[p++] = (buffer[1] << 4) + (buffer[2] >> 2);
				if (buffer[3] != 64)
					plain[p++] = (buffer[2] << 6) + buffer[3];
				counts = 0;
			}
		}

		plain[p] = '\0';    /* string padding character */

		filedata->pData = plain;
		filedata->LinearSize = p + (uint64_t)1;

		*returnmimetype = malloc(mimetypesize + (uint64_t)1);
		UTF8* returnmimetyp = *returnmimetype;
		memcpy(returnmimetyp, (void*)((uint64_t)URI + mimetypestartindex), mimetypesize);
		returnmimetyp[mimetypesize] = '\0';
	}
	else
	{
		const UTF8* toreplace = (UTF8*)"/";

		const UTF8* replacement = (UTF8*)"\\";

		const UTF8* productf = FindAndReplace(URI, toreplace, replacement);

		UTF8* product = (UTF8*)malloc(sizeof(UTF8) * (strlen((char*)basefileloc) + strlen((char*)productf) + 1));
		if (product == NULL)
			return Out_Of_Memory_Result;

		memcpy((void*)product, basefileloc, strlen((char*)basefileloc));
		memcpy((void*)(product + strlen((char*)basefileloc)), productf, strlen((char*)productf));

		product[strlen((char*)basefileloc) + strlen((char*)productf)] = '\0';

		*returnmimetype = Get_FilePathExtension(URI);

		Open_Data(filedata, product);
	}
	return (Success);
}

TEXRESULT Parse_Buffer(Value* value, ResourceHeaderAllocation* pAllocation, const UTF8* BaseDirectory, const void* BinaryData, ResourceHeaderAllocation iGraphicsWindow, uint32_t ThreadIndex) {
	TEXRESULT res = (Success);

	ResourceHeaderAllocation iBufferSource;
	{
		RHeaderBufferSourceCreateInfo CreateInfo;
		memset(&CreateInfo, 0, sizeof(CreateInfo));

		if (ObjGet(value, "byteLength") != NULL)
		{
			Value* byteLengthV = ObjGet(value, "byteLength");
			CreateInfo.Data.LinearSize = *GetLongLong(byteLengthV);
		}
		else return (Failure);

		if (ObjGet(value, "uri") != NULL)
		{
			Value* uriV = ObjGet(value, "uri");
			UTF8* returnmimetype = NULL;
			Decode_URI(&CreateInfo.Data, GetStr(uriV), BaseDirectory, &returnmimetype);

			if (returnmimetype != NULL)
				free(returnmimetype);
		}
		else //if file glb
		{
			if (BinaryData != NULL)
			{
				CreateInfo.Data.pData = (unsigned char*)malloc(sizeof(char) * CreateInfo.Data.LinearSize);
				if (CreateInfo.Data.pData == NULL)
					return (Out_Of_Memory_Result | Failure);
				memcpy(CreateInfo.Data.pData, BinaryData, CreateInfo.Data.LinearSize);
			}
			else return (Failure);
		}

		ResourceHeaderCreateInfo MainCreateInfo;
		memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
		MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_BufferSource;
		if (ObjGet(value, "name") != NULL)
			MainCreateInfo.Name = GetStr(ObjGet(value, "name"));
		if ((res = Object_Ref_Create_ResourceHeader(&iBufferSource, MainCreateInfo, &CreateInfo, ThreadIndex)) != (Success))
			return res;

		free(CreateInfo.Data.pData);
	}

	{
		RHeaderBufferCreateInfo CreateInfo;
		memset(&CreateInfo, 0, sizeof(CreateInfo));
		CreateInfo.iGraphicsWindow = iGraphicsWindow;
		CreateInfo.iBufferSource = iBufferSource;
		CreateInfo.AllocationType = AllocationType_Linear;
		//CreateInfo.BufferUsage = ;
		ResourceHeaderCreateInfo MainCreateInfo;
		memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
		MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Buffer;
		if (ObjGet(value, "name") != NULL)
			MainCreateInfo.Name = GetStr(ObjGet(value, "name"));
		if ((res = Object_Ref_Create_ResourceHeader(pAllocation, MainCreateInfo, &CreateInfo, ThreadIndex)) != (Success))
			return res;
	}
	return (Success);
}

TEXRESULT Parse_Image(Value* value, ResourceHeaderAllocation* pAllocation, const UTF8* BaseDirectory, Value* Basevalue, const ResourceHeaderAllocation* BufferArray, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);
	FileData pData;

	RHeaderImageSourceCreateInfo CreateInfo;
	memset(&CreateInfo, 0, sizeof(CreateInfo));

	UTF8* mimetype = NULL;
	if (ObjGet(value, "uri") != NULL)
	{
		if ((res = Decode_URI(&pData, GetStr(ObjGet(value, "uri")), BaseDirectory, &mimetype)) != (Success))
			return res;
	}
	if (ObjGet(value, "bufferView") != NULL)
	{
		Value* bufferViewV = ObjGet(value, "bufferView");
		Value* bufferViewsV = ObjGet(Basevalue, "bufferViews");
		Value* bufferViewActualV = ArrayGet(bufferViewsV, *GetLongLong(bufferViewV));	

		RHeaderBuffer* pBuffer = Object_Ref_Get_ResourceHeaderPointer(BufferArray[*GetLongLong(ObjGet(bufferViewActualV, "buffer"))], false, false, ThreadIndex);
		RHeaderBufferSource* pBufferSource = Object_Ref_Get_ResourceHeaderPointer(pBuffer->iBufferSource, false, false, ThreadIndex);

		pData.pData = (unsigned char*)((uint64_t)pBufferSource->Data.pData + (uint64_t)*GetLongLong(ObjGet(bufferViewActualV, "byteOffset")));
		pData.LinearSize = *GetLongLong(ObjGet(bufferViewActualV, "byteLength"));

		Object_Ref_End_ResourceHeaderPointer(pBuffer->iBufferSource, false, false, ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(BufferArray[*GetLongLong(ObjGet(bufferViewActualV, "buffer"))], false, false, ThreadIndex);
	}
	if (pData.pData != NULL && pData.LinearSize != NULL)
	{
		if (ObjGet(value, "mimeType") != NULL)
		{
			free(mimetype);
			Value* mimeTypeV = ObjGet(value, "mimeType");

			uint64_t lastof = Find_Last_Of(GetStr(mimeTypeV), (UTF8*)"/");
			uint64_t filenamelen = strlen(GetStr(mimeTypeV));

			mimetype = (UTF8*)malloc(sizeof(UTF8) * ((filenamelen - lastof) + (uint64_t)1));
			memcpy((void*)mimetype, GetStr(mimeTypeV) + lastof, sizeof(UTF8) * ((filenamelen - lastof) + (uint64_t)1));
			mimetype[(filenamelen - lastof)] = '\0';
		}
		uint32_t identifier = *((uint32_t*)((uint64_t)mimetype + sizeof(char)));
		if ((res = Graphics_Convert_Ref_XtoTEXI(&pData, &CreateInfo.ImageData, identifier)) != (Success))
			return res;

		ResourceHeaderCreateInfo MainCreateInfo;
		memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
		MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_ImageSource;
		MainCreateInfo.Name = NULL;
		if ((res = Object_Ref_Create_ResourceHeader(pAllocation, MainCreateInfo, &CreateInfo, ThreadIndex)) != (Success))
			return res;
		free(CreateInfo.ImageData);
		free(mimetype);
	}
	else
		return (Failure);

	return (Success);
}
TEXRESULT Parse_Sampler(Value* value, RHeaderTextureCreateInfo* pResult)
{
	if (ObjGet(value, "magFilter") != NULL)
	{
		Value* magFilterV = ObjGet(value, "magFilter");
		switch (*GetInt(magFilterV))
		{
		case 9728: //GL_NEAREST
			pResult->MagFilter = TextureFilterMode_Nearest;
			break;
		case 9729: //GL_LINEAR
			pResult->MagFilter = TextureFilterMode_Linear;
			break;
		}
	}
	if (ObjGet(value, "minFilter") != NULL)
	{
		Value* minFilterV = ObjGet(value, "minFilter");
		switch (*GetInt(minFilterV))
		{
		case 9728: //GL_NEAREST
			pResult->MinFilter = TextureFilterMode_Nearest;
			break;
		case 9729: //GL_LINEAR
			pResult->MinFilter = TextureFilterMode_Linear;
			break;
		}
	}
	if (ObjGet(value, "wrapS") != NULL)
	{
		Value* wrapSV = ObjGet(value, "wrapS");
		switch (*GetInt(wrapSV))
		{
		case 33071: //GL_CLAMP_TO_EDGE
			pResult->AddressModeU = TextureAddressMode_ClampToEdge;
			break;
		case 33648: //GL_MIRRORED_REPEAT
			pResult->AddressModeU = TextureAddressMode_MirroredRepeat;
			break;
		case 10497: //GL_REPEAT
			pResult->AddressModeU = TextureAddressMode_Repeat;
			break;
		}
	}
	if (ObjGet(value, "wrapT") != NULL)
	{
		Value* wrapTV = ObjGet(value, "wrapT");
		switch (*GetInt(wrapTV))
		{
		case 33071: //GL_CLAMP_TO_EDGE
			pResult->AddressModeV = TextureAddressMode_ClampToEdge;
			break;
		case 33648: //GL_MIRRORED_REPEAT
			pResult->AddressModeV = TextureAddressMode_MirroredRepeat;
			break;
		case 10497: //GL_REPEAT
			pResult->AddressModeV = TextureAddressMode_Repeat;
			break;
		}
	}
	pResult->AddressModeW = pResult->AddressModeV;

	return (Success);
}
TEXRESULT Parse_Texture(Value* value, ResourceHeaderAllocation* pAllocation, Value* Basevalue, const UTF8* BaseDirectory, const ResourceHeaderAllocation* BufferArray, ResourceHeaderAllocation iGraphicsWindow, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);

	RHeaderTextureCreateInfo CreateInfo;
	memset(&CreateInfo, 0, sizeof(CreateInfo));
	if (ObjGet(value, "sampler") != NULL)
	{
		Value* samplerV = ObjGet(value, "sampler");
		Value* samplersV = ObjGet(Basevalue, "samplers");	
		if ((res = Parse_Sampler(ArrayGet(samplersV, *GetLongLong(samplerV)), &CreateInfo)) != (Success))
			return res;
	}

	if (ObjGet(value, "source") != NULL)
	{
		ResourceHeaderAllocation iImageSource;

		Value* sourceV = ObjGet(value, "source");
		Value* imagesV = ObjGet(Basevalue, "images");
		if ((res = Parse_Image(ArrayGet(imagesV, *GetLongLong(sourceV)), &iImageSource, BaseDirectory, Basevalue, BufferArray, ThreadIndex)) != (Success))
			return res;

		CreateInfo.iGraphicsWindow = iGraphicsWindow;
		CreateInfo.iImageSource = iImageSource;
		CreateInfo.AllocationType = AllocationType_Linear;
		CreateInfo.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit);
		ResourceHeaderCreateInfo MainCreateInfo;
		memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
		MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
		if (ObjGet(value, "name") != NULL)
			MainCreateInfo.Name = GetStr(ObjGet(value, "name"));
		if ((res = Object_Ref_Create_ResourceHeader(pAllocation, MainCreateInfo, &CreateInfo, ThreadIndex)) != (Success))
			return res;
	}
	else
		return (Failure);


	return (Success);
}

TEXRESULT Parse_Material(Value* value, ResourceHeaderAllocation* pAllocation, const ResourceHeaderAllocation* TexturesArray, ResourceHeaderAllocation iGraphicsWindow, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);
	RHeaderMaterialCreateInfo CreateInfo;
	memset(&CreateInfo, 0, sizeof(CreateInfo));
	CreateInfo.iGraphicsWindow = iGraphicsWindow;

	CreateInfo.BaseColourMode = MaterialMode_Solid;

	if (ObjGet(value, "emissiveFactor") != NULL)
		for (size_t i1 = 0; i1 < 3; i1++)
			CreateInfo.EmissiveFactor[i1] = *GetNum(ArrayGet(ObjGet(value, "emissiveFactor"), i1));

	if (ObjGet(value, "alphaMode") != NULL)
	{
		switch (*((uint32_t*)GetStr(ObjGet(value, "alphaMode"))))
		{
		case 0x45555141: // OPAQUE
			CreateInfo.AlphaMode = AlphaMode_Opaque;
			break;
		case 0x4b53414d: //MASK
			CreateInfo.AlphaMode = AlphaMode_Mask;
			break;
		case 0x444e454c42: //BLEND
			CreateInfo.AlphaMode = AlphaMode_Blend;
			break;
		}
	}

	if (ObjGet(value, "alphaCutoff") != NULL)
		CreateInfo.AlphaCutoff = *GetNum(ObjGet(value, "alphaCutoff"));
	else
		CreateInfo.AlphaCutoff = 0.5;

	if (ObjGet(value, "doubleSided") != NULL)
		CreateInfo.DoubleSided = *GetBool(ObjGet(value, "doubleSided"));

	if (ObjGet(value, "pbrMetallicRoughness") != NULL)
	{
		Value* pbrMetallicRoughnessV = ObjGet(value, "pbrMetallicRoughness");

		if (ObjGet(pbrMetallicRoughnessV, "baseColorFactor") != NULL)
			for (size_t i1 = 0; i1 < 4; i1++)
				CreateInfo.BaseColourFactor[i1] = *GetNum(ArrayGet(ObjGet(pbrMetallicRoughnessV, "baseColorFactor"), i1));
		else
			for (size_t i1 = 0; i1 < 4; i1++)
				CreateInfo.BaseColourFactor[i1] = 1.0f;

		if (ObjGet(pbrMetallicRoughnessV, "metallicFactor") != NULL)
			CreateInfo.MetallicFactor = *GetNum(ObjGet(pbrMetallicRoughnessV, "metallicFactor"));
		else
			CreateInfo.MetallicFactor = 1;

		if (ObjGet(pbrMetallicRoughnessV, "roughnessFactor") != NULL)
			CreateInfo.RoughnessFactor = *GetNum(ObjGet(pbrMetallicRoughnessV, "metallicFactor"));
		else
			CreateInfo.RoughnessFactor = 1;

		if (ObjGet(pbrMetallicRoughnessV, "baseColorTexture") != NULL)
		{
			Value* baseColorTextureV = ObjGet(pbrMetallicRoughnessV, "baseColorTexture");
			if (ObjGet(baseColorTextureV, "texCoord") != NULL)
				CreateInfo.BaseColourTexture.UVIndex = *GetLongLong(ObjGet(baseColorTextureV, "texCoord"));
			if (ObjGet(baseColorTextureV, "index") != NULL)
				CreateInfo.BaseColourTexture.iTexture = TexturesArray[*GetLongLong(ObjGet(baseColorTextureV, "index"))];
			CreateInfo.BaseColourMode = MaterialMode_Colour;
		}

		if (ObjGet(pbrMetallicRoughnessV, "metallicRoughnessTexture") != NULL)
		{
			Value* metallicRoughnessTextureV = ObjGet(pbrMetallicRoughnessV, "metallicRoughnessTexture");
			if (ObjGet(metallicRoughnessTextureV, "texCoord") != NULL)
				CreateInfo.MetallicRoughnessTexture.UVIndex = *GetLongLong(ObjGet(metallicRoughnessTextureV, "texCoord"));
			if (ObjGet(metallicRoughnessTextureV, "index") != NULL)
				CreateInfo.MetallicRoughnessTexture.iTexture = TexturesArray[*GetLongLong(ObjGet(metallicRoughnessTextureV, "index"))];
			CreateInfo.BaseColourMode = MaterialMode_Colour;
		}
	}

	if (ObjGet(value, "normalTexture") != NULL)
	{
		Value* normalTextureV = ObjGet(value, "normalTexture");
		if (ObjGet(normalTextureV, "texCoord") != NULL)
			CreateInfo.NormalTexture.UVIndex = *GetLongLong(ObjGet(normalTextureV, "texCoord"));
		if (ObjGet(normalTextureV, "index") != NULL)
			CreateInfo.NormalTexture.iTexture = TexturesArray[*GetLongLong(ObjGet(normalTextureV, "index"))];
		if (ObjGet(normalTextureV, "scale") != NULL)
			CreateInfo.NormalScale = *GetNum(ObjGet(normalTextureV, "scale"));
		CreateInfo.BaseColourMode = MaterialMode_Colour;
	}
	if (ObjGet(value, "occlusionTexture") != NULL)
	{
		Value* occlusionTextureV = ObjGet(value, "occlusionTexture");
		if (ObjGet(occlusionTextureV, "texCoord") != NULL)
			CreateInfo.OcclusionTexture.UVIndex = *GetLongLong(ObjGet(occlusionTextureV, "texCoord"));
		if (ObjGet(occlusionTextureV, "index") != NULL)
			CreateInfo.OcclusionTexture.iTexture = TexturesArray[*GetLongLong(ObjGet(occlusionTextureV, "index"))];
		if (ObjGet(occlusionTextureV, "strength") != NULL)
			CreateInfo.OcclusionStrength = *GetNum(ObjGet(occlusionTextureV, "strength"));
		CreateInfo.BaseColourMode = MaterialMode_Colour;
	}
	if (ObjGet(value, "emissiveTexture") != NULL)
	{
		Value* emissiveTextureV = ObjGet(value, "emissiveTexture");
		if (ObjGet(emissiveTextureV, "texCoord") != NULL)
			CreateInfo.EmissiveTexture.UVIndex = *GetLongLong(ObjGet(emissiveTextureV, "texCoord"));
		if (ObjGet(emissiveTextureV, "index") != NULL)
			CreateInfo.EmissiveTexture.iTexture = TexturesArray[*GetLongLong(ObjGet(emissiveTextureV, "index"))];
		CreateInfo.BaseColourMode = MaterialMode_Colour;
	}

	ResourceHeaderCreateInfo MainCreateInfo;
	memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
	MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
	if (ObjGet(value, "name") != NULL)
		MainCreateInfo.Name = GetStr(ObjGet(value, "name"));
	if ((res = Object_Ref_Create_ResourceHeader(pAllocation, MainCreateInfo, &CreateInfo, ThreadIndex)) != (Success))
		return res;

	return (Success);
}

TEXRESULT Parse_Accessor(Value* value, Accessor* pResult, Value* Basevalue, const ResourceHeaderAllocation* BufferArray, ResourceHeaderAllocation iGraphicsWindow, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);
	//if (Basevalue["bufferViews"][value["bufferView"].GetInt64()].HasMember("byteLength"))
	//	pResult->ByteLength = Basevalue["bufferViews"][value["bufferView"].GetInt64()]["byteLength"].GetInt64();
	//else return (Failure);
	//Basevalue["bufferViews"][value["bufferView"].GetInt64()]
	Value* bufferviewactualV = ArrayGet(ObjGet(Basevalue, "bufferViews"), *GetLongLong(ObjGet(value, "bufferView")));
	
	if (ObjGet(bufferviewactualV, "byteStride"))
		pResult->ByteStride = *GetLongLong(ObjGet(bufferviewactualV, "byteStride"));

	if (ObjGet(bufferviewactualV, "byteOffset"))
		pResult->ByteOffset = *GetLongLong(ObjGet(bufferviewactualV, "byteOffset"));
	//printf("bufferviewindex %i %i\n", value["bufferView"].GetInt64(), Basevalue["bufferViews"][value["bufferView"].GetInt64()]["byteOffset"].GetInt64());
	//if (value.HasMember("target"))
	//	printf("target unsupported vareiable not opengl lol\n");

	if (ObjGet(bufferviewactualV, "buffer"))
		pResult->iBuffer = BufferArray[*GetLongLong(ObjGet(bufferviewactualV, "buffer"))];
	else return (Failure);

	if (ObjGet(value, "byteOffset") != NULL)
		pResult->ByteOffset += *GetLongLong(ObjGet(value, "byteOffset"));

	if (ObjGet(value, "normalized") != NULL)
		pResult->Normalized = *GetBool(ObjGet(value, "normalized"));
	else
		pResult->Normalized = false;

	if (ObjGet(value, "componentType") != NULL)
		pResult->Format = Convert_ComponentType(*GetInt(ObjGet(value, "componentType")));
	else return (Failure);

	if (ObjGet(value, "count") != NULL)
		pResult->Count = *GetLongLong(ObjGet(value, "count"));
	else return (Failure);

	if (ObjGet(value, "type") != NULL)
	{
		switch (*(AccessorType*)GetStr(ObjGet(value, "type")))
		{
		case (AccessorType)0x4c414353:
			pResult->Type = AccessorType_SCALAR;
			break;
		case (AccessorType)0x32434556:
			pResult->Type = AccessorType_VEC2;
			break;
		case (AccessorType)0x33434556:
			pResult->Type = AccessorType_VEC3;
			break;
		case (AccessorType)0x34434556:
			pResult->Type = AccessorType_VEC4;
			break;
		case (AccessorType)0x3254414d:
			pResult->Type = AccessorType_MAT2;
			break;
		case (AccessorType)0x3354414d:
			pResult->Type = AccessorType_MAT3;
			break;
		case (AccessorType)0x3454414d:
			pResult->Type = AccessorType_MAT4;
			break;
		}
	}
	else return (Failure);

	pResult->Inputrate = AttributeInputRate_Vertex;

	//convert sparse to normal
	if (ObjGet(value, "sparse") != NULL)  {		
		Value* sparseV = ObjGet(value, "sparse");
		struct Sparse
		{
			uint64_t Count;
			struct
			{
				uint64_t ByteOffset;
				uint64_t  BufferView;
				//RHeaderBufferView* BufferView;
				GL_ComponentType componenttype;
			}Indices;
			struct
			{
				uint64_t ByteOffset;
				uint64_t BufferView;
				//RHeaderBufferView* BufferView;
			}Values;
		}sparse;
		memset(&sparse, 0, sizeof(sparse));


		if (ObjGet(sparseV, "count") != NULL)
			sparse.Count = *GetLongLong(ObjGet(sparseV, "count"));
		else return (Failure);

		if (ObjGet(sparseV, "indices") != NULL)
		{
			Value* indicesV = ObjGet(sparseV, "indices");
			if (ObjGet(indicesV, "byteOffset"))
				sparse.Indices.ByteOffset = *GetLongLong(ObjGet(indicesV, "byteOffset"));

			if (ObjGet(indicesV, "bufferView"))
				sparse.Indices.BufferView = *GetLongLong(ObjGet(indicesV, "bufferView"));
			else return (Failure);

			if (ObjGet(indicesV, "componentType"))
				sparse.Indices.componenttype = *GetLongLong(ObjGet(indicesV, "componentType"));
			else return (Failure);
		}
		else return (Failure);

		if (ObjGet(sparseV, "values") != NULL)
		{
			Value* valuesV = ObjGet(sparseV, "values");
			if (ObjGet(valuesV, "byteOffset"))
				sparse.Values.ByteOffset = *GetLongLong(ObjGet(valuesV, "byteOffset"));

			if (ObjGet(valuesV, "bufferView"))
				sparse.Values.BufferView = *GetLongLong(ObjGet(valuesV, "bufferView"));
			else return (Failure);
		}
		else return (Failure);

		//create new buffer and bufferview

		uint32_t stride = NULL;
		if (pResult->ByteStride != NULL)
			stride = pResult->ByteStride;
		else
			stride = ((GraphicsFormatBitsPerChannels[(uint32_t)pResult->Format][0] / 8) * (uint32_t)pResult->Type);

		FileData NewSource = {0, 0};
		NewSource.LinearSize = pResult->Count * stride;
		NewSource.pData = (unsigned char*)malloc(NewSource.LinearSize);


		RHeaderBuffer* pOldBuffer = Object_Ref_Get_ResourceHeaderPointer(pResult->iBuffer, false, false, ThreadIndex);
		RHeaderBufferSource* pOldBufferSource = Object_Ref_Get_ResourceHeaderPointer(pOldBuffer->iBufferSource, false, false, ThreadIndex);

		if (ObjGet(value, "bufferView") != NULL)
			memcpy(NewSource.pData, (void*)((uint64_t)pOldBufferSource->Data.pData + (uint64_t)pResult->ByteOffset), NewSource.LinearSize);
		else
			memset(NewSource.pData, 0, NewSource.LinearSize);

		//apply sparse
		//Basevalue["bufferViews"][sparse.Indices.BufferView]
		Value* sparseindicesbufferView = ArrayGet(ObjGet(Basevalue, "bufferViews"), sparse.Indices.BufferView);
		//Basevalue["bufferViews"][sparse.Values.BufferView]
		Value* sparsevaluesbufferView = ArrayGet(ObjGet(Basevalue, "bufferViews"), sparse.Values.BufferView);

		RHeaderBuffer* pIndicesBuffer = Object_Ref_Get_ResourceHeaderPointer(BufferArray[*GetLongLong(ObjGet(sparseindicesbufferView, "buffer"))], false, false, ThreadIndex);
		RHeaderBuffer* pValuesBuffer = Object_Ref_Get_ResourceHeaderPointer(BufferArray[*GetLongLong(ObjGet(sparsevaluesbufferView, "buffer"))], false, false, ThreadIndex);

		RHeaderBufferSource* pIndicesBufferSource = Object_Ref_Get_ResourceHeaderPointer(pIndicesBuffer->iBufferSource, false, false, ThreadIndex);
		RHeaderBufferSource* pValuesBufferSource = Object_Ref_Get_ResourceHeaderPointer(pValuesBuffer->iBufferSource, false, false, ThreadIndex);

		if (pOldBuffer == NULL)
		{
			Engine_Ref_FunctionError("Parse_Accessor", "pOldBuffer Invalid.", 0);
		}
		if (pOldBufferSource == NULL)
		{
			Engine_Ref_FunctionError("Parse_Accessor", "pOldBufferSource Invalid.", 0);
		}
		if (pIndicesBuffer == NULL)
		{
			Engine_Ref_FunctionError("Parse_Accessor", "pIndicesBuffer Invalid.", 0);
		}
		if (pValuesBuffer == NULL)
		{
			Engine_Ref_FunctionError("Parse_Accessor", "pValuesBuffer Invalid.", 0);
		}
		if (pIndicesBufferSource == NULL)
		{
			Engine_Ref_FunctionError("Parse_Accessor", "pIndicesBufferSource Invalid.", 0);
		}
		if (pValuesBufferSource == NULL)
		{
			Engine_Ref_FunctionError("Parse_Accessor", "pValuesBufferSource Invalid.", 0);
		}


		uint8_t* indicesdata = (uint8_t*)((uint64_t)pIndicesBufferSource->Data.pData + (uint64_t)*GetLongLong(ObjGet(sparseindicesbufferView, "byteOffset")) + (uint64_t)sparse.Indices.ByteOffset);
		uint8_t* valuesdata = (uint8_t*)((uint64_t)pValuesBufferSource->Data.pData + (uint64_t)*GetLongLong(ObjGet(sparsevaluesbufferView, "byteOffset")) + (uint64_t)sparse.Values.ByteOffset);


		uint8_t* pdst = (uint8_t*)((uint64_t)NewSource.pData);

		switch (sparse.Indices.componenttype)
		{
		case GL_ComponentType_BYTE: //BYTE
			for (size_t i1 = 0; i1 < sparse.Count; i1++)
				memcpy(&pdst[((int8_t*)indicesdata)[i1] * stride], &valuesdata[i1 * stride], stride);
			break;
		case GL_ComponentType_UNSIGNED_BYTE: //UNSIGNED_BYTE
			for (size_t i1 = 0; i1 < sparse.Count; i1++)
				memcpy(&pdst[((uint8_t*)indicesdata)[i1] * stride], &valuesdata[i1 * stride], stride);
			break;
		case GL_ComponentType_SHORT: //SHORT
			for (size_t i1 = 0; i1 < sparse.Count; i1++)
				memcpy(&pdst[((int16_t*)indicesdata)[i1] * stride], &valuesdata[i1 * stride], stride);
			break;
		case GL_ComponentType_UNSIGNED_SHORT: //UNSIGNED_SHORT
			for (size_t i1 = 0; i1 < sparse.Count; i1++)
				memcpy(&pdst[((uint16_t*)indicesdata)[i1] * stride], &valuesdata[i1 * stride], stride);
			break;
		case GL_ComponentType_INT: //SIGNED_INT:
			for (size_t i1 = 0; i1 < sparse.Count; i1++)
				memcpy(&pdst[((int32_t*)indicesdata)[i1] * stride], &valuesdata[i1 * stride], stride);
			break;
		case GL_ComponentType_UNSIGNED_INT: //UNSIGNED_INT:
			for (size_t i1 = 0; i1 < sparse.Count; i1++)
				memcpy(&pdst[((uint32_t*)indicesdata)[i1] * stride], &valuesdata[i1 * stride], stride);
			break;
		}



		Object_Ref_End_ResourceHeaderPointer(pOldBuffer->Header.Allocation, false, false, ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(pOldBufferSource->Header.Allocation, false, false, ThreadIndex);

		Object_Ref_End_ResourceHeaderPointer(pIndicesBuffer->Header.Allocation, false, false, ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(pValuesBuffer->Header.Allocation, false, false, ThreadIndex);

		Object_Ref_End_ResourceHeaderPointer(pIndicesBufferSource->Header.Allocation, false, false, ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(pValuesBufferSource->Header.Allocation, false, false, ThreadIndex);

		ResourceHeaderAllocation iBufferSource;
		{
			RHeaderBufferSourceCreateInfo BufferSourceCreateInfo;
			memset(&BufferSourceCreateInfo, 0, sizeof(BufferSourceCreateInfo));
			BufferSourceCreateInfo.Data.LinearSize = NewSource.LinearSize;
			BufferSourceCreateInfo.Data.pData = NewSource.pData;
			ResourceHeaderCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_BufferSource;
			MainCreateInfo.Name = NULL;
			if ((res = Object_Ref_Create_ResourceHeader(&iBufferSource, MainCreateInfo, &BufferSourceCreateInfo, ThreadIndex)) != (Success))
				return res;
			free(BufferSourceCreateInfo.Data.pData);
		}

		ResourceHeaderAllocation iBuffer;
		{
			RHeaderBufferCreateInfo BufferCreateInfo;
			memset(&BufferCreateInfo, 0, sizeof(BufferCreateInfo));
			BufferCreateInfo.iBufferSource = iBufferSource;
			BufferCreateInfo.AllocationType = AllocationType_Linear;
			BufferCreateInfo.iGraphicsWindow = iGraphicsWindow;
			ResourceHeaderCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Buffer;
			MainCreateInfo.Name = NULL;
			if ((res = Object_Ref_Create_ResourceHeader(&iBuffer, MainCreateInfo, &BufferCreateInfo, ThreadIndex)) != (Success))
				return res;
		}

		//pResult->ByteLength = NewSource.LinearSize;

		pResult->ByteStride = stride;
		pResult->ByteOffset = 0;
		pResult->iBuffer = iBuffer;
	}
	
	return (Success);
}

TEXRESULT Parse_AnimationSampler(Value* value, RHeaderAnimationChannelCreateInfo* pResult, Value* Basevalue, const ResourceHeaderAllocation* BufferArray, ResourceHeaderAllocation iGraphicsWindow, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);

	if (ObjGet(value, "input") != NULL)
	{
		Value* inputV = ObjGet(value, "input");
		Value* accessorsV = ObjGet(Basevalue, "accessors");
		if ((res = Parse_Accessor(ArrayGet(accessorsV, *GetLongLong(inputV)), &pResult->Sampler.Input, Basevalue, BufferArray, iGraphicsWindow, ThreadIndex)) != (Success))
			return res;
	}
	else
		return (Failure);
	if (ObjGet(value, "output") != NULL)
	{
		Value* outputV = ObjGet(value, "output");
		Value* accessorsV = ObjGet(Basevalue, "accessors");
		if ((res = Parse_Accessor(ArrayGet(accessorsV, *GetLongLong(outputV)), &pResult->Sampler.Output, Basevalue, BufferArray, iGraphicsWindow, ThreadIndex)) != (Success))
			return res;
	}
	else
		return (Failure);

	if (ObjGet(value, "interpolation") != NULL)
	{
		Value* interpolationV = ObjGet(value, "interpolation");
		if (strncmp("LINEAR", GetStr(interpolationV), 6) == 0)
			pResult->Sampler.Interpolation = InterpolationType_Linear;
		if (strncmp("STEP", GetStr(interpolationV), 4) == 0)
			pResult->Sampler.Interpolation = InterpolationType_Step;
		if (strncmp("CUBICSPLINE", GetStr(interpolationV), 11) == 0)
			pResult->Sampler.Interpolation = InterpolationType_Cubicspline;
	}
	else
		pResult->Sampler.Interpolation = InterpolationType_Linear;

	return (Success);
}

TEXRESULT Parse_AnimationChannel(Value* value, ResourceHeaderAllocation* pAllocation, ResourceHeaderAllocation Parent, ObjectAllocation* Nodes,
	Value* Basevalue, Value* animationvalue, const ResourceHeaderAllocation* BufferArray, ResourceHeaderAllocation iGraphicsWindow, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);

	RHeaderAnimationChannelCreateInfo CreateInfoChannel;
	memset(&CreateInfoChannel, 0, sizeof(CreateInfoChannel));

	CreateInfoChannel.iAnimation = Parent;

	if (ObjGet(value, "target") != NULL)
	{
		Value* targetV = ObjGet(value, "target");
		if (ObjGet(targetV, "path"))
		{
			Value* pathV = ObjGet(targetV, "path");
			if (strncmp("translation", GetStr(pathV), 11) == 0)
				CreateInfoChannel.Target = AnimationTargetType_Translation;
			if (strncmp("rotation", GetStr(pathV), 9) == 0)
				CreateInfoChannel.Target = AnimationTargetType_Rotation;
			if (strncmp("scale", GetStr(pathV), 5) == 0)
				CreateInfoChannel.Target = AnimationTargetType_Scale;
			if (strncmp("weights", GetStr(pathV), 7) == 0)
				CreateInfoChannel.Target = AnimationTargetType_Weights;

		}
		else return (Failure);

	}
	else return (Failure);

	if (ObjGet(value, "sampler") != NULL)
	{
		Value* samplerV = ObjGet(value, "sampler");
		Value* samplersV = ObjGet(animationvalue, "samplers");
		if ((res = Parse_AnimationSampler(ArrayGet(samplersV, *GetLongLong(samplerV)), &CreateInfoChannel, Basevalue, BufferArray, iGraphicsWindow, ThreadIndex)) != (Success))
			return res;
	}
	else return (Failure);

	ResourceHeaderCreateInfo MainCreateInfo;
	memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
	MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_AnimationChannel;
	//MainCreateInfo.Name = ;
	if ((res = Object_Ref_Create_ResourceHeader(pAllocation, MainCreateInfo, &CreateInfoChannel, ThreadIndex)) != (Success))
		return res;

	if (ObjGet(value, "target") != NULL)
	{
		Value* targetV = ObjGet(value, "target");
		if (ObjGet(targetV, "node") != NULL)
		{
			Value* nodeV = ObjGet(targetV, "node");
			Object_Ref_Add_Object_ResourceHeaderChild(*pAllocation, Nodes[*GetLongLong(nodeV)], ThreadIndex);
		}
	}


	return (Success);
}
TEXRESULT Parse_Animation(Value* value, ResourceHeaderAllocation* pAllocation, ObjectAllocation* Nodes, Value* Basevalue, const ResourceHeaderAllocation* BufferArray, ResourceHeaderAllocation iGraphicsWindow, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);
	RHeaderAnimationCreateInfo CreateInfo;
	memset(&CreateInfo, 0, sizeof(CreateInfo));
	CreateInfo.Speed = 1.0;
	CreateInfo.PlaybackMode = AnimationPlaybackMode_Repeat;

	if (ObjGet(value, "channels") != NULL)
	{
		CreateInfo.iChannelsSize = SizeOf(ObjGet(value, "channels"));
		CreateInfo.iChannels = (ResourceHeaderAllocation*)calloc(CreateInfo.iChannelsSize, sizeof(*CreateInfo.iChannels));
	}

	ResourceHeaderCreateInfo MainCreateInfo;
	memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
	MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Animation;
	if (ObjGet(value, "name") != NULL)
		MainCreateInfo.Name = GetStr(ObjGet(value, "name"));
	if ((res = Object_Ref_Create_ResourceHeader(pAllocation, MainCreateInfo, &CreateInfo, ThreadIndex)) != (Success))
		return res;

	RHeaderAnimation* pAnimation = Object_Ref_Get_ResourceHeaderPointer(*pAllocation, true, false, ThreadIndex);
	for (size_t i = 0; i < pAnimation->iChannelsSize; i++)
	{
		ResourceHeaderAllocation iChannel;	
		if ((res = Parse_AnimationChannel(ArrayGet(ObjGet(value, "channels"), i), &iChannel, *pAllocation, Nodes, Basevalue, value, BufferArray, iGraphicsWindow, ThreadIndex)) != (Success))
			return res;
		pAnimation->iChannels[i] = iChannel;
	}
	if (CreateInfo.iChannels != NULL)
	{
		free(CreateInfo.iChannels);
	}
	Object_Ref_End_ResourceHeaderPointer(*pAllocation, true, false, ThreadIndex);
	return (Success);
}

TEXRESULT Parse_Primitive(Value* value, ElementAllocation* pAllocation, Value* Basevalue, const ResourceHeaderAllocation* MaterialArray,
	const ResourceHeaderAllocation Parent, const ResourceHeaderAllocation* BufferArray, ResourceHeaderAllocation iGraphicsWindow, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);
	ElementGraphicsCreateInfo CreateInfo;
	memset(&CreateInfo, 0, sizeof(CreateInfo));

	CreateInfo.iGraphicsWindow = iGraphicsWindow;

	GraphicsEffectCreateInfoGeneric3D Info3D;
	memset(&Info3D, 0, sizeof(Info3D));

	CreateInfo.EffectCreateInfosSize = 1;
	CreateInfo.EffectCreateInfos = (ElementGraphicsCreateInfoEffect*)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));

	CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)GraphicsEffect_Generic3D;
	CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &Info3D;

	Info3D.AttributesSize = SizeOf(ObjGet(value, "attributes"));
	if (ObjGet(value, "targets") != NULL)
		for (size_t i2 = 0; i2 < SizeOf(ObjGet(value, "targets")); i2++)
			Info3D.AttributesSize += SizeOf(ArrayGet(ObjGet(value, "targets"), i2));


	if (ObjGet(value, "material") != NULL)
	{	
		CreateInfo.iMaterial = MaterialArray[*GetLongLong(ObjGet(value, "material"))];
	}
	else
	{
		//default material
		ResourceHeaderAllocation iMaterial;
		RHeaderMaterialCreateInfo CreateInfoDefaultMaterial;
		memset(&CreateInfoDefaultMaterial, 0, sizeof(CreateInfoDefaultMaterial));
		CreateInfoDefaultMaterial.DoubleSided = true;
		CreateInfoDefaultMaterial.BaseColourMode = MaterialMode_Solid;
		CreateInfoDefaultMaterial.iGraphicsWindow = iGraphicsWindow;
		ResourceHeaderCreateInfo MainCreateInfo;
		memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
		MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
		MainCreateInfo.Name = NULL;
		Object_Ref_Create_ResourceHeader(&iMaterial, MainCreateInfo, &CreateInfoDefaultMaterial, ThreadIndex);
		CreateInfo.iMaterial = iMaterial;
	}

	if (ObjGet(value, "indices") != NULL)
	{
		Value* accessorV = ObjGet(value, "indices");
		Value* accessorsV = ObjGet(Basevalue, "accessors");
		Parse_Accessor(ArrayGet(accessorsV, *GetLongLong(accessorV)), &Info3D.Indices, Basevalue, BufferArray, iGraphicsWindow, ThreadIndex);
	}

	if (ObjGet(value, "mode") != NULL)
		if (*GetInt(ObjGet(value, "mode")) != (uint32_t)GL_PrimitiveMode_TRIANGLES)
			Engine_Ref_FunctionError("Parse_Primitive()", "Triangle Engine X will not support non triangle primitives.", 0);

	Info3D.Attributes = (Attribute*)calloc(Info3D.AttributesSize, sizeof(Attribute));

	uint32_t it = 0;
	if (ObjGet(value, "attributes") != NULL)
	{
		Value* nextV = Begin(ObjGet(value, "attributes"));
		while (nextV != 0)
		{
			Parse_Accessor(ArrayGet(ObjGet(Basevalue, "accessors"), *GetLongLong(nextV)), &Info3D.Attributes[it].Accessor, Basevalue, BufferArray, iGraphicsWindow, ThreadIndex);

			Info3D.Attributes[it].TargetGroup = 0;
			if (strncmp("POSITION", GetKey(nextV), 8) == 0)
				Info3D.Attributes[it].AttribType = AttributeType_Position;
			if (strncmp("NORMAL", GetKey(nextV), 6) == 0)
				Info3D.Attributes[it].AttribType = AttributeType_Normal;
			if (strncmp("TANGENT", GetKey(nextV), 7) == 0)
				Info3D.Attributes[it].AttribType = AttributeType_Tangent;
			if (strncmp("TEXCOORD_", GetKey(nextV), 8) == 0)
				Info3D.Attributes[it].AttribType = AttributeType_TexCoord;
			if (strncmp("COLOR_", GetKey(nextV), 6) == 0)
				Info3D.Attributes[it].AttribType = AttributeType_Colour;
			if (strncmp("JOINTS_", GetKey(nextV), 7) == 0)
				Info3D.Attributes[it].AttribType = AttributeType_Joints;
			if (strncmp("WEIGHTS_", GetKey(nextV), 8) == 0)
				Info3D.Attributes[it].AttribType = AttributeType_SkinWeights;
			it++;

			nextV = Next(nextV);
		}
	}
	else return (Failure);

	if (ObjGet(value, "targets") != NULL)
	{
		for (size_t i2 = 0; i2 < SizeOf(ObjGet(value, "targets")); i2++)
		{
			Value* nextV = Begin(ArrayGet(ObjGet(value, "targets"), i2));
			while (nextV != 0)
			{
				Parse_Accessor(ArrayGet(ObjGet(Basevalue, "accessors"), *GetLongLong(nextV)), &Info3D.Attributes[it].Accessor, Basevalue, BufferArray, iGraphicsWindow, ThreadIndex);

				Info3D.Attributes[it].TargetGroup = 1 + i2;

				if (strncmp("POSITION", GetKey(nextV), 8) == 0)
					Info3D.Attributes[it].AttribType = AttributeType_Position;
				if (strncmp("NORMAL", GetKey(nextV), 6) == 0)
					Info3D.Attributes[it].AttribType = AttributeType_Normal;
				if (strncmp("TANGENT", GetKey(nextV), 7) == 0)
					Info3D.Attributes[it].AttribType = AttributeType_Tangent;
				if (strncmp("TEXCOORD_", GetKey(nextV), 8) == 0)
					Info3D.Attributes[it].AttribType = AttributeType_TexCoord;
				if (strncmp("COLOR_", GetKey(nextV), 6) == 0)
					Info3D.Attributes[it].AttribType = AttributeType_Colour;
				if (strncmp("JOINTS_", GetKey(nextV), 7) == 0)
					Info3D.Attributes[it].AttribType = AttributeType_Joints;
				if (strncmp("WEIGHTS_", GetKey(nextV), 8) == 0)
					Info3D.Attributes[it].AttribType = AttributeType_SkinWeights;
				it++;

				nextV = Next(nextV);
			}
		}
	}

	ElementCreateInfo MainCreateInfo;
	memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
	MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
	MainCreateInfo.Name = NULL;
	if ((res = Object_Ref_Create_Element(pAllocation, MainCreateInfo, &CreateInfo, ThreadIndex)) != (Success))
		return res;
	Object_Ref_Add_ResourceHeader_ElementChild(*pAllocation, Parent, ThreadIndex);
	
	free(Info3D.Attributes);
	free(CreateInfo.EffectCreateInfos);
	return (Success);
}
TEXRESULT Parse_Mesh(Value* value, ResourceHeaderAllocation* pAllocation, Value* Basevalue, Value* NodeValue,
	const ResourceHeaderAllocation* MaterialArray, const ObjectAllocation Parent, const ResourceHeaderAllocation* BufferArray, ResourceHeaderAllocation iGraphicsWindow, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);
	{
		ResourceHeaderCreateInfo MainCreateInfo;
		memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
		MainCreateInfo.Identifier = (uint32_t)ResourceHeader_Generic;
		if (ObjGet(value, "name") != NULL)
			MainCreateInfo.Name = GetStr(ObjGet(value, "name"));
		if ((res = Object_Ref_Create_ResourceHeader(pAllocation, MainCreateInfo, NULL, ThreadIndex)) != (Success))
			return res;
		Object_Ref_Add_Object_ResourceHeaderChild(*pAllocation, Parent, ThreadIndex);
	}
	ResourceHeaderAllocation WeightsAllocation;
	{
		RHeaderWeightsCreateInfo CreateInfo;
		memset(&CreateInfo, 0, sizeof(CreateInfo));

		if (ObjGet(NodeValue, "weights") != NULL)
		{
			Value* weightsV = ObjGet(NodeValue, "weights");
			CreateInfo.WeightsSize = SizeOf(weightsV) + (size_t)1;
			CreateInfo.Weights = (float*)calloc(CreateInfo.WeightsSize, sizeof(*CreateInfo.Weights));
			CreateInfo.Weights[0] = 1.0f;
			for (size_t i1 = 0; i1 < SizeOf(weightsV); i1++)
				CreateInfo.Weights[i1 + 1] = *GetNum(ArrayGet(weightsV, i1));
		}
		else if (ObjGet(value, "weights") != NULL)
		{
			Value* weightsV = ObjGet(value, "weights");
			CreateInfo.WeightsSize = SizeOf(weightsV) + (size_t)1;
			CreateInfo.Weights = (float*)calloc(CreateInfo.WeightsSize, sizeof(*CreateInfo.Weights));
			CreateInfo.Weights[0] = 1.0f;
			for (size_t i1 = 0; i1 < SizeOf(weightsV); i1++)
				CreateInfo.Weights[i1 + 1] = *GetNum(ArrayGet(weightsV, i1));
		}
		else
		{
			CreateInfo.WeightsSize = 1;
			CreateInfo.Weights = (float*)calloc(CreateInfo.WeightsSize, sizeof(*CreateInfo.Weights));
			CreateInfo.Weights[0] = 1.0f;
		}
		ResourceHeaderCreateInfo MainCreateInfo;
		memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
		MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Weights;
		if (ObjGet(value, "name") != NULL)
			MainCreateInfo.Name = GetStr(ObjGet(value, "name"));
		if ((res = Object_Ref_Create_ResourceHeader(&WeightsAllocation, MainCreateInfo, &CreateInfo, ThreadIndex)) != (Success))
			return res;
		free(CreateInfo.Weights);
		Object_Ref_Add_Object_ResourceHeaderChild(WeightsAllocation, Parent, ThreadIndex);
	}

	if (ObjGet(value, "primitives") != NULL)
	{
		for (size_t i = 0; i < SizeOf(ObjGet(value, "primitives")); i++)
		{
			ElementAllocation iPrimitive;
			if ((res = Parse_Primitive(ArrayGet(ObjGet(value, "primitives"), i), &iPrimitive, Basevalue, MaterialArray, *pAllocation, BufferArray, iGraphicsWindow, ThreadIndex)) != (Success))
				return res;
		}
	}
	else return (Failure);


	return (Success);
}
TEXRESULT Parse_Camera(Value* value, ResourceHeaderAllocation* pAllocation, const ObjectAllocation Parent, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);
	RHeaderCameraCreateInfo CreateInfo;
	memset(&CreateInfo, 0, sizeof(CreateInfo));

	if (ObjGet(value, "type"))
	{
		if (strcmp(GetStr(ObjGet(value, "type")), "perspective") == 0)
		{
			CreateInfo.Type = CameraType_Perspective;
			if (ObjGet(value, "perspective"))
			{
				Value* perspectiveV = ObjGet(value, "perspective");
				if (ObjGet(perspectiveV, "aspectRatio"))
					CreateInfo.CameraU.Perspective.AspectRatio = *GetNum(ObjGet(perspectiveV, "aspectRatio"));
				if (ObjGet(perspectiveV, "yfov"))
					CreateInfo.CameraU.Perspective.y_fov = *GetNum(ObjGet(perspectiveV, "yfov"));
				else return (Failure);
				if (ObjGet(perspectiveV, "zfar"))
					CreateInfo.CameraU.Perspective.z_far = *GetNum(ObjGet(perspectiveV, "zfar"));
				if (ObjGet(perspectiveV, "znear"))
					CreateInfo.CameraU.Perspective.z_near = *GetNum(ObjGet(perspectiveV, "znear"));
				else return (Failure);
			}
			else return (Failure);
		}
		else if (strcmp(GetStr(ObjGet(value, "type")), "orthographic") == 0)
		{
			CreateInfo.Type = CameraType_Orthographic;
			if (ObjGet(value, "orthographic"))
			{
				Value* orthographicV = ObjGet(value, "orthographic");
				if (ObjGet(orthographicV, "xmag"))
					CreateInfo.CameraU.Orthographic.x_mag = *GetNum(ObjGet(orthographicV, "xmag"));
				else return (Failure);
				if (ObjGet(orthographicV, "ymag"))
					CreateInfo.CameraU.Orthographic.y_mag = *GetNum(ObjGet(orthographicV, "ymag"));
				else return (Failure);
				if (ObjGet(orthographicV, "zfar"))
					CreateInfo.CameraU.Orthographic.z_far = *GetNum(ObjGet(orthographicV, "zfar"));
				else return (Failure);
				if (ObjGet(orthographicV, "znear"))
					CreateInfo.CameraU.Orthographic.z_near = *GetNum(ObjGet(orthographicV, "znear"));
				else return (Failure);
			}
			else return (Failure);
		}
	}
	else return (Failure);

	ResourceHeaderCreateInfo MainCreateInfo;
	memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
	MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Camera;
	if (ObjGet(value, "name") != NULL)
	{
		Value* nameV = ObjGet(value, "name");
		MainCreateInfo.Name = GetStr(nameV);
	}
	if ((res = Object_Ref_Create_ResourceHeader(pAllocation, MainCreateInfo, &CreateInfo, ThreadIndex)) != (Success))
		return res;

	Object_Ref_Add_Object_ResourceHeaderChild(*pAllocation, Parent, ThreadIndex);
	return (Success);
}
TEXRESULT Parse_Skin(Value* value, ResourceHeaderAllocation* pAllocation, Value* Basevalue,
	const ObjectAllocation* NodesArray, const ObjectAllocation Parent, const ResourceHeaderAllocation* BufferArray, ResourceHeaderAllocation iGraphicsWindow, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);
	RHeaderSkinCreateInfo CreateInfo;
	memset(&CreateInfo, 0, sizeof(CreateInfo));


	if (ObjGet(value, "inverseBindMatrices"))
	{
		Value* inverseBindMatricesV = ObjGet(value, "inverseBindMatrices");
		Value* accessorsV = ObjGet(Basevalue, "accessors");
		if ((res = Parse_Accessor(ArrayGet(accessorsV, *GetLongLong(inverseBindMatricesV)), &CreateInfo.InverseBindMatrices, Basevalue, BufferArray, iGraphicsWindow, ThreadIndex)) != (Success))
			return res;
	}

	if (ObjGet(value, "skeleton"))
		CreateInfo.iSkeleton = NodesArray[*GetLongLong(ObjGet(value, "skeleton"))];

	if (ObjGet(value, "joints"))
	{
		Value* jointsV = ObjGet(value, "joints");
		CreateInfo.iJointsSize = SizeOf(jointsV);
		CreateInfo.iJoints = (Object**)calloc(CreateInfo.iJointsSize, sizeof(*CreateInfo.iJoints));
		for (size_t i1 = 0; i1 < CreateInfo.iJointsSize; i1++)
			CreateInfo.iJoints[i1] = NodesArray[*GetLongLong(ArrayGet(jointsV, i1))];
	}

	ResourceHeaderCreateInfo MainCreateInfo;
	memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
	MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Skin;
	if (ObjGet(value, "name") != NULL)
	{
		Value* nameV = ObjGet(value, "name");
		MainCreateInfo.Name = GetStr(nameV);
	}
	if ((res = Object_Ref_Create_ResourceHeader(pAllocation, MainCreateInfo, &CreateInfo, ThreadIndex)) != (Success))
		return res;

	free(CreateInfo.iJoints);
	Object_Ref_Add_Object_ResourceHeaderChild(*pAllocation, Parent, ThreadIndex);
	return (Success);
}

//gltf extensions
TEXRESULT Parse_Light(Value* value, ResourceHeaderAllocation* pAllocation, const ObjectAllocation Parent, uint32_t ThreadIndex)
{
	TEXRESULT res = (Success);
	RHeaderLightCreateInfo CreateInfo;
	memset(&CreateInfo, 0, sizeof(CreateInfo));


	if (ObjGet(value, "type"))
	{
		if (strcmp(GetStr(ObjGet(value, "type")), "directional") == 0)
		{
			CreateInfo.Type = LightType_Directional;
			if (ObjGet(value, "directional"))
			{
				Value* directionalV = ObjGet(value, "directional");
			}
			else return (Failure);
		}
		else if (strcmp(GetStr(ObjGet(value, "type")), "point") == 0)
		{
			CreateInfo.Type = LightType_Point;
			if (ObjGet(value, "point"))
			{
				Value* pointV = ObjGet(value, "point");
			}
			else return (Failure);
		}
		else if (strcmp(GetStr(ObjGet(value, "type")), "spot") == 0)
		{
			CreateInfo.Type = LightType_Spot;
			if (ObjGet(value, "spot"))
			{
				Value* spotV = ObjGet(value, "spot");
				if (ObjGet(spotV, "innerConeAngle"))
					CreateInfo.LightU.Spot.InnerConeAngle = *GetNum(ObjGet(spotV, "innerConeAngle"));
				else
					CreateInfo.LightU.Spot.InnerConeAngle = 0;

				if (ObjGet(spotV, "outerConeAngle"))
					CreateInfo.LightU.Spot.OuterConeAngle = *GetNum(ObjGet(spotV, "outerConeAngle"));
				else
					CreateInfo.LightU.Spot.OuterConeAngle = 3.14 / 4.0;

			}
			else return (Failure);
		}
	}
	else return (Failure);

	if (ObjGet(value, "color"))
		for (size_t i1 = 0; i1 < 3; i1++)
			CreateInfo.Colour[i1] = *GetNum(ArrayGet(ObjGet(value, "color"), i1));
	else
		for (size_t i1 = 0; i1 < 3; i1++)
			CreateInfo.Colour[i1] = 1.0;

	if (ObjGet(value, "range"))
		CreateInfo.Range = *GetNum(ObjGet(value, "range"));

	if (ObjGet(value, "intensity") != NULL)
		CreateInfo.Intensity = *GetNum(ObjGet(value, "intensity"));



	ResourceHeaderCreateInfo MainCreateInfo;
	memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
	MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Light;
	if (ObjGet(value, "name") != NULL)
	{
		Value* nameV = ObjGet(value, "name");
		MainCreateInfo.Name = GetStr(nameV);
	}
	if ((res = Object_Ref_Create_ResourceHeader(pAllocation, MainCreateInfo, &CreateInfo, ThreadIndex)) != (Success))
		return res;

	Object_Ref_Add_Object_ResourceHeaderChild(*pAllocation, Parent, ThreadIndex);

}


TEXRESULT Load_3Dscene(const UTF8* Path, ResourceHeaderAllocation iGraphicsWindow, ResourceHeaderAllocation iScene, uint32_t ThreadIndex) {	
	TEXRESULT tres = Success;
	FileData filedata;
	if ((tres = Open_Data(&filedata, Path)) != (Success))
	{
		Engine_Ref_FunctionError("Load_3Dscene()", "Open_Data() Failed, TEXRESULT == ", tres);
		return (Invalid_Parameter | Failure);
	}

	const UTF8* ext = Get_FilePathExtension(Path);
	const UTF8* basedirectory = (UTF8*)Get_FilePathRoot(Path);

	Allocator* A = NewAllocator();

	Value* src_v = NewValue(A);
	bool Result = true;

	//we dont care about version since it doesnt matter nor magic since we dont care about error checking here :)
	void* binarydata = NULL; //pointer to pData in bin gltf
	if (strncmp((char*)ext, ".glb", 4) == 0) //binary gltf
	{
		uint32_t it = 0;
		GLB_HEADER* header = (GLB_HEADER*)((uint64_t)filedata.pData + (uint64_t)it);
		header->magic;
		header->version;
		header->length;
		it += sizeof(GLB_HEADER);
		while (it < header->length)
		{
			GLB_CHUNK* curpointer = (GLB_CHUNK*)((uint64_t)filedata.pData + (uint64_t)it);

			switch ((GLB_CHUNKTYPE)curpointer->chunkType)
			{
			case GLB_CHUNKTYPE_JSON:
				//yes i know this overwrites the size component of the glb binary bit but i dont really care.
				curpointer->chunkData[curpointer->chunkLength] = '\0';		
				if ((Result = ParseFast(src_v, curpointer->chunkData)) != true)
				{
					Engine_Ref_FunctionError("Load_2Dscene()", "ParseFast() Failed, Result == ", Result);
					return (Failure);
				}
				it += curpointer->chunkLength;
				break;
			case GLB_CHUNKTYPE_BIN:
				binarydata = curpointer->chunkData;
				it += curpointer->chunkLength;
				break;
			}
			it += 8; //chunklength & chunktype
		}
	}
	else //ascii gltf
	{	
		if ((Result = ParseFast(src_v, filedata.pData)) != true)
		{
			Engine_Ref_FunctionError("Load_2Dscene()", "ParseFast() Failed, Result == ", Result);
			return (Failure);
		}
	}

	if (ObjGet(src_v, "extensionsUsed") != NULL)
	{
		Value* extensionsUsedV = ObjGet(src_v, "extensionsUsed");
		Value* extensionsUsedNextV = Begin(extensionsUsedV);
		while (extensionsUsedNextV != NULL)
		{
			for (size_t i1 = 0; i1 < GLTF_ExtensionsSupportedSize; i1++)
			{		
				if (strcmp(GetStr(extensionsUsedNextV), (char*)GLTF_ExtensionsSupported[i1]) == 0)
				{

				}
			}
			extensionsUsedNextV = Next(extensionsUsedNextV);
		}
	}
	if (ObjGet(src_v, "extensionsRequired") != NULL)
	{
		Value* extensionsRequiredV = ObjGet(src_v, "extensionsRequired");
		Value* extensionsRequiredNextV = Begin(extensionsRequiredV);
		while (extensionsRequiredNextV != NULL)
		{
			for (size_t i1 = 0; i1 < GLTF_ExtensionsSupportedSize; i1++)
			{
				if (strcmp(GetStr(extensionsRequiredNextV), (char*)GLTF_ExtensionsSupported[i1]) != 0)
					return (Failure);
			}
		}
		extensionsRequiredNextV = Next(extensionsRequiredNextV);
	}

	ObjectAllocation* nodes = NULL;
	if (ObjGet(src_v, "nodes") != NULL)
	{
		Value* nodesV = ObjGet(src_v, "nodes");
		nodes = (ObjectAllocation*)calloc(SizeOf(nodesV), sizeof(ObjectAllocation));
		Value* nodesNextV = Begin(nodesV);
		for (size_t i = 0; i < SizeOf(nodesV); i++)
		{
			ObjectCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)Object_Generic;
			if (ObjGet(nodesNextV, "name") != NULL)
			{
				Value* nodesNextnameV = ObjGet(nodesNextV, "name");
				MainCreateInfo.Name = GetStr(nodesNextnameV);
			}
			Object_Ref_Create_Object(&nodes[i], MainCreateInfo, NULL, ThreadIndex);
			Object_Ref_Add_Object_ResourceHeaderChild(iScene, nodes[i], ThreadIndex);
			nodesNextV = Next(nodesNextV);
		}
	}

	if (ObjGet(src_v, "scenes") != NULL)
	{
		Value* scenesV = ObjGet(src_v, "scenes");
		Value* scenesNextV = Begin(scenesV);
		for (size_t i = 0; i < SizeOf(scenesV); i++)
		{
			ObjectAllocation iObject;

			ObjectCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)Object_Generic;
			if (ObjGet(scenesNextV, "name") != NULL)
			{
				Value* scenesNextnameV = ObjGet(scenesNextV, "name");
				MainCreateInfo.Name = GetStr(scenesNextnameV);
			}
			Object_Ref_Create_Object(&iObject, MainCreateInfo, NULL, ThreadIndex);

			//ResourceHeaderAllocation* iHeaderScene;
			//Object_Ref_Create_ResourceHeader(&iHeaderScene, iobject, (uint32_t)GraphicsHeader_Scene);
			if (ObjGet(scenesNextV, "nodes") != NULL)
			{
				Value* scenesNextnodesV = ObjGet(scenesNextV, "nodes");
				Value* scenesNextnodesNextV = Begin(scenesNextnodesV);
				for (size_t i1 = 0; i1 < SizeOf(scenesNextnodesV); i1++)
				{
					Object_Ref_Add_ObjectChild(nodes[*GetLongLong(scenesNextnodesNextV)], iObject, ThreadIndex);
					scenesNextnodesNextV = Next(scenesNextnodesNextV);
				}
			}
			scenesNextV = Next(scenesNextV);
		}
	}

	ResourceHeaderAllocation* Buffers = NULL;
	if (ObjGet(src_v, "buffers") != NULL)
	{
		Value* buffersV = ObjGet(src_v, "buffers");
		Buffers = (ResourceHeaderAllocation*)calloc(SizeOf(buffersV), sizeof(ResourceHeaderAllocation));
		Value* buffersNextV = Begin(buffersV);
		for (size_t i = 0; i < SizeOf(buffersV); i++)
		{
			Parse_Buffer(buffersNextV, &Buffers[i], basedirectory, binarydata, iGraphicsWindow, ThreadIndex);
			buffersNextV = Next(buffersNextV);
		}
	}

	ResourceHeaderAllocation* Textures = NULL;
	if (ObjGet(src_v, "textures") != NULL)
	{
		Value* texturesV = ObjGet(src_v, "textures");
		Textures = (ResourceHeaderAllocation*)calloc(SizeOf(texturesV), sizeof(ResourceHeaderAllocation));
		Value* texturesNextV = Begin(texturesV);
		for (size_t i = 0; i < SizeOf(texturesV); i++)
		{
			Parse_Texture(texturesNextV, &Textures[i], src_v, basedirectory, Buffers, iGraphicsWindow, ThreadIndex);
			texturesNextV = Next(texturesNextV);
		}
	}

	ResourceHeaderAllocation* Materials = NULL;
	if (ObjGet(src_v, "materials") != NULL)
	{
		Value* materialsV = ObjGet(src_v, "materials");
		Materials = (ResourceHeaderAllocation*)calloc(SizeOf(materialsV), sizeof(ResourceHeaderAllocation));
		Value* materialsNextV = Begin(materialsV);
		for (size_t i = 0; i < SizeOf(materialsV); i++)
		{
			Parse_Material(materialsNextV, &Materials[i], Textures, iGraphicsWindow, ThreadIndex);
			materialsNextV = Next(materialsNextV);
		}
	}

	if (ObjGet(src_v, "animations") != NULL)
	{
		Value* animationsV = ObjGet(src_v, "animations");
		Value* animationsNextV = Begin(animationsV);
		for (size_t i = 0; i < SizeOf(animationsV); i++)
		{
			ResourceHeaderAllocation iAnimation;
			Parse_Animation(animationsNextV, &iAnimation, nodes, src_v, Buffers, iGraphicsWindow, ThreadIndex);
			animationsNextV = Next(animationsNextV);
		}
	}

	if (ObjGet(src_v, "nodes") != NULL)
	{
		Value* nodesV = ObjGet(src_v, "nodes");
		Value* nodesNextV = Begin(nodesV);
		for (size_t i = 0; i < SizeOf(nodesV); i++)
		{
			ObjectAllocation iObject = nodes[i];

			if (ObjGet(nodesNextV, "children") != NULL)
			{
				Value* nodesNextchildrenV = ObjGet(nodesNextV, "children");
				Value* nodesNextchildrenNextV = Begin(nodesNextchildrenV);
				for (size_t i1 = 0; i1 < SizeOf(nodesNextchildrenV); i1++)
				{
					Object_Ref_Add_ObjectChild(nodes[*GetLongLong(nodesNextchildrenNextV)], nodes[i], ThreadIndex);
					nodesNextchildrenNextV = Next(nodesNextchildrenNextV);
				}
			}

			RHeaderPositionCreateInfo PositionCreateInfo;
			memset(&PositionCreateInfo, 0, sizeof(PositionCreateInfo));

			vec3 Translation;
			glm_vec3_zero(Translation);
			vec4 Rotation;
			glm_vec4_zero(Rotation);
			vec3 Scale;
			glm_vec3_one(Scale);

			if (ObjGet(nodesNextV, "rotation") != NULL)
				for (size_t i1 = 0; i1 < 4; i1++)
					Rotation[i1] = *GetNum(ArrayGet(ObjGet(nodesNextV, "rotation"), i1));
			if (ObjGet(nodesNextV, "scale") != NULL)
				for (size_t i1 = 0; i1 < 3; i1++)
					Scale[i1] = *GetNum(ArrayGet(ObjGet(nodesNextV, "scale"), i1));
			if (ObjGet(nodesNextV, "translation") != NULL)
				for (size_t i1 = 0; i1 < 3; i1++)
					Translation[i1] = *GetNum(ArrayGet(ObjGet(nodesNextV, "translation"), i1));
			if (ObjGet(nodesNextV, "matrix") != NULL)
			{
				for (size_t i1 = 0; i1 < 16; i1++)
					PositionCreateInfo.Matrix[i1 / 4][i1 % 4] = *GetNum(ArrayGet(ObjGet(nodesNextV, "matrix"), i1));
			}
			else
			{
				mat4 identitym;
				glm_mat4_identity(identitym);
				mat4 translationm;
				glm_mat4_identity(translationm);
				glm_translate(translationm, Translation);
				mat4 rotationm;
				glm_mat4_identity(rotationm);
				glm_quat_mat4(Rotation, rotationm);
				mat4 scalem;
				glm_mat4_identity(scalem);
				glm_scale(scalem, Scale);

				glm_mul_sse2(translationm, rotationm, PositionCreateInfo.Matrix);
				glm_mul_sse2(PositionCreateInfo.Matrix, scalem, PositionCreateInfo.Matrix);
				glm_mul_sse2(PositionCreateInfo.Matrix, identitym, PositionCreateInfo.Matrix);
			}

			if (ObjGet(nodesNextV, "camera") != NULL)
			{
				Value* nodesNextcameraV = ObjGet(nodesNextV, "camera");
				Value* camerasV = ObjGet(src_v, "cameras");
				ResourceHeaderAllocation iCamera;
				if ((tres = Parse_Camera(ArrayGet(camerasV, *GetLongLong(nodesNextcameraV)), &iCamera, iObject, ThreadIndex)) != (Success))
					return tres;
			}

			if (ObjGet(nodesNextV, "skin") != NULL)
			{
				Value* nodesNextskinV = ObjGet(nodesNextV, "skin");
				Value* skinsV = ObjGet(src_v, "skins");
				ResourceHeaderAllocation iSkin;
				if ((tres = Parse_Skin(ArrayGet(skinsV, *GetLongLong(nodesNextskinV)), &iSkin, src_v, nodes, iObject, Buffers, iGraphicsWindow, ThreadIndex)) != (Success))
					return tres;
			}
			if (ObjGet(nodesNextV, "mesh") != NULL)
			{
				Value* nodesNextmeshV = ObjGet(nodesNextV, "mesh");
				Value* meshesV = ObjGet(src_v, "meshes");
				ResourceHeaderAllocation iMesh;
				if ((tres = Parse_Mesh(ArrayGet(meshesV, *GetLongLong(nodesNextmeshV)), &iMesh, src_v, nodesNextV, Materials, iObject, Buffers, iGraphicsWindow, ThreadIndex)) != (Success))
					return tres;
			}
			if (ObjGet(nodesNextV, "extensions") != NULL)
			{
				Value* nodesNextextensionsV = ObjGet(nodesNextV, "extensions");
				if (ObjGet(nodesNextextensionsV, "KHR_lights_punctual") != NULL)
				{
					Value* nodesNextextensionsKHR_lights_punctualV = ObjGet(nodesNextextensionsV, "KHR_lights_punctual");
					Value* nodesNextlightV = ObjGet(nodesNextextensionsKHR_lights_punctualV, "light");

					Value* extensionsV = ObjGet(src_v, "extensions");
					Value* extensionsKHR_lights_punctualV = ObjGet(extensionsV, "extensionsKHR_lights_punctual");
					Value* lightsV = ObjGet(extensionsKHR_lights_punctualV, "lights");

					ResourceHeaderAllocation iLight;
					if ((tres = Parse_Light(ArrayGet(lightsV, *GetLongLong(nodesNextlightV)), &iLight, iObject, ThreadIndex)) != (Success))
						return tres;
				}
			}

			ResourceHeaderAllocation iPositionHeader;
			{
				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Position;
				if (ObjGet(nodesNextV, "name") != NULL)
				{
					Value* nodesNextnameV = ObjGet(nodesNextV, "name");
					MainCreateInfo.Name = GetStr(nodesNextnameV);
				}
				if ((tres = Object_Ref_Create_ResourceHeader(&iPositionHeader, MainCreateInfo, &PositionCreateInfo, ThreadIndex)) != (Success))
					return tres;
			}
			Object_Ref_Add_Object_ResourceHeaderChild(iPositionHeader, iObject, ThreadIndex);
			nodesNextV = Next(nodesNextV);
		}
	}
	if (nodes != NULL)
		free(nodes);
	if (Buffers != NULL)
		free(Buffers);
	if (Textures != NULL)
		free(Textures);
	if (Materials != NULL)
		free(Materials);

	ReleaseAllocator(A);
	free(ext);
	free(basedirectory);
	free(filedata.pData);
	return (Success);
}

void parse_g2d(Value* src_v, ObjectAllocation iParent, const UTF8* fileloc, ResourceHeaderAllocation iGraphicsWindow, ResourceHeaderAllocation iScene, uint32_t ThreadIndex)
{	
	if (ObjGet(src_v, "Childs") != NULL)
	{
		Value* childsV = ObjGet(src_v, "Childs");
		Value* nextV = Begin(childsV);
		while (nextV != 0)
		{
			Value* elementV = nextV;
			nextV = Next(nextV);

			UTF8* Name = NULL;
			if (ObjGet(elementV, "Name") != NULL)
			{
				Value* NameV = ObjGet(elementV, "Name");
				Name = GetStr(NameV);
			}

			ObjectAllocation iObject;
			{
				ObjectCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)Object_Generic;
				MainCreateInfo.Name = Name;
				Object_Ref_Create_Object(&iObject, MainCreateInfo, NULL, ThreadIndex);
				if (Object_Ref_Get_ObjectAllocationData(iParent) != NULL)
					Object_Ref_Add_ObjectChild(iObject, iParent, ThreadIndex);
			}
			Object_Ref_Add_Object_ResourceHeaderChild(iScene, iObject, ThreadIndex);

			RHeaderMaterialCreateInfo CreateInfoMaterial;
			memset(&CreateInfoMaterial, 0, sizeof(CreateInfoMaterial));
			CreateInfoMaterial.iGraphicsWindow = iGraphicsWindow;

			if (ObjGet(elementV, "Colour") != NULL)
			{
				Value* ColourV = ObjGet(elementV, "Colour");
				Value* ColournextV = Begin(ColourV);
				for (size_t i1 = 0; i1 < 4; i1++)
				{		
					CreateInfoMaterial.BaseColourFactor[i1] = *GetNum(ColournextV);
					ColournextV = Next(ColournextV);
				}
			}
			else
				for (size_t i1 = 0; i1 < 4; i1++)
					CreateInfoMaterial.BaseColourFactor[i1] = 1.0f;

			if (ObjGet(elementV, "AlphaMode") != NULL)
			{
				Value* AlphaModeV = ObjGet(elementV, "AlphaMode");
				switch (*((uint32_t*)GetStr(AlphaModeV)))
				{
				case 0x45555141: // OPAQUE
					CreateInfoMaterial.AlphaMode = AlphaMode_Opaque;
					break;
				case 0x4b53414d: //MASK
					CreateInfoMaterial.AlphaMode = AlphaMode_Mask;
					break;
				case 0x444e454c42: //BLEND
					CreateInfoMaterial.AlphaMode = AlphaMode_Blend;
					break;
				}
			}
			else
				CreateInfoMaterial.AlphaMode = AlphaMode_Blend;
			//CreateInfoMaterial.AlphaMode = AlphaMode_Mask;

			if (ObjGet(elementV, "AlphaCutoff") != NULL)
			{
				Value* AlphaCutoffV = ObjGet(elementV, "AlphaCutoff");
				CreateInfoMaterial.AlphaCutoff = *GetNum(AlphaCutoffV);
			}
			else
				CreateInfoMaterial.AlphaCutoff = 0.5f;

			if (ObjGet(elementV, "Button") != NULL)
			{
				Value* ButtonV = ObjGet(elementV, "Button");
				ResourceHeaderAllocation iButton;
				{
					RHeaderButtonCreateInfo CreateInfoAux;
					memset(&CreateInfoAux, 0, sizeof(CreateInfoAux));
					if (ObjGet(ButtonV, "CallbackSymbol") != NULL)
					{
						Value* ButtonCallbackSymbolV = ObjGet(ButtonV, "CallbackSymbol");
						CreateInfoAux.CallbackSymbol = GetStr(ButtonCallbackSymbolV);
					}
					ResourceHeaderCreateInfo MainCreateInfoAux;
					memset(&MainCreateInfoAux, 0, sizeof(MainCreateInfoAux));
					MainCreateInfoAux.Identifier = (uint32_t)GUIHeader_Button;
					MainCreateInfoAux.Name = Name;
					Object_Ref_Create_ResourceHeader(&iButton, MainCreateInfoAux, &CreateInfoAux, ThreadIndex);
					Object_Ref_Add_Object_ResourceHeaderChild(iButton, iObject, ThreadIndex);
				}
			}
			if (ObjGet(elementV, "Camera") != NULL)
			{
				Value* CameraV = ObjGet(elementV, "Camera");

				ResourceHeaderAllocation iImageSource;
				{
					RHeaderImageSourceCreateInfo CreateInfo;
					memset(&CreateInfo, 0, sizeof(CreateInfo));
					Graphics_Ref_Create_DummyTEXI(&CreateInfo.ImageData, GraphicsFormat_Undefined, 0, 0, 0, 1, 0, 0);
					ResourceHeaderCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_ImageSource;
					MainCreateInfo.Name = Name;
					Object_Ref_Create_ResourceHeader(&iImageSource, MainCreateInfo, &CreateInfo, ThreadIndex);
					Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, ThreadIndex);
					free(CreateInfo.ImageData);
				}
				ResourceHeaderAllocation iTextureTarget;
				{
					RHeaderTextureCreateInfo CreateInfo;
					memset(&CreateInfo, 0, sizeof(CreateInfo));
					CreateInfo.iGraphicsWindow = iGraphicsWindow;
					CreateInfo.iImageSource = iImageSource;
					CreateInfo.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit | TextureUsage_ColourAttachmentBit | TextureUsage_InputAttachmentBit);
					CreateInfo.AllocationType = AllocationType_Discrite;
					ResourceHeaderCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
					MainCreateInfo.Name = Name;
					Object_Ref_Create_ResourceHeader(&iTextureTarget, MainCreateInfo, &CreateInfo, ThreadIndex);
					Object_Ref_Add_Object_ResourceHeaderChild(iTextureTarget, iObject, ThreadIndex);
				}
				ResourceHeaderAllocation iRHeaderRender;
				{
					RHeaderRenderCreateInfo CreateInfo;
					memset(&CreateInfo, 0, sizeof(CreateInfo));
					CreateInfo.Clear[0] = 0.0f;
					CreateInfo.Clear[1] = 0.0f;
					CreateInfo.Clear[2] = 0.0f;
					CreateInfo.Clear[3] = 1.0f;
					CreateInfo.iGraphicsWindow = iGraphicsWindow;
					CreateInfo.iTextureTarget = iTextureTarget;

					CreateInfo.iScenesSize = 1;
					CreateInfo.iScenes = calloc(CreateInfo.iScenesSize, sizeof(*CreateInfo.iScenes));
					CreateInfo.iScenes[0] = iScene;

					ResourceHeaderCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Render;
					MainCreateInfo.Name = Name;
					Object_Ref_Create_ResourceHeader(&iRHeaderRender, MainCreateInfo, &CreateInfo, ThreadIndex);
					Object_Ref_Add_Object_ResourceHeaderChild(iRHeaderRender, iObject, ThreadIndex);
					free(CreateInfo.iScenes);
				}
				ResourceHeaderAllocation iCameraHeader;
				{
					RHeaderCameraCreateInfo CreateInfo;
					memset(&CreateInfo, 0, sizeof(CreateInfo));
					if (ObjGet(CameraV, "Type") != NULL)
					{
						Value* CameraTypeV = ObjGet(CameraV, "Type");
						CreateInfo.Type = *GetLongLong(CameraTypeV);
					}
					switch (CreateInfo.Type)
					{
					case CameraType_Perspective:
						if (ObjGet(CameraV, "AspectRatio") != NULL)
						{
							Value* CameraAspectRatioV = ObjGet(CameraV, "AspectRatio");
							CreateInfo.CameraU.Perspective.AspectRatio = *GetNum(CameraAspectRatioV);
						}
						else
						{
							RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);
							CreateInfo.CameraU.Perspective.AspectRatio = (double)pGraphicsWindow->TargetExtentWidth / (double)pGraphicsWindow->TargetExtentHeight;
							Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);
						}
						if (ObjGet(CameraV, "y_fov") != NULL)
						{
							Value* Cameray_fovV = ObjGet(CameraV, "y_fov");
							CreateInfo.CameraU.Perspective.y_fov = *GetNum(Cameray_fovV);
						}
						else
							CreateInfo.CameraU.Perspective.y_fov = 60.0;
						if (ObjGet(CameraV, "z_far") != NULL)
						{
							Value* Cameraz_farV = ObjGet(CameraV, "z_far");
							CreateInfo.CameraU.Perspective.z_far = *GetNum(Cameraz_farV);
						}
						else
							CreateInfo.CameraU.Perspective.z_far = 30.0;
						if (ObjGet(CameraV, "z_near") != NULL)
						{
							Value* Cameraz_nearV = ObjGet(CameraV, "z_near");
							CreateInfo.CameraU.Perspective.z_near = *GetNum(Cameraz_nearV);
						}
						else
							CreateInfo.CameraU.Perspective.z_near = 0.1;
						break;
					case CameraType_Orthographic:
						if (ObjGet(CameraV, "x_mag") != NULL)
						{
							Value* Camerax_magV = ObjGet(CameraV, "x_mag");
							CreateInfo.CameraU.Orthographic.x_mag = *GetNum(Camerax_magV);
						}
						else
							CreateInfo.CameraU.Orthographic.x_mag = 80.0;
						if (ObjGet(CameraV, "y_mag") != NULL)
						{
							Value* Cameray_magV = ObjGet(CameraV, "y_mag");
							CreateInfo.CameraU.Orthographic.y_mag = *GetNum(Cameray_magV);
						}
						else
							CreateInfo.CameraU.Orthographic.y_mag = 80.0;
						if (ObjGet(CameraV, "z_far") != NULL)
						{
							Value* Cameraz_farV = ObjGet(CameraV, "z_far");
							CreateInfo.CameraU.Orthographic.z_far = *GetNum(Cameraz_farV);
						}
						else
							CreateInfo.CameraU.Orthographic.z_far = 30.0;
						if (ObjGet(CameraV, "z_near") != NULL)
						{
							Value* Cameraz_nearV = ObjGet(CameraV, "z_near");
							CreateInfo.CameraU.Orthographic.z_near = *GetNum(Cameraz_nearV);
						}
						else
							CreateInfo.CameraU.Orthographic.z_near = 0.1;
						break;
					}
					ResourceHeaderCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Camera;
					MainCreateInfo.Name = Name;
					Object_Ref_Create_ResourceHeader(&iCameraHeader, MainCreateInfo, &CreateInfo, ThreadIndex);
					Object_Ref_Add_Object_ResourceHeaderChild(iCameraHeader, iObject, ThreadIndex);

				}
				ResourceHeaderAllocation iPositionHeader;
				{
					RHeaderPositionCreateInfo CreateInfo;
					memset(&CreateInfo, 0, sizeof(CreateInfo));

					vec3 Translation;
					glm_vec3_zero(Translation);
					vec4 Rotation;
					glm_vec4_zero(Rotation);
					vec3 Scale;
					glm_vec3_one(Scale);

					if (ObjGet(CameraV, "Position") != NULL)
					{
						Value* CameraPositionV = ObjGet(CameraV, "Position");
						Value* CameraPositionNextV = Begin(CameraPositionV);
						for (size_t i1 = 0; i1 < 3; i1++)
						{
							Translation[i1] = *GetNum(CameraPositionNextV);
							CameraPositionNextV = Next(CameraPositionNextV);
						}
					}
					if (ObjGet(CameraV, "Rotation") != NULL)
					{
						Value* CameraRotationV = ObjGet(CameraV, "Rotation");
						Value* CameraRotationNextV = Begin(CameraRotationV);
						for (size_t i1 = 0; i1 < 4; i1++)
						{
							Rotation[i1] = *GetNum(CameraRotationNextV);
							CameraRotationNextV = Next(CameraRotationNextV);
						}
					}

					glm_mat4_identity(CreateInfo.Matrix);

					mat4 identitym;
					glm_mat4_identity(identitym);
					mat4 translationm;
					glm_mat4_identity(translationm);
					glm_translate(translationm, Translation);
					mat4 rotationm;
					glm_mat4_identity(rotationm);
					glm_quat_mat4(Rotation, rotationm);
					mat4 scalem;
					glm_mat4_identity(scalem);
					glm_scale(scalem, Scale);

					glm_mul_sse2(translationm, rotationm, CreateInfo.Matrix);
					glm_mul_sse2(CreateInfo.Matrix, scalem, CreateInfo.Matrix);
					glm_mul_sse2(CreateInfo.Matrix, identitym, CreateInfo.Matrix);

					ResourceHeaderCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Position;
					MainCreateInfo.Name = Name;
					Object_Ref_Create_ResourceHeader(&iPositionHeader, MainCreateInfo, &CreateInfo, ThreadIndex);
					Object_Ref_Add_Object_ResourceHeaderChild(iPositionHeader, iObject, ThreadIndex);
				}
				CreateInfoMaterial.BaseColourTexture.iTexture = iTextureTarget;
			}
			if (ObjGet(elementV, "uri") != NULL)
			{
				Value* uriV = ObjGet(elementV, "uri");
				FileData pData = {0, 0};
				UTF8* mimetype = NULL;
				Decode_URI(&pData, (UTF8*)GetStr(uriV), fileloc, &mimetype);
				if (pData.pData != NULL && pData.LinearSize != NULL)
				{
					ResourceHeaderAllocation iImageSource;
					{
						RHeaderImageSourceCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						uint32_t identifier = *((uint32_t*)((uint64_t)mimetype + sizeof(char)));
						Graphics_Convert_Ref_XtoTEXI(&pData, &Info.ImageData, identifier);
						free(mimetype);
						free(pData.pData);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_ImageSource;
						MainCreateInfo.Name = Name;
						Object_Ref_Create_ResourceHeader(&iImageSource, MainCreateInfo, &Info, ThreadIndex);
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, ThreadIndex);
						free(Info.ImageData);
						
					}
					ResourceHeaderAllocation iTextureHeader;
					{
						RHeaderTextureCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Info.iGraphicsWindow = iGraphicsWindow;
						Info.iImageSource = iImageSource;
						Info.AllocationType = AllocationType_Linear;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit);
						ResourceHeaderCreateInfo MainCreateInfo ;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = Name;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, ThreadIndex);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, ThreadIndex);
					}
					CreateInfoMaterial.BaseColourTexture.iTexture = iTextureHeader;
				}

			}
			if (ObjGet(elementV, "Water") != NULL)
			{
				Value* WaterV = ObjGet(elementV, "Water");
				ResourceHeaderAllocation iTextureTarget;
				{
					ResourceHeaderAllocation iImageSource;
					{
						RHeaderImageSourceCreateInfo CreateInfo;
						memset(&CreateInfo, 0, sizeof(CreateInfo));
						Graphics_Ref_Create_DummyTEXI(&CreateInfo.ImageData, GraphicsFormat_Undefined, 0, 0, 0, 1, 0, 0);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_ImageSource;
						MainCreateInfo.Name = Name;
						Object_Ref_Create_ResourceHeader(&iImageSource, MainCreateInfo, &CreateInfo, ThreadIndex);
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, ThreadIndex);
						free(CreateInfo.ImageData);
					}
					{
						RHeaderTextureCreateInfo CreateInfo;
						memset(&CreateInfo, 0, sizeof(CreateInfo));
						CreateInfo.iGraphicsWindow = iGraphicsWindow;
						CreateInfo.iImageSource = iImageSource;
						CreateInfo.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit | TextureUsage_StorageBit);
						CreateInfo.AllocationType = AllocationType_Discrite;
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = Name;
						Object_Ref_Create_ResourceHeader(&iTextureTarget, MainCreateInfo, &CreateInfo, ThreadIndex);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureTarget, iObject, ThreadIndex);
					}
				}
				ResourceHeaderAllocation iTextureNoiseR0;
				{
					ResourceHeaderAllocation iImageSource;
					{
						RHeaderImageSourceCreateInfo CreateInfo;
						memset(&CreateInfo, 0, sizeof(CreateInfo));
						FileData pData = { NULL, 0 };
						Open_Data(&pData, (UTF8*)"data\\AuxTextures\\Noise\\noiseR0.bmp");
						TEXI_HEADER* header = NULL;
						Graphics_Convert_Ref_XtoTEXI(&pData, &header, bmp);
						free(pData.pData);
						CreateInfo.ImageData = header;
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_ImageSource;
						MainCreateInfo.Name = Name;
						Object_Ref_Create_ResourceHeader(&iImageSource, MainCreateInfo, &CreateInfo, ThreadIndex);
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, ThreadIndex);
						free(CreateInfo.ImageData);
					}
					{
						RHeaderTextureCreateInfo CreateInfo;
						memset(&CreateInfo, 0, sizeof(CreateInfo));
						CreateInfo.iGraphicsWindow = iGraphicsWindow;
						CreateInfo.iImageSource = iImageSource;
						CreateInfo.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit);
						CreateInfo.AllocationType = AllocationType_Linear;
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = Name;
						Object_Ref_Create_ResourceHeader(&iTextureNoiseR0, MainCreateInfo, &CreateInfo, ThreadIndex);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureNoiseR0, iObject, ThreadIndex);
					}
				}
				ResourceHeaderAllocation iWaterRender;
				{
					RHeaderWaterRenderCreateInfo CreateInfo;
					memset(&CreateInfo, 0, sizeof(CreateInfo));
					CreateInfo.iGraphicsWindow = iGraphicsWindow;
					CreateInfo.iTextureTarget = iTextureTarget;
					CreateInfo.iNoise = iTextureNoiseR0;
					CreateInfo.WaterAmplitude = 20.0f;
					CreateInfo.WaterIntensity = 16.0f;
					CreateInfo.Waterl = 1.0f;
					CreateInfo.WaterL = 1000;
					CreateInfo.WaterResolution = 256;
					CreateInfo.FlowDirection[0] = 0.0f;
					CreateInfo.FlowDirection[1] = 1.0f;
					ResourceHeaderCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GraphicsEffectsHeader_WaterRender;
					MainCreateInfo.Name = Name;
					Object_Ref_Create_ResourceHeader(&iWaterRender, MainCreateInfo, &CreateInfo, ThreadIndex);
					Object_Ref_Add_Object_ResourceHeaderChild(iWaterRender, iObject, ThreadIndex);
				}
				CreateInfoMaterial.BaseColourTexture.iTexture = iTextureTarget;
			}
			if (ObjGet(elementV, "Text") != NULL)
			{
				Value* TextV = ObjGet(elementV, "Text");
				{
					ResourceHeaderAllocation iImageSource;
					{
						RHeaderImageSourceCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Graphics_Ref_Create_DummyTEXI(&Info.ImageData, GraphicsFormat_Undefined, 0, 0, 0, 1, 0, 0);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_ImageSource;
						MainCreateInfo.Name = Name;
						Object_Ref_Create_ResourceHeader(&iImageSource, MainCreateInfo, &Info, ThreadIndex);
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, ThreadIndex);
						free(Info.ImageData);
					}

					ResourceHeaderAllocation iTextureHeader;
					{
						RHeaderTextureCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Info.iGraphicsWindow = iGraphicsWindow;
						Info.iImageSource = iImageSource;
						Info.AllocationType = AllocationType_Linear;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = Name;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, ThreadIndex);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, ThreadIndex);
					}
					CreateInfoMaterial.BaseColourTexture.iTexture = iTextureHeader;
				}
				{
					ResourceHeaderAllocation iImageSource;
					{
						RHeaderImageSourceCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Graphics_Ref_Create_DummyTEXI(&Info.ImageData, GraphicsFormat_Undefined, 0, 0, 0, 1, 0, 0);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_ImageSource;
						MainCreateInfo.Name = Name;
						Object_Ref_Create_ResourceHeader(&iImageSource, MainCreateInfo, &Info, ThreadIndex);
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, ThreadIndex);
						free(Info.ImageData);
					}

					ResourceHeaderAllocation iTextureHeader;
					{
						RHeaderTextureCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Info.iGraphicsWindow = iGraphicsWindow;
						Info.iImageSource = iImageSource;
						Info.AllocationType = AllocationType_Linear;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = Name;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, ThreadIndex);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, ThreadIndex);
					}
					CreateInfoMaterial.EmissiveTexture.iTexture = iTextureHeader;
				}
			}
			if (Object_Ref_Get_ResourceHeaderAllocationData(CreateInfoMaterial.BaseColourTexture.iTexture) != NULL)
			{
				CreateInfoMaterial.BaseColourMode = MaterialMode_Colour;
			}
			else
			{
				CreateInfoMaterial.BaseColourMode = MaterialMode_Solid;
			}
			
			ResourceHeaderAllocation iPositionHeader;
			{
				RHeaderPositionCreateInfo CreateInfo = { sizeof(CreateInfo) };

				vec3 Translation;
				glm_vec3_zero(Translation);
				vec4 Rotation;
				glm_vec4_zero(Rotation);
				vec3 Scale;
				glm_vec3_one(Scale);

				if (ObjGet(elementV, "Position") != NULL)
				{
					Value* elementPositionV = ObjGet(elementV, "Position");
					Value* elementPositionNextV = Begin(elementPositionV);
					for (size_t i1 = 0; i1 < 3; i1++)
					{
						Translation[i1] = *GetNum(elementPositionNextV);
						elementPositionNextV = Next(elementPositionNextV);
					}
				}
				else
					for (size_t i1 = 0; i1 < 2; i1++)
						Translation[i1] = 0.5f;

				glm_mat4_identity(CreateInfo.Matrix);

				mat4 identitym;
				glm_mat4_identity(identitym);
				mat4 translationm;
				glm_mat4_identity(translationm);
				glm_translate(translationm, Translation);
				mat4 rotationm;
				glm_mat4_identity(rotationm);
				glm_quat_mat4(Rotation, rotationm);
				mat4 scalem;
				glm_mat4_identity(scalem);
				glm_scale(scalem, Scale);

				glm_mul_sse2(translationm, rotationm, CreateInfo.Matrix);
				glm_mul_sse2(CreateInfo.Matrix, scalem, CreateInfo.Matrix);
				glm_mul_sse2(CreateInfo.Matrix, identitym, CreateInfo.Matrix);

				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Position;
				MainCreateInfo.Name = Name;
				Object_Ref_Create_ResourceHeader(&iPositionHeader, MainCreateInfo, &CreateInfo, ThreadIndex);
				Object_Ref_Add_Object_ResourceHeaderChild(iPositionHeader, iObject, ThreadIndex);
			}

			ResourceHeaderAllocation iMaterialHeader;
			{
				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
				MainCreateInfo.Name = Name;
				Object_Ref_Create_ResourceHeader(&iMaterialHeader, MainCreateInfo, &CreateInfoMaterial, ThreadIndex);
				Object_Ref_Add_Object_ResourceHeaderChild(iMaterialHeader, iObject, ThreadIndex);
			}
			ElementAllocation iElement;
			{
				RHeaderMaterial* pMaterial = Object_Ref_Get_ResourceHeaderPointer(iMaterialHeader, true, false, ThreadIndex);
				ElementGraphicsCreateInfo CreateInfo;
				memset(&CreateInfo, 0, sizeof(CreateInfo));
				CreateInfo.iMaterial = iMaterialHeader;
				CreateInfo.iGraphicsWindow = iGraphicsWindow;

				CreateInfo.EffectCreateInfosSize = 1;
				CreateInfo.EffectCreateInfos = (ElementGraphicsCreateInfoEffect*)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));

				if (ObjGet(elementV, "Text") != NULL)
				{
					Value* TextV = ObjGet(elementV, "Text");
					pMaterial->BaseColourMode = MaterialMode_Alpha;
					GraphicsEffectCreateInfoText InfoText;
					memset(&InfoText, 0, sizeof(InfoText));

					CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)GUIEffect_Text;
					CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &InfoText;

					if (ObjGet(TextV, "Text") != NULL)
					{
						Value* TextTextV = ObjGet(TextV, "Text");
						InfoText.Text = GetStr(TextTextV);
					}
					if (ObjGet(TextV, "FontSize") != NULL)
					{
						Value* TextFontSizeV = ObjGet(TextV, "FontSize");
						InfoText.FontSize = *GetLongLong(TextFontSizeV);
					}
					if (ObjGet(TextV, "Fonts") != NULL)
					{
						Value* TextFontsV = ObjGet(TextV, "Fonts");
						Value* TextFontsNextV = Begin(TextFontsV);
						while (TextFontsNextV != NULL)
						{
							InfoText.iFontsSize++;
							TextFontsNextV = Next(TextFontsNextV);
						}

						InfoText.iFonts = (RHeaderFont**)calloc(InfoText.iFontsSize, sizeof(*InfoText.iFonts));

						TextFontsNextV = Begin(TextFontsV);
						for (size_t i1 = 0; i1 < InfoText.iFontsSize; i1++)
						{
							ResourceHeaderAllocation iFont;
							RHeaderFontCreateInfo CreateInfoFont;
							memset(&CreateInfoFont, 0, sizeof(CreateInfoFont));
							Open_Data(&CreateInfoFont.Data, (UTF8*)GetStr(TextFontsNextV));
							ResourceHeaderCreateInfo MainCreateInfo;
							memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
							MainCreateInfo.Identifier = (uint32_t)GUIHeader_Font;
							MainCreateInfo.Name = Name;
							Object_Ref_Create_ResourceHeader(&iFont, MainCreateInfo, &CreateInfoFont, ThreadIndex);
							Object_Ref_Add_Object_ResourceHeaderChild(iFont, iObject, ThreadIndex);
							free(CreateInfoFont.Data.pData);
							InfoText.iFonts[i1] = iFont;

							TextFontsNextV = Next(TextFontsNextV);
						}
					}

					if (ObjGet(elementV, "Size") != NULL)
					{
						Value* elementSizeV = ObjGet(elementV, "Size");
						Value* elementSizeNextV = Begin(elementSizeV);
						for (size_t i1 = 0; i1 < 2; i1++)
						{
							InfoText.Size[i1] = *GetNum(elementSizeNextV);
							elementSizeNextV = Next(elementSizeNextV);
						}
					}
					else
						for (size_t i1 = 0; i1 < 2; i1++)
							InfoText.Size[i1] = 1.0f;
					/*
					if (ObjGet(elementV, "Position") != NULL)
					{
						Value* elementPositionV = ObjGet(elementV, "Position");
						Value* elementPositionNextV = Begin(elementPositionV);
						for (size_t i1 = 0; i1 < 3; i1++)
						{
							bb;
							//InfoText.Position[i1] = *GetNum(elementPositionNextV);
							elementPositionNextV = Next(elementPositionNextV);
						}
					}
					else
						for (size_t i1 = 0; i1 < 3; i1++)
							InfoText.Position[i1] = 0.5f;*/
					if (ObjGet(elementV, "BoundingBoxSize") != NULL)
					{
						Value* elementBoundingBoxSizeV = ObjGet(elementV, "BoundingBoxSize");
						Value* elementBoundingBoxSizeNextV = Begin(elementBoundingBoxSizeV);
						for (size_t i1 = 0; i1 < 2; i1++)
						{
							InfoText.BoundingBoxSize[i1] = *GetNum(elementBoundingBoxSizeNextV);
							elementBoundingBoxSizeNextV = Next(elementBoundingBoxSizeNextV);
						}
					}
					else
						for (size_t i1 = 0; i1 < 2; i1++)
							InfoText.BoundingBoxSize[i1] = InfoText.Size[i1];
					if (ObjGet(elementV, "BoundingBoxPosition") != NULL)
					{
						Value* elementBoundingBoxPositionV = ObjGet(elementV, "BoundingBoxPosition");
						Value* elementBoundingBoxPositionNextV = Begin(elementBoundingBoxPositionV);
						for (size_t i1 = 0; i1 < 2; i1++)
						{
							InfoText.BoundingBoxPosition[i1] = *GetNum(elementBoundingBoxPositionNextV);
							elementBoundingBoxPositionNextV = Next(elementBoundingBoxPositionNextV);
						}
					}
					else
						for (size_t i1 = 0; i1 < 2; i1++)
							InfoText.BoundingBoxPosition[i1] = 0.0f;


					ElementCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
					MainCreateInfo.Name = Name;
					Object_Ref_Create_Element(&iElement, MainCreateInfo, &CreateInfo, ThreadIndex);
					Object_Ref_Add_ResourceHeader_ElementChild(iElement, iPositionHeader, ThreadIndex);
					free(CreateInfo.EffectCreateInfos);
					free(InfoText.iFonts);
				}
				else
				{
					GraphicsEffectCreateInfoGeneric2D Info2D;
					memset(&Info2D, 0, sizeof(Info2D));

					CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)GraphicsEffect_Generic2D;
					CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &Info2D;

					if (ObjGet(elementV, "Size") != NULL)
					{
						Value* elementSizeV = ObjGet(elementV, "Size");
						Value* elementSizeNextV = Begin(elementSizeV);
						for (size_t i1 = 0; i1 < 2; i1++)
						{
							Info2D.Size[i1] = *GetNum(elementSizeNextV);
							elementSizeNextV = Next(elementSizeNextV);
						}
					}
					else
						for (size_t i1 = 0; i1 < 2; i1++)
							Info2D.Size[i1] = 1.0f;
					/*
					if (ObjGet(elementV, "Position") != NULL)
					{
						Value* elementPositionV = ObjGet(elementV, "Position");
						Value* elementPositionNextV = Begin(elementPositionV);
						for (size_t i1 = 0; i1 < 3; i1++)
						{
							bb;
							//Info2D.Position[i1] = *GetNum(elementPositionNextV);
							elementPositionNextV = Next(elementPositionNextV);
						}
					}
					else
						for (size_t i1 = 0; i1 < 3; i1++)
							Info2D.Position[i1] = 0.5f;*/
					if (ObjGet(elementV, "BoundingBoxSize") != NULL)
					{
						Value* elementBoundingBoxSizeV = ObjGet(elementV, "BoundingBoxSize");
						Value* elementBoundingBoxSizeNextV = Begin(elementBoundingBoxSizeV);
						for (size_t i1 = 0; i1 < 2; i1++)
						{
							Info2D.BoundingBoxSize[i1] = *GetNum(elementBoundingBoxSizeNextV);
							elementBoundingBoxSizeNextV = Next(elementBoundingBoxSizeNextV);
						}
					}
					else
						for (size_t i1 = 0; i1 < 2; i1++)
							Info2D.BoundingBoxSize[i1] = Info2D.Size[i1];		
					if (ObjGet(elementV, "BoundingBoxPosition") != NULL)
					{
						Value* elementBoundingBoxPositionV = ObjGet(elementV, "BoundingBoxPosition");
						Value* elementBoundingBoxPositionNextV = Begin(elementBoundingBoxPositionV);
						for (size_t i1 = 0; i1 < 2; i1++)
						{
							Info2D.BoundingBoxPosition[i1] = *GetNum(elementBoundingBoxPositionNextV);
							elementBoundingBoxPositionNextV = Next(elementBoundingBoxPositionNextV);
						}
					}
					else
						for (size_t i1 = 0; i1 < 2; i1++)
							Info2D.BoundingBoxPosition[i1] = 0.0f;

					ElementCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
					MainCreateInfo.Name = Name;
					Object_Ref_Create_Element(&iElement, MainCreateInfo, &CreateInfo, ThreadIndex);
					Object_Ref_Add_ResourceHeader_ElementChild(iElement, iPositionHeader, ThreadIndex);
					free(CreateInfo.EffectCreateInfos);
				}
				Object_Ref_End_ResourceHeaderPointer(iMaterialHeader, true, false, ThreadIndex);
			}
			parse_g2d(elementV, iObject, fileloc, iGraphicsWindow, iScene, ThreadIndex);
		}
	}
}
TEXRESULT Load_2Dscene(const UTF8* Path, ResourceHeaderAllocation iGraphicsWindow, ResourceHeaderAllocation iScene, uint32_t ThreadIndex){
	TEXRESULT tres = Success;
	FileData filedata;
	if ((tres = Open_Data(&filedata, Path)) != (Success))
	{
		Engine_Ref_FunctionError("Load_2Dscene()", "Open_Data() Failed, TEXRESULT == ", tres);
		return (Invalid_Parameter | Failure);
	}
	const UTF8* ext = Get_FilePathExtension(Path);
	const UTF8* basedirectory = Get_FilePathRoot(Path);
	Allocator* A = NewAllocator();
	Value* src_v = NewValue(A);
	bool Result = true;
	if ((Result = ParseFast(src_v, filedata.pData)) != true)
	{
		Engine_Ref_FunctionError("Load_2Dscene()", "ParseFast() Failed, Result == ", Result);
		return (Failure);
	}
	if (ObjGet(src_v, "asset") != NULL)
	{
		ObjectAllocation blank = { 0, 0 };
		parse_g2d(src_v, blank, (UTF8*)basedirectory, iGraphicsWindow, iScene, ThreadIndex);
	}
	ReleaseAllocator(A);
	free(ext);
	free(basedirectory);
	free(filedata.pData);
	return (Success);
}

#define ConverterErrorCheck(functionname)\
if (src == NULL) {\
	Engine_Ref_ArgsError(functionname, "Source == NULL ");\
	return (Invalid_Parameter | Failure);\
}\
if (dst == NULL) {\
	Engine_Ref_ArgsError(functionname, "Destination == NULL ");\
	return (Invalid_Parameter | Failure);\
}

//////////////////////////////////////////////////////////////////////////
//BMP/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

TEXRESULT BMP_To_TEXI(FileData* src, TEXI_HEADER** dst) 
{
	ConverterErrorCheck("BMP_To_TEXI");

	TEXI_HEADER temph;
	memset(&temph, 0, sizeof(temph));

	BMP_HEADER* header = (BMP_HEADER*)src->pData;
	if (strncmp(header->Signature, "BM", 2) != 0) //check if correct file
	{
		return (Invalid_Format | Failure);
	}

	BMP_BITMAPINFOHEADER* bitmapinfo = ((BMP_BITMAPINFOHEADER*)((uint64_t)src->pData + sizeof(BMP_HEADER)));

	temph.LinearSize = (uint64_t)(header->FileSize - header->DataOffset) + 1;
	temph.ImageSize = temph.LinearSize;
	temph.Width = bitmapinfo->Width;
	temph.Height = bitmapinfo->Height;
	temph.Depth = 1;
	temph.MipmapCount = 1;

	//bitmapinfo->Size; // 40
	//bitmapinfo->Width; // = 0
	//bitmapinfo->Height; // = 0
	//bitmapinfo->Planes; // = 1
	switch (bitmapinfo->BitsPerPixel)
	{
	case 1:
		//palletted
		break;
	case 2:
		//palletted
		break;
	case 4:
		//palletted
		break;
	case 8:
		//palletted
		break;
	case 16:
		temph.Format = GraphicsFormat_B4G4R4A4_UNORM_PACK16;
		break;
	case 24:
		temph.Format = GraphicsFormat_B8G8R8_SRGB;
		break;
	case 32:
		temph.Format = GraphicsFormat_B8G8R8A8_SRGB;
		break;
	}
	bitmapinfo->BitsPerPixel;

	switch (bitmapinfo->Compression)
	{
	case 0:

		break;
	}

	//bitmapinfo->Compression; // = 0
	//bitmapinfo->ImageSize; // = 0
	//bitmapinfo->h_res; // = 1000
	//bitmapinfo->v_res; // = 1000
	//bitmapinfo->ColoursUsed; // = 0
	//bitmapinfo->ImportantColours; // = 0

	BMP_PixelData* pixeldata = ((BMP_PixelData*)((uint64_t)src->pData + header->DataOffset));

	*dst = (TEXI_HEADER*)malloc(sizeof(TEXI_HEADER) + temph.LinearSize);

	TEXI_HEADER* pdst = *dst;

	memcpy(pdst, &temph, sizeof(TEXI_HEADER)); //copy header

	memcpy(pdst->Data, pixeldata->data, pdst->LinearSize - 1); //copy pData
	pdst->Data[temph.LinearSize - 1] = '\0';

	return (Success);
}
TEXRESULT TEXI_To_BMP(TEXI_HEADER* src, FileData* dst)
{
	ConverterErrorCheck("TEXI_To_BMP");


	FormatDetails formatDetails = Graphics_Ref_Get_FormatDetails(src->Format);

	uint32_t sizeoffile = sizeof(BMP_HEADER) + sizeof(BMP_BITMAPINFOHEADER) + src->LinearSize;
	dst->pData = (unsigned char*)malloc(sizeoffile);
	dst->LinearSize = sizeoffile;

	uint32_t totaloffset = 0;

	BMP_HEADER* header = (BMP_HEADER*)dst->pData;
	strncpy(header->Signature, "BM", 2);
	strncpy((char*)&header->Reserved, "TEXI", 4);
	header->FileSize = sizeoffile;
	header->DataOffset = (sizeof(BMP_HEADER) + sizeof(BMP_BITMAPINFOHEADER));

	totaloffset += sizeof(BMP_HEADER);

	BMP_BITMAPINFOHEADER* bitmapinfo = (BMP_BITMAPINFOHEADER*)((void*)((uint64_t)dst->pData + totaloffset));

	bitmapinfo->Size = 40; // 40
	bitmapinfo->Width = src->Width; // = 0
	bitmapinfo->Height = src->Height; // = 0
	bitmapinfo->Planes = 1; // = 1
	bitmapinfo->BitsPerPixel = formatDetails.Stride;

	bitmapinfo->h_res = 1000; // = 1000
	bitmapinfo->v_res = 1000; // = 1000
	//compression
	bitmapinfo->Compression = NULL; // = 0
	bitmapinfo->ImageSize = 0; // = 0
	//pallete
	bitmapinfo->ColoursUsed = NULL; // = 0
	bitmapinfo->ImportantColours = NULL; // = 0

	totaloffset += sizeof(BMP_BITMAPINFOHEADER);

	BMP_PixelData* pixeldata = (BMP_PixelData*)((void*)((uint64_t)dst->pData + totaloffset));

	memcpy(pixeldata->data, src->Data, src->LinearSize);


	((char*)dst->pData)[sizeoffile - 1] = '\0';

	return (Success);
}

//////////////////////////////////////////////////////////////////////////
//DDS/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

TEXRESULT DDS_To_TEXI(FileData* src, TEXI_HEADER** dst)
{
	ConverterErrorCheck("DDS_To_TEXI");

	TEXI_HEADER temph;
	memset(&temph, 0, sizeof(temph));

	DDS_HEADER* header = (DDS_HEADER*)src->pData;
	if (strncmp(header->magic, "DDS ", 4) != 0) //check if correct file
	{
		return (Invalid_Format | Failure);
	}

	temph.Width = header->dwWidth;
	temph.Height = header->dwHeight;
	temph.Depth = header->dwDepth;
	uint64_t pointer = sizeof(DDS_HEADER);
	//ddspf

	bool alpha = false;

	if ((header->ddspf.dwFlags >> 0) & 1)
	{
		alpha = true;
	}
	else
	{
		alpha = false;
	}
	if ((header->ddspf.dwFlags >> 1) & 1)
	{
		switch (header->ddspf.dwRGBBitCount)
		{
		case 8:
			temph.Format = GraphicsFormat_R8_UINT;
			break;
		case 16:
			temph.Format = GraphicsFormat_R16_UINT;
			break;
		case 32:
			temph.Format = GraphicsFormat_R32_UINT;
			break;
		case 64:
			temph.Format = GraphicsFormat_R64_UINT;
			break;
		}
	}
	if ((header->ddspf.dwFlags >> 2) & 1)
	{
		uint32_t* fourcc = (uint32_t*)header->ddspf.dwFourCC;
		switch (*fourcc)
		{
		case DDS_FOURCC_DXT1:
			temph.Format = GraphicsFormat_BC1_RGBA_UNORM_BLOCK;
			break;
		case DDS_FOURCC_DXT2:
			temph.Format = GraphicsFormat_BC2_UNORM_BLOCK; //mayby rgb tho?
			break;
		case DDS_FOURCC_DXT3:
			temph.Format = GraphicsFormat_BC2_UNORM_BLOCK;
			break;
		case DDS_FOURCC_DXT4:
			temph.Format = GraphicsFormat_BC3_UNORM_BLOCK;
			break;
		case DDS_FOURCC_DXT5:
			temph.Format = GraphicsFormat_BC3_UNORM_BLOCK;
			break;
		case DDS_FOURCC_DX10:
			//read dx10 strucc
			//DO THIS IN FUTuRE
			temph.Format = GraphicsFormat_BC1_RGBA_UNORM_BLOCK; //panik

			//DXGI_FORMAT              dxgiFormat;
			//D3D10_RESOURCE_DIMENSION resourceDimension;
			//UINT                     miscFlag;
			//UINT                     arraySize;
			//UINT                     miscFlags2;


			pointer += sizeof(DDS_DX10);
			break;
		}

	}
	if ((header->ddspf.dwFlags >> 3) & 1)
	{
		//might need clarification
		switch (header->ddspf.dwRGBBitCount)
		{
		case 24:
			temph.Format = GraphicsFormat_B8G8R8_UINT;
			break;
		case 32:
			temph.Format = GraphicsFormat_B8G8R8A8_UINT;
			break;
		}
	}
	if ((header->ddspf.dwFlags >> 4) & 1)
	{
		switch (header->ddspf.dwRGBBitCount)
		{
		case 8:
			temph.Format = GraphicsFormat_R8_UINT;
			break;
		case 16:
			temph.Format = GraphicsFormat_R16_UINT;
			break;
		case 32:
			temph.Format = GraphicsFormat_R32_UINT;
			break;
		case 64:
			temph.Format = GraphicsFormat_R64_UINT;
			break;
		}
	}

	DDS_PixelData* pixeldata = (DDS_PixelData*)((uint64_t)header + (uint64_t)pointer);


	temph.MipmapCount = 1;
	if (header->dwMipMapCount > 1)
		temph.MipmapCount = header->dwMipMapCount;

	temph.ImageSize = header->dwPitchOrLinearSize;
	temph.LinearSize = 0;
	uint64_t size = temph.ImageSize;
	for (size_t i = 0; i < temph.MipmapCount; i++)
	{
		temph.LinearSize += size;
		size /= 4;
	}
	temph.LinearSize++;

	*dst = (TEXI_HEADER*)malloc(sizeof(TEXI_HEADER) + temph.LinearSize);
	TEXI_HEADER* pdst = *dst;
	if (pdst == NULL)
		return (Out_Of_Memory_Result | Failure);

	memcpy(pdst, &temph, sizeof(TEXI_HEADER)); //copy header
	memcpy(pdst->Data, pixeldata->data, pdst->LinearSize - 1); //copy pData
	pdst->Data[temph.LinearSize - 1] = '\0';
	return (Success);
}
TEXRESULT TEXI_To_DDS(TEXI_HEADER* src, FileData* dst)
{
	ConverterErrorCheck("TEXI_To_DDS");

	return (Success);
}

//////////////////////////////////////////////////////////////////////////
//PNG/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

void stbi_write_callback(void* context, void* data, int size)
{
	FileData* pFileData = context;
	Resize_Array(&pFileData->pData, pFileData->LinearSize, pFileData->LinearSize + size, 1);
	pFileData->LinearSize += size;
}

TEXRESULT PNG_To_TEXI(FileData* src, TEXI_HEADER** dst)
{
	ConverterErrorCheck("PNG_To_TEXI");

	TEXI_HEADER temph;
	memset(&temph, 0, sizeof(temph));
	
	int x, y, n;
	unsigned char* data = stbi_load_from_memory(src->pData, src->LinearSize, &x, &y, &n, 4);

	temph.Format = GraphicsFormat_R8G8B8A8_SRGB;
	temph.Width = x;
	temph.Height = y;
	temph.Depth = 1;
	temph.LinearSize = (((temph.Height * temph.Width) * 4) * temph.Depth) + 1;
	temph.ImageSize = temph.LinearSize;
	temph.MipmapCount = 1;

	*dst = (TEXI_HEADER*)malloc(sizeof(TEXI_HEADER) + temph.LinearSize);
	TEXI_HEADER* pdst = *dst;
	if (pdst == NULL)
		return (Out_Of_Memory_Result | Failure);

	memcpy(pdst, &temph, sizeof(TEXI_HEADER)); //copy header
	memcpy(pdst->Data, data, pdst->LinearSize - 1); //copy pData
	pdst->Data[temph.LinearSize - 1] = '\0';

	free(data);



	return (Success);
}
TEXRESULT TEXI_To_PNG(TEXI_HEADER* src, FileData* dst)
{
	ConverterErrorCheck("TEXI_To_PNG");

	FormatDetails formatDetails = Graphics_Ref_Get_FormatDetails(src->Format);

	if (formatDetails.BitsPerChannel[0] != 8 || formatDetails.BitsPerChannel[1] != 8 || formatDetails.BitsPerChannel[2] != 8 || formatDetails.BitsPerChannel[3] != 8)
	{
		Engine_Ref_FunctionError("TEXI_To_TGA", "stb only supports 8 bit images.", 0);
		return (Invalid_Parameter | Failure);
	}
	//ONLY SUPPORTS 8 BIT FORMATS
	stbi_write_png_to_func(stbi_write_callback, dst, src->Width, src->Height, formatDetails.ChannelCount, src->Data, src->Width * formatDetails.Stride);


	return (Success);
}

//////////////////////////////////////////////////////////////////////////
//JPEG////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

TEXRESULT JPEG_To_TEXI(FileData* src, TEXI_HEADER** dst)
{
	ConverterErrorCheck("JPEG_To_TEXI");

	TEXI_HEADER temph;
	memset(&temph, 0, sizeof(temph));

	int x, y, n;
	unsigned char* data = stbi_load_from_memory(src->pData, src->LinearSize, &x, &y, &n, 4);

	temph.Format = GraphicsFormat_R8G8B8A8_SRGB;
	temph.Width = x;
	temph.Height = y;
	temph.Depth = 1;
	temph.LinearSize = (((temph.Height * temph.Width) * 4) * temph.Depth) + 1;
	temph.ImageSize = temph.LinearSize;
	temph.MipmapCount = 1;

	*dst = (TEXI_HEADER*)malloc(sizeof(TEXI_HEADER) + temph.LinearSize);
	TEXI_HEADER* pdst = *dst;
	if (pdst == NULL)
		return (Out_Of_Memory_Result | Failure);

	memcpy(pdst, &temph, sizeof(TEXI_HEADER)); //copy header
	memcpy(pdst->Data, data, pdst->LinearSize - 1); //copy pData
	pdst->Data[temph.LinearSize - 1] = '\0';

	free(data);

	return (Success);
}
TEXRESULT TEXI_To_JPEG(TEXI_HEADER* src, FileData* dst)
{
	ConverterErrorCheck("TEXI_To_JPEG");

	FormatDetails formatDetails = Graphics_Ref_Get_FormatDetails(src->Format);

	if (formatDetails.BitsPerChannel[0] != 8 || formatDetails.BitsPerChannel[1] != 8 || formatDetails.BitsPerChannel[2] != 8 || formatDetails.BitsPerChannel[3] != 8)
	{
		Engine_Ref_FunctionError("TEXI_To_TGA", "stb only supports 8 bit images.", 0);
		return (Invalid_Parameter | Failure);
	}
	//ONLY SUPPORTS 8 BIT FORMATS
	stbi_write_jpg_to_func(stbi_write_callback, dst, src->Width, src->Height, formatDetails.ChannelCount, src->Data, 100);

	return (Success);
}

//////////////////////////////////////////////////////////////////////////
//TGA/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

TEXRESULT TGA_To_TEXI(FileData* src, TEXI_HEADER** dst)
{
	ConverterErrorCheck("TGA_To_TEXI");

	TEXI_HEADER temph;
	memset(&temph, 0, sizeof(temph));

	int x, y, n;
	unsigned char* data = stbi_load_from_memory(src->pData, src->LinearSize, &x, &y, &n, 4);

	temph.Format = GraphicsFormat_R8G8B8A8_SRGB;
	temph.Width = x;
	temph.Height = y;
	temph.Depth = 1;
	temph.LinearSize = (((temph.Height * temph.Width) * 4) * temph.Depth) + 1;
	temph.ImageSize = temph.LinearSize;
	temph.MipmapCount = 1;

	*dst = (TEXI_HEADER*)malloc(sizeof(TEXI_HEADER) + temph.LinearSize);
	TEXI_HEADER* pdst = *dst;
	if (pdst == NULL)
		return (Out_Of_Memory_Result | Failure);

	memcpy(pdst, &temph, sizeof(TEXI_HEADER)); //copy header
	memcpy(pdst->Data, data, pdst->LinearSize - 1); //copy pData
	pdst->Data[temph.LinearSize - 1] = '\0';

	free(data);

	return (Success);
}
TEXRESULT TEXI_To_TGA(TEXI_HEADER* src, FileData* dst)
{
	ConverterErrorCheck("TEXI_To_TGA");
	
	FormatDetails formatDetails = Graphics_Ref_Get_FormatDetails(src->Format);

	if (formatDetails.BitsPerChannel[0] != 8 || formatDetails.BitsPerChannel[1] != 8 || formatDetails.BitsPerChannel[2] != 8 || formatDetails.BitsPerChannel[3] != 8)
	{
		Engine_Ref_FunctionError("TEXI_To_TGA", "stb only supports 8 bit images.", 0);
		return (Invalid_Parameter | Failure);
	}
	//ONLY SUPPORTS 8 BIT FORMATS
	stbi_write_tga_to_func(stbi_write_callback, dst, src->Width, src->Height, formatDetails.ChannelCount, src->Data);

	return (Success);
}

//////////////////////////////////////////////////////////////////////////
//WAV/////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

TEXRESULT WAV_To_TEXA(FileData* src, TEXA_HEADER** dst)
{
	if (src == NULL)
		return (Failure);

	WAV_HEADER* header = (WAV_HEADER*)src->pData;
	TEXA_HEADER temph;
	memset(&temph, 0, sizeof(temph));
	unsigned char* tempdata = NULL;

	if (strncmp(header->ChunkID, "RIFF", 4) != 0) //check if correct file
	{
		return (Invalid_Format | Failure);
	}
	if (strncmp(header->ChunkID, "RIFX", 4) == 0) //big endian version 
	{
		return (Invalid_Format | Failure);
	}

	if (strncmp(header->Format, "WAVE", 4) != 0)
	{

		return (Invalid_Format | Failure);
	}



	uint64_t totaloffset = sizeof(WAV_HEADER); //total offset from start of file

	WAV_SubChunkHeader* subchunk = 0;

	while (totaloffset < ((uint64_t)header->ChunkSize + 8))
	{
		subchunk = (WAV_SubChunkHeader*)((void*)((uint64_t)src->pData + totaloffset));

		totaloffset += (uint64_t)subchunk->SubchunkSize + 8;

		switch (*((uint32_t*)&subchunk->SubchunkID))
		{
		case (uint32_t)0x61746164: //pData;
			temph.LinearSize = ((WAV_data*)subchunk)->Header.SubchunkSize;
			tempdata = (unsigned char*)malloc(temph.LinearSize);
			memcpy(tempdata, &((WAV_data*)subchunk)->data, temph.LinearSize);
			break;
		case (uint32_t)0x20746d66: //fmt ;


			temph.ChannelCount = ((WAV_fmt*)subchunk)->NumChannels;
			temph.SampleRate = ((WAV_fmt*)subchunk)->SampleRate;
			temph.ByteRate = ((WAV_fmt*)subchunk)->ByteRate;
			temph.BlockAlign = ((WAV_fmt*)subchunk)->BlockAlign;
			switch (((WAV_fmt*)subchunk)->BitsPerSample)
			{
			case 8:
				temph.Format = AudioFormat_uint8;
				break;
			case 16:
				temph.Format = AudioFormat_int16LE;
				break;
			}

			switch (((WAV_fmt*)subchunk)->AudioFormat)
			{
			case 1:

				break;
			case 2: //if other then 1 read params;
				//((WAV::fmt*)subchunk)->ExtraParamSize;
				return (Invalid_Format); //return failure for now because unsupported
				break;
			}

			break;
		}

	}

	FormatDetails formatDetails = Audio_Ref_Get_FormatDetails(temph.Format);

	temph.FrameCount = (uint64_t)temph.LinearSize / (((uint64_t)formatDetails.BitsPerChannel[0] / (uint64_t)8) * (uint64_t)temph.ChannelCount);

	temph.LinearSize++;
	TEXA_HEADER* pdst = (TEXA_HEADER*)malloc(sizeof(TEXA_HEADER) + temph.LinearSize);
	if (pdst == NULL)
		return (Out_Of_Memory_Result | Failure);
	*dst = pdst;
	memcpy(pdst, &temph, sizeof(TEXA_HEADER)); //copy header
	memcpy(pdst->Data, tempdata, pdst->LinearSize - 1); //copy pData
	pdst->Data[temph.LinearSize - 1] = '\0';

	free(tempdata);
	return (Success);
}
TEXRESULT TEXA_To_WAV(TEXA_HEADER* src, FileData* dst)
{
	if (src == NULL)
		return (Failure);

	FormatDetails formatDetails = Audio_Ref_Get_FormatDetails(src->Format);

	uint32_t sizeoffile = sizeof(WAV_HEADER) + sizeof(WAV_fmt) + sizeof(WAV_data) + src->LinearSize;
	dst->pData = (unsigned char*)malloc(sizeoffile);

	WAV_HEADER* header = (WAV_HEADER*)dst->pData;

	strcpy(header->ChunkID, "RIFF");
	header->ChunkSize = sizeoffile - 8;
	strcpy(header->Format, "WAVE");

	uint64_t totaloffset = sizeof(WAV_HEADER); //total offset from start of file

	WAV_fmt* fmt = (WAV_fmt*)((void*)((uint64_t)dst->pData + totaloffset));;

	strcpy(fmt->Header.SubchunkID, "fmt ");
	fmt->Header.SubchunkSize = sizeof(WAV_fmt) - 8;
	fmt->AudioFormat = 1;
	fmt->NumChannels = src->ChannelCount;
	fmt->SampleRate = src->SampleRate;
	fmt->ByteRate = src->ByteRate;
	fmt->BlockAlign = src->BlockAlign;
	fmt->BitsPerSample = formatDetails.BitsPerChannel[0];
	//fmt->ExtraParamSize = 0;


	totaloffset += sizeof(WAV_fmt);
	WAV_data* pData = (WAV_data*)((void*)((uint64_t)dst->pData + totaloffset));;

	strcpy(pData->Header.SubchunkID, "pData");
	pData->Header.SubchunkSize = src->LinearSize;
	memcpy(pData->data, src->Data, src->LinearSize);


	((char*)dst->pData)[sizeoffile - 1] = '\0';
	dst->LinearSize = sizeoffile;

	return (Success);
}

//////////////////////////////////////////////////////////////////////////
//Main Function///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

TEXRESULT Initialise_Formats() {
	memset(&Utils, 0, sizeof(Utils));

	Graphics_Convert_Ref_Add_XtoTEXIconverter(&BMP_To_TEXI, bmp);
	Graphics_Convert_Ref_Add_TEXItoXconverter(&TEXI_To_BMP, bmp);

	Graphics_Convert_Ref_Add_XtoTEXIconverter(&DDS_To_TEXI, dds);
	Graphics_Convert_Ref_Add_TEXItoXconverter(&TEXI_To_DDS, dds);

	Graphics_Convert_Ref_Add_XtoTEXIconverter(&PNG_To_TEXI, png);
	Graphics_Convert_Ref_Add_TEXItoXconverter(&TEXI_To_PNG, png);

	Graphics_Convert_Ref_Add_XtoTEXIconverter(&JPEG_To_TEXI, jpeg);
	Graphics_Convert_Ref_Add_TEXItoXconverter(&TEXI_To_JPEG, jpeg);

	Graphics_Convert_Ref_Add_XtoTEXIconverter(&TGA_To_TEXI, tga);
	Graphics_Convert_Ref_Add_TEXItoXconverter(&TEXI_To_TGA, tga);

	Audio_Convert_Ref_Add_XtoTEXAconverter(&WAV_To_TEXA, wav);
	Audio_Convert_Ref_Add_TEXAtoXconverter(&TEXA_To_WAV, wav);

	return (Success);
}

TEXRESULT Destroy_Formats() {
	Graphics_Convert_Ref_Remove_XtoTEXIconverter(bmp);
	Graphics_Convert_Ref_Remove_TEXItoXconverter(bmp);

	Graphics_Convert_Ref_Remove_XtoTEXIconverter(dds);
	Graphics_Convert_Ref_Remove_TEXItoXconverter(dds);

	Graphics_Convert_Ref_Remove_XtoTEXIconverter(png);
	Graphics_Convert_Ref_Remove_TEXItoXconverter(png);

	Graphics_Convert_Ref_Remove_XtoTEXIconverter(jpeg);
	Graphics_Convert_Ref_Remove_TEXItoXconverter(jpeg);

	Audio_Convert_Ref_Remove_XtoTEXAconverter(wav);
	Audio_Convert_Ref_Remove_TEXAtoXconverter(wav);

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
	Object_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	Graphics_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	Audio_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	GUI_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);



	ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData("Formats::Utils"), &FormatsRes.pUtils, &Utils);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Formats::Initialise_Formats"), &FormatsRes.pInitialise_Formats, (void**)&Initialise_Formats, Construct, 10.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Formats::Destroy_Formats"), &FormatsRes.pDestroy_Formats, (void**)&Destroy_Formats, Destruct, 10.0f, 0, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Formats::Load_2Dscene"), &FormatsRes.pLoad_2Dscene, (void**)&Load_2Dscene, (CallFlagBits)NULL, 0.0f, NULL, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"Formats::Load_3Dscene"), &FormatsRes.pLoad_3Dscene, (void**)&Load_3Dscene, (CallFlagBits)NULL, 0.0f, NULL, NULL);

}





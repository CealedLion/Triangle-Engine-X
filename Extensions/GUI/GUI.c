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
//Ours
#include "Extension.h"
#include "Object.h"
#define TEX_EXPOSE_GRAPHICS
#include "Graphics.h"
#include "GraphicsShaders.h"
//Main
#define TEX_EXPOSE_GUI
#include "GUI.h"

volatile GUIUtils Utils;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Misc
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
* Added in 1.0.0
*/
FormatDetails Get_FT_pixelmodeDetails(FT_Pixel_Mode mode)
{
	FormatDetails details = { sizeof(details) };
	details.ChannelCount = FreetypeFormatChannelCounts[(uint32_t)mode];
	details.ChannelTypes = (DataType*)FreetypeFormatDataType[(uint32_t)mode];
	details.ChannelNames = (char*)FreetypeFormatChannelIndentifiers[(uint32_t)mode];
	details.BitsPerChannel = (uint8_t*)FreetypeFormatBitsPerChannels[(uint32_t)mode];
	details.Stride = FreetypeFormatStrides[(uint32_t)mode];
	return details;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Destroy_ButtonHeader(RHeaderButton* pResourceHeader, bool Full, uint32_t ThreadIndex)
{	
	pResourceHeader->Callback_Function = NULL;
	if (Full == true)
	{
		if (pResourceHeader->CallbackSymbol != NULL)
			free(pResourceHeader->CallbackSymbol);
		pResourceHeader->CallbackSymbol = NULL;
	}
	return (Success);
}

TEXRESULT Destroy_FontHeader(RHeaderFont* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	if (pResourceHeader->FtFace != NULL)
	{
		FT_Error err = 0;
		if ((err = FT_Done_Face(pResourceHeader->FtFace)) != 0)
		{
			Engine_Ref_FunctionError("Destroy_FontHeader()", FT_Error_String(err), err);
			return (Failure);
		}
	}
	pResourceHeader->FtFace = NULL;
	if (Full == true)
	{
		if (pResourceHeader->Data.pData != NULL)
			free(pResourceHeader->Data.pData);
		pResourceHeader->Data.pData = NULL;
	}
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ReCreate
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT ReCreate_ButtonHeader(RHeaderButton* pResourceHeader, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (pResourceHeader->CallbackSymbol == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_ButtonHeader()", "pResourceHeader->CallbackSymbol == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	FunctionInfo Info;
	memset(&Info, 0, sizeof(Info));
	Info.Name = pResourceHeader->CallbackSymbol;
	Info.ppFunction = (void**)&pResourceHeader->Callback_Function;
	Engine_Ref_Resolve_FunctionSymbol(&Info);
	return (Success);
}

TEXRESULT ReCreate_FontHeader(RHeaderFont* pResourceHeader, uint32_t ThreadIndex)
{
	FT_Error err = 0;
	//recreate
	if ((err = FT_New_Memory_Face(Utils.FtLibrary, (const FT_Byte*)pResourceHeader->Data.pData, pResourceHeader->Data.LinearSize, 0, &pResourceHeader->FtFace)) != 0)
	{
		Engine_Ref_FunctionError("ReCreate_FontHeader()", FT_Error_String(err), err);
		return (Failure);
	}
	if ((err = FT_Select_Charmap(pResourceHeader->FtFace, ft_encoding_unicode)) != 0)
	{
		Engine_Ref_FunctionError("ReCreate_FontHeader()", FT_Error_String(err), err);
		return (Failure);
	}
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Packers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Pack_ButtonHeader(const RHeaderButton* pResourceHeader, RHeaderButton* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedResourceHeader->Callback_Function, 0, sizeof(pCopiedResourceHeader->Callback_Function));

		if (pResourceHeader->CallbackSymbol != NULL)
		{
			memcpy(((void*)((uint64_t)pData + (uint64_t)*pBufferPointer)), pResourceHeader->CallbackSymbol, sizeof(UTF8) * (strlen((char*)pResourceHeader->CallbackSymbol) + 1));
			pCopiedResourceHeader->CallbackSymbol = (UTF8*)*pBufferPointer;
			*pBufferPointer += sizeof(UTF8) * (strlen((char*)pResourceHeader->CallbackSymbol) + 1);
		}
	}
	else
	{
		*pBufferPointer += sizeof(UTF8) * (strlen((char*)pResourceHeader->CallbackSymbol) + 1);
	}
	return (Success);
}

TEXRESULT Pack_FontHeader(const RHeaderFont* pResourceHeader, RHeaderFont* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedResourceHeader->FtFace, 0, sizeof(pCopiedResourceHeader->FtFace));
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
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Unpackers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT UnPack_ButtonHeader(const RHeaderButton* pResourceHeader, RHeaderButton* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	if (pResourceHeader->CallbackSymbol != NULL)
	{
		const UTF8* pText = (UTF8*)((void*)((uint64_t)pData + (uint64_t)pResourceHeader->CallbackSymbol));

		pCopiedResourceHeader->CallbackSymbol = (UTF8*)malloc(sizeof(UTF8) * (strlen((char*)pText) + 1));
		memcpy(pCopiedResourceHeader->CallbackSymbol, pText, sizeof(UTF8) * (strlen((char*)pText) + 1));	
	}
	return (Success);
}

TEXRESULT UnPack_FontHeader(const RHeaderFont* pResourceHeader, RHeaderFont* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	if (pResourceHeader->Data.pData != NULL && pResourceHeader->Data.LinearSize != NULL)
	{
		pCopiedResourceHeader->Data.pData = (unsigned char*)malloc(pResourceHeader->Data.LinearSize);
		memcpy(pCopiedResourceHeader->Data.pData, (void*)((uint64_t)pData + (uint64_t)pResourceHeader->Data.pData), pResourceHeader->Data.LinearSize);
	}
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_ButtonHeader(RHeaderButton* pResourceHeader, RHeaderButtonCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_ButtonHeader()", "pCreateInfo == NULLPTR");
			return (Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->CallbackSymbol = (UTF8*)CopyData((void*)pCreateInfo->CallbackSymbol);
		ReCreate_ButtonHeader(pResourceHeader, ThreadIndex);
	}
	*pAllocationSize = sizeof(RHeaderButton);
	return (Success);
}

TEXRESULT Create_FontHeader(RHeaderFont* pResourceHeader, RHeaderFontCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_FontHeader()", "pCreateInfo == NULLPTR");
			return (Invalid_Parameter | Failure);
		}
		if (pCreateInfo->Data.pData == NULL)
		{
			Engine_Ref_ArgsError("Create_FontHeader()", "Data.pData == NULLPTR");
			return (Invalid_Parameter | Failure);
		}
		if (pCreateInfo->Data.LinearSize == NULL)
		{
			Engine_Ref_ArgsError("Create_FontHeader()", "pCreateInfo->Data.LinearSize == NULL");
			return (Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->Data.LinearSize = pCreateInfo->Data.LinearSize;
		pResourceHeader->Data.pData = malloc(pResourceHeader->Data.LinearSize);
		memcpy(pResourceHeader->Data.pData, pCreateInfo->Data.pData, pResourceHeader->Data.LinearSize);
		ReCreate_FontHeader(pResourceHeader, ThreadIndex);
	}
	*pAllocationSize = sizeof(RHeaderFont);
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Draw Effect Element
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Draw_Text(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, GraphicsEffectText* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers, RHeaderCamera* pCamera, mat4 CameraVP)
{	
	for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
	{
		VkBuffer vkBuffer = GPU_Buffers[0].Allocater.pArenaAllocater->VkBuffer;
		VkDeviceSize VkOffset = GPU_Buffers[0].Pointer + GPU_BufferPointers[0];
		GPU_BufferPointers[0] += sizeof(*pEffect->GPU_GraphicsEffectInfos);

		vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pEffect->VkPipeline);

		PushConstantsGeneric2D PushConstants2D;
		memset(&PushConstants2D, 0, sizeof(PushConstants2D));
		glm_mat4_copy(CameraVP, PushConstants2D.VP);
		PushConstants2D.pad = pEffect->GPU_GraphicsEffectInfos[i].mode;
		PushConstants2D.pad1 = pEffect->GPU_GraphicsEffectInfos[i].selected;
		vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, ((GraphicsUtils*)GraphicsRes.pUtils)->GenericResources[Graphics_Ref_Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].PipelineLayout2D, VK_SHADER_STAGE_ALL, 0,
			pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstants2D);

		VkDescriptorSet descriptorsets[1] = {
			pMaterialHeader->VkMaterialDescriptorSets[FrameIndex]
		};
		uint32_t descriptorsetSize = 1;
		
		vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
			((GraphicsUtils*)GraphicsRes.pUtils)->GenericResources[Graphics_Ref_Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].PipelineLayout2D, 0, descriptorsetSize, descriptorsets, 0, NULL);

		vkCmdBindVertexBuffers(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 0, 1, &vkBuffer, &VkOffset);

		vkCmdDraw(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 6, 1, 0, 0);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Update Effect Element
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Update_Text(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, GraphicsEffectText* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
	if (GPU_Buffers == NULL)
	{
		GPU_BufferPointers[0] += sizeof(*pEffect->GPU_GraphicsEffectInfos) * pEffect->GPU_GraphicsEffectInfosSize;
	}
	else
	{
		if (pEffect->GPU_GraphicsEffectInfosSize != NULL)
		{		
			memcpy((void*)((uint64_t)GPU_BufferPointers[0]), pEffect->GPU_GraphicsEffectInfos, pEffect->GPU_GraphicsEffectInfosSize * sizeof(*pEffect->GPU_GraphicsEffectInfos));
		}
		GPU_BufferPointers[0] += sizeof(*pEffect->GPU_GraphicsEffectInfos) * pEffect->GPU_GraphicsEffectInfosSize;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Signataure Updates
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdateSignature_Text(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Destroy_Text(ElementGraphics* pElement, GraphicsEffectText* pEffect, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);
	if (pEffect->GPU_GraphicsEffectInfos != NULL)
		free(pEffect->GPU_GraphicsEffectInfos);
	pEffect->GPU_GraphicsEffectInfos = NULL;
	pEffect->GPU_GraphicsEffectInfosSize = NULL;

	if (Full == true)
	{
		if (pEffect->VkPipeline != NULL)
			vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipeline, NULL);
		pEffect->VkPipeline = NULL;
			

		if (pEffect->UTF8_Text != NULL)
			free(pEffect->UTF8_Text);
		pEffect->FontSize = NULL;
		pEffect->UTF8_Text = NULL;


		if (pEffect->VkShaderVertex != NULL)
			vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderVertex, NULL);
		pEffect->VkShaderVertex = NULL;
		if (pEffect->VkShaderFragment != NULL)
			vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderFragment, NULL);
		pEffect->VkShaderFragment = NULL;
	}
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Recreation
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT ReCreate_Text(ElementGraphics* pElement, GraphicsEffectText* pEffect, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_Text()", "pElement == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (pEffect == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_Text()", "pEffect == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	TEXRESULT tres = Success;
	VkResult res = VK_SUCCESS;
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);

	//mayby instance?
	RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);


	ResourceHeaderInstance Texture0Instance;
	Object_Ref_CreateInstance_ResourceHeader(pMaterial->BaseColourTexture.iTexture, &Texture0Instance, ThreadIndex);
	RHeaderTexture* pTexture0 = Texture0Instance.pInstance;
	RHeaderImageSource* pImageSource0 = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture0->iImageSource);

	ResourceHeaderInstance Texture1Instance;
	Object_Ref_CreateInstance_ResourceHeader(pMaterial->EmissiveTexture.iTexture, &Texture1Instance, ThreadIndex);
	RHeaderTexture* pTexture1 = Texture1Instance.pInstance;
	RHeaderImageSource* pImageSource1 = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture1->iImageSource);
	
	pEffect->GPU_GraphicsEffectInfos = NULL;
	pEffect->GPU_GraphicsEffectInfosSize = NULL;
	{
		uint64_t TotalTextureWidth0 = 0;
		uint64_t pTextImages0Size = 0;
		TEXI_HEADER** pTextImages0 = NULL;

		uint64_t TotalTextureWidth1 = 0;
		uint64_t pTextImages1Size = 0;
		TEXI_HEADER** pTextImages1 = NULL;

		FT_Error FTerr = 0;

		float AdvanceX = 0;
		float AdvanceY = (float)((pEffect->FontSize * Utils.DPI) / 72) / 2;

		UTF32 PreviousCodePoint = 0;
		UTF32* UTF32_Text = NULL;
		UTF8_To_UTF32(pEffect->UTF8_Text, &UTF32_Text);

		uint64_t size = 0;
		while (UTF32_Text[size] != (UTF32)'\0') {
			size++;
		}
		size++;

		Resize_Array((void**)&pEffect->GPU_GraphicsEffectInfos, pEffect->GPU_GraphicsEffectInfosSize, pEffect->GPU_GraphicsEffectInfosSize + size, sizeof(*pEffect->GPU_GraphicsEffectInfos));


		for (size_t i = 0; i < size; i++){
			UTF32 CurrentCodePoint = UTF32_Text[i];

			GPU_GraphicsEffectText* pGPU_effect = &pEffect->GPU_GraphicsEffectInfos[pEffect->GPU_GraphicsEffectInfosSize];
			pEffect->GPU_GraphicsEffectInfosSize += 1;

			if (CurrentCodePoint == 0x0D || CurrentCodePoint == 0x0A)
			{
				pGPU_effect->Size[0] = 0;
				pGPU_effect->Size[1] = 0;

				pGPU_effect->Position[0] = (pEffect->Position[0] - pEffect->Size[0]) + pGPU_effect->Size[0] + ((AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth);
				pGPU_effect->Position[1] = ((pEffect->Position[1] - pEffect->Size[1]) - pGPU_effect->Size[1]) + ((AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight);
				pGPU_effect->Position[2] = pEffect->Position[2];

				pGPU_effect->AdvanceX = AdvanceX;
				pGPU_effect->AdvanceY = AdvanceY;

				glm_vec2_copy(pEffect->BoundingBoxPosition, pGPU_effect->BoundingBoxPosition);
				glm_vec2_copy(pEffect->BoundingBoxSize, pGPU_effect->BoundingBoxSize);

				if (UTF32_Text[i + 1] == 0x0A) //handle CRLF
				{
					GPU_GraphicsEffectText* pGPU_effect = &pEffect->GPU_GraphicsEffectInfos[pEffect->GPU_GraphicsEffectInfosSize];
					pEffect->GPU_GraphicsEffectInfosSize += 1;

					pGPU_effect->Size[0] = 0;
					pGPU_effect->Size[1] = 0;

					pGPU_effect->Position[0] = (pEffect->Position[0] - pEffect->Size[0]) + pGPU_effect->Size[0] + ((AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth);
					pGPU_effect->Position[1] = ((pEffect->Position[1] - pEffect->Size[1]) - pGPU_effect->Size[1]) + ((AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight);
					pGPU_effect->Position[2] = pEffect->Position[2];

					pGPU_effect->AdvanceX = AdvanceX;
					pGPU_effect->AdvanceY = AdvanceY;

					glm_vec2_copy(pEffect->BoundingBoxPosition, pGPU_effect->BoundingBoxPosition);
					glm_vec2_copy(pEffect->BoundingBoxSize, pGPU_effect->BoundingBoxSize);

					i++;
				}

				AdvanceX = 0;
				AdvanceY += ((pEffect->FontSize * Utils.DPI) / 72) / 2;
			}
			else {

				bool tab = false;
				if (CurrentCodePoint == 0x09) {
					tab = true;
					CurrentCodePoint = 0x20;
				}

				uint64_t GlyphIndex = NULL;
				RHeaderFont* pFont = NULL;

				for (size_t i = 0; i < pEffect->iFontsSize; i++) {
					pFont = (RHeaderFont*)Object_Ref_Get_ResourceHeaderPointer(pEffect->iFonts[i]);
					GlyphIndex = FT_Get_Char_Index(pFont->FtFace, CurrentCodePoint);
					if (GlyphIndex != NULL)
						break;
				}
				if (GlyphIndex == NULL) {
					Engine_Ref_FunctionError("ReCreate_TextHeader()", "No Suitable Glyph Found. UTF32 == ", CurrentCodePoint);
					return (Failure);
				}

				bool alreadyrendered = false;
				uint64_t alreadyrenderedindex = 0;
				for (size_t i2 = 0; i2 < i; i2++)
				{
					if (UTF32_Text[i2] == UTF32_Text[i]) //weve already rendered this character
					{
						alreadyrendered = true;
						alreadyrenderedindex = i2;
					}
				}

				float scalefactor = 1.0f;

				uint32_t FT_Flags = 0;
				GraphicsFormat Format = GraphicsFormat_Undefined;

				if (FT_HAS_COLOR(pFont->FtFace)) {
					Format = GraphicsFormat_B8G8R8A8_SRGB;
					FT_Flags |= FT_LOAD_COLOR;
				}
				else {
					Format = GraphicsFormat_R8_SRGB;
					FT_Flags |= FT_LOAD_DEFAULT;
				}
				if (FT_HAS_FIXED_SIZES(pFont->FtFace)) {
					if ((FTerr = FT_Select_Size(pFont->FtFace, 0)) != 0)
						Engine_Ref_FunctionError("Update_Text()", "FT_Select_Size Failed, FT_Error == ", FTerr);
					scalefactor = ((float)((pEffect->FontSize * Utils.DPI) / 72) / (float)(pFont->FtFace->size->metrics.height >> 6)) / 2;
				}
				else {
					if ((FTerr = FT_Set_Char_Size(pFont->FtFace, pEffect->FontSize, pEffect->FontSize,
						((pGraphicsWindow->CurrentExtentWidth * Utils.DPI) >> 6), ((pGraphicsWindow->CurrentExtentWidth * Utils.DPI) >> 6))) != 0)
						Engine_Ref_FunctionError("Update_Text()", "FT_Set_Char_Size Failed, FT_Error == ", FTerr);
				}
				if ((FTerr = FT_Load_Glyph(pFont->FtFace, GlyphIndex, FT_Flags)) != 0)
					Engine_Ref_FunctionError("Update_Text()", "FT_Load_Glyph Failed, FT_Error == ", FTerr);


				if (!FT_HAS_COLOR(pFont->FtFace)) {
					if ((FTerr = FT_Render_Glyph(pFont->FtFace->glyph, FT_RENDER_MODE_NORMAL)) != 0)
						Engine_Ref_FunctionError("Update_Text()", "FT_Render_Glyph Failed, FT_Error == ", FTerr);
				}

				if (alreadyrendered == true)
				{
					pGPU_effect->Size[0] = pEffect->GPU_GraphicsEffectInfos[alreadyrenderedindex].Size[0];
					pGPU_effect->Size[1] = pEffect->GPU_GraphicsEffectInfos[alreadyrenderedindex].Size[1];
					pGPU_effect->TextureOffset[0] = pEffect->GPU_GraphicsEffectInfos[alreadyrenderedindex].TextureOffset[0];
					pGPU_effect->TextureOffset[1] = pEffect->GPU_GraphicsEffectInfos[alreadyrenderedindex].TextureOffset[1];
					pGPU_effect->TextureSize[0] = pEffect->GPU_GraphicsEffectInfos[alreadyrenderedindex].TextureSize[0];
					pGPU_effect->TextureSize[1] = pEffect->GPU_GraphicsEffectInfos[alreadyrenderedindex].TextureSize[1];
					pGPU_effect->mode = pEffect->GPU_GraphicsEffectInfos[alreadyrenderedindex].mode;
				}
				else
				{
					if (pFont->FtFace->glyph->bitmap.rows * pFont->FtFace->glyph->bitmap.pitch != NULL && pFont->FtFace->glyph->bitmap.buffer != NULL)
					{
						if (!FT_HAS_COLOR(pFont->FtFace)) {
							FormatDetails details = Get_FT_pixelmodeDetails((FT_Pixel_Mode)pFont->FtFace->glyph->bitmap.pixel_mode);
							uint64_t lsize = ((pFont->FtFace->glyph->bitmap.rows * pFont->FtFace->glyph->bitmap.pitch));
							Resize_Array((void**)&pTextImages0, pTextImages0Size, pTextImages0Size + 1, sizeof(*pTextImages0));
							Graphics_Ref_Create_DummyTEXI(&pTextImages0[pTextImages0Size], Format, pFont->FtFace->glyph->bitmap.pitch / details.ChannelCount, pFont->FtFace->glyph->bitmap.rows, 1, 1, lsize, lsize);
							memcpy(pTextImages0[pTextImages0Size]->Data, pFont->FtFace->glyph->bitmap.buffer, lsize);
							pGPU_effect->Size[0] = (((float)(pTextImages0[pTextImages0Size]->Width * scalefactor) / 2) / (float)pGraphicsWindow->CurrentExtentWidth);
							pGPU_effect->Size[1] = (((float)(pTextImages0[pTextImages0Size]->Height * scalefactor) / 2) / (float)pGraphicsWindow->CurrentExtentHeight);
							pGPU_effect->TextureOffset[0] = TotalTextureWidth0;
							pGPU_effect->TextureOffset[1] = 0;
							pGPU_effect->TextureSize[0] = pTextImages0[pTextImages0Size]->Width;
							pGPU_effect->TextureSize[1] = pTextImages0[pTextImages0Size]->Height;
							pGPU_effect->mode = 1;
							TotalTextureWidth0 += pTextImages0[pTextImages0Size]->Width;
							pTextImages0Size += 1;
						}
						else {

							FormatDetails details = Get_FT_pixelmodeDetails((FT_Pixel_Mode)pFont->FtFace->glyph->bitmap.pixel_mode);
							uint64_t lsize = ((pFont->FtFace->glyph->bitmap.rows * pFont->FtFace->glyph->bitmap.pitch));
							Resize_Array((void**)&pTextImages1, pTextImages1Size, pTextImages1Size + 1, sizeof(*pTextImages1));
							Graphics_Ref_Create_DummyTEXI(&pTextImages1[pTextImages1Size], Format, pFont->FtFace->glyph->bitmap.pitch / details.ChannelCount, pFont->FtFace->glyph->bitmap.rows, 1, 1, lsize, lsize);
							memcpy(pTextImages1[pTextImages1Size]->Data, pFont->FtFace->glyph->bitmap.buffer, lsize);
							pGPU_effect->Size[0] = ((((float)pTextImages1[pTextImages1Size]->Width * scalefactor) / 2) / (float)pGraphicsWindow->CurrentExtentWidth);
							pGPU_effect->Size[1] = ((((float)pTextImages1[pTextImages1Size]->Height * scalefactor) / 2) / (float)pGraphicsWindow->CurrentExtentHeight);
							pGPU_effect->TextureOffset[0] = TotalTextureWidth1;
							pGPU_effect->TextureOffset[1] = 0;
							pGPU_effect->TextureSize[0] = pTextImages1[pTextImages1Size]->Width;
							pGPU_effect->TextureSize[1] = pTextImages1[pTextImages1Size]->Height;
							pGPU_effect->mode = 0;
							TotalTextureWidth1 += pTextImages1[pTextImages1Size]->Width;
							pTextImages1Size += 1;
						}
					}
				}

				if (FT_HAS_KERNING(pFont->FtFace))
				{
					FT_Vector delta;
					FT_Get_Kerning(pFont->FtFace, PreviousCodePoint, CurrentCodePoint, FT_KERNING_DEFAULT, &delta);
					AdvanceX += (delta.x >> 6) * scalefactor;
					AdvanceY += (delta.y >> 6) * scalefactor;
				}

				pGPU_effect->Position[0] = (pEffect->Position[0] - pEffect->Size[0]) + pGPU_effect->Size[0] + ((((pFont->FtFace->glyph->metrics.horiBearingX >> 6) * scalefactor) + AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth);
				pGPU_effect->Position[1] = (pEffect->Position[1] - pEffect->Size[1]) + pGPU_effect->Size[1] - ((((pFont->FtFace->glyph->metrics.horiBearingY >> 6) * scalefactor) - AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight);
				pGPU_effect->Position[2] = pEffect->Position[2];
				
				if (tab == true) {
					pGPU_effect->AdvanceX = AdvanceX;
					pGPU_effect->AdvanceY = AdvanceY;
					AdvanceX += ((pFont->FtFace->glyph->advance.x >> 6) * scalefactor) * Utils.TabIndents;
				}
				else
				{
					pGPU_effect->AdvanceX = AdvanceX;
					pGPU_effect->AdvanceY = AdvanceY;
					AdvanceX += (pFont->FtFace->glyph->advance.x >> 6) * scalefactor;
				}			
				//AdvanceY += (pFont->FtFace->glyph->advance.y >> 6);
				glm_vec2_copy(pEffect->BoundingBoxPosition, pGPU_effect->BoundingBoxPosition);
				glm_vec2_copy(pEffect->BoundingBoxSize, pGPU_effect->BoundingBoxSize);

			}
			PreviousCodePoint = CurrentCodePoint;
		}
		free(UTF32_Text);
		if (pTextImages1Size != NULL)
		{
			if (pImageSource1->ImageData != NULL)
				free(pImageSource1->ImageData);

			if ((tres = Graphics_Ref_Create_ImageAtlas(pTextImages1, pTextImages1Size, &pImageSource1->ImageData)) != Success)
				return tres;

			for (size_t i = 0; i < pTextImages1Size; i++)
				free(pTextImages1[i]);
			free(pTextImages1);
			//Object_Ref_ReCreate_ResourceHeader(pImageSource1->Header.Allocation);
			Object_Ref_ReCreate_ResourceHeader(pTexture1->Header.Allocation, &Texture1Instance, ThreadIndex);
		}
		else
		{
			if (pImageSource1->ImageData != NULL)
				free(pImageSource1->ImageData);

			if ((tres = Graphics_Ref_Create_ImageAtlas(pTextImages0, pTextImages0Size, &pImageSource1->ImageData)) != Success)
				return tres;
			//Object_Ref_ReCreate_ResourceHeader(pImageSource1->Header.Allocation);
			Object_Ref_ReCreate_ResourceHeader(pTexture1->Header.Allocation, &Texture1Instance, ThreadIndex);
		}
		if (pTextImages0Size != NULL)
		{
			if (pImageSource0->ImageData != NULL)
				free(pImageSource0->ImageData);

			if ((tres = Graphics_Ref_Create_ImageAtlas(pTextImages0, pTextImages0Size, &pImageSource0->ImageData)) != Success)
				return tres;

			for (size_t i = 0; i < pTextImages0Size; i++)
				free(pTextImages0[i]);
			free(pTextImages0);
			//Object_Ref_ReCreate_ResourceHeader(pImageSource0->Header.Allocation, );
			Object_Ref_ReCreate_ResourceHeader(pTexture0->Header.Allocation, &Texture0Instance, ThreadIndex);
		}
	}

	if (pEffect->VkPipeline == NULL)
	{
	uint64_t FragmentShader2DCompiledPointer = 0;
	SPIRV FragmentShader2DCompiled[FragmentShader2D_MaxSize];
	memset(FragmentShader2DCompiled, 0, FragmentShader2D_MaxSize * sizeof(*FragmentShader2DCompiled));

	const SPIRV Fragment_Main0[] = FragmentShader2D_Main();
	memcpy((void*)((uint64_t)FragmentShader2DCompiled + (uint64_t)FragmentShader2DCompiledPointer), Fragment_Main0, FragmentShader2D_MainSize); //copy first part
	FragmentShader2DCompiledPointer += FragmentShader2D_MainSize;
	{
		vec4 selectedcolour;
		selectedcolour[0] = 0.0f;
		selectedcolour[1] = 1.0f;
		selectedcolour[2] = 0.0f;
		selectedcolour[3] = 1.0f;

		const SPIRV Fragment_TextureSampling_Atlas[] = FragmentShader2D_TextureSamplingAndTextureMode_Text();
		memcpy((void*)((uint64_t)FragmentShader2DCompiled + (uint64_t)FragmentShader2DCompiledPointer), Fragment_TextureSampling_Atlas, FragmentShader2D_TextureSamplingAndTextureMode_TextSize);
		FragmentShader2DCompiledPointer += FragmentShader2D_TextureSamplingAndTextureMode_TextSize;

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
			memcpy((void*)((uint64_t)FragmentShader2DCompiled + (uint64_t)FragmentShader2DCompiledPointer), Fragment_AlphaMode_Blend, FragmentShader2D_AlphaMode_BlendSize);
			FragmentShader2DCompiledPointer += FragmentShader2D_AlphaMode_BlendSize;
			break;
		}
	}

	const SPIRV Vertex[] = VertexShader2D();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderVertex, Vertex, VertexShader2DSize, "ReCreate_Text()");
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderFragment, FragmentShader2DCompiled, FragmentShader2DCompiledPointer, "ReCreate_Text()");

	uint32_t ShaderCount = 2;
	VkPipelineShaderStageCreateInfo ShaderStages[2];
	memset(ShaderStages, 0, sizeof(*ShaderStages) * ShaderCount);
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
	InputBindingDescs[0].stride = sizeof(GPU_GraphicsEffectText);

	//Attributes
	//size
	InputAttribDescs[0].binding = 0;
	InputAttribDescs[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	InputAttribDescs[0].location = 0;
	InputAttribDescs[0].offset = offsetof(GPU_GraphicsEffectText, Size);
	//position
	InputAttribDescs[1].binding = 0;
	InputAttribDescs[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	InputAttribDescs[1].location = 1;
	InputAttribDescs[1].offset = offsetof(GPU_GraphicsEffectText, Position);

	//bboxsize
	InputAttribDescs[2].binding = 0;
	InputAttribDescs[2].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	InputAttribDescs[2].location = 2;
	InputAttribDescs[2].offset = offsetof(GPU_GraphicsEffectText, BoundingBoxSize);
	//bboxposition
	InputAttribDescs[3].binding = 0;
	InputAttribDescs[3].format = VK_FORMAT_R32G32B32A32_SFLOAT;
	InputAttribDescs[3].location = 3;
	InputAttribDescs[3].offset = offsetof(GPU_GraphicsEffectText, BoundingBoxPosition);
	//textureoffset
	InputAttribDescs[4].binding = 0;
	InputAttribDescs[4].format = VK_FORMAT_R32G32B32A32_SINT;
	InputAttribDescs[4].location = 4;
	InputAttribDescs[4].offset = offsetof(GPU_GraphicsEffectText, TextureOffset);
	//texturesize
	InputAttribDescs[5].binding = 0;
	InputAttribDescs[5].format = VK_FORMAT_R32G32B32A32_SINT;
	InputAttribDescs[5].location = 5;
	InputAttribDescs[5].offset = offsetof(GPU_GraphicsEffectText, TextureSize);

	//pipeline

	VkPipelineVertexInputStateCreateInfo VertexInputInfo;
	memset(&VertexInputInfo, 0, sizeof(VertexInputInfo));
	VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	VertexInputInfo.vertexBindingDescriptionCount = (uint32_t)InputBindingDescsSize;
	VertexInputInfo.pVertexBindingDescriptions = InputBindingDescs; // Optional

	VertexInputInfo.vertexAttributeDescriptionCount = (uint32_t)InputAttribDescsSize;
	VertexInputInfo.pVertexAttributeDescriptions = InputAttribDescs; // Optional


	VkPipelineInputAssemblyStateCreateInfo InputAssemblyState;
	memset(&InputAssemblyState, 0, sizeof(InputAssemblyState));
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
	memset(&ViewportState, 0, sizeof(ViewportState));
	ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportState.viewportCount = 1; //multi screeen~?!?!??!!?
	ViewportState.pViewports = &Viewport;
	ViewportState.scissorCount = 1;
	ViewportState.pScissors = &Scissor;

	VkPipelineRasterizationStateCreateInfo RasterizationState;
	memset(&RasterizationState, 0, sizeof(RasterizationState));
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
	memset(&MultisampleState, 0, sizeof(MultisampleState));
	MultisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	MultisampleState.sampleShadingEnable = VK_FALSE;
	MultisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	MultisampleState.minSampleShading = 1.0f; // Optional
	MultisampleState.pSampleMask = NULL; // Optional
	MultisampleState.alphaToCoverageEnable = VK_FALSE; // Optional
	MultisampleState.alphaToOneEnable = VK_FALSE; // Optional

	VkPipelineColorBlendAttachmentState ColourBlendAttachment;
	memset(&ColourBlendAttachment, 0, sizeof(ColourBlendAttachment));
	ColourBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	ColourBlendAttachment.blendEnable = VK_TRUE;
	ColourBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	ColourBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	ColourBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	ColourBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	ColourBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_DST_ALPHA;
	ColourBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendAttachmentState ColourBlendAttachmentDeffered;
	memset(&ColourBlendAttachmentDeffered, 0, sizeof(ColourBlendAttachmentDeffered));
	ColourBlendAttachmentDeffered.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	VkPipelineColorBlendAttachmentState attachments[4] = { ColourBlendAttachment, ColourBlendAttachment, ColourBlendAttachment, ColourBlendAttachment };
	VkPipelineColorBlendStateCreateInfo ColourBlending;
	memset(&ColourBlending, 0, sizeof(ColourBlending));
	ColourBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColourBlending.attachmentCount = 2;
	ColourBlending.pAttachments = attachments;

	VkPipelineDepthStencilStateCreateInfo DepthStencil;
	memset(&DepthStencil, 0, sizeof(DepthStencil));
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
	memset(&DynamicStates, 0, sizeof(DynamicStates));
	DynamicStates.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	DynamicStates.dynamicStateCount = statesSize;
	DynamicStates.pDynamicStates = states;


	{
		VkGraphicsPipelineCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
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
		Info.layout = ((GraphicsUtils*)GraphicsRes.pUtils)->GenericResources[Graphics_Ref_Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].PipelineLayout2D;
		Info.renderPass = pGraphicsWindow->VkRenderPassDeferred;
		//Info.subpass = 1;
		Info.basePipelineHandle = VK_NULL_HANDLE; // Optional
		Info.basePipelineIndex = -1; // Optional


		if ((res = vkCreateGraphicsPipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipeline)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_Generic2D()", "vkCreateGraphicsPipelines Failed. VkResult == ", res);
			return (Failure);
		}
	}
	}
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Packers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Pack_Text(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const GraphicsEffectText* pEffect, GraphicsEffectText* pCopiedEffect, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedEffect->VkPipeline, 0, sizeof(pCopiedEffect->VkPipeline));

		memset(&pCopiedEffect->GPU_GraphicsEffectInfos, 0, sizeof(pCopiedEffect->GPU_GraphicsEffectInfos));
		memset(&pCopiedEffect->GPU_GraphicsEffectInfosSize, 0, sizeof(pCopiedEffect->GPU_GraphicsEffectInfosSize));

		memset(&pCopiedEffect->VkShaderVertex, 0, sizeof(pCopiedEffect->VkShaderVertex));
		memset(&pCopiedEffect->VkShaderFragment, 0, sizeof(pCopiedEffect->VkShaderFragment));


		if (pEffect->UTF8_Text != NULL)
		{
			memcpy(((void*)((uint64_t)pData + (uint64_t)*pBufferPointer)), pEffect->UTF8_Text, strlen((char*)pEffect->UTF8_Text) + 1);
			pCopiedEffect->UTF8_Text = (UTF8*)*pBufferPointer;
			*pBufferPointer += strlen((char*)pEffect->UTF8_Text) + 1;
		}
	}
	else
	{
		*pBufferPointer += strlen((char*)pEffect->UTF8_Text) + 1;
	}
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect UnPackers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT UnPack_Text(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const GraphicsEffectText* pEffect, GraphicsEffectText* pCopiedEffect, const void* pData, uint32_t ThreadIndex)
{
	if (pEffect->UTF8_Text != NULL)
	{
		const UTF8* pText = (UTF8*)((void*)((uint64_t)pData + (uint64_t)pEffect->UTF8_Text));
		pCopiedEffect->UTF8_Text = (UTF8*)malloc(strlen((char*)pText) + 1);
		memcpy(pCopiedEffect->UTF8_Text, pText, strlen((char*)pText) + 1);
	}
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_Text(ElementGraphics* pElement, GraphicsEffectText* pEffect, GraphicsEffectCreateInfoText* pEffectCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pEffect == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pEffectCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_Text()", "pEffectCreateInfo == NULLPTR");
			return (Invalid_Parameter | Failure);
		}
#endif
		glm_vec2_copy(pEffectCreateInfo->Size, pEffect->Size);
		glm_vec3_copy(pEffectCreateInfo->Position, pEffect->Position);

		glm_vec2_copy(pEffectCreateInfo->BoundingBoxSize, pEffect->BoundingBoxSize);
		glm_vec2_copy(pEffectCreateInfo->BoundingBoxPosition, pEffect->BoundingBoxPosition);

		pEffect->UTF8_Text = (UTF8*)CopyData((void*)pEffectCreateInfo->Text);
		pEffect->FontSize = pEffectCreateInfo->FontSize;
		pEffect->iFontsSize = pEffectCreateInfo->pFontsSize;
		for (size_t i = 0; i < pEffect->iFontsSize; i++)
		{
			pEffect->iFonts[i] = pEffectCreateInfo->pFonts[i]->Header.Allocation;
		}
		ReCreate_Text(pElement, pEffect, ThreadIndex);
	}
	*pAllocationSize = sizeof(GraphicsEffectText) + (sizeof(ResourceHeaderAllocation) * pEffectCreateInfo->pFontsSize);
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//main
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Check_Click(ElementAllocation* pReturnElement, ResourceHeaderAllocation* pReturnResourceHeader, ObjectAllocation* pReturnObject, uint32_t x, uint32_t y)
{	
	float lowest = FLT_MAX;
	for (size_t i = 0; i < ((GraphicsUtils*)GraphicsRes.pUtils)->ElementGraphicsBuffer.Size;)
	{
		ElementGraphics* pElement = (ElementGraphics*)&((GraphicsUtils*)GraphicsRes.pUtils)->ElementGraphicsBuffer.Buffer[i];
		if (pElement->Header.AllocationSize != NULL && pElement->Header.Allocation.Identifier == (uint32_t)GraphicsElement_ElementGraphics)
		{
			RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);
			for (size_t i0 = 0; i0 < pElement->Header.iParentsSize; i0++)
			{
				ResourceHeader* pParentHeader = Object_Ref_Get_ResourceHeaderPointer(pElement->Header.iParents[i0]);
				for (size_t i1 = 0; i1 < pParentHeader->Header.iParentsSize; i1++)
				{
					Object* pObject = Object_Ref_Get_ObjectPointer(pParentHeader->Header.iParents[i1]);
					RHeaderScene* pSceneHeader = (RHeaderScene*)Object_Ref_Scan_ObjectHeadersSingle(pObject->Header.Allocation, (uint32_t)GraphicsHeader_Scene);
					if (pSceneHeader->Active == true)
					{
						uint64_t pointer = 0;
						for (size_t i3 = 0; i3 < pElement->EffectsSize; i3++)
						{
							GraphicsEffect* pEffect = (GraphicsEffect*)((void*)((uint64_t)pElement->Effects + pointer));
							GraphicsEffectSignature* pSignature = NULL;
							GraphicsEffectBufferIndex BufferIndex = NULL;
							Graphics_Effects_Ref_Find_GraphicsEffectSignature(pEffect->Header.Identifier, &pSignature, &BufferIndex);
							if (pEffect->Header.Identifier == GraphicsEffect_Generic2D) {
								GraphicsEffectGeneric2D* pEffect1 = pEffect;

								float px = ((pEffect1->BoundingBoxPosition[0]) * (float)pGraphicsWindow->CurrentExtentWidth);
								float py = ((pEffect1->BoundingBoxPosition[1]) * (float)pGraphicsWindow->CurrentExtentHeight);

								float sx = ((pEffect1->BoundingBoxSize[0]) * (float)pGraphicsWindow->CurrentExtentWidth);
								float sy = ((pEffect1->BoundingBoxSize[1]) * (float)pGraphicsWindow->CurrentExtentHeight);

								if (x > (px - sx) &&
									x < (px + sx) &&
									y > (py - sy) &&
									y < (py + sy) &&
									pEffect1->Position[2] < lowest)
								{
									lowest = pEffect1->Position[2];
									*pReturnElement = pElement->Header.Allocation;
									*pReturnResourceHeader = pParentHeader->Header.Allocation;
									*pReturnObject = pObject->Header.Allocation;
								}
							}else if (pEffect->Header.Identifier == GUIEffect_Text) {
								GraphicsEffectText* pEffect1 = pEffect;

								float px = ((pEffect1->BoundingBoxPosition[0]) * (float)pGraphicsWindow->CurrentExtentWidth);
								float py = ((pEffect1->BoundingBoxPosition[1]) * (float)pGraphicsWindow->CurrentExtentHeight);

								float sx = ((pEffect1->BoundingBoxSize[0]) * (float)pGraphicsWindow->CurrentExtentWidth);
								float sy = ((pEffect1->BoundingBoxSize[1]) * (float)pGraphicsWindow->CurrentExtentHeight);

								if (x > (px - sx) &&
									x < (px + sx) &&
									y > (py - sy) &&
									y < (py + sy) &&
									pEffect1->Position[2] < lowest)
								{
									lowest = pEffect1->Position[2];
									*pReturnElement = pElement->Header.Allocation;
									*pReturnResourceHeader = pParentHeader->Header.Allocation;
									*pReturnObject = pObject->Header.Allocation;
								}
							}
							pointer += pEffect->Header.AllocationSize;
						}
					}
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

TEXRESULT Update_GUI()
{
	ElementAllocation ClickedElement = {0, 0};
	ResourceHeaderAllocation ClickedResourceHeader = { 0, 0 };
	ObjectAllocation ClickedObject = { 0, 0 };
	
	Check_Click(&ClickedElement, &ClickedResourceHeader, &ClickedObject,
		(uint32_t)((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.X_Position, (uint32_t)((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.Y_Position);
	if (Object_Ref_Get_ObjectAllocationValidity(ClickedObject) == Success &&
		Object_Ref_Get_ResourceHeaderAllocationValidity(ClickedResourceHeader) == Success &&
		Object_Ref_Get_ElementAllocationValidity(ClickedElement) == Success)
	{

		Object* pObject = Object_Ref_Get_ObjectPointer(ClickedObject);
		for (size_t i = 0; i < pObject->Header.iResourceHeadersSize; i++)
		{
			if (pObject->Header.iResourceHeaders[i].Identifier == GUIHeader_Button)
			{
				RHeaderButton* pButton = (RHeaderButton*)Object_Ref_Get_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i]);
				Button_Callback* ButtonCallbackFunction = (Button_Callback*)pButton->Callback_Function;
				ButtonCallbackFunction(ClickedElement, ClickedResourceHeader, ClickedObject, pButton, GUIButtonState_Hover);
				if (((EngineUtils*)EngineRes.pUtils)->MouseButton_Callback_state.State == KeyRelease)
					ButtonCallbackFunction(ClickedElement, ClickedResourceHeader, ClickedObject, pButton, GUIButtonState_Release);
				if (((EngineUtils*)EngineRes.pUtils)->MouseButton_Callback_state.State == KeyPress)
					ButtonCallbackFunction(ClickedElement, ClickedResourceHeader, ClickedObject, pButton, GUIButtonState_Press);
				if (((EngineUtils*)EngineRes.pUtils)->MouseButton_Callback_state.State == KeyRepeat)
					ButtonCallbackFunction(ClickedElement, ClickedResourceHeader, ClickedObject, pButton, GUIButtonState_Repeat);
			}
		}
	}
	return Success;
}

TEXRESULT Initialise_GUI()
{
	memset(&Utils, 0, sizeof(Utils));

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Config
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.InitialHeadersMax = 1024;
	Utils.DPI = 96;
	Utils.TabIndents = 4;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Signatures
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderButtonSig.Buffer =		&Utils.RHeaderButtonBuffer;
	Utils.RHeaderButtonSig.ByteLength = sizeof(RHeaderButton);
	Utils.RHeaderButtonSig.Identifier = (uint32_t)GUIHeader_Button;
	Utils.RHeaderButtonSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_ButtonHeader;
	Utils.RHeaderButtonSig.Constructor =(Create_ResourceHeaderTemplate*)&Create_ButtonHeader;
	Utils.RHeaderButtonSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_ButtonHeader;
	Utils.RHeaderButtonSig.Packer =		(Pack_ResourceHeaderTemplate*)&Pack_ButtonHeader;
	Utils.RHeaderButtonSig.UnPacker =	(UnPack_ResourceHeaderTemplate*)&UnPack_ButtonHeader;
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderButtonBuffer, Utils.InitialHeadersMax);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderButtonSig);


	Utils.RHeaderFontSig.Buffer = &Utils.RHeaderFontBuffer;
	Utils.RHeaderFontSig.ByteLength = sizeof(RHeaderFont);
	Utils.RHeaderFontSig.Identifier = (uint32_t)GUIHeader_Font;
	Utils.RHeaderFontSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_FontHeader;
	Utils.RHeaderFontSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_FontHeader;
	Utils.RHeaderFontSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_FontHeader;
	Utils.RHeaderFontSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_FontHeader;
	Utils.RHeaderFontSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_FontHeader;
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderFontBuffer, Utils.InitialHeadersMax);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderFontSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Effects
	///////////////////////////////////////////////////////////////////////////////////////////////
	/**/
	Utils.TextSig.Identifier =		(uint32_t)GUIEffect_Text;
	Utils.TextSig.Constructor =		(Create_GraphicsEffectTemplate*)&Create_Text;
	Utils.TextSig.ReConstructor =	(ReCreate_GraphicsEffectTemplate*)&ReCreate_Text;
	Utils.TextSig.Destructor =		(Destroy_GraphicsEffectTemplate*)&Destroy_Text;
	Utils.TextSig.Packer =			(Pack_GraphicsEffectTemplate*)&Pack_Text;
	Utils.TextSig.UnPacker =		(UnPack_GraphicsEffectTemplate*)&UnPack_Text;
	Utils.TextSig.Draw =			(Draw_GraphicsEffectTemplate*)&Draw_Text;
	Utils.TextSig.Update =			(Update_GraphicsEffectTemplate*)&Update_Text;
	Utils.TextSig.UpdateSignature = &UpdateSignature_Text;
	Utils.TextSig.SignatureGPUBuffersSize = 1; //param2d
	Graphics_Effects_Ref_Register_GraphicsEffectSignature(&Utils.TextSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Other
	///////////////////////////////////////////////////////////////////////////////////////////////

	FT_Error err = 0;
	if ((err = FT_Init_FreeType(&Utils.FtLibrary)) != 0)
	{
		Engine_Ref_FunctionError("Initialise_GUI()", FT_Error_String(err), err);
		return (Failure);
	}
	return (Success);
}

TEXRESULT Destroy_GUI()
{
	///////////////////////////////////////////////////////////////////////////////////////////////
	//Signatures
	///////////////////////////////////////////////////////////////////////////////////////////////

	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderButtonBuffer);
	Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderFontBuffer);

	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderButtonSig);	
	Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderFontSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//effects
	///////////////////////////////////////////////////////////////////////////////////////////////
	
	//Graphics_Effects_Ref_DeRegister_GraphicsEffectSignature(&Utils.TextSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//other
	///////////////////////////////////////////////////////////////////////////////////////////////

	FT_Error err = 0;
	if ((err = FT_Done_FreeType(Utils.FtLibrary)) != 0)
	{
		Engine_Ref_FunctionError("Destroy_GUI()", FT_Error_String(err), err);
		return;
	}
	Utils.FtLibrary = NULL;

	//memset(&Utils, 0, sizeof(Utils));
	//memset(&Config, 0, sizeof(Config));
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

	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"GUI::InitialHeadersMax"), &Utils.InitialHeadersMax, 1, sizeof(Utils.InitialHeadersMax));
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"GUI::DPI"), &Utils.DPI, 1, sizeof(Utils.DPI));
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"GUI::TabIndents"), &Utils.TabIndents, 1, sizeof(Utils.TabIndents));

	//Resources
	ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData((void*)"GUI::Utils"), &GUIRes.pUtils, &Utils);

	//Functions
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"GUI::Initialise_GUI"), &GUIRes.pInitialise_GUI, &Initialise_GUI, Construct, 100.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"GUI::Destroy_GUI"), &GUIRes.pDestroy_GUI, &Destroy_GUI, Destruct, 100.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"GUI::Update_GUI"), &GUIRes.pUpdate_GUI, &Update_GUI, MouseButton_Input, 0.01f, 0, NULL);

}
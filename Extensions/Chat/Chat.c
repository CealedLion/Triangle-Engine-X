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
#include "Graphics.h"
#include "GraphicsEffects.h"
#include "Audio.h"
#include "Network.h"
#include "Formats.h"
#define TEX_EXPOSE_GUI
#include "GUI.h"
#include "Chemistry.h"

volatile struct{
	UTF8* DefaultIP; // = (UTF8*)"216.58.223.255";
}Config;

const float speed = 0.001f;
const float mouseSpeed = 0.00000001f;
const float ScrollSpeed = 50.0f;

double lasttime = 0.0;

uint64_t CurClickedElementTextIterator; //only if text
ElementAllocation CurClickedElement;
ResourceHeaderAllocation CurClickedResourceHeader;
ObjectAllocation CurClickedObject;

bool selecting = false;

ElementAllocation iTextCursor;

ElementAllocation iFPS_DisplayText;

ElementAllocation iMolecularSimulation;

typedef struct PreviousTextInstance{
	UTF8* Text;
	uint64_t CursorIndex;
	ElementAllocation iElement;
}PreviousTextInstance;

PreviousTextInstance* PreviousTexts;
uint64_t PreviousTextsSize;
uint64_t PreviousTextsIndex;

uint64_t SelectedTextStartIndex;
uint64_t SelectedTextEndIndex;

uint64_t SelectedTextStartIndex1;
uint64_t SelectedTextEndIndex1;

//////////////////////////////////////////////////////////////////////////
//Macros
//////////////////////////////////////////////////////////////////////////

void ButtonClick_Callback(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedObject, RHeaderButton* pButton, GUIButtonCallbackState Action)
{
	CurClickedElement = ClickedElement;
	CurClickedResourceHeader = ClickedResourceHeader;
	CurClickedObject = ClickedObject;
}

void Add_PrevText(GraphicsEffectText* pEffect)
{
	if (PreviousTextsIndex != 0)
	{
		for (size_t i = 0; i < PreviousTextsSize; i++)
		{
			free(PreviousTexts[i].Text);
		}
		free(PreviousTexts);
		PreviousTexts = NULL;
		PreviousTextsSize = 0;
		PreviousTextsIndex = 0;
	}
	Resize_Array(&PreviousTexts, PreviousTextsSize, PreviousTextsSize + 1, sizeof(*PreviousTexts));
	PreviousTexts[PreviousTextsSize].Text = CopyData(pEffect->UTF8_Text);
	PreviousTexts[PreviousTextsSize].CursorIndex = CurClickedElementTextIterator;
	PreviousTextsSize += 1;
}

void Update_Cursor(RHeaderGraphicsWindow* pGraphicsWindow, GraphicsEffectText* pEffect, GPU_GraphicsEffectText* pTargetElement)
{
	ElementGraphics* pElementTextCursor = Object_Ref_Get_ElementPointer(iTextCursor);
	GraphicsEffectGeneric2D* pEffect2D = NULL;
	Graphics_Effects_Ref_Get_GraphicsEffect(pElementTextCursor, GraphicsEffect_Generic2D, &pEffect2D);

	RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElementTextCursor->iMaterial);
	RHeaderTexture* pTexture0 = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pMaterial->BaseColourTexture.iTexture);
	RHeaderImageSource* pImageSource0 = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture0->iImageSource);

	
	float scalefactor = ((float)((pEffect->FontSize * ((GUIUtils*)GUIRes.pUtils)->DPI) / 72) / (float)(pImageSource0->ImageData->Height) / 2);
	pEffect2D->Size[0] = (((float)(pImageSource0->ImageData->Width * scalefactor) / 2) / (float)pGraphicsWindow->CurrentExtentWidth);
	pEffect2D->Size[1] = (((float)(pImageSource0->ImageData->Height * scalefactor) / 2) / (float)pGraphicsWindow->CurrentExtentHeight);

	pEffect2D->Position[0] = (pEffect->Position[0] - pEffect->Size[0]) + ((pTargetElement->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth);
	pEffect2D->Position[1] = (pEffect->Position[1] - pEffect->Size[1]) - pEffect2D->Size[1] + ((pTargetElement->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight);
	pEffect2D->Position[2] = pEffect->Position[2];

	glm_vec2_copy(pEffect2D->Size, pEffect2D->BoundingBoxSize);
	glm_vec2_copy(pEffect2D->Position, pEffect2D->BoundingBoxPosition);
}

void InsertCodepoint(RHeaderGraphicsWindow* pGraphicsWindow, UTF32 codepoint)
{
	ElementInstance ElementInstance;
	Object_Ref_CreateInstance_Element(CurClickedElement, &ElementInstance, 0);
	ElementGraphics* pElementGraphics = ElementInstance.pInstance;

	GraphicsEffectText* pEffect = NULL;
	Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

	Add_PrevText(pEffect);

	UTF32* UTF32_Text = NULL;
	UTF8_To_UTF32(pEffect->UTF8_Text, &UTF32_Text);
	
	uint64_t presize = UTF32strlen(UTF32_Text) + 1;
	if (SelectedTextEndIndex - SelectedTextStartIndex != 0)
	{
		if (SelectedTextStartIndex >= 0 && SelectedTextEndIndex < presize)
		{
			uint64_t size = SelectedTextEndIndex - SelectedTextStartIndex;

			RemoveMember_Array(&UTF32_Text, presize, SelectedTextStartIndex, sizeof(*UTF32_Text), size);

			if (CurClickedElementTextIterator != SelectedTextStartIndex)
			{
				CurClickedElementTextIterator -= size;
			}
			SelectedTextEndIndex = CurClickedElementTextIterator;
			SelectedTextStartIndex = CurClickedElementTextIterator;
		}
	}
	presize = UTF32strlen(UTF32_Text) + 1;
	if (CurClickedElementTextIterator >= 0 && SelectedTextEndIndex <= presize)
	{
		InsertMember_Array(&UTF32_Text, UTF32strlen(UTF32_Text) + 1, CurClickedElementTextIterator, sizeof(*UTF32_Text), &codepoint, 1);
		CurClickedElementTextIterator++;
	}

	free(pEffect->UTF8_Text);
	UTF32_To_UTF8(UTF32_Text, &pEffect->UTF8_Text);
	Object_Ref_ReCreate_Element(CurClickedElement, &ElementInstance, 0);
	Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator]);
}

void RemoveCodepoint(RHeaderGraphicsWindow* pGraphicsWindow)
{
	ElementInstance ElementInstance;
	Object_Ref_CreateInstance_Element(CurClickedElement, &ElementInstance, 0);
	ElementGraphics* pElementGraphics = ElementInstance.pInstance;

	GraphicsEffectText* pEffect = NULL;
	Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

	Add_PrevText(pEffect);

	UTF32* UTF32_Text = NULL;
	UTF8_To_UTF32(pEffect->UTF8_Text, &UTF32_Text);

	uint64_t presize = UTF32strlen(UTF32_Text) + 1;
	if (SelectedTextEndIndex - SelectedTextStartIndex != 0)
	{
		if (SelectedTextStartIndex >= 0 && SelectedTextEndIndex < presize)
		{
			uint64_t size = SelectedTextEndIndex - SelectedTextStartIndex;

			RemoveMember_Array(&UTF32_Text, presize, SelectedTextStartIndex, sizeof(*UTF32_Text), size);

			if (CurClickedElementTextIterator != SelectedTextStartIndex)
			{
				CurClickedElementTextIterator -= size;
			}
			SelectedTextEndIndex = CurClickedElementTextIterator;
			SelectedTextStartIndex = CurClickedElementTextIterator;
			selecting = false;
		}
	}
	else
	{
		if (CurClickedElementTextIterator > 0 && SelectedTextEndIndex <= presize)
		{
			RemoveMember_Array(&UTF32_Text, presize, CurClickedElementTextIterator - 1, sizeof(*UTF32_Text), 1);
			CurClickedElementTextIterator--;
		}
	}

	free(pEffect->UTF8_Text);
	UTF32_To_UTF8(UTF32_Text, &pEffect->UTF8_Text);
	Object_Ref_ReCreate_Element(CurClickedElement, &ElementInstance, 0);
	Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator]);
}

//////////////////////////////////////////////////////////////////////////
//Callbacks
//////////////////////////////////////////////////////////////////////////

TEXRESULT Close_Callback()
{
	Object_Ref_Write_TEIF((const UTF8*)"BIN.teif", 0);
	Engine_Ref_Exit_Application();
	return (Success);
}

TEXRESULT Character_Callback()
{
	ResourceHeaderSignature* windowsignature;
	ResourceHeaderBufferIndex BufferIndex1 = 0;
	Object_Ref_Find_ResourceHeaderSignature(GraphicsHeader_GraphicsWindow, &windowsignature, &BufferIndex1);
	RHeaderGraphicsWindow* pGraphicsWindow = ((RHeaderGraphicsWindow*)&windowsignature->Buffer->Buffer[0]);

	
	if (((EngineUtils*)EngineRes.pUtils)->Character_Callback_state.CodePoint == 'm')
	{
		Engine_Ref_Set_WindowFullScreen(pGraphicsWindow->pWindow, !pGraphicsWindow->pWindow->FullScreen);
		return (Success);
	}

	//control keys
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_CONTROL == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_CONTROL == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_V == KeyPress)
	{
		ElementInstance ElementInstance;
		Object_Ref_CreateInstance_Element(CurClickedElement, &ElementInstance, 0);
		ElementGraphics* pElementGraphics = ElementInstance.pInstance;

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		Add_PrevText(pEffect);

		UTF8* ClipboardText = NULL;
		uint64_t ClipboardTextSize = NULL;
		Engine_Ref_Read_ClipboardUTF8(pGraphicsWindow->pWindow, NULL, &ClipboardTextSize);
		ClipboardText = malloc(ClipboardTextSize);
		Engine_Ref_Read_ClipboardUTF8(pGraphicsWindow->pWindow, ClipboardText, &ClipboardTextSize);


		UTF32* UTF32_Text = NULL;
		UTF8_To_UTF32(pEffect->UTF8_Text, &UTF32_Text);

		uint64_t presize = UTF32strlen(UTF32_Text) + 1;
		if (SelectedTextEndIndex - SelectedTextStartIndex != 0)
		{
			if (SelectedTextStartIndex > 0 && SelectedTextEndIndex < presize)
			{
				uint64_t size = SelectedTextEndIndex - SelectedTextStartIndex;

				RemoveMember_Array(&UTF32_Text, presize, SelectedTextStartIndex, sizeof(*UTF32_Text), size);

				if (CurClickedElementTextIterator != SelectedTextStartIndex)
				{
					CurClickedElementTextIterator -= size;
				}
				SelectedTextEndIndex = CurClickedElementTextIterator;
				SelectedTextStartIndex = CurClickedElementTextIterator;
				selecting = false;
			}
		}
	
		if (ClipboardText != NULL)
		{
			UTF32* UTF32_ClipboardText = NULL;
			UTF8_To_UTF32(ClipboardText, &UTF32_ClipboardText);

			InsertMember_Array(&UTF32_Text, UTF32strlen(UTF32_Text) + 1, CurClickedElementTextIterator, sizeof(*UTF32_Text), UTF32_ClipboardText, UTF32strlen(UTF32_ClipboardText));
			CurClickedElementTextIterator += UTF32strlen(UTF32_ClipboardText);

			free(UTF32_ClipboardText);
		}

		free(ClipboardText);
		free(pEffect->UTF8_Text);
		UTF32_To_UTF8(UTF32_Text, &pEffect->UTF8_Text);
		Object_Ref_ReCreate_Element(CurClickedElement, &ElementInstance, 0);
		Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator]);
		return (Success);
	}
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_CONTROL == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_CONTROL == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_X == KeyPress)
	{
		ElementInstance ElementInstance;
		Object_Ref_CreateInstance_Element(CurClickedElement, &ElementInstance, 0);
		ElementGraphics* pElementGraphics = ElementInstance.pInstance;

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		Add_PrevText(pEffect);

		UTF32* UTF32_Text = NULL;
		UTF8_To_UTF32(pEffect->UTF8_Text, &UTF32_Text);

		uint64_t presize = UTF32strlen(UTF32_Text) + 1;
		if (SelectedTextEndIndex - SelectedTextStartIndex != 0)
		{
			if (SelectedTextStartIndex > 0 && SelectedTextEndIndex < presize)
			{
				uint64_t size = SelectedTextEndIndex - SelectedTextStartIndex;

				UTF32* utf32newtext = calloc(size + 1, sizeof(*UTF32_Text));
				memcpy(utf32newtext, UTF32_Text + (SelectedTextStartIndex), size * sizeof(*UTF32_Text));
				utf32newtext[size] = '\0';

				UTF8* utf8newtext = NULL;
				UTF32_To_UTF8(utf32newtext, &utf8newtext);
				Engine_Ref_Write_ClipboardUTF8(pGraphicsWindow->pWindow, utf8newtext);
				free(utf32newtext);
				free(utf8newtext);

				RemoveMember_Array(&UTF32_Text, presize, SelectedTextStartIndex, sizeof(*UTF32_Text), size);

				if (CurClickedElementTextIterator != SelectedTextStartIndex)
				{
					CurClickedElementTextIterator -= size;
				}
				SelectedTextEndIndex = CurClickedElementTextIterator;
				SelectedTextStartIndex = CurClickedElementTextIterator;
				selecting = false;
			}
		}
		free(pEffect->UTF8_Text);
		UTF32_To_UTF8(UTF32_Text, &pEffect->UTF8_Text);
		Object_Ref_ReCreate_Element(CurClickedElement, &ElementInstance, 0);
		Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator]);
		return (Success);
	}
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_CONTROL == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_CONTROL == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_C == KeyPress)
	{
		ElementGraphics* pElementGraphics = NULL;
		Object_Ref_StartThread_Element(CurClickedElement, 0, &pElementGraphics);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);


		UTF32* UTF32_Text = NULL;
		UTF8_To_UTF32(pEffect->UTF8_Text, &UTF32_Text);

		uint64_t presize = UTF32strlen(UTF32_Text) + 1;
		if (SelectedTextEndIndex - SelectedTextStartIndex != 0)
		{
			if (SelectedTextStartIndex >= 0 && SelectedTextEndIndex < presize)
			{
				uint64_t size = SelectedTextEndIndex - SelectedTextStartIndex;

				UTF32* utf32newtext = calloc(size + 1, sizeof(*UTF32_Text));
				memcpy(utf32newtext, UTF32_Text + (SelectedTextStartIndex), size * sizeof(*UTF32_Text));
				utf32newtext[size] = '\0';

				UTF8* utf8newtext = NULL;
				UTF32_To_UTF8(utf32newtext, &utf8newtext);
				Engine_Ref_Write_ClipboardUTF8(pGraphicsWindow->pWindow, utf8newtext);
				free(utf32newtext);
				free(utf8newtext);
			}
		}
		free(pEffect->UTF8_Text);
		UTF32_To_UTF8(UTF32_Text, &pEffect->UTF8_Text);
		return (Success);
	}
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_CONTROL == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_CONTROL == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_Z == KeyPress)
	{
		ElementInstance ElementInstance;
		Object_Ref_CreateInstance_Element(CurClickedElement, &ElementInstance, 0);
		ElementGraphics* pElementGraphics = ElementInstance.pInstance;

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		if (PreviousTextsIndex == 0)
		{
			Resize_Array(&PreviousTexts, PreviousTextsSize, PreviousTextsSize + 1, sizeof(*PreviousTexts));
			PreviousTexts[PreviousTextsSize].Text = CopyData(pEffect->UTF8_Text);
			PreviousTexts[PreviousTextsSize].CursorIndex = CurClickedElementTextIterator;
			PreviousTextsSize += 1;
			PreviousTextsIndex++;
		}

		if (PreviousTextsIndex < PreviousTextsSize)
		{
			PreviousTextsIndex++;
			free(pEffect->UTF8_Text);
			pEffect->UTF8_Text = CopyData(PreviousTexts[PreviousTextsSize - PreviousTextsIndex].Text);
			CurClickedElementTextIterator = PreviousTexts[PreviousTextsSize - PreviousTextsIndex].CursorIndex;
		}
		Object_Ref_ReCreate_Element(CurClickedElement, &ElementInstance, 0);
		Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator]);
		return (Success);
	}
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_CONTROL == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_CONTROL == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_Y == KeyPress)
	{
		ElementInstance ElementInstance;
		Object_Ref_CreateInstance_Element(CurClickedElement, &ElementInstance, 0);
		ElementGraphics* pElementGraphics = ElementInstance.pInstance;

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		if (PreviousTextsIndex == 0)
		{
			Resize_Array(&PreviousTexts, PreviousTextsSize, PreviousTextsSize + 1, sizeof(*PreviousTexts));
			PreviousTexts[PreviousTextsSize].Text = CopyData(pEffect->UTF8_Text);
			PreviousTexts[PreviousTextsSize].CursorIndex = CurClickedElementTextIterator;
			PreviousTextsSize += 1;
		}

		if (PreviousTextsIndex > 1)
		{
			PreviousTextsIndex--;
			free(pEffect->UTF8_Text);
			pEffect->UTF8_Text = CopyData(PreviousTexts[PreviousTextsSize - PreviousTextsIndex].Text);
			CurClickedElementTextIterator = PreviousTexts[PreviousTextsSize - PreviousTextsIndex].CursorIndex;
		}
		Object_Ref_ReCreate_Element(CurClickedElement, &ElementInstance, 0);
		Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator]);
		return (Success);
	}

	//typing
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_SHIFT == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_SHIFT == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_ENTER == KeyPress && Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success))
	{
		InsertCodepoint(pGraphicsWindow, 0x0D);
		InsertCodepoint(pGraphicsWindow, 0x0A);
		return (Success);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_TAB == KeyPress && Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success))
	{
		//4 indents
		InsertCodepoint(pGraphicsWindow, 0x09);
		//InsertCodepoint(pGraphicsWindow, 0x20);
		//InsertCodepoint(pGraphicsWindow, 0x20);
		//InsertCodepoint(pGraphicsWindow, 0x20);
		return (Success);
	}
	if (((EngineUtils*)EngineRes.pUtils)->Character_Callback_state.CodePoint == 0x08 && Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success))
	{
		RemoveCodepoint(pGraphicsWindow);
		return (Success);
	}
	if (((EngineUtils*)EngineRes.pUtils)->Character_Callback_state.CodePoint >= 32 && Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success))
	{
		InsertCodepoint(pGraphicsWindow, ((EngineUtils*)EngineRes.pUtils)->Character_Callback_state.CodePoint);
		return (Success);
	}
	return (Success);
}

TEXRESULT Click_Callback()
{
	ResourceHeaderSignature* windowsignature;
	ResourceHeaderBufferIndex BufferIndex1 = 0;
	Object_Ref_Find_ResourceHeaderSignature(GraphicsHeader_GraphicsWindow, &windowsignature, &BufferIndex1);
	RHeaderGraphicsWindow* pGraphicsWindow = ((RHeaderGraphicsWindow*)&windowsignature->Buffer->Buffer[0]);

	if (pGraphicsWindow->pWindow->STATE_MOUSE_BUTTON_1 == KeyPress && (pGraphicsWindow->pWindow->STATE_KEY_LEFT_SHIFT == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_SHIFT == KeyPress) && Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success)) //get next closet character to the cursor
	{
		ElementInstance ElementInstance;
		Object_Ref_CreateInstance_Element(CurClickedElement, &ElementInstance, 0);
		ElementGraphics* pElementGraphics = ElementInstance.pInstance;

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];


		vec2 pa;
		glm_vec2_zero(pa);
		pa[0] = ((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.X_Position / pGraphicsWindow->CurrentExtentWidth;
		pa[1] = ((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.Y_Position / pGraphicsWindow->CurrentExtentHeight;
		float halffactor = (float)((pEffect->FontSize * ((GUIUtils*)GUIRes.pUtils)->DPI) / 72) / 4;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			vec2 pb;
			glm_vec2_zero(pb);
			pb[0] = ((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth));
			pb[1] = ((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY - halffactor) / (float)pGraphicsWindow->CurrentExtentHeight));
			float distance = glm_vec2_distance(pa, pb);
			if (distance < max)
			{
				max = distance;
				CurClickedElementTextIterator = i;
				pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			}
		}
		SelectedTextEndIndex = CurClickedElementTextIterator;

		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			pEffect->GPU_GraphicsEffectInfos[i].selected = 0;
		}
		for (size_t i = SelectedTextStartIndex; i < SelectedTextEndIndex; i++)
		{
			pEffect->GPU_GraphicsEffectInfos[i].selected = 1;
		}
		Object_Ref_ReCreate_Element(CurClickedElement, &ElementInstance, 0);
		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest);
		return (Success);
	}
	if (pGraphicsWindow->pWindow->STATE_MOUSE_BUTTON_1 == KeyPress && Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success)) //get next closet character to the cursor
	{
		ElementGraphics* pElementGraphics = NULL;
		Object_Ref_StartThread_Element(CurClickedElement, 0, &pElementGraphics);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		vec2 pa;
		glm_vec2_zero(pa);
		pa[0] = ((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.X_Position / pGraphicsWindow->CurrentExtentWidth;
		pa[1] = ((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.Y_Position / pGraphicsWindow->CurrentExtentHeight;
		float halffactor = (float)((pEffect->FontSize * ((GUIUtils*)GUIRes.pUtils)->DPI) / 72) / 4;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			vec2 pb;
			glm_vec2_zero(pb);
			pb[0] = ((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth));
			pb[1] = ((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY - halffactor) / (float)pGraphicsWindow->CurrentExtentHeight));
			float distance = glm_vec2_distance(pa, pb);
			if (distance < max)
			{
				max = distance;
				CurClickedElementTextIterator = i;
				pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			}
		}
		SelectedTextStartIndex1 = CurClickedElementTextIterator;
		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest);
		selecting = true;
		return (Success);
	}
	return (Success);
}

TEXRESULT Key_Callback()
{
	ResourceHeaderSignature* windowsignature;
	ResourceHeaderBufferIndex BufferIndex1 = 0;
	Object_Ref_Find_ResourceHeaderSignature(GraphicsHeader_GraphicsWindow, &windowsignature, &BufferIndex1);
	RHeaderGraphicsWindow* pGraphicsWindow = ((RHeaderGraphicsWindow*)&windowsignature->Buffer->Buffer[0]);

	//navigation keys
	if (pGraphicsWindow->pWindow->STATE_KEY_RIGHT == KeyPress && Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success)) //get next closet character to the right
	{
		ElementGraphics* pElementGraphics = NULL;
		Object_Ref_StartThread_Element(CurClickedElement, 0, &pElementGraphics);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		float halffactor = (float)((pEffect->FontSize * ((GUIUtils*)GUIRes.pUtils)->DPI) / 72) / 8;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			if (((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) > ((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_oldEffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) &&
				((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) < max &&
				((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY - halffactor) / (float)pGraphicsWindow->CurrentExtentHeight)) <= ((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) &&
				((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY + halffactor) / (float)pGraphicsWindow->CurrentExtentHeight)) >= ((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)))
			{
				max = ((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth));
				CurClickedElementTextIterator = i;
				pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			}
		}
		if ((pGPU_EffectClosest == pGPU_oldEffectClosest) && CurClickedElementTextIterator < pEffect->GPU_GraphicsEffectInfosSize - 1)
		{
			CurClickedElementTextIterator++;
			pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		}
		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_LEFT == KeyPress && Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success)) //get next closet character to the left
	{
		ElementGraphics* pElementGraphics = NULL;
		Object_Ref_StartThread_Element(CurClickedElement, 0, &pElementGraphics);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		float halffactor = (float)((pEffect->FontSize * ((GUIUtils*)GUIRes.pUtils)->DPI) / 72) / 8;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			if (((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) < ((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_oldEffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) &&
				((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) > -max &&
				((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY - halffactor) / (float)pGraphicsWindow->CurrentExtentHeight)) <= ((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) &&
				((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY + halffactor) / (float)pGraphicsWindow->CurrentExtentHeight)) >= ((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)))
			{
				max = ((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth));
				CurClickedElementTextIterator = i;
				pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			}
		}
		if ((pGPU_EffectClosest == pGPU_oldEffectClosest) && CurClickedElementTextIterator > 1)
		{
			CurClickedElementTextIterator--;
			pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		}
		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_UP == KeyPress && Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success)) //get next closet character to the top
	{
		ElementGraphics* pElementGraphics = NULL;
		Object_Ref_StartThread_Element(CurClickedElement, 0, &pElementGraphics);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		float halffactor = (float)((pEffect->FontSize * ((GUIUtils*)GUIRes.pUtils)->DPI) / 72) / 8;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			if (((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) < ((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_oldEffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) &&
				((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) > -max &&
				((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX - halffactor) / (float)pGraphicsWindow->CurrentExtentWidth)) <= ((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) &&
				((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX + halffactor) / (float)pGraphicsWindow->CurrentExtentWidth)) >= ((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)))
			{
				max = ((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight));
				CurClickedElementTextIterator = i;
				pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			}
		}
		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_DOWN == KeyPress && Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success)) //get next closet character to the bototm
	{
		ElementGraphics* pElementGraphics = NULL;
		Object_Ref_StartThread_Element(CurClickedElement, 0, &pElementGraphics);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		float halffactor1 = (float)((pEffect->FontSize * ((GUIUtils*)GUIRes.pUtils)->DPI) / 72) / 8;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			if (((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) > ((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_oldEffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) &&
				((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) < max &&
				((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX - halffactor1) / (float)pGraphicsWindow->CurrentExtentWidth)) <= ((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) &&
				((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX + halffactor1) / (float)pGraphicsWindow->CurrentExtentWidth)) >= ((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)))
			{
				max = ((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight));
				CurClickedElementTextIterator = i;
				pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			}
		}
		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest);
	}
	return (Success);
}

TEXRESULT Scroll_Callback()
{
	ResourceHeaderSignature* windowsignature;
	ResourceHeaderBufferIndex BufferIndex1 = 0;
	Object_Ref_Find_ResourceHeaderSignature(GraphicsHeader_GraphicsWindow, &windowsignature, &BufferIndex1);
	RHeaderGraphicsWindow* pGraphicsWindow = ((RHeaderGraphicsWindow*)&windowsignature->Buffer->Buffer[0]);

	if (Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success))
	{
		ElementGraphics* pElementGraphics = NULL;
		Object_Ref_StartThread_Element(CurClickedElement, 0, &pElementGraphics);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		pEffect->Position[1] += (((EngineUtils*)EngineRes.pUtils)->Scroll_Callback_state.Delta / (float)pGraphicsWindow->CurrentExtentHeight) * ScrollSpeed;

		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			pEffect->GPU_GraphicsEffectInfos[i].Position[1] += (((EngineUtils*)EngineRes.pUtils)->Scroll_Callback_state.Delta / (float)pGraphicsWindow->CurrentExtentHeight) * ScrollSpeed;
		}
		Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator]);
		return (Success);
	}
	return (Success);
}

//////////////////////////////////////////////////////////////////////////
//Main Function///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

TEXRESULT Update_Chat()
{	
	
	ResourceHeaderSignature* windowsignature;
	ResourceHeaderBufferIndex BufferIndex1 = 0;
	Object_Ref_Find_ResourceHeaderSignature(GraphicsHeader_GraphicsWindow, &windowsignature, &BufferIndex1);
	RHeaderGraphicsWindow* pGraphicsWindow = ((RHeaderGraphicsWindow*)&windowsignature->Buffer->Buffer[0]);
	
	ResourceHeaderSignature* camerasignature;
	ResourceHeaderBufferIndex BufferIndex = 0;
	Object_Ref_Find_ResourceHeaderSignature(GraphicsHeader_Camera, &camerasignature, &BufferIndex);
	RHeaderCamera* pCameraHeader = ((RHeaderCamera*)&camerasignature->Buffer->Buffer[0]);
	
	if (pGraphicsWindow->pWindow->STATE_MOUSE_BUTTON_1 == KeyRelease)
	{
		selecting = false;
	}
	if (selecting == true)
	{
		if (Object_Ref_Get_ElementAllocationValidity(CurClickedElement) == (Success))
		{
			ElementGraphics* pElementGraphics = NULL;
			Object_Ref_StartThread_Element(CurClickedElement, 0, &pElementGraphics);

			GraphicsEffectText* pEffect = NULL;
			Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

			GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

			vec2 pa;
			glm_vec2_zero(pa);
			pa[0] = ((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.X_Position / pGraphicsWindow->CurrentExtentWidth;
			pa[1] = ((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.Y_Position / pGraphicsWindow->CurrentExtentHeight;
			float halffactor = (float)((pEffect->FontSize * ((GUIUtils*)GUIRes.pUtils)->DPI) / 72) / 4;
			float max = FLT_MAX;
			for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
			{
				GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
				vec2 pb;
				glm_vec2_zero(pb);
				pb[0] = ((pEffect->Position[0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth));
				pb[1] = ((pEffect->Position[1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY - halffactor) / (float)pGraphicsWindow->CurrentExtentHeight));
				float distance = glm_vec2_distance(pa, pb);
				if (distance < max)
				{
					max = distance;
					CurClickedElementTextIterator = i;
					pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
				}
			}
			SelectedTextEndIndex1 = CurClickedElementTextIterator;

			if (CurClickedElementTextIterator < SelectedTextStartIndex1)
			{
				SelectedTextStartIndex = SelectedTextEndIndex1;
				SelectedTextEndIndex = SelectedTextStartIndex1;
			}
			else
			{
				SelectedTextStartIndex = SelectedTextStartIndex1;
				SelectedTextEndIndex = SelectedTextEndIndex1;
			}
			for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
			{
				pEffect->GPU_GraphicsEffectInfos[i].selected = 0;
			}
			for (size_t i = SelectedTextStartIndex; i < SelectedTextEndIndex; i++)
			{
				pEffect->GPU_GraphicsEffectInfos[i].selected = 1;
			}
			Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest);
		}
	}
	/**/
	if (((double)clock() / (double)CLOCKS_PER_SEC) - lasttime > 1.0)//fps counter shit
	{	
		double FPS = ((double)pGraphicsWindow->FramesDone);
		double MSPF = 1000.0f / ((double)pGraphicsWindow->FramesDone);
		pGraphicsWindow->FramesDone = 0;
		
		lasttime = ((double)clock() / (double)CLOCKS_PER_SEC);

		ElementInstance ElementInstance;
		Object_Ref_CreateInstance_Element(iFPS_DisplayText, &ElementInstance, 0);
		ElementGraphics* pElementGraphics = ElementInstance.pInstance;

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		free(pEffect->UTF8_Text);

		char buffer[128 + 19];
		snprintf(&buffer, 128 + 19, "FPS: %f | MSPF: %f", ((float)FPS), ((float)MSPF));


		pEffect->UTF8_Text = CopyData(buffer); //this is why its error in debug mode.
		Object_Ref_ReCreate_Element(iFPS_DisplayText, &ElementInstance, 0);
	}
	
	
	RHeaderPosition* pPositionHeader = (RHeaderPosition*)Object_Ref_Scan_ObjectHeadersSingle(pCameraHeader->Header.iParents[0], (uint32_t)GraphicsHeader_Position);
	
	float framehorizontalAngle = mouseSpeed * ((float)pGraphicsWindow->CurrentExtentWidth / 2.0f - ((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.X_Position);
	float frameverticalAngle = mouseSpeed * ((float)pGraphicsWindow->CurrentExtentHeight / 2.0f - ((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.Y_Position);

	//framehorizontalAngle = 0;
	//frameverticalAngle = 0;

	vec4 Translation;
	glm_vec3_zero(Translation);
	mat4 Rotation;
	glm_mat4_zero(Rotation);
	vec3 Scale;
	glm_vec3_one(Scale);

	glm_decompose(pPositionHeader->Matrix, Translation, Rotation, Scale);

	vec3 right;
	glm_vec3_zero(right);
	right[0] = -1.0f;
	right[1] = 0.0f;
	right[2] = 0.0f;
	glm_vec3_rotate_m4(Rotation, right, right);

	vec3 direction;
	glm_vec3_zero(direction);
	direction[0] = 0.0f;
	direction[1] = 0.0f;
	direction[2] = 1.0f;
	glm_vec3_rotate_m4(Rotation, direction, direction);

	vec3 up;
	glm_vec3_zero(up);
	up[0] = 0.0f;
	up[1] = -1.0f;
	up[2] = 0.0f;
	glm_vec3_rotate_m4(Rotation, up, up);
	
	vec3 speedvec3;
	glm_vec3_zero(speedvec3);
	speedvec3[0] = speed;
	speedvec3[1] = speed;
	speedvec3[2] = speed;
	
	if (pGraphicsWindow->pWindow->STATE_KEY_W == KeyPress)
	{
		vec3 vector;
		glm_vec3_zero(vector);
		glm_vec3_mul(direction, speedvec3, vector);
		glm_vec3_sub(Translation, vector, Translation);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_S == KeyPress)
	{
		vec3 vector;
		glm_vec3_zero(vector);
		glm_vec3_mul(direction, speedvec3, vector);
		glm_vec3_add(Translation, vector, Translation);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_D == KeyPress)
	{
		vec3 vector;
		glm_vec3_zero(vector);
		glm_vec3_mul(right, speedvec3, vector);
		glm_vec3_sub(Translation, vector, Translation);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_A == KeyPress)
	{
		vec3 vector;
		glm_vec3_zero(vector);
		glm_vec3_mul(right, speedvec3, vector);
		glm_vec3_add(Translation, vector, Translation);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_Q == KeyPress)
	{
		vec3 vector;
		glm_vec3_zero(vector);
		glm_vec3_mul(up, speedvec3, vector);
		glm_vec3_sub(Translation, vector, Translation);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_E == KeyPress)
	{
		vec3 vector;
		glm_vec3_zero(vector);
		glm_vec3_mul(up, speedvec3, vector);
		glm_vec3_add(Translation, vector, Translation);
	}
	
	mat4 identitym;
	glm_mat4_identity(identitym);
	mat4 translationm;
	glm_mat4_identity(translationm);
	glm_translate(translationm, Translation);
	mat4 rotationm;
	glm_mat4_copy(Rotation, rotationm);


	vec3 horiz;
	glm_vec3_zero(horiz);
	horiz[0] = -1;
	horiz[1] = 0;
	horiz[2] = 0;

	vec3 vertic;
	glm_vec3_zero(vertic);
	vertic[0] = 0;
	vertic[1] = 1;
	vertic[2] = 0;

	mat4 scalem;
	glm_mat4_identity(scalem);
	glm_scale(scalem, Scale);


	glm_mul_sse2(translationm, rotationm, pPositionHeader->Matrix);
	glm_mul_sse2(pPositionHeader->Matrix, scalem, pPositionHeader->Matrix);
	glm_mul_sse2(pPositionHeader->Matrix, identitym, pPositionHeader->Matrix);

	//glm_rotate(pPositionHeader->Matrix, frameverticalAngle, horiz);
	glm_rotate(pPositionHeader->Matrix, framehorizontalAngle, vertic);
	return (Success);
}

TEXRESULT Initialise_Chat()
{
	for (size_t i = 0; i < 1; i++)
	{
		ObjectAllocation iObject;
		{
			ObjectCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)Object_Generic;
			MainCreateInfo.Name = NULL;
			Object_Ref_Create_Object(&iObject, MainCreateInfo, NULL, 0);
		}
		ResourceHeaderAllocation iGraphicsWindow;
		{
			RHeaderGraphicsWindowCreateInfo CreateInfo;
			memset(&CreateInfo, 0, sizeof(CreateInfo));
			CreateInfo.TargetExtentWidth = 1024;
			CreateInfo.TargetExtentHeight = 1024;
			CreateInfo.TargetFrameBuffersSize = 1;
			ResourceHeaderCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_GraphicsWindow;
			MainCreateInfo.Name = "Triangle Engine X";
			Object_Ref_Create_ResourceHeader(&iGraphicsWindow, MainCreateInfo, &CreateInfo, 0);
			Object_Ref_Add_Object_ResourceHeaderChild(iGraphicsWindow, iObject);
		}

		ResourceHeaderAllocation iScene;
		{
			RHeaderSceneCreateInfo CreateInfo;
			memset(&CreateInfo, 0, sizeof(CreateInfo));
			CreateInfo.InitialActive = true;
			ResourceHeaderCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Scene;
			MainCreateInfo.Name = NULL;
			Object_Ref_Create_ResourceHeader(&iScene, MainCreateInfo, &CreateInfo, 0);
			Object_Ref_Add_Object_ResourceHeaderChild(iScene, iObject);
		}

		Formats_Ref_Load_2Dscene((const UTF8*)"data\\GUI\\2Dscene.json",
			(RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow), Object_Ref_Get_ResourceHeaderPointer(iScene), 0);

		//TEXRESULT ress = Formats_Ref_Load_3Dscene((const UTF8*)"data\\Models\\z-23\\scene.gltf",
		//	(RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow), Object_Ref_Get_ResourceHeaderPointer(iScene), 0);

		{
			ResourceHeaderAllocation iResourceHeaderParent;
			{
				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)ResourceHeader_Generic;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iResourceHeaderParent, MainCreateInfo, NULL, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iResourceHeaderParent, iObject);
			}

			ResourceHeaderAllocation iMaterial;
			{
				RHeaderMaterialCreateInfo CreateInfoMaterial;
				memset(&CreateInfoMaterial, 0, sizeof(CreateInfoMaterial));

				CreateInfoMaterial.pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow);

				CreateInfoMaterial.BaseColourFactor[0] = 1.0f;
				CreateInfoMaterial.BaseColourFactor[1] = 1.0f;
				CreateInfoMaterial.BaseColourFactor[2] = 1.0f;
				CreateInfoMaterial.BaseColourFactor[3] = 1.0f;

				CreateInfoMaterial.AlphaMode = AlphaMode_Blend;


				{
					ResourceHeaderAllocation iImageSource;
					{
						RHeaderImageSourceCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Graphics_Ref_Create_DummyTEXI(&Info.ImageData, GraphicsFormat_Undefined, 0, 0, 0, 1, 0, 0);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_ImageSource;
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iImageSource, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject);
						free(Info.ImageData);
					}
					ResourceHeaderAllocation iTextureHeader;
					{
						RHeaderTextureCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Info.pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow);
						Info.pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(iImageSource);
						Info.AllocationType = AllocationType_Discrite;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit | TextureUsage_StorageBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject);
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
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iImageSource, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject);
						free(Info.ImageData);
					}
					ResourceHeaderAllocation iTextureHeader;
					{
						RHeaderTextureCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Info.pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow);
						Info.pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(iImageSource);
						Info.AllocationType = AllocationType_Discrite;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit | TextureUsage_StorageBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject);
					}
					CreateInfoMaterial.EmissiveTexture.iTexture = iTextureHeader;
				}

				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iMaterial, MainCreateInfo, &CreateInfoMaterial, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iMaterial, iObject);
			}

			{
				RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(iMaterial);
				ElementGraphicsCreateInfo CreateInfo;
				memset(&CreateInfo, 0, sizeof(CreateInfo));
				CreateInfo.pMaterial = pMaterial;
				CreateInfo.pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow);

				CreateInfo.EffectCreateInfosSize = 1;
				CreateInfo.EffectCreateInfos = (ElementGraphicsCreateInfoEffect*)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));

				ChemistryEffectCreateInfoFundamental Info;
				memset(&Info, 0, sizeof(Info));

				CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)ChemistryEffects_Fundamental;
				CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &Info;

				Info.ChunkSize = 1;
				Info.Resolution = 5096;

				Info.ParticlesSize = (3000);
				Info.Particles = calloc(Info.ParticlesSize, sizeof(*Info.Particles));

				uint64_t it = 0;	
				
				/*
				for (size_t i1 = 0; i1 < 4; i1++)
				{
					for (size_t i = 0; i < 32; i++)
					{
						Info.Particles[it].Position[0] = -(-0.0f + (-0.8 * i1)) + (i * 0.1);
						Info.Particles[it].Position[1] = -(-5.0f + (0.8 * i1)) + (i * 0.1);
						Info.Particles[it].Position[2] = 0;
						Info.Particles[it].Position[3] = i1 % 2 ? -1 : 1;
						Info.Particles[it].PositionVelocity[0] = -1.0f;
						Info.Particles[it].PositionVelocity[1] = 1.0f;
						Info.Particles[it].PositionVelocity[2] = 0;
						glm_vec3_normalize(Info.Particles[it].PositionVelocity);
						it++;
					}
				}
			
				for (size_t ix = 0; ix < 16; ix++)
				{
					for (size_t iy = 0; iy < 16; iy++)
					{
						for (size_t iz = 0; iz < 16; iz++)
						{
							Info.Particles[it].Position[0] = ix;
							Info.Particles[it].Position[1] = iy;
							Info.Particles[it].Position[2] = iz;
							Info.Particles[it].Position[3] = 1.0f;
							Info.Particles[it].PositionVelocity[0] = 1.0f;
							Info.Particles[it].PositionVelocity[1] = 0.0f;
							Info.Particles[it].PositionVelocity[2] = 0.0f;
							it++;
						}
					}
				}
				
				
				for (size_t i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 0; i < 25; i++)
					{
						Info.Particles[it].Position[0] = 0.0f;
						Info.Particles[it].Position[1] = 0.0f;
						Info.Particles[it].Position[2] = (0.0f + i);
						Info.Particles[it].Position[3] = 1.0f;
						Info.Particles[it].PositionVelocity[0] = 0.0f;
						Info.Particles[it].PositionVelocity[1] = 0.0f;
						Info.Particles[it].PositionVelocity[2] = -1;

						Info.Particles[it].Position[1] += 10.0f;
						it++;
					}
				}
			*/
				
		
				uint64_t val = 0;
				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 5; i < 6; i++)
					{
						float height = i;

						val = (M_PI * 2 * height);
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos(i1 * (6.28318531f / val)) * height;
							Info.Particles[it].Position[1] = sin(i1 * (6.28318531f / val)) * height;
							Info.Particles[it].Position[2] = 0.0f;
							Info.Particles[it].Position[3] = 1.0f;
							Info.Particles[it].PositionVelocity[0] = ((cos((i1 + 1) * (6.28318531f / val)) * (height * 1.0)) - Info.Particles[it].Position[0]);
							Info.Particles[it].PositionVelocity[1] = ((sin((i1 + 1) * (6.28318531f / val)) * (height * 1.0)) - Info.Particles[it].Position[1]);
							Info.Particles[it].PositionVelocity[2] = 0.0f;

							Info.Particles[it].Position[1] += 10.0f;

							it++;
						}
					}
				}
				
				
				/*
				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 0; i < 20; i++)
					{
						val = (M_PI * 2 * (i));
						val = 500;
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos(i1 * (6.28318531f / (val))) * (i);
							Info.Particles[it].Position[1] = sin(i1 * (6.28318531f / (val))) * (i);
							Info.Particles[it].Position[2] = i0;
							Info.Particles[it].Position[3] = (i / 4) % 2 ? -1 : 1;
							Info.Particles[it].PositionVelocity[0] = cos(i1 * (6.28318531f / (val)));
							Info.Particles[it].PositionVelocity[1] = sin(i1 * (6.28318531f / (val)));
							Info.Particles[it].PositionVelocity[2] = 0.0f;

							Info.Particles[it].Position[0] += 40;

							it++;
						}
					}
				}

				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 0; i < 20; i++)
					{
						val = (M_PI * 2 * (i));
						val = 500;
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos(i1 * (6.28318531f / (val))) * (i);
							Info.Particles[it].Position[1] = sin(i1 * (6.28318531f / (val))) * (i);
							Info.Particles[it].Position[2] = i0;
							Info.Particles[it].Position[3] = (i / 4) % 2 ? -1 : 1;
							Info.Particles[it].PositionVelocity[0] = cos(i1 * (6.28318531f / (val)));
							Info.Particles[it].PositionVelocity[1] = sin(i1 * (6.28318531f / (val)));
							Info.Particles[it].PositionVelocity[2] = 0.0f;

							Info.Particles[it].Position[0] -= 40;

							it++;
						}
					}
				}
			
				
				uint64_t ringc = 24;
				
				for (size_t i0 = 0; i0 < ringc; i0++)
				{
					for (size_t i = 1; i < 5; i++)
					{
						float height = i * 0.5;
						val = (M_PI * 2 * height) * 4;
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = (cos(i1 * (6.28318531f / val)) * height);
							Info.Particles[it].Position[1] = 0.0f;
							Info.Particles[it].Position[2] = sin(i1 * (6.28318531f / val)) * height;
							Info.Particles[it].Position[3] = 1.0f;
							Info.Particles[it].PositionVelocity[0] = ((cos((i1 + 1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[0]);
							Info.Particles[it].PositionVelocity[1] = 0.0f;
							Info.Particles[it].PositionVelocity[2] = ((sin((i1 + 1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[2]);

							Info.Particles[it].Position[0] += height;

							vec3 axis = {0.0f, 0.0f, 1.0f};


							glm_vec3_rotate(Info.Particles[it].Position, (i0 * (6.28318531f / ringc)), axis);
							glm_vec3_rotate(Info.Particles[it].PositionVelocity, (i0 * (6.28318531f / ringc)), axis);

							Info.Particles[it].Position[1] += 20.0f;

							it++;
						}
					}
				}	
				*/

				Engine_Ref_FunctionError("PARTICLES SIZE", "AAA", it);

				ElementCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_Element(&iMolecularSimulation, MainCreateInfo, &CreateInfo, 0);
				Object_Ref_Add_ResourceHeader_ElementChild(iMolecularSimulation, iResourceHeaderParent);
				free(CreateInfo.EffectCreateInfos);
				free(Info.Particles);
			}
		}
		
		{
			ResourceHeaderAllocation iResourceHeaderParent;
			{
				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)ResourceHeader_Generic;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iResourceHeaderParent, MainCreateInfo, NULL, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iResourceHeaderParent, iObject);

			}


			ResourceHeaderAllocation iMaterial;
			{
				RHeaderMaterialCreateInfo CreateInfoMaterial;
				memset(&CreateInfoMaterial, 0, sizeof(CreateInfoMaterial));

				CreateInfoMaterial.pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow);

				CreateInfoMaterial.BaseColourFactor[0] = 1.0f;
				CreateInfoMaterial.BaseColourFactor[1] = 0.0f;
				CreateInfoMaterial.BaseColourFactor[2] = 0.0f;
				CreateInfoMaterial.BaseColourFactor[3] = 1.0f;

				CreateInfoMaterial.AlphaMode = AlphaMode_Blend;

				{
					ResourceHeaderAllocation iImageSource;
					{
						RHeaderImageSourceCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Graphics_Ref_Create_DummyTEXI(&Info.ImageData, GraphicsFormat_Undefined, 0, 0, 0, 1, 0, 0);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_ImageSource;
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iImageSource, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject);
						free(Info.ImageData);
					}
					ResourceHeaderAllocation iTextureHeader;
					{
						RHeaderTextureCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Info.pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow);
						Info.pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(iImageSource);
						Info.AllocationType = AllocationType_Linear;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject);
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
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iImageSource, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject);
						free(Info.ImageData);
					}
					ResourceHeaderAllocation iTextureHeader;
					{
						RHeaderTextureCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Info.pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow);
						Info.pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(iImageSource);
						Info.AllocationType = AllocationType_Linear;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject);
					}
					CreateInfoMaterial.EmissiveTexture.iTexture = iTextureHeader;
				}

				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iMaterial, MainCreateInfo, &CreateInfoMaterial, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iMaterial, iObject);
			}

			{
				RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(iMaterial);
				ElementGraphicsCreateInfo CreateInfo;
				memset(&CreateInfo, 0, sizeof(CreateInfo));
				CreateInfo.pMaterial = pMaterial;
				CreateInfo.pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow);

				CreateInfo.EffectCreateInfosSize = 1;
				CreateInfo.EffectCreateInfos = (ElementGraphicsCreateInfoEffect*)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));

				pMaterial->BaseColourMode = MaterialMode_Alpha;
				GraphicsEffectCreateInfoText InfoText;
				memset(&InfoText, 0, sizeof(InfoText));

				CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)GUIEffect_Text;
				CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &InfoText;

				InfoText.Text = (UTF8*)"FPS:";
				InfoText.FontSize = 100;

				InfoText.pFontsSize = 2;
				InfoText.pFonts = (RHeaderFont**)calloc(InfoText.pFontsSize, sizeof(*InfoText.pFonts));
				{
					ResourceHeaderAllocation iFont;
					RHeaderFontCreateInfo CreateInfoFont;
					memset(&CreateInfoFont, 0, sizeof(CreateInfoFont));
					Open_Data(&CreateInfoFont.Data, (UTF8*)"data\\Fonts\\NotoSerif\\NotoSerif-Regular.ttf");
					ResourceHeaderCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GUIHeader_Font;
					MainCreateInfo.Name = NULL;
					Object_Ref_Create_ResourceHeader(&iFont, MainCreateInfo, &CreateInfoFont, 0);
					Object_Ref_Add_Object_ResourceHeaderChild(iFont, iObject);
					InfoText.pFonts[0] = (RHeaderFont*)Object_Ref_Get_ResourceHeaderPointer(iFont);
					free(CreateInfoFont.Data.pData);
				}
				{
					ResourceHeaderAllocation iFont;
					RHeaderFontCreateInfo CreateInfoFont;
					memset(&CreateInfoFont, 0, sizeof(CreateInfoFont));
					Open_Data(&CreateInfoFont.Data, (UTF8*)"data\\Fonts\\NotoColorEmoji\\NotoColorEmoji.ttf");
					ResourceHeaderCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GUIHeader_Font;
					MainCreateInfo.Name = NULL;
					Object_Ref_Create_ResourceHeader(&iFont, MainCreateInfo, &CreateInfoFont, 0);
					Object_Ref_Add_Object_ResourceHeaderChild(iFont, iObject);
					InfoText.pFonts[1] = (RHeaderFont*)Object_Ref_Get_ResourceHeaderPointer(iFont);
					free(CreateInfoFont.Data.pData);
				}

				InfoText.Size[0] = 0.4f;
				InfoText.Size[1] = 0.10f;

				InfoText.Position[0] = 0.4f;
				InfoText.Position[1] = 1.0f;

				for (size_t i1 = 0; i1 < 2; i1++)
					InfoText.BoundingBoxSize[i1] = InfoText.Size[i1];

				for (size_t i1 = 0; i1 < 2; i1++)
					InfoText.BoundingBoxPosition[i1] = InfoText.Position[i1];

				ElementCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_Element(&iFPS_DisplayText, MainCreateInfo, &CreateInfo, 0);
				Object_Ref_Add_ResourceHeader_ElementChild(iFPS_DisplayText, iResourceHeaderParent);
				free(CreateInfo.EffectCreateInfos);
				free(InfoText.pFonts);
			}
		}	
	}
		
	/*
	for (size_t i = 0; i < 1; i++)
	{
		ObjectAllocation iObject;
		{
			ObjectCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)Object_Generic;
			MainCreateInfo.Name = NULL;
			Object_Ref_Create_Object(&iObject, MainCreateInfo, NULL, 0);
		}
		ResourceHeaderAllocation iGraphicsWindow;
		{
			RHeaderGraphicsWindowCreateInfo CreateInfo;
			memset(&CreateInfo, 0, sizeof(CreateInfo));
			CreateInfo.TargetExtentWidth = 1000;
			CreateInfo.TargetExtentHeight = 1000;
			CreateInfo.TargetFrameBuffersSize = 4;
			ResourceHeaderCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_GraphicsWindow;
			MainCreateInfo.Name = "Triangle Engine X";
			Object_Ref_Create_ResourceHeader(&iGraphicsWindow, MainCreateInfo, &CreateInfo, 0);
			Object_Ref_Add_Object_ResourceHeaderChild(iGraphicsWindow, iObject);
		}

		ResourceHeaderAllocation iScene;
		{
			RHeaderSceneCreateInfo CreateInfo;
			memset(&CreateInfo, 0, sizeof(CreateInfo));
			CreateInfo.InitialActive = true;
			ResourceHeaderCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Scene;
			MainCreateInfo.Name = NULL;
			Object_Ref_Create_ResourceHeader(&iScene, MainCreateInfo, &CreateInfo, 0);
			Object_Ref_Add_Object_ResourceHeaderChild(iScene, iObject);
		}

		Formats_Ref_Load_2Dscene((const UTF8*)"data\\GUI\\2Dscene.json",
			(RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow), Object_Ref_Get_ResourceHeaderPointer(iScene), 0);




		RHeaderScene* pScene = Object_Ref_Get_ResourceHeaderPointer(iScene);
		for (size_t i = 0; i < pScene->Header.iParentsSize; i++)
		{
			Object* pgameobject = Object_Ref_Get_ObjectPointer(pScene->Header.iParents[i]);
			for (size_t i1 = 0; i1 < pgameobject->Header.iResourceHeadersSize; i1++)
			{
				ResourceHeader* pResourceHeader = Object_Ref_Get_ResourceHeaderPointer(pgameobject->Header.iResourceHeaders[i1]);
				for (size_t i2 = 0; i2 < pResourceHeader->Header.iElementsSize; i2++)
				{
					Element* pElement = Object_Ref_Get_ElementPointer(pResourceHeader->Header.iElements[i2]);
					if (strcmp(pElement->Header.Name, "TextCursor") == 0)
					{
						iTextCursor = pElement->Header.Allocation;
					}
				}
			}
		}

		/*
		{
			ResourceHeaderAllocation iResourceHeaderParent;
			{
				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)ResourceHeader_Generic;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iResourceHeaderParent, MainCreateInfo, NULL, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iResourceHeaderParent, iObject);

			}

			ResourceHeaderAllocation iMaterial;
			{
				RHeaderMaterialCreateInfo CreateInfoMaterial;
				memset(&CreateInfoMaterial, 0, sizeof(CreateInfoMaterial));

				CreateInfoMaterial.pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow);

				CreateInfoMaterial.BaseColourFactor[0] = 1.0f;
				CreateInfoMaterial.BaseColourFactor[1] = 1.0f;
				CreateInfoMaterial.BaseColourFactor[2] = 1.0f;
				CreateInfoMaterial.BaseColourFactor[3] = 1.0f;

				CreateInfoMaterial.AlphaMode = AlphaMode_Opaque;

				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iMaterial, MainCreateInfo, &CreateInfoMaterial, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iMaterial, iObject);
			}

			{
				RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(iMaterial);
				ElementGraphicsCreateInfo CreateInfo;
				memset(&CreateInfo, 0, sizeof(CreateInfo));
				CreateInfo.pMaterial = pMaterial;
				CreateInfo.pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow);

				CreateInfo.EffectCreateInfosSize = 1;
				CreateInfo.EffectCreateInfos = (ElementGraphicsCreateInfoEffect*)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));

				ChemistryEffectCreateInfoSimplifiedMolecular Info;
				memset(&Info, 0, sizeof(Info));

				CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)ChemistryEffects_SimplifiedMolecular;
				CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &Info;

				Info.ParticlesSize = 1;
				Info.Particles = calloc(Info.ParticlesSize, sizeof(*Info.Particles));

				Info.Particles[0].Position[0] = 0.0f;
				Info.Particles[0].Size = 1.0f;
				Info.Particles[0].Charge = 1.0f;
				/*
				for (size_t i = 0; i < 8; i++)
				{
					Info.Particles[1 + i].Position[0] = 0.0f;
					Info.Particles[1 + i].Size = 0.0005f;
					Info.Particles[1 + i].Charge = -1.0f;
				}




				ElementCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_Element(&iMolecularSimulation, MainCreateInfo, &CreateInfo, 0);
				Object_Ref_Add_ResourceHeader_ElementChild(iMolecularSimulation, iResourceHeaderParent);
				free(CreateInfo.EffectCreateInfos);
				free(Info.Particles);
			}
		}
	*/
	/*
		ResourceHeaderAllocation iAudioSource;
		{
			RHeaderAudioSourceCreateInfo CreateInfo;
			memset(&CreateInfo, 0, sizeof(CreateInfo));
			//basic playback
			const UTF8* path = (UTF8*)"data\\Audio\\syntheticdawn-maintheme.wav";
			FileData audiofile;
			Open_Data(&audiofile, path);
			TEXA_HEADER* header = NULL;
			Audio_Convert_Ref_XtoTEXA(&audiofile, &header, wav);
			free(audiofile.pData);
			CreateInfo.AudioData = header;
			ResourceHeaderCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)AudioHeader_AudioSource;
			MainCreateInfo.Name = NULL;
			Object_Ref_Create_ResourceHeader(&iAudioSource, MainCreateInfo, &CreateInfo);
			Object_Ref_Add_Object_ResourceHeaderChild(iAudioSource, iObject);
			free(header);
		}


		RHeaderAudioSource* pAudioSource = (RHeaderAudioSource*)Object_Ref_Get_ResourceHeaderPointer(iAudioSource);

		ElementAllocation iAudioElement;
		{
			ElementAudioCreateInfo CreateInfo;
			memset(&CreateInfo, 0, sizeof(CreateInfo));
			CreateInfo.UsageFlags = AudioElementUsage_Playback;
			CreateInfo.pAudioSource = pAudioSource;
			CreateInfo.StartFrame = 0;

			AudioEffectCreateInfoVolume InfoVolume;
			memset(&InfoVolume, 0, sizeof(InfoVolume));
			InfoVolume.Volume = 1.0f;


			CreateInfo.EffectCreateInfosSize = 1;
			CreateInfo.EffectCreateInfos = (void**)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));

			CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)AudioEffect_Volume;
			CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &InfoVolume;

			ElementCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)AudioElement_ElementAudio;
			MainCreateInfo.Name = NULL;
			Object_Ref_Create_Element(&iAudioElement, MainCreateInfo, &CreateInfo);
			Object_Ref_Add_ResourceHeader_ElementChild(iAudioElement, iAudioSource);
			free(CreateInfo.EffectCreateInfos);
		}


		ElementAudio* pAudioElement = Object_Ref_Get_ElementPointer(iAudioElement);

		//Convert_AudioData(&pAudioSource->AudioData, Format::int32LE);
		//std::thread thread(Convert_AudioData, &pAudioSource->AudioData, Format::int32LE);
		//thread.detach();
		//RHeaderOutputStream* pOutputStream = (RHeaderOutputStream*)Object_Ref_Get_ResourceHeaderPointer(oheader);
		Audio_Ref_Start_OutputStream(pAudioElement);
		*/
	//Object_Ref_Write_TEIF((const UTF8*)"BIN.teif", 0);	
	//Object_Ref_Read_TEIF((const UTF8*)"BIN.teif", 0);	

	return (TEXRESULT)((Success));
}

TEXRESULT Destroy_Chat()
{

	return (Success);
}

struct ChatResStruct
{
	void* pInitialise_Chat;
	void* pDestroy_Chat;
	void* pUpdate_Chat;
	void* pButtonClick_Callback;
	void* pKey_Callback;
	void* pCharacter_Callback;
	void* pClick_Callback;
	void* pScroll_Callback;
	void* pClose_Callback;

}ChatRes;

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
	Audio_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	Graphics_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	Network_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	GUI_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	Formats_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);

	//exports
	//resources
	//functions
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Initialise_Chat"), &ChatRes.pInitialise_Chat, &Initialise_Chat, Construct, 10000.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Destroy_Chat"), &ChatRes.pDestroy_Chat, &Destroy_Chat, Destruct, 0.001f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Update_Chat"), &ChatRes.pUpdate_Chat, &Update_Chat, EveryFrame, 0.1f, 0, NULL);
	
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::ButtonClick_Callback"), &ChatRes.pButtonClick_Callback, &ButtonClick_Callback, NoCall, 0.0f, 0, NULL);
	
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Character_Callback"), &ChatRes.pCharacter_Callback, &Character_Callback, Character_Input, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Key_Callback"), &ChatRes.pKey_Callback, &Key_Callback, Key_Input, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Click_Callback"), &ChatRes.pClick_Callback, &Click_Callback, MouseButton_Input, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Scroll_Callback"), &ChatRes.pScroll_Callback, &Scroll_Callback, Scroll_Input, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Close_Callback"), &ChatRes.pClose_Callback, &Close_Callback, Window_Close, 0.0f, 0, NULL);


}


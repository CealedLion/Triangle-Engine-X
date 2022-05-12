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
#include "GUI.h"
#include "Chemistry.h"

//volatile struct {
//	UTF8* DefaultIP; // = (UTF8*)"216.58.223.255";
//}Config;

float speed = 0.01f;
const float mouseSpeed = 0.005f;
const float ScrollSpeed = 50.0f;

ResourceHeaderAllocation iGraphicsWindow = { sizeof(iGraphicsWindow) };

ResourceHeaderAllocation iCameraHeader = { sizeof(iCameraHeader) };

ResourceHeaderAllocation iScene = { sizeof(iScene) };

/////////////////////////////////////////////
//reactor shit
/////////////////////////////////////////////

float reactortemp = 0.0f;
float reactorpercentage = 10.0f;
const float coolingfactor = 10.0f;
const float heatingfactor = 1.0f;

typedef struct PID {
	double SetPoint; // Desired Value

	double Proportion; // Proportional Const
	double Integral; // Integral Const
	double Derivative; // Derivative Const

	double LastError; // Error[-1]
	double PrevError; // Error[-2]
	double SumError; // Sums of Errors
} PID;

double PIDCalc(PID* pp, double NextPoint)
{
	double dError,
		Error;

	pp->SumError += (Error = pp->SetPoint - NextPoint);
	dError = pp->LastError - pp->PrevError;
	pp->PrevError = pp->LastError;
	pp->LastError = Error;


	return (pp->Proportion * Error
		+ pp->Integral * pp->SumError
		+ pp->Derivative * dError
		);
}

PID sPID = {100, 0.2, 0.2, 0.0, 0.0, 0.0, 0.0}; // PID Control Structure
double rOut = 0.0; // PID Response (Output)
double rIn = 0.0; // PID Feedback (Input)

/////////////////////////////////////////////
/////////////////////////////////////////////



double lasttime = 0.0;

uint64_t CurClickedElementTextIterator; //only if text
ElementAllocation CurClickedElement;
ResourceHeaderAllocation CurClickedResourceHeader;
ObjectAllocation CurClickedObject;

bool selecting = false;

ElementAllocation iTextCursor;

ElementAllocation iSelectionBox;


ElementAllocation iFPS_DisplayText;

ElementAllocation iMultiplierText;


ElementAllocation iMolecularSimulation;



typedef struct PrefabIconStruct {
	UTF8* Name;
}PrefabIconStruct;
uint64_t PrefabIconsSize = 0;
PrefabIconStruct* PrefabIcons = NULL;

typedef struct CategoryIconStruct {
	UTF8* Name;
	float Offset;
	int ReverseIndex;
}CategoryIconStruct;
uint64_t CategoryIconsSize = 0;
CategoryIconStruct* CategoryIcons = NULL;


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
//Chemistry Macros
//////////////////////////////////////////////////////////////////////////

void Add_ChemistryElement(ChemistryElementType Element, vec3 Position, GPU_Particle* Particles, uint64_t* pIterator, int32_t flip, bool AutomaticPairing)
{
	Particles[*pIterator].Position[0] = Position[0];
	Particles[*pIterator].Position[1] = Position[1];
	Particles[*pIterator].Position[2] = Position[2];
	Particles[*pIterator].Position[3] = (((1836.15267f * Element) + (1838.68366f * ChemistryElementsNeutrons[Element]))) * 0.01f; //mass
	Particles[*pIterator].PositionVelocity[0] = 0.0f;
	Particles[*pIterator].PositionVelocity[1] = 0.0f;
	Particles[*pIterator].PositionVelocity[2] = 0.0f;
	Particles[*pIterator].PositionVelocity[3] = Element; //charge
	Particles[*pIterator].Magnitude[0] = 0.0f;
	Particles[*pIterator].Magnitude[1] = 0.0f;
	Particles[*pIterator].Magnitude[2] = 1.0f;
	Particles[*pIterator].Magnitude[3] = 0.0f; //nuclear spin exists but eh.
	Particles[*pIterator].Acceleration[1] = -1.0f;
	(*pIterator)++;
	
	int shellsizes[] =     { 2,  2, 6,  2,  6,  10,  2,  6,  10, 14,  2,  6,  10, 14, 18 };
	int shellprevsizes[] = { 0,  2, 4,  10, 12, 18,  28, 30, 36, 46,  60, 62, 68, 78, 92 };
	for (size_t shell = 0; shell < 15; shell++)
	{
		uint32_t val = min(max((int)Element - shellprevsizes[shell], 0), shellsizes[shell]);
		for (size_t i2 = 0; i2 < val; i2++)
		{
			if (AutomaticPairing == true)
			{
				size_t iterator = ((shellsizes[shell] / 2) <= i2) ? (i2 - (shellsizes[shell] / 2)) : (i2);
				Particles[*pIterator].Position[0] = ((cos((iterator) * (6.28318531f / val)) * ((shell + 1) * 1.2)) + Position[0]);
				Particles[*pIterator].Position[1] = ((sin((iterator) * (6.28318531f / val)) * ((shell + 1) * 1.2)) + Position[1]);
				Particles[*pIterator].Position[2] = (-0.001f * iterator) + Position[2];
			}
			else
			{
				Particles[*pIterator].Position[0] = (cos((i2) * (6.28318531f / val)) * ((shell + 1) * 1.2)) + Position[0];
				Particles[*pIterator].Position[1] = (sin((i2) * (6.28318531f / val)) * ((shell + 1) * 1.2)) + Position[1];
				Particles[*pIterator].Position[2] = (-0.001f * i2) + Position[2];			
			}
			Particles[*pIterator].Position[3] = 1.0f; //mass
			Particles[*pIterator].PositionVelocity[0] = (cos((i2 + 1) * (6.28318531f / val)) * 0.00);
			Particles[*pIterator].PositionVelocity[1] = (sin((i2 + 1) * (6.28318531f / val)) * 0.00);
			Particles[*pIterator].PositionVelocity[2] = 0.0f;
			Particles[*pIterator].PositionVelocity[3] = -1.0f; //charge
			Particles[*pIterator].Magnitude[0] = cos((i2 + 1) * (6.28318531f / val)) * 1.0;
			Particles[*pIterator].Magnitude[1] = sin((i2 + 1) * (6.28318531f / val)) * 1.0;
			//Particles[*pIterator].Magnitude[2] = ((shellsizes[shell] / 2) <= i2) ? (flip * -1) : (flip);
			Particles[*pIterator].Magnitude[3] = 1.0f; //spin
			Particles[*pIterator].Acceleration[1] = -1.0f;
			(*pIterator)++;
		}
	}
}
/*
* Added in 1.0.0
* adds a icon that can be clicked, can be either a prefab or a navigation icon. 
* @param iParent is the object that this will be a subcategory of. 
* @param IsNavigation makes it a navigation icon
* @param CategoryOffset is only for navigation icon
* @param CategoryReverseIndex is only for navigation icon
*/
void Add_ChemistryIcon(ObjectAllocation iParent, const UTF8* Name, const UTF8* filepath, const UTF8* mimetype, bool IsNavigation, float CategoryOffset, int CategoryReverseIndex)
{
	uint32_t ThreadIndex = 0;

	uint64_t xindex = 0;
	{
		Object* pParent = Object_Ref_Get_ObjectPointer(iParent, false, false, ThreadIndex);
		xindex = pParent->Header.iChildrenSize;

		Object_Ref_End_ObjectPointer(iParent, false, false, ThreadIndex);
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

	{
		ResourceHeaderAllocation iMaterial;
		{
			RHeaderMaterialCreateInfo CreateInfoMaterial;
			memset(&CreateInfoMaterial, 0, sizeof(CreateInfoMaterial));
			CreateInfoMaterial.iGraphicsWindow = iGraphicsWindow;
			CreateInfoMaterial.BaseColourFactor[0] = 1.0f;
			CreateInfoMaterial.BaseColourFactor[1] = 1.0f;
			CreateInfoMaterial.BaseColourFactor[2] = 1.0f;
			CreateInfoMaterial.BaseColourFactor[3] = 1.0f;
			CreateInfoMaterial.AlphaMode = AlphaMode_Blend;
			FileData pData = { 0, 0 };
			Open_Data(&pData, filepath);
			if (pData.pData != NULL && pData.LinearSize != NULL)
			{
				ResourceHeaderAllocation iImageSource;
				{
					RHeaderImageSourceCreateInfo Info;
					memset(&Info, 0, sizeof(Info));
					uint32_t identifier = *((uint32_t*)((uint64_t)mimetype + sizeof(char)));
					Graphics_Convert_Ref_XtoTEXI(&pData, &Info.ImageData, identifier);
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
					ResourceHeaderCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
					MainCreateInfo.Name = Name;
					Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, ThreadIndex);
					Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, ThreadIndex);
				}
				CreateInfoMaterial.BaseColourTexture.iTexture = iTextureHeader;
			}
			if (Object_Ref_Get_ResourceHeaderAllocationData(CreateInfoMaterial.BaseColourTexture.iTexture) != NULL)
			{
				CreateInfoMaterial.BaseColourMode = MaterialMode_Colour;
			}
			else
			{
				CreateInfoMaterial.BaseColourMode = MaterialMode_Solid;
			}
			ResourceHeaderCreateInfo MainCreateInfo = { sizeof(MainCreateInfo) };
			MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
			MainCreateInfo.Name = Name;
			Object_Ref_Create_ResourceHeader(&iMaterial, MainCreateInfo, &CreateInfoMaterial, ThreadIndex);
			Object_Ref_Add_Object_ResourceHeaderChild(iMaterial, iObject, ThreadIndex);
		}
		ResourceHeaderAllocation iPositionHeader;
		{
			RHeaderPositionCreateInfo CreateInfo = { sizeof(CreateInfo) };

			vec3 Translation;
			glm_vec3_zero(Translation);

			Translation[0] = 0.12f * xindex;
			Translation[1] = 0.0f;
			Translation[2] = 0.0f;

			glm_mat4_identity(CreateInfo.Matrix);

			mat4 translationm;
			glm_mat4_identity(translationm);
			glm_translate(translationm, Translation);

			glm_mul_sse2(translationm, CreateInfo.Matrix, CreateInfo.Matrix);

			ResourceHeaderCreateInfo MainCreateInfo = { sizeof(MainCreateInfo) };
			MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Position;
			MainCreateInfo.Name = Name;
			Object_Ref_Create_ResourceHeader(&iPositionHeader, MainCreateInfo, &CreateInfo, ThreadIndex);
			Object_Ref_Add_Object_ResourceHeaderChild(iPositionHeader, iObject, ThreadIndex);
		}
		ResourceHeaderAllocation iButtonHeader = {sizeof(iButtonHeader)};
		{
			RHeaderButtonCreateInfo CreateInfo = { sizeof(CreateInfo) };
			CreateInfo.CallbackSymbol = CopyData("Chat::IconClick_Callback");

			ResourceHeaderCreateInfo MainCreateInfo = { sizeof(MainCreateInfo) };
			MainCreateInfo.Identifier = (uint32_t)GUIHeader_Button;
			MainCreateInfo.Name = Name;
			Object_Ref_Create_ResourceHeader(&iPositionHeader, MainCreateInfo, &CreateInfo, ThreadIndex);
			Object_Ref_Add_Object_ResourceHeaderChild(iPositionHeader, iObject, ThreadIndex);
		}
		ElementAllocation iElement;
		{
			ElementGraphicsCreateInfo CreateInfo;
			memset(&CreateInfo, 0, sizeof(CreateInfo));
			CreateInfo.iMaterial = iMaterial;
			CreateInfo.iGraphicsWindow = iGraphicsWindow;

			CreateInfo.EffectCreateInfosSize = 1;
			CreateInfo.EffectCreateInfos = (ElementGraphicsCreateInfoEffect*)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));

			GraphicsEffectCreateInfoGeneric2D Info2D;
			memset(&Info2D, 0, sizeof(Info2D));

			CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)GraphicsEffect_Generic2D;
			CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &Info2D;

			Info2D.Size[0] = 0.055f;
			Info2D.Size[1] = 0.055f;

			for (size_t i1 = 0; i1 < 2; i1++)
				Info2D.BoundingBoxSize[i1] = Info2D.Size[i1];
			for (size_t i1 = 0; i1 < 2; i1++)
				Info2D.BoundingBoxPosition[i1] = 0.0f;

			ElementCreateInfo MainCreateInfo = { sizeof(MainCreateInfo) };
			MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
			MainCreateInfo.Name = Name;
			Object_Ref_Create_Element(&iElement, MainCreateInfo, &CreateInfo, ThreadIndex);
			Object_Ref_Add_ResourceHeader_ElementChild(iElement, iPositionHeader, ThreadIndex);
			free(CreateInfo.EffectCreateInfos);
		}
	}

	if (IsNavigation == true)
	{
		Resize_Array(&CategoryIcons, CategoryIconsSize, CategoryIconsSize + 1, sizeof(*CategoryIcons));
		CategoryIcons[CategoryIconsSize].Name = CopyData(Name);
		CategoryIcons[CategoryIconsSize].Offset = CategoryOffset;
		CategoryIcons[CategoryIconsSize].ReverseIndex = CategoryReverseIndex;
		CategoryIconsSize++;
	}
	else if (IsNavigation == false)
	{ 
		Resize_Array(&PrefabIcons, PrefabIconsSize, PrefabIconsSize + 1, sizeof(*PrefabIcons));
		PrefabIcons[PrefabIconsSize].Name = CopyData(Name);
		PrefabIconsSize++;
	}
}

//////////////////////////////////////////////////////////////////////////
//Click Callbacks
//////////////////////////////////////////////////////////////////////////

void FileClick_Callback(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedObject, ResourceHeaderAllocation iButton, GUIButtonCallbackState Action)
{
	static bool clicked = false;
	static bool BGstate = false;
	if (Action == GUIButtonState_Press && clicked == false)
	{
		uint32_t ThreadIndex = 0;

		Object* pObject = Object_Ref_Get_ObjectPointer(ClickedObject, false, false, ThreadIndex);
		{
			ResourceHeaderAllocation iPositionHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(pObject->Header.iChildren[0], GraphicsHeader_Position, ThreadIndex);
			RHeaderPosition* pPositionHeader = Object_Ref_Get_ResourceHeaderPointer(iPositionHeader, true, false, ThreadIndex);
			pPositionHeader->Matrix[3][1] = (BGstate = !BGstate) == true ? 0.058 : -1.0f;
			Object_Ref_End_ResourceHeaderPointer(iPositionHeader, true, false, ThreadIndex);
		}
		Object_Ref_End_ObjectPointer(ClickedObject, false, false, ThreadIndex);

		clicked = true;
	}
	if (Action == GUIButtonState_Release)
	{
		clicked = false;
	}
}

void AddClick_Callback(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedObject, ResourceHeaderAllocation iButton, GUIButtonCallbackState Action)
{
	static bool clicked = false;
	static bool BGstate = false;
	if (Action == GUIButtonState_Press && clicked == false)
	{
		uint32_t ThreadIndex = 0;

		Object* pObject = Object_Ref_Get_ObjectPointer(ClickedObject, false, false, ThreadIndex);
		{
			ResourceHeaderAllocation iPositionHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(pObject->Header.iChildren[0], GraphicsHeader_Position, ThreadIndex);
			RHeaderPosition* pPositionHeader = Object_Ref_Get_ResourceHeaderPointer(iPositionHeader, true, false, ThreadIndex);
			pPositionHeader->Matrix[3][1] = (BGstate = !BGstate) == true ? 0.058 : -1.0f;
			Object_Ref_End_ResourceHeaderPointer(iPositionHeader, true, false, ThreadIndex);
		}
		Object_Ref_End_ObjectPointer(ClickedObject, false, false, ThreadIndex);

		clicked = true;
	}
	if (Action == GUIButtonState_Release)
	{
		clicked = false;
	}
}

void ViewClick_Callback(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedObject, ResourceHeaderAllocation iButton, GUIButtonCallbackState Action)
{
	static bool clicked = false;
	static bool BGstate = false;
	if (Action == GUIButtonState_Press && clicked == false)
	{
		uint32_t ThreadIndex = 0;

		Object* pObject = Object_Ref_Get_ObjectPointer(ClickedObject, false, false, ThreadIndex);
		{
			ResourceHeaderAllocation iPositionHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(pObject->Header.iChildren[0], GraphicsHeader_Position, ThreadIndex);
			RHeaderPosition* pPositionHeader = Object_Ref_Get_ResourceHeaderPointer(iPositionHeader, true, false, ThreadIndex);
			pPositionHeader->Matrix[3][1] = (BGstate = !BGstate) == true ? 0.058 : -1.0f;
			Object_Ref_End_ResourceHeaderPointer(iPositionHeader, true, false, ThreadIndex);
		}
		Object_Ref_End_ObjectPointer(ClickedObject, false, false, ThreadIndex);

		clicked = true;
	}
	if (Action == GUIButtonState_Release)
	{
		clicked = false;
	}
}

void AnalyzeClick_Callback(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedObject, ResourceHeaderAllocation iButton, GUIButtonCallbackState Action)
{
	static bool clicked = false;
	static bool BGstate = false;
	if (Action == GUIButtonState_Press && clicked == false)
	{
		uint32_t ThreadIndex = 0;

		Object* pObject = Object_Ref_Get_ObjectPointer(ClickedObject, false, false, ThreadIndex);
		{
			ResourceHeaderAllocation iPositionHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(pObject->Header.iChildren[0], GraphicsHeader_Position, ThreadIndex);
			RHeaderPosition* pPositionHeader = Object_Ref_Get_ResourceHeaderPointer(iPositionHeader, true, false, ThreadIndex);
			pPositionHeader->Matrix[3][1] = (BGstate = !BGstate) == true ? 0.058 : -1.0f;
			Object_Ref_End_ResourceHeaderPointer(iPositionHeader, true, false, ThreadIndex);
		}
		Object_Ref_End_ObjectPointer(ClickedObject, false, false, ThreadIndex);

		clicked = true;
	}
	if (Action == GUIButtonState_Release)
	{
		clicked = false;
	}

}

void TestClick_Callback(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedObject, ResourceHeaderAllocation iButton, GUIButtonCallbackState Action)
{
	static bool clicked = false;
	static bool BGstate = false;
	if (Action == GUIButtonState_Press && clicked == false)
	{
		uint32_t ThreadIndex = 0;

		Object* pObject = Object_Ref_Get_ObjectPointer(ClickedObject, false, false, ThreadIndex);
		{
			ResourceHeaderAllocation iPositionHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(pObject->Header.iChildren[0], GraphicsHeader_Position, ThreadIndex);
			RHeaderPosition* pPositionHeader = Object_Ref_Get_ResourceHeaderPointer(iPositionHeader, true, false, ThreadIndex);
			pPositionHeader->Matrix[3][1] = (BGstate = !BGstate) == true ? 0.058 : -1.0f;
			Object_Ref_End_ResourceHeaderPointer(iPositionHeader, true, false, ThreadIndex);
		}
		Object_Ref_End_ObjectPointer(ClickedObject, false, false, ThreadIndex);

		clicked = true;
	}
	if (Action == GUIButtonState_Release)
	{
		clicked = false;
	}

}


void FileIconClick_Callback(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedObject, ResourceHeaderAllocation iButton, GUIButtonCallbackState Action)
{
	static bool clicked = false;
	if (Action == GUIButtonState_Press && clicked == false)
	{
		uint32_t ThreadIndex = 0;
		RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);

		Object* pObject = Object_Ref_Get_ObjectPointer(ClickedObject, false, false, ThreadIndex);
		ElementGraphics* pElement = Object_Ref_Get_ElementPointer(ClickedElement, false, false, ThreadIndex);

		if (strcmp(pElement->Header.Name, "Icon:Button:Save") == 0)
		{
			Object_Ref_Write_TEIF((const UTF8*)"BIN.teif", 0);
		}
		if (strcmp(pElement->Header.Name, "Icon:Button:Clear") == 0)
		{
			ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
			ChemistryEffectSimplified* pEffect = NULL;
			Graphics_Effects_Ref_Get_GraphicsEffect(pElement, ChemistryEffects_Simplified, &pEffect);
			GPU_Particle* Particles = NULL;
			uint64_t ParticlesSize = NULL;
			Chemistry_Ref_ReadParticles_Simplified(pGraphicsWindow, pElement, pEffect, &ParticlesSize, &Particles, ThreadIndex);

			//free(pEffect->Particles);

			pEffect->ParticlesSize = 0;
			pEffect->Particles = NULL;

			Object_Ref_ReCreate_Element(iMolecularSimulation, ThreadIndex);
			Object_Ref_End_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
		}


		Object_Ref_End_ElementPointer(ClickedElement, false, false, ThreadIndex);
		Object_Ref_End_ObjectPointer(ClickedObject, false, false, ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);

		clicked = true;
	}
	if (Action == GUIButtonState_Release)
	{
		clicked = false;
	}

}

void AtomSizerClick_Callback(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedObject, ResourceHeaderAllocation iButton, GUIButtonCallbackState Action)
{
	static bool clicked = false;
	if (Action == GUIButtonState_Press && clicked == false)
	{
		uint32_t ThreadIndex = 0;
		RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);

		uint32_t Element = 1;
		{
			Object* pObject = Object_Ref_Get_ObjectPointer(ClickedObject, false, false, ThreadIndex);
			Object* pParentObject = Object_Ref_Get_ObjectPointer(pObject->Header.iParent, false, false, ThreadIndex);
			ResourceHeaderAllocation iResourceHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(pParentObject->Header.iChildren[0], GraphicsHeader_Position, ThreadIndex);
			ResourceHeader* pResourceHeader = Object_Ref_Get_ResourceHeaderPointer(iResourceHeader, false, false, ThreadIndex);
			ElementGraphics* pElement = Object_Ref_Get_ElementPointer(pResourceHeader->Header.iElements[0], false, false, ThreadIndex);
			GraphicsEffectText* pEffect = NULL;
			Graphics_Effects_Ref_Get_GraphicsEffect(pElement, GUIEffect_Text, &pEffect);

			Element = atoi(pEffect->UTF8_Text);

			Object_Ref_End_ElementPointer(pResourceHeader->Header.iElements[0], false, false, ThreadIndex);
			Object_Ref_End_ResourceHeaderPointer(iResourceHeader, false, false, ThreadIndex);
			Object_Ref_End_ObjectPointer(pObject->Header.iParent, false, false, ThreadIndex);
			Object_Ref_End_ObjectPointer(ClickedObject, false, false, ThreadIndex);
		}



		ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
		ChemistryEffectSimplified* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElement, ChemistryEffects_Simplified, &pEffect);
		GPU_Particle* Particles = NULL;
		uint64_t ParticlesSize = NULL;
		Chemistry_Ref_ReadParticles_Simplified(pGraphicsWindow, pElement, pEffect, &ParticlesSize, &Particles, ThreadIndex);

		//free(pEffect->Particles);

		pEffect->ParticlesSize = ParticlesSize;
		pEffect->Particles = calloc(pEffect->ParticlesSize + 1 + Element, sizeof(*pEffect->Particles));
		memcpy(pEffect->Particles, Particles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));

		vec3 Position;
		glm_vec3_zero(Position);

		int32_t flip = -1;
		if (pGraphicsWindow->pWindow->STATE_KEY_G == KeyPress)
		{
			flip = 1;
		}
		bool paired = false;
		if (pGraphicsWindow->pWindow->STATE_KEY_H == KeyPress)
		{
			paired = true;
		}


		Add_ChemistryElement(Element, Position, pEffect->Particles, &pEffect->ParticlesSize, flip, paired);


		Object_Ref_ReCreate_Element(iMolecularSimulation, ThreadIndex);
		Object_Ref_End_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);

		clicked = true;
	}
	if (Action == GUIButtonState_Release)
	{
		clicked = false;
	}
}

void IconClick_Callback(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedObject, ResourceHeaderAllocation iButton, GUIButtonCallbackState Action)
{
	static float offset = 0.0f;
	static int CurrentLevel = 0;
	//make only 1 selection window and goup;
	static bool clicked = false;
	if (Action == GUIButtonState_Press && clicked == false)
	{
		uint32_t ThreadIndex = 0;
		RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);

		Object* pObject = Object_Ref_Get_ObjectPointer(ClickedObject, false, false, ThreadIndex);
		ElementGraphics* pElement = Object_Ref_Get_ElementPointer(ClickedElement, false, false, ThreadIndex);

		{
			//Object* pObjectParent = Object_Ref_Get_ObjectPointer(pObject->Header.iParent, false, false, ThreadIndex);

			ResourceHeaderAllocation iPositionHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(ClickedObject, GraphicsHeader_Position, ThreadIndex);
			RHeaderPosition* pPositionHeader = Object_Ref_Get_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);
	
			//ResourceHeaderAllocation iPositionHeaderSelect = Object_Ref_Scan_ObjectResourceHeadersSingle(pObjectParent->Header.iChildren[0], GraphicsHeader_Position, ThreadIndex);
			
			ElementGraphics* pElementSelect = Object_Ref_Get_ElementPointer(iSelectionBox, false, false, ThreadIndex);
			RHeaderPosition* pPositionHeaderSelect = Object_Ref_Get_ResourceHeaderPointer(pElementSelect->Header.iResourceHeaders[0], false, false, ThreadIndex);
			

			pPositionHeaderSelect->Matrix[3][0] = pPositionHeader->Matrix[3][0];
			pPositionHeaderSelect->Matrix[3][1] = pPositionHeader->Matrix[3][1];

			Object_Ref_End_ResourceHeaderPointer(pElementSelect->Header.iResourceHeaders[0], false, false, ThreadIndex);
			Object_Ref_End_ElementPointer(iSelectionBox, false, false, ThreadIndex);
			Object_Ref_End_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);
			//Object_Ref_End_ObjectPointer(pObject->Header.iParent, false, false, ThreadIndex);
		}

		for (size_t i = 0; i < PrefabIconsSize; i++)
		{
			if (strcmp(pElement->Header.Name, PrefabIcons[i].Name) == 0)
			{			
				ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
				ChemistryEffectSimplified* pEffect = NULL;
				Graphics_Effects_Ref_Get_GraphicsEffect(pElement, ChemistryEffects_Simplified, &pEffect);
				GPU_Particle* Particles = NULL;
				uint64_t ParticlesSize = NULL;
				Chemistry_Ref_ReadParticles_Simplified(pGraphicsWindow, pElement, pEffect, &ParticlesSize, &Particles, ThreadIndex);

				//free(pEffect->Particles);

				pEffect->ParticlesSize = ParticlesSize;
				pEffect->Particles = calloc(pEffect->ParticlesSize + 1, sizeof(*pEffect->Particles));
				memcpy(pEffect->Particles, Particles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));


				//Add_ChemistryElement(ChemistryElementType_Titanium, Position, Info.Particles, &it);


				pEffect->Particles[pEffect->ParticlesSize].Position[0] = 0.01f;
				pEffect->Particles[pEffect->ParticlesSize].Position[1] = 0.01f;
				pEffect->Particles[pEffect->ParticlesSize].Position[2] = 0.01f;
				pEffect->Particles[pEffect->ParticlesSize].Position[3] = 1.0f;
				pEffect->Particles[pEffect->ParticlesSize].PositionVelocity[0] = 0.0f;
				pEffect->Particles[pEffect->ParticlesSize].PositionVelocity[1] = 0.0f;
				pEffect->Particles[pEffect->ParticlesSize].PositionVelocity[2] = 0.0f;
				pEffect->Particles[pEffect->ParticlesSize].PositionVelocity[3] = -1.0f;
				pEffect->Particles[pEffect->ParticlesSize].Magnitude[0] = 0.0f;
				pEffect->Particles[pEffect->ParticlesSize].Magnitude[1] = 0.0f;
				pEffect->Particles[pEffect->ParticlesSize].Magnitude[2] = 1.0; //(((int)i % 2) * 2) - 1
				pEffect->Particles[pEffect->ParticlesSize].Magnitude[3] = 1.0f;

				pEffect->Particles[pEffect->ParticlesSize].Acceleration[3] = 1.0f;
				pEffect->ParticlesSize++;


				Object_Ref_ReCreate_Element(iMolecularSimulation, ThreadIndex);
				Object_Ref_End_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);		
			}
		}
	
		for (size_t i = 0; i < CategoryIconsSize; i++)
		{
			if (strcmp(pElement->Header.Name, CategoryIcons[i].Name) == 0)
			{
				Object* pObjectParent = Object_Ref_Get_ObjectPointer(pObject->Header.iParent, false, false, ThreadIndex);

				ResourceHeaderAllocation iPositionHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(pObjectParent->Header.iParent, GraphicsHeader_Position, ThreadIndex);
				RHeaderPosition* pPositionHeader = Object_Ref_Get_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);

				pPositionHeader->Matrix[3][1] = CategoryIcons[i].Offset;
				CurrentLevel = i;

				Object_Ref_End_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);
				Object_Ref_End_ObjectPointer(pObject->Header.iParent, false, false, ThreadIndex);
			}
		}
		if (strcmp(pElement->Header.Name, "Icon:Button:GoUp") == 0)
		{
			Object* pObjectParent = Object_Ref_Get_ObjectPointer(pObject->Header.iParent, false, false, ThreadIndex);

			ResourceHeaderAllocation iPositionHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(pObjectParent->Header.iParent, GraphicsHeader_Position, ThreadIndex);
			RHeaderPosition* pPositionHeader = Object_Ref_Get_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);

			CurrentLevel = CategoryIcons[CurrentLevel].ReverseIndex;
			pPositionHeader->Matrix[3][1] = CategoryIcons[CurrentLevel].Offset;

			Object_Ref_End_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);
			Object_Ref_End_ObjectPointer(pObject->Header.iParent, false, false, ThreadIndex);
		}
			
		{
			ResourceHeaderAllocation iPositionHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(pObject->Header.iParent, GraphicsHeader_Position, ThreadIndex);
			RHeaderPosition* pPositionHeader = Object_Ref_Get_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);
			offset = ((((EngineRes.pUtils->MousePos_Callback_state.X_Position / (float)pGraphicsWindow->CurrentExtentWidth) - 0.5f) * 2) * 0.5f) - pPositionHeader->Matrix[3][0];
			Object_Ref_End_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);
		}

		Object_Ref_End_ElementPointer(ClickedElement, false, false, ThreadIndex);
		Object_Ref_End_ObjectPointer(ClickedObject, false, false, ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);

		clicked = true;
	}
	if (Action == GUIButtonState_Release)
	{
		clicked = false;
	}


	if (Action == GUIButtonState_Press || Action == GUIButtonState_Repeat)
	{
		uint32_t ThreadIndex = 0;
		RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);
		Object* pObject = Object_Ref_Get_ObjectPointer(ClickedObject, false, false, ThreadIndex);
		

		ResourceHeaderAllocation iPositionHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(pObject->Header.iParent, GraphicsHeader_Position, ThreadIndex);
		RHeaderPosition* pPositionHeader = Object_Ref_Get_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);

		pPositionHeader->Matrix[3][0] = (((((EngineRes.pUtils->MousePos_Callback_state.X_Position / (float)pGraphicsWindow->CurrentExtentWidth) - 0.5f) * 2) * 0.5f)) - offset;

		Object_Ref_End_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);
		Object_Ref_End_ObjectPointer(ClickedObject, false, false, ThreadIndex);
	}
}

void DropdownClick_Callback(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedObject, ResourceHeaderAllocation iButton, GUIButtonCallbackState Action)
{

}

TEXRESULT ChemistryClick_Callback()
{
	static vec2 clickpos = { 0.0f, 0.0f };

	uint32_t ThreadIndex = 0;
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);

	static bool clicked = false;
	if (pGraphicsWindow->pWindow->STATE_MOUSE_BUTTON_1 == KeyPress && clicked == false)
	{
		clickpos[0] = ((((EngineRes.pUtils->MousePos_Callback_state.X_Position / (float)pGraphicsWindow->CurrentExtentWidth) - 0.5f)) * 2);
		clickpos[1] = ((((EngineRes.pUtils->MousePos_Callback_state.Y_Position / (float)pGraphicsWindow->CurrentExtentHeight) - 0.5f)) * 2);

		clicked = true;
	}
	if (pGraphicsWindow->pWindow->STATE_MOUSE_BUTTON_1 == KeyRelease)
	{
		vec2 endclickpos = { 0.0f, 0.0f };
		endclickpos[0] = ((((EngineRes.pUtils->MousePos_Callback_state.X_Position / (float)pGraphicsWindow->CurrentExtentWidth) - 0.5f)) * 2);
		endclickpos[1] = ((((EngineRes.pUtils->MousePos_Callback_state.Y_Position / (float)pGraphicsWindow->CurrentExtentHeight) - 0.5f)) * 2);

		
		ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
		ChemistryEffectSimplified* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElement, ChemistryEffects_Simplified, &pEffect);

		RHeaderCamera* pCameraHeader = Object_Ref_Get_ResourceHeaderPointer(iCameraHeader, false, false, ThreadIndex);
		mat4 VP;
		mat4 CameraPositionMatrix;
		glm_mat4_identity(CameraPositionMatrix);
		Graphics_Ref_Calculate_TotalMatrix(&CameraPositionMatrix, pCameraHeader->Header.iObjects[0], ThreadIndex);
		//multiple position headers is undefined
		mat4 vmat;
		mat4 pmat;
		glm_mat4_identity(vmat);
		glm_mat4_identity(pmat);
		glm_mat4_inv_precise_sse2(CameraPositionMatrix, vmat);
		if (pCameraHeader != NULL) {
			switch (pCameraHeader->Type) {
			case CameraType_Perspective:
				glm_perspective((float)pCameraHeader->CameraU.Perspective.y_fov, (float)pCameraHeader->CameraU.Perspective.AspectRatio,
					(float)pCameraHeader->CameraU.Perspective.z_near, (float)pCameraHeader->CameraU.Perspective.z_far, pmat);
				break;
			case CameraType_Orthographic:
				glm_ortho(-(float)pCameraHeader->CameraU.Orthographic.x_mag, (float)pCameraHeader->CameraU.Orthographic.x_mag,
					-(float)pCameraHeader->CameraU.Orthographic.y_mag, (float)pCameraHeader->CameraU.Orthographic.y_mag,
					(float)pCameraHeader->CameraU.Orthographic.z_near, (float)pCameraHeader->CameraU.Orthographic.z_far, pmat);
				break;
			}
		}
		else {
			glm_mat4_identity(pmat);
		}
		glm_mul_sse2(pmat, vmat, VP);

		Object_Ref_End_ResourceHeaderPointer(iCameraHeader, false, false, ThreadIndex);

		GPU_Particle* Particles = NULL;
		uint64_t ParticlesSize = NULL;
		Chemistry_Ref_ReadParticles_Simplified(pGraphicsWindow, pElement, pEffect, &ParticlesSize, &Particles, ThreadIndex);

		pEffect->ParticlesSize = ParticlesSize;
		memcpy(pEffect->Particles, Particles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));

		bool aaa = true;
		for (size_t i = 0; i < pEffect->ParticlesSize; i++)
		{
			vec4 product;
			glm_vec3_copy(pEffect->Particles[i].Position, product);
			product[3] = 1.0f;
			glm_mat4_mulv(VP, product, product);

			product[0] /= product[3];
			product[1] /= product[3];
			product[2] /= product[3];

			if (glm_vec2_distance(clickpos, endclickpos) < 0.015f)
			{
			}
			else
			{
				if (product[0] > (clickpos[0]) &&
					product[0] < (endclickpos[0]) &&
					product[1] > (clickpos[1]) &&
					product[1] < (endclickpos[1])) {
					aaa = false;
				}
			}
		}

		for (size_t i = 0; i < pEffect->ParticlesSize; i++)
		{
			vec4 product;
			glm_vec3_copy(pEffect->Particles[i].Position, product);
			product[3] = 1.0f;
			glm_mat4_mulv(VP, product, product);

			product[0] /= product[3];
			product[1] /= product[3];
			product[2] /= product[3];

			if (pEffect->Particles[i].Acceleration[3] == 1.0f && aaa == true)
			{
				//transform coordinates into screen space, then add the mousepos, then transform back to model space.
				mat4 INVVP; //inverse matrix from screen space to model space
				glm_mat4_inv_precise_sse2(VP, INVVP);

				vec4 finalpos; //screen space particle position;
				glm_vec4_copy(product, finalpos);

				vec2 mousetransform;
				mousetransform[0] = (endclickpos[0] - clickpos[0]);
				mousetransform[1] = (endclickpos[1] - clickpos[1]); //(endclickpos[1] - clickpos[1])

				glm_vec2_add(finalpos, mousetransform, finalpos);

				finalpos[0] *= finalpos[3];
				finalpos[1] *= finalpos[3];
				finalpos[2] *= finalpos[3];

				glm_mat4_mulv(INVVP, finalpos, finalpos); //back to model space

				glm_vec3_copy(finalpos, pEffect->Particles[i].Position);
			}
			
			if (pGraphicsWindow->pWindow->STATE_KEY_LEFT_SHIFT != KeyPress)
			{
				pEffect->Particles[i].Acceleration[3] = 0.0f;
			}
			if (glm_vec2_distance(clickpos, endclickpos) < 0.015f)
			{
				if (glm_vec2_distance(product, clickpos) < 0.015f)
				{
					pEffect->Particles[i].Acceleration[3] = !((int)pEffect->Particles[i].Acceleration[3]);
				}
			}
			else
			{
				if (product[0] > (clickpos[0]) &&
					product[0] < (endclickpos[0]) &&
					product[1] > (clickpos[1]) &&
					product[1] < (endclickpos[1])) {
					pEffect->Particles[i].Acceleration[3] = !((int)pEffect->Particles[i].Acceleration[3]);
				}
			}
		}


		Object_Ref_ReCreate_Element(iMolecularSimulation, ThreadIndex);
		Object_Ref_End_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);


		clicked = false;
	}

	Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);

	return (Success);
}

TEXRESULT ChemistryKey_Callback()
{
	uint32_t ThreadIndex = 0;
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);

	ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
	ChemistryEffectSimplified* pEffect = NULL;
	Graphics_Effects_Ref_Get_GraphicsEffect(pElement, ChemistryEffects_Simplified, &pEffect);

	GPU_Particle* Particles = NULL;
	uint64_t ParticlesSize = NULL;
	Chemistry_Ref_ReadParticles_Simplified(pGraphicsWindow, pElement, pEffect, &ParticlesSize, &Particles, ThreadIndex);

	pEffect->ParticlesSize = ParticlesSize;
	memcpy(pEffect->Particles, Particles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));


	if (pGraphicsWindow->pWindow->STATE_KEY_DELETE == KeyPress)
	{
		void* oldparticles = pEffect->Particles;
		pEffect->Particles = calloc(pEffect->ParticlesSize, sizeof(*pEffect->Particles));
		memcpy(pEffect->Particles, oldparticles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));

		size_t aa = pEffect->ParticlesSize;
		for (size_t i = 0; i < aa; i++)
		{
			if (pEffect->Particles[i].Acceleration[3] == 1.0f)
			{
				RemoveMember_Array(&pEffect->Particles, pEffect->ParticlesSize, i, sizeof(*pEffect->Particles), 1);
				pEffect->ParticlesSize -= 1;
				i--;
				aa--;
			}
		}
	}
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_CONTROL == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_CONTROL == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_C)
	{
		GPU_Particle* oldparticles = pEffect->Particles;
		size_t oldsize = pEffect->ParticlesSize;
		pEffect->Particles = calloc(pEffect->ParticlesSize, sizeof(*pEffect->Particles));
		memcpy(pEffect->Particles, oldparticles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));
		for (size_t i = 0; i < oldsize; i++)
		{
			if (pEffect->Particles[i].Acceleration[3] == 1.0f)
			{
				GPU_Particle* pParticle = &oldparticles[i];

				Resize_Array(&pEffect->Particles, pEffect->ParticlesSize, pEffect->ParticlesSize + 1, sizeof(*pEffect->Particles));
				memcpy(&pEffect->Particles[pEffect->ParticlesSize], pParticle, sizeof(*pEffect->Particles));
				pEffect->ParticlesSize += 1;

				pEffect->Particles[i].Acceleration[3] = 0.0f;
			}
		}
	}
	//mayby add cut and stuff too 

	size_t aa = pEffect->ParticlesSize;
	for (size_t i = 0; i < aa; i++)
	{
		if (pEffect->Particles[i].Acceleration[3] == 1.0f)
		{
			//manipulation
			float speed = 0.4f;
			if (pGraphicsWindow->pWindow->STATE_KEY_LEFT_SHIFT == KeyPress)
				speed = 0.01f;
			if (pGraphicsWindow->pWindow->STATE_KEY_RIGHT == KeyPress)
				pEffect->Particles[i].Position[0] += speed;
			if (pGraphicsWindow->pWindow->STATE_KEY_LEFT == KeyPress)
				pEffect->Particles[i].Position[0] -= speed;
			if (pGraphicsWindow->pWindow->STATE_KEY_UP == KeyPress)
				pEffect->Particles[i].Position[1] += speed;
			if (pGraphicsWindow->pWindow->STATE_KEY_DOWN == KeyPress)
				pEffect->Particles[i].Position[1] -= speed;
			if (pGraphicsWindow->pWindow->STATE_KEY_PAGE_UP == KeyPress)
				pEffect->Particles[i].Position[2] += speed;
			if (pGraphicsWindow->pWindow->STATE_KEY_PAGE_DOWN == KeyPress)
				pEffect->Particles[i].Position[2] -= speed;
		}
	}

	Object_Ref_ReCreate_Element(iMolecularSimulation, ThreadIndex);
	Object_Ref_End_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);



	Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);
	
	return (Success);
}


void ButtonClick_Callback(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedObject, ResourceHeaderAllocation iButton, GUIButtonCallbackState Action)
{
	if (Action == GUIButtonState_Press)
	{
		CurClickedElement = ClickedElement;
		CurClickedResourceHeader = ClickedResourceHeader;
		CurClickedObject = ClickedObject;
	}
}

//////////////////////////////////////////////////////////////////////////
//Macros
//////////////////////////////////////////////////////////////////////////

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

void Update_Cursor(RHeaderGraphicsWindow* pGraphicsWindow, GraphicsEffectText* pEffect, GPU_GraphicsEffectText* pTargetElement, ElementGraphics* pElement) {
	uint32_t ThreadIndex = 0;
	ElementGraphics* pElementTextCursor = Object_Ref_Get_ElementPointer(iTextCursor, true, false, 0);
#ifndef NDEBUG
	if (pElementTextCursor == NULL) {
		Engine_Ref_ObjectError("Update_Cursor()", "pElementTextCursor", pElementTextCursor, "iTextCursor Invalid.");
		return;
	}
#endif
	GraphicsEffectGeneric2D* pEffect2D = NULL;
	Graphics_Effects_Ref_Get_GraphicsEffect(pElementTextCursor, GraphicsEffect_Generic2D, &pEffect2D);

	RHeaderMaterial* pMaterial = Object_Ref_Get_ResourceHeaderPointer(pElementTextCursor->iMaterial, false, false, ThreadIndex);
	RHeaderTexture* pTexture = Object_Ref_Get_ResourceHeaderPointer(pMaterial->BaseColourTexture.iTexture, false, false, ThreadIndex);
	RHeaderImageSource* pImageSource = Object_Ref_Get_ResourceHeaderPointer(pTexture->iImageSource, false, false, ThreadIndex);
	
#ifndef NDEBUG
	if (pMaterial == NULL) {
		Engine_Ref_ObjectError("Update_Cursor()", "pElementTextCursor", pElementTextCursor, "ElementGraphics.iMaterial Invalid.");
		return;
	}
	if (pTexture == NULL) {
		Engine_Ref_ObjectError("Update_Cursor()", "pMaterial", pMaterial, "RHeaderMaterial.BaseColourTexture.iTexture Invalid.");
		return;
	}
	if (pImageSource == NULL) {
		Engine_Ref_ObjectError("Update_Cursor()", "pTexture", pTexture, "RHeaderTexture.iImageSource Invalid.");
		return;
	}
	if (pImageSource->ImageData == NULL) {
		Engine_Ref_ObjectError("Update_Cursor()", "pImageSource", pImageSource, "RHeaderImageSource.ImageData Invalid.");
		return;
	}
#endif 
	RHeaderPosition* pPositionHeader1 = Object_Ref_Get_ResourceHeaderPointer(pElementTextCursor->Header.iResourceHeaders[0], false, false, ThreadIndex);
	mat4 Position0;
	glm_mat4_identity(Position0);
	Graphics_Ref_Calculate_TotalMatrix(&Position0, pPositionHeader1->Header.iObjects[0], ThreadIndex);


	RHeaderPosition* pPositionHeader2 = Object_Ref_Get_ResourceHeaderPointer(pElement->Header.iResourceHeaders[0], false, false, ThreadIndex);
	Object_Ref_End_ResourceHeaderPointer(pElement->Header.iResourceHeaders[0], false, false, ThreadIndex);
	mat4 Position1;
	glm_mat4_identity(Position1);
	Graphics_Ref_Calculate_TotalMatrix(&Position1, pPositionHeader2->Header.iObjects[0], ThreadIndex);

	float scalefactor = ((float)((pEffect->FontSize * GUIRes.pUtils->Config.DPI) / 72) / (float)(pImageSource->ImageData->Height) / 2);
	pEffect2D->Size[0] = (((float)(pImageSource->ImageData->Width * scalefactor) / 2) / (float)pGraphicsWindow->CurrentExtentWidth);
	pEffect2D->Size[1] = (((float)(pImageSource->ImageData->Height * scalefactor) / 2) / (float)pGraphicsWindow->CurrentExtentHeight);
	

	pPositionHeader1->Matrix[3][0] = (Position1[3][0] - pEffect->Size[0]) + ((pTargetElement->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth);
	pPositionHeader1->Matrix[3][1] = (Position1[3][1] - pEffect->Size[1]) - pEffect2D->Size[1] + ((pTargetElement->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight);
	//pPositionHeader1->Matrix[3][2] = (Position1[3][2]);

	Object_Ref_End_ResourceHeaderPointer(pElementTextCursor->Header.iResourceHeaders[0], false, false, ThreadIndex);



	Object_Ref_End_ResourceHeaderPointer(pElementTextCursor->iMaterial, false, false, ThreadIndex);
	Object_Ref_End_ResourceHeaderPointer(pMaterial->BaseColourTexture.iTexture, false, false, ThreadIndex);
	Object_Ref_End_ResourceHeaderPointer(pTexture->iImageSource, false, false, ThreadIndex);

	glm_vec2_copy(pEffect2D->Size, pEffect2D->BoundingBoxSize);
	Object_Ref_End_ElementPointer(iTextCursor, true, false, ThreadIndex);
}

void InsertCodepoint(RHeaderGraphicsWindow* pGraphicsWindow, UTF32 codepoint) {
	ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
	if (pElementGraphics == NULL) {
		Engine_Ref_ObjectError("InsertCodepoint()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
		return;
	}
#endif
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
	//free(pEffect->UTF8_Text);
	UTF32_To_UTF8(UTF32_Text, &pEffect->UTF8_Text);
	Object_Ref_ReCreate_Element(CurClickedElement, 0);
	Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
	Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator], pElementGraphics);
}

void RemoveCodepoint(RHeaderGraphicsWindow* pGraphicsWindow) {
	ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
	if (pElementGraphics == NULL) {
		Engine_Ref_ObjectError("RemoveCodepoint()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
		return;
	}
#endif
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
	//free(pEffect->UTF8_Text);
	UTF32_To_UTF8(UTF32_Text, &pEffect->UTF8_Text);
	Object_Ref_ReCreate_Element(CurClickedElement, 0);
	Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
	Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator], pElementGraphics);
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

TEXRESULT Character_Callback() {
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
#ifndef NDEBUG
	if (pGraphicsWindow == NULL) {
		Engine_Ref_ObjectError("Character_Callback()", "pGraphicsWindow", pGraphicsWindow, "iGraphicsWindow Invalid.");
		return (Failure);
	}
#endif
	if (EngineRes.pUtils->Character_Callback_state.CodePoint == 'm')
	{
		Engine_Ref_Set_WindowFullScreen(pGraphicsWindow->pWindow, !pGraphicsWindow->pWindow->FullScreen);
		return (Success);
	}
	//control keys
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_CONTROL == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_CONTROL == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_V == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Character_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
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
		//free(pEffect->UTF8_Text);
		UTF32_To_UTF8(UTF32_Text, &pEffect->UTF8_Text);
		Object_Ref_ReCreate_Element(CurClickedElement, 0);
		Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator], pElementGraphics);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_CONTROL == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_CONTROL == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_X == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Character_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
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
		//free(pEffect->UTF8_Text);
		UTF32_To_UTF8(UTF32_Text, &pEffect->UTF8_Text);
		Object_Ref_ReCreate_Element(CurClickedElement, 0);
		Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator], pElementGraphics);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_CONTROL == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_CONTROL == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_C == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Character_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
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
		//free(pEffect->UTF8_Text);
		UTF32_To_UTF8(UTF32_Text, &pEffect->UTF8_Text);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_CONTROL == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_CONTROL == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_Z == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Character_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
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
			//free(pEffect->UTF8_Text);
			pEffect->UTF8_Text = CopyData(PreviousTexts[PreviousTextsSize - PreviousTextsIndex].Text);
			CurClickedElementTextIterator = PreviousTexts[PreviousTextsSize - PreviousTextsIndex].CursorIndex;
		}
		Object_Ref_ReCreate_Element(CurClickedElement, 0);
		Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator], pElementGraphics);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_CONTROL == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_CONTROL == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_Y == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Character_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
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
			//free(pEffect->UTF8_Text);
			pEffect->UTF8_Text = CopyData(PreviousTexts[PreviousTextsSize - PreviousTextsIndex].Text);
			CurClickedElementTextIterator = PreviousTexts[PreviousTextsSize - PreviousTextsIndex].CursorIndex;
		}
		Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator], pElementGraphics);
		Object_Ref_ReCreate_Element(CurClickedElement, 0);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	//typing
	if ((pGraphicsWindow->pWindow->STATE_KEY_LEFT_SHIFT == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_SHIFT == KeyPress) && pGraphicsWindow->pWindow->STATE_KEY_ENTER == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		InsertCodepoint(pGraphicsWindow, 0x0D);
		InsertCodepoint(pGraphicsWindow, 0x0A);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_TAB == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		//4 indents
		InsertCodepoint(pGraphicsWindow, 0x09);
		//InsertCodepoint(pGraphicsWindow, 0x20);
		//InsertCodepoint(pGraphicsWindow, 0x20);
		//InsertCodepoint(pGraphicsWindow, 0x20);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	if (EngineRes.pUtils->Character_Callback_state.CodePoint == 0x08 && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		RemoveCodepoint(pGraphicsWindow);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	if (EngineRes.pUtils->Character_Callback_state.CodePoint >= 32 && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		InsertCodepoint(pGraphicsWindow, EngineRes.pUtils->Character_Callback_state.CodePoint);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
	return (Success);
}

TEXRESULT Click_Callback()
{
	uint32_t ThreadIndex = 0;
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
#ifndef NDEBUG
	if (pGraphicsWindow == NULL) {
		Engine_Ref_ObjectError("Click_Callback()", "pGraphicsWindow", pGraphicsWindow, "iGraphicsWindow Invalid.");
		return (Failure);
	}
#endif

	if (pGraphicsWindow->pWindow->STATE_MOUSE_BUTTON_1 == KeyPress && (pGraphicsWindow->pWindow->STATE_KEY_LEFT_SHIFT == KeyPress || pGraphicsWindow->pWindow->STATE_KEY_RIGHT_SHIFT == KeyPress) && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL) //get next closet character to the cursor
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Click_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
		RHeaderPosition* pPositionHeader1 = Object_Ref_Get_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);
		mat4 Position;
		glm_mat4_identity(Position);
		Graphics_Ref_Calculate_TotalMatrix(&Position, pPositionHeader1->Header.iObjects[0], ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		vec2 pa;
		glm_vec2_zero(pa);
		pa[0] = EngineRes.pUtils->MousePos_Callback_state.X_Position / pGraphicsWindow->CurrentExtentWidth;
		pa[1] = EngineRes.pUtils->MousePos_Callback_state.Y_Position / pGraphicsWindow->CurrentExtentHeight;
		float halffactor = (float)((pEffect->FontSize * GUIRes.pUtils->Config.DPI) / 72) / 4;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			vec2 pb;
			glm_vec2_zero(pb);

			pb[0] = ((Position[3][0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth));
			pb[1] = ((Position[3][1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY - halffactor) / (float)pGraphicsWindow->CurrentExtentHeight));
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
		Object_Ref_ReCreate_Element(CurClickedElement, 0);
		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest, pElementGraphics);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	if (pGraphicsWindow->pWindow->STATE_MOUSE_BUTTON_1 == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL) //get next closet character to the cursor
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Click_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
		RHeaderPosition* pPositionHeader1 = Object_Ref_Get_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);
		mat4 Position;
		glm_mat4_identity(Position);
		Graphics_Ref_Calculate_TotalMatrix(&Position, pPositionHeader1->Header.iObjects[0], ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		vec2 pa;
		glm_vec2_zero(pa);
		pa[0] = EngineRes.pUtils->MousePos_Callback_state.X_Position / pGraphicsWindow->CurrentExtentWidth;
		pa[1] = EngineRes.pUtils->MousePos_Callback_state.Y_Position / pGraphicsWindow->CurrentExtentHeight;
		float halffactor = (float)((pEffect->FontSize * GUIRes.pUtils->Config.DPI) / 72) / 4;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			vec2 pb;
			glm_vec2_zero(pb);
			
			pb[0] = ((Position[3][0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth));
			pb[1] = ((Position[3][1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY - halffactor) / (float)pGraphicsWindow->CurrentExtentHeight));
			float distance = glm_vec2_distance(pa, pb);
			if (distance < max)
			{
				max = distance;
				CurClickedElementTextIterator = i;
				pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			}
		}
		SelectedTextStartIndex1 = CurClickedElementTextIterator;


		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest, pElementGraphics);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, ThreadIndex);
		selecting = true;
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
	return (Success);
}

TEXRESULT Key_Callback()
{
	uint32_t ThreadIndex = 0;
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
#ifndef NDEBUG
	if (pGraphicsWindow == NULL) {
		Engine_Ref_ObjectError("Key_Callback()", "pGraphicsWindow", pGraphicsWindow, "iGraphicsWindow Invalid.");
		return (Failure);
	}
#endif
	//navigation keys
	if (pGraphicsWindow->pWindow->STATE_KEY_RIGHT == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL) //get next closet character to the right
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Key_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
		RHeaderPosition* pPositionHeader1 = Object_Ref_Get_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);
		mat4 Position;
		glm_mat4_identity(Position);
		Graphics_Ref_Calculate_TotalMatrix(&Position, pPositionHeader1->Header.iObjects[0], ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		float halffactor = (float)((pEffect->FontSize * GUIRes.pUtils->Config.DPI) / 72) / 8;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			if (((Position[3][0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) > ((Position[3][0] - pEffect->Size[0]) + ((pGPU_oldEffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) &&
				((Position[3][0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) < max &&
				((Position[3][1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY - halffactor) / (float)pGraphicsWindow->CurrentExtentHeight)) <= ((Position[3][1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) &&
				((Position[3][1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY + halffactor) / (float)pGraphicsWindow->CurrentExtentHeight)) >= ((Position[3][1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)))
			{
				max = ((Position[3][0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth));
				CurClickedElementTextIterator = i;
				pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			}
		}
		if ((pGPU_EffectClosest == pGPU_oldEffectClosest) && CurClickedElementTextIterator < pEffect->GPU_GraphicsEffectInfosSize - 1)
		{
			CurClickedElementTextIterator++;
			pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		}
		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest, pElementGraphics);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_LEFT == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL) //get next closet character to the left
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Key_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
		RHeaderPosition* pPositionHeader1 = Object_Ref_Get_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);
		mat4 Position;
		glm_mat4_identity(Position);
		Graphics_Ref_Calculate_TotalMatrix(&Position, pPositionHeader1->Header.iObjects[0], ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		float halffactor = (float)((pEffect->FontSize * GUIRes.pUtils->Config.DPI) / 72) / 8;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			if (((Position[3][0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) < ((Position[3][0] - pEffect->Size[0]) + ((pGPU_oldEffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) &&
				((Position[3][0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) > -max &&
				((Position[3][1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY - halffactor) / (float)pGraphicsWindow->CurrentExtentHeight)) <= ((Position[3][1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) &&
				((Position[3][1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY + halffactor) / (float)pGraphicsWindow->CurrentExtentHeight)) >= ((Position[3][1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)))
			{
				max = ((Position[3][0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth));
				CurClickedElementTextIterator = i;
				pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			}
		}
		if ((pGPU_EffectClosest == pGPU_oldEffectClosest) && CurClickedElementTextIterator > 1)
		{
			CurClickedElementTextIterator--;
			pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		}
		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest, pElementGraphics);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_UP == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL) //get next closet character to the top
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Key_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
		RHeaderPosition* pPositionHeader1 = Object_Ref_Get_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);
		mat4 Position;
		glm_mat4_identity(Position);
		Graphics_Ref_Calculate_TotalMatrix(&Position, pPositionHeader1->Header.iObjects[0], ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		float halffactor = (float)((pEffect->FontSize * GUIRes.pUtils->Config.DPI) / 72) / 8;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			if (((Position[3][1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) < ((Position[3][1] - pEffect->Size[1]) + ((pGPU_oldEffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) &&
				((Position[3][1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) > -max &&
				((Position[3][0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX - halffactor) / (float)pGraphicsWindow->CurrentExtentWidth)) <= ((Position[3][0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) &&
				((Position[3][0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX + halffactor) / (float)pGraphicsWindow->CurrentExtentWidth)) >= ((Position[3][0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)))
			{
				max = ((Position[3][1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight));
				CurClickedElementTextIterator = i;
				pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			}
		}
		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest, pElementGraphics);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_DOWN == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL) //get next closet character to the bototm
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Key_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
		RHeaderPosition* pPositionHeader1 = Object_Ref_Get_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);
		mat4 Position;
		glm_mat4_identity(Position);
		Graphics_Ref_Calculate_TotalMatrix(&Position, pPositionHeader1->Header.iObjects[0], ThreadIndex);
		Object_Ref_End_ResourceHeaderPointer(pElementGraphics->Header.iResourceHeaders[0], false, false, ThreadIndex);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		float halffactor1 = (float)((pEffect->FontSize * GUIRes.pUtils->Config.DPI) / 72) / 8;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			if (((Position[3][1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) > ((Position[3][1] - pEffect->Size[1]) + ((pGPU_oldEffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) &&
				((Position[3][1] - pEffect->Size[1]) + ((pGPU_Effect->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight)) < max &&
				((Position[3][0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX - halffactor1) / (float)pGraphicsWindow->CurrentExtentWidth)) <= ((Position[3][0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)) &&
				((Position[3][0] - pEffect->Size[0]) + ((pGPU_Effect->AdvanceX + halffactor1) / (float)pGraphicsWindow->CurrentExtentWidth)) >= ((Position[3][0] - pEffect->Size[0]) + ((pGPU_EffectClosest->AdvanceX) / (float)pGraphicsWindow->CurrentExtentWidth)))
			{
				max = ((Position[3][1] - pEffect->Size[1]) + ((pGPU_EffectClosest->AdvanceY) / (float)pGraphicsWindow->CurrentExtentHeight));
				CurClickedElementTextIterator = i;
				pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
			}
		}
		Update_Cursor(pGraphicsWindow, pEffect, pGPU_EffectClosest, pElementGraphics);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, ThreadIndex);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_ESCAPE == KeyPress && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		CurClickedElement.Identifier = 0;
		CurClickedElement.Pointer = 0;

		ElementGraphics* pElementTextCursor = Object_Ref_Get_ElementPointer(iTextCursor, true, false, ThreadIndex);

		GraphicsEffectGeneric2D* pEffect2D = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementTextCursor, GraphicsEffect_Generic2D, &pEffect2D);

		RHeaderPosition* pPositionHeader1 = Object_Ref_Get_ResourceHeaderPointer(pElementTextCursor->Header.iResourceHeaders[0], false, false, ThreadIndex);
		pPositionHeader1->Matrix[3][0] = 0.0f;
		pPositionHeader1->Matrix[3][1] = 0.0f;
		pPositionHeader1->Matrix[3][2] = 0.0f;
		Object_Ref_End_ResourceHeaderPointer(pElementTextCursor->Header.iResourceHeaders[0], false, false, ThreadIndex);

		Object_Ref_End_ElementPointer(iTextCursor, true, false, ThreadIndex);
	}
	Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);
	return (Success);
}

TEXRESULT Scroll_Callback()
{
	uint32_t ThreadIndex = 0;
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
#ifndef NDEBUG
	if (pGraphicsWindow == NULL) {
		Engine_Ref_ObjectError("Scroll_Callback()", "pGraphicsWindow", pGraphicsWindow, "iGraphicsWindow Invalid.");
		return (Failure);
	}
#endif
	if (Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, 0);
#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Scroll_Callback()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);
		//pEffect->Position[1] += (EngineRes.pUtils->Scroll_Callback_state.Delta / (float)pGraphicsWindow->CurrentExtentHeight) * ScrollSpeed;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			pEffect->GPU_GraphicsEffectInfos[i].Position[1] += (EngineRes.pUtils->Scroll_Callback_state.Delta / (float)pGraphicsWindow->CurrentExtentHeight) * ScrollSpeed;
		}
		Update_Cursor(pGraphicsWindow, pEffect, &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator], pElementGraphics);
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, 0);
		Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
		return (Success);
	}
	Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, 0);
	return (Success);
}

//////////////////////////////////////////////////////////////////////////
//Main Function///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

TEXRESULT Update_Chat()
{		
	uint32_t ThreadIndex = 0;
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex);
#ifndef NDEBUG
	if (pGraphicsWindow == NULL) {
		Engine_Ref_ObjectError("Scroll_Callback()", "pGraphicsWindow", pGraphicsWindow, "iGraphicsWindow Invalid.");
		return (Failure);
	}
#endif
	/*
	if (pGraphicsWindow->pWindow->STATE_MOUSE_BUTTON_1 == KeyRelease)
	{
		selecting = false;
	}
	if (selecting == true && Object_Ref_Get_ElementAllocationData(CurClickedElement) != NULL)
	{
		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(CurClickedElement, true, false, ThreadIndex);

#ifndef NDEBUG
		if (pElementGraphics == NULL) {
			Engine_Ref_ObjectError("Update_Chat()", "pElementGraphics", pElementGraphics, "CurClickedElement Invalid.");
			return (Failure);
		}
#endif
		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		GPU_GraphicsEffectText* pGPU_oldEffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];
		GPU_GraphicsEffectText* pGPU_EffectClosest = &pEffect->GPU_GraphicsEffectInfos[CurClickedElementTextIterator];

		vec2 pa;
		glm_vec2_zero(pa);
		pa[0] = EngineRes.pUtils->MousePos_Callback_state.X_Position / pGraphicsWindow->CurrentExtentWidth;
		pa[1] = EngineRes.pUtils->MousePos_Callback_state.Y_Position / pGraphicsWindow->CurrentExtentHeight;
		float halffactor = (float)((pEffect->FontSize * GUIRes.pUtils->Config.DPI) / 72) / 4;
		float max = FLT_MAX;
		for (size_t i = 0; i < pEffect->GPU_GraphicsEffectInfosSize; i++)
		{
			GPU_GraphicsEffectText* pGPU_Effect = &pEffect->GPU_GraphicsEffectInfos[i];
			vec2 pb;
			glm_vec2_zero(pb);		
			/*
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
		Object_Ref_End_ElementPointer(CurClickedElement, true, false, ThreadIndex);
	}
	*/
	static int cpufps = 0;
	/**/
	if (((double)clock() / (double)CLOCKS_PER_SEC) - lasttime > 1) 
	{	
		double FPS = ((double)pGraphicsWindow->FramesDone);
		double CPUFPS = ((double)cpufps);
		double MSPF = 1000.0f / ((double)pGraphicsWindow->FramesDone);
		pGraphicsWindow->FramesDone = 0;
		cpufps = 0;

		lasttime = ((double)clock() / (double)CLOCKS_PER_SEC);

		ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iFPS_DisplayText, true, false, ThreadIndex);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElement, GUIEffect_Text, &pEffect);

		//free(pEffect->UTF8_Text);
		char buffer[128 + 19];
		snprintf(&buffer, 128 + 19, "FPS: %f   CPUFPS: %f", ((float)FPS), ((float)CPUFPS));

		pEffect->UTF8_Text = CopyData(buffer); //this is why its error in debug mode.
		Object_Ref_ReCreate_Element(iFPS_DisplayText, ThreadIndex);
		Object_Ref_End_ElementPointer(iFPS_DisplayText, true, false, ThreadIndex);
	}
	cpufps++;

	if (pGraphicsWindow->pWindow->STATE_KEY_R == KeyPress)
	{
		float Multiplier = 0.0f;
		{
			ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
			ChemistryEffectSimplified* pEffect = NULL;
			Graphics_Effects_Ref_Get_GraphicsEffect(pElement, ChemistryEffects_Simplified, &pEffect);
			pEffect->Multiplier += 0.05f;
			Multiplier = pEffect->Multiplier;
			Object_Ref_End_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
		}
		{
			ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iMultiplierText, true, false, ThreadIndex);
			GraphicsEffectText* pEffect = NULL;
			Graphics_Effects_Ref_Get_GraphicsEffect(pElement, GUIEffect_Text, &pEffect);
			//free(pEffect->UTF8_Text);
			char buffer[128 + 19];
			snprintf(&buffer, 128 + 19, "Multiplier: %f", Multiplier);
			pEffect->UTF8_Text = CopyData(buffer); //this is why its error in debug mode.
			Object_Ref_ReCreate_Element(iMultiplierText, ThreadIndex);
			Object_Ref_End_ElementPointer(iMultiplierText, true, false, ThreadIndex);
		}
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_F == KeyPress)
	{
		float Multiplier = 0.0f;
		{
			ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
			ChemistryEffectSimplified* pEffect = NULL;
			Graphics_Effects_Ref_Get_GraphicsEffect(pElement, ChemistryEffects_Simplified, &pEffect);
			pEffect->Multiplier -= 0.05f;
			if (pEffect->Multiplier < 0.0f)
				pEffect->Multiplier = 0.0f;
			Multiplier = pEffect->Multiplier;
			Object_Ref_End_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
		}
		{
			ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iMultiplierText, true, false, ThreadIndex);
			GraphicsEffectText* pEffect = NULL;
			Graphics_Effects_Ref_Get_GraphicsEffect(pElement, GUIEffect_Text, &pEffect);
			//free(pEffect->UTF8_Text);
			char buffer[128 + 19];
			snprintf(&buffer, 128 + 19, "Multiplier: %f", Multiplier);
			pEffect->UTF8_Text = CopyData(buffer); //this is why its error in debug mode.
			Object_Ref_ReCreate_Element(iMultiplierText, ThreadIndex);
			Object_Ref_End_ElementPointer(iMultiplierText, true, false, ThreadIndex);
		}
	}

	if (pGraphicsWindow->pWindow->STATE_KEY_P == KeyPress)
	{
		float Multiplier = 0.0f;
		{
			ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
			ChemistryEffectSimplified* pEffect = NULL;
			Graphics_Effects_Ref_Get_GraphicsEffect(pElement, ChemistryEffects_Simplified, &pEffect);
			pEffect->Multiplier = 0.0f;
			if (pEffect->Multiplier < 0.0f)
				pEffect->Multiplier = 0.0f;
			Multiplier = pEffect->Multiplier;
			Object_Ref_End_ElementPointer(iMolecularSimulation, true, false, ThreadIndex);
		}
		{
			ElementGraphics* pElement = Object_Ref_Get_ElementPointer(iMultiplierText, true, false, ThreadIndex);
			GraphicsEffectText* pEffect = NULL;
			Graphics_Effects_Ref_Get_GraphicsEffect(pElement, GUIEffect_Text, &pEffect);
			//free(pEffect->UTF8_Text);
			char buffer[128 + 19];
			snprintf(&buffer, 128 + 19, "Multiplier: %f", Multiplier);
			pEffect->UTF8_Text = CopyData(buffer); //this is why its error in debug mode.
			Object_Ref_ReCreate_Element(iMultiplierText, ThreadIndex);
			Object_Ref_End_ElementPointer(iMultiplierText, true, false, ThreadIndex);
		}
	}

	/*
	if (((double)clock() / (double)CLOCKS_PER_SEC) - lasttime > 1.0)
	{
		double FPS = ((double)pGraphicsWindow->FramesDone);
		double MSPF = 1000.0f / ((double)pGraphicsWindow->FramesDone);
		pGraphicsWindow->FramesDone = 0;

		lasttime = ((double)clock() / (double)CLOCKS_PER_SEC);

		ElementGraphics* pElementGraphics = Object_Ref_Get_ElementPointer(iFPS_DisplayText, true, false, 0);

		GraphicsEffectText* pEffect = NULL;
		Graphics_Effects_Ref_Get_GraphicsEffect(pElementGraphics, GUIEffect_Text, &pEffect);

		free(pEffect->UTF8_Text);


		reactortemp += reactorpercentage * heatingfactor;
		reactortemp -= reactortemp / coolingfactor;

		rIn = reactortemp; // Read Input
		rOut = PIDCalc(&sPID, rIn); // Perform PID Interation
		reactorpercentage = ((rOut < 10.0) ? 10.0f : rOut); // Effect Needed Changes



		char buffer[128 + 19];
		snprintf(&buffer, 128 + 19, "TEMP: %f PERCENT: %f", reactortemp, reactorpercentage);


		pEffect->UTF8_Text = CopyData(buffer); //this is why its error in debug mode.
		Object_Ref_ReCreate_Element(iFPS_DisplayText, 0);
		Object_Ref_End_ElementPointer(iFPS_DisplayText, true, false, 0);
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_T == KeyPress && reactorpercentage < 99.999)
	{
		reactorpercentage += 0.01f;
	}
	if (pGraphicsWindow->pWindow->STATE_KEY_G == KeyPress && reactorpercentage > 10.00)
	{
		reactorpercentage -= 0.01f;
	}
	*/

	RHeaderCamera* pCameraHeader = Object_Ref_Get_ResourceHeaderPointer(iCameraHeader, false, false, ThreadIndex);
	ResourceHeaderAllocation iPositionHeader = Object_Ref_Scan_ObjectResourceHeadersSingle(pCameraHeader->Header.iObjects[0], GraphicsHeader_Position, ThreadIndex);	
	RHeaderPosition* pPositionHeader = Object_Ref_Get_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);
	static float framehorizontalAngle = 0.0f;
	static float frameverticalAngle = 0.0f;
	static double initmousex = 0.0f, initmousey = 0.0f;

	static double mousex = 0.0f, mousey = 0.0f;
	static bool updated = false;
	static bool oclick = false;

	if (pGraphicsWindow->pWindow->STATE_KEY_LEFT_SHIFT == KeyPress)
	{
		speed = 0.0005f;
	}
	else
	{
		speed = 0.01f;
	}

	if (pGraphicsWindow->pWindow->STATE_MOUSE_BUTTON_3 == KeyPress)
	{
		if (oclick == false)
		{
			initmousex = mouseSpeed * ((float)pGraphicsWindow->CurrentExtentWidth / 2.0f - (EngineRes.pUtils->MousePos_Callback_state.X_Position));
			initmousey = mouseSpeed * ((float)pGraphicsWindow->CurrentExtentHeight / 2.0f - (EngineRes.pUtils->MousePos_Callback_state.Y_Position));
			oclick = true;
		}

		updated = false;
		framehorizontalAngle = (mouseSpeed * ((float)pGraphicsWindow->CurrentExtentWidth / 2.0f - (EngineRes.pUtils->MousePos_Callback_state.X_Position))) - initmousex;
		frameverticalAngle = (mouseSpeed * ((float)pGraphicsWindow->CurrentExtentHeight / 2.0f - (EngineRes.pUtils->MousePos_Callback_state.Y_Position))) - initmousey;
	}
	else if (updated == false)
	{
		mousex += framehorizontalAngle;
		mousey += frameverticalAngle;
		framehorizontalAngle = 0.0f;
		frameverticalAngle = 0.0f;
		initmousex = 0.0f;
		initmousey = 0.0f;
		updated = true;
		oclick = false;
	}

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
	///glm_mat4_copy(Rotation, rotationm);
	mat4 scalem;
	glm_mat4_identity(scalem);
	glm_scale(scalem, Scale);

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


	glm_rotate_make(rotationm, 3.14, horiz);
	glm_rotate(rotationm, mousex + framehorizontalAngle, vertic);
	glm_rotate(rotationm, mousey + frameverticalAngle, horiz);

	glm_mul_sse2(translationm, rotationm, pPositionHeader->Matrix);
	glm_mul_sse2(pPositionHeader->Matrix, scalem, pPositionHeader->Matrix);
	glm_mul_sse2(pPositionHeader->Matrix, identitym, pPositionHeader->Matrix);


	//glm_rotate(pPositionHeader->Matrix, framehorizontalAngle, vertic);


	Object_Ref_End_ResourceHeaderPointer(iPositionHeader, false, false, ThreadIndex);
	Object_Ref_End_ResourceHeaderPointer(iCameraHeader, false, false, ThreadIndex);

	Object_Ref_End_ResourceHeaderPointer(iGraphicsWindow, false, false, ThreadIndex); 
	return (Success);
}

TEXRESULT Initialise_Chat() {
	uint32_t ThreadIndex = 0;

	for (size_t i = 0; i < 1; i++)
	{
		ObjectAllocation iObject;
		{
			ObjectCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)Object_Generic;
			MainCreateInfo.Name = NULL;
			Object_Ref_Create_Object(&iObject, MainCreateInfo, NULL, ThreadIndex);
		}
		{
			RHeaderGraphicsWindowCreateInfo CreateInfo;
			memset(&CreateInfo, 0, sizeof(CreateInfo));
			CreateInfo.TargetExtentWidth = 1024;
			CreateInfo.TargetExtentHeight = 1024;
			CreateInfo.TargetFrameBuffersSize = 2;
			ResourceHeaderCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_GraphicsWindow;
			MainCreateInfo.Name = "Triangle Engine X";
			Object_Ref_Create_ResourceHeader(&iGraphicsWindow, MainCreateInfo, &CreateInfo, ThreadIndex);
			Object_Ref_Add_Object_ResourceHeaderChild(iGraphicsWindow, iObject, ThreadIndex);
		}

		{
			RHeaderSceneCreateInfo CreateInfo;
			memset(&CreateInfo, 0, sizeof(CreateInfo));
			CreateInfo.InitialActive = true;
			ResourceHeaderCreateInfo MainCreateInfo;
			memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
			MainCreateInfo.Identifier = (uint32_t)ResourceHeader_Scene;
			MainCreateInfo.Name = NULL;
			Object_Ref_Create_ResourceHeader(&iScene, MainCreateInfo, &CreateInfo, ThreadIndex);
			Object_Ref_Add_Object_ResourceHeaderChild(iScene, iObject, ThreadIndex);
		}

		Formats_Ref_Load_2Dscene((const UTF8*)"data\\GUI\\2Dscene.json", iGraphicsWindow, iScene, ThreadIndex);

		//Formats_Ref_Load_3Dscene((const UTF8*)"data\\Models\\glTF-Sample-Models-master\\2.0\\Fox\\glTF\\Fox.gltf", iGraphicsWindow, iScene, 0);
		//Formats_Ref_Load_3Dscene((const UTF8*)"data\\Models\\f6f\\scene.gltf", iGraphicsWindow, iScene, 0);
		//Formats_Ref_Load_3Dscene((const UTF8*)"data\\Models\\flag\\scene.gltf", iGraphicsWindow, iScene, 0);

		{
			RHeaderScene* pScene = Object_Ref_Get_ResourceHeaderPointer(iScene, false, false, ThreadIndex);
			for (size_t i = 0; i < pScene->Header.iObjectsSize; i++)
			{
				Object* pObject = Object_Ref_Get_ObjectPointer(pScene->Header.iObjects[i], false, false, ThreadIndex);
				for (size_t i1 = 0; i1 < pObject->Header.iResourceHeadersSize; i1++)
				{
					ResourceHeader* pResourceHeader = Object_Ref_Get_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i1], false, false, ThreadIndex);
					for (size_t i2 = 0; i2 < pResourceHeader->Header.iElementsSize; i2++)
					{
						Element* pElement = Object_Ref_Get_ElementPointer(pResourceHeader->Header.iElements[i2], false, false, ThreadIndex);
						if (strcmp(pElement->Header.Name, "Indicator:TextCursor") == 0)
						{
							iTextCursor = pElement->Header.Allocation;
						}
						Object_Ref_End_ElementPointer(pResourceHeader->Header.iElements[i2], false, false, ThreadIndex);
					}
					Object_Ref_End_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i1], false, false, ThreadIndex);
				}
				Object_Ref_End_ObjectPointer(pScene->Header.iObjects[i], false, false, ThreadIndex);
			}
			Object_Ref_End_ResourceHeaderPointer(iScene, false, false, ThreadIndex);
		}

		{
			RHeaderScene* pScene = Object_Ref_Get_ResourceHeaderPointer(iScene, false, false, ThreadIndex);
			for (size_t i = 0; i < pScene->Header.iObjectsSize; i++)
			{
				Object* pObject = Object_Ref_Get_ObjectPointer(pScene->Header.iObjects[i], false, false, ThreadIndex);
				for (size_t i1 = 0; i1 < pObject->Header.iResourceHeadersSize; i1++)
				{
					ResourceHeader* pResourceHeader = Object_Ref_Get_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i1], false, false, ThreadIndex);
					for (size_t i2 = 0; i2 < pResourceHeader->Header.iElementsSize; i2++)
					{
						Element* pElement = Object_Ref_Get_ElementPointer(pResourceHeader->Header.iElements[i2], false, false, ThreadIndex);
						if (strcmp(pElement->Header.Name, "Indicator:SelectionBox") == 0)
						{
							iSelectionBox = pElement->Header.Allocation;
						}
						Object_Ref_End_ElementPointer(pResourceHeader->Header.iElements[i2], false, false, ThreadIndex);
					}
					Object_Ref_End_ResourceHeaderPointer(pObject->Header.iResourceHeaders[i1], false, false, ThreadIndex);
				}
				Object_Ref_End_ObjectPointer(pScene->Header.iObjects[i], false, false, ThreadIndex);
			}
			Object_Ref_End_ResourceHeaderPointer(iScene, false, false, ThreadIndex);
		}

		//autistic but it will do
		for (size_t i = 0; i < ObjectsRes.pUtils->InternalResourceHeaderBuffer.AllocationDatas.BufferSize; i++) {
			AllocationData* pAllocationData = &ObjectsRes.pUtils->InternalResourceHeaderBuffer.AllocationDatas.Buffer[i];
			if (pAllocationData->Allocation.ResourceHeader.Identifier == GraphicsHeader_Camera) {
				iCameraHeader = pAllocationData->Allocation.ResourceHeader;
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
				Object_Ref_Add_Object_ResourceHeaderChild(iResourceHeaderParent, iObject, 0);
			}
			ResourceHeaderAllocation iMaterial;
			{
				RHeaderMaterialCreateInfo CreateInfoMaterial;
				memset(&CreateInfoMaterial, 0, sizeof(CreateInfoMaterial));
				CreateInfoMaterial.iGraphicsWindow = iGraphicsWindow;
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
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, 0);
						free(Info.ImageData);
					}
					ResourceHeaderAllocation iTextureHeader;
					{
						RHeaderTextureCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Info.iGraphicsWindow = iGraphicsWindow;
						Info.iImageSource = iImageSource;
						Info.AllocationType = AllocationType_Discrite;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit | TextureUsage_StorageBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, 0);
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
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, 0);
						free(Info.ImageData);
					}
					ResourceHeaderAllocation iTextureHeader;
					{
						RHeaderTextureCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Info.iGraphicsWindow = iGraphicsWindow;
						Info.iImageSource = iImageSource;
						Info.AllocationType = AllocationType_Discrite;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit | TextureUsage_StorageBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, 0);
					}
					CreateInfoMaterial.EmissiveTexture.iTexture = iTextureHeader;
				}

				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iMaterial, MainCreateInfo, &CreateInfoMaterial, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iMaterial, iObject, 0);
			}

			{
				ElementGraphicsCreateInfo CreateInfo;
				memset(&CreateInfo, 0, sizeof(CreateInfo));
				CreateInfo.iMaterial = iMaterial;
				CreateInfo.iGraphicsWindow = iGraphicsWindow;

				CreateInfo.EffectCreateInfosSize = 1;
				CreateInfo.EffectCreateInfos = (ElementGraphicsCreateInfoEffect*)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));

				ChemistryEffectCreateInfoSimpleModel Info;
				memset(&Info, 0, sizeof(Info));

				CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)ChemistryEffects_SimpleModel;
				CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &Info;

				Info.pad  = 1;
				Info.Resolution = 5096;

				Info.ParticlesSize = (3000);
				Info.Particles = calloc(Info.ParticlesSize, sizeof(*Info.Particles));

				uint64_t it = 0;

				uint64_t val = 0;
				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 1; i < 5; i++)
					{
						float height = i * 2;

						val = (M_PI * 2 * height);
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos((i1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[1] = sin((i1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[2] = 0.0f;
							Info.Particles[it].PositionVelocity[0] = ((cos((i1 + 1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[0]);
							Info.Particles[it].PositionVelocity[1] = ((sin((i1 + 1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[1]);
							Info.Particles[it].PositionVelocity[2] = 0.0f;


							//Info.Particles[it].Magnitude[0] = 1.0f;
							Info.Particles[it].Magnitude[1] = 1.0f;
							//Info.Particles[it].Magnitude[2] = 1.0f;

							Info.Particles[it].Position[1] += 20.0f;

							it++;
						}
					}
				}

				val = 0;
				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 1; i < 5; i++)
					{
						float height = i * 2;

						val = (M_PI * 2 * height);
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos((i1 + 1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[1] = sin((i1 + 1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[2] = 0.0f;
							Info.Particles[it].PositionVelocity[0] = ((cos((i1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[0]);
							Info.Particles[it].PositionVelocity[1] = ((sin((i1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[1]);
							Info.Particles[it].PositionVelocity[2] = 0.0f;


							//Info.Particles[it].Magnitude[0] = -1.0f;
							Info.Particles[it].Magnitude[1] = -1.0f;
							//Info.Particles[it].Magnitude[2] = -1.0f;

							Info.Particles[it].Position[1] += 20.0f;

							it++;
						}
					}
				}


				ElementCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_Element(&iMolecularSimulation, MainCreateInfo, &CreateInfo, 0);
				Object_Ref_Add_ResourceHeader_ElementChild(iMolecularSimulation, iResourceHeaderParent, 0);
				free(CreateInfo.EffectCreateInfos);
				free(Info.Particles);
			}
		}
		*/		
		/*
				/*
				val = 0;
				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 15; i < 16; i++)
					{
						float height = i * 0.3;

						val = (M_PI * 2 * height);
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos((i1 + 1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[1] = 0;
							Info.Particles[it].Position[2] = sin((i1 + 1) * (6.28318531f / val)) * height;
							Info.Particles[it].PositionVelocity[0] = ((cos((i1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[0]);
							Info.Particles[it].PositionVelocity[1] = 0;
							Info.Particles[it].PositionVelocity[2] = ((sin((i1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[2]);

							//Info.Particles[it].Position[0] += 0.0001;

							//Info.Particles[it].Magnitude[0] = -1.0f;
							Info.Particles[it].Magnitude[1] = -1.0f;
							//Info.Particles[it].Magnitude[2] = -1.0f;

							//Info.Particles[it].Magnitude[2] = -0.1f;


							it++;
						}
					}
				}
				
				Info.ParticlesSize = it;
				
				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 2; i < 3; i++)
					{
						float height = i * 1;

						val = (M_PI * 2 * height);
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos((i1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[1] = sin((i1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[2] = 0.0f;
							Info.Particles[it].PositionVelocity[0] = ((cos((i1 + 1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[0]);
							Info.Particles[it].PositionVelocity[1] = ((sin((i1 + 1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[1]);
							Info.Particles[it].PositionVelocity[2] = 0.0f;

							Info.Particles[it].Position[0] += 3.3;

							//Info.Particles[it].Magnitude[0] = 1.0f;
							Info.Particles[it].Magnitude[1] = 1.0f;
							//Info.Particles[it].Magnitude[2] = 1.0f;

							//Info.Particles[it].Magnitude[2] = -0.1f;

							Info.Particles[it].Position[1] += 20.0f;

							it++;
						}
					}
				}
				
				val = 0;
				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 2; i < 3; i++)
					{
						float height = i * 1;

						val = (M_PI * 2 * height);
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos((i1 + 1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[1] = sin((i1 + 1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[2] = 0.0f;
							Info.Particles[it].PositionVelocity[0] = ((cos((i1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[0]);
							Info.Particles[it].PositionVelocity[1] = ((sin((i1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[1]);
							Info.Particles[it].PositionVelocity[2] = 0.0f;

							Info.Particles[it].Position[0] += 3.3;

							//Info.Particles[it].Magnitude[0] = -1.0f;
							Info.Particles[it].Magnitude[1] = -1.0f;
							//Info.Particles[it].Magnitude[2] = -1.0f;

							//Info.Particles[it].Magnitude[2] = -0.1f;

							Info.Particles[it].Position[1] += 20.0f;

							it++;
						}
					}
				}
				
				
				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 1; i < 2; i++)
					{
						float height = i * 1;

						val = (M_PI * 2 * height);
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos((i1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[1] = sin((i1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[2] = 0.0f;
							Info.Particles[it].PositionVelocity[0] = ((cos((i1 + 1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[0]);
							Info.Particles[it].PositionVelocity[1] = ((sin((i1 + 1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[1]);
							Info.Particles[it].PositionVelocity[2] = 0.0f;

							Info.Particles[it].Position[0] -= 2;

							//Info.Particles[it].Magnitude[0] = 1.0f;
							Info.Particles[it].Magnitude[1] = 1.0f;
							//Info.Particles[it].Magnitude[2] = 1.0f;

							//Info.Particles[it].Magnitude[2] = -0.1f;

							Info.Particles[it].Position[1] += 20.0f;

							it++;
						}
					}
				}

				val = 0;
				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 1; i < 2; i++)
					{
						float height = i * 1;

						val = (M_PI * 2 * height);
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos((i1 + 1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[1] = sin((i1 + 1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[2] = 0.0f;
							Info.Particles[it].PositionVelocity[0] = ((cos((i1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[0]);
							Info.Particles[it].PositionVelocity[1] = ((sin((i1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[1]);
							Info.Particles[it].PositionVelocity[2] = 0.0f;

							Info.Particles[it].Position[0] -= 2;

							//Info.Particles[it].Magnitude[0] = -1.0f;
							Info.Particles[it].Magnitude[1] = -1.0f;
							//Info.Particles[it].Magnitude[2] = -1.0f;

							//Info.Particles[it].Magnitude[2] = -0.1f;

							Info.Particles[it].Position[1] += 20.0f;

							it++;
						}
					}
				}
				

				
				uint64_t ringc = 6;

				for (size_t i0 = 0; i0 < ringc; i0++)
				{
					for (size_t i = 1; i < 2; i++)
					{
						float height = i * 0.5;
						val = (M_PI * 2 * height) * 2;
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
				*/
		/*
		{
			ResourceHeaderAllocation iResourceHeaderParent;
			{
				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)ResourceHeader_Generic;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iResourceHeaderParent, MainCreateInfo, NULL, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iResourceHeaderParent, iObject, 0);
			}
			ResourceHeaderAllocation iMaterial;
			{
				RHeaderMaterialCreateInfo CreateInfoMaterial;
				memset(&CreateInfoMaterial, 0, sizeof(CreateInfoMaterial));
				CreateInfoMaterial.iGraphicsWindow = iGraphicsWindow;
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
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, 0);
						free(Info.ImageData);
					}
					ResourceHeaderAllocation iTextureHeader;
					{
						RHeaderTextureCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Info.iGraphicsWindow = iGraphicsWindow;
						Info.iImageSource = iImageSource;
						Info.AllocationType = AllocationType_Discrite;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit | TextureUsage_StorageBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, 0);
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
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, 0);
						free(Info.ImageData);
					}
					ResourceHeaderAllocation iTextureHeader;
					{
						RHeaderTextureCreateInfo Info;
						memset(&Info, 0, sizeof(Info));
						Info.iGraphicsWindow = iGraphicsWindow;
						Info.iImageSource = iImageSource;
						Info.AllocationType = AllocationType_Discrite;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit | TextureUsage_StorageBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, 0);
					}
					CreateInfoMaterial.EmissiveTexture.iTexture = iTextureHeader;
				}

				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iMaterial, MainCreateInfo, &CreateInfoMaterial, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iMaterial, iObject, 0);
			}

			{
				ElementGraphicsCreateInfo CreateInfo;
				memset(&CreateInfo, 0, sizeof(CreateInfo));
				CreateInfo.iMaterial = iMaterial;
				CreateInfo.iGraphicsWindow = iGraphicsWindow;

				CreateInfo.EffectCreateInfosSize = 1;
				CreateInfo.EffectCreateInfos = (ElementGraphicsCreateInfoEffect*)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));

				ChemistryEffectCreateInfoFundamental Info;
				memset(&Info, 0, sizeof(Info));

				CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)ChemistryEffects_Fundamental;
				CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &Info;

				Info.ParticlesSize = (2000);
				Info.Particles = calloc(Info.ParticlesSize, sizeof(*Info.Particles));

				uint64_t it = 0;

				
				for (size_t i1 = 0; i1 < 10; i1++)
				{
					for (int i = 0; i < 3; i++)
					{
						Info.Particles[it].Position[0] = -(-0.0f) + (i * 1.0);
						Info.Particles[it].Position[1] = -(5.0f) + (i1 * -1.0);
						Info.Particles[it].Position[2] = 0.0f;
						Info.Particles[it].PositionVelocity[0] = 0.0f;
						Info.Particles[it].PositionVelocity[1] = 1.0f;
						Info.Particles[it].PositionVelocity[2] = 0.0f;

						Info.Particles[it].Magnitude[0] = 0.0f;
						Info.Particles[it].Magnitude[1] = 1.0f;
						Info.Particles[it].Magnitude[2] = 0.0f;

						it++;
					}
				}
				
				for (size_t i1 = 0; i1 < 1; i1++)
				{
					for (int i = 0; i < 10; i++)
					{
						Info.Particles[it].Position[0] = -(-0.0f) + (i1 * 1.0) + (i * -1.0);
						Info.Particles[it].Position[1] = -(-0.0f) + (i * -1.0);
						Info.Particles[it].Position[2] = 0.0f;
						Info.Particles[it].PositionVelocity[0] = 1.0f;
						Info.Particles[it].PositionVelocity[1] = 1.0f;
						Info.Particles[it].PositionVelocity[2] = 0.0f;

						Info.Particles[it].Magnitude[0] = 1.0f;
						Info.Particles[it].Magnitude[1] = 0.0f;
						Info.Particles[it].Magnitude[2] = 0.0f;

						it++;
					}
				}		
				


				for (size_t i1 = 0; i1 < 1; i1++)
				{
					for (int i = 0; i < 1; i++)
					{
						Info.Particles[it].Position[0] = -(-7.0f) + (i1 * 1.0) + (i * -1.0);
						Info.Particles[it].Position[1] = -(-0.0f) + (i * -1.0);
						Info.Particles[it].Position[2] = 0.0f;
						Info.Particles[it].PositionVelocity[0] = -1.0f;
						Info.Particles[it].PositionVelocity[1] = 0.0f;
						Info.Particles[it].PositionVelocity[2] = 0.0f;

						Info.Particles[it].Magnitude[0] = 0.0f;
						Info.Particles[it].Magnitude[1] = 1.0f;
						Info.Particles[it].Magnitude[2] = 0.0f;

						it++;
					}
				}

				//RING XZ
					
				uint64_t val = 0;	
				
				val = 0;
				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 4; i < 5; i++)
					{
						float height = i * 1.0;

						val = (M_PI * 2 * height);
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos((i1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[1] = 0;
							Info.Particles[it].Position[2] = sin((i1) * (6.28318531f / val)) * height;
							Info.Particles[it].PositionVelocity[0] = ((cos((i1 + 1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[0]);
							Info.Particles[it].PositionVelocity[1] = 0;
							Info.Particles[it].PositionVelocity[2] = ((sin((i1 + 1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[2]);


							//Info.Particles[it].Magnitude[0] = Info.Particles[it].PositionVelocity[0];
							//Info.Particles[it].Magnitude[1] = Info.Particles[it].PositionVelocity[1];
							//Info.Particles[it].Magnitude[2] = Info.Particles[it].PositionVelocity[2];

							Info.Particles[it].Magnitude[1] = 1.0000f;

							it++;
						}
					}
				}
				
				
				val = 0;
				for (int i0 = 0; i0 < 1; i0++)
				{
					for (size_t i = 4; i < 5; i++)
					{
						float height = i * 1.0;

						val = (M_PI * 2 * height);
						for (size_t i1 = 0; i1 < val; i1++)
						{
							Info.Particles[it].Position[0] = cos((i1 + 1) * (6.28318531f / val)) * height;
							Info.Particles[it].Position[1] = 0;
							Info.Particles[it].Position[2] = sin((i1 + 1) * (6.28318531f / val)) * height;
							Info.Particles[it].PositionVelocity[0] = ((cos((i1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[0]);
							Info.Particles[it].PositionVelocity[1] = 0;
							Info.Particles[it].PositionVelocity[2] = ((sin((i1) * (6.28318531f / val)) * height) - Info.Particles[it].Position[2]);

							//Info.Particles[it].Magnitude[0] = -Info.Particles[it].PositionVelocity[0];
							//Info.Particles[it].Magnitude[1] = -Info.Particles[it].PositionVelocity[1];
							//Info.Particles[it].Magnitude[2] = -Info.Particles[it].PositionVelocity[2];

							Info.Particles[it].Magnitude[1] = -1.0000f;

							it++;
						}
					}
				}
				

				ElementCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_Element(&iMolecularSimulation, MainCreateInfo, &CreateInfo, 0);
				Object_Ref_Add_ResourceHeader_ElementChild(iMolecularSimulation, iResourceHeaderParent, 0);
				free(CreateInfo.EffectCreateInfos);
				free(Info.Particles);
			}
		}
		*/
				
		{
			ResourceHeaderAllocation iResourceHeaderParent;
			{
				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)ResourceHeader_Generic;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iResourceHeaderParent, MainCreateInfo, NULL, ThreadIndex);
				Object_Ref_Add_Object_ResourceHeaderChild(iResourceHeaderParent, iObject, ThreadIndex);
			}
			ResourceHeaderAllocation iMaterial;
			{
				RHeaderMaterialCreateInfo CreateInfoMaterial;
				memset(&CreateInfoMaterial, 0, sizeof(CreateInfoMaterial));
				CreateInfoMaterial.iGraphicsWindow = iGraphicsWindow;
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
						Info.AllocationType = AllocationType_Discrite;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit | TextureUsage_StorageBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = NULL;
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
						MainCreateInfo.Name = NULL;
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
						Info.AllocationType = AllocationType_Discrite;
						Info.TextureUsage = (TextureUsageFlags)(TextureUsage_SampledBit | TextureUsage_TransferDstBit | TextureUsage_StorageBit);
						ResourceHeaderCreateInfo MainCreateInfo;
						memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
						MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Texture;
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, ThreadIndex);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, ThreadIndex);
					}
					CreateInfoMaterial.EmissiveTexture.iTexture = iTextureHeader;
				}


				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iMaterial, MainCreateInfo, &CreateInfoMaterial, ThreadIndex);
				Object_Ref_Add_Object_ResourceHeaderChild(iMaterial, iObject, ThreadIndex);
			}

			{
				ElementGraphicsCreateInfo CreateInfo;
				memset(&CreateInfo, 0, sizeof(CreateInfo));
				CreateInfo.iMaterial = iMaterial;
				CreateInfo.iGraphicsWindow = iGraphicsWindow;

				CreateInfo.EffectCreateInfosSize = 1;
				CreateInfo.EffectCreateInfos = (ElementGraphicsCreateInfoEffect*)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));

				ChemistryEffectCreateInfoSimplified Info;
				memset(&Info, 0, sizeof(Info));

				CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)ChemistryEffects_Simplified;
				CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &Info;

				Info.ParticlesSize = (1000);
				Info.Particles = calloc(Info.ParticlesSize, sizeof(*Info.Particles));

				Info.Multiplier = 0.0f;

				Info.SimulationResolution = 8;

				uint64_t it = 0;
				vec3 Position;
				glm_vec3_zero(Position);
				Add_ChemistryElement(7, Position, Info.Particles, &it, -1, true);
				//Position[0] +=  10;
				//Add_ChemistryElement(6, Position, Info.Particles, &it, -1, true);


				for (size_t i = 1; i < 1; i++)
				{
					Position[0] += (i) * 5;
					Position[1] += ((i / 10) % 2) * 5;
					
					//Add_ChemistryElement(i, Position, Info.Particles, &it, -1, true);
				}


				//dont forget to add magnetismw field shit here too;

				Info.ParticlesSize = it;

				ElementCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_Element(&iMolecularSimulation, MainCreateInfo, &CreateInfo, ThreadIndex);
				Object_Ref_Add_ResourceHeader_ElementChild(iMolecularSimulation, iResourceHeaderParent, ThreadIndex);
				free(CreateInfo.EffectCreateInfos);
				free(Info.Particles);
			}
		}

		{
			for (size_t i = 0; i < ObjectsRes.pUtils->InternalObjectBuffer.AllocationDatas.BufferSize; i++) {
				AllocationData* pAllocationData = &ObjectsRes.pUtils->InternalObjectBuffer.AllocationDatas.Buffer[i];
				if (pAllocationData->Allocation.Object.Identifier == Object_Generic) {
					Object* pObject = Object_Ref_Get_ObjectPointer(pAllocationData->Allocation.Object, false, false, ThreadIndex);
					if (strcmp(pObject->Header.Name, "Level:Hydrocarbons") == 0)
					{
						Add_ChemistryIcon(pObject->Header.Allocation, "Icon:Button:C4H10", "data\\GUI\\Textures\\C4H10.png", ".png", false, 0, 0);
					}
					Object_Ref_End_ObjectPointer(pAllocationData->Allocation.Object, false, false, ThreadIndex);
				}
			}

			Resize_Array(&CategoryIcons, CategoryIconsSize, CategoryIconsSize + 1, sizeof(*CategoryIcons));
			CategoryIcons[CategoryIconsSize].Name = CopyData("Icon:Button:Home");
			CategoryIcons[CategoryIconsSize].Offset = 0.0f;
			CategoryIcons[CategoryIconsSize].ReverseIndex = 0;
			CategoryIconsSize++;

			Resize_Array(&CategoryIcons, CategoryIconsSize, CategoryIconsSize + 1, sizeof(*CategoryIcons));
			CategoryIcons[CategoryIconsSize].Name = CopyData("Icon:Button:Atoms");
			CategoryIcons[CategoryIconsSize].Offset = 100.0f;
			CategoryIcons[CategoryIconsSize].ReverseIndex = 0;
			CategoryIconsSize++;

			Resize_Array(&CategoryIcons, CategoryIconsSize, CategoryIconsSize + 1, sizeof(*CategoryIcons));
			CategoryIcons[CategoryIconsSize].Name = CopyData("Icon:Button:Chemicals");
			CategoryIcons[CategoryIconsSize].Offset = 200.0f;
			CategoryIcons[CategoryIconsSize].ReverseIndex = 0;
			CategoryIconsSize++;

			Resize_Array(&CategoryIcons, CategoryIconsSize, CategoryIconsSize + 1, sizeof(*CategoryIcons));
			CategoryIcons[CategoryIconsSize].Name = CopyData("Icon:Button:Hydrocarbons");
			CategoryIcons[CategoryIconsSize].Offset = 300.0f;
			CategoryIcons[CategoryIconsSize].ReverseIndex = 2;
			CategoryIconsSize++;
		}

		{
			ResourceHeaderAllocation iMaterial;
			{
				RHeaderMaterialCreateInfo CreateInfoMaterial;
				memset(&CreateInfoMaterial, 0, sizeof(CreateInfoMaterial));
				CreateInfoMaterial.iGraphicsWindow = iGraphicsWindow;
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
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, 0);
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
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, 0);
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
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, 0);
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
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, 0);
					}
					CreateInfoMaterial.EmissiveTexture.iTexture = iTextureHeader;
				}

				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iMaterial, MainCreateInfo, &CreateInfoMaterial, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iMaterial, iObject, 0);
			}
			ResourceHeaderAllocation iPositionHeader;
			{
				RHeaderPositionCreateInfo CreateInfo = { sizeof(CreateInfo) };

				vec3 Translation;
				glm_vec3_zero(Translation);

				Translation[0] = 0.93f;
				Translation[1] = 0.032f;
				Translation[2] = 0.001f;

				glm_mat4_identity(CreateInfo.Matrix);

				mat4 translationm;
				glm_mat4_identity(translationm);
				glm_translate(translationm, Translation);

				glm_mul_sse2(translationm, CreateInfo.Matrix, CreateInfo.Matrix);

				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Position;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iPositionHeader, MainCreateInfo, &CreateInfo, ThreadIndex);
				Object_Ref_Add_Object_ResourceHeaderChild(iPositionHeader, iObject, ThreadIndex);
			}

			{
				RHeaderMaterial* pMaterial = Object_Ref_Get_ResourceHeaderPointer(iMaterial, true, false, 0);
				pMaterial->BaseColourMode = MaterialMode_Alpha;
				Object_Ref_End_ResourceHeaderPointer(iMaterial, true, false, 0);

				ElementGraphicsCreateInfo CreateInfo;
				memset(&CreateInfo, 0, sizeof(CreateInfo));
				CreateInfo.iMaterial = iMaterial;
				CreateInfo.iGraphicsWindow = iGraphicsWindow;

				CreateInfo.EffectCreateInfosSize = 1;
				CreateInfo.EffectCreateInfos = (ElementGraphicsCreateInfoEffect*)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));


				GraphicsEffectCreateInfoText InfoText;
				memset(&InfoText, 0, sizeof(InfoText));

				CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)GUIEffect_Text;
				CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &InfoText;

				InfoText.Text = (UTF8*)".";
				InfoText.FontSize = 60;

				InfoText.iFontsSize = 1;
				InfoText.iFonts = (RHeaderFont**)calloc(InfoText.iFontsSize, sizeof(*InfoText.iFonts));
				{
					ResourceHeaderAllocation iFont;
					RHeaderFontCreateInfo CreateInfoFont;
					memset(&CreateInfoFont, 0, sizeof(CreateInfoFont));
					Open_Data(&CreateInfoFont.Data, (UTF8*)"data\\Fonts\\OpenSans-VariableFont_wdth,wght.ttf");
					ResourceHeaderCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GUIHeader_Font;
					MainCreateInfo.Name = NULL;
					Object_Ref_Create_ResourceHeader(&iFont, MainCreateInfo, &CreateInfoFont, 0);
					Object_Ref_Add_Object_ResourceHeaderChild(iFont, iObject, 0);
					InfoText.iFonts[0] = iFont;
					free(CreateInfoFont.Data.pData);
				}

				InfoText.Size[0] = 0.51f;
				InfoText.Size[1] = 0.05f;

				//InfoText.Position[0] = 0.4f;
				//InfoText.Position[1] = 1.0f;

				for (size_t i1 = 0; i1 < 2; i1++)
					InfoText.BoundingBoxSize[i1] = InfoText.Size[i1];

				//for (size_t i1 = 0; i1 < 2; i1++)
				//	InfoText.BoundingBoxPosition[i1] = InfoText.Position[i1];

				ElementCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_Element(&iFPS_DisplayText, MainCreateInfo, &CreateInfo, 0);
				Object_Ref_Add_ResourceHeader_ElementChild(iFPS_DisplayText, iPositionHeader, 0);
				free(CreateInfo.EffectCreateInfos);
				free(InfoText.iFonts);
			}
		}
		{
			ResourceHeaderAllocation iMaterial;
			{
				RHeaderMaterialCreateInfo CreateInfoMaterial;
				memset(&CreateInfoMaterial, 0, sizeof(CreateInfoMaterial));
				CreateInfoMaterial.iGraphicsWindow = iGraphicsWindow;
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
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, 0);
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
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, 0);
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
						Object_Ref_Add_Object_ResourceHeaderChild(iImageSource, iObject, 0);
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
						MainCreateInfo.Name = NULL;
						Object_Ref_Create_ResourceHeader(&iTextureHeader, MainCreateInfo, &Info, 0);
						Object_Ref_Add_Object_ResourceHeaderChild(iTextureHeader, iObject, 0);
					}
					CreateInfoMaterial.EmissiveTexture.iTexture = iTextureHeader;
				}

				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Material;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iMaterial, MainCreateInfo, &CreateInfoMaterial, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iMaterial, iObject, 0);
			}

			ResourceHeaderAllocation iPositionHeader;
			{
				RHeaderPositionCreateInfo CreateInfo = { sizeof(CreateInfo) };

				vec3 Translation;
				glm_vec3_zero(Translation);

				Translation[0] = 0.0f;
				Translation[1] = 0.0f;

				glm_mat4_identity(CreateInfo.Matrix);

				mat4 translationm;
				glm_mat4_identity(translationm);
				glm_translate(translationm, Translation);

				glm_mul_sse2(translationm, CreateInfo.Matrix, CreateInfo.Matrix);

				ResourceHeaderCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsHeader_Position;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_ResourceHeader(&iPositionHeader, MainCreateInfo, &CreateInfo, ThreadIndex);
				Object_Ref_Add_Object_ResourceHeaderChild(iPositionHeader, iObject, ThreadIndex);
			}

			{
				RHeaderMaterial* pMaterial = Object_Ref_Get_ResourceHeaderPointer(iMaterial, true, false, 0);
				pMaterial->BaseColourMode = MaterialMode_Alpha;
				Object_Ref_End_ResourceHeaderPointer(iMaterial, true, false, 0);

				ElementGraphicsCreateInfo CreateInfo;
				memset(&CreateInfo, 0, sizeof(CreateInfo));
				CreateInfo.iMaterial = iMaterial;
				CreateInfo.iGraphicsWindow = iGraphicsWindow;

				CreateInfo.EffectCreateInfosSize = 1;
				CreateInfo.EffectCreateInfos = (ElementGraphicsCreateInfoEffect*)calloc(CreateInfo.EffectCreateInfosSize, sizeof(*CreateInfo.EffectCreateInfos));


				GraphicsEffectCreateInfoText InfoText;
				memset(&InfoText, 0, sizeof(InfoText));

				CreateInfo.EffectCreateInfos[0].Identifier = (uint32_t)GUIEffect_Text;
				CreateInfo.EffectCreateInfos[0].pEffectCreateInfo = &InfoText;

				InfoText.Text = (UTF8*)"Multiplier:";
				InfoText.FontSize = 60;

				InfoText.iFontsSize = 1;
				InfoText.iFonts = (RHeaderFont**)calloc(InfoText.iFontsSize, sizeof(*InfoText.iFonts));
				{
					ResourceHeaderAllocation iFont;
					RHeaderFontCreateInfo CreateInfoFont;
					memset(&CreateInfoFont, 0, sizeof(CreateInfoFont));
					Open_Data(&CreateInfoFont.Data, (UTF8*)"data\\Fonts\\OpenSans-VariableFont_wdth,wght.ttf");
					ResourceHeaderCreateInfo MainCreateInfo;
					memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
					MainCreateInfo.Identifier = (uint32_t)GUIHeader_Font;
					MainCreateInfo.Name = NULL;
					Object_Ref_Create_ResourceHeader(&iFont, MainCreateInfo, &CreateInfoFont, 0);
					Object_Ref_Add_Object_ResourceHeaderChild(iFont, iObject, 0);
					InfoText.iFonts[0] = iFont;
					free(CreateInfoFont.Data.pData);
				}

				InfoText.Size[0] = 0.15f;
				InfoText.Size[1] = 0.05f;

				//InfoText.Position[0] = 0.4f;
				//InfoText.Position[1] = 0.95f;

				for (size_t i1 = 0; i1 < 2; i1++)
					InfoText.BoundingBoxSize[i1] = InfoText.Size[i1];

				//for (size_t i1 = 0; i1 < 2; i1++)
				//	InfoText.BoundingBoxPosition[i1] = InfoText.Position[i1];

				ElementCreateInfo MainCreateInfo;
				memset(&MainCreateInfo, 0, sizeof(MainCreateInfo));
				MainCreateInfo.Identifier = (uint32_t)GraphicsElement_ElementGraphics;
				MainCreateInfo.Name = NULL;
				Object_Ref_Create_Element(&iMultiplierText, MainCreateInfo, &CreateInfo, 0);
				Object_Ref_Add_ResourceHeader_ElementChild(iMultiplierText, iPositionHeader, 0);
				free(CreateInfo.EffectCreateInfos);
				free(InfoText.iFonts);
			}
		}

		
		
	}	

	/*
		{
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
				Object_Ref_Create_ResourceHeader(&iAudioSource, MainCreateInfo, &CreateInfo, 0);
				Object_Ref_Add_Object_ResourceHeaderChild(iAudioSource, iObject, 0);
				free(header);
			}

			ElementAllocation iAudioElement;
			{
				ElementAudioCreateInfo CreateInfo;
				memset(&CreateInfo, 0, sizeof(CreateInfo));
				CreateInfo.UsageFlags = AudioElementUsage_Playback;
				CreateInfo.iAudioSource = iAudioSource;
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
				Object_Ref_Create_Element(&iAudioElement, MainCreateInfo, &CreateInfo, 0);
				Object_Ref_Add_ResourceHeader_ElementChild(iAudioElement, iAudioSource, 0);
				free(CreateInfo.EffectCreateInfos);
			}


			ElementAudio* pAudioElement = Object_Ref_Get_ElementPointer(iAudioElement, true, false, 0);

			//Convert_AudioData(&pAudioSource->AudioData, Format::int32LE);
			//std::thread thread(Convert_AudioData, &pAudioSource->AudioData, Format::int32LE);
			//thread.detach();
			//RHeaderOutputStream* pOutputStream = (RHeaderOutputStream*)Object_Ref_Get_ResourceHeaderPointer(oheader);
			Audio_Ref_Start_OutputStream(pAudioElement);

			Object_Ref_End_ElementPointer(iAudioElement, true, false, 0);
		}
	*/
	//Object_Ref_Write_TEIF((const UTF8*)"BIN.teif", 0);	
	//Object_Ref_Read_TEIF((const UTF8*)"BIN.teif", 0);	

	return (Success);
}

TEXRESULT Destroy_Chat()
{

	return (Success);
}

struct ChatResStruct {
	void* pInitialise_Chat;
	void* pDestroy_Chat;
	void* pUpdate_Chat;

	void* pButtonClick_Callback;

	void* pKey_Callback;
	void* pCharacter_Callback;
	void* pClick_Callback;
	void* pScroll_Callback;
	void* pClose_Callback;


	void* pChemistryClick_Callback;
	void* pChemistryKey_Callback;


	void* pFileClick_Callback;
	void* pAddClick_Callback;
	void* pViewClick_Callback;
	void* pAnalyzeClick_Callback;
	void* pTestClick_Callback;

	void* pFileIconClick_Callback;
	void* pDropdownClick_Callback;
	void* pIconClick_Callback;
	void* pAtomSizerClick_Callback;
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
	Chemistry_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);

	//exports
	//resources
	//functions
	//ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData("Formats::Utils"), &FormatsRes.pUtils, &Utils);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Initialise_Chat"), &ChatRes.pInitialise_Chat, &Initialise_Chat, Construct, 10000.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Destroy_Chat"), &ChatRes.pDestroy_Chat, &Destroy_Chat, Destruct, 0.001f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Update_Chat"), &ChatRes.pUpdate_Chat, &Update_Chat, EveryFrame, 0.1f, 0, NULL);
	

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::ButtonClick_Callback"), &ChatRes.pButtonClick_Callback, &ButtonClick_Callback, NoCall, 0.0f, 0, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Character_Callback"), &ChatRes.pCharacter_Callback, &Character_Callback, Character_Input, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Key_Callback"), &ChatRes.pKey_Callback, &Key_Callback, Key_Input, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Click_Callback"), &ChatRes.pClick_Callback, &Click_Callback, MouseButton_Input, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Scroll_Callback"), &ChatRes.pScroll_Callback, &Scroll_Callback, Scroll_Input, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::Close_Callback"), &ChatRes.pClose_Callback, &Close_Callback, Window_Close, 0.0f, 0, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::ChemistryClick_Callback"), &ChatRes.pChemistryClick_Callback, &ChemistryClick_Callback, MouseButton_Input, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::ChemistryKey_Callback"), &ChatRes.pChemistryKey_Callback, &ChemistryKey_Callback, Key_Input, 0.0f, 0, NULL);



	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::FileClick_Callback"), &ChatRes.pFileClick_Callback, &FileClick_Callback, NoCall, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::AddClick_Callback"), &ChatRes.pAddClick_Callback, &AddClick_Callback, NoCall, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::ViewClick_Callback"), &ChatRes.pViewClick_Callback, &ViewClick_Callback, NoCall, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::AnalyzeClick_Callback"), &ChatRes.pAnalyzeClick_Callback, &AnalyzeClick_Callback, NoCall, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::TestClick_Callback"), &ChatRes.pTestClick_Callback, &TestClick_Callback, NoCall, 0.0f, 0, NULL);


	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::FileIconClick_Callback"), &ChatRes.pFileIconClick_Callback, &FileIconClick_Callback, NoCall, 0.0f, 0, NULL);

	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::DropdownClick_Callback"), &ChatRes.pDropdownClick_Callback, &DropdownClick_Callback, NoCall, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::IconClick_Callback"), &ChatRes.pIconClick_Callback, &IconClick_Callback, NoCall, 0.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chat::AtomSizerClick_Callback"), &ChatRes.pAtomSizerClick_Callback, &AtomSizerClick_Callback, NoCall, 0.0f, 0, NULL);




}


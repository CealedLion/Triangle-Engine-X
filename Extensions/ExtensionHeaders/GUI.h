/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Standard Triangle Engine X GUI API.

SPECIFICATION:

* This library is built on Triangle Engine X's graphics library.
* 
* It is a high level library that is basicially a bunch of shortcuts to make complicated
objects such as dropdown boxes, scrollbars, etc.

* TEX_EXPOSE_GUI
* 
* Utils can be imported. GUI::Utils

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
#define TEX_GUI_API

#ifdef TEX_EXPOSE_GUI
#include <ft2build.h>
#include <libpng/png.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_TRUETYPE_TABLES_H
#include FT_COLOR_H
#include FT_SIZES_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Enums
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* amount of bits each channel in format is
* compressed are undefined
*/
const uint8_t FreetypeFormatBitsPerChannels[][4] = {
	{0, 0, 0, 0},		//UNDEFEIND
	{1, 0, 0, 0},
	{8, 0, 0, 0},
	{2, 0, 0, 0},
	{4, 0, 0, 0},
	{8, 8, 8, 0},
	{8, 8, 8, 0},
	{8, 8, 8, 8},
};
/*
* Added in 1.0.0
* amount of ChannelIndentifiers format has.
*/
const char FreetypeFormatChannelIndentifiers[][4] = {
	{'R', 0, 0, 0}, //UNDEFEIND
	{'R', 0, 0, 0},
	{'R', 0, 0, 0},
	{'R', 0, 0, 0},
	{'R', 0, 0, 0},
	{'B', 'G', 'R', 0},
	{'B', 'G', 'R', 0},
	{'B', 'G', 'R', 'A'},
};
/*
* Added in 1.0.0
* amount of bit stride each format has.
*/
const uint8_t FreetypeFormatStrides[] = {

	0, //UNDEFEIND
	1 * 1,
	8 * 1,
	2 * 1,
	4 * 1,
	8 * 3,
	8 * 3,
	8 * 4,

};
/*
* Added in 1.0.0
* amount of components each format has.
*/
const uint8_t FreetypeFormatChannelCounts[] = {
	0, //UNDEFEIND
	1,	//FT_PIXEL_MODE_MONO,
	1,	//FT_PIXEL_MODE_GRAY,
	1,	//FT_PIXEL_MODE_GRAY2,
	1,	//FT_PIXEL_MODE_GRAY4,
	3,	//FT_PIXEL_MODE_LCD,
	3,	//FT_PIXEL_MODE_LCD_V,
	4,	//FT_PIXEL_MODE_BGRA,
};
/*
* Added in 1.0.0
* datatype of each vkformat
*/
const DataType FreetypeFormatDataType[][4] = {

	{Undefined, Undefined, Undefined, Undefined}, //UNDEFEIND
	{UnsignedInt, Undefined, Undefined, Undefined},	//FT_PIXEL_MODE_MONO,
	{UnsignedInt, Undefined, Undefined, Undefined},	//FT_PIXEL_MODE_GRAY,
	{UnsignedInt, Undefined, Undefined, Undefined},	//FT_PIXEL_MODE_GRAY2,
	{UnsignedInt, Undefined, Undefined, Undefined},	//FT_PIXEL_MODE_GRAY4,
	{UnsignedInt, UnsignedInt, UnsignedInt, Undefined},	//FT_PIXEL_MODE_LCD,
	{UnsignedInt, UnsignedInt, UnsignedInt, Undefined},	//FT_PIXEL_MODE_LCD_V,
	{UnsignedInt, UnsignedInt, UnsignedInt, UnsignedInt},	//FT_PIXEL_MODE_BGRA,
};
#endif
/*
* Added in 1.0.0
* GUI Uses enums from 3000
*/
typedef enum GUIHeaderType {
	GUIHeader_Button = 3000,
	GUIHeader_Font = 3001
}GUIHeaderType;  
/*
* Added in 1.0.0
* GUI Uses enums from 3000
*/
typedef enum GUIEffectsType {
	GUIEffect_Text = 3000,
}GUIEffectsType;
/*
* Added in 1.0.0
* GUI button states, describes the button state of a rheaderbutton.
* Doesnt specify what button clicked any of them on the mouse couldve.
* Release when unclicked.
* Press when clicked.
* Repeat when clicked for 2 frames.
* hover when hovered over with mouse.
*/
typedef enum GUIButtonState {
	GUIButtonState_Release = 0,
	GUIButtonState_Press = 1,
	GUIButtonState_Repeat = 2,
	GUIButtonState_Hover = 3
}GUIButtonCallbackState;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Structs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Callback function for buttons
*/
struct RHeaderButton;
typedef void(Button_Callback)(ElementAllocation ClickedElement, ResourceHeaderAllocation ClickedResourceHeader, ObjectAllocation ClickedGameObject, ResourceHeaderAllocation iButton, GUIButtonCallbackState Action);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ResourceHeaders
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* when in a gameobject with object2d or object3d it will turn them into clickable objects.
* plays function when object is clicked.
* works both element2d and element3d
* Callback symbol safe to destruct after creation, like all createinfo data unless
  said so.
*/
typedef struct RHeaderButtonCreateInfo {
	UTF8* CallbackSymbol;
}RHeaderButtonCreateInfo;
typedef struct RHeaderButton {
	ResourceHeaderTEMPLATE Header;

	UTF8* CallbackSymbol;

	//every reinit
	Button_Callback* Callback_Function;
}RHeaderButton;
/*
* Added in 1.0.0
* Font storage header
* Data is font file in memory. like ttf or otf
*/
typedef struct RHeaderFontCreateInfo {
	FileData Data;
}RHeaderFontCreateInfo;
typedef struct RHeaderFont {
	ResourceHeaderTEMPLATE Header;

	FileData Data;

#ifdef TEX_EXPOSE_GUI
	FT_Face FtFace;
#else
	void* FtFace;
#endif
}RHeaderFont;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Renders Text Effect.
* requires pElement->iMaterial to have texture bound to basecolourtexture and for it to have valid imagesource header.
* For Coloured text elements requires pElement->iMaterial to have texture bound to Emissive texture and for it to have valid imagesource header.
*/
typedef struct GraphicsEffectCreateInfoText {
	vec2 Size; //size in percentage of screen.
	vec3 Position; //position in percentage of screen.
	//bounding box means everything outside of it wont be rendered.
	vec2 BoundingBoxSize; //size in percentage of screen.
	vec2 BoundingBoxPosition; //position in percentage of screen.

	size_t FontSize; //text size in points

	UTF8* Text; //text encoded in UTF-8

	size_t iFontsSize;
	ResourceHeaderAllocation* iFonts; //Font set, collection of fonts to use
}GraphicsEffectCreateInfoText;
typedef struct GPU_GraphicsEffectText {
	vec2 Size; //size in percentage of screen.
	vec3 Position; //position in percentage of screen.
	//bounding box means everything outside of it wont be rendered.
	vec2 BoundingBoxSize; //size in percentage of screen.
	vec2 BoundingBoxPosition; //position in percentage of screen.

	int TextureOffset[2];
	int TextureSize[2];

	int mode;
	int selected;

	float AdvanceX;
	float AdvanceY;
}GPU_GraphicsEffectText;
typedef struct GraphicsEffectText {
	GraphicsEffectTemplate Header;

	vec2 Size; //size in percentage of screen.
	vec3 Position; //position in percentage of screen.
	//bounding box means everything outside of it wont be rendered.
	vec2 BoundingBoxSize; //size in percentage of screen.
	vec2 BoundingBoxPosition; //position in percentage of screen.

	size_t FontSize; //text size in points
	UTF8* UTF8_Text; //text encoded in UTF-8

	//every reinit
	uint64_t GPU_GraphicsEffectInfosSize;
	GPU_GraphicsEffectText* GPU_GraphicsEffectInfos; //GPU_GraphicsEffectInfosSize

#ifdef TEX_EXPOSE_GUI
	VkPipeline VkPipeline;

	VkShaderModule VkShaderVertex;
	VkShaderModule VkShaderFragment;
#else
	void* VkPipeline;

	void* VkShaderVertex;
	void* VkShaderFragment;
#endif

	size_t iFontsSize;
	ResourceHeaderAllocation iFonts[]; //font set, collection of fonts to use
}GraphicsEffectText;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Utils
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct GUIUtils {
	struct {
		uint32_t DPI;
		uint32_t TabIndents;
	}Config;

	//Other
#ifdef TEX_EXPOSE_GUI
	FT_Library FtLibrary;
#else
	void* FtLibrary;
#endif

	//Signatures
	ResourceHeaderSignature RHeaderButtonSig;
	ResourceHeaderSignature RHeaderFontSig;

	//Effects
	GraphicsEffectSignature TextSig;
}GUIUtils;

struct GUIResStruct {
	GUIUtils* pUtils;

	void* pInitialise_GUI;
	void* pDestroy_GUI;
	void* pUpdate_GUI;

	void* pButtonClick_Callback;
	void* pKey_Callback;
	void* pCharacter_Callback;
	void* pClick_Callback;
	void* pScroll_Callback;

	void* pLoad_Font;
	void* pDestroy_Font;
}GUIRes;

//Initialise_Resources MUST be called to use the library in your dll
void GUI_Initialise_Resources(FunctionInfo*** pExternFunctions, uint64_t* pExternFunctionsSize, ResourceInfo*** pExternResources, uint64_t* pExternResourcesSize) {
	memset(&GUIRes, 0, sizeof(GUIRes));

	ResourceImport(pExternResources, pExternResourcesSize, (const UTF8*)CopyData((void*)"GUI::Utils"), &GUIRes.pUtils);
}




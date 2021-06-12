/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Triangle Engine X Format Extension

SPECIFICATION: 

 * GLTF
 * TEXIF
 * PNG
 * JPEG

 Audio: 
 * WAV


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once


//corrospond to mimetype
typedef enum TEXIConverters{
	bmp = 0x00706d62,
	dds = 0x00736464,
	png = 0x00676e70,
	jpeg = 0x6765706a,
	tga = 0x00616774,
}TEXIConverters;

typedef enum TEXAConverters{
	wav = 0x00766177
}TEXAConverters;

#ifdef TEX_EXPOSE_FORMATS

uint32_t GLTF_ExtensionsSupportedSize = 1;
const UTF8* GLTF_ExtensionsSupported[] =
{
	(const UTF8*)"KHR_lights_punctual"
};


typedef enum GLB_CHUNKTYPE
{
	GLB_CHUNKTYPE_JSON = 0x4E4F534A,
	GLB_CHUNKTYPE_BIN = 0x004E4942,
}GLB_CHUNKTYPE;

typedef struct GLB_HEADER
{
	uint32_t magic;
	uint32_t version;
	uint32_t length;
}GLB_HEADER;

typedef struct GLB_CHUNK
{
	uint32_t chunkLength;
	uint32_t chunkType;
	unsigned char chunkData[];
}GLB_CHUNK;


#pragma pack(push, 1)
//bmp
typedef enum BMP_Compression{
	BI_RGB = 0,
	BI_RLE8 = 1,
	BI_RLE4 = 2,
	BI_BITFIELDS = 3,
	BI_JPEG = 4,
	BI_PNG = 5,
	BI_ALPHABITFIELDS = 6,
	BI_CMYK = 11,
	BI_CMYKRLE8 = 12,
	BI_CMYKRLE4 = 13,
}BMP_Compression;

typedef struct BMP_HEADER
{
	char 		Signature[2];
	uint32_t	FileSize; // = 0
	uint32_t	Reserved;
	uint32_t	DataOffset; // = 54
}BMP_HEADER;


typedef struct BMP_BITMAPINFOHEADER
{
	uint32_t	Size; // 40
	uint32_t	Width; // = 0
	uint32_t	Height; // = 0
	uint16_t	Planes; // = 1
	uint16_t	BitsPerPixel;
	uint32_t	Compression; // = 0
	uint32_t	ImageSize; // = 0
	uint32_t	h_res; // = 1000
	uint32_t	v_res; // = 1000
	uint32_t	ColoursUsed; // = 0
	uint32_t	ImportantColours; // = 0
}BMP_BITMAPINFOHEADER;

typedef struct BMP_ColorTable
{
	uint8_t RGBA[][4];
}BMP_ColorTable;

typedef struct BMP_PixelData
{
	char data[];
}BMP_PixelData;


//dds
typedef enum DDS_FOURCC{
	DDS_FOURCC_DXT1 = 0x31545844,
	DDS_FOURCC_DXT2 = 0x32545844,
	DDS_FOURCC_DXT3 = 0x33545844,
	DDS_FOURCC_DXT4 = 0x34545844,
	DDS_FOURCC_DXT5 = 0x35545844,
	DDS_FOURCC_DX10 = 0x30315844, //30315844
}DDS_FOURCC;

typedef enum DDS_DDPF_FLAGS{
	DDS_DDPF_ALPHAPIXELS = 0x1,
	DDS_DDPF_ALPHA = 0x2,
	DDS_DDPF_FOURCC = 0x4,
	DDS_DDPF_RGB = 0x40,
	DDS_DDPF_YUV = 0x200,
	DDS_DDPF_LUMINANCE = 0x20000
}DDS_DDPF_FLAGS;

typedef enum DDS_FLAGS{
	DDS_FLAG_CAPS = 0x1,
	DDS_FLAG_HEIGHT = 0x2,
	DDS_FLAG_WIDTH = 0x4,
	DDS_FLAG_PITCH = 0x8,
	DDS_FLAG_PIXELFORMAT = 0x1000,
	DDS_FLAG_MIPMAPCOUNT = 0x20000,
	DDS_FLAG_LINEARSIZE = 0x80000,
	DDS_FLAG_DEPTH = 0x800000
}DDS_FLAGS;

typedef enum DDS_Caps{
	DDS_CAPS_COMPLEX = 0x8,
	DDS_CAPS_MIPMAP = 0x400000,
	DDS_CAPS_TEXTURE = 0x1000
}DDS_Caps;

typedef enum DDS_Caps2{
	DDS_CAPS2_CUBEMAP = 0x200,
	DDS_CAPS2_CUBEMAP_POSITIVEX = 0x400,
	DDS_CAPS2_CUBEMAP_NEGATIVEX = 0x800,
	DDS_CAPS2_CUBEMAP_POSITIVEY = 0x1000,
	DDS_CAPS2_CUBEMAP_NEGATIVEY = 0x2000,
	DDS_CAPS2_CUBEMAP_POSITIVEZ = 0x4000,
	DDS_CAPS2_CUBEMAP_NEGATIVEZ = 0x8000,
	DDS_CAPS2_VOLUME = 0x200000
}DDS_Caps2;

typedef enum DDS_ResourceDimension{
	DDS_DIMENSION_TEXTURE1D = 2,
	DDS_DIMENSION_TEXTURE2D = 3,
	DDS_DIMENSION_TEXTURE3D = 4
}DDS_ResourceDimension;

typedef struct DDS_DX10{
	uint32_t dxgiFormat; //convert to VKformat PLOX
	DDS_ResourceDimension resourceDimension; //3d, 2d, 1d, ETC.
	uint32_t miscFlag;
	uint32_t arraySize;
	uint32_t miscFlags2;
}DDS_DX10;

typedef struct DDS_PIXELFORMAT{
	uint32_t dwSize; // = 32
	uint32_t dwFlags; // = 4
	char dwFourCC[4]; // = 1
	uint32_t dwRGBBitCount;
	uint32_t dwRBitMask;
	uint32_t dwGBitMask;
	uint32_t dwBBitMask;
	uint32_t dwABitMask;
}DDS_PIXELFORMAT;

typedef struct DDS_HEADER
{
	char magic[4];
	uint32_t dwSize;
	uint32_t dwFlags;
	uint32_t dwHeight;
	uint32_t dwWidth;
	uint32_t dwPitchOrLinearSize;
	uint32_t dwDepth;
	uint32_t dwMipMapCount;
	uint32_t dwReserved1[11];
	DDS_PIXELFORMAT ddspf;
	DDS_Caps dwCaps;
	DDS_Caps2 dwCaps2;
	uint32_t dwCaps3;
	uint32_t dwCaps4;
	uint32_t dwReserved2;
}DDS_HEADER;

typedef struct DDS_PixelData
{
	char data[];
}DDS_PixelData;

//png
//third party atm

//jpg
//NO JPG YET

//wav
typedef struct WAV_HEADER //fixed size
{
	char ChunkID[4];
	uint32_t ChunkSize;
	char Format[4];
}WAV_HEADER;


typedef struct WAV_SubChunkHeader //fixed size //generic subchunk
{
	char SubchunkID[4];
	uint32_t SubchunkSize;
}WAV_SubChunkHeader;

typedef struct WAV_fmt  //variable sized but mostly fixed
{
	WAV_SubChunkHeader Header;
	uint16_t AudioFormat;
	uint16_t NumChannels;
	uint32_t SampleRate;
	uint32_t ByteRate;
	uint16_t BlockAlign;
	uint16_t BitsPerSample;
	//uint16_t ExtraParamSize;
}WAV_fmt;

typedef struct WAV_data //variable sized
{
	WAV_SubChunkHeader Header;
	char data[];
}WAV_data;

#pragma pack(pop)

typedef enum GL_PrimitiveMode{
	GL_PrimitiveMode_POINTS,
	GL_PrimitiveMode_LINES,
	GL_PrimitiveMode_LINE_LOOP,
	GL_PrimitiveMode_LINE_STRIP,
	GL_PrimitiveMode_TRIANGLES,
	GL_PrimitiveMode_TRIANGLE_STRIP,
	GL_PrimitiveMode_TRIANGLE_FAN
}GL_PrimitiveMode;

typedef enum GL_ComponentType{
	GL_ComponentType_BYTE = 5120,
	GL_ComponentType_UNSIGNED_BYTE = 5121,
	GL_ComponentType_SHORT = 5122,
	GL_ComponentType_UNSIGNED_SHORT = 5123,
	GL_ComponentType_INT = 5124,
	GL_ComponentType_UNSIGNED_INT = 5125,
	GL_ComponentType_FLOAT = 5126
}GL_ComponentType;

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Utils
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef TEX_EXPOSE_FORMATS
typedef struct FormatUtils{
	uint32_t pad;

}FormatUtils;
#endif

struct FormatsResStruct
{
	void* pInitialise_Formats;
	void* pDestroy_Formats;

	void* pLoad_2Dscene;
	void* pLoad_3Dscene;
}FormatsRes;

//Initialise_Resources MUST be called to use the library in your dll
void Formats_Initialise_Resources(FunctionInfo*** pExternFunctions, uint64_t* pExternFunctionsSize, ResourceInfo*** pExternResources, uint64_t* pExternResourcesSize)
{
	memset(&FormatsRes, 0, sizeof(FormatsRes));

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Formats::Load_2Dscene"), &FormatsRes.pLoad_2Dscene);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Formats::Load_3Dscene"), &FormatsRes.pLoad_3Dscene);
}

TEXRESULT Formats_Ref_Load_2Dscene(const UTF8* Path, RHeaderGraphicsWindow* pGraphicsWindow, RHeaderScene* pScene, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(const UTF8 * Path, RHeaderGraphicsWindow * pGraphicsWindow, RHeaderScene * pScene, uint32_t ThreadIndex) =
		(TEXRESULT(*)(const UTF8 * Path, RHeaderGraphicsWindow * pGraphicsWindow, RHeaderScene * pScene, uint32_t ThreadIndex))FormatsRes.pLoad_2Dscene;

	return function(Path, pGraphicsWindow, pScene, ThreadIndex);
}

TEXRESULT Formats_Ref_Load_3Dscene(const UTF8* Path, RHeaderGraphicsWindow* pGraphicsWindow, RHeaderScene* pScene, uint32_t ThreadIndex)
{
	TEXRESULT(*function)(const UTF8 * Path, RHeaderGraphicsWindow * pGraphicsWindow, RHeaderScene * pScene, uint32_t ThreadIndex) =
		(TEXRESULT(*)(const UTF8 * Path, RHeaderGraphicsWindow * pGraphicsWindow, RHeaderScene * pScene, uint32_t ThreadIndex))FormatsRes.pLoad_3Dscene;

	return function(Path, pGraphicsWindow, pScene, ThreadIndex);
}






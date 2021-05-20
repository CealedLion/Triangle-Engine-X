/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

* include this header if you want to make a triangle engine extension

* Extension structs

SPECIFICATION: 

* EngineUtils are exported under "Engine::Utils"

* All Functions in this game engine if have a array in their arguments will copy it if 
it needs to.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Enums
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Triangle Engine X Result
*/
typedef enum TEXRESULT{
	Success = 0x0,
	Failure = 0x1,
	Invalid_Format = 0x2,
	Invalid_Parameter = 0x4, 
	Resize_Array_Result = 0x200, //resize the respective array
	Out_Of_Memory_Result = 0x400,
	Timeout = 0x800,
	Busy = 0x1000,
}TEXRESULT;

/*
* Added in 1.0.0
* Specify When a function is called.
*/
typedef enum CallFlagBits{
	NoCall =			0x00000000, //nocall duh
	Construct =			0x00000001, //called in initialisation
	Destruct =			0x00000002, //called in desctrucion
	EveryFrame =		0x00000004, //called every frame
	//various input types
	Key_Input =			0x00000008, //when a keyboard is pressed
	Character_Input =	0x00000010, //typing input, like keyboard press but for texting
	MouseButton_Input = 0x00000020, //when a mouse button is pressed
	MousePos_Input =	0x00000040, //when a mouse moves
	MouseEnter_Input =	0x00000080, //when a mouse is hovering over window
	Scroll_Input =		0x00000100, //when a scroll wheel is scrolled
	//connection callback types
	Joystick_Connect =  0x00000400, //when a joystick is connected/disconnected
	Monitor_Connect =	0x00001000, //when a monitor is connected/disconnected
	//window callback types
	Drop_Input =		0x00002000, //when a dragged path is dropped onto a window.
	Window_Resize =		0x00004000, //when a window is resized.
	FrameBuffer_Resize =0x00008000, //when a framebuffer is resized.
	Window_Refresh =	0x00010000, //when a window needs to be refreshed, such as if it is uncovered after being covered by another window.
	Window_Move =		0x00020000, //when a window is dragged/moved.
	Window_Minimise =	0x00040000, //when a window is minimised/iconified. 
	Window_Focused =	0x00080000, //when a window gains focus.
	Window_Close =		0x00100000, //when a window is closed.
	Window_Open =		0x00200000, //when a window is Opened.
	//end
	CallFlags_MAX = 0x00100000
}CallFlagBits;

/*
* Added in 1.0.0
* Inbuilt Multithreading
* You can obviously do multithreading yourself, but this is for multithreading scheduled functions mainly.
*/
typedef enum FunctionThreadingMode{
	Single_Thread =	0,
	Multi_Thread =	1
}FunctionThreadingMode;

/*
* Added in 1.0.0
* Engine Binary Type, Used to make sure all extensions are compiled with the same setting.
*/
typedef enum BinaryType{
	Debug =		1,
	Release =	2
}BinaryType;

/*
* Added in 1.0.0
* Keys State
*/
typedef enum KeyState{
	KeyRelease = 0,
	KeyPress = 1,
	KeyRepeat = 2 //when a key is pressed for more then 1 frames
}KeyState;

/*
* Added in 1.0.0
* Key Indexes
*/
typedef enum Keys{
	//The unknown key
	KEY_UNKNOWN,
	//Printable keys
	KEY_SPACE,
	KEY_APOSTROPHE,
	KEY_COMMA,
	KEY_MINUS,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_SEMICOLON,
	KEY_PLUS,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_LEFT_BRACKET,
	KEY_BACKSLASH,
	KEY_RIGHT_BRACKET,
	KEY_GRAVE_ACCENT,
	KEY_WORLD_1,// non-US #1
	KEY_WORLD_2, // non-US #2 
	// Function keys 
	KEY_ESCAPE,
	KEY_ENTER,
	KEY_TAB,
	KEY_BACKSPACE,
	KEY_INSERT,
	KEY_DELETE,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_DOWN,
	KEY_UP,
	KEY_PAGE_UP,
	KEY_PAGE_DOWN,
	KEY_HOME,
	KEY_END,
	KEY_CAPS_LOCK,
	KEY_SCROLL_LOCK,
	KEY_NUM_LOCK,
	KEY_PRINT_SCREEN,
	KEY_PAUSE,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_F13,
	KEY_F14,
	KEY_F15,
	KEY_F16,
	KEY_F17,
	KEY_F18,
	KEY_F19,
	KEY_F20,
	KEY_F21,
	KEY_F22,
	KEY_F23,
	KEY_F24,
	KEY_F25,
	KEY_KP_0,
	KEY_KP_1,
	KEY_KP_2,
	KEY_KP_3,
	KEY_KP_4,
	KEY_KP_5,
	KEY_KP_6,
	KEY_KP_7,
	KEY_KP_8,
	KEY_KP_9,
	KEY_KP_DECIMAL,
	KEY_KP_DIVIDE,
	KEY_KP_MULTIPLY,
	KEY_KP_SUBTRACT,
	KEY_KP_ADD,
	KEY_KP_ENTER,
	KEY_LEFT_SHIFT,
	KEY_LEFT_CONTROL,
	KEY_LEFT_ALT,
	KEY_LEFT_SUPER,
	KEY_RIGHT_SHIFT,
	KEY_RIGHT_CONTROL,
	KEY_RIGHT_ALT,
	KEY_RIGHT_SUPER,
	KEY_MENU,

	KEY_LAST = KEY_MENU
}Key;

/*
* Added in 1.0.0
*/
typedef enum MouseButtons{
	MOUSE_BUTTON_1 = 0,
	MOUSE_BUTTON_2 = 1,
	MOUSE_BUTTON_3 = 2,
	MOUSE_BUTTON_4 = 3,
	MOUSE_BUTTON_5 = 4,
	MOUSE_BUTTON_6 = 5,
	MOUSE_BUTTON_7 = 6,
	MOUSE_BUTTON_8 = 7,
	MOUSE_BUTTON_LAST = MOUSE_BUTTON_8,
	MOUSE_BUTTON_LEFT = MOUSE_BUTTON_1,
	MOUSE_BUTTON_RIGHT = MOUSE_BUTTON_2,
	MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3,
	MOUSE_BUTTON_X1 = MOUSE_BUTTON_4,
	MOUSE_BUTTON_X2 = MOUSE_BUTTON_5,
}MouseButton;
/*
* Added in 1.0.0
* Specifies the index of the joystick
* 16 max concurrent joysticks.
*/
typedef enum Joystick{
	JOYSTICK_1 = 0,
	JOYSTICK_2 = 1,
	JOYSTICK_3 = 2,
	JOYSTICK_4 = 3,
	JOYSTICK_5 = 4,
	JOYSTICK_6 = 5,
	JOYSTICK_7 = 6,
	JOYSTICK_8 = 7,
	JOYSTICK_9 = 8,
	JOYSTICK_10 = 9,
	JOYSTICK_11 = 10,
	JOYSTICK_12 = 11,
	JOYSTICK_13 = 12,
	JOYSTICK_14 = 13,
	JOYSTICK_15 = 14,
	JOYSTICK_16 = 15,
	JOYSTICK_LAST = JOYSTICK_16
}Joystick;

/*
* Added in 1.0.0
* Connected and disconnected physically from the PC (usually).
*/
typedef enum ConnectionEvents
{
	CONNECTED = 0x00040001,
	DISCONNECTED = 0x00040002
}ConnectionEvent;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Structs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define KibiBytes(count) (count * ((uint64_t)1024))    
#define MebiBytes(count) (count * ((uint64_t)1024 * (uint64_t)1024))    
#define GibiBytes(count) (count * ((uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024))    
#define TebiBytes(count) (count * ((uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024))    
#define PebiBytes(count) (count * ((uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024))   
#define ExbiBytes(count) (count * ((uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024)) 

#define KiloBytes(count) (count * ((uint64_t)1000))    
#define MegaBytes(count) (count * ((uint64_t)1000 * (uint64_t)1000))    
#define GigaBytes(count) (count * ((uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000))    
#define TeraBytes(count) (count * ((uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000))    
#define PetaBytes(count) (count * ((uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000))   
#define ExaBytes (count) (count * ((uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000))   


#define ToKibiBytes(count) (count / ((uint64_t)1024))    
#define ToMebiBytes(count) (count / ((uint64_t)1024 * (uint64_t)1024))    
#define ToGibiBytes(count) (count / ((uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024))    
#define ToTebiBytes(count) (count / ((uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024))    
#define ToPebiBytes(count) (count / ((uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024))   
#define ToExbiBytes(count) (count / ((uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024 * (uint64_t)1024)) 

#define ToKiloBytes(count) (count / ((uint64_t)1000))    
#define ToMegaBytes(count) (count / ((uint64_t)1000 * (uint64_t)1000))    
#define ToGigaBytes(count) (count / ((uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000))    
#define ToTeraBytes(count) (count / ((uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000))    
#define ToPetaBytes(count) (count / ((uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000))   
#define ToExaBytes (count) (count / ((uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000))   


#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

typedef struct FileData
{
	uint64_t LinearSize;
	void* pData;
}FileData;

typedef enum DataType
{
	Undefined,
	SignedInt,
	UnsignedInt,
	SignedFloat,
	UnsignedFloat
}DataType;

typedef enum AccessorType { //acessor type enum = size of element in elements
	AccessorType_SCALAR = 1,
	AccessorType_VEC2 = 2,
	AccessorType_VEC3 = 3,
	AccessorType_VEC4 = 4,
	AccessorType_MAT2 = 4,
	AccessorType_MAT3 = 9,
	AccessorType_MAT4 = 16,
}AccessorType;

/*
* Unicode UTF8 string, the standard encoding for Triangle Engine X.
*/
typedef unsigned char UTF8;
/*
* Unicode UTF16 Little Endian string, Standard in Microsoft Windows.
*/
typedef uint16_t UTF16;
/*
* Unicode UTF32 Little Endian string.
*/
typedef uint32_t UTF32;

/*
* Mutex types 
*/
typedef enum MutexType
{
	MutexType_Plain = 0,
	MutexType_Timed = 1,
	MutexType_Recursive = 2,
}MutexType;


typedef char Mutex[56];//big enough to fit windows and linux mutex
typedef char Condition[64]; //big enough to fit windows and linux condition
typedef void Thread;


/** Thread start function.
* Any thread that is started with the @ref thrd_create() function must be
* started through a function of this type.
* @param arg The thread argument (the @c arg argument of the corresponding
*        @ref thrd_create() call).
* @return The thread return value, which can be obtained by another thread
* by using the @ref thrd_join() function.
*/
typedef int (*thrd_start_t)(void* arg);

/** Destructor function for a thread-specific storage.
* @param val The value of the destructed thread-specific storage.
*/
typedef void (*tss_dtor_t)(void* val);
/*
#ifdef _TEX_WIN32_
typedef struct {
	LONG volatile status;
	CRITICAL_SECTION lock;
} once_flag;
#define ONCE_FLAG_INIT {0,}
#else
#define once_flag pthread_once_t
#define ONCE_FLAG_INIT PTHREAD_ONCE_INIT
#endif
*/


typedef struct FormatDetails
{
	uint64_t ChannelCount;
	uint64_t Stride; //amount of bits in total from 1 element to the next

	//these shouldnt be freed! they should be all just pointers to a static array

	DataType* ChannelTypes;//pointer to channel types object
	char* ChannelNames; //pointer to channel indentifiers object
	uint8_t* BitsPerChannel; //pointer to bits per channel object
}FormatDetails;

uint64_t AlignNumber(uint64_t number, uint64_t alignment)
{
	return (number & -(int64_t)alignment) < number ?
		(number & -(int64_t)alignment) + alignment : (number & -(int64_t)alignment);
}

int memsize(int i)
{
	int size = 1;

	if (i > 255)
		size = 2;
	else if (i > 65535)
		size = 3;
	else if (i > 2147483647)
		size = 4;
	return size;
}

void memset64(void* dest, uint64_t value, uintptr_t size)
{
	uintptr_t i;
	for (i = 0; i < (size & (~7)); i += 8)
	{
		memcpy(((char*)dest) + i, &value, 8);
	}
	for (; i < size; i++)
	{
		((char*)dest)[i] = ((char*)&value)[i & 7];
	}
}

uint16_t swap_uint16(uint16_t val)
{
	return (val << 8) | (val >> 8);
}

//! Byte swap short
int16_t swap_int16(int16_t val)
{
	return (val << 8) | ((val >> 8) & 0xFF);
}

//! Byte swap unsigned int
uint32_t swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

//! Byte swap int
int32_t swap_int32(int32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | ((val >> 16) & 0xFFFF);
}

int64_t swap_int64(int64_t val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
	return (val << 32) | ((val >> 32) & 0xFFFFFFFFULL);
}

uint64_t swap_uint64(uint64_t val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
	return (val << 32) | (val >> 32);
}

/*
 * bit shifts entire array
 * amount of bits shift must be less then array size.
*/
void bitshiftR_array(uint8_t* pData, const uint32_t datasize, const uint32_t bits)
{
	int64_t bytes = bits / 8;
	int64_t bitsp = bits % 8;

	for (int64_t i = 0; i < (int64_t)(datasize - (2 + bytes)); i++)
	{
		pData[i] = (uint8_t)(pData[(int64_t)i + (int64_t)(bytes)] >> bitsp | pData[(int64_t)i + (int64_t)(1 + bytes)] << ((int64_t)8 - (int64_t)bitsp));
	}
	pData[(int64_t)datasize - (int64_t)(1 + bytes)] = pData[(int64_t)datasize - (int64_t)(1)] >> bitsp;
	for (size_t i = 0; i < (uint64_t)bytes; i++)
	{
		pData[(int64_t)datasize - (int64_t)(1 + i)] = 0;
	}
}

/*
 * bit shifts entire array
 * amount of bits shift must be less then array size.
*/
void bitshiftL_array(uint8_t* pData, const uint32_t datasize, const uint32_t bits)
{
	uint64_t bytes = bits / 8;
	uint64_t bitsp = bits % 8;

	for (int64_t i = datasize - 1; i >= (int64_t)((int64_t)1 + (int64_t)bytes); i--)
	{
		pData[i] = (uint8_t)(pData[(int64_t)i - (int64_t)(bytes)] << bitsp | pData[(int64_t)i - (int64_t)(1 + bytes)] >> ((int64_t)8 - (int64_t)bitsp));
	}
	pData[(int64_t)bytes] = pData[0] << bitsp;
	for (size_t i = 0; i < (uint64_t)bytes; i++)
	{
		pData[(int64_t)i] = 0;
	}
}



TEXRESULT Open_Data(FileData* filedata, const UTF8* path)
{

	FILE* file = fopen((char*)path, "rb"); //open file
	if (file == NULL)
	{
		return (TEXRESULT)(Invalid_Parameter | Failure);
	}
	fseek(file, 0, SEEK_END); //find end of file
	filedata->LinearSize = ftell(file); //ftell returns position of seeker and hence size of file
	rewind(file); //back to start
	filedata->pData = (unsigned char*)malloc(sizeof(unsigned char) * filedata->LinearSize + 1); //allocate enough memory +1 for file ending

	fread(filedata->pData, (size_t)filedata->LinearSize, 1, file); //insert pData into memory

	((char*)filedata->pData)[filedata->LinearSize] = '\0'; //add line ending

	filedata->LinearSize += 1;
	fclose(file);

	return Success;

}

TEXRESULT Save_data(FileData* filedata, const UTF8* path)
{

	FILE* file = fopen((char*)path, "wb"); //open file
	if (file == NULL)
		return (TEXRESULT)(Invalid_Parameter | Failure);


	fwrite(filedata->pData, sizeof(unsigned char), filedata->LinearSize, file);

	fclose(file);

	return Success;
}

void Resize_Array(void** buffer, uint64_t oldsize, uint64_t newsize, uint64_t membersize)
{
	void* oldarray = *buffer;
	void* TempArray = calloc(newsize, membersize);
	if (oldarray != NULL)
	{	
		memcpy(TempArray, oldarray, membersize * min(newsize, oldsize)); //only copy amount of smaller to keep from overflows
		free(oldarray);
	}
	//assign new array to old array
	*buffer = TempArray;
}

void RemoveMember_Array(void** buffer, uint64_t oldsize, uint64_t memberindex, uint64_t membersize, uint64_t membercount)
{
	void* oldarray = *buffer;

	uint64_t newsize = oldsize - membercount;


	if (newsize != 0)
	{
		void* TempArray = calloc(newsize, membersize);

		if (memberindex != NULL) //copy first part of array
			memcpy(TempArray, oldarray, membersize * memberindex);

		if (oldarray != NULL) //copy second part of array and offset it
		{
			memcpy((void*)((uint64_t)TempArray + (uint64_t)(memberindex * membersize)), (void*)((uint64_t)oldarray + (uint64_t)((memberindex + membercount) * membersize)), membersize * (newsize - memberindex));
		}

		//assign new array to old array
		*buffer = TempArray;
	}
	if (oldarray != NULL)
	{
		free(oldarray);
	}
}

void InsertMember_Array(void** buffer, uint64_t oldsize, uint64_t memberindex, uint64_t membersize, void* members, uint64_t membercount)
{
	void* oldarray = *buffer;
	void* TempArray = calloc(oldsize + membercount, membersize);


	if (memberindex != NULL) //copy first part of array
		memcpy(TempArray, oldarray, membersize * memberindex);

	if (oldarray != NULL)  //copy second part of array and offset it
	{
		memcpy((void*)((uint64_t)TempArray + (uint64_t)((memberindex + membercount) * membersize)), (void*)((uint64_t)oldarray + (uint64_t)(memberindex * membersize)), membersize * (oldsize - memberindex));
		free(oldarray);
	}

	if (members != NULL)
		memcpy((void*)((uint64_t)TempArray + (uint64_t)(memberindex * membersize)), members, membersize * membercount);

	//assign new array to old array
	*buffer = TempArray;
}



/*
typedef struct Palette
{
	const char* pData;
	uint32_t size; // size in bytes
	VkFormat format;
}Palette;
*/


/*
 * src is the paletted image.
 * srcformatbits is the bit precision of the src, can be anything.
 * dst is the product
 * output image is based on the format of the palette
 * supports everything but compressed formats where you should decompress first.
*/
/*
uint32_t Decompress_PalettedData(FileData* src, FileData* dst, uint32_t srcformatbits, Palette* palette)
{
	uint32_t paletteStride = Resolve_VKFormatStride(palette->format);

	uint32_t srcComponents = ((src->LinearSize * 8) / srcformatbits);

	dst->LinearSize = (srcComponents * paletteStride); //make it same precision as the palette

	dst->pData = (unsigned char*)malloc(sizeof(uint8_t) * dst->LinearSize);

	uint64_t mask = 0;
	for (size_t i = 0; i < srcformatbits; i++)
		mask = mask | (uint64_t)pow(2, i);

	uint32_t srciter = 0; //srciterator in bits


	uint64_t* index = (uint64_t*)malloc(sizeof(uint64_t));

	uint64_t sizebytes = 0;
	sizebytes = srcformatbits / 8; //this isnt the best solution.
	if (sizebytes == 0)
		sizebytes = 1;

	for (size_t i = 0; i < srcComponents; i++)
	{
		uint64_t indexer = (srciter / 8);

		//it could be much faster if i can find another solution for the intermediate buffer
		index[0] = (uint64_t)NULL;
		memcpy(index, &src->pData[indexer], sizebytes);

		index[0] = indexer >> (srciter % 8);

		memcpy(&dst->pData[(i)	* paletteStride], &palette->pData[mask & *index], paletteStride);

		srciter += srcformatbits;
	}

	free(index);

	return 0;
}

uint32_t Decompress_Data()
{

	return 0;
}

uint32_t Recompress_Data()
{

	return 0;
}
*/


/*
 * Can Convert ALL datatypes, float to int, etc whatever.
 * Can convert packed formats too. and pack them back.
 * Cannot do compressed formats, decompress first.
 * max value per channel 64 bit
*/
TEXRESULT Convert_Data(FileData* src, FormatDetails* srcdetails, FormatDetails* dstdetails)
{
	uint8_t srcstridebytes = srcdetails->Stride / 8;
	uint8_t srcstridebits = srcdetails->Stride % 8;
	uint8_t dststridebytes = dstdetails->Stride / 8;
	uint8_t dststridebits = dstdetails->Stride % 8;

	uint64_t srcComponents = ((src->LinearSize * 8) / (srcdetails->Stride)); //we care about all the channels


	FileData dst;
	dst.LinearSize = ((uint64_t)srcComponents * ((uint64_t)dstdetails->Stride / ((uint64_t)8))) + ((uint64_t)1);
	dst.pData = (unsigned char*)malloc(dst.LinearSize);

	uint64_t* srcmasks = (uint64_t*)calloc(sizeof(uint64_t), srcdetails->ChannelCount);
	uint64_t* dstmasks = (uint64_t*)calloc(sizeof(uint64_t), srcdetails->ChannelCount);

	uint64_t* bitshiftLs = (uint64_t*)calloc(sizeof(uint64_t), srcdetails->ChannelCount);
	uint64_t* bitshiftRs = (uint64_t*)calloc(sizeof(uint64_t), srcdetails->ChannelCount);

	uint8_t* srcoffsets = (uint8_t*)calloc(sizeof(uint8_t), srcdetails->ChannelCount);
	uint8_t* dstoffsets = (uint8_t*)calloc(sizeof(uint8_t), srcdetails->ChannelCount);

	uint8_t* channelindex = (uint8_t*)calloc(sizeof(uint8_t), srcdetails->ChannelCount);


	for (size_t i = 0; i < srcdetails->ChannelCount; i++)
	{
		bitshiftRs[i] = ((srcdetails->BitsPerChannel[i] - dstdetails->BitsPerChannel[i]) > 0) ? (srcdetails->BitsPerChannel[i] - dstdetails->BitsPerChannel[i]) : 0;
		bitshiftLs[i] = ((dstdetails->BitsPerChannel[i] - srcdetails->BitsPerChannel[i]) > 0) ? (dstdetails->BitsPerChannel[i] - srcdetails->BitsPerChannel[i]) : 0;

		switch (srcdetails->ChannelTypes[i])
		{
		case SignedInt:
			srcmasks[i] = (uint64_t)1 << (uint64_t)(srcdetails->BitsPerChannel[i] - 1);
			break;
		case UnsignedInt:
			srcmasks[i] = 0;
			break;
		case SignedFloat:
			return (TEXRESULT)(Invalid_Parameter | Failure);
		case UnsignedFloat:
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}

		for (size_t i1 = 0; i1 < dstdetails->ChannelCount; i1++)
		{
			if (srcdetails->ChannelNames[i] == dstdetails->ChannelNames[i1])
			{
				//channelindex[i] = i1;
				//channelindex[i] =  (i1); //remember its little endian so back to front
				dstoffsets[i] = srcdetails->BitsPerChannel[i];
				for (size_t i3 = 0; i3 < i1; i3++)
					srcoffsets[i] += srcdetails->BitsPerChannel[i3];
			}

		}
		channelindex[i] = i;
	}


	//channelindex[0] = 3;
	//channelindex[1] = 2;
	//channelindex[2] = 1;
	//channelindex[3] = 0;

	for (size_t i = 0; i < dstdetails->ChannelCount; i++)
	{
		switch (dstdetails->ChannelTypes[i])
		{
		case SignedInt:
			dstmasks[i] = (uint64_t)1 << (uint64_t)(dstdetails->BitsPerChannel[i] - 1);
			break;
		case UnsignedInt:
			dstmasks[i] = 0;
			break;
		case SignedFloat:
			return (TEXRESULT)(Invalid_Parameter | Failure);
		case UnsignedFloat:
			return (TEXRESULT)(Invalid_Parameter | Failure);
		}
	}

	uint8_t* buffer = (uint8_t*)malloc(sizeof(uint8_t) * srcstridebytes);
	uint64_t sample = 0;
	uint32_t channels = min(srcdetails->ChannelCount, dstdetails->ChannelCount);

	for (size_t i = 0; i < srcComponents; i++)
	{
		uint8_t* srcdata = &((uint8_t*)src->pData)[(i * srcstridebytes)];
		uint8_t* dstdata = &((uint8_t*)dst.pData)[(i * dststridebytes)];

		uint32_t bits = (i * srcdetails->Stride) % 8;

		for (size_t i1 = channels; i1-- > 0; )
		{
			bitshiftL_array(dstdata, srcstridebytes, dstoffsets[channelindex[i1]]); //bit shift the pData to the back 

			uint64_t mask = UINT64_MAX << ((srcdetails->BitsPerChannel[channelindex[i1]])); //mask will be inverteed

			memcpy(buffer, &srcdata[(srcoffsets[channelindex[i1]] / 8)], srcstridebytes); //copy to buffer to avoid overflow

			//bitshiftR_array(buffer, srcstridebytes, srcoffsets[channelindex[i1]]); //bit shift to front % 8) + bits
			//needs to be other way aruound
			sample = *((uint64_t*)buffer);

			sample = ~mask & sample; //mask off
			sample = sample + srcmasks[channelindex[i1]]; //remove sign or nothing
			sample = sample << bitshiftLs[channelindex[i1]];
			sample = sample >> bitshiftRs[channelindex[i1]];
			sample = sample - dstmasks[channelindex[i1]]; //add sign or nothing'

			*((uint64_t*)dstdata) = *((uint64_t*)dstdata) | (sample);
		}
	}

	((char*)dst.pData)[dst.LinearSize - 1] = '\0';

	free(srcmasks);
	free(dstmasks);


	free(bitshiftLs);
	free(bitshiftRs);

	free(srcoffsets);
	free(dstoffsets);

	free(buffer);


	free(src->pData);
	src->pData = dst.pData;
	src->LinearSize = dst.LinearSize;

	return Success;
}


void* CopyData(void* src)
{
	uint64_t len = strlen((char*)src);

	void* newalloc = (char*)malloc(len + (uint64_t)1);
	memcpy(newalloc, src, len);
	((char*)newalloc)[len] = '\0';

	return newalloc;
}



uint64_t Find_first_of(const UTF8* src, const UTF8* tofind)
{
	uint64_t lastpos = 0;
	uint64_t srclen = strlen((char*)src);
	uint64_t tofindlen = strlen((char*)tofind);

	for (size_t i = 0; i < srclen; i++)
		if (strncmp((char*)(src + i), (char*)tofind, tofindlen) == 0)
			return i;

	return UINT64_MAX;
}


uint64_t Find_last_of(const UTF8* src, const UTF8* tofind)
{
	uint64_t lastpos = 0;
	uint64_t srclen = strlen((char*)src);
	uint64_t tofindlen = strlen((char*)tofind);

	for (size_t i = 0; i < srclen; i++)
		if (strncmp((char*)(src + i), (char*)tofind, tofindlen) == 0)
			lastpos = i;

	return lastpos;
}

const UTF8* Get_FilePathExtension(const UTF8* filename)
{
	uint64_t lastof = Find_last_of(filename, (UTF8*)".");
	uint64_t filenamelen = strlen((char*)filename);

	if (lastof < filenamelen)
	{
		UTF8* newstring = (UTF8*)malloc(sizeof(UTF8) * ((filenamelen - lastof) + (uint64_t)1));
		memcpy((void*)newstring, filename + lastof, sizeof(UTF8) * ((filenamelen - lastof) + (uint64_t)1));
		newstring[(filenamelen - lastof)] = '\0';
		return  newstring;
	}

	return (UTF8*)" ";
}

const UTF8* Get_FilePathRoot(const UTF8* filename)
{
	uint64_t lastof = Find_last_of(filename, (UTF8*)"\\") + (uint64_t)1;
	uint64_t filenamelen = strlen((char*)filename);

	if (lastof < filenamelen)
	{
		UTF8* newstring = (UTF8*)malloc(sizeof(UTF8) * (lastof + (uint64_t)1));
		memcpy((void*)newstring, filename, sizeof(UTF8) * (lastof + (uint64_t)1));
		newstring[lastof] = '\0';
		return  newstring;
	}

	return (UTF8*)" ";
}


const UTF8* FindAndReplace(const UTF8* src, const UTF8* toreplace, const UTF8* replacement)
{
	//dont compute it more then once lol
	uint64_t srclen = strlen((char*)src);
	uint64_t toreplacelen = strlen((char*)toreplace);
	uint64_t replacementlen = strlen((char*)replacement);

	UTF8* temp = (UTF8*)malloc(sizeof(UTF8) * (srclen * replacementlen));

	uint64_t trueit = 0;
	uint64_t srcit = 0;

	while (srcit < srclen)
	{
		if (strncmp((char*)(src + srcit), (char*)toreplace, toreplacelen) == 0)
		{
			memcpy((void*)(temp + trueit), replacement, replacementlen);
			trueit += replacementlen;
			srcit += toreplacelen;
		}
		else
		{
			temp[trueit] = src[srcit];
			srcit++;
			trueit++;
		}
	}

	UTF8* finalal = (UTF8*)malloc(sizeof(UTF8) * (srcit + 1));
	memcpy(finalal, temp, sizeof(UTF8) * (srcit));
	finalal[srcit] = '\0';

	free(temp);

	return finalal;
}


static const char trailingBytesForUTF8[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

static const UTF32 offsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,  0x03C82080UL, 0xFA082080UL, 0x82082080UL };
static const UTF8 firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

#define UNI_REPLACEMENT_CHAR (UTF32)0x0000FFFD
#define UNI_MAX_BMP (UTF32)0x0000FFFF
#define UNI_MAX_UTF16 (UTF32)0x0010FFFF
#define UNI_MAX_UTF32 (UTF32)0x7FFFFFFF
#define UNI_MAX_LEGAL_UTF32 (UTF32)0x0010FFFF

static bool isLegalUTF8(const UTF8* source, uint64_t length) {
	UTF8 a;
	const UTF8* srcptr = source + length;
	switch (length) {
	default: return false;
		/* Everything else falls through when "true"... */
	case 4: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
	case 3: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
	case 2: if ((a = (*--srcptr)) > 0xBF) return false;

		switch ((unsigned char)*source) {
			/* no fall-through in this inner switch */
		case 0xE0: if (a < 0xA0) return false; break;
		case 0xED: if (a > 0x9F) return false; break;
		case 0xF0: if (a < 0x90) return false; break;
		case 0xF4: if (a > 0x8F) return false; break;
		default:   if (a < 0x80) return false;
		}

	case 1: if (*source >= 0x80 && *source < 0xC2) return false;
	}
	if (*source > 0xF4) return false;
	return true;
}

uint64_t UTF32strlen(UTF32* UTF32_Text)
{
	uint64_t i = NULL;
	while (UTF32_Text[i] != '\0')
		i++;
	return i;
}


TEXRESULT UTF8_To_UTF32(UTF8* src, UTF32** dst)
{
	uint64_t srclen = strlen((char*)src) + 1;

	UTF8* source = src;
	UTF8* sourceend = (UTF8*)((uint64_t)src + srclen);

	*dst = (UTF32*)calloc(srclen, sizeof(UTF32));
	UTF32* target = *dst;


	while (source < sourceend)
	{
		unsigned short extraBytesToRead = trailingBytesForUTF8[*source];

		UTF32 ch = NULL;

		switch (extraBytesToRead) {
		case 5: ch += *source++; ch <<= 6;
		case 4: ch += *source++; ch <<= 6;
		case 3: ch += *source++; ch <<= 6;
		case 2: ch += *source++; ch <<= 6;
		case 1: ch += *source++; ch <<= 6;
		case 0: ch += *source++;
		}

		ch -= offsetsFromUTF8[extraBytesToRead];
		*target++ = ch;
	}

	return Success;
}

TEXRESULT UTF32_To_UTF8(UTF32* src, UTF8** dst)
{
	uint64_t i11 = NULL;
	while (src[i11] != '\0')
	{
		i11++;
	}
	*dst = (UTF8*)malloc((i11 * 8) + 1);
	UTF8* target = *dst;
	UTF32* source = src;
	for (size_t i = 0; i < i11; i++)
	{
		UTF32 ch;
		unsigned short bytesToWrite = 0;
		const UTF32 byteMask = 0xBF;
		const UTF32 byteMark = 0x80;
		ch = *source++;
		/*
		 * Figure out how many bytes the result will require. Turn any
		 * illegally large UTF32 things (> Plane 17) into replacement chars.
		 */
		if (ch < (UTF32)0x80) {
			bytesToWrite = 1;
		}
		else if (ch < (UTF32)0x800) {
			bytesToWrite = 2;
		}
		else if (ch < (UTF32)0x10000) {
			bytesToWrite = 3;
		}
		else if (ch <= UNI_MAX_LEGAL_UTF32) {
			bytesToWrite = 4;
		}
		else {
			bytesToWrite = 3;
			ch = UNI_REPLACEMENT_CHAR;
		}

		target += bytesToWrite;
		switch (bytesToWrite) { /* note: everything falls through. */
		case 4: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
		case 3: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
		case 2: *--target = (UTF8)((ch | byteMark) & byteMask); ch >>= 6;
		case 1: *--target = (UTF8)(ch | firstByteMark[bytesToWrite]);
		}
		target += bytesToWrite;
	}
	*target = '\0';
	return Success;
}



/*
* Added in 1.0.0
* exports or imports a resource
* If *ppResource == NULL it will be a import and the resolver will try to fill it with a valid item.
* If *ppResource is valid then it will send the item to the gameengine and can be used universally across all extensions.
*/
typedef struct ResourceInfo{
	const UTF8* Name; //name of the resource 
	void** ppResource; //pointer to the pointer of a resource
}ResourceInfo;

/*
* Added in 1.0.0
* exports or imports a function
* If *ppFunction == NULL it will be a import and the resolver will try to fill it with a valid item.
* If *ppFunction is valid then it will send the item to the gameengine and can be used universally across all extensions.
*/
typedef struct FunctionInfo{
	const UTF8* Name; //name of the function
	void** ppFunction; //pointer to a pointer of a function

	CallFlagBits CallFlags;
	FunctionThreadingMode ThreadMode;
	float Priority; //lower priority runs first

	uint64_t NumArgs; //param size
	ResourceInfo* Args; //pointer to a array of requests
}FunctionInfo;


/*
* Added in 1.0.0
* to export for universal config system
* Can be updated with Apply_Config()
*/
typedef struct ConfigParameterInfo{
	void* pParameter;
	uint64_t ByteLength; //byte length per array element
	uint64_t ArrayElementsCount;
	const UTF8* Name;
}ConfigParameterInfo;

/*
* Added in 1.0.0
*/
typedef uint64_t ExtensionAllocation;

/*
* Added in 1.0.0
* Used in the extension to create one from a DLL
*/
typedef struct ExtensionCreateInfo
{
	FunctionInfo** pFunctions; //array of pointers to functioninfos  //do not destroy it will be used directly in engine //destructed by engine automatically
	uint64_t pFunctionsSize;
	ResourceInfo** pResources; //array of pointers to resourceinfos //do not destroy it will be used directly in engine //destructed by engine automatically
	uint64_t pResourcesSize;

	uint32_t ExtensionVersion[3]; //version of the extension itself
	uint32_t MinRequiredVersion[3]; //highest versions that the extension is compatible with.
	uint32_t MaxRequiredVersion[3]; //lowest versions that the extension is compatible with.

	BinaryType BinType; //if it was built for debug or release

	uint64_t ConfigParametersSize;
	ConfigParameterInfo* ConfigParameters; //do not destroy it will be used directly in engine //destructed by engine automatically
}ExtensionCreateInfo;

/*
* Added in 1.0.0
* Used internally by the game engine to load extensions
*/
typedef struct ExtensionDataCreateInfo
{
	const char* Name;
}ExtensionDataCreateInfo;
typedef struct ExtensionData
{
	ExtensionAllocation Allocation;
	uint64_t AllocationSize;
	const UTF8* Name;
	void* handle; //handle to windows DLL or linux DLL
	FunctionInfo** pFunctions; //array of pointers to functioninfos structs
	uint64_t pFunctionsSize;
	ResourceInfo** pResources;  //array of pointers to resource structs
	uint64_t pResourcesSize;

	uint32_t ExtensionVersion[3]; //version of the extension itself
	uint32_t MinRequiredVersion[3]; //highest versions that the extension is compatible with.
	uint32_t MaxRequiredVersion[3]; //lowest versions that the extension is compatible with.

	BinaryType BinType; //if it was built for debug or release

	uint64_t ConfigParametersSize;
	ConfigParameterInfo* ConfigParameters; //do not destroy it will be used directly in engine //destructed by engine automatically
}ExtensionData;

/*
* Added in 1.0.0
* Used internally by the game engine to store extensions
*/
typedef struct ExtensionDataBuffer
{
	Mutex mutex;
	uint64_t PrevPointer;
	uint64_t Max;
	ExtensionData* Buffer;
}ExtensionDataBuffer;

/*
* Added in 1.0.0
*/
typedef struct MonitorInfo{
	uint32_t Width; //The width, in screen coordinates, of the video mode.
	uint32_t Height; //The height, in screen coordinates, of the video mode.
	uint32_t RedBits; //The bit depth of the red channel of the video mode.
	uint32_t GreenBits; //The bit depth of the green channel of the video mode.
	uint32_t BlueBits; //The bit depth of the blue channel of the video mode.
	uint32_t RefreshRate; //The refresh rate, in Hz, of the video mode.

	uint32_t WidthMM; //physical width in mm
	uint32_t HeightMM; //physical height in mm

	//the position, in screen coordinates, of the upper - left corner of the specified monitor.
	uint32_t Xpos;  //position of the monitor's viewport on the virtual screen.
	uint32_t Ypos;


	uint32_t DPI; //dpi :))
}MonitorInfo;

/*
* Added in 1.0.0
* native monitor handle
* Returned by Get_Monitors()
*/
typedef void Monitor;


///////////////////////////////////////////////////////////////////
//Input
///////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Window
*/
typedef struct Window{
	void* Window; //native window handle

	struct
	{
		unsigned short highSurrogate;
	}win32;

	bool FullScreen;

	KeyState STATE_KEY_SPACE;
	KeyState STATE_KEY_APOSTROPHE;
	KeyState STATE_KEY_COMMA;
	KeyState STATE_KEY_MINUS;
	KeyState STATE_KEY_PERIOD;
	KeyState STATE_KEY_SLASH;
	KeyState STATE_KEY_0;
	KeyState STATE_KEY_1;
	KeyState STATE_KEY_2;
	KeyState STATE_KEY_3;
	KeyState STATE_KEY_4;
	KeyState STATE_KEY_5;
	KeyState STATE_KEY_6;
	KeyState STATE_KEY_7;
	KeyState STATE_KEY_8;
	KeyState STATE_KEY_9;
	KeyState STATE_KEY_SEMICOLON;
	KeyState STATE_KEY_PLUS;
	KeyState STATE_KEY_A;
	KeyState STATE_KEY_B;
	KeyState STATE_KEY_C;
	KeyState STATE_KEY_D;
	KeyState STATE_KEY_E;
	KeyState STATE_KEY_F;
	KeyState STATE_KEY_G;
	KeyState STATE_KEY_H;
	KeyState STATE_KEY_I;
	KeyState STATE_KEY_J;
	KeyState STATE_KEY_K;
	KeyState STATE_KEY_L;
	KeyState STATE_KEY_M;
	KeyState STATE_KEY_N;
	KeyState STATE_KEY_O;
	KeyState STATE_KEY_P;
	KeyState STATE_KEY_Q;
	KeyState STATE_KEY_R;
	KeyState STATE_KEY_S;
	KeyState STATE_KEY_T;
	KeyState STATE_KEY_U;
	KeyState STATE_KEY_V;
	KeyState STATE_KEY_W;
	KeyState STATE_KEY_X;
	KeyState STATE_KEY_Y;
	KeyState STATE_KEY_Z;
	KeyState STATE_KEY_LEFT_BRACKET;
	KeyState STATE_KEY_BACKSLASH;
	KeyState STATE_KEY_RIGHT_BRACKET;
	KeyState STATE_KEY_GRAVE_ACCENT;
	KeyState STATE_KEY_WORLD_1;
	KeyState STATE_KEY_WORLD_2;
	KeyState STATE_KEY_ESCAPE;
	KeyState STATE_KEY_ENTER;
	KeyState STATE_KEY_TAB;
	KeyState STATE_KEY_BACKSPACE;
	KeyState STATE_KEY_INSERT;
	KeyState STATE_KEY_DELETE;
	KeyState STATE_KEY_RIGHT;
	KeyState STATE_KEY_LEFT;
	KeyState STATE_KEY_DOWN;
	KeyState STATE_KEY_UP;
	KeyState STATE_KEY_PAGE_UP;
	KeyState STATE_KEY_PAGE_DOWN;
	KeyState STATE_KEY_HOME;
	KeyState STATE_KEY_END;
	KeyState STATE_KEY_CAPS_LOCK;
	KeyState STATE_KEY_SCROLL_LOCK;
	KeyState STATE_KEY_NUM_LOCK;
	KeyState STATE_KEY_PRINT_SCREEN;
	KeyState STATE_KEY_PAUSE;
	KeyState STATE_KEY_F1;
	KeyState STATE_KEY_F2;
	KeyState STATE_KEY_F3;
	KeyState STATE_KEY_F4;
	KeyState STATE_KEY_F5;
	KeyState STATE_KEY_F6;
	KeyState STATE_KEY_F7;
	KeyState STATE_KEY_F8;
	KeyState STATE_KEY_F9;
	KeyState STATE_KEY_F10;
	KeyState STATE_KEY_F11;
	KeyState STATE_KEY_F12;
	KeyState STATE_KEY_F13;
	KeyState STATE_KEY_F14;
	KeyState STATE_KEY_F15;
	KeyState STATE_KEY_F16;
	KeyState STATE_KEY_F17;
	KeyState STATE_KEY_F18;
	KeyState STATE_KEY_F19;
	KeyState STATE_KEY_F20;
	KeyState STATE_KEY_F21;
	KeyState STATE_KEY_F22;
	KeyState STATE_KEY_F23;
	KeyState STATE_KEY_F24;
	KeyState STATE_KEY_KP_0;
	KeyState STATE_KEY_KP_1;
	KeyState STATE_KEY_KP_2;
	KeyState STATE_KEY_KP_3;
	KeyState STATE_KEY_KP_4;
	KeyState STATE_KEY_KP_5;
	KeyState STATE_KEY_KP_6;
	KeyState STATE_KEY_KP_7;
	KeyState STATE_KEY_KP_8;
	KeyState STATE_KEY_KP_9;
	KeyState STATE_KEY_KP_DECIMAL;
	KeyState STATE_KEY_KP_DIVIDE;
	KeyState STATE_KEY_KP_MULTIPLY;
	KeyState STATE_KEY_KP_SUBTRACT;
	KeyState STATE_KEY_KP_ADD;
	KeyState STATE_KEY_KP_ENTER;
	KeyState STATE_KEY_LEFT_SHIFT;
	KeyState STATE_KEY_LEFT_CONTROL;
	KeyState STATE_KEY_LEFT_ALT;
	KeyState STATE_KEY_LEFT_SUPER;
	KeyState STATE_KEY_RIGHT_SHIFT;
	KeyState STATE_KEY_RIGHT_CONTROL;
	KeyState STATE_KEY_RIGHT_ALT;
	KeyState STATE_KEY_RIGHT_SUPER;
	KeyState STATE_KEY_MENU;

	KeyState STATE_MOUSE_BUTTON_1;
	KeyState STATE_MOUSE_BUTTON_2;
	KeyState STATE_MOUSE_BUTTON_3;
	KeyState STATE_MOUSE_BUTTON_4;
	KeyState STATE_MOUSE_BUTTON_5;
	KeyState STATE_MOUSE_BUTTON_6;
	KeyState STATE_MOUSE_BUTTON_7;
	KeyState STATE_MOUSE_BUTTON_8;
}Window;

//various input types
typedef struct Key_Callback_struct
{
	Window* pWindow;
	Key KeyCode; //virtual key code
	uint32_t ScanCode; //scancode, per keyboard/system OEM dependant
	KeyState State; //press state
}Key_Callback_struct;
typedef struct Character_Callback_struct
{
	Window* pWindow;
	UTF32 CodePoint; //utf32 codepoint 
}Character_Callback_struct;
typedef struct MouseButton_Callback_struct
{
	Window* pWindow;
	MouseButton Button;
	KeyState State;
}MouseButton_Callback_struct;
typedef struct MousePos_Callback_struct
{
	Window* pWindow;
	double X_Position;
	double Y_Position;
}MousePos_Callback_struct;
typedef struct MouseEnter_Callback_struct
{
	Window* pWindow;
	bool Entered; //true == entered, false == left.
}MouseEnter_Callback_struct;
typedef struct Scroll_Callback_struct
{
	Window* pWindow;
	double X_Offset;
	double Y_Offset;
	double Delta;
}Scroll_Callback_struct;
//connection callback types
typedef struct Joystick_Connect_Callback_struct
{
	Joystick Joystick;
	ConnectionEvent Action;
}Joystick_Connect_Callback_struct;
typedef struct Monitor_Connect_Callback_struct
{
	Monitor* pMonitor;
	ConnectionEvent Action;
}Monitor_Connect_Callback_struct;
//window callback types
typedef struct Drop_Callback_struct
{
	Window* pWindow;
	uint32_t PathsSize;
	const UTF8** Paths; //array of paths
}Drop_Callback_struct;
typedef struct Window_Resize_Callback_struct
{
	Window* pWindow;
	uint32_t NewWidth;
	uint32_t NewHeight;
}Window_Resize_Callback_struct;
typedef struct FrameBuffer_Resize_Callback_struct
{
	Window* pWindow;
	uint32_t NewWidth;
	uint32_t NewHeight;
}FrameBuffer_Resize_Callback_struct;
typedef struct Window_Refresh_Callback_struct
{
	Window* pWindow;
}Window_Refresh_Callback_struct;
typedef struct Window_Move_Callback_struct
{
	Window* pWindow; 
	double X_Position;//The new x-coordinate, in screen coordinates, of the upper - left corner of the client area of the window.
	double Y_Position;//The new y-coordinate, in screen coordinates, of the upper - left corner of the client area of the window.
}Window_Move_Callback_struct;
typedef struct Window_Minimise_Callback_struct
{
	Window* pWindow;
	bool Iconified; //iconified true if the window was iconified, or false if it was restored.
}Window_Minimise_Callback_struct;
typedef struct Window_Focused_Callback_struct
{
	Window* pWindow;
	bool Focus; //true if the window was focus, or false if it was removed focus.
}Window_Focused_Callback_struct;
typedef struct Window_Close_Callback_struct
{
	Window* pWindow;
}Window_Close_Callback_struct;
typedef struct Window_Open_Callback_struct
{
	Window* pWindow;
}Window_Open_Callback_struct;

//main
typedef struct EngineUtils{
	bool ApplicationClose;

	//OS-Specific Information.
	struct WindowsInfo {
		void* Instance; //HINSTANCE hInstance;
		void* PrevInstance; // HINSTANCE hPrevInstance
		int CommandShow; //int nCmdShow
		UTF8* CommandLine;
	}win32;
	struct PosixInfo {
		uint32_t pad;
	}posix;
	//Computer Information.
	struct CPUINFO {
		size_t MaxThreads;
	}CPU;
	//Internal Window Buffer.
	Window** pWindows;
	size_t pWindowsSize;
	Mutex WindowsMutex;


	ExtensionDataBuffer ExtensionBuffer;
	//default extension
	ExtensionAllocation EngineExtension;
	//Callback States
	Key_Callback_struct Key_Callback_state;
	Character_Callback_struct Character_Callback_state;
	MouseButton_Callback_struct MouseButton_Callback_state;
	MousePos_Callback_struct MousePos_Callback_state;
	MouseEnter_Callback_struct MouseEnter_Callback_state;
	Scroll_Callback_struct Scroll_Callback_state;
	Joystick_Connect_Callback_struct Joystick_Connect_Callback_state;
	Monitor_Connect_Callback_struct Monitor_Connect_Callback_state;
	Drop_Callback_struct Drop_Callback_state;
	Window_Resize_Callback_struct Window_Resize_Callback_state;
	FrameBuffer_Resize_Callback_struct FrameBuffer_Resize_Callback_state;
	Window_Refresh_Callback_struct Window_Refresh_Callback_state;
	Window_Move_Callback_struct Window_Move_Callback_state;
	Window_Minimise_Callback_struct Window_Minimise_Callback_state;
	Window_Focused_Callback_struct Window_Focused_Callback_state;
	Window_Close_Callback_struct Window_Close_Callback_state;
	Window_Open_Callback_struct Window_Open_Callback_state;
	//end

	struct CategoriesStruct
	{
		//all of them
		ResourceInfo** ExternalResources;
		uint64_t		ExternalResourcesSize;
		FunctionInfo** ExternalFunctions;
		uint64_t		ExternalFunctionsSize;

		//categorized
		FunctionInfo** Construct;
		uint64_t		ConstructSize;
		FunctionInfo** Destruct;
		uint64_t		DestructSize;
		FunctionInfo** EveryFrame;
		uint64_t		EveryFrameSize;
		FunctionInfo** Key_Input;
		uint64_t		Key_InputSize;
		FunctionInfo** Character_Input;
		uint64_t		Character_InputSize;
		FunctionInfo** MouseButton_Input;
		uint64_t		MouseButton_InputSize;
		FunctionInfo** MousePos_Input;
		uint64_t		MousePos_InputSize;
		FunctionInfo** MouseEnter_Input;
		uint64_t		MouseEnter_InputSize;
		FunctionInfo** Scroll_Input;
		uint64_t		Scroll_InputSize;
		FunctionInfo** Joystick_Connect;
		uint64_t		Joystick_ConnectSize;
		FunctionInfo** Monitor_Connect;
		uint64_t		Monitor_ConnectSize;
		FunctionInfo** Drop_Input;
		uint64_t		Drop_InputSize;
		FunctionInfo** Window_Resize;
		uint64_t		Window_ResizeSize;
		FunctionInfo** FrameBuffer_Resize;
		uint64_t		FrameBuffer_ResizeSize;
		FunctionInfo** Window_Refresh;
		uint64_t		Window_RefreshSize;
		FunctionInfo** Window_Move;
		uint64_t		Window_MoveSize;
		FunctionInfo** Window_Minimise;
		uint64_t		Window_MinimiseSize;
		FunctionInfo** Window_Focused;
		uint64_t		Window_FocusedSize;
		FunctionInfo** Window_Close;
		uint64_t		Window_CloseSize;
		FunctionInfo** Window_Open;
		uint64_t		Window_OpenSize;
	}Category;
}EngineUtils;

///////////////////////////////////////////////////////////////////
//Import/Export macros
///////////////////////////////////////////////////////////////////


//////////////////ALL IMPORTS AND EXPORTS WILL BE RESET AFTER DESTROYING THE MAIN ENGINE

/*
* Added in 1.0.0
*/
void ResourceImport(ResourceInfo*** ppResourceInfos, uint64_t* pResourceInfosSize, const UTF8* Name, void** ppResource)
{
	uint64_t ResourceInfosSize = *pResourceInfosSize;
	Resize_Array((void**)ppResourceInfos, ResourceInfosSize, ResourceInfosSize + 1, sizeof(ResourceInfo*));
	ResourceInfo** pResourceInfos = *ppResourceInfos;

	pResourceInfos[ResourceInfosSize] = (ResourceInfo*)calloc(1, sizeof(ResourceInfo));
	pResourceInfos[ResourceInfosSize]->Name = Name;
	pResourceInfos[ResourceInfosSize]->ppResource = ppResource;
	*pResourceInfosSize += 1;
}

/*
* Added in 1.0.0
*/
void ResourceExport(ResourceInfo*** ppResourceInfos, uint64_t* pResourceInfosSize, const UTF8* Name, void** ppResource, void* pResource)
{
	uint64_t ResourceInfosSize = *pResourceInfosSize;
	Resize_Array((void**)ppResourceInfos, ResourceInfosSize, ResourceInfosSize + 1, sizeof(ResourceInfo*));
	ResourceInfo** pResourceInfos = *ppResourceInfos;

	pResourceInfos[ResourceInfosSize] = (ResourceInfo*)calloc(1, sizeof(ResourceInfo));
	pResourceInfos[ResourceInfosSize]->Name = Name;
	pResourceInfos[ResourceInfosSize]->ppResource = ppResource;
	*pResourceInfos[ResourceInfosSize]->ppResource = pResource;
	*pResourceInfosSize += 1;
}

/*
* Added in 1.0.0
*/
void FunctionImport(FunctionInfo*** ppFunctionInfos, uint64_t* pFunctionInfosSize, const UTF8* Name, void** ppFunction)
{
	uint64_t FunctionInfosSize = *pFunctionInfosSize;
	Resize_Array((void**)ppFunctionInfos, FunctionInfosSize, FunctionInfosSize + 1, sizeof(FunctionInfo*));
	FunctionInfo** pFunctionInfos = *ppFunctionInfos;

	pFunctionInfos[FunctionInfosSize] = (FunctionInfo*)calloc(1, sizeof(FunctionInfo));
	pFunctionInfos[FunctionInfosSize]->Name = Name;
	pFunctionInfos[FunctionInfosSize]->ppFunction = ppFunction;
	pFunctionInfos[FunctionInfosSize]->CallFlags = (CallFlagBits)NULL; 
	pFunctionInfos[FunctionInfosSize]->ThreadMode = (FunctionThreadingMode)NULL; 
	pFunctionInfos[FunctionInfosSize]->Priority = 0.0f; 
	pFunctionInfos[FunctionInfosSize]->NumArgs = NULL; 
	pFunctionInfos[FunctionInfosSize]->Args = NULL;
	*pFunctionInfosSize += 1;
}

/*
* Added in 1.0.0
*/
void FunctionExport(FunctionInfo*** ppFunctionInfos, uint64_t* pFunctionInfosSize, const UTF8* Name, void** ppFunction, void* pFunction,
	CallFlagBits CallFlags, FunctionThreadingMode ThreadMode, float Priority, uint64_t NumArguments, ResourceInfo* pArguments)
{
	uint64_t FunctionInfosSize = *pFunctionInfosSize;
	Resize_Array((void**)ppFunctionInfos, FunctionInfosSize, FunctionInfosSize + 1, sizeof(FunctionInfo*));
	FunctionInfo** pFunctionInfos = *ppFunctionInfos;

	pFunctionInfos[FunctionInfosSize] = (FunctionInfo*)calloc(1, sizeof(FunctionInfo));
	pFunctionInfos[FunctionInfosSize]->Name = Name;
	pFunctionInfos[FunctionInfosSize]->ppFunction = ppFunction;
	*pFunctionInfos[FunctionInfosSize]->ppFunction = pFunction;
	pFunctionInfos[FunctionInfosSize]->CallFlags = CallFlags;
	pFunctionInfos[FunctionInfosSize]->ThreadMode = ThreadMode;
	pFunctionInfos[FunctionInfosSize]->Priority = Priority;
	pFunctionInfos[FunctionInfosSize]->NumArgs = NumArguments;
	pFunctionInfos[FunctionInfosSize]->Args = pArguments;
	*pFunctionInfosSize += 1;
}

/*
* Added in 1.0.0
*/
void ConfigParameterExport(ConfigParameterInfo** pConfigParameterInfos, uint64_t* pConfigParameterInfosSize, const UTF8* Name, void* pParameter, uint64_t ArrayElementsCount, uint64_t ByteLength)
{
	uint64_t ConfigParameterInfosSize = *pConfigParameterInfosSize;
	Resize_Array((void**)pConfigParameterInfos, ConfigParameterInfosSize, ConfigParameterInfosSize + 1, sizeof(ConfigParameterInfo));
	ConfigParameterInfo* ConfigParameterInfos = *pConfigParameterInfos;
	ConfigParameterInfos[ConfigParameterInfosSize].Name = Name;
	ConfigParameterInfos[ConfigParameterInfosSize].ArrayElementsCount = ArrayElementsCount;
	ConfigParameterInfos[ConfigParameterInfosSize].ByteLength = ByteLength;
	ConfigParameterInfos[ConfigParameterInfosSize].pParameter = pParameter;
	*pConfigParameterInfosSize += 1;
}



#define MakeVersion(Version, Major, Minor, Patch)\
Version[0] = Major;\
Version[1] = Minor;\
Version[2] = Patch;

struct EngineResStruct
{
	void* pUtils;

	void* pResize_ExtensionDataBuffer;

	void* pGet_ExtensionDataPointer;
	void* pCreate_ExtensionData;
	void* pDestroy_ExtensionData;

	void* pLoad_Extension;
	void* pDeLoad_Extension;

	void* pResolve_Linkages;
	void* pRecreate_Categories;

	void* pResolve_FunctionSymbol;
	void* pResolve_ResourceSymbol;

	void* pCreate_Window;
	void* pDestroy_Window;

	void* pSet_WindowFullScreen;

	void* pRead_ClipboardUTF8;
	void* pWrite_ClipboardUTF8;

	void* pGet_PrimaryMonitor;
	void* pGet_MonitorInfo;

	void* pExit_Application;
	void* pApply_Config;


	void* pCreate_Mutex;
	void* pDestroy_Mutex;
	void* pLock_Mutex;
	void* pTimedLock_Mutex;
	void* pTryLock_Mutex;
	void* pUnlock_Mutex;

	void* pCreate_Condition;
	void* pDestroy_Condition;
	void* pSignal_Condition;
	void* pBroadcast_Condition;
	void* pWait_Condition;
	void* pTimedWait_Condition;

	void* pCreate_Thread;
	void* pCurrent_Thread;
	void* pDetach_Thread;
	void* pThreadEqual;
	void* pExit_Thread;
	void* pJoin_Thread;
	void* pSleep_Thread;
	void* pYield_Thread;

	//void* pCall_Once;

	void* pObjectError;
	void* pFunctionError;
	void* pArgsError;

}EngineRes;

//Initialise_Resources MUST be called to use the library in your extension
void Engine_Initialise_Resources(FunctionInfo*** pExternFunctions, uint64_t* pExternFunctionsSize, ResourceInfo*** pExternResources, uint64_t* pExternResourcesSize)
{
	memset(&EngineRes, NULL, sizeof(EngineRes));

	ResourceImport(pExternResources, pExternResourcesSize, (const UTF8*)CopyData((void*)"Engine::Utils"), &EngineRes.pUtils);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Resize_ExtensionDataBuffer"), &EngineRes.pResize_ExtensionDataBuffer);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Get_ExtensionDataPointer"), &EngineRes.pGet_ExtensionDataPointer);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Create_ExtensionData"), &EngineRes.pCreate_ExtensionData);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Destroy_ExtensionData"), &EngineRes.pDestroy_ExtensionData);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Load_Extension"), &EngineRes.pLoad_Extension);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::DeLoad_Extension"), &EngineRes.pDeLoad_Extension);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Resolve_Linkages"), &EngineRes.pResolve_Linkages);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Recreate_Categories"), &EngineRes.pRecreate_Categories);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Resolve_FunctionSymbol"), &EngineRes.pResolve_FunctionSymbol);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Resolve_ResourceSymbol"), &EngineRes.pResolve_ResourceSymbol);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Create_Window"), &EngineRes.pCreate_Window);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Destroy_Window"), &EngineRes.pDestroy_Window);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Set_WindowFullScreen"), &EngineRes.pSet_WindowFullScreen);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Read_ClipboardUTF8"), &EngineRes.pRead_ClipboardUTF8);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Write_ClipboardUTF8"), &EngineRes.pWrite_ClipboardUTF8);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Get_PrimaryMonitor"), &EngineRes.pGet_PrimaryMonitor);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Get_MonitorInfo"), &EngineRes.pGet_MonitorInfo);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Exit_Application"), &EngineRes.pExit_Application);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Apply_Config"), &EngineRes.pApply_Config);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Create_Mutex"), &EngineRes.pCreate_Mutex);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Destroy_Mutex"), &EngineRes.pDestroy_Mutex);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Lock_Mutex"), &EngineRes.pLock_Mutex);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::TimedLock_Mutex"), &EngineRes.pTimedLock_Mutex);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::TryLock_Mutex"), &EngineRes.pTryLock_Mutex);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Unlock_Mutex"), &EngineRes.pUnlock_Mutex);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Create_Condition"), &EngineRes.pCreate_Condition);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Destroy_Condition"), &EngineRes.pDestroy_Condition);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Signal_Condition"), &EngineRes.pBroadcast_Condition);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Signal_Condition"), &EngineRes.pSignal_Condition);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Broadcast_Condition"), &EngineRes.pBroadcast_Condition);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Wait_Condition"), &EngineRes.pWait_Condition);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::TimedWait_Condition"), &EngineRes.pTimedWait_Condition);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Create_Thread"), &EngineRes.pCreate_Thread);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Current_Thread"), &EngineRes.pCurrent_Thread);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Detach_Thread"), &EngineRes.pDetach_Thread);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::ThreadEqual"), &EngineRes.pThreadEqual);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Exit_Thread"), &EngineRes.pExit_Thread);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Join_Thread"), &EngineRes.pJoin_Thread);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Sleep_Thread"), &EngineRes.pSleep_Thread);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Yield_Thread"), &EngineRes.pYield_Thread);

		//FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::Call_Once"), &EngineRes.pCall_Once);

	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::ObjectError"), &EngineRes.pObjectError);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::FunctionError"), &EngineRes.pFunctionError);
	FunctionImport(pExternFunctions, pExternFunctionsSize, (const UTF8*)CopyData((void*)"Engine::ArgsError"), &EngineRes.pArgsError);

}

TEXRESULT Engine_Ref_Resize_ExtensionDataBuffer(uint64_t NewSize)
{
	TEXRESULT(*function)(uint64_t NewSize) =
		(TEXRESULT(*)(uint64_t NewSize))EngineRes.pResize_ExtensionDataBuffer;

	return function(NewSize);
}

ExtensionData* Engine_Ref_Get_ExtensionDataPointer(ExtensionAllocation Allocation)
{
	ExtensionData* (*function)(ExtensionAllocation Allocation) =
		(ExtensionData * (*)(ExtensionAllocation Allocation))EngineRes.pGet_ExtensionDataPointer;

	return function(Allocation);
}

TEXRESULT Engine_Ref_Create_ExtensionData(ExtensionAllocation* pAllocation, ExtensionDataCreateInfo* CreateInfo)
{
	TEXRESULT(*function)(ExtensionAllocation * pAllocation, ExtensionDataCreateInfo * CreateInfo) =
		(TEXRESULT(*)(ExtensionAllocation * pAllocation, ExtensionDataCreateInfo * CreateInfo))EngineRes.pCreate_ExtensionData;

	return function(pAllocation, CreateInfo);
}

void Engine_Ref_Destroy_ExtensionData(ExtensionAllocation Allocation)
{
	void(*function)(ExtensionAllocation Allocation) =
		(void(*)(ExtensionAllocation Allocation))EngineRes.pDestroy_ExtensionData;

	function(Allocation);
}

void Engine_Ref_Resolve_Linkages()
{
	void(*function)() =
		(void(*)())EngineRes.pResolve_Linkages;

	function();
}

void Engine_Ref_Recreate_Categories()
{
	void(*function)() =
		(void(*)())EngineRes.pRecreate_Categories;

	function();
}

TEXRESULT Engine_Ref_Resolve_FunctionSymbol(FunctionInfo* ReturnInfo)
{
	TEXRESULT(*function)(FunctionInfo * ReturnInfo) =
		(TEXRESULT(*)(FunctionInfo * ReturnInfo))EngineRes.pResolve_FunctionSymbol;

	return function(ReturnInfo);
}

TEXRESULT Engine_Ref_Resolve_ResourceSymbol(ResourceInfo* ReturnResource)
{
	TEXRESULT(*function)(ResourceInfo * ReturnResource) =
		(TEXRESULT(*)(ResourceInfo * ReturnResource))EngineRes.pResolve_ResourceSymbol;

	return function(ReturnResource);
}


TEXRESULT Engine_Ref_Create_Window(Window** ppWindow, uint64_t Width, uint64_t Height, const UTF8* Name)
{
	TEXRESULT(*function)(Window * *ppWindow, uint64_t Width, uint64_t Height, const UTF8 * Name) =
		(TEXRESULT(*)(Window * *ppWindow, uint64_t Width, uint64_t Height, const UTF8 * Name))EngineRes.pCreate_Window;

	return function(ppWindow, Width, Height, Name);
}

TEXRESULT Engine_Ref_Destroy_Window(Window* pWindow, const UTF8* Name)
{
	TEXRESULT(*function)(Window * pWindow, const UTF8 * Name) =
		(TEXRESULT(*)(Window * pWindow, const UTF8 * Name))EngineRes.pDestroy_Window;

	return function(pWindow, Name);
}

TEXRESULT Engine_Ref_Set_WindowFullScreen(Window* pWindow, bool FullScreen)
{
	TEXRESULT(*function)(Window * pWindow, bool FullScreen) =
		(TEXRESULT(*)(Window * pWindow, bool FullScreen))EngineRes.pSet_WindowFullScreen;

	return function(pWindow, FullScreen);
}

TEXRESULT Engine_Ref_Read_ClipboardUTF8(Window* pWindow, UTF8* pData, uint64_t* pDataSize)
{
	TEXRESULT(*function)(Window * pWindow, UTF8 * pData, uint64_t * pDataSize) =
		(TEXRESULT(*)(Window * pWindow, UTF8 * pData, uint64_t * pDataSize))EngineRes.pRead_ClipboardUTF8;

	return function(pWindow, pData, pDataSize);
}

TEXRESULT Engine_Ref_Write_ClipboardUTF8(Window* pWindow, UTF8* pData)
{
	TEXRESULT(*function)(Window * pWindow, UTF8 * pData) =
		(TEXRESULT(*)(Window * pWindow, UTF8 * pData))EngineRes.pWrite_ClipboardUTF8;

	return function(pWindow, pData);
}

TEXRESULT Engine_Ref_Get_PrimaryMonitor(Window* pWindow, Monitor** ppMonitor)
{
	TEXRESULT(*function)(Window * pWindow, Monitor * *ppMonitor) =
		(TEXRESULT(*)(Window * pWindow, Monitor * *ppMonitor))EngineRes.pGet_PrimaryMonitor;

	return function(pWindow, ppMonitor);
}

TEXRESULT Engine_Ref_Get_MonitorInfo(MonitorInfo* pMonitorInfo, Monitor* pMonitor)
{
	TEXRESULT(*function)(MonitorInfo * pMonitorInfo, Monitor * pMonitor) =
		(TEXRESULT(*)(MonitorInfo * pMonitorInfo, Monitor * pMonitor))EngineRes.pGet_MonitorInfo;

	return function(pMonitorInfo, pMonitor);
}

void Engine_Ref_Exit_Application()
{
	void(*function)() =
		(void(*)())EngineRes.pExit_Application;

	function();
}

void Engine_Ref_Apply_Config(const UTF8* ConfigParameterName, void* pConfigParameterToApply, uint64_t ArrayElementsCount, uint64_t ElementArrayIndex)
{
	void(*function)(const UTF8 * ConfigParameterName, void* pConfigParameterToApply, uint64_t ArrayElementsCount, uint64_t ElementArrayIndex) =
		(void(*)(const UTF8 * ConfigParameterName, void* pConfigParameterToApply, uint64_t ArrayElementsCount, uint64_t ElementArrayIndex))EngineRes.pApply_Config;

	function(ConfigParameterName, pConfigParameterToApply, ArrayElementsCount, ElementArrayIndex);
}

/*
//If TIME_UTC is missing, provide it and provide a wrapper for timespec_get.
#ifndef TIME_UTC
#define TIME_UTC 1
#define _TTHREAD_EMULATE_TIMESPEC_GET_

#if defined(_TTHREAD_WIN32_)
struct _tthread_timespec {
	time_t tv_sec;
	long   tv_nsec;
};
#define timespec _tthread_timespec
#endif

int _tthread_timespec_get(struct timespec* ts, int base);
#define timespec_get _tthread_timespec_get
#endif
*/

/** Create a mutex object.
* @param mtx A mutex object.
* @param type Bit-mask that must have one of the following six values:
*   @li @c mtx_plain for a simple non-recursive mutex
*   @li @c mtx_timed for a non-recursive mutex that supports timeout
*   @li @c mtx_plain | @c mtx_recursive (same as @c mtx_plain, but recursive)
*   @li @c mtx_timed | @c mtx_recursive (same as @c mtx_timed, but recursive)
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Engine_Ref_Create_Mutex(Mutex* pMutex, MutexType Type)
{
	TEXRESULT(*function)(Mutex * pMutex, MutexType Type) =
		(TEXRESULT(*)(Mutex * pMutex, MutexType Type))EngineRes.pCreate_Mutex;
	return function(pMutex, Type);
}
/** Release any resources used by the given mutex.
* @param mtx A mutex object.
*/
void Engine_Ref_Destroy_Mutex(Mutex* pMutex)
{
	void(*function)(Mutex * pMutex) =
		(void(*)(Mutex * pMutex))EngineRes.pDestroy_Mutex;
	function(pMutex);
}

/** Lock the given mutex.
* Blocks until the given mutex can be locked. If the mutex is non-recursive, and
* the calling thread already has a lock on the mutex, this call will block
* forever.
* @param mtx A mutex object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Engine_Ref_Lock_Mutex(Mutex* pMutex)
{
	TEXRESULT(*function)(Mutex * pMutex) =
		(TEXRESULT(*)(Mutex * pMutex))EngineRes.pLock_Mutex;
	return function(pMutex);
}

/** Lock the given mutex, or block until a specific point in time.
* Blocks until either the given mutex can be locked, or the specified TIME_UTC
* based time.
* @param mtx A mutex object.
* @param ts A UTC based calendar time
* @return @ref The mtx_timedlock function returns thrd_success on success, or
* thrd_timedout if the time specified was reached without acquiring the
* requested resource, or thrd_error if the request could not be honored.
*/
TEXRESULT Engine_Ref_TimedLock_Mutex(Mutex* pMutex, const struct timespec* ts)
{
	TEXRESULT(*function)(Mutex * pMutex, const struct timespec* ts) =
		(TEXRESULT(*)(Mutex * pMutex, const struct timespec* ts))EngineRes.pTimedLock_Mutex;
	return function(pMutex, ts);
}

/** Try to lock the given mutex.
* The specified mutex shall support either test and return or timeout. If the
* mutex is already locked, the function returns without blocking.
* @param mtx A mutex object.
* @return @ref thrd_success on success, or @ref thrd_busy if the resource
* requested is already in use, or @ref thrd_error if the request could not be
* honored.
*/
TEXRESULT Engine_Ref_TryLock_Mutex(Mutex* pMutex)
{
	TEXRESULT(*function)(Mutex * pMutex) =
		(TEXRESULT(*)(Mutex * pMutex))EngineRes.pTryLock_Mutex;
	return function(pMutex);
}

/** Unlock the given mutex.
* @param mtx A mutex object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Engine_Ref_Unlock_Mutex(Mutex* pMutex)
{
	TEXRESULT(*function)(Mutex * pMutex) =
		(TEXRESULT(*)(Mutex * pMutex))EngineRes.pUnlock_Mutex;
	return function(pMutex);
}

/** Create a condition variable object.
* @param cond A condition variable object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Engine_Ref_Create_Condition(Condition* pCondition)
{
	TEXRESULT(*function)(Condition* pCondition) =
		(TEXRESULT(*)(Condition * pCondition))EngineRes.pCreate_Condition;
	return function(pCondition);
}

/** Release any resources used by the given condition variable.
* @param cond A condition variable object.
*/
void Engine_Ref_Destroy_Condition(Condition* pCondition)
{
	void(*function)(Condition * pCondition) =
		(void(*)(Condition * pCondition))EngineRes.pDestroy_Condition;
	function(pCondition);
}

/** Signal a condition variable.
* Unblocks one of the threads that are blocked on the given condition variable
* at the time of the call. If no threads are blocked on the condition variable
* at the time of the call, the function does nothing and return success.
* @param cond A condition variable object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Engine_Ref_Signal_Condition(Condition* pCondition)
{
	TEXRESULT(*function)(Condition * pCondition) =
		(TEXRESULT(*)(Condition * pCondition))EngineRes.pSignal_Condition;
	return function(pCondition);
}

/** Broadcast a condition variable.
* Unblocks all of the threads that are blocked on the given condition variable
* at the time of the call. If no threads are blocked on the condition variable
* at the time of the call, the function does nothing and return success.
* @param cond A condition variable object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Engine_Ref_Broadcast_Condition(Condition* pCondition)
{
	TEXRESULT(*function)(Condition * pCondition) =
		(TEXRESULT(*)(Condition * pCondition))EngineRes.pBroadcast_Condition;
	return function(pCondition);
}

/** Wait for a condition variable to become signaled.
* The function atomically unlocks the given mutex and endeavors to block until
* the given condition variable is signaled by a call to cnd_signal or to
* cnd_broadcast. When the calling thread becomes unblocked it locks the mutex
* before it returns.
* @param cond A condition variable object.
* @param mtx A mutex object.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Engine_Ref_Wait_Condition(Condition* pCondition, Mutex* pMutex)
{
	TEXRESULT(*function)(Condition * pCondition, Mutex * pMutex) =
		(TEXRESULT(*)(Condition * pCondition, Mutex * pMutex))EngineRes.pWait_Condition;
	return function(pCondition, pMutex);
}

/** Wait for a condition variable to become signaled.
* The function atomically unlocks the given mutex and endeavors to block until
* the given condition variable is signaled by a call to cnd_signal or to
* cnd_broadcast, or until after the specified time. When the calling thread
* becomes unblocked it locks the mutex before it returns.
* @param cond A condition variable object.
* @param mtx A mutex object.
* @param xt A point in time at which the request will time out (absolute time).
* @return @ref thrd_success upon success, or @ref thrd_timeout if the time
* specified in the call was reached without acquiring the requested resource, or
* @ref thrd_error if the request could not be honored.
*/
TEXRESULT Engine_Ref_TimedWait_Condition(Condition* pCondition, Mutex* pMutex, const struct timespec* ts)
{
	TEXRESULT(*function)(Condition * pCondition, Mutex * pMutex, const struct timespec* ts) =
		(TEXRESULT(*)(Condition * pCondition, Mutex * pMutex, const struct timespec* ts))EngineRes.pTimedWait_Condition;
	return function(pCondition, pMutex, ts);
}

/** Create a new thread.
* @param thr Identifier of the newly created thread.
* @param func A function pointer to the function that will be executed in
*        the new thread.
* @param arg An argument to the thread function.
* @return @ref thrd_success on success, or @ref thrd_nomem if no memory could
* be allocated for the thread requested, or @ref thrd_error if the request
* could not be honored.
* @note A thread’s identifier may be reused for a different thread once the
* original thread has exited and either been detached or joined to another
* thread.
*/
TEXRESULT Engine_Ref_Create_Thread(Thread** ppThread, thrd_start_t Function, void* arg)
{
	TEXRESULT(*function)(Thread** ppThread, thrd_start_t Function, void* arg) =
		(TEXRESULT(*)(Thread** ppThread, thrd_start_t Function, void* arg))EngineRes.pCreate_Thread;
	return function(ppThread, Function, arg);
}

/** Identify the calling thread.
* @return The identifier of the calling thread.
*/
Thread* Engine_Ref_Current_Thread(void)
{
	Thread*(*function)(void) =
		(Thread*(*)(void))EngineRes.pCurrent_Thread;
	return function();
}

/** Dispose of any resources allocated to the thread when that thread exits.
 * @return thrd_success, or thrd_error on error
*/
TEXRESULT Engine_Ref_Detach_Thread(Thread* pThread)
{
	TEXRESULT(*function)(Thread* pThread) =
		(TEXRESULT(*)(Thread* pThread))EngineRes.pDetach_Thread;
	return function(pThread);
}

/** Compare two thread identifiers.
* The function determines if two thread identifiers refer to the same thread.
* @return Zero if the two thread identifiers refer to different threads.
* Otherwise a nonzero value is returned.
*/
TEXRESULT Engine_Ref_ThreadEqual(Thread* pThread0, Thread* pThread1)
{
	TEXRESULT(*function)(Thread * pThread, Thread * pThread1) =
		(TEXRESULT(*)(Thread * pThread, Thread * pThread1))EngineRes.pThreadEqual;
	return function(pThread0, pThread1);
}

/** Terminate execution of the calling thread.
* @param res Result code of the calling thread.
*/
void Engine_Ref_Exit_Thread(int res)
{
	void(*function)(int res) =
		(void(*)(int res))EngineRes.pExit_Thread;
	function(res);
}

/** Wait for a thread to terminate.
* The function joins the given thread with the current thread by blocking
* until the other thread has terminated.
* @param thr The thread to join with.
* @param res If this pointer is not NULL, the function will store the result
*        code of the given thread in the integer pointed to by @c res.
* @return @ref thrd_success on success, or @ref thrd_error if the request could
* not be honored.
*/
TEXRESULT Engine_Ref_Join_Thread(Thread* pThread, int* res)
{
	TEXRESULT(*function)(Thread * pThread, int* res) =
		(TEXRESULT(*)(Thread * pThread, int* res))EngineRes.pJoin_Thread;
	return function(pThread, res);
}

/** Put the calling thread to sleep.
* Suspend execution of the calling thread.
* @param duration  Interval to sleep for
* @param remaining If non-NULL, this parameter will hold the remaining
*                  time until time_point upon return. This will
*                  typically be zero, but if the thread was woken up
*                  by a signal that is not ignored before duration was
*                  reached @c remaining will hold a positive time.
* @return 0 (zero) on successful sleep, -1 if an interrupt occurred,
*         or a negative value if the operation fails.
*/
TEXRESULT Engine_Ref_Sleep_Thread(const struct timespec* duration, struct timespec* remaining)
{
	TEXRESULT(*function)(const struct timespec* duration, struct timespec* remaining) =
		(TEXRESULT(*)(const struct timespec* duration, struct timespec* remaining))EngineRes.pSleep_Thread;
	return function(duration, remaining);
}

/** Yield execution to another thread.
* Permit other threads to run, even if the current thread would ordinarily
* continue to run.
*/
void Engine_Ref_Yield_Thread(void)
{
	void(*function)(void) =
		(void(*)(void))EngineRes.pYield_Thread;
	function();
}

/** Invoke a callback exactly once
 * @param flag Flag used to ensure the callback is invoked exactly
 *        once.
 * @param func Callback to invoke.
 */
/*
void Engine_Ref_Call_Once(once_flag* flag, void (*func)(void))
{
	void(*function)(once_flag * flag, void (*func)(void)) =
		(void(*)(once_flag * flag, void (*func)(void)))EngineRes.pCall_Once;
	function(flag, func);
}*/

void Engine_Ref_ObjectError(const UTF8* FunctionName, const UTF8* ObjectName, void* ObjectPointer, const UTF8* Error)
{
	void(*function)(const UTF8 * FunctionName, const UTF8 * ObjectName, void* ObjectPointer, const UTF8 * Error) =
		(void(*)(const UTF8 * FunctionName, const UTF8 * ObjectName, void* ObjectPointer, const UTF8 * Error))EngineRes.pObjectError;
	function(FunctionName, ObjectName, ObjectPointer, Error);
}

void Engine_Ref_FunctionError(const UTF8* FunctionName, const UTF8* Error, uint64_t Value)
{
	void(*function)(const UTF8 * FunctionName, const UTF8 * Error, uint64_t Value) =
		(void(*)(const UTF8 * FunctionName, const UTF8 * Error, uint64_t Value))EngineRes.pFunctionError;
	function(FunctionName, Error, Value);
}

void Engine_Ref_ArgsError(const UTF8* FunctionName, const UTF8* Error)
{
	void(*function)(const UTF8 * FunctionName, const UTF8 * Error) =
		(void(*)(const UTF8 * FunctionName, const UTF8 * Error))EngineRes.pArgsError;
	function(FunctionName, Error);
}



#define SPIRV_Header(Bound)\
SpvMagicNumber, SpvVersion, 'TEX ', Bound, 0,

//turing SPIRV readable into TEX arraycode

//step 1
//(\d+)(\(.*\))* : (\d+)(\(.+\))*(?([^\r\n])\s)*(\w+) 
//(5<<SpvWordCountShift)|SpvOp$5 $3 $1 

//step 2
//(\d+)(\(.*\))*(?([^\r\n])\s)*:(?([^\r\n])\s)*(\w+)
//(5<<SpvWordCountShift)|SpvOp$3 $1

//step 3
//(?([^\r\n])\s){2}(\w+)(?([^\r\n])\s)
//(5<<SpvWordCountShift)|SpvOp$1 

//step4
//[^\r\n]*(\(\d+<<)
//$1

//step5
//\(\w+\)
// 

//step6 //adding commas //not perfect
//(?([^\r\n])\s)+
//, 

//step 7 //comma2 //not perfect
//(\r\n)
//,\r\n


/*takes up 12 indexes*/
#define SPIRV_Matrix4x4Add(startindex, vec4type, mat4type, result, matrix1, matrix2)\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, vec4type, startindex + 0, matrix1, 0,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, vec4type, startindex + 1, matrix2, 0,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, vec4type, startindex + 2, matrix1, 1,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, vec4type, startindex + 3, matrix2, 1,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, vec4type, startindex + 4, matrix1, 2,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, vec4type, startindex + 5, matrix2, 2,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, vec4type, startindex + 6, matrix1, 3,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, vec4type, startindex + 7, matrix2, 3,\
(5<<SpvWordCountShift)|SpvOpFAdd, vec4type, startindex + 8, startindex + 0, startindex + 1,\
(5<<SpvWordCountShift)|SpvOpFAdd, vec4type, startindex + 9, startindex + 2, startindex + 3,\
(5<<SpvWordCountShift)|SpvOpFAdd, vec4type, startindex + 10, startindex + 4, startindex + 5,\
(5<<SpvWordCountShift)|SpvOpFAdd, vec4type, startindex + 11, startindex + 6, startindex + 7,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, mat4type, result, startindex + 8, startindex + 9, startindex + 10, startindex + 11,


///////////////////////////////////////////////////////////////////////////////////////////////
//Deferred
///////////////////////////////////////////////////////////////////////////////////////////////

typedef enum VertexShaderDeferredVariables {
}VertexShaderDeferredVariables;
#define VertexShaderDeferredSize (716 * sizeof(SPIRV))
#define VertexShaderDeferred() {\
	SPIRV_Header(144)\
	(2 << SpvWordCountShift) | SpvOpCapability, SpvCapabilityShader,\
	(2 << SpvWordCountShift) | SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
	(3 << SpvWordCountShift) | SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
	(8 << SpvWordCountShift) | SpvOpEntryPoint, SpvExecutionModelVertex, 4, 'niam', '\0', 122, 124, 133,\
	/*inputs*/\
	(4 << SpvWordCountShift) | SpvOpDecorate,		122,    SpvDecorationBuiltIn, SpvBuiltInVertexIndex,\
	(4 << SpvWordCountShift) | SpvOpDecorate,		124,	SpvDecorationBuiltIn, SpvBuiltInInstanceIndex,\
	(5 << SpvWordCountShift) | SpvOpMemberDecorate, 131, 0,	SpvDecorationBuiltIn, SpvBuiltInPosition,\
	(5 << SpvWordCountShift) | SpvOpMemberDecorate, 131, 1,	SpvDecorationBuiltIn, SpvBuiltInPointSize,\
	(5 << SpvWordCountShift) | SpvOpMemberDecorate, 131, 2,	SpvDecorationBuiltIn, SpvBuiltInClipDistance,\
	(5 << SpvWordCountShift) | SpvOpMemberDecorate, 131, 3,	SpvDecorationBuiltIn, SpvBuiltInCullDistance,\
	(3 << SpvWordCountShift) | SpvOpDecorate, 131, SpvDecorationBlock,\
	/*Main SpvStorageClassFunction*/\
	(2 << SpvWordCountShift) | SpvOpTypeVoid,              2,\
	(3 << SpvWordCountShift) | SpvOpTypeFunction,          3,      2,\
	(3 << SpvWordCountShift) | SpvOpTypeFloat,             6,      32,\
	(4 << SpvWordCountShift) | SpvOpTypeVector,            7,      6,  2,\
	(4 << SpvWordCountShift) | SpvOpTypePointer,           8,      SpvStorageClassFunction, 7,\
    /*declaring vec2 for scale.*/\
	(4 << SpvWordCountShift) | SpvOpConstant, 6,           10,     1065353216,\
	(5 << SpvWordCountShift) | SpvOpConstantComposite, 7,  11,       10, 10,\
    /*declaring vec3 for position.*/\
	(4 << SpvWordCountShift) | SpvOpTypeVector,            12,     6,  3,\
	(4 << SpvWordCountShift) | SpvOpTypePointer,           13,     SpvStorageClassFunction, 12,\
	(4 << SpvWordCountShift) | SpvOpConstant, 6,           15,     0,\
	(6 << SpvWordCountShift) | SpvOpConstantComposite, 12, 16,      15, 15, 15,\
    /*declaring int: how many verts in an instance.*/\
	(4 << SpvWordCountShift) | SpvOpTypeInt,               17,     32, 0,\
	(4 << SpvWordCountShift) | SpvOpConstant, 17,          18,     6,\
    /*declaring vertex table*/\
	(4 << SpvWordCountShift) | SpvOpTypeArray,             19,     12,   18,\
	(4 << SpvWordCountShift) | SpvOpTypePointer,           20,     SpvStorageClassFunction, 19,\
    /*int.*/\
	(4 << SpvWordCountShift) | SpvOpConstant, 17,          22,     0,\
    /*pointer to scale vec2*/\
	(4 << SpvWordCountShift) | SpvOpTypePointer,           23,     SpvStorageClassFunction, 6,\
    /*int.*/\
	(4 << SpvWordCountShift) | SpvOpConstant, 17,          29,     1,\
    /*int.*/\
	(4 << SpvWordCountShift) | SpvOpConstant, 17,          36,     2,\
    /*declaring constant vertex UV table*/\
	(4 << SpvWordCountShift) | SpvOpTypeArray,             111,    7,  18,\
	(4 << SpvWordCountShift) | SpvOpTypePointer,           112,    SpvStorageClassFunction, 111,\
	(5 << SpvWordCountShift) | SpvOpConstantComposite, 7,  114,    10, 15,\
	(5 << SpvWordCountShift) | SpvOpConstantComposite, 7,  115,    15, 10,\
	(5 << SpvWordCountShift) | SpvOpConstantComposite, 7,  116,    15, 15,\
	(9 << SpvWordCountShift) | SpvOpConstantComposite, 111,117,    114, 115, 116, 114, 11, 115,\
    /*declaring int*/\
	(4 << SpvWordCountShift) | SpvOpTypeInt,               118,    32,     1,\
	(4 << SpvWordCountShift) | SpvOpTypePointer,           119,    SpvStorageClassFunction, 118,\
    /*inputs*/\
	(4 << SpvWordCountShift) | SpvOpTypePointer,           121,    SpvStorageClassInput, 118,\
	(4 << SpvWordCountShift) | SpvOpVariable, 121,         122,    SpvStorageClassInput,\
	(4 << SpvWordCountShift) | SpvOpVariable, 121,         124,    SpvStorageClassInput,\
    /*declaring uint*/\
	(4 << SpvWordCountShift) | SpvOpConstant, 118,         126,        6,\
	(4 << SpvWordCountShift) | SpvOpTypeVector,            129,    6,      4,\
    /*declaring float array*/\
	(4 << SpvWordCountShift) | SpvOpTypeArray,             130,    6,      29,\
    /*declaring struct*/\
	(6 << SpvWordCountShift) | SpvOpTypeStruct,            131,    129, 6, 130, 130,\
    /*pointer to struct*/\
	(4 << SpvWordCountShift) | SpvOpTypePointer,           132,    SpvStorageClassOutput, 131,\
	(4 << SpvWordCountShift) | SpvOpVariable, 132,         133,    SpvStorageClassOutput,\
	(4 << SpvWordCountShift) | SpvOpConstant, 118,         134,    0,\
	(4 << SpvWordCountShift) | SpvOpTypePointer,           142,    SpvStorageClassOutput, 129,\
	(5 << SpvWordCountShift) | SpvOpFunction, 2,           4,      SpvFunctionControlMaskNone, 3,\
	(2 << SpvWordCountShift) | SpvOpLabel,                 5,\
	(4 << SpvWordCountShift) | SpvOpVariable, 8,           9,      SpvStorageClassFunction,\
	(4 << SpvWordCountShift) | SpvOpVariable, 13,          14,     SpvStorageClassFunction,\
	(4 << SpvWordCountShift) | SpvOpVariable, 20,          21,     SpvStorageClassFunction,\
	(4 << SpvWordCountShift) | SpvOpVariable, 112,         113,    SpvStorageClassFunction,\
	(4 << SpvWordCountShift) | SpvOpVariable, 119,         120,    SpvStorageClassFunction,\
	(3 << SpvWordCountShift) | SpvOpStore, 9, 11,\
	(3 << SpvWordCountShift) | SpvOpStore, 14, 16,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       24, 9, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               25, 24,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       26, 14, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               27, 26,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               28, 25, 27,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       30, 9, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               31, 30,\
	(4 << SpvWordCountShift) | SpvOpFNegate, 6,            32, 31,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       33, 14, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               34, 33,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               35, 32, 34,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       37, 14, 36,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               38, 37,\
	(6 << SpvWordCountShift) | SpvOpCompositeConstruct, 12,39, 28, 35, 38,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       40, 9, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               41, 40,\
	(4 << SpvWordCountShift) | SpvOpFNegate, 6,            42, 41,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       43, 14, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               44, 43,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               45, 42, 44,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       46, 9, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               47, 46,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       48, 14, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               49, 48,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               50, 47, 49,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       51, 14, 36,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               52, 51,\
	(6 << SpvWordCountShift) | SpvOpCompositeConstruct, 12,53, 45, 50, 52,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       54, 9, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               55, 54,\
	(4 << SpvWordCountShift) | SpvOpFNegate, 6,            56, 55,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       57, 14, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               58, 57,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               59, 56, 58,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       60, 9, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               61, 60,\
	(4 << SpvWordCountShift) | SpvOpFNegate, 6,            62, 61,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       63, 14, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               64, 63,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               65, 62, 64,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       66, 14, 36,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               67, 66,\
	(6 << SpvWordCountShift) | SpvOpCompositeConstruct, 12,68, 59, 65, 67,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       69, 9, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               70, 69,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       71, 14, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               72, 71,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               73, 70, 72,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       74, 9, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               75, 74,\
	(4 << SpvWordCountShift) | SpvOpFNegate, 6,            76, 75,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       77, 14, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               78, 77,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               79, 76, 78,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       80, 14, 36,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               81, 80,\
	(6 << SpvWordCountShift) | SpvOpCompositeConstruct, 12,82, 73, 79, 81,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       83, 9, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               84, 83,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       85, 14, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               86, 85,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               87, 84, 86,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       88, 9, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               89, 88,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       90, 14, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               91, 90,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               92, 89, 91,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       93, 14, 36,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               94, 93,\
	(6 << SpvWordCountShift) | SpvOpCompositeConstruct, 12,95, 87, 92, 94,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       96, 9, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               97, 96,\
	(4 << SpvWordCountShift) | SpvOpFNegate, 6,            98, 97,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       99, 14, 22,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               100, 99,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               101, 98, 100,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       102, 9, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               103, 102,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       104, 14, 29,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               105, 104,\
	(5 << SpvWordCountShift) | SpvOpFAdd, 6,               106, 103, 105,\
	(5 << SpvWordCountShift) | SpvOpAccessChain, 23,       107, 14, 36,\
	(4 << SpvWordCountShift) | SpvOpLoad, 6,               108, 107,\
	(6 << SpvWordCountShift) | SpvOpCompositeConstruct, 12,109, 101, 106, 108,\
	(9 << SpvWordCountShift) | SpvOpCompositeConstruct, 19,110, 39, 53, 68, 82, 95, 109,\
	(3 << SpvWordCountShift) | SpvOpStore, 21, 110,\
	(3 << SpvWordCountShift) | SpvOpStore, 113, 117,\
	(4 << SpvWordCountShift) | SpvOpLoad, 118,             123, 122,\
	(4 << SpvWordCountShift) | SpvOpLoad, 118,             125, 124,\
	(5 << SpvWordCountShift) | SpvOpIMul, 118,             127, 125, 126,\
	(5 << SpvWordCountShift) | SpvOpISub, 118,             128, 123, 127,\
	(3 <<SpvWordCountShift) | SpvOpStore, 120, 128,\
	(4 <<SpvWordCountShift) | SpvOpLoad, 118,             135, 120,\
	(5 <<SpvWordCountShift) | SpvOpAccessChain, 13,       136, 21, 135,\
	(4 <<SpvWordCountShift) | SpvOpLoad, 12,              137, 136,\
	(5 <<SpvWordCountShift) | SpvOpCompositeExtract, 6,   138, 137, 0,\
	(5 <<SpvWordCountShift) | SpvOpCompositeExtract, 6,   139, 137, 1,\
	(5<<SpvWordCountShift) | SpvOpCompositeExtract, 6,   140, 137, 2,\
	(7<<SpvWordCountShift) | SpvOpCompositeConstruct,129,141, 138, 139, 140, 10,\
	(5<<SpvWordCountShift) | SpvOpAccessChain, 142,      143, 133, 134,\
	(3<<SpvWordCountShift) | SpvOpStore, 143, 141,\
	(1<<SpvWordCountShift) | SpvOpReturn,\
	(1<<SpvWordCountShift) | SpvOpFunctionEnd,\
}

typedef enum FragmentShaderDeferredVariables {
	FragmentDeferredVariable_ZEROISNOTUSED,
	FragmentDeferredExtension_GLSL450,
	FragmentDeferredFunction_Main,

	FragmentDeferredType_Void,
	FragmentDeferredType_Function,
	FragmentDeferredType_bool,

	FragmentDeferredType_float32,
	FragmentDeferredType_float32vec2,
	FragmentDeferredType_float32vec3,
	FragmentDeferredType_float32vec4,
	FragmentDeferredType_float32mat4,

	FragmentDeferredType_uint32,
	FragmentDeferredType_uint32vec2,
	FragmentDeferredType_uint32vec3,
	FragmentDeferredType_uint32vec4,

	FragmentDeferredType_int32,
	FragmentDeferredType_int32vec2,
	FragmentDeferredType_int32vec3,
	FragmentDeferredType_int32vec4,

	//constants
	FragmentDeferredConstant_float32_0f,
	FragmentDeferredConstant_float32_1f,
	FragmentDeferredConstant_float32_2f,

	FragmentDeferredConstant_uint32_0,

	FragmentDeferredConstant_int32_0,
	FragmentDeferredConstant_int32_1,
	FragmentDeferredConstant_int32_2,

	FragmentDeferredConstant_int32vec2_NULL,

	//input locations
	FragmentDeferredType_Image_float32_2D_0_0_0_0_Unknown,
	FragmentDeferredType_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown,

	FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Albedo,
	FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Position,
	FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Normal,
	FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_PBR,
	FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Transperancy,
	FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Revealage,
	FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Depth,

	//pushconstants
	FragmentDeferredType_struct_PushConstants,
	FragmentDeferredType_PushConstantPointer_struct_PushConstants,
	FragmentDeferredVariable_PushConstantPointer_struct_PushConstants,


	//output
	FragmentDeferredType_OutputPointer_float32vec4,
	FragmentDeferredConstant_float32vec4_NULL,
	FragmentDeferredVariable_OutputPointer_float32vec4_Colour,
	FragmentDeferredVariable_OutputPointer_float32vec4_Colour1,

	//function
	FragmentDeferredLabel_Start,

	FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Albedo,
	FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Position,
	FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Normal,
	FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_PBR,
	FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Transperancy,
	FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Revealage,
	FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Depth,

	FragmentDeferredLoadedVariable_float32vec4_Albedo,
	FragmentDeferredLoadedVariable_float32vec4_Position,
	FragmentDeferredLoadedVariable_float32vec4_Normal,
	FragmentDeferredLoadedVariable_float32vec4_PBR,
	FragmentDeferredLoadedVariable_float32vec4_Transperancy,
	FragmentDeferredLoadedVariable_float32vec4_Revealage,
	FragmentDeferredLoadedVariable_float32vec4_Depth,

	FragmentDeferredLoadedVariable_float32_AlbedoX,
	FragmentDeferredLoadedVariable_float32_AlbedoY,
	FragmentDeferredLoadedVariable_float32_AlbedoZ,
	FragmentDeferredLoadedVariable_float32_AlbedoW,

	FragmentDeferredLoadedVariable_float32_TransperancyX,
	FragmentDeferredLoadedVariable_float32_TransperancyY,
	FragmentDeferredLoadedVariable_float32_TransperancyZ,
	FragmentDeferredLoadedVariable_float32_TransperancyW,

	FragmentDeferredLoadedVariable_float32vec3_Albedo,
	FragmentDeferredLoadedVariable_float32vec3_Transperancy,

	FragmentDeferredLoadedVariable_float32_op0,
	FragmentDeferredLoadedVariable_float32_op1,
	FragmentDeferredLoadedVariable_float32_op2,
	FragmentDeferredLoadedVariable_float32_op3,
	FragmentDeferredLoadedVariable_float32_op4,

	FragmentDeferredLoadedVariable_float32vec3_op0,
	FragmentDeferredLoadedVariable_float32vec3_op1,
	FragmentDeferredLoadedVariable_float32vec3_op2,

	FragmentDeferredLoadedVariable_float32vec4_op0,


	FragmentDeferredVariables_MAX,
}FragmentShaderDefferedVariables;
#define FragmentShaderDeferredSize (493 * sizeof(SPIRV))
#define FragmentShaderDeferred() {\
SPIRV_Header(FragmentDeferredVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityImageQuery,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityInputAttachment,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, FragmentDeferredExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(15<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelFragment, FragmentDeferredFunction_Main, 'niam', '\0', FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Albedo, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Position,\
FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Normal, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_PBR, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Transperancy, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Revealage,\
FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Depth, FragmentDeferredVariable_PushConstantPointer_struct_PushConstants, FragmentDeferredVariable_OutputPointer_float32vec4_Colour, FragmentDeferredVariable_OutputPointer_float32vec4_Colour1, \
(3<<SpvWordCountShift)|SpvOpExecutionMode, FragmentDeferredFunction_Main, SpvExecutionModeOriginUpperLeft,\
/*DECORATION*/\
/*INPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Albedo, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Albedo, SpvDecorationBinding, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Albedo, SpvDecorationInputAttachmentIndex, 0,\
\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Position, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Position, SpvDecorationBinding, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Position, SpvDecorationInputAttachmentIndex, 1,\
\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Normal, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Normal, SpvDecorationBinding, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Normal, SpvDecorationInputAttachmentIndex, 2,\
\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_PBR, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_PBR, SpvDecorationBinding, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_PBR, SpvDecorationInputAttachmentIndex, 3,\
\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Transperancy, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Transperancy, SpvDecorationBinding, 4,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Transperancy, SpvDecorationInputAttachmentIndex, 4,\
\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Revealage, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Revealage, SpvDecorationBinding, 5,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Revealage, SpvDecorationInputAttachmentIndex, 5,\
\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Depth, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Depth, SpvDecorationBinding, 6,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Depth, SpvDecorationInputAttachmentIndex, 6,\
/*pushconstants*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentDeferredType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentDeferredType_struct_PushConstants, 1, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentDeferredType_struct_PushConstants, 2, SpvDecorationOffset, 24,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentDeferredType_struct_PushConstants, 3, SpvDecorationOffset, 32,\
(3<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_OutputPointer_float32vec4_Colour, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentDeferredVariable_OutputPointer_float32vec4_Colour1, SpvDecorationLocation, 1,\
\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, FragmentDeferredType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, FragmentDeferredType_Function, FragmentDeferredType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, FragmentDeferredType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, FragmentDeferredType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentDeferredType_float32vec2, FragmentDeferredType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentDeferredType_float32vec3, FragmentDeferredType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentDeferredType_float32vec4, FragmentDeferredType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, FragmentDeferredType_float32mat4, FragmentDeferredType_float32vec4, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, FragmentDeferredType_uint32, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentDeferredType_uint32vec2, FragmentDeferredType_uint32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentDeferredType_uint32vec3, FragmentDeferredType_uint32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentDeferredType_uint32vec4, FragmentDeferredType_uint32, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, FragmentDeferredType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentDeferredType_int32vec2, FragmentDeferredType_int32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentDeferredType_int32vec3, FragmentDeferredType_int32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentDeferredType_int32vec4, FragmentDeferredType_int32, 4,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentDeferredType_float32, FragmentDeferredConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentDeferredType_float32, FragmentDeferredConstant_float32_1f, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentDeferredType_float32, FragmentDeferredConstant_float32_2f, 1073741824,\
\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentDeferredType_uint32, FragmentDeferredConstant_uint32_0, 0,\
\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentDeferredType_int32, FragmentDeferredConstant_int32_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentDeferredType_int32, FragmentDeferredConstant_int32_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentDeferredType_int32, FragmentDeferredConstant_int32_2, 2,\
\
(3<<SpvWordCountShift)|SpvOpConstantNull, FragmentDeferredType_int32vec2, FragmentDeferredConstant_int32vec2_NULL,\
/*input locations*/\
(9<<SpvWordCountShift)|SpvOpTypeImage, FragmentDeferredType_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredType_float32, SpvDimSubpassData, 0, 0, 0, 2, SpvImageFormatUnknown,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentDeferredType_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown, SpvStorageClassUniformConstant, FragmentDeferredType_Image_float32_2D_0_0_0_0_Unknown,\
\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentDeferredType_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Albedo, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentDeferredType_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Position, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentDeferredType_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Normal, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentDeferredType_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_PBR, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentDeferredType_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Transperancy, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentDeferredType_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Revealage, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentDeferredType_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Depth, SpvStorageClassUniformConstant,\
/*pushconstants*/\
(6<<SpvWordCountShift)|SpvOpTypeStruct, FragmentDeferredType_struct_PushConstants, FragmentDeferredType_float32vec4, FragmentDeferredType_float32vec2, FragmentDeferredType_float32, FragmentDeferredType_int32vec2,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentDeferredType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, FragmentDeferredType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentDeferredType_PushConstantPointer_struct_PushConstants, FragmentDeferredVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
/*outputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentDeferredType_OutputPointer_float32vec4, SpvStorageClassOutput, FragmentDeferredType_float32vec4,\
(3<<SpvWordCountShift)|SpvOpConstantNull, FragmentDeferredType_float32vec4, FragmentDeferredConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentDeferredType_OutputPointer_float32vec4, FragmentDeferredVariable_OutputPointer_float32vec4_Colour, SpvStorageClassOutput, FragmentDeferredConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentDeferredType_OutputPointer_float32vec4, FragmentDeferredVariable_OutputPointer_float32vec4_Colour1, SpvStorageClassOutput, FragmentDeferredConstant_float32vec4_NULL,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, FragmentDeferredType_Void, FragmentDeferredFunction_Main, SpvFunctionControlMaskNone, FragmentDeferredType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, FragmentDeferredLabel_Start,\
	/*Loading Variables*/\
	(4<<SpvWordCountShift)|SpvOpLoad, FragmentDeferredType_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Albedo, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Albedo,\
	(4<<SpvWordCountShift)|SpvOpLoad, FragmentDeferredType_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Position, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Position,\
	(4<<SpvWordCountShift)|SpvOpLoad, FragmentDeferredType_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Normal, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Normal,\
	(4<<SpvWordCountShift)|SpvOpLoad, FragmentDeferredType_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_PBR, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_PBR,\
	(4<<SpvWordCountShift)|SpvOpLoad, FragmentDeferredType_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Transperancy, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Transperancy,\
	(4<<SpvWordCountShift)|SpvOpLoad, FragmentDeferredType_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Revealage, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Revealage,\
	(4<<SpvWordCountShift)|SpvOpLoad, FragmentDeferredType_Image_float32_2D_0_0_0_0_Unknown, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Depth, FragmentDeferredVariable_UniformConstantPointer_Image_float32_2D_0_0_0_0_Unknown_Depth,\
	\
	(5<<SpvWordCountShift)|SpvOpImageRead, FragmentDeferredType_float32vec4, FragmentDeferredLoadedVariable_float32vec4_Albedo, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Albedo, FragmentDeferredConstant_int32vec2_NULL,\
	(5<<SpvWordCountShift)|SpvOpImageRead, FragmentDeferredType_float32vec4, FragmentDeferredLoadedVariable_float32vec4_Position, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Position, FragmentDeferredConstant_int32vec2_NULL,\
	(5<<SpvWordCountShift)|SpvOpImageRead, FragmentDeferredType_float32vec4, FragmentDeferredLoadedVariable_float32vec4_Normal, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Normal, FragmentDeferredConstant_int32vec2_NULL,\
	(5<<SpvWordCountShift)|SpvOpImageRead, FragmentDeferredType_float32vec4, FragmentDeferredLoadedVariable_float32vec4_PBR, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_PBR, FragmentDeferredConstant_int32vec2_NULL,\
	(5<<SpvWordCountShift)|SpvOpImageRead, FragmentDeferredType_float32vec4, FragmentDeferredLoadedVariable_float32vec4_Transperancy, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Transperancy, FragmentDeferredConstant_int32vec2_NULL,\
	(5<<SpvWordCountShift)|SpvOpImageRead, FragmentDeferredType_float32vec4, FragmentDeferredLoadedVariable_float32vec4_Revealage, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Revealage, FragmentDeferredConstant_int32vec2_NULL,\
	(5<<SpvWordCountShift)|SpvOpImageRead, FragmentDeferredType_float32vec4, FragmentDeferredLoadedVariable_float32vec4_Depth, FragmentDeferredLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Depth, FragmentDeferredConstant_int32vec2_NULL,\
	/*colour = vec4(transperancy.a * transperancy.rgb + (1 - transperancy.a) * albedo.rgb, (transperancy.a + albedo.a));*/\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_AlbedoX, FragmentDeferredLoadedVariable_float32vec4_Albedo, 0,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_AlbedoY, FragmentDeferredLoadedVariable_float32vec4_Albedo, 1,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_AlbedoZ, FragmentDeferredLoadedVariable_float32vec4_Albedo, 2,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_AlbedoW, FragmentDeferredLoadedVariable_float32vec4_Albedo, 3,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_TransperancyX, FragmentDeferredLoadedVariable_float32vec4_Transperancy, 0,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_TransperancyY, FragmentDeferredLoadedVariable_float32vec4_Transperancy, 1,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_TransperancyZ, FragmentDeferredLoadedVariable_float32vec4_Transperancy, 2,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_TransperancyW, FragmentDeferredLoadedVariable_float32vec4_Transperancy, 3,\
	\
	(6<<SpvWordCountShift)|SpvOpCompositeConstruct, FragmentDeferredType_float32vec3, FragmentDeferredLoadedVariable_float32vec3_Albedo, FragmentDeferredLoadedVariable_float32_AlbedoX, FragmentDeferredLoadedVariable_float32_AlbedoY, FragmentDeferredLoadedVariable_float32_AlbedoZ,\
	(6<<SpvWordCountShift)|SpvOpCompositeConstruct, FragmentDeferredType_float32vec3, FragmentDeferredLoadedVariable_float32vec3_Transperancy, FragmentDeferredLoadedVariable_float32_TransperancyX, FragmentDeferredLoadedVariable_float32_TransperancyY, FragmentDeferredLoadedVariable_float32_TransperancyZ,\
	\
	(5<<SpvWordCountShift)|SpvOpFSub, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_op0, FragmentDeferredConstant_float32_1f, FragmentDeferredLoadedVariable_float32_TransperancyW,\
	(5<<SpvWordCountShift)|SpvOpFAdd, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_op1, FragmentDeferredLoadedVariable_float32_TransperancyW, FragmentDeferredLoadedVariable_float32_AlbedoW,\
	(5<<SpvWordCountShift)|SpvOpVectorTimesScalar, FragmentDeferredType_float32vec3, FragmentDeferredLoadedVariable_float32vec3_op0, FragmentDeferredLoadedVariable_float32vec3_Transperancy, FragmentDeferredLoadedVariable_float32_TransperancyW,\
	(5<<SpvWordCountShift)|SpvOpVectorTimesScalar, FragmentDeferredType_float32vec3, FragmentDeferredLoadedVariable_float32vec3_op1, FragmentDeferredLoadedVariable_float32vec3_Albedo, FragmentDeferredLoadedVariable_float32_op0,\
	(5<<SpvWordCountShift)|SpvOpFAdd, FragmentDeferredType_float32vec3, FragmentDeferredLoadedVariable_float32vec3_op2, FragmentDeferredLoadedVariable_float32vec3_op0, FragmentDeferredLoadedVariable_float32vec3_op1,\
	\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_op2, FragmentDeferredLoadedVariable_float32vec3_op2, 0,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_op3, FragmentDeferredLoadedVariable_float32vec3_op2, 1,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, FragmentDeferredType_float32, FragmentDeferredLoadedVariable_float32_op4, FragmentDeferredLoadedVariable_float32vec3_op2, 2,\
	(7<<SpvWordCountShift)|SpvOpCompositeConstruct, FragmentDeferredType_float32vec4, FragmentDeferredLoadedVariable_float32vec4_op0, FragmentDeferredLoadedVariable_float32_op2, FragmentDeferredLoadedVariable_float32_op3, FragmentDeferredLoadedVariable_float32_op4, FragmentDeferredLoadedVariable_float32_op1,\
	(3<<SpvWordCountShift)|SpvOpStore, FragmentDeferredVariable_OutputPointer_float32vec4_Colour, FragmentDeferredLoadedVariable_float32vec4_op0,\
	(3<<SpvWordCountShift)|SpvOpStore, FragmentDeferredVariable_OutputPointer_float32vec4_Colour1, FragmentDeferredLoadedVariable_float32vec4_op0,\
/*FUNCTION END*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}


///////////////////////////////////////////////////////////////////////////////////////////////
//2D
///////////////////////////////////////////////////////////////////////////////////////////////

typedef enum VertexShader2DVariables {
	Vertex2DVariable_ZEROISNOTUSED,
	//Vertex2DExtension_GLSL450,
	Vertex2DFunction_Main,

	Vertex2DType_Void,
	Vertex2DType_Function,
	Vertex2DType_bool,

	Vertex2DType_float32,
	Vertex2DType_float32vec2,
	Vertex2DType_float32vec3,
	Vertex2DType_float32vec4,
	Vertex2DType_float32mat4,

	Vertex2DType_uint32,
	Vertex2DType_uint32vec2,
	Vertex2DType_uint32vec3,
	Vertex2DType_uint32vec4,

	Vertex2DType_int32,
	Vertex2DType_int32vec2,
	Vertex2DType_int32vec3,
	Vertex2DType_int32vec4,

	//constants
	Vertex2DConstant_float32_0f,
	Vertex2DConstant_float32_1f,
	Vertex2DConstant_float32_2f,

	Vertex2DConstant_uint_0,

	Vertex2DConstant_int_0,
	Vertex2DConstant_int_1,
	Vertex2DConstant_int_6,

	Vertex2DConstant_float32vec2_NULL,
	Vertex2DConstant_float32vec3_NULL,
	Vertex2DConstant_int32vec2_NULL,

	Vertex2DConstant_float32vec2_1f_0f,
	Vertex2DConstant_float32vec2_0f_1f,
	Vertex2DConstant_float32vec2_0f_0f,
	Vertex2DConstant_float32vec2_1f_1f,


	//inputs
	Vertex2DType_InputPointer_float32vec2,
	Vertex2DType_InputPointer_float32vec3,
	Vertex2DType_InputPointer_int32vec2,

	Vertex2DVariable_InputPointer_float32vec2_Size,
	Vertex2DVariable_InputPointer_float32vec3_Position,
	Vertex2DVariable_InputPointer_float32vec2_BoundingBoxSize,
	Vertex2DVariable_InputPointer_float32vec2_BoundingBoxPosition,
	Vertex2DVariable_InputPointer_int32vec2_TextureOffset,
	Vertex2DVariable_InputPointer_int32vec2_TextureSize,

	Vertex2DType_InputPointer_int32,
	Vertex2DVariable_InputPointer_VertexIndex,
	Vertex2DVariable_InputPointer_InstanceIndex,


	Vertex2DType_struct_PushConstants,
	Vertex2DType_PushConstantPointer_struct_PushConstants,
	Vertex2DVariable_PushConstantPointer_struct_PushConstants,

	//outputs
	Vertex2DType_OutputPointer_float32vec2,
	Vertex2DType_OutputPointer_float32vec3,
	Vertex2DType_OutputPointer_float32vec4,
	Vertex2DType_OutputPointer_int32vec2,

	Vertex2DVariable_OutputPointer_float32vec2_Size,
	Vertex2DVariable_OutputPointer_float32vec3_Position,
	Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxSize,
	Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxPosition,
	Vertex2DVariable_OutputPointer_int32vec2_TextureOffset,
	Vertex2DVariable_OutputPointer_int32vec2_TextureSize,
	Vertex2DVariable_OutputPointer_float32vec2_UVS,

	Vertex2DType_float32_Array_1,
	Vertex2DType_struct_BuiltIn,
	Vertex2DType_OutputPointer_struct_BuiltIn,
	Vertex2DVariable_OutputPointer_struct_BuiltIn,
	Vertex2DVariable_OutputPointer_float32vec4_Position,

	Vertex2DType_float32vec3_Array_6_Positions,
	Vertex2DType_float32vec2_Array_6_UVS,

	Vertex2DType_FunctionPointer_float32vec3_Array_6_Positions,
	Vertex2DType_FunctionPointer_float32vec2_Array_6_UVS,

	Vertex2DVariable_FunctionPointer_float32vec3_Array_6_Positions,
	Vertex2DVariable_FunctionPointer_float32vec2_Array_6_UVS,

	Vertex2DType_FunctionPointer_float32vec3,
	Vertex2DType_FunctionPointer_float32vec2,

	Vertex2DLabel_Start,


	Vertex2DLoadedVariable_float32vec2_Size,
	Vertex2DLoadedVariable_float32vec3_Position,
	Vertex2DLoadedVariable_float32vec2_BoundingBoxSize,
	Vertex2DLoadedVariable_float32vec2_BoundingBoxPosition,
	Vertex2DLoadedVariable_int32vec2_TextureOffset,
	Vertex2DLoadedVariable_int32vec2_TextureSize,
	//Vertex2DLoadedVariable_float32vec2_UVS,

	Vertex2DLoadedVariable_float32vec2_SizeMul2,
	Vertex2DLoadedVariable_float32vec2_BoundingBoxSizeMul2,

	Vertex2DLoadedVariable_float32vec2_BoundingBoxPositionMul2,
	Vertex2DLoadedVariable_float32vec2_BoundingBoxPositionMul2Sub1,

	Vertex2DLoadedVariable_float32vec2_op0,
	Vertex2DLoadedVariable_float32vec2_op1,
	Vertex2DLoadedVariable_float32vec2_op2,
	Vertex2DLoadedVariable_float32vec2_op3,

	Vertex2DLoadedVariable_float32_op0,
	Vertex2DLoadedVariable_float32_op1,


	Vertex2DLoadedVariable_float32_op4,
	Vertex2DLoadedVariable_float32_op5,
	Vertex2DLoadedVariable_float32_op6,
	Vertex2DLoadedVariable_float32vec3_PositionMul2Sub1,
	Vertex2DLoadedVariable_float32_op7,
	Vertex2DLoadedVariable_float32_op8,
	Vertex2DLoadedVariable_float32_op9,
	Vertex2DLoadedVariable_float32_op10,
	Vertex2DLoadedVariable_float32_op11,
	Vertex2DLoadedVariable_float32_op12,
	Vertex2DLoadedVariable_float32_op13,
	Vertex2DLoadedVariable_float32_op14,
	Vertex2DLoadedVariable_float32_op15,
	Vertex2DLoadedVariable_float32_op16,
	Vertex2DLoadedVariable_float32_op17,
	Vertex2DLoadedVariable_float32_op18,
	Vertex2DLoadedVariable_float32_op19,
	Vertex2DLoadedVariable_float32_op20,


	Vertex2DLoadedVariable_float32vec3_op0,
	Vertex2DLoadedVariable_float32vec3_op1,
	Vertex2DLoadedVariable_float32vec3_op2,
	Vertex2DLoadedVariable_float32vec3_op3,

	Vertex2DLoadedVariable_float32vec3_Array_6_Positions,
	Vertex2DLoadedVariable_float32vec2_Array_6_UVS,

	Vertex2DLoadedVariable_int32_VertexIndex,
	Vertex2DLoadedVariable_int32_InstanceIndex,

	Vertex2DLoadedVariable_int32_op0,
	Vertex2DLoadedVariable_int32_index,

	Vertex2DVariable_FunctionPointer_float32vec3_IndexedPositions,
	Vertex2DVariable_FunctionPointer_float32vec2_IndexedUVS,

	Vertex2DLoadedVariable_float32vec3_op4,

	Vertex2DLoadedVariable_float32vec2_op5,
	Vertex2DLoadedVariable_float32vec2_op6,
	Vertex2DLoadedVariable_float32vec4_op7,

	Vertex2DVariables_MAX
}VertexShader2DVariables;
#define VertexShader2DSize (721 * sizeof(SPIRV))
#define VertexShader2D() {\
SPIRV_Header(Vertex2DVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(22<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelVertex, Vertex2DFunction_Main, 'niam', '\0',Vertex2DVariable_InputPointer_float32vec2_Size, Vertex2DVariable_InputPointer_float32vec3_Position, Vertex2DVariable_InputPointer_float32vec2_BoundingBoxSize,\
Vertex2DVariable_InputPointer_float32vec2_BoundingBoxPosition, Vertex2DVariable_InputPointer_int32vec2_TextureOffset, Vertex2DVariable_InputPointer_int32vec2_TextureSize, Vertex2DVariable_InputPointer_VertexIndex, Vertex2DVariable_InputPointer_InstanceIndex, \
Vertex2DVariable_PushConstantPointer_struct_PushConstants, 	Vertex2DVariable_OutputPointer_float32vec2_Size, Vertex2DVariable_OutputPointer_float32vec3_Position, Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxSize, Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxPosition,\
Vertex2DVariable_OutputPointer_int32vec2_TextureOffset, Vertex2DVariable_OutputPointer_int32vec2_TextureSize, Vertex2DVariable_OutputPointer_float32vec2_UVS, Vertex2DVariable_OutputPointer_struct_BuiltIn,\
/*DECORATION*/\
/*INPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_InputPointer_float32vec2_Size, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_InputPointer_float32vec3_Position, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_InputPointer_float32vec2_BoundingBoxSize, SpvDecorationLocation, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_InputPointer_float32vec2_BoundingBoxPosition, SpvDecorationLocation, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_InputPointer_int32vec2_TextureOffset, SpvDecorationLocation, 4,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_InputPointer_int32vec2_TextureSize, SpvDecorationLocation, 5,\
/*Built In*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_InputPointer_VertexIndex, SpvDecorationBuiltIn, SpvBuiltInVertexIndex,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_InputPointer_InstanceIndex, SpvDecorationBuiltIn, SpvBuiltInInstanceIndex,\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex2DType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex2DType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex2DType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex2DType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, Vertex2DType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_OutputPointer_float32vec2_Size, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_OutputPointer_float32vec3_Position, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxSize, SpvDecorationLocation, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxPosition, SpvDecorationLocation, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_OutputPointer_int32vec2_TextureOffset, SpvDecorationLocation, 4,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_OutputPointer_int32vec2_TextureSize, SpvDecorationLocation, 5,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex2DVariable_OutputPointer_float32vec2_UVS, SpvDecorationLocation, 6,\
/*Built In*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex2DType_struct_BuiltIn, 0, SpvDecorationBuiltIn, SpvBuiltInPosition,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex2DType_struct_BuiltIn, 1, SpvDecorationBuiltIn, SpvBuiltInPointSize,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex2DType_struct_BuiltIn, 2, SpvDecorationBuiltIn, SpvBuiltInClipDistance,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex2DType_struct_BuiltIn, 3, SpvDecorationBuiltIn, SpvBuiltInCullDistance,\
(3<<SpvWordCountShift)|SpvOpDecorate, Vertex2DType_struct_BuiltIn, SpvDecorationBlock,\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, Vertex2DType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, Vertex2DType_Function, Vertex2DType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, Vertex2DType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, Vertex2DType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex2DType_float32vec2, Vertex2DType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex2DType_float32vec3, Vertex2DType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex2DType_float32vec4, Vertex2DType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, Vertex2DType_float32mat4, Vertex2DType_float32vec4, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, Vertex2DType_uint32, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex2DType_uint32vec2, Vertex2DType_uint32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex2DType_uint32vec3, Vertex2DType_uint32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex2DType_uint32vec4, Vertex2DType_uint32, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, Vertex2DType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex2DType_int32vec2, Vertex2DType_int32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex2DType_int32vec3, Vertex2DType_int32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex2DType_int32vec4, Vertex2DType_int32, 4,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex2DType_float32, Vertex2DConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex2DType_float32, Vertex2DConstant_float32_1f, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex2DType_float32, Vertex2DConstant_float32_2f, 1073741824,\
\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex2DType_uint32, Vertex2DConstant_uint_0, 0,\
\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex2DType_int32, Vertex2DConstant_int_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex2DType_int32, Vertex2DConstant_int_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex2DType_int32, Vertex2DConstant_int_6, 6,\
/*UV value constants*/\
(5<<SpvWordCountShift)|SpvOpConstantComposite, Vertex2DType_float32vec2, Vertex2DConstant_float32vec2_1f_0f, Vertex2DConstant_float32_1f, Vertex2DConstant_float32_0f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, Vertex2DType_float32vec2, Vertex2DConstant_float32vec2_0f_1f, Vertex2DConstant_float32_0f, Vertex2DConstant_float32_1f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, Vertex2DType_float32vec2, Vertex2DConstant_float32vec2_0f_0f, Vertex2DConstant_float32_0f, Vertex2DConstant_float32_0f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, Vertex2DType_float32vec2, Vertex2DConstant_float32vec2_1f_1f, Vertex2DConstant_float32_1f, Vertex2DConstant_float32_1f,\
/*Input/Output Type Declarations*/\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpTypeStruct, Vertex2DType_struct_PushConstants, Vertex2DType_float32mat4, Vertex2DType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, Vertex2DType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_PushConstantPointer_struct_PushConstants, Vertex2DVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
/*inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_InputPointer_int32, SpvStorageClassInput, Vertex2DType_int32,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_InputPointer_int32, Vertex2DVariable_InputPointer_VertexIndex, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_InputPointer_int32, Vertex2DVariable_InputPointer_InstanceIndex, SpvStorageClassInput,\
/*built in output*/\
(4<<SpvWordCountShift)|SpvOpTypeArray, Vertex2DType_float32_Array_1, Vertex2DType_float32, Vertex2DConstant_int_1,\
(6<<SpvWordCountShift)|SpvOpTypeStruct, Vertex2DType_struct_BuiltIn, Vertex2DType_float32vec4, Vertex2DType_float32, Vertex2DType_float32_Array_1, Vertex2DType_float32_Array_1,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_OutputPointer_struct_BuiltIn, SpvStorageClassOutput, Vertex2DType_struct_BuiltIn,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_OutputPointer_struct_BuiltIn, Vertex2DVariable_OutputPointer_struct_BuiltIn, SpvStorageClassOutput,\
/*input locations*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_InputPointer_float32vec2, SpvStorageClassInput, Vertex2DType_float32vec2,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_InputPointer_float32vec3, SpvStorageClassInput, Vertex2DType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_InputPointer_int32vec2, SpvStorageClassInput, Vertex2DType_int32vec2,\
\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_InputPointer_float32vec2, Vertex2DVariable_InputPointer_float32vec2_Size, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_InputPointer_float32vec3, Vertex2DVariable_InputPointer_float32vec3_Position, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_InputPointer_float32vec2, Vertex2DVariable_InputPointer_float32vec2_BoundingBoxSize, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_InputPointer_float32vec2, Vertex2DVariable_InputPointer_float32vec2_BoundingBoxPosition, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_InputPointer_int32vec2, Vertex2DVariable_InputPointer_int32vec2_TextureOffset, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_InputPointer_int32vec2, Vertex2DVariable_InputPointer_int32vec2_TextureSize, SpvStorageClassInput,\
/*output inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_OutputPointer_float32vec2, SpvStorageClassOutput, Vertex2DType_float32vec2,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_OutputPointer_float32vec3, SpvStorageClassOutput, Vertex2DType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_OutputPointer_float32vec4, SpvStorageClassOutput, Vertex2DType_float32vec4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_OutputPointer_int32vec2, SpvStorageClassOutput, Vertex2DType_int32vec2,\
(3<<SpvWordCountShift)|SpvOpConstantNull, Vertex2DType_float32vec2, Vertex2DConstant_float32vec2_NULL,\
(3<<SpvWordCountShift)|SpvOpConstantNull, Vertex2DType_float32vec3, Vertex2DConstant_float32vec3_NULL,\
(3<<SpvWordCountShift)|SpvOpConstantNull, Vertex2DType_int32vec2, Vertex2DConstant_int32vec2_NULL,\
\
(5<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_OutputPointer_float32vec2, Vertex2DVariable_OutputPointer_float32vec2_Size, SpvStorageClassOutput, Vertex2DConstant_float32vec2_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_OutputPointer_float32vec3, Vertex2DVariable_OutputPointer_float32vec3_Position, SpvStorageClassOutput, Vertex2DConstant_float32vec3_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_OutputPointer_float32vec2, Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxSize, SpvStorageClassOutput, Vertex2DConstant_float32vec2_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_OutputPointer_float32vec2, Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxPosition, SpvStorageClassOutput, Vertex2DConstant_float32vec2_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_OutputPointer_int32vec2, Vertex2DVariable_OutputPointer_int32vec2_TextureOffset, SpvStorageClassOutput, Vertex2DConstant_int32vec2_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_OutputPointer_int32vec2, Vertex2DVariable_OutputPointer_int32vec2_TextureSize, SpvStorageClassOutput, Vertex2DConstant_int32vec2_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_OutputPointer_float32vec2, Vertex2DVariable_OutputPointer_float32vec2_UVS, SpvStorageClassOutput, Vertex2DConstant_float32vec2_NULL,\
\
(4<<SpvWordCountShift)|SpvOpTypeArray, Vertex2DType_float32vec3_Array_6_Positions, Vertex2DType_float32vec3, Vertex2DConstant_int_6,\
(4<<SpvWordCountShift)|SpvOpTypeArray, Vertex2DType_float32vec2_Array_6_UVS, Vertex2DType_float32vec2, Vertex2DConstant_int_6,\
\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_FunctionPointer_float32vec3_Array_6_Positions, SpvStorageClassFunction, Vertex2DType_float32vec3_Array_6_Positions,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_FunctionPointer_float32vec2_Array_6_UVS, SpvStorageClassFunction, Vertex2DType_float32vec2_Array_6_UVS,\
\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_FunctionPointer_float32vec3, SpvStorageClassFunction, Vertex2DType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex2DType_FunctionPointer_float32vec2, SpvStorageClassFunction, Vertex2DType_float32vec2,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, Vertex2DType_Void, Vertex2DFunction_Main, SpvFunctionControlMaskNone, Vertex2DType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, Vertex2DLabel_Start,\
/*create vars*/\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_FunctionPointer_float32vec3_Array_6_Positions, Vertex2DVariable_FunctionPointer_float32vec3_Array_6_Positions, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex2DType_FunctionPointer_float32vec2_Array_6_UVS, Vertex2DVariable_FunctionPointer_float32vec2_Array_6_UVS, SpvStorageClassFunction,\
/*Assign inputs to outputs and also load variables*/\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_Size, Vertex2DVariable_InputPointer_float32vec2_Size,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_OutputPointer_float32vec2_Size, Vertex2DLoadedVariable_float32vec2_Size,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex2DType_float32vec3, Vertex2DLoadedVariable_float32vec3_Position, Vertex2DVariable_InputPointer_float32vec3_Position,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_OutputPointer_float32vec3_Position, Vertex2DLoadedVariable_float32vec3_Position,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_BoundingBoxSize, Vertex2DVariable_InputPointer_float32vec2_BoundingBoxSize,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxSize, Vertex2DLoadedVariable_float32vec2_BoundingBoxSize,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_BoundingBoxPosition, Vertex2DVariable_InputPointer_float32vec2_BoundingBoxPosition,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxPosition, Vertex2DLoadedVariable_float32vec2_BoundingBoxPosition,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex2DType_int32vec2, Vertex2DLoadedVariable_int32vec2_TextureOffset, Vertex2DVariable_InputPointer_int32vec2_TextureOffset,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_OutputPointer_int32vec2_TextureOffset, Vertex2DLoadedVariable_int32vec2_TextureOffset,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex2DType_int32vec2, Vertex2DLoadedVariable_int32vec2_TextureSize, Vertex2DVariable_InputPointer_int32vec2_TextureSize,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_OutputPointer_int32vec2_TextureSize, Vertex2DLoadedVariable_int32vec2_TextureSize,\
/*processing size*/\
(5<<SpvWordCountShift)|SpvOpVectorTimesScalar, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_SizeMul2, Vertex2DLoadedVariable_float32vec2_Size, Vertex2DConstant_float32_2f,\
/*processing position*/\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op0, Vertex2DLoadedVariable_float32vec3_Position, 0,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op1, Vertex2DLoadedVariable_float32vec3_Position, 1,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_op0, Vertex2DLoadedVariable_float32_op0, Vertex2DLoadedVariable_float32_op1,\
(5<<SpvWordCountShift)|SpvOpVectorTimesScalar, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_op1, Vertex2DLoadedVariable_float32vec2_op0, Vertex2DConstant_float32_2f,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_op2, Vertex2DConstant_float32_1f, Vertex2DConstant_float32_1f,\
(5<<SpvWordCountShift)|SpvOpFSub, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_op3, Vertex2DLoadedVariable_float32vec2_op1, Vertex2DLoadedVariable_float32vec2_op2,\
/*processing bbox size*/\
(5<<SpvWordCountShift)|SpvOpVectorTimesScalar, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_BoundingBoxSizeMul2, Vertex2DLoadedVariable_float32vec2_BoundingBoxSize, Vertex2DConstant_float32_2f,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxSize, Vertex2DLoadedVariable_float32vec2_BoundingBoxSizeMul2,\
/*processing bbox position*/\
(5<<SpvWordCountShift)|SpvOpVectorTimesScalar, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_BoundingBoxPositionMul2, Vertex2DLoadedVariable_float32vec2_BoundingBoxPosition, Vertex2DConstant_float32_2f,\
(5<<SpvWordCountShift)|SpvOpFSub, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_BoundingBoxPositionMul2Sub1, Vertex2DLoadedVariable_float32vec2_BoundingBoxPositionMul2, Vertex2DLoadedVariable_float32vec2_op2,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_OutputPointer_float32vec2_BoundingBoxPosition, Vertex2DLoadedVariable_float32vec2_BoundingBoxPositionMul2Sub1,\
/*building vec*/\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op4, Vertex2DLoadedVariable_float32vec2_op3, 0,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op5, Vertex2DLoadedVariable_float32vec2_op3, 1,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op6, Vertex2DLoadedVariable_float32vec3_Position, 2,\
(6<<SpvWordCountShift)|SpvOpCompositeConstruct, Vertex2DType_float32vec3, Vertex2DLoadedVariable_float32vec3_PositionMul2Sub1, Vertex2DLoadedVariable_float32_op4, Vertex2DLoadedVariable_float32_op5, Vertex2DLoadedVariable_float32_op6,\
\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op7, Vertex2DLoadedVariable_float32vec2_SizeMul2, 0,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op8, Vertex2DLoadedVariable_float32vec2_SizeMul2, 1,\
/*positions array*/\
(5<<SpvWordCountShift)|SpvOpFAdd, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op9, Vertex2DLoadedVariable_float32_op7, Vertex2DLoadedVariable_float32_op4,\
(4<<SpvWordCountShift)|SpvOpFNegate, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op10, Vertex2DLoadedVariable_float32_op8,\
(5<<SpvWordCountShift)|SpvOpFAdd, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op11, Vertex2DLoadedVariable_float32_op10, Vertex2DLoadedVariable_float32_op5,\
(6<<SpvWordCountShift)|SpvOpCompositeConstruct, Vertex2DType_float32vec3, Vertex2DLoadedVariable_float32vec3_op0, Vertex2DLoadedVariable_float32_op9, Vertex2DLoadedVariable_float32_op11, Vertex2DLoadedVariable_float32_op6,\
(4<<SpvWordCountShift)|SpvOpFNegate, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op12, Vertex2DLoadedVariable_float32_op7,\
(5<<SpvWordCountShift)|SpvOpFAdd, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op13, Vertex2DLoadedVariable_float32_op12, Vertex2DLoadedVariable_float32_op4,\
(5<<SpvWordCountShift)|SpvOpFAdd, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op14, Vertex2DLoadedVariable_float32_op8, Vertex2DLoadedVariable_float32_op5,\
(6<<SpvWordCountShift)|SpvOpCompositeConstruct, Vertex2DType_float32vec3, Vertex2DLoadedVariable_float32vec3_op1, Vertex2DLoadedVariable_float32_op13, Vertex2DLoadedVariable_float32_op14, Vertex2DLoadedVariable_float32_op6,\
(4<<SpvWordCountShift)|SpvOpFNegate, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op15, Vertex2DLoadedVariable_float32_op7,\
(5<<SpvWordCountShift)|SpvOpFAdd, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op16, Vertex2DLoadedVariable_float32_op15, Vertex2DLoadedVariable_float32_op4,\
(4<<SpvWordCountShift)|SpvOpFNegate, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op17, Vertex2DLoadedVariable_float32_op8,\
(5<<SpvWordCountShift)|SpvOpFAdd, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op18, Vertex2DLoadedVariable_float32_op17, Vertex2DLoadedVariable_float32_op5,\
(6<<SpvWordCountShift)|SpvOpCompositeConstruct, Vertex2DType_float32vec3, Vertex2DLoadedVariable_float32vec3_op2, Vertex2DLoadedVariable_float32_op16, Vertex2DLoadedVariable_float32_op18, Vertex2DLoadedVariable_float32_op6,\
(5<<SpvWordCountShift)|SpvOpFAdd, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op19, Vertex2DLoadedVariable_float32_op7, Vertex2DLoadedVariable_float32_op4,\
(5<<SpvWordCountShift)|SpvOpFAdd, Vertex2DType_float32, Vertex2DLoadedVariable_float32_op20, Vertex2DLoadedVariable_float32_op8, Vertex2DLoadedVariable_float32_op5,\
(6<<SpvWordCountShift)|SpvOpCompositeConstruct, Vertex2DType_float32vec3, Vertex2DLoadedVariable_float32vec3_op3, Vertex2DLoadedVariable_float32_op19, Vertex2DLoadedVariable_float32_op20, Vertex2DLoadedVariable_float32_op6,\
(9<<SpvWordCountShift)|SpvOpCompositeConstruct, Vertex2DType_float32vec3_Array_6_Positions, Vertex2DLoadedVariable_float32vec3_Array_6_Positions,\
	 Vertex2DLoadedVariable_float32vec3_op0, Vertex2DLoadedVariable_float32vec3_op1, Vertex2DLoadedVariable_float32vec3_op2, Vertex2DLoadedVariable_float32vec3_op0, Vertex2DLoadedVariable_float32vec3_op3, Vertex2DLoadedVariable_float32vec3_op1,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_FunctionPointer_float32vec3_Array_6_Positions, Vertex2DLoadedVariable_float32vec3_Array_6_Positions,\
/*UVS array*/\
(9<<SpvWordCountShift)|SpvOpCompositeConstruct, Vertex2DType_float32vec2_Array_6_UVS, Vertex2DLoadedVariable_float32vec2_Array_6_UVS,\
	 Vertex2DConstant_float32vec2_1f_0f, Vertex2DConstant_float32vec2_0f_1f, Vertex2DConstant_float32vec2_0f_0f, Vertex2DConstant_float32vec2_1f_0f, Vertex2DConstant_float32vec2_1f_1f, Vertex2DConstant_float32vec2_0f_1f,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_FunctionPointer_float32vec2_Array_6_UVS, Vertex2DLoadedVariable_float32vec2_Array_6_UVS,\
/*index*/\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex2DType_int32, Vertex2DLoadedVariable_int32_VertexIndex, Vertex2DVariable_InputPointer_VertexIndex,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex2DType_int32, Vertex2DLoadedVariable_int32_InstanceIndex, Vertex2DVariable_InputPointer_InstanceIndex,\
(5<<SpvWordCountShift)|SpvOpIMul, Vertex2DType_int32, Vertex2DLoadedVariable_int32_op0, Vertex2DLoadedVariable_int32_InstanceIndex, Vertex2DConstant_int_6,\
(5<<SpvWordCountShift)|SpvOpISub, Vertex2DType_int32, Vertex2DLoadedVariable_int32_index, Vertex2DLoadedVariable_int32_VertexIndex, Vertex2DLoadedVariable_int32_op0,\
/*output*/\
/*out position*/\
(5<<SpvWordCountShift)|SpvOpAccessChain, Vertex2DType_FunctionPointer_float32vec3, Vertex2DVariable_FunctionPointer_float32vec3_IndexedPositions, Vertex2DVariable_FunctionPointer_float32vec3_Array_6_Positions, Vertex2DLoadedVariable_int32_index,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex2DType_float32vec3, Vertex2DLoadedVariable_float32vec3_op4, Vertex2DVariable_FunctionPointer_float32vec3_IndexedPositions,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_OutputPointer_float32vec3_Position, Vertex2DLoadedVariable_float32vec3_op4,\
/*out UVS*/\
(5<<SpvWordCountShift)|SpvOpAccessChain, Vertex2DType_FunctionPointer_float32vec2, Vertex2DVariable_FunctionPointer_float32vec2_IndexedUVS, Vertex2DVariable_FunctionPointer_float32vec2_Array_6_UVS, Vertex2DLoadedVariable_int32_index,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_op5, Vertex2DVariable_FunctionPointer_float32vec2_IndexedUVS,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_OutputPointer_float32vec2_UVS, Vertex2DLoadedVariable_float32vec2_op5,\
/*out inbuilt position*/\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, Vertex2DType_float32vec2, Vertex2DLoadedVariable_float32vec2_op6, Vertex2DConstant_float32_1f, Vertex2DConstant_float32_1f,\
(9<<SpvWordCountShift)|SpvOpVectorShuffle, Vertex2DType_float32vec4, Vertex2DLoadedVariable_float32vec4_op7, Vertex2DLoadedVariable_float32vec3_op4, Vertex2DLoadedVariable_float32vec2_op6, 0, 1, 2, 3,\
\
(5<<SpvWordCountShift)|SpvOpAccessChain, Vertex2DType_OutputPointer_float32vec4, Vertex2DVariable_OutputPointer_float32vec4_Position, Vertex2DVariable_OutputPointer_struct_BuiltIn, Vertex2DConstant_int_0,\
(3<<SpvWordCountShift)|SpvOpStore, Vertex2DVariable_OutputPointer_float32vec4_Position, Vertex2DLoadedVariable_float32vec4_op7,\
/*function end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd, \
}

typedef enum FragmentShader2DVariables {

	Fragment2DVariable_ZEROISNOTUSED,
	Fragment2DExtension_GLSL450,
	Fragment2DFunction_Main,

	Fragment2DType_Void,
	Fragment2DType_Function,
	Fragment2DType_bool,

	Fragment2DType_float32,
	Fragment2DType_float32vec2,
	Fragment2DType_float32vec3,
	Fragment2DType_float32vec4,
	Fragment2DType_float32mat4,

	Fragment2DType_uint32,
	Fragment2DType_uint32vec2,
	Fragment2DType_uint32vec3,
	Fragment2DType_uint32vec4,

	Fragment2DType_int32,
	Fragment2DType_int32vec2,
	Fragment2DType_int32vec3,
	Fragment2DType_int32vec4,

	//constants
	Fragment2DConstant_float32_0f,
	Fragment2DConstant_float32_01f,
	Fragment2DConstant_float32_1f,
	Fragment2DConstant_float32_2f,

	Fragment2DConstant_uint32_0,

	Fragment2DConstant_int32_0,
	Fragment2DConstant_int32_1,
	Fragment2DConstant_int32_2,
	Fragment2DConstant_int32_5,

	Fragment2DConstant_float32vec2_NULL,
	Fragment2DConstant_float32vec3_NULL,
	Fragment2DConstant_int32vec2_NULL,

	Fragment2DConstant_float32vec2_1f_0f,
	Fragment2DConstant_float32vec2_0f_1f,
	Fragment2DConstant_float32vec2_0f_0f,
	Fragment2DConstant_float32vec2_1f_1f,

	//inputs
	//input locations
	Fragment2DType_InputPointer_float32vec2,
	Fragment2DType_InputPointer_float32vec3,
	Fragment2DType_InputPointer_int32vec2,
	
	Fragment2DVariable_InputPointer_float32vec2_Size,
	Fragment2DVariable_InputPointer_float32vec3_Position,
	Fragment2DVariable_InputPointer_float32vec2_BoundingBoxSize,
	Fragment2DVariable_InputPointer_float32vec2_BoundingBoxPosition,
	Fragment2DVariable_InputPointer_int32vec2_TextureOffset,
	Fragment2DVariable_InputPointer_int32vec2_TextureSize,
	Fragment2DVariable_InputPointer_float32vec2_UVS,

	//textures
	Fragment2DType_Image_float32_2D_0_0_0_1_Unknown,
	Fragment2DType_SampledImage_float32_2D_0_0_0_1_Unknown,
	Fragment2DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown,
	Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Emissive,
	Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Normal,
	Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Occlusion,
	Fragment2DVariable_UniformConstantPointer_SampledImage_float32_BaseColour,
	Fragment2DVariable_UniformConstantPointer_SampledImage_float32_MetallicRoughness,

	//material
	Fragment2DType_struct_Material,
	Fragment2DType_UniformPointer_struct_Material,
	Fragment2DVariable_UniformPointer_struct_Material,
	Fragment2DType_UniformPointer_float32vec4,
	Fragment2DType_UniformPointer_float32,

	//pushconstants
	Fragment2DType_struct_PushConstants,
	Fragment2DType_PushConstantPointer_struct_PushConstants,
	Fragment2DVariable_PushConstantPointer_struct_PushConstants,
	Fragment2DType_PushConstantPointer_int32,

	//output image attachments
	Fragment2DType_OutputPointer_float32vec4,
	Fragment2DConstant_float32vec4_NULL,
	Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,
	Fragment2DVariable_OutputPointer_float32vec4_OutPositionOrRevealage,

	Fragment2DConstantComposite_float32vec4_SelectedColour,

	Fragment2DLabel_Start,

	Fragment2DLoadedVariable_float32vec2_Size,
	Fragment2DLoadedVariable_float32vec3_Position,
	Fragment2DLoadedVariable_float32vec2_BoundingBoxSize,
	Fragment2DLoadedVariable_float32vec2_BoundingBoxPosition,

	Fragment2DLoadedVariable_float32_SizeX,
	Fragment2DLoadedVariable_float32_SizeY,
	Fragment2DLoadedVariable_float32_PositionX,
	Fragment2DLoadedVariable_float32_PositionY,
	Fragment2DLoadedVariable_float32_BoundingBoxSizeX,
	Fragment2DLoadedVariable_float32_BoundingBoxSizeY,
	Fragment2DLoadedVariable_float32_BoundingBoxPositionX,	
	Fragment2DLoadedVariable_float32_BoundingBoxPositionY,



	Fragment2DLoadedVariable_float32_op0,
	Fragment2DLoadedVariable_float32_op1,
	Fragment2DLoadedVariable_float32_op2,
	Fragment2DLoadedVariable_float32_op3,

	Fragment2DLabel_BoundingBoxValidationSelectionMerge,
	Fragment2DLabel_BoundingBoxValidationTrue,
	Fragment2DLabel_BoundingBoxValidationFalse,

	Fragment2DLoadVariable_bool_op0,
	Fragment2DLoadVariable_bool_op1,
	Fragment2DLoadVariable_bool_op2,
	Fragment2DLoadVariable_bool_op3,

	Fragment2DLoadVariable_bool_op4,
	Fragment2DLoadVariable_bool_op5,
	Fragment2DLoadVariable_bool_op6,
	Fragment2DLoadVariable_bool_op7,

	Fragment2DVariable_PushConstantPointer_int32_Mode,
	Fragment2DLoadedVariable_int32_Mode,

	Fragment2DVariable_PushConstantPointer_int32_Selected,
	Fragment2DLoadedVariable_int32_Selected,



	//misc extensons

	Fragment2DLoadVariable_bool_op8,

	Fragment2DLoadVariable_bool_op9,

	Fragment2DLabel_ModeMerge,
	Fragment2DLabel_ModeTrue,
	Fragment2DLabel_ModeFalse,


	Fragment2DLabel_SelectedMerge,
	Fragment2DLabel_SelectedTrue,
	Fragment2DLabel_SelectedFalse,


	Fragment2DVariable_UniformPointer_float32vec4_BaseColourFactor,
	Fragment2DLoadedVariable_float32vec4_BaseColourFactor,

	Fragment2DVariable_UniformPointer_float32vec4_Emissive,
	Fragment2DLoadedVariable_float32vec4_Emissive,

	Fragment2DVariable_UniformPointer_float32_AlphaCutoff,
	Fragment2DLoadedVariable_float32_AlphaCutoff,

	Fragment2DLoadedVariable_SampledImage_float32_BaseColour,
	Fragment2DLoadedVariable_SampledImage_float32_Emissive,
	Fragment2DLoadedVariable_float32vec2_UVS,
	Fragment2DLoadedVariable_int32vec2_TextureOffset,
	Fragment2DLoadedVariable_int32vec2_TextureSize,

	Fragment2DLoadedVariable_Image_float32_BaseColour,
	Fragment2DLoadedVariable_Image_float32_Emissive,

	Fragment2DLoadedVariable_float32vec2_TextureOffset,
	Fragment2DLoadedVariable_float32vec2_TextureSize,

	Fragment2DLoadedVariable_int32vec2_BaseColourSize,
	Fragment2DLoadedVariable_float32vec2_BaseColourSize,
	Fragment2DLoadedVariable_int32vec2_EmissiveSize,
	Fragment2DLoadedVariable_float32vec2_EmissiveSize,

	Fragment2DLoadedVariable_float32vec4_op0,

	Fragment2DLoadedVariable_float32vec2_op00,
	Fragment2DLoadedVariable_float32vec2_op01,
	Fragment2DLoadedVariable_float32vec2_op02,
	Fragment2DLoadedVariable_float32vec2_op03,

	Fragment2DLoadedVariable_float32vec4_op00,
	Fragment2DLoadedVariable_float32vec4_op01,
	Fragment2DLoadedVariable_float32vec4_op02,

	Fragment2DLoadedVariable_float32vec2_op0_0,
	Fragment2DLoadedVariable_float32vec2_op0_1,
	Fragment2DLoadedVariable_float32vec2_op0_2,
	Fragment2DLoadedVariable_float32vec2_op0_3,

	Fragment2DLoadedVariable_float32vec4_op0_0,
	Fragment2DLoadedVariable_float32vec4_op0_1,
	Fragment2DLoadedVariable_float32vec4_op0_2,


	Fragment2DLoadedVariable_float32vec4_op4,
	Fragment2DLoadedVariable_float32vec4_op4_0,

	Fragment2DLoadedVariable_float32vec4_op5,
	Fragment2DLoadedVariable_float32vec4_op6,
		Fragment2DLoadedVariable_float32vec4_op51,
		Fragment2DLoadedVariable_float32vec4_op61,
	Fragment2DLoadedVariable_float32vec4_op7,
	Fragment2DLoadedVariable_float32_op5,


	Fragment2DLoadedVariable_float32vec4_op8,
	Fragment2DLoadedVariable_float32vec4_op9,

	Fragment2DLoadedVariable_float32_op6,
	Fragment2DLoadedVariable_float32_op7,
	Fragment2DLoadedVariable_float32_op8,
	Fragment2DLoadedVariable_float32_op9,
	Fragment2DLoadedVariable_float32_op10,


	Fragment2DVariables_MAX
}FragmentShader2DVariables;
#define FragmentShader2D_MainSize (677 * sizeof(SPIRV))
#define FragmentShader2D_Main() {\
SPIRV_Header(Fragment2DVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityImageQuery,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, Fragment2DExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(21<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelFragment, Fragment2DFunction_Main, 'niam', '\0', Fragment2DVariable_InputPointer_float32vec2_Size, Fragment2DVariable_InputPointer_float32vec3_Position, Fragment2DVariable_InputPointer_float32vec2_BoundingBoxSize,\
Fragment2DVariable_InputPointer_float32vec2_BoundingBoxPosition, Fragment2DVariable_InputPointer_int32vec2_TextureOffset, Fragment2DVariable_InputPointer_int32vec2_TextureSize, Fragment2DVariable_InputPointer_float32vec2_UVS,\
Fragment2DVariable_UniformPointer_struct_Material, Fragment2DVariable_PushConstantPointer_struct_PushConstants, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DVariable_OutputPointer_float32vec4_OutPositionOrRevealage,\
Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Emissive, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Normal, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Occlusion, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_BaseColour, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_MetallicRoughness, \
(3<<SpvWordCountShift)|SpvOpExecutionMode, Fragment2DFunction_Main, SpvExecutionModeOriginUpperLeft,\
/*DECORATION*/\
/*INPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_InputPointer_float32vec2_Size, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_InputPointer_float32vec3_Position, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_InputPointer_float32vec2_BoundingBoxSize, SpvDecorationLocation, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_InputPointer_float32vec2_BoundingBoxPosition, SpvDecorationLocation, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_InputPointer_int32vec2_TextureOffset, SpvDecorationLocation, 4,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_InputPointer_int32vec2_TextureOffset, SpvDecorationFlat,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_InputPointer_int32vec2_TextureSize, SpvDecorationLocation, 5,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_InputPointer_int32vec2_TextureSize, SpvDecorationFlat,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_InputPointer_float32vec2_UVS, SpvDecorationLocation, 6,\
/*Textures*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Emissive, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Emissive, SpvDecorationBinding, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Normal, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Normal, SpvDecorationBinding, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Occlusion, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Occlusion, SpvDecorationBinding, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_BaseColour, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_BaseColour, SpvDecorationBinding, 4,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_MetallicRoughness, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_MetallicRoughness, SpvDecorationBinding, 5,\
/*Material*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 1, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 2, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 3, SpvDecorationOffset, 36,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 4, SpvDecorationOffset, 40,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 5, SpvDecorationOffset, 44,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 6, SpvDecorationOffset, 48,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 7, SpvDecorationOffset, 52,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 8, SpvDecorationOffset, 56,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 9, SpvDecorationOffset, 60,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 10, SpvDecorationOffset, 64,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 11, SpvDecorationOffset, 68,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 12, SpvDecorationOffset, 72,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 13, SpvDecorationOffset, 76,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 14, SpvDecorationOffset, 80,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 15, SpvDecorationOffset, 84,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 16, SpvDecorationOffset, 88,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 17, SpvDecorationOffset, 92,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_Material, 18, SpvDecorationOffset, 96,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment2DType_struct_Material, SpvDecorationBlock,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformPointer_struct_Material, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_UniformPointer_struct_Material, SpvDecorationBinding, 0,\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment2DType_struct_PushConstants, 2, SpvDecorationOffset, 68,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment2DType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment2DVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvDecorationLocation, 1,\
\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, Fragment2DType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, Fragment2DType_Function, Fragment2DType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, Fragment2DType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, Fragment2DType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment2DType_float32vec2, Fragment2DType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment2DType_float32vec3, Fragment2DType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment2DType_float32vec4, Fragment2DType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, Fragment2DType_float32mat4, Fragment2DType_float32vec4, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, Fragment2DType_uint32, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment2DType_uint32vec2, Fragment2DType_uint32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment2DType_uint32vec3, Fragment2DType_uint32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment2DType_uint32vec4, Fragment2DType_uint32, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, Fragment2DType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment2DType_int32vec2, Fragment2DType_int32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment2DType_int32vec3, Fragment2DType_int32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment2DType_int32vec4, Fragment2DType_int32, 4,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment2DType_float32, Fragment2DConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment2DType_float32, Fragment2DConstant_float32_01f, 1055353216,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment2DType_float32, Fragment2DConstant_float32_1f, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment2DType_float32, Fragment2DConstant_float32_2f, 1073741824,\
\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment2DType_uint32, Fragment2DConstant_uint32_0, 0,\
\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment2DType_int32, Fragment2DConstant_int32_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment2DType_int32, Fragment2DConstant_int32_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment2DType_int32, Fragment2DConstant_int32_2, 2,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment2DType_int32, Fragment2DConstant_int32_5, 5,\
/*input locations*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment2DType_InputPointer_float32vec2, SpvStorageClassInput, Fragment2DType_float32vec2,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment2DType_InputPointer_float32vec3, SpvStorageClassInput, Fragment2DType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment2DType_InputPointer_int32vec2, SpvStorageClassInput, Fragment2DType_int32vec2,\
\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_InputPointer_float32vec2, Fragment2DVariable_InputPointer_float32vec2_Size, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_InputPointer_float32vec3, Fragment2DVariable_InputPointer_float32vec3_Position, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_InputPointer_float32vec2, Fragment2DVariable_InputPointer_float32vec2_BoundingBoxSize, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_InputPointer_float32vec2, Fragment2DVariable_InputPointer_float32vec2_BoundingBoxPosition, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_InputPointer_int32vec2, Fragment2DVariable_InputPointer_int32vec2_TextureOffset, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_InputPointer_int32vec2, Fragment2DVariable_InputPointer_int32vec2_TextureSize, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_InputPointer_float32vec2, Fragment2DVariable_InputPointer_float32vec2_UVS, SpvStorageClassInput,\
/*textures*/\
(9<<SpvWordCountShift)|SpvOpTypeImage, Fragment2DType_Image_float32_2D_0_0_0_1_Unknown, Fragment2DType_float32, SpvDim2D, 0, 0, 0, 1, SpvImageFormatUnknown,\
(3<<SpvWordCountShift)|SpvOpTypeSampledImage, Fragment2DType_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment2DType_Image_float32_2D_0_0_0_1_Unknown,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment2DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, SpvStorageClassUniformConstant, Fragment2DType_SampledImage_float32_2D_0_0_0_1_Unknown,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Emissive, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Normal, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Occlusion, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_BaseColour, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_MetallicRoughness, SpvStorageClassUniformConstant,\
/*material*/\
(21<<SpvWordCountShift)|SpvOpTypeStruct, Fragment2DType_struct_Material, Fragment2DType_float32vec4, Fragment2DType_float32vec4, Fragment2DType_float32, Fragment2DType_float32, Fragment2DType_float32,\
	Fragment2DType_float32, Fragment2DType_float32, Fragment2DType_float32, Fragment2DType_float32, Fragment2DType_float32, Fragment2DType_int32, Fragment2DType_int32, Fragment2DType_int32, Fragment2DType_int32,\
	Fragment2DType_uint32, Fragment2DType_uint32, Fragment2DType_uint32, Fragment2DType_uint32, Fragment2DType_uint32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment2DType_UniformPointer_struct_Material, SpvStorageClassUniform, Fragment2DType_struct_Material,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_UniformPointer_struct_Material, Fragment2DVariable_UniformPointer_struct_Material, SpvStorageClassUniform,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment2DType_UniformPointer_float32vec4, SpvStorageClassUniform, Fragment2DType_float32vec4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment2DType_UniformPointer_float32, SpvStorageClassUniform, Fragment2DType_float32,\
/*pushconstants*/\
(5<<SpvWordCountShift)|SpvOpTypeStruct, Fragment2DType_struct_PushConstants, Fragment2DType_float32mat4, Fragment2DType_int32, Fragment2DType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment2DType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, Fragment2DType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_PushConstantPointer_struct_PushConstants, Fragment2DVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment2DType_PushConstantPointer_int32, SpvStorageClassPushConstant, Fragment2DType_int32,\
/*outputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment2DType_OutputPointer_float32vec4, SpvStorageClassOutput, Fragment2DType_float32vec4,\
(3<<SpvWordCountShift)|SpvOpConstantNull, Fragment2DType_float32vec4, Fragment2DConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_OutputPointer_float32vec4, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvStorageClassOutput, Fragment2DConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Fragment2DType_OutputPointer_float32vec4, Fragment2DVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvStorageClassOutput, Fragment2DConstant_float32vec4_NULL,\
\
(7<<SpvWordCountShift)|SpvOpConstantComposite, Fragment2DType_float32vec4, Fragment2DConstantComposite_float32vec4_SelectedColour, Fragment2DConstant_float32_0f, Fragment2DConstant_float32_1f, Fragment2DConstant_float32_1f, Fragment2DConstant_float32_01f,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, Fragment2DType_Void, Fragment2DFunction_Main, SpvFunctionControlMaskNone, Fragment2DType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, Fragment2DLabel_Start,\
	/*Loading Variables*/\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_Size, Fragment2DVariable_InputPointer_float32vec2_Size,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec3, Fragment2DLoadedVariable_float32vec3_Position, Fragment2DVariable_InputPointer_float32vec3_Position,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_BoundingBoxSize, Fragment2DVariable_InputPointer_float32vec2_BoundingBoxSize,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_BoundingBoxPosition, Fragment2DVariable_InputPointer_float32vec2_BoundingBoxPosition,\
	\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_SizeX, Fragment2DLoadedVariable_float32vec2_Size, 0,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_SizeY, Fragment2DLoadedVariable_float32vec2_Size, 1,\
	\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_PositionX, Fragment2DLoadedVariable_float32vec3_Position, 0,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_PositionY, Fragment2DLoadedVariable_float32vec3_Position, 1,\
	\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_BoundingBoxSizeX, Fragment2DLoadedVariable_float32vec2_BoundingBoxSize, 0,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_BoundingBoxSizeY, Fragment2DLoadedVariable_float32vec2_BoundingBoxSize, 1,\
	\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_BoundingBoxPositionX, Fragment2DLoadedVariable_float32vec2_BoundingBoxPosition, 0,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_BoundingBoxPositionY, Fragment2DLoadedVariable_float32vec2_BoundingBoxPosition, 1,\
	/*BoundingBox Check*/\
 	(5<<SpvWordCountShift)|SpvOpFSub, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op0, Fragment2DLoadedVariable_float32_BoundingBoxPositionX, Fragment2DLoadedVariable_float32_BoundingBoxSizeX,\
	(5<<SpvWordCountShift)|SpvOpFOrdGreaterThan, Fragment2DType_bool, Fragment2DLoadVariable_bool_op0, Fragment2DLoadedVariable_float32_PositionX, Fragment2DLoadedVariable_float32_op0,\
	\
	(5<<SpvWordCountShift)|SpvOpFAdd, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op1, Fragment2DLoadedVariable_float32_BoundingBoxPositionX, Fragment2DLoadedVariable_float32_BoundingBoxSizeX,\
	(5<<SpvWordCountShift)|SpvOpFOrdLessThan, Fragment2DType_bool, Fragment2DLoadVariable_bool_op1, Fragment2DLoadedVariable_float32_PositionX, Fragment2DLoadedVariable_float32_op1,\
	\
	(5<<SpvWordCountShift)|SpvOpFSub, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op2, Fragment2DLoadedVariable_float32_BoundingBoxPositionY, Fragment2DLoadedVariable_float32_BoundingBoxSizeY,\
	(5<<SpvWordCountShift)|SpvOpFOrdGreaterThan, Fragment2DType_bool, Fragment2DLoadVariable_bool_op2, Fragment2DLoadedVariable_float32_PositionY, Fragment2DLoadedVariable_float32_op2,\
	\
	(5<<SpvWordCountShift)|SpvOpFAdd, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op3, Fragment2DLoadedVariable_float32_BoundingBoxPositionY, Fragment2DLoadedVariable_float32_BoundingBoxSizeY,\
	(5<<SpvWordCountShift)|SpvOpFOrdLessThan, Fragment2DType_bool, Fragment2DLoadVariable_bool_op3, Fragment2DLoadedVariable_float32_PositionY, Fragment2DLoadedVariable_float32_op3,\
	/*If BoundingBox Validation*/\
	(5<<SpvWordCountShift)|SpvOpLogicalAnd, Fragment2DType_bool, Fragment2DLoadVariable_bool_op4, Fragment2DLoadVariable_bool_op0, Fragment2DLoadVariable_bool_op1,\
	(5<<SpvWordCountShift)|SpvOpLogicalAnd, Fragment2DType_bool, Fragment2DLoadVariable_bool_op5, Fragment2DLoadVariable_bool_op2, Fragment2DLoadVariable_bool_op3,\
	(5<<SpvWordCountShift)|SpvOpLogicalAnd, Fragment2DType_bool, Fragment2DLoadVariable_bool_op6, Fragment2DLoadVariable_bool_op4, Fragment2DLoadVariable_bool_op5,\
	(4<<SpvWordCountShift)|SpvOpLogicalNot, Fragment2DType_bool, Fragment2DLoadVariable_bool_op7, Fragment2DLoadVariable_bool_op6,\
	\
	(3<<SpvWordCountShift)|SpvOpSelectionMerge, Fragment2DLabel_BoundingBoxValidationSelectionMerge, SpvSelectionControlMaskNone,\
	(4<<SpvWordCountShift)|SpvOpBranchConditional, Fragment2DLoadVariable_bool_op7, Fragment2DLabel_BoundingBoxValidationTrue, Fragment2DLabel_BoundingBoxValidationSelectionMerge,\
		(2<<SpvWordCountShift)|SpvOpLabel, Fragment2DLabel_BoundingBoxValidationTrue,\
		(1<<SpvWordCountShift)|SpvOpKill,\
	(2<<SpvWordCountShift)|SpvOpLabel, Fragment2DLabel_BoundingBoxValidationSelectionMerge,\
	/*basecolourfactor*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment2DType_UniformPointer_float32vec4, Fragment2DVariable_UniformPointer_float32vec4_BaseColourFactor, Fragment2DVariable_UniformPointer_struct_Material, Fragment2DConstant_int32_0,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_BaseColourFactor, Fragment2DVariable_UniformPointer_float32vec4_BaseColourFactor,\
	/*alphacutoff*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment2DType_UniformPointer_float32, Fragment2DVariable_UniformPointer_float32_AlphaCutoff, Fragment2DVariable_UniformPointer_struct_Material, Fragment2DConstant_int32_5,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32, Fragment2DLoadedVariable_float32_AlphaCutoff, Fragment2DVariable_UniformPointer_float32_AlphaCutoff,\
	/*get infos index offset*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment2DType_PushConstantPointer_int32, Fragment2DVariable_PushConstantPointer_int32_Mode, Fragment2DVariable_PushConstantPointer_struct_PushConstants, Fragment2DConstant_int32_1,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_int32, Fragment2DLoadedVariable_int32_Mode, Fragment2DVariable_PushConstantPointer_int32_Mode,\
	\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment2DType_PushConstantPointer_int32, Fragment2DVariable_PushConstantPointer_int32_Selected, Fragment2DVariable_PushConstantPointer_struct_PushConstants, Fragment2DConstant_int32_2,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_int32, Fragment2DLoadedVariable_int32_Selected, Fragment2DVariable_PushConstantPointer_int32_Selected,\
}

#define FragmentShader2D_TextureSampling_DefaultSize (16 * sizeof(SPIRV))
#define FragmentShader2D_TextureSampling_Default() {\
(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment2DLoadedVariable_SampledImage_float32_BaseColour, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_BaseColour,\
(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_UVS, Fragment2DVariable_InputPointer_float32vec2_UVS,\
(5<<SpvWordCountShift)|SpvOpImageSampleImplicitLod, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op0, Fragment2DLoadedVariable_SampledImage_float32_BaseColour, Fragment2DLoadedVariable_float32vec2_UVS,\
(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_op0,\
}

#define FragmentShader2D_TextureSamplingAndTextureMode_TextSize (220 * sizeof(SPIRV))
#define FragmentShader2D_TextureSamplingAndTextureMode_Text() {\
(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_UVS, Fragment2DVariable_InputPointer_float32vec2_UVS,\
(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_int32vec2, Fragment2DLoadedVariable_int32vec2_TextureOffset, Fragment2DVariable_InputPointer_int32vec2_TextureOffset,\
(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_int32vec2, Fragment2DLoadedVariable_int32vec2_TextureSize, Fragment2DVariable_InputPointer_int32vec2_TextureSize,\
(4<<SpvWordCountShift)|SpvOpConvertSToF, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_TextureOffset, Fragment2DLoadedVariable_int32vec2_TextureOffset,\
(4<<SpvWordCountShift)|SpvOpConvertSToF, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_TextureSize, Fragment2DLoadedVariable_int32vec2_TextureSize,\
\
(5<<SpvWordCountShift)|SpvOpIEqual, Fragment2DType_bool, Fragment2DLoadVariable_bool_op8, Fragment2DLoadedVariable_int32_Mode, Fragment2DConstant_int32_1,\
\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, Fragment2DLabel_ModeMerge, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, Fragment2DLoadVariable_bool_op8, Fragment2DLabel_ModeTrue, Fragment2DLabel_ModeFalse,\
(2<<SpvWordCountShift)|SpvOpLabel, Fragment2DLabel_ModeTrue,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment2DLoadedVariable_SampledImage_float32_BaseColour, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_BaseColour,\
	(4<<SpvWordCountShift)|SpvOpImage, Fragment2DType_Image_float32_2D_0_0_0_1_Unknown, Fragment2DLoadedVariable_Image_float32_BaseColour, Fragment2DLoadedVariable_SampledImage_float32_BaseColour,\
	\
	(5<<SpvWordCountShift)|SpvOpImageQuerySizeLod, Fragment2DType_int32vec2, Fragment2DLoadedVariable_int32vec2_BaseColourSize, Fragment2DLoadedVariable_Image_float32_BaseColour, Fragment2DConstant_int32_0,\
	(4<<SpvWordCountShift)|SpvOpConvertSToF, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_BaseColourSize, Fragment2DLoadedVariable_int32vec2_BaseColourSize,\
	(5<<SpvWordCountShift)|SpvOpFDiv, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_op00, Fragment2DLoadedVariable_float32vec2_TextureSize, Fragment2DLoadedVariable_float32vec2_BaseColourSize,\
	(5<<SpvWordCountShift)|SpvOpFMul, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_op01, Fragment2DLoadedVariable_float32vec2_UVS, Fragment2DLoadedVariable_float32vec2_op00,\
	(5<<SpvWordCountShift)|SpvOpFDiv, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_op02, Fragment2DLoadedVariable_float32vec2_TextureOffset, Fragment2DLoadedVariable_float32vec2_BaseColourSize,\
	(5<<SpvWordCountShift)|SpvOpFAdd, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_op03, Fragment2DLoadedVariable_float32vec2_op01, Fragment2DLoadedVariable_float32vec2_op02,\
	(5<<SpvWordCountShift)|SpvOpImageSampleImplicitLod, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op00, Fragment2DLoadedVariable_SampledImage_float32_BaseColour, Fragment2DLoadedVariable_float32vec2_op03,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op01, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,\
	(5<<SpvWordCountShift)|SpvOpFAdd, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op02, Fragment2DLoadedVariable_float32vec4_op00, Fragment2DLoadedVariable_float32vec4_op01,\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_op02,\
	\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op5, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op5, Fragment2DLoadedVariable_float32vec4_op5, 0,\
	(7<<SpvWordCountShift)|SpvOpCompositeConstruct, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op6, Fragment2DConstant_float32_1f, Fragment2DConstant_float32_1f, Fragment2DConstant_float32_1f, Fragment2DLoadedVariable_float32_op5,\
	(5<<SpvWordCountShift)|SpvOpFMul, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op7, Fragment2DLoadedVariable_float32vec4_op6, Fragment2DLoadedVariable_float32vec4_BaseColourFactor,\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_op7,\
	(2<<SpvWordCountShift)|SpvOpBranch, Fragment2DLabel_ModeMerge,\
(2<<SpvWordCountShift)|SpvOpLabel, Fragment2DLabel_ModeFalse,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment2DLoadedVariable_SampledImage_float32_Emissive, Fragment2DVariable_UniformConstantPointer_SampledImage_float32_Emissive,\
	(4<<SpvWordCountShift)|SpvOpImage, Fragment2DType_Image_float32_2D_0_0_0_1_Unknown, Fragment2DLoadedVariable_Image_float32_Emissive, Fragment2DLoadedVariable_SampledImage_float32_Emissive,\
	\
	(5<<SpvWordCountShift)|SpvOpImageQuerySizeLod, Fragment2DType_int32vec2, Fragment2DLoadedVariable_int32vec2_EmissiveSize, Fragment2DLoadedVariable_Image_float32_Emissive, Fragment2DConstant_int32_0,\
	(4<<SpvWordCountShift)|SpvOpConvertSToF, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_EmissiveSize, Fragment2DLoadedVariable_int32vec2_EmissiveSize,\
	(5<<SpvWordCountShift)|SpvOpFDiv, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_op0_0, Fragment2DLoadedVariable_float32vec2_TextureSize, Fragment2DLoadedVariable_float32vec2_EmissiveSize,\
	(5<<SpvWordCountShift)|SpvOpFMul, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_op0_1, Fragment2DLoadedVariable_float32vec2_UVS, Fragment2DLoadedVariable_float32vec2_op0_0,\
	(5<<SpvWordCountShift)|SpvOpFDiv, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_op0_2, Fragment2DLoadedVariable_float32vec2_TextureOffset, Fragment2DLoadedVariable_float32vec2_EmissiveSize,\
	(5<<SpvWordCountShift)|SpvOpFAdd, Fragment2DType_float32vec2, Fragment2DLoadedVariable_float32vec2_op0_3, Fragment2DLoadedVariable_float32vec2_op0_2, Fragment2DLoadedVariable_float32vec2_op0_1,\
	(5<<SpvWordCountShift)|SpvOpImageSampleImplicitLod, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op0_0, Fragment2DLoadedVariable_SampledImage_float32_Emissive, Fragment2DLoadedVariable_float32vec2_op0_3,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op0_1, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,\
	(5<<SpvWordCountShift)|SpvOpFAdd, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op0_2, Fragment2DLoadedVariable_float32vec4_op0_0, Fragment2DLoadedVariable_float32vec4_op0_1,\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_op0_2,\
	\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op51, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,\
	(5<<SpvWordCountShift)|SpvOpFMul, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op61, Fragment2DLoadedVariable_float32vec4_op51, Fragment2DLoadedVariable_float32vec4_BaseColourFactor,\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_op61,\
	(2<<SpvWordCountShift)|SpvOpBranch, Fragment2DLabel_ModeMerge,\
(2<<SpvWordCountShift)|SpvOpLabel, Fragment2DLabel_ModeMerge,\
/*selected shader mode*/\
(5<<SpvWordCountShift)|SpvOpIEqual, Fragment2DType_bool, Fragment2DLoadVariable_bool_op9, Fragment2DLoadedVariable_int32_Selected, Fragment2DConstant_int32_1,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, Fragment2DLabel_SelectedMerge, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, Fragment2DLoadVariable_bool_op9, Fragment2DLabel_SelectedTrue, Fragment2DLabel_SelectedFalse,\
(2<<SpvWordCountShift)|SpvOpLabel, Fragment2DLabel_SelectedTrue,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op4, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,\
	(5<<SpvWordCountShift)|SpvOpFAdd, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op4_0, Fragment2DConstantComposite_float32vec4_SelectedColour, Fragment2DLoadedVariable_float32vec4_op4,\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_op4_0,\
	(2<<SpvWordCountShift)|SpvOpBranch, Fragment2DLabel_SelectedMerge,\
(2<<SpvWordCountShift)|SpvOpLabel, Fragment2DLabel_SelectedFalse,\
	(2<<SpvWordCountShift)|SpvOpBranch, Fragment2DLabel_SelectedMerge,\
(2<<SpvWordCountShift)|SpvOpLabel, Fragment2DLabel_SelectedMerge,\
};


#define FragmentShader2D_TextureMode_ColourSize (12 * sizeof(SPIRV))
#define FragmentShader2D_TextureMode_Colour() {\
(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op5, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,\
(5<<SpvWordCountShift)|SpvOpFMul, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op6, Fragment2DLoadedVariable_float32vec4_op5, Fragment2DLoadedVariable_float32vec4_BaseColourFactor,\
(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_op6,\
};

#define FragmentShader2D_TextureMode_AlphaSize (24 * sizeof(SPIRV))
#define FragmentShader2D_TextureMode_Alpha() {\
(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op5, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op5, Fragment2DLoadedVariable_float32vec4_op5, 0,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op6, Fragment2DConstant_float32_1f, Fragment2DConstant_float32_1f, Fragment2DConstant_float32_1f, Fragment2DLoadedVariable_float32_op5,\
(5<<SpvWordCountShift)|SpvOpFMul, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op7, Fragment2DLoadedVariable_float32vec4_op6, Fragment2DLoadedVariable_float32vec4_BaseColourFactor,\
(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_op7,\
}

#define FragmentShader2D_TextureMode_SolidSize (3 * sizeof(SPIRV))
#define FragmentShader2D_TextureMode_Solid() {\
(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_BaseColourFactor,\
}


#define FragmentShader2D_AlphaMode_OpaqueSize (31 * sizeof(SPIRV))
#define FragmentShader2D_AlphaMode_Opaque() {\
(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op8, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op6, Fragment2DLoadedVariable_float32vec4_op8, 0,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op7, Fragment2DLoadedVariable_float32vec4_op8, 1,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op8, Fragment2DLoadedVariable_float32vec4_op8, 2,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op9, Fragment2DLoadedVariable_float32_op6, Fragment2DLoadedVariable_float32_op7, Fragment2DLoadedVariable_float32_op8, Fragment2DConstant_float32_1f,\
(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_op9,\
\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd\
}

#define FragmentShader2D_AlphaMode_MaskSize (43 * sizeof(SPIRV))
#define FragmentShader2D_AlphaMode_Mask() {\
(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op8, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op6, Fragment2DLoadedVariable_float32vec4_op8, 0,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op7, Fragment2DLoadedVariable_float32vec4_op8, 1,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op8, Fragment2DLoadedVariable_float32vec4_op8, 2,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op9, Fragment2DLoadedVariable_float32vec4_op8, 3,\
(7<<SpvWordCountShift)|SpvOpExtInst, Fragment2DType_float32, Fragment2DLoadedVariable_float32_op10, Fragment2DExtension_GLSL450, 48, Fragment2DLoadedVariable_float32_AlphaCutoff, Fragment2DLoadedVariable_float32_op9,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op9, Fragment2DLoadedVariable_float32_op6, Fragment2DLoadedVariable_float32_op7, Fragment2DLoadedVariable_float32_op8, Fragment2DLoadedVariable_float32_op10,\
(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_op9,\
\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd\
}

#define FragmentShader2D_AlphaMode_BlendSize (9 * sizeof(SPIRV))
#define FragmentShader2D_AlphaMode_Blend() {\
(4<<SpvWordCountShift)|SpvOpLoad, Fragment2DType_float32vec4, Fragment2DLoadedVariable_float32vec4_op8, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,\
(3<<SpvWordCountShift)|SpvOpStore, Fragment2DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment2DLoadedVariable_float32vec4_op8,\
\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd\
}

#define FragmentShader2D_MaxSize (677 + 220 + 43)

///////////////////////////////////////////////////////////////////////////////////////////////
//3D
///////////////////////////////////////////////////////////////////////////////////////////////

//vert
#define Vertex3DDynamSize 110
typedef enum VertexShader3DVariables {
	Vertex3DVariable_ZEROISNOTUSED,
	Vertex3DExtension_GLSL450,
	Vertex3DFunction_Main,

	Vertex3DType_Void,
	Vertex3DType_Function,
	Vertex3DType_bool,

	Vertex3DType_float32,
	Vertex3DType_float32vec2,
	Vertex3DType_float32vec3,
	Vertex3DType_float32vec4,
	Vertex3DType_float32mat4,

	Vertex3DType_uint32,
	Vertex3DType_uint32vec2,
	Vertex3DType_uint32vec3,
	Vertex3DType_uint32vec4,

	Vertex3DType_int32,
	Vertex3DType_int32vec2,
	Vertex3DType_int32vec3,
	Vertex3DType_int32vec4,

	//pushconstants
	Vertex3DType_Struct_PushConstants,
	Vertex3DType_PushConstantPointer_Struct_PushConstants,
	Vertex3DVariable_PushConstantPointer_Struct_PushConstants,

	//input
	Vertex3DType_InputPointer_int32,
	Vertex3DVariable_InputPointer_VertexIndex,
	Vertex3DVariable_InputPointer_InstanceIndex,

	Vertex3DType_struct_Info,
	Vertex3DType_RuntimeArray_struct_Infos,
	Vertex3DType_struct_Infos,
	Vertex3DType_StorageBufferPointer_struct_Infos,
	Vertex3DVariable_StorageBufferPointer_struct_Infos,
	Vertex3DType_StorageBufferPointer_struct_Info,
	Vertex3DType_StorageBufferPointer_int32,

	Vertex3DType_RuntimeArray_float32_Weights,
	Vertex3DType_Struct_Weights,
	Vertex3DType_StorageBufferPointer_Struct_Weights,
	Vertex3DVariable_StorageBufferPointer_Struct_Weights,
	Vertex3DType_StorageBufferPointer_float32_Weight,

	Vertex3DType_RuntimeArray_float32mat4_JointsMatrices,
	Vertex3DType_Struct_JointsMatrices,
	Vertex3DType_StorageBufferPointer_Struct_JointsMatrices,
	Vertex3DVariable_StorageBufferPointer_Struct_JointsMatrices,
	Vertex3DType_StorageBufferPointer_float32mat4_JointMatrix,

	Vertex3DType_Struct_Light,
	Vertex3DType_RuntimeArray_struct_Lights,
	Vertex3DType_Struct_Lights,
	Vertex3DType_StorageBufferPointer_Struct_Lights,
	Vertex3DVariable_StorageBufferPointer_Struct_Lights,
	Vertex3DType_StorageBufferPointer_Struct_Light,

	Vertex3DType_RuntimeArray_float32mat4_Matrices,
	Vertex3DType_Struct_Matrices,
	Vertex3DType_StorageBufferPointer_Struct_Matrices,
	Vertex3DVariable_StorageBufferPointer_Struct_Matrices,
	Vertex3DType_StorageBufferPointer_float32mat4_Matrix,

	//output
	Vertex3DType_float32_Array_1,
	Vertex3DType_BuiltInStruct,
	Vertex3DType_OutputPointer_BuiltInStruct,
	Vertex3DVariable_OutputPointer_BuiltInStruct,
	Vertex3DVariable_OutputPointer_float32vec4_Position,
	//to fragment
	Vertex3DType_OutputPointer_float32vec3,
	Vertex3DType_OutputPointer_float32vec4,

	Vertex3DConstant_float32vec3_NULL,
	Vertex3DConstant_float32vec4_NULL,

	Vertex3DVariable_OutputPointer_float32vec3_FinalPosition,
	Vertex3DVariable_OutputPointer_float32vec3_FinalNormal,
	Vertex3DVariable_OutputPointer_float32vec4_FinalTangent,

	//constants
	Vertex3DConstant_float32_0f,
	Vertex3DConstant_float32_1f,
	Vertex3DConstant_float32_2f,

	Vertex3DConstant_uint_0,
	Vertex3DConstant_uint_1,

	Vertex3DConstant_int_0,
	Vertex3DConstant_int_1,
	Vertex3DConstant_int_2,
	Vertex3DConstant_int_3,
	Vertex3DConstant_int_4,

	Vertex3DConstant_float32vec4_1f_0f_0f_0f,
	Vertex3DConstant_float32vec4_0f_1f_0f_0f,
	Vertex3DConstant_float32vec4_0f_0f_1f_0f,
	Vertex3DConstant_float32vec4_0f_0f_0f_1f,
	Vertex3DConstant_float32mat4_identity,



	Vertex3DLabel_StartOfFunction,

	Vertex3DType_FunctionPointer_float32mat4,
	Vertex3DVariable_FunctionPointer_float32mat4_SkinMatrix,

	Vertex3DType_FunctionPointer_float32vec4,
	Vertex3DVariable_FunctionPointer_float32vec4_SkinWeights,
	Vertex3DType_FunctionPointer_int32vec4,
	Vertex3DVariable_FunctionPointer_int32vec4_Joints,


	Vertex3DType_PushConstantPointer_float32mat4,
	Vertex3DVariable_PushConstantPointer_MatrixVP,
	Vertex3DLoadedVariable_PushConstantPointer_MatrixVP,


	Vertex3DType_PushConstantPointer_int32,

	Vertex3DVariable_PushConstantPointer_InfosOffset,
	Vertex3DVLoadedVariable_int32_InfosOffset,

	Vertex3DVariable_PushConstantPointer_WeightsOffset,
	Vertex3DVLoadedVariable_int32_WeightsOffset,

	Vertex3DVariable_PushConstantPointer_JointsOffset,
	Vertex3DVLoadedVariable_int32_JointsOffset,

	Vertex3DVariable_PushConstantPointer_MatricesOffset,
	Vertex3DVLoadedVariable_int32_MatricesOffset,


	Vertex3DVariable_StorageBufferPointer_float32mat4_Matrix,
	Vertex3DLoadedVariable_float32mat4_Matrix,

	Vertex3DLoadedVariable_float32mat4_op0,
	Vertex3DLoadedVariable_float32vec2_op1,
	Vertex3DLoadedVariable_float32vec3_op2,
	Vertex3DLoadedVariable_float32vec4_op3,
	Vertex3DLoadedVariable_float32mat4_op4,
	Vertex3DLoadedVariable_float32mat4_op5,
	Vertex3DLoadedVariable_float32vec4_op6,

	Vertex3DVariables_MAX,
}VertexShader3DVariables;
#define VertexShader3D_Main0_Size (33 * sizeof(SPIRV))
#define VertexShader3D_Main0(attributesize, passthroughsize) {\
SPIRV_Header(Vertex3DVariables_MAX + (Vertex3DDynamSize * attributesize))\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, Vertex3DExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
((15 + attributesize + passthroughsize)<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelVertex, Vertex3DFunction_Main, 'niam', '\0', Vertex3DVariable_PushConstantPointer_Struct_PushConstants, Vertex3DVariable_StorageBufferPointer_struct_Infos, Vertex3DVariable_StorageBufferPointer_Struct_Weights,\
	Vertex3DVariable_StorageBufferPointer_Struct_JointsMatrices, Vertex3DVariable_StorageBufferPointer_Struct_Lights, Vertex3DVariable_StorageBufferPointer_Struct_Matrices, Vertex3DVariable_OutputPointer_BuiltInStruct,\
	Vertex3DVariable_OutputPointer_float32vec3_FinalPosition, Vertex3DVariable_OutputPointer_float32vec3_FinalNormal, Vertex3DVariable_OutputPointer_float32vec4_FinalTangent,\
}

#define VertexShader3D_Interface_Attribute_Size (1 * sizeof(SPIRV))
#define VertexShader3D_Interface_Attribute(i, outputtrue) {Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + outputtrue}

#define VertexShader3D_Decoration_Attribute_Size (4 * sizeof(SPIRV))
#define VertexShader3D_Decoration_Attribute(i, outputtrue, index) {\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + outputtrue, SpvDecorationLocation, index,\
}

#define VertexShader3D_Main1_Size (573 * sizeof(SPIRV))
#define VertexShader3D_Main1() {\
/*decorations*/\
/*builtin*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_InputPointer_VertexIndex, SpvDecorationBuiltIn, SpvBuiltInVertexIndex,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_InputPointer_InstanceIndex, SpvDecorationBuiltIn, SpvBuiltInInstanceIndex,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_BuiltInStruct, 0, SpvDecorationBuiltIn, SpvBuiltInPosition,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_BuiltInStruct, 1, SpvDecorationBuiltIn, SpvBuiltInPointSize,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_BuiltInStruct, 2, SpvDecorationBuiltIn, SpvBuiltInClipDistance,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_BuiltInStruct, 3, SpvDecorationBuiltIn, SpvBuiltInCullDistance,\
(3<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_BuiltInStruct, SpvDecorationBlock,\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_PushConstants, 1, SpvDecorationOffset, 64,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_PushConstants, 2, SpvDecorationOffset, 64 + 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_PushConstants, 3, SpvDecorationOffset, 64 + 4 + 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_PushConstants, 4, SpvDecorationOffset, 64 + 4 + 4 + 4,\
(3<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_Struct_PushConstants, SpvDecorationBlock,\
/*storagebuffers*/\
/*infos*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_struct_Info, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_struct_Info, 1, SpvDecorationOffset, 4,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_RuntimeArray_struct_Infos, SpvDecorationArrayStride, 8,\
(3<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_struct_Infos, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_struct_Infos, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_StorageBufferPointer_struct_Infos, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_StorageBufferPointer_struct_Infos, SpvDecorationBinding, 0,\
/*weights*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_RuntimeArray_float32_Weights, SpvDecorationArrayStride, 4,\
(3<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_Struct_Weights, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_Weights, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_StorageBufferPointer_Struct_Weights, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_StorageBufferPointer_Struct_Weights, SpvDecorationBinding, 1,\
/*joints*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_RuntimeArray_float32mat4_JointsMatrices, SpvDecorationArrayStride, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_RuntimeArray_float32mat4_JointsMatrices, SpvDecorationColMajor,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_RuntimeArray_float32mat4_JointsMatrices, SpvDecorationMatrixStride, 16,\
(3<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_Struct_JointsMatrices, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_JointsMatrices, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_StorageBufferPointer_Struct_JointsMatrices, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_StorageBufferPointer_Struct_JointsMatrices, SpvDecorationBinding, 2,\
/*lights*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_Light, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_Light, 1, SpvDecorationOffset, 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_Light, 2, SpvDecorationOffset, 8,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_Light, 3, SpvDecorationOffset, 12,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_Light, 4, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_Light, 5, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_Light, 6, SpvDecorationOffset, 48,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_RuntimeArray_struct_Lights, SpvDecorationArrayStride, 128,\
(3<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_Struct_Lights, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_Lights, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_StorageBufferPointer_Struct_Lights, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_StorageBufferPointer_Struct_Lights, SpvDecorationBinding, 3,\
/*matrices*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_RuntimeArray_float32mat4_Matrices, SpvDecorationArrayStride, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_RuntimeArray_float32mat4_Matrices, SpvDecorationColMajor,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_RuntimeArray_float32mat4_Matrices, SpvDecorationMatrixStride, 16,\
(3<<SpvWordCountShift)|SpvOpDecorate, Vertex3DType_Struct_Matrices, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Vertex3DType_Struct_Matrices, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_StorageBufferPointer_Struct_Matrices, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_StorageBufferPointer_Struct_Matrices, SpvDecorationBinding, 4,\
/*output to fragment*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_OutputPointer_float32vec3_FinalPosition, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_OutputPointer_float32vec3_FinalNormal, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Vertex3DVariable_OutputPointer_float32vec4_FinalTangent, SpvDecorationLocation, 2,\
/*post decoration */\
(2<<SpvWordCountShift)|SpvOpTypeVoid, Vertex3DType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, Vertex3DType_Function, Vertex3DType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, Vertex3DType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, Vertex3DType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex3DType_float32vec2, Vertex3DType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex3DType_float32vec3, Vertex3DType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex3DType_float32vec4, Vertex3DType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, Vertex3DType_float32mat4, Vertex3DType_float32vec4, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, Vertex3DType_uint32, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex3DType_uint32vec2, Vertex3DType_uint32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex3DType_uint32vec3, Vertex3DType_uint32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex3DType_uint32vec4, Vertex3DType_uint32, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, Vertex3DType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex3DType_int32vec2, Vertex3DType_int32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex3DType_int32vec3, Vertex3DType_int32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Vertex3DType_int32vec4, Vertex3DType_int32, 4,\
/*basic constants*/\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex3DType_float32, Vertex3DConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex3DType_float32, Vertex3DConstant_float32_1f, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex3DType_float32, Vertex3DConstant_float32_2f, 1073741824,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex3DType_uint32, Vertex3DConstant_uint_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex3DType_uint32, Vertex3DConstant_uint_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex3DType_int32, Vertex3DConstant_int_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex3DType_int32, Vertex3DConstant_int_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex3DType_int32, Vertex3DConstant_int_2, 2,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex3DType_int32, Vertex3DConstant_int_3, 3,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex3DType_int32, Vertex3DConstant_int_4, 4,\
/*pushconstants*/\
(7<<SpvWordCountShift)|SpvOpTypeStruct, Vertex3DType_Struct_PushConstants, Vertex3DType_float32mat4, Vertex3DType_int32, Vertex3DType_int32, Vertex3DType_int32, Vertex3DType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_PushConstantPointer_Struct_PushConstants, SpvStorageClassPushConstant, Vertex3DType_Struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_PushConstantPointer_Struct_PushConstants, Vertex3DVariable_PushConstantPointer_Struct_PushConstants, SpvStorageClassPushConstant,\
/*inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_InputPointer_int32, SpvStorageClassInput, Vertex3DType_int32,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_InputPointer_int32, Vertex3DVariable_InputPointer_VertexIndex, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_InputPointer_int32, Vertex3DVariable_InputPointer_InstanceIndex, SpvStorageClassInput,\
/*storagebuffer infos*/\
(4<<SpvWordCountShift)|SpvOpTypeStruct, Vertex3DType_struct_Info, Vertex3DType_int32, Vertex3DType_int32,\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, Vertex3DType_RuntimeArray_struct_Infos, Vertex3DType_struct_Info,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, Vertex3DType_struct_Infos, Vertex3DType_RuntimeArray_struct_Infos,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_StorageBufferPointer_struct_Infos, SpvStorageClassStorageBuffer, Vertex3DType_struct_Infos,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_StorageBufferPointer_struct_Infos, Vertex3DVariable_StorageBufferPointer_struct_Infos, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_StorageBufferPointer_struct_Info, SpvStorageClassStorageBuffer, Vertex3DType_struct_Info,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_StorageBufferPointer_int32, SpvStorageClassStorageBuffer, Vertex3DType_int32,\
/*storagebuffer weights*/\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, Vertex3DType_RuntimeArray_float32_Weights, Vertex3DType_float32,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, Vertex3DType_Struct_Weights, Vertex3DType_RuntimeArray_float32_Weights,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_StorageBufferPointer_Struct_Weights, SpvStorageClassStorageBuffer, Vertex3DType_Struct_Weights,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_StorageBufferPointer_Struct_Weights, Vertex3DVariable_StorageBufferPointer_Struct_Weights, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_StorageBufferPointer_float32_Weight, SpvStorageClassStorageBuffer, Vertex3DType_float32,\
/*storagebuffer joints*/\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, Vertex3DType_RuntimeArray_float32mat4_JointsMatrices, Vertex3DType_float32mat4,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, Vertex3DType_Struct_JointsMatrices, Vertex3DType_RuntimeArray_float32mat4_JointsMatrices,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_StorageBufferPointer_Struct_JointsMatrices, SpvStorageClassStorageBuffer, Vertex3DType_Struct_JointsMatrices,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_StorageBufferPointer_Struct_JointsMatrices, Vertex3DVariable_StorageBufferPointer_Struct_JointsMatrices, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_StorageBufferPointer_float32mat4_JointMatrix, SpvStorageClassStorageBuffer, Vertex3DType_float32mat4,\
/*storagebuffer lights*/\
(9<<SpvWordCountShift)|SpvOpTypeStruct, Vertex3DType_Struct_Light, Vertex3DType_float32, Vertex3DType_float32, Vertex3DType_float32, Vertex3DType_float32, Vertex3DType_float32vec4, Vertex3DType_float32vec4, Vertex3DType_int32,\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, Vertex3DType_RuntimeArray_struct_Lights, Vertex3DType_Struct_Light,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, Vertex3DType_Struct_Lights, Vertex3DType_RuntimeArray_struct_Lights,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_StorageBufferPointer_Struct_Lights, SpvStorageClassStorageBuffer, Vertex3DType_Struct_Lights,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_StorageBufferPointer_Struct_Lights, Vertex3DVariable_StorageBufferPointer_Struct_Lights, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_StorageBufferPointer_Struct_Light, SpvStorageClassStorageBuffer, Vertex3DType_Struct_Light,\
/*storagebuffer matrices*/\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, Vertex3DType_RuntimeArray_float32mat4_Matrices, Vertex3DType_float32mat4,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, Vertex3DType_Struct_Matrices, Vertex3DType_RuntimeArray_float32mat4_Matrices,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_StorageBufferPointer_Struct_Matrices, SpvStorageClassStorageBuffer, Vertex3DType_Struct_Matrices,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_StorageBufferPointer_Struct_Matrices, Vertex3DVariable_StorageBufferPointer_Struct_Matrices, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_StorageBufferPointer_float32mat4_Matrix, SpvStorageClassStorageBuffer, Vertex3DType_float32mat4,\
/*outputs*/\
(4<<SpvWordCountShift)|SpvOpTypeArray, Vertex3DType_float32_Array_1, Vertex3DType_float32, Vertex3DConstant_int_1,\
(6<<SpvWordCountShift)|SpvOpTypeStruct, Vertex3DType_BuiltInStruct, Vertex3DType_float32vec4, Vertex3DType_float32, Vertex3DType_float32_Array_1, Vertex3DType_float32_Array_1,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_OutputPointer_BuiltInStruct, SpvStorageClassOutput, Vertex3DType_BuiltInStruct,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_OutputPointer_BuiltInStruct, Vertex3DVariable_OutputPointer_BuiltInStruct, SpvStorageClassOutput,\
/*to fragment shader location*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_OutputPointer_float32vec3, SpvStorageClassOutput, Vertex3DType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_OutputPointer_float32vec4, SpvStorageClassOutput, Vertex3DType_float32vec4,\
(3<<SpvWordCountShift)|SpvOpConstantNull, Vertex3DType_float32vec3, Vertex3DConstant_float32vec3_NULL,\
(3<<SpvWordCountShift)|SpvOpConstantNull, Vertex3DType_float32vec4, Vertex3DConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_OutputPointer_float32vec3, Vertex3DVariable_OutputPointer_float32vec3_FinalPosition, SpvStorageClassOutput, Vertex3DConstant_float32vec3_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_OutputPointer_float32vec3, Vertex3DVariable_OutputPointer_float32vec3_FinalNormal, SpvStorageClassOutput, Vertex3DConstant_float32vec3_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_OutputPointer_float32vec4, Vertex3DVariable_OutputPointer_float32vec4_FinalTangent, SpvStorageClassOutput, Vertex3DConstant_float32vec4_NULL,\
/*misc types*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_FunctionPointer_float32mat4, SpvStorageClassFunction, Vertex3DType_float32mat4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_FunctionPointer_float32vec4, SpvStorageClassFunction, Vertex3DType_float32vec4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_FunctionPointer_int32vec4, SpvStorageClassFunction, Vertex3DType_int32vec4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_PushConstantPointer_float32mat4, SpvStorageClassPushConstant, Vertex3DType_float32mat4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DType_PushConstantPointer_int32, SpvStorageClassPushConstant, Vertex3DType_int32,\
/*matrix constant identity*/\
(7<<SpvWordCountShift)|SpvOpConstantComposite, Vertex3DType_float32vec4, Vertex3DConstant_float32vec4_1f_0f_0f_0f, Vertex3DConstant_float32_1f, Vertex3DConstant_float32_0f, Vertex3DConstant_float32_0f, Vertex3DConstant_float32_0f,\
(7<<SpvWordCountShift)|SpvOpConstantComposite, Vertex3DType_float32vec4, Vertex3DConstant_float32vec4_0f_1f_0f_0f, Vertex3DConstant_float32_0f, Vertex3DConstant_float32_1f, Vertex3DConstant_float32_0f, Vertex3DConstant_float32_0f,\
(7<<SpvWordCountShift)|SpvOpConstantComposite, Vertex3DType_float32vec4, Vertex3DConstant_float32vec4_0f_0f_1f_0f, Vertex3DConstant_float32_0f, Vertex3DConstant_float32_0f, Vertex3DConstant_float32_1f, Vertex3DConstant_float32_0f,\
(7<<SpvWordCountShift)|SpvOpConstantComposite, Vertex3DType_float32vec4, Vertex3DConstant_float32vec4_0f_0f_0f_1f, Vertex3DConstant_float32_0f, Vertex3DConstant_float32_0f, Vertex3DConstant_float32_0f, Vertex3DConstant_float32_1f,\
(7<<SpvWordCountShift)|SpvOpConstantComposite, Vertex3DType_float32mat4, Vertex3DConstant_float32mat4_identity, Vertex3DConstant_float32vec4_1f_0f_0f_0f, Vertex3DConstant_float32vec4_0f_1f_0f_0f, Vertex3DConstant_float32vec4_0f_0f_1f_0f, Vertex3DConstant_float32vec4_0f_0f_0f_1f,\
}

#define VertexShader3D_Variable_AttributeInput_Size (12 * sizeof(SPIRV))
#define VertexShader3D_Variable_AttributeInput(i, type) {\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 4, SpvStorageClassInput, type,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 4, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 0, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpConstant, Vertex3DType_int32, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 7, i,\
}
#define VertexShader3D_Variable_AttributeOutput_Size (8 * sizeof(SPIRV))
#define VertexShader3D_Variable_AttributeOutput(i, type) {\
(4<<SpvWordCountShift)|SpvOpTypePointer, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 5, SpvStorageClassOutput, type,\
(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 5, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 1, SpvStorageClassOutput,\
}


#define VertexShader3D_Main2_Size (65 * sizeof(SPIRV))
#define VertexShader3D_Main2() {\
/*actual logic*/\
/*starting function*/\
(5<<SpvWordCountShift)|SpvOpFunction, Vertex3DType_Void, Vertex3DFunction_Main, SpvFunctionControlMaskNone, Vertex3DType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, Vertex3DLabel_StartOfFunction,\
	/*skin matrix*/\
	(5<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_FunctionPointer_float32mat4, Vertex3DVariable_FunctionPointer_float32mat4_SkinMatrix, SpvStorageClassFunction, Vertex3DConstant_float32mat4_identity,\
	/*skin weights*/\
	(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_FunctionPointer_float32vec4, Vertex3DVariable_FunctionPointer_float32vec4_SkinWeights, SpvStorageClassFunction,\
	/*joints*/\
	(4<<SpvWordCountShift)|SpvOpVariable, Vertex3DType_FunctionPointer_int32vec4, Vertex3DVariable_FunctionPointer_int32vec4_Joints, SpvStorageClassFunction,\
	/*get pushconstants VP matrix*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Vertex3DType_PushConstantPointer_float32mat4, Vertex3DVariable_PushConstantPointer_MatrixVP, Vertex3DVariable_PushConstantPointer_Struct_PushConstants, Vertex3DConstant_int_0,\
	(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_float32mat4, Vertex3DLoadedVariable_PushConstantPointer_MatrixVP, Vertex3DVariable_PushConstantPointer_MatrixVP,\
	/*get infos index offset*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Vertex3DType_PushConstantPointer_int32, Vertex3DVariable_PushConstantPointer_InfosOffset, Vertex3DVariable_PushConstantPointer_Struct_PushConstants, Vertex3DConstant_int_1,\
	(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_int32, Vertex3DVLoadedVariable_int32_InfosOffset, Vertex3DVariable_PushConstantPointer_InfosOffset,\
	/*get weights index offset*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Vertex3DType_PushConstantPointer_int32, Vertex3DVariable_PushConstantPointer_WeightsOffset, Vertex3DVariable_PushConstantPointer_Struct_PushConstants, Vertex3DConstant_int_2,\
	(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_int32, Vertex3DVLoadedVariable_int32_WeightsOffset, Vertex3DVariable_PushConstantPointer_WeightsOffset,\
	/*get joints matrixs index offset*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Vertex3DType_PushConstantPointer_int32, Vertex3DVariable_PushConstantPointer_JointsOffset, Vertex3DVariable_PushConstantPointer_Struct_PushConstants, Vertex3DConstant_int_3,\
	(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_int32, Vertex3DVLoadedVariable_int32_JointsOffset, Vertex3DVariable_PushConstantPointer_JointsOffset,\
	/*get matrixs index offset*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Vertex3DType_PushConstantPointer_int32, Vertex3DVariable_PushConstantPointer_MatricesOffset, Vertex3DVariable_PushConstantPointer_Struct_PushConstants, Vertex3DConstant_int_4,\
	(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_int32, Vertex3DVLoadedVariable_int32_MatricesOffset, Vertex3DVariable_PushConstantPointer_MatricesOffset,\
	/*convert*/\
}





#define VertexShader3D_Function_AttributeNormalized_Size (63 * sizeof(SPIRV))
#define VertexShader3D_Function_AttributeNormalized(i, type, outputpointer) {\
/*infosoffset + currentattrib*/\
(5<<SpvWordCountShift)|SpvOpIAdd, Vertex3DType_int32, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 17, Vertex3DVLoadedVariable_int32_InfosOffset, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 7,\
(7<<SpvWordCountShift)|SpvOpAccessChain, Vertex3DType_StorageBufferPointer_int32, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 18, Vertex3DVariable_StorageBufferPointer_struct_Infos, Vertex3DConstant_int_0, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 17, Vertex3DConstant_int_1,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_int32, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 19, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 18,\
/*normalize and store*/\
(4<<SpvWordCountShift)|SpvOpLoad, type, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 20, outputpointer,\
(7<<SpvWordCountShift)|SpvOpExtInst, Vertex3DType_float32, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 21, Vertex3DExtension_GLSL450, 26, Vertex3DConstant_float32_2f, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 19,\
(5<<SpvWordCountShift)|SpvOpVectorTimesScalar, type, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 22, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 20, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 21,\
(3<<SpvWordCountShift)|SpvOpStore, outputpointer, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 22,\
}

#define VertexShader3D_Function_AttributeWeighted_Size (52 * sizeof(SPIRV))
#define VertexShader3D_Function_AttributeWeighted(i, type, outputpointer) {\
/*add weights offset and targetgroup*/\
/*getinfos*/\
(5<<SpvWordCountShift)|SpvOpIAdd, Vertex3DType_int32, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 8, Vertex3DVLoadedVariable_int32_InfosOffset, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 7,\
\
(7<<SpvWordCountShift)|SpvOpAccessChain, Vertex3DType_StorageBufferPointer_int32, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 9, Vertex3DVariable_StorageBufferPointer_struct_Infos, Vertex3DConstant_int_0, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 8, Vertex3DConstant_int_0,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_int32, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 10, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 9,\
\
(4<<SpvWordCountShift)|SpvOpLoad, type, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 6, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 0,\
\
(5<<SpvWordCountShift)|SpvOpIAdd, Vertex3DType_int32, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 11, Vertex3DVLoadedVariable_int32_WeightsOffset, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 10,\
(6<<SpvWordCountShift)|SpvOpAccessChain, Vertex3DType_StorageBufferPointer_float32_Weight, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 12, Vertex3DVariable_StorageBufferPointer_Struct_Weights, Vertex3DConstant_int_0, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 11,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_float32, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 13, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 12,\
/*weights * attrib*/\
(5<<SpvWordCountShift)|SpvOpVectorTimesScalar, type, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 14, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 6, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 13,\
/*+=*/\
(4<<SpvWordCountShift)|SpvOpLoad, type, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 15, outputpointer,\
(5<<SpvWordCountShift)|SpvOpFAdd, type, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 16, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 15, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 14,\
(3<<SpvWordCountShift)|SpvOpStore, outputpointer, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 16,\
}
#define VertexShader3D_Function_AttributePass_Size (7 * sizeof(SPIRV))
#define VertexShader3D_Function_AttributePass(i, type, outputpointer) {\
(4<<SpvWordCountShift)|SpvOpLoad, type, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 6, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 0,\
(3<<SpvWordCountShift)|SpvOpStore, outputpointer, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 6,\
}





/*takes 20 places*/
#define VertexShader3D_Function_AttributeSkinComponent(startingindex, componentindex)\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Vertex3DType_int32, startingindex + 0, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 19, componentindex,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, Vertex3DType_float32, startingindex + 1,  Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 20, componentindex,\
(5<<SpvWordCountShift)|SpvOpIAdd, Vertex3DType_int32, startingindex + 2, startingindex + 0, Vertex3DVLoadedVariable_int32_JointsOffset,\
(6<<SpvWordCountShift)|SpvOpAccessChain, Vertex3DType_StorageBufferPointer_float32mat4_JointMatrix, startingindex + 3, Vertex3DVariable_StorageBufferPointer_Struct_JointsMatrices, Vertex3DConstant_int_0, startingindex + 2,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_float32mat4, startingindex + 4, startingindex + 3,\
(5<<SpvWordCountShift)|SpvOpMatrixTimesScalar, Vertex3DType_float32mat4, startingindex + 5, startingindex + 4, startingindex + 1,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_float32mat4, startingindex + 6, Vertex3DVariable_FunctionPointer_float32mat4_SkinMatrix,\
SPIRV_Matrix4x4Add(startingindex + 8, Vertex3DType_float32vec4, Vertex3DType_float32mat4, startingindex + 7, startingindex + 6, startingindex + 5)\
(3<<SpvWordCountShift)|SpvOpStore, Vertex3DVariable_FunctionPointer_float32mat4_SkinMatrix, startingindex + 7,

#define VertexShader3D_Function_AttributeSkin_Size (424 * sizeof(SPIRV))
#define VertexShader3D_Function_AttributeSkin(i) {\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_int32vec4, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 23, Vertex3DVariable_FunctionPointer_int32vec4_Joints,\
(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_float32vec4, Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 24, Vertex3DVariable_FunctionPointer_float32vec4_SkinWeights,\
\
VertexShader3D_Function_AttributeSkinComponent(Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 25, 0)\
VertexShader3D_Function_AttributeSkinComponent(Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 45, 1)\
VertexShader3D_Function_AttributeSkinComponent(Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 65, 2)\
VertexShader3D_Function_AttributeSkinComponent(Vertex3DVariables_MAX + (i * Vertex3DDynamSize) + 85, 3)\
}

#define VertexShader3D_Main3_Size (57 * sizeof(SPIRV))
#define VertexShader3D_Main3() {\
	/*Position = vec4((pushconstants.VP * matrixarray[pushconstants.MatrixsOffset]) * SkinMatrix *  vec4(FinalPosition, 1));*/\
	/*matrixarray[pushconstants.MatrixsOffset]*/\
	(6<<SpvWordCountShift)|SpvOpAccessChain, Vertex3DType_StorageBufferPointer_float32mat4_Matrix, Vertex3DVariable_StorageBufferPointer_float32mat4_Matrix, Vertex3DVariable_StorageBufferPointer_Struct_Matrices, Vertex3DConstant_int_0, Vertex3DVLoadedVariable_int32_MatricesOffset,\
	(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_float32mat4, Vertex3DLoadedVariable_float32mat4_Matrix, Vertex3DVariable_StorageBufferPointer_float32mat4_Matrix,\
	/*pushconstants.VP * matrixarray[pushconstants.MatrixsOffset]*/\
	(5<<SpvWordCountShift)|SpvOpMatrixTimesMatrix, Vertex3DType_float32mat4, Vertex3DLoadedVariable_float32mat4_op0, Vertex3DLoadedVariable_PushConstantPointer_MatrixVP, Vertex3DLoadedVariable_float32mat4_Matrix,\
	/*vec4(FinalPosition, 1)*/\
	(5<<SpvWordCountShift)|SpvOpCompositeConstruct, Vertex3DType_float32vec2, Vertex3DLoadedVariable_float32vec2_op1, Vertex3DConstant_float32_1f, Vertex3DConstant_float32_1f,\
	(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_float32vec3, Vertex3DLoadedVariable_float32vec3_op2, Vertex3DVariable_OutputPointer_float32vec3_FinalPosition,\
	(9<<SpvWordCountShift)|SpvOpVectorShuffle, Vertex3DType_float32vec4, Vertex3DLoadedVariable_float32vec4_op3, Vertex3DLoadedVariable_float32vec3_op2, Vertex3DLoadedVariable_float32vec2_op1, 0, 1, 2, 3,\
	/*mul1*/\
	(4<<SpvWordCountShift)|SpvOpLoad, Vertex3DType_float32mat4, Vertex3DLoadedVariable_float32mat4_op4, Vertex3DVariable_FunctionPointer_float32mat4_SkinMatrix,\
	(5<<SpvWordCountShift)|SpvOpMatrixTimesMatrix, Vertex3DType_float32mat4, Vertex3DLoadedVariable_float32mat4_op5, Vertex3DLoadedVariable_float32mat4_op0, Vertex3DLoadedVariable_float32mat4_op4,\
	/*mul2	*/\
	(5<<SpvWordCountShift)|SpvOpMatrixTimesVector, Vertex3DType_float32vec4, Vertex3DLoadedVariable_float32vec4_op6, Vertex3DLoadedVariable_float32mat4_op5, Vertex3DLoadedVariable_float32vec4_op3,\
	/*store to builtin position and position*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Vertex3DType_OutputPointer_float32vec4, Vertex3DVariable_OutputPointer_float32vec4_Position, Vertex3DVariable_OutputPointer_BuiltInStruct, Vertex3DConstant_int_0,\
	(3<<SpvWordCountShift)|SpvOpStore, Vertex3DVariable_OutputPointer_float32vec4_Position, Vertex3DLoadedVariable_float32vec4_op6,\
/*end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}


////////////////////////////////////////////////////////////////////////
//frag//////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

#define Fragment3DDynamSize (30)
typedef enum FragmentShader3DVariables {
	Fragment3DVariable_ZEROISNOTUSED,
	Fragment3DExtension_GLSL450,
	Fragment3DFunction_Main,

	Fragment3DType_Void,
	Fragment3DType_Function,
	Fragment3DType_bool,

	Fragment3DType_float32,
	Fragment3DType_float32vec2,
	Fragment3DType_float32vec3,
	Fragment3DType_float32vec4,
	Fragment3DType_float32mat4,

	Fragment3DType_uint32,
	Fragment3DType_uint32vec2,
	Fragment3DType_uint32vec3,
	Fragment3DType_uint32vec4,

	Fragment3DType_int32,
	Fragment3DType_int32vec2,
	Fragment3DType_int32vec3,
	Fragment3DType_int32vec4,

	//input

	//pushconstants
	Fragment3DType_Struct_PushConstants,
	Fragment3DType_PushConstantPointer_Struct_PushConstants,
	Fragment3DVariable_PushConstantPointer_Struct_PushConstants,
	//infos
	Fragment3DType_struct_Info,
	Fragment3DType_RuntimeArray_struct_Infos,
	Fragment3DType_struct_Infos,
	Fragment3DType_StorageBufferPointer_struct_Infos,
	Fragment3DVariable_StorageBufferPointer_struct_Infos,
	Fragment3DType_StorageBufferPointer_struct_Info,
	//weights
	Fragment3DType_RuntimeArray_float32_Weights,
	Fragment3DType_Struct_Weights,
	Fragment3DType_StorageBufferPointer_Struct_Weights,
	Fragment3DVariable_StorageBufferPointer_Struct_Weights,
	Fragment3DType_StorageBufferPointer_float32_Weight,
	//joints
	Fragment3DType_RuntimeArray_float32mat4_JointsMatrices,
	Fragment3DType_Struct_JointsMatrices,
	Fragment3DType_StorageBufferPointer_Struct_JointsMatrices,
	Fragment3DVariable_StorageBufferPointer_Struct_JointsMatrices,
	Fragment3DType_StorageBufferPointer_float32mat4_JointMatrix,
	//lights
	Fragment3DType_Struct_Light,
	Fragment3DType_RuntimeArray_struct_Lights,
	Fragment3DType_Struct_Lights,
	Fragment3DType_StorageBufferPointer_Struct_Lights,
	Fragment3DVariable_StorageBufferPointer_Struct_Lights,
	Fragment3DType_StorageBufferPointer_Struct_Light,
	//matrices
	Fragment3DType_RuntimeArray_float32mat4_Matrices,
	Fragment3DType_Struct_Matrices,
	Fragment3DType_StorageBufferPointer_Struct_Matrices,
	Fragment3DVariable_StorageBufferPointer_Struct_Matrices,
	Fragment3DType_StorageBufferPointer_float32mat4_Matrix,
	//material
	Fragment3DType_struct_Material,
	Fragment3DType_UniformPointer_struct_Material,
	Fragment3DVariable_UniformPointer_struct_Material,

	//material textures
	Fragment3DType_Image_float32_2D_0_0_0_1_Unknown,
	Fragment3DType_SampledImage_float32_2D_0_0_0_1_Unknown,
	Fragment3DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown,
	Fragment3DVariable_UniformConstantPointer_Image_float32_Emissive,
	Fragment3DVariable_UniformConstantPointer_Image_float32_Normal,
	Fragment3DVariable_UniformConstantPointer_Image_float32_Occlusion,
	Fragment3DVariable_UniformConstantPointer_Image_float32_BaseColour,
	Fragment3DVariable_UniformConstantPointer_Image_float32_MetallicRoughness,



	//from vert
	Fragment3DType_InputPointer_float32vec3,
	Fragment3DType_InputPointer_float32vec4,

	Fragment3DVariable_InputPointer_float32vec3_FinalPosition,
	Fragment3DVariable_InputPointer_float32vec3_FinalNormal,
	Fragment3DVariable_InputPointer_float32vec4_FinalTangent,

	//output
	//output image attachments
	Fragment3DType_OutputPointer_float32vec4,
	Fragment3DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,
	Fragment3DVariable_OutputPointer_float32vec4_OutPositionOrRevealage,
	Fragment3DVariable_OutputPointer_float32vec4_OutNormal,
	Fragment3DVariable_OutputPointer_float32vec4_OutPBR,


	//constants
	Fragment3DConstant_float32_0f,
	Fragment3DConstant_float32_1f,

	Fragment3DConstant_uint_0,
	Fragment3DConstant_uint_1,

	Fragment3DConstant_int_0,
	Fragment3DConstant_int_1,
	Fragment3DConstant_int_2,
	Fragment3DConstant_int_3,
	Fragment3DConstant_int_4,



	//logic
	Fragment3DLabel_StartOfFunction,



	Fragment3DType_PushConstantPointer_float32mat4,
	Fragment3DVariable_PushConstantPointer_MatrixVP,
	Fragment3DLoadedVariable_PushConstantPointer_MatrixVP,

	Fragment3DType_PushConstantPointer_int32,

	Fragment3DVariable_PushConstantPointer_InfosOffset,
	Fragment3DVLoadedVariable_int32_InfosOffset,

	Fragment3DVariable_PushConstantPointer_WeightsOffset,
	Fragment3DLoadedVariable_int32_WeightsOffset,

	Fragment3DVariable_PushConstantPointer_JointsOffset,
	Fragment3DLoadedVariable_int32_JointsOffset,

	Fragment3DVariable_PushConstantPointer_MatricesOffset,
	Fragment3DLoadedVariable_int32_MatricesOffset,

	Fragment3DType_UniformPointer_float32vec4,
	Fragment3DVariable_UniformPointer_float32vec4_BaseColourFactor,
	Fragment3DLoadedVariable_float32vec4_BaseColourFactor,

	Fragment3DConstant_int_5,
	Fragment3DType_UniformPointer_float32,
	Fragment3DVariable_UniformPointer_float32_AlphaCutoff,
	Fragment3DLoadedVariable_float32_AlphaCutoff,

	Fragment3DType_FunctionPointer_float32vec4,
	Fragment3DConstant_float32vec4_NULL,
	Fragment3DVariable_FunctionPointer_float32vec4_Normal,
	Fragment3DVariable_FunctionPointer_float32vec4_Colour,
	Fragment3DVariable_FunctionPointer_float32vec4_Emissive,
	Fragment3DVariable_FunctionPointer_float32vec4_Occlusion,
	Fragment3DVariable_FunctionPointer_float32vec4_MetallicRoughness,

	Fragment3DLoadedVariable_float32vec4_op0,
	Fragment3DLoadedVariable_float32vec4_op1,
	Fragment3DLoadedVariable_float32vec2_op2,
	Fragment3DLoadedVariable_float32vec4_op3,

	Fragment3DLoadedVariable_float32vec2_op4,
	Fragment3DLoadedVariable_float32vec4_op5,
	Fragment3DLoadedVariable_float32vec4_op6,
	Fragment3DLoadedVariable_float32_op7,
	Fragment3DLoadedVariable_float32_op8,

	Fragment3DVariables_MAX,
}FragmentShader3DVariables;
#define FragmentShader3D_Main0_Size (42 * sizeof(SPIRV))
#define FragmentShader3D_Main0(attributesize) {\
SPIRV_Header(Fragment3DVariables_MAX + (Fragment3DDynamSize * attributesize))\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, Fragment3DExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
((24 + attributesize)<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelFragment, Fragment3DFunction_Main, 'niam', '\0', Fragment3DVariable_PushConstantPointer_Struct_PushConstants, Fragment3DVariable_StorageBufferPointer_struct_Infos, Fragment3DVariable_StorageBufferPointer_Struct_Weights,\
	Fragment3DVariable_StorageBufferPointer_Struct_JointsMatrices, Fragment3DVariable_StorageBufferPointer_Struct_Lights, Fragment3DVariable_StorageBufferPointer_Struct_Matrices, Fragment3DVariable_UniformPointer_struct_Material,\
	Fragment3DVariable_InputPointer_float32vec3_FinalPosition, Fragment3DVariable_InputPointer_float32vec3_FinalNormal, Fragment3DVariable_InputPointer_float32vec4_FinalTangent,\
	Fragment3DVariable_UniformConstantPointer_Image_float32_Emissive, Fragment3DVariable_UniformConstantPointer_Image_float32_Normal, Fragment3DVariable_UniformConstantPointer_Image_float32_Occlusion,\
	Fragment3DVariable_UniformConstantPointer_Image_float32_BaseColour, Fragment3DVariable_UniformConstantPointer_Image_float32_MetallicRoughness,\
	Fragment3DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment3DVariable_OutputPointer_float32vec4_OutPositionOrRevealage, Fragment3DVariable_OutputPointer_float32vec4_OutNormal, Fragment3DVariable_OutputPointer_float32vec4_OutPBR,\
}

#define FragmentShader3D_Interface_Attribute_Size (1 * sizeof(SPIRV))
#define FragmentShader3D_Interface_Attribute(i) {Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 0}

#define FragmentShader3D_ExecutionMode_Size (3 * sizeof(SPIRV))
#define FragmentShader3D_ExecutionMode() {(3<<SpvWordCountShift)|SpvOpExecutionMode, Fragment3DFunction_Main, SpvExecutionModeOriginUpperLeft,}



//sampler inputs
#define FragmentShader3D_Decoration_TextureInput_Size (8 * sizeof(SPIRV))
#define FragmentShader3D_Decoration_TextureInput(binding, image) {\
(4<<SpvWordCountShift)|SpvOpDecorate, image, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, image, SpvDecorationBinding, binding,\
}


//input pointer
#define FragmentShader3D_Decoration_Attribute_Size (4 * sizeof(SPIRV))
#define FragmentShader3D_Decoration_Attribute(i, shaderconnectsize) {\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 0, SpvDecorationLocation, shaderconnectsize,\
}


#define FragmentShader3D_Main1_Size (678 * sizeof(SPIRV))
#define FragmentShader3D_Main1() {\
/*decorations*/\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_PushConstants, 1, SpvDecorationOffset, 64,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_PushConstants, 2, SpvDecorationOffset, 64 + 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_PushConstants, 3, SpvDecorationOffset, 64 + 4 + 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_PushConstants, 4, SpvDecorationOffset, 64 + 4 + 4 + 4,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_Struct_PushConstants, SpvDecorationBlock,\
/*storagebuffers*/\
/*infos*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Info, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Info, 1, SpvDecorationOffset, 4,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_RuntimeArray_struct_Infos, SpvDecorationArrayStride, 8,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_struct_Infos, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Infos, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_StorageBufferPointer_struct_Infos, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_StorageBufferPointer_struct_Infos, SpvDecorationBinding, 0,\
/*weights*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_RuntimeArray_float32_Weights, SpvDecorationArrayStride, 4,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_Struct_Weights, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_Weights, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_StorageBufferPointer_Struct_Weights, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_StorageBufferPointer_Struct_Weights, SpvDecorationBinding, 1,\
/*joints*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_RuntimeArray_float32mat4_JointsMatrices, SpvDecorationArrayStride, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_RuntimeArray_float32mat4_JointsMatrices, SpvDecorationColMajor,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_RuntimeArray_float32mat4_JointsMatrices, SpvDecorationMatrixStride, 16,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_Struct_JointsMatrices, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_JointsMatrices, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_StorageBufferPointer_Struct_JointsMatrices, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_StorageBufferPointer_Struct_JointsMatrices, SpvDecorationBinding, 2,\
/*lights*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_Light, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_Light, 1, SpvDecorationOffset, 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_Light, 2, SpvDecorationOffset, 8,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_Light, 3, SpvDecorationOffset, 12,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_Light, 4, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_Light, 5, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_Light, 6, SpvDecorationOffset, 48,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_RuntimeArray_struct_Lights, SpvDecorationArrayStride, 128,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_Struct_Lights, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_Lights, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_StorageBufferPointer_Struct_Lights, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_StorageBufferPointer_Struct_Lights, SpvDecorationBinding, 3,\
/*matrices*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_RuntimeArray_float32mat4_Matrices, SpvDecorationArrayStride, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_RuntimeArray_float32mat4_Matrices, SpvDecorationColMajor,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_RuntimeArray_float32mat4_Matrices, SpvDecorationMatrixStride, 16,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_Struct_Matrices, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_Struct_Matrices, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_StorageBufferPointer_Struct_Matrices, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_StorageBufferPointer_Struct_Matrices, SpvDecorationBinding, 4,\
/*material*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 1, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 2, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 3, SpvDecorationOffset, 36,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 4, SpvDecorationOffset, 40,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 5, SpvDecorationOffset, 44,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 6, SpvDecorationOffset, 48,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 7, SpvDecorationOffset, 52,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 8, SpvDecorationOffset, 56,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 9, SpvDecorationOffset, 60,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 10, SpvDecorationOffset, 64,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 11, SpvDecorationOffset, 68,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 12, SpvDecorationOffset, 72,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 13, SpvDecorationOffset, 76,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 14, SpvDecorationOffset, 80,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 15, SpvDecorationOffset, 84,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 16, SpvDecorationOffset, 88,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 17, SpvDecorationOffset, 92,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, Fragment3DType_struct_Material, 18, SpvDecorationOffset, 96,\
(3<<SpvWordCountShift)|SpvOpDecorate, Fragment3DType_struct_Material, SpvDecorationBlock,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_UniformPointer_struct_Material, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_UniformPointer_struct_Material, SpvDecorationBinding, 0,\
/*from vert*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_InputPointer_float32vec3_FinalPosition, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_InputPointer_float32vec3_FinalNormal, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_InputPointer_float32vec4_FinalTangent, SpvDecorationLocation, 2,\
/*outattachments*/\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_OutputPointer_float32vec4_OutNormal, SpvDecorationLocation, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, Fragment3DVariable_OutputPointer_float32vec4_OutPBR, SpvDecorationLocation, 3,\
/*basic types*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, Fragment3DType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, Fragment3DType_Function, Fragment3DType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, Fragment3DType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, Fragment3DType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment3DType_float32vec2, Fragment3DType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment3DType_float32vec3, Fragment3DType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment3DType_float32vec4, Fragment3DType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, Fragment3DType_float32mat4, Fragment3DType_float32vec4, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, Fragment3DType_uint32, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment3DType_uint32vec2, Fragment3DType_uint32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment3DType_uint32vec3, Fragment3DType_uint32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment3DType_uint32vec4, Fragment3DType_uint32, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, Fragment3DType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment3DType_int32vec2, Fragment3DType_int32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment3DType_int32vec3, Fragment3DType_int32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, Fragment3DType_int32vec4, Fragment3DType_int32, 4,\
/*basic constants*/\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment3DType_float32, Fragment3DConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment3DType_float32, Fragment3DConstant_float32_1f, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment3DType_uint32, Fragment3DConstant_uint_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment3DType_uint32, Fragment3DConstant_uint_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment3DType_int32, Fragment3DConstant_int_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment3DType_int32, Fragment3DConstant_int_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment3DType_int32, Fragment3DConstant_int_2, 2,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment3DType_int32, Fragment3DConstant_int_3, 3,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment3DType_int32, Fragment3DConstant_int_4, 4,\
/*inputs*/\
/*pushconstants*/\
(7<<SpvWordCountShift)|SpvOpTypeStruct, Fragment3DType_Struct_PushConstants, Fragment3DType_float32mat4, Fragment3DType_int32, Fragment3DType_int32, Fragment3DType_int32, Fragment3DType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_PushConstantPointer_Struct_PushConstants, SpvStorageClassPushConstant, Fragment3DType_Struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_PushConstantPointer_Struct_PushConstants, Fragment3DVariable_PushConstantPointer_Struct_PushConstants, SpvStorageClassPushConstant,\
/*storagebuffer infos*/\
(4<<SpvWordCountShift)|SpvOpTypeStruct, Fragment3DType_struct_Info, Fragment3DType_int32, Fragment3DType_int32,\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, Fragment3DType_RuntimeArray_struct_Infos, Fragment3DType_struct_Info,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, Fragment3DType_struct_Infos, Fragment3DType_RuntimeArray_struct_Infos,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_StorageBufferPointer_struct_Infos, SpvStorageClassStorageBuffer, Fragment3DType_struct_Infos,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_StorageBufferPointer_struct_Infos, Fragment3DVariable_StorageBufferPointer_struct_Infos, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_StorageBufferPointer_struct_Info, SpvStorageClassStorageBuffer, Fragment3DType_struct_Info,\
/*storagebuffer weights*/\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, Fragment3DType_RuntimeArray_float32_Weights, Fragment3DType_float32,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, Fragment3DType_Struct_Weights, Fragment3DType_RuntimeArray_float32_Weights,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_StorageBufferPointer_Struct_Weights, SpvStorageClassStorageBuffer, Fragment3DType_Struct_Weights,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_StorageBufferPointer_Struct_Weights, Fragment3DVariable_StorageBufferPointer_Struct_Weights, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_StorageBufferPointer_float32_Weight, SpvStorageClassStorageBuffer, Fragment3DType_float32,\
/*storagebuffer joints*/\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, Fragment3DType_RuntimeArray_float32mat4_JointsMatrices, Fragment3DType_float32mat4,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, Fragment3DType_Struct_JointsMatrices, Fragment3DType_RuntimeArray_float32mat4_JointsMatrices,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_StorageBufferPointer_Struct_JointsMatrices, SpvStorageClassStorageBuffer, Fragment3DType_Struct_JointsMatrices,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_StorageBufferPointer_Struct_JointsMatrices, Fragment3DVariable_StorageBufferPointer_Struct_JointsMatrices, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_StorageBufferPointer_float32mat4_JointMatrix, SpvStorageClassStorageBuffer, Fragment3DType_float32mat4,\
/*storagebuffer lights*/\
(9<<SpvWordCountShift)|SpvOpTypeStruct, Fragment3DType_Struct_Light, Fragment3DType_float32, Fragment3DType_float32, Fragment3DType_float32, Fragment3DType_float32, Fragment3DType_float32vec4, Fragment3DType_float32vec4, Fragment3DType_int32,\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, Fragment3DType_RuntimeArray_struct_Lights, Fragment3DType_Struct_Light,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, Fragment3DType_Struct_Lights, Fragment3DType_RuntimeArray_struct_Lights,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_StorageBufferPointer_Struct_Lights, SpvStorageClassStorageBuffer, Fragment3DType_Struct_Lights,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_StorageBufferPointer_Struct_Lights, Fragment3DVariable_StorageBufferPointer_Struct_Lights, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_StorageBufferPointer_Struct_Light, SpvStorageClassStorageBuffer, Fragment3DType_Struct_Light,\
/*storagebuffer matrices*/\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, Fragment3DType_RuntimeArray_float32mat4_Matrices, Fragment3DType_float32mat4,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, Fragment3DType_Struct_Matrices, Fragment3DType_RuntimeArray_float32mat4_Matrices,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_StorageBufferPointer_Struct_Matrices, SpvStorageClassStorageBuffer, Fragment3DType_Struct_Matrices,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_StorageBufferPointer_Struct_Matrices, Fragment3DVariable_StorageBufferPointer_Struct_Matrices, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_StorageBufferPointer_float32mat4_Matrix, SpvStorageClassStorageBuffer, Fragment3DType_float32mat4,\
/*material*/\
(21<<SpvWordCountShift)|SpvOpTypeStruct, Fragment3DType_struct_Material, Fragment3DType_float32vec4, Fragment3DType_float32vec4, Fragment3DType_float32, Fragment3DType_float32, Fragment3DType_float32,\
	Fragment3DType_float32, Fragment3DType_float32, Fragment3DType_float32, Fragment3DType_float32, Fragment3DType_float32, Fragment3DType_int32, Fragment3DType_int32, Fragment3DType_int32, Fragment3DType_int32,\
	Fragment3DType_uint32, Fragment3DType_uint32, Fragment3DType_uint32, Fragment3DType_uint32, Fragment3DType_uint32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_UniformPointer_struct_Material, SpvStorageClassUniform, Fragment3DType_struct_Material,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_UniformPointer_struct_Material, Fragment3DVariable_UniformPointer_struct_Material, SpvStorageClassUniform,\
/*samplers*/\
(9<<SpvWordCountShift)|SpvOpTypeImage, Fragment3DType_Image_float32_2D_0_0_0_1_Unknown, Fragment3DType_float32, SpvDim2D, 0, 0, 0, 1, SpvImageFormatUnknown,\
(3<<SpvWordCountShift)|SpvOpTypeSampledImage, Fragment3DType_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment3DType_Image_float32_2D_0_0_0_1_Unknown,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, SpvStorageClassUniformConstant, Fragment3DType_SampledImage_float32_2D_0_0_0_1_Unknown,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment3DVariable_UniformConstantPointer_Image_float32_Emissive, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment3DVariable_UniformConstantPointer_Image_float32_Normal, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment3DVariable_UniformConstantPointer_Image_float32_Occlusion, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment3DVariable_UniformConstantPointer_Image_float32_BaseColour, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_UniformConstantPointer_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment3DVariable_UniformConstantPointer_Image_float32_MetallicRoughness, SpvStorageClassUniformConstant,\
/*from fragment shader location*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_InputPointer_float32vec3, SpvStorageClassInput, Fragment3DType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_InputPointer_float32vec4, SpvStorageClassInput, Fragment3DType_float32vec4,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_InputPointer_float32vec3, Fragment3DVariable_InputPointer_float32vec3_FinalPosition, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_InputPointer_float32vec3, Fragment3DVariable_InputPointer_float32vec3_FinalNormal, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_InputPointer_float32vec4, Fragment3DVariable_InputPointer_float32vec4_FinalTangent, SpvStorageClassInput,\
/*outputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_OutputPointer_float32vec4, SpvStorageClassOutput, Fragment3DType_float32vec4,\
/*misc*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_PushConstantPointer_float32mat4, SpvStorageClassPushConstant, Fragment3DType_float32mat4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_PushConstantPointer_int32, SpvStorageClassPushConstant, Fragment3DType_int32,\
(4<<SpvWordCountShift)|SpvOpConstant, Fragment3DType_int32, Fragment3DConstant_int_5, 5,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_FunctionPointer_float32vec4, SpvStorageClassFunction, Fragment3DType_float32vec4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_UniformPointer_float32vec4, SpvStorageClassUniform, Fragment3DType_float32vec4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DType_UniformPointer_float32, SpvStorageClassUniform, Fragment3DType_float32,\
(3<<SpvWordCountShift)|SpvOpConstantNull, Fragment3DType_float32vec4, Fragment3DConstant_float32vec4_NULL,\
\
(5<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_OutputPointer_float32vec4, Fragment3DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvStorageClassOutput,  Fragment3DConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_OutputPointer_float32vec4, Fragment3DVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvStorageClassOutput,  Fragment3DConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_OutputPointer_float32vec4, Fragment3DVariable_OutputPointer_float32vec4_OutNormal, SpvStorageClassOutput, Fragment3DConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_OutputPointer_float32vec4, Fragment3DVariable_OutputPointer_float32vec4_OutPBR, SpvStorageClassOutput, Fragment3DConstant_float32vec4_NULL,\
}

#define FragmentShader3D_Variable_AttributeInput_Size (8 * sizeof(SPIRV))
#define FragmentShader3D_Variable_AttributeInput(i, type) {\
(4<<SpvWordCountShift)|SpvOpTypePointer, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 1, SpvStorageClassInput, type,\
(4<<SpvWordCountShift)|SpvOpVariable, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 1, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 0, SpvStorageClassInput,\
}

#define FragmentShader3D_Main2_Size (95 * sizeof(SPIRV))
#define FragmentShader3D_Main2() {\
/*actual logic*/\
/*starting function*/\
(5<<SpvWordCountShift)|SpvOpFunction, Fragment3DType_Void, Fragment3DFunction_Main, SpvFunctionControlMaskNone, Fragment3DType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, Fragment3DLabel_StartOfFunction,\
	/*declare final variables*/\
	(5<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_FunctionPointer_float32vec4, Fragment3DVariable_FunctionPointer_float32vec4_Normal,  SpvStorageClassFunction, Fragment3DConstant_float32vec4_NULL,\
	(5<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_FunctionPointer_float32vec4, Fragment3DVariable_FunctionPointer_float32vec4_Colour, SpvStorageClassFunction, Fragment3DConstant_float32vec4_NULL,\
	(5<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_FunctionPointer_float32vec4, Fragment3DVariable_FunctionPointer_float32vec4_Emissive, SpvStorageClassFunction, Fragment3DConstant_float32vec4_NULL,\
	(5<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_FunctionPointer_float32vec4, Fragment3DVariable_FunctionPointer_float32vec4_Occlusion, SpvStorageClassFunction, Fragment3DConstant_float32vec4_NULL,\
	(5<<SpvWordCountShift)|SpvOpVariable, Fragment3DType_FunctionPointer_float32vec4, Fragment3DVariable_FunctionPointer_float32vec4_MetallicRoughness, SpvStorageClassFunction, Fragment3DConstant_float32vec4_NULL,\
	/*get pushconstants VP matrix*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment3DType_PushConstantPointer_float32mat4, Fragment3DVariable_PushConstantPointer_MatrixVP, Fragment3DVariable_PushConstantPointer_Struct_PushConstants, Fragment3DConstant_int_0,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32mat4, Fragment3DLoadedVariable_PushConstantPointer_MatrixVP, Fragment3DVariable_PushConstantPointer_MatrixVP,\
	/*get infos index offset*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment3DType_PushConstantPointer_int32, Fragment3DVariable_PushConstantPointer_InfosOffset, Fragment3DVariable_PushConstantPointer_Struct_PushConstants, Fragment3DConstant_int_1,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_int32, Fragment3DVLoadedVariable_int32_InfosOffset, Fragment3DVariable_PushConstantPointer_InfosOffset,\
	/*get weights index offset*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment3DType_PushConstantPointer_int32, Fragment3DVariable_PushConstantPointer_WeightsOffset, Fragment3DVariable_PushConstantPointer_Struct_PushConstants, Fragment3DConstant_int_2,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_int32, Fragment3DLoadedVariable_int32_WeightsOffset, Fragment3DVariable_PushConstantPointer_WeightsOffset,\
	/*get joints matrixs index offset*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment3DType_PushConstantPointer_int32, Fragment3DVariable_PushConstantPointer_JointsOffset, Fragment3DVariable_PushConstantPointer_Struct_PushConstants, Fragment3DConstant_int_3,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_int32, Fragment3DLoadedVariable_int32_JointsOffset, Fragment3DVariable_PushConstantPointer_JointsOffset,\
	/*get matrixs index offset*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment3DType_PushConstantPointer_int32, Fragment3DVariable_PushConstantPointer_MatricesOffset, Fragment3DVariable_PushConstantPointer_Struct_PushConstants, Fragment3DConstant_int_4,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_int32, Fragment3DLoadedVariable_int32_MatricesOffset, Fragment3DVariable_PushConstantPointer_MatricesOffset,\
	/*basecolourfactor*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment3DType_UniformPointer_float32vec4, Fragment3DVariable_UniformPointer_float32vec4_BaseColourFactor, Fragment3DVariable_UniformPointer_struct_Material, Fragment3DConstant_int_0,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32vec4, Fragment3DLoadedVariable_float32vec4_BaseColourFactor, Fragment3DVariable_UniformPointer_float32vec4_BaseColourFactor,\
	/*alphacutoff*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment3DType_UniformPointer_float32, Fragment3DVariable_UniformPointer_float32_AlphaCutoff, Fragment3DVariable_UniformPointer_struct_Material, Fragment3DConstant_int_5,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32, Fragment3DLoadedVariable_float32_AlphaCutoff, Fragment3DVariable_UniformPointer_float32_AlphaCutoff,\
}

#define FragmentShader3D_Function_AttributeTexCoord_Size (25 * sizeof(SPIRV))
#define FragmentShader3D_Function_AttributeTexCoord(startindex, i, image, outputpointer) {\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_SampledImage_float32_2D_0_0_0_1_Unknown, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 2 + startindex, image,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32vec2, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 3 + startindex, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 0,	\
	(5<<SpvWordCountShift)|SpvOpImageSampleImplicitLod, Fragment3DType_float32vec4, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 4 + startindex, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 2 + startindex, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 3 + startindex,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32vec4, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 5 + startindex, outputpointer,\
	(5<<SpvWordCountShift)|SpvOpFAdd, Fragment3DType_float32vec4, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 6 + startindex, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 5 + startindex, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 4 + startindex,\
	(3<<SpvWordCountShift)|SpvOpStore, outputpointer, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 6 + startindex,\
}
#define FragmentShader3D_Function_AttributeColour_Size (16 * sizeof(SPIRV))
#define FragmentShader3D_Function_AttributeColour(i) {\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32vec4, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 2, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 0,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32vec4, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 3, Fragment3DVariable_FunctionPointer_float32vec4_Colour,\
	(5<<SpvWordCountShift)|SpvOpFAdd, Fragment3DType_float32vec4, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 4, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 3, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 2,\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment3DVariable_FunctionPointer_float32vec4_Colour, Fragment3DVariables_MAX + (i * Fragment3DDynamSize) + 4,\
}

//after all attributes

#define FragmentShader3D_Function_Colour_Size (12 * sizeof(SPIRV))
#define FragmentShader3D_Function_Colour() {\
	/*Colour = outTransperancy.rgba  * Mtl.BaseColourFactor;*/\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32vec4, Fragment3DLoadedVariable_float32vec4_op0, Fragment3DVariable_FunctionPointer_float32vec4_Colour,\
	/*outTransperancy.rgba * Mtl.BaseColourFactor*/\
	(5<<SpvWordCountShift)|SpvOpFMul, Fragment3DType_float32vec4, Fragment3DLoadedVariable_float32vec4_op1, Fragment3DLoadedVariable_float32vec4_op0, Fragment3DLoadedVariable_float32vec4_BaseColourFactor,\
	/*store*/\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment3DVariable_FunctionPointer_float32vec4_Colour, Fragment3DLoadedVariable_float32vec4_op1,\
}
#define FragmentShader3D_Function_Alpha_Size (26 * sizeof(SPIRV))
#define FragmentShader3D_Function_Alpha() {\
	/*Colour = vec4(1, 1, 1, outTransperancy.r) * Mtl.BaseColourFactor;*/\
	/*vec4(1, 1, 1, outTransperancy.r)*/\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32vec4, Fragment3DLoadedVariable_float32vec4_op0, Fragment3DVariable_FunctionPointer_float32vec4_Colour,\
	(5<<SpvWordCountShift)|SpvOpCompositeConstruct, Fragment3DType_float32vec2, Fragment3DLoadedVariable_float32vec2_op2, Fragment3DConstant_float32_1f, Fragment3DConstant_float32_1f,\
	(9<<SpvWordCountShift)|SpvOpVectorShuffle, Fragment3DType_float32vec4, Fragment3DLoadedVariable_float32vec4_op1, Fragment3DLoadedVariable_float32vec4_op0, Fragment3DLoadedVariable_float32vec2_op2, 4, 4, 4, 0,\
	/*x * Mtl.BaseColourFactor*/\
	(5<<SpvWordCountShift)|SpvOpFMul, Fragment3DType_float32vec4, Fragment3DLoadedVariable_float32vec4_op3, Fragment3DLoadedVariable_float32vec4_op1, Fragment3DLoadedVariable_float32vec4_BaseColourFactor,\
	/*store*/\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment3DVariable_FunctionPointer_float32vec4_Colour, Fragment3DLoadedVariable_float32vec4_op3,\
}
#define FragmentShader3D_Function_Solid_Size (3 * sizeof(SPIRV))
#define FragmentShader3D_Function_Solid() {\
	/*Colour = Mtl.BaseColourFactor;*/\
	/*store*/\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment3DVariable_FunctionPointer_float32vec4_Colour, Fragment3DLoadedVariable_float32vec4_BaseColourFactor,\
}



#define FragmentShader3D_Function_Opaque_Size (21 * sizeof(SPIRV))
#define FragmentShader3D_Function_Opaque() {\
	/*outAlbedo = vec4(FinalColour.rgb, 1);*/\
	/*vec4(FinalColour.rgb, 1)*/\
	(5<<SpvWordCountShift)|SpvOpCompositeConstruct, Fragment3DType_float32vec2, Fragment3DLoadedVariable_float32vec2_op4, Fragment3DConstant_float32_1f, Fragment3DConstant_float32_1f,\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32vec4, Fragment3DLoadedVariable_float32vec4_op5, Fragment3DVariable_FunctionPointer_float32vec4_Colour,\
	(9<<SpvWordCountShift)|SpvOpVectorShuffle, Fragment3DType_float32vec4, Fragment3DLoadedVariable_float32vec4_op6, Fragment3DLoadedVariable_float32vec4_op5, Fragment3DLoadedVariable_float32vec2_op4, 0, 1, 2, 4,\
	/*store*/\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment3DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment3DLoadedVariable_float32vec4_op6,\
}
#define FragmentShader3D_Function_Mask_Size (33 * sizeof(SPIRV))
#define FragmentShader3D_Function_Mask() {\
	/*outAlbedo = vec4(FinalColour.rgb, step(Mtl.AlphaCutoff, FinalColour.a));*/\
	/*step(Mtl.AlphaCutoff, FinalColour.a)*/\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32vec4, Fragment3DLoadedVariable_float32vec4_op5, Fragment3DVariable_FunctionPointer_float32vec4_Colour,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, Fragment3DType_float32, Fragment3DLoadedVariable_float32_op7, Fragment3DLoadedVariable_float32vec4_op5, 3,\
	(7<<SpvWordCountShift)|SpvOpExtInst, Fragment3DType_float32, Fragment3DLoadedVariable_float32_op8, Fragment3DExtension_GLSL450, 48, Fragment3DLoadedVariable_float32_AlphaCutoff, Fragment3DLoadedVariable_float32_op7,\
	/*vec4(FinalColour.rgb, x)*/\
	(5<<SpvWordCountShift)|SpvOpCompositeConstruct, Fragment3DType_float32vec2, Fragment3DLoadedVariable_float32vec2_op4, Fragment3DLoadedVariable_float32_op8, Fragment3DLoadedVariable_float32_op8,\
	(9<<SpvWordCountShift)|SpvOpVectorShuffle, Fragment3DType_float32vec4, Fragment3DLoadedVariable_float32vec4_op6, Fragment3DLoadedVariable_float32vec4_op5, Fragment3DLoadedVariable_float32vec2_op4, 0, 1, 2, 4,\
	/*store*/\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment3DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment3DLoadedVariable_float32vec4_op6,\
}
#define FragmentShader3D_Function_Blend_Size (7 * sizeof(SPIRV))
#define FragmentShader3D_Function_Blend() {\
	/*outTransperancy = FinalColour;*/\
	/*load*/\
	(4<<SpvWordCountShift)|SpvOpLoad, Fragment3DType_float32vec4, Fragment3DLoadedVariable_float32vec4_op5, Fragment3DVariable_FunctionPointer_float32vec4_Colour,\
	/*store*/\
	(3<<SpvWordCountShift)|SpvOpStore, Fragment3DVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, Fragment3DLoadedVariable_float32vec4_op5,\
}

#define FragmentShader3D_Main3_Size (2 * sizeof(SPIRV))
#define FragmentShader3D_Main3() {\
	/*outNormal = vec4( mat3(matrixarray[pushconstants.MatrixsOffset]) * FinalNormal , 1); //* ((2*NormalS) - 1)*/\
	/*outPosition =  vec4((matrixarray[pushconstants.MatrixsOffset]) * dvec4(FinalPosition, 1));*/\
	/*outPBR = FinalMetallicRoughness;*/\
/*end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd\
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Water
///////////////////////////////////////////////////////////////////////////////////////////////

typedef enum ComputeShaderh0kVariables {
}ComputeShaderh0kVariables;
#define ComputeShaderh0kSize (1405 * sizeof(SPIRV))
#define ComputeShaderh0k() {\
SPIRV_Header(263)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, 1, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(9<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelGLCompute, 4, 'niam', '\0', 17, 24, 38, 242,\
(6<<SpvWordCountShift)|SpvOpExecutionMode, 4, SpvExecutionModeLocalSize, 16, 16, 1,\
\
(4<<SpvWordCountShift)|SpvOpDecorate, 17, SpvDecorationBuiltIn, SpvBuiltInGlobalInvocationId,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 22, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 22, 1, SpvDecorationOffset, 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 22, 2, SpvDecorationOffset, 8,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 22, 3, SpvDecorationOffset, 12,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 22, 4, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 22, 5, SpvDecorationOffset, 20,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 22, 6, SpvDecorationOffset, 24,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 22, 7, SpvDecorationOffset, 28,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 22, 8, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 22, 9, SpvDecorationOffset, 40,\
(3<<SpvWordCountShift)|SpvOpDecorate, 22, SpvDecorationBlock,\
(4<<SpvWordCountShift)|SpvOpDecorate, 38, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 38, SpvDecorationBinding, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, 242, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 242, SpvDecorationBinding, 0,\
(3<<SpvWordCountShift)|SpvOpDecorate, 242, SpvDecorationNonReadable,\
(4<<SpvWordCountShift)|SpvOpDecorate, 262, SpvDecorationBuiltIn, SpvBuiltInWorkgroupSize,\
\
(2<<SpvWordCountShift)|SpvOpTypeVoid, 2,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, 3, 2,\
(3<<SpvWordCountShift)|SpvOpTypeFloat, 6, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 7, 6, 4,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, 8, 7,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 11, 6, 2,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 12, SpvStorageClassFunction, 11,\
(4<<SpvWordCountShift)|SpvOpTypeInt, 14, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 15, 14, 3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 16, SpvStorageClassInput, 15,\
(4<<SpvWordCountShift)|SpvOpVariable, 16, 17, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 18, 14, 2,\
(12<<SpvWordCountShift)|SpvOpTypeStruct, 22, 14, 14, 14, 14, 14, 6, 6, 6, 6, 11,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 23, SpvStorageClassPushConstant, 22,\
(4<<SpvWordCountShift)|SpvOpVariable, 23, 24, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypeInt, 25, 32, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, 25, 26, 0,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 27, SpvStorageClassPushConstant, 14,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 33, SpvStorageClassFunction, 6,\
(9<<SpvWordCountShift)|SpvOpTypeImage, 35, 6, SpvDim2D, 0, 0, 0, 1, SpvImageFormatUnknown,\
(3<<SpvWordCountShift)|SpvOpTypeSampledImage, 36, 35,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 37, SpvStorageClassUniformConstant, 36,\
(4<<SpvWordCountShift)|SpvOpVariable, 37, 38, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 41, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, 14, 43, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 45, 981668463,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 46, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, 14, 52, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, 14, 59, 2,\
(4<<SpvWordCountShift)|SpvOpConstant, 14, 66, 3,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 70, 1086918619,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 74, 3221225472,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 87, SpvStorageClassFunction, 7,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 116, 1073741824,\
(4<<SpvWordCountShift)|SpvOpConstant, 25, 124, 4,\
(4<<SpvWordCountShift)|SpvOpConstant, 25, 138, 6,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 139, SpvStorageClassPushConstant, 6,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 145, 1092416963,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 151, 953267991,\
(2<<SpvWordCountShift)|SpvOpTypeBool, 152,\
(4<<SpvWordCountShift)|SpvOpConstant, 25, 161, 5,\
(4<<SpvWordCountShift)|SpvOpConstant, 25, 170, 9,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 171, SpvStorageClassPushConstant, 11,\
(4<<SpvWordCountShift)|SpvOpConstant, 25, 189, 7,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 197, 1068827891,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 199, 3313106944,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 200, 1165623296,\
(9<<SpvWordCountShift)|SpvOpTypeImage, 240, 6, SpvDim2D, 0, 0, 0, 2, SpvImageFormatR32f,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 241, SpvStorageClassUniformConstant, 240,\
(4<<SpvWordCountShift)|SpvOpVariable, 241, 242, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 246, 25, 2,\
(4<<SpvWordCountShift)|SpvOpConstant, 14, 261, 16,\
(6<<SpvWordCountShift)|SpvOpConstantComposite, 15, 262, 261, 261, 52,\
(5<<SpvWordCountShift)|SpvOpFunction, 2, 4, SpvFunctionControlMaskNone, 3,\
(2<<SpvWordCountShift)|SpvOpLabel, 5,\
(4<<SpvWordCountShift)|SpvOpVariable, 12, 109, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 12, 120, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 137, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 147, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 156, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 160, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 202, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 87, 238, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpLoad, 15, 110, 17,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 18, 111, 110, 110, 0, 1,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, 11, 112, 111,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 27, 113, 24, 26,\
(4<<SpvWordCountShift)|SpvOpLoad, 14, 114, 113,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, 6, 115, 114,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 117, 115, 116,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 11, 118, 117, 117,\
(5<<SpvWordCountShift)|SpvOpFSub, 11, 119, 112, 118,\
(3<<SpvWordCountShift)|SpvOpStore, 109, 119,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 33, 121, 109, 43,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 122, 121,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 123, 70, 122,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 27, 125, 24, 124,\
(4<<SpvWordCountShift)|SpvOpLoad, 14, 126, 125,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, 6, 127, 126,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 128, 123, 127,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 33, 129, 109, 52,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 130, 129,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 131, 70, 130,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 27, 132, 24, 124,\
(4<<SpvWordCountShift)|SpvOpLoad, 14, 133, 132,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, 6, 134, 133,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 135, 131, 134,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 11, 136, 128, 135,\
(3<<SpvWordCountShift)|SpvOpStore, 120, 136,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 139, 140, 24, 138,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 141, 140,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 139, 142, 24, 138,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 143, 142,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 144, 141, 143,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 146, 144, 145,\
(3<<SpvWordCountShift)|SpvOpStore, 137, 146,\
(4<<SpvWordCountShift)|SpvOpLoad, 11, 148, 120,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 149, 1, 66, 148,\
(3<<SpvWordCountShift)|SpvOpStore, 147, 149,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 150, 147,\
(5<<SpvWordCountShift)|SpvOpFOrdLessThan, 152, 153, 150, 151,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, 155, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, 153, 154, 155,\
(2<<SpvWordCountShift)|SpvOpLabel, 154,\
(3<<SpvWordCountShift)|SpvOpStore, 147, 151,\
(2<<SpvWordCountShift)|SpvOpBranch, 155,\
(2<<SpvWordCountShift)|SpvOpLabel, 155,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 157, 147,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 158, 147,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 159, 157, 158,\
(3<<SpvWordCountShift)|SpvOpStore, 156, 159,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 139, 162, 24, 161,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 163, 162,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 164, 156,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 165, 156,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 166, 164, 165,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 167, 163, 166,\
(4<<SpvWordCountShift)|SpvOpLoad, 11, 168, 120,\
(6<<SpvWordCountShift)|SpvOpExtInst, 11, 169, 1, 69, 168,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 171, 172, 24, 170,\
(4<<SpvWordCountShift)|SpvOpLoad, 11, 173, 172,\
(6<<SpvWordCountShift)|SpvOpExtInst, 11, 174, 1, 69, 173,\
(5<<SpvWordCountShift)|SpvOpDot, 6, 175, 169, 174,\
(7<<SpvWordCountShift)|SpvOpExtInst, 6, 176, 1, 26, 175, 116,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 177, 167, 176,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 178, 156,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 179, 137,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 180, 178, 179,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 181, 137,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 182, 180, 181,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 183, 46, 182,\
(4<<SpvWordCountShift)|SpvOpFNegate, 6, 184, 183,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 185, 1, 27, 184,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 186, 177, 185,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 187, 156,\
(4<<SpvWordCountShift)|SpvOpFNegate, 6, 188, 187,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 139, 190, 24, 189,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 191, 190,\
(7<<SpvWordCountShift)|SpvOpExtInst, 6, 192, 1, 26, 191, 116,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 193, 188, 192,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 194, 1, 27, 193,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 195, 186, 194,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 196, 1, 31, 195,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 198, 196, 197,\
(8<<SpvWordCountShift)|SpvOpExtInst, 6, 201, 1, 43, 198, 199, 200,\
(3<<SpvWordCountShift)|SpvOpStore, 160, 201,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 139, 203, 24, 161,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 204, 203,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 205, 156,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 206, 156,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 207, 205, 206,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 208, 204, 207,\
(4<<SpvWordCountShift)|SpvOpLoad, 11, 209, 120,\
(4<<SpvWordCountShift)|SpvOpFNegate, 11, 210, 209,\
(6<<SpvWordCountShift)|SpvOpExtInst, 11, 211, 1, 69, 210,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 171, 212, 24, 170,\
(4<<SpvWordCountShift)|SpvOpLoad, 11, 213, 212,\
(6<<SpvWordCountShift)|SpvOpExtInst, 11, 214, 1, 69, 213,\
(5<<SpvWordCountShift)|SpvOpDot, 6, 215, 211, 214,\
(7<<SpvWordCountShift)|SpvOpExtInst, 6, 216, 1, 26, 215, 116,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 217, 208, 216,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 218, 156,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 219, 137,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 220, 218, 219,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 221, 137,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 222, 220, 221,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 223, 46, 222,\
(4<<SpvWordCountShift)|SpvOpFNegate, 6, 224, 223,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 225, 1, 27, 224,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 226, 217, 225,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 227, 156,\
(4<<SpvWordCountShift)|SpvOpFNegate, 6, 228, 227,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 139, 229, 24, 189,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 230, 229,\
(7<<SpvWordCountShift)|SpvOpExtInst, 6, 231, 1, 26, 230, 116,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 232, 228, 231,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 233, 1, 27, 232,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 234, 226, 233,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 235, 1, 31, 234,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 236, 235, 197,\
(8<<SpvWordCountShift)|SpvOpExtInst, 6, 237, 1, 43, 236, 199, 200,\
(3<<SpvWordCountShift)|SpvOpStore, 202, 237,\
(4<<SpvWordCountShift)|SpvOpFunctionCall, 7, 239, 9,\
(3<<SpvWordCountShift)|SpvOpStore, 238, 239,\
(4<<SpvWordCountShift)|SpvOpLoad, 240, 243, 242,\
(4<<SpvWordCountShift)|SpvOpLoad, 15, 244, 17,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 18, 245, 244, 244, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 246, 247, 245,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 248, 238,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 11, 249, 248, 248, 0, 1,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 250, 160,\
(5<<SpvWordCountShift)|SpvOpVectorTimesScalar, 11, 251, 249, 250,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 252, 238,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 11, 253, 252, 252, 2, 3,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 254, 202,\
(5<<SpvWordCountShift)|SpvOpVectorTimesScalar, 11, 255, 253, 254,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 256, 251, 0,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 257, 251, 1,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 258, 255, 0,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 259, 255, 1,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 260, 256, 257, 258, 259,\
(4<<SpvWordCountShift)|SpvOpImageWrite, 243, 247, 260,\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
(5<<SpvWordCountShift)|SpvOpFunction, 7, 9, SpvFunctionControlMaskNone, 8,\
(2<<SpvWordCountShift)|SpvOpLabel, 10,\
(4<<SpvWordCountShift)|SpvOpVariable, 12, 13, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 34, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 48, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 55, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 62, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 69, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 73, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 79, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 33, 82, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 87, 88, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpLoad, 15, 19, 17,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 18, 20, 19, 19, 0, 1,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, 11, 21, 20,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 27, 28, 24, 26,\
(4<<SpvWordCountShift)|SpvOpLoad, 14, 29, 28,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, 6, 30, 29,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 11, 31, 30, 30,\
(5<<SpvWordCountShift)|SpvOpFDiv, 11, 32, 21, 31,\
(3<<SpvWordCountShift)|SpvOpStore, 13, 32,\
(4<<SpvWordCountShift)|SpvOpLoad, 36, 39, 38,\
(4<<SpvWordCountShift)|SpvOpLoad, 11, 40, 13,\
(7<<SpvWordCountShift)|SpvOpImageSampleExplicitLod, 7, 42, 39, 40, SpvImageOperandsLodMask, 41,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 44, 42, 0,\
(8<<SpvWordCountShift)|SpvOpExtInst, 6, 47, 1, 43, 44, 45, 46,\
(3<<SpvWordCountShift)|SpvOpStore, 34, 47,\
(4<<SpvWordCountShift)|SpvOpLoad, 36, 49, 38,\
(4<<SpvWordCountShift)|SpvOpLoad, 11, 50, 13,\
(7<<SpvWordCountShift)|SpvOpImageSampleExplicitLod, 7, 51, 49, 50, SpvImageOperandsLodMask, 41,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 53, 51, 1,\
(8<<SpvWordCountShift)|SpvOpExtInst, 6, 54, 1, 43, 53, 45, 46,\
(3<<SpvWordCountShift)|SpvOpStore, 48, 54,\
(4<<SpvWordCountShift)|SpvOpLoad, 36, 56, 38,\
(4<<SpvWordCountShift)|SpvOpLoad, 11, 57, 13,\
(7<<SpvWordCountShift)|SpvOpImageSampleExplicitLod, 7, 58, 56, 57, SpvImageOperandsLodMask, 41,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 60, 58, 2,\
(8<<SpvWordCountShift)|SpvOpExtInst, 6, 61, 1, 43, 60, 45, 46,\
(3<<SpvWordCountShift)|SpvOpStore, 55, 61,\
(4<<SpvWordCountShift)|SpvOpLoad, 36, 63, 38,\
(4<<SpvWordCountShift)|SpvOpLoad, 11, 64, 13,\
(7<<SpvWordCountShift)|SpvOpImageSampleExplicitLod, 7, 65, 63, 64, SpvImageOperandsLodMask, 41,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 67, 65, 3,\
(8<<SpvWordCountShift)|SpvOpExtInst, 6, 68, 1, 43, 67, 45, 46,\
(3<<SpvWordCountShift)|SpvOpStore, 62, 68,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 71, 34,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 72, 70, 71,\
(3<<SpvWordCountShift)|SpvOpStore, 69, 72,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 75, 48,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 76, 1, 28, 75,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 77, 74, 76,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 78, 1, 31, 77,\
(3<<SpvWordCountShift)|SpvOpStore, 73, 78,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 80, 55,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 81, 70, 80,\
(3<<SpvWordCountShift)|SpvOpStore, 79, 81,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 83, 62,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 84, 1, 28, 83,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 85, 74, 84,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 86, 1, 31, 85,\
(3<<SpvWordCountShift)|SpvOpStore, 82, 86,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 89, 73,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 90, 69,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 91, 1, 14, 90,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 92, 89, 91,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 93, 73,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 94, 69,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 95, 1, 13, 94,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 96, 93, 95,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 97, 82,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 98, 79,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 99, 1, 14, 98,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 100, 97, 99,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 101, 82,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 102, 79,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 103, 1, 13, 102,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 104, 101, 103,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 105, 92, 96, 100, 104,\
(3<<SpvWordCountShift)|SpvOpStore, 88, 105,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 106, 88,\
(2<<SpvWordCountShift)|SpvOpReturnValue, 106,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd\
}

typedef enum ComputeShaderhktVariables {
}ComputeShaderhktVariables;
#define ComputeShaderhktSize (1439 * sizeof(SPIRV));
#define ComputeShaderhkt() {\
SPIRV_Header(271)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, 1, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(11<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelGLCompute, 4, 'niam', '\0', 86, 95, 141, 238, 249, 259,\
(6<<SpvWordCountShift)|SpvOpExecutionMode, 4, SpvExecutionModeLocalSize, 16, 16, 1,\
\
(4<<SpvWordCountShift)|SpvOpDecorate, 86, SpvDecorationBuiltIn, SpvBuiltInGlobalInvocationId,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 93, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 93, 1, SpvDecorationOffset, 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 93, 2, SpvDecorationOffset, 8,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 93, 3, SpvDecorationOffset, 12,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 93, 4, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 93, 5, SpvDecorationOffset, 20,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 93, 6, SpvDecorationOffset, 24,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 93, 7, SpvDecorationOffset, 28,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 93, 8, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 93, 9, SpvDecorationOffset, 40,\
(3<<SpvWordCountShift)|SpvOpDecorate, 93, SpvDecorationBlock,\
(4<<SpvWordCountShift)|SpvOpDecorate, 141, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 141, SpvDecorationBinding, 3,\
(3<<SpvWordCountShift)|SpvOpDecorate, 141, SpvDecorationNonWritable,\
(4<<SpvWordCountShift)|SpvOpDecorate, 238, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 238, SpvDecorationBinding, 0,\
(3<<SpvWordCountShift)|SpvOpDecorate, 238, SpvDecorationNonReadable,\
(4<<SpvWordCountShift)|SpvOpDecorate, 249, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 249, SpvDecorationBinding, 1,\
(3<<SpvWordCountShift)|SpvOpDecorate, 249, SpvDecorationNonReadable,\
(4<<SpvWordCountShift)|SpvOpDecorate, 259, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 259, SpvDecorationBinding, 2,\
(3<<SpvWordCountShift)|SpvOpDecorate, 259, SpvDecorationNonReadable,\
(4<<SpvWordCountShift)|SpvOpDecorate, 270, SpvDecorationBuiltIn, SpvBuiltInWorkgroupSize,\
\
(2<<SpvWordCountShift)|SpvOpTypeVoid, 2,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, 3, 2,\
(3<<SpvWordCountShift)|SpvOpTypeFloat, 6, 32,\
(4<<SpvWordCountShift)|SpvOpTypeStruct, 7, 6, 6,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 8, SpvStorageClassFunction, 7,\
(5<<SpvWordCountShift)|SpvOpTypeFunction, 9, 7, 8, 8,\
(4<<SpvWordCountShift)|SpvOpTypeFunction, 18, 7, 8,\
(4<<SpvWordCountShift)|SpvOpTypeInt, 23, 32, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, 23, 24, 0,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 25, SpvStorageClassFunction, 6,\
(4<<SpvWordCountShift)|SpvOpConstant, 23, 31, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 80, 6, 2,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 81, SpvStorageClassFunction, 80,\
(4<<SpvWordCountShift)|SpvOpTypeInt, 83, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 84, 83, 3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 85, SpvStorageClassInput, 84,\
(4<<SpvWordCountShift)|SpvOpVariable, 85, 86, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 87, 83, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 90, 23, 2,\
(12<<SpvWordCountShift)|SpvOpTypeStruct, 93, 83, 83, 83, 83, 83, 6, 6, 6, 6, 80,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 94, SpvStorageClassPushConstant, 93,\
(4<<SpvWordCountShift)|SpvOpVariable, 94, 95, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 96, SpvStorageClassPushConstant, 83,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 100, 1073741824,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 105, 1086918619,\
(4<<SpvWordCountShift)|SpvOpConstant, 83, 106, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, 23, 110, 4,\
(4<<SpvWordCountShift)|SpvOpConstant, 83, 115, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 128, 925353388,\
(2<<SpvWordCountShift)|SpvOpTypeBool, 129,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 134, 1092416963,\
(9<<SpvWordCountShift)|SpvOpTypeImage, 139, 6, SpvDim2D, 0, 0, 0, 2, SpvImageFormatR32f,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 140, SpvStorageClassUniformConstant, 139,\
(4<<SpvWordCountShift)|SpvOpVariable, 140, 141, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 146, 6, 4,\
(4<<SpvWordCountShift)|SpvOpConstant, 83, 162, 2,\
(4<<SpvWordCountShift)|SpvOpConstant, 83, 169, 3,\
(4<<SpvWordCountShift)|SpvOpConstant, 23, 176, 8,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 177, SpvStorageClassPushConstant, 6,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 212, 0,\
(4<<SpvWordCountShift)|SpvOpVariable, 140, 238, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 247, 1065353216,\
(4<<SpvWordCountShift)|SpvOpVariable, 140, 249, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, 140, 259, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpConstant, 83, 269, 16,\
(6<<SpvWordCountShift)|SpvOpConstantComposite, 84, 270, 269, 269, 115,\
(5<<SpvWordCountShift)|SpvOpFunction, 2, 4, SpvFunctionControlMaskNone, 3,\
(2<<SpvWordCountShift)|SpvOpLabel, 5,\
(4<<SpvWordCountShift)|SpvOpVariable, 81, 82, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 81, 104, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 25, 124, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 25, 133, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 138, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 156, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 172, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 25, 174, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 25, 182, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 188, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 192, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 197, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 198, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 200, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 203, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 205, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 208, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 209, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 211, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 219, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 220, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 222, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 225, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 232, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 233, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 235, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpLoad, 84, 88, 86,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 87, 89, 88, 88, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 90, 91, 89,\
(4<<SpvWordCountShift)|SpvOpConvertSToF, 80, 92, 91,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 96, 97, 95, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 83, 98, 97,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, 6, 99, 98,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 101, 99, 100,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 80, 102, 101, 101,\
(5<<SpvWordCountShift)|SpvOpFSub, 80, 103, 92, 102,\
(3<<SpvWordCountShift)|SpvOpStore, 82, 103,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 107, 82, 106,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 108, 107,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 109, 105, 108,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 96, 111, 95, 110,\
(4<<SpvWordCountShift)|SpvOpLoad, 83, 112, 111,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, 6, 113, 112,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 114, 109, 113,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 116, 82, 115,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 117, 116,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 118, 105, 117,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 96, 119, 95, 110,\
(4<<SpvWordCountShift)|SpvOpLoad, 83, 120, 119,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, 6, 121, 120,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 122, 118, 121,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 80, 123, 114, 122,\
(3<<SpvWordCountShift)|SpvOpStore, 104, 123,\
(4<<SpvWordCountShift)|SpvOpLoad, 80, 125, 104,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 126, 1, 66, 125,\
(3<<SpvWordCountShift)|SpvOpStore, 124, 126,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 127, 124,\
(5<<SpvWordCountShift)|SpvOpFOrdLessThan, 129, 130, 127, 128,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, 132, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, 130, 131, 132,\
(2<<SpvWordCountShift)|SpvOpLabel, 131,\
(3<<SpvWordCountShift)|SpvOpStore, 124, 128,\
(2<<SpvWordCountShift)|SpvOpBranch, 132,\
(2<<SpvWordCountShift)|SpvOpLabel, 132,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 135, 124,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 136, 134, 135,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 137, 1, 31, 136,\
(3<<SpvWordCountShift)|SpvOpStore, 133, 137,\
(4<<SpvWordCountShift)|SpvOpLoad, 139, 142, 141,\
(4<<SpvWordCountShift)|SpvOpLoad, 84, 143, 86,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 87, 144, 143, 143, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 90, 145, 144,\
(5<<SpvWordCountShift)|SpvOpImageRead, 146, 147, 142, 145,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 148, 147, 0,\
(4<<SpvWordCountShift)|SpvOpLoad, 139, 149, 141,\
(4<<SpvWordCountShift)|SpvOpLoad, 84, 150, 86,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 87, 151, 150, 150, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 90, 152, 151,\
(5<<SpvWordCountShift)|SpvOpImageRead, 146, 153, 149, 152,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 154, 153, 1,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 155, 148, 154,\
(3<<SpvWordCountShift)|SpvOpStore, 138, 155,\
(4<<SpvWordCountShift)|SpvOpLoad, 139, 157, 141,\
(4<<SpvWordCountShift)|SpvOpLoad, 84, 158, 86,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 87, 159, 158, 158, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 90, 160, 159,\
(5<<SpvWordCountShift)|SpvOpImageRead, 146, 161, 157, 160,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 163, 161, 2,\
(4<<SpvWordCountShift)|SpvOpLoad, 139, 164, 141,\
(4<<SpvWordCountShift)|SpvOpLoad, 84, 165, 86,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 87, 166, 165, 165, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 90, 167, 166,\
(5<<SpvWordCountShift)|SpvOpImageRead, 146, 168, 164, 167,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 6, 170, 168, 3,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 171, 163, 170,\
(3<<SpvWordCountShift)|SpvOpStore, 172, 171,\
(5<<SpvWordCountShift)|SpvOpFunctionCall, 7, 173, 20, 172,\
(3<<SpvWordCountShift)|SpvOpStore, 156, 173,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 175, 133,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 177, 178, 95, 176,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 179, 178,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 180, 175, 179,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 181, 1, 14, 180,\
(3<<SpvWordCountShift)|SpvOpStore, 174, 181,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 183, 133,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 177, 184, 95, 176,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 185, 184,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 186, 183, 185,\
(6<<SpvWordCountShift)|SpvOpExtInst, 6, 187, 1, 13, 186,\
(3<<SpvWordCountShift)|SpvOpStore, 182, 187,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 189, 174,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 190, 182,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 191, 189, 190,\
(3<<SpvWordCountShift)|SpvOpStore, 188, 191,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 193, 174,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 194, 182,\
(4<<SpvWordCountShift)|SpvOpFNegate, 6, 195, 194,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 196, 193, 195,\
(3<<SpvWordCountShift)|SpvOpStore, 192, 196,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 199, 138,\
(3<<SpvWordCountShift)|SpvOpStore, 198, 199,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 201, 188,\
(3<<SpvWordCountShift)|SpvOpStore, 200, 201,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 202, 12, 198, 200,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 204, 156,\
(3<<SpvWordCountShift)|SpvOpStore, 203, 204,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 206, 192,\
(3<<SpvWordCountShift)|SpvOpStore, 205, 206,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 207, 12, 203, 205,\
(3<<SpvWordCountShift)|SpvOpStore, 208, 202,\
(3<<SpvWordCountShift)|SpvOpStore, 209, 207,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 210, 16, 208, 209,\
(3<<SpvWordCountShift)|SpvOpStore, 197, 210,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 213, 104, 106,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 214, 213,\
(4<<SpvWordCountShift)|SpvOpFNegate, 6, 215, 214,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 216, 124,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 217, 215, 216,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 218, 212, 217,\
(3<<SpvWordCountShift)|SpvOpStore, 211, 218,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 221, 211,\
(3<<SpvWordCountShift)|SpvOpStore, 220, 221,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 223, 197,\
(3<<SpvWordCountShift)|SpvOpStore, 222, 223,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 224, 12, 220, 222,\
(3<<SpvWordCountShift)|SpvOpStore, 219, 224,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 226, 104, 115,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 227, 226,\
(4<<SpvWordCountShift)|SpvOpFNegate, 6, 228, 227,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 229, 124,\
(5<<SpvWordCountShift)|SpvOpFDiv, 6, 230, 228, 229,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 231, 212, 230,\
(3<<SpvWordCountShift)|SpvOpStore, 225, 231,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 234, 225,\
(3<<SpvWordCountShift)|SpvOpStore, 233, 234,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 236, 197,\
(3<<SpvWordCountShift)|SpvOpStore, 235, 236,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 237, 12, 233, 235,\
(3<<SpvWordCountShift)|SpvOpStore, 232, 237,\
(4<<SpvWordCountShift)|SpvOpLoad, 139, 239, 238,\
(4<<SpvWordCountShift)|SpvOpLoad, 84, 240, 86,\
\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 87, 241, 240, 240, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 90, 242, 241,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 243, 197, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 244, 243,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 245, 197, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 246, 245,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, 146, 248, 244, 246, 212, 247,\
(4<<SpvWordCountShift)|SpvOpImageWrite, 239, 242, 248,\
(4<<SpvWordCountShift)|SpvOpLoad, 139, 250, 249,\
(4<<SpvWordCountShift)|SpvOpLoad, 84, 251, 86,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 87, 252, 251, 251, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 90, 253, 252,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 254, 219, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 255, 254,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 256, 219, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 257, 256,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, 146, 258, 255, 257, 212, 247,\
(4<<SpvWordCountShift)|SpvOpImageWrite, 250, 253, 258,\
(4<<SpvWordCountShift)|SpvOpLoad, 139, 260, 259,\
(4<<SpvWordCountShift)|SpvOpLoad, 84, 261, 86,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 87, 262, 261, 261, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 90, 263, 262,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 264, 232, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 265, 264,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 266, 232, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 267, 266,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, 146, 268, 265, 267, 212, 247,\
(4<<SpvWordCountShift)|SpvOpImageWrite, 260, 263, 268,\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
(5<<SpvWordCountShift)|SpvOpFunction, 7, 12, SpvFunctionControlMaskNone, 9,\
(3<<SpvWordCountShift)|SpvOpFunctionParameter, 8, 10,\
(3<<SpvWordCountShift)|SpvOpFunctionParameter, 8, 11,\
(2<<SpvWordCountShift)|SpvOpLabel, 13,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 22, SpvStorageClassFunction,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 26, 10, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 27, 26,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 28, 11, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 29, 28,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 30, 27, 29,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 32, 10, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 33, 32,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 34, 11, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 35, 34,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 36, 33, 35,\
(5<<SpvWordCountShift)|SpvOpFSub, 6, 37, 30, 36,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 38, 22, 24,\
(3<<SpvWordCountShift)|SpvOpStore, 38, 37,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 39, 10, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 40, 39,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 41, 11, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 42, 41,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 43, 40, 42,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 44, 10, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 45, 44,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 46, 11, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 47, 46,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 48, 45, 47,\
(5<<SpvWordCountShift)|SpvOpFAdd, 6, 49, 43, 48,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 50, 22, 31,\
(3<<SpvWordCountShift)|SpvOpStore, 50, 49,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 51, 22,\
(2<<SpvWordCountShift)|SpvOpReturnValue, 51,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
(5<<SpvWordCountShift)|SpvOpFunction, 7, 16, SpvFunctionControlMaskNone, 9,\
(3<<SpvWordCountShift)|SpvOpFunctionParameter, 8, 14,\
(3<<SpvWordCountShift)|SpvOpFunctionParameter, 8, 15,\
(2<<SpvWordCountShift)|SpvOpLabel, 17,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 54, SpvStorageClassFunction,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 55, 14, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 56, 55,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 57, 15, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 58, 57,\
(5<<SpvWordCountShift)|SpvOpFAdd, 6, 59, 56, 58,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 60, 54, 24,\
(3<<SpvWordCountShift)|SpvOpStore, 60, 59,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 61, 14, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 62, 61,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 63, 15, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 64, 63,\
(5<<SpvWordCountShift)|SpvOpFAdd, 6, 65, 62, 64,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 66, 54, 31,\
(3<<SpvWordCountShift)|SpvOpStore, 66, 65,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 67, 54,\
(2<<SpvWordCountShift)|SpvOpReturnValue, 67,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
(5<<SpvWordCountShift)|SpvOpFunction, 7, 20, SpvFunctionControlMaskNone, 18,\
(3<<SpvWordCountShift)|SpvOpFunctionParameter, 8, 19,\
(2<<SpvWordCountShift)|SpvOpLabel, 21,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 70, SpvStorageClassFunction,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 71, 19, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 72, 71,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 73, 19, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 74, 73,\
(4<<SpvWordCountShift)|SpvOpFNegate, 6, 75, 74,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 76, 72, 75,\
(3<<SpvWordCountShift)|SpvOpStore, 70, 76,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 77, 70,\
(2<<SpvWordCountShift)|SpvOpReturnValue, 77,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

///////////////////////////////////////////////////////////////////////////////////////////////
//Water Fast Fourier Transform
///////////////////////////////////////////////////////////////////////////////////////////////

typedef enum ComputeShaderTwiddleFactorsVariables {
	TwiddleFactorsVariable_ZEROISNOTUSED,
	TwiddleFactorsVariable_ExtInstGLSL450,
	TwiddleFactorsType_Void,
	TwiddleFactorsType_Function,
	TwiddleFactorsType_bool,

	TwiddleFactorsType_PushConstantsStruct,

	TwiddleFactorsType_ComplexStruct,
	
	TwiddleFactorsType_Float,
	TwiddleFactorsType_floatvec2,
	TwiddleFactorsType_floatvec3,
	TwiddleFactorsType_floatvec4,
	TwiddleFactorsType_uint,
	TwiddleFactorsType_uintvec2,
	TwiddleFactorsType_uintvec3,
	TwiddleFactorsType_int,
	TwiddleFactorsType_intvec2,

	TwiddleFactorsType_Image_Float_2D_0_0_0_2_R32f,

	TwiddleFactorsType_PushConstantPointer_PushConstantsStruct,
	TwiddleFactorsType_FunctionPointer_int,
	TwiddleFactorsType_FunctionPointer_uint,
	TwiddleFactorsType_PushConstantPointer_uint,
	TwiddleFactorsType_FunctionPointer_ComplexStruct,
	TwiddleFactorsType_FunctionPointerFloat,
	TwiddleFactorsType_InputPointer_uintvec3,
	TwiddleFactorsType_InputPointer_uint,
	TwiddleFactorsType_StorageBufferPointer_int,

	TwiddleFactorsType_UniformConstantPointer_Image_Float_2D_0_0_0_2_R32f,

	TwiddleFactorsVariable_EntryPoint,
	TwiddleFactorsLabel_StartOfFunction,


	TwiddleFactorsConstant_uint_16,
	TwiddleFactorsConstantComposite_uintvec3_1_16_1,


	TwiddleFactorsVariable_InputPointer_uintvec3_BuiltInInvocationID,
	TwiddleFactorsVariable_InputPointer_uint_BuiltInInvocationID_0,
	TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_0,
	TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_0,

	TwiddleFactorsVariable_InputPointer_uint_BuiltInInvocationID_1,
	TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_1,
	TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_1,

	TwiddleFactorsVariable_InputPointer_uint_BuiltInInvocationID_2,
	TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_2,
	TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_2,

	TwiddleFactorsConstant_float_0,
	TwiddleFactorsConstant_Float_1065353216,
	TwiddleFactorsConstant_Float_1073741824,
	TwiddleFactorsConstant_Float_1086918619,

	TwiddleFactorsConstant_uint_0,
	TwiddleFactorsConstant_uint_1,
	TwiddleFactorsConstant_uint_2,

	TwiddleFactorsConstant_int_0,
	TwiddleFactorsConstant_int_1,

	TwiddleFactorsType_RuntimeArray_BitReversedIndices,
	TwiddleFactorsType_Struct_BitReversedIndices,

	TwiddleFactorsType_StorageBufferPointer_Struct_BitReversedIndices,
	TwiddleFactorsVariable_StorageBufferPointer_Struct_BitReversedIndices,

	TwiddleFactorsVariable_FunctionPointer_float_k,
	TwiddleFactorsVariable_FunctionPointer_ComplexStruct,
	TwiddleFactorsVariable_FunctionPointer_int_ButterflySpan,
	TwiddleFactorsVariable_FunctionPointer_int_BufferflyWing,
	TwiddleFactorsVariable_PushConstantPointer_PushConstantsStruct,

	TwiddleFactorsVariable_UniformConstantPointer_Image_Float_2D_0_0_0_2_R32f,

	TwiddleFactorsVariable_PushConstantPointer_PushConstantsStruct_0,
	TwiddleFactorsLoadedVariable_uint_WaterResolution,
	TwiddleFactorsLoadedVariable_float_WaterResolution,


	//k
	TwiddleFactorsLoadedVariable_float_k_op5_float,
	TwiddleFactorsLoadedVariable_float_k_op6_float,
	TwiddleFactorsLoadedVariable_float_k_op7_float,
	TwiddleFactorsLoadedVariable_float_k_op8_float,
	TwiddleFactorsLoadedVariable_float_k_op9_float,

	//complex twiddle
	TwiddleFactorsLoadedVariable_complex_twiddle_k_float,
	TwiddleFactorsLoadedVariable_complex_twiddle_op1_float,
	TwiddleFactorsLoadedVariable_complex_twiddle_op2_float,
	TwiddleFactorsLoadedVariable_complex_twiddle_op3_float,
	TwiddleFactorsLoadedVariable_complex_twiddle_op4_float,
	TwiddleFactorsLoadedVariable_complex_twiddle_op5_StructComplex,
	//butterfly
	TwiddleFactorsLoadedVariable_int_ButterflySpan_op0_float,
	TwiddleFactorsLoadedVariable_int_ButterflySpan_op1_int,

	TwiddleFactorsLoadedVariable_int_ButterflyWing_op0_float,
	TwiddleFactorsLoadedVariable_int_ButterflyWing_op1_float,
	TwiddleFactorsLoadedVariable_int_ButterflyWing_op2_float,
	TwiddleFactorsLoadedVariable_int_ButterflyWing_op3_float,
	TwiddleFactorsLoadedVariable_int_ButterflyWing_op4_float,
	TwiddleFactorsLoadedVariable_int_ButterflyWing_op5_bool,

	TwiddleFactorsSelectionMerge_Butterfly,
	TwiddleFactorsLabel_Butterfly_true,
	TwiddleFactorsLabel_Butterfly_false,

	//x.x == 0
	TwiddleFactorsLoadedVariable_stage_uintvec2_invocId,

	TwiddleFactorsLoadedVariable_stage_op0_bool,
	TwiddleFactorsLoadedVariable_stage_ButterflyWing_int,
	TwiddleFactorsLoadedVariable_stage_ButterflySpan_int,
	TwiddleFactorsLoadedVariable_stage_ButterflySpan_float,
	TwiddleFactorsLoadedVariable_Image_Float_2D_0_0_0_2_R32f,

	TwiddleFactorsLoadedVariable_stage_FunctionPointer_ComplexStruct_0,
	TwiddleFactorsLoadedVariable_stage_ComplexStruct_0,
	TwiddleFactorsLoadedVariable_stage_FunctionPointer_ComplexStruct_1,
	TwiddleFactorsLoadedVariable_stage_ComplexStruct_1,

	TwiddleFactorsSelectionMerge_FirstStage,
	TwiddleFactorsLabel_FirstStage_true,
	TwiddleFactorsLabel_FirstStage_false,

	//first stage

	TwiddleFactorsLoadedVariable_stage_op1_bool_0,
	TwiddleFactorsSelectionMerge_stage_0,
	TwiddleFactorLabel_TopWingTrue_0,
	TwiddleFactorLabel_TopWingFalse_0,

	TwiddleFactorsLoadedVariable_op0_StorageBufferPointer_0_0,
	TwiddleFactorsLoadedVariable_op1_floatvec4_0_0,
	TwiddleFactorsLoadedVariable_op2_float_0_0,
	TwiddleFactorsLoadedVariable_op3_int_0_0,
	TwiddleFactorsLoadedVariable_op4_StorageBufferPointer_0_0,

	TwiddleFactorsLoadedVariable_BitReversedIndex0_int_0_0,
	TwiddleFactorsLoadedVariable_BitReversedIndex0_float_0_0,

	TwiddleFactorsLoadedVariable_BitReversedIndex1_int_0_0,
	TwiddleFactorsLoadedVariable_BitReversedIndex1_float_0_0,
	

	TwiddleFactorsLoadedVariable_op0_StorageBufferPointer_0_1,
	TwiddleFactorsLoadedVariable_op1_floatvec4_0_1,
	TwiddleFactorsLoadedVariable_op2_float_0_1,
	TwiddleFactorsLoadedVariable_op3_int_0_1,
	TwiddleFactorsLoadedVariable_op4_StorageBufferPointer_0_1,
	TwiddleFactorsLoadedVariable_op5_int_0_1,
	TwiddleFactorsLoadedVariable_op6_float_0_1,

	TwiddleFactorsLoadedVariable_BitReversedIndex0_int_0_1,
	TwiddleFactorsLoadedVariable_BitReversedIndex0_float_0_1,

	TwiddleFactorsLoadedVariable_BitReversedIndex1_int_0_1,
	TwiddleFactorsLoadedVariable_BitReversedIndex1_float_0_1,


	//not first stage

	TwiddleFactorsLoadedVariable_stage_op1_bool_1,
	TwiddleFactorsSelectionMerge_stage_1,
	TwiddleFactorLabel_TopWingTrue_1,
	TwiddleFactorLabel_TopWingFalse_1,

	TwiddleFactorsLoadedVariable_op0_float_1_0,
	TwiddleFactorsLoadedVariable_op1_floatvec4_1_0,

	TwiddleFactorsLoadedVariable_op0_float_1_1,
	TwiddleFactorsLoadedVariable_op1_floatvec4_1_1,
}ComputeShaderTwiddleFactorsVariables;
#define ComputeShaderTwiddleFactorsSize (744 * sizeof(SPIRV))
#define ComputeShaderTwiddleFactors() {\
SPIRV_Header(130)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel, \
(6<<SpvWordCountShift)|SpvOpExtInstImport, TwiddleFactorsVariable_ExtInstGLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(9<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelGLCompute, TwiddleFactorsVariable_EntryPoint, 'niam', '\0', \
	TwiddleFactorsVariable_InputPointer_uintvec3_BuiltInInvocationID, TwiddleFactorsVariable_StorageBufferPointer_Struct_BitReversedIndices, TwiddleFactorsVariable_PushConstantPointer_PushConstantsStruct, TwiddleFactorsVariable_UniformConstantPointer_Image_Float_2D_0_0_0_2_R32f,\
(6<<SpvWordCountShift)|SpvOpExecutionMode, TwiddleFactorsVariable_EntryPoint, SpvExecutionModeLocalSize, 1, 16, 1,\
/*decorations*/\
(4<<SpvWordCountShift)|SpvOpDecorate, TwiddleFactorsVariable_InputPointer_uintvec3_BuiltInInvocationID, SpvDecorationBuiltIn, SpvBuiltInGlobalInvocationId,\
(4<<SpvWordCountShift)|SpvOpDecorate, TwiddleFactorsConstantComposite_uintvec3_1_16_1, SpvDecorationBuiltIn, SpvBuiltInWorkgroupSize,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, TwiddleFactorsType_PushConstantsStruct, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, TwiddleFactorsType_PushConstantsStruct, 1, SpvDecorationOffset, 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, TwiddleFactorsType_PushConstantsStruct, 2, SpvDecorationOffset, 8,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, TwiddleFactorsType_PushConstantsStruct, 3, SpvDecorationOffset, 12,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, TwiddleFactorsType_PushConstantsStruct, 4, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, TwiddleFactorsType_PushConstantsStruct, 5, SpvDecorationOffset, 20,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, TwiddleFactorsType_PushConstantsStruct, 6, SpvDecorationOffset, 24,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, TwiddleFactorsType_PushConstantsStruct, 7, SpvDecorationOffset, 28,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, TwiddleFactorsType_PushConstantsStruct, 8, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, TwiddleFactorsType_PushConstantsStruct, 9, SpvDecorationOffset, 40,\
(3<<SpvWordCountShift)|SpvOpDecorate, TwiddleFactorsType_PushConstantsStruct, SpvDecorationBlock,\
(4<<SpvWordCountShift)|SpvOpDecorate, TwiddleFactorsVariable_UniformConstantPointer_Image_Float_2D_0_0_0_2_R32f, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, TwiddleFactorsVariable_UniformConstantPointer_Image_Float_2D_0_0_0_2_R32f, SpvDecorationBinding, 0,\
(3<<SpvWordCountShift)|SpvOpDecorate, TwiddleFactorsVariable_UniformConstantPointer_Image_Float_2D_0_0_0_2_R32f, SpvDecorationNonReadable,\
(4<<SpvWordCountShift)|SpvOpDecorate, TwiddleFactorsType_RuntimeArray_BitReversedIndices, SpvDecorationArrayStride, 4,\
(3<<SpvWordCountShift)|SpvOpDecorate, TwiddleFactorsType_Struct_BitReversedIndices, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, TwiddleFactorsType_Struct_BitReversedIndices, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, TwiddleFactorsVariable_StorageBufferPointer_Struct_BitReversedIndices, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, TwiddleFactorsVariable_StorageBufferPointer_Struct_BitReversedIndices, SpvDecorationBinding, 1,\
/*actual code*/\
\
(2<<SpvWordCountShift)|SpvOpTypeVoid, TwiddleFactorsType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, TwiddleFactorsType_Function, TwiddleFactorsType_Void,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, TwiddleFactorsType_Float, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, TwiddleFactorsType_floatvec2, TwiddleFactorsType_Float, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, TwiddleFactorsType_floatvec3, TwiddleFactorsType_Float, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, TwiddleFactorsType_floatvec4, TwiddleFactorsType_Float, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, TwiddleFactorsType_uint, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, TwiddleFactorsType_uintvec2, TwiddleFactorsType_uint, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, TwiddleFactorsType_uintvec3, TwiddleFactorsType_uint, 3,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, TwiddleFactorsType_int, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, TwiddleFactorsType_intvec2, TwiddleFactorsType_int, 2,\
/*random stuff*/\
(2<<SpvWordCountShift)|SpvOpTypeBool, TwiddleFactorsType_bool,\
\
(4<<SpvWordCountShift)|SpvOpTypePointer, TwiddleFactorsType_InputPointer_uintvec3, SpvStorageClassInput, TwiddleFactorsType_uintvec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, TwiddleFactorsType_FunctionPointerFloat, SpvStorageClassFunction, TwiddleFactorsType_Float,\
(12<<SpvWordCountShift)|SpvOpTypeStruct, TwiddleFactorsType_PushConstantsStruct, TwiddleFactorsType_uint, TwiddleFactorsType_uint, TwiddleFactorsType_uint, TwiddleFactorsType_uint, TwiddleFactorsType_uint, TwiddleFactorsType_Float, TwiddleFactorsType_Float, TwiddleFactorsType_Float, TwiddleFactorsType_Float, TwiddleFactorsType_floatvec2,\
(4<<SpvWordCountShift)|SpvOpTypePointer, TwiddleFactorsType_PushConstantPointer_PushConstantsStruct, SpvStorageClassPushConstant, TwiddleFactorsType_PushConstantsStruct,\
(4<<SpvWordCountShift)|SpvOpTypePointer, TwiddleFactorsType_PushConstantPointer_uint, SpvStorageClassPushConstant, TwiddleFactorsType_uint,\
(4<<SpvWordCountShift)|SpvOpTypeStruct, TwiddleFactorsType_ComplexStruct, TwiddleFactorsType_Float, TwiddleFactorsType_Float,\
(4<<SpvWordCountShift)|SpvOpTypePointer, TwiddleFactorsType_FunctionPointer_ComplexStruct, SpvStorageClassFunction, TwiddleFactorsType_ComplexStruct,\
(4<<SpvWordCountShift)|SpvOpTypePointer, TwiddleFactorsType_FunctionPointer_int, SpvStorageClassFunction, TwiddleFactorsType_int,\
(4<<SpvWordCountShift)|SpvOpTypePointer, TwiddleFactorsType_FunctionPointer_uint, SpvStorageClassFunction, TwiddleFactorsType_uint,\
(9<<SpvWordCountShift)|SpvOpTypeImage, TwiddleFactorsType_Image_Float_2D_0_0_0_2_R32f, TwiddleFactorsType_Float, SpvDim2D, 0, 0, 0, 2, SpvImageFormatR32f,\
(4<<SpvWordCountShift)|SpvOpTypePointer, TwiddleFactorsType_UniformConstantPointer_Image_Float_2D_0_0_0_2_R32f, SpvStorageClassUniformConstant, TwiddleFactorsType_Image_Float_2D_0_0_0_2_R32f,\
(4<<SpvWordCountShift)|SpvOpTypePointer, TwiddleFactorsType_InputPointer_uint, SpvStorageClassInput, TwiddleFactorsType_uint,\
/*storagebuffer*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, TwiddleFactorsType_StorageBufferPointer_int, SpvStorageClassStorageBuffer, TwiddleFactorsType_int,\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, TwiddleFactorsType_RuntimeArray_BitReversedIndices, TwiddleFactorsType_int,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, TwiddleFactorsType_Struct_BitReversedIndices, TwiddleFactorsType_RuntimeArray_BitReversedIndices,\
(4<<SpvWordCountShift)|SpvOpTypePointer, TwiddleFactorsType_StorageBufferPointer_Struct_BitReversedIndices, SpvStorageClassStorageBuffer, TwiddleFactorsType_Struct_BitReversedIndices,\
(4<<SpvWordCountShift)|SpvOpVariable, TwiddleFactorsType_StorageBufferPointer_Struct_BitReversedIndices, TwiddleFactorsVariable_StorageBufferPointer_Struct_BitReversedIndices, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpVariable, TwiddleFactorsType_PushConstantPointer_PushConstantsStruct, TwiddleFactorsVariable_PushConstantPointer_PushConstantsStruct, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, TwiddleFactorsType_UniformConstantPointer_Image_Float_2D_0_0_0_2_R32f, TwiddleFactorsVariable_UniformConstantPointer_Image_Float_2D_0_0_0_2_R32f, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, TwiddleFactorsType_InputPointer_uintvec3, TwiddleFactorsVariable_InputPointer_uintvec3_BuiltInInvocationID, SpvStorageClassInput,\
/*constants*/\
(4<<SpvWordCountShift)|SpvOpConstant, TwiddleFactorsType_Float, TwiddleFactorsConstant_float_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, TwiddleFactorsType_Float, TwiddleFactorsConstant_Float_1073741824, 1073741824,\
(4<<SpvWordCountShift)|SpvOpConstant, TwiddleFactorsType_Float, TwiddleFactorsConstant_Float_1065353216, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, TwiddleFactorsType_Float, TwiddleFactorsConstant_Float_1086918619, 1086918619,\
(4<<SpvWordCountShift)|SpvOpConstant, TwiddleFactorsType_uint, TwiddleFactorsConstant_uint_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, TwiddleFactorsType_uint, TwiddleFactorsConstant_uint_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, TwiddleFactorsType_uint, TwiddleFactorsConstant_uint_2, 2,\
(4<<SpvWordCountShift)|SpvOpConstant, TwiddleFactorsType_int, TwiddleFactorsConstant_int_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, TwiddleFactorsType_int, TwiddleFactorsConstant_int_1, 1,\
/*workgroupsize*/\
(4<<SpvWordCountShift)|SpvOpConstant, TwiddleFactorsType_uint, TwiddleFactorsConstant_uint_16, 16,\
(6<<SpvWordCountShift)|SpvOpConstantComposite, TwiddleFactorsType_uintvec3, TwiddleFactorsConstantComposite_uintvec3_1_16_1, TwiddleFactorsConstant_uint_1, TwiddleFactorsConstant_uint_16, TwiddleFactorsConstant_uint_1,\
/*starting function*/\
(5<<SpvWordCountShift)|SpvOpFunction, TwiddleFactorsType_Void, TwiddleFactorsVariable_EntryPoint, SpvFunctionControlMaskNone, TwiddleFactorsType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorsLabel_StartOfFunction,\
/*declaring variables*/\
(4<<SpvWordCountShift)|SpvOpVariable, TwiddleFactorsType_FunctionPointerFloat,			TwiddleFactorsVariable_FunctionPointer_float_k,				SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, TwiddleFactorsType_FunctionPointer_ComplexStruct, TwiddleFactorsVariable_FunctionPointer_ComplexStruct,		SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, TwiddleFactorsType_FunctionPointer_int,			TwiddleFactorsVariable_FunctionPointer_int_ButterflySpan,	SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, TwiddleFactorsType_FunctionPointer_int,			TwiddleFactorsVariable_FunctionPointer_int_BufferflyWing,	SpvStorageClassFunction,\
/*getting invocation ID's*/\
(5<<SpvWordCountShift)|SpvOpAccessChain, TwiddleFactorsType_InputPointer_uint, TwiddleFactorsVariable_InputPointer_uint_BuiltInInvocationID_0, TwiddleFactorsVariable_InputPointer_uintvec3_BuiltInInvocationID, TwiddleFactorsConstant_uint_0,\
(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_uint, TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_0, TwiddleFactorsVariable_InputPointer_uint_BuiltInInvocationID_0,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_0, TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_0,\
(5<<SpvWordCountShift)|SpvOpAccessChain, TwiddleFactorsType_InputPointer_uint, TwiddleFactorsVariable_InputPointer_uint_BuiltInInvocationID_1, TwiddleFactorsVariable_InputPointer_uintvec3_BuiltInInvocationID, TwiddleFactorsConstant_uint_1,\
(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_uint, TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_1, TwiddleFactorsVariable_InputPointer_uint_BuiltInInvocationID_1,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_1, TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_1,\
(5<<SpvWordCountShift)|SpvOpAccessChain, TwiddleFactorsType_InputPointer_uint, TwiddleFactorsVariable_InputPointer_uint_BuiltInInvocationID_2, TwiddleFactorsVariable_InputPointer_uintvec3_BuiltInInvocationID, TwiddleFactorsConstant_uint_2,\
(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_uint, TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_2, TwiddleFactorsVariable_InputPointer_uint_BuiltInInvocationID_2,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_2, TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_2,\
/*getting struct data*/\
(5<<SpvWordCountShift)|SpvOpAccessChain, TwiddleFactorsType_PushConstantPointer_uint, TwiddleFactorsVariable_PushConstantPointer_PushConstantsStruct_0, TwiddleFactorsVariable_PushConstantPointer_PushConstantsStruct, TwiddleFactorsConstant_int_0,\
(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_uint, TwiddleFactorsLoadedVariable_uint_WaterResolution, TwiddleFactorsVariable_PushConstantPointer_PushConstantsStruct_0,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_float_WaterResolution, TwiddleFactorsLoadedVariable_uint_WaterResolution,\
/*float k = mod(x.y * (float(PushConstants.WaterResolution)/ pow(2,x.x+1)), PushConstants.WaterResolution);*/\
/*x.x + 1.0f*/\
(5<<SpvWordCountShift)|SpvOpFAdd, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_float_k_op5_float, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_0, TwiddleFactorsConstant_Float_1065353216,\
/*pow(2, x)*/\
(7<<SpvWordCountShift)|SpvOpExtInst, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_float_k_op6_float, TwiddleFactorsVariable_ExtInstGLSL450, 26, TwiddleFactorsConstant_Float_1073741824, TwiddleFactorsLoadedVariable_float_k_op5_float,\
/*waterres / x*/\
(5<<SpvWordCountShift)|SpvOpFDiv, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_float_k_op7_float, TwiddleFactorsLoadedVariable_float_WaterResolution, TwiddleFactorsLoadedVariable_float_k_op6_float,\
/*x.y * x*/\
(5<<SpvWordCountShift)|SpvOpFMul, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_float_k_op8_float, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_1, TwiddleFactorsLoadedVariable_float_k_op7_float,\
/*fmod(x)*/\
(5<<SpvWordCountShift)|SpvOpFMod, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_float_k_op9_float, TwiddleFactorsLoadedVariable_float_k_op8_float, TwiddleFactorsLoadedVariable_float_WaterResolution,\
/*storing product*/\
(3<<SpvWordCountShift)|SpvOpStore, TwiddleFactorsVariable_FunctionPointer_float_k, TwiddleFactorsLoadedVariable_float_k_op9_float,\
/*complex twiddle = complex(cos(2.0*M_PI*k/float(PushConstants.WaterResolution)), sin(2.0*M_PI*k/float(PushConstants.WaterResolution)));*/\
(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_complex_twiddle_k_float, TwiddleFactorsVariable_FunctionPointer_float_k,\
(5<<SpvWordCountShift)|SpvOpFMul, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_complex_twiddle_op1_float, TwiddleFactorsConstant_Float_1086918619, TwiddleFactorsLoadedVariable_complex_twiddle_k_float,\
(5<<SpvWordCountShift)|SpvOpFDiv, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_complex_twiddle_op2_float, TwiddleFactorsLoadedVariable_complex_twiddle_op1_float, TwiddleFactorsLoadedVariable_float_WaterResolution,\
/*twiddle complex 0*/\
(6<<SpvWordCountShift)|SpvOpExtInst, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_complex_twiddle_op3_float, TwiddleFactorsVariable_ExtInstGLSL450, 14, TwiddleFactorsLoadedVariable_complex_twiddle_op2_float,\
/*twiddle complex 1*/\
(6<<SpvWordCountShift)|SpvOpExtInst, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_complex_twiddle_op4_float, TwiddleFactorsVariable_ExtInstGLSL450, 13, TwiddleFactorsLoadedVariable_complex_twiddle_op2_float,\
/*storing complex*/\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, TwiddleFactorsType_ComplexStruct, TwiddleFactorsLoadedVariable_complex_twiddle_op5_StructComplex, TwiddleFactorsLoadedVariable_complex_twiddle_op3_float, TwiddleFactorsLoadedVariable_complex_twiddle_op4_float,\
(3<<SpvWordCountShift)|SpvOpStore, TwiddleFactorsVariable_FunctionPointer_ComplexStruct, TwiddleFactorsLoadedVariable_complex_twiddle_op5_StructComplex,\
/*int butterflyspan = int(pow(2, x.x));*/\
(7<<SpvWordCountShift)|SpvOpExtInst, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_int_ButterflySpan_op0_float, TwiddleFactorsVariable_ExtInstGLSL450, 26, TwiddleFactorsConstant_Float_1073741824, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_0,\
(4<<SpvWordCountShift)|SpvOpConvertFToS, TwiddleFactorsType_int, TwiddleFactorsLoadedVariable_int_ButterflySpan_op1_int, TwiddleFactorsLoadedVariable_int_ButterflySpan_op0_float,\
(3<<SpvWordCountShift)|SpvOpStore, TwiddleFactorsVariable_FunctionPointer_int_ButterflySpan, TwiddleFactorsLoadedVariable_int_ButterflySpan_op1_int,\
/*x.x + 1.0f*/\
(5<<SpvWordCountShift)|SpvOpFAdd, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_int_ButterflyWing_op0_float, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_0, TwiddleFactorsConstant_Float_1065353216,\
/*pow(2, x)*/\
(7<<SpvWordCountShift)|SpvOpExtInst, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_int_ButterflyWing_op1_float, TwiddleFactorsVariable_ExtInstGLSL450, 26, TwiddleFactorsConstant_Float_1073741824, TwiddleFactorsLoadedVariable_int_ButterflyWing_op0_float,\
/*mod(x.y, x)*/\
(5<<SpvWordCountShift)|SpvOpFMod, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_int_ButterflyWing_op2_float, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_1, TwiddleFactorsLoadedVariable_int_ButterflyWing_op1_float,\
/*pow(2, x.x)*/\
(7<<SpvWordCountShift)|SpvOpExtInst, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_int_ButterflyWing_op3_float, TwiddleFactorsVariable_ExtInstGLSL450, 26, TwiddleFactorsConstant_Float_1073741824, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_0,\
/*if statement*/\
(5<<SpvWordCountShift)|SpvOpFOrdLessThan, TwiddleFactorsType_bool, TwiddleFactorsLoadedVariable_int_ButterflyWing_op5_bool, TwiddleFactorsLoadedVariable_int_ButterflyWing_op2_float, TwiddleFactorsLoadedVariable_int_ButterflyWing_op3_float,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, TwiddleFactorsSelectionMerge_Butterfly, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, TwiddleFactorsLoadedVariable_int_ButterflyWing_op5_bool, TwiddleFactorsLabel_Butterfly_true, TwiddleFactorsLabel_Butterfly_false,\
/*true*/\
	(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorsLabel_Butterfly_true,\
	(3<<SpvWordCountShift)|SpvOpStore, TwiddleFactorsVariable_FunctionPointer_int_BufferflyWing, TwiddleFactorsConstant_int_1,\
	(2<<SpvWordCountShift)|SpvOpBranch, TwiddleFactorsSelectionMerge_Butterfly,\
/*false*/\
	(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorsLabel_Butterfly_false,\
	(3<<SpvWordCountShift)|SpvOpStore, TwiddleFactorsVariable_FunctionPointer_int_BufferflyWing, TwiddleFactorsConstant_int_0,\
	(2<<SpvWordCountShift)|SpvOpBranch, TwiddleFactorsSelectionMerge_Butterfly,\
/*end if*/\
(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorsSelectionMerge_Butterfly,\
/*if x.x == 0*/\
(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_int, TwiddleFactorsLoadedVariable_stage_ButterflyWing_int, TwiddleFactorsVariable_FunctionPointer_int_BufferflyWing,\
(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_int, TwiddleFactorsLoadedVariable_stage_ButterflySpan_int, TwiddleFactorsVariable_FunctionPointer_int_ButterflySpan,\
(4<<SpvWordCountShift)|SpvOpConvertSToF, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_stage_ButterflySpan_float, TwiddleFactorsLoadedVariable_stage_ButterflySpan_int,\
(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_Image_Float_2D_0_0_0_2_R32f, TwiddleFactorsLoadedVariable_Image_Float_2D_0_0_0_2_R32f, TwiddleFactorsVariable_UniformConstantPointer_Image_Float_2D_0_0_0_2_R32f,\
(5<<SpvWordCountShift)|SpvOpAccessChain, TwiddleFactorsType_FunctionPointerFloat, TwiddleFactorsLoadedVariable_stage_FunctionPointer_ComplexStruct_0, TwiddleFactorsVariable_FunctionPointer_ComplexStruct, TwiddleFactorsConstant_int_0,\
(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_stage_ComplexStruct_0, TwiddleFactorsLoadedVariable_stage_FunctionPointer_ComplexStruct_0,\
(5<<SpvWordCountShift)|SpvOpAccessChain, TwiddleFactorsType_FunctionPointerFloat, TwiddleFactorsLoadedVariable_stage_FunctionPointer_ComplexStruct_1, TwiddleFactorsVariable_FunctionPointer_ComplexStruct, TwiddleFactorsConstant_int_1,\
(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_stage_ComplexStruct_1, TwiddleFactorsLoadedVariable_stage_FunctionPointer_ComplexStruct_1,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, TwiddleFactorsType_uintvec2, TwiddleFactorsLoadedVariable_stage_uintvec2_invocId, TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_0, TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_1,\
/*if statement*/\
(5<<SpvWordCountShift)|SpvOpFOrdEqual, TwiddleFactorsType_bool, TwiddleFactorsLoadedVariable_stage_op0_bool, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_0, TwiddleFactorsConstant_float_0,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, TwiddleFactorsSelectionMerge_FirstStage, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, TwiddleFactorsLoadedVariable_stage_op0_bool, TwiddleFactorsLabel_FirstStage_true, TwiddleFactorsLabel_FirstStage_false,\
/*true*/\
	(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorsLabel_FirstStage_true,\
	/*if statement*/\
	(5<<SpvWordCountShift)|SpvOpIEqual, TwiddleFactorsType_bool, TwiddleFactorsLoadedVariable_stage_op1_bool_0, TwiddleFactorsLoadedVariable_stage_ButterflyWing_int, TwiddleFactorsConstant_int_1,\
	(3<<SpvWordCountShift)|SpvOpSelectionMerge, TwiddleFactorsSelectionMerge_stage_0, SpvSelectionControlMaskNone,\
	(4<<SpvWordCountShift)|SpvOpBranchConditional, TwiddleFactorsLoadedVariable_stage_op1_bool_0, TwiddleFactorLabel_TopWingTrue_0, TwiddleFactorLabel_TopWingFalse_0,\
	/*true*/\
		(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorLabel_TopWingTrue_0,\
		(6<<SpvWordCountShift)|SpvOpAccessChain, TwiddleFactorsType_StorageBufferPointer_int, TwiddleFactorsLoadedVariable_op0_StorageBufferPointer_0_0,\
	TwiddleFactorsVariable_StorageBufferPointer_Struct_BitReversedIndices, TwiddleFactorsConstant_int_0, TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_1,\
		(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_int, TwiddleFactorsLoadedVariable_BitReversedIndex0_int_0_0, TwiddleFactorsLoadedVariable_op0_StorageBufferPointer_0_0,\
		(4<<SpvWordCountShift)|SpvOpConvertSToF, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_BitReversedIndex0_float_0_0, TwiddleFactorsLoadedVariable_BitReversedIndex0_int_0_0,\
		(5<<SpvWordCountShift)|SpvOpFAdd, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_op2_float_0_0, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_1, TwiddleFactorsConstant_Float_1065353216,\
		(4<<SpvWordCountShift)|SpvOpConvertFToS, TwiddleFactorsType_int, TwiddleFactorsLoadedVariable_op3_int_0_0, TwiddleFactorsLoadedVariable_op2_float_0_0,\
		(6<<SpvWordCountShift)|SpvOpAccessChain, TwiddleFactorsType_StorageBufferPointer_int, TwiddleFactorsLoadedVariable_op4_StorageBufferPointer_0_0,\
	TwiddleFactorsVariable_StorageBufferPointer_Struct_BitReversedIndices, TwiddleFactorsConstant_int_0, TwiddleFactorsLoadedVariable_op3_int_0_0,\
		(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_int, TwiddleFactorsLoadedVariable_BitReversedIndex1_int_0_0, TwiddleFactorsLoadedVariable_op4_StorageBufferPointer_0_0,\
		(4<<SpvWordCountShift)|SpvOpConvertSToF, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_BitReversedIndex1_float_0_0, TwiddleFactorsLoadedVariable_BitReversedIndex1_int_0_0,\
		(7<<SpvWordCountShift)|SpvOpCompositeConstruct, TwiddleFactorsType_floatvec4, TwiddleFactorsLoadedVariable_op1_floatvec4_0_0, TwiddleFactorsLoadedVariable_stage_ComplexStruct_0,\
			TwiddleFactorsLoadedVariable_stage_ComplexStruct_1, TwiddleFactorsLoadedVariable_BitReversedIndex0_float_0_0, TwiddleFactorsLoadedVariable_BitReversedIndex1_float_0_0,\
		(4<<SpvWordCountShift)|SpvOpImageWrite, TwiddleFactorsLoadedVariable_Image_Float_2D_0_0_0_2_R32f, TwiddleFactorsLoadedVariable_stage_uintvec2_invocId, TwiddleFactorsLoadedVariable_op1_floatvec4_0_0,\
		(2<<SpvWordCountShift)|SpvOpBranch, TwiddleFactorsSelectionMerge_stage_0,\
	/*false*/\
		(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorLabel_TopWingFalse_0,\
		(5<<SpvWordCountShift)|SpvOpFSub, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_op2_float_0_1, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_1, TwiddleFactorsConstant_Float_1065353216,\
		(4<<SpvWordCountShift)|SpvOpConvertFToS, TwiddleFactorsType_int, TwiddleFactorsLoadedVariable_op3_int_0_1, TwiddleFactorsLoadedVariable_op2_float_0_1,\
		(6<<SpvWordCountShift)|SpvOpAccessChain, TwiddleFactorsType_StorageBufferPointer_int, TwiddleFactorsLoadedVariable_op0_StorageBufferPointer_0_1,\
	TwiddleFactorsVariable_StorageBufferPointer_Struct_BitReversedIndices, TwiddleFactorsConstant_int_0, TwiddleFactorsLoadedVariable_op3_int_0_1,\
		(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_int, TwiddleFactorsLoadedVariable_BitReversedIndex0_int_0_1, TwiddleFactorsLoadedVariable_op0_StorageBufferPointer_0_1,\
		(4<<SpvWordCountShift)|SpvOpConvertSToF, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_BitReversedIndex0_float_0_1, TwiddleFactorsLoadedVariable_BitReversedIndex0_int_0_1,\
		(6<<SpvWordCountShift)|SpvOpAccessChain, TwiddleFactorsType_StorageBufferPointer_int, TwiddleFactorsLoadedVariable_op4_StorageBufferPointer_0_1,\
	TwiddleFactorsVariable_StorageBufferPointer_Struct_BitReversedIndices, TwiddleFactorsConstant_int_0, TwiddleFactorsLoadedVariable_uint_BuiltInInvocationID_1,\
		(4<<SpvWordCountShift)|SpvOpLoad, TwiddleFactorsType_int, TwiddleFactorsLoadedVariable_BitReversedIndex1_int_0_1, TwiddleFactorsLoadedVariable_op4_StorageBufferPointer_0_1,\
		(4<<SpvWordCountShift)|SpvOpConvertSToF, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_BitReversedIndex1_float_0_1, TwiddleFactorsLoadedVariable_BitReversedIndex1_int_0_1,\
		(7<<SpvWordCountShift)|SpvOpCompositeConstruct, TwiddleFactorsType_floatvec4, TwiddleFactorsLoadedVariable_op1_floatvec4_0_1, TwiddleFactorsLoadedVariable_stage_ComplexStruct_0,\
			TwiddleFactorsLoadedVariable_stage_ComplexStruct_1, TwiddleFactorsLoadedVariable_BitReversedIndex0_float_0_1, TwiddleFactorsLoadedVariable_BitReversedIndex1_float_0_1,\
		(4<<SpvWordCountShift)|SpvOpImageWrite, TwiddleFactorsLoadedVariable_Image_Float_2D_0_0_0_2_R32f, TwiddleFactorsLoadedVariable_stage_uintvec2_invocId, TwiddleFactorsLoadedVariable_op1_floatvec4_0_1,\
		(2<<SpvWordCountShift)|SpvOpBranch, TwiddleFactorsSelectionMerge_stage_0,\
		(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorsSelectionMerge_stage_0,\
	(2<<SpvWordCountShift)|SpvOpBranch, TwiddleFactorsSelectionMerge_FirstStage,\
/*false*/\
	(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorsLabel_FirstStage_false,\
	/*if statement*/\
	(5<<SpvWordCountShift)|SpvOpIEqual, TwiddleFactorsType_bool, TwiddleFactorsLoadedVariable_stage_op1_bool_1, TwiddleFactorsLoadedVariable_stage_ButterflyWing_int, TwiddleFactorsConstant_int_1,\
	(3<<SpvWordCountShift)|SpvOpSelectionMerge, TwiddleFactorsSelectionMerge_stage_1, SpvSelectionControlMaskNone,\
	(4<<SpvWordCountShift)|SpvOpBranchConditional, TwiddleFactorsLoadedVariable_stage_op1_bool_1, TwiddleFactorLabel_TopWingTrue_1, TwiddleFactorLabel_TopWingFalse_1,\
	/*true*/\
		(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorLabel_TopWingTrue_1,\
		(5<<SpvWordCountShift)|SpvOpFAdd, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_op0_float_1_0, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_1, TwiddleFactorsLoadedVariable_stage_ButterflySpan_float,\
		(7<<SpvWordCountShift)|SpvOpCompositeConstruct, TwiddleFactorsType_floatvec4, TwiddleFactorsLoadedVariable_op1_floatvec4_1_0, TwiddleFactorsLoadedVariable_stage_ComplexStruct_0,\
			TwiddleFactorsLoadedVariable_stage_ComplexStruct_1, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_1, TwiddleFactorsLoadedVariable_op0_float_1_0,\
		(4<<SpvWordCountShift)|SpvOpImageWrite, TwiddleFactorsLoadedVariable_Image_Float_2D_0_0_0_2_R32f, TwiddleFactorsLoadedVariable_stage_uintvec2_invocId, TwiddleFactorsLoadedVariable_op1_floatvec4_1_0,\
		(2<<SpvWordCountShift)|SpvOpBranch, TwiddleFactorsSelectionMerge_stage_1,\
	/*false*/\
		(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorLabel_TopWingFalse_1,\
		(5<<SpvWordCountShift)|SpvOpFSub, TwiddleFactorsType_Float, TwiddleFactorsLoadedVariable_op0_float_1_1, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_1, TwiddleFactorsLoadedVariable_stage_ButterflySpan_float,\
		(7<<SpvWordCountShift)|SpvOpCompositeConstruct, TwiddleFactorsType_floatvec4, TwiddleFactorsLoadedVariable_op1_floatvec4_1_1, TwiddleFactorsLoadedVariable_stage_ComplexStruct_0,\
			TwiddleFactorsLoadedVariable_stage_ComplexStruct_1, TwiddleFactorsLoadedVariable_op0_float_1_1, TwiddleFactorsLoadedVariable_float_BuiltInInvocationID_1,\
		(4<<SpvWordCountShift)|SpvOpImageWrite, TwiddleFactorsLoadedVariable_Image_Float_2D_0_0_0_2_R32f, TwiddleFactorsLoadedVariable_stage_uintvec2_invocId, TwiddleFactorsLoadedVariable_op1_floatvec4_1_1,\
		(2<<SpvWordCountShift)|SpvOpBranch, TwiddleFactorsSelectionMerge_stage_1,\
		(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorsSelectionMerge_stage_1,\
	(2<<SpvWordCountShift)|SpvOpBranch, TwiddleFactorsSelectionMerge_FirstStage,\
(2<<SpvWordCountShift)|SpvOpLabel, TwiddleFactorsSelectionMerge_FirstStage,\
/*endif*/\
/*end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

typedef enum ComputeShaderButterflyVariables {
}ComputeShaderButterflyVariables;
#define ComputeShaderButterflySize (2209 * sizeof(SPIRV))
#define ComputeShaderButterfly() {\
SPIRV_Header(423)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, 1, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(10<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelGLCompute, 4, 'niam', '\0', 76, 84, 98, 111, 168,\
(6<<SpvWordCountShift)|SpvOpExecutionMode, 4, SpvExecutionModeLocalSize, 16, 16, 1,\
\
(4<<SpvWordCountShift)|SpvOpDecorate, 76, SpvDecorationBuiltIn, SpvBuiltInGlobalInvocationId,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 82, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 82, 1, SpvDecorationOffset, 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 82, 2, SpvDecorationOffset, 8,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 82, 3, SpvDecorationOffset, 12,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 82, 4, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 82, 5, SpvDecorationOffset, 20,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 82, 6, SpvDecorationOffset, 24,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 82, 7, SpvDecorationOffset, 28,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 82, 8, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 82, 9, SpvDecorationOffset, 40,\
(3<<SpvWordCountShift)|SpvOpDecorate, 82, SpvDecorationBlock,\
(4<<SpvWordCountShift)|SpvOpDecorate, 98, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 98, SpvDecorationBinding, 0,\
(3<<SpvWordCountShift)|SpvOpDecorate, 98, SpvDecorationNonWritable,\
(4<<SpvWordCountShift)|SpvOpDecorate, 111, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 111, SpvDecorationBinding, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, 168, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 168, SpvDecorationBinding, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, 422, SpvDecorationBuiltIn, SpvBuiltInWorkgroupSize,\
\
(2<<SpvWordCountShift)|SpvOpTypeVoid, 2,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, 3, 2,\
(3<<SpvWordCountShift)|SpvOpTypeFloat, 6, 32,\
(4<<SpvWordCountShift)|SpvOpTypeStruct, 7, 6, 6,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 8, SpvStorageClassFunction, 7,\
(5<<SpvWordCountShift)|SpvOpTypeFunction, 9, 7, 8, 8,\
(4<<SpvWordCountShift)|SpvOpTypeInt, 23, 32, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, 23, 24, 0,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 25, SpvStorageClassFunction, 6,\
(4<<SpvWordCountShift)|SpvOpConstant, 23, 31, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 70, 23, 2,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 71, SpvStorageClassFunction, 70,\
(4<<SpvWordCountShift)|SpvOpTypeInt, 73, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 74, 73, 3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 75, SpvStorageClassInput, 74,\
(4<<SpvWordCountShift)|SpvOpVariable, 75, 76, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 77, 73, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 81, 6, 2,\
(12<<SpvWordCountShift)|SpvOpTypeStruct, 82, 73, 73, 73, 73, 73, 6, 6, 6, 6, 81,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 83, SpvStorageClassPushConstant, 82,\
(4<<SpvWordCountShift)|SpvOpVariable, 83, 84, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 85, SpvStorageClassPushConstant, 73,\
(4<<SpvWordCountShift)|SpvOpConstant, 73, 88, 0,\
(2<<SpvWordCountShift)|SpvOpTypeBool, 89,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 93, 6, 4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 94, SpvStorageClassFunction, 93,\
(9<<SpvWordCountShift)|SpvOpTypeImage, 96, 6, SpvDim2D, 0, 0, 0, 2, SpvImageFormatR32f,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 97, SpvStorageClassUniformConstant, 96,\
(4<<SpvWordCountShift)|SpvOpVariable, 97, 98, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpConstant, 23, 100, 2,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 104, SpvStorageClassFunction, 23,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 109, SpvStorageClassFunction, 81,\
(4<<SpvWordCountShift)|SpvOpVariable, 97, 111, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpConstant, 73, 113, 2,\
(4<<SpvWordCountShift)|SpvOpConstant, 73, 117, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, 73, 125, 3,\
(4<<SpvWordCountShift)|SpvOpVariable, 97, 168, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 175, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 176, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, 23, 407, 3,\
(4<<SpvWordCountShift)|SpvOpConstant, 73, 421, 16,\
(6<<SpvWordCountShift)|SpvOpConstantComposite, 74, 422, 421, 421, 117,\
(5<<SpvWordCountShift)|SpvOpFunction, 2, 4, SpvFunctionControlMaskNone, 3,\
(2<<SpvWordCountShift)|SpvOpLabel, 5,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 85, 408, 84, 407,\
(4<<SpvWordCountShift)|SpvOpLoad, 73, 409, 408,\
(5<<SpvWordCountShift)|SpvOpIEqual, 89, 410, 409, 88,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, 412, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, 410, 411, 414,\
(2<<SpvWordCountShift)|SpvOpLabel, 411,\
(4<<SpvWordCountShift)|SpvOpFunctionCall, 2, 413, 18,\
(2<<SpvWordCountShift)|SpvOpBranch, 412,\
(2<<SpvWordCountShift)|SpvOpLabel, 414,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 85, 415, 84, 407,\
(4<<SpvWordCountShift)|SpvOpLoad, 73, 416, 415,\
(5<<SpvWordCountShift)|SpvOpIEqual, 89, 417, 416, 117,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, 419, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, 417, 418, 419,\
(2<<SpvWordCountShift)|SpvOpLabel, 418,\
(4<<SpvWordCountShift)|SpvOpFunctionCall, 2, 420, 20,\
(2<<SpvWordCountShift)|SpvOpBranch, 419,\
(2<<SpvWordCountShift)|SpvOpLabel, 419,\
(2<<SpvWordCountShift)|SpvOpBranch, 412,\
(2<<SpvWordCountShift)|SpvOpLabel, 412,\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
(5<<SpvWordCountShift)|SpvOpFunction, 7, 12, SpvFunctionControlMaskNone, 9,\
(3<<SpvWordCountShift)|SpvOpFunctionParameter, 8, 10,\
(3<<SpvWordCountShift)|SpvOpFunctionParameter, 8, 11,\
(2<<SpvWordCountShift)|SpvOpLabel, 13,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 22, SpvStorageClassFunction,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 26, 10, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 27, 26,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 28, 11, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 29, 28,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 30, 27, 29,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 32, 10, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 33, 32,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 34, 11, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 35, 34,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 36, 33, 35,\
(5<<SpvWordCountShift)|SpvOpFSub, 6, 37, 30, 36,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 38, 22, 24,\
(3<<SpvWordCountShift)|SpvOpStore, 38, 37,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 39, 10, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 40, 39,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 41, 11, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 42, 41,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 43, 40, 42,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 44, 10, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 45, 44,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 46, 11, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 47, 46,\
(5<<SpvWordCountShift)|SpvOpFMul, 6, 48, 45, 47,\
(5<<SpvWordCountShift)|SpvOpFAdd, 6, 49, 43, 48,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 50, 22, 31,\
(3<<SpvWordCountShift)|SpvOpStore, 50, 49,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 51, 22,\
(2<<SpvWordCountShift)|SpvOpReturnValue, 51,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
(5<<SpvWordCountShift)|SpvOpFunction, 7, 16, SpvFunctionControlMaskNone, 9,\
(3<<SpvWordCountShift)|SpvOpFunctionParameter, 8, 14,\
(3<<SpvWordCountShift)|SpvOpFunctionParameter, 8, 15,\
(2<<SpvWordCountShift)|SpvOpLabel, 17,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 54, SpvStorageClassFunction,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 55, 14, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 56, 55,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 57, 15, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 58, 57,\
(5<<SpvWordCountShift)|SpvOpFAdd, 6, 59, 56, 58,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 60, 54, 24,\
(3<<SpvWordCountShift)|SpvOpStore, 60, 59,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 61, 14, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 62, 61,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 63, 15, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 64, 63,\
(5<<SpvWordCountShift)|SpvOpFAdd, 6, 65, 62, 64,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 66, 54, 31,\
(3<<SpvWordCountShift)|SpvOpStore, 66, 65,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 67, 54,\
(2<<SpvWordCountShift)|SpvOpReturnValue, 67,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
\
\
\
\
(5<<SpvWordCountShift)|SpvOpFunction, 2, 18, SpvFunctionControlMaskNone, 3,\
(2<<SpvWordCountShift)|SpvOpLabel, 19,\
(4<<SpvWordCountShift)|SpvOpVariable, 71, 72, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 94, 95, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 110, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 123, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 134, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 140, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 146, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 152, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 158, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 159, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 161, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 164, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 166, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 94, 184, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 193, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 203, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 213, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 219, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 225, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 231, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 237, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 239, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 242, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 244, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpLoad, 74, 78, 76,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 77, 79, 78, 78, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 70, 80, 79,\
(3<<SpvWordCountShift)|SpvOpStore, 72, 80,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 85, 86, 84, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 73, 87, 86,\
(5<<SpvWordCountShift)|SpvOpIEqual, 89, 90, 87, 88,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, 92, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, 90, 91, 178,\
\
(2<<SpvWordCountShift)|SpvOpLabel, 91,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 99, 98,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 85, 101, 84, 100,\
(4<<SpvWordCountShift)|SpvOpLoad, 73, 102, 101,\
(4<<SpvWordCountShift)|SpvOpBitcast, 23, 103, 102,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 105, 72, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 106, 105,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 107, 103, 106,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 108, 99, 107,\
(3<<SpvWordCountShift)|SpvOpStore, 95, 108,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 112, 111,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 114, 95, 113,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 115, 114,\
(4<<SpvWordCountShift)|SpvOpConvertFToS, 23, 116, 115,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 118, 72, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 119, 118,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 120, 116, 119,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 121, 112, 120,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 81, 122, 121, 121, 0, 1,\
(3<<SpvWordCountShift)|SpvOpStore, 110, 122,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 124, 111,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 126, 95, 125,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 127, 126,\
(4<<SpvWordCountShift)|SpvOpConvertFToS, 23, 128, 127,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 129, 72, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 130, 129,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 131, 128, 130,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 132, 124, 131,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 81, 133, 132, 132, 0, 1,\
(3<<SpvWordCountShift)|SpvOpStore, 123, 133,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 135, 95, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 136, 135,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 137, 95, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 138, 137,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 81, 139, 136, 138,\
(3<<SpvWordCountShift)|SpvOpStore, 134, 139,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 141, 110, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 142, 141,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 143, 110, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 144, 143,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 145, 142, 144,\
(3<<SpvWordCountShift)|SpvOpStore, 140, 145,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 147, 123, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 148, 147,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 149, 123, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 150, 149,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 151, 148, 150,\
(3<<SpvWordCountShift)|SpvOpStore, 146, 151,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 153, 134, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 154, 153,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 155, 134, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 156, 155,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 157, 154, 156,\
(3<<SpvWordCountShift)|SpvOpStore, 152, 157,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 160, 152,\
(3<<SpvWordCountShift)|SpvOpStore, 159, 160,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 162, 146,\
(3<<SpvWordCountShift)|SpvOpStore, 161, 162,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 163, 12, 159, 161,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 165, 140,\
(3<<SpvWordCountShift)|SpvOpStore, 164, 165,\
(3<<SpvWordCountShift)|SpvOpStore, 166, 163,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 167, 16, 164, 166,\
(3<<SpvWordCountShift)|SpvOpStore, 158, 167,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 169, 168,\
(4<<SpvWordCountShift)|SpvOpLoad, 70, 170, 72,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 171, 158, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 172, 171,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 173, 158, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 174, 173,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, 93, 177, 172, 174, 175, 176,\
(4<<SpvWordCountShift)|SpvOpImageWrite, 169, 170, 177,\
(2<<SpvWordCountShift)|SpvOpBranch, 92,\
(2<<SpvWordCountShift)|SpvOpLabel, 178,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 85, 179, 84, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 73, 180, 179,\
(5<<SpvWordCountShift)|SpvOpIEqual, 89, 181, 180, 117,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, 183, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, 181, 182, 183,\
\
(2<<SpvWordCountShift)|SpvOpLabel, 182,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 185, 98,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 85, 186, 84, 100,\
(4<<SpvWordCountShift)|SpvOpLoad, 73, 187, 186,\
(4<<SpvWordCountShift)|SpvOpBitcast, 23, 188, 187,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 189, 72, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 190, 189,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 191, 188, 190,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 192, 185, 191,\
(3<<SpvWordCountShift)|SpvOpStore, 184, 192,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 194, 168,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 195, 184, 113,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 196, 195,\
(4<<SpvWordCountShift)|SpvOpConvertFToS, 23, 197, 196,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 198, 72, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 199, 198,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 200, 197, 199,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 201, 194, 200,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 81, 202, 201, 201, 0, 1,\
(3<<SpvWordCountShift)|SpvOpStore, 193, 202,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 204, 168,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 205, 184, 125,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 206, 205,\
(4<<SpvWordCountShift)|SpvOpConvertFToS, 23, 207, 206,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 208, 72, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 209, 208,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 210, 207, 209,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 211, 204, 210,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 81, 212, 211, 211, 0, 1,\
(3<<SpvWordCountShift)|SpvOpStore, 203, 212,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 214, 184, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 215, 214,\
\
\
\
\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 216, 184, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 217, 216,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 81, 218, 215, 217,\
(3<<SpvWordCountShift)|SpvOpStore, 213, 218,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 220, 193, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 221, 220,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 222, 193, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 223, 222,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 224, 221, 223,\
(3<<SpvWordCountShift)|SpvOpStore, 219, 224,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 226, 203, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 227, 226,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 228, 203, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 229, 228,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 230, 227, 229,\
(3<<SpvWordCountShift)|SpvOpStore, 225, 230,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 232, 213, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 233, 232,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 234, 213, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 235, 234,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 236, 233, 235,\
(3<<SpvWordCountShift)|SpvOpStore, 231, 236,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 238, 231,\
(3<<SpvWordCountShift)|SpvOpStore, 237, 238,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 240, 225,\
(3<<SpvWordCountShift)|SpvOpStore, 239, 240,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 241, 12, 237, 239,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 243, 219,\
(3<<SpvWordCountShift)|SpvOpStore, 242, 243,\
(3<<SpvWordCountShift)|SpvOpStore, 244, 241,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 245, 16, 242, 244,\
(3<<SpvWordCountShift)|SpvOpStore, 158, 245,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 246, 111,\
(4<<SpvWordCountShift)|SpvOpLoad, 70, 247, 72,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 248, 158, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 249, 248,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 250, 158, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 251, 250,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, 93, 252, 249, 251, 175, 176,\
(4<<SpvWordCountShift)|SpvOpImageWrite, 246, 247, 252,\
(2<<SpvWordCountShift)|SpvOpBranch, 183,\
(2<<SpvWordCountShift)|SpvOpLabel, 183,\
(2<<SpvWordCountShift)|SpvOpBranch, 92,\
(2<<SpvWordCountShift)|SpvOpLabel, 92,\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
(5<<SpvWordCountShift)|SpvOpFunction, 2, 20, SpvFunctionControlMaskNone, 3,\
(2<<SpvWordCountShift)|SpvOpLabel, 21,\
(4<<SpvWordCountShift)|SpvOpVariable, 71, 253, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 94, 262, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 271, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 281, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 291, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 297, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 303, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 309, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 315, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 316, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 318, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 321, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 323, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 94, 338, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 347, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 357, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 109, 367, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 373, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 379, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 385, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 391, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 393, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 396, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 398, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpLoad, 74, 254, 76,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 77, 255, 254, 254, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 70, 256, 255,\
(3<<SpvWordCountShift)|SpvOpStore, 253, 256,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 85, 257, 84, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 73, 258, 257,\
(5<<SpvWordCountShift)|SpvOpIEqual, 89, 259, 258, 88,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, 261, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, 259, 260, 332,\
(2<<SpvWordCountShift)|SpvOpLabel, 260,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 263, 98,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 85, 264, 84, 100,\
(4<<SpvWordCountShift)|SpvOpLoad, 73, 265, 264,\
(4<<SpvWordCountShift)|SpvOpBitcast, 23, 266, 265,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 267, 253, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 268, 267,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 269, 266, 268,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 270, 263, 269,\
(3<<SpvWordCountShift)|SpvOpStore, 262, 270,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 272, 111,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 273, 253, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 274, 273,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 275, 262, 113,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 276, 275,\
(4<<SpvWordCountShift)|SpvOpConvertFToS, 23, 277, 276,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 278, 274, 277,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 279, 272, 278,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 81, 280, 279, 279, 0, 1,\
(3<<SpvWordCountShift)|SpvOpStore, 271, 280,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 282, 111,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 283, 253, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 284, 283,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 285, 262, 125,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 286, 285,\
(4<<SpvWordCountShift)|SpvOpConvertFToS, 23, 287, 286,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 288, 284, 287,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 289, 282, 288,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 81, 290, 289, 289, 0, 1,\
(3<<SpvWordCountShift)|SpvOpStore, 281, 290,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 292, 262, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 293, 292,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 294, 262, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 295, 294,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 81, 296, 293, 295,\
(3<<SpvWordCountShift)|SpvOpStore, 291, 296,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 298, 271, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 299, 298,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 300, 271, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 301, 300,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 302, 299, 301,\
(3<<SpvWordCountShift)|SpvOpStore, 297, 302,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 304, 281, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 305, 304,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 306, 281, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 307, 306,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 308, 305, 307,\
(3<<SpvWordCountShift)|SpvOpStore, 303, 308,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 310, 291, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 311, 310,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 312, 291, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 313, 312,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 314, 311, 313,\
(3<<SpvWordCountShift)|SpvOpStore, 309, 314,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 317, 309,\
(3<<SpvWordCountShift)|SpvOpStore, 316, 317,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 319, 303,\
(3<<SpvWordCountShift)|SpvOpStore, 318, 319,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 320, 12, 316, 318,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 322, 297,\
(3<<SpvWordCountShift)|SpvOpStore, 321, 322,\
(3<<SpvWordCountShift)|SpvOpStore, 323, 320,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 324, 16, 321, 323,\
(3<<SpvWordCountShift)|SpvOpStore, 315, 324,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 325, 168,\
(4<<SpvWordCountShift)|SpvOpLoad, 70, 326, 253,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 327, 315, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 328, 327,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 329, 315, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 330, 329,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, 93, 331, 328, 330, 175, 176,\
(4<<SpvWordCountShift)|SpvOpImageWrite, 325, 326, 331,\
(2<<SpvWordCountShift)|SpvOpBranch, 261,\
(2<<SpvWordCountShift)|SpvOpLabel, 332,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 85, 333, 84, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 73, 334, 333,\
(5<<SpvWordCountShift)|SpvOpIEqual, 89, 335, 334, 117,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, 337, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, 335, 336, 337,\
(2<<SpvWordCountShift)|SpvOpLabel, 336,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 339, 98,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 85, 340, 84, 100,\
(4<<SpvWordCountShift)|SpvOpLoad, 73, 341, 340,\
(4<<SpvWordCountShift)|SpvOpBitcast, 23, 342, 341,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 343, 253, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 344, 343,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 345, 342, 344,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 346, 339, 345,\
(3<<SpvWordCountShift)|SpvOpStore, 338, 346,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 348, 168,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 349, 253, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 350, 349,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 351, 338, 113,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 352, 351,\
(4<<SpvWordCountShift)|SpvOpConvertFToS, 23, 353, 352,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 354, 350, 353,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 355, 348, 354,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 81, 356, 355, 355, 0, 1,\
(3<<SpvWordCountShift)|SpvOpStore, 347, 356,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 358, 168,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 104, 359, 253, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 23, 360, 359,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 361, 338, 125,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 362, 361,\
(4<<SpvWordCountShift)|SpvOpConvertFToS, 23, 363, 362,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 364, 360, 363,\
(5<<SpvWordCountShift)|SpvOpImageRead, 93, 365, 358, 364,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 81, 366, 365, 365, 0, 1,\
(3<<SpvWordCountShift)|SpvOpStore, 357, 366,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 368, 338, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 369, 368,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 370, 338, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 371, 370,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 81, 372, 369, 371,\
(3<<SpvWordCountShift)|SpvOpStore, 367, 372,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 374, 347, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 375, 374,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 376, 347, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 377, 376,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 378, 375, 377,\
(3<<SpvWordCountShift)|SpvOpStore, 373, 378,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 380, 357, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 381, 380,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 382, 357, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 383, 382,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 384, 381, 383,\
(3<<SpvWordCountShift)|SpvOpStore, 379, 384,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 386, 367, 88,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 387, 386,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 388, 367, 117,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 389, 388,\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, 7, 390, 387, 389,\
(3<<SpvWordCountShift)|SpvOpStore, 385, 390,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 392, 385,\
(3<<SpvWordCountShift)|SpvOpStore, 391, 392,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 394, 379,\
(3<<SpvWordCountShift)|SpvOpStore, 393, 394,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 395, 12, 391, 393,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 397, 373,\
(3<<SpvWordCountShift)|SpvOpStore, 396, 397,\
(3<<SpvWordCountShift)|SpvOpStore, 398, 395,\
(6<<SpvWordCountShift)|SpvOpFunctionCall, 7, 399, 16, 396, 398,\
(3<<SpvWordCountShift)|SpvOpStore, 315, 399,\
(4<<SpvWordCountShift)|SpvOpLoad, 96, 400, 111,\
(4<<SpvWordCountShift)|SpvOpLoad, 70, 401, 253,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 402, 315, 24,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 403, 402,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 25, 404, 315, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 405, 404,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, 93, 406, 403, 405, 175, 176,\
(4<<SpvWordCountShift)|SpvOpImageWrite, 400, 401, 406,\
(2<<SpvWordCountShift)|SpvOpBranch, 337,\
(2<<SpvWordCountShift)|SpvOpLabel, 337,\
(2<<SpvWordCountShift)|SpvOpBranch, 261,\
(2<<SpvWordCountShift)|SpvOpLabel, 261,\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

typedef enum ComputeShaderInversionVariables {
}ComputeShaderInversionVariables;
#define ComputeShaderInversionSize (694 * sizeof(SPIRV))
#define ComputeShaderInversion() {\
SPIRV_Header(124)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, 1, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(10<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelGLCompute, 4, 'niam', '\0', 13, 48, 67, 73, 99,\
(6<<SpvWordCountShift)|SpvOpExecutionMode, 4, SpvExecutionModeLocalSize, 16, 16, 1,\
\
(4<<SpvWordCountShift)|SpvOpDecorate, 13, SpvDecorationBuiltIn, SpvBuiltInGlobalInvocationId,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 46, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 46, 1, SpvDecorationOffset, 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 46, 2, SpvDecorationOffset, 8,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 46, 3, SpvDecorationOffset, 12,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 46, 4, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 46, 5, SpvDecorationOffset, 20,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 46, 6, SpvDecorationOffset, 24,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 46, 7, SpvDecorationOffset, 28,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 46, 8, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, 46, 9, SpvDecorationOffset, 40,\
(3<<SpvWordCountShift)|SpvOpDecorate, 46, SpvDecorationBlock,\
(4<<SpvWordCountShift)|SpvOpDecorate, 67, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 67, SpvDecorationBinding, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, 73, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 73, SpvDecorationBinding, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 99, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, 99, SpvDecorationBinding, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, 123, SpvDecorationBuiltIn, SpvBuiltInWorkgroupSize,\
\
(2<<SpvWordCountShift)|SpvOpTypeVoid, 2,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, 3, 2,\
(4<<SpvWordCountShift)|SpvOpTypeInt, 6, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 7, 6, 2,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 8, SpvStorageClassFunction, 7,\
(4<<SpvWordCountShift)|SpvOpTypeInt, 10, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 11, 10, 3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 12, SpvStorageClassInput, 11,\
(4<<SpvWordCountShift)|SpvOpVariable, 12, 13, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 14, 10, 2,\
(3<<SpvWordCountShift)|SpvOpTypeFloat, 18, 32,\
(4<<SpvWordCountShift)|SpvOpConstant, 10, 19, 2,\
(4<<SpvWordCountShift)|SpvOpTypeArray, 20, 18, 19,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 21, SpvStorageClassFunction, 20,\
(4<<SpvWordCountShift)|SpvOpConstant, 18, 23, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, 18, 24, 3212836864,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, 20, 25, 23, 24,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 26, SpvStorageClassFunction, 6,\
(4<<SpvWordCountShift)|SpvOpConstant, 10, 28, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, 10, 31, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, 18, 36, 1073741824,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 39, SpvStorageClassFunction, 18,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 45, 18, 2,\
(12<<SpvWordCountShift)|SpvOpTypeStruct, 46, 10, 10, 10, 10, 10, 18, 18, 18, 18, 45,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 47, SpvStorageClassPushConstant, 46,\
(4<<SpvWordCountShift)|SpvOpVariable, 47, 48, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 49, 0,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 50, SpvStorageClassPushConstant, 10,\
(4<<SpvWordCountShift)|SpvOpConstant, 6, 57, 1,\
(2<<SpvWordCountShift)|SpvOpTypeBool, 60,\
(9<<SpvWordCountShift)|SpvOpTypeImage, 65, 18, SpvDim2D, 0, 0, 0, 2, SpvImageFormatR32f,\
(4<<SpvWordCountShift)|SpvOpTypePointer, 66, SpvStorageClassUniformConstant, 65,\
(4<<SpvWordCountShift)|SpvOpVariable, 66, 67, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpTypeVector, 70, 18, 4,\
(4<<SpvWordCountShift)|SpvOpVariable, 66, 73, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, 66, 99, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpConstant, 10, 122, 16,\
(6<<SpvWordCountShift)|SpvOpConstantComposite, 11, 123, 122, 122, 31,\
(5<<SpvWordCountShift)|SpvOpFunction, 2, 4, SpvFunctionControlMaskNone, 3,\
(2<<SpvWordCountShift)|SpvOpLabel, 5,\
(4<<SpvWordCountShift)|SpvOpVariable, 8, 9, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 21, 22, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 26, 27, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 39, 40, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 39, 44, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 39, 64, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, 39, 98, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpLoad, 11, 15, 13,\
(7<<SpvWordCountShift)|SpvOpVectorShuffle, 14, 16, 15, 15, 0, 1,\
(4<<SpvWordCountShift)|SpvOpBitcast, 7, 17, 16,\
(3<<SpvWordCountShift)|SpvOpStore, 9, 17,\
(3<<SpvWordCountShift)|SpvOpStore, 22, 25,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 26, 29, 9, 28,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 30, 29,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 26, 32, 9, 31,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 33, 32,\
(5<<SpvWordCountShift)|SpvOpIAdd, 6, 34, 30, 33,\
(4<<SpvWordCountShift)|SpvOpConvertSToF, 18, 35, 34,\
(5<<SpvWordCountShift)|SpvOpFMod, 18, 37, 35, 36,\
(4<<SpvWordCountShift)|SpvOpConvertFToS, 6, 38, 37,\
(3<<SpvWordCountShift)|SpvOpStore, 27, 38,\
(4<<SpvWordCountShift)|SpvOpLoad, 6, 41, 27,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 39, 42, 22, 41,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 43, 42,\
(3<<SpvWordCountShift)|SpvOpStore, 40, 43,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 50, 51, 48, 49,\
(4<<SpvWordCountShift)|SpvOpLoad, 10, 52, 51,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 50, 53, 48, 49,\
(4<<SpvWordCountShift)|SpvOpLoad, 10, 54, 53,\
(5<<SpvWordCountShift)|SpvOpIMul, 10, 55, 52, 54,\
(4<<SpvWordCountShift)|SpvOpConvertUToF, 18, 56, 55,\
(3<<SpvWordCountShift)|SpvOpStore, 44, 56,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 50, 58, 48, 57,\
(4<<SpvWordCountShift)|SpvOpLoad, 10, 59, 58,\
(5<<SpvWordCountShift)|SpvOpIEqual, 60, 61, 59, 28,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, 63, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, 61, 62, 92,\
(2<<SpvWordCountShift)|SpvOpLabel, 62,\
(4<<SpvWordCountShift)|SpvOpLoad, 65, 68, 67,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 69, 9,\
(5<<SpvWordCountShift)|SpvOpImageRead, 70, 71, 68, 69,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 18, 72, 71, 0,\
(3<<SpvWordCountShift)|SpvOpStore, 64, 72,\
(4<<SpvWordCountShift)|SpvOpLoad, 65, 74, 73,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 75, 9,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 76, 40,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 77, 64,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 78, 44,\
(5<<SpvWordCountShift)|SpvOpFDiv, 18, 79, 77, 78,\
(5<<SpvWordCountShift)|SpvOpFMul, 18, 80, 76, 79,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 81, 40,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 82, 64,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 83, 44,\
(5<<SpvWordCountShift)|SpvOpFDiv, 18, 84, 82, 83,\
(5<<SpvWordCountShift)|SpvOpFMul, 18, 85, 81, 84,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 86, 40,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 87, 64,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 88, 44,\
(5<<SpvWordCountShift)|SpvOpFDiv, 18, 89, 87, 88,\
(5<<SpvWordCountShift)|SpvOpFMul, 18, 90, 86, 89,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 91, 80, 85, 90, 23,\
(4<<SpvWordCountShift)|SpvOpImageWrite, 74, 75, 91,\
(2<<SpvWordCountShift)|SpvOpBranch, 63,\
(2<<SpvWordCountShift)|SpvOpLabel, 92,\
(5<<SpvWordCountShift)|SpvOpAccessChain, 50, 93, 48, 57,\
(4<<SpvWordCountShift)|SpvOpLoad, 10, 94, 93,\
(5<<SpvWordCountShift)|SpvOpIEqual, 60, 95, 94, 31,\
(3<<SpvWordCountShift)|SpvOpSelectionMerge, 97, SpvSelectionControlMaskNone,\
(4<<SpvWordCountShift)|SpvOpBranchConditional, 95, 96, 97,\
(2<<SpvWordCountShift)|SpvOpLabel, 96,\
(4<<SpvWordCountShift)|SpvOpLoad, 65, 100, 99,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 101, 9,\
(5<<SpvWordCountShift)|SpvOpImageRead, 70, 102, 100, 101,\
(5<<SpvWordCountShift)|SpvOpCompositeExtract, 18, 103, 102, 0,\
(3<<SpvWordCountShift)|SpvOpStore, 98, 103,\
(4<<SpvWordCountShift)|SpvOpLoad, 65, 104, 73,\
(4<<SpvWordCountShift)|SpvOpLoad, 7, 105, 9,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 106, 40,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 107, 98,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 108, 44,\
(5<<SpvWordCountShift)|SpvOpFDiv, 18, 109, 107, 108,\
(5<<SpvWordCountShift)|SpvOpFMul, 18, 110, 106, 109,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 111, 40,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 112, 98,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 113, 44,\
(5<<SpvWordCountShift)|SpvOpFDiv, 18, 114, 112, 113,\
(5<<SpvWordCountShift)|SpvOpFMul, 18, 115, 111, 114,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 116, 40,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 117, 98,\
(4<<SpvWordCountShift)|SpvOpLoad, 18, 118, 44,\
(5<<SpvWordCountShift)|SpvOpFDiv, 18, 119, 117, 118,\
(5<<SpvWordCountShift)|SpvOpFMul, 18, 120, 116, 119,\
(7<<SpvWordCountShift)|SpvOpCompositeConstruct, 70, 121, 110, 115, 120, 23,\
(4<<SpvWordCountShift)|SpvOpImageWrite, 104, 105, 121,\
(2<<SpvWordCountShift)|SpvOpBranch, 97,\
(2<<SpvWordCountShift)|SpvOpLabel, 97,\
(2<<SpvWordCountShift)|SpvOpBranch, 63,\
(2<<SpvWordCountShift)|SpvOpLabel, 63,\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

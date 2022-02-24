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
	//VertexDeferredExtension_GLSL450,
	VertexDeferredFunction_Main = 1,

	VertexDeferredType_Void,
	VertexDeferredType_Function,
	VertexDeferredType_bool,

	VertexDeferredType_float32,
	VertexDeferredType_float32vec2,
	VertexDeferredType_float32vec3,
	VertexDeferredType_float32vec4,
	VertexDeferredType_float32mat4,

	VertexDeferredType_uint32,
	VertexDeferredType_uint32vec2,
	VertexDeferredType_uint32vec3,
	VertexDeferredType_uint32vec4,

	VertexDeferredType_int32,
	VertexDeferredType_int32vec2,
	VertexDeferredType_int32vec3,
	VertexDeferredType_int32vec4,

	//constants
	VertexDeferredConstant_float32_0f,
	VertexDeferredConstant_float32_1f,
	VertexDeferredConstant_float32_N1f,

	VertexDeferredConstant_uint_0,

	VertexDeferredConstant_int_0,
	VertexDeferredConstant_int_1,
	VertexDeferredConstant_int_6,

	VertexDeferredConstant_float32vec2_1f_0f,
	VertexDeferredConstant_float32vec2_0f_1f,
	VertexDeferredConstant_float32vec2_0f_0f,
	VertexDeferredConstant_float32vec2_1f_1f,

	VertexDeferredConstant_float32vec2_1f_N1f,
	VertexDeferredConstant_float32vec2_N1f_N1f,
	VertexDeferredConstant_float32vec2_N1f_1f,


	//inputs
	VertexDeferredType_InputPointer_int32,
	VertexDeferredVariable_InputPointer_VertexIndex,
	VertexDeferredVariable_InputPointer_InstanceIndex,

	VertexDeferredType_struct_PushConstants,
	VertexDeferredType_PushConstantPointer_struct_PushConstants,
	VertexDeferredVariable_PushConstantPointer_struct_PushConstants,

	//outputs
	VertexDeferredType_OutputPointer_float32vec4,

	VertexDeferredType_float32_Array_1,
	VertexDeferredType_struct_BuiltIn,
	VertexDeferredType_OutputPointer_struct_BuiltIn,
	VertexDeferredVariable_OutputPointer_struct_BuiltIn,
	VertexDeferredVariable_OutputPointer_float32vec4_Position,

	VertexDeferredType_float32vec2_Array_6,
	VertexDeferredType_FunctionPointer_float32vec2_Array_6,

	VertexDeferredVariable_FunctionPointer_float32vec2_Array_6_Positions,
	VertexDeferredVariable_FunctionPointer_float32vec2_Array_6_UVS,

	VertexDeferredType_FunctionPointer_float32vec2,

	VertexDeferredLabel_Start,

	VertexDeferredLoadedVariable_float32vec2_Array_6_Positions,
	VertexDeferredLoadedVariable_float32vec2_Array_6_UVS,

	VertexDeferredLoadedVariable_int32_VertexIndex,
	VertexDeferredLoadedVariable_int32_InstanceIndex,

	VertexDeferredLoadedVariable_int32_op0,
	VertexDeferredLoadedVariable_int32_index,

	VertexDeferredVariable_FunctionPointer_float32vec2_IndexedPositions,
	VertexDeferredVariable_FunctionPointer_float32vec2_IndexedUVS,

	VertexDeferredLoadedVariable_float32vec2_op4,
	VertexDeferredLoadedVariable_float32vec2_op5,
	VertexDeferredLoadedVariable_float32vec2_op6,
	VertexDeferredLoadedVariable_float32vec4_op7,

	VertexDeferredVariables_MAX
}VertexShaderDeferredVariables;
#define VertexShaderDeferredSize (352 * sizeof(SPIRV))
#define VertexShaderDeferred() {\
SPIRV_Header(VertexDeferredVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(9<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelVertex, VertexDeferredFunction_Main, 'niam', '\0', VertexDeferredVariable_InputPointer_VertexIndex, VertexDeferredVariable_InputPointer_InstanceIndex, \
VertexDeferredVariable_PushConstantPointer_struct_PushConstants, VertexDeferredVariable_OutputPointer_struct_BuiltIn,\
/*DECORATION*/\
/*INPUT*/\
/*Built In*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexDeferredVariable_InputPointer_VertexIndex, SpvDecorationBuiltIn, SpvBuiltInVertexIndex,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexDeferredVariable_InputPointer_InstanceIndex, SpvDecorationBuiltIn, SpvBuiltInInstanceIndex,\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, VertexDeferredType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexDeferredType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexDeferredType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexDeferredType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexDeferredType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
/*Built In*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexDeferredType_struct_BuiltIn, 0, SpvDecorationBuiltIn, SpvBuiltInPosition,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexDeferredType_struct_BuiltIn, 1, SpvDecorationBuiltIn, SpvBuiltInPointSize,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexDeferredType_struct_BuiltIn, 2, SpvDecorationBuiltIn, SpvBuiltInClipDistance,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexDeferredType_struct_BuiltIn, 3, SpvDecorationBuiltIn, SpvBuiltInCullDistance,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexDeferredType_struct_BuiltIn, SpvDecorationBlock,\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, VertexDeferredType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, VertexDeferredType_Function, VertexDeferredType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, VertexDeferredType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, VertexDeferredType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexDeferredType_float32vec2, VertexDeferredType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexDeferredType_float32vec3, VertexDeferredType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexDeferredType_float32vec4, VertexDeferredType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, VertexDeferredType_float32mat4, VertexDeferredType_float32vec4, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, VertexDeferredType_uint32, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexDeferredType_uint32vec2, VertexDeferredType_uint32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexDeferredType_uint32vec3, VertexDeferredType_uint32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexDeferredType_uint32vec4, VertexDeferredType_uint32, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, VertexDeferredType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexDeferredType_int32vec2, VertexDeferredType_int32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexDeferredType_int32vec3, VertexDeferredType_int32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexDeferredType_int32vec4, VertexDeferredType_int32, 4,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, VertexDeferredType_float32, VertexDeferredConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexDeferredType_float32, VertexDeferredConstant_float32_1f, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexDeferredType_float32, VertexDeferredConstant_float32_N1f, 3212836864,\
\
(4<<SpvWordCountShift)|SpvOpConstant, VertexDeferredType_uint32, VertexDeferredConstant_uint_0, 0,\
\
(4<<SpvWordCountShift)|SpvOpConstant, VertexDeferredType_int32, VertexDeferredConstant_int_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexDeferredType_int32, VertexDeferredConstant_int_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexDeferredType_int32, VertexDeferredConstant_int_6, 6,\
/*UV value constants*/\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexDeferredType_float32vec2, VertexDeferredConstant_float32vec2_1f_0f, VertexDeferredConstant_float32_1f, VertexDeferredConstant_float32_0f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexDeferredType_float32vec2, VertexDeferredConstant_float32vec2_0f_1f, VertexDeferredConstant_float32_0f, VertexDeferredConstant_float32_1f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexDeferredType_float32vec2, VertexDeferredConstant_float32vec2_0f_0f, VertexDeferredConstant_float32_0f, VertexDeferredConstant_float32_0f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexDeferredType_float32vec2, VertexDeferredConstant_float32vec2_1f_1f, VertexDeferredConstant_float32_1f, VertexDeferredConstant_float32_1f,\
\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexDeferredType_float32vec2, VertexDeferredConstant_float32vec2_1f_N1f, VertexDeferredConstant_float32_1f, VertexDeferredConstant_float32_N1f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexDeferredType_float32vec2, VertexDeferredConstant_float32vec2_N1f_N1f, VertexDeferredConstant_float32_N1f, VertexDeferredConstant_float32_N1f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexDeferredType_float32vec2, VertexDeferredConstant_float32vec2_N1f_1f, VertexDeferredConstant_float32_N1f, VertexDeferredConstant_float32_1f,\
/*Input/Output Type Declarations*/\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpTypeStruct, VertexDeferredType_struct_PushConstants, VertexDeferredType_float32mat4, VertexDeferredType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexDeferredType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, VertexDeferredType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexDeferredType_PushConstantPointer_struct_PushConstants, VertexDeferredVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
/*inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexDeferredType_InputPointer_int32, SpvStorageClassInput, VertexDeferredType_int32,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexDeferredType_InputPointer_int32, VertexDeferredVariable_InputPointer_VertexIndex, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexDeferredType_InputPointer_int32, VertexDeferredVariable_InputPointer_InstanceIndex, SpvStorageClassInput,\
/*built in output*/\
(4<<SpvWordCountShift)|SpvOpTypeArray, VertexDeferredType_float32_Array_1, VertexDeferredType_float32, VertexDeferredConstant_int_1,\
(6<<SpvWordCountShift)|SpvOpTypeStruct, VertexDeferredType_struct_BuiltIn, VertexDeferredType_float32vec4, VertexDeferredType_float32, VertexDeferredType_float32_Array_1, VertexDeferredType_float32_Array_1,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexDeferredType_OutputPointer_struct_BuiltIn, SpvStorageClassOutput, VertexDeferredType_struct_BuiltIn,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexDeferredType_OutputPointer_struct_BuiltIn, VertexDeferredVariable_OutputPointer_struct_BuiltIn, SpvStorageClassOutput,\
/*input locations*/\
/*output inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexDeferredType_OutputPointer_float32vec4, SpvStorageClassOutput, VertexDeferredType_float32vec4,\
\
(4<<SpvWordCountShift)|SpvOpTypeArray, VertexDeferredType_float32vec2_Array_6, VertexDeferredType_float32vec2, VertexDeferredConstant_int_6,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexDeferredType_FunctionPointer_float32vec2_Array_6, SpvStorageClassFunction, VertexDeferredType_float32vec2_Array_6,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexDeferredType_FunctionPointer_float32vec2, SpvStorageClassFunction, VertexDeferredType_float32vec2,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, VertexDeferredType_Void, VertexDeferredFunction_Main, SpvFunctionControlMaskNone, VertexDeferredType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, VertexDeferredLabel_Start,\
/*create vars*/\
(4<<SpvWordCountShift)|SpvOpVariable, VertexDeferredType_FunctionPointer_float32vec2_Array_6, VertexDeferredVariable_FunctionPointer_float32vec2_Array_6_Positions, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexDeferredType_FunctionPointer_float32vec2_Array_6, VertexDeferredVariable_FunctionPointer_float32vec2_Array_6_UVS, SpvStorageClassFunction,\
/*positions array*/\
(9<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexDeferredType_float32vec2_Array_6, VertexDeferredLoadedVariable_float32vec2_Array_6_Positions,\
	 VertexDeferredConstant_float32vec2_1f_N1f, VertexDeferredConstant_float32vec2_N1f_1f, VertexDeferredConstant_float32vec2_N1f_N1f, VertexDeferredConstant_float32vec2_1f_N1f, VertexDeferredConstant_float32vec2_1f_1f, VertexDeferredConstant_float32vec2_N1f_1f,\
(3<<SpvWordCountShift)|SpvOpStore, VertexDeferredVariable_FunctionPointer_float32vec2_Array_6_Positions, VertexDeferredLoadedVariable_float32vec2_Array_6_Positions,\
/*UVS array*/\
(9<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexDeferredType_float32vec2_Array_6, VertexDeferredLoadedVariable_float32vec2_Array_6_UVS,\
	 VertexDeferredConstant_float32vec2_1f_0f, VertexDeferredConstant_float32vec2_0f_1f, VertexDeferredConstant_float32vec2_0f_0f, VertexDeferredConstant_float32vec2_1f_0f, VertexDeferredConstant_float32vec2_1f_1f, VertexDeferredConstant_float32vec2_0f_1f,\
(3<<SpvWordCountShift)|SpvOpStore, VertexDeferredVariable_FunctionPointer_float32vec2_Array_6_UVS, VertexDeferredLoadedVariable_float32vec2_Array_6_UVS,\
/*index*/\
(4<<SpvWordCountShift)|SpvOpLoad, VertexDeferredType_int32, VertexDeferredLoadedVariable_int32_VertexIndex, VertexDeferredVariable_InputPointer_VertexIndex,\
(4<<SpvWordCountShift)|SpvOpLoad, VertexDeferredType_int32, VertexDeferredLoadedVariable_int32_InstanceIndex, VertexDeferredVariable_InputPointer_InstanceIndex,\
(5<<SpvWordCountShift)|SpvOpIMul, VertexDeferredType_int32, VertexDeferredLoadedVariable_int32_op0, VertexDeferredLoadedVariable_int32_InstanceIndex, VertexDeferredConstant_int_6,\
(5<<SpvWordCountShift)|SpvOpISub, VertexDeferredType_int32, VertexDeferredLoadedVariable_int32_index, VertexDeferredLoadedVariable_int32_VertexIndex, VertexDeferredLoadedVariable_int32_op0,\
/*output*/\
/*out position*/\
(5<<SpvWordCountShift)|SpvOpAccessChain, VertexDeferredType_FunctionPointer_float32vec2, VertexDeferredVariable_FunctionPointer_float32vec2_IndexedPositions, VertexDeferredVariable_FunctionPointer_float32vec2_Array_6_Positions, VertexDeferredLoadedVariable_int32_index,\
(4<<SpvWordCountShift)|SpvOpLoad, VertexDeferredType_float32vec2, VertexDeferredLoadedVariable_float32vec2_op4, VertexDeferredVariable_FunctionPointer_float32vec2_IndexedPositions,\
/*out UVS*/\
(5<<SpvWordCountShift)|SpvOpAccessChain, VertexDeferredType_FunctionPointer_float32vec2, VertexDeferredVariable_FunctionPointer_float32vec2_IndexedUVS, VertexDeferredVariable_FunctionPointer_float32vec2_Array_6_UVS, VertexDeferredLoadedVariable_int32_index,\
(4<<SpvWordCountShift)|SpvOpLoad, VertexDeferredType_float32vec2, VertexDeferredLoadedVariable_float32vec2_op5, VertexDeferredVariable_FunctionPointer_float32vec2_IndexedUVS,\
/*out inbuilt position*/\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexDeferredType_float32vec2, VertexDeferredLoadedVariable_float32vec2_op6, VertexDeferredConstant_float32_1f, VertexDeferredConstant_float32_1f,\
(9<<SpvWordCountShift)|SpvOpVectorShuffle, VertexDeferredType_float32vec4, VertexDeferredLoadedVariable_float32vec4_op7, VertexDeferredLoadedVariable_float32vec2_op4, VertexDeferredLoadedVariable_float32vec2_op6, 0, 1, 2, 3,\
\
(5<<SpvWordCountShift)|SpvOpAccessChain, VertexDeferredType_OutputPointer_float32vec4, VertexDeferredVariable_OutputPointer_float32vec4_Position, VertexDeferredVariable_OutputPointer_struct_BuiltIn, VertexDeferredConstant_int_0,\
(3<<SpvWordCountShift)|SpvOpStore, VertexDeferredVariable_OutputPointer_float32vec4_Position, VertexDeferredLoadedVariable_float32vec4_op7,\
/*function end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

typedef enum FragmentShaderDeferredVariables {
	FragmentDeferredExtension_GLSL450 = 1,
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
	Fragment2DConstant_int32_4,

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
(4<<SpvWordCountShift)|SpvOpConstant, Fragment2DType_int32, Fragment2DConstant_int32_4, 4,\
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
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment2DType_UniformPointer_float32, Fragment2DVariable_UniformPointer_float32_AlphaCutoff, Fragment2DVariable_UniformPointer_struct_Material, Fragment2DConstant_int32_4,\
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
	(5<<SpvWordCountShift)|SpvOpAccessChain, Fragment3DType_UniformPointer_float32, Fragment3DVariable_UniformPointer_float32_AlphaCutoff, Fragment3DVariable_UniformPointer_struct_Material, Fragment3DConstant_int_4,\
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
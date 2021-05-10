#pragma once
//C
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//Third-Party
#include <atomic\atomic.h>
//ours
#include "Extension.h"
#include "Object.h"
#define TEX_EXPOSE_GRAPHICS
#include "GraphicsShaders.h"
#include "Graphics.h"
#define TEX_EXPOSE_CHEMISTRY
#include "Chemistry.h"

volatile struct
{
	uint32_t pad;
}Config;

volatile ChemistryUtils Utils;

///////////////////////////////////////////////////////////////////////////////////////////////
//SimplifiedMolecular Shader
///////////////////////////////////////////////////////////////////////////////////////////////

typedef enum VertexShaderSimplifiedMolecularVariables {
	VertexSimplifiedMolecularExtension_GLSL450 = 1,
	VertexSimplifiedMolecularFunction_Main,

	VertexSimplifiedMolecularType_Void,
	VertexSimplifiedMolecularType_Function,

	VertexSimplifiedMolecularType_float32,
	VertexSimplifiedMolecularType_float32vec2,
	VertexSimplifiedMolecularType_float32vec3,
	VertexSimplifiedMolecularType_float32vec4,
	VertexSimplifiedMolecularType_float32mat4,

	VertexSimplifiedMolecularType_int32,

	//constants
	VertexSimplifiedMolecularConstant_float32_0f,
	VertexSimplifiedMolecularConstant_float32_1f,

	VertexSimplifiedMolecularConstant_int_0,
	VertexSimplifiedMolecularConstant_int_1,

	VertexSimplifiedMolecularConstant_float32vec3_NULL,


	//inputs
	VertexSimplifiedMolecularType_InputPointer_float32vec3,

	VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Position,
	VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Colour,
	VertexSimplifiedMolecularVariable_InputPointer_int32_ElementType,

	VertexSimplifiedMolecularType_InputPointer_int32,
	VertexSimplifiedMolecularVariable_InputPointer_VertexIndex,
	VertexSimplifiedMolecularVariable_InputPointer_InstanceIndex,


	VertexSimplifiedMolecularType_struct_PushConstants,
	VertexSimplifiedMolecularType_PushConstantPointer_struct_PushConstants,
	VertexSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants,

	//outputs
	VertexSimplifiedMolecularType_OutputPointer_float32vec3,
	VertexSimplifiedMolecularType_OutputPointer_float32vec4,
	VertexSimplifiedMolecularType_OutputPointer_float32,

	VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Position,
	VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Colour,

	VertexSimplifiedMolecularType_float32_Array_1,
	VertexSimplifiedMolecularType_struct_BuiltIn,
	VertexSimplifiedMolecularType_OutputPointer_struct_BuiltIn,
	VertexSimplifiedMolecularVariable_OutputPointer_struct_BuiltIn,
	VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_Position,
	VertexSimplifiedMolecularVariable_OutputPointer_float32_PointSize,

	VertexSimplifiedMolecularType_PushConstantPointer_float32mat4,

	VertexSimplifiedMolecularLabel_Start,

	VertexSimplifiedMolecularVariable_PushConstantPointer_MatrixVP,
	VertexSimplifiedMolecularLoadedVariable_PushConstantPointer_MatrixVP,


	VertexSimplifiedMolecularLoadedVariable_float32vec3_Position,
	VertexSimplifiedMolecularLoadedVariable_float32vec3_Colour,
	VertexSimplifiedMolecularLoadedVariable_int32_ElementType,

	VertexSimplifiedMolecularLoadedVariable_float32vec2_op0,
	VertexSimplifiedMolecularLoadedVariable_float32vec4_op0,
	VertexSimplifiedMolecularLoadedVariable_float32vec4_op1,

	VertexSimplifiedMolecularLoadedVariable_float32_op0,

	VertexSimplifiedMolecularVariables_MAX
}VertexShaderSimplifiedMolecularVariables;
#define VertexShaderSimplifiedMolecularSize (308 * sizeof(SPIRV))
#define VertexShaderSimplifiedMolecular() {\
SPIRV_Header(VertexSimplifiedMolecularVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(14<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelVertex, VertexSimplifiedMolecularFunction_Main, 'niam', '\0', VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Position, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Colour, VertexSimplifiedMolecularVariable_InputPointer_int32_ElementType, VertexSimplifiedMolecularVariable_InputPointer_VertexIndex, VertexSimplifiedMolecularVariable_InputPointer_InstanceIndex, \
VertexSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Position, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Colour, VertexSimplifiedMolecularVariable_OutputPointer_struct_BuiltIn,\
/*DECORATION*/\
/*INPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Position, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Colour, SpvDecorationLocation, 1,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_int32_ElementType, SpvDecorationFlat,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_int32_ElementType, SpvDecorationLocation, 2,\
/*Built In*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_VertexIndex, SpvDecorationBuiltIn, SpvBuiltInVertexIndex,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_InstanceIndex, SpvDecorationBuiltIn, SpvBuiltInInstanceIndex,\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Position, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Colour, SpvDecorationLocation, 1,\
/*Built In*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_BuiltIn, 0, SpvDecorationBuiltIn, SpvBuiltInPosition,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_BuiltIn, 1, SpvDecorationBuiltIn, SpvBuiltInPointSize,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_BuiltIn, 2, SpvDecorationBuiltIn, SpvBuiltInClipDistance,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_BuiltIn, 3, SpvDecorationBuiltIn, SpvBuiltInCullDistance,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularType_struct_BuiltIn, SpvDecorationBlock,\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, VertexSimplifiedMolecularType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, VertexSimplifiedMolecularType_Function, VertexSimplifiedMolecularType_Void,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, VertexSimplifiedMolecularType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexSimplifiedMolecularType_float32vec2, VertexSimplifiedMolecularType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexSimplifiedMolecularType_float32vec3, VertexSimplifiedMolecularType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexSimplifiedMolecularType_float32vec4, VertexSimplifiedMolecularType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, VertexSimplifiedMolecularType_float32mat4, VertexSimplifiedMolecularType_float32vec4, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, VertexSimplifiedMolecularType_int32, 32, 1,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, VertexSimplifiedMolecularType_float32, VertexSimplifiedMolecularConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexSimplifiedMolecularType_float32, VertexSimplifiedMolecularConstant_float32_1f, 1065353216,\
\
(4<<SpvWordCountShift)|SpvOpConstant, VertexSimplifiedMolecularType_int32, VertexSimplifiedMolecularConstant_int_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexSimplifiedMolecularType_int32, VertexSimplifiedMolecularConstant_int_1, 1,\
/*Input/Output Type Declarations*/\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpTypeStruct, VertexSimplifiedMolecularType_struct_PushConstants, VertexSimplifiedMolecularType_float32mat4, VertexSimplifiedMolecularType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, VertexSimplifiedMolecularType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_PushConstantPointer_struct_PushConstants, VertexSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
/*inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_InputPointer_int32, SpvStorageClassInput, VertexSimplifiedMolecularType_int32,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_int32, VertexSimplifiedMolecularVariable_InputPointer_VertexIndex, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_int32, VertexSimplifiedMolecularVariable_InputPointer_InstanceIndex, SpvStorageClassInput,\
/*built in output*/\
(4<<SpvWordCountShift)|SpvOpTypeArray, VertexSimplifiedMolecularType_float32_Array_1, VertexSimplifiedMolecularType_float32, VertexSimplifiedMolecularConstant_int_1,\
(6<<SpvWordCountShift)|SpvOpTypeStruct, VertexSimplifiedMolecularType_struct_BuiltIn, VertexSimplifiedMolecularType_float32vec4, VertexSimplifiedMolecularType_float32, VertexSimplifiedMolecularType_float32_Array_1, VertexSimplifiedMolecularType_float32_Array_1,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_OutputPointer_struct_BuiltIn, SpvStorageClassOutput, VertexSimplifiedMolecularType_struct_BuiltIn,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_OutputPointer_struct_BuiltIn, VertexSimplifiedMolecularVariable_OutputPointer_struct_BuiltIn, SpvStorageClassOutput,\
/*input locations*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_InputPointer_float32vec3, SpvStorageClassInput, VertexSimplifiedMolecularType_float32vec3,\
\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_float32vec3, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Position, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_float32vec3, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Colour, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_int32, VertexSimplifiedMolecularVariable_InputPointer_int32_ElementType, SpvStorageClassInput,\
/*output inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_OutputPointer_float32vec3, SpvStorageClassOutput, VertexSimplifiedMolecularType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_OutputPointer_float32vec4, SpvStorageClassOutput, VertexSimplifiedMolecularType_float32vec4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_OutputPointer_float32, SpvStorageClassOutput, VertexSimplifiedMolecularType_float32,\
\
(3<<SpvWordCountShift)|SpvOpConstantNull, VertexSimplifiedMolecularType_float32vec3, VertexSimplifiedMolecularConstant_float32vec3_NULL,\
\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_OutputPointer_float32vec3, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Position, SpvStorageClassOutput, VertexSimplifiedMolecularConstant_float32vec3_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_OutputPointer_float32vec3, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Colour, SpvStorageClassOutput, VertexSimplifiedMolecularConstant_float32vec3_NULL,\
\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_PushConstantPointer_float32mat4, SpvStorageClassPushConstant, VertexSimplifiedMolecularType_float32mat4,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, VertexSimplifiedMolecularType_Void, VertexSimplifiedMolecularFunction_Main, SpvFunctionControlMaskNone, VertexSimplifiedMolecularType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, VertexSimplifiedMolecularLabel_Start,\
	/*Assign inputs to outputs and also load variables*/\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimplifiedMolecularType_float32vec3, VertexSimplifiedMolecularLoadedVariable_float32vec3_Position, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Position,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Position, VertexSimplifiedMolecularLoadedVariable_float32vec3_Position,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimplifiedMolecularType_float32vec3, VertexSimplifiedMolecularLoadedVariable_float32vec3_Colour, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Colour,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Colour, VertexSimplifiedMolecularLoadedVariable_float32vec3_Colour,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimplifiedMolecularType_int32, VertexSimplifiedMolecularLoadedVariable_int32_ElementType, VertexSimplifiedMolecularVariable_InputPointer_int32_ElementType,\
	/*get pushconstants VP matrix*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, VertexSimplifiedMolecularType_PushConstantPointer_float32mat4, VertexSimplifiedMolecularVariable_PushConstantPointer_MatrixVP, VertexSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants, VertexSimplifiedMolecularConstant_int_0,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimplifiedMolecularType_float32mat4, VertexSimplifiedMolecularLoadedVariable_PushConstantPointer_MatrixVP, VertexSimplifiedMolecularVariable_PushConstantPointer_MatrixVP,\
	/*out inbuilt position*/\
	(5<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexSimplifiedMolecularType_float32vec2, VertexSimplifiedMolecularLoadedVariable_float32vec2_op0, VertexSimplifiedMolecularConstant_float32_1f, VertexSimplifiedMolecularConstant_float32_1f,\
	(9<<SpvWordCountShift)|SpvOpVectorShuffle, VertexSimplifiedMolecularType_float32vec4, VertexSimplifiedMolecularLoadedVariable_float32vec4_op0, VertexSimplifiedMolecularLoadedVariable_float32vec3_Position, VertexSimplifiedMolecularLoadedVariable_float32vec2_op0, 0, 1, 2, 3,\
	\
	(5<<SpvWordCountShift)|SpvOpMatrixTimesVector, VertexSimplifiedMolecularType_float32vec4, VertexSimplifiedMolecularLoadedVariable_float32vec4_op1, VertexSimplifiedMolecularLoadedVariable_PushConstantPointer_MatrixVP, VertexSimplifiedMolecularLoadedVariable_float32vec4_op0,\
	\
	(5<<SpvWordCountShift)|SpvOpAccessChain, VertexSimplifiedMolecularType_OutputPointer_float32vec4, VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_Position, VertexSimplifiedMolecularVariable_OutputPointer_struct_BuiltIn, VertexSimplifiedMolecularConstant_int_0,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_Position, VertexSimplifiedMolecularLoadedVariable_float32vec4_op1,\
	/*pointsize*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, VertexSimplifiedMolecularType_OutputPointer_float32, VertexSimplifiedMolecularVariable_OutputPointer_float32_PointSize, VertexSimplifiedMolecularVariable_OutputPointer_struct_BuiltIn, VertexSimplifiedMolecularConstant_int_1,\
	(4<<SpvWordCountShift)|SpvOpConvertUToF, VertexSimplifiedMolecularType_float32, VertexSimplifiedMolecularLoadedVariable_float32_op0, VertexSimplifiedMolecularLoadedVariable_int32_ElementType,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimplifiedMolecularVariable_OutputPointer_float32_PointSize, VertexSimplifiedMolecularLoadedVariable_float32_op0,\
/*function end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

typedef enum FragmentShaderSimplifiedMolecularVariables {
	FragmentSimplifiedMolecularExtension_GLSL450 = 1,
	FragmentSimplifiedMolecularFunction_Main,

	FragmentSimplifiedMolecularType_Void,
	FragmentSimplifiedMolecularType_Function,

	FragmentSimplifiedMolecularType_float32,
	FragmentSimplifiedMolecularType_float32vec2,
	FragmentSimplifiedMolecularType_float32vec3,
	FragmentSimplifiedMolecularType_float32vec4,
	FragmentSimplifiedMolecularType_float32mat4,

	FragmentSimplifiedMolecularType_int32,

	//constants
	FragmentSimplifiedMolecularConstant_float32_0f,
	FragmentSimplifiedMolecularConstant_float32_1f,

	FragmentSimplifiedMolecularConstant_int32_0,

	//inputs
	//input locations
	FragmentSimplifiedMolecularType_InputPointer_float32vec3,

	FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Position,
	FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Colour,

	//pushconstants
	FragmentSimplifiedMolecularType_struct_PushConstants,
	FragmentSimplifiedMolecularType_PushConstantPointer_struct_PushConstants,
	FragmentSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants,
	FragmentSimplifiedMolecularType_PushConstantPointer_int32,

	//output image attachments
	FragmentSimplifiedMolecularType_OutputPointer_float32vec4,
	FragmentSimplifiedMolecularConstant_float32vec4_NULL,
	FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,
	FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutPositionOrRevealage,

	FragmentSimplifiedMolecularConstantComposite_float32vec4_SelectedColour,

	//function start

	FragmentSimplifiedMolecularLabel_Start,

	FragmentSimplifiedMolecularLoadedVariable_float32vec3_Position,
	FragmentSimplifiedMolecularLoadedVariable_float32vec3_Colour,

	FragmentSimplifiedMolecularLoadedVariable_float32vec2_op0,
	FragmentSimplifiedMolecularLoadedVariable_float32vec4_op0,


	FragmentSimplifiedMolecularVariables_MAX
}FragmentShaderSimplifiedMolecularVariables;
#define FragmentShaderSimplifiedMolecularSize (196 * sizeof(SPIRV))
#define FragmentShaderSimplifiedMolecular() {\
SPIRV_Header(FragmentSimplifiedMolecularVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityImageQuery,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, FragmentSimplifiedMolecularExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(10<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelFragment, FragmentSimplifiedMolecularFunction_Main, 'niam', '\0', FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Position, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Colour,\
FragmentSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutPositionOrRevealage,\
(3<<SpvWordCountShift)|SpvOpExecutionMode, FragmentSimplifiedMolecularFunction_Main, SpvExecutionModeOriginUpperLeft,\
/*DECORATION*/\
/*INPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Position, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Colour, SpvDecorationLocation, 1,\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, 2, SpvDecorationOffset, 68,\
(3<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvDecorationLocation, 1,\
\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, FragmentSimplifiedMolecularType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, FragmentSimplifiedMolecularType_Function, FragmentSimplifiedMolecularType_Void,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, FragmentSimplifiedMolecularType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentSimplifiedMolecularType_float32vec2, FragmentSimplifiedMolecularType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentSimplifiedMolecularType_float32vec3, FragmentSimplifiedMolecularType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentSimplifiedMolecularType_float32vec4, FragmentSimplifiedMolecularType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, FragmentSimplifiedMolecularType_float32mat4, FragmentSimplifiedMolecularType_float32vec4, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, FragmentSimplifiedMolecularType_int32, 32, 1,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentSimplifiedMolecularType_float32, FragmentSimplifiedMolecularConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentSimplifiedMolecularType_float32, FragmentSimplifiedMolecularConstant_float32_1f, 1065353216,\
\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentSimplifiedMolecularType_int32, FragmentSimplifiedMolecularConstant_int32_0, 0,\
/*input locations*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimplifiedMolecularType_InputPointer_float32vec3, SpvStorageClassInput, FragmentSimplifiedMolecularType_float32vec3,\
\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_InputPointer_float32vec3, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Position, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_InputPointer_float32vec3, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Colour, SpvStorageClassInput,\
/*pushconstants*/\
(5<<SpvWordCountShift)|SpvOpTypeStruct, FragmentSimplifiedMolecularType_struct_PushConstants, FragmentSimplifiedMolecularType_float32mat4, FragmentSimplifiedMolecularType_int32, FragmentSimplifiedMolecularType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimplifiedMolecularType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, FragmentSimplifiedMolecularType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_PushConstantPointer_struct_PushConstants, FragmentSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimplifiedMolecularType_PushConstantPointer_int32, SpvStorageClassPushConstant, FragmentSimplifiedMolecularType_int32,\
/*outputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimplifiedMolecularType_OutputPointer_float32vec4, SpvStorageClassOutput, FragmentSimplifiedMolecularType_float32vec4,\
(3<<SpvWordCountShift)|SpvOpConstantNull, FragmentSimplifiedMolecularType_float32vec4, FragmentSimplifiedMolecularConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_OutputPointer_float32vec4, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvStorageClassOutput, FragmentSimplifiedMolecularConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_OutputPointer_float32vec4, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvStorageClassOutput, FragmentSimplifiedMolecularConstant_float32vec4_NULL,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, FragmentSimplifiedMolecularType_Void, FragmentSimplifiedMolecularFunction_Main, SpvFunctionControlMaskNone, FragmentSimplifiedMolecularType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, FragmentSimplifiedMolecularLabel_Start,\
	/*Loading Variables*/\
	(4<<SpvWordCountShift)|SpvOpLoad, FragmentSimplifiedMolecularType_float32vec3, FragmentSimplifiedMolecularLoadedVariable_float32vec3_Position, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Position,\
	(4<<SpvWordCountShift)|SpvOpLoad, FragmentSimplifiedMolecularType_float32vec3, FragmentSimplifiedMolecularLoadedVariable_float32vec3_Colour, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Colour,\
	/*out inbuilt Colour*/\
	(5<<SpvWordCountShift)|SpvOpCompositeConstruct, FragmentSimplifiedMolecularType_float32vec2, FragmentSimplifiedMolecularLoadedVariable_float32vec2_op0, FragmentSimplifiedMolecularConstant_float32_1f, FragmentSimplifiedMolecularConstant_float32_1f,\
	(9<<SpvWordCountShift)|SpvOpVectorShuffle, FragmentSimplifiedMolecularType_float32vec4, FragmentSimplifiedMolecularLoadedVariable_float32vec4_op0, FragmentSimplifiedMolecularLoadedVariable_float32vec3_Colour, FragmentSimplifiedMolecularLoadedVariable_float32vec2_op0, 0, 1, 2, 3,\
	\
	(3<<SpvWordCountShift)|SpvOpStore, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, FragmentSimplifiedMolecularLoadedVariable_float32vec4_op0,\
/*function end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd\
}


typedef enum VertexShaderCovalentBondVariables {
	VertexCovalentBondExtension_GLSL450 = 1,
	VertexCovalentBondFunction_Main,

	VertexCovalentBondType_Void,
	VertexCovalentBondType_Function,
	VertexCovalentBondType_bool,

	VertexCovalentBondType_float32,
	VertexCovalentBondType_float32vec2,
	VertexCovalentBondType_float32vec3,
	VertexCovalentBondType_float32vec4,
	VertexCovalentBondType_float32mat4,

	VertexCovalentBondType_int32,

	//constants
	VertexCovalentBondConstant_float32_0f,
	VertexCovalentBondConstant_float32_1f,

	VertexCovalentBondConstant_int_0,
	VertexCovalentBondConstant_int_1,

	VertexCovalentBondConstant_float32vec3_NULL,


	//inputs
	VertexCovalentBondType_InputPointer_float32vec3,

	VertexCovalentBondVariable_InputPointer_float32vec3_Position,

	VertexCovalentBondType_InputPointer_int32,
	VertexCovalentBondVariable_InputPointer_VertexIndex,
	VertexCovalentBondVariable_InputPointer_InstanceIndex,


	VertexCovalentBondType_struct_PushConstants,
	VertexCovalentBondType_PushConstantPointer_struct_PushConstants,
	VertexCovalentBondVariable_PushConstantPointer_struct_PushConstants,

	//outputs
	VertexCovalentBondType_OutputPointer_float32vec4,
	VertexCovalentBondType_OutputPointer_float32,

	VertexCovalentBondType_float32_Array_1,
	VertexCovalentBondType_struct_BuiltIn,
	VertexCovalentBondType_OutputPointer_struct_BuiltIn,
	VertexCovalentBondVariable_OutputPointer_struct_BuiltIn,
	VertexCovalentBondVariable_OutputPointer_float32vec4_Position,
	VertexCovalentBondVariable_OutputPointer_float32_PointSize,

	VertexCovalentBondType_PushConstantPointer_float32mat4,

	VertexCovalentBondLabel_Start,

	VertexCovalentBondVariable_PushConstantPointer_MatrixVP,
	VertexCovalentBondLoadedVariable_PushConstantPointer_MatrixVP,


	VertexCovalentBondLoadedVariable_float32vec3_Position,

	VertexCovalentBondLoadedVariable_float32vec2_op0,
	VertexCovalentBondLoadedVariable_float32vec4_op0,
	VertexCovalentBondLoadedVariable_float32vec4_op1,

	VertexCovalentBondVariables_MAX
}VertexShaderCovalentBondVariables;
#define VertexShaderCovalentBondSize (239 * sizeof(SPIRV))
#define VertexShaderCovalentBond() {\
SPIRV_Header(VertexCovalentBondVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(10<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelVertex, VertexCovalentBondFunction_Main, 'niam', '\0', VertexCovalentBondVariable_InputPointer_float32vec3_Position, VertexCovalentBondVariable_InputPointer_VertexIndex, VertexCovalentBondVariable_InputPointer_InstanceIndex, \
VertexCovalentBondVariable_PushConstantPointer_struct_PushConstants, VertexCovalentBondVariable_OutputPointer_struct_BuiltIn,\
/*DECORATION*/\
/*INPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexCovalentBondVariable_InputPointer_float32vec3_Position, SpvDecorationLocation, 0,\
/*Built In*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexCovalentBondVariable_InputPointer_VertexIndex, SpvDecorationBuiltIn, SpvBuiltInVertexIndex,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexCovalentBondVariable_InputPointer_InstanceIndex, SpvDecorationBuiltIn, SpvBuiltInInstanceIndex,\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, VertexCovalentBondType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexCovalentBondType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexCovalentBondType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexCovalentBondType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexCovalentBondType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
/*Built In*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexCovalentBondType_struct_BuiltIn, 0, SpvDecorationBuiltIn, SpvBuiltInPosition,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexCovalentBondType_struct_BuiltIn, 1, SpvDecorationBuiltIn, SpvBuiltInPointSize,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexCovalentBondType_struct_BuiltIn, 2, SpvDecorationBuiltIn, SpvBuiltInClipDistance,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexCovalentBondType_struct_BuiltIn, 3, SpvDecorationBuiltIn, SpvBuiltInCullDistance,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexCovalentBondType_struct_BuiltIn, SpvDecorationBlock,\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, VertexCovalentBondType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, VertexCovalentBondType_Function, VertexCovalentBondType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, VertexCovalentBondType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, VertexCovalentBondType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexCovalentBondType_float32vec2, VertexCovalentBondType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexCovalentBondType_float32vec3, VertexCovalentBondType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexCovalentBondType_float32vec4, VertexCovalentBondType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, VertexCovalentBondType_float32mat4, VertexCovalentBondType_float32vec4, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, VertexCovalentBondType_int32, 32, 1,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, VertexCovalentBondType_float32, VertexCovalentBondConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexCovalentBondType_float32, VertexCovalentBondConstant_float32_1f, 1065353216,\
\
(4<<SpvWordCountShift)|SpvOpConstant, VertexCovalentBondType_int32, VertexCovalentBondConstant_int_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexCovalentBondType_int32, VertexCovalentBondConstant_int_1, 1,\
/*Input/Output Type Declarations*/\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpTypeStruct, VertexCovalentBondType_struct_PushConstants, VertexCovalentBondType_float32mat4, VertexCovalentBondType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexCovalentBondType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, VertexCovalentBondType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexCovalentBondType_PushConstantPointer_struct_PushConstants, VertexCovalentBondVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
/*inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexCovalentBondType_InputPointer_int32, SpvStorageClassInput, VertexCovalentBondType_int32,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexCovalentBondType_InputPointer_int32, VertexCovalentBondVariable_InputPointer_VertexIndex, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexCovalentBondType_InputPointer_int32, VertexCovalentBondVariable_InputPointer_InstanceIndex, SpvStorageClassInput,\
/*built in output*/\
(4<<SpvWordCountShift)|SpvOpTypeArray, VertexCovalentBondType_float32_Array_1, VertexCovalentBondType_float32, VertexCovalentBondConstant_int_1,\
(6<<SpvWordCountShift)|SpvOpTypeStruct, VertexCovalentBondType_struct_BuiltIn, VertexCovalentBondType_float32vec4, VertexCovalentBondType_float32, VertexCovalentBondType_float32_Array_1, VertexCovalentBondType_float32_Array_1,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexCovalentBondType_OutputPointer_struct_BuiltIn, SpvStorageClassOutput, VertexCovalentBondType_struct_BuiltIn,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexCovalentBondType_OutputPointer_struct_BuiltIn, VertexCovalentBondVariable_OutputPointer_struct_BuiltIn, SpvStorageClassOutput,\
/*input locations*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexCovalentBondType_InputPointer_float32vec3, SpvStorageClassInput, VertexCovalentBondType_float32vec3,\
\
(4<<SpvWordCountShift)|SpvOpVariable, VertexCovalentBondType_InputPointer_float32vec3, VertexCovalentBondVariable_InputPointer_float32vec3_Position, SpvStorageClassInput,\
/*output inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexCovalentBondType_OutputPointer_float32vec4, SpvStorageClassOutput, VertexCovalentBondType_float32vec4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexCovalentBondType_OutputPointer_float32, SpvStorageClassOutput, VertexCovalentBondType_float32,\
\
(3<<SpvWordCountShift)|SpvOpConstantNull, VertexCovalentBondType_float32vec3, VertexCovalentBondConstant_float32vec3_NULL,\
\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexCovalentBondType_PushConstantPointer_float32mat4, SpvStorageClassPushConstant, VertexCovalentBondType_float32mat4,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, VertexCovalentBondType_Void, VertexCovalentBondFunction_Main, SpvFunctionControlMaskNone, VertexCovalentBondType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, VertexCovalentBondLabel_Start,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexCovalentBondType_float32vec3, VertexCovalentBondLoadedVariable_float32vec3_Position, VertexCovalentBondVariable_InputPointer_float32vec3_Position,\
	/*get pushconstants VP matrix*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, VertexCovalentBondType_PushConstantPointer_float32mat4, VertexCovalentBondVariable_PushConstantPointer_MatrixVP, VertexCovalentBondVariable_PushConstantPointer_struct_PushConstants, VertexCovalentBondConstant_int_0,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexCovalentBondType_float32mat4, VertexCovalentBondLoadedVariable_PushConstantPointer_MatrixVP, VertexCovalentBondVariable_PushConstantPointer_MatrixVP,\
	/*out inbuilt position*/\
	(5<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexCovalentBondType_float32vec2, VertexCovalentBondLoadedVariable_float32vec2_op0, VertexCovalentBondConstant_float32_1f, VertexCovalentBondConstant_float32_1f,\
	(9<<SpvWordCountShift)|SpvOpVectorShuffle, VertexCovalentBondType_float32vec4, VertexCovalentBondLoadedVariable_float32vec4_op0, VertexCovalentBondLoadedVariable_float32vec3_Position, VertexCovalentBondLoadedVariable_float32vec2_op0, 0, 1, 2, 3,\
	\
	(5<<SpvWordCountShift)|SpvOpMatrixTimesVector, VertexCovalentBondType_float32vec4, VertexCovalentBondLoadedVariable_float32vec4_op1, VertexCovalentBondLoadedVariable_PushConstantPointer_MatrixVP, VertexCovalentBondLoadedVariable_float32vec4_op0,\
	\
	(5<<SpvWordCountShift)|SpvOpAccessChain, VertexCovalentBondType_OutputPointer_float32vec4, VertexCovalentBondVariable_OutputPointer_float32vec4_Position, VertexCovalentBondVariable_OutputPointer_struct_BuiltIn, VertexCovalentBondConstant_int_0,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexCovalentBondVariable_OutputPointer_float32vec4_Position, VertexCovalentBondLoadedVariable_float32vec4_op1,\
/*function end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

typedef enum FragmentShaderCovalentBondVariables {
	FragmentCovalentBondExtension_GLSL450 = 1,
	FragmentCovalentBondFunction_Main,

	FragmentCovalentBondType_Void,
	FragmentCovalentBondType_Function,

	FragmentCovalentBondType_float32,
	FragmentCovalentBondType_float32vec4,
	FragmentCovalentBondType_float32mat4,

	FragmentCovalentBondType_int32,

	//constants
	FragmentCovalentBondConstant_float32_0f,
	FragmentCovalentBondConstant_float32_1f,
	FragmentCovalentBondConstant_float32vec4_1f_1f_1f_1f,

	//inputs
	//pushconstants
	FragmentCovalentBondType_struct_PushConstants,
	FragmentCovalentBondType_PushConstantPointer_struct_PushConstants,
	FragmentCovalentBondVariable_PushConstantPointer_struct_PushConstants,
	FragmentCovalentBondType_PushConstantPointer_int32,

	//output image attachments
	FragmentCovalentBondType_OutputPointer_float32vec4,
	FragmentCovalentBondConstant_float32vec4_NULL,
	FragmentCovalentBondVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,
	FragmentCovalentBondVariable_OutputPointer_float32vec4_OutPositionOrRevealage,

	FragmentCovalentBondConstantComposite_float32vec4_SelectedColour,

	//function start
	FragmentCovalentBondLabel_Start,

	FragmentCovalentBondVariables_MAX
}FragmentShaderCovalentBondVariables;
#define FragmentShaderCovalentBondSize (147 * sizeof(SPIRV))
#define FragmentShaderCovalentBond() {\
SPIRV_Header(FragmentCovalentBondVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityImageQuery,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, FragmentCovalentBondExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(8<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelFragment, FragmentCovalentBondFunction_Main, 'niam', '\0', FragmentCovalentBondVariable_PushConstantPointer_struct_PushConstants, FragmentCovalentBondVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, FragmentCovalentBondVariable_OutputPointer_float32vec4_OutPositionOrRevealage,\
(3<<SpvWordCountShift)|SpvOpExecutionMode, FragmentCovalentBondFunction_Main, SpvExecutionModeOriginUpperLeft,\
/*DECORATION*/\
/*INPUT*/\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentCovalentBondType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentCovalentBondType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentCovalentBondType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentCovalentBondType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentCovalentBondType_struct_PushConstants, 2, SpvDecorationOffset, 68,\
(3<<SpvWordCountShift)|SpvOpDecorate, FragmentCovalentBondType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentCovalentBondVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentCovalentBondVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvDecorationLocation, 1,\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, FragmentCovalentBondType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, FragmentCovalentBondType_Function, FragmentCovalentBondType_Void,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, FragmentCovalentBondType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentCovalentBondType_float32vec4, FragmentCovalentBondType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, FragmentCovalentBondType_float32mat4, FragmentCovalentBondType_float32vec4, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, FragmentCovalentBondType_int32, 32, 1,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentCovalentBondType_float32, FragmentCovalentBondConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentCovalentBondType_float32, FragmentCovalentBondConstant_float32_1f, 1065353216,\
(7<<SpvWordCountShift)|SpvOpConstantComposite, FragmentCovalentBondType_float32vec4, FragmentCovalentBondConstant_float32vec4_1f_1f_1f_1f, FragmentCovalentBondConstant_float32_1f, FragmentCovalentBondConstant_float32_1f, FragmentCovalentBondConstant_float32_1f, FragmentCovalentBondConstant_float32_1f,\
/*pushconstants*/\
(5<<SpvWordCountShift)|SpvOpTypeStruct, FragmentCovalentBondType_struct_PushConstants, FragmentCovalentBondType_float32mat4, FragmentCovalentBondType_int32, FragmentCovalentBondType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentCovalentBondType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, FragmentCovalentBondType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentCovalentBondType_PushConstantPointer_struct_PushConstants, FragmentCovalentBondVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentCovalentBondType_PushConstantPointer_int32, SpvStorageClassPushConstant, FragmentCovalentBondType_int32,\
/*outputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentCovalentBondType_OutputPointer_float32vec4, SpvStorageClassOutput, FragmentCovalentBondType_float32vec4,\
(3<<SpvWordCountShift)|SpvOpConstantNull, FragmentCovalentBondType_float32vec4, FragmentCovalentBondConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentCovalentBondType_OutputPointer_float32vec4, FragmentCovalentBondVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvStorageClassOutput, FragmentCovalentBondConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentCovalentBondType_OutputPointer_float32vec4, FragmentCovalentBondVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvStorageClassOutput, FragmentCovalentBondConstant_float32vec4_NULL,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, FragmentCovalentBondType_Void, FragmentCovalentBondFunction_Main, SpvFunctionControlMaskNone, FragmentCovalentBondType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, FragmentCovalentBondLabel_Start,\
	/*out inbuilt Colour*/\
	(3<<SpvWordCountShift)|SpvOpStore, FragmentCovalentBondVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, FragmentCovalentBondConstant_float32vec4_1f_1f_1f_1f,\
/*function end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd\
}


/**/
typedef enum ComputeShaderButterfly1Variables {
	ButterflyVariable_ExtInstGLSL450 = 1,
	ButterflyFunction_Main,

	ButterflyType_Void,
	ButterflyType_Function,
	ButterflyType_bool,


	ButterflyType_float32,
	ButterflyType_float32vec2,
	ButterflyType_float32vec3,
	ButterflyType_float32vec4,

	ButterflyType_uint32,
	ButterflyType_uint32vec2,
	ButterflyType_uint32vec3,

	ButterflyType_int32,
	ButterflyType_int32vec2,


	//basic constants
	ButterflyConstant_float32_0,

	ButterflyConstant_uint32_0,
	ButterflyConstant_uint32_1,
	ButterflyConstant_uint32_2,

	ButterflyConstant_int32_0,
	ButterflyConstant_int32_1,

	//input
	ButterflyType_InputPointer_uint32vec3,
	ButterflyType_InputPointer_uint32,

	ButterflyType_struct_PushConstants,
	ButterflyType_PushConstantPointer_struct_PushConstants,
	ButterflyVariable_PushConstantPointer_struct_PushConstants,
	ButterflyType_PushConstantPointer_int32,

	ButterflyVariable_InputPointer_uint32vec3_BuiltInInvocationID,

	//twiddlefactors image
	ButterflyType_Image_float32_2D_0_0_0_2_R32f,
	ButterflyType_UniformConstantPointer_Image_float32_2D_0_0_0_2_R32f,
	ButterflyVariable_UniformConstantPointer_Image_float32_2D_0_0_0_2_R32f,

	//output/input
	//GPU_Atom 
	ButterflyType_struct_Atom,
	ButterflyType_RuntimeArray_struct_Atoms,
	ButterflyType_struct_Atoms,
	ButterflyType_StorageBufferPointer_struct_Atoms,
	ButterflyType_StorageBufferPointer_struct_Atom,
	ButterflyType_StorageBufferPointer_float32vec3,

	//pingpong0
	ButterflyVariable_StorageBufferPointer_struct_AtomsPingPong0,
	//pingpong1
	ButterflyVariable_StorageBufferPointer_struct_AtomsPingPong1,

	//output



	ButterflyType_FunctionPointer_struct_Atom,



	ButterflyLabel_Start,



	ButterflyVariable_InputPointer_uint32_BuiltInInvocationID_0,
	ButterflyLoadedVariable_uint32_BuiltInInvocationID_0,

	ButterflyVariable_InputPointer_uint32_BuiltInInvocationID_1,
	ButterflyLoadedVariable_uint32_BuiltInInvocationID_1,

	ButterflyVariable_InputPointer_uint32_BuiltInInvocationID_2,
	ButterflyLoadedVariable_uint32_BuiltInInvocationID_2,


	ButterflyVariable_PushConstantPointer_int32_ButterflyStage,
	ButterflyLoadedVariable_int32_ButterflyStage,

	ButterflyVariable_PushConstantPointer_int32_PingPongIndex,
	ButterflyLoadedVariable_int32_PingPongIndex,


	ButterflyLoadedVariable_int32vec2_op0,
	ButterflyLoadedVariable_float32vec4_TwiddleFactors,



	ButterflyLoadedVariable_float32_op0,
	ButterflyLoadedVariable_float32_op1,
	ButterflyLoadedVariable_float32_op2,
	ButterflyLoadedVariable_float32_op3,

	ButterflyLoadedVariable_int32_op0,
	ButterflyLoadedVariable_int32_op1,

	//ButterflyLoadedVariable_float32vec2_op3,

	//ButterflyLoadedVariable_float32vec3_SampleA,
	//ButterflyLoadedVariable_float32vec3_SampleB,
	ButterflyVariable_FunctionPointer_struct_Atom,

	ButterflyLoadVariable_bool_op0,

	ButterflyLabel_PingPongSelectionMerge,
	ButterflyLabel_PingPongTrue,
	ButterflyLabel_PingPongFalse,

	ButterflyVariable_StorageBufferPointer_struct_AtomPingPong0,
	ButterflyLoadedVariable_struct_AtomPingPong0,
	ButterflyVariable_StorageBufferPointer_struct_AtomPingPong1,
	ButterflyLoadedVariable_struct_AtomPingPong1,


	
	ButterflyVariables_MAX
}ComputeShaderButterfly1Variables;
#define ComputeShaderButterfly1Size (744 * sizeof(SPIRV))
#define ComputeShaderButterfly1() {\
SPIRV_Header(ButterflyVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel, \
(6<<SpvWordCountShift)|SpvOpExtInstImport, ButterflyVariable_ExtInstGLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(11<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelGLCompute, ButterflyFunction_Main, 'niam', '\0', \
	ButterflyVariable_InputPointer_uint32vec3_BuiltInInvocationID, ButterflyVariable_PushConstantPointer_struct_PushConstants, ButterflyVariable_InputPointer_uint32vec3_BuiltInInvocationID, ButterflyVariable_UniformConstantPointer_Image_float32_2D_0_0_0_2_R32f,\
	ButterflyVariable_StorageBufferPointer_struct_AtomsPingPong0, ButterflyVariable_StorageBufferPointer_struct_AtomsPingPong1,\
(6<<SpvWordCountShift)|SpvOpExecutionMode, ButterflyFunction_Main, SpvExecutionModeLocalSize, 1, 16, 1,\
/*DECORATION*/\
/*INPUT*/\
/*PushConstants*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_PushConstants, 1, SpvDecorationOffset, 4,\
(3<<SpvWordCountShift)|SpvOpDecorate, ButterflyType_struct_PushConstants, SpvDecorationBlock,\
/*TwiddleFactors Image*/\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_UniformConstantPointer_Image_float32_2D_0_0_0_2_R32f, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_UniformConstantPointer_Image_float32_2D_0_0_0_2_R32f, SpvDecorationBinding, 0,\
(3<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_UniformConstantPointer_Image_float32_2D_0_0_0_2_R32f, SpvDecorationNonWritable,\
/*InvocationID*/\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_InputPointer_uint32vec3_BuiltInInvocationID, SpvDecorationBuiltIn, SpvBuiltInGlobalInvocationId,\
/*OUTPUT*/\
/*INPUT/OUTPUT*/\
/*storagebuffer GPU_Atoms*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_Atom, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_Atom, 1, SpvDecorationOffset, 12,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_Atom, 2, SpvDecorationOffset, 24,\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyType_RuntimeArray_struct_Atoms, SpvDecorationArrayStride, 28,\
(3<<SpvWordCountShift)|SpvOpDecorate, ButterflyType_struct_Atoms, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_Atoms, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_StorageBufferPointer_struct_AtomsPingPong0, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_StorageBufferPointer_struct_AtomsPingPong0, SpvDecorationBinding, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_StorageBufferPointer_struct_AtomsPingPong1, SpvDecorationDescriptorSet, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_StorageBufferPointer_struct_AtomsPingPong1, SpvDecorationBinding, 4,\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, ButterflyType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, ButterflyType_Function, ButterflyType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, ButterflyType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, ButterflyType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, ButterflyType_float32vec2, ButterflyType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, ButterflyType_float32vec3, ButterflyType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, ButterflyType_float32vec4, ButterflyType_float32, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, ButterflyType_uint32, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, ButterflyType_uint32vec2, ButterflyType_uint32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, ButterflyType_uint32vec3, ButterflyType_uint32, 3,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, ButterflyType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, ButterflyType_int32vec2, ButterflyType_int32, 2,\
/*Basic Constants*/\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_float32, ButterflyConstant_float32_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_uint32, ButterflyConstant_uint32_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_uint32, ButterflyConstant_uint32_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_uint32, ButterflyConstant_uint32_2, 2,\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_int32, ButterflyConstant_int32_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_int32, ButterflyConstant_int32_1, 1,\
/*INPUT*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_InputPointer_uint32vec3, SpvStorageClassInput, ButterflyType_uint32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_InputPointer_uint32, SpvStorageClassInput, ButterflyType_uint32,\
/*PushConstants*/\
(4<<SpvWordCountShift)|SpvOpTypeStruct, ButterflyType_struct_PushConstants, ButterflyType_int32, ButterflyType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, ButterflyType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, ButterflyType_PushConstantPointer_struct_PushConstants, ButterflyVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_PushConstantPointer_int32, SpvStorageClassPushConstant, ButterflyType_int32,\
/*TwiddleFactors Image*/\
(9<<SpvWordCountShift)|SpvOpTypeImage, ButterflyType_Image_float32_2D_0_0_0_2_R32f, ButterflyType_float32, SpvDim2D, 0, 0, 0, 2, SpvImageFormatR32f,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_UniformConstantPointer_Image_float32_2D_0_0_0_2_R32f, SpvStorageClassUniformConstant, ButterflyType_Image_float32_2D_0_0_0_2_R32f,\
(4<<SpvWordCountShift)|SpvOpVariable, ButterflyType_UniformConstantPointer_Image_float32_2D_0_0_0_2_R32f, ButterflyVariable_UniformConstantPointer_Image_float32_2D_0_0_0_2_R32f, SpvStorageClassUniformConstant,\
/*InvocationID*/\
(4<<SpvWordCountShift)|SpvOpVariable, ButterflyType_InputPointer_uint32vec3, ButterflyVariable_InputPointer_uint32vec3_BuiltInInvocationID, SpvStorageClassInput,\
/*OUTPUT*/\
/*INPUT/OUTPUT*/\
/*storagebuffer GPU_Atoms*/\
(5<<SpvWordCountShift)|SpvOpTypeStruct, ButterflyType_struct_Atom, ButterflyType_float32vec3, ButterflyType_float32vec3, ButterflyType_int32,\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, ButterflyType_RuntimeArray_struct_Atoms, ButterflyType_struct_Atom,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, ButterflyType_struct_Atoms, ButterflyType_RuntimeArray_struct_Atoms,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_StorageBufferPointer_struct_Atoms, SpvStorageClassStorageBuffer, ButterflyType_struct_Atoms,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_StorageBufferPointer_struct_Atom, SpvStorageClassStorageBuffer, ButterflyType_struct_Atom,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_StorageBufferPointer_float32vec3, SpvStorageClassStorageBuffer, ButterflyType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpVariable, ButterflyType_StorageBufferPointer_struct_Atoms, ButterflyVariable_StorageBufferPointer_struct_AtomsPingPong0, SpvStorageClassStorageBuffer,\
(4<<SpvWordCountShift)|SpvOpVariable, ButterflyType_StorageBufferPointer_struct_Atoms, ButterflyVariable_StorageBufferPointer_struct_AtomsPingPong1, SpvStorageClassStorageBuffer,\
\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_FunctionPointer_struct_Atom, SpvStorageClassFunction, ButterflyType_struct_Atom,\
/*starting function*/\
(5<<SpvWordCountShift)|SpvOpFunction, ButterflyType_Void, ButterflyFunction_Main, SpvFunctionControlMaskNone, ButterflyType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, ButterflyLabel_Start,\
	/*getting invocation ID's*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_InputPointer_uint32, ButterflyVariable_InputPointer_uint32_BuiltInInvocationID_0, ButterflyVariable_InputPointer_uint32vec3_BuiltInInvocationID, ButterflyConstant_uint32_0,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_uint32, ButterflyLoadedVariable_uint32_BuiltInInvocationID_0, ButterflyVariable_InputPointer_uint32_BuiltInInvocationID_0,\
	(5<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_InputPointer_uint32, ButterflyVariable_InputPointer_uint32_BuiltInInvocationID_1, ButterflyVariable_InputPointer_uint32vec3_BuiltInInvocationID, ButterflyConstant_uint32_1,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_uint32, ButterflyLoadedVariable_uint32_BuiltInInvocationID_1, ButterflyVariable_InputPointer_uint32_BuiltInInvocationID_1,\
	(5<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_InputPointer_uint32, ButterflyVariable_InputPointer_uint32_BuiltInInvocationID_2, ButterflyVariable_InputPointer_uint32vec3_BuiltInInvocationID, ButterflyConstant_uint32_2,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_uint32, ButterflyLoadedVariable_uint32_BuiltInInvocationID_2, ButterflyVariable_InputPointer_uint32_BuiltInInvocationID_2,\
	/*pushconstant accessing*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_PushConstantPointer_int32, ButterflyVariable_PushConstantPointer_int32_ButterflyStage, ButterflyVariable_PushConstantPointer_struct_PushConstants,  ButterflyConstant_int32_0,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_int32, ButterflyLoadedVariable_int32_ButterflyStage, ButterflyVariable_PushConstantPointer_int32_ButterflyStage,\
	\
	(5<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_PushConstantPointer_int32, ButterflyVariable_PushConstantPointer_int32_PingPongIndex, ButterflyVariable_PushConstantPointer_struct_PushConstants,  ButterflyConstant_int32_1,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_int32, ButterflyLoadedVariable_int32_PingPongIndex, ButterflyVariable_PushConstantPointer_int32_PingPongIndex,\
	\
	(5<<SpvWordCountShift)|SpvOpCompositeConstruct, ButterflyType_int32vec2, ButterflyLoadedVariable_int32vec2_op0, ButterflyLoadedVariable_int32_ButterflyStage, ButterflyLoadedVariable_uint32_BuiltInInvocationID_1,\
	(5<<SpvWordCountShift)|SpvOpImageRead, ButterflyType_float32vec4, ButterflyLoadedVariable_float32vec4_TwiddleFactors, ButterflyVariable_UniformConstantPointer_Image_float32_2D_0_0_0_2_R32f, ButterflyLoadedVariable_int32vec2_op0,\
	\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, ButterflyType_float32, ButterflyLoadedVariable_float32_op0, ButterflyLoadedVariable_float32vec4_TwiddleFactors, 0,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, ButterflyType_float32, ButterflyLoadedVariable_float32_op1, ButterflyLoadedVariable_float32vec4_TwiddleFactors, 1,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, ButterflyType_float32, ButterflyLoadedVariable_float32_op2, ButterflyLoadedVariable_float32vec4_TwiddleFactors, 2,\
	(5<<SpvWordCountShift)|SpvOpCompositeExtract, ButterflyType_float32, ButterflyLoadedVariable_float32_op3, ButterflyLoadedVariable_float32vec4_TwiddleFactors, 3,\
	(4<<SpvWordCountShift)|SpvOpConvertFToS, ButterflyType_int32, ButterflyLoadedVariable_int32_op0, ButterflyLoadedVariable_float32_op2,\
	(4<<SpvWordCountShift)|SpvOpConvertFToS, ButterflyType_int32, ButterflyLoadedVariable_int32_op1, ButterflyLoadedVariable_float32_op3,\
	/*IF pingpong == 0 or else*/\
	(4<<SpvWordCountShift)|SpvOpVariable, ButterflyType_FunctionPointer_struct_Atom, ButterflyVariable_FunctionPointer_struct_Atom, SpvStorageClassFunction,\
	(5<<SpvWordCountShift)|SpvOpIEqual, ButterflyType_bool, ButterflyLoadVariable_bool_op0, ButterflyLoadedVariable_int32_PingPongIndex, ButterflyConstant_int32_1,\
	\
	(3<<SpvWordCountShift)|SpvOpSelectionMerge, ButterflyLabel_PingPongSelectionMerge, SpvSelectionControlMaskNone,\
	(4<<SpvWordCountShift)|SpvOpBranchConditional, ButterflyLoadVariable_bool_op0, ButterflyLabel_PingPongTrue, ButterflyLabel_PingPongFalse,\
	(2<<SpvWordCountShift)|SpvOpLabel, ButterflyLabel_PingPongTrue,\
		(6<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_StorageBufferPointer_struct_Atom, ButterflyVariable_StorageBufferPointer_struct_AtomPingPong0, ButterflyVariable_StorageBufferPointer_struct_AtomsPingPong0, ButterflyConstant_int32_0, ButterflyVLoadedVariable_int32_MatricesOffset,\
		(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_struct_Atom, ButterflyLoadedVariable_struct_AtomPingPong0, ButterflyVariable_StorageBufferPointer_struct_AtomPingPong0,\
		(3<<SpvWordCountShift)|SpvOpStore, ButterflyVariable_FunctionPointer_struct_Atom, ButterflyLoadedVariable_struct_AtomPingPong0,\
		(2<<SpvWordCountShift)|SpvOpBranch, ButterflyLabel_PingPongSelectionMerge,\
	(2<<SpvWordCountShift)|SpvOpLabel, ButterflyLabel_PingPongFalse,\
		(2<<SpvWordCountShift)|SpvOpBranch, ButterflyLabel_PingPongSelectionMerge,\
	(2<<SpvWordCountShift)|SpvOpLabel, ButterflyLabel_PingPongSelectionMerge,\
/*end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Draw Effect Element
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Draw_SimplifiedMolecular(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, ChemistryEffectSimplifiedMolecular* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers, PushConstantsGeometry* PushConstants)
{
	{
		VkBuffer vkBuffer = pGraphicsWindow->pLogicalDevice->SrcBuffer.VkBuffer;
		VkDeviceSize VkOffset = GPU_Buffers[0].Pointer + GPU_BufferPointers[0];
		GPU_BufferPointers[0] += sizeof(*pEffect->GPU_Atoms) * pEffect->GPU_AtomsSize;

		vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pEffect->VkPipelineAtom);

		PushConstantsSimplifiedMolecular PushConstantsSimplifiedMolecular;
		memset(&PushConstantsSimplifiedMolecular, NULL, sizeof(PushConstantsSimplifiedMolecular));
		glm_vec3_copy(pEffect->Position, PushConstantsSimplifiedMolecular.Position);
		uint8_t pushconstantbuffer[sizeof(PushConstantsSimplifiedMolecular) + sizeof(*PushConstants)];
		memcpy(pushconstantbuffer, PushConstants, sizeof(*PushConstants));
		memcpy((void*)((uint64_t)pushconstantbuffer + (uint64_t)sizeof(*PushConstants)), &PushConstantsSimplifiedMolecular, sizeof(PushConstantsSimplifiedMolecular));
		vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pGraphicsWindow->pLogicalDevice->PipelineLayout2D, VK_SHADER_STAGE_ALL, 0,
			pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, pushconstantbuffer);

		vkCmdBindVertexBuffers(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 0, 1, &vkBuffer, &VkOffset);

		vkCmdDraw(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 1, pEffect->GPU_AtomsSize, 0, 0);
	}
	{
		VkBuffer vkBuffer = pGraphicsWindow->pLogicalDevice->SrcBuffer.VkBuffer;
		VkDeviceSize VkOffset = GPU_Buffers[1].Pointer + GPU_BufferPointers[1];
		GPU_BufferPointers[1] += sizeof(GPU_CovalentBond) * pEffect->CovalentBondsSize;

		vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pEffect->VkPipelineCovalentBond);

		PushConstantsSimplifiedMolecular PushConstantsSimplifiedMolecular;
		memset(&PushConstantsSimplifiedMolecular, NULL, sizeof(PushConstantsSimplifiedMolecular));
		glm_vec3_copy(pEffect->Position, PushConstantsSimplifiedMolecular.Position);
		uint8_t pushconstantbuffer[sizeof(PushConstantsSimplifiedMolecular) + sizeof(*PushConstants)];
		memcpy(pushconstantbuffer, PushConstants, sizeof(*PushConstants));
		memcpy((void*)((uint64_t)pushconstantbuffer + (uint64_t)sizeof(*PushConstants)), &PushConstantsSimplifiedMolecular, sizeof(PushConstantsSimplifiedMolecular));
		vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pGraphicsWindow->pLogicalDevice->PipelineLayout2D, VK_SHADER_STAGE_ALL, 0,
			pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, pushconstantbuffer);

		vkCmdBindVertexBuffers(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 0, 1, &vkBuffer, &VkOffset);

		vkCmdDraw(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->CovalentBondsSize * 2, 1, 0, 0);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Update Effect Element
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Update_SimplifiedMolecular(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, ChemistryEffectSimplifiedMolecular* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
	if (GPU_Buffers == NULL)
	{
		GPU_BufferPointers[0] += sizeof(*pEffect->GPU_Atoms) * pEffect->GPU_AtomsSize;
		GPU_BufferPointers[1] += sizeof(GPU_CovalentBond) * pEffect->CovalentBondsSize;
	}
	else
	{	
		/*
		for (size_t i = 0; i < pEffect->GPU_AtomsSize; i++)
		{
			GPU_Atom* pAtom = &pEffect->GPU_Atoms[i];
			glm_vec3_add(pAtom->Position, pAtom->Velocity, pAtom->Position);

			for (size_t i1 = 0; i1 < pAtom->BondCount; i1++)
			{		
				uint32_t index = 0;
				if (i == pEffect->CovalentBonds[pAtom->BondIndices[i1]].AtomIndices[1])
					index = 1;

				glm_vec3_copy(pAtom->Position, pEffect->CovalentBonds[pAtom->BondIndices[i1]].Position[index]);
				glm_vec3_copy(pEffect->GPU_Atoms[pEffect->CovalentBonds[pAtom->BondIndices[i1]].AtomIndices[!index]].Position, pEffect->CovalentBonds[pAtom->BondIndices[i1]].Position[!index]);
				
				
				//float OxygenCarbonStrength = 10000.0021f;
				float OxygenCarbonDistance = 0.3f;
				//vec3 zero;
				//glm_vec3_zero(zero);
				//float linearvelocity = glm_vec3_distance(pAtom->Velocity, zero);

				//r = d - 2(d . n)n
				vec3 normal;
				glm_vec3_sub(pEffect->CovalentBonds[pAtom->BondIndices[i1]].Position[0], pEffect->CovalentBonds[pAtom->BondIndices[i1]].Position[1], normal);
				glm_vec3_normalize(normal);

				float dot = 2 * glm_dot(pAtom->Velocity, normal);
				vec3 d;
				glm_vec3_scale(normal, dot, d);
				glm_vec3_sub(pAtom->Velocity, d, pAtom->Velocity);

				glm_vec3_copy(pAtom->Position, pEffect->CovalentBonds[pAtom->BondIndices[i1]].Position[index]);
				glm_vec3_copy(pEffect->GPU_Atoms[pEffect->CovalentBonds[pAtom->BondIndices[i1]].AtomIndices[!index]].Position, pEffect->CovalentBonds[pAtom->BondIndices[i1]].Position[!index]);


				float reboundforce = (glm_vec3_distance(pAtom->Position, pEffect->GPU_Atoms[pEffect->CovalentBonds[pAtom->BondIndices[i1]].AtomIndices[!index]].Position) - OxygenCarbonDistance) * -1;
				reboundforce = reboundforce * 0.01;
				vec3 rebound;
				glm_vec3_sub(pAtom->Position, pEffect->GPU_Atoms[pEffect->CovalentBonds[pAtom->BondIndices[i1]].AtomIndices[!index]].Position, rebound);
				glm_vec3_scale(rebound, reboundforce, rebound);

				glm_vec3_add(pAtom->Position, rebound, pAtom->Position);


				glm_vec3_copy(pAtom->Position, pEffect->CovalentBonds[pAtom->BondIndices[i1]].Position[index]);
				glm_vec3_copy(pEffect->GPU_Atoms[pEffect->CovalentBonds[pAtom->BondIndices[i1]].AtomIndices[!index]].Position, pEffect->CovalentBonds[pAtom->BondIndices[i1]].Position[!index]);

				
				if (linearvelocity > OxygenCarbonStrength)
				{
					//break the bond
					RemoveMember_Array(&pEffect->CovalentBonds, pEffect->CovalentBondsSize, pAtom->BondIndices[i1], sizeof(*pEffect->CovalentBonds), 1);
					pEffect->CovalentBondsSize--;
				}
				
			}
		}

		for (size_t i = 0; i < pEffect->CovalentBondsSize; i++)
		{
			GPU_CovalentBond* pCovalentBond = ((uint64_t)pGraphicsWindow->pLogicalDevice->SrcBufPointer + GPU_Buffers[1].Pointer + GPU_BufferPointers[1]);
			GPU_BufferPointers[1] += sizeof(GPU_CovalentBond);
		
			glm_vec3_copy(pEffect->GPU_Atoms[pEffect->CovalentBonds[i].AtomIndices[1]].Position, pCovalentBond->Position[0]);
			glm_vec3_copy(pEffect->GPU_Atoms[pEffect->CovalentBonds[i].AtomIndices[0]].Position, pCovalentBond->Position[1]);

		}
		*/

		if (pEffect->GPU_AtomsSize != NULL)
		{
			memcpy((void*)((uint64_t)pGraphicsWindow->pLogicalDevice->SrcBufPointer + GPU_Buffers[0].Pointer + GPU_BufferPointers[0]),
				pEffect->GPU_Atoms, pEffect->GPU_AtomsSize * sizeof(*pEffect->GPU_Atoms));
		}
		GPU_BufferPointers[0] += sizeof(*pEffect->GPU_Atoms) * pEffect->GPU_AtomsSize;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Signataure Updates
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdateSignature_SimplifiedMolecular(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{



}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Destroy_SimplifiedMolecular(ElementGraphics* pElement, ChemistryEffectSimplifiedMolecular* pEffect, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);
	if (Full == true)
	{
		if (pEffect->GPU_Atoms != NULL)
			free(pEffect->GPU_Atoms);
		pEffect->GPU_Atoms = NULL;
		pEffect->GPU_AtomsSize = NULL;

		if (pEffect->CovalentBonds != NULL)
			free(pEffect->CovalentBonds);
		pEffect->CovalentBonds = NULL;
		pEffect->CovalentBondsSize = NULL;

		if (pEffect->VkPipelineAtom != NULL)
			vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineAtom, NULL);
		pEffect->VkPipelineAtom = NULL;

		if (pEffect->VkShaderVertexAtom != NULL)
			vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderVertexAtom, NULL);
		pEffect->VkShaderVertexAtom = NULL;
		if (pEffect->VkShaderFragmentAtom != NULL)
			vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderFragmentAtom, NULL);
		pEffect->VkShaderFragmentAtom = NULL;

		if (pEffect->VkPipelineCovalentBond != NULL)
			vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineCovalentBond, NULL);
		pEffect->VkPipelineCovalentBond = NULL;

		if (pEffect->VkShaderVertexCovalentBond != NULL)
			vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderVertexCovalentBond, NULL);
		pEffect->VkShaderVertexCovalentBond = NULL;
		if (pEffect->VkShaderFragmentCovalentBond != NULL)
			vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderFragmentCovalentBond, NULL);
		pEffect->VkShaderFragmentCovalentBond = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Recreation
/////////////////////////////////////////////////////////////////////////////////////////////a///////////////////////////////////////////////////

void ReCreate_SimplifiedMolecular(ElementGraphics* pElement, ChemistryEffectSimplifiedMolecular* pEffect, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_SimplifiedMolecular()", "pElement == NULLPTR");
		return;
	}
	if (pEffect == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_SimplifiedMolecular()", "pEffect == NULLPTR");
		return;
	}
#endif
	VkResult res = VK_SUCCESS;
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);

	VkPipelineMultisampleStateCreateInfo MultisampleState;
	memset(&MultisampleState, NULL, sizeof(MultisampleState));
	MultisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	MultisampleState.sampleShadingEnable = VK_FALSE;
	MultisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	MultisampleState.minSampleShading = 1.0f; // Optional
	MultisampleState.pSampleMask = NULL; // Optional
	MultisampleState.alphaToCoverageEnable = VK_FALSE; // Optional
	MultisampleState.alphaToOneEnable = VK_FALSE; // Optional

	VkPipelineColorBlendAttachmentState ColourBlendAttachment;
	memset(&ColourBlendAttachment, NULL, sizeof(ColourBlendAttachment));
	ColourBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	ColourBlendAttachment.blendEnable = VK_TRUE;
	ColourBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
	ColourBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	ColourBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	ColourBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	ColourBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_DST_ALPHA;
	ColourBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendAttachmentState ColourBlendAttachmentDeffered;
	memset(&ColourBlendAttachmentDeffered, NULL, sizeof(ColourBlendAttachmentDeffered));
	ColourBlendAttachmentDeffered.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	VkPipelineColorBlendAttachmentState attachments[4] = { ColourBlendAttachment, ColourBlendAttachment, ColourBlendAttachment, ColourBlendAttachment };
	VkPipelineColorBlendStateCreateInfo ColourBlending;
	memset(&ColourBlending, NULL, sizeof(ColourBlending));
	ColourBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	ColourBlending.attachmentCount = 2;
	ColourBlending.pAttachments = attachments;

	VkPipelineDepthStencilStateCreateInfo DepthStencil;
	memset(&DepthStencil, NULL, sizeof(DepthStencil));
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
	memset(&DynamicStates, NULL, sizeof(DynamicStates));
	DynamicStates.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	DynamicStates.dynamicStateCount = statesSize;
	DynamicStates.pDynamicStates = states;

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
	memset(&ViewportState, NULL, sizeof(ViewportState));
	ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	ViewportState.viewportCount = 1; //multi screeen~?!?!??!!?
	ViewportState.pViewports = &Viewport;
	ViewportState.scissorCount = 1;
	ViewportState.pScissors = &Scissor;

	{
		const SPIRV Vertex[] = VertexShaderSimplifiedMolecular();
		const SPIRV Fragment[] = FragmentShaderSimplifiedMolecular();

		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderVertexAtom, Vertex, VertexShaderSimplifiedMolecularSize, "ReCreate_SimplifiedMolecular()");
		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderFragmentAtom, Fragment, FragmentShaderSimplifiedMolecularSize, "ReCreate_SimplifiedMolecular()");

		uint32_t ShaderCount = 2;
		VkPipelineShaderStageCreateInfo ShaderStages[2];
		memset(ShaderStages, NULL, sizeof(*ShaderStages) * ShaderCount);
		ShaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		ShaderStages[0].module = pEffect->VkShaderVertexAtom;
		ShaderStages[0].pName = "main";

		ShaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		ShaderStages[1].module = pEffect->VkShaderFragmentAtom;
		ShaderStages[1].pName = "main";

		uint64_t InputBindingDescsSize = 1;
		VkVertexInputBindingDescription InputBindingDescs[1];
		uint64_t InputAttribDescsSize = 3;
		VkVertexInputAttributeDescription InputAttribDescs[3];

		//Buffer Binding Main
		InputBindingDescs[0].binding = 0;
		InputBindingDescs[0].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
		InputBindingDescs[0].stride = sizeof(GPU_Atom);

		//Attributes
		//position
		InputAttribDescs[0].binding = 0;
		InputAttribDescs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		InputAttribDescs[0].location = 0;
		InputAttribDescs[0].offset = offsetof(GPU_Atom, Position);
		//Colour
		InputAttribDescs[1].binding = 0;
		InputAttribDescs[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		InputAttribDescs[1].location = 1;
		InputAttribDescs[1].offset = offsetof(GPU_Atom, Colour);
		//ElementType
		InputAttribDescs[2].binding = 0;
		InputAttribDescs[2].format = VK_FORMAT_R32G32B32A32_SINT;
		InputAttribDescs[2].location = 2;
		InputAttribDescs[2].offset = offsetof(GPU_Atom, AtomElementType);

		//pipeline

		VkPipelineVertexInputStateCreateInfo VertexInputInfo;
		memset(&VertexInputInfo, NULL, sizeof(VertexInputInfo));
		VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		VertexInputInfo.vertexBindingDescriptionCount = (uint32_t)InputBindingDescsSize;
		VertexInputInfo.pVertexBindingDescriptions = InputBindingDescs; // Optional

		VertexInputInfo.vertexAttributeDescriptionCount = (uint32_t)InputAttribDescsSize;
		VertexInputInfo.pVertexAttributeDescriptions = InputAttribDescs; // Optional


		VkPipelineInputAssemblyStateCreateInfo InputAssemblyState;
		memset(&InputAssemblyState, NULL, sizeof(InputAssemblyState));
		InputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		InputAssemblyState.primitiveRestartEnable = VK_FALSE;

		VkPipelineRasterizationStateCreateInfo RasterizationState;
		memset(&RasterizationState, NULL, sizeof(RasterizationState));
		RasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		RasterizationState.depthClampEnable = VK_FALSE;
		RasterizationState.rasterizerDiscardEnable = VK_FALSE;
		RasterizationState.polygonMode = VK_POLYGON_MODE_POINT;
		RasterizationState.lineWidth = 1.0f;
		RasterizationState.cullMode = VK_CULL_MODE_NONE; //CULL MODE
		RasterizationState.frontFace = VK_FRONT_FACE_CLOCKWISE;
		RasterizationState.depthBiasEnable = VK_FALSE;
		RasterizationState.depthBiasConstantFactor = 0.0f; // Optional
		RasterizationState.depthBiasClamp = 0.0f; // Optional
		RasterizationState.depthBiasSlopeFactor = 0.0f; // Optional

		{
			VkGraphicsPipelineCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));

			Info.subpass = 0;
			ColourBlending.attachmentCount = 4;

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
			Info.layout = pGraphicsWindow->pLogicalDevice->PipelineLayout2D;
			Info.renderPass = pGraphicsWindow->VkDeferredRenderPass;
			//Info.subpass = 1;
			Info.basePipelineHandle = VK_NULL_HANDLE; // Optional
			Info.basePipelineIndex = -1; // Optional

			if ((res = vkCreateGraphicsPipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipelineAtom)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_Generic2D()", "vkCreateGraphicsPipelines Failed. VkResult == ", res);
				return;
			}
		}
	}


	{
		const SPIRV Vertex[] = VertexShaderCovalentBond();
		const SPIRV Fragment[] = FragmentShaderCovalentBond();

		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderVertexCovalentBond, Vertex, VertexShaderCovalentBondSize, "ReCreate_SimplifiedMolecular()");
		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderFragmentCovalentBond, Fragment, FragmentShaderCovalentBondSize, "ReCreate_SimplifiedMolecular()");

		uint32_t ShaderCount = 2;
		VkPipelineShaderStageCreateInfo ShaderStages[2];
		memset(ShaderStages, NULL, sizeof(*ShaderStages)* ShaderCount);
		ShaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		ShaderStages[0].module = pEffect->VkShaderVertexCovalentBond;
		ShaderStages[0].pName = "main";

		ShaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		ShaderStages[1].module = pEffect->VkShaderFragmentCovalentBond;
		ShaderStages[1].pName = "main";

		uint64_t InputBindingDescsSize = 1;
		VkVertexInputBindingDescription InputBindingDescs[1];
		uint64_t InputAttribDescsSize = 1;
		VkVertexInputAttributeDescription InputAttribDescs[1];

		//Buffer Binding Main
		InputBindingDescs[0].binding = 0;
		InputBindingDescs[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		InputBindingDescs[0].stride = sizeof(vec3);

		//Attributes
		//position
		InputAttribDescs[0].binding = 0;
		InputAttribDescs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		InputAttribDescs[0].location = 0;
		InputAttribDescs[0].offset = 0;

		//pipeline
		VkPipelineVertexInputStateCreateInfo VertexInputInfo;
		memset(&VertexInputInfo, NULL, sizeof(VertexInputInfo));
		VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		VertexInputInfo.vertexBindingDescriptionCount = (uint32_t)InputBindingDescsSize;
		VertexInputInfo.pVertexBindingDescriptions = InputBindingDescs; // Optional

		VertexInputInfo.vertexAttributeDescriptionCount = (uint32_t)InputAttribDescsSize;
		VertexInputInfo.pVertexAttributeDescriptions = InputAttribDescs; // Optional

		VkPipelineInputAssemblyStateCreateInfo InputAssemblyState;
		memset(&InputAssemblyState, NULL, sizeof(InputAssemblyState));
		InputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		InputAssemblyState.primitiveRestartEnable = VK_FALSE;

		VkPipelineRasterizationStateCreateInfo RasterizationState;
		memset(&RasterizationState, NULL, sizeof(RasterizationState));
		RasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		RasterizationState.depthClampEnable = VK_FALSE;
		RasterizationState.rasterizerDiscardEnable = VK_FALSE;
		RasterizationState.polygonMode = VK_POLYGON_MODE_LINE;
		RasterizationState.lineWidth = 1.0f;
		RasterizationState.cullMode = VK_CULL_MODE_NONE; //CULL MODE
		RasterizationState.frontFace = VK_FRONT_FACE_CLOCKWISE;
		RasterizationState.depthBiasEnable = VK_FALSE;
		RasterizationState.depthBiasConstantFactor = 0.0f; // Optional
		RasterizationState.depthBiasClamp = 0.0f; // Optional
		RasterizationState.depthBiasSlopeFactor = 0.0f; // Optional

		{
			VkGraphicsPipelineCreateInfo Info;
			memset(&Info, NULL, sizeof(Info));

			Info.subpass = 0;
			ColourBlending.attachmentCount = 4;

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
			Info.layout = pGraphicsWindow->pLogicalDevice->PipelineLayout2D;
			Info.renderPass = pGraphicsWindow->VkDeferredRenderPass;
			//Info.subpass = 1;
			Info.basePipelineHandle = VK_NULL_HANDLE; // Optional
			Info.basePipelineIndex = -1; // Optional

			if ((res = vkCreateGraphicsPipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipelineCovalentBond)) != VK_SUCCESS)
			{
				Engine_Ref_FunctionError("ReCreate_Generic2D()", "vkCreateGraphicsPipelines Failed. VkResult == ", res);
				return;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Packers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Pack_SimplifiedMolecular(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const ChemistryEffectSimplifiedMolecular* pEffect, ChemistryEffectSimplifiedMolecular* pCopiedEffect, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedEffect->VkPipelineAtom, NULL, sizeof(pCopiedEffect->VkPipelineAtom));
		memset(&pCopiedEffect->VkShaderVertexAtom, NULL, sizeof(pCopiedEffect->VkShaderVertexAtom));
		memset(&pCopiedEffect->VkShaderFragmentAtom, NULL, sizeof(pCopiedEffect->VkShaderFragmentAtom));

		memset(&pCopiedEffect->VkPipelineCovalentBond, NULL, sizeof(pCopiedEffect->VkPipelineCovalentBond));
		memset(&pCopiedEffect->VkShaderVertexCovalentBond, NULL, sizeof(pCopiedEffect->VkShaderVertexCovalentBond));
		memset(&pCopiedEffect->VkShaderFragmentCovalentBond, NULL, sizeof(pCopiedEffect->VkShaderFragmentCovalentBond));


		if (pEffect->GPU_Atoms != NULL)
		{
			memcpy(((void*)((uint64_t)pData + (uint64_t)*pBufferPointer)), pEffect->GPU_Atoms, pEffect->GPU_AtomsSize * sizeof(*pEffect->GPU_Atoms));
			pCopiedEffect->GPU_Atoms = (UTF8*)*pBufferPointer;
			*pBufferPointer += pEffect->GPU_AtomsSize * sizeof(*pEffect->GPU_Atoms);
		}

		if (pEffect->CovalentBonds != NULL)
		{
			memcpy(((void*)((uint64_t)pData + (uint64_t)*pBufferPointer)), pEffect->CovalentBonds, pEffect->CovalentBondsSize * sizeof(*pEffect->CovalentBonds));
			pCopiedEffect->CovalentBonds = (UTF8*)*pBufferPointer;
			*pBufferPointer += pEffect->CovalentBondsSize * sizeof(*pEffect->CovalentBonds);
		}
	}
	else
	{
		*pBufferPointer += pEffect->GPU_AtomsSize * sizeof(*pEffect->GPU_Atoms);

		*pBufferPointer += pEffect->CovalentBondsSize * sizeof(*pEffect->CovalentBonds);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect UnPackers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UnPack_SimplifiedMolecular(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const ChemistryEffectSimplifiedMolecular* pEffect, ChemistryEffectSimplifiedMolecular* pCopiedEffect, const void* pData, uint32_t ThreadIndex)
{
	if (pEffect->GPU_Atoms != NULL)
	{
		pCopiedEffect->GPU_Atoms = (UTF8*)calloc(pCopiedEffect->GPU_AtomsSize, sizeof(*pCopiedEffect->GPU_Atoms));
		memcpy(pCopiedEffect->GPU_Atoms, ((void*)((uint64_t)pData + (uint64_t)pEffect->GPU_Atoms)), pEffect->GPU_AtomsSize * sizeof(*pEffect->GPU_Atoms));
	}

	if (pEffect->CovalentBonds != NULL)
	{
		pCopiedEffect->CovalentBonds = (UTF8*)calloc(pCopiedEffect->CovalentBondsSize, sizeof(*pCopiedEffect->CovalentBonds));
		memcpy(pCopiedEffect->CovalentBonds, ((void*)((uint64_t)pData + (uint64_t)pEffect->CovalentBonds)), pEffect->CovalentBondsSize * sizeof(*pEffect->CovalentBonds));
	}

	ReCreate_SimplifiedMolecular(pCopiedElement, pCopiedEffect, ThreadIndex);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_SimplifiedMolecular(ElementGraphics* pElement, ChemistryEffectSimplifiedMolecular* EffectInfo, ChemistryEffectCreateInfoSimplifiedMolecular* EffectCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (EffectInfo == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (EffectCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_SimplifiedMolecular()", "EffectCreateInfo == NULLPTR");
			return (TEXRESULT)Invalid_Parameter;
		}
#endif
		glm_vec3_copy(EffectCreateInfo->Position, EffectInfo->Position);

		if (EffectCreateInfo->AtomsSize != NULL)
		{
			EffectInfo->GPU_AtomsSize = EffectCreateInfo->AtomsSize;
			EffectInfo->GPU_Atoms = calloc(EffectInfo->GPU_AtomsSize, sizeof(*EffectInfo->GPU_Atoms));
			memcpy(EffectInfo->GPU_Atoms, EffectCreateInfo->Atoms, EffectInfo->GPU_AtomsSize * sizeof(*EffectInfo->GPU_Atoms));
		}
		
		if (EffectCreateInfo->CovalentBonds != NULL)
		{
			EffectInfo->CovalentBondsSize = EffectCreateInfo->CovalentBondsSize;
			EffectInfo->CovalentBonds = calloc(EffectInfo->CovalentBondsSize, sizeof(*EffectInfo->CovalentBonds));
			memcpy(EffectInfo->CovalentBonds, EffectCreateInfo->CovalentBonds, EffectInfo->CovalentBondsSize * sizeof(*EffectInfo->CovalentBonds));
		}
		
		ReCreate_SimplifiedMolecular(pElement, EffectInfo, ThreadIndex);
	}
	*pAllocationSize = sizeof(ChemistryEffectSimplifiedMolecular);
	return (TEXRESULT)Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Initialise_Chemistry()
{
	Utils.SimplifiedMolecularSignature.Identifier = (uint32_t)ChemistryEffects_SimplifiedMolecular;
	Utils.SimplifiedMolecularSignature.Constructor = (Create_GraphicsEffectTemplate*)&Create_SimplifiedMolecular;
	Utils.SimplifiedMolecularSignature.ReConstructor = (ReCreate_GraphicsEffectTemplate*)&ReCreate_SimplifiedMolecular;
	Utils.SimplifiedMolecularSignature.Destructor = (Destroy_GraphicsEffectTemplate*)&Destroy_SimplifiedMolecular;
	Utils.SimplifiedMolecularSignature.Packer = (Pack_GraphicsEffectTemplate*)&Pack_SimplifiedMolecular;
	Utils.SimplifiedMolecularSignature.UnPacker = (UnPack_GraphicsEffectTemplate*)&UnPack_SimplifiedMolecular;
	Utils.SimplifiedMolecularSignature.Update = (Update_GraphicsEffectTemplate*)&Update_SimplifiedMolecular;
	Utils.SimplifiedMolecularSignature.Draw = (Draw_GraphicsEffectTemplate*)&Draw_SimplifiedMolecular;
	Utils.SimplifiedMolecularSignature.UpdateSignature = &UpdateSignature_SimplifiedMolecular;
	Utils.SimplifiedMolecularSignature.SignatureGPUBuffersSize = 2; //paramatom
	Graphics_Effects_Ref_Register_GraphicsEffectSignature(&Utils.SimplifiedMolecularSignature);

	return (TEXRESULT)(Success);
}

void Destroy_Chemistry()
{

}

void Update_Chemistry()
{	
	
}

//entry poin t to the extension
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
	//Audio_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	Graphics_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	//Network_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	//GUI_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	//Formats_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);

	//exports
	//Resources
	ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData((void*)"Chemistry::Utils"), &ChemistryRes.pUtils, &Utils);

	//functions
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chemistry::Initialise_Chemistry"), &ChemistryRes.pInitialise_Chemistry, &Initialise_Chemistry, Construct, Single_Thread, 1000.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chemistry::Destroy_Chemistry"), &ChemistryRes.pDestroy_Chemistry, &Destroy_Chemistry, Destruct, Single_Thread, 0.001f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chemistry::Update_Chemistry"), &ChemistryRes.pUpdate_Chemistry, &Update_Chemistry, EveryFrame, Single_Thread, 0.1f, 0, NULL);


}


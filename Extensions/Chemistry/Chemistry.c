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

	//BASIC TYPES
	VertexSimplifiedMolecularType_Void,
	VertexSimplifiedMolecularType_Function,

	VertexSimplifiedMolecularType_float32,
	VertexSimplifiedMolecularType_float32vec2,
	VertexSimplifiedMolecularType_float32vec3,
	VertexSimplifiedMolecularType_float32vec4,
	VertexSimplifiedMolecularType_float32mat4,

	VertexSimplifiedMolecularType_int32,

	//CONSTANTS
	VertexSimplifiedMolecularConstant_float32_0f,
	VertexSimplifiedMolecularConstant_float32_1f,

	VertexSimplifiedMolecularConstant_int_0,
	VertexSimplifiedMolecularConstant_int_1,

	//INPUT
	//Input Attributes
	VertexSimplifiedMolecularType_InputPointer_float32,
	VertexSimplifiedMolecularType_InputPointer_float32vec3,
	VertexSimplifiedMolecularType_InputPointer_float32vec4,

	VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Position,
	VertexSimplifiedMolecularVariable_InputPointer_float32vec3_PositionVelocity,
	VertexSimplifiedMolecularVariable_InputPointer_float32vec4_Rotation,
	VertexSimplifiedMolecularVariable_InputPointer_float32vec4_RotationVelocity,
	VertexSimplifiedMolecularVariable_InputPointer_float32_Size,
	//BuiltIn
	VertexSimplifiedMolecularType_InputPointer_int32,
	VertexSimplifiedMolecularVariable_InputPointer_VertexIndex,
	VertexSimplifiedMolecularVariable_InputPointer_InstanceIndex,
	//PushConstants
	VertexSimplifiedMolecularType_struct_PushConstants,
	VertexSimplifiedMolecularType_PushConstantPointer_struct_PushConstants,
	VertexSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants,
	VertexSimplifiedMolecularType_PushConstantPointer_float32mat4,

	//OUTPUT
	//Output Attributes
	VertexSimplifiedMolecularType_OutputPointer_float32,
	VertexSimplifiedMolecularType_OutputPointer_float32vec3,
	VertexSimplifiedMolecularType_OutputPointer_float32vec4,

	VertexSimplifiedMolecularConstant_float32vec3_NULL,
	VertexSimplifiedMolecularConstant_float32vec4_NULL,

	VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Position,
	VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_PositionVelocity,
	VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_Rotation,
	VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_RotationVelocity,
	VertexSimplifiedMolecularVariable_OutputPointer_float32_Size,
	//BuiltIn
	VertexSimplifiedMolecularType_float32_Array_1,
	VertexSimplifiedMolecularType_struct_BuiltIn,
	VertexSimplifiedMolecularType_OutputPointer_struct_BuiltIn,
	VertexSimplifiedMolecularVariable_OutputPointer_struct_BuiltIn,
	VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_Position,
	VertexSimplifiedMolecularVariable_OutputPointer_float32_PointSize,

	//MAIN FUNCTION
	VertexSimplifiedMolecularLabel_Start,

	VertexSimplifiedMolecularVariable_PushConstantPointer_MatrixVP,
	VertexSimplifiedMolecularLoadedVariable_PushConstantPointer_MatrixVP,


	VertexSimplifiedMolecularLoadedVariable_float32vec3_Position,
	VertexSimplifiedMolecularLoadedVariable_float32vec3_PositionVelocity,
	VertexSimplifiedMolecularLoadedVariable_float32vec4_Rotation,
	VertexSimplifiedMolecularLoadedVariable_float32vec4_RotationVelocity,
	VertexSimplifiedMolecularLoadedVariable_float32_Size,


	VertexSimplifiedMolecularLoadedVariable_float32vec2_op0,
	VertexSimplifiedMolecularLoadedVariable_float32vec4_op0,
	VertexSimplifiedMolecularLoadedVariable_float32vec4_op1,

	VertexSimplifiedMolecularLoadedVariable_float32_op0,
	VertexSimplifiedMolecularLoadedVariable_float32_op1,

	VertexSimplifiedMolecularVariables_MAX
}VertexShaderSimplifiedMolecularVariables;
#define VertexShaderSimplifiedMolecularSize (395 * sizeof(SPIRV))
#define VertexShaderSimplifiedMolecular() {\
SPIRV_Header(VertexSimplifiedMolecularVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, VertexSimplifiedMolecularExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(19<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelVertex, VertexSimplifiedMolecularFunction_Main, 'niam', '\0',\
VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Position, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_PositionVelocity, VertexSimplifiedMolecularVariable_InputPointer_float32vec4_Rotation, VertexSimplifiedMolecularVariable_InputPointer_float32vec4_RotationVelocity, VertexSimplifiedMolecularVariable_InputPointer_float32_Size,\
VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Position, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_PositionVelocity, VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_Rotation, VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_RotationVelocity, VertexSimplifiedMolecularVariable_OutputPointer_float32_Size,\
VertexSimplifiedMolecularVariable_InputPointer_VertexIndex, VertexSimplifiedMolecularVariable_InputPointer_InstanceIndex, VertexSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants, VertexSimplifiedMolecularVariable_OutputPointer_struct_BuiltIn,\
/*DECORATION*/\
/*INPUT*/\
/*Input Attributes*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Position, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_PositionVelocity, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_float32vec4_Rotation, SpvDecorationLocation, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_float32vec4_RotationVelocity, SpvDecorationLocation, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_float32_Size, SpvDecorationLocation, 4,\
/*BuiltIn*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_VertexIndex, SpvDecorationBuiltIn, SpvBuiltInVertexIndex,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_InputPointer_InstanceIndex, SpvDecorationBuiltIn, SpvBuiltInInstanceIndex,\
/*PushConstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimplifiedMolecularType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
/*Output Attributes*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Position, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_PositionVelocity, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_Rotation, SpvDecorationLocation, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_RotationVelocity, SpvDecorationLocation, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimplifiedMolecularVariable_OutputPointer_float32_Size, SpvDecorationLocation, 4,\
/*BuiltIn*/\
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
/*INPUT*/\
/*PushConstants*/\
(4<<SpvWordCountShift)|SpvOpTypeStruct, VertexSimplifiedMolecularType_struct_PushConstants, VertexSimplifiedMolecularType_float32mat4, VertexSimplifiedMolecularType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, VertexSimplifiedMolecularType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_PushConstantPointer_struct_PushConstants, VertexSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_PushConstantPointer_float32mat4, SpvStorageClassPushConstant, VertexSimplifiedMolecularType_float32mat4,\
/*BuiltIn*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_InputPointer_int32, SpvStorageClassInput, VertexSimplifiedMolecularType_int32,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_int32, VertexSimplifiedMolecularVariable_InputPointer_VertexIndex, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_int32, VertexSimplifiedMolecularVariable_InputPointer_InstanceIndex, SpvStorageClassInput,\
/*Input Attributes*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_InputPointer_float32, SpvStorageClassInput, VertexSimplifiedMolecularType_float32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_InputPointer_float32vec3, SpvStorageClassInput, VertexSimplifiedMolecularType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_InputPointer_float32vec4, SpvStorageClassInput, VertexSimplifiedMolecularType_float32vec4,\
\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_float32vec3, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Position, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_float32vec3, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_PositionVelocity, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_float32vec4, VertexSimplifiedMolecularVariable_InputPointer_float32vec4_Rotation, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_float32vec4, VertexSimplifiedMolecularVariable_InputPointer_float32vec4_RotationVelocity, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_InputPointer_float32, VertexSimplifiedMolecularVariable_InputPointer_float32_Size, SpvStorageClassInput,\
/*OUTPUT*/\
/*Output Attributes*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_OutputPointer_float32, SpvStorageClassOutput, VertexSimplifiedMolecularType_float32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_OutputPointer_float32vec3, SpvStorageClassOutput, VertexSimplifiedMolecularType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_OutputPointer_float32vec4, SpvStorageClassOutput, VertexSimplifiedMolecularType_float32vec4,\
\
(3<<SpvWordCountShift)|SpvOpConstantNull, VertexSimplifiedMolecularType_float32vec3, VertexSimplifiedMolecularConstant_float32vec3_NULL,\
(3<<SpvWordCountShift)|SpvOpConstantNull, VertexSimplifiedMolecularType_float32vec4, VertexSimplifiedMolecularConstant_float32vec4_NULL,\
\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_OutputPointer_float32vec3, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Position, SpvStorageClassOutput, VertexSimplifiedMolecularConstant_float32vec3_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_OutputPointer_float32vec3, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_PositionVelocity, SpvStorageClassOutput, VertexSimplifiedMolecularConstant_float32vec3_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_OutputPointer_float32vec4, VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_Rotation, SpvStorageClassOutput, VertexSimplifiedMolecularConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_OutputPointer_float32vec4, VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_RotationVelocity, SpvStorageClassOutput, VertexSimplifiedMolecularConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_OutputPointer_float32, VertexSimplifiedMolecularVariable_OutputPointer_float32_Size, SpvStorageClassOutput, VertexSimplifiedMolecularConstant_float32_0f,\
/*BuiltIn*/\
(4<<SpvWordCountShift)|SpvOpTypeArray, VertexSimplifiedMolecularType_float32_Array_1, VertexSimplifiedMolecularType_float32, VertexSimplifiedMolecularConstant_int_1,\
(6<<SpvWordCountShift)|SpvOpTypeStruct, VertexSimplifiedMolecularType_struct_BuiltIn, VertexSimplifiedMolecularType_float32vec4, VertexSimplifiedMolecularType_float32, VertexSimplifiedMolecularType_float32_Array_1, VertexSimplifiedMolecularType_float32_Array_1,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimplifiedMolecularType_OutputPointer_struct_BuiltIn, SpvStorageClassOutput, VertexSimplifiedMolecularType_struct_BuiltIn,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimplifiedMolecularType_OutputPointer_struct_BuiltIn, VertexSimplifiedMolecularVariable_OutputPointer_struct_BuiltIn, SpvStorageClassOutput,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, VertexSimplifiedMolecularType_Void, VertexSimplifiedMolecularFunction_Main, SpvFunctionControlMaskNone, VertexSimplifiedMolecularType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, VertexSimplifiedMolecularLabel_Start,\
	/*Assign inputs to outputs and also load variables*/\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimplifiedMolecularType_float32vec3, VertexSimplifiedMolecularLoadedVariable_float32vec3_Position, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_Position,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_Position, VertexSimplifiedMolecularLoadedVariable_float32vec3_Position,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimplifiedMolecularType_float32vec3, VertexSimplifiedMolecularLoadedVariable_float32vec3_PositionVelocity, VertexSimplifiedMolecularVariable_InputPointer_float32vec3_PositionVelocity,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimplifiedMolecularVariable_OutputPointer_float32vec3_PositionVelocity, VertexSimplifiedMolecularLoadedVariable_float32vec3_PositionVelocity,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimplifiedMolecularType_float32vec4, VertexSimplifiedMolecularLoadedVariable_float32vec4_Rotation, VertexSimplifiedMolecularVariable_InputPointer_float32vec4_Rotation,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_Rotation, VertexSimplifiedMolecularLoadedVariable_float32vec4_Rotation,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimplifiedMolecularType_float32vec4, VertexSimplifiedMolecularLoadedVariable_float32vec4_RotationVelocity, VertexSimplifiedMolecularVariable_InputPointer_float32vec4_RotationVelocity,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimplifiedMolecularVariable_OutputPointer_float32vec4_RotationVelocity, VertexSimplifiedMolecularLoadedVariable_float32vec4_RotationVelocity,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimplifiedMolecularType_float32, VertexSimplifiedMolecularLoadedVariable_float32_Size, VertexSimplifiedMolecularVariable_InputPointer_float32_Size,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimplifiedMolecularVariable_OutputPointer_float32_Size, VertexSimplifiedMolecularLoadedVariable_float32_Size,\
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
	(6<<SpvWordCountShift)|SpvOpExtInst, VertexSimplifiedMolecularType_float32, VertexSimplifiedMolecularLoadedVariable_float32_op0, VertexSimplifiedMolecularExtension_GLSL450, 31, VertexSimplifiedMolecularLoadedVariable_float32_Size,\
	(6<<SpvWordCountShift)|SpvOpExtInst, VertexSimplifiedMolecularType_float32, VertexSimplifiedMolecularLoadedVariable_float32_op1, VertexSimplifiedMolecularExtension_GLSL450, 31, VertexSimplifiedMolecularLoadedVariable_float32_op0,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimplifiedMolecularVariable_OutputPointer_float32_PointSize, VertexSimplifiedMolecularLoadedVariable_float32_op1,\
/*function end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

typedef enum FragmentShaderSimplifiedMolecularVariables {
	FragmentSimplifiedMolecularExtension_GLSL450 = 1,
	FragmentSimplifiedMolecularFunction_Main,

	//BASIC TYPES
	FragmentSimplifiedMolecularType_Void,
	FragmentSimplifiedMolecularType_Function,

	FragmentSimplifiedMolecularType_float32,
	FragmentSimplifiedMolecularType_float32vec2,
	FragmentSimplifiedMolecularType_float32vec3,
	FragmentSimplifiedMolecularType_float32vec4,
	FragmentSimplifiedMolecularType_float32mat4,

	FragmentSimplifiedMolecularType_int32,

	//CONSTANTS
	FragmentSimplifiedMolecularConstant_float32_0f,
	FragmentSimplifiedMolecularConstant_float32_1f,

	FragmentSimplifiedMolecularConstant_int32_0,

	//INPUT
	//Input Attributes
	FragmentSimplifiedMolecularType_InputPointer_float32,
	FragmentSimplifiedMolecularType_InputPointer_float32vec3,
	FragmentSimplifiedMolecularType_InputPointer_float32vec4,

	FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Position,
	FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_PositionVelocity,
	FragmentSimplifiedMolecularVariable_InputPointer_float32vec4_Rotation,
	FragmentSimplifiedMolecularVariable_InputPointer_float32vec4_RotationVelocity,
	FragmentSimplifiedMolecularVariable_InputPointer_float32_Size,

	//PushConstants
	FragmentSimplifiedMolecularType_struct_PushConstants,
	FragmentSimplifiedMolecularType_PushConstantPointer_struct_PushConstants,
	FragmentSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants,
	FragmentSimplifiedMolecularType_PushConstantPointer_int32,

	//OUTPUT
	//Subpass Attachments
	FragmentSimplifiedMolecularType_OutputPointer_float32vec4,
	FragmentSimplifiedMolecularConstant_float32vec4_NULL,
	FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,
	FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutPositionOrRevealage,

	FragmentSimplifiedMolecularConstantComposite_float32vec4_SelectedColour,

	//MAIN FUNCTION
	FragmentSimplifiedMolecularLabel_Start,

	FragmentSimplifiedMolecularLoadedVariable_float32vec4_op0,

	FragmentSimplifiedMolecularVariables_MAX
}FragmentShaderSimplifiedMolecularVariables;
#define FragmentShaderSimplifiedMolecularSize (216 * sizeof(SPIRV))
#define FragmentShaderSimplifiedMolecular() {\
SPIRV_Header(FragmentSimplifiedMolecularVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityImageQuery,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, FragmentSimplifiedMolecularExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(13<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelFragment, FragmentSimplifiedMolecularFunction_Main, 'niam', '\0',\
FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Position, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_PositionVelocity, FragmentSimplifiedMolecularVariable_InputPointer_float32vec4_Rotation, FragmentSimplifiedMolecularVariable_InputPointer_float32vec4_RotationVelocity, FragmentSimplifiedMolecularVariable_InputPointer_float32_Size,\
FragmentSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutPositionOrRevealage,\
(3<<SpvWordCountShift)|SpvOpExecutionMode, FragmentSimplifiedMolecularFunction_Main, SpvExecutionModeOriginUpperLeft,\
/*DECORATION*/\
/*INPUT*/\
/*Input Attributes*/\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Position, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_PositionVelocity, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularVariable_InputPointer_float32vec4_Rotation, SpvDecorationLocation, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularVariable_InputPointer_float32vec4_RotationVelocity, SpvDecorationLocation, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularVariable_InputPointer_float32_Size, SpvDecorationLocation, 4,\
/*PushConstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, 2, SpvDecorationOffset, 68,\
(3<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
/*Output Attributes*/\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvDecorationLocation, 1,\
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
/*INPUT*/\
/*Input Attributes*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimplifiedMolecularType_InputPointer_float32, SpvStorageClassInput, FragmentSimplifiedMolecularType_float32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimplifiedMolecularType_InputPointer_float32vec3, SpvStorageClassInput, FragmentSimplifiedMolecularType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimplifiedMolecularType_InputPointer_float32vec4, SpvStorageClassInput, FragmentSimplifiedMolecularType_float32vec4,\
\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_InputPointer_float32vec3, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_Position, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_InputPointer_float32vec3, FragmentSimplifiedMolecularVariable_InputPointer_float32vec3_PositionVelocity, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_InputPointer_float32vec4, FragmentSimplifiedMolecularVariable_InputPointer_float32vec4_Rotation, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_InputPointer_float32vec4, FragmentSimplifiedMolecularVariable_InputPointer_float32vec4_RotationVelocity, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_InputPointer_float32, FragmentSimplifiedMolecularVariable_InputPointer_float32_Size, SpvStorageClassInput,\
/*PushConstants*/\
(5<<SpvWordCountShift)|SpvOpTypeStruct, FragmentSimplifiedMolecularType_struct_PushConstants, FragmentSimplifiedMolecularType_float32mat4, FragmentSimplifiedMolecularType_int32, FragmentSimplifiedMolecularType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimplifiedMolecularType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, FragmentSimplifiedMolecularType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_PushConstantPointer_struct_PushConstants, FragmentSimplifiedMolecularVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimplifiedMolecularType_PushConstantPointer_int32, SpvStorageClassPushConstant, FragmentSimplifiedMolecularType_int32,\
/*OUTPUT*/\
/*Output Attributes*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimplifiedMolecularType_OutputPointer_float32vec4, SpvStorageClassOutput, FragmentSimplifiedMolecularType_float32vec4,\
\
(3<<SpvWordCountShift)|SpvOpConstantNull, FragmentSimplifiedMolecularType_float32vec4, FragmentSimplifiedMolecularConstant_float32vec4_NULL,\
\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_OutputPointer_float32vec4, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvStorageClassOutput, FragmentSimplifiedMolecularConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentSimplifiedMolecularType_OutputPointer_float32vec4, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvStorageClassOutput, FragmentSimplifiedMolecularConstant_float32vec4_NULL,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, FragmentSimplifiedMolecularType_Void, FragmentSimplifiedMolecularFunction_Main, SpvFunctionControlMaskNone, FragmentSimplifiedMolecularType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, FragmentSimplifiedMolecularLabel_Start,\
	/*Output Default Colour*/\
	(7<<SpvWordCountShift)|SpvOpCompositeConstruct, FragmentSimplifiedMolecularType_float32vec4, FragmentSimplifiedMolecularLoadedVariable_float32vec4_op0, FragmentSimplifiedMolecularConstant_float32_1f, FragmentSimplifiedMolecularConstant_float32_1f, FragmentSimplifiedMolecularConstant_float32_1f, FragmentSimplifiedMolecularConstant_float32_1f,\
	(3<<SpvWordCountShift)|SpvOpStore, FragmentSimplifiedMolecularVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, FragmentSimplifiedMolecularLoadedVariable_float32vec4_op0,\
/*function end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd\
}


typedef enum VertexShaderCovalentBondVariables {
	VertexCovalentBondExtension_GLSL450 = 1,
	VertexCovalentBondFunction_Main,

	//BASIC TYPES
	VertexCovalentBondType_Void,
	VertexCovalentBondType_Function,
	VertexCovalentBondType_bool,

	VertexCovalentBondType_float32,
	VertexCovalentBondType_float32vec2,
	VertexCovalentBondType_float32vec3,
	VertexCovalentBondType_float32vec4,
	VertexCovalentBondType_float32mat4,

	VertexCovalentBondType_int32,

	//CONSTANTS
	VertexCovalentBondConstant_float32_0f,
	VertexCovalentBondConstant_float32_1f,

	VertexCovalentBondConstant_int_0,
	VertexCovalentBondConstant_int_1,

	VertexCovalentBondConstant_float32vec3_NULL,

	//INPUT
	//Input Attributes
	VertexCovalentBondType_InputPointer_float32vec3,
	VertexCovalentBondVariable_InputPointer_float32vec3_Position,
	//BuiltIn
	VertexCovalentBondType_InputPointer_int32,
	VertexCovalentBondVariable_InputPointer_VertexIndex,
	VertexCovalentBondVariable_InputPointer_InstanceIndex,
	//PushConstants
	VertexCovalentBondType_struct_PushConstants,
	VertexCovalentBondType_PushConstantPointer_struct_PushConstants,
	VertexCovalentBondVariable_PushConstantPointer_struct_PushConstants,
	VertexCovalentBondType_PushConstantPointer_float32mat4,

	//OUTPUT
	//BuiltIn
	VertexCovalentBondType_OutputPointer_float32vec4,
	VertexCovalentBondType_OutputPointer_float32,
	VertexCovalentBondType_float32_Array_1,
	VertexCovalentBondType_struct_BuiltIn,
	VertexCovalentBondType_OutputPointer_struct_BuiltIn,
	VertexCovalentBondVariable_OutputPointer_struct_BuiltIn,
	VertexCovalentBondVariable_OutputPointer_float32vec4_Position,
	VertexCovalentBondVariable_OutputPointer_float32_PointSize,


	//MAIN FUNCTION
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

	//BASIC TYPES
	FragmentCovalentBondType_Void,
	FragmentCovalentBondType_Function,

	FragmentCovalentBondType_float32,
	FragmentCovalentBondType_float32vec4,
	FragmentCovalentBondType_float32mat4,

	FragmentCovalentBondType_int32,

	//CONSTANTS
	FragmentCovalentBondConstant_float32_0f,
	FragmentCovalentBondConstant_float32_1f,
	FragmentCovalentBondConstant_float32vec4_1f_1f_1f_1f,

	//INPUT
	//PushConstants
	FragmentCovalentBondType_struct_PushConstants,
	FragmentCovalentBondType_PushConstantPointer_struct_PushConstants,
	FragmentCovalentBondVariable_PushConstantPointer_struct_PushConstants,
	FragmentCovalentBondType_PushConstantPointer_int32,

	//OUTPUT
	//Subpass Attachments
	FragmentCovalentBondType_OutputPointer_float32vec4,
	FragmentCovalentBondConstant_float32vec4_NULL,
	FragmentCovalentBondVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,
	FragmentCovalentBondVariable_OutputPointer_float32vec4_OutPositionOrRevealage,

	FragmentCovalentBondConstantComposite_float32vec4_SelectedColour,

	//MAIN FUNCTION
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




typedef enum ComputeShaderButterflyVariables {
	ButterflyVariable_ExtInstGLSL450 = 1,
	ButterflyFunction_Main,

	//BASIC TYPES
	ButterflyType_Void,
	ButterflyType_Function,
	ButterflyType_bool,

	ButterflyType_float32,
	ButterflyType_float32vec2,
	ButterflyType_float32vec3,
	ButterflyType_float32vec4,

	ButterflyType_int32,
	ButterflyType_int32vec2,
	ButterflyType_int32vec3,

	//CONSTANTS
	ButterflyConstant_float32_0,
	ButterflyConstant_float32_7,

	ButterflyConstant_int32_N1,
	ButterflyConstant_int32_0,
	ButterflyConstant_int32_1,
	ButterflyConstant_int32_2,

	//INPUT
	//PushConstants
	ButterflyType_struct_PushConstants,
	ButterflyType_PushConstantPointer_struct_PushConstants,
	ButterflyVariable_PushConstantPointer_struct_PushConstants,
	ButterflyType_PushConstantPointer_int32,
	//BuiltIn
	ButterflyType_InputPointer_int32vec3,
	ButterflyVariable_InputPointer_int32vec3_BuiltInInvocationID,
	ButterflyType_InputPointer_int32,
	//StorageBuffer GPU_Particles
	ButterflyType_struct_Particle,
	ButterflyType_RuntimeArray_struct_Particles,
	ButterflyType_struct_Particles,
	ButterflyType_StorageBufferPointer_struct_Particles,
	ButterflyType_StorageBufferPointer_struct_Particle,
	ButterflyVariable_StorageBufferPointer_struct_Particles,
	//INPUT/OUTPUT
	//Result
	ButterflyType_Image_float32_3D_0_0_0_2_R32f,
	ButterflyType_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f,
	ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong0,
	ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1,


	//MAIN FUNCTION
	ButterflyLabel_Start,
	
	ButterflyLoadedVariable_int32vec3_BuiltInInvocationID,
	ButterflyVariable_InputPointer_int32_BuiltInInvocationID_0,
	ButterflyLoadedVariable_int32_BuiltInInvocationID_0,
	ButterflyVariable_InputPointer_int32_BuiltInInvocationID_1,
	ButterflyLoadedVariable_int32_BuiltInInvocationID_1,
	ButterflyVariable_InputPointer_int32_BuiltInInvocationID_2,
	ButterflyLoadedVariable_int32_BuiltInInvocationID_2,
	

	ButterflyVariable_PushConstantPointer_int32_ButterflyStage,
	ButterflyLoadedVariable_int32_ButterflyStage,
	ButterflyVariable_PushConstantPointer_int32_PingPongIndex,
	ButterflyLoadedVariable_int32_PingPongIndex,
	ButterflyVariable_PushConstantPointer_int32_ButterflyDirection,
	ButterflyLoadedVariable_int32_ButterflyDirection,


	ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong0,
	ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1,


	ButterflyLoadedVariable_bool_op0,
	ButterflyLabel_PingPongTrue,

	ButterflyLabel_LoopContinueTarget,



	ButterflyLabel_LoopMerge,

	ButterflyLabel_PingPongFalse,




	ButterflyLabel_PingPongMerge,




	ButterflyVariables_MAX
}ComputeShaderButterflyVariables;
#define ComputeShaderButterflySize (744 * sizeof(SPIRV))
#define ComputeShaderButterfly() {\
SPIRV_Header(ButterflyVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel, \
(6<<SpvWordCountShift)|SpvOpExtInstImport, ButterflyVariable_ExtInstGLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(11<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelGLCompute, ButterflyFunction_Main, 'niam', '\0', \
	ButterflyVariable_InputPointer_int32vec3_BuiltInInvocationID, ButterflyVariable_PushConstantPointer_struct_PushConstants, ButterflyVariable_StorageBufferPointer_struct_Particles,\
	ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong0, ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1,\
(6<<SpvWordCountShift)|SpvOpExecutionMode, ButterflyFunction_Main, SpvExecutionModeLocalSize, 16, 16, 16,\
/*DECORATION*/\
/*INPUT*/\
/*PushConstants*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_PushConstants, 1, SpvDecorationOffset, 4,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_PushConstants, 2, SpvDecorationOffset, 8,\
(3<<SpvWordCountShift)|SpvOpDecorate, ButterflyType_struct_PushConstants, SpvDecorationBlock,\
/*InvocationID*/\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_InputPointer_int32vec3_BuiltInInvocationID, SpvDecorationBuiltIn, SpvBuiltInGlobalInvocationId,\
/*StorageBuffer GPU_Particles*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_Particle, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_Particle, 1, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_Particle, 2, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_Particle, 3, SpvDecorationOffset, 48,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_Particle, 4, SpvDecorationOffset, 64,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_Particle, 5, SpvDecorationOffset, 68,\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyType_RuntimeArray_struct_Particles, SpvDecorationArrayStride, 72,\
(3<<SpvWordCountShift)|SpvOpDecorate, ButterflyType_struct_Particles, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, ButterflyType_struct_Particles, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_StorageBufferPointer_struct_Particles, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_StorageBufferPointer_struct_Particles, SpvDecorationBinding, 0,\
/*INPUT/OUTPUT*/\
/*Result Storage Image*/\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong0, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong0, SpvDecorationBinding, 1,\
\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, SpvDecorationBinding, 2,\
/*BASIC TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, ButterflyType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, ButterflyType_Function, ButterflyType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, ButterflyType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, ButterflyType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, ButterflyType_float32vec2, ButterflyType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, ButterflyType_float32vec3, ButterflyType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, ButterflyType_float32vec4, ButterflyType_float32, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, ButterflyType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, ButterflyType_int32vec2, ButterflyType_int32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, ButterflyType_int32vec3, ButterflyType_int32, 3,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_float32, ButterflyConstant_float32_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_float32, ButterflyConstant_float32_7, 1088421888,\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_int32, ButterflyConstant_int32_N1, -1,\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_int32, ButterflyConstant_int32_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_int32, ButterflyConstant_int32_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, ButterflyType_int32, ButterflyConstant_int32_2, 2,\
/*INPUT*/\
/*PushConstants*/\
(5<<SpvWordCountShift)|SpvOpTypeStruct, ButterflyType_struct_PushConstants, ButterflyType_int32, ButterflyType_int32, ButterflyType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, ButterflyType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, ButterflyType_PushConstantPointer_struct_PushConstants, ButterflyVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_PushConstantPointer_int32, SpvStorageClassPushConstant, ButterflyType_int32,\
/*InvocationID*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_InputPointer_int32vec3, SpvStorageClassInput, ButterflyType_int32vec3,\
(4<<SpvWordCountShift)|SpvOpVariable, ButterflyType_InputPointer_int32vec3, ButterflyVariable_InputPointer_int32vec3_BuiltInInvocationID, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_InputPointer_int32, SpvStorageClassInput, ButterflyType_int32,\
/*StorageBuffer GPU_Atoms*/\
(8<<SpvWordCountShift)|SpvOpTypeStruct, ButterflyType_struct_Particle, ButterflyType_float32vec3, ButterflyType_float32vec3, ButterflyType_float32vec4, ButterflyType_float32vec4, ButterflyType_float32, ButterflyType_float32,\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, ButterflyType_RuntimeArray_struct_Particles, ButterflyType_struct_Particle,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, ButterflyType_struct_Particles, ButterflyType_RuntimeArray_struct_Particles,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_StorageBufferPointer_struct_Particles, SpvStorageClassStorageBuffer, ButterflyType_struct_Particles,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_StorageBufferPointer_struct_Particle, SpvStorageClassStorageBuffer, ButterflyType_struct_Particle,\
(4<<SpvWordCountShift)|SpvOpVariable, ButterflyType_StorageBufferPointer_struct_Particles, ButterflyVariable_StorageBufferPointer_struct_Particles, SpvStorageClassStorageBuffer,\
/*INPUT/OUTPUT*/\
/*Result Storage Image*/\
(9<<SpvWordCountShift)|SpvOpTypeImage, ButterflyType_Image_float32_3D_0_0_0_2_R32f, ButterflyType_float32, SpvDim3D, 0, 0, 0, 2, SpvImageFormatR32f,\
(4<<SpvWordCountShift)|SpvOpTypePointer, ButterflyType_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f, SpvStorageClassUniformConstant, ButterflyType_Image_float32_3D_0_0_0_2_R32f,\
(4<<SpvWordCountShift)|SpvOpVariable, ButterflyType_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f, ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong0, SpvStorageClassUniformConstant,\
(4<<SpvWordCountShift)|SpvOpVariable, ButterflyType_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f, ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, SpvStorageClassUniformConstant,\
\
(4<<SpvWordCountShift)|SpvOpTypeArray, ButterflyType_float32vec3_Array_7_Coordinates, ButterflyType_float32vec3, ButterflyConstant_int_7,\
\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, ButterflyType_Void, ButterflyFunction_Main, SpvFunctionControlMaskNone, ButterflyType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, ButterflyLabel_Start,\
	/*getting invocation ID's*/\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_BuiltInInvocationID, ButterflyVariable_InputPointer_int32vec3_BuiltInInvocationID,\
	(5<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_InputPointer_int32, ButterflyVariable_InputPointer_int32_BuiltInInvocationID_0, ButterflyVariable_InputPointer_int32vec3_BuiltInInvocationID, ButterflyConstant_int32_0,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_int32, ButterflyLoadedVariable_int32_BuiltInInvocationID_0, ButterflyVariable_InputPointer_int32_BuiltInInvocationID_0,\
	(5<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_InputPointer_int32, ButterflyVariable_InputPointer_int32_BuiltInInvocationID_1, ButterflyVariable_InputPointer_int32vec3_BuiltInInvocationID, ButterflyConstant_int32_1,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_int32, ButterflyLoadedVariable_int32_BuiltInInvocationID_1, ButterflyVariable_InputPointer_int32_BuiltInInvocationID_1,\
	(5<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_InputPointer_int32, ButterflyVariable_InputPointer_int32_BuiltInInvocationID_2, ButterflyVariable_InputPointer_int32vec3_BuiltInInvocationID, ButterflyConstant_int32_2,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_int32, ButterflyLoadedVariable_int32_BuiltInInvocationID_2, ButterflyVariable_InputPointer_int32_BuiltInInvocationID_2,\
	/*pushconstant accessing*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_PushConstantPointer_int32, ButterflyVariable_PushConstantPointer_int32_ButterflyStage, ButterflyVariable_PushConstantPointer_struct_PushConstants, ButterflyConstant_int32_0,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_int32, ButterflyLoadedVariable_int32_ButterflyStage, ButterflyVariable_PushConstantPointer_int32_ButterflyStage,\
	\
	(5<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_PushConstantPointer_int32, ButterflyVariable_PushConstantPointer_int32_PingPongIndex, ButterflyVariable_PushConstantPointer_struct_PushConstants, ButterflyConstant_int32_1,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_int32, ButterflyLoadedVariable_int32_PingPongIndex, ButterflyVariable_PushConstantPointer_int32_PingPongIndex,\
	\
	(5<<SpvWordCountShift)|SpvOpAccessChain, ButterflyType_PushConstantPointer_int32, ButterflyVariable_PushConstantPointer_int32_ButterflyDirection, ButterflyVariable_PushConstantPointer_struct_PushConstants, ButterflyConstant_int32_2,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_int32, ButterflyLoadedVariable_int32_ButterflyDirection, ButterflyVariable_PushConstantPointer_int32_ButterflyDirection,\
	\
	/*Loading Images*/\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_Image_float32_3D_0_0_0_2_R32f, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong0, ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong0,\
	(4<<SpvWordCountShift)|SpvOpLoad, ButterflyType_Image_float32_3D_0_0_0_2_R32f, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyVariable_UniformConstantPointer_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1,\
	/*Creating coordinates*/\
	(6<<SpvWordCountShift)|SpvOpCompositeConstruct, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op0, ButterflyConstant_int32_1, ButterflyConstant_int32_0, ButterflyConstant_int32_0,\
	(6<<SpvWordCountShift)|SpvOpCompositeConstruct, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op1, ButterflyConstant_int32_N1, ButterflyConstant_int32_0, ButterflyConstant_int32_0,\
	(6<<SpvWordCountShift)|SpvOpCompositeConstruct, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op2, ButterflyConstant_int32_0, ButterflyConstant_int32_1, ButterflyConstant_int32_0,\
	(6<<SpvWordCountShift)|SpvOpCompositeConstruct, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op3, ButterflyConstant_int32_0, ButterflyConstant_int32_N1, ButterflyConstant_int32_0,\
	(6<<SpvWordCountShift)|SpvOpCompositeConstruct, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op4, ButterflyConstant_int32_0, ButterflyConstant_int32_0, ButterflyConstant_int32_1,\
	(6<<SpvWordCountShift)|SpvOpCompositeConstruct, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op5, ButterflyConstant_int32_0, ButterflyConstant_int32_0, ButterflyConstant_int32_N1,\
	\
	(5<<SpvWordCountShift)|SpvOpIAdd, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op6, ButterflyLoadedVariable_int32vec3_op0, ButterflyLoadedVariable_int32vec3_BuiltInInvocationID,\
	(5<<SpvWordCountShift)|SpvOpIAdd, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op7, ButterflyLoadedVariable_int32vec3_op1, ButterflyLoadedVariable_int32vec3_BuiltInInvocationID,\
	(5<<SpvWordCountShift)|SpvOpIAdd, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op8, ButterflyLoadedVariable_int32vec3_op2, ButterflyLoadedVariable_int32vec3_BuiltInInvocationID,\
	(5<<SpvWordCountShift)|SpvOpIAdd, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op9, ButterflyLoadedVariable_int32vec3_op3, ButterflyLoadedVariable_int32vec3_BuiltInInvocationID,\
	(5<<SpvWordCountShift)|SpvOpIAdd, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op10, ButterflyLoadedVariable_int32vec3_op4, ButterflyLoadedVariable_int32vec3_BuiltInInvocationID,\
	(5<<SpvWordCountShift)|SpvOpIAdd, ButterflyType_int32vec3, ButterflyLoadedVariable_int32vec3_op11, ButterflyLoadedVariable_int32vec3_op5, ButterflyLoadedVariable_int32vec3_BuiltInInvocationID,\
	\
	/*IF pingpong == 0 or else*/\
	(5<<SpvWordCountShift)|SpvOpIEqual, ButterflyType_bool, ButterflyLoadedVariable_bool_op0, ButterflyLoadedVariable_int32_PingPongIndex, ButterflyConstant_int32_0,\
	(3<<SpvWordCountShift)|SpvOpSelectionMerge, ButterflyLabel_PingPongMerge, SpvSelectionControlMaskNone,\
	(4<<SpvWordCountShift)|SpvOpBranchConditional, ButterflyLoadedVariable_bool_op0, ButterflyLabel_PingPongTrue, ButterflyLabel_PingPongFalse,\
	(2<<SpvWordCountShift)|SpvOpLabel, ButterflyLabel_PingPongTrue,\
		\
		(4<<SpvWordCountShift)|SpvOpLoopMerge, ButterflyLabel_LoopMerge, ButterflyLabel_LoopContinueTarget, SpvLoopControlMaskNone,\
		(5<<SpvWordCountShift)|SpvOpSLessThan, ButterflyType_bool, ButterflyLoadedVariable_bool_aa, ButterflyLoadedVariable_int32_aaa, ButterflyConstant_int32_9,\
		(4<<SpvWordCountShift)|SpvOpBranchConditional, ButterflyLoadedVariable_bool_op1, ButterflyLabel_LoopContinueTarget, ButterflyLabel_LoopMerge,\
		(2<<SpvWordCountShift)|SpvOpLabel, ButterflyLabel_LoopContinueTarget,\
			(5<<SpvWordCountShift)|SpvOpImageRead, ButterflyType_float32vec4, ButterflyLoadedVariable_float32vec4_sample, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong0, ButterflyLoadedVariable_int32vec3_BuiltInInvocationID,\
			(3<<SpvWordCountShift)|SpvOpStore, ButterflyVariable_FunctionPointer_float32vec4_Sample_1, ButterflyLoadedVariable_float32vec4_sample_1_0_0__0,\
			(2<<SpvWordCountShift)|SpvOpBranch, ButterflyLabel_LoopContinueTarget,\
		(2<<SpvWordCountShift)|SpvOpLabel, ButterflyLabel_LoopMerge,\
		(2<<SpvWordCountShift)|SpvOpBranch, ButterflyLabel_PingPongMerge,\
	(2<<SpvWordCountShift)|SpvOpLabel, ButterflyLabel_PingPongFalse,\
		(5<<SpvWordCountShift)|SpvOpImageRead, ButterflyType_float32vec4, ButterflyLoadedVariable_float32vec4_sample_0_0_0__1, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_BuiltInInvocationID,\
		(5<<SpvWordCountShift)|SpvOpImageRead, ButterflyType_float32vec4, ButterflyLoadedVariable_float32vec4_sample_1_0_0__1, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op6,\
		(5<<SpvWordCountShift)|SpvOpImageRead, ButterflyType_float32vec4, ButterflyLoadedVariable_float32vec4_sample_N1_0_0__1, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op7,\
		(5<<SpvWordCountShift)|SpvOpImageRead, ButterflyType_float32vec4, ButterflyLoadedVariable_float32vec4_sample_0_1_0__1, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op8,\
		(5<<SpvWordCountShift)|SpvOpImageRead, ButterflyType_float32vec4, ButterflyLoadedVariable_float32vec4_sample_0_N1_0__1, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op9,\
		(5<<SpvWordCountShift)|SpvOpImageRead, ButterflyType_float32vec4, ButterflyLoadedVariable_float32vec4_sample_0_0_1__1, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op10,\
		(5<<SpvWordCountShift)|SpvOpImageRead, ButterflyType_float32vec4, ButterflyLoadedVariable_float32vec4_sample_0_0_N1__1, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op11,\
		\
		(3<<SpvWordCountShift)|SpvOpStore, ButterflyVariable_FunctionPointer_float32vec4_Sample_0, ButterflyLoadedVariable_float32vec4_sample_0_0_0__1,\
		(3<<SpvWordCountShift)|SpvOpStore, ButterflyVariable_FunctionPointer_float32vec4_Sample_1, ButterflyLoadedVariable_float32vec4_sample_1_0_0__1,\
		(3<<SpvWordCountShift)|SpvOpStore, ButterflyVariable_FunctionPointer_float32vec4_Sample_2, ButterflyLoadedVariable_float32vec4_sample_N1_0_0__1,\
		(3<<SpvWordCountShift)|SpvOpStore, ButterflyVariable_FunctionPointer_float32vec4_Sample_3, ButterflyLoadedVariable_float32vec4_sample_0_1_0__1,\
		(3<<SpvWordCountShift)|SpvOpStore, ButterflyVariable_FunctionPointer_float32vec4_Sample_4, ButterflyLoadedVariable_float32vec4_sample_0_N1_0__1,\
		(3<<SpvWordCountShift)|SpvOpStore, ButterflyVariable_FunctionPointer_float32vec4_Sample_5, ButterflyLoadedVariable_float32vec4_sample_0_0_1__1,\
		(3<<SpvWordCountShift)|SpvOpStore, ButterflyVariable_FunctionPointer_float32vec4_Sample_6, ButterflyLoadedVariable_float32vec4_sample_0_0_N1__1,\
		(2<<SpvWordCountShift)|SpvOpBranch, ButterflyLabel_PingPongMerge,\
	(2<<SpvWordCountShift)|SpvOpLabel, ButterflyLabel_PingPongMerge,\
\
		(5<<SpvWordCountShift)|SpvOpCompositeExtract, ButterflyType_float32, ButterflyLoadedVariable_float32_force_sample0_0, ButterflyLoadedVariable_float32vec4_sample_0_0_0__0, 0,\
		(5<<SpvWordCountShift)|SpvOpCompositeExtract, ButterflyType_float32, ButterflyLoadedVariable_float32_force_sample1_0, ButterflyLoadedVariable_float32vec4_sample_1_0_0__0, 0,\
		(5<<SpvWordCountShift)|SpvOpCompositeExtract, ButterflyType_float32, ButterflyLoadedVariable_float32_force_sample2_0, ButterflyLoadedVariable_float32vec4_sample_N1_0_0__0, 0,\
		(5<<SpvWordCountShift)|SpvOpCompositeExtract, ButterflyType_float32, ButterflyLoadedVariable_float32_force_sample3_0, ButterflyLoadedVariable_float32vec4_sample_0_1_0__0, 0,\
		(5<<SpvWordCountShift)|SpvOpCompositeExtract, ButterflyType_float32, ButterflyLoadedVariable_float32_force_sample4_0, ButterflyLoadedVariable_float32vec4_sample_0_N1_0__0, 0,\
		(5<<SpvWordCountShift)|SpvOpCompositeExtract, ButterflyType_float32, ButterflyLoadedVariable_float32_force_sample5_0, ButterflyLoadedVariable_float32vec4_sample_0_0_1__0, 0,\
		(5<<SpvWordCountShift)|SpvOpCompositeExtract, ButterflyType_float32, ButterflyLoadedVariable_float32_force_sample6_0, ButterflyLoadedVariable_float32vec4_sample_0_0_N1__0, 0,\
		\
		(5<<SpvWordCountShift)|SpvOpFAdd, ButterflyType_float32, ButterflyLoadedVariable_float32_op0_0, ButterflyLoadedVariable_float32_force_sample1_0, ButterflyLoadedVariable_float32_force_sample2_0,\
		(5<<SpvWordCountShift)|SpvOpFAdd, ButterflyType_float32, ButterflyLoadedVariable_float32_op1_0, ButterflyLoadedVariable_float32_force_sample3_0, ButterflyLoadedVariable_float32_force_sample4_0,\
		(5<<SpvWordCountShift)|SpvOpFAdd, ButterflyType_float32, ButterflyLoadedVariable_float32_op2_0, ButterflyLoadedVariable_float32_force_sample5_0, ButterflyLoadedVariable_float32_force_sample6_0,\
		(5<<SpvWordCountShift)|SpvOpFAdd, ButterflyType_float32, ButterflyLoadedVariable_float32_op3_0, ButterflyLoadedVariable_float32_op0_0, ButterflyLoadedVariable_float32_op1_0,\
		(5<<SpvWordCountShift)|SpvOpFAdd, ButterflyType_float32, ButterflyLoadedVariable_float32_op4_0, ButterflyLoadedVariable_float32_op3_0, ButterflyLoadedVariable_float32_op2_0,\
		(5<<SpvWordCountShift)|SpvOpFAdd, ButterflyType_float32, ButterflyLoadedVariable_float32_op5_0, ButterflyLoadedVariable_float32_op4_0, ButterflyLoadedVariable_float32_force_sample0_0,\
		\
		(5<<SpvWordCountShift)|SpvOpFDiv, ButterflyType_float32, ButterflyLoadedVariable_float32_op6_0, ButterflyLoadedVariable_float32_op5_0, ButterflyConstant_float32_7,\
		\
		(7<<SpvWordCountShift)|SpvOpCompositeConstruct, ButterflyType_float32vec4, ButterflyLoadedVariable_float32vec4_op0_0, ButterflyLoadedVariable_float32_op6_0, ButterflyConstant_float32_0, ButterflyConstant_float32_0, ButterflyConstant_float32_0,\
		\
		(4<<SpvWordCountShift)|SpvOpImageWrite, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_BuiltInInvocationID, ButterflyLoadedVariable_float32vec4_op0_0,\
		(4<<SpvWordCountShift)|SpvOpImageWrite, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op6, ButterflyLoadedVariable_float32vec4_op0_0,\
		(4<<SpvWordCountShift)|SpvOpImageWrite, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op7, ButterflyLoadedVariable_float32vec4_op0_0,\
		(4<<SpvWordCountShift)|SpvOpImageWrite, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op8, ButterflyLoadedVariable_float32vec4_op0_0,\
		(4<<SpvWordCountShift)|SpvOpImageWrite, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op9, ButterflyLoadedVariable_float32vec4_op0_0,\
		(4<<SpvWordCountShift)|SpvOpImageWrite, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op10, ButterflyLoadedVariable_float32vec4_op0_0,\
		(4<<SpvWordCountShift)|SpvOpImageWrite, ButterflyLoadedVariable_Image_float32_3D_0_0_0_2_R32f_ResultPingPong1, ButterflyLoadedVariable_int32vec3_op11, ButterflyLoadedVariable_float32vec4_op0_0,\
/*end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}



///////////////////////////////////////////////////////////////////////////////////////////////
//Advanced Quantum Shader
///////////////////////////////////////////////////////////////////////////////////////////////

typedef enum VertexShaderQuantumVariables {
	//VertexQuantumExtension_GLSL450,
	VertexQuantumFunction_Main = 1,

	//BASIC TYPES
	VertexQuantumType_Void,
	VertexQuantumType_Function,
	VertexQuantumType_bool,

	VertexQuantumType_float32,
	VertexQuantumType_float32vec2,
	VertexQuantumType_float32vec3,
	VertexQuantumType_float32vec4,
	VertexQuantumType_float32mat4,

	VertexQuantumType_uint32,
	VertexQuantumType_uint32vec2,
	VertexQuantumType_uint32vec3,
	VertexQuantumType_uint32vec4,

	VertexQuantumType_int32,
	VertexQuantumType_int32vec2,
	VertexQuantumType_int32vec3,
	VertexQuantumType_int32vec4,

	//CONSTANTS
	VertexQuantumConstant_float32_0f,
	VertexQuantumConstant_float32_1f,
	VertexQuantumConstant_float32_N1f,

	VertexQuantumConstant_uint_0,

	VertexQuantumConstant_int_0,
	VertexQuantumConstant_int_1,
	VertexQuantumConstant_int_6,

	VertexQuantumConstant_float32vec2_1f_0f,
	VertexQuantumConstant_float32vec2_0f_1f,
	VertexQuantumConstant_float32vec2_0f_0f,
	VertexQuantumConstant_float32vec2_1f_1f,

	VertexQuantumConstant_float32vec2_1f_N1f,
	VertexQuantumConstant_float32vec2_N1f_N1f,
	VertexQuantumConstant_float32vec2_N1f_1f,


	//INPUT
	//BuiltIn
	VertexQuantumType_InputPointer_int32,
	VertexQuantumVariable_InputPointer_VertexIndex,
	VertexQuantumVariable_InputPointer_InstanceIndex,
	//PushConstants
	VertexQuantumType_struct_PushConstants,
	VertexQuantumType_PushConstantPointer_struct_PushConstants,
	VertexQuantumVariable_PushConstantPointer_struct_PushConstants,

	//OUTPUT
	//BuiltIn
	VertexQuantumType_OutputPointer_float32vec4,
	VertexQuantumType_float32_Array_1,
	VertexQuantumType_struct_BuiltIn,
	VertexQuantumType_OutputPointer_struct_BuiltIn,
	VertexQuantumVariable_OutputPointer_struct_BuiltIn,
	VertexQuantumVariable_OutputPointer_float32vec4_Position,

	//Misc
	VertexQuantumType_float32vec2_Array_6,
	VertexQuantumType_FunctionPointer_float32vec2_Array_6,

	VertexQuantumVariable_FunctionPointer_float32vec2_Array_6_Positions,
	VertexQuantumVariable_FunctionPointer_float32vec2_Array_6_UVS,

	VertexQuantumType_FunctionPointer_float32vec2,
	//MAIN FUNCTION
	VertexQuantumLabel_Start,

	VertexQuantumLoadedVariable_float32vec2_Array_6_Positions,
	VertexQuantumLoadedVariable_float32vec2_Array_6_UVS,

	VertexQuantumLoadedVariable_int32_VertexIndex,
	VertexQuantumLoadedVariable_int32_InstanceIndex,

	VertexQuantumLoadedVariable_int32_op0,
	VertexQuantumLoadedVariable_int32_index,

	VertexQuantumVariable_FunctionPointer_float32vec2_IndexedPositions,
	VertexQuantumVariable_FunctionPointer_float32vec2_IndexedUVS,

	VertexQuantumLoadedVariable_float32vec2_op4,
	VertexQuantumLoadedVariable_float32vec2_op5,
	VertexQuantumLoadedVariable_float32vec2_op6,
	VertexQuantumLoadedVariable_float32vec4_op7,

	VertexQuantumVariables_MAX
}VertexShaderQuantumVariables;
#define VertexShaderQuantumSize (352 * sizeof(SPIRV))
#define VertexShaderQuantum() {\
SPIRV_Header(VertexQuantumVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(9<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelVertex, VertexQuantumFunction_Main, 'niam', '\0', VertexQuantumVariable_InputPointer_VertexIndex, VertexQuantumVariable_InputPointer_InstanceIndex, \
VertexQuantumVariable_PushConstantPointer_struct_PushConstants, VertexQuantumVariable_OutputPointer_struct_BuiltIn,\
/*DECORATION*/\
/*INPUT*/\
/*Built In*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexQuantumVariable_InputPointer_VertexIndex, SpvDecorationBuiltIn, SpvBuiltInVertexIndex,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexQuantumVariable_InputPointer_InstanceIndex, SpvDecorationBuiltIn, SpvBuiltInInstanceIndex,\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, VertexQuantumType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexQuantumType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexQuantumType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexQuantumType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexQuantumType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
/*Built In*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexQuantumType_struct_BuiltIn, 0, SpvDecorationBuiltIn, SpvBuiltInPosition,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexQuantumType_struct_BuiltIn, 1, SpvDecorationBuiltIn, SpvBuiltInPointSize,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexQuantumType_struct_BuiltIn, 2, SpvDecorationBuiltIn, SpvBuiltInClipDistance,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexQuantumType_struct_BuiltIn, 3, SpvDecorationBuiltIn, SpvBuiltInCullDistance,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexQuantumType_struct_BuiltIn, SpvDecorationBlock,\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, VertexQuantumType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, VertexQuantumType_Function, VertexQuantumType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, VertexQuantumType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, VertexQuantumType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexQuantumType_float32vec2, VertexQuantumType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexQuantumType_float32vec3, VertexQuantumType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexQuantumType_float32vec4, VertexQuantumType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, VertexQuantumType_float32mat4, VertexQuantumType_float32vec4, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, VertexQuantumType_uint32, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexQuantumType_uint32vec2, VertexQuantumType_uint32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexQuantumType_uint32vec3, VertexQuantumType_uint32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexQuantumType_uint32vec4, VertexQuantumType_uint32, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, VertexQuantumType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexQuantumType_int32vec2, VertexQuantumType_int32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexQuantumType_int32vec3, VertexQuantumType_int32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexQuantumType_int32vec4, VertexQuantumType_int32, 4,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, VertexQuantumType_float32, VertexQuantumConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexQuantumType_float32, VertexQuantumConstant_float32_1f, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexQuantumType_float32, VertexQuantumConstant_float32_N1f, 3212836864,\
\
(4<<SpvWordCountShift)|SpvOpConstant, VertexQuantumType_uint32, VertexQuantumConstant_uint_0, 0,\
\
(4<<SpvWordCountShift)|SpvOpConstant, VertexQuantumType_int32, VertexQuantumConstant_int_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexQuantumType_int32, VertexQuantumConstant_int_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexQuantumType_int32, VertexQuantumConstant_int_6, 6,\
/*UV value constants*/\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexQuantumType_float32vec2, VertexQuantumConstant_float32vec2_1f_0f, VertexQuantumConstant_float32_1f, VertexQuantumConstant_float32_0f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexQuantumType_float32vec2, VertexQuantumConstant_float32vec2_0f_1f, VertexQuantumConstant_float32_0f, VertexQuantumConstant_float32_1f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexQuantumType_float32vec2, VertexQuantumConstant_float32vec2_0f_0f, VertexQuantumConstant_float32_0f, VertexQuantumConstant_float32_0f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexQuantumType_float32vec2, VertexQuantumConstant_float32vec2_1f_1f, VertexQuantumConstant_float32_1f, VertexQuantumConstant_float32_1f,\
\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexQuantumType_float32vec2, VertexQuantumConstant_float32vec2_1f_N1f, VertexQuantumConstant_float32_1f, VertexQuantumConstant_float32_N1f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexQuantumType_float32vec2, VertexQuantumConstant_float32vec2_N1f_N1f, VertexQuantumConstant_float32_N1f, VertexQuantumConstant_float32_N1f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexQuantumType_float32vec2, VertexQuantumConstant_float32vec2_N1f_1f, VertexQuantumConstant_float32_N1f, VertexQuantumConstant_float32_1f,\
/*Input/Output Type Declarations*/\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpTypeStruct, VertexQuantumType_struct_PushConstants, VertexQuantumType_float32mat4, VertexQuantumType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexQuantumType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, VertexQuantumType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexQuantumType_PushConstantPointer_struct_PushConstants, VertexQuantumVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
/*inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexQuantumType_InputPointer_int32, SpvStorageClassInput, VertexQuantumType_int32,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexQuantumType_InputPointer_int32, VertexQuantumVariable_InputPointer_VertexIndex, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexQuantumType_InputPointer_int32, VertexQuantumVariable_InputPointer_InstanceIndex, SpvStorageClassInput,\
/*built in output*/\
(4<<SpvWordCountShift)|SpvOpTypeArray, VertexQuantumType_float32_Array_1, VertexQuantumType_float32, VertexQuantumConstant_int_1,\
(6<<SpvWordCountShift)|SpvOpTypeStruct, VertexQuantumType_struct_BuiltIn, VertexQuantumType_float32vec4, VertexQuantumType_float32, VertexQuantumType_float32_Array_1, VertexQuantumType_float32_Array_1,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexQuantumType_OutputPointer_struct_BuiltIn, SpvStorageClassOutput, VertexQuantumType_struct_BuiltIn,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexQuantumType_OutputPointer_struct_BuiltIn, VertexQuantumVariable_OutputPointer_struct_BuiltIn, SpvStorageClassOutput,\
/*input locations*/\
/*output inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexQuantumType_OutputPointer_float32vec4, SpvStorageClassOutput, VertexQuantumType_float32vec4,\
\
(4<<SpvWordCountShift)|SpvOpTypeArray, VertexQuantumType_float32vec2_Array_6, VertexQuantumType_float32vec2, VertexQuantumConstant_int_6,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexQuantumType_FunctionPointer_float32vec2_Array_6, SpvStorageClassFunction, VertexQuantumType_float32vec2_Array_6,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexQuantumType_FunctionPointer_float32vec2, SpvStorageClassFunction, VertexQuantumType_float32vec2,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, VertexQuantumType_Void, VertexQuantumFunction_Main, SpvFunctionControlMaskNone, VertexQuantumType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, VertexQuantumLabel_Start,\
/*create vars*/\
(4<<SpvWordCountShift)|SpvOpVariable, VertexQuantumType_FunctionPointer_float32vec2_Array_6, VertexQuantumVariable_FunctionPointer_float32vec2_Array_6_Positions, SpvStorageClassFunction,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexQuantumType_FunctionPointer_float32vec2_Array_6, VertexQuantumVariable_FunctionPointer_float32vec2_Array_6_UVS, SpvStorageClassFunction,\
/*positions array*/\
(9<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexQuantumType_float32vec2_Array_6, VertexQuantumLoadedVariable_float32vec2_Array_6_Positions,\
	 VertexQuantumConstant_float32vec2_1f_N1f, VertexQuantumConstant_float32vec2_N1f_1f, VertexQuantumConstant_float32vec2_N1f_N1f, VertexQuantumConstant_float32vec2_1f_N1f, VertexQuantumConstant_float32vec2_1f_1f, VertexQuantumConstant_float32vec2_N1f_1f,\
(3<<SpvWordCountShift)|SpvOpStore, VertexQuantumVariable_FunctionPointer_float32vec2_Array_6_Positions, VertexQuantumLoadedVariable_float32vec2_Array_6_Positions,\
/*UVS array*/\
(9<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexQuantumType_float32vec2_Array_6, VertexQuantumLoadedVariable_float32vec2_Array_6_UVS,\
	 VertexQuantumConstant_float32vec2_1f_0f, VertexQuantumConstant_float32vec2_0f_1f, VertexQuantumConstant_float32vec2_0f_0f, VertexQuantumConstant_float32vec2_1f_0f, VertexQuantumConstant_float32vec2_1f_1f, VertexQuantumConstant_float32vec2_0f_1f,\
(3<<SpvWordCountShift)|SpvOpStore, VertexQuantumVariable_FunctionPointer_float32vec2_Array_6_UVS, VertexQuantumLoadedVariable_float32vec2_Array_6_UVS,\
/*index*/\
(4<<SpvWordCountShift)|SpvOpLoad, VertexQuantumType_int32, VertexQuantumLoadedVariable_int32_VertexIndex, VertexQuantumVariable_InputPointer_VertexIndex,\
(4<<SpvWordCountShift)|SpvOpLoad, VertexQuantumType_int32, VertexQuantumLoadedVariable_int32_InstanceIndex, VertexQuantumVariable_InputPointer_InstanceIndex,\
(5<<SpvWordCountShift)|SpvOpIMul, VertexQuantumType_int32, VertexQuantumLoadedVariable_int32_op0, VertexQuantumLoadedVariable_int32_InstanceIndex, VertexQuantumConstant_int_6,\
(5<<SpvWordCountShift)|SpvOpISub, VertexQuantumType_int32, VertexQuantumLoadedVariable_int32_index, VertexQuantumLoadedVariable_int32_VertexIndex, VertexQuantumLoadedVariable_int32_op0,\
/*output*/\
/*out position*/\
(5<<SpvWordCountShift)|SpvOpAccessChain, VertexQuantumType_FunctionPointer_float32vec2, VertexQuantumVariable_FunctionPointer_float32vec2_IndexedPositions, VertexQuantumVariable_FunctionPointer_float32vec2_Array_6_Positions, VertexQuantumLoadedVariable_int32_index,\
(4<<SpvWordCountShift)|SpvOpLoad, VertexQuantumType_float32vec2, VertexQuantumLoadedVariable_float32vec2_op4, VertexQuantumVariable_FunctionPointer_float32vec2_IndexedPositions,\
/*out UVS*/\
(5<<SpvWordCountShift)|SpvOpAccessChain, VertexQuantumType_FunctionPointer_float32vec2, VertexQuantumVariable_FunctionPointer_float32vec2_IndexedUVS, VertexQuantumVariable_FunctionPointer_float32vec2_Array_6_UVS, VertexQuantumLoadedVariable_int32_index,\
(4<<SpvWordCountShift)|SpvOpLoad, VertexQuantumType_float32vec2, VertexQuantumLoadedVariable_float32vec2_op5, VertexQuantumVariable_FunctionPointer_float32vec2_IndexedUVS,\
/*out inbuilt position*/\
(5<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexQuantumType_float32vec2, VertexQuantumLoadedVariable_float32vec2_op6, VertexQuantumConstant_float32_1f, VertexQuantumConstant_float32_1f,\
(9<<SpvWordCountShift)|SpvOpVectorShuffle, VertexQuantumType_float32vec4, VertexQuantumLoadedVariable_float32vec4_op7, VertexQuantumLoadedVariable_float32vec2_op4, VertexQuantumLoadedVariable_float32vec2_op6, 0, 1, 2, 3,\
\
(5<<SpvWordCountShift)|SpvOpAccessChain, VertexQuantumType_OutputPointer_float32vec4, VertexQuantumVariable_OutputPointer_float32vec4_Position, VertexQuantumVariable_OutputPointer_struct_BuiltIn, VertexQuantumConstant_int_0,\
(3<<SpvWordCountShift)|SpvOpStore, VertexQuantumVariable_OutputPointer_float32vec4_Position, VertexQuantumLoadedVariable_float32vec4_op7,\
/*function end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

typedef enum FragmentShaderQuantumVariables {
	FragmentQuantumExtension_GLSL450 = 1,
	FragmentQuantumFunction_Main,

	//BASIC TYPES
	FragmentQuantumType_Void,
	FragmentQuantumType_Function,
	FragmentQuantumType_bool,

	FragmentQuantumType_float32,
	FragmentQuantumType_float32vec2,
	FragmentQuantumType_float32vec3,
	FragmentQuantumType_float32vec4,
	FragmentQuantumType_float32mat4,

	FragmentQuantumType_uint32,
	FragmentQuantumType_uint32vec2,
	FragmentQuantumType_uint32vec3,
	FragmentQuantumType_uint32vec4,

	FragmentQuantumType_int32,
	FragmentQuantumType_int32vec2,
	FragmentQuantumType_int32vec3,
	FragmentQuantumType_int32vec4,

	//CONSTANTS
	FragmentQuantumConstant_float32_0f,
	FragmentQuantumConstant_float32_1f,
	FragmentQuantumConstant_float32_2f,

	FragmentQuantumConstant_uint32_0,

	FragmentQuantumConstant_int32_0,
	FragmentQuantumConstant_int32_1,
	FragmentQuantumConstant_int32_2,

	//INPUT
	//GPU_Atom 
	FragmentQuantumType_struct_Atom,
	FragmentQuantumType_RuntimeArray_struct_Atoms,
	FragmentQuantumType_struct_Atoms,
	FragmentQuantumType_StorageBufferPointer_struct_Atoms,
	FragmentQuantumType_StorageBufferPointer_struct_Atom,
	FragmentQuantumVariable_StorageBufferPointer_struct_Atoms,

	//GPU_Electrons
	FragmentQuantumType_struct_Electron,
	FragmentQuantumType_RuntimeArray_struct_Electrons,
	FragmentQuantumType_struct_Electrons,
	FragmentQuantumType_StorageBufferPointer_struct_Electrons,
	FragmentQuantumType_StorageBufferPointer_struct_Electron,
	FragmentQuantumVariable_StorageBufferPointer_struct_Electrons,

	//FragmentQuantumType_StorageBufferPointer_float32vec3,

	//PushConstants
	FragmentQuantumType_struct_PushConstants,
	FragmentQuantumType_PushConstantPointer_struct_PushConstants,
	FragmentQuantumVariable_PushConstantPointer_struct_PushConstants,


	//OUTPUT
	//Subpass Attachments
	FragmentQuantumType_OutputPointer_float32vec4,
	FragmentQuantumConstant_float32vec4_NULL,
	FragmentQuantumVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,
	FragmentQuantumVariable_OutputPointer_float32vec4_OutPositionOrRevealage,

	//MAIN FUNCTION
	FragmentQuantumLabel_Start,

	FragmentQuantumLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Albedo,
	FragmentQuantumLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Position,
	FragmentQuantumLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Normal,
	FragmentQuantumLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_PBR,
	FragmentQuantumLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Transperancy,
	FragmentQuantumLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Revealage,
	FragmentQuantumLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Depth,

	FragmentQuantumLoadedVariable_float32vec4_Albedo,
	FragmentQuantumLoadedVariable_float32vec4_Position,
	FragmentQuantumLoadedVariable_float32vec4_Normal,
	FragmentQuantumLoadedVariable_float32vec4_PBR,
	FragmentQuantumLoadedVariable_float32vec4_Transperancy,
	FragmentQuantumLoadedVariable_float32vec4_Revealage,
	FragmentQuantumLoadedVariable_float32vec4_Depth,

	FragmentQuantumLoadedVariable_float32_AlbedoX,
	FragmentQuantumLoadedVariable_float32_AlbedoY,
	FragmentQuantumLoadedVariable_float32_AlbedoZ,
	FragmentQuantumLoadedVariable_float32_AlbedoW,

	FragmentQuantumLoadedVariable_float32_TransperancyX,
	FragmentQuantumLoadedVariable_float32_TransperancyY,
	FragmentQuantumLoadedVariable_float32_TransperancyZ,
	FragmentQuantumLoadedVariable_float32_TransperancyW,

	FragmentQuantumLoadedVariable_float32vec3_Albedo,
	FragmentQuantumLoadedVariable_float32vec3_Transperancy,

	FragmentQuantumLoadedVariable_float32_op0,
	FragmentQuantumLoadedVariable_float32_op1,
	FragmentQuantumLoadedVariable_float32_op2,
	FragmentQuantumLoadedVariable_float32_op3,
	FragmentQuantumLoadedVariable_float32_op4,

	FragmentQuantumLoadedVariable_float32vec3_op0,
	FragmentQuantumLoadedVariable_float32vec3_op1,
	FragmentQuantumLoadedVariable_float32vec3_op2,

	FragmentQuantumLoadedVariable_float32vec4_op0,


	FragmentQuantumVariables_MAX,
}FragmentShaderQuantumVariables;
#define FragmentShaderQuantumSize (326 * sizeof(SPIRV))
#define FragmentShaderQuantum() {\
SPIRV_Header(FragmentQuantumVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityImageQuery,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityInputAttachment,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, FragmentQuantumExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(10<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelFragment, FragmentQuantumFunction_Main, 'niam', '\0', FragmentQuantumVariable_StorageBufferPointer_struct_Atoms, FragmentQuantumVariable_StorageBufferPointer_struct_Electrons,\
FragmentQuantumVariable_PushConstantPointer_struct_PushConstants, FragmentQuantumVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, FragmentQuantumVariable_OutputPointer_float32vec4_OutPositionOrRevealage,\
(3<<SpvWordCountShift)|SpvOpExecutionMode, FragmentQuantumFunction_Main, SpvExecutionModeOriginUpperLeft,\
/*DECORATION*/\
/*INPUT*/\
/*StorageBuffer GPU_Atoms*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_Atom, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_Atom, 1, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_Atom, 2, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_Atom, 3, SpvDecorationOffset, 48,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_Atom, 4, SpvDecorationOffset, 64,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentQuantumType_RuntimeArray_struct_Atoms, SpvDecorationArrayStride, 80,\
(3<<SpvWordCountShift)|SpvOpDecorate, FragmentQuantumType_struct_Atoms, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_Atoms, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentQuantumVariable_StorageBufferPointer_struct_Atoms, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentQuantumVariable_StorageBufferPointer_struct_Atoms, SpvDecorationBinding, 0,\
/*StorageBuffer GPU_Electrons*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_Electron, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_Electron, 1, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_Electron, 2, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_Electron, 3, SpvDecorationOffset, 48,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentQuantumType_RuntimeArray_struct_Electrons, SpvDecorationArrayStride, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, FragmentQuantumType_struct_Electrons, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_Electrons, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentQuantumVariable_StorageBufferPointer_struct_Electrons, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentQuantumVariable_StorageBufferPointer_struct_Electrons, SpvDecorationBinding, 1,\
/*PushConstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentQuantumType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(3<<SpvWordCountShift)|SpvOpDecorate, FragmentQuantumType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
/*Subpass Attachments*/\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentQuantumVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentQuantumVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvDecorationLocation, 1,\
\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, FragmentQuantumType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, FragmentQuantumType_Function, FragmentQuantumType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, FragmentQuantumType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, FragmentQuantumType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentQuantumType_float32vec2, FragmentQuantumType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentQuantumType_float32vec3, FragmentQuantumType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentQuantumType_float32vec4, FragmentQuantumType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, FragmentQuantumType_float32mat4, FragmentQuantumType_float32vec4, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, FragmentQuantumType_uint32, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentQuantumType_uint32vec2, FragmentQuantumType_uint32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentQuantumType_uint32vec3, FragmentQuantumType_uint32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentQuantumType_uint32vec4, FragmentQuantumType_uint32, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, FragmentQuantumType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentQuantumType_int32vec2, FragmentQuantumType_int32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentQuantumType_int32vec3, FragmentQuantumType_int32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentQuantumType_int32vec4, FragmentQuantumType_int32, 4,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentQuantumType_float32, FragmentQuantumConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentQuantumType_float32, FragmentQuantumConstant_float32_1f, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentQuantumType_float32, FragmentQuantumConstant_float32_2f, 1073741824,\
\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentQuantumType_uint32, FragmentQuantumConstant_uint32_0, 0,\
\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentQuantumType_int32, FragmentQuantumConstant_int32_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentQuantumType_int32, FragmentQuantumConstant_int32_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentQuantumType_int32, FragmentQuantumConstant_int32_2, 2,\
/*INPUT*/\
/*StorageBuffer GPU_Atoms*/\
(7<<SpvWordCountShift)|SpvOpTypeStruct, FragmentQuantumType_struct_Atom, FragmentQuantumType_float32vec3, FragmentQuantumType_float32vec3, FragmentQuantumType_float32vec4, FragmentQuantumType_float32vec4, FragmentQuantumType_int32,\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, FragmentQuantumType_RuntimeArray_struct_Atoms, FragmentQuantumType_struct_Atom,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, FragmentQuantumType_struct_Atoms, FragmentQuantumType_RuntimeArray_struct_Atoms,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentQuantumType_StorageBufferPointer_struct_Atoms, SpvStorageClassStorageBuffer, FragmentQuantumType_struct_Atoms,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentQuantumType_StorageBufferPointer_struct_Atom, SpvStorageClassStorageBuffer, FragmentQuantumType_struct_Atom,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentQuantumType_StorageBufferPointer_struct_Atoms, FragmentQuantumVariable_StorageBufferPointer_struct_Atoms, SpvStorageClassStorageBuffer,\
/*StorageBuffer GPU_Electrons*/\
(6<<SpvWordCountShift)|SpvOpTypeStruct, FragmentQuantumType_struct_Electron, FragmentQuantumType_float32vec3, FragmentQuantumType_float32vec3, FragmentQuantumType_float32vec4, FragmentQuantumType_float32vec4,\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, FragmentQuantumType_RuntimeArray_struct_Electrons, FragmentQuantumType_struct_Electron,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, FragmentQuantumType_struct_Electrons, FragmentQuantumType_RuntimeArray_struct_Electrons,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentQuantumType_StorageBufferPointer_struct_Electrons, SpvStorageClassStorageBuffer, FragmentQuantumType_struct_Electrons,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentQuantumType_StorageBufferPointer_struct_Electron, SpvStorageClassStorageBuffer, FragmentQuantumType_struct_Electron,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentQuantumType_StorageBufferPointer_struct_Electrons, FragmentQuantumVariable_StorageBufferPointer_struct_Electrons, SpvStorageClassStorageBuffer,\
/*PushConstants*/\
(3<<SpvWordCountShift)|SpvOpTypeStruct, FragmentQuantumType_struct_PushConstants, FragmentQuantumType_float32mat4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentQuantumType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, FragmentQuantumType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentQuantumType_PushConstantPointer_struct_PushConstants, FragmentQuantumVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
/*OUTPUT*/\
/*Subpass Attachments*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentQuantumType_OutputPointer_float32vec4, SpvStorageClassOutput, FragmentQuantumType_float32vec4,\
(3<<SpvWordCountShift)|SpvOpConstantNull, FragmentQuantumType_float32vec4, FragmentQuantumConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentQuantumType_OutputPointer_float32vec4, FragmentQuantumVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvStorageClassOutput, FragmentQuantumConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentQuantumType_OutputPointer_float32vec4, FragmentQuantumVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvStorageClassOutput, FragmentQuantumConstant_float32vec4_NULL,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, FragmentQuantumType_Void, FragmentQuantumFunction_Main, SpvFunctionControlMaskNone, FragmentQuantumType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, FragmentQuantumLabel_Start,\
	/*albedo = vec4()*/\
	/*(3<<SpvWordCountShift)|SpvOpStore, FragmentQuantumVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, fffffffffffffffffffffffffffffffff,*/\
/*FUNCTION END*/\
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
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers, RHeaderCamera* pCamera, mat4 CameraVP)
{
	//pResourceHeader->Time = ((double)clock() / (double)CLOCKS_PER_SEC);

	RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
	RHeaderTexture* pTexture = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pMaterial->BaseColourTexture.iTexture);
	RHeaderImageSource* pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture->iImageSource);

	VkResult res = VK_SUCCESS;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Rendering
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Engine_Ref_Lock_Mutex(pEffect->mutex);
	{
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pTexture->GPU_Texture.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = 0;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
				VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}

		vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pEffect->VkPipelineCompute);

		PushConstantsButterfly PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.ButterflyStage = 0;
		PushConstants.ButterflyDirection = 0;
		PushConstants.PingPongIndex = 0;

		vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->VkPipelineLayoutCompute, VK_SHADER_STAGE_COMPUTE_BIT, 0,
			pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstants);

		vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
			pEffect->VkPipelineLayoutCompute, 0, 1, &pEffect->VkDescriptorSetCompute, 0, NULL);

		vkCmdDispatch(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->SimulationResolution / 16, pEffect->SimulationResolution / 16, pEffect->SimulationResolution / 16);

		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pTexture->GPU_Texture.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}
	}
	/*
	{//butterfly		
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pResourceHeader->TexturePingPong.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = 0;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
				VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}

		vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pResourceHeader->VkPipelineButterfly);
		vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
			pResourceHeader->VkPipelineLayoutButterfly, 0, 1, &pResourceHeader->VkDescriptorSetButterfly, 0, NULL);

		uint64_t log_2_N = (int)(log(pResourceHeader->WaterResolution) / log(2));
		for (size_t i = 0; i < log_2_N; i++)
		{
			for (size_t i1 = 0; i1 < 2; i1++)
			{
				{
					VkImageMemoryBarrier Barrier;
					Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
					Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
					Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
					Barrier.image = pResourceHeader->Texturehkt_dy.VkImage;
					Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					Barrier.subresourceRange.baseMipLevel = 0;
					Barrier.subresourceRange.levelCount = 1;
					Barrier.subresourceRange.baseArrayLayer = 0;
					Barrier.subresourceRange.layerCount = 1;
					Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
					Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
					switch (PingPongIndex)
					{
					case 0:
						Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						break;
					case 1:
						Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						break;
					}
					Barrier.pNext = NULL;


					vkCmdPipelineBarrier(
						pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
						VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
						0,
						0, NULL,
						0, NULL,
						1, &Barrier
					);
				}
				{
					VkImageMemoryBarrier Barrier;
					Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
					Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
					Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
					Barrier.image = pResourceHeader->TexturePingPong.VkImage;
					Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					Barrier.subresourceRange.baseMipLevel = 0;
					Barrier.subresourceRange.levelCount = 1;
					Barrier.subresourceRange.baseArrayLayer = 0;
					Barrier.subresourceRange.layerCount = 1;
					Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
					Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
					switch (PingPongIndex)
					{
					case 0:
						Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						break;
					case 1:
						Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						break;
					}
					Barrier.pNext = NULL;


					vkCmdPipelineBarrier(
						pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
						VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
						0,
						0, NULL,
						0, NULL,
						1, &Barrier
					);
				}



				uint8_t pushconstantbuffer[sizeof(WaterPushConstants)];
				WaterPushConstants PushConstants;
				memset(&PushConstants, 0, sizeof(PushConstants));
				glm_vec2_copy(pResourceHeader->FlowDirection, PushConstants.FlowDirection);
				PushConstants.WaterResolution = pResourceHeader->WaterResolution;
				PushConstants.WaterL = pResourceHeader->WaterL;
				PushConstants.WaterAmplitude = pResourceHeader->WaterAmplitude;
				PushConstants.WaterIntensity = pResourceHeader->WaterIntensity;
				PushConstants.Waterl = pResourceHeader->Waterl;
				PushConstants.Time = pResourceHeader->Time;
				PushConstants.ButterflyStage = i;
				PushConstants.ButterflyDirection = i1;
				PushConstants.PingPongIndex = PingPongIndex;

				memcpy(pushconstantbuffer, &PushConstants, sizeof(PushConstants));
				vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->VkPipelineLayouthkt, VK_SHADER_STAGE_COMPUTE_BIT, 0,
					pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &pushconstantbuffer);

				vkCmdDispatch(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->WaterResolution / 16, pResourceHeader->WaterResolution / 16, 1);

				PingPongIndex++;
				PingPongIndex %= 2;

				{
					VkImageMemoryBarrier Barrier;
					Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
					Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
					Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
					Barrier.image = pResourceHeader->Texturehkt_dy.VkImage;
					Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					Barrier.subresourceRange.baseMipLevel = 0;
					Barrier.subresourceRange.levelCount = 1;
					Barrier.subresourceRange.baseArrayLayer = 0;
					Barrier.subresourceRange.layerCount = 1;
					Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
					Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
					switch (PingPongIndex)
					{
					case 0:
						Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						break;
					case 1:
						Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						break;
					}
					Barrier.pNext = NULL;


					vkCmdPipelineBarrier(
						pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
						VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
						0,
						0, NULL,
						0, NULL,
						1, &Barrier
					);
				}
				{
					VkImageMemoryBarrier Barrier;
					Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
					Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
					Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
					Barrier.image = pResourceHeader->TexturePingPong.VkImage;
					Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
					Barrier.subresourceRange.baseMipLevel = 0;
					Barrier.subresourceRange.levelCount = 1;
					Barrier.subresourceRange.baseArrayLayer = 0;
					Barrier.subresourceRange.layerCount = 1;
					Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
					Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
					switch (PingPongIndex)
					{
					case 0:
						Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						break;
					case 1:
						Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						break;
					}
					Barrier.pNext = NULL;


					vkCmdPipelineBarrier(
						pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
						VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
						0,
						0, NULL,
						0, NULL,
						1, &Barrier
					);
				}
			}
		}
	}
	*/
	/*
	{//inversion
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pTexture->GPU_Texture.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
				VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}

		vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pResourceHeader->VkPipelineInversion);

		uint8_t pushconstantbuffer[sizeof(WaterPushConstants)];
		WaterPushConstants PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		glm_vec2_copy(pResourceHeader->FlowDirection, PushConstants.FlowDirection);
		PushConstants.WaterResolution = pResourceHeader->WaterResolution;
		PushConstants.WaterL = pResourceHeader->WaterL;
		PushConstants.WaterAmplitude = pResourceHeader->WaterAmplitude;
		PushConstants.WaterIntensity = pResourceHeader->WaterIntensity;
		PushConstants.Waterl = pResourceHeader->Waterl;
		PushConstants.Time = pResourceHeader->Time;
		PushConstants.ButterflyStage = 0;
		PushConstants.ButterflyDirection = 0;
		PushConstants.PingPongIndex = PingPongIndex;

		memcpy(pushconstantbuffer, &PushConstants, sizeof(PushConstants));
		vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->VkPipelineLayouth0k, VK_SHADER_STAGE_COMPUTE_BIT, 0,
			pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &pushconstantbuffer);

		vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
			pResourceHeader->VkPipelineLayoutInversion, 0, 1, &pResourceHeader->VkDescriptorSetInversion, 0, NULL);
		vkCmdDispatch(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->WaterResolution / 16, pResourceHeader->WaterResolution / 16, 1);

		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			Barrier.image = pTexture->GPU_Texture.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}
	}
	*/
	Engine_Ref_Unlock_Mutex(pEffect->mutex);

	VkBuffer vkBuffer = GPU_Buffers[0].Allocater.pArenaAllocater->VkBuffer;
	VkDeviceSize VkOffset = GPU_Buffers[0].Pointer + GPU_BufferPointers[0];
	GPU_BufferPointers[0] += sizeof(*pEffect->Particles) * pEffect->ParticlesSize;

	vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pEffect->VkPipelineParticle);

	PushConstantsSimplifiedMolecular PushConstantsSimplifiedMolecular;
	memset(&PushConstantsSimplifiedMolecular, NULL, sizeof(PushConstantsSimplifiedMolecular));
	glm_mat4_copy(CameraVP, PushConstantsSimplifiedMolecular.VP);
	glm_vec3_copy(pEffect->Position, PushConstantsSimplifiedMolecular.Position);
	vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, ((GraphicsUtils*)GraphicsRes.pUtils)->GenericResources[Graphics_Ref_Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].PipelineLayout2D, VK_SHADER_STAGE_ALL, 0,
		pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstantsSimplifiedMolecular);

	vkCmdBindVertexBuffers(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 0, 1, &vkBuffer, &VkOffset);

	vkCmdDraw(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 1, pEffect->ParticlesSize, 0, 0);
}

void Draw_QuantumAtomic(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, ChemistryEffectQuantumAtomic* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers, RHeaderCamera* pCamera, mat4 CameraVP)
{
	vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pEffect->VkPipelineQuantum);

	PushConstantsQuantumAtomic PushConstantsQuantumAtomic;
	memset(&PushConstantsQuantumAtomic, NULL, sizeof(PushConstantsQuantumAtomic));
	//glm_mat4_copy(CameraVP, PushConstantsQuantumAtomic.VP);
	//glm_vec3_copy(pEffect->Position, PushConstantsQuantumAtomic.Position);
	vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->VkPipelineLayoutQuantum, VK_SHADER_STAGE_ALL, 0,
		pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstantsQuantumAtomic);

	VkDescriptorSet descriptorsets[1] = {
		pEffect->VkDescriptorSetsQuantum[FrameIndex]
	};
	uint32_t descriptorsetSize = 1;

	vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
		pEffect->VkPipelineLayoutQuantum, 0, descriptorsetSize, descriptorsets, 0, NULL);

	vkCmdDraw(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 1, pEffect->GPU_AtomsSize, 0, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Update Effect Element
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Update_SimplifiedMolecular(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, ChemistryEffectSimplifiedMolecular* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
	Engine_Ref_Lock_Mutex(pEffect->mutex);
	if (GPU_Buffers == NULL)
	{
		GPU_BufferPointers[0] += pEffect->ParticlesSize * sizeof(*pEffect->Particles);
	}
	else
	{	
		RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
		RHeaderTexture* pTexture = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pMaterial->BaseColourTexture.iTexture);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Updating Descriptor Sets
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		{//compute
			VkDescriptorBufferInfo BufferInfo;
			BufferInfo.buffer = GPU_Buffers[0].Allocater.pArenaAllocater->VkBuffer;
			BufferInfo.offset = GPU_Buffers[0].Pointer;
			BufferInfo.range = GPU_Buffers[0].SizeBytes;
			Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pEffect->VkDescriptorSetCompute, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &BufferInfo, NULL);
		} {
			VkDescriptorImageInfo ImageInfo;
			ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
			ImageInfo.imageView = pTexture->GPU_Texture.VkImageView;
			ImageInfo.sampler = NULL;
			Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pEffect->VkDescriptorSetCompute, 1, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
		} {
			VkDescriptorImageInfo ImageInfo;
			ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
			ImageInfo.imageView = pTexture->GPU_Texture.VkImageView;
			ImageInfo.sampler = NULL;
			Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pEffect->VkDescriptorSetCompute, 2, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
		}

		/*
		if (((EngineUtils*)EngineRes.pUtils)->pWindows[0]->STATE_KEY_R == KeyPress && press == false)
		{
			Resize_Array(&pEffect->Particles, pEffect->ParticlesSize, pEffect->ParticlesSize + 1, sizeof(*pEffect->Particles));
			memset(&pEffect->Particles[pEffect->ParticlesSize], 0, sizeof(*pEffect->Particles));
			pEffect->Particles[pEffect->ParticlesSize].Size = 0.00054f;
			pEffect->Particles[pEffect->ParticlesSize].Charge = -1.0f;
			pEffect->Particles[pEffect->ParticlesSize].Position[0] = (((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.X_Position - 500) / 100;
			pEffect->Particles[pEffect->ParticlesSize].Position[1] = -((((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.Y_Position - 500) / 100);
			pEffect->ParticlesSize++;
			press = true;
		}
		if (((EngineUtils*)EngineRes.pUtils)->pWindows[0]->STATE_KEY_T == KeyPress && press == false)
		{
			Resize_Array(&pEffect->Particles, pEffect->ParticlesSize, pEffect->ParticlesSize + 1, sizeof(*pEffect->Particles));
			memset(&pEffect->Particles[pEffect->ParticlesSize], 0, sizeof(*pEffect->Particles));
			pEffect->Particles[pEffect->ParticlesSize].Size = 1.0f;
			pEffect->Particles[pEffect->ParticlesSize].Charge = 1.0f;
			pEffect->Particles[pEffect->ParticlesSize].Position[0] = (((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.X_Position - 500) / 100;
			pEffect->Particles[pEffect->ParticlesSize].Position[1] = -((((EngineUtils*)EngineRes.pUtils)->MousePos_Callback_state.Y_Position - 500) / 100);
			pEffect->ParticlesSize++;
			press = true;
		}
		if (((EngineUtils*)EngineRes.pUtils)->pWindows[0]->STATE_KEY_R == KeyRelease && ((EngineUtils*)EngineRes.pUtils)->pWindows[0]->STATE_KEY_T == KeyRelease)
		{
			press = false;
		}

		for (size_t i = 0; i < pEffect->ParticlesSize; i++)
		{
			GPU_Particle* pParticle1 = &pEffect->Particles[i];	
			for (size_t i1 = 0; i1 < pEffect->ParticlesSize; i1++)
			{
				if (i != i1)
				{
					GPU_Particle* pParticle2 = &pEffect->Particles[i1];
					float distancesqaured = glm_vec3_distance(pParticle1->Position, pParticle2->Position) * 10000;

					double force = 0.0;
					//gravity needs to be 10^24 times weaker then electromagnetic.
					//force += ((1.0 / 404331557902116024553602703216.58) / distancesqaured) * pParticle2->Size; // ((0.00000000001) / distancesqaured) * pParticle2->Size
					//electromagnetic
					force += -((0.8988 * (((pParticle1->Charge * pParticle2->Charge)) / distancesqaured)));
					
					force *= 0.0001;

					if (force < 10.0f && force > -10.0f)
					{
						vec3 aa;
						glm_vec3_scale(pParticle2->Position, force / pParticle1->Size, aa);

						vec3 aaa;
						glm_vec3_divs(aa, pParticle2->Size / pParticle1->Size, aaa);

						glm_vec3_add(pParticle1->PositionVelocity, aa, pParticle1->PositionVelocity);
						glm_vec3_sub(pParticle2->PositionVelocity, aaa, pParticle2->PositionVelocity);
					}
				}
			}

			float bleed = 0.999f;
			glm_vec3_scale(pParticle1->PositionVelocity, bleed, pParticle1->PositionVelocity);
			glm_vec4_scale(pParticle1->RotationVelocity, bleed, pParticle1->RotationVelocity);

			pParticle1->PositionVelocity[0] += ((float)rand()) * 0.0000000000001;
			pParticle1->PositionVelocity[1] += ((float)rand()) * 0.0000000000001;
			pParticle1->PositionVelocity[2] += ((float)rand()) * 0.0000000000001;

			glm_vec3_add(pParticle1->Position, pParticle1->PositionVelocity, pParticle1->Position);
			glm_quat_mul(pParticle1->Rotation, pParticle1->RotationVelocity, pParticle1->Rotation);
		}
		for (size_t i = 0; i < pEffect->ParticlesSize; i++)
		{
			GPU_Particle* pParticle = &pEffect->Particles[i];
			glm_vec3_add(pParticle->Position, pParticle->PositionVelocity, pParticle->Position);
			glm_quat_mul(pParticle->Rotation, pParticle->RotationVelocity, pParticle->Rotation);
		}
		*/
		if (pEffect->ParticlesSize != NULL)
		{
			memcpy((void*)((uint64_t)GPU_BufferPointers[0]), pEffect->Particles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));
		}
		GPU_BufferPointers[0] += pEffect->ParticlesSize * sizeof(*pEffect->Particles);
	}
	Engine_Ref_Unlock_Mutex(pEffect->mutex);
}

void Update_QuantumAtomic(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, ChemistryEffectQuantumAtomic* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
	if (GPU_Buffers == NULL)
	{
		GPU_BufferPointers[0] += sizeof(*pEffect->GPU_Atoms) * pEffect->GPU_AtomsSize;
		GPU_BufferPointers[1] += sizeof(*pEffect->GPU_Electrons) * pEffect->GPU_ElectronsSize;
	}
	else
	{
		/*
		if (pEffect->GPU_AtomsSize != NULL)
		{
			memcpy((void*)((uint64_t)pGraphicsWindow->pLogicalDevice->SrcBufPointer + GPU_Buffers[0].Pointer + GPU_BufferPointers[0]),
				pEffect->GPU_Atoms, pEffect->GPU_AtomsSize * sizeof(*pEffect->GPU_Atoms));
		}*/
		GPU_BufferPointers[0] += sizeof(*pEffect->GPU_Atoms) * pEffect->GPU_AtomsSize;
		GPU_BufferPointers[1] += sizeof(*pEffect->GPU_Electrons) * pEffect->GPU_ElectronsSize;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Signataure Updates
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdateSignature_SimplifiedMolecular(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
}

void UpdateSignature_QuantumAtomic(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Signataure Draws
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawSignature_SimplifiedMolecular(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
}

void DrawSignature_QuantumAtomic(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Destroy_SimplifiedMolecular(ElementGraphics* pElement, ChemistryEffectSimplifiedMolecular* pEffect, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);
	
	Engine_Ref_Destroy_Mutex(pEffect->mutex);

	if (pEffect->VkPipelineCompute != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineCompute, NULL);
	pEffect->VkPipelineCompute = NULL;

	if (pEffect->VkPipelineLayoutCompute != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineLayoutCompute, NULL);
	pEffect->VkPipelineLayoutCompute = NULL;

	if (pEffect->VkDescriptorSetLayoutCompute != NULL)
		vkDestroyDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkDescriptorSetLayoutCompute, NULL);
	pEffect->VkDescriptorSetLayoutCompute = NULL;

	/*
	if (pEffect->VkDescriptorSetsCompute != NULL)
	{
		//vkFreeDescriptorSets(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkWindowDescriptorPool, pResourceHeader->CurrentFrameBuffersSize, pResourceHeader->VkDescriptorSetsInputAttachment);
		free(pEffect->VkDescriptorSetsCompute);
	}*/
	pEffect->VkDescriptorSetCompute = NULL;

	if (pEffect->VkDescriptorPoolCompute != NULL)
		vkDestroyDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkDescriptorPoolCompute, NULL);
	pEffect->VkDescriptorPoolCompute = NULL;

	if (pEffect->VkShaderCompute != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderCompute, NULL);
	pEffect->VkShaderCompute = NULL;


	if (pEffect->VkPipelineParticle != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineParticle, NULL);
	pEffect->VkPipelineParticle = NULL;

	if (pEffect->VkShaderVertexParticle != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderVertexParticle, NULL);
	pEffect->VkShaderVertexParticle = NULL;
	if (pEffect->VkShaderFragmentParticle != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderFragmentParticle, NULL);
	pEffect->VkShaderFragmentParticle = NULL;

	
	if (Full == true)
	{

		if (pEffect->Particles != NULL)
			free(pEffect->Particles);
		pEffect->Particles = NULL;
		pEffect->ParticlesSize = NULL;
	}
}

void Destroy_QuantumAtomic(ElementGraphics* pElement, ChemistryEffectQuantumAtomic* pEffect, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);
	
	if (pEffect->VkPipelineQuantum != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineQuantum, NULL);
	pEffect->VkPipelineQuantum = NULL;

	if (pEffect->VkPipelineLayoutQuantum != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineLayoutQuantum, NULL);
	pEffect->VkPipelineLayoutQuantum = NULL;

	if (pEffect->VkDescriptorSetLayoutQuantum != NULL)
		vkDestroyDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkDescriptorSetLayoutQuantum, NULL);

	if (pEffect->VkDescriptorSetsQuantum != NULL)
	{
		//vkFreeDescriptorSets(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkWindowDescriptorPool, pResourceHeader->CurrentFrameBuffersSize, pResourceHeader->VkDescriptorSetsInputAttachment);
		free(pEffect->VkDescriptorSetsQuantum);
	}
	if (pEffect->VkDescriptorPoolQuantum != NULL)
		vkDestroyDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkDescriptorPoolQuantum, NULL);


	if (pEffect->VkShaderVertexQuantum != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderVertexQuantum, NULL);
	pEffect->VkShaderVertexQuantum = NULL;
	if (pEffect->VkShaderFragmentQuantum != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderFragmentQuantum, NULL);
	pEffect->VkShaderFragmentQuantum = NULL;
	
	if (Full == true)
	{
		if (pEffect->GPU_Atoms != NULL && pEffect->GPU_AtomsSize != NULL)
			free(pEffect->GPU_Atoms);
		pEffect->GPU_Atoms = NULL;
		pEffect->GPU_AtomsSize = NULL;

		if (pEffect->GPU_Electrons != NULL && pEffect->GPU_ElectronsSize != NULL)
			free(pEffect->GPU_Electrons);
		pEffect->GPU_Electrons = NULL;
		pEffect->GPU_ElectronsSize = NULL;
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
	TEXRESULT tres = Success;
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);
	RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->BaseColourTexture.iTexture) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_SimplifiedMolecular()", "pMaterial->BaseColourTexture.iTexture Invalid");
		return;
	}
#endif

	RHeaderTexture* pTexture = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pMaterial->BaseColourTexture.iTexture);
	RHeaderImageSource* pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture->iImageSource);

#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pTexture->iImageSource) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_SimplifiedMolecular()", "pMaterial->BaseColourTexture.iTexture->iImageSource Invalid");
		return;
	}
	if (pImageSource->ImageData == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_SimplifiedMolecular()", "pMaterial->BaseColourTexture.iTexture->iImageSource->ImageData == NULLPTR");
		return;
	}
#endif
	pImageSource->ImageData->Width = pEffect->SimulationResolution;
	pImageSource->ImageData->Height = pEffect->SimulationResolution;
	pImageSource->ImageData->Depth = pEffect->SimulationResolution;
	pImageSource->ImageData->Format = GraphicsFormat_R32G32B32A32_SFLOAT;
	pImageSource->ImageData->MipmapCount = 1;
	Object_Ref_ReCreate_ResourceHeader(pTexture->Header.Allocation, NULL, ThreadIndex);


	Engine_Ref_Create_Mutex(pEffect->mutex, MutexType_Plain);


	const SPIRV ShaderButterfly[] = ComputeShaderButterfly();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkShaderCompute, ComputeShaderButterfly, ComputeShaderButterflySize, "ReCreate_SimplifiedMolecular()");


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//DescriptorLayout
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		VkDescriptorSetLayoutBinding BindingsCompute[ChemistrySimplifiedMolecularBuffersCount + ChemistrySimplifiedMolecularImagesCount];
		
		size_t i = 0;
		for (; i < ChemistrySimplifiedMolecularBuffersCount; i++)
		{
			BindingsCompute[i].binding = i;
			BindingsCompute[i].descriptorCount = 1;
			BindingsCompute[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			BindingsCompute[i].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			BindingsCompute[i].pImmutableSamplers = NULL;
		}
		for (; i < ChemistrySimplifiedMolecularBuffersCount + ChemistrySimplifiedMolecularImagesCount; i++)
		{
			BindingsCompute[i].binding = i;
			BindingsCompute[i].descriptorCount = 1;
			BindingsCompute[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			BindingsCompute[i].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			BindingsCompute[i].pImmutableSamplers = NULL;
		}

		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)ChemistrySimplifiedMolecularBuffersCount + ChemistrySimplifiedMolecularImagesCount;
		Info.pBindings = BindingsCompute;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkDescriptorSetLayoutCompute)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_SimplifiedMolecular()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipeline Layouts
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		VkDescriptorSetLayout layouts[1] = { pEffect->VkDescriptorSetLayoutCompute };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_ALL;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkPipelineLayoutCompute)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_SimplifiedMolecular()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Descriptor Pool
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{//pool
		uint32_t PoolSizesSize = 2;
		VkDescriptorPoolSize PoolSizes[2];

		PoolSizes[0].descriptorCount = ChemistrySimplifiedMolecularBuffersCount;
		PoolSizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

		PoolSizes[1].descriptorCount = ChemistrySimplifiedMolecularImagesCount;
		PoolSizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;

		VkDescriptorPoolCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		Info.maxSets = 1 * pGraphicsWindow->CurrentFrameBuffersSize;
		Info.poolSizeCount = PoolSizesSize;
		Info.pPoolSizes = PoolSizes;
		if ((res = vkCreateDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkDescriptorPoolCompute)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_SimplifiedMolecular()", "vkCreateDescriptorPool, VkResult == ", res);
			return;
		}
	}

	uint32_t layoutsSize = 1;
	VkDescriptorSetLayout layouts[1] = { pEffect->VkDescriptorSetLayoutCompute };
	VkDescriptorSet sets[1];

	VkDescriptorSetAllocateInfo Info;
	memset(&Info, NULL, sizeof(Info));
	Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	Info.descriptorPool = pEffect->VkDescriptorPoolCompute;
	Info.descriptorSetCount = layoutsSize;
	Info.pSetLayouts = layouts;
	Info.pNext = NULL;
	if ((res = vkAllocateDescriptorSets(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, sets)) != VK_SUCCESS)
	{
		Engine_Ref_FunctionError("ReCreate_SimplifiedMolecular()", "vkAllocateDescriptorSets, VkResult == ", res);
		return;
	}
	pEffect->VkDescriptorSetCompute = sets[0];


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipelines
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{//pipeline h0k
		VkComputePipelineCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pEffect->VkShaderCompute;
		Info.stage.pName = "main";
		Info.layout = pEffect->VkPipelineLayoutCompute;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipelineCompute)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_SimplifiedMolecular()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return;
		}
	}


	{
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

		const SPIRV Vertex[] = VertexShaderSimplifiedMolecular();
		const SPIRV Fragment[] = FragmentShaderSimplifiedMolecular();

		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderVertexParticle, Vertex, VertexShaderSimplifiedMolecularSize, "ReCreate_SimplifiedMolecular()");
		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderFragmentParticle, Fragment, FragmentShaderSimplifiedMolecularSize, "ReCreate_SimplifiedMolecular()");

		uint32_t ShaderCount = 2;
		VkPipelineShaderStageCreateInfo ShaderStages[2];
		memset(ShaderStages, NULL, sizeof(*ShaderStages)* ShaderCount);
		ShaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		ShaderStages[0].module = pEffect->VkShaderVertexParticle;
		ShaderStages[0].pName = "main";

		ShaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		ShaderStages[1].module = pEffect->VkShaderFragmentParticle;
		ShaderStages[1].pName = "main";

		uint64_t InputBindingDescsSize = 1;
		VkVertexInputBindingDescription InputBindingDescs[1];
		uint64_t InputAttribDescsSize = 5;
		VkVertexInputAttributeDescription InputAttribDescs[5];

		//Buffer Binding Main
		InputBindingDescs[0].binding = 0;
		InputBindingDescs[0].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
		InputBindingDescs[0].stride = sizeof(GPU_Particle);
		//Attributes
		//Position
		InputAttribDescs[0].binding = 0;
		InputAttribDescs[0].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		InputAttribDescs[0].location = 0;
		InputAttribDescs[0].offset = offsetof(GPU_Particle, Position);
		//PositionVelocity
		InputAttribDescs[1].binding = 0;
		InputAttribDescs[1].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		InputAttribDescs[1].location = 1;
		InputAttribDescs[1].offset = offsetof(GPU_Particle, PositionVelocity);
		//Rotation
		InputAttribDescs[2].binding = 0;
		InputAttribDescs[2].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		InputAttribDescs[2].location = 2;
		InputAttribDescs[2].offset = offsetof(GPU_Particle, Rotation);
		//RotationVelocity
		InputAttribDescs[3].binding = 0;
		InputAttribDescs[3].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		InputAttribDescs[3].location = 3;
		InputAttribDescs[3].offset = offsetof(GPU_Particle, RotationVelocity);
		//size
		InputAttribDescs[4].binding = 0;
		InputAttribDescs[4].format = VK_FORMAT_R32G32B32A32_SFLOAT;
		InputAttribDescs[4].location = 4;
		InputAttribDescs[4].offset = offsetof(GPU_Particle, Size);


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
		Info.layout = ((GraphicsUtils*)GraphicsRes.pUtils)->GenericResources[Graphics_Ref_Get_DeviceIndex(pGraphicsWindow->pLogicalDevice)].PipelineLayout2D;
		Info.renderPass = pGraphicsWindow->VkRenderPassDeferred;
		//Info.subpass = 1;
		Info.basePipelineHandle = VK_NULL_HANDLE; // Optional
		Info.basePipelineIndex = -1; // Optional

		if ((res = vkCreateGraphicsPipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipelineParticle)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_Generic2D()", "vkCreateGraphicsPipelines Failed. VkResult == ", res);
			return;
		}
	}

	/*
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Rendering
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	VkCommandPool VkCmdPool = NULL;
	VkCommandBuffer VkCmdBuffer = NULL;
	{
		VkCommandPoolCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		Info.queueFamilyIndex = pGraphicsWindow->pLogicalDevice->ComputeQueueFamilyIndex;
		Info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
		if ((res = vkCreateCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &VkCmdPool)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateCommandPool Failed, VkResult == ", res);
			return;
		}
	}
	{
		VkCommandBufferAllocateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		Info.commandPool = VkCmdPool;
		Info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		Info.commandBufferCount = 1;
		Info.pNext = NULL;
		if ((res = vkAllocateCommandBuffers(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, &VkCmdBuffer)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkAllocateCommandBuffers Failed, VkResult == ", res);
			return;
		}
	}
	{
		VkCommandBufferBeginInfo BeginInfo;
		memset(&BeginInfo, NULL, sizeof(BeginInfo));
		BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		BeginInfo.pInheritanceInfo = NULL;
		BeginInfo.pNext = NULL;
		if ((res = vkBeginCommandBuffer(VkCmdBuffer, &BeginInfo)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkBeginCommandBuffer Failed, VkResult == ", res);
			return;
		}
	}

	{//h0k
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pResourceHeader->Textureh0k.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = 0;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}
		vkCmdBindPipeline(VkCmdBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pResourceHeader->VkPipelineh0k);

		uint8_t pushconstantbuffer[sizeof(WaterPushConstants)];
		WaterPushConstants PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		glm_vec2_copy(pResourceHeader->FlowDirection, PushConstants.FlowDirection);
		PushConstants.WaterResolution = pResourceHeader->WaterResolution;
		PushConstants.WaterL = pResourceHeader->WaterL;
		PushConstants.WaterAmplitude = pResourceHeader->WaterAmplitude;
		PushConstants.WaterIntensity = pResourceHeader->WaterIntensity;
		PushConstants.Waterl = pResourceHeader->Waterl;
		PushConstants.Time = pResourceHeader->Time;
		PushConstants.ButterflyStage = 0;
		PushConstants.ButterflyDirection = 0;
		PushConstants.PingPongIndex = 0;

		memcpy(pushconstantbuffer, &PushConstants, sizeof(PushConstants));
		vkCmdPushConstants(VkCmdBuffer, pResourceHeader->VkPipelineLayouth0k, VK_SHADER_STAGE_COMPUTE_BIT, 0,
			pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &pushconstantbuffer);

		vkCmdBindDescriptorSets(VkCmdBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
			pResourceHeader->VkPipelineLayouth0k, 0, 1, &pResourceHeader->VkDescriptorSeth0k, 0, NULL);
		vkCmdDispatch(VkCmdBuffer, pResourceHeader->WaterResolution / 16, pResourceHeader->WaterResolution / 16, 1);
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pResourceHeader->Textureh0k.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}
	}
	{//twiddlefactors
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pResourceHeader->TextureTwiddleFactors.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = 0;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}

		vkCmdBindPipeline(VkCmdBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pResourceHeader->VkPipelineTwiddleFactors);

		uint8_t pushconstantbuffer[sizeof(WaterPushConstants)];
		WaterPushConstants PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		glm_vec2_copy(pResourceHeader->FlowDirection, PushConstants.FlowDirection);
		PushConstants.WaterResolution = pResourceHeader->WaterResolution;
		PushConstants.WaterL = pResourceHeader->WaterL;
		PushConstants.WaterAmplitude = pResourceHeader->WaterAmplitude;
		PushConstants.WaterIntensity = pResourceHeader->WaterIntensity;
		PushConstants.Waterl = pResourceHeader->Waterl;
		PushConstants.Time = pResourceHeader->Time;
		PushConstants.ButterflyStage = 0;
		PushConstants.ButterflyDirection = 0;
		PushConstants.PingPongIndex = 0;

		memcpy(pushconstantbuffer, &PushConstants, sizeof(PushConstants));
		vkCmdPushConstants(VkCmdBuffer, pResourceHeader->VkPipelineLayoutTwiddleFactors, VK_SHADER_STAGE_COMPUTE_BIT, 0,
			pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &pushconstantbuffer);

		vkCmdBindDescriptorSets(VkCmdBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
			pResourceHeader->VkPipelineLayoutTwiddleFactors, 0, 1, &pResourceHeader->VkDescriptorSetTwiddleFactors, 0, NULL);
		vkCmdDispatch(VkCmdBuffer, log_2_N, pResourceHeader->WaterResolution / 16, 1);
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pResourceHeader->TextureTwiddleFactors.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				0, NULL,
				1, &Barrier
			);
		}
	}

	//end
	vkEndCommandBuffer(VkCmdBuffer);

	uint32_t QueueIndex = 0;
	{
		bool found = false;
		while (found == false)
		{
			for (size_t i = 0; i < pGraphicsWindow->pLogicalDevice->ComputeQueueFamilySize; i++)
			{
				if (Engine_Ref_TryLock_Mutex(pGraphicsWindow->pLogicalDevice->ComputeQueueMutexes[i]) == Success)
				{
					QueueIndex = i;
					found = true;
					break;
				}
			}
		}
	}
	VkQueue Queue = NULL;
	vkGetDeviceQueue(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pGraphicsWindow->pLogicalDevice->ComputeQueueFamilyIndex, QueueIndex, &Queue);

	VkSubmitInfo SubmitInfo;
	memset(&SubmitInfo, NULL, sizeof(SubmitInfo));
	SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.commandBufferCount = (uint32_t)1;
	SubmitInfo.pCommandBuffers = &VkCmdBuffer;

	if ((res = vkQueueSubmit(Queue, 1, &SubmitInfo, VK_NULL_HANDLE)) != VK_SUCCESS)
	{
		Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkQueueSubmit Failed, VkResult == ", res);
		return;
	}

	vkQueueWaitIdle(Queue);
	Engine_Ref_Unlock_Mutex(pGraphicsWindow->pLogicalDevice->ComputeQueueMutexes[QueueIndex]);

	vkFreeCommandBuffers(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VkCmdPool, 1, &VkCmdBuffer);
	vkDestroyCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VkCmdPool, NULL);

	*/
}

void ReCreate_QuantumAtomic(ElementGraphics* pElement, ChemistryEffectQuantumAtomic* pEffect, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_QuantumAtomic()", "pElement == NULLPTR");
		return;
	}
	if (pEffect == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_QuantumAtomic()", "pEffect == NULLPTR");
		return;
	}
#endif
	VkResult res = VK_SUCCESS;
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//DescriptorLayout
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		VkDescriptorSetLayoutBinding BindingsQuantum[ChemistryQuantumAtomicBuffersCount];
		for (size_t i = 0; i < ChemistryQuantumAtomicBuffersCount; i++)
		{
			BindingsQuantum[i].binding = i;
			BindingsQuantum[i].descriptorCount = 1;
			BindingsQuantum[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			BindingsQuantum[i].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
			BindingsQuantum[i].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)ChemistryQuantumAtomicBuffersCount;
		Info.pBindings = BindingsQuantum;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkDescriptorSetLayoutQuantum)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_QuantumAtomic()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipeline Layouts
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		VkDescriptorSetLayout layouts[1] = { pEffect->VkDescriptorSetLayoutQuantum };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_ALL;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkPipelineLayoutQuantum)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_QuantumAtomic()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Descriptor Pool
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{//pool
		uint32_t PoolSizesSize = 1;
		VkDescriptorPoolSize PoolSizes[1];

		PoolSizes[0].descriptorCount = ChemistryQuantumAtomicBuffersCount;
		PoolSizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

		VkDescriptorPoolCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		Info.maxSets = 1 * pGraphicsWindow->CurrentFrameBuffersSize;
		Info.poolSizeCount = PoolSizesSize;
		Info.pPoolSizes = PoolSizes;
		if ((res = vkCreateDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkDescriptorPoolQuantum)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_QuantumAtomic()", "vkCreateDescriptorPool, VkResult == ", res);
			return;
		}
	}
	pEffect->VkDescriptorSetsQuantum = calloc(pGraphicsWindow->CurrentFrameBuffersSize, sizeof(*pEffect->VkDescriptorSetsQuantum));
	for (size_t i = 0; i < pGraphicsWindow->CurrentFrameBuffersSize; i++)
	{
		uint32_t layoutsSize = 1;
		VkDescriptorSetLayout layouts[1] = { pEffect->VkDescriptorSetLayoutQuantum };
		VkDescriptorSet sets[1];

		VkDescriptorSetAllocateInfo Info;
		memset(&Info, NULL, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		Info.descriptorPool = pEffect->VkDescriptorPoolQuantum;
		Info.descriptorSetCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pNext = NULL;
		if ((res = vkAllocateDescriptorSets(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, sets)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_QuantumAtomic()", "vkAllocateDescriptorSets, VkResult == ", res);
			return;
		}
		pEffect->VkDescriptorSetsQuantum[i] = sets[0];
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipeline
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	const SPIRV Vertex[] = VertexShaderQuantum();
	const SPIRV Fragment[] = FragmentShaderQuantum();

	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderVertexQuantum, Vertex, VertexShaderQuantumSize, "ReCreate_QuantumAtomic()");
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderFragmentQuantum, Fragment, FragmentShaderQuantumSize, "ReCreate_QuantumAtomic()");

	uint32_t ShaderStagesCount = 2;
	VkPipelineShaderStageCreateInfo ShaderStages[2];
	memset(&ShaderStages, NULL, sizeof(*ShaderStages) * ShaderStagesCount);

	ShaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
	ShaderStages[0].module = pEffect->VkShaderVertexQuantum;
	ShaderStages[0].pName = "main";

	ShaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	ShaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	ShaderStages[1].module = pEffect->VkShaderFragmentQuantum;
	ShaderStages[1].pName = "main";



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
		VkPipelineVertexInputStateCreateInfo VertexInputState;
		memset(&VertexInputState, NULL, sizeof(VertexInputState));
		VertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		VkPipelineInputAssemblyStateCreateInfo InputAssemblyState;
		memset(&InputAssemblyState, NULL, sizeof(InputAssemblyState));
		InputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		InputAssemblyState.primitiveRestartEnable = VK_FALSE;

		VkPipelineRasterizationStateCreateInfo RasterizationState;
		memset(&RasterizationState, NULL, sizeof(RasterizationState));
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

		VkGraphicsPipelineCreateInfo Info;
		memset(&Info, NULL, sizeof(Info));

		Info.subpass = 0;
		ColourBlending.attachmentCount = 4;

		Info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		Info.stageCount = ShaderStagesCount;
		Info.pStages = ShaderStages;
		Info.pVertexInputState = &VertexInputState;
		Info.pInputAssemblyState = &InputAssemblyState;
		Info.pViewportState = &ViewportState;
		Info.pRasterizationState = &RasterizationState;
		Info.pMultisampleState = &MultisampleState;
		Info.pDepthStencilState = &DepthStencil; // Optional
		Info.pColorBlendState = &ColourBlending;
		Info.pDynamicState = &DynamicStates; // Optional
		Info.layout = pEffect->VkPipelineLayoutQuantum;
		Info.renderPass = pGraphicsWindow->VkRenderPassDeferred;
		Info.basePipelineHandle = VK_NULL_HANDLE; // Optional
		Info.basePipelineIndex = -1; // Optional

		if ((res = vkCreateGraphicsPipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, NULL, 1, &Info, NULL, &pEffect->VkPipelineQuantum)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_GraphicsWindowHeader()", "vkCreateGraphicsPipelines Failed, VkResult == ", res);
			return;
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
		memset(&pCopiedEffect->mutex, NULL, sizeof(pCopiedEffect->mutex));

		memset(&pCopiedEffect->VkPipelineCompute, NULL, sizeof(pCopiedEffect->VkPipelineCompute));
		memset(&pCopiedEffect->VkPipelineLayoutCompute, NULL, sizeof(pCopiedEffect->VkPipelineLayoutCompute));

		memset(&pCopiedEffect->VkDescriptorSetLayoutCompute, NULL, sizeof(pCopiedEffect->VkDescriptorSetLayoutCompute));
		memset(&pCopiedEffect->VkDescriptorSetCompute, NULL, sizeof(pCopiedEffect->VkDescriptorSetCompute));
		memset(&pCopiedEffect->VkDescriptorPoolCompute, NULL, sizeof(pCopiedEffect->VkDescriptorPoolCompute));

		memset(&pCopiedEffect->VkShaderCompute, NULL, sizeof(pCopiedEffect->VkShaderCompute));


		memset(&pCopiedEffect->VkPipelineParticle, NULL, sizeof(pCopiedEffect->VkPipelineParticle));
		memset(&pCopiedEffect->VkShaderVertexParticle, NULL, sizeof(pCopiedEffect->VkShaderVertexParticle));
		memset(&pCopiedEffect->VkShaderFragmentParticle, NULL, sizeof(pCopiedEffect->VkShaderFragmentParticle));
		if (pEffect->Particles != NULL)
		{
			memcpy(((void*)((uint64_t)pData + (uint64_t)*pBufferPointer)), pEffect->Particles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));
			pCopiedEffect->Particles = *pBufferPointer;
			*pBufferPointer += pEffect->ParticlesSize * sizeof(*pEffect->Particles);
		}
	}
	else
	{
		*pBufferPointer += pEffect->ParticlesSize * sizeof(*pEffect->Particles);
	}
}

void Pack_QuantumAtomic(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const ChemistryEffectQuantumAtomic* pEffect, ChemistryEffectQuantumAtomic* pCopiedEffect, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedEffect->VkPipelineQuantum, NULL, sizeof(pCopiedEffect->VkPipelineQuantum));
		memset(&pCopiedEffect->VkPipelineLayoutQuantum, NULL, sizeof(pCopiedEffect->VkPipelineLayoutQuantum));

		memset(&pCopiedEffect->VkDescriptorSetLayoutQuantum, NULL, sizeof(pCopiedEffect->VkDescriptorSetLayoutQuantum));
		memset(&pCopiedEffect->VkDescriptorSetsQuantum, NULL, sizeof(pCopiedEffect->VkDescriptorSetsQuantum));
		memset(&pCopiedEffect->VkDescriptorPoolQuantum, NULL, sizeof(pCopiedEffect->VkDescriptorPoolQuantum));

		memset(&pCopiedEffect->VkShaderVertexQuantum, NULL, sizeof(pCopiedEffect->VkShaderVertexQuantum));
		memset(&pCopiedEffect->VkShaderFragmentQuantum, NULL, sizeof(pCopiedEffect->VkShaderFragmentQuantum));
		if (pEffect->GPU_Atoms != NULL)
		{
			memcpy(((void*)((uint64_t)pData + (uint64_t)*pBufferPointer)), pEffect->GPU_Atoms, pEffect->GPU_AtomsSize * sizeof(*pEffect->GPU_Atoms));
			pCopiedEffect->GPU_Atoms = *pBufferPointer;
			*pBufferPointer += pEffect->GPU_AtomsSize * sizeof(*pEffect->GPU_Atoms);
		}
		if (pEffect->GPU_Electrons != NULL)
		{
			memcpy(((void*)((uint64_t)pData + (uint64_t)*pBufferPointer)), pEffect->GPU_Electrons, pEffect->GPU_ElectronsSize * sizeof(*pEffect->GPU_Electrons));
			pCopiedEffect->GPU_Electrons = *pBufferPointer;
			*pBufferPointer += pEffect->GPU_ElectronsSize * sizeof(*pEffect->GPU_Electrons);
		}
	}
	else
	{
		*pBufferPointer += pEffect->GPU_AtomsSize * sizeof(*pEffect->GPU_Atoms);
		*pBufferPointer += pEffect->GPU_ElectronsSize * sizeof(*pEffect->GPU_Electrons);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect UnPackers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UnPack_SimplifiedMolecular(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const ChemistryEffectSimplifiedMolecular* pEffect, ChemistryEffectSimplifiedMolecular* pCopiedEffect, const void* pData, uint32_t ThreadIndex)
{
	if (pEffect->Particles != NULL)
	{
		pCopiedEffect->Particles = (UTF8*)calloc(pCopiedEffect->ParticlesSize, sizeof(*pCopiedEffect->Particles));
		memcpy(pCopiedEffect->Particles, ((void*)((uint64_t)pData + (uint64_t)pEffect->Particles)), pEffect->ParticlesSize * sizeof(*pEffect->Particles));
	}
	ReCreate_SimplifiedMolecular(pCopiedElement, pCopiedEffect, ThreadIndex);
}

void UnPack_QuantumAtomic(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const ChemistryEffectQuantumAtomic* pEffect, ChemistryEffectQuantumAtomic* pCopiedEffect, const void* pData, uint32_t ThreadIndex)
{
	if (pEffect->GPU_Atoms != NULL)
	{
		pCopiedEffect->GPU_Atoms = (UTF8*)calloc(pCopiedEffect->GPU_AtomsSize, sizeof(*pCopiedEffect->GPU_Atoms));
		memcpy(pCopiedEffect->GPU_Atoms, ((void*)((uint64_t)pData + (uint64_t)pEffect->GPU_Atoms)), pEffect->GPU_AtomsSize * sizeof(*pEffect->GPU_Atoms));
	}
	if (pEffect->GPU_Electrons != NULL)
	{
		pCopiedEffect->GPU_Electrons = (UTF8*)calloc(pCopiedEffect->GPU_ElectronsSize, sizeof(*pCopiedEffect->GPU_Electrons));
		memcpy(pCopiedEffect->GPU_Electrons, ((void*)((uint64_t)pData + (uint64_t)pEffect->GPU_Electrons)), pEffect->GPU_ElectronsSize * sizeof(*pEffect->GPU_Electrons));
	}
	ReCreate_QuantumAtomic(pCopiedElement, pCopiedEffect, ThreadIndex);
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
		EffectInfo->SimulationResolution = EffectCreateInfo->SimulationResolution;

		glm_vec3_copy(EffectCreateInfo->Position, EffectInfo->Position);
		if (EffectCreateInfo->ParticlesSize != NULL)
		{
			EffectInfo->ParticlesSize = EffectCreateInfo->ParticlesSize;
			EffectInfo->Particles = calloc(EffectInfo->ParticlesSize, sizeof(*EffectInfo->Particles));
			memcpy(EffectInfo->Particles, EffectCreateInfo->Particles, EffectInfo->ParticlesSize * sizeof(*EffectInfo->Particles));
		}
		ReCreate_SimplifiedMolecular(pElement, EffectInfo, ThreadIndex);
	}
	*pAllocationSize = sizeof(ChemistryEffectSimplifiedMolecular);
	return (TEXRESULT)Success;
}

TEXRESULT Create_QuantumAtomic(ElementGraphics* pElement, ChemistryEffectQuantumAtomic* EffectInfo, ChemistryEffectCreateInfoQuantumAtomic* EffectCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (EffectInfo == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (EffectCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_QuantumAtomic()", "EffectCreateInfo == NULLPTR");
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
		if (EffectCreateInfo->ElectronsSize != NULL)
		{
			EffectInfo->GPU_ElectronsSize = EffectCreateInfo->ElectronsSize;
			EffectInfo->GPU_Electrons = calloc(EffectInfo->GPU_ElectronsSize, sizeof(*EffectInfo->GPU_Electrons));
			memcpy(EffectInfo->GPU_Electrons, EffectCreateInfo->Electrons, EffectInfo->GPU_ElectronsSize * sizeof(*EffectInfo->GPU_Electrons));
		}
		ReCreate_QuantumAtomic(pElement, EffectInfo, ThreadIndex);
	}
	*pAllocationSize = sizeof(ChemistryEffectQuantumAtomic);
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
	Utils.SimplifiedMolecularSignature.DrawSignature = &DrawSignature_SimplifiedMolecular;
	Utils.SimplifiedMolecularSignature.SignatureGPUBuffersSize = ChemistrySimplifiedMolecularBuffersCount;
	Graphics_Effects_Ref_Register_GraphicsEffectSignature(&Utils.SimplifiedMolecularSignature);

	Utils.QuantumAtomicSignature.Identifier = (uint32_t)ChemistryEffects_QuantumAtomic;
	Utils.QuantumAtomicSignature.Constructor = (Create_GraphicsEffectTemplate*)&Create_QuantumAtomic;
	Utils.QuantumAtomicSignature.ReConstructor = (ReCreate_GraphicsEffectTemplate*)&ReCreate_QuantumAtomic;
	Utils.QuantumAtomicSignature.Destructor = (Destroy_GraphicsEffectTemplate*)&Destroy_QuantumAtomic;
	Utils.QuantumAtomicSignature.Packer = (Pack_GraphicsEffectTemplate*)&Pack_QuantumAtomic;
	Utils.QuantumAtomicSignature.UnPacker = (UnPack_GraphicsEffectTemplate*)&UnPack_QuantumAtomic;
	Utils.QuantumAtomicSignature.Update = (Update_GraphicsEffectTemplate*)&Update_QuantumAtomic;
	Utils.QuantumAtomicSignature.Draw = (Draw_GraphicsEffectTemplate*)&Draw_QuantumAtomic;
	Utils.QuantumAtomicSignature.UpdateSignature = &UpdateSignature_QuantumAtomic;
	Utils.QuantumAtomicSignature.DrawSignature = &DrawSignature_QuantumAtomic;
	Utils.QuantumAtomicSignature.SignatureGPUBuffersSize = ChemistryQuantumAtomicBuffersCount; //storagebuffer atom, storagebuffer electron.
	Graphics_Effects_Ref_Register_GraphicsEffectSignature(&Utils.QuantumAtomicSignature);

	return (TEXRESULT)(Success);
}

void Destroy_Chemistry()
{
	//Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.SimplifiedMolecularSignature);

	//Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.QuantumAtomicSignature);

}

void Update_Chemistry()
{	
	
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
	//Audio_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	Graphics_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	//Network_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	//GUI_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);
	//Formats_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);

	//exports
	//Resources
	ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData((void*)"Chemistry::Utils"), &ChemistryRes.pUtils, &Utils);

	//functions
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chemistry::Initialise_Chemistry"), &ChemistryRes.pInitialise_Chemistry, &Initialise_Chemistry, Construct, 10.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chemistry::Destroy_Chemistry"), &ChemistryRes.pDestroy_Chemistry, &Destroy_Chemistry, Destruct, 100.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData("Chemistry::Update_Chemistry"), &ChemistryRes.pUpdate_Chemistry, &Update_Chemistry, EveryFrame, 0.01f, 0, NULL);


}


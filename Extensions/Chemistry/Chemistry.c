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
//SimpleModel Shaders
///////////////////////////////////////////////////////////////////////////////////////////////

typedef enum VertexShaderSimpleModelVariables {
	VertexSimpleModelExtension_GLSL450 = 1,
	VertexSimpleModelFunction_Main,

	//BASIC TYPES
	VertexSimpleModelType_Void,
	VertexSimpleModelType_Function,

	VertexSimpleModelType_float32,
	VertexSimpleModelType_float32vec2,
	VertexSimpleModelType_float32vec3,
	VertexSimpleModelType_float32vec4,
	VertexSimpleModelType_float32mat4,

	VertexSimpleModelType_int32,

	//CONSTANTS
	VertexSimpleModelConstant_float32_0f,
	VertexSimpleModelConstant_float32_1f,

	VertexSimpleModelConstant_int_0,
	VertexSimpleModelConstant_int_1,

	//INPUT
	//Input Attributes
	VertexSimpleModelType_InputPointer_float32,
	VertexSimpleModelType_InputPointer_float32vec3,
	VertexSimpleModelType_InputPointer_float32vec4,

	VertexSimpleModelVariable_InputPointer_float32vec3_Position,
	VertexSimpleModelVariable_InputPointer_float32vec3_PositionVelocity,
	VertexSimpleModelVariable_InputPointer_float32vec4_Rotation,
	VertexSimpleModelVariable_InputPointer_float32vec4_RotationVelocity,
	VertexSimpleModelVariable_InputPointer_float32_Size,
	//BuiltIn
	VertexSimpleModelType_InputPointer_int32,
	VertexSimpleModelVariable_InputPointer_VertexIndex,
	VertexSimpleModelVariable_InputPointer_InstanceIndex,
	//PushConstants
	VertexSimpleModelType_struct_PushConstants,
	VertexSimpleModelType_PushConstantPointer_struct_PushConstants,
	VertexSimpleModelVariable_PushConstantPointer_struct_PushConstants,
	VertexSimpleModelType_PushConstantPointer_float32mat4,

	//OUTPUT
	//Output Attributes
	VertexSimpleModelType_OutputPointer_float32,
	VertexSimpleModelType_OutputPointer_float32vec3,
	VertexSimpleModelType_OutputPointer_float32vec4,

	VertexSimpleModelConstant_float32vec3_NULL,
	VertexSimpleModelConstant_float32vec4_NULL,

	VertexSimpleModelVariable_OutputPointer_float32vec3_Position,
	VertexSimpleModelVariable_OutputPointer_float32vec3_PositionVelocity,
	VertexSimpleModelVariable_OutputPointer_float32vec4_Rotation,
	VertexSimpleModelVariable_OutputPointer_float32vec4_RotationVelocity,
	VertexSimpleModelVariable_OutputPointer_float32_Size,
	//BuiltIn
	VertexSimpleModelType_float32_Array_1,
	VertexSimpleModelType_struct_BuiltIn,
	VertexSimpleModelType_OutputPointer_struct_BuiltIn,
	VertexSimpleModelVariable_OutputPointer_struct_BuiltIn,
	VertexSimpleModelVariable_OutputPointer_float32vec4_Position,
	VertexSimpleModelVariable_OutputPointer_float32_PointSize,

	//MAIN FUNCTION
	VertexSimpleModelLabel_Start,

	VertexSimpleModelVariable_PushConstantPointer_MatrixVP,
	VertexSimpleModelLoadedVariable_PushConstantPointer_MatrixVP,


	VertexSimpleModelLoadedVariable_float32vec3_Position,
	VertexSimpleModelLoadedVariable_float32vec3_PositionVelocity,
	VertexSimpleModelLoadedVariable_float32vec4_Rotation,
	VertexSimpleModelLoadedVariable_float32vec4_RotationVelocity,
	VertexSimpleModelLoadedVariable_float32_Size,


	VertexSimpleModelLoadedVariable_float32vec2_op0,
	VertexSimpleModelLoadedVariable_float32vec4_op0,
	VertexSimpleModelLoadedVariable_float32vec4_op1,

	VertexSimpleModelLoadedVariable_float32_op0,
	VertexSimpleModelLoadedVariable_float32_op1,

	VertexSimpleModelVariables_MAX
}VertexShaderSimpleModelVariables;
#define VertexShaderSimpleModelSize (395 * sizeof(SPIRV))
#define VertexShaderSimpleModel() {\
SPIRV_Header(VertexSimpleModelVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, VertexSimpleModelExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(19<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelVertex, VertexSimpleModelFunction_Main, 'niam', '\0',\
VertexSimpleModelVariable_InputPointer_float32vec3_Position, VertexSimpleModelVariable_InputPointer_float32vec3_PositionVelocity, VertexSimpleModelVariable_InputPointer_float32vec4_Rotation, VertexSimpleModelVariable_InputPointer_float32vec4_RotationVelocity, VertexSimpleModelVariable_InputPointer_float32_Size,\
VertexSimpleModelVariable_OutputPointer_float32vec3_Position, VertexSimpleModelVariable_OutputPointer_float32vec3_PositionVelocity, VertexSimpleModelVariable_OutputPointer_float32vec4_Rotation, VertexSimpleModelVariable_OutputPointer_float32vec4_RotationVelocity, VertexSimpleModelVariable_OutputPointer_float32_Size,\
VertexSimpleModelVariable_InputPointer_VertexIndex, VertexSimpleModelVariable_InputPointer_InstanceIndex, VertexSimpleModelVariable_PushConstantPointer_struct_PushConstants, VertexSimpleModelVariable_OutputPointer_struct_BuiltIn,\
/*DECORATION*/\
/*INPUT*/\
/*Input Attributes*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_InputPointer_float32vec3_Position, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_InputPointer_float32vec3_PositionVelocity, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_InputPointer_float32vec4_Rotation, SpvDecorationLocation, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_InputPointer_float32vec4_RotationVelocity, SpvDecorationLocation, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_InputPointer_float32_Size, SpvDecorationLocation, 4,\
/*BuiltIn*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_InputPointer_VertexIndex, SpvDecorationBuiltIn, SpvBuiltInVertexIndex,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_InputPointer_InstanceIndex, SpvDecorationBuiltIn, SpvBuiltInInstanceIndex,\
/*PushConstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimpleModelType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimpleModelType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimpleModelType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimpleModelType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
/*Output Attributes*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_OutputPointer_float32vec3_Position, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_OutputPointer_float32vec3_PositionVelocity, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_OutputPointer_float32vec4_Rotation, SpvDecorationLocation, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_OutputPointer_float32vec4_RotationVelocity, SpvDecorationLocation, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelVariable_OutputPointer_float32_Size, SpvDecorationLocation, 4,\
/*BuiltIn*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimpleModelType_struct_BuiltIn, 0, SpvDecorationBuiltIn, SpvBuiltInPosition,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimpleModelType_struct_BuiltIn, 1, SpvDecorationBuiltIn, SpvBuiltInPointSize,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimpleModelType_struct_BuiltIn, 2, SpvDecorationBuiltIn, SpvBuiltInClipDistance,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexSimpleModelType_struct_BuiltIn, 3, SpvDecorationBuiltIn, SpvBuiltInCullDistance,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexSimpleModelType_struct_BuiltIn, SpvDecorationBlock,\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, VertexSimpleModelType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, VertexSimpleModelType_Function, VertexSimpleModelType_Void,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, VertexSimpleModelType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexSimpleModelType_float32vec2, VertexSimpleModelType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexSimpleModelType_float32vec3, VertexSimpleModelType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexSimpleModelType_float32vec4, VertexSimpleModelType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, VertexSimpleModelType_float32mat4, VertexSimpleModelType_float32vec4, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, VertexSimpleModelType_int32, 32, 1,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, VertexSimpleModelType_float32, VertexSimpleModelConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexSimpleModelType_float32, VertexSimpleModelConstant_float32_1f, 1065353216,\
\
(4<<SpvWordCountShift)|SpvOpConstant, VertexSimpleModelType_int32, VertexSimpleModelConstant_int_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexSimpleModelType_int32, VertexSimpleModelConstant_int_1, 1,\
/*INPUT*/\
/*PushConstants*/\
(4<<SpvWordCountShift)|SpvOpTypeStruct, VertexSimpleModelType_struct_PushConstants, VertexSimpleModelType_float32mat4, VertexSimpleModelType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimpleModelType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, VertexSimpleModelType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_PushConstantPointer_struct_PushConstants, VertexSimpleModelVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimpleModelType_PushConstantPointer_float32mat4, SpvStorageClassPushConstant, VertexSimpleModelType_float32mat4,\
/*BuiltIn*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimpleModelType_InputPointer_int32, SpvStorageClassInput, VertexSimpleModelType_int32,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_InputPointer_int32, VertexSimpleModelVariable_InputPointer_VertexIndex, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_InputPointer_int32, VertexSimpleModelVariable_InputPointer_InstanceIndex, SpvStorageClassInput,\
/*Input Attributes*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimpleModelType_InputPointer_float32, SpvStorageClassInput, VertexSimpleModelType_float32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimpleModelType_InputPointer_float32vec3, SpvStorageClassInput, VertexSimpleModelType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimpleModelType_InputPointer_float32vec4, SpvStorageClassInput, VertexSimpleModelType_float32vec4,\
\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_InputPointer_float32vec3, VertexSimpleModelVariable_InputPointer_float32vec3_Position, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_InputPointer_float32vec3, VertexSimpleModelVariable_InputPointer_float32vec3_PositionVelocity, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_InputPointer_float32vec4, VertexSimpleModelVariable_InputPointer_float32vec4_Rotation, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_InputPointer_float32vec4, VertexSimpleModelVariable_InputPointer_float32vec4_RotationVelocity, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_InputPointer_float32, VertexSimpleModelVariable_InputPointer_float32_Size, SpvStorageClassInput,\
/*OUTPUT*/\
/*Output Attributes*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimpleModelType_OutputPointer_float32, SpvStorageClassOutput, VertexSimpleModelType_float32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimpleModelType_OutputPointer_float32vec3, SpvStorageClassOutput, VertexSimpleModelType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimpleModelType_OutputPointer_float32vec4, SpvStorageClassOutput, VertexSimpleModelType_float32vec4,\
\
(3<<SpvWordCountShift)|SpvOpConstantNull, VertexSimpleModelType_float32vec3, VertexSimpleModelConstant_float32vec3_NULL,\
(3<<SpvWordCountShift)|SpvOpConstantNull, VertexSimpleModelType_float32vec4, VertexSimpleModelConstant_float32vec4_NULL,\
\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_OutputPointer_float32vec3, VertexSimpleModelVariable_OutputPointer_float32vec3_Position, SpvStorageClassOutput, VertexSimpleModelConstant_float32vec3_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_OutputPointer_float32vec3, VertexSimpleModelVariable_OutputPointer_float32vec3_PositionVelocity, SpvStorageClassOutput, VertexSimpleModelConstant_float32vec3_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_OutputPointer_float32vec4, VertexSimpleModelVariable_OutputPointer_float32vec4_Rotation, SpvStorageClassOutput, VertexSimpleModelConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_OutputPointer_float32vec4, VertexSimpleModelVariable_OutputPointer_float32vec4_RotationVelocity, SpvStorageClassOutput, VertexSimpleModelConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_OutputPointer_float32, VertexSimpleModelVariable_OutputPointer_float32_Size, SpvStorageClassOutput, VertexSimpleModelConstant_float32_0f,\
/*BuiltIn*/\
(4<<SpvWordCountShift)|SpvOpTypeArray, VertexSimpleModelType_float32_Array_1, VertexSimpleModelType_float32, VertexSimpleModelConstant_int_1,\
(6<<SpvWordCountShift)|SpvOpTypeStruct, VertexSimpleModelType_struct_BuiltIn, VertexSimpleModelType_float32vec4, VertexSimpleModelType_float32, VertexSimpleModelType_float32_Array_1, VertexSimpleModelType_float32_Array_1,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexSimpleModelType_OutputPointer_struct_BuiltIn, SpvStorageClassOutput, VertexSimpleModelType_struct_BuiltIn,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexSimpleModelType_OutputPointer_struct_BuiltIn, VertexSimpleModelVariable_OutputPointer_struct_BuiltIn, SpvStorageClassOutput,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, VertexSimpleModelType_Void, VertexSimpleModelFunction_Main, SpvFunctionControlMaskNone, VertexSimpleModelType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, VertexSimpleModelLabel_Start,\
	/*Assign inputs to outputs and also load variables*/\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimpleModelType_float32vec3, VertexSimpleModelLoadedVariable_float32vec3_Position, VertexSimpleModelVariable_InputPointer_float32vec3_Position,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimpleModelVariable_OutputPointer_float32vec3_Position, VertexSimpleModelLoadedVariable_float32vec3_Position,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimpleModelType_float32vec3, VertexSimpleModelLoadedVariable_float32vec3_PositionVelocity, VertexSimpleModelVariable_InputPointer_float32vec3_PositionVelocity,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimpleModelVariable_OutputPointer_float32vec3_PositionVelocity, VertexSimpleModelLoadedVariable_float32vec3_PositionVelocity,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimpleModelType_float32vec4, VertexSimpleModelLoadedVariable_float32vec4_Rotation, VertexSimpleModelVariable_InputPointer_float32vec4_Rotation,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimpleModelVariable_OutputPointer_float32vec4_Rotation, VertexSimpleModelLoadedVariable_float32vec4_Rotation,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimpleModelType_float32vec4, VertexSimpleModelLoadedVariable_float32vec4_RotationVelocity, VertexSimpleModelVariable_InputPointer_float32vec4_RotationVelocity,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimpleModelVariable_OutputPointer_float32vec4_RotationVelocity, VertexSimpleModelLoadedVariable_float32vec4_RotationVelocity,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimpleModelType_float32, VertexSimpleModelLoadedVariable_float32_Size, VertexSimpleModelVariable_InputPointer_float32_Size,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimpleModelVariable_OutputPointer_float32_Size, VertexSimpleModelLoadedVariable_float32_Size,\
	/*get pushconstants VP matrix*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, VertexSimpleModelType_PushConstantPointer_float32mat4, VertexSimpleModelVariable_PushConstantPointer_MatrixVP, VertexSimpleModelVariable_PushConstantPointer_struct_PushConstants, VertexSimpleModelConstant_int_0,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexSimpleModelType_float32mat4, VertexSimpleModelLoadedVariable_PushConstantPointer_MatrixVP, VertexSimpleModelVariable_PushConstantPointer_MatrixVP,\
	/*out inbuilt position*/\
	(5<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexSimpleModelType_float32vec2, VertexSimpleModelLoadedVariable_float32vec2_op0, VertexSimpleModelConstant_float32_1f, VertexSimpleModelConstant_float32_1f,\
	(9<<SpvWordCountShift)|SpvOpVectorShuffle, VertexSimpleModelType_float32vec4, VertexSimpleModelLoadedVariable_float32vec4_op0, VertexSimpleModelLoadedVariable_float32vec3_Position, VertexSimpleModelLoadedVariable_float32vec2_op0, 0, 1, 2, 3,\
	\
	(5<<SpvWordCountShift)|SpvOpMatrixTimesVector, VertexSimpleModelType_float32vec4, VertexSimpleModelLoadedVariable_float32vec4_op1, VertexSimpleModelLoadedVariable_PushConstantPointer_MatrixVP, VertexSimpleModelLoadedVariable_float32vec4_op0,\
	\
	(5<<SpvWordCountShift)|SpvOpAccessChain, VertexSimpleModelType_OutputPointer_float32vec4, VertexSimpleModelVariable_OutputPointer_float32vec4_Position, VertexSimpleModelVariable_OutputPointer_struct_BuiltIn, VertexSimpleModelConstant_int_0,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimpleModelVariable_OutputPointer_float32vec4_Position, VertexSimpleModelLoadedVariable_float32vec4_op1,\
	/*pointsize*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, VertexSimpleModelType_OutputPointer_float32, VertexSimpleModelVariable_OutputPointer_float32_PointSize, VertexSimpleModelVariable_OutputPointer_struct_BuiltIn, VertexSimpleModelConstant_int_1,\
	(6<<SpvWordCountShift)|SpvOpExtInst, VertexSimpleModelType_float32, VertexSimpleModelLoadedVariable_float32_op0, VertexSimpleModelExtension_GLSL450, 31, VertexSimpleModelLoadedVariable_float32_Size,\
	(6<<SpvWordCountShift)|SpvOpExtInst, VertexSimpleModelType_float32, VertexSimpleModelLoadedVariable_float32_op1, VertexSimpleModelExtension_GLSL450, 31, VertexSimpleModelLoadedVariable_float32_op0,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexSimpleModelVariable_OutputPointer_float32_PointSize, VertexSimpleModelLoadedVariable_float32_op1,\
/*function end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

typedef enum FragmentShaderSimpleModelVariables {
	FragmentSimpleModelExtension_GLSL450 = 1,
	FragmentSimpleModelFunction_Main,

	//BASIC TYPES
	FragmentSimpleModelType_Void,
	FragmentSimpleModelType_Function,

	FragmentSimpleModelType_float32,
	FragmentSimpleModelType_float32vec2,
	FragmentSimpleModelType_float32vec3,
	FragmentSimpleModelType_float32vec4,
	FragmentSimpleModelType_float32mat4,

	FragmentSimpleModelType_int32,

	//CONSTANTS
	FragmentSimpleModelConstant_float32_0f,
	FragmentSimpleModelConstant_float32_1f,

	FragmentSimpleModelConstant_int32_0,

	//INPUT
	//Input Attributes
	FragmentSimpleModelType_InputPointer_float32,
	FragmentSimpleModelType_InputPointer_float32vec3,
	FragmentSimpleModelType_InputPointer_float32vec4,

	FragmentSimpleModelVariable_InputPointer_float32vec3_Position,
	FragmentSimpleModelVariable_InputPointer_float32vec3_PositionVelocity,
	FragmentSimpleModelVariable_InputPointer_float32vec4_Rotation,
	FragmentSimpleModelVariable_InputPointer_float32vec4_RotationVelocity,
	FragmentSimpleModelVariable_InputPointer_float32_Size,

	//PushConstants
	FragmentSimpleModelType_struct_PushConstants,
	FragmentSimpleModelType_PushConstantPointer_struct_PushConstants,
	FragmentSimpleModelVariable_PushConstantPointer_struct_PushConstants,
	FragmentSimpleModelType_PushConstantPointer_int32,

	//OUTPUT
	//Subpass Attachments
	FragmentSimpleModelType_OutputPointer_float32vec4,
	FragmentSimpleModelConstant_float32vec4_NULL,
	FragmentSimpleModelVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,
	FragmentSimpleModelVariable_OutputPointer_float32vec4_OutPositionOrRevealage,

	FragmentSimpleModelConstantComposite_float32vec4_SelectedColour,

	//MAIN FUNCTION
	FragmentSimpleModelLabel_Start,

	FragmentSimpleModelLoadedVariable_float32vec4_op0,

	FragmentSimpleModelVariables_MAX
}FragmentShaderSimpleModelVariables;
#define FragmentShaderSimpleModelSize (216 * sizeof(SPIRV))
#define FragmentShaderSimpleModel() {\
SPIRV_Header(FragmentSimpleModelVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityImageQuery,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, FragmentSimpleModelExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(13<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelFragment, FragmentSimpleModelFunction_Main, 'niam', '\0',\
FragmentSimpleModelVariable_InputPointer_float32vec3_Position, FragmentSimpleModelVariable_InputPointer_float32vec3_PositionVelocity, FragmentSimpleModelVariable_InputPointer_float32vec4_Rotation, FragmentSimpleModelVariable_InputPointer_float32vec4_RotationVelocity, FragmentSimpleModelVariable_InputPointer_float32_Size,\
FragmentSimpleModelVariable_PushConstantPointer_struct_PushConstants, FragmentSimpleModelVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, FragmentSimpleModelVariable_OutputPointer_float32vec4_OutPositionOrRevealage,\
(3<<SpvWordCountShift)|SpvOpExecutionMode, FragmentSimpleModelFunction_Main, SpvExecutionModeOriginUpperLeft,\
/*DECORATION*/\
/*INPUT*/\
/*Input Attributes*/\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimpleModelVariable_InputPointer_float32vec3_Position, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimpleModelVariable_InputPointer_float32vec3_PositionVelocity, SpvDecorationLocation, 1,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimpleModelVariable_InputPointer_float32vec4_Rotation, SpvDecorationLocation, 2,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimpleModelVariable_InputPointer_float32vec4_RotationVelocity, SpvDecorationLocation, 3,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimpleModelVariable_InputPointer_float32_Size, SpvDecorationLocation, 4,\
/*PushConstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimpleModelType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimpleModelType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimpleModelType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimpleModelType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentSimpleModelType_struct_PushConstants, 2, SpvDecorationOffset, 68,\
(3<<SpvWordCountShift)|SpvOpDecorate, FragmentSimpleModelType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
/*Output Attributes*/\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimpleModelVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentSimpleModelVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvDecorationLocation, 1,\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, FragmentSimpleModelType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, FragmentSimpleModelType_Function, FragmentSimpleModelType_Void,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, FragmentSimpleModelType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentSimpleModelType_float32vec2, FragmentSimpleModelType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentSimpleModelType_float32vec3, FragmentSimpleModelType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentSimpleModelType_float32vec4, FragmentSimpleModelType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, FragmentSimpleModelType_float32mat4, FragmentSimpleModelType_float32vec4, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, FragmentSimpleModelType_int32, 32, 1,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentSimpleModelType_float32, FragmentSimpleModelConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentSimpleModelType_float32, FragmentSimpleModelConstant_float32_1f, 1065353216,\
\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentSimpleModelType_int32, FragmentSimpleModelConstant_int32_0, 0,\
/*INPUT*/\
/*Input Attributes*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimpleModelType_InputPointer_float32, SpvStorageClassInput, FragmentSimpleModelType_float32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimpleModelType_InputPointer_float32vec3, SpvStorageClassInput, FragmentSimpleModelType_float32vec3,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimpleModelType_InputPointer_float32vec4, SpvStorageClassInput, FragmentSimpleModelType_float32vec4,\
\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimpleModelType_InputPointer_float32vec3, FragmentSimpleModelVariable_InputPointer_float32vec3_Position, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimpleModelType_InputPointer_float32vec3, FragmentSimpleModelVariable_InputPointer_float32vec3_PositionVelocity, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimpleModelType_InputPointer_float32vec4, FragmentSimpleModelVariable_InputPointer_float32vec4_Rotation, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimpleModelType_InputPointer_float32vec4, FragmentSimpleModelVariable_InputPointer_float32vec4_RotationVelocity, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimpleModelType_InputPointer_float32, FragmentSimpleModelVariable_InputPointer_float32_Size, SpvStorageClassInput,\
/*PushConstants*/\
(5<<SpvWordCountShift)|SpvOpTypeStruct, FragmentSimpleModelType_struct_PushConstants, FragmentSimpleModelType_float32mat4, FragmentSimpleModelType_int32, FragmentSimpleModelType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimpleModelType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, FragmentSimpleModelType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentSimpleModelType_PushConstantPointer_struct_PushConstants, FragmentSimpleModelVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimpleModelType_PushConstantPointer_int32, SpvStorageClassPushConstant, FragmentSimpleModelType_int32,\
/*OUTPUT*/\
/*Output Attributes*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentSimpleModelType_OutputPointer_float32vec4, SpvStorageClassOutput, FragmentSimpleModelType_float32vec4,\
\
(3<<SpvWordCountShift)|SpvOpConstantNull, FragmentSimpleModelType_float32vec4, FragmentSimpleModelConstant_float32vec4_NULL,\
\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentSimpleModelType_OutputPointer_float32vec4, FragmentSimpleModelVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvStorageClassOutput, FragmentSimpleModelConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentSimpleModelType_OutputPointer_float32vec4, FragmentSimpleModelVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvStorageClassOutput, FragmentSimpleModelConstant_float32vec4_NULL,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, FragmentSimpleModelType_Void, FragmentSimpleModelFunction_Main, SpvFunctionControlMaskNone, FragmentSimpleModelType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, FragmentSimpleModelLabel_Start,\
	/*Output Default Colour*/\
	(7<<SpvWordCountShift)|SpvOpCompositeConstruct, FragmentSimpleModelType_float32vec4, FragmentSimpleModelLoadedVariable_float32vec4_op0, FragmentSimpleModelConstant_float32_1f, FragmentSimpleModelConstant_float32_1f, FragmentSimpleModelConstant_float32_1f, FragmentSimpleModelConstant_float32_1f,\
	(3<<SpvWordCountShift)|SpvOpStore, FragmentSimpleModelVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, FragmentSimpleModelLoadedVariable_float32vec4_op0,\
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

///////////////////////////////////////////////////////////////////////////////////////////////
//Full Model Shaders
///////////////////////////////////////////////////////////////////////////////////////////////

typedef enum VertexShaderFullModelVariables {
	//VertexFullModelExtension_GLSL450,
	VertexFullModelFunction_Main = 1,

	//BASIC TYPES
	VertexFullModelType_Void,
	VertexFullModelType_Function,
	VertexFullModelType_bool,

	VertexFullModelType_float32,
	VertexFullModelType_float32vec2,
	VertexFullModelType_float32vec3,
	VertexFullModelType_float32vec4,
	VertexFullModelType_float32mat4,

	VertexFullModelType_uint32,
	VertexFullModelType_uint32vec2,
	VertexFullModelType_uint32vec3,
	VertexFullModelType_uint32vec4,

	VertexFullModelType_int32,
	VertexFullModelType_int32vec2,
	VertexFullModelType_int32vec3,
	VertexFullModelType_int32vec4,

	//CONSTANTS
	VertexFullModelConstant_float32_0f,
	VertexFullModelConstant_float32_1f,
	VertexFullModelConstant_float32_N1f,

	VertexFullModelConstant_uint_0,

	VertexFullModelConstant_int_0,
	VertexFullModelConstant_int_1,
	VertexFullModelConstant_int_6,

	VertexFullModelConstant_float32vec2_1f_0f,
	VertexFullModelConstant_float32vec2_0f_1f,
	VertexFullModelConstant_float32vec2_0f_0f,
	VertexFullModelConstant_float32vec2_1f_1f,

	VertexFullModelConstant_float32vec2_1f_N1f,
	VertexFullModelConstant_float32vec2_N1f_N1f,
	VertexFullModelConstant_float32vec2_N1f_1f,


	//INPUT
	//BuiltIn
	VertexFullModelType_InputPointer_int32,
	VertexFullModelVariable_InputPointer_VertexIndex,
	VertexFullModelVariable_InputPointer_InstanceIndex,
	//PushConstants
	VertexFullModelType_struct_PushConstants,
	VertexFullModelType_PushConstantPointer_struct_PushConstants,
	VertexFullModelVariable_PushConstantPointer_struct_PushConstants,

	//OUTPUT
	//BuiltIn
	VertexFullModelType_OutputPointer_float32vec4,
	VertexFullModelType_float32_Array_1,
	VertexFullModelType_struct_BuiltIn,
	VertexFullModelType_OutputPointer_struct_BuiltIn,
	VertexFullModelVariable_OutputPointer_struct_BuiltIn,
	VertexFullModelVariable_OutputPointer_float32vec4_Position,

	//Misc
	VertexFullModelType_float32vec2_Array_6,
	VertexFullModelType_FunctionPointer_float32vec2_Array_6,

	VertexFullModelVariable_FunctionPointer_float32vec2_Array_6_Positions,
	VertexFullModelVariable_FunctionPointer_float32vec2_Array_6_UVS,

	VertexFullModelType_FunctionPointer_float32vec2,
	//MAIN FUNCTION
	VertexFullModelLabel_Start,

	VertexFullModelLoadedVariable_float32vec2_Array_6_Positions,
	VertexFullModelLoadedVariable_float32vec2_Array_6_UVS,

	VertexFullModelLoadedVariable_int32_VertexIndex,
	VertexFullModelLoadedVariable_int32_InstanceIndex,

	VertexFullModelLoadedVariable_int32_op0,
	VertexFullModelLoadedVariable_int32_index,

	VertexFullModelVariable_FunctionPointer_float32vec2_IndexedPositions,
	VertexFullModelVariable_FunctionPointer_float32vec2_IndexedUVS,

	VertexFullModelLoadedVariable_float32vec2_op4,
	VertexFullModelLoadedVariable_float32vec2_op5,
	VertexFullModelLoadedVariable_float32vec2_op6,
	VertexFullModelLoadedVariable_float32vec4_op7,

	VertexFullModelVariables_MAX
}VertexShaderFullModelVariables;
#define VertexShaderFullModelSize (352 * sizeof(SPIRV))
#define VertexShaderFullModel() {\
SPIRV_Header(VertexFullModelVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(9<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelVertex, VertexFullModelFunction_Main, 'niam', '\0', VertexFullModelVariable_InputPointer_VertexIndex, VertexFullModelVariable_InputPointer_InstanceIndex, \
VertexFullModelVariable_PushConstantPointer_struct_PushConstants, VertexFullModelVariable_OutputPointer_struct_BuiltIn,\
/*DECORATION*/\
/*INPUT*/\
/*Built In*/\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexFullModelVariable_InputPointer_VertexIndex, SpvDecorationBuiltIn, SpvBuiltInVertexIndex,\
(4<<SpvWordCountShift)|SpvOpDecorate, VertexFullModelVariable_InputPointer_InstanceIndex, SpvDecorationBuiltIn, SpvBuiltInInstanceIndex,\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, VertexFullModelType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexFullModelType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexFullModelType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexFullModelType_struct_PushConstants, 1, SpvDecorationOffset, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexFullModelType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
/*Built In*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexFullModelType_struct_BuiltIn, 0, SpvDecorationBuiltIn, SpvBuiltInPosition,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexFullModelType_struct_BuiltIn, 1, SpvDecorationBuiltIn, SpvBuiltInPointSize,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexFullModelType_struct_BuiltIn, 2, SpvDecorationBuiltIn, SpvBuiltInClipDistance,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, VertexFullModelType_struct_BuiltIn, 3, SpvDecorationBuiltIn, SpvBuiltInCullDistance,\
(3<<SpvWordCountShift)|SpvOpDecorate, VertexFullModelType_struct_BuiltIn, SpvDecorationBlock,\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, VertexFullModelType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, VertexFullModelType_Function, VertexFullModelType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, VertexFullModelType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, VertexFullModelType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexFullModelType_float32vec2, VertexFullModelType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexFullModelType_float32vec3, VertexFullModelType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexFullModelType_float32vec4, VertexFullModelType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, VertexFullModelType_float32mat4, VertexFullModelType_float32vec4, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, VertexFullModelType_uint32, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexFullModelType_uint32vec2, VertexFullModelType_uint32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexFullModelType_uint32vec3, VertexFullModelType_uint32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexFullModelType_uint32vec4, VertexFullModelType_uint32, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, VertexFullModelType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexFullModelType_int32vec2, VertexFullModelType_int32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexFullModelType_int32vec3, VertexFullModelType_int32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, VertexFullModelType_int32vec4, VertexFullModelType_int32, 4,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, VertexFullModelType_float32, VertexFullModelConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexFullModelType_float32, VertexFullModelConstant_float32_1f, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexFullModelType_float32, VertexFullModelConstant_float32_N1f, 3212836864,\
\
(4<<SpvWordCountShift)|SpvOpConstant, VertexFullModelType_uint32, VertexFullModelConstant_uint_0, 0,\
\
(4<<SpvWordCountShift)|SpvOpConstant, VertexFullModelType_int32, VertexFullModelConstant_int_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexFullModelType_int32, VertexFullModelConstant_int_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, VertexFullModelType_int32, VertexFullModelConstant_int_6, 6,\
/*UV value constants*/\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexFullModelType_float32vec2, VertexFullModelConstant_float32vec2_1f_0f, VertexFullModelConstant_float32_1f, VertexFullModelConstant_float32_0f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexFullModelType_float32vec2, VertexFullModelConstant_float32vec2_0f_1f, VertexFullModelConstant_float32_0f, VertexFullModelConstant_float32_1f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexFullModelType_float32vec2, VertexFullModelConstant_float32vec2_0f_0f, VertexFullModelConstant_float32_0f, VertexFullModelConstant_float32_0f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexFullModelType_float32vec2, VertexFullModelConstant_float32vec2_1f_1f, VertexFullModelConstant_float32_1f, VertexFullModelConstant_float32_1f,\
\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexFullModelType_float32vec2, VertexFullModelConstant_float32vec2_1f_N1f, VertexFullModelConstant_float32_1f, VertexFullModelConstant_float32_N1f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexFullModelType_float32vec2, VertexFullModelConstant_float32vec2_N1f_N1f, VertexFullModelConstant_float32_N1f, VertexFullModelConstant_float32_N1f,\
(5<<SpvWordCountShift)|SpvOpConstantComposite, VertexFullModelType_float32vec2, VertexFullModelConstant_float32vec2_N1f_1f, VertexFullModelConstant_float32_N1f, VertexFullModelConstant_float32_1f,\
/*Input/Output Type Declarations*/\
/*pushconstants*/\
(4<<SpvWordCountShift)|SpvOpTypeStruct, VertexFullModelType_struct_PushConstants, VertexFullModelType_float32mat4, VertexFullModelType_int32,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexFullModelType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, VertexFullModelType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexFullModelType_PushConstantPointer_struct_PushConstants, VertexFullModelVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
/*inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexFullModelType_InputPointer_int32, SpvStorageClassInput, VertexFullModelType_int32,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexFullModelType_InputPointer_int32, VertexFullModelVariable_InputPointer_VertexIndex, SpvStorageClassInput,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexFullModelType_InputPointer_int32, VertexFullModelVariable_InputPointer_InstanceIndex, SpvStorageClassInput,\
/*built in output*/\
(4<<SpvWordCountShift)|SpvOpTypeArray, VertexFullModelType_float32_Array_1, VertexFullModelType_float32, VertexFullModelConstant_int_1,\
(6<<SpvWordCountShift)|SpvOpTypeStruct, VertexFullModelType_struct_BuiltIn, VertexFullModelType_float32vec4, VertexFullModelType_float32, VertexFullModelType_float32_Array_1, VertexFullModelType_float32_Array_1,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexFullModelType_OutputPointer_struct_BuiltIn, SpvStorageClassOutput, VertexFullModelType_struct_BuiltIn,\
(4<<SpvWordCountShift)|SpvOpVariable, VertexFullModelType_OutputPointer_struct_BuiltIn, VertexFullModelVariable_OutputPointer_struct_BuiltIn, SpvStorageClassOutput,\
/*input locations*/\
/*output inputs*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexFullModelType_OutputPointer_float32vec4, SpvStorageClassOutput, VertexFullModelType_float32vec4,\
\
(4<<SpvWordCountShift)|SpvOpTypeArray, VertexFullModelType_float32vec2_Array_6, VertexFullModelType_float32vec2, VertexFullModelConstant_int_6,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexFullModelType_FunctionPointer_float32vec2_Array_6, SpvStorageClassFunction, VertexFullModelType_float32vec2_Array_6,\
(4<<SpvWordCountShift)|SpvOpTypePointer, VertexFullModelType_FunctionPointer_float32vec2, SpvStorageClassFunction, VertexFullModelType_float32vec2,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, VertexFullModelType_Void, VertexFullModelFunction_Main, SpvFunctionControlMaskNone, VertexFullModelType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, VertexFullModelLabel_Start,\
	/*create vars*/\
	(4<<SpvWordCountShift)|SpvOpVariable, VertexFullModelType_FunctionPointer_float32vec2_Array_6, VertexFullModelVariable_FunctionPointer_float32vec2_Array_6_Positions, SpvStorageClassFunction,\
	(4<<SpvWordCountShift)|SpvOpVariable, VertexFullModelType_FunctionPointer_float32vec2_Array_6, VertexFullModelVariable_FunctionPointer_float32vec2_Array_6_UVS, SpvStorageClassFunction,\
	/*positions array*/\
	(9<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexFullModelType_float32vec2_Array_6, VertexFullModelLoadedVariable_float32vec2_Array_6_Positions,\
		 VertexFullModelConstant_float32vec2_1f_N1f, VertexFullModelConstant_float32vec2_N1f_1f, VertexFullModelConstant_float32vec2_N1f_N1f, VertexFullModelConstant_float32vec2_1f_N1f, VertexFullModelConstant_float32vec2_1f_1f, VertexFullModelConstant_float32vec2_N1f_1f,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexFullModelVariable_FunctionPointer_float32vec2_Array_6_Positions, VertexFullModelLoadedVariable_float32vec2_Array_6_Positions,\
	/*UVS array*/\
	(9<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexFullModelType_float32vec2_Array_6, VertexFullModelLoadedVariable_float32vec2_Array_6_UVS,\
		 VertexFullModelConstant_float32vec2_1f_0f, VertexFullModelConstant_float32vec2_0f_1f, VertexFullModelConstant_float32vec2_0f_0f, VertexFullModelConstant_float32vec2_1f_0f, VertexFullModelConstant_float32vec2_1f_1f, VertexFullModelConstant_float32vec2_0f_1f,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexFullModelVariable_FunctionPointer_float32vec2_Array_6_UVS, VertexFullModelLoadedVariable_float32vec2_Array_6_UVS,\
	/*index*/\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexFullModelType_int32, VertexFullModelLoadedVariable_int32_VertexIndex, VertexFullModelVariable_InputPointer_VertexIndex,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexFullModelType_int32, VertexFullModelLoadedVariable_int32_InstanceIndex, VertexFullModelVariable_InputPointer_InstanceIndex,\
	(5<<SpvWordCountShift)|SpvOpIMul, VertexFullModelType_int32, VertexFullModelLoadedVariable_int32_op0, VertexFullModelLoadedVariable_int32_InstanceIndex, VertexFullModelConstant_int_6,\
	(5<<SpvWordCountShift)|SpvOpISub, VertexFullModelType_int32, VertexFullModelLoadedVariable_int32_index, VertexFullModelLoadedVariable_int32_VertexIndex, VertexFullModelLoadedVariable_int32_op0,\
	/*output*/\
	/*out position*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, VertexFullModelType_FunctionPointer_float32vec2, VertexFullModelVariable_FunctionPointer_float32vec2_IndexedPositions, VertexFullModelVariable_FunctionPointer_float32vec2_Array_6_Positions, VertexFullModelLoadedVariable_int32_index,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexFullModelType_float32vec2, VertexFullModelLoadedVariable_float32vec2_op4, VertexFullModelVariable_FunctionPointer_float32vec2_IndexedPositions,\
	/*out UVS*/\
	(5<<SpvWordCountShift)|SpvOpAccessChain, VertexFullModelType_FunctionPointer_float32vec2, VertexFullModelVariable_FunctionPointer_float32vec2_IndexedUVS, VertexFullModelVariable_FunctionPointer_float32vec2_Array_6_UVS, VertexFullModelLoadedVariable_int32_index,\
	(4<<SpvWordCountShift)|SpvOpLoad, VertexFullModelType_float32vec2, VertexFullModelLoadedVariable_float32vec2_op5, VertexFullModelVariable_FunctionPointer_float32vec2_IndexedUVS,\
	/*out inbuilt position*/\
	(5<<SpvWordCountShift)|SpvOpCompositeConstruct, VertexFullModelType_float32vec2, VertexFullModelLoadedVariable_float32vec2_op6, VertexFullModelConstant_float32_1f, VertexFullModelConstant_float32_1f,\
	(9<<SpvWordCountShift)|SpvOpVectorShuffle, VertexFullModelType_float32vec4, VertexFullModelLoadedVariable_float32vec4_op7, VertexFullModelLoadedVariable_float32vec2_op4, VertexFullModelLoadedVariable_float32vec2_op6, 0, 1, 2, 3,\
	\
	(5<<SpvWordCountShift)|SpvOpAccessChain, VertexFullModelType_OutputPointer_float32vec4, VertexFullModelVariable_OutputPointer_float32vec4_Position, VertexFullModelVariable_OutputPointer_struct_BuiltIn, VertexFullModelConstant_int_0,\
	(3<<SpvWordCountShift)|SpvOpStore, VertexFullModelVariable_OutputPointer_float32vec4_Position, VertexFullModelLoadedVariable_float32vec4_op7,\
/*function end*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

typedef enum FragmentShaderFullModelVariables {
	FragmentFullModelExtension_GLSL450 = 1,
	FragmentFullModelFunction_Main,

	//BASIC TYPES
	FragmentFullModelType_Void,
	FragmentFullModelType_Function,
	FragmentFullModelType_bool,

	FragmentFullModelType_float32,
	FragmentFullModelType_float32vec2,
	FragmentFullModelType_float32vec3,
	FragmentFullModelType_float32vec4,
	FragmentFullModelType_float32mat4,

	FragmentFullModelType_uint32,
	FragmentFullModelType_uint32vec2,
	FragmentFullModelType_uint32vec3,
	FragmentFullModelType_uint32vec4,

	FragmentFullModelType_int32,
	FragmentFullModelType_int32vec2,
	FragmentFullModelType_int32vec3,
	FragmentFullModelType_int32vec4,

	//CONSTANTS
	FragmentFullModelConstant_float32_0f,
	FragmentFullModelConstant_float32_1f,
	FragmentFullModelConstant_float32_2f,

	FragmentFullModelConstant_uint32_0,

	FragmentFullModelConstant_int32_0,
	FragmentFullModelConstant_int32_1,
	FragmentFullModelConstant_int32_2,

	//INPUT
	//GPU_Atom 
	FragmentFullModelType_struct_Atom,
	FragmentFullModelType_RuntimeArray_struct_Atoms,
	FragmentFullModelType_struct_Atoms,
	FragmentFullModelType_StorageBufferPointer_struct_Atoms,
	FragmentFullModelType_StorageBufferPointer_struct_Atom,
	FragmentFullModelVariable_StorageBufferPointer_struct_Atoms,

	//GPU_Electrons
	FragmentFullModelType_struct_Electron,
	FragmentFullModelType_RuntimeArray_struct_Electrons,
	FragmentFullModelType_struct_Electrons,
	FragmentFullModelType_StorageBufferPointer_struct_Electrons,
	FragmentFullModelType_StorageBufferPointer_struct_Electron,
	FragmentFullModelVariable_StorageBufferPointer_struct_Electrons,

	//FragmentFullModelType_StorageBufferPointer_float32vec3,

	//PushConstants
	FragmentFullModelType_struct_PushConstants,
	FragmentFullModelType_PushConstantPointer_struct_PushConstants,
	FragmentFullModelVariable_PushConstantPointer_struct_PushConstants,


	//OUTPUT
	//Subpass Attachments
	FragmentFullModelType_OutputPointer_float32vec4,
	FragmentFullModelConstant_float32vec4_NULL,
	FragmentFullModelVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy,
	FragmentFullModelVariable_OutputPointer_float32vec4_OutPositionOrRevealage,

	//MAIN FUNCTION
	FragmentFullModelLabel_Start,

	FragmentFullModelLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Albedo,
	FragmentFullModelLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Position,
	FragmentFullModelLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Normal,
	FragmentFullModelLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_PBR,
	FragmentFullModelLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Transperancy,
	FragmentFullModelLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Revealage,
	FragmentFullModelLoadedVariable_Image_float32_2D_0_0_0_0_Unknown_Depth,

	FragmentFullModelLoadedVariable_float32vec4_Albedo,
	FragmentFullModelLoadedVariable_float32vec4_Position,
	FragmentFullModelLoadedVariable_float32vec4_Normal,
	FragmentFullModelLoadedVariable_float32vec4_PBR,
	FragmentFullModelLoadedVariable_float32vec4_Transperancy,
	FragmentFullModelLoadedVariable_float32vec4_Revealage,
	FragmentFullModelLoadedVariable_float32vec4_Depth,

	FragmentFullModelLoadedVariable_float32_AlbedoX,
	FragmentFullModelLoadedVariable_float32_AlbedoY,
	FragmentFullModelLoadedVariable_float32_AlbedoZ,
	FragmentFullModelLoadedVariable_float32_AlbedoW,

	FragmentFullModelLoadedVariable_float32_TransperancyX,
	FragmentFullModelLoadedVariable_float32_TransperancyY,
	FragmentFullModelLoadedVariable_float32_TransperancyZ,
	FragmentFullModelLoadedVariable_float32_TransperancyW,

	FragmentFullModelLoadedVariable_float32vec3_Albedo,
	FragmentFullModelLoadedVariable_float32vec3_Transperancy,

	FragmentFullModelLoadedVariable_float32_op0,
	FragmentFullModelLoadedVariable_float32_op1,
	FragmentFullModelLoadedVariable_float32_op2,
	FragmentFullModelLoadedVariable_float32_op3,
	FragmentFullModelLoadedVariable_float32_op4,

	FragmentFullModelLoadedVariable_float32vec3_op0,
	FragmentFullModelLoadedVariable_float32vec3_op1,
	FragmentFullModelLoadedVariable_float32vec3_op2,

	FragmentFullModelLoadedVariable_float32vec4_op0,


	FragmentFullModelVariables_MAX,
}FragmentShaderFullModelVariables;
#define FragmentShaderFullModelSize (326 * sizeof(SPIRV))
#define FragmentShaderFullModel() {\
SPIRV_Header(FragmentFullModelVariables_MAX)\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityShader,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityImageQuery,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityInputAttachment,\
(2<<SpvWordCountShift)|SpvOpCapability, SpvCapabilityVulkanMemoryModel,\
(6<<SpvWordCountShift)|SpvOpExtInstImport, FragmentFullModelExtension_GLSL450, 'LSLG', 'dts.', '054.', '\0',\
(3<<SpvWordCountShift)|SpvOpMemoryModel, SpvAddressingModelLogical, SpvMemoryModelVulkan,\
(10<<SpvWordCountShift)|SpvOpEntryPoint, SpvExecutionModelFragment, FragmentFullModelFunction_Main, 'niam', '\0', FragmentFullModelVariable_StorageBufferPointer_struct_Atoms, FragmentFullModelVariable_StorageBufferPointer_struct_Electrons,\
FragmentFullModelVariable_PushConstantPointer_struct_PushConstants, FragmentFullModelVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, FragmentFullModelVariable_OutputPointer_float32vec4_OutPositionOrRevealage,\
(3<<SpvWordCountShift)|SpvOpExecutionMode, FragmentFullModelFunction_Main, SpvExecutionModeOriginUpperLeft,\
/*DECORATION*/\
/*INPUT*/\
/*StorageBuffer GPU_Atoms*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_Atom, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_Atom, 1, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_Atom, 2, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_Atom, 3, SpvDecorationOffset, 48,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_Atom, 4, SpvDecorationOffset, 64,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentFullModelType_RuntimeArray_struct_Atoms, SpvDecorationArrayStride, 80,\
(3<<SpvWordCountShift)|SpvOpDecorate, FragmentFullModelType_struct_Atoms, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_Atoms, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentFullModelVariable_StorageBufferPointer_struct_Atoms, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentFullModelVariable_StorageBufferPointer_struct_Atoms, SpvDecorationBinding, 0,\
/*StorageBuffer GPU_Electrons*/\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_Electron, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_Electron, 1, SpvDecorationOffset, 16,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_Electron, 2, SpvDecorationOffset, 32,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_Electron, 3, SpvDecorationOffset, 48,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentFullModelType_RuntimeArray_struct_Electrons, SpvDecorationArrayStride, 64,\
(3<<SpvWordCountShift)|SpvOpDecorate, FragmentFullModelType_struct_Electrons, SpvDecorationBlock,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_Electrons, 0, SpvDecorationOffset, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentFullModelVariable_StorageBufferPointer_struct_Electrons, SpvDecorationDescriptorSet, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentFullModelVariable_StorageBufferPointer_struct_Electrons, SpvDecorationBinding, 1,\
/*PushConstants*/\
(4<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_PushConstants, 0, SpvDecorationColMajor,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_PushConstants, 0, SpvDecorationOffset, 0,\
(5<<SpvWordCountShift)|SpvOpMemberDecorate, FragmentFullModelType_struct_PushConstants, 0, SpvDecorationMatrixStride, 16,\
(3<<SpvWordCountShift)|SpvOpDecorate, FragmentFullModelType_struct_PushConstants, SpvDecorationBlock,\
/*OUTPUT*/\
/*Subpass Attachments*/\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentFullModelVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvDecorationLocation, 0,\
(4<<SpvWordCountShift)|SpvOpDecorate, FragmentFullModelVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvDecorationLocation, 1,\
\
/*TYPES*/\
(2<<SpvWordCountShift)|SpvOpTypeVoid, FragmentFullModelType_Void,\
(3<<SpvWordCountShift)|SpvOpTypeFunction, FragmentFullModelType_Function, FragmentFullModelType_Void,\
(2<<SpvWordCountShift)|SpvOpTypeBool, FragmentFullModelType_bool,\
/*floats*/\
(3<<SpvWordCountShift)|SpvOpTypeFloat, FragmentFullModelType_float32, 32,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentFullModelType_float32vec2, FragmentFullModelType_float32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentFullModelType_float32vec3, FragmentFullModelType_float32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentFullModelType_float32vec4, FragmentFullModelType_float32, 4,\
(4<<SpvWordCountShift)|SpvOpTypeMatrix, FragmentFullModelType_float32mat4, FragmentFullModelType_float32vec4, 4,\
/*unsigned int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, FragmentFullModelType_uint32, 32, 0,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentFullModelType_uint32vec2, FragmentFullModelType_uint32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentFullModelType_uint32vec3, FragmentFullModelType_uint32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentFullModelType_uint32vec4, FragmentFullModelType_uint32, 4,\
/*signed int*/\
(4<<SpvWordCountShift)|SpvOpTypeInt, FragmentFullModelType_int32, 32, 1,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentFullModelType_int32vec2, FragmentFullModelType_int32, 2,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentFullModelType_int32vec3, FragmentFullModelType_int32, 3,\
(4<<SpvWordCountShift)|SpvOpTypeVector, FragmentFullModelType_int32vec4, FragmentFullModelType_int32, 4,\
/*CONSTANTS*/\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentFullModelType_float32, FragmentFullModelConstant_float32_0f, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentFullModelType_float32, FragmentFullModelConstant_float32_1f, 1065353216,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentFullModelType_float32, FragmentFullModelConstant_float32_2f, 1073741824,\
\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentFullModelType_uint32, FragmentFullModelConstant_uint32_0, 0,\
\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentFullModelType_int32, FragmentFullModelConstant_int32_0, 0,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentFullModelType_int32, FragmentFullModelConstant_int32_1, 1,\
(4<<SpvWordCountShift)|SpvOpConstant, FragmentFullModelType_int32, FragmentFullModelConstant_int32_2, 2,\
/*INPUT*/\
/*StorageBuffer GPU_Atoms*/\
(7<<SpvWordCountShift)|SpvOpTypeStruct, FragmentFullModelType_struct_Atom, FragmentFullModelType_float32vec3, FragmentFullModelType_float32vec3, FragmentFullModelType_float32vec4, FragmentFullModelType_float32vec4, FragmentFullModelType_int32,\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, FragmentFullModelType_RuntimeArray_struct_Atoms, FragmentFullModelType_struct_Atom,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, FragmentFullModelType_struct_Atoms, FragmentFullModelType_RuntimeArray_struct_Atoms,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentFullModelType_StorageBufferPointer_struct_Atoms, SpvStorageClassStorageBuffer, FragmentFullModelType_struct_Atoms,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentFullModelType_StorageBufferPointer_struct_Atom, SpvStorageClassStorageBuffer, FragmentFullModelType_struct_Atom,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentFullModelType_StorageBufferPointer_struct_Atoms, FragmentFullModelVariable_StorageBufferPointer_struct_Atoms, SpvStorageClassStorageBuffer,\
/*StorageBuffer GPU_Electrons*/\
(6<<SpvWordCountShift)|SpvOpTypeStruct, FragmentFullModelType_struct_Electron, FragmentFullModelType_float32vec3, FragmentFullModelType_float32vec3, FragmentFullModelType_float32vec4, FragmentFullModelType_float32vec4,\
(3<<SpvWordCountShift)|SpvOpTypeRuntimeArray, FragmentFullModelType_RuntimeArray_struct_Electrons, FragmentFullModelType_struct_Electron,\
(3<<SpvWordCountShift)|SpvOpTypeStruct, FragmentFullModelType_struct_Electrons, FragmentFullModelType_RuntimeArray_struct_Electrons,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentFullModelType_StorageBufferPointer_struct_Electrons, SpvStorageClassStorageBuffer, FragmentFullModelType_struct_Electrons,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentFullModelType_StorageBufferPointer_struct_Electron, SpvStorageClassStorageBuffer, FragmentFullModelType_struct_Electron,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentFullModelType_StorageBufferPointer_struct_Electrons, FragmentFullModelVariable_StorageBufferPointer_struct_Electrons, SpvStorageClassStorageBuffer,\
/*PushConstants*/\
(3<<SpvWordCountShift)|SpvOpTypeStruct, FragmentFullModelType_struct_PushConstants, FragmentFullModelType_float32mat4,\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentFullModelType_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant, FragmentFullModelType_struct_PushConstants,\
(4<<SpvWordCountShift)|SpvOpVariable, FragmentFullModelType_PushConstantPointer_struct_PushConstants, FragmentFullModelVariable_PushConstantPointer_struct_PushConstants, SpvStorageClassPushConstant,\
/*OUTPUT*/\
/*Subpass Attachments*/\
(4<<SpvWordCountShift)|SpvOpTypePointer, FragmentFullModelType_OutputPointer_float32vec4, SpvStorageClassOutput, FragmentFullModelType_float32vec4,\
(3<<SpvWordCountShift)|SpvOpConstantNull, FragmentFullModelType_float32vec4, FragmentFullModelConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentFullModelType_OutputPointer_float32vec4, FragmentFullModelVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, SpvStorageClassOutput, FragmentFullModelConstant_float32vec4_NULL,\
(5<<SpvWordCountShift)|SpvOpVariable, FragmentFullModelType_OutputPointer_float32vec4, FragmentFullModelVariable_OutputPointer_float32vec4_OutPositionOrRevealage, SpvStorageClassOutput, FragmentFullModelConstant_float32vec4_NULL,\
/*MAIN FUNCTION*/\
(5<<SpvWordCountShift)|SpvOpFunction, FragmentFullModelType_Void, FragmentFullModelFunction_Main, SpvFunctionControlMaskNone, FragmentFullModelType_Function,\
(2<<SpvWordCountShift)|SpvOpLabel, FragmentFullModelLabel_Start,\
	/*albedo = vec4()*/\
	/*(3<<SpvWordCountShift)|SpvOpStore, FragmentFullModelVariable_OutputPointer_float32vec4_OutAlbedoOrTransperancy, fffffffffffffffffffffffffffffffff,*/\
/*FUNCTION END*/\
(1<<SpvWordCountShift)|SpvOpReturn,\
(1<<SpvWordCountShift)|SpvOpFunctionEnd,\
}

#ifdef aaa
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
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Draw Effect Element
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Draw_SimpleModel(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, ChemistryEffectSimpleModel* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers, RHeaderCamera* pCamera, mat4 CameraVP)
{

}

void Draw_FullModel(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, ChemistryEffectFullModel* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers, RHeaderCamera* pCamera, mat4 CameraVP)
{
	vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pEffect->VkPipeline);

	PushConstantsFullModel PushConstants;
	memset(&PushConstants, 0, sizeof(PushConstants));

	mat4 CameraPositionMatrix;
	glm_mat4_identity(CameraPositionMatrix);
	Graphics_Ref_Calculate_TotalMatrix(&CameraPositionMatrix, pCamera->Header.iParents[0]);
	glm_mat4_inv_precise_sse2(CameraPositionMatrix, CameraPositionMatrix);

	vec4 Translation;
	glm_vec3_zero(Translation);
	mat4 Rotation;
	glm_mat4_zero(Rotation);
	vec3 Scale;
	glm_vec3_one(Scale);

	glm_decompose(CameraPositionMatrix, Translation, Rotation, Scale);

	glm_mat4_copy(Rotation, PushConstants.Rotation);

	glm_vec4_copy(Translation, PushConstants.Position);
	PushConstants.PingPongIndex = pEffect->PingPongIndex;
	PushConstants.FieldOfView = 70.0f;
	PushConstants.ResolutionX = pGraphicsWindow->CurrentExtentWidth;
	PushConstants.ResolutionY = pGraphicsWindow->CurrentExtentHeight;
	//glm_vec3_copy(pEffect->Position, PushConstants.Position);
	vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->VkPipelineLayout, VK_SHADER_STAGE_ALL, 0,
		pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstants);

	vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
		pEffect->VkPipelineLayout, 0, 1, &pEffect->VkDescriptorSets[FrameIndex], 0, NULL);

	vkCmdDraw(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 6, 1, 0, 0);
}

void Draw_Fundamental(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, ChemistryEffectFundamental* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers, RHeaderCamera* pCamera, mat4 CameraVP)
{	
	Engine_Ref_Lock_Mutex(pEffect->mutex);
	VkBuffer vkBuffer = pEffect->AllocationParticles1.Allocater.pArenaAllocater->VkBuffer;
	VkDeviceSize VkOffset = pEffect->AllocationParticles1.Pointer;

	vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pEffect->VkPipeline);

	PushConstantsFundamental PushConstants;
	memset(&PushConstants, 0, sizeof(PushConstants));
	glm_mat4_copy(CameraVP, PushConstants.VP);
	vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->VkPipelineLayout, VK_SHADER_STAGE_ALL, 0,
		pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstants);

	vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
		pEffect->VkPipelineLayout, 0, 1, &pEffect->VkDescriptorSet, 0, NULL);
	
	vkCmdBindVertexBuffers(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 0, 1, &vkBuffer, &VkOffset);

	vkCmdDraw(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, 6, pEffect->ParticlesSize, 0, 0);
	Engine_Ref_Unlock_Mutex(pEffect->mutex);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Update Effect Element
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Update_SimpleModel(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, ChemistryEffectSimpleModel* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
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
}

void Update_FullModel(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, ChemistryEffectFullModel* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
	if (GPU_Buffers == NULL)
	{

	}
	else
	{
		RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
		RHeaderTexture* pTexture0 = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pMaterial->BaseColourTexture.iTexture);
		RHeaderTexture* pTexture1 = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pMaterial->EmissiveTexture.iTexture);

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Updating Descriptor Sets
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		{//compute
			VkDescriptorBufferInfo BufferInfo = { sizeof(BufferInfo) };
			BufferInfo.buffer = pEffect->AllocationParticles.Allocater.pArenaAllocater->VkBuffer;
			BufferInfo.offset = pEffect->AllocationParticles.Pointer;
			BufferInfo.range = pEffect->AllocationParticles.SizeBytes;
			Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pEffect->VkDescriptorSets[FrameIndex], 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &BufferInfo, NULL);
		} {
			VkDescriptorImageInfo ImageInfo = { sizeof(ImageInfo) };
			ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
			ImageInfo.imageView = pTexture0->GPU_Texture.VkImageView;
			ImageInfo.sampler = NULL;
			Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pEffect->VkDescriptorSets[FrameIndex], 1, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
		} {
			VkDescriptorImageInfo ImageInfo = { sizeof(ImageInfo) };
			ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
			ImageInfo.imageView = pTexture1->GPU_Texture.VkImageView;
			ImageInfo.sampler = NULL;
			Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pEffect->VkDescriptorSets[FrameIndex], 2, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
		}
	}
}

void Update_Fundamental(ElementGraphics* pElement, ResourceHeader* pHeader, Object* pObject, ChemistryEffectFundamental* pEffect,
	RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, RHeaderMaterial* pMaterialHeader, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
	if (GPU_Buffers == NULL)
	{

	}
	else
	{

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Signataure Updates
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdateSignature_SimpleModel(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{

}

void UpdateSignature_FullModel(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{

}

void UpdateSignature_Fundamental(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Signataure Draws
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawSignature_SimpleModel(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
}

void DrawSignature_FullModel(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
	for (size_t i2 = 0; i2 < ((GraphicsUtils*)GraphicsRes.pUtils)->ElementGraphicsBuffer.Size;)
	{
		ElementGraphics* pElement = &((GraphicsUtils*)GraphicsRes.pUtils)->ElementGraphicsBuffer.Buffer[i2];
		if (pElement->Header.AllocationSize != 0 && pElement->Header.Allocation.Identifier == (uint32_t)GraphicsElement_ElementGraphics)
		{
			uint64_t pointer = 0;
			for (size_t i3 = 0; i3 < pElement->EffectsSize; i3++)
			{
				ChemistryEffectFullModel* pEffect = (ChemistryEffectFullModel*)((void*)((uint64_t)pElement->Effects + pointer));
				if (pEffect->Header.Identifier == ChemistryEffects_FullModel)
				{
					RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
					RHeaderTexture* pTexture0 = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pMaterial->BaseColourTexture.iTexture);
					RHeaderTexture* pTexture1 = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pMaterial->EmissiveTexture.iTexture);
					
					VkResult res = VK_SUCCESS;

					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//Rendering
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					Engine_Ref_Lock_Mutex(pEffect->mutex);
					{
						VkImageMemoryBarrier Barrier = { sizeof(Barrier) };
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pTexture0->GPU_Texture.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = 0;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
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
					{
						VkImageMemoryBarrier Barrier = { sizeof(Barrier) };
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pTexture1->GPU_Texture.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = 0;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
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
					{
						vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pEffect->VkPipelineComputeSource);

						PushConstantsComputeFullModel PushConstants;
						memset(&PushConstants, 0, sizeof(PushConstants));
						PushConstants.PingPongIndex = pEffect->PingPongIndex;
						PushConstants.Time = ((double)clock() / (double)CLOCKS_PER_SEC);
						vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->VkPipelineLayout, VK_SHADER_STAGE_ALL, 0,
							pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstants);

						vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
							pEffect->VkPipelineLayout, 0, 1, &pEffect->VkDescriptorSets[FrameIndex], 0, NULL);

						vkCmdDispatch(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->ParticlesSize, 1, 1);
					}
					{
						vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pEffect->VkPipelineComputeField);

						PushConstantsComputeFullModel PushConstants;
						memset(&PushConstants, 0, sizeof(PushConstants));
						PushConstants.PingPongIndex = pEffect->PingPongIndex;
						PushConstants.Time = ((double)clock() / (double)CLOCKS_PER_SEC);
						vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->VkPipelineLayout, VK_SHADER_STAGE_ALL, 0,
							pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstants);

						vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
							pEffect->VkPipelineLayout, 0, 1, &pEffect->VkDescriptorSets[FrameIndex], 0, NULL);

						vkCmdDispatch(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->SimulationResolution / 8, pEffect->SimulationResolution / 8, pEffect->SimulationResolution / 8);
					}

					{
						VkImageMemoryBarrier Barrier = { sizeof(Barrier) };
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pTexture0->GPU_Texture.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
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
					{
						VkImageMemoryBarrier Barrier = { sizeof(Barrier) };
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pTexture1->GPU_Texture.VkImage;
						Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
						Barrier.subresourceRange.baseMipLevel = 0;
						Barrier.subresourceRange.levelCount = 1;
						Barrier.subresourceRange.baseArrayLayer = 0;
						Barrier.subresourceRange.layerCount = 1;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
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
					pEffect->PingPongIndex = !pEffect->PingPongIndex;
					Engine_Ref_Unlock_Mutex(pEffect->mutex);
				}
				pointer += pEffect->Header.AllocationSize;
			}
			i2 += pElement->Header.AllocationSize;
		}
		else
		{
			i2++;
		}
	}
}

void DrawSignature_Fundamental(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{	
	for (size_t i2 = 0; i2 < ((GraphicsUtils*)GraphicsRes.pUtils)->ElementGraphicsBuffer.Size;)
	{
		ElementGraphics* pElement = &((GraphicsUtils*)GraphicsRes.pUtils)->ElementGraphicsBuffer.Buffer[i2];
		if (pElement->Header.AllocationSize != 0 && pElement->Header.Allocation.Identifier == (uint32_t)GraphicsElement_ElementGraphics)
		{
			uint64_t pointer = 0;
			for (size_t i3 = 0; i3 < pElement->EffectsSize; i3++)
			{
				ChemistryEffectFundamental* pEffect = (ChemistryEffectFundamental*)((void*)((uint64_t)pElement->Effects + pointer));
				if (pEffect->Header.Identifier == ChemistryEffects_Fundamental)
				{
					VkResult res = VK_SUCCESS;

					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//Rendering
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					Engine_Ref_Lock_Mutex(pEffect->mutex);
					{
						VkBufferMemoryBarrier Barrier = { sizeof(Barrier) };
						Barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
						Barrier.buffer = pEffect->AllocationParticles0.Allocater.pArenaAllocater->VkBuffer;
						Barrier.offset = pEffect->AllocationParticles0.Pointer;
						Barrier.size = pEffect->AllocationParticles0.SizeBytes;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = 0;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
							0,
							0, NULL,
							1, &Barrier,
							0, NULL
						);
					}
					{
						VkBufferMemoryBarrier Barrier = { sizeof(Barrier) };
						Barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
						Barrier.buffer = pEffect->AllocationParticles1.Allocater.pArenaAllocater->VkBuffer;
						Barrier.offset = pEffect->AllocationParticles1.Pointer;
						Barrier.size = pEffect->AllocationParticles1.SizeBytes;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = 0;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
							0,
							0, NULL,
							1, &Barrier,
							0, NULL
						);
					}
					{
						vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pEffect->VkPipelineCompute);
						vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
							pEffect->VkPipelineLayout, 0, 1, &pEffect->VkDescriptorSet, 0, NULL);
						
						{
							PushConstantsComputeFundamental PushConstants;
							memset(&PushConstants, 0, sizeof(PushConstants));
							PushConstants.Part = 0;
							PushConstants.Particles = pEffect->ParticlesSize;
							//PushConstants.ChunkSize = pEffect->ChunkSize;
							PushConstants.Resolution = pEffect->Resolution;
							vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->VkPipelineLayout, VK_SHADER_STAGE_ALL, 0,
								pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstants);

							vkCmdDispatch(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->ParticlesSize, 1, 1);
						}
						{
							PushConstantsComputeFundamental PushConstants;
							memset(&PushConstants, 0, sizeof(PushConstants));
							PushConstants.Part = 1;
							PushConstants.Particles = pEffect->ParticlesSize;
							//PushConstants.ChunkSize = pEffect->ChunkSize;
							PushConstants.Resolution = pEffect->Resolution;
							vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->VkPipelineLayout, VK_SHADER_STAGE_ALL, 0,
								pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstants);

							vkCmdDispatch(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pEffect->ParticlesSize, 1, 1);
						}
					}
					{
						VkBufferMemoryBarrier Barrier = { sizeof(Barrier) };
						Barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
						Barrier.buffer = pEffect->AllocationParticles0.Allocater.pArenaAllocater->VkBuffer;
						Barrier.offset = pEffect->AllocationParticles0.Pointer;
						Barrier.size = pEffect->AllocationParticles0.SizeBytes;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT,
							0,
							0, NULL,
							1, &Barrier,
							0, NULL
						);
					}
					{
						VkBufferMemoryBarrier Barrier = { sizeof(Barrier) };
						Barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
						Barrier.buffer = pEffect->AllocationParticles1.Allocater.pArenaAllocater->VkBuffer;
						Barrier.offset = pEffect->AllocationParticles1.Pointer;
						Barrier.size = pEffect->AllocationParticles1.SizeBytes;
						Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
						Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
						Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
						Barrier.pNext = NULL;

						vkCmdPipelineBarrier(
							pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer,
							VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT,
							0,
							0, NULL,
							1, &Barrier,
							0, NULL
						);
					}
					Engine_Ref_Unlock_Mutex(pEffect->mutex);
				}
				pointer += pEffect->Header.AllocationSize;
			}
			i2 += pElement->Header.AllocationSize;
		}
		else
		{
			i2++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Destroy_SimpleModel(ElementGraphics* pElement, ChemistryEffectSimpleModel* pEffect, bool Full, uint32_t ThreadIndex)
{
	return (Success);
}

TEXRESULT Destroy_FullModel(ElementGraphics* pElement, ChemistryEffectFullModel* pEffect, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);

	if (pEffect->VkPipelineComputeSource != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineComputeSource, NULL);
	pEffect->VkPipelineComputeSource = NULL;
	if (pEffect->VkShaderComputeSource != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderComputeSource, NULL);
	pEffect->VkShaderComputeSource = NULL;

	if (pEffect->VkPipelineComputeField != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineComputeField, NULL);
	pEffect->VkPipelineComputeField = NULL;
	if (pEffect->VkShaderComputeField != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderComputeField, NULL);
	pEffect->VkShaderComputeField = NULL;


	if (pEffect->VkPipelineLayout != NULL)
		vkDestroyPipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineLayout, NULL);
	pEffect->VkPipelineLayout = NULL;

	if (pEffect->VkDescriptorSetLayout != NULL)
		vkDestroyDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkDescriptorSetLayout, NULL);
	pEffect->VkDescriptorSetLayout = NULL;

	if (pEffect->VkDescriptorSets != NULL)
	{
		//vkFreeDescriptorSets(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkWindowDescriptorPool, pResourceHeader->CurrentFrameBuffersSize, pResourceHeader->VkDescriptorSetsInputAttachment);
		free(pEffect->VkDescriptorSets);
	}
	pEffect->VkDescriptorSets = NULL;

	if (pEffect->VkDescriptorPool != NULL)
		vkDestroyDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkDescriptorPool, NULL);
	pEffect->VkDescriptorPool = NULL;



	if (pEffect->VkPipeline != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipeline, NULL);
	pEffect->VkPipeline = NULL;
	if (pEffect->VkShaderVertex != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderVertex, NULL);
	pEffect->VkShaderVertex = NULL;
	if (pEffect->VkShaderFragment != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderFragment, NULL);
	pEffect->VkShaderFragment = NULL;

	Graphics_Ref_GPUfree(pGraphicsWindow->pLogicalDevice, &pEffect->AllocationParticles);

	Engine_Ref_Destroy_Mutex(pEffect->mutex);

	if (Full == true)
	{
		if (pEffect->Particles != NULL)
			free(pEffect->Particles);
		pEffect->Particles = NULL;
		pEffect->ParticlesSize = 0;
	}
	return (Success);
}

TEXRESULT Destroy_Fundamental(ElementGraphics* pElement, ChemistryEffectFundamental* pEffect, bool Full, uint32_t ThreadIndex)
{
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);

	if (pEffect->VkPipelineCompute != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineCompute, NULL);
	pEffect->VkPipelineCompute = NULL;
	if (pEffect->VkShaderCompute != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderCompute, NULL);
	pEffect->VkShaderCompute = NULL;


	if (pEffect->VkPipelineLayout != NULL)
		vkDestroyPipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipelineLayout, NULL);
	pEffect->VkPipelineLayout = NULL;

	if (pEffect->VkDescriptorSetLayout != NULL)
		vkDestroyDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkDescriptorSetLayout, NULL);
	pEffect->VkDescriptorSetLayout = NULL;

	if (pEffect->VkDescriptorSet != NULL)
	{
		//vkFreeDescriptorSets(pResourceHeader->pLogicalDevice->VkLogicalDevice, pResourceHeader->VkWindowDescriptorPool, pResourceHeader->CurrentFrameBuffersSize, pResourceHeader->VkDescriptorSetsInputAttachment);
		//free(pEffect->VkDescriptorSets);
	}
	pEffect->VkDescriptorSet = NULL;

	if (pEffect->VkDescriptorPool != NULL)
		vkDestroyDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkDescriptorPool, NULL);
	pEffect->VkDescriptorPool = NULL;



	if (pEffect->VkPipeline != NULL)
		vkDestroyPipeline(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkPipeline, NULL);
	pEffect->VkPipeline = NULL;
	if (pEffect->VkShaderVertex != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderVertex, NULL);
	pEffect->VkShaderVertex = NULL;
	if (pEffect->VkShaderFragment != NULL)
		vkDestroyShaderModule(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, pEffect->VkShaderFragment, NULL);
	pEffect->VkShaderFragment = NULL;

	Graphics_Ref_GPUfree(pGraphicsWindow->pLogicalDevice, &pEffect->AllocationParticles0);
	Graphics_Ref_GPUfree(pGraphicsWindow->pLogicalDevice, &pEffect->AllocationParticles1);

	Engine_Ref_Destroy_Mutex(pEffect->mutex);

	if (Full == true)
	{
		if (pEffect->Particles != NULL)
			free(pEffect->Particles);
		pEffect->Particles = NULL;
		pEffect->ParticlesSize = 0;
	}
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Recreation
/////////////////////////////////////////////////////////////////////////////////////////////a///////////////////////////////////////////////////

TEXRESULT ReCreate_SimpleModel(ElementGraphics* pElement, ChemistryEffectSimpleModel* pEffect, uint32_t ThreadIndex)
{
	/*

	{
		const SPIRV Vertex[] = VertexShaderSimplifiedMolecular();
		const SPIRV Fragment[] = FragmentShaderSimplifiedMolecular();

		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderVertexParticle, Vertex, VertexShaderSimplifiedMolecularSize, "ReCreate_FullModel()");
		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderFragmentParticle, Fragment, FragmentShaderSimplifiedMolecularSize, "ReCreate_FullModel()");

		uint32_t ShaderCount = 2;
		VkPipelineShaderStageCreateInfo ShaderStages[2];
		memset(ShaderStages, 0, sizeof(*ShaderStages) * ShaderCount);
		ShaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
		ShaderStages[0].module = pEffect->VkShaderVertexParticle;
		ShaderStages[0].pName = "main";

		ShaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		ShaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		ShaderStages[1].module = pEffect->VkShaderFragmentParticle;
		ShaderStages[1].pName = "main";

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
		memset(&VertexInputInfo, 0, sizeof(VertexInputInfo));
		VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		VertexInputInfo.vertexBindingDescriptionCount = (uint32_t)InputBindingDescsSize;
		VertexInputInfo.pVertexBindingDescriptions = InputBindingDescs; // Optional

		VertexInputInfo.vertexAttributeDescriptionCount = (uint32_t)InputAttribDescsSize;
		VertexInputInfo.pVertexAttributeDescriptions = InputAttribDescs; // Optional


		VkPipelineInputAssemblyStateCreateInfo InputAssemblyState;
		memset(&InputAssemblyState, 0, sizeof(InputAssemblyState));
		InputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		InputAssemblyState.primitiveRestartEnable = VK_FALSE;

		VkPipelineRasterizationStateCreateInfo RasterizationState;
		memset(&RasterizationState, 0, sizeof(RasterizationState));
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
		memset(&Info, 0, sizeof(Info));

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

		if ((res = vkCreateGraphicsPipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipeline)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_FullModel()", "vkCreateGraphicsPipelines Failed. VkResult == ", res);
			return;
		}
}*/
	return (Success);
}

TEXRESULT ReCreate_FullModel(ElementGraphics* pElement, ChemistryEffectFullModel* pEffect, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_FullModel()", "pElement == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (pEffect == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_FullModel()", "pEffect == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	VkResult res = VK_SUCCESS;
	TEXRESULT tres = Success;
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);
	RHeaderMaterial* pMaterial = (RHeaderMaterial*)Object_Ref_Get_ResourceHeaderPointer(pElement->iMaterial);
#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pMaterial->BaseColourTexture.iTexture) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_FullModel()", "pMaterial->BaseColourTexture.iTexture Invalid");
		return (Invalid_Parameter | Failure);
	}
#endif

	RHeaderTexture* pTexture0 = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pMaterial->BaseColourTexture.iTexture);
	RHeaderImageSource* pImageSource0 = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture0->iImageSource);

	RHeaderTexture* pTexture1 = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pMaterial->EmissiveTexture.iTexture);
	RHeaderImageSource* pImageSource1 = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture1->iImageSource);

#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pTexture0->iImageSource) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_FullModel()", "pMaterial->BaseColourTexture.iTexture->iImageSource Invalid");
		return (Invalid_Parameter | Failure);
	}
	if (pImageSource0->ImageData == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_FullModel()", "pMaterial->BaseColourTexture.iTexture->iImageSource->ImageData == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pTexture1->iImageSource) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_FullModel()", "pMaterial->EmissiveTexture.iTexture->iImageSource Invalid");
		return (Invalid_Parameter | Failure);
	}
	if (pImageSource1->ImageData == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_FullModel()", "pMaterial->EmissiveTexture.iTexture->iImageSource->ImageData == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	pImageSource0->ImageData->Width = pEffect->SimulationResolution;
	pImageSource0->ImageData->Height = pEffect->SimulationResolution;
	pImageSource0->ImageData->Depth = pEffect->SimulationResolution;
	pImageSource0->ImageData->Format = GraphicsFormat_R32G32B32A32_SFLOAT;
	pImageSource0->ImageData->MipmapCount = 1;
	Object_Ref_ReCreate_ResourceHeader(pTexture0->Header.Allocation, NULL, ThreadIndex);

	pImageSource1->ImageData->Width = pEffect->SimulationResolution;
	pImageSource1->ImageData->Height = pEffect->SimulationResolution;
	pImageSource1->ImageData->Depth = pEffect->SimulationResolution;
	pImageSource1->ImageData->Format = GraphicsFormat_R32G32B32A32_SFLOAT;
	pImageSource1->ImageData->MipmapCount = 1;
	Object_Ref_ReCreate_ResourceHeader(pTexture1->Header.Allocation, NULL, ThreadIndex);

	Engine_Ref_Create_Mutex(pEffect->mutex, MutexType_Plain);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//DescriptorLayout
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		VkDescriptorSetLayoutBinding BindingsCompute[ChemistryFullModelBuffersCount + ChemistryFullModelImagesCount] = { (ChemistryFullModelBuffersCount + ChemistryFullModelImagesCount) * sizeof(*BindingsCompute) };
		size_t i = 0;
		for (; i < ChemistryFullModelBuffersCount; i++)
		{
			BindingsCompute[i].binding = i;
			BindingsCompute[i].descriptorCount = 1;
			BindingsCompute[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			BindingsCompute[i].stageFlags = VK_SHADER_STAGE_ALL;
			BindingsCompute[i].pImmutableSamplers = NULL;
		}
		for (; i < ChemistryFullModelBuffersCount + ChemistryFullModelImagesCount; i++)
		{
			BindingsCompute[i].binding = i;
			BindingsCompute[i].descriptorCount = 1;
			BindingsCompute[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			BindingsCompute[i].stageFlags = VK_SHADER_STAGE_ALL;
			BindingsCompute[i].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)ChemistryFullModelBuffersCount + ChemistryFullModelImagesCount;
		Info.pBindings = BindingsCompute;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkDescriptorSetLayout)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_FullModel()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipeline Layouts
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		VkDescriptorSetLayout layouts[1] = { pEffect->VkDescriptorSetLayout };
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
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkPipelineLayout)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_FullModel()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Descriptor Pool
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		uint32_t PoolSizesSize = 2;
		VkDescriptorPoolSize PoolSizes[2] = { PoolSizesSize * sizeof(*PoolSizes) };

		PoolSizes[0].descriptorCount = ChemistryFullModelBuffersCount;
		PoolSizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

		PoolSizes[1].descriptorCount = ChemistryFullModelImagesCount;
		PoolSizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;

		VkDescriptorPoolCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		Info.maxSets = 1 * pGraphicsWindow->CurrentFrameBuffersSize;
		Info.poolSizeCount = PoolSizesSize;
		Info.pPoolSizes = PoolSizes;
		if ((res = vkCreateDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkDescriptorPool)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_FullModel()", "vkCreateDescriptorPool, VkResult == ", res);
			return (Failure);
		}
	}
	pEffect->VkDescriptorSets = calloc(pGraphicsWindow->CurrentFrameBuffersSize, sizeof(*pEffect->VkDescriptorSets));
	for (size_t i = 0; i < pGraphicsWindow->CurrentFrameBuffersSize; i++)
	{
		uint32_t layoutsSize = 1;
		VkDescriptorSetLayout layouts[1] = { pEffect->VkDescriptorSetLayout };
		VkDescriptorSet sets[1];

		VkDescriptorSetAllocateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		Info.descriptorPool = pEffect->VkDescriptorPool;
		Info.descriptorSetCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pNext = NULL;
		if ((res = vkAllocateDescriptorSets(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, sets)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_FullModel()", "vkAllocateDescriptorSets, VkResult == ", res);
			return (Failure);
		}
		pEffect->VkDescriptorSets[i] = sets[0];
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Allocation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		VkMemoryRequirements MemoryRequirements = { sizeof(MemoryRequirements) };
		MemoryRequirements.alignment = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.minStorageBufferOffsetAlignment;
		MemoryRequirements.size = pEffect->ParticlesSize * sizeof(*pEffect->Particles);
		MemoryRequirements.memoryTypeBits = NULL;
		pEffect->AllocationParticles = Graphics_Ref_GPUmalloc(pGraphicsWindow->pLogicalDevice, MemoryRequirements, TargetMemory_Src, AllocationType_Linear, ThreadIndex);
		if (pEffect->AllocationParticles.SizeBytes == NULL)
		{
			Engine_Ref_FunctionError("ReCreate_FullModel()", "Not Enough Space In GPU Memory!", NULL);
			return (Out_Of_Memory_Result | Failure);
		}
		GPU_Particle* pParticles = (GPU_Particle*)((void*)(((uint64_t)pEffect->AllocationParticles.Allocater.pArenaAllocater->MappedMemory + pEffect->AllocationParticles.Pointer)));
		memcpy(pParticles, pEffect->Particles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipelines
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		FileData DataCompute = { 0, 0 };
		Open_Data(&DataCompute, "data\\Shaders\\ChemistryComputeSource.comp.spv");

		//const SPIRV ShaderButterfly[] = ComputeShaderButterfly();
		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderComputeSource, DataCompute.pData, DataCompute.LinearSize - 1, "ReCreate_FullModel()");

		VkComputePipelineCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pEffect->VkShaderComputeSource;
		Info.stage.pName = "main";
		Info.layout = pEffect->VkPipelineLayout;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipelineComputeSource)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_FullModel()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return (Failure);
		}
		free(DataCompute.pData);
	}
	{
		FileData DataCompute = { 0, 0 };
		Open_Data(&DataCompute, "data\\Shaders\\ChemistryComputeField.comp.spv");

		//const SPIRV ShaderButterfly[] = ComputeShaderButterfly();
		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderComputeField, DataCompute.pData, DataCompute.LinearSize - 1, "ReCreate_FullModel()");

		VkComputePipelineCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pEffect->VkShaderComputeField;
		Info.stage.pName = "main";
		Info.layout = pEffect->VkPipelineLayout;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipelineComputeField)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_FullModel()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return (Failure);
		}
		free(DataCompute.pData);
	}
	{
		//FileData DataVertex = { 0, 0 };
		//Open_Data(&DataVertex, "data\\Shaders\\ChemistryProjection.vert.spv");

		FileData DataFragment = { 0, 0 };
		Open_Data(&DataFragment, "data\\Shaders\\ChemistryProjection.frag.spv");

		const SPIRV Vertex[] = VertexShaderFullModel();
		//const SPIRV Fragment[] = FragmentShaderSimplifiedMolecular();

		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderVertex, Vertex, VertexShaderFullModelSize, "ReCreate_FullModel()");
		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderFragment, DataFragment.pData, DataFragment.LinearSize - 1, "ReCreate_FullModel()");

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
		ColourBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
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

		VkViewport Viewport;
		memset(&Viewport, 0, sizeof(Viewport));
		Viewport.x = 0.0f;
		Viewport.y = 0.0f;
		Viewport.width = (float)pGraphicsWindow->CurrentExtentWidth;
		Viewport.height = (float)pGraphicsWindow->CurrentExtentHeight;
		Viewport.minDepth = 0.0f;
		Viewport.maxDepth = 1.0f;

		VkRect2D Scissor;
		memset(&Scissor, 0, sizeof(Scissor));
		Scissor.offset.x = 0;
		Scissor.offset.y = 0;
		Scissor.extent.width = pGraphicsWindow->CurrentExtentWidth;
		Scissor.extent.height = pGraphicsWindow->CurrentExtentHeight;

		VkPipelineViewportStateCreateInfo ViewportState;
		memset(&ViewportState, 0, sizeof(ViewportState));
		ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		ViewportState.viewportCount = 1;
		ViewportState.pViewports = &Viewport;
		ViewportState.scissorCount = 1;
		ViewportState.pScissors = &Scissor;


		//pipeline
		VkPipelineVertexInputStateCreateInfo VertexInputInfo;
		memset(&VertexInputInfo, 0, sizeof(VertexInputInfo));
		VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		VkPipelineInputAssemblyStateCreateInfo InputAssemblyState;
		memset(&InputAssemblyState, 0, sizeof(InputAssemblyState));
		InputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		InputAssemblyState.primitiveRestartEnable = VK_FALSE;

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

		VkGraphicsPipelineCreateInfo Info;
		memset(&Info, 0, sizeof(Info));

		Info.subpass = 1;
		ColourBlending.attachmentCount = 2;

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
		Info.layout = pEffect->VkPipelineLayout;
		Info.renderPass = pGraphicsWindow->VkRenderPassDeferred;
		//Info.subpass = 1;
		Info.basePipelineHandle = VK_NULL_HANDLE; // Optional
		Info.basePipelineIndex = -1; // Optional

		if ((res = vkCreateGraphicsPipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipeline)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_FullModel()", "vkCreateGraphicsPipelines Failed. VkResult == ", res);
			return (Failure);
		}
		//free(DataVertex.pData);
		free(DataFragment.pData);
	}
	return (Success);
}

int cmpfunc(const void* a, const void* b) {
	float chunk = 10.f;
	if ((round(((GPU_Particle*)a)->Position[0] / chunk) * chunk) > (round(((GPU_Particle*)b)->Position[0] / chunk) * chunk) &&
		(round(((GPU_Particle*)a)->Position[1] / chunk) * chunk) > (round(((GPU_Particle*)b)->Position[1] / chunk) * chunk) &&
		(round(((GPU_Particle*)a)->Position[2] / chunk) * chunk) > (round(((GPU_Particle*)b)->Position[2] / chunk) * chunk) == true)
	{
		return true;
	}
}

TEXRESULT ReCreate_Fundamental(ElementGraphics* pElement, ChemistryEffectFundamental* pEffect, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (pElement == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_Fundamental()", "pElement == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
	if (pEffect == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_Fundamental()", "pEffect == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	VkResult res = VK_SUCCESS;
	TEXRESULT tres = Success;
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pElement->iGraphicsWindow);

	Engine_Ref_Create_Mutex(pEffect->mutex, MutexType_Plain);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Calculation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	qsort(&pEffect->Particles[0], pEffect->ParticlesSize, sizeof(*pEffect->Particles), cmpfunc);

	//clearing
	/*
	for (int i = 0; i < pEffect->ParticlesSize; i++)
	{
		pEffect->Particles[i].PositionVelocity[3] = -1.0f;
		pEffect->Particles[i].level = -1;
		for (int i00 = 0; i00 < 2; i00++) {
			for (int i10 = 0; i10 < 2; i10++) {
				for (int i20 = 0; i20 < 2; i20++) {
					pEffect->Particles[i].Info0[i00][i10][i20] = -1;
				}
			}
		}
	}
	pEffect->Particles[0].PositionVelocity[3] = 0;
	pEffect->Particles[0].level = 0;
	
	int level = 0;
	bool end = false;
	while (end == false)
	{
		for (int i0 = 0; i0 < pEffect->ParticlesSize; i0++) //make sure correct level
		{		
			//if has parent node
			if (pEffect->Particles[i0].PositionVelocity[3] != -1 && pEffect->Particles[i0].level == level) // 
			{			
				float LevelChunkSize = ((float)pEffect->Resolution / pow(2.0f, ((float)level)));
				float ChunkSizeOffset = ((LevelChunkSize / 2.0f));

				vec3 ChunkPosition = {	(round(pEffect->Particles[i0].Position[0] / ChunkSizeOffset) * ChunkSizeOffset),
										(round(pEffect->Particles[i0].Position[1] / ChunkSizeOffset) * ChunkSizeOffset),
										(round(pEffect->Particles[i0].Position[2] / ChunkSizeOffset) * ChunkSizeOffset) };
				end = true;		
				for (int i1 = 0; i1 < pEffect->ParticlesSize; i1++) //make sure not already a parent ffs
				{
					if ((pEffect->Particles[i1].Position[0]) <= (ChunkPosition[0] + (LevelChunkSize * 8)) &&
						(pEffect->Particles[i1].Position[0]) >= (ChunkPosition[0] - (LevelChunkSize * 8)) &&
						(pEffect->Particles[i1].Position[1]) <= (ChunkPosition[1] + (LevelChunkSize * 8)) &&
						(pEffect->Particles[i1].Position[1]) >= (ChunkPosition[1] - (LevelChunkSize * 8)) &&
						(pEffect->Particles[i1].Position[2]) <= (ChunkPosition[2] + (LevelChunkSize * 8)) &&
						(pEffect->Particles[i1].Position[2]) >= (ChunkPosition[2] - (LevelChunkSize * 8)) &&
						i1 != i0 && 
						pEffect->Particles[i1].PositionVelocity[3] == -1)
					{
						int coord[3] = {glm_clamp((((pEffect->Particles[i1].Position[0] - ChunkPosition[0]) + 1.0f) / 2), 0.0, 1.0),
										glm_clamp((((pEffect->Particles[i1].Position[1] - ChunkPosition[1]) + 1.0f) / 2), 0.0, 1.0),
										glm_clamp((((pEffect->Particles[i1].Position[2] - ChunkPosition[2]) + 1.0f) / 2), 0.0, 1.0) };



						if (pEffect->Particles[i0].Info0[coord[0]][coord[1]][coord[2]] == -1.0f)
						{			
							char buffer[256];
							snprintf(buffer, 256, "%i %i C: %i %i %i P: %f %f %f CP: %f %f %f CS: %f ",
								i0, i1, coord[0], coord[1], coord[2],
								pEffect->Particles[i1].Position[0], pEffect->Particles[i1].Position[1], pEffect->Particles[i1].Position[2],
								ChunkPosition[0], ChunkPosition[1], ChunkPosition[2],
								LevelChunkSize);

							Engine_Ref_FunctionError(buffer, " a", 0);
						
							pEffect->Particles[i1].level = level + 1;
							pEffect->Particles[i1].PositionVelocity[3] = i0;
							pEffect->Particles[i0].Info0[coord[0]][coord[1]][coord[2]] = i1;
						}
					}
					if (pEffect->Particles[i1].PositionVelocity[3] == -1)
					{
						end = false;
					}
				}	
			}
		}
		level++;
	}
	pEffect->Particles[0].PositionVelocity[3] = -1;
	*/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//DescriptorLayout
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	{
		VkDescriptorSetLayoutBinding BindingsCompute[ChemistryFundamentalBuffersCount + ChemistryFundamentalImagesCount] = { (ChemistryFundamentalBuffersCount + ChemistryFundamentalImagesCount) * sizeof(*BindingsCompute) };
		size_t i = 0;
		for (; i < ChemistryFundamentalBuffersCount; i++)
		{
			BindingsCompute[i].binding = i;
			BindingsCompute[i].descriptorCount = 1;
			BindingsCompute[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			BindingsCompute[i].stageFlags = VK_SHADER_STAGE_ALL;
			BindingsCompute[i].pImmutableSamplers = NULL;
		}
		for (; i < ChemistryFundamentalBuffersCount + ChemistryFundamentalImagesCount; i++)
		{
			BindingsCompute[i].binding = i;
			BindingsCompute[i].descriptorCount = 1;
			BindingsCompute[i].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			BindingsCompute[i].stageFlags = VK_SHADER_STAGE_ALL;
			BindingsCompute[i].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)ChemistryFundamentalBuffersCount + ChemistryFundamentalImagesCount;
		Info.pBindings = BindingsCompute;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkDescriptorSetLayout)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_Fundamental()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipeline Layouts
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		VkDescriptorSetLayout layouts[1] = { pEffect->VkDescriptorSetLayout };
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
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkPipelineLayout)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_Fundamental()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Descriptor Pool
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		uint32_t PoolSizesSize = 2;
		VkDescriptorPoolSize PoolSizes[2] = { PoolSizesSize * sizeof(*PoolSizes) };

		PoolSizes[0].descriptorCount = ChemistryFundamentalBuffersCount;
		PoolSizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

		PoolSizes[1].descriptorCount = ChemistryFundamentalImagesCount;
		PoolSizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;

		VkDescriptorPoolCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		Info.maxSets = 1 * pGraphicsWindow->CurrentFrameBuffersSize;
		Info.poolSizeCount = PoolSizesSize;
		Info.pPoolSizes = PoolSizes;
		if ((res = vkCreateDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pEffect->VkDescriptorPool)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_Fundamental()", "vkCreateDescriptorPool, VkResult == ", res);
			return (Failure);
		}
	}
	{
		uint32_t layoutsSize = 1;
		VkDescriptorSetLayout layouts[1] = { pEffect->VkDescriptorSetLayout };
		VkDescriptorSet sets[1];

		VkDescriptorSetAllocateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		Info.descriptorPool = pEffect->VkDescriptorPool;
		Info.descriptorSetCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pNext = NULL;
		if ((res = vkAllocateDescriptorSets(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, sets)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_Fundamental()", "vkAllocateDescriptorSets, VkResult == ", res);
			return (Failure);
		}
		pEffect->VkDescriptorSet = sets[0];
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Allocation
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		VkMemoryRequirements MemoryRequirements = { sizeof(MemoryRequirements) };
		MemoryRequirements.alignment = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.minStorageBufferOffsetAlignment;
		MemoryRequirements.size = pEffect->ParticlesSize * sizeof(*pEffect->Particles);
		MemoryRequirements.memoryTypeBits = NULL;
		pEffect->AllocationParticles0 = Graphics_Ref_GPUmalloc(pGraphicsWindow->pLogicalDevice, MemoryRequirements, TargetMemory_Src, AllocationType_Linear, ThreadIndex);
		if (pEffect->AllocationParticles0.SizeBytes == NULL)
		{
			Engine_Ref_FunctionError("ReCreate_Fundamental()", "Not Enough Space In GPU Memory!", NULL);
			return (Out_Of_Memory_Result | Failure);
		}
		GPU_Particle* pParticles = (GPU_Particle*)((void*)(((uint64_t)pEffect->AllocationParticles0.Allocater.pArenaAllocater->MappedMemory + pEffect->AllocationParticles0.Pointer)));
		memcpy(pParticles, pEffect->Particles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));
	}
	{
		VkMemoryRequirements MemoryRequirements = { sizeof(MemoryRequirements) };
		MemoryRequirements.alignment = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.minStorageBufferOffsetAlignment;
		MemoryRequirements.size = pEffect->ParticlesSize * sizeof(*pEffect->Particles);
		MemoryRequirements.memoryTypeBits = NULL;
		pEffect->AllocationParticles1 = Graphics_Ref_GPUmalloc(pGraphicsWindow->pLogicalDevice, MemoryRequirements, TargetMemory_Src, AllocationType_Linear, ThreadIndex);
		if (pEffect->AllocationParticles1.SizeBytes == NULL)
		{
			Engine_Ref_FunctionError("ReCreate_Fundamental()", "Not Enough Space In GPU Memory!", NULL);
			return (Out_Of_Memory_Result | Failure);
		}
		GPU_Particle* pParticles = (GPU_Particle*)((void*)(((uint64_t)pEffect->AllocationParticles1.Allocater.pArenaAllocater->MappedMemory + pEffect->AllocationParticles1.Pointer)));
		memcpy(pParticles, pEffect->Particles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipelines
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		FileData DataCompute = { 0, 0 };
		Open_Data(&DataCompute, "data\\Shaders\\ChemistryComputeFundamental.comp.spv");

		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderCompute, DataCompute.pData, DataCompute.LinearSize - 1, "ReCreate_Fundamental()");

		VkComputePipelineCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pEffect->VkShaderCompute;
		Info.stage.pName = "main";
		Info.layout = pEffect->VkPipelineLayout;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipelineCompute)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_Fundamental()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return (Failure);
		}
		free(DataCompute.pData);
	}
	{
		FileData DataVertex = { 0, 0 };
		Open_Data(&DataVertex, "data\\Shaders\\ChemistryComputeFundamental.vert.spv");

		FileData DataFragment = { 0, 0 };
		Open_Data(&DataFragment, "data\\Shaders\\ChemistryComputeFundamental.frag.spv");

		//const SPIRV Vertex[] = VertexShaderFundamental();
		//const SPIRV Fragment[] = FragmentShaderSimplifiedMolecular();

		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderVertex, DataVertex.pData, DataVertex.LinearSize - 1, "ReCreate_Fundamental()");
		CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pEffect->VkShaderFragment, DataFragment.pData, DataFragment.LinearSize - 1, "ReCreate_Fundamental()");

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
		VkVertexInputBindingDescription InputBindingDescs[1] = {sizeof(InputBindingDescs) * InputBindingDescsSize };
		uint64_t InputAttribDescsSize = 2;
		VkVertexInputAttributeDescription InputAttribDescs[2] = { sizeof(InputAttribDescs) * InputAttribDescsSize };

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


		//pipeline
		VkPipelineVertexInputStateCreateInfo VertexInputInfo;
		memset(&VertexInputInfo, 0, sizeof(VertexInputInfo));
		VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

		VertexInputInfo.vertexBindingDescriptionCount = (uint32_t)InputBindingDescsSize;
		VertexInputInfo.pVertexBindingDescriptions = InputBindingDescs; // Optional

		VertexInputInfo.vertexAttributeDescriptionCount = (uint32_t)InputAttribDescsSize;
		VertexInputInfo.pVertexAttributeDescriptions = InputAttribDescs; // Optional

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
		ColourBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
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

		VkViewport Viewport;
		memset(&Viewport, 0, sizeof(Viewport));
		Viewport.x = 0.0f;
		Viewport.y = 0.0f;
		Viewport.width = (float)pGraphicsWindow->CurrentExtentWidth;
		Viewport.height = (float)pGraphicsWindow->CurrentExtentHeight;
		Viewport.minDepth = 0.0f;
		Viewport.maxDepth = 1.0f;

		VkRect2D Scissor;
		memset(&Scissor, 0, sizeof(Scissor));
		Scissor.offset.x = 0;
		Scissor.offset.y = 0;
		Scissor.extent.width = pGraphicsWindow->CurrentExtentWidth;
		Scissor.extent.height = pGraphicsWindow->CurrentExtentHeight;

		VkPipelineViewportStateCreateInfo ViewportState;
		memset(&ViewportState, 0, sizeof(ViewportState));
		ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		ViewportState.viewportCount = 1;
		ViewportState.pViewports = &Viewport;
		ViewportState.scissorCount = 1;
		ViewportState.pScissors = &Scissor;

		VkPipelineInputAssemblyStateCreateInfo InputAssemblyState;
		memset(&InputAssemblyState, 0, sizeof(InputAssemblyState));
		InputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		InputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		InputAssemblyState.primitiveRestartEnable = VK_FALSE;

		VkPipelineRasterizationStateCreateInfo RasterizationState;
		memset(&RasterizationState, 0, sizeof(RasterizationState));
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

		VkGraphicsPipelineCreateInfo Info;
		memset(&Info, 0, sizeof(Info));

		Info.subpass = 1;
		ColourBlending.attachmentCount = 2;

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
		Info.layout = pEffect->VkPipelineLayout;
		Info.renderPass = pGraphicsWindow->VkRenderPassDeferred;
		//Info.subpass = 1;
		Info.basePipelineHandle = VK_NULL_HANDLE; // Optional
		Info.basePipelineIndex = -1; // Optional

		if ((res = vkCreateGraphicsPipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pEffect->VkPipeline)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_Fundamental()", "vkCreateGraphicsPipelines Failed. VkResult == ", res);
			return (Failure);
		}
		free(DataVertex.pData);
		free(DataFragment.pData);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Updating Descriptor Sets
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{
		VkDescriptorBufferInfo BufferInfo = { sizeof(BufferInfo) };
		BufferInfo.buffer = pEffect->AllocationParticles0.Allocater.pArenaAllocater->VkBuffer;
		BufferInfo.offset = pEffect->AllocationParticles0.Pointer;
		BufferInfo.range = pEffect->AllocationParticles0.SizeBytes;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pEffect->VkDescriptorSet, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &BufferInfo, NULL);
	}
	{
		VkDescriptorBufferInfo BufferInfo = { sizeof(BufferInfo) };
		BufferInfo.buffer = pEffect->AllocationParticles1.Allocater.pArenaAllocater->VkBuffer;
		BufferInfo.offset = pEffect->AllocationParticles1.Pointer;
		BufferInfo.range = pEffect->AllocationParticles1.SizeBytes;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pEffect->VkDescriptorSet, 1, 0, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &BufferInfo, NULL);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Rendering
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	/*
	VkCommandPool VkCmdPool = NULL;
	VkCommandBuffer VkCmdBuffer = NULL;
	{
		VkCommandPoolCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		Info.queueFamilyIndex = pGraphicsWindow->pLogicalDevice->ComputeQueueFamilyIndex;
		Info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
		if ((res = vkCreateCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &VkCmdPool)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateCommandPool Failed, VkResult == ", res);
			return (Failure);
		}
	}
	{
		VkCommandBufferAllocateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		Info.commandPool = VkCmdPool;
		Info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		Info.commandBufferCount = 1;
		Info.pNext = NULL;
		if ((res = vkAllocateCommandBuffers(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, &VkCmdBuffer)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkAllocateCommandBuffers Failed, VkResult == ", res);
			return (Failure);
		}
	}
	{
		VkCommandBufferBeginInfo BeginInfo;
		memset(&BeginInfo, 0, sizeof(BeginInfo));
		BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
		BeginInfo.pInheritanceInfo = NULL;
		BeginInfo.pNext = NULL;
		if ((res = vkBeginCommandBuffer(VkCmdBuffer, &BeginInfo)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkBeginCommandBuffer Failed, VkResult == ", res);
			return (Failure);
		}
	}

	{//first pass
		{
			VkBufferMemoryBarrier Barrier = { sizeof(Barrier) };
			Barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
			Barrier.buffer = pEffect->AllocationParticles0.Allocater.pArenaAllocater->VkBuffer;
			Barrier.offset = pEffect->AllocationParticles0.Pointer;
			Barrier.size = pEffect->AllocationParticles0.SizeBytes;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = 0;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				1, &Barrier,
				0, NULL
			);
		}
		{
			VkBufferMemoryBarrier Barrier = { sizeof(Barrier) };
			Barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
			Barrier.buffer = pEffect->AllocationParticles1.Allocater.pArenaAllocater->VkBuffer;
			Barrier.offset = pEffect->AllocationParticles1.Pointer;
			Barrier.size = pEffect->AllocationParticles1.SizeBytes;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = 0;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				1, &Barrier,
				0, NULL
			);
		}
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pEffect->ImageMap0.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = 0;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
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
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pEffect->ImageMap1.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = 0;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
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
		{
			vkCmdBindPipeline(VkCmdBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pEffect->VkPipelineCompute);
			vkCmdBindDescriptorSets(VkCmdBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
				pEffect->VkPipelineLayout, 0, 1, &pEffect->VkDescriptorSet, 0, NULL);

			uint64_t log_2_N = (int)(log(pEffect->ParticlesSize) / log(2));
			uint64_t c = 1;
			for (size_t i = 0; i < log_2_N + 1; i++)
			{
				PushConstantsComputeFundamental PushConstants;
				memset(&PushConstants, 0, sizeof(PushConstants));
				PushConstants.Part = 0;
				PushConstants.Particles = pEffect->ParticlesSize;
				PushConstants.ChunkSize = pEffect->ChunkSize;
				PushConstants.Resolution = pEffect->Resolution;
				vkCmdPushConstants(VkCmdBuffer, pEffect->VkPipelineLayout, VK_SHADER_STAGE_ALL, 0,
					pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &PushConstants);

				vkCmdDispatch(VkCmdBuffer, c, 1, 1);
				c *= 2;
			}
		}
		{
			VkBufferMemoryBarrier Barrier = { sizeof(Barrier) };
			Barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
			Barrier.buffer = pEffect->AllocationParticles0.Allocater.pArenaAllocater->VkBuffer;
			Barrier.offset = pEffect->AllocationParticles0.Pointer;
			Barrier.size = pEffect->AllocationParticles0.SizeBytes;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				1, &Barrier,
				0, NULL
			);
		}
		{
			VkBufferMemoryBarrier Barrier = { sizeof(Barrier) };
			Barrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
			Barrier.buffer = pEffect->AllocationParticles1.Allocater.pArenaAllocater->VkBuffer;
			Barrier.offset = pEffect->AllocationParticles1.Pointer;
			Barrier.size = pEffect->AllocationParticles1.SizeBytes;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
			Barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
			Barrier.pNext = NULL;

			vkCmdPipelineBarrier(
				VkCmdBuffer,
				VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
				0,
				0, NULL,
				1, &Barrier,
				0, NULL
			);
		}
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pEffect->ImageMap0.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
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
		{
			VkImageMemoryBarrier Barrier;
			Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
			Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
			Barrier.image = pEffect->ImageMap1.VkImage;
			Barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			Barrier.subresourceRange.baseMipLevel = 0;
			Barrier.subresourceRange.levelCount = 1;
			Barrier.subresourceRange.baseArrayLayer = 0;
			Barrier.subresourceRange.layerCount = 1;
			Barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
			Barrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;
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
	memset(&SubmitInfo, 0, sizeof(SubmitInfo));
	SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	SubmitInfo.commandBufferCount = (uint32_t)1;
	SubmitInfo.pCommandBuffers = &VkCmdBuffer;

	if ((res = vkQueueSubmit(Queue, 1, &SubmitInfo, VK_NULL_HANDLE)) != VK_SUCCESS)
	{
		Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkQueueSubmit Failed, VkResult == ", res);
		return (Failure);
	}

	vkQueueWaitIdle(Queue);
	Engine_Ref_Unlock_Mutex(pGraphicsWindow->pLogicalDevice->ComputeQueueMutexes[QueueIndex]);

	vkFreeCommandBuffers(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VkCmdPool, 1, &VkCmdBuffer);
	vkDestroyCommandPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VkCmdPool, NULL);
	*/
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Packers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Pack_SimpleModel(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const ChemistryEffectSimpleModel* pEffect, ChemistryEffectSimpleModel* pCopiedEffect, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	return (Success);
}

TEXRESULT Pack_FullModel(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const ChemistryEffectFullModel* pEffect, ChemistryEffectFullModel* pCopiedEffect, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedEffect->PingPongIndex, 0, sizeof(pCopiedEffect->PingPongIndex));

		memset(&pCopiedEffect->mutex, 0, sizeof(pCopiedEffect->mutex));

		memset(&pCopiedEffect->AllocationParticles, 0, sizeof(pCopiedEffect->AllocationParticles));

		memset(&pCopiedEffect->VkPipelineComputeSource, 0, sizeof(pCopiedEffect->VkPipelineComputeSource));
		memset(&pCopiedEffect->VkShaderComputeSource, 0, sizeof(pCopiedEffect->VkShaderComputeSource));

		memset(&pCopiedEffect->VkPipelineComputeField, 0, sizeof(pCopiedEffect->VkPipelineComputeField));
		memset(&pCopiedEffect->VkShaderComputeField, 0, sizeof(pCopiedEffect->VkShaderComputeField));

		memset(&pCopiedEffect->VkPipelineLayout, 0, sizeof(pCopiedEffect->VkPipelineLayout));
		memset(&pCopiedEffect->VkDescriptorSetLayout, 0, sizeof(pCopiedEffect->VkDescriptorSetLayout));
		memset(&pCopiedEffect->VkDescriptorSets, 0, sizeof(pCopiedEffect->VkDescriptorSets));
		memset(&pCopiedEffect->VkDescriptorPool, 0, sizeof(pCopiedEffect->VkDescriptorPool));


		memset(&pCopiedEffect->VkPipeline, 0, sizeof(pCopiedEffect->VkPipeline));
		memset(&pCopiedEffect->VkShaderVertex, 0, sizeof(pCopiedEffect->VkShaderVertex));
		memset(&pCopiedEffect->VkShaderFragment, 0, sizeof(pCopiedEffect->VkShaderFragment));

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
	return (Success);
}

TEXRESULT Pack_Fundamental(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const ChemistryEffectFundamental* pEffect, ChemistryEffectFundamental* pCopiedEffect, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedEffect->mutex, 0, sizeof(pCopiedEffect->mutex));

		memset(&pCopiedEffect->AllocationParticles0, 0, sizeof(pCopiedEffect->AllocationParticles0));
		memset(&pCopiedEffect->AllocationParticles1, 0, sizeof(pCopiedEffect->AllocationParticles1));

		memset(&pCopiedEffect->VkPipelineCompute, 0, sizeof(pCopiedEffect->VkPipelineCompute));
		memset(&pCopiedEffect->VkShaderCompute, 0, sizeof(pCopiedEffect->VkShaderCompute));

		memset(&pCopiedEffect->VkPipelineLayout, 0, sizeof(pCopiedEffect->VkPipelineLayout));
		memset(&pCopiedEffect->VkDescriptorSetLayout, 0, sizeof(pCopiedEffect->VkDescriptorSetLayout));
		memset(&pCopiedEffect->VkDescriptorSet, 0, sizeof(pCopiedEffect->VkDescriptorSet));
		memset(&pCopiedEffect->VkDescriptorPool, 0, sizeof(pCopiedEffect->VkDescriptorPool));


		memset(&pCopiedEffect->VkPipeline, 0, sizeof(pCopiedEffect->VkPipeline));
		memset(&pCopiedEffect->VkShaderVertex, 0, sizeof(pCopiedEffect->VkShaderVertex));
		memset(&pCopiedEffect->VkShaderFragment, 0, sizeof(pCopiedEffect->VkShaderFragment));

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
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect UnPackers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT UnPack_SimpleModel(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const ChemistryEffectSimpleModel* pEffect, ChemistryEffectSimpleModel* pCopiedEffect, const void* pData, uint32_t ThreadIndex)
{
	return (Success);
}

TEXRESULT UnPack_FullModel(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const ChemistryEffectFullModel* pEffect, ChemistryEffectFullModel* pCopiedEffect, const void* pData, uint32_t ThreadIndex)
{
	if (pEffect->Particles != NULL)
	{
		pCopiedEffect->Particles = calloc(pCopiedEffect->ParticlesSize, sizeof(*pCopiedEffect->Particles));
		memcpy(pCopiedEffect->Particles, ((void*)((uint64_t)pData + (uint64_t)pEffect->Particles)), pEffect->ParticlesSize * sizeof(*pEffect->Particles));
	}
	return (Success);
}

TEXRESULT UnPack_Fundamental(const ElementGraphics* pElement, ElementGraphics* pCopiedElement, const ChemistryEffectFundamental* pEffect, ChemistryEffectFundamental* pCopiedEffect, const void* pData, uint32_t ThreadIndex)
{
	if (pEffect->Particles != NULL)
	{
		pCopiedEffect->Particles = calloc(pCopiedEffect->ParticlesSize, sizeof(*pCopiedEffect->Particles));
		memcpy(pCopiedEffect->Particles, ((void*)((uint64_t)pData + (uint64_t)pEffect->Particles)), pEffect->ParticlesSize * sizeof(*pEffect->Particles));
	}
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Effect Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_SimpleModel(ElementGraphics* pElement, ChemistryEffectSimpleModel* pEffect, ChemistryEffectCreateInfoSimpleModel* pEffectCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pEffect == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pEffectCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_SimpleModel()", "pEffectCreateInfo == NULLPTR");
			return (Invalid_Parameter | Failure);
		}
#endif
		ReCreate_SimpleModel(pElement, pEffect, ThreadIndex);
	}
	*pAllocationSize = sizeof(ChemistryEffectSimpleModel);
	return (Success);
}

TEXRESULT Create_FullModel(ElementGraphics* pElement, ChemistryEffectFullModel* pEffect, ChemistryEffectCreateInfoFullModel* pEffectCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pEffect == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pEffectCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_FullModel()", "pEffectCreateInfo == NULLPTR");
			return (Invalid_Parameter | Failure);
		}
#endif
		pEffect->SimulationResolution = pEffectCreateInfo->SimulationResolution;

		if (pEffectCreateInfo->ParticlesSize != 0)
		{
			pEffect->ParticlesSize = pEffectCreateInfo->ParticlesSize;
			pEffect->Particles = calloc(pEffect->ParticlesSize, sizeof(*pEffect->Particles));
			memcpy(pEffect->Particles, pEffectCreateInfo->Particles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));
		}
		ReCreate_FullModel(pElement, pEffect, ThreadIndex);
	}
	*pAllocationSize = sizeof(ChemistryEffectFullModel);
	return (Success);
}

TEXRESULT Create_Fundamental(ElementGraphics* pElement, ChemistryEffectFundamental* pEffect, ChemistryEffectCreateInfoFundamental* pEffectCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pEffect == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pEffectCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_Fundamental()", "pEffectCreateInfo == NULLPTR");
			return (Invalid_Parameter | Failure);
		}
#endif
		//pEffect->ChunkSize = pEffectCreateInfo->ChunkSize;
		pEffect->Resolution = pEffectCreateInfo->Resolution;
		if (pEffectCreateInfo->ParticlesSize != 0)
		{
			pEffect->ParticlesSize = pEffectCreateInfo->ParticlesSize;
			pEffect->Particles = calloc(pEffect->ParticlesSize, sizeof(*pEffect->Particles));
			memcpy(pEffect->Particles, pEffectCreateInfo->Particles, pEffect->ParticlesSize * sizeof(*pEffect->Particles));
		}
		ReCreate_Fundamental(pElement, pEffect, ThreadIndex);
	}
	*pAllocationSize = sizeof(ChemistryEffectFundamental);
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Initialise_Chemistry()
{
	Utils.SimpleModelSignature.Identifier = (uint32_t)ChemistryEffects_SimpleModel;
	Utils.SimpleModelSignature.Constructor = (Create_GraphicsEffectTemplate*)&Create_SimpleModel;
	Utils.SimpleModelSignature.ReConstructor = (ReCreate_GraphicsEffectTemplate*)&ReCreate_SimpleModel;
	Utils.SimpleModelSignature.Destructor = (Destroy_GraphicsEffectTemplate*)&Destroy_SimpleModel;
	Utils.SimpleModelSignature.Packer = (Pack_GraphicsEffectTemplate*)&Pack_SimpleModel;
	Utils.SimpleModelSignature.UnPacker = (UnPack_GraphicsEffectTemplate*)&UnPack_SimpleModel;
	Utils.SimpleModelSignature.Update = (Update_GraphicsEffectTemplate*)&Update_SimpleModel;
	Utils.SimpleModelSignature.Draw = (Draw_GraphicsEffectTemplate*)&Draw_SimpleModel;
	Utils.SimpleModelSignature.UpdateSignature = &UpdateSignature_SimpleModel;
	Utils.SimpleModelSignature.DrawSignature = &DrawSignature_SimpleModel;
	Utils.SimpleModelSignature.SignatureGPUBuffersSize = ChemistrySimpleModelBuffersCount;
	Graphics_Effects_Ref_Register_GraphicsEffectSignature(&Utils.SimpleModelSignature);

	Utils.FullModelSignature.Identifier = (uint32_t)ChemistryEffects_FullModel;
	Utils.FullModelSignature.Constructor = (Create_GraphicsEffectTemplate*)&Create_FullModel;
	Utils.FullModelSignature.ReConstructor = (ReCreate_GraphicsEffectTemplate*)&ReCreate_FullModel;
	Utils.FullModelSignature.Destructor = (Destroy_GraphicsEffectTemplate*)&Destroy_FullModel;
	Utils.FullModelSignature.Packer = (Pack_GraphicsEffectTemplate*)&Pack_FullModel;
	Utils.FullModelSignature.UnPacker = (UnPack_GraphicsEffectTemplate*)&UnPack_FullModel;
	Utils.FullModelSignature.Update = (Update_GraphicsEffectTemplate*)&Update_FullModel;
	Utils.FullModelSignature.Draw = (Draw_GraphicsEffectTemplate*)&Draw_FullModel;
	Utils.FullModelSignature.UpdateSignature = &UpdateSignature_FullModel;
	Utils.FullModelSignature.DrawSignature = &DrawSignature_FullModel;
	Utils.FullModelSignature.SignatureGPUBuffersSize = ChemistryFullModelBuffersCount;
	Graphics_Effects_Ref_Register_GraphicsEffectSignature(&Utils.FullModelSignature);

	Utils.FundamentalSignature.Identifier = (uint32_t)ChemistryEffects_Fundamental;
	Utils.FundamentalSignature.Constructor = (Create_GraphicsEffectTemplate*)&Create_Fundamental;
	Utils.FundamentalSignature.ReConstructor = (ReCreate_GraphicsEffectTemplate*)&ReCreate_Fundamental;
	Utils.FundamentalSignature.Destructor = (Destroy_GraphicsEffectTemplate*)&Destroy_Fundamental;
	Utils.FundamentalSignature.Packer = (Pack_GraphicsEffectTemplate*)&Pack_Fundamental;
	Utils.FundamentalSignature.UnPacker = (UnPack_GraphicsEffectTemplate*)&UnPack_Fundamental;
	Utils.FundamentalSignature.Update = (Update_GraphicsEffectTemplate*)&Update_Fundamental;
	Utils.FundamentalSignature.Draw = (Draw_GraphicsEffectTemplate*)&Draw_Fundamental;
	Utils.FundamentalSignature.UpdateSignature = &UpdateSignature_Fundamental;
	Utils.FundamentalSignature.DrawSignature = &DrawSignature_Fundamental;
	Utils.FundamentalSignature.SignatureGPUBuffersSize = ChemistryFundamentalBuffersCount;
	Graphics_Effects_Ref_Register_GraphicsEffectSignature(&Utils.FundamentalSignature);

	return (TEXRESULT)(Success);
}

TEXRESULT Destroy_Chemistry()
{
	//Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.SimplifiedMolecularSignature);

	//Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.QuantumAtomicSignature);
	return Success;
}

TEXRESULT Update_Chemistry()
{	
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


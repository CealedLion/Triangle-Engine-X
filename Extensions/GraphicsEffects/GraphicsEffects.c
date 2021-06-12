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
#include <vulkan/vulkan.h>
#include <vulkan/spirv.h>
#define TEX_EXPOSE_GRAPHICS
#include "Graphics.h"
#include "GraphicsShaders.h"
#define TEX_EXPOSE_GRAPHICSEFFECTS
#include "GraphicsEffects.h"

volatile struct{
	uint64_t InitialHeadersMax;
}Config;

volatile GraphicsEffectsUtils Utils;


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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Misc
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_WaterTexture(GPU_Texture* pGPU_Texture, LogicalDevice* pLogicalDevice, uint32_t Width, uint32_t Height, GraphicsFormat Format, AllocationType Type, uint32_t ThreadIndex)
{
	VkResult res = VK_SUCCESS;
	{
		VkImageCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		Info.pNext = NULL;
		Info.flags = NULL;
		Info.imageType = VK_IMAGE_TYPE_2D;
		Info.format = (VkFormat)Format;
		Info.extent.width = Width;
		Info.extent.height = Height;
		Info.extent.depth = 1;
		Info.mipLevels = 1;
		Info.arrayLayers = 1;
		Info.samples = VK_SAMPLE_COUNT_1_BIT;
		Info.tiling = VK_IMAGE_TILING_OPTIMAL;
		Info.usage = VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		Info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		Info.queueFamilyIndexCount = NULL;
		Info.pQueueFamilyIndices = NULL;
		Info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		if ((res = vkCreateImage(pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGPU_Texture->VkImage)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("Create_WaterTexture()", "vkCreateImage Failed, VkResult == ", res);
			return (Failure);
		}
	}
	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(pLogicalDevice->VkLogicalDevice, pGPU_Texture->VkImage, &memRequirements);
	pGPU_Texture->Allocation = Graphics_Ref_GPUmalloc(pLogicalDevice, memRequirements, TargetMemory_Dst, Type, ThreadIndex);
	if (pGPU_Texture->Allocation.SizeBytes == NULL)
	{
		Engine_Ref_FunctionError("Create_WaterTexture()", "Not Enough Space In GPU Memory!", NULL);
		return (Failure);
	}

	if ((res = vkBindImageMemory(pLogicalDevice->VkLogicalDevice, pGPU_Texture->VkImage, pGPU_Texture->Allocation.Allocater.VkMemory, pGPU_Texture->Allocation.Pointer)) != VK_SUCCESS)
	{
		Engine_Ref_FunctionError("Create_WaterTexture()", "vkBindImageMemory Failed, VkResult == ", res);
		return (Failure);
	}
	{
		VkImageViewCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		Info.image = pGPU_Texture->VkImage;
		Info.viewType = VK_IMAGE_VIEW_TYPE_2D;
		Info.format = (VkFormat)Format;

		Info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		Info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		Info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		Info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		Info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		Info.subresourceRange.baseMipLevel = 0;
		Info.subresourceRange.levelCount = 1;
		Info.subresourceRange.baseArrayLayer = 0;
		Info.subresourceRange.layerCount = 1;

		if ((res = vkCreateImageView(pLogicalDevice->VkLogicalDevice, &Info, NULL, &pGPU_Texture->VkImageView)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("Create_WaterTexture()", "vkCreateImageView Failed, VkResult == ", res);
			return (Failure);
		}
	}
	return (Success);
}

unsigned char reverse(unsigned char n, size_t b){
	unsigned char rv = 0;
	for (size_t i = 0; i < b; ++i, n >>= 1) {
		rv = (rv << 1) | (n & 0x01);
	}
	return rv;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Destructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Destroy_WaterRenderHeader(RHeaderWaterRender* pResourceHeader, bool Full, uint32_t ThreadIndex)
{
	Engine_Ref_Lock_Mutex(pResourceHeader->mutex);

	//every reinit
	RHeaderGraphicsWindow* pGraphicsWindow = Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);

	LogicalDevice* pLogicalDevice = pGraphicsWindow->pLogicalDevice;

	Graphics_Ref_GPUfree(pLogicalDevice, &pResourceHeader->AllocationBitReversedIndices);

	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->Textureh0k);
	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->TextureTwiddleFactors);
	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->Texturehkt_dy);
	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->Texturehkt_dx);
	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->Texturehkt_dz);
	Graphics_Ref_Destroy_GPU_Texture(pLogicalDevice, &pResourceHeader->TexturePingPong);
	if (pResourceHeader->VkShaderh0k != NULL)
		vkDestroyShaderModule(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderh0k, NULL);
	if (pResourceHeader->VkShaderTwiddleFactors != NULL)
		vkDestroyShaderModule(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderTwiddleFactors, NULL);
	if (pResourceHeader->VkShaderhkt != NULL)
		vkDestroyShaderModule(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderhkt, NULL);
	if (pResourceHeader->VkShaderButterfly != NULL)
		vkDestroyShaderModule(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderButterfly, NULL);
	if (pResourceHeader->VkShaderInversion != NULL)
		vkDestroyShaderModule(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkShaderInversion, NULL);
	if (pResourceHeader->VkDescriptorSetLayouth0k != NULL)
		vkDestroyDescriptorSetLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorSetLayouth0k, NULL);
	if (pResourceHeader->VkDescriptorSetLayoutTwiddleFactors != NULL)
		vkDestroyDescriptorSetLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorSetLayoutTwiddleFactors, NULL);
	if (pResourceHeader->VkDescriptorSetLayouthkt != NULL)
		vkDestroyDescriptorSetLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorSetLayouthkt, NULL);
	if (pResourceHeader->VkDescriptorSetLayoutButterfly != NULL)
		vkDestroyDescriptorSetLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorSetLayoutButterfly, NULL);
	if (pResourceHeader->VkDescriptorSetLayoutInversion != NULL)
		vkDestroyDescriptorSetLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorSetLayoutInversion, NULL);
	if (pResourceHeader->VkPipelineLayouth0k != NULL)
		vkDestroyPipelineLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineLayouth0k, NULL);
	if (pResourceHeader->VkPipelineLayoutTwiddleFactors != NULL)
		vkDestroyPipelineLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineLayoutTwiddleFactors, NULL);
	if (pResourceHeader->VkPipelineLayouthkt != NULL)
		vkDestroyPipelineLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineLayouthkt, NULL);
	if (pResourceHeader->VkPipelineLayoutButterfly != NULL)
		vkDestroyPipelineLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineLayoutButterfly, NULL);
	if (pResourceHeader->VkPipelineLayoutInversion != NULL)
		vkDestroyPipelineLayout(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineLayoutInversion, NULL);
	if (pResourceHeader->VkPipelineh0k != NULL)
		vkDestroyPipeline(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineh0k, NULL);
	if (pResourceHeader->VkPipelineTwiddleFactors != NULL)
		vkDestroyPipeline(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineTwiddleFactors, NULL);
	if (pResourceHeader->VkPipelinehkt != NULL)
		vkDestroyPipeline(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelinehkt, NULL);
	if (pResourceHeader->VkPipelineButterfly != NULL)
		vkDestroyPipeline(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineButterfly, NULL);
	if (pResourceHeader->VkPipelineInversion != NULL)
		vkDestroyPipeline(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkPipelineInversion, NULL);
	//if (pResourceHeader->VkDescriptorSeth0k != NULL)
	//	free(pResourceHeader->VkDescriptorSeth0k);
	//if (pResourceHeader->VkDescriptorSetTwiddleFactors != NULL)
	//	free(pResourceHeader->VkDescriptorSetTwiddleFactors);
	//if (pResourceHeader->VkDescriptorSethkt != NULL)
	//	free(pResourceHeader->VkDescriptorSethkt);
	//if (pResourceHeader->VkDescriptorSetButterfly != NULL)
	//	free(pResourceHeader->VkDescriptorSetButterfly);
	//if (pResourceHeader->VkDescriptorSetInversion != NULL)
	//	free(pResourceHeader->VkDescriptorSetInversion);
	if (pResourceHeader->VkDescriptorPoolWater != NULL)
		vkDestroyDescriptorPool(pLogicalDevice->VkLogicalDevice, pResourceHeader->VkDescriptorPoolWater, NULL);

	Engine_Ref_Destroy_Mutex(pResourceHeader->mutex);
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ReCreate
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT ReCreate_WaterRenderHeader(RHeaderWaterRender* pResourceHeader, uint32_t ThreadIndex)
{
#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iGraphicsWindow) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_WaterRenderHeader()", "pResourceHeader->iGraphicsWindow Invalid");
		return (Invalid_Parameter | Failure);
	}
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iTextureTarget) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_WaterRenderHeader()", "pResourceHeader->iTextureTarget Invalid");
		return (Invalid_Parameter | Failure);
	}
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pResourceHeader->iNoise) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_WaterRenderHeader()", "pResourceHeader->iNoise Invalid");
		return (Invalid_Parameter | Failure);
	}
#endif
	RHeaderGraphicsWindow* pGraphicsWindow = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
	RHeaderTexture* pTexture = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iTextureTarget);
	RHeaderTexture* pNoise = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iNoise);

	RHeaderImageSource* pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture->iImageSource);

#ifndef NDEBUG
	if (Object_Ref_Get_ResourceHeaderAllocationValidity(pTexture->iImageSource) != Success)
	{
		Engine_Ref_ArgsError("ReCreate_WaterRenderHeader()", "pTexture->iImageSource Invalid");
		return (Invalid_Parameter | Failure);
	}
	if (pImageSource->ImageData == NULL)
	{
		Engine_Ref_ArgsError("ReCreate_WaterRenderHeader()", "pImageSource->ImageData == NULLPTR");
		return (Invalid_Parameter | Failure);
	}
#endif
	pImageSource->ImageData->Width = pResourceHeader->WaterResolution;
	pImageSource->ImageData->Height = pResourceHeader->WaterResolution;
	pImageSource->ImageData->Depth = 1;
	pImageSource->ImageData->Format = GraphicsFormat_R32G32B32A32_SFLOAT;
	pImageSource->ImageData->MipmapCount = 1;
	Object_Ref_ReCreate_ResourceHeader(pTexture->Header.Allocation, NULL, ThreadIndex);

	TEXRESULT tres = Success;
	VkResult res = VK_SUCCESS;

	Engine_Ref_Create_Mutex(pResourceHeader->mutex, MutexType_Plain);

	const SPIRV Shaderh0k[] = ComputeShaderh0k();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkShaderh0k, Shaderh0k, ComputeShaderh0kSize, "ReCreate_WaterRenderHeader()");
	const SPIRV ShaderTwiddleFactors[] = ComputeShaderTwiddleFactors();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkShaderTwiddleFactors, ShaderTwiddleFactors, ComputeShaderTwiddleFactorsSize, "ReCreate_WaterRenderHeader()");
	const SPIRV Shaderhkt[] = ComputeShaderhkt();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkShaderhkt, Shaderhkt, ComputeShaderhktSize, "ReCreate_WaterRenderHeader()");
	const SPIRV ShaderButterfly[] = ComputeShaderButterfly();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkShaderButterfly, ShaderButterfly, ComputeShaderButterflySize, "ReCreate_WaterRenderHeader()");
	const SPIRV ShaderInversion[] = ComputeShaderInversion();
	CompileVkShaderModule(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkShaderInversion, ShaderInversion, ComputeShaderInversionSize, "ReCreate_WaterRenderHeader()");


	uint64_t log_2_N = (int)(log(pResourceHeader->WaterResolution) / log(2));

	if ((tres = Create_WaterTexture(&pResourceHeader->Textureh0k, pGraphicsWindow->pLogicalDevice, pResourceHeader->WaterResolution, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return (Failure);
	if ((tres = Create_WaterTexture(&pResourceHeader->Texturehkt_dy, pGraphicsWindow->pLogicalDevice, pResourceHeader->WaterResolution, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return (Failure);
	if ((tres = Create_WaterTexture(&pResourceHeader->Texturehkt_dx, pGraphicsWindow->pLogicalDevice, pResourceHeader->WaterResolution, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return (Failure);
	if ((tres = Create_WaterTexture(&pResourceHeader->Texturehkt_dz, pGraphicsWindow->pLogicalDevice, pResourceHeader->WaterResolution, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return (Failure);
	if ((tres = Create_WaterTexture(&pResourceHeader->TextureTwiddleFactors, pGraphicsWindow->pLogicalDevice, log_2_N, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return (Failure);
	if ((tres = Create_WaterTexture(&pResourceHeader->TexturePingPong, pGraphicsWindow->pLogicalDevice, pResourceHeader->WaterResolution, pResourceHeader->WaterResolution,
		GraphicsFormat_R32G32B32A32_SFLOAT, AllocationType_Linear, ThreadIndex)) != Success)
		return (Failure);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//DescriptorLayout
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	{//Layout h0k
#define Bindingsh0kCount 2
		VkDescriptorSetLayoutBinding Bindings[Bindingsh0kCount];
		{
			Bindings[0].binding = 0;
			Bindings[0].descriptorCount = 1;
			Bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[0].pImmutableSamplers = NULL;
		}
		{
			Bindings[1].binding = 1;
			Bindings[1].descriptorCount = 1;
			Bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
			Bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[1].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)Bindingsh0kCount;
		Info.pBindings = Bindings;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorSetLayouth0k)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}
	{//Layout twiddlefactors
#define BindingsTwiddleFactorsCount 2
		VkDescriptorSetLayoutBinding Bindings[BindingsTwiddleFactorsCount];
		{
			Bindings[0].binding = 0;
			Bindings[0].descriptorCount = 1;
			Bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[0].pImmutableSamplers = NULL;
		}
		{
			Bindings[1].binding = 1;
			Bindings[1].descriptorCount = 1;
			Bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
			Bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[1].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)BindingsTwiddleFactorsCount;
		Info.pBindings = Bindings;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorSetLayoutTwiddleFactors)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}
	{//Layout hkt
#define BindingshktCount 4
		VkDescriptorSetLayoutBinding Bindings[BindingshktCount];
		{
			Bindings[0].binding = 0;
			Bindings[0].descriptorCount = 1;
			Bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[0].pImmutableSamplers = NULL;
		}
		{
			Bindings[1].binding = 1;
			Bindings[1].descriptorCount = 1;
			Bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[1].pImmutableSamplers = NULL;
		}
		{
			Bindings[2].binding = 2;
			Bindings[2].descriptorCount = 1;
			Bindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[2].pImmutableSamplers = NULL;
		}
		{
			Bindings[3].binding = 3;
			Bindings[3].descriptorCount = 1;
			Bindings[3].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[3].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[3].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)BindingshktCount;
		Info.pBindings = Bindings;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorSetLayouthkt)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}
	{//Layout butterfly
#define BindingsButterflyCount 3
		VkDescriptorSetLayoutBinding Bindings[BindingsButterflyCount];
		{
			Bindings[0].binding = 0;
			Bindings[0].descriptorCount = 1;
			Bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[0].pImmutableSamplers = NULL;
		}
		{
			Bindings[1].binding = 1;
			Bindings[1].descriptorCount = 1;
			Bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[1].pImmutableSamplers = NULL;
		}
		{
			Bindings[2].binding = 2;
			Bindings[2].descriptorCount = 1;
			Bindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[2].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)BindingsButterflyCount;
		Info.pBindings = Bindings;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorSetLayoutButterfly)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}
	{//Layout inversion
#define BindingsInversionCount 3
		VkDescriptorSetLayoutBinding Bindings[BindingsInversionCount];
		{
			Bindings[0].binding = 0;
			Bindings[0].descriptorCount = 1;
			Bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[0].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[0].pImmutableSamplers = NULL;
		}
		{
			Bindings[1].binding = 1;
			Bindings[1].descriptorCount = 1;
			Bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[1].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[1].pImmutableSamplers = NULL;
		}
		{
			Bindings[2].binding = 2;
			Bindings[2].descriptorCount = 1;
			Bindings[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
			Bindings[2].stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;
			Bindings[2].pImmutableSamplers = NULL;
		}
		VkDescriptorSetLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		Info.bindingCount = (uint32_t)BindingsInversionCount;
		Info.pBindings = Bindings;
		if ((res = vkCreateDescriptorSetLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorSetLayoutInversion)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateDescriptorSetLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipeline Layouts
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{//layout h0k
		VkDescriptorSetLayout layouts[1] = { pResourceHeader->VkDescriptorSetLayouth0k };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkPipelineLayouth0k)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}
	{//layout twiddlefactors
		VkDescriptorSetLayout layouts[1] = { pResourceHeader->VkDescriptorSetLayoutTwiddleFactors };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkPipelineLayoutTwiddleFactors)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}
	{//layout hkt
		VkDescriptorSetLayout layouts[1] = { pResourceHeader->VkDescriptorSetLayouthkt };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkPipelineLayouthkt)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}
	{//layout butterfly
		VkDescriptorSetLayout layouts[1] = { pResourceHeader->VkDescriptorSetLayoutButterfly };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkPipelineLayoutButterfly)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}
	{//layout inversion
		VkDescriptorSetLayout layouts[1] = { pResourceHeader->VkDescriptorSetLayoutInversion };
		uint32_t layoutsSize = 1;

		VkPushConstantRange PushConstants;
		memset(&PushConstants, 0, sizeof(PushConstants));
		PushConstants.offset = 0;
		PushConstants.size = pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize;
		PushConstants.stageFlags = VK_SHADER_STAGE_COMPUTE_BIT;

		VkPipelineLayoutCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		Info.setLayoutCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pPushConstantRanges = &PushConstants;
		Info.pushConstantRangeCount = 1;
		if ((res = vkCreatePipelineLayout(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkPipelineLayoutInversion)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreatePipelineLayout Failed, VkResult == ", res);
			return (Failure);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pipelines
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{//pipeline h0k
		VkComputePipelineCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pResourceHeader->VkShaderh0k;
		Info.stage.pName = "main";
		Info.layout = pResourceHeader->VkPipelineLayouth0k;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pResourceHeader->VkPipelineh0k)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return (Failure);
		}
	}
	{//pipeline TwiddleFactors
		VkComputePipelineCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pResourceHeader->VkShaderTwiddleFactors;
		Info.stage.pName = "main";
		Info.layout = pResourceHeader->VkPipelineLayoutTwiddleFactors;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pResourceHeader->VkPipelineTwiddleFactors)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return (Failure);
		}
	}
	{//pipeline hkt
		VkComputePipelineCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pResourceHeader->VkShaderhkt;
		Info.stage.pName = "main";
		Info.layout = pResourceHeader->VkPipelineLayouthkt;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pResourceHeader->VkPipelinehkt)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return (Failure);
		}
	}
	{//pipeline Butterfly
		VkComputePipelineCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pResourceHeader->VkShaderButterfly;
		Info.stage.pName = "main";
		Info.layout = pResourceHeader->VkPipelineLayoutButterfly;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pResourceHeader->VkPipelineButterfly)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return (Failure);
		}
	}
	{//pipeline Inversion
		VkComputePipelineCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		Info.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		Info.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
		Info.stage.module = pResourceHeader->VkShaderInversion;
		Info.stage.pName = "main";
		Info.layout = pResourceHeader->VkPipelineLayoutInversion;
		Info.flags = NULL;
		Info.pNext = NULL;
		Info.basePipelineHandle = VK_NULL_HANDLE;
		Info.basePipelineIndex = -1;
		if ((res = vkCreateComputePipelines(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, VK_NULL_HANDLE, 1, &Info, NULL, &pResourceHeader->VkPipelineInversion)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateComputePipelines Failed. VkResult == ", res);
			return (Failure);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Sets
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{//pool
		uint32_t PoolSizesSize = 3;
		VkDescriptorPoolSize PoolSizes[3];

		PoolSizes[0].descriptorCount = 1;
		PoolSizes[0].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

		PoolSizes[1].descriptorCount = 1 + 1 + 4 + 3 + 3;
		PoolSizes[1].type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;

		PoolSizes[2].descriptorCount = 1;
		PoolSizes[2].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;

		VkDescriptorPoolCreateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		Info.maxSets = 5;
		Info.poolSizeCount = PoolSizesSize;
		Info.pPoolSizes = PoolSizes;
		if ((res = vkCreateDescriptorPool(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, NULL, &pResourceHeader->VkDescriptorPoolWater)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkCreateDescriptorPool, VkResult == ", res);
			return (Failure);
		}
	}
	{//sets
		uint32_t layoutsSize = 5;
		VkDescriptorSetLayout layouts[5] = { pResourceHeader->VkDescriptorSetLayouth0k, pResourceHeader->VkDescriptorSetLayoutTwiddleFactors,
		pResourceHeader->VkDescriptorSetLayouthkt, pResourceHeader->VkDescriptorSetLayoutButterfly, pResourceHeader->VkDescriptorSetLayoutInversion };
		VkDescriptorSet sets[5];

		VkDescriptorSetAllocateInfo Info;
		memset(&Info, 0, sizeof(Info));
		Info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		Info.descriptorPool = pResourceHeader->VkDescriptorPoolWater;
		Info.descriptorSetCount = layoutsSize;
		Info.pSetLayouts = layouts;
		Info.pNext = NULL;
		if ((res = vkAllocateDescriptorSets(pGraphicsWindow->pLogicalDevice->VkLogicalDevice, &Info, sets)) != VK_SUCCESS)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "vkAllocateDescriptorSets, VkResult == ", res);
			return (Failure);
		}
		pResourceHeader->VkDescriptorSeth0k = sets[0];
		pResourceHeader->VkDescriptorSetTwiddleFactors = sets[1];
		pResourceHeader->VkDescriptorSethkt = sets[2];
		pResourceHeader->VkDescriptorSetButterfly = sets[3];
		pResourceHeader->VkDescriptorSetInversion = sets[4];
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Updating Descriptor Sets
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	{	
		VkMemoryRequirements requirements;
		requirements.size = AlignNumber(pResourceHeader->WaterResolution * sizeof(int), pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.minStorageBufferOffsetAlignment);
		requirements.alignment = pGraphicsWindow->pLogicalDevice->SrcBuffer.Alignment;
		requirements.memoryTypeBits = NULL;
		pResourceHeader->AllocationBitReversedIndices = Graphics_Ref_GPUmalloc(pGraphicsWindow->pLogicalDevice, requirements, TargetMemory_Src, AllocationType_Linear, ThreadIndex);
		if (pResourceHeader->AllocationBitReversedIndices.SizeBytes == NULL)
		{
			Engine_Ref_FunctionError("ReCreate_WaterRenderHeader()", "Not Enough Space In GPU Memory!", NULL);
			return (Out_Of_Memory_Result | Failure);
		}
		int* targetbits = (int*)((void*)(((uint64_t)pResourceHeader->AllocationBitReversedIndices.Allocater.pArenaAllocater->MappedMemory + pResourceHeader->AllocationBitReversedIndices.Pointer)));
		for (int i = 0; i < pResourceHeader->WaterResolution; i++)
		{
			unsigned char x = reverse((unsigned char)i, 8);
			targetbits[i] = x;
		}
	}

	{//h0k
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Textureh0k.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSeth0k, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		ImageInfo.imageView = pNoise->GPU_Texture.VkImageView;
		ImageInfo.sampler = pNoise->GPU_Texture.VkSampler;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSeth0k, 1, 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, NULL, &ImageInfo);
	}
		
	{//TwiddleFactors
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->TextureTwiddleFactors.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetTwiddleFactors, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorBufferInfo BufferInfo;
		BufferInfo.buffer = pResourceHeader->AllocationBitReversedIndices.Allocater.pArenaAllocater->VkBuffer;
		BufferInfo.offset = pResourceHeader->AllocationBitReversedIndices.Pointer;
		BufferInfo.range = AlignNumber(pResourceHeader->WaterResolution * sizeof(int), pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.minStorageBufferOffsetAlignment);
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetTwiddleFactors, 1, 0, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, &BufferInfo, NULL);
	}

	{//hkt
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Texturehkt_dy.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSethkt, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Texturehkt_dx.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSethkt, 1, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Texturehkt_dz.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSethkt, 2, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Textureh0k.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSethkt, 3, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	}

	{//butterfly
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->TextureTwiddleFactors.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetButterfly, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Texturehkt_dy.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetButterfly, 1, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->TexturePingPong.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetButterfly, 2, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	}

	{//inversion
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pTexture->GPU_Texture.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetInversion, 0, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->Texturehkt_dy.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetInversion, 1, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	} {
		VkDescriptorImageInfo ImageInfo;
		ImageInfo.imageLayout = VK_IMAGE_LAYOUT_GENERAL;
		ImageInfo.imageView = pResourceHeader->TexturePingPong.VkImageView;
		ImageInfo.sampler = NULL;
		Graphics_Ref_Update_Descriptor(pGraphicsWindow->pLogicalDevice, pResourceHeader->VkDescriptorSetInversion, 2, 0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, NULL, &ImageInfo);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Rendering
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
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
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Packers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Pack_WaterRenderHeader(const RHeaderWaterRender* pResourceHeader, RHeaderWaterRender* pCopiedResourceHeader, uint64_t* pBufferPointer, void* pData, uint32_t ThreadIndex)
{
	if (pData != NULL)
	{
		memset(&pCopiedResourceHeader->mutex, 0, sizeof(pCopiedResourceHeader->mutex));

		memset(&pCopiedResourceHeader->AllocationBitReversedIndices, 0, sizeof(pCopiedResourceHeader->AllocationBitReversedIndices));

		memset(&pCopiedResourceHeader->Textureh0k, 0, sizeof(pCopiedResourceHeader->Textureh0k));
		memset(&pCopiedResourceHeader->TextureTwiddleFactors, 0, sizeof(pCopiedResourceHeader->TextureTwiddleFactors));
		memset(&pCopiedResourceHeader->Texturehkt_dy, 0, sizeof(pCopiedResourceHeader->Texturehkt_dy));
		memset(&pCopiedResourceHeader->Texturehkt_dx, 0, sizeof(pCopiedResourceHeader->Texturehkt_dx));
		memset(&pCopiedResourceHeader->Texturehkt_dz, 0, sizeof(pCopiedResourceHeader->Texturehkt_dz));
		memset(&pCopiedResourceHeader->TexturePingPong, 0, sizeof(pCopiedResourceHeader->TexturePingPong));

		memset(&pCopiedResourceHeader->VkShaderh0k, 0, sizeof(pCopiedResourceHeader->VkShaderh0k));
		memset(&pCopiedResourceHeader->VkShaderTwiddleFactors, 0, sizeof(pCopiedResourceHeader->VkShaderTwiddleFactors));
		memset(&pCopiedResourceHeader->VkShaderhkt, 0, sizeof(pCopiedResourceHeader->VkShaderhkt));
		memset(&pCopiedResourceHeader->VkShaderButterfly, 0, sizeof(pCopiedResourceHeader->VkShaderButterfly));
		memset(&pCopiedResourceHeader->VkShaderInversion, 0, sizeof(pCopiedResourceHeader->VkShaderInversion));

		memset(&pCopiedResourceHeader->VkDescriptorSetLayouth0k, 0, sizeof(pCopiedResourceHeader->VkDescriptorSetLayouth0k));
		memset(&pCopiedResourceHeader->VkDescriptorSetLayoutTwiddleFactors, 0, sizeof(pCopiedResourceHeader->VkDescriptorSetLayoutTwiddleFactors));
		memset(&pCopiedResourceHeader->VkDescriptorSetLayouthkt, 0, sizeof(pCopiedResourceHeader->VkDescriptorSetLayouthkt));
		memset(&pCopiedResourceHeader->VkDescriptorSetLayoutButterfly, 0, sizeof(pCopiedResourceHeader->VkDescriptorSetLayoutButterfly));
		memset(&pCopiedResourceHeader->VkDescriptorSetLayoutInversion, 0, sizeof(pCopiedResourceHeader->VkDescriptorSetLayoutInversion));

		memset(&pCopiedResourceHeader->VkPipelineLayouth0k, 0, sizeof(pCopiedResourceHeader->VkPipelineLayouth0k));
		memset(&pCopiedResourceHeader->VkPipelineLayoutTwiddleFactors, 0, sizeof(pCopiedResourceHeader->VkPipelineLayoutTwiddleFactors));
		memset(&pCopiedResourceHeader->VkPipelineLayouthkt, 0, sizeof(pCopiedResourceHeader->VkPipelineLayouthkt));
		memset(&pCopiedResourceHeader->VkPipelineLayoutButterfly, 0, sizeof(pCopiedResourceHeader->VkPipelineLayoutButterfly));
		memset(&pCopiedResourceHeader->VkPipelineLayoutInversion, 0, sizeof(pCopiedResourceHeader->VkPipelineLayoutInversion));

		memset(&pCopiedResourceHeader->VkPipelineh0k, 0, sizeof(pCopiedResourceHeader->VkPipelineh0k));
		memset(&pCopiedResourceHeader->VkPipelineTwiddleFactors, 0, sizeof(pCopiedResourceHeader->VkPipelineTwiddleFactors));
		memset(&pCopiedResourceHeader->VkPipelinehkt, 0, sizeof(pCopiedResourceHeader->VkPipelinehkt));
		memset(&pCopiedResourceHeader->VkPipelineButterfly, 0, sizeof(pCopiedResourceHeader->VkPipelineButterfly));
		memset(&pCopiedResourceHeader->VkPipelineInversion, 0, sizeof(pCopiedResourceHeader->VkPipelineInversion));


		memset(&pCopiedResourceHeader->VkDescriptorPoolWater, 0, sizeof(pCopiedResourceHeader->VkDescriptorPoolWater));

		memset(&pCopiedResourceHeader->VkDescriptorSeth0k, 0, sizeof(pCopiedResourceHeader->VkDescriptorSeth0k));
		memset(&pCopiedResourceHeader->VkDescriptorSetTwiddleFactors, 0, sizeof(pCopiedResourceHeader->VkDescriptorSetTwiddleFactors));
		memset(&pCopiedResourceHeader->VkDescriptorSethkt, 0, sizeof(pCopiedResourceHeader->VkDescriptorSethkt));
		memset(&pCopiedResourceHeader->VkDescriptorSetButterfly, 0, sizeof(pCopiedResourceHeader->VkDescriptorSetButterfly));
		memset(&pCopiedResourceHeader->VkDescriptorSetInversion, 0, sizeof(pCopiedResourceHeader->VkDescriptorSetInversion));
	}
	else
	{
	
	}
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Unpackers
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT UnPack_WaterRenderHeader(const RHeaderWaterRender* pResourceHeader, RHeaderWaterRender* pCopiedResourceHeader, void* pData, uint32_t ThreadIndex)
{
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Constructors
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Create_WaterRenderHeader(RHeaderWaterRender* pResourceHeader, RHeaderWaterRenderCreateInfo* pCreateInfo, uint64_t* pAllocationSize, uint32_t ThreadIndex)
{
	if (pResourceHeader == NULL)
	{

	}
	else
	{
#ifndef NDEBUG
		if (pCreateInfo == NULL)
		{
			Engine_Ref_ArgsError("Create_WaterRenderHeader()", "pCreateInfo == NULLPTR");
			return (Invalid_Parameter | Failure);
		}
#endif
		pResourceHeader->iGraphicsWindow = pCreateInfo->pGraphicsWindow->Header.Allocation;
		pResourceHeader->iTextureTarget = pCreateInfo->pTextureTarget->Header.Allocation;
		pResourceHeader->WaterResolution = pCreateInfo->WaterResolution;
		pResourceHeader->WaterL = pCreateInfo->WaterL;
		pResourceHeader->WaterAmplitude = pCreateInfo->WaterAmplitude;
		pResourceHeader->WaterIntensity = pCreateInfo->WaterIntensity;
		pResourceHeader->Waterl = pCreateInfo->Waterl;

		glm_vec2_copy(pCreateInfo->FlowDirection, pResourceHeader->FlowDirection);

		pResourceHeader->iNoise = pCreateInfo->pNoise->Header.Allocation;

		ReCreate_WaterRenderHeader(pResourceHeader, ThreadIndex);
	}
	*pAllocationSize = sizeof(RHeaderWaterRender);
	return (Success);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Graphics Effects
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawSignature_Water(GraphicsEffectSignature* pSignature, RHeaderGraphicsWindow* pGraphicsWindow, uint32_t FrameIndex, GPU_Allocation* GPU_Buffers, uint64_t* GPU_BufferPointers)
{
	for (size_t i = 0; i < Utils.RHeaderWaterRenderBuffer.Size;)
	{
		RHeaderWaterRender* pResourceHeader = (RHeaderWaterRender*)&Utils.RHeaderWaterRenderBuffer.Buffer[i];
		if (pResourceHeader->Header.AllocationSize != NULL && pResourceHeader->Header.Allocation.Identifier == (uint32_t)GraphicsEffectsHeader_WaterRender)
		{
			RHeaderGraphicsWindow* pGraphicsWindow1 = (RHeaderGraphicsWindow*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iGraphicsWindow);
			if (Object_Ref_Compare_ResourceHeaderAllocation(pGraphicsWindow->Header.Allocation, pGraphicsWindow1->Header.Allocation) == Success)
			{
				Engine_Ref_Lock_Mutex(pResourceHeader->mutex);

				pResourceHeader->Time = ((double)clock() / (double)CLOCKS_PER_SEC);

				RHeaderTexture* pTexture = (RHeaderTexture*)Object_Ref_Get_ResourceHeaderPointer(pResourceHeader->iTextureTarget);
				RHeaderImageSource* pImageSource = (RHeaderImageSource*)Object_Ref_Get_ResourceHeaderPointer(pTexture->iImageSource);

				VkResult res = VK_SUCCESS;

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Rendering
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				uint8_t PingPongIndex = 0;
				{//hkt
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->Texturehkt_dy.VkImage;
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
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->Texturehkt_dx.VkImage;
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
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->Texturehkt_dz.VkImage;
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

					vkCmdBindPipeline(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, pResourceHeader->VkPipelinehkt);

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
					vkCmdPushConstants(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->VkPipelineLayouthkt, VK_SHADER_STAGE_COMPUTE_BIT, 0,
						pGraphicsWindow->pLogicalDevice->pPhysicalDevice->Properties.limits.maxPushConstantsSize, &pushconstantbuffer);

					vkCmdBindDescriptorSets(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
						pResourceHeader->VkPipelineLayouthkt, 0, 1, &pResourceHeader->VkDescriptorSethkt, 0, NULL);
					vkCmdDispatch(pGraphicsWindow->SwapChain.FrameBuffers[FrameIndex].VkRenderCommandBuffer, pResourceHeader->WaterResolution / 16, pResourceHeader->WaterResolution / 16, 1);

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
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->Texturehkt_dx.VkImage;
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
					{
						VkImageMemoryBarrier Barrier;
						Barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
						Barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
						Barrier.image = pResourceHeader->Texturehkt_dz.VkImage;
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
				Engine_Ref_Unlock_Mutex(pResourceHeader->mutex);
			}

			i += pResourceHeader->Header.AllocationSize;
		}
		else
		{
			i++;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXRESULT Update_GraphicsEffects()
{
	return Success;
}

TEXRESULT Initialise_GraphicsEffects()
{
	memset(&Utils, 0, sizeof(Utils));
	memset(&Config, 0, sizeof(Config));

	//Config
	Config.InitialHeadersMax = 512;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Signatures
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.RHeaderWaterRenderSig.Buffer = &Utils.RHeaderWaterRenderBuffer;
	Utils.RHeaderWaterRenderSig.ByteLength = sizeof(RHeaderWaterRender);
	Utils.RHeaderWaterRenderSig.Identifier = (uint32_t)GraphicsEffectsHeader_WaterRender;
	Utils.RHeaderWaterRenderSig.Destructor = (Destroy_ResourceHeaderTemplate*)&Destroy_WaterRenderHeader;
	Utils.RHeaderWaterRenderSig.Constructor = (Create_ResourceHeaderTemplate*)&Create_WaterRenderHeader;
	Utils.RHeaderWaterRenderSig.ReConstructor = (ReCreate_ResourceHeaderTemplate*)&ReCreate_WaterRenderHeader;
	Utils.RHeaderWaterRenderSig.Packer = (Pack_ResourceHeaderTemplate*)&Pack_WaterRenderHeader;
	Utils.RHeaderWaterRenderSig.UnPacker = (UnPack_ResourceHeaderTemplate*)&UnPack_WaterRenderHeader;
	Object_Ref_Create_ResourceHeaderBuffer(&Utils.RHeaderWaterRenderBuffer, Config.InitialHeadersMax);
	Object_Ref_Register_ResourceHeaderSignature(&Utils.RHeaderWaterRenderSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Effects
	///////////////////////////////////////////////////////////////////////////////////////////////

	Utils.WaterSig.Identifier = (uint32_t)GraphicsEffectsEffect_Water;
	//Utils.WaterSig.Constructor = (Create_GraphicsEffectTemplate*)&Create_Water;
	//Utils.WaterSig.ReConstructor = (ReCreate_GraphicsEffectTemplate*)&ReCreate_Water;
	//Utils.WaterSig.Destructor = (Destroy_GraphicsEffectTemplate*)&Destroy_Water;
	//Utils.WaterSig.Packer = (Pack_GraphicsEffectTemplate*)&Pack_Text;
	//Utils.WaterSig.UnPacker = (UnPack_GraphicsEffectTemplate*)&UnPack_Text;
	//Utils.WaterSig.Update = (Update_GraphicsEffectTemplate*)&Update_Text;
	//Utils.WaterSig.UpdateSignature = &UpdateSignature_Water;
	//Utils.WaterSig.Draw = (Draw_GraphicsEffectTemplate*)&Draw_Text;
	Utils.WaterSig.DrawSignature = &DrawSignature_Water;
	Utils.WaterSig.SignatureGPUBuffersSize = 0;
	Graphics_Effects_Ref_Register_GraphicsEffectSignature(&Utils.WaterSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//other
	///////////////////////////////////////////////////////////////////////////////////////////////

	return (Success);
}

TEXRESULT Destroy_GraphicsEffects()
{
	//Engine_Ref_FunctionError("GRAPHICSEFFECTS", "START DESTROYING", 0);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//Signatures
	///////////////////////////////////////////////////////////////////////////////////////////////

	//Object_Ref_Destroy_ResourceHeaderBuffer(&Utils.RHeaderWaterRenderBuffer);
	//Object_Ref_DeRegister_ResourceHeaderSignature(&Utils.RHeaderWaterRenderSig);

	///////////////////////////////////////////////////////////////////////////////////////////////
	//other
	///////////////////////////////////////////////////////////////////////////////////////////////

	//Graphics_Effects_Ref_DeRegister_GraphicsEffectSignature(&Utils.WaterSig);

	//memset(&Utils, 0, sizeof(Utils));
	//memset(&Config, 0, sizeof(Config));

	//Engine_Ref_FunctionError("GRAPHICSEFFECTS", "DESTROYED", 0);
	return Success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Extension Information
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
	Graphics_Initialise_Resources(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, &ReturnInfo->pResources, &ReturnInfo->pResourcesSize);

	//Config
	ConfigParameterExport(&ReturnInfo->ConfigParameters, &ReturnInfo->ConfigParametersSize, (const UTF8*)CopyData((void*)"GraphicsEffects::InitialHeadersMax"), &Config.InitialHeadersMax, 1, sizeof(Config.InitialHeadersMax));

	//Resources
	ResourceExport(&ReturnInfo->pResources, &ReturnInfo->pResourcesSize, (const UTF8*)CopyData((void*)"GraphicsEffects::Utils"), &GraphicsEffectsRes.pUtils, &Utils);

	//Functions
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"GraphicsEffects::Initialise_GraphicsEffects"), &GraphicsEffectsRes.pInitialise_GraphicsEffects, &Initialise_GraphicsEffects, Construct, 10.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"GraphicsEffects::Destroy_GraphicsEffects"), &GraphicsEffectsRes.pDestroy_GraphicsEffects, &Destroy_GraphicsEffects, Destruct, 100.0f, 0, NULL);
	FunctionExport(&ReturnInfo->pFunctions, &ReturnInfo->pFunctionsSize, (const UTF8*)CopyData((void*)"GraphicsEffects::Update_GraphicsEffects"), &GraphicsEffectsRes.pUpdate_GraphicsEffects, &Update_GraphicsEffects, EveryFrame, 10.0f, 0, NULL);
}
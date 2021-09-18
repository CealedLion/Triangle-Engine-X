/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Triangle Engine X Additional Graphics Effects.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#pragma once
#define TEX_GRAPHICSEFFECTS

/*
* Added in 1.0.0
* GraphicsEffects Uses enums from 5000
*/
typedef enum GraphicsEffectsHeaderType{
	GraphicsEffectsHeader_WaterRender = 5000
}GraphicsEffectsHeaderType;
/*
* Added in 1.0.0
* GraphicsEffects Uses enums from 5000
*/
typedef enum GraphicsEffectsEffectsType{
	GraphicsEffectsEffect_Water = 5000
}GraphicsEffectsEffectsType;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//structs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* PushConstants for water shader.
*/ 
typedef struct WaterPushConstants {
	//uvec4
	uint32_t WaterResolution;
	uint32_t PingPongIndex;
	uint32_t ButterflyStage;
	uint32_t ButterflyDirection;
	//uvec4
	uint32_t WaterL;
	//vec4
	float WaterAmplitude;
	float WaterIntensity;
	float Waterl;
	float Time;
	//vec2
	vec2 FlowDirection;
}WaterPushConstants;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ResourceHeaders
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* Renders a water shader heightmap to specified texture using specified noise.
*/
typedef struct RHeaderWaterRenderCreateInfo {
	ResourceHeaderAllocation iGraphicsWindow; //Required
	ResourceHeaderAllocation iTextureTarget; //Required
	ResourceHeaderAllocation iNoise; //Required

	uint32_t WaterResolution; //res 256
	uint32_t WaterL; // = 1000
	float WaterAmplitude; // = 20
	float WaterIntensity; // = 16
	float Waterl; // = 1

	vec2 FlowDirection;

}RHeaderWaterRenderCreateInfo;
typedef struct RHeaderWaterRender {
	ResourceHeaderTEMPLATE Header;

	//custom
	ResourceHeaderAllocation iGraphicsWindow;
	ResourceHeaderAllocation iTextureTarget;
	ResourceHeaderAllocation iNoise;

	uint64_t WaterResolution;
	uint64_t WaterL;
	float WaterAmplitude;
	float WaterIntensity;
	float Waterl;

	double Time;



	vec2 FlowDirection;

	//every reinit
	Mutex mutex;

	GPU_Allocation AllocationBitReversedIndices;
	GPU_Texture Textureh0k;
	GPU_Texture TextureTwiddleFactors;
	GPU_Texture Texturehkt_dy;
	GPU_Texture Texturehkt_dx;
	GPU_Texture Texturehkt_dz;
	GPU_Texture TexturePingPong;

#ifdef TEX_EXPOSE_GRAPHICSEFFECTS
	VkShaderModule VkShaderh0k;
	VkShaderModule VkShaderTwiddleFactors;
	VkShaderModule VkShaderhkt;
	VkShaderModule VkShaderButterfly;
	VkShaderModule VkShaderInversion;

	VkDescriptorSetLayout VkDescriptorSetLayouth0k;
	VkDescriptorSetLayout VkDescriptorSetLayoutTwiddleFactors;
	VkDescriptorSetLayout VkDescriptorSetLayouthkt;
	VkDescriptorSetLayout VkDescriptorSetLayoutButterfly;
	VkDescriptorSetLayout VkDescriptorSetLayoutInversion;

	VkPipelineLayout VkPipelineLayouth0k;
	VkPipelineLayout VkPipelineLayoutTwiddleFactors;
	VkPipelineLayout VkPipelineLayouthkt;
	VkPipelineLayout VkPipelineLayoutButterfly;
	VkPipelineLayout VkPipelineLayoutInversion;

	VkPipeline VkPipelineh0k;
	VkPipeline VkPipelineTwiddleFactors;
	VkPipeline VkPipelinehkt;
	VkPipeline VkPipelineButterfly;
	VkPipeline VkPipelineInversion;

	VkDescriptorPool VkDescriptorPoolWater;
	VkDescriptorSet VkDescriptorSeth0k;
	VkDescriptorSet VkDescriptorSetTwiddleFactors;
	VkDescriptorSet VkDescriptorSethkt;
	VkDescriptorSet VkDescriptorSetButterfly;
	VkDescriptorSet VkDescriptorSetInversion;

#else
	void* VkShaderh0k;
	void* VkShaderTwiddleFactors;
	void* VkShaderhkt;
	void* VkShaderButterfly;
	void* VkShaderInversion;

	void* VkDescriptorSetLayouth0k;
	void* VkDescriptorSetLayoutTwiddleFactors;
	void* VkDescriptorSetLayouthkt;
	void* VkDescriptorSetLayoutButterfly;
	void* VkDescriptorSetLayoutInversion;

	void* VkPipelineLayouth0k;
	void* VkPipelineLayoutTwiddleFactors;
	void* VkPipelineLayouthkt;
	void* VkPipelineLayoutButterfly;
	void* VkPipelineLayoutInversion;

	void* VkPipelineh0k;
	void* VkPipelineTwiddleFactors;
	void* VkPipelinehkt;
	void* VkPipelineButterfly;
	void* VkPipelineInversion;

	void* VkDescriptorPoolWater;
	void* VkDescriptorSeth0k;
	void* VkDescriptorSetTwiddleFactors;
	void* VkDescriptorSethkt;
	void* VkDescriptorSetButterfly;
	void* VkDescriptorSetInversion;

#endif
}RHeaderWaterRender;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Utils
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct GraphicsEffectsUtils {	
	struct {
		uint64_t pad;
	}Config;

	//Signatures
	ResourceHeaderSignature RHeaderWaterRenderSig;
	GraphicsEffectSignature WaterSig;
}GraphicsEffectsUtils;

struct GraphicsEffectsResStruct {
	GraphicsEffectsUtils* pUtils;

	void* pInitialise_GraphicsEffects;
	void* pDestroy_GraphicsEffects;
	void* pUpdate_GraphicsEffects;
}GraphicsEffectsRes;

//Initialise_Resources MUST be called to use the library in your dll
void GraphicsEffects_Initialise_Resources(FunctionInfo*** pExternFunctions, uint64_t* pExternFunctionsSize, ResourceInfo*** pExternResources, uint64_t* pExternResourcesSize) {
	memset(&GraphicsEffectsRes, 0, sizeof(GraphicsEffectsRes));

	ResourceImport(pExternResources, pExternResourcesSize, (const UTF8*)CopyData((void*)"GraphicsEffects::Utils"), &GraphicsEffectsRes.pUtils);

}

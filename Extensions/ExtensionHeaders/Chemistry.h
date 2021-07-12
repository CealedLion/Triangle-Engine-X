#pragma once
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Enums
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
*/
typedef enum ChemistryElementType {
	ChemistryElementType_Hydrogen = 1,
	ChemistryElementType_Helium,
	ChemistryElementType_Lithium,
	ChemistryElementType_Berylium,
	ChemistryElementType_Boron,
	ChemistryElementType_Carbon,
	ChemistryElementType_Nitrogen,
	ChemistryElementType_Oxygen,
	ChemistryElementType_Flouride,
	ChemistryElementType_Neon,
	ChemistryElementType_Sodium,
	ChemistryElementType_Magnesium,
	ChemistryElementType_Aluminium,
	ChemistryElementType_Silicon,
	ChemistryElementType_Phosphorous,
	ChemistryElementType_Sulphur,
	ChemistryElementType_Chlorine,
	ChemistryElementType_Argon,
	ChemistryElementType_Potassium,
	ChemistryElementType_Calcium,
	ChemistryElementType_Scandium,
	ChemistryElementType_Titanium,
	ChemistryElementType_Vanadium,
	ChemistryElementType_Chromium,
	ChemistryElementType_Manganese,
	ChemistryElementType_Iron,
	ChemistryElementType_Cobalt,
	ChemistryElementType_Nickel,
	ChemistryElementType_Copper,
	ChemistryElementType_Zinc,
	ChemistryElementType_Gallium,
	ChemistryElementType_Germanium,
	ChemistryElementType_Arsenic,
	ChemistryElementType_Selenium,
	ChemistryElementType_Bromine,
	ChemistryElementType_Krypton,
	ChemistryElementType_Rubidium,
	ChemistryElementType_Strontium,
	ChemistryElementType_Yttrium,
	ChemistryElementType_Zirconium,
	ChemistryElementType_Niobium,
	ChemistryElementType_Molybdenum,
	ChemistryElementType_Technetium,
	ChemistryElementType_Ruthenium,
	ChemistryElementType_Rhodium,
	ChemistryElementType_Palladium,
	ChemistryElementType_Silver,
	ChemistryElementType_Cadmium,
	ChemistryElementType_Indium,
	ChemistryElementType_Tin,
	ChemistryElementType_Antimony,
	ChemistryElementType_Tellurium,
	ChemistryElementType_Iodine,
	ChemistryElementType_Xenon,
	ChemistryElementType_Cesium,
	ChemistryElementType_Barium,
	ChemistryElementType_Lanthanum,
	ChemistryElementType_Cerium,
	ChemistryElementType_Praseodynium,
	ChemistryElementType_Neodynium,
	ChemistryElementType_Promethium,
	ChemistryElementType_Samarium,
	ChemistryElementType_Europium,
	ChemistryElementType_Gadolinium,
	ChemistryElementType_Terbium,
	ChemistryElementType_Dysprosium,
	ChemistryElementType_Holmium,
	ChemistryElementType_Erbium,
	ChemistryElementType_Thulium,
	ChemistryElementType_Ytterbium,
	ChemistryElementType_Lutetium,
	ChemistryElementType_Hafnium,
	ChemistryElementType_Tantalum,
	ChemistryElementType_Tungsten,
	ChemistryElementType_Rhenium,
	ChemistryElementType_Osmium,
	ChemistryElementType_Iridium,
	ChemistryElementType_Platinium,
	ChemistryElementType_Gold,
	ChemistryElementType_Mercury,
	ChemistryElementType_Thallium,
	ChemistryElementType_Lead,
	ChemistryElementType_Bismuth,
	ChemistryElementType_Polonium,
	ChemistryElementType_Astatine,
	ChemistryElementType_Radon,
	ChemistryElementType_Francium,
	ChemistryElementType_Radium,
	ChemistryElementType_Actinium,
	ChemistryElementType_Thorium,
	ChemistryElementType_Protactinium,
	ChemistryElementType_Uranium,
	ChemistryElementType_Neptunium,
	ChemistryElementType_Plutonium,
	ChemistryElementType_Americium,
	ChemistryElementType_Curium,
	ChemistryElementType_Berkelium,
	ChemistryElementType_Californium,
	ChemistryElementType_Einsteinium,
	ChemistryElementType_Fermium,
	ChemistryElementType_Mendelevium,
	ChemistryElementType_Nobelium,
	ChemistryElementType_Lawrencium,
	ChemistryElementType_Rutherfordium,
	ChemistryElementType_Dubnium,
	ChemistryElementType_Seaborgium,
	ChemistryElementType_Bohrium,
	ChemistryElementType_Hassium,
	ChemistryElementType_Meitnerium,
	ChemistryElementType_Darmstadtium,
	ChemistryElementType_Roentgenium,
	ChemistryElementType_Copernicium,
	ChemistryElementType_Nihonium,
	ChemistryElementType_Flerovium,
	ChemistryElementType_Moscovium,
	ChemistryElementType_Livermorium,
	ChemistryElementType_Tennessine,
	ChemistryElementType_Oganesson,
}ChemistryElementType;
/*
* Added in 1.0.0
*/
const uint8_t ChemistryElementsElectrons[][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0,}, //UNDEFEIND
	{1, 0, 0, 0, 0, 0, 0, 0,}, //ChemistryElementType_Hydrogen
	{2, 0, 0, 0, 0, 0, 0, 0,}, //ChemistryElementType_Helium
	{2, 1, 0, 0, 0, 0, 0, 0,}, //ChemistryElementType_Lithium
	{2, 2, 0, 0, 0, 0, 0, 0,}, //ChemistryElementType_Berylium
	{2, 3, 0, 0, 0, 0, 0, 0,}, //ChemistryElementType_Boron
	{2, 4, 0, 0, 0, 0, 0, 0,}, //ChemistryElementType_Carbon
	{2, 5, 0, 0, 0, 0, 0, 0,}, //ChemistryElementType_Nitrogen
	{2, 6, 0, 0, 0, 0, 0, 0,}, //ChemistryElementType_Oxygen
	{2, 7, 0, 0, 0, 0, 0, 0,}, //ChemistryElementType_Flouride
	{2, 8, 0, 0, 0, 0, 0, 0,}, //ChemistryElementType_Neon
	{2, 8, 1, 0, 0, 0, 0, 0,}, //ChemistryElementType_Sodium
	{2, 8, 2, 0, 0, 0, 0, 0,}, //ChemistryElementType_Magnesium
	{2, 8, 3, 0, 0, 0, 0, 0,}, //ChemistryElementType_Aluminium
	{2, 8, 4, 0, 0, 0, 0, 0,}, //ChemistryElementType_Silicon
	{2, 8, 5, 0, 0, 0, 0, 0,}, //ChemistryElementType_Phosphorous
	{2, 8, 6, 0, 0, 0, 0, 0,}, //ChemistryElementType_Sulphur
	{2, 8, 7, 0, 0, 0, 0, 0,}, //ChemistryElementType_Chlorine
	{2, 8, 8, 0, 0, 0, 0, 0,}, //ChemistryElementType_Argon
	{2, 8, 8, 1, 0, 0, 0, 0,}, //ChemistryElementType_Potassium
	{2, 8, 8, 2, 0, 0, 0, 0,}, //ChemistryElementType_Calcium
	{2, 8, 9, 2, 0, 0, 0, 0,}, //ChemistryElementType_Scandium
	{2, 8, 10, 2, 0, 0, 0, 0,}, //ChemistryElementType_Titanium
	{2, 8, 11, 2, 0, 0, 0, 0,}, //ChemistryElementType_Vanadium
	{2, 8, 13, 1, 0, 0, 0, 0,}, //ChemistryElementType_Chromium
	{2, 8, 13, 2, 0, 0, 0, 0,}, //ChemistryElementType_Manganese
	{2, 8, 14, 2, 0, 0, 0, 0,}, //ChemistryElementType_Iron
	{2, 8, 15, 2, 0, 0, 0, 0,}, //ChemistryElementType_Cobalt
	{2, 8, 16, 2, 0, 0, 0, 0,}, //ChemistryElementType_Nickel
	{2, 8, 18, 1, 0, 0, 0, 0,}, //ChemistryElementType_Copper
	{2, 8, 18, 2, 0, 0, 0, 0,}, //ChemistryElementType_Zinc
	{2, 8, 18, 3, 0, 0, 0, 0,}, //ChemistryElementType_Gallium
	{2, 8, 18, 4, 0, 0, 0, 0,}, //ChemistryElementType_Germanium
	{2, 8, 18, 5, 0, 0, 0, 0,}, //ChemistryElementType_Arsenic
	{2, 8, 18, 6, 0, 0, 0, 0,}, //ChemistryElementType_Selenium
	{2, 8, 18, 7, 0, 0, 0, 0,}, //ChemistryElementType_Bromine
	{2, 8, 18, 8, 0, 0, 0, 0,}, //ChemistryElementType_Krypton
	{2, 8, 18, 8, 1, 0, 0, 0,}, //ChemistryElementType_Rubidium
	{2, 8, 18, 8, 2, 0, 0, 0,}, //ChemistryElementType_Strontium
	{2, 8, 18, 9, 2, 0, 0, 0,}, //ChemistryElementType_Yttrium
	{2, 8, 18, 10, 2, 0, 0, 0,}, //ChemistryElementType_Zirconium
	{2, 8, 18, 12, 1, 0, 0, 0,}, //ChemistryElementType_Niobium
	{2, 8, 18, 13, 1, 0, 0, 0,}, //ChemistryElementType_Molybdenum
	{2, 8, 18, 13, 2, 0, 0, 0,}, //ChemistryElementType_Technetium
	{2, 8, 18, 15, 1, 0, 0, 0,}, //ChemistryElementType_Ruthenium
	{2, 8, 18, 16, 1, 0, 0, 0,}, //ChemistryElementType_Rhodium
	{2, 8, 18, 18, 0, 0, 0, 0,}, //ChemistryElementType_Palladium
	{2, 8, 18, 18, 1, 0, 0, 0,}, //ChemistryElementType_Silver
	{2, 8, 18, 18, 2, 0, 0, 0,}, //ChemistryElementType_Cadmium
	{2, 8, 18, 18, 3, 0, 0, 0,}, //ChemistryElementType_Indium
	{2, 8, 18, 18, 4, 0, 0, 0,}, //ChemistryElementType_Tin
	{2, 8, 18, 18, 5, 0, 0, 0,}, //ChemistryElementType_Antimony
	{2, 8, 18, 18, 6, 0, 0, 0,}, //ChemistryElementType_Tellurium
	{2, 8, 18, 18, 7, 0, 0, 0,}, //ChemistryElementType_Iodine
	{2, 8, 18, 18, 8, 0, 0, 0,}, //ChemistryElementType_Xenon
	{2, 8, 18, 18, 8, 1, 0, 0,}, //ChemistryElementType_Cesium
	{2, 8, 18, 18, 8, 2, 0, 0,}, //ChemistryElementType_Barium
	{2, 8, 18, 18, 9, 2, 0, 0,}, //ChemistryElementType_Lanthanum
	{2, 8, 18, 19, 9, 2, 0, 0,}, //ChemistryElementType_Cerium
	{2, 8, 18, 21, 8, 2, 0, 0,}, //ChemistryElementType_Praseodynium
	{2, 8, 18, 22, 8, 2, 0, 0,}, //ChemistryElementType_Neodynium
	{2, 8, 18, 23, 8, 2, 0, 0,}, //ChemistryElementType_Promethium
	{2, 8, 18, 24, 8, 2, 0, 0,}, //ChemistryElementType_Samarium
	{2, 8, 18, 25, 8, 2, 0, 0,}, //ChemistryElementType_Europium
	{2, 8, 18, 25, 9, 2, 0, 0,}, //ChemistryElementType_Gadolinium
	{2, 8, 18, 27, 8, 2, 0, 0,}, //ChemistryElementType_Terbium
	{2, 8, 18, 28, 8, 2, 0, 0,}, //ChemistryElementType_Dysprosium
	{2, 8, 18, 29, 8, 2, 0, 0,}, //ChemistryElementType_Holmium
	{2, 8, 18, 30, 8, 2, 0, 0,}, //ChemistryElementType_Erbium
	{2, 8, 18, 31, 8, 2, 0, 0,}, //ChemistryElementType_Thulium
	{2, 8, 18, 32, 8, 2, 0, 0,}, //ChemistryElementType_Ytterbium
	{2, 8, 18, 32, 9, 2, 0, 0,}, //ChemistryElementType_Lutetium
	{2, 8, 18, 32, 10, 2, 0, 0,}, //ChemistryElementType_Hafnium
	{2, 8, 18, 32, 11, 2, 0, 0,}, //ChemistryElementType_Tantalum
	{2, 8, 18, 32, 12, 2, 0, 0,}, //ChemistryElementType_Tungsten
	{2, 8, 18, 32, 13, 2, 0, 0,}, //ChemistryElementType_Rhenium
	{2, 8, 18, 32, 14, 2, 0, 0,}, //ChemistryElementType_Osmium
	{2, 8, 18, 32, 15, 2, 0, 0,}, //ChemistryElementType_Iridium
	{2, 8, 18, 32, 17, 1, 0, 0,}, //ChemistryElementType_Platinium
	{2, 8, 18, 32, 18, 1, 0, 0,}, //ChemistryElementType_Gold
	{2, 8, 18, 32, 18, 2, 0, 0,}, //ChemistryElementType_Mercury
	{2, 8, 18, 32, 18, 3, 0, 0,}, //ChemistryElementType_Thallium
	{2, 8, 18, 32, 18, 4, 0, 0,}, //ChemistryElementType_Lead
	{2, 8, 18, 32, 18, 5, 0, 0,}, //ChemistryElementType_Bismuth
	{2, 8, 18, 32, 18, 6, 0, 0,}, //ChemistryElementType_Polonium
	{2, 8, 18, 32, 18, 7, 0, 0,}, //ChemistryElementType_Astatine
	{2, 8, 18, 32, 18, 8, 0, 0,}, //ChemistryElementType_Radon
	{2, 8, 18, 32, 18, 8, 1, 0,}, //ChemistryElementType_Francium
	{2, 8, 18, 32, 18, 8, 2, 0,}, //ChemistryElementType_Radium
	{2, 8, 18, 32, 18, 9, 2, 0,}, //ChemistryElementType_Actinium
	{2, 8, 18, 32, 18, 10, 2, 0,}, //ChemistryElementType_Thorium
	{2, 8, 18, 32, 20, 9, 2, 0,}, //ChemistryElementType_Protactinium
	{2, 8, 18, 32, 21, 9, 2, 0,}, //ChemistryElementType_Uranium
	{2, 8, 18, 32, 22, 9, 2, 0,}, //ChemistryElementType_Neptunium
	{2, 8, 18, 32, 24, 8, 2, 0,}, //ChemistryElementType_Plutonium
	{2, 8, 18, 32, 25, 8, 2, 0,}, //ChemistryElementType_Americium
	{2, 8, 18, 32, 25, 9, 2, 0,}, //ChemistryElementType_Curium
	{2, 8, 18, 32, 27, 8, 2, 0,}, //ChemistryElementType_Berkelium
	{2, 8, 18, 32, 28, 8, 2, 0,}, //ChemistryElementType_Californium
	{2, 8, 18, 32, 29, 8, 2, 0,}, //ChemistryElementType_Einsteinium
	{2, 8, 18, 32, 30, 8, 2, 0,}, //ChemistryElementType_Fermium
	{2, 8, 18, 32, 31, 8, 2, 0,}, //ChemistryElementType_Mendelevium
	{2, 8, 18, 32, 32, 8, 2, 0,}, //ChemistryElementType_Nobelium
	{2, 8, 18, 32, 32, 8, 2, 0,}, //ChemistryElementType_Lawrencium
	{2, 8, 18, 32, 32, 10, 2, 0,}, //ChemistryElementType_Rutherfordium
	{2, 8, 18, 32, 32, 11, 2, 0,}, //ChemistryElementType_Dubnium
	{2, 8, 18, 32, 32, 12, 2, 0,}, //ChemistryElementType_Seaborgium
	{2, 8, 18, 32, 32, 13, 2, 0,}, //ChemistryElementType_Bohrium
	{2, 8, 18, 32, 32, 14, 2, 0,}, //ChemistryElementType_Hassium
	{2, 8, 18, 32, 32, 15, 2, 0,}, //ChemistryElementType_Meitnerium
	{2, 8, 18, 32, 32, 16, 2, 0,}, //ChemistryElementType_Darmstadtium
	{2, 8, 18, 32, 32, 17, 2, 0,}, //ChemistryElementType_Roentgenium
	{2, 8, 18, 32, 32, 18, 2, 0,}, //ChemistryElementType_Copernicium
	{2, 8, 18, 32, 32, 18, 3, 0,}, //ChemistryElementType_Nihonium
	{2, 8, 18, 32, 32, 18, 4, 0,}, //ChemistryElementType_Flerovium
	{2, 8, 18, 32, 32, 18, 5, 0,}, //ChemistryElementType_Moscovium
	{2, 8, 18, 32, 32, 18, 6, 0,}, //ChemistryElementType_Livermorium
	{2, 8, 18, 32, 32, 18, 7, 0,}, //ChemistryElementType_Tennessine
	{2, 8, 18, 32, 32, 18, 8, 0,}, //ChemistryElementType_Oganesson
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Structs
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
* The fundamental unit of nature.
*/
typedef struct GPU_Particle {
	vec4 Position;
	vec4 PositionVelocity;

	//int Info0[2][2][2];
	//int level;
}GPU_Particle;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Utils
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Added in 1.0.0
*/
typedef enum ChemistryEffectsType {
	ChemistryEffects_SimpleModel = 1000000,
	ChemistryEffects_FullModel = 1000001,
	ChemistryEffects_Fundamental = 1000002,
}ChemistryEffectsType;
/*
* Added in 1.0.0
*/
typedef struct PushConstantsSimpleModel {
	mat4 VP;
	vec3 Position;
}PushConstantsSimpleModel;
/*
* Added in 1.0.0
*/
typedef struct PushConstantsFullModel {
	mat4 Rotation;
	vec4 Position;
	int ResolutionX;
	int ResolutionY;
	int PingPongIndex;
	float FieldOfView;
}PushConstantsFullModel;
/*
* Added in 1.0.0
*/
typedef struct PushConstantsComputeFullModel {
	int32_t PingPongIndex;
	float Time;
}PushConstantsComputeFullModel;
/*
* Added in 1.0.0
*/
typedef struct PushConstantsFundamental {
	mat4 VP;
}PushConstantsFundamental;
/*
* Added in 1.0.0
*/
typedef struct PushConstantsComputeFundamental {
	int Part;
	int Particles;
	float ChunkSize;
	int Resolution;
}PushConstantsComputeFundamental;
/*
* Added in 1.0.0
* Renders Simplified Molecular Simulation Effect.
*/
typedef struct ChemistryEffectCreateInfoSimpleModel {
	uint32_t pad;
}ChemistryEffectCreateInfoSimpleModel;
typedef struct ChemistryEffectSimpleModel {
	GraphicsEffectTemplate Header;

}ChemistryEffectSimpleModel;
/*
* Added in 1.0.0
*/
typedef struct ChemistryEffectCreateInfoFullModel {

	uint32_t SimulationResolution;

	uint64_t ParticlesSize;
	GPU_Particle* Particles;
}ChemistryEffectCreateInfoFullModel;
typedef struct ChemistryEffectFullModel {
	GraphicsEffectTemplate Header;

	uint32_t SimulationResolution;

	uint64_t ParticlesSize;
	GPU_Particle* Particles;

	//every reinit
	int32_t PingPongIndex;

	Mutex mutex;

	GPU_Allocation AllocationParticles;

#ifdef TEX_EXPOSE_GRAPHICS
	VkPipeline VkPipelineComputeSource;
	VkShaderModule VkShaderComputeSource;

	VkPipeline VkPipelineComputeField;
	VkShaderModule VkShaderComputeField;



	VkPipelineLayout VkPipelineLayout;
	VkDescriptorSetLayout VkDescriptorSetLayout;
	VkDescriptorSet* VkDescriptorSets;
	VkDescriptorPool VkDescriptorPool;
#else
	void* VkPipelineComputeSource;
	void* VkShaderComputeSource;

	void* VkPipelineComputeField;
	void* VkShaderComputeField;

	void* VkPipelineLayout;
	void* VkDescriptorSetLayout;
	void** VkDescriptorSets;
	void* VkDescriptorPool;
#endif

#ifdef TEX_EXPOSE_GRAPHICS
	VkPipeline VkPipeline;
	VkShaderModule VkShaderVertex;
	VkShaderModule VkShaderFragment;
#else
	void* VkPipeline;
	void* VkShaderVertex;
	void* VkShaderFragment;
#endif
}ChemistryEffectFullModel;
/*
* Added in 1.0.0
*/
typedef struct ChemistryEffectCreateInfoFundamental {
	uint64_t ParticlesSize;
	GPU_Particle* Particles;

	float ChunkSize;
	uint64_t Resolution;
}ChemistryEffectCreateInfoFundamental;
typedef struct ChemistryEffectFundamental {
	GraphicsEffectTemplate Header;

	uint64_t ParticlesSize;
	GPU_Particle* Particles;

	uint64_t Resolution;

	//every reinit
	Mutex mutex;

	GPU_Allocation AllocationParticles0;
	GPU_Allocation AllocationParticles1;

#ifdef TEX_EXPOSE_GRAPHICS
	VkPipeline VkPipelineCompute;
	VkShaderModule VkShaderCompute;

	VkPipelineLayout VkPipelineLayout;
	VkDescriptorSetLayout VkDescriptorSetLayout;
	VkDescriptorSet VkDescriptorSet;
	VkDescriptorPool VkDescriptorPool;
#else
	void* VkPipelineCompute;
	void* VkShaderCompute;

	void* VkPipelineLayout;
	void* VkDescriptorSetLayout;
	void* VkDescriptorSet;
	void* VkDescriptorPool;
#endif

#ifdef TEX_EXPOSE_GRAPHICS
	VkPipeline VkPipeline;
	VkShaderModule VkShaderVertex;
	VkShaderModule VkShaderFragment;
#else
	void* VkPipeline;
	void* VkShaderVertex;
	void* VkShaderFragment;
#endif
}ChemistryEffectFundamental;



#ifdef TEX_EXPOSE_CHEMISTRY
#define ChemistrySimpleModelBuffersCount 1

#define ChemistryFullModelBuffersCount 1
#define ChemistryFullModelImagesCount 2

#define ChemistryFundamentalBuffersCount 2
#define ChemistryFundamentalImagesCount 2

typedef struct ChemistryUtils{
	GraphicsEffectSignature SimpleModelSignature;
	GraphicsEffectSignature FullModelSignature;
	GraphicsEffectSignature FundamentalSignature;
}ChemistryUtils;
#endif

struct ChemistryResStruct{
	void* pUtils;
	void* pInitialise_Chemistry;
	void* pDestroy_Chemistry;
	void* pUpdate_Chemistry;
}ChemistryRes;

//Initialise_Resources MUST be called to use the library in your dll
void Chemistry_Initialise_Resources(FunctionInfo*** pExternFunctions, uint64_t* pExternFunctionsSize, ResourceInfo*** pExternResources, uint64_t* pExternResourcesSize)
{
	memset(&ChemistryRes, 0, sizeof(ChemistryRes));
}






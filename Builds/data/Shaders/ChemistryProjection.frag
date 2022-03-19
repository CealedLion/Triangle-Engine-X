#version 450
#extension GL_KHR_vulkan_glsl : enable

struct Particle {	
	vec4 Position;
	vec4 PositionVelocity;
	vec4 Magnitude;
	vec4 Acceleration;
	//int Info0[2][2][2];
	//int level;
};


layout(std430, set = 0, binding = 0) buffer ParticlesBuffer0 {
	Particle ParticlesS[];
}Particles0;
layout(std430, set = 0, binding = 1) buffer ParticlesBuffer1 {
	Particle ParticlesS[];
}Particles1;

layout (set = 0, binding = 2, r32f) uniform image3D Result0;
layout (set = 0, binding = 3, r32f) uniform image3D Result1;


layout(push_constant) uniform PushConstantsFullModel {
	mat4 Rotation;
	vec4 Position;
	int ResolutionX;
	int ResolutionY;
	int PingPongIndex;
	float FieldOfView;
}PushConstants;

layout(location = 0) out vec4 OutAlbedoOrTransperancy;
layout(location = 1) out vec4 OutPositionOrRevealage;

void main(void)
{
	mat3 finalrot = mat3(PushConstants.Rotation);
	vec2 FragCoord = vec2(-(gl_FragCoord.x - (1024 / 2)), (gl_FragCoord.y - (1024 / 2)));	
	vec3 FragCoordOffset = vec3((FragCoord.xy / 1024), 1); // / (6.28318 / (1 /*1 radian*/)
	vec3 OffsetFactor = finalrot * FragCoordOffset;	
	vec3 ray = finalrot * vec3(PushConstants.Position.x, -PushConstants.Position.y, PushConstants.Position.z);
	float Res0 = 0;	
	float Res1 = 0;	
	if (PushConstants.PingPongIndex == 0)
	{
		for(int i = 0; i < 1000; ++i) //count
		{ 
			vec4 Data = imageLoad(Result1, ivec3(round(ray.x), round(ray.y), round(ray.z)));
			float sample0 = distance(Data.xyz, vec3(0)) * 1.0;
			Res0 += sample0 * clamp(Data.w, 0, 1);
			Res1 += sample0 * (-clamp(Data.w, 0, 1) + 1);
			ray += OffsetFactor;
		}
	}
	else
	{
		for(int i = 0; i < 1000; ++i) //count
		{ 
			vec4 Data = imageLoad(Result0, ivec3(round(ray.x), round(ray.y), round(ray.z)));
			float sample0 = distance(Data.xyz, vec3(0)) * 1.0;
			Res0 += sample0 * clamp(Data.w, 0, 1);
			Res1 += sample0 * (-clamp(Data.w, 0, 1) + 1);
			ray += OffsetFactor;
		}
	}
	OutAlbedoOrTransperancy = vec4(Res0, 0, Res1, Res0 + Res1);
	//OutAlbedoOrTransperancy = vec4(Res0, 0, Res1, Res0 + Res1);
}
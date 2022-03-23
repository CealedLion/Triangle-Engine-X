#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 PositionVelocity;
layout(location = 2) in vec4 Magnitude;
layout(location = 3) in vec4 Acceleration;

layout(location = 0) out vec4 AlbedoOrTransperancy;
layout(location = 1) out vec4 RevealageOrPosition;


layout (set = 0, binding = 2, r32f) uniform image3D Field0;
layout (set = 0, binding = 3, r32f) uniform image3D Field1;


layout(push_constant) uniform PushConstantsFundamental {
	mat4 VP;
	int Particles;
	int SimulationResolution;
}PushConstants;

void main(void)
{
	//vec4 Data1 = imageLoad(Field1, ivec3(0));
	//AlbedoOrTransperancy = vec4(0, 0.5, 0, 1);


	AlbedoOrTransperancy = vec4(PositionVelocity.w + Acceleration.w, 0 + Acceleration.w, (-PositionVelocity.w + 1) + Acceleration.w, 1);
	//AlbedoOrTransperancy = vec4((Magnitude.x + 1) / 2, (Magnitude.y + 1) / 2, (Magnitude.z + 1) / 2, 1);
}
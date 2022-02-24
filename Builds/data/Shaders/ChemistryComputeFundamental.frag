#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 PositionVelocity;
layout(location = 2) in vec4 Magnitude;
layout(location = 3) in vec4 Acceleration;

layout(location = 0) out vec4 AlbedoOrTransperancy;
layout(location = 1) out vec4 RevealageOrPosition;



layout(push_constant) uniform PushConstantsFundamental {
	mat4 VP;
}PushConstants;

void main(void)
{
	//AlbedoOrTransperancy = vec4(distance(PositionVelocity.xyz, vec3(0)) * Position.w, 0, distance(PositionVelocity.xyz, vec3(0)) * (-Position.w + 1), 1);
	AlbedoOrTransperancy = vec4((Magnitude.x + 1) / 2, (Magnitude.y + 1) / 2, (Magnitude.z + 1) / 2, 1);
}
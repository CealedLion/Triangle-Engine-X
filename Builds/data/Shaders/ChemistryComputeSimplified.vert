#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 PositionVelocity;
layout(location = 2) in vec4 Magnitude;
layout(location = 3) in vec4 Acceleration;

layout(location = 0) out vec4 outPosition;
layout(location = 1) out vec4 outPositionVelocity;
layout(location = 2) out vec4 outMagnitude;
layout(location = 3) out vec4 outAcceleration;

struct Particle {	
	vec4 Position;
	vec4 PositionVelocity;
	vec4 Magnitude;

	//int Info0[2][2][2];
	//int level;
};

layout(std430, set = 0, binding = 0) buffer ParticlesBuffer0 {
	Particle ParticlesS[];
}Particles0;
layout(std430, set = 0, binding = 1) buffer ParticlesBuffer1 {
	Particle ParticlesS[];
}Particles1;

layout(push_constant) uniform PushConstantsFundamental {
	mat4 VP;
}PushConstants;

vec3 arr[42] = {
vec3(0.000000, -1.000000, 0.000000),vec3(0.723607, -0.447220, 0.525725),vec3(-0.276388, -0.447220, 0.850649),vec3(-0.894426, -0.447216, 0.000000),vec3(-0.276388, -0.447220, -0.850649),vec3(0.723607, -0.447220, -0.525725),
vec3(0.276388, 0.447220, 0.850649),vec3(-0.723607, 0.447220, 0.525725),vec3(-0.723607, 0.447220, -0.525725),vec3(0.276388, 0.447220, -0.850649),vec3(0.894426, 0.447216, 0.000000),vec3(0.000000, 1.000000, 0.000000),
vec3(-0.162456, -0.850654, 0.499995),vec3(0.425323, -0.850654, 0.309011),vec3(0.262869, -0.525738, 0.809012),vec3(0.850648, -0.525736, 0.000000),vec3(0.425323, -0.850654, -0.309011),vec3(-0.525730, -0.850652, 0.000000),
vec3(-0.688189, -0.525736, 0.499997),vec3(-0.162456, -0.850654, -0.499995),vec3(-0.688189, -0.525736, -0.499997),vec3(0.262869, -0.525738, -0.809012),vec3(0.951058, 0.000000, 0.309013),vec3(0.951058, 0.000000, -0.309013),
vec3(0.000000, 0.000000, 1.000000),vec3(0.587786, 0.000000, 0.809017),vec3(-0.951058, 0.000000, 0.309013),vec3(-0.587786, 0.000000, 0.809017),vec3(-0.587786, 0.000000, -0.809017),vec3(-0.951058, 0.000000, -0.309013),
vec3(0.587786, 0.000000, -0.809017),vec3(0.000000, 0.000000, -1.000000),vec3(0.688189, 0.525736, 0.499997),vec3(-0.262869, 0.525738, 0.809012),vec3(-0.850648, 0.525736, 0.000000),vec3(-0.262869, 0.525738, -0.809012),
vec3(0.688189, 0.525736, -0.499997),vec3(0.162456, 0.850654, 0.499995),vec3(0.525730, 0.850652, 0.000000),vec3(-0.425323, 0.850654, 0.309011),vec3(-0.425323, 0.850654, -0.309011),vec3(0.162456, 0.850654, -0.499995)
};


int indices[240] = {
1, 14, 13,
2, 14, 16,
1, 13, 18,
1, 18, 20,
1, 20, 17,
2, 16, 23,
3, 15, 25,
4, 19, 27,
5, 21, 29,
6, 22, 31,
2, 23, 26,
3, 25, 28,
4, 27, 30,
5, 29, 32,
6, 31, 24,
7, 33, 38,
8, 34, 40,
9, 35, 41,
10, 36, 42,
11, 37, 39,
39, 42, 12,
39, 37, 42,
37, 10, 42,
42, 41, 12,
42, 36, 41,
36, 9, 41,
41, 40, 12,
41, 35, 40,
35, 8, 40,
40, 38, 12,
40, 34, 38,
34, 7, 38,
38, 39, 12,
38, 33, 39,
33, 11, 39,
24, 37, 11,
24, 31, 37,
31, 10, 37,
32, 36, 10,
32, 29, 36,
29, 9, 36,
30, 35, 9,
30, 27, 35,
27, 8, 35,
28, 34, 8,
28, 25, 34,
25, 7, 34,
26, 33, 7,
26, 23, 33,
23, 11, 33,
31, 32, 10,
31, 22, 32,
22, 5, 32,
29, 30, 9,
29, 21, 30,
21, 4, 30,
27, 28, 8,
27, 19, 28,
19, 3, 28,
25, 26, 7,
25, 15, 26,
15, 2, 26,
23, 24, 11,
23, 16, 24,
16, 6, 24,
17, 22, 6,
17, 20, 22,
20, 5, 22,
20, 21, 5,
20, 18, 21,
18, 4, 21,
18, 19, 4,
18, 13, 19,
13, 3, 19,
16, 17, 6,
16, 14, 17,
14, 1, 17,
13, 15, 3,
13, 14, 15,
14, 2, 15
};



void main(void)
{
	outPosition = Position;
	outPositionVelocity = PositionVelocity;
	outMagnitude = Magnitude;
	outAcceleration = Acceleration;

	if (gl_VertexIndex == 0)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz, 1.0f));
	}	
	else if (gl_VertexIndex == 1)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz + (PositionVelocity.xyz * 0.05), 1.0f));
	}	
	else if (gl_VertexIndex == 2)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz, 1.0f));
	}
	else if (gl_VertexIndex == 3)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz + (Magnitude.xyz * 0.05f), 1.0f));
	}
}
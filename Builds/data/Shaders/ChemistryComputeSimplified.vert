#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 PositionVelocity;
layout(location = 2) in vec4 Magnitude;

layout(location = 0) out vec4 outPosition;
layout(location = 1) out vec4 outPositionVelocity;
layout(location = 2) out vec4 outMagnitude;

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

void main(void)
{
	outPosition = Position;
	outPositionVelocity = PositionVelocity;
	outMagnitude = Magnitude;

	if (gl_VertexIndex == 0)
	{
		gl_Position = PushConstants.VP * vec4(Position.xyz, 1.0f);
	}
	else if (gl_VertexIndex == 1)
	{
		gl_Position = PushConstants.VP * vec4(Position.xyz + PositionVelocity.xyz, 1.0f);
	}

	else if (gl_VertexIndex == 2)
	{
		gl_Position = PushConstants.VP * vec4(Position.xyz + PositionVelocity.xyz, 1.0f);
	}
	else if (gl_VertexIndex == 3)
	{
		gl_Position = PushConstants.VP * vec4(Position.xyz + (PositionVelocity.xyz * 0.9) + ((vec3(-PositionVelocity.z, PositionVelocity.x, -PositionVelocity.y)) * 0.1), 1.0f);
	}
	else if (gl_VertexIndex == 4)
	{
		gl_Position = PushConstants.VP * vec4(Position.xyz + PositionVelocity.xyz, 1.0f);
	}
	else if (gl_VertexIndex == 5)
	{
		gl_Position = PushConstants.VP * vec4(Position.xyz + (PositionVelocity.xyz * 0.9) + ((vec3(PositionVelocity.z, -PositionVelocity.x, PositionVelocity.y)) * 0.1), 1.0f);
	}	
	else if (gl_VertexIndex == 6)
	{
		gl_Position = PushConstants.VP *  vec4(Position.xyz, 1.0f);
	}
	else if (gl_VertexIndex == 7)
	{
		gl_Position = PushConstants.VP * vec4(Position.xyz + Magnitude.xyz, 1.0f);
	}
}
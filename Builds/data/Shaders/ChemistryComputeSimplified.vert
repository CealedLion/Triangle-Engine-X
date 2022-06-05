#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 PositionVelocity;
layout(location = 2) in vec4 Magnitude;
layout(location = 3) in vec4 MagnitudeVelocity;
layout(location = 4) in vec4 Acceleration;

layout(location = 0) out vec4 outPosition;
layout(location = 1) out vec4 outPositionVelocity;
layout(location = 2) out vec4 outMagnitude;
layout(location = 3) out vec4 outMagnitudeVelocity;
layout(location = 4) out vec4 outAcceleration;

struct Particle {	
	vec4 Position;
	vec4 PositionVelocity;
	vec4 Magnitude;
	vec4 MagnitudeVelocity;
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

layout(push_constant) uniform PushConstantsFundamental {
	mat4 VP;
	int Particles;
}PushConstants;

void main(void)
{
	outPosition = Position;
	outPositionVelocity = PositionVelocity;
	outMagnitude = Magnitude;
	outMagnitudeVelocity = MagnitudeVelocity;
	outAcceleration = Acceleration;



	/*
	if (gl_InstanceIndex < PushConstants.Particles)
	{
	if (gl_VertexIndex == 0)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz, 1.0f));
	}	
	else if (gl_VertexIndex == 1)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz + (PositionVelocity.xyz * 0.15), 1.0f));
	}	
	else if (gl_VertexIndex == 2)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz, 1.0f));
	}
	else if (gl_VertexIndex == 3)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz + (Magnitude.xyz * 0.15f), 1.0f));
	}
	}
	else
	{
	if (gl_VertexIndex == 0)
	{
		gl_Position = (PushConstants.VP * vec4((vec3(invoc - (PushConstants.SimulationResolution / 2)) * 0.033), 1.0f));
	}	
	else if (gl_VertexIndex == 1)
	{
		gl_Position = (PushConstants.VP * vec4((vec3(invoc - (PushConstants.SimulationResolution / 2)) * 0.033) + (direction.xyz * 0.05), 1.0f));
	}	
	else if (gl_VertexIndex == 2)
	{
		gl_Position = (PushConstants.VP * vec4((vec3(invoc - (PushConstants.SimulationResolution / 2)) * 0.033), 1.0f));
	}
	else if (gl_VertexIndex == 3)
	{
		gl_Position = (PushConstants.VP * vec4((vec3(invoc - (PushConstants.SimulationResolution / 2)) * 0.033) + (direction.xyz * 0.05f), 1.0f));
	}
	}
	*/
	if (gl_VertexIndex == 0)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz, 1.0f));
	}	
	else if (gl_VertexIndex == 1)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz + (PositionVelocity.xyz * 0.15), 1.0f));
	}	
	else if (gl_VertexIndex == 2)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz, 1.0f));
	}
	else if (gl_VertexIndex == 3)
	{
		gl_Position = (PushConstants.VP * vec4(Position.xyz + (Magnitude.xyz * 0.15f), 1.0f));
	}
}
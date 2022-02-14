#version 450
#extension GL_KHR_vulkan_glsl : enable

layout(push_constant) uniform PushConstantsFullModel {
	mat4 VP;
	int PingPongIndex;
}PushConstants;

layout(location = 0) out int z;
layout(location = 1) out vec2 coords;

void main(void)
{
	vec2 Positions[6] = {
		vec2(1, -1),
		vec2(-1, 1),
		vec2(-1, -1),
		vec2(1, -1),
		vec2(1, 1),
		vec2(-1, 1),
	};

	vec2 Coordinates[6] = {
		vec2(1, 0),
		vec2(0, 1),
		vec2(0, 0),
		vec2(1, 0),
		vec2(1, 1),
		vec2(0, 1),
	};
	z = gl_InstanceIndex;
	coords = Coordinates[gl_VertexIndex];
	gl_Position = vec4(Positions[gl_VertexIndex], -(gl_InstanceIndex * 0.1), 1);

}
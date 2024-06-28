#version 450 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texture_coord;
layout(location = 2) in float a_texture_index;
layout(location = 3) in vec4 a_color;

layout(location = 0) uniform mat4 u_view_projection;

out vec2 v_texture_coord;
out float v_texture_index;
out vec4 v_color;

void main()
{
	v_texture_coord = a_texture_coord;
	v_texture_index = a_texture_index;
	v_color = a_color;

	gl_Position = u_view_projection * vec4(a_position, 1.0);
}

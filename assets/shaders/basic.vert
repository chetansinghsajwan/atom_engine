#version 450

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;
layout(location = 2) in vec2 a_texture_coord;
layout(location = 3) in float a_texture_index;
layout(location = 4) in float a_tiling_factor;

layout(location = 0) uniform mat4 u_view_projection;

out vec4 v_color;
out vec2 v_texture_coord;
out float v_texture_index;
out float v_tiling_factor;

void main()
{
    v_color = a_color;
    v_texture_coord = a_texture_coord;
    v_texture_index = a_texture_index;
    v_tiling_factor = a_tiling_factor;
    gl_Position = u_view_projection * vec4(a_position, 1.0);
}

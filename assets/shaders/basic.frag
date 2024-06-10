#version 450

layout(location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_texture_coord;
in float v_texture_index;
in float v_tiling_factor;

uniform sampler2D u_textures[32];

void main()
{
    color = texture(u_textures[int(v_texture_index)], v_texture_coord * v_tiling_factor) * v_color;
}

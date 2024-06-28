#version 450 core

layout(location = 0) out vec4 o_color;

in vec2 v_texture_coord;
in float v_texture_index;
in vec4 v_color;

layout(location = 1) uniform sampler2D u_textures[32];

float screen_pixel_range()
{
	const float pixel_range = 2.0; // set to distance field's pixel range
	vec2 unit_range = vec2(pixel_range) / vec2(textureSize(u_textures[int(v_texture_index)], 0));
    vec2 screen_texture_size = vec2(1.0) / fwidth(v_texture_coord);
    return max(.5 * dot(unit_range, screen_texture_size), 1.0);
}

float median(float r, float g, float b)
{
    return max(min(r, g), min(max(r, g), b));
}

void main()
{
	vec4 texColor = v_color * texture(u_textures[int(v_texture_index)], v_texture_coord);

	vec3 msd = texture(u_textures[int(v_texture_index)], v_texture_coord).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screen_pixel_distance = screen_pixel_range() * (sd - 0.5);
    float opacity = clamp(screen_pixel_distance + 0.5, 0.0, 1.0);
	if (opacity == 0.0)
		discard;

	vec4 bg_color = vec4(0.0);
	o_color = mix(bg_color, v_color, opacity);
}

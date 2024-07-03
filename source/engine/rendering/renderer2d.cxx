module;
#include "glad/glad.h"

module atom.engine:rendering.renderer2d.impl;

import :rendering.renderer2d;
import atom_core;
import atom_logging;
import :math;
import :colors;
import :logging;
import :rendering.orthographic_camera;
import :rendering.shader_factory;
import :rendering.camera;
import :rendering.sprite;
import :rendering.texture;
import :rendering.texture2d;
import :rendering.frame_buffer;
import :rendering.vertex_array;
import :rendering.texture_factory;
import :rendering.font;
import :opengl;

namespace atom::engine
{
    struct _quad_vertex_data
    {
        f32vec3 position;
        f32vec2 texture_coord;
        f32 texture_index;
        f32 tiling_factor;
        class color color;
    };

    struct _text_vertex_data
    {
        f32vec3 position;
        f32vec2 texture_coord;
        f32 texture_index;
        class color color;
    };

    logging::logger* _logger = nullptr;
    opengl_renderer_api* _renderer_api;
    renderer2d::statistics _stats;

    // texture data
    constexpr u32 _max_texture_slot_count = 32;
    texture2d** _texture_slots;
    u32 _texture_slot_index = 1; // 0 is reserved for white
    texture2d* _white_texture = nullptr;

    // quad data
    constexpr u32 _max_quad_count = 1000;
    constexpr u32 _max_quad_vertex_count = _max_quad_count * 4;
    constexpr u32 _max_quad_index_count = _max_quad_count * 6;
    vertex_array* _quad_vertex_array = nullptr;
    vertex_buffer* _quad_vertex_buffer = nullptr;
    _quad_vertex_data* _quad_vertex_buffer_base = nullptr;
    _quad_vertex_data* _quad_vertex_buffer_ptr = nullptr;
    f32vec4 _quad_vertex_positions[4];
    u32 _quad_index_count = 0;
    shader* _quad_shader = nullptr;

    // text data
    constexpr u32 _max_text_count = 1000;
    constexpr u32 _max_text_vertex_count = _max_text_count * 4;
    constexpr u32 _max_text_index_count = _max_text_count * 6;
    constexpr u32 _max_text_texture_slot_count = 32;
    vertex_array* _text_vertex_array;
    vertex_buffer* _text_vertex_buffer;
    _text_vertex_data* _text_vertex_buffer_base = nullptr;
    _text_vertex_data* _text_vertex_buffer_ptr = nullptr;
    u32 _text_index_count = 0;
    shader* _text_shader;

    // font data
    font* _default_font = nullptr;

    auto renderer2d::initialize() -> void
    {
        _logger = logging::logger_manager::create_logger({ .name = "renderer2d" }).get_value();
        _logger->log_info("initializing renderer2d...");

        _renderer_api = new opengl_renderer_api();

        shader_factory::set_root_path(assets_path);

        string_view font_path =
            "/home/chetan/projects/atom_workspace/atom_engine/assets/fonts/roboto/roboto-bold.ttf";

        _logger->log_info("loading font '{}'.", font_path);

        _default_font = font::load_from_file(font_path).get_value_checked();

        _logger->log_info("loading font done.");

        // setup texture data

        _texture_slots = new texture2d*[_max_texture_slot_count];

        u32 _white_texture_data = 0xffffffff;
        _white_texture = texture_factory::create_from_data(
            memory_view{ &_white_texture_data, sizeof(_white_texture_data) }, texture_format::rgb8,
            u32vec2{ 1, 1 });

        _texture_slots[0] = _white_texture;

        int samplers[_max_texture_slot_count];
        for (usize i = 0; i < _max_texture_slot_count; i++)
            samplers[i] = i;

        // initialize quad rendering

        _quad_vertex_array = vertex_array::create();

        _quad_vertex_buffer =
            vertex_buffer::create_with_size(_max_quad_vertex_count * sizeof(_quad_vertex_data));
        _quad_vertex_buffer->set_layout({
            { shader_data_type::float3, "a_position"      },
            { shader_data_type::float2, "a_texture_coord" },
            { shader_data_type::float1, "a_texture_index" },
            { shader_data_type::float1, "a_tiling_factor" },
            { shader_data_type::float4, "a_color"         },
        });
        _quad_vertex_array->add_vertex_buffer(_quad_vertex_buffer);

        _quad_vertex_buffer_base = new _quad_vertex_data[_max_quad_vertex_count];
        _quad_vertex_buffer_ptr = _quad_vertex_buffer_base;

        u32* quad_indices = new u32[_max_quad_index_count];
        u32 offset = 0;
        for (u32 i = 0; i < _max_quad_index_count; i += 6)
        {
            quad_indices[i + 0] = offset + 0;
            quad_indices[i + 1] = offset + 1;
            quad_indices[i + 2] = offset + 2;

            quad_indices[i + 3] = offset + 2;
            quad_indices[i + 4] = offset + 3;
            quad_indices[i + 5] = offset + 0;

            offset += 4;
        }

        index_buffer* quad_index_buffer = index_buffer::create(quad_indices, _max_quad_index_count);
        _quad_vertex_array->set_index_buffer(quad_index_buffer);
        delete[] quad_indices;

        _quad_shader = shader_factory::create_from_files("shaders/basic").get_value_checked();
        _quad_shader->bind();
        _quad_shader->set_int_array("u_textures", samplers, _max_texture_slot_count);

        _quad_vertex_positions[0] = f32vec4{ -.5f, -.5f, 0, 1 };
        _quad_vertex_positions[1] = f32vec4{ .5f, -.5f, 0, 1 };
        _quad_vertex_positions[2] = f32vec4{ .5f, .5f, 0, 1 };
        _quad_vertex_positions[3] = f32vec4{ -.5f, .5f, 0, 1 };

        // initialize text rendering

        _text_vertex_array = vertex_array::create();
        _text_vertex_buffer =
            vertex_buffer::create_with_size(_max_text_vertex_count * sizeof(_text_vertex_data));
        _text_vertex_buffer->set_layout({
            { shader_data_type::float3, "a_position"      },
            { shader_data_type::float2, "a_texture_coord" },
            { shader_data_type::float1, "a_texture_index" },
            { shader_data_type::float4, "a_color"         },
        });
        _text_vertex_array->add_vertex_buffer(_text_vertex_buffer);
        _text_vertex_array->set_index_buffer(quad_index_buffer);
        _text_vertex_buffer_base = new _text_vertex_data[_max_text_vertex_count];
        _text_vertex_buffer_ptr = _text_vertex_buffer_base;

        _text_shader = shader_factory::create_from_files("shaders/msdf_text").get_value_checked();
        _text_shader->bind();
        _text_shader->set_int_array("u_textures", samplers, _max_texture_slot_count);

        _logger->log_info("initializing renderer2d done.");
    }

    auto renderer2d::finalize() -> void
    {
        _logger->log_info("finalizing renderer2d...");

        _renderer_api->finalize();
        delete _renderer_api;

        delete _quad_vertex_array;
        delete _quad_vertex_buffer;
        delete _quad_vertex_buffer_base;
        delete _quad_shader;

        delete _text_vertex_array;
        delete _text_vertex_buffer;
        delete _text_vertex_buffer_base;
        delete _text_shader;

        delete _texture_slots;

        _logger->log_info("finalizing renderer2d done.");
    }

    auto renderer2d::begin_scene(orthographic_camera* camera) -> void
    {
        _quad_shader->bind();
        _quad_shader->set_uniform_mat4("u_view_projection", camera->get_view_projection_matrix());
        _quad_vertex_buffer_ptr = _quad_vertex_buffer_base;
        _quad_index_count = 0;

        _text_shader->bind();
        _text_shader->set_uniform_mat4("u_view_projection", camera->get_view_projection_matrix());
        _text_vertex_buffer_ptr = _text_vertex_buffer_base;
        _text_index_count = 0;

        _texture_slot_index = 1;
    }

    auto renderer2d::begin_scene(class camera* camera, const f32mat4& transform) -> void
    {
        f32mat4 view_projection = camera->get_projection() * math::inverse(transform);

        _quad_shader->bind();
        _quad_shader->set_uniform_mat4("u_view_projection", view_projection);
        _quad_vertex_buffer_ptr = _quad_vertex_buffer_base;
        _quad_index_count = 0;

        _text_shader->bind();
        _text_shader->set_uniform_mat4("u_view_projection", view_projection);
        _text_vertex_buffer_ptr = _text_vertex_buffer_base;
        _text_index_count = 0;

        _texture_slot_index = 1;
    }

    auto renderer2d::end_scene() -> void
    {
        flush();
    }

    auto renderer2d::flush() -> void
    {
        for (usize i = 0; i < _texture_slot_index; i++)
        {
            opengl_texture2d* gl_texture = reinterpret_cast<opengl_texture2d*>(_texture_slots[i]);
            GLuint renderer_id = gl_texture->get_renderer_id();

            glBindTextureUnit(i, renderer_id);
        }

        if (_quad_index_count > 0)
        {
            u32 quad_vertex_data_size =
                (_quad_vertex_buffer_ptr - _quad_vertex_buffer_base) * sizeof(_quad_vertex_data);

            _quad_vertex_buffer->set_data(_quad_vertex_buffer_base, quad_vertex_data_size);
            _quad_shader->bind();

            _renderer_api->draw_indexed(_quad_vertex_array, _quad_index_count);
            _stats.draw_calls += 1;
        }

        if (_text_index_count > 0)
        {
            u32 text_vertex_data_size =
                (_text_vertex_buffer_ptr - _text_vertex_buffer_base) * sizeof(_text_vertex_data);

            _text_vertex_buffer->set_data(_text_vertex_buffer_base, text_vertex_data_size);
            _text_shader->bind();

            opengl_texture2d* font_atlas =
                reinterpret_cast<opengl_texture2d*>(_default_font->get_atlas());
            GLuint renderer_id = font_atlas->get_renderer_id();
            glBindTextureUnit(2, renderer_id);

            _renderer_api->draw_indexed(_text_vertex_array, _text_index_count);
            _stats.draw_calls += 1;
        }
    }

    auto renderer2d::set_clear_color(const class color& color) -> void
    {
        _renderer_api->set_clear_color(color);
    }

    auto renderer2d::clear_color() -> void
    {
        _renderer_api->clear_color();
    }

    auto renderer2d::draw_text(string_view text, const f32mat4& transform) -> void
    {
        draw_text(text, _default_font, transform, colors::white);
    }

    auto renderer2d::draw_text(string_view text, class font* font, const f32mat4& transform,
        const class color& color) -> void
    {
        const FontMetrics& font_metrics = font->get_metrics();
        texture2d* font_atlas = font->get_atlas();
        u32vec2 font_atlas_size = font_atlas->get_size();

        f64 x = 0.0;
        f64 y = 0.0;
        f64 fs_scale = 1. / (font_metrics.ascenderY - font_metrics.descenderY);
        f32 line_height_offset = 0.0f;
        f32 texture_index = _get_texture_index(font_atlas);

        for (char ch : text)
        {
            if (ch == '\0')
                continue;

            if (ch == '\r')
                continue;

            if (ch == '\n')
            {
                x = 0;
                y -= fs_scale * font_metrics.lineHeight + line_height_offset;
                continue;
            }

            if (ch == '\t')
                ch = ' ';

            auto glyph = font->get_glyph(ch);

            if (glyph == nullptr)
            {
                glyph = font->get_glyph('?');
            }

            contract_asserts(glyph != nullptr);

            double pl, pb, pr, pt;
            glyph->getQuadPlaneBounds(pl, pb, pr, pt);

            f32vec2 quad_min = f32vec2{ (f32)pl, (f32)pb };
            f32vec2 quad_max = f32vec2{ (f32)pr, (f32)pt };
            quad_min *= fs_scale;
            quad_max *= fs_scale;
            quad_min += f32vec2{ x, y };
            quad_max += f32vec2{ x, y };

            double al, ab, ar, at;
            glyph->getQuadAtlasBounds(al, ab, ar, at);

            const f32 texel_width = 1.0f / font_atlas_size.x;
            const f32 texel_height = 1.0f / font_atlas_size.y;

            f32vec2 texture_coord_min{ (f32)al, (f32)ab };
            f32vec2 texture_coord_max{ (f32)ar, (f32)at };
            texture_coord_min *= f32vec2{ texel_width, texel_height };
            texture_coord_max *= f32vec2{ texel_width, texel_height };

            _draw_char(ch, transform, color, quad_min, quad_max, texture_coord_min,
                texture_coord_max, texture_index);

            x += fs_scale * glyph->getAdvance();
        }
    }

    auto renderer2d::draw_quad(const f32mat4& transform, const class color& color) -> void
    {
        constexpr f32vec2 texture_coords[4] = {
            f32vec2{ 0, 0 },
            f32vec2{ 1, 0 },
            f32vec2{ 1, 1 },
            f32vec2{ 0, 1 },
        };

        _draw_quad(transform, _white_texture, texture_coords, 1, color);
    }

    auto renderer2d::draw_quad(
        const f32vec3& position, f32vec2 size, f32 rotation, const class color& color) -> void
    {
        constexpr f32vec2 texture_coords[4] = {
            f32vec2{ 0, 0 },
            f32vec2{ 1, 0 },
            f32vec2{ 1, 1 },
            f32vec2{ 0, 1 },
        };

        _draw_quad(position, size, rotation, _white_texture, texture_coords, 1, color);
    }

    auto renderer2d::draw_texture(const f32mat4& transform, texture2d* texture, f32 tiling_factor,
        const class color& tint) -> void
    {
        constexpr f32vec2 texture_coords[4] = {
            f32vec2{ 0, 0 },
            f32vec2{ 1, 0 },
            f32vec2{ 1, 1 },
            f32vec2{ 0, 1 },
        };

        _draw_quad(transform, texture, texture_coords, tiling_factor, tint);
    }

    auto renderer2d::draw_texture(const f32vec3& position, f32vec2 size, f32 rotation,
        texture2d* texture, f32 tiling_factor, const class color& tint) -> void
    {
        constexpr f32vec2 texture_coords[4] = {
            f32vec2{ 0, 0 },
            f32vec2{ 1, 0 },
            f32vec2{ 1, 1 },
            f32vec2{ 0, 1 },
        };

        _draw_quad(position, size, rotation, texture, texture_coords, tiling_factor, tint);
    }

    auto renderer2d::draw_sprite(const f32vec3& position, f32vec2 size, f32 rotation,
        class sprite* sprite, f32 tiling_factor, const class color& tint) -> void
    {
        _draw_quad(position, size, rotation, sprite->get_texture(),
            sprite->get_texture_coords().get_data(), tiling_factor, tint);
    }

    auto renderer2d::draw_sprite(const f32mat4& transform, class sprite* sprite, f32 tiling_factor,
        const class color& tint) -> void
    {
        _draw_quad(transform, sprite->get_texture(), sprite->get_texture_coords().get_data(),
            tiling_factor, tint);
    }

    auto renderer2d::reset_stats() -> void
    {
        _stats = renderer2d::statistics();
    }

    auto renderer2d::get_stats() -> statistics
    {
        return _stats;
    }

    auto renderer2d::on_window_resize(u32vec2 size) -> void
    {
        _renderer_api->set_viewport(0, 0, size.x, size.y);
    }

    auto renderer2d::_draw_quad(const f32mat4& transform, texture2d* texture,
        const f32vec2* texture_coords, f32 tiling_factor, const class color& tint) -> void
    {
        contract_debug_expects(texture != nullptr);

        if (_quad_index_count >= _max_quad_index_count)
        {
            _start_new_batch();
        }

        f32 texture_index = _get_texture_index(texture);

        _quad_vertex_buffer_ptr->position = transform * _quad_vertex_positions[0];
        _quad_vertex_buffer_ptr->color = tint;
        _quad_vertex_buffer_ptr->texture_coord = texture_coords[0];
        _quad_vertex_buffer_ptr->texture_index = texture_index;
        _quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
        _quad_vertex_buffer_ptr++;

        _quad_vertex_buffer_ptr->position = transform * _quad_vertex_positions[1];
        _quad_vertex_buffer_ptr->color = tint;
        _quad_vertex_buffer_ptr->texture_coord = texture_coords[1];
        _quad_vertex_buffer_ptr->texture_index = texture_index;
        _quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
        _quad_vertex_buffer_ptr++;

        _quad_vertex_buffer_ptr->position = transform * _quad_vertex_positions[2];
        _quad_vertex_buffer_ptr->color = tint;
        _quad_vertex_buffer_ptr->texture_coord = texture_coords[2];
        _quad_vertex_buffer_ptr->texture_index = texture_index;
        _quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
        _quad_vertex_buffer_ptr++;

        _quad_vertex_buffer_ptr->position = transform * _quad_vertex_positions[3];
        _quad_vertex_buffer_ptr->color = tint;
        _quad_vertex_buffer_ptr->texture_coord = texture_coords[3];
        _quad_vertex_buffer_ptr->texture_index = texture_index;
        _quad_vertex_buffer_ptr->tiling_factor = tiling_factor;
        _quad_vertex_buffer_ptr++;

        _quad_index_count += 6;

        _stats.quad_count += 1;
    }

    auto renderer2d::_draw_quad(const f32vec3& position, f32vec2 size, f32 rotation,
        texture2d* texture, const f32vec2* texture_coords, f32 tiling_factor,
        const class color& tint) -> void
    {
        contract_debug_expects(texture != nullptr);

        f32mat4 transform = math::translate(f32mat4{ 1 }, position)
                            * math::scale(f32mat4{ 1 }, f32vec3{ size.x, size.y, 1 });

        if (rotation != 0.)
        {
            transform *= math::rotate(f32mat4{ 1 }, math::radians(rotation), f32vec3{ 0, 0, 1 });
        }

        _draw_quad(transform, texture, texture_coords, tiling_factor, tint);
    }

    auto renderer2d::_draw_char(char ch, const f32mat4& transform, const class color& color, f32vec2 quad_min,
        f32vec2 quad_max, f32vec2 texture_coord_min, f32vec2 texture_coord_max,
        f32 texture_index) -> void
    {
        _text_vertex_buffer_ptr->position = transform * vec4(quad_min, 0.0f, 1.0f);
        _text_vertex_buffer_ptr->color = color;
        _text_vertex_buffer_ptr->texture_coord = texture_coord_min;
        _text_vertex_buffer_ptr->texture_index = texture_index;
        _text_vertex_buffer_ptr++;

        _text_vertex_buffer_ptr->position = transform * vec4(quad_min.x, quad_max.y, 0.0f, 1.0f);
        _text_vertex_buffer_ptr->color = color;
        _text_vertex_buffer_ptr->texture_coord = { texture_coord_min.x, texture_coord_max.y };
        _text_vertex_buffer_ptr->texture_index = texture_index;
        _text_vertex_buffer_ptr++;

        _text_vertex_buffer_ptr->position = transform * vec4(quad_max, 0.0f, 1.0f);
        _text_vertex_buffer_ptr->color = color;
        _text_vertex_buffer_ptr->texture_coord = texture_coord_max;
        _text_vertex_buffer_ptr->texture_index = texture_index;
        _text_vertex_buffer_ptr++;

        _text_vertex_buffer_ptr->position = transform * vec4(quad_max.x, quad_min.y, 0.0f, 1.0f);
        _text_vertex_buffer_ptr->color = color;
        _text_vertex_buffer_ptr->texture_coord = { texture_coord_max.x, texture_coord_min.y };
        _text_vertex_buffer_ptr->texture_index = texture_index;
        _text_vertex_buffer_ptr++;

        _text_index_count += 6;
    }

    auto renderer2d::_start_new_batch() -> void
    {
        flush();

        _quad_vertex_buffer_ptr = _quad_vertex_buffer_base;
        _quad_index_count = 0;

        _text_vertex_buffer_ptr = _text_vertex_buffer_base;
        _text_index_count = 0;

        _texture_slot_index = 1;
    }

    auto renderer2d::_get_texture_index(texture2d* texture) -> usize
    {
        for (usize i = 0; i < _texture_slot_index; i++)
        {
            if (_texture_slots[i] == texture)
                return i;
        }

        _texture_slots[_texture_slot_index] = texture;
        return _texture_slot_index++;
    }
}

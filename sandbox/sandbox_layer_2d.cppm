module;
#include "imgui.h"

export module atom.engine.sandbox:layer2d;

import atom.core;
import atom.logging;
import atom.engine;

using namespace atom;

namespace sandbox
{
    export class sandbox_layer_2d: public engine::layer
    {
    public:
        sandbox_layer_2d()
            : layer("sandbox")
        {
            _logger = logging::logger_manager::create_logger({ .name = "sandbox" }).get_value();
        }

        ~sandbox_layer_2d() {}

    public:
        virtual auto on_attach() -> void override
        {
            _logger->log_info("sandbox_layer_2d attached.");

            _window = engine::window_manager::get_windows().get_mut_front();
            _logger->log_info("using window '{}'.", _window->get_name());

            ATOM_DEBUG_ASSERTS(_window != nullptr);

            for (engine::input_device* device : engine::input_manager::get_devices())
            {
                if (device->get_type() == engine::input_device_type::keyboard)
                {
                    _keyboard = reinterpret_cast<engine::keyboard*>(device);
                    _logger->log_info("using keyboard '{}'.", _keyboard->get_name());
                    break;
                }
            }

            ATOM_DEBUG_ASSERTS(_keyboard != nullptr);

            for (engine::input_device* device : engine::input_manager::get_devices())
            {
                if (device->get_type() == engine::input_device_type::mouse)
                {
                    _mouse = reinterpret_cast<engine::mouse*>(device);
                    _logger->log_info("using mouse '{}'.", _mouse->get_name());
                    break;
                }
            }

            ATOM_DEBUG_ASSERTS(_mouse != nullptr);

            _frame_buffer = engine::frame_buffer::create({
                .width = 1280,
                .height = 720,
            });

            _scene = new engine::scene();
            _entity_manager = _scene->get_entity_manager();

            _camera_entity = _entity_manager->create_entity("camera");
            _camera_entity->emplace_component<engine::camera_component>();

            _stairs_entity = _entity_manager->create_entity("stairs");
            _stairs_entity->emplace_component<engine::sprite_component>();

            _barrel_entity = _entity_manager->create_entity("barrel");
            _barrel_entity->emplace_component<engine::sprite_component>();

            _tree_entity = _entity_manager->create_entity("tree");
            _tree_entity->emplace_component<engine::sprite_component>();
        }

        virtual auto on_deattach() -> void override
        {
            delete _camera_entity;
            delete _stairs_entity;
            delete _barrel_entity;
            delete _tree_entity;
            delete _scene;
            delete _frame_buffer;
            delete _logger;
        }

        virtual auto on_update(engine::time_step delta_time) -> void override
        {
            const engine::frame_buffer_specs& specs = _frame_buffer->get_specs();
            if (_screen_size.x > 0.0f && _screen_size.y > 0.0f
                && (specs.width != _screen_size.x || specs.height != _screen_size.y))
            {
                _frame_buffer->resize(_screen_size);
                _scene->on_viewport_resize(_screen_size);
            }

            engine::renderer_2d::reset_stats();

            _frame_buffer->bind();
            engine::render_command::set_clear_color({ 0.1f, 0.1f, 0.1f, 1 });
            engine::render_command::clear_color();

            _scene->on_update(delta_time);

            _frame_buffer->unbind();
        }

        virtual auto on_imgui_render() -> void override
        {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
            ImGui::Begin("viewport");

            ImVec2 imgui_screen_size = ImGui::GetContentRegionAvail();
            _screen_size = engine::vec2{ imgui_screen_size.x, imgui_screen_size.y };

            void* imgui_texture_renderer_id =
                reinterpret_cast<void*>(_frame_buffer->get_color_attachment_renderer_id());
            ImGui::Image(imgui_texture_renderer_id, ImVec2(_screen_size.x, _screen_size.y),
                ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

            ImGui::End();
            ImGui::PopStyleVar();
        }

    private:
        logging::logger* _logger;
        engine::window* _window;
        engine::keyboard* _keyboard;
        engine::mouse* _mouse;

        engine::frame_buffer* _frame_buffer;
        engine::vec2 _screen_size;
        engine::scene* _scene;
        engine::entity_manager* _entity_manager;
        engine::entity* _camera_entity;
        engine::entity* _stairs_entity;
        engine::entity* _barrel_entity;
        engine::entity* _tree_entity;
    };
}

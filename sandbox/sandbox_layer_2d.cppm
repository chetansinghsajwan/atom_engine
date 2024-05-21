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

            contract_debug_asserts(_window != nullptr);

            for (engine::input_device* device : engine::input_manager::get_devices())
            {
                if (device->get_type() == engine::input_device_type::keyboard)
                {
                    _keyboard = reinterpret_cast<engine::keyboard*>(device);
                    _logger->log_info("using keyboard '{}'.", _keyboard->get_name());
                    break;
                }
            }

            contract_debug_asserts(_keyboard != nullptr);

            for (engine::input_device* device : engine::input_manager::get_devices())
            {
                if (device->get_type() == engine::input_device_type::mouse)
                {
                    _mouse = reinterpret_cast<engine::mouse*>(device);
                    _logger->log_info("using mouse '{}'.", _mouse->get_name());
                    break;
                }
            }

            contract_debug_asserts(_mouse != nullptr);

            _frame_buffer = engine::frame_buffer::create({
                .width = 1280,
                .height = 720,
            });

            _scene = new engine::scene();
            _entity_manager = _scene->get_entity_manager();

            _camera_entity = _entity_manager->create_entity("camera");
            _camera_entity->emplace_component<engine::camera_component>();

            _box1_entity = _entity_manager->create_entity("box1");
            _box1_entity->get_component<engine::transform_component>()->set_position({ -2, 1, 0 });
            _box1_entity->emplace_component<engine::sprite_component>()->set_color(engine::colors::green);
            _box1_entity->emplace_component<engine::rigidbody_component>()->set_type(
                engine::rigidbody_component::body_type::dynamic);
            _box1_entity->emplace_component<engine::box_collider2d_component>();

            _box2_entity = _entity_manager->create_entity("box2");
            _box2_entity->get_component<engine::transform_component>()->set_position({ 2.1, 0, 0 });
            _box2_entity->emplace_component<engine::sprite_component>()->set_color(engine::colors::red);
        }

        virtual auto on_deattach() -> void override
        {
            delete _camera_entity;
            delete _box1_entity;
            delete _box2_entity;
            delete _scene;
            delete _frame_buffer;
            delete _logger;
        }

        virtual auto on_update(engine::time_step time) -> void override
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

            _scene->on_update(time);

            _frame_buffer->unbind();
        }

        virtual auto on_imgui_render() -> void override
        {
            engine::ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, engine::ImVec2{ 0, 0 });
            engine::ImGui::Begin("viewport");

            engine::ImVec2 imgui_screen_size = engine::ImGui::GetContentRegionAvail();
            _screen_size = engine::vec2{ imgui_screen_size.x, imgui_screen_size.y };

            void* imgui_texture_renderer_id =
                reinterpret_cast<void*>(_frame_buffer->get_color_attachment_renderer_id());
            engine::ImGui::Image(imgui_texture_renderer_id,
                engine::ImVec2(_screen_size.x, _screen_size.y), engine::ImVec2{ 0, 1 },
                engine::ImVec2{ 1, 0 });

            engine::ImGui::End();
            engine::ImGui::PopStyleVar();
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
        engine::entity* _box1_entity;
        engine::entity* _box2_entity;
    };
}

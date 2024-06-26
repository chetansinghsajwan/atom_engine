export module atom.engine.sandbox:sandbox2d_layer.impl;

import atom.core;
import atom.logging;
import atom.engine;
import :sandbox2d_layer;

using namespace atom;

sandbox2d_layer::sandbox2d_layer()
    : layer{ "sandbox" }
{
    _logger = logging::logger_manager::create_logger({ .name = "sandbox" }).get_value();
}

sandbox2d_layer::~sandbox2d_layer()
{
    delete _cherno_texture;
}

auto sandbox2d_layer::on_attach() -> void
{
    _logger->log_info("sandbox2d_layer attached.");

    _window = engine::window_manager::get_windows() | ranges::get_mut_front();
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

    string_view font_path =
        "/home/chetan/projects/atom-workspace/atom.engine/assets/fonts/roboto/roboto-bold.ttf";
    _logger->log_info("loading font '{}'.", font_path);

    _font = engine::font::load_from_file(font_path).get_value_checked();

    _logger->log_info("loading font done.");

    _cherno_texture = engine::texture_factory::create_from_file(
        "/home/chetan/projects/atom-workspace/atom.engine/assets/textures/cherno.png")
                          .get_value_checked();

    _world = new engine::world{};
    _entity_manager = _world->get_entity_manager();

    _camera_entity = _entity_manager->create_entity("camera");
    _entity_manager->emplace_component<engine::camera_component>(_camera_entity);

    _box1_entity = _entity_manager->create_entity("box1");
    _entity_manager->get_component<engine::transform_component>(_box1_entity)
        ->set_position({ -2, 1, 0 });

    engine::sprite_component* box1_sprite =
        _entity_manager->emplace_component<engine::sprite_component>(_box1_entity);
    box1_sprite->set_texture(_font->get_atlas_texture());
    box1_sprite->set_color(engine::colors::white);

    _entity_manager->emplace_component<engine::rigidbody_component>(_box1_entity)
        ->set_type(engine::rigidbody_component::body_type::dynamic);

    _box2_entity = _entity_manager->create_entity("box2");
    _entity_manager->get_component<engine::transform_component>(_box2_entity)
        ->set_position({ 1, 1, 1 });
    _entity_manager->emplace_component<engine::sprite_component>(_box2_entity)
        ->set_color(engine::colors::red);
    _entity_manager->emplace_component<engine::rigidbody_component>(_box2_entity)
        ->set_type(engine::rigidbody_component::body_type::kinematic);
}

auto sandbox2d_layer::on_deattach() -> void
{
    delete _world;
    delete _logger;
}

auto sandbox2d_layer::on_update(engine::time_step time) -> void
{
    _world->on_update(time);
}

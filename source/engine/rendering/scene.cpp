#include "atom/engine/rendering/scene.h"
#include "engine/rendering/renderer_2d.h"

namespace atom::engine
{
    scene::scene()
    {
        _entity_manager = new entity_manager();
    }

    scene::~scene()
    {
        delete _entity_manager;
    }

    auto scene::on_update(time_step time) -> void
    {
        entt::registry* entt_registry = _entity_manager->get_internal();
        auto group = entt_registry->group<transform_component>(entt::get<sprite_component>);
        for (auto entity : group)
        {
            const auto& [transform, sprite] = group.get<transform_component, sprite_component>(entity);
            renderer_2d::draw_quad(transform.get_matrix(), sprite.get_color());
        }
    }
}

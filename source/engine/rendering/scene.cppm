export module atom.engine:rendering.scene;

import atom.core;
import entt;
import :box2d;
import :ecs;
import :time;
import :math;
import :rendering.renderer_2d;

namespace atom::engine
{
    export class scene
    {
    public:
        scene(entity_manager* manager)
            : _entity_manager{ manager }
        {}

        ~scene() {}

    public:
        auto on_start() -> void {}

        auto on_update(time_step time) -> void
        {
            class camera* camera = nullptr;
            f32mat4 camera_transform;

            auto view =
                _entity_manager->get_internal()->view<transform_component, camera_component>();
            for (auto entity : view)
            {
                auto [transform, camera_comp] =
                    view.get<transform_component, camera_component>(entity);

                camera = &camera_comp.get_camera();
                camera_transform = transform.get_matrix();
                break;
            }

            if (camera != nullptr)
            {
                renderer_2d::begin_scene(camera, camera_transform);

                entt::registry* entt_registry = _entity_manager->get_internal();
                auto group = entt_registry->group<transform_component>(entt::get<sprite_component>);
                for (auto entity : group)
                {
                    const auto& [transform, sprite] =
                        group.get<transform_component, sprite_component>(entity);

                    renderer_2d::draw_quad(transform.get_matrix(), sprite.get_color());
                }

                renderer_2d::end_scene();
            }
        }

        auto on_stop() -> void {}

        auto on_viewport_resize(f32vec2 size) -> void
        {
            _viewport_width = size.x;
            _viewport_height = size.y;

            auto view = _entity_manager->get_internal()->view<camera_component>();
            for (auto entity : view)
            {
                auto& camera_comp = view.get<camera_component>(entity);
                camera_comp.get_camera().set_viewport_size(_viewport_width, _viewport_height);
            }
        }

        auto get_entity_manager() const -> entity_manager*
        {
            return _entity_manager;
        }

    private:
        entity_manager* _entity_manager;
        u32 _viewport_width;
        u32 _viewport_height;
    };
}

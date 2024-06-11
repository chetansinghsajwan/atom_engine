export module atom.engine:ecs.rigidbody_component;

import atom.core;
import :box2d;
import :math;
import :time;
import :ecs.entity;
import :ecs.entity_manager;
import :ecs.entity_component;
import :ecs.transform_component;

namespace atom::engine
{
    export class rigidbody_component: public entity_component
    {
        using base_type = entity_component;
        using this_type = rigidbody_component;

    public:
        enum class body_type : byte
        {
            static_,
            dynamic,
            kinematic
        };

    public:
        rigidbody_component();

        rigidbody_component(const this_type&);
        rigidbody_component& operator=(const this_type&);

        rigidbody_component(this_type&&);
        rigidbody_component& operator=(this_type&&);

        ~rigidbody_component();

    public:
        auto set_type(body_type type) -> void;

        auto get_type() const -> body_type;

        auto set_fixed_rotation(bool flag) -> void;

        auto get_fixed_rotation() const -> bool;

        virtual auto on_attach(class entity* entity) -> void override;

        virtual auto on_update(time_step time) -> void override;

        virtual auto on_deattach() -> void override;

        auto _get_body() -> b2Body*;

    private:
        constexpr auto _convert_atom_rigibody_to_box2d(body_type type) -> b2BodyType;

    private:
        transform_component* _transform_component = nullptr;

        body_type _body_type = body_type::static_;
        bool _fixed_rotation = false;

        b2World* _physics_world = nullptr;
        b2Body* _physics_body = nullptr;
    };
}

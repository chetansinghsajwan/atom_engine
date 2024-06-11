export module atom.engine:ecs;

export import :ecs.system;
export import :ecs.system_manager;
export import :ecs.entity;
export import :ecs.entity_manager;
export import :ecs.entity_component;
export import :ecs.transform_component;
export import :ecs.camera_component;
export import :ecs.sprite_component;
export import :ecs.rigidbody_component;
export import :ecs.box_collider2d_component;

// @todo: remove this once, entt is completely behind the abstraction layer.
//        we need equality operators from this.
export import entt;

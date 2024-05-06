#pragma once
#include "atom/engine/ecs.h"
#include "atom/engine/time.h"

namespace atom::engine
{
    class scene
    {
    public:
        scene();
        ~scene();

    public:
        auto on_update(time_stemp time) -> void;
    
        auto get_entity_manager() const -> entity_manager*
        {
            return _entity_manager;
        }

    public:
        entity_manager* _entity_manager;
    };
}

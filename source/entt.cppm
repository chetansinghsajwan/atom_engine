module;
#include "entt/entt.hpp"

export module entt;

export namespace entt
{
    using entt::entity;
    using entt::get;
    using entt::null;
    using entt::registry;

    using entt::operator==;
    using entt::operator!=;
    using entt::operator<;
    using entt::operator<=;
    using entt::operator>;
    using entt::operator>=;

    namespace internal
    {
        using internal::operator==;
        using internal::operator!=;
        using internal::operator<;
        using internal::operator<=;
        using internal::operator>;
        using internal::operator>=;
    }
}

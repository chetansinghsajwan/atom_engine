#pragma once
#include "atom.core.h"

namespace atom::engine
{
    class event_base
    {
    public:
        event_base()
            : handled(false)
        {}

    public:
        bool handled;
    };

    template <typename event_type>
    class event_listener
    {
    public:
        virtual auto handle(event_type& event) -> void = 0;
    };

    template <typename event_type>
    class event_source
    {
        static_assert(std::derived_from<event_type, event_base>,
            "event_type must be derived from `event_base`.");

    public:
        using listener_type = event_listener<event_type>;

    public:
        event_source()
            : _listeners()
        {}

        ~event_source() {}

    public:
        auto subscribe(listener_type* listener) -> void
        {
            ATOM_DEBUG_EXPECTS(listener != nullptr);

            _listeners.emplace_back(listener);
        }

        auto unsubscribe(listener_type* listener) -> void
        {
            ATOM_DEBUG_EXPECTS(listener != nullptr);

            _listeners.remove_one_find(listener);
        }

        auto dispatch(event_type& event)
        {
            for (listener_type* listener : _listeners)
            {
                listener->handle(event);

                if (event.handled)
                    break;
            }
        }

    private:
        dynamic_array<listener_type*> _listeners;
    };
}

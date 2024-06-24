export module atom.engine:events;

import atom.core;

namespace atom::engine
{
    export class event_base
    {
    public:
        event_base()
            : handled(false)
        {}

    public:
        bool handled;
    };

    export template <typename event_type>
    class event_listener
    {
    public:
        virtual auto on_event(event_type& event) -> void = 0;
    };

    export template <typename event_type>
    class event_source
    {
        static_assert(type_info<event_type>::template is_derived_from<event_base>(),
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
            contract_debug_expects(listener != nullptr);

            _listeners.emplace_back(listener);
        }

        auto unsubscribe(listener_type* listener) -> void
        {
            contract_debug_expects(listener != nullptr);

            _listeners.remove_one_find(listener);
        }

        auto dispatch(event_type& event)
        {
            for (listener_type* listener : _listeners)
            {
                listener->on_event(event);

                if (event.handled)
                    break;
            }
        }

    private:
        dynamic_array<listener_type*> _listeners;
    };
}

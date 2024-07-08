export module atom_engine:inputs.input_manager_impl;

import atom_core;
import :inputs.input_device;

namespace atom::engine
{
    class input_manager_impl
    {
    public:
        input_manager_impl()
            : _devices()
            , _last_id(0)
        {}

        virtual ~input_manager_impl() = default;

    public:
        auto get_devices() const -> array_view<input_device*>
        {
            return _devices;
        }

    protected:
        auto _create_new_id() -> input_device_id
        {
            input_device_id id(_last_id.num);
            _last_id.num++;
            return id;
        }

        auto _add_new_device(input_device* device) -> void
        {
            _devices.emplace_last(device);
        }

    protected:
        dynamic_array<input_device*> _devices;
        input_device_id _last_id;
    };
}

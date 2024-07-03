export module atom_engine:inputs.input_manager;

import atom_core;
import :inputs.input_device;
import :inputs.input_manager_impl;

namespace atom::engine
{
    export class input_manager
    {
    public:
        static auto initialize() -> void;

        static auto finalize() -> void;

        static auto get_devices() -> array_view<input_device*>
        {
            return _impl->get_devices();
        }

    private:
        static inline input_manager_impl* _impl;
    };
}

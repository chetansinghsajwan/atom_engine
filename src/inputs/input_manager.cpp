export module atom.engine:input_manager;
import atom.core;
import :input_manager_impl;
import :glfw_input_manager_impl;

namespace atom::engine
{
    export class input_manager
    {
    public:
        static auto initialize() -> void
        {
            _impl = new glfw_input_manager_impl();
        }

        static auto finalize() -> void
        {
            delete _impl;
        }

    private:
        static inline input_manager_impl* _impl;
    };
}

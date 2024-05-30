export module atom.engine:shaders;

import atom.core;

namespace atom::engine
{
    export enum class shader_stage
    {
        vertex_shader,
        fragment_shader,
        compute_shader,
        geometry_shader,
    };

    export class shader_compilation_error: public error
    {
    public:
        shader_compilation_error(string msg)
            : _msg_buf{ move(msg) }
            , error{}
        {
            error::msg = { _msg_buf.get_data(), _msg_buf.get_count() };
        }

    private:
        string _msg_buf;
    };

    export class shader_compiler
    {
    public:
        static auto initialize() -> void;

        static auto finalize() -> void;

        static auto compile_to_spirv(string_view source,
            shader_stage stage) -> result<dynamic_buffer<>, shader_compilation_error>;
    };
}

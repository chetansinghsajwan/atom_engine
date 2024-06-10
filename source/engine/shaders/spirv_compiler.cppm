export module atom.engine:shaders.spirv_compiler;

import atom.core;
import :shaders.shader_utils;

namespace atom::engine
{
    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
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

    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    export class shader_linking_error: public error
    {
    public:
        shader_linking_error()
            : _msg_buf{}
            , error{}
        {}

        shader_linking_error(string msg)
            : _msg_buf{ move(msg) }
            , error{}
        {
            error::msg = { _msg_buf.get_data(), _msg_buf.get_count() };
        }

    private:
        string _msg_buf;
    };

    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    export using spirv_compilation_result =
        result<dynamic_buffer, shader_compilation_error, shader_linking_error>;

    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    export class spirv_compiler
    {
    public:
        /// ----------------------------------------------------------------------------------------
        /// initializes `spirv_compiler`. this is needed before any other operation.
        /// ----------------------------------------------------------------------------------------
        static auto initialize() -> void;

        /// ----------------------------------------------------------------------------------------
        /// finalizes `spirv_compiler`. `initialize()` must be called again to reuse this class.
        /// ----------------------------------------------------------------------------------------
        static auto finalize() -> void;

        /// ----------------------------------------------------------------------------------------
        /// returns `true` if this class is initialized.
        /// ----------------------------------------------------------------------------------------
        static auto is_initialized() -> bool;

        /// ----------------------------------------------------------------------------------------
        /// compiles shader modules from `inputs` into shader program.
        /// ----------------------------------------------------------------------------------------
        static auto compile(shader_stage stage, string_view source) -> spirv_compilation_result;

    private:
        static bool _is_initialized;
    };
}

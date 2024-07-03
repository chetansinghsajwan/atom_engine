export module atom_engine:rendering.shader_factory;

import atom_core;
import atom_logging;
import :rendering.shader;
import :rendering.shader_factory_impl;
import :shaders.spirv_compiler;

namespace atom::engine
{
    export class shader_factory
    {
    public:
        static auto initialize() -> void;

        static auto finalize() -> void;

        static auto set_root_path(string_view path) -> void;

        static auto get_root_path() -> string_view;

        /// ----------------------------------------------------------------------------------------
        /// creates shaders from each shader file with different extensions. this will search and
        /// read files for each type of shader.
        ///
        /// # example
        ///
        /// if path is "assets/shaders/glow", then it will search for files like
        /// - "assets/shaders/glow.vert"
        /// - "assets/shaders/glow.frag"
        /// ----------------------------------------------------------------------------------------
        static auto create_from_files(
            string_view path) -> result<shader*, shader_compilation_error, shader_linking_error>;

        static auto create_from_file(string_view path) -> shader*;

        static auto create_from_source(
            string_view vertex_source, string_view fragment_source) -> shader*;

        static auto destroy(class shader* shader) -> void;

    private:
        static auto _get_absolute_path(string_view path) -> string;

        static auto _parse_sources_from_file(
            string_view source, string_view* vertex_source, string_view* fragement_source) -> void;

        static auto _create_impl() -> shader_factory_impl*;

        static auto _create_from_files_spirv(
            string_view path) -> result<shader*, shader_compilation_error, shader_linking_error>;

        static auto _create_from_files_opengl(
            string_view path) -> result<shader*, shader_compilation_error, shader_linking_error>;

    private:
        static inline shader_factory_impl* _impl = nullptr;
        static inline logging::logger* _logger = nullptr;
        static inline std::string _root_path = "";
    };
}

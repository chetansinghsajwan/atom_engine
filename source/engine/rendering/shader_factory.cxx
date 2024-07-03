module;
#include "glad/glad.h"

module atom_engine:rendering.shader_factory.impl;
import :rendering.shader_factory;

import atom_core;
import atom_logging;
import :rendering.shader_factory_impl;
import :opengl.shader_factory_impl;
import :rendering.shader;
import :rendering.shader_factory_impl;
import :shaders.shader_utils;
import :shaders.spirv_compiler;

namespace atom::engine
{
    auto shader_factory::initialize() -> void
    {
        contract_debug_expects(_impl == nullptr, "shader_factory is already initialized.");

        _logger = logging::logger_manager::create_logger({ .name = "shader_factory" }).get_value();
        _impl = _create_impl();

        spirv_compiler::initialize();
    }

    auto shader_factory::finalize() -> void
    {
        contract_debug_expects(_impl != nullptr, "shader_factory is not initialized.");

        spirv_compiler::finalize();

        delete _impl;
        delete _logger;
    }

    auto shader_factory::set_root_path(string_view path) -> void
    {
        _root_path = std::string(path.get_data(), path.get_count());
        if (not _root_path.empty())
        {
            if (_root_path.back() == '\0')
            {
                _root_path.erase(_root_path.end() - 1);
            }

            if (_root_path.back() != '/')
            {
                _root_path.push_back('/');
            }
        }
    }

    auto shader_factory::get_root_path() -> string_view
    {
        return string_view::from_std(_root_path);
    }

    auto _add_shader_extension(string_view path, shader_stage stage) -> string
    {
        string_view shader_file_extension = shader_utils::get_file_extension_for_stage(stage);

        string final_path = path;
        final_path | ranges::get_back() = '.';
        final_path.insert_range_back(shader_file_extension);

        return final_path;
    }

    auto _convert_shader_stage_to_opengl(shader_stage stage) -> GLuint
    {
        switch (stage)
        {
            case shader_stage::vertex:   return GL_VERTEX_SHADER;
            case shader_stage::fragment: return GL_FRAGMENT_SHADER;
            case shader_stage::geometry: return GL_GEOMETRY_SHADER;
            case shader_stage::compute:  return GL_COMPUTE_SHADER;
            default:
            {
                contract_panic("invalid or unsupported value.");
            }
        }
    }

    auto shader_factory::_create_from_files_spirv(
        string_view path) -> result<shader*, shader_compilation_error, shader_linking_error>
    {
        // get absolute path
        string abs_path = _get_absolute_path(path);
        _logger->log_info("reading shader files at '{}'", abs_path);

        bool is_error = false;

        result<shader*, shader_compilation_error, shader_linking_error> result_{ nullptr };

        GLuint gl_shaders[shader_utils::get_stage_count()] = { 0 };
        for (shader_stage stage : shader_utils::get_stages())
        {
            string final_path = _add_shader_extension(abs_path, stage);

            _logger->log_info("reading shader file '{}'...", final_path);
            auto shader_source_result = filesystem::read_file_str(final_path);

            if (shader_source_result.is_error<filesystem::noentry_error>())
            {
                _logger->log_info("reading shader file done, file not found, skipping.");
                continue;
            }

            if (shader_source_result.is_error())
            {
                _logger->log_error("could not read shader file '{}', skipping", final_path);
                continue;
            }

            string shader_source = move(shader_source_result).get_value();
            _logger->log_info("reading shader file done.", final_path);

            _logger->log_info("compiling and linking shader...");

            spirv_compilation_result compilation_result =
                spirv_compiler::compile(stage, shader_source);

            if (compilation_result.is_error<shader_compilation_error>())
            {
                // todo: log error details as well
                shader_compilation_error& error =
                    compilation_result.get_error<shader_compilation_error>();
                _logger->log_error("shader compilation failed, error: {}", error.msg);

                is_error = true;
                result_.set_error(error);
                break;
            }

            if (compilation_result.is_error<shader_linking_error>())
            {
                // todo: log error details as well
                _logger->log_error("shader linking failed.");

                is_error = true;
                result_.set_error(compilation_result.get_error<shader_linking_error>());
                break;
            }

            // we got the output
            dynamic_buffer spv_binary = move(compilation_result).get_value();

            _logger->log_info(
                "compiling and linking shader done, spv size: {}.", spv_binary.get_size());

            _logger->log_info("creating opengl shader...");

            // create opengl shader
            GLuint gl_shader_stage = _convert_shader_stage_to_opengl(stage);
            GLuint gl_shader = glCreateShader(gl_shader_stage);

            _logger->log_trace("created opengl shader, id: {}", gl_shader);
            _logger->log_trace("uploading spv binary data to opengl shader...");

            glShaderBinary(1, &gl_shader, GL_SHADER_BINARY_FORMAT_SPIR_V, spv_binary.get_data(),
                spv_binary.get_size());

            if (glGetError() != GL_NO_ERROR)
            {
                contract_panic("error loading spirv bytecode into vertex shader.");
            }

            _logger->log_trace("uploading spv binary data to opengl shader done.");
            _logger->log_trace("specializing opengl shader...");

            glSpecializeShader(gl_shader, "main", 0, nullptr, nullptr);

            _logger->log_trace("specializing opengl shader done.");

            gl_shaders[(usize)stage] = gl_shader;

            _logger->log_info("creating opengl shader done.");
        }

        // error occcurred, so cleanup and return
        if (is_error)
        {
            _logger->log_trace("deleting allocated shader resources...");

            for (GLuint gl_shader : gl_shaders)
            {
                if (gl_shader == 0)
                {
                    continue;
                }

                glDeleteShader(gl_shader);
            }

            _logger->log_trace("deleting allocated shader resources done.");

            return result_;
        }

        _logger->log_trace("creating opengl shader program...");

        // create opengl program
        GLuint gl_program = glCreateProgram();
        for (GLuint gl_shader : gl_shaders)
        {
            if (gl_shader == 0)
            {
                continue;
            }

            glAttachShader(gl_program, gl_shader);
        }

        _logger->log_trace("creating opengl shader program done.");

        _logger->log_trace("linking opengl shader program...");
        glLinkProgram(gl_program);

        int success;
        glGetProgramiv(gl_program, GL_LINK_STATUS, &success);
        if (not success)
        {
            char info_log[512];
            glGetProgramInfoLog(gl_program, 512, nullptr, info_log);

            _logger->log_trace("linking opengl shader program failed, msg: {}", info_log);
            return shader_linking_error{
                string{ create_from_raw, info_log }
            };
        }

        _logger->log_trace("linking opengl shader program done.");
        _logger->log_trace("deleting allocated shader resources...");

        for (GLuint gl_shader : gl_shaders)
        {
            if (gl_shader == 0)
            {
                continue;
            }

            glDeleteShader(gl_shader);
        }
        _logger->log_trace("deleting allocated shader resources done.");

        return new opengl_shader{ gl_program };
    }

    auto shader_factory::_create_from_files_opengl(
        string_view path) -> result<shader*, shader_compilation_error, shader_linking_error>
    {
        // get absolute path
        string abs_path = _get_absolute_path(path);
        _logger->log_info("reading shader files at '{}'", abs_path);

        bool is_error = false;

        result<shader*, shader_compilation_error, shader_linking_error> result_{ nullptr };

        GLuint gl_shaders[shader_utils::get_stage_count()] = { 0 };
        for (shader_stage stage : shader_utils::get_stages())
        {
            string final_path = _add_shader_extension(abs_path, stage);

            _logger->log_info("reading shader file '{}'...", final_path);
            auto shader_source_result = filesystem::read_file_str(final_path);

            if (shader_source_result.is_error<filesystem::noentry_error>())
            {
                _logger->log_info("reading shader file done, file not found, skipping.");
                continue;
            }

            if (shader_source_result.is_error())
            {
                _logger->log_error("could not read shader file '{}', skipping", final_path);
                continue;
            }

            string shader_source = move(shader_source_result).get_value();
            _logger->log_info("reading shader file done.", final_path);

            _logger->log_info("compiling shader...");

            const char* shader_source_raw = shader_source.get_data();
            GLint shader_source_length = shader_source.get_count();

            GLuint gl_shader_stage = _convert_shader_stage_to_opengl(stage);
            GLuint gl_shader = glCreateShader(gl_shader_stage);
            glShaderSource(gl_shader, 1, &shader_source_raw, &shader_source_length);

            glCompileShader(gl_shader);

            GLint is_compiled = 0;
            glGetShaderiv(gl_shader, GL_COMPILE_STATUS, &is_compiled);
            if (is_compiled == GL_FALSE)
            {
                GLint max_length = 0;
                glGetShaderiv(gl_shader, GL_INFO_LOG_LENGTH, &max_length);

                dynamic_array<GLchar> info_log{ create_with_capacity, (usize)max_length };
                glGetShaderInfoLog(gl_shader, max_length, &max_length, info_log.get_mut_data());

                // cleanup up the allocated resources
                glDeleteShader(gl_shader);

                _logger->log_fatal("shader compilation failed. info_log: {}", info_log.get_data());

                is_error = true;
                result_.emplace_error<shader_compilation_error>("");
                break;
            }

            gl_shaders[(usize)stage] = gl_shader;

            _logger->log_info("compiling shader done.");
        }

        // error occcurred, so cleanup and return
        if (is_error)
        {
            _logger->log_trace("deleting allocated shader resources...");

            for (GLuint gl_shader : gl_shaders)
            {
                if (gl_shader == 0)
                {
                    continue;
                }

                glDeleteShader(gl_shader);
            }

            _logger->log_trace("deleting allocated shader resources done.");

            return result_;
        }

        _logger->log_trace("creating opengl shader program...");

        // create opengl program
        GLuint gl_program = glCreateProgram();
        for (GLuint gl_shader : gl_shaders)
        {
            if (gl_shader == 0)
            {
                continue;
            }

            glAttachShader(gl_program, gl_shader);
        }

        _logger->log_trace("creating opengl shader program done.");

        _logger->log_trace("linking opengl shader program...");
        glLinkProgram(gl_program);

        int success;
        glGetProgramiv(gl_program, GL_LINK_STATUS, &success);
        if (not success)
        {
            char info_log[512];
            glGetProgramInfoLog(gl_program, 512, nullptr, info_log);

            _logger->log_trace("linking opengl shader program failed, msg: {}", info_log);
            return shader_linking_error{
                string{ create_from_raw, info_log }
            };
        }

        _logger->log_trace("linking opengl shader program done.");
        _logger->log_trace("deleting allocated shader resources...");

        for (GLuint gl_shader : gl_shaders)
        {
            if (gl_shader == 0)
            {
                continue;
            }

            glDeleteShader(gl_shader);
        }
        _logger->log_trace("deleting allocated shader resources done.");

        return new opengl_shader{ gl_program };
    }

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
    auto shader_factory::create_from_files(
        string_view path) -> result<shader*, shader_compilation_error, shader_linking_error>
    {
        contract_debug_expects(_impl != nullptr, "shader_factory is not initialized.");

        return _create_from_files_opengl(path);
    }

    auto shader_factory::create_from_file(string_view path) -> shader*
    {
        contract_debug_expects(_impl != nullptr, "shader_factory is not initialized.");

        string abs_path = _get_absolute_path(path);

        _logger->log_trace("loading shader from file '{}'", abs_path);
        _logger->log_trace("reading file...");

        string source = filesystem::read_file_str(abs_path).get_value();

        _logger->log_trace("reading file done.");
        _logger->log_trace("parsing file content...");

        string_view vertex_source;
        string_view fragement_source;
        _parse_sources_from_file(source, &vertex_source, &fragement_source);

        _logger->log_trace("parsing file content done.");

        return create_from_source(vertex_source, fragement_source);
    }

    auto shader_factory::create_from_source(
        string_view vertex_source, string_view fragment_source) -> shader*
    {
        contract_debug_expects(_impl != nullptr, "shader_factory is not initialized.");

        return _impl->create(vertex_source, fragment_source);
    }

    auto shader_factory::destroy(class shader* shader) -> void
    {
        contract_debug_expects(_impl != nullptr, "shader_factory is not initialized.");

        return _impl->destroy(shader);
    }

    auto shader_factory::_get_absolute_path(string_view path) -> string
    {
        contract_debug_expects(path | ranges::is_not_empty());

        // path is already an absolute path
        if ((path | ranges::get_front()) == '/')
            return path;

        string_view root_path = string_view::from_std(_root_path);
        string result{ create_with_capacity, root_path.get_count() + path.get_count() };
        result.insert_range_back(root_path);
        result.insert_range_back(path);
        return result;
    }

    auto shader_factory::_parse_sources_from_file(
        string_view source, string_view* vertex_source, string_view* fragement_source) -> void
    {
        const char* token_begin = "#type ";
        const char* token_end = token_begin + 6;
        const char* source_begin = source.get_data();
        const char* source_end = source_begin + source.get_count();
        const char* last_token_begin = nullptr;
        const char* last_token_end = nullptr;
        const char* source_it = source_begin;
        while (source_it != source_end)
        {
            const char* current_token_begin =
                std::search(source_it, source_end, token_begin, token_end);
            const char* current_token_end = current_token_begin + (token_end - token_begin);

            // process the pervious result first
            if (last_token_begin != nullptr)
            {
                const char* last_type_begin = last_token_end;
                const char* last_type_end = std::find(last_type_begin, source_end, '\n');
                const char* last_source_begin = last_type_end + 1;
                const char* last_source_end = current_token_begin;

                std::string_view last_type(last_type_begin, last_type_end);
                if (last_type == "vertex")
                {
                    if (vertex_source != nullptr)
                    {
                        _logger->log_trace("parsed vertex shader.");

                        *vertex_source =
                            string_view(ranges::from(last_source_begin, last_source_end));
                    }
                    else
                    {
                        _logger->log_trace(
                            "parsed vertex shader, but was not requested, so skipping.");
                    }
                }
                else if (last_type == "fragement")
                {
                    if (fragement_source != nullptr)
                    {
                        _logger->log_trace("parsed fragement shader.");

                        *fragement_source =
                            string_view(ranges::from(last_source_begin, last_source_end));
                    }
                    else
                    {
                        _logger->log_trace(
                            "parsed fragement shader, but was not requested, so skipping.");
                    }
                }
                else
                {
                    contract_panic("unknown shader type.");
                }
            }

            // we did not found an token.
            if (current_token_begin == source_end)
                break;

            last_token_begin = current_token_begin;
            last_token_end = current_token_end;
            source_it = current_token_end;
        }
    }

    auto shader_factory::_create_impl() -> shader_factory_impl*
    {
        return new opengl_shader_factory_impl();
    }
}

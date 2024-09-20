import atom.core;
import atom.logging;

#include "atom/engine/rendering/shader_factory.h"
#include "atom/engine/filesystem.h"
#include "atom/engine/logging.h"
#include "engine/rendering/shader_factory_impl.h"
#include "engine/opengl/opengl_shader_factory_impl.h"

namespace atom::engine
{
    static shader_factory_impl* _impl;
    static logging::logger* _logger;
    static std::string _root_path;

    static auto _get_absolute_path(string_view path) -> string
    {
        ATOM_DEBUG_EXPECTS(not path.is_empty());

        // path is already an absolute path
        if (path.get_front() == '/')
            return path;

        string_view root_path = string_view::from_std(_root_path);
        string result = string::with_capacity(root_path.get_count() + path.get_count());
        result.insert_range_back(root_path);
        result.insert_range_back(path);
        return result;
    }

    static auto _parse_sources_from_file(
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
                            string_view(range_from(last_source_begin, last_source_end));
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
                            string_view(range_from(last_source_begin, last_source_end));
                    }
                    else
                    {
                        _logger->log_trace(
                            "parsed fragement shader, but was not requested, so skipping.");
                    }
                }
                else
                {
                    ATOM_PANIC("unknown shader type.", last_type);
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

    auto shader_factory::initialize() -> void
    {
        ATOM_DEBUG_EXPECTS(_impl == nullptr, "shader_factory is already initialized.");

        _logger = logging::logger_manager::create_logger({ .name = "shader_factory" }).get_value();
        _impl = new opengl_shader_factory_impl();
    }

    auto shader_factory::finalize() -> void
    {
        ATOM_DEBUG_EXPECTS(_impl != nullptr, "shader_factory is not initialized.");

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

    auto shader_factory::create_from_file(string_view path) -> shader*
    {
        ATOM_DEBUG_EXPECTS(_impl != nullptr, "shader_factory is not initialized.");

        string abs_path = _get_absolute_path(path);

        _logger->log_trace("loading shader from file '{}'", abs_path);
        _logger->log_trace("reading file...");

        string source = filesystem::read_file(abs_path).get_value();

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
        ATOM_DEBUG_EXPECTS(_impl != nullptr, "shader_factory is not initialized.");

        return _impl->create(vertex_source, fragment_source);
    }

    auto shader_factory::destroy(class shader* shader) -> void
    {
        ATOM_DEBUG_EXPECTS(_impl != nullptr, "shader_factory is not initialized.");

        return _impl->destroy(shader);
    }
}

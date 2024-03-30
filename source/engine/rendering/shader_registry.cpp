#include "atom/engine/rendering/shader_registry.h"
#include "atom/engine/logging.h"

namespace atom::engine
{
    logging::logger* _logger;
    unordered_map<string_view, shader*> _register;

    auto shader_registry::initialize() -> void
    {
        _logger = logging::logger_manager::create_logger({ .name = "shader_factory" }).get_value();
        _logger->log_info("initializing...");
        _logger->log_info("initializing done.");
    }

    auto shader_registry::finalize() -> void
    {
        _logger->log_info("finalizing...");
        _logger->log_info("finalizing done.");
        delete _logger;
    }

    auto shader_registry::register_(
        string_view name, class shader* shader) -> result<void, value_exists_error>
    {
        _logger->log_info("registring shader, name: '{}'...", name);

        auto result = _register.insert(pair<string_view, class shader*>(name, shader));
        if (result.second)
        {
            _logger->log_info("registring shader done.");
            return result_void();
        }
        else
        {
            _logger->log_info(
                "registering shader failed, a shader already with the same key already exists.");
            return value_exists_error();
        }
    }

    auto shader_registry::register_override(string_view name, class shader* shader) -> void
    {
        _logger->log_info("registring shader, name: '{}'...", name);

        auto result = _register.insert_or_assign(name, shader);
        if (result.second)
        {
            _logger->log_info("registring shader done.");
        }
        else
        {
            _logger->log_info("registring shader done, replaced previous entry.");
        }
    }

    auto shader_registry::get_name(class shader* shader) -> string_view
    {
        for (auto entry : _register)
        {
            if (entry.second == shader)
            {
                return entry.first;
            }
        }

        return string_view::from_empty();
    }

    auto shader_registry::get_shader(string_view name) -> shader*
    {
        auto it = _register.find(name);
        if (it == _register.end())
            return nullptr;

        return it->second;
    }

    auto shader_registry::has_name(string_view name) -> bool
    {
        return _register.contains(name);
    }

    auto shader_registry::has_shader(class shader* shader) -> bool
    {
        ATOM_DEBUG_EXPECTS(shader != nullptr);

        for (auto entry : _register)
        {
            if (entry.second == shader)
                return true;
        }

        return false;
    }
}

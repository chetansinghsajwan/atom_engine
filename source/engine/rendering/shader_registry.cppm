export module atom.engine:rendering.shader_registry;

import atom.core;
import atom.logging;
import :rendering.shader;

namespace atom::engine
{
    export class shader_registry
    {
    public:
        static auto initialize() -> void
        {
            _logger =
                logging::logger_manager::create_logger({ .name = "shader_factory" }).get_value();
            _logger->log_info("initializing...");
            _logger->log_info("initializing done.");
        }

        static auto finalize() -> void
        {
            _logger->log_info("finalizing...");
            _logger->log_info("finalizing done.");
            delete _logger;
        }

        static auto register_(
            string_view name, class shader* shader) -> result<void, value_exists_error>
        {
            _logger->log_info("registring shader, name: '{}'...", name);

            auto result = _register.insert(pair<string_view, class shader*>(name, shader));
            if (result.second)
            {
                _logger->log_info("registring shader done.");
                return { create_from_void };
            }
            else
            {
                _logger->log_info("registering shader failed, a shader already with the same key "
                                  "already exists.");
                return value_exists_error();
            }
        }

        static auto register_override(string_view name, class shader* shader) -> void
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

        static auto get_name(class shader* shader) -> string_view
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

        static auto get_shader(string_view name) -> shader*
        {
            auto it = _register.find(name);
            if (it == _register.end())
                return nullptr;

            return it->second;
        }

        static auto has_name(string_view name) -> bool
        {
            return _register.contains(name);
        }

        static auto has_shader(class shader* shader) -> bool
        {
            contract_debug_expects(shader != nullptr);

            for (auto entry : _register)
            {
                if (entry.second == shader)
                    return true;
            }

            return false;
        }

    private:
        static inline logging::logger* _logger;
        static inline unordered_map<string_view, shader*> _register;
    };
}

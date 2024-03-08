#pragma once

namespace atom::engine
{
    enum class renderer_api
    {
        none,
        opengl
    };

    class renderer
    {
    public:
        static auto get_api() -> renderer_api
        {
            return _api;
        }

    private:
        static renderer_api _api;
    };
}

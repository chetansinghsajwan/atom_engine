#pragma once

namespace atom::editor
{
    class panel
    {
    public:
        panel() {}

    public:
        virtual auto on_imgui_render() -> void = 0;
    };
}

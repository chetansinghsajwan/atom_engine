export module atom_engine:glfw.window_user_data;

namespace atom::engine
{
    class glfw_window;
    class glfw_keyboard;
    class glfw_mouse;

    struct glfw_window_user_data
    {
        glfw_window* window;
        glfw_keyboard* keyboard;
        glfw_mouse* mouse;
    };
}

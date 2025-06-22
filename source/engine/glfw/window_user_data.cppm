export module atom_engine:glfw.window_user_data;

namespace atom::engine
{
    struct glfw_window;
    struct glfw_keyboard;
    struct glfw_mouse;

    struct glfw_window_user_data
    {
        glfw_window* window;
        glfw_keyboard* keyboard;
        glfw_mouse* mouse;
    };
}

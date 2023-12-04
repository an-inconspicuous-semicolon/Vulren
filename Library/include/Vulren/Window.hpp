//
// Created by reece on 04/11/2023.
//

#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32

#include <string>
#include <functional>
#include <forward_list>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Vulren/Resource.hpp"
#include "Vulren/Wrapper.hpp"


namespace vulren
{

class Window
        : public Resource,
          public Wrapper<GLFWwindow*>
{
public:
    enum class CursorMode
    {
        Normal = 0,
        Centered = 1,
        Hidden = 2,
    };

    struct Descriptor
    {
        unsigned int width = 640, height = 480;
        std::string title;
        bool manual_resize_enabled = true;
        bool manual_mode_switch_enabled = false;
        bool fullscreen = false;
        bool splashscreen = false;
        CursorMode default_cursor_mode = CursorMode::Normal;
    };

    struct EventType
    {
        using WindowClose = std::function<bool(Window&)>;
        using WindowSize = std::function<void(Window&, unsigned int, unsigned int)>;
        using CursorPos = std::function<void(Window&, double, double)>;
        using MouseButton = std::function<void(Window&, int button, int action, int mods)>;
        using MouseScroll = std::function<void(Window&, double, double)>;
        using KeyboardKey = std::function<void(Window&, int, int, int, int)>;
        using KeyboardChar = std::function<void(Window&, unsigned int)>;
    };

public:
    ~Window() override;

    void close();

    bool is_open();

    GLFWwindow* get() override;

    unsigned int width() const;
    unsigned int height() const;
    const std::string& title() const;

    void resize(unsigned int new_width, unsigned int new_height);
    void set_title(std::string new_title);

    HWND get_native_handle() const;

    void add_window_close_callback(const EventType::WindowClose& callback);
    void add_window_size_callback(const EventType::WindowSize& callback);
    void add_cursor_position_callback(const EventType::CursorPos& callback);
    void add_mouse_button_callback(const EventType::MouseButton& callback);
    void add_mouse_scroll_callback(const EventType::MouseScroll& callback);
    void add_keyboard_key_callback(const EventType::KeyboardKey& callback);
    void add_keyboard_char_callback(const EventType::KeyboardChar& callback);

    void remove_window_close_callback(Window::EventType::WindowClose& callback);
    void remove_window_size_callback(const EventType::WindowSize& callback);
    void remove_cursor_position_callback(const EventType::CursorPos& callback);
    void remove_mouse_button_callback(const EventType::MouseButton& callback);
    void remove_mouse_scroll_callback(const EventType::MouseScroll& callback);
    void remove_keyboard_key_callback(const EventType::KeyboardKey& callback);
    void remove_keyboard_char_callback(const EventType::KeyboardChar& callback);

protected:
    friend class ResourceManager;

    // why can't friends be inherited :(
    friend class Instance;

    explicit Window(Descriptor desc);
    static void PollEvents();

private:
    static void GlfwErrorCallback(int code, const char* description);
    static void GlfwWindowCloseCallback(GLFWwindow* window);
    static void GlfwWindowSizeCallback(GLFWwindow* window, int width, int height);
    static void GlfwCursorPosCallback(GLFWwindow* window, double x_pos, double y_pos);
    static void GlfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void GlfwMouseScrollCallback(GLFWwindow* window, double x_offset, double y_offset);
    static void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void GlfwCharCallback(GLFWwindow* window, unsigned int codepoint);

    static void InitialiseGlfw();

    void update_window_size(int expected_width, int expected_height);

private:
    Descriptor m_desc;
    GLFWwindow* m_handle;

    std::forward_list<EventType::WindowClose> m_callbacks_for_window_close;
    std::forward_list<EventType::WindowSize> m_callbacks_for_window_size;
    std::forward_list<EventType::CursorPos> m_callbacks_for_cursor_pos;
    std::forward_list<EventType::MouseButton> m_callbacks_for_mouse_button;
    std::forward_list<EventType::MouseScroll> m_callbacks_for_mouse_scroll;
    std::forward_list<EventType::KeyboardKey> m_callbacks_for_keyboard_key;
    std::forward_list<EventType::KeyboardChar> m_callbacks_for_keyboard_char;

    static unsigned int s_glfw_references;
};

} // vulren

//
// Created by reece on 04/11/2023.
//

#include <stdexcept>
#include <sstream>
#include <utility>
#include "Vulren/Window.hpp"
#include "internal/Logging.hpp"

namespace vulren
{

unsigned int Window::s_glfw_references = 0;


Window::Window(Descriptor desc)
        : m_desc(std::move(desc))
{
    if (s_glfw_references == 0)
    {
        InitialiseGlfw();
    }
    s_glfw_references++;

    glfwWindowHint(GLFW_STEREO, GLFW_FALSE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    glfwWindowHint(GLFW_RESIZABLE, m_desc.manual_resize_enabled);
    glfwWindowHint(GLFW_DECORATED, !m_desc.splashscreen && !m_desc.fullscreen);
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
    glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);

    GLFWmonitor* primary_monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* primary_video_mode = glfwGetVideoMode(primary_monitor);

    int final_width, final_height;
    if (m_desc.fullscreen)
    {
        final_width = primary_video_mode->width;
        final_height = primary_video_mode->height;
    } else
    {
        final_width = static_cast<int>(m_desc.width);
        final_height = static_cast<int>(m_desc.height);
    }

    GLFWmonitor* final_monitor = nullptr;
    if (m_desc.fullscreen) final_monitor = primary_monitor;


    GLFWwindow* ptr = glfwCreateWindow(
            final_width, final_height, m_desc.title
                                             .c_str(), final_monitor, nullptr
    );
    if (ptr == nullptr) throw std::runtime_error("Failed to create glfw Window");

    glfwSetWindowUserPointer(ptr, this);
    glfwSetWindowCloseCallback(ptr, GlfwWindowCloseCallback);
    glfwSetWindowSizeCallback(ptr, GlfwWindowSizeCallback);
    glfwSetCursorPosCallback(ptr, GlfwCursorPosCallback);
    glfwSetMouseButtonCallback(ptr, GlfwMouseButtonCallback);
    glfwSetScrollCallback(ptr, GlfwMouseScrollCallback);
    glfwSetKeyCallback(ptr, GlfwKeyCallback);
    glfwSetCharCallback(ptr, GlfwCharCallback);

    m_handle = ptr;
    internal::log_info("Created window \"" + m_desc.title + '\"');
}

Window::~Window()
{
    if (s_glfw_references != 0 && --s_glfw_references == 0)
    {
        glfwTerminate();
    }
}

void Window::close()
{
    if (m_handle)
    {
        glfwDestroyWindow(m_handle);
        internal::log_info("Destroyed window \"" + m_desc.title + '\"');
        m_handle = nullptr;
    }
}


void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::InitialiseGlfw()
{
    if (!glfwInit()) throw std::runtime_error("Failed to initialise glfw");
    glfwSetErrorCallback(GlfwErrorCallback);
}

bool Window::is_open()
{
    return m_handle != nullptr;
}

GLFWwindow* Window::get()
{
    return m_handle;
}

unsigned int Window::width() const
{
    return m_desc.width;
}

unsigned int Window::height() const
{
    return m_desc.height;
}

const std::string& Window::title() const
{
    return m_desc.title;
}

void Window::resize(unsigned int new_width, unsigned int new_height)
{
    int width = static_cast<int>(new_width);
    int height = static_cast<int>(new_height);

    glfwSetWindowSize(m_handle, width, height);
}

void Window::set_title(std::string new_title)
{
    m_desc.title = std::move(new_title);
}

void Window::update_window_size(int expected_width, int expected_height)
{
    int actual_width, actual_height;

    // sometimes the width of a window is changed by the window manager. (especially with tiling window managers on linux) so we need to check that we got what we wanted
    glfwGetWindowSize(m_handle, &actual_width, &actual_height);

    if (actual_width != expected_width || actual_height != expected_height)
    {
        std::ostringstream oss;
        oss << "Window size was changed by the OS. Expected (" << expected_width << ", " << expected_height
            << ") but got (" << actual_width << ", " << actual_height << ")";
        internal::log_warning(oss.str());
    }

    m_desc.width = actual_width;
    m_desc.height = actual_height;
}

HWND Window::get_native_handle() const
{
    return glfwGetWin32Window(m_handle);
}

void Window::GlfwErrorCallback(int code, const char* description)
{
    std::ostringstream oss;
    oss << "GLFW Error " << code << ": " << description;

    internal::log_error(oss.str());
}

void Window::GlfwWindowCloseCallback(GLFWwindow* window)
{
    void* user_ptr = glfwGetWindowUserPointer(window);
    auto* window_ptr = reinterpret_cast<Window*>(user_ptr);

    for (const auto& callback: window_ptr->m_callbacks_for_window_close)
    {
        if (callback(*window_ptr)) break;
    }

    window_ptr->close();
}

void Window::GlfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    void* user_ptr = glfwGetWindowUserPointer(window);
    auto* window_ptr = reinterpret_cast<Window*>(user_ptr);

    window_ptr->m_desc
              .width = static_cast<unsigned int>(width);
    window_ptr->m_desc
              .height = static_cast<unsigned int>(height);

    for (const auto& callback: window_ptr->m_callbacks_for_window_size)
    {
        callback(
                *window_ptr, window_ptr->m_desc.width, window_ptr->m_desc.height
        );
    }
}

void Window::GlfwCursorPosCallback(GLFWwindow* window, double x_pos, double y_pos)
{
    void* user_ptr = glfwGetWindowUserPointer(window);
    auto* window_ptr = reinterpret_cast<Window*>(user_ptr);

    for (const auto& callback: window_ptr->m_callbacks_for_cursor_pos)
    {
        callback(*window_ptr, x_pos, y_pos);
    }
}

void Window::GlfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    void* user_ptr = glfwGetWindowUserPointer(window);
    auto* window_ptr = reinterpret_cast<Window*>(user_ptr);

    for (const auto& callback: window_ptr->m_callbacks_for_mouse_button)
    {
        callback(*window_ptr, button, action, mods);
    }
}

void Window::GlfwMouseScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
{
    void* user_ptr = glfwGetWindowUserPointer(window);
    auto* window_ptr = reinterpret_cast<Window*>(user_ptr);

    for (const auto& callback: window_ptr->m_callbacks_for_mouse_scroll)
    {
        callback(*window_ptr, x_offset, y_offset);
    }
}

void Window::GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    void* user_ptr = glfwGetWindowUserPointer(window);
    auto* window_ptr = reinterpret_cast<Window*>(user_ptr);

    for (const auto& callback: window_ptr->m_callbacks_for_keyboard_key)
    {
        callback(*window_ptr, key, scancode, action, mods);
    }
}

void Window::GlfwCharCallback(GLFWwindow* window, unsigned int codepoint)
{
    void* user_ptr = glfwGetWindowUserPointer(window);
    auto* window_ptr = reinterpret_cast<Window*>(user_ptr);

    for (const auto& callback: window_ptr->m_callbacks_for_keyboard_char)
    {
        callback(*window_ptr, codepoint);
    }
}

void Window::add_window_close_callback(const Window::EventType::WindowClose& callback)
{
    m_callbacks_for_window_close.push_front(callback);
}

void Window::add_window_size_callback(const Window::EventType::WindowSize& callback)
{
    m_callbacks_for_window_size.push_front(callback);
}

void Window::add_cursor_position_callback(const Window::EventType::CursorPos& callback)
{
    m_callbacks_for_cursor_pos.push_front(callback);
}

void Window::add_mouse_button_callback(const Window::EventType::MouseButton& callback)
{
    m_callbacks_for_mouse_button.push_front(callback);
}

void Window::add_mouse_scroll_callback(const Window::EventType::MouseScroll& callback)
{
    m_callbacks_for_mouse_scroll.push_front(callback);
}

void Window::add_keyboard_key_callback(const Window::EventType::KeyboardKey& callback)
{
    m_callbacks_for_keyboard_key.push_front(callback);
}

void Window::add_keyboard_char_callback(const Window::EventType::KeyboardChar& callback)
{
    m_callbacks_for_keyboard_char.push_front(callback);
}

void Window::remove_window_close_callback(Window::EventType::WindowClose& callback)
{
    m_callbacks_for_window_close.remove_if(
            [&callback](const auto& storedCallback)
            {
                return storedCallback.target_type() == callback.target_type();
            }
    );
}

void Window::remove_window_size_callback(const Window::EventType::WindowSize& callback)
{
    m_callbacks_for_window_size.remove_if(
            [&callback](const auto& storedCallback)
            {
                return storedCallback.target_type() == callback.target_type();
            }
    );
}

void Window::remove_cursor_position_callback(const Window::EventType::CursorPos& callback)
{
    m_callbacks_for_cursor_pos.remove_if(
            [&callback](const auto& storedCallback)
            {
                return storedCallback.target_type() == callback.target_type();
            }
    );
}

void Window::remove_mouse_button_callback(const Window::EventType::MouseButton& callback)
{
    m_callbacks_for_mouse_button.remove_if(
            [&callback](const auto& storedCallback)
            {
                return storedCallback.target_type() == callback.target_type();
            }
    );
}

void Window::remove_mouse_scroll_callback(const Window::EventType::MouseScroll& callback)
{
    m_callbacks_for_mouse_scroll.remove_if(
            [&callback](const auto& storedCallback)
            {
                return storedCallback.target_type() == callback.target_type();
            }
    );
}

void Window::remove_keyboard_key_callback(const Window::EventType::KeyboardKey& callback)
{
    m_callbacks_for_keyboard_key.remove_if(
            [&callback](const auto& storedCallback)
            {
                return storedCallback.target_type() == callback.target_type();
            }
    );
}

void Window::remove_keyboard_char_callback(const Window::EventType::KeyboardChar& callback)
{
    m_callbacks_for_keyboard_char.remove_if(
            [&callback](const auto& storedCallback)
            {
                return storedCallback.target_type() == callback.target_type();
            }
    );
}

} // vulren
//
// Created by reece on 04/11/2023.
//

#include <stdexcept>
#include <sstream>
#include "Vulren/Window.hpp"
#include "internal/Logging.hpp"

namespace vulren
{

unsigned int Window::s_glfw_references = 0;

Window::Window(unsigned int width, unsigned int height, std::string title)
        : m_width(width),
          m_height(height),
          m_title(std::move(title))
{
    if (s_glfw_references == 0)
    {
        InitialiseGlfw();
    }
    s_glfw_references++;

    glfwWindowHint(GLFW_STEREO, GLFW_FALSE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
    glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);

    int glfw_width = static_cast<int>(width);
    int glfw_height = static_cast<int>(height);

    GLFWwindow* ptr = glfwCreateWindow(glfw_width, glfw_height, m_title.c_str(), nullptr, nullptr);
    if (ptr == nullptr) throw std::runtime_error("Failed to create glfw Window");

    glfwSetWindowUserPointer(ptr, this);
    glfwSetWindowCloseCallback(ptr, GlfwWindowCloseCallback);

    m_handle = ptr;
    internal::log_info("Created window " + m_title);
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
        internal::log_info("Destroyed window " + m_title);
        m_handle = nullptr;
    }
}

void Window::GlfwErrorCallback(int code, const char* description)
{
    std::ostringstream oss;
    oss << "GLFW Error " << code << ": " << description;

    internal::log_error(oss.str());
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::GlfwWindowCloseCallback(GLFWwindow* window)
{
    void* user_ptr = glfwGetWindowUserPointer(window);
    auto* window_ptr = reinterpret_cast<Window*>(user_ptr);

    window_ptr->close();
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


} // vulren
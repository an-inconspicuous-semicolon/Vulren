//
// Created by reece on 04/11/2023.
//

#pragma once

#include <string>
#include <GLFW/glfw3.h>

#include "Vulren/Resource.hpp"

namespace vulren
{

class Window
        : public Resource
{
public:
    ~Window() override;

    void close();
    bool is_open();

protected:
    friend class ResourceManager;

    friend class Instance;

    Window(unsigned int width, unsigned height, std::string title);
    static void PollEvents();

private:
    static void GlfwErrorCallback(int code, const char* description);
    static void GlfwWindowCloseCallback(GLFWwindow* window);

    static void InitialiseGlfw();

private:
    unsigned int m_width, m_height;
    std::string m_title;

    GLFWwindow* m_handle;

    static unsigned int s_glfw_references;
};

} // vulren

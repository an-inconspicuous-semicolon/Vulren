//
// Created by reece on 02/11/2023.
//

#include "Vulren/Instance.hpp"

namespace vulren
{

Instance::Instance()
= default;

Instance::~Instance()
= default;


Result<Handle<Window>> Instance::create_window(unsigned int width, unsigned int height, std::string&& title)
{
    Window* window;
    try
    {
        window = new Window(width, height, std::forward<std::string>(title));
    } catch (std::exception& exception)
    {
        return cpp::fail(new Error("Failed to create window", exception.what()));
    }

    m_resources.push_back(window);
    return create_handle<Window>(window);
}

void Instance::handle_events()
{
    Window::PollEvents();
}
} // vulren
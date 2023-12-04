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

Result<Handle<Window>> Instance::create_window(const Window::Descriptor& descriptor)
{
    Window* window;
    try
    {
        window = new Window(descriptor);
    }
    catch (std::exception& exception)
    {
        return cpp::fail(new Error("Failed to create window", exception.what()));
    }

    m_resources.push_back(window);
    return create_handle<Window>(window);
}

void Instance::handle_events() // NOLINT(*-convert-member-functions-to-static)
{
    Window::PollEvents();
}
} // vulren
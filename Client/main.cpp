//
// Created by reece on 01/11/2023.
//

#include "Vulren/vulren.hpp"
#include <iostream>


int main()
{
    vulren::Instance instance;

    vulren::Window::Descriptor window_desc{};
    window_desc.width = 640;
    window_desc.height = 480;
    window_desc.title = "Hello, World!";
    window_desc.fullscreen = false;


    auto window_result = instance.create_window(window_desc);
    if (window_result.has_error())
    {
        throw window_result.error()
                           ->as_exception();
    }


    vulren::Handle<vulren::Window> window = window_result.value();

    vulren::Window::EventType::KeyboardChar func = [](vulren::Window& window, unsigned int codepoint)
    {
        std::cout << (char) codepoint;
        if (codepoint == '[') window.close();
    };
    window->add_keyboard_char_callback(func);

    while (window->is_open())
    {
        instance.handle_events();
    }
}

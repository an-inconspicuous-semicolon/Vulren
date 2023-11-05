//
// Created by reece on 01/11/2023.
//

#include "Vulren/vulren.hpp"


int main()
{
    vulren::Instance instance;
    auto window_result = instance.create_window(640, 480, "Hello, World!");
    if (window_result.has_error())
    {
        throw window_result.error()
                           ->as_error();
    }

    vulren::Handle<vulren::Window> window = window_result.value();

    while (window->is_open())
    {
        instance.handle_events();
    }
}
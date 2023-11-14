//
// Created by reece on 02/11/2023.
//

#pragma once

#include "Vulren/ResourceManager.hpp"
#include "Vulren/Window.hpp"
#include "Vulren/Result.hpp"

namespace vulren
{

class Instance
        : ResourceManager
{
public:
    Instance();
    ~Instance();

    Result<Handle<Window>> create_window(const Window::Descriptor& descriptor);

    void handle_events();

};


} // vulren

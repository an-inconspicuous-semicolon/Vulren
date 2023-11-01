//
// Created by reece on 01/11/2023.
//

#include "Vulren/vulren.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

int main()
{
    auto logger = spdlog::stdout_color_st("some name");

    vulren::set_logger(logger);

    vulren::say_hello();
}
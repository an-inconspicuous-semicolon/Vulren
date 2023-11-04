//
// Created by reece on 01/11/2023.
//

#pragma once

#include <memory>
#include <spdlog/logger.h>


namespace vulren
{
void set_logger(std::shared_ptr<spdlog::logger>& logger);
}
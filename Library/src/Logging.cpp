//
// Created by reece on 01/11/2023.
//

#include <spdlog/spdlog.h>

#include "Vulren/Logging.hpp"
#include "internal/Logging.hpp"

namespace vulren
{

std::shared_ptr<spdlog::logger> spdlog_logger = nullptr;

std::shared_ptr<spdlog::logger> get_logger()
{
    if (!spdlog_logger)
    { return spdlog::default_logger(); }
    else
    { return spdlog_logger; }
}

void set_logger(std::shared_ptr<spdlog::logger>& logger)
{
    spdlog_logger = logger;
}

void internal::log_info(std::string_view message)
{
    get_logger()->info(message);
}

void internal::log_warning(std::string_view message)
{
    get_logger()->warn(message);
}

void internal::log_error(std::string_view message)
{
    get_logger()->error(message);
}

void internal::log_fatal(std::string_view message)
{
    get_logger()->critical(message);
}

}
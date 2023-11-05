//
// Created by reece on 01/11/2023.
//

#include <spdlog/spdlog.h>

#include "Vulren/Logging.hpp"
#include "internal/Logging.hpp"

namespace vulren
{

std::shared_ptr<spdlog::logger> spdlog_logger = nullptr;

void set_logger(std::shared_ptr<spdlog::logger>& logger)
{
    spdlog_logger = logger;
}

void internal::log_info(std::string_view message)
{
    if (!spdlog_logger)
    { spdlog::default_logger_raw()->info(message); }
    else
    { spdlog_logger->info(message); }
}

void internal::log_warning(std::string_view message)
{
    if (!spdlog_logger)
    { spdlog::default_logger_raw()->warn(message); }
    else
    { spdlog_logger->warn(message); }
}

void internal::log_error(std::string_view message)
{
    if (!spdlog_logger)
    { spdlog::default_logger_raw()->error(message); }
    else
    { spdlog_logger->error(message); }
}

void internal::log_fatal(std::string_view message)
{
    if (!spdlog_logger)
    { spdlog::default_logger_raw()->critical(message); }
    else
    { spdlog_logger->critical(message); }
}

}
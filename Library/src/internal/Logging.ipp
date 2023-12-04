//
// Created by reece on 01/11/2023.
//

#pragma once

#include "Vulren/Result.hpp"


namespace vulren::internal
{

void log_info(std::string_view message);
void log_warning(std::string_view message);
void log_error(std::string_view message);
void log_fatal(std::string_view message);

template <typename T>
void log_result_on_fail(const Result<T> result)
{
    if (!result.has_error())
    { return; }
    Message& message = result.error();

    switch (message.severity())
    {
        case Message::Severity::Information:
            log_info(message.str());
            break;
        case Message::Severity::Warning:
            log_warning(message.str());
            break;
        case Message::Severity::Error:
            log_error(message.str());
            break;
        case Message::Severity::Fatal:
            log_fatal(message.str());
            break;
    }
}
}


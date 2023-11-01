//
// Created by reece on 01/11/2023.
//

#include "Vulren/Message.hpp"
#include <filesystem>
#include <sstream>

namespace vulren
{


Message::Message(std::string name, std::string description, std::source_location location)
        : m_name(std::move(name)),
          m_description(std::move(description)),
          m_location(location)
{
}

std::string vulren::Message::get_file_name() const
{
    std::filesystem::path file_path(m_location.file_name());
    return file_path.filename().string();
}

Message::operator std::string() const noexcept
{
    return str();
}

std::string Message::str() const noexcept
{
    std::ostringstream oss;

    oss << "[message]";
#ifdef _DEBUG
    oss << " (" << get_file_name() << " > " << m_location.function_name() << ":" << m_location.line() << ')';
#endif
    oss << m_name << " - " << m_description;

    return oss.str();
}

Message::Severity Message::severity() const noexcept
{
    return Message::Severity::Information;
}

std::string Information::str() const noexcept
{
    std::ostringstream oss;

    oss << "[info]";
#ifdef _DEBUG
    oss << " (" << get_file_name() << " > " << m_location.function_name() << ":" << m_location.line() << ')';
#endif
    oss << m_name << " - " << m_description;

    return oss.str();
}

Message::Severity Information::severity() const noexcept
{
    return Message::Severity::Information;
}

std::string Warning::str() const noexcept
{
    std::ostringstream oss;

    oss << "[warning]";
#ifdef _DEBUG
    oss << " (" << get_file_name() << " > " << m_location.function_name() << ":" << m_location.line() << ')';
#endif
    oss << m_name << " - " << m_description;

    return oss.str();
}

Message::Severity Warning::severity() const noexcept
{
    return Message::Severity::Warning;
}

std::string Error::str() const noexcept
{
    std::ostringstream oss;

    oss << "[ERROR]";
#ifdef _DEBUG
    oss << " (" << get_file_name() << " > " << m_location.function_name() << ":" << m_location.line() << ')';
#endif
    oss << m_name << " - " << m_description;

    return oss.str();
}

Message::Severity Error::severity() const noexcept
{
    return Message::Severity::Error;
}

std::string Fatal::str() const noexcept
{
    std::ostringstream oss;

    oss << "[--FATAL--]";
#ifdef _DEBUG
    oss << " (" << get_file_name() << " > " << m_location.function_name() << ":" << m_location.line() << ')';
#endif
    oss << m_name << " - " << m_description;

    return oss.str();
}

Message::Severity Fatal::severity() const noexcept
{
    return Message::Severity::Fatal;
}

}
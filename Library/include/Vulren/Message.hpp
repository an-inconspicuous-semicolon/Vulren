//
// Created by reece on 01/11/2023.
//

#pragma once

#include <string>
#include <source_location>

namespace vulren
{

class Message
{
public:

    enum class Severity
    {
        Information = 0,
        Warning,
        Error,
        Fatal
    };

public:
    Message(std::string name, std::string description, std::source_location location = std::source_location::current());
    virtual ~Message() = default;

    virtual std::string str() const noexcept;
    explicit operator std::string() const noexcept;

    virtual Severity severity() const noexcept;

protected:
    std::string get_file_name() const;

protected:
    std::string m_name;
    std::string m_description;
    std::source_location m_location;
};

std::ostream& operator<<(std::ostream& stream, const Message& message);

class Information
        : public Message
{
public:
    using Message::Message;
    std::string str() const noexcept override;
    Severity severity() const noexcept override;
};

class Warning
        : public Message
{
public:
    using Message::Message;
    std::string str() const noexcept override;
    Severity severity() const noexcept override;
};

class Error
        : public Message
{
public:
    using Message::Message;
    std::string str() const noexcept override;
    Severity severity() const noexcept override;
};

class Fatal
        : public Message
{
public:
    using Message::Message;
    std::string str() const noexcept override;
    Severity severity() const noexcept override;
};

}
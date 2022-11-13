#pragma once

#include <string>
#include <exception>

class ParseException : public std::exception
{
private:
    std::string msg;

public:
    ParseException(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

class IllegalStateException : public std::exception
{
private:
    std::string msg;

public:
    IllegalStateException(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

class UnsupportedOperationException : public std::exception
{
private:
    std::string msg;

public:
    UnsupportedOperationException(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

class IOException : public std::exception
{
private:
    std::string msg;

public:
    IOException(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

class InterruptedException : public std::exception
{
private:
    std::string msg;

public:
    InterruptedException(const std::string &message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};

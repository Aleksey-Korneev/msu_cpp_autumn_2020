#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <typeinfo>

class InvalidFormat : std::exception
{
    std::string message;
public:
    explicit InvalidFormat(const std::string&);
    const char * what() const noexcept override
    {
        return message.c_str();
    }
};

class InvalidValue : std::exception
{
    std::string message;
public:
    explicit InvalidValue(const std::string&);
    const char * what() const noexcept override
    {
        return message.c_str();
    }
};

void unpack_template_args(std::vector<std::string>&);

template<class T>
void unpack_template_args(std::vector<std::string>&, const T&);

template<class T, class... Args>
void unpack_template_args(std::vector<std::string>&, const T&, const Args&...);

template<class... Args>
std::string format(const std::string&, const Args&...);

#include "impl/format.tpp"

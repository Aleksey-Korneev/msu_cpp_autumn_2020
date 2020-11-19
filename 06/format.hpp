#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <typeinfo>

class InvalidFormat : std::exception
{
    std::string message;
public:
    InvalidFormat(const std::string& message_): message(message_)
    {
    }
    const char * what() const noexcept
    {
        return message.c_str();
    }
};

class RuntimeError : std::exception
{
    std::string message;
public:
    RuntimeError(const std::string& message_): message(message_)
    {
    }
    const char * what() const noexcept
    {
        return message.c_str();
    }
};

void unpack_template_args(std::vector<std::string>&)
{
}

template<class T>
void unpack_template_args(std::vector<std::string>& template_args, T&& arg)
{
    std::stringstream s;
    s << std::forward<T>(arg);
    if (!s) {
        std::stringstream message;
        message << "No match for \'operator<<\' (operand types are \'";
        message << typeid(s).name();
        message << "\' and \'";
        message << typeid(arg).name();
        message << "\'."; 
        throw RuntimeError(message.str());
    }
    std::string str_arg;
    str_arg = s.str();
    template_args.push_back(str_arg);
}

template<class T, class... Args>
void unpack_template_args(std::vector<std::string>& template_args, T&& arg, Args&&... args)
{
    unpack_template_args(template_args, std::forward<T>(arg));
    unpack_template_args(template_args, std::forward<Args>(args)...);
}

template<class... Args>
std::string format(const std::string& str, Args&&... args)
{
    std::vector<std::string> template_args;
    unpack_template_args(template_args, std::forward<Args>(args)...);
    std::ostringstream res;
    size_t opening_brace = str.find("{", 0);
    size_t closing_brace = str.find("}", 0);
    size_t pos = 0;
    while (opening_brace != std::string::npos && closing_brace != std::string::npos) {
        if (opening_brace > closing_brace) {
            throw InvalidFormat("Unexpected closing brace.");
        }
        if (str.find("{", opening_brace + 1) < closing_brace) {
            throw InvalidFormat("Unexpected opening brace.");
        }   
        res << str.substr(pos, opening_brace - pos);
        int arg_num;
        try {
            arg_num = stoi(str.substr(opening_brace + 1, closing_brace - 1 - opening_brace));
        } catch (const std::invalid_argument& e) {
            throw InvalidFormat("Invalid index.");
        }
        if (arg_num < 0 || static_cast<size_t>(arg_num) >= template_args.size()) {
            throw InvalidFormat("Argument index out of range.");
        }
        res << template_args[arg_num];
        pos = closing_brace + 1;
        opening_brace = str.find("{", opening_brace + 1);
        closing_brace = str.find("}", closing_brace + 1);
    }
    if (opening_brace == std::string::npos && closing_brace == std::string::npos) {
        res << str.substr(pos, str.size() - pos);
        return res.str();
    } else if (opening_brace == std::string::npos) {
        throw InvalidFormat("Unexpected closing brace.");
    } else {
        throw InvalidFormat("Unexpected opening brace.");
    }
}

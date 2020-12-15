#pragma once
#include <iostream>
#include <sstream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    std::ostream& out;
    static constexpr char Separator = ' ';

    template<class T>
    Error process(T&)
    {
        return Error::CorruptedArchive;
    }

    Error process(bool val)
    {
        out << (val? "true" : "false");
        return Error::NoError;
    }

    Error process(uint64_t val)
    {
        out << val;
        return Error::NoError;
    }

    template<class T, class... ArgsT>
    Error process(T&& val, ArgsT&&... args)
    {
        if (process(val) == Error::NoError) {
            out << Separator;
            return process(args...);
        }
        return Error::CorruptedArchive;
    }

public:
    explicit Serializer(std::ostream& out_)
        : out(out_)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }
};


class Deserializer
{
    std::istream& input;
    
    template<class T>
    Error process(T&&)
    {
        return Error::CorruptedArchive;
    }

    Error process(bool& val)
    {
        std::string str;
        input >> str;
        if (str == "true") {
            val = true;
        } else if (str == "false") {
            val = false;
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    Error process(uint64_t& val)
    {
        std::string str;
        input >> str;
        try {
            val = std::stoull(str);
        } catch (const std::exception&) {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template<class T, class... ArgsT>
    Error process(T&& val, ArgsT&&... args)
    {
        if (process(std::forward<T>(val)) == Error::NoError) {
            return process(std::forward<ArgsT>(args)...);
        }
        return Error::CorruptedArchive;
    }

public:
    explicit Deserializer(std::istream& input_)
        : input(input_)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&&... args)
    {
        return process(std::forward<ArgsT>(args)...);
    }
};

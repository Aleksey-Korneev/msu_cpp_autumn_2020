#include "serializer.hpp"
#include <cassert>

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

struct UnsuppportedData
{
    uint64_t a;
    double b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

struct ShuffledData
{
    uint64_t a;
    uint64_t b;
    bool c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }
};

//Serializing and deserializing supported data
void test1()
{
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

//Serializing unsupported data
void test2()
{
    UnsuppportedData x { 1, 1.5, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    const Error err = serializer.save(x);

    assert(err == Error::CorruptedArchive);
}

//Deserializing unsupported data
void test3()
{
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    UnsuppportedData y { 0, 0.0, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::CorruptedArchive);
}


//Deserializing shuffled data
void test4()
{
    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    ShuffledData y { 0, 0, false };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::CorruptedArchive);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    std::cout << "All tests passed." << std::endl;
    return 0;
}

#include <iostream>
#include <cassert>
#include <sstream>
#include "task4.h"

struct Data{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error Serialize(Serializer& serializer){
        return serializer(a, b, c);
    }
};

int main(){
    Data x { 1, true, 2 };
    std::stringstream stream;
    Serializer serializer(stream);
    serializer.Save(x);

    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.Load(y);

    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}
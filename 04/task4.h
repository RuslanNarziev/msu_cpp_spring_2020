#pragma once
#include <iostream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer {
    static constexpr char Separator = ' ';
    std::ostream & output;
public:
    explicit Serializer(std::ostream & out): output(out) {}

    template <class T>
    Error Save(T & object) const {
        return object.Serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args) const {
        return Process(args...);
    } 
    
private:
    template<class T>
    Error Process(T& val) const {
        return Error::CorruptedArchive;
    } 
    
    template <class T, class... Args>
    Error Process(T&& val, Args&&... args) const {
        Process(val);
        return Process(args...);
    }

    Error Process(uint64_t & val) const {
        output << val << Separator;
        return Error::NoError;
    }
    Error Process(bool & val) const {
        if (val) {
            output << "true" << Separator;
        } else {
            output << "false" << Separator;
        }
        return Error::NoError;
    }
};

class Deserializer {
    static constexpr char Separator = ' ';
    std::istream & input;
public:
    explicit Deserializer(std::istream & in): input(in) {}

    template <class T>
    Error Load(T & object) const {
        return object.Serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&...  args) const {
        return Process(args...);
    }
    
private:
    template<class T>
    Error Process(T & val) const {
        return Error::CorruptedArchive;
    }
    
    template <class T, class... Args>
    Error Process(T&& val, Args&&... args) const {
        Process(val);
        return Process(args...);
    }

    Error Process(uint64_t & val) const {
        std::string word;
        input >> word;
        uint64_t res = atoll(word.data());
        if(res) {
            val = res;
            return Error::NoError;
        } 
        return Error::CorruptedArchive;
    }
    Error Process(bool & val) const {
        std::string word;
        input >> word;
        if (word == "true")
            val = true;
        else if (word == "false")
            val = false;
        else
            return Error::CorruptedArchive;
        return Error::NoError;
    }
};
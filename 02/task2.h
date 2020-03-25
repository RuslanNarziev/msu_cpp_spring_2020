#pragma once
#include <iostream>

using On_number = void (*)(int num);
using On_string = void (*)(char* str);
using On_void = void (*)();

class Parser {
    On_number Call_num;
    On_string Call_str;
    On_void Call_beg;
    On_void Call_end;
public:
    Parser(On_number Call_num, On_string Call_str, On_void Call_beg, On_void Call_end);
    void Parse(const char* text);
    void Set_Call_num(On_number Call_num);
    void Set_Call_str(On_string Call_str);
    void Set_Call_beg(On_void Call_beg);
    void Set_Call_end(On_void Call_end);
};
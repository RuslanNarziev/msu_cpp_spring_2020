#include "task2.h"

void Call_num(int num) {
    std::cout << "This is number " << num << "\n";
}

void Call_str(char* str) {
    std::cout << "This is string " << str;
}

int main() {
    char* text = "asd1 1 asd 2                 dsa";
    std::cout << "Source text: " << text << "\n";
    Parser Ps(Call_num, Call_str, 0, 0);
    Ps.Parse(text);
    return 0;
}
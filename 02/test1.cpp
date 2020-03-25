#include "task2.h"

void Call_num(int num) {
    std::cout << "This is number " << num << "\n";
}

void Call_str(char* str) {
    std::cout << "This is string " << str << "\n";
}

void Call_beg() {
    std::cout << "Begining of parsing\n";
}

void Call_end() {
    std::cout << "End of parsing\n";
}

int main() {
    char* text = "asd 1 asd 2 \ndsa";
    std::cout << "Source text: " << text << "\n";
    Parser Ps(Call_num, Call_str, Call_beg, Call_end);
    Ps.Parse(text);
    return 0;
}
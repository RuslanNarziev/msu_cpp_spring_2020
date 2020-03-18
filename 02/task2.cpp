#include "task2.h"
#include <cstdlib>
#include <string.h>

void Parser::Parse(const char* text) {
    bool is_num = true;
    bool is_word = false;
    char* word;
    const char* word_begin = text;
    char c;
    if(Call_beg)
        Call_beg();
    do {
        c = *text++;
        if((c == '\t') || (c == '\n') || (c == ' ') || (c == '\0')) {
            if(is_word) {
                word = (char*) malloc(text - word_begin);
                memcpy(word, word_begin, text - word_begin - 1);
                word[text - word_begin - 1] = '\n';
                if(is_num) {
                    if(Call_num)
                        Call_num(atoi(word));
                } else
                    if(Call_str)
                        Call_str(word);
                free(word);
            } word_begin = text;
            is_num = true;  
            is_word = false;
        } else {
            is_word = true;
            if((c < '0') || (c > '9')) 
                is_num = false;
        }
    } while(c);
    if(Call_end)
        Call_end();
}

Parser::Parser(On_number Call_num, On_string Call_str, On_void Call_beg, On_void Call_end) {
    this->Call_beg = Call_beg;
    this->Call_end = Call_end; 
    this->Call_num = Call_num;
    this->Call_str = Call_str;
}
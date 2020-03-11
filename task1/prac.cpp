#include <string.h>
#include <cstdlib>
#include <stdio.h>

class Student {
    char* surname;
    char* name;
    int note_5, note_4, note_3;
public:
    long id;
    Student(char* str1, char*str2, long _id, int n5, int n4, int n3);
    Student(const Student & B);
    ~Student();
    double Mean() const;
    Student operator++(int);
    Student & operator++();
};

int main() {
    Student V = Student("Pogosyan", "Vovan", 666, 2, 3, 10);
    Student R = V;
    ++++R;
    printf("%f, %d\n", R.Mean(), R.id);
    
}

Student::Student(const Student & B) {
    surname = new char(strlen(B.surname) + 1);
    strcpy(surname, B.surname);
    name = new char(strlen(B.name) + 1);
    strcpy(name, B.name);
    id = B.id;
    note_5 = B.note_5;
    note_4 = B.note_4;
    note_3 = B.note_3;
}

Student::~Student() {
    free(surname);
    free(name);
}

Student::Student(char* str1, char*str2, long _id, int n5, int n4, int n3) {
    surname = new char(strlen(str1) + 1);
    strcpy(surname, str1);
    name = new char(strlen(str2) + 1);
    strcpy(name, str2);
    id = _id;
    note_5 = n5;
    note_4 = n4;
    note_3 = n3;
}

double Student::Mean() const {
    return (double)(5 * note_5 + 4 * note_4 + 3 * note_3) / (note_5 + note_4 + note_3);
}

Student Student::operator++(int) {
    Student temp(*this);
    id++;
    return temp;
}

Student & Student::operator++() {
    id++;
    return *this;
}
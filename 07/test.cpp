#include "task7.h"

int main() {
    vector<int> arr(5);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.pop_back();
    for(size_t i = 0; i < arr.size(); i++)
        std::cout << arr[i];

    std::cout << std::endl << *++arr.rbegin() << std::endl;

    arr.resize(5);
    arr.resize(7, 9);
    for(size_t i = 0; i < arr.size(); i++)
        std::cout << arr[i];

    std::cout << std::endl <<  arr.empty();
    arr.clear();
    std::cout << arr.empty();
}
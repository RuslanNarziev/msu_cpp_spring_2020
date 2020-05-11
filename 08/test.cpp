#include "task8.h"
#include <iostream>
#include <cassert>

struct A {
    int value;
};

int get_value(const A& a) { return a.value; }
int main(){
    ThreadPool pool(3);
    auto task1 = pool.exec(get_value, A{1});
    assert(task1.get() == 1);

    for(int i = 0; i < 10; ++i) {
        auto task = pool.exec([i](){ return i; });
        assert(task.get() == i);
    }
    std::cout << "Correct";
    return 0;
}
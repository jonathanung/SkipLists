#include "SkipList.hpp"
#include <iostream>
#include <cstdlib>

int main(){
    srand(time(0));
    SkipList sL = SkipList();
    sL.insertValue(3);
    sL.insertValue(5);
    sL.insertValue(2);
    sL.insertValue(7);
    sL.insertValue(6);
    sL.insertValue(13);
    sL.insertValue(7);
    sL.insertValue(11);
    sL.insertValue(1);
    sL.insertValue(5);
    sL.insertValue(19);
    sL.insertValue(313);
    sL.insertValue(37);
    sL.insertValue(311);
    sL.insertValue(31);
    sL.insertValue(35);
    sL.insertValue(319);
    sL.insertValue(5);
    std::cout << "-------------INIT LIST-------------" << std::endl;
    std::cout << sL;
    // sL.show();
    bool found = sL.search(11);
    std::cout << "result search 11: " << found << std::endl;
    found = sL.search(99);
    std::cout << "result search 99: " << found << std::endl;
    std::cout << "-------------REMOVE 19-------------" << std::endl;
    sL.remove(19);
    std::cout << sL;
    std::cout << "-------------REMOVEH 7-------------" << std::endl;
    sL.removeHighest(7);
    std::cout << sL;
    std::cout << "-------------REMOVEH 7-------------" << std::endl;
    sL.removeHighest(7);
    std::cout << sL;
    std::cout << "-------------REMOVEF 5-------------" << std::endl;
    sL.removeFirst(5);
    std::cout << sL;
    std::cout << "-------------REMOVEF 5-------------" << std::endl;
    sL.removeFirst(5);
    std::cout << sL;
    std::cout << "-------------REMOVEF 5-------------" << std::endl;
    sL.removeFirst(5);
    std::cout << sL;
    return 0;
}
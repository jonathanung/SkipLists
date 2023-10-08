#include "DSkipList.hpp"
#include <iostream>
#include <cstdlib>

int main(){
    srand(time(0));
    DSkipList dSL = DSkipList();
    dSL.insertValue(3);
    std::cout << dSL;
    dSL.insertValue(5);
    dSL.insertValue(2);
    dSL.insertValue(7);
    dSL.insertValue(6);
    dSL.insertValue(13);
    dSL.insertValue(7);
    dSL.insertValue(11);
    dSL.insertValue(1);
    dSL.insertValue(5);
    dSL.insertValue(19);
    dSL.insertValue(313);
    dSL.insertValue(37);
    dSL.insertValue(311);
    dSL.insertValue(31);
    dSL.insertValue(35);
    dSL.insertValue(319);
    dSL.insertValue(5);
    std::cout << "-------------INIT LIST-------------" << std::endl;
    std::cout << dSL;
    std::cout << "-------------INIT LIST BACK-------------" << std::endl;
    dSL.showBack();
    // dSL.show();
    bool found = dSL.search(11);
    std::cout << "result search 11: " << found << std::endl;
    found = dSL.search(99);
    std::cout << "result search 99: " << found << std::endl;
    found = dSL.search(311);
    std::cout << "result search 311: " << found << std::endl;
    found = dSL.search(309);
    std::cout << "result search 309: " << found << std::endl;
    std::cout << "-------------REMOVEH 19-------------" << std::endl;
    dSL.remove(19);
    std::cout << dSL;
    std::cout << "-------------REMOVEH 7-------------" << std::endl;
    dSL.remove(7);
    std::cout << dSL;
    std::cout << "-------------REMOVEH 7-------------" << std::endl;
    dSL.remove(7);
    std::cout << dSL;
    std::cout << "-------------REMOVEF 5-------------" << std::endl;
    dSL.removeFirst(5);
    std::cout << dSL;
    std::cout << "-------------REMOVEL 5-------------" << std::endl;
    dSL.removeLast(5);
    std::cout << dSL;
    std::cout << "-------------REMOVEF 5-------------" << std::endl;
    dSL.removeFirst(5);
    std::cout << dSL;
    std::cout << "-------------FINAL LIST BACK-------------" << std::endl;
    dSL.showBack();
    return 0;
}
#include <iostream>
#include "red_back.h"
using namespace std;

int main(){
    red_black<int> numbers;
    numbers.insert(3);
    numbers.insert(2);
    numbers.insert(1);
    numbers.print();
    return 0;
}
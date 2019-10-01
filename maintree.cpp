#include <iostream>
#include "tree.h"
#include <random>
using namespace std;

int main(){
    tree<int> numbers;
    numbers.insert(3);
    numbers.insert(9);
    numbers.insert(1);
    numbers.insert(2);
    numbers.insert(15);
    numbers.insert(7);
    //cout << numbers.search(3);
    tree<int>::iterator it = numbers.begin();
    ListaDesordenada<int> lista;
    for(;it!=numbers.end();++it)
        lista.insertLast(*it);
    lista.print();
    return 0;   
}
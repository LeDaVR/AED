#include <iostream>
#include "list.h"
using namespace std;

int main(){
    list<int> lista;
    lista.insert(4);
    list<int>::iterator it = lista.begin();
    lista.insert(5,it);
    lista.insert(1,it);
    lista.print();
    return 0;
}



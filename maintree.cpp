#include <iostream>
#include "tree.h"
#include <random>
using namespace std;

int randomInteger(int min, int max){
    return rand() % (max-min+1) + min;
}

int main(){
    tree<int> numbers;
    /*numbers.insert(6);
    numbers.insert(4);
    numbers.insert(5);
    numbers.insert(1);
    numbers.insert(8);
    cout << numbers.search(1) << endl;
    numbers.remove(1);
    cout << numbers.search(1) << endl;
    cout << numbers.search(6) << endl;
    numbers.remove(6);
    cout << numbers.search(6) << endl;
    numbers.insert(1);
    cout << numbers.search(1) << endl;*/
    long long int iteraciones = 0;
    int cont=0;
    bool arr[100] = {false};
    while(cont!=100){
        int random = randomInteger(1,100);
        if ( !arr[random-1] )
        {   
            numbers.insert(random);
            arr[random-1] = true;
            cont++;
        }
        iteraciones++;
    }
    cout << iteraciones<<endl;
    /*for(int i = 1 ; i <= 100 ; i++)
        cout << numbers.search(i) << endl;*/
    return 0;
}
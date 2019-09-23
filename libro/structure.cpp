#include <iostream>
#include "nodo.h"
using namespace std;

template <class T>
class Stack{
    public:
        Stack(){
            first = nullptr;
            aux = nullptr;
            minimo = nullptr;
            size=0;
        }
        void push(T data){
            Nodo<T>* newNode= new Nodo<T>;
            newNode->link = nullptr ;
            newNode->data = data ;
            if(size==0){
                newNode->prev_link = nullptr;
                first=newNode;
                Nodo<T>* newMin = new Nodo<T>;
                newMin ->data = data;
                newMin ->link = nullptr ;
                newMin -> prev_link = nullptr;
                minimo = newMin;
            }
            else{
                aux->link=newNode;
                newNode->prev_link = aux;
                if(newNode->data < minimo->data){
                    Nodo<T>* newMin = new Nodo<T>;
                    newMin->data  = data;
                    minimo->link = newMin;
                    newMin->prev_link = minimo;
                    newMin->link = nullptr;
                    minimo = minimo->link;
                }         
            }
            aux=newNode;
            size++;
        }
        void pop(){
            if(!size)
                return;
            if(size==1){
                first=nullptr;
                delete aux;
                aux=nullptr;
                delete minimo;
                minimo = nullptr;
            }
            else{
                Nodo<T>* temp = aux;
                aux = aux->prev_link;
                delete temp;
                aux->link = nullptr;
                if(minimo->data==aux->data){
                    Nodo<T>* popaux = minimo;
                    minimo = minimo->prev_link;
                    delete popaux;
                    minimo->link = nullptr; 
                }
            }
            size--;
        }
        T top(){
            return aux->data;
        }
        T findMin(){
            return minimo->data;
        }
        ~Stack(){
            Nodo<T>* temp = first;
            Nodo<T>* aux2 = temp;
            while(temp){
                temp = temp->link ;
                delete aux2;
                aux2 = temp;
            }
            temp = minimo;
            aux2 = temp;
            while(minimo){
                temp = temp->prev_link;
                delete aux2;
                aux2 = temp;
            }
        }
    private:
        Nodo<T>* first;
        Nodo<T>* aux;
        int size;
        Nodo<T>* minimo;
};


long fib( int n )
{
    if( n <= 1 )
        return 1;
    else
        return fib( n - 1 ) + fib( n - 2 );
}

int main(){
    cout<<fib(49);
    return 0;
}
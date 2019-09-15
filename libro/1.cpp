#include <iostream>
#include "listaordenada.h"
#include "listadesordenada.h"
#include "doublelinkedlist.h"

using namespace std;


template <class T>
void printLots(ListaOrdenada<T> a, ListaOrdenada<T> b){
	for(linkedListIterator<T> b_it=b.begin();b_it!=b.end();++b_it){
		if(*b_it<a.length()){
			int cont=*b_it;
			linkedListIterator<T> a_it=a.begin();
			while(cont){
				++a_it;
				cont--;
			}
			cout << *a_it << " ";
		}
		else
			break;
	}
}

template <typename T>
linkedListIterator<T> find( linkedListIterator<T> begin, linkedListIterator<T> end, const T x ){
	for(linkedListIterator<T> temp = begin; temp !=end ; ++temp){
		if(x==*temp)
			return temp;
	}
	return end;
}

template <class T>
ListaOrdenada<T> interseccion(ListaOrdenada<T> a,ListaOrdenada<T> b){
	linkedListIterator<T> a_it = a.begin();
	linkedListIterator<T> b_it = b.begin();
	for(a_it,b_it;a_it!=a.end()||b_it!=b.end();)
}

int main(){
	ListaDesordenada<int> unordered;
	unordered.insertLast(1);
	unordered.insertLast(2);
	unordered.insertLast(3);
	unordered.insertLast(4);
	
	ListaOrdenada<int> a;
	ListaOrdenada<int> b;
	a.insert(1);
	a.insert(2);
	a.insert(3);
	a.insert(4);
	a.insert(5);
	a.insert(6);
	b.insert(0);
	b.insert(2);
	b.insert(3);
	//printLots(a,b);
	
	doubleLinkedList<int> doble;
	doble.insertFirst(1);
	doble.insertFirst(2);

	cout << "swap : "<<endl;
	unordered.swap(1,0);
	unordered.print();
	doble.swap(0,1);
	doble.print();
	find(a.begin(),a.end(),3);
	return 0;	
}


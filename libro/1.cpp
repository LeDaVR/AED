#include <iostream>
#include "listaordenada.h"
#include "listadesordenada.h"
#include "doublelinkedlist.h"
#include <list>
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
	ListaOrdenada<T> temp;
	for(linkedListIterator<T> i=a.begin();i!=a.end();++i){
		if(b.search(*i))
			temp.insert(*i);
	}
	return temp;
}

template <class T>
ListaOrdenada<T> combine(ListaOrdenada<T> a,ListaOrdenada<T> b){
	ListaOrdenada<T> temp;
	for(linkedListIterator<T> i=a.begin();i!=a.end();++i){
		if(!temp.search(*i))
			temp.insert(*i);
	}
	for(linkedListIterator<T> i=b.begin();i!=b.end();++i){
		if(!temp.search(*i))
			temp.insert(*i);
	}
	return temp;
}


void play(int numberofplayers,int pivote){
	ListaDesordenada<int> jugadores;
	for(int i=0;i<numberofplayers;i++)
		jugadores.insertLast(i+1);
	int contador=0;
	linkedListIterator<int> it=jugadores.begin();
	while(jugadores.length()!=1){
		contador=contador+pivote;
		it=jugadores.begin();
		if(contador>=jugadores.length())
			contador%=jugadores.length();
		for(int i=0;i<contador;i++)
			++it;
		jugadores.deleteNode(*it);
	}
	it=jugadores.begin();
	cout<<"el ganador es " << *it <<endl;
}

// 3.9
// cuando hacemos uso de push pop insert o erase se redimensiona el vector por lo que la direccion del vector cambia, pero los iteradores actuales aun apuntan a la direccion antigua por eso se invalidan.



int main(){
	ListaDesordenada<int> unordered;
	unordered.insertLast(1);
	unordered.insertLast(2);
	unordered.insertLast(8);
	unordered.insertLast(9);
	
	ListaDesordenada<int> unordered2;
	unordered2.insertLast(3);
	unordered2.insertLast(4);
	unordered2.insertLast(5);
	unordered2.insertLast(6);
	unordered2.insertLast(7);

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
	doble.insertFirst(3);
	doble.insertFirst(4);

	cout << "swap : "<<endl;
	unordered.swap(1,0);
	unordered.print();
	doble.swap(0,1);
	doble.print();
	find(a.begin(),a.end(),3);
	cout<<endl;
	
	ListaOrdenada<int> comunes;
	comunes = interseccion(a,b);
	comunes.print();
	cout<<endl;
	//play(50000,3);

	linkedListIterator<int> it=doble.begin();
	cout<<*it<<endl;
	++it;
	--it;
	cout<<*it<<endl;

	unordered.splice(1,unordered2);

	unordered.print();
	cout<< " iterador inverso "<<endl;
	doubleLinkedList<int>::reverse_iterator re = doble.rbegin();
	while( re != doble.rend() )
		cout << *re++ << endl;
	
	linkedListIterator<int> et=unordered.begin();
	if(et.isStole())
		cout<<"as"<<endl;
	unordered.deleteNode(2);
	if(et.isStole())
		cout<<"as"<<endl;
	cout<<"GG"<<endl;
	return 0;	
}


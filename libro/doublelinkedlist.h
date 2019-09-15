#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "linkedlist.h"

#include <iostream>
using namespace std;
template <class T>
class doubleLinkedList : linkedList<T>{
	public:
        void print(); 
		bool search(const T elemento) const;
		void insertFirst(const T item);
		void insertLast(const T item);
		void deleteNode(const T elemento);
        void swap(int pos1,int pos2);
		
};

template <class T>
void doubleLinkedList<T>::print(){
    Nodo<T> *current;
    current = this->first;
    while (current != NULL)
    {
        cout << current->data << " ";
        current = current->link;
    }
}


template <class T>
void doubleLinkedList<T>::swap(int pos1,int pos2){
    Nodo<T>* current=this->first;
    if(pos2>pos1){
        int temp=pos1;
        pos1=pos2;
        pos2=temp;
    }
    for(int i=0;i<pos1;i++)
        current=current->link;
    if(current==this->first){
        this->first=current->link;
        current->link=current->link->link;
        this->first->link=current;
        current->prev_link=this->first;
        this->first->prev_link=nullptr;
        current->link->prev_link=current;
    }


}

template <class T>
bool doubleLinkedList<T>::search(const T elemento) const
{
    Nodo<T> *current;
    bool found = false;
    current = this->first;
    while (current != NULL && !found)
        if (current->data == elemento)
            found = true;
        else
            current = current->link;
    return found;
}

template <class T>
void doubleLinkedList<T>::insertFirst(const T item)
{
    Nodo<T> *newNode;
    newNode = new Nodo<T>;
    newNode->data = item;
    newNode->link = this->first;
    newNode->prev_link = nullptr ;
    this->first = newNode;
    this->count++;
    if (this->last == NULL)
        this->last = newNode;
}

template <class T>
void doubleLinkedList<T>::insertLast(const T item)
{
    Nodo<T> *newNode;
    newNode = new Nodo<T>;
    newNode->data = item;
    newNode->link = NULL;
    newNode->prev_link = this->last;
    if (this->first == NULL)
    {
        this->first = newNode;
        this->last = newNode;
        this->count++;
    }
    else
    {
        this->last->link = newNode;
        this->last = newNode;
        this->count++;
    }
}

template <class T>
void doubleLinkedList<T>::deleteNode(const T elemento)
{
    /*Nodo<T> *current;
    Nodo<T> *aux;
    bool found;
    if (this->first == NULL) // si esta vacia
        cout << "La lista esta vacia no se puede borrar" << endl;
    else
    {
        if (this->first->data == elemento)
        {
            current = this->first;
            this->first = this->first->link;
            this->first->link_prev=nullptr;
            this->count--;
            if (this->first == NULL)
                this->last = NULL;
            delete current;
        }
        else
        {
            found = false;
            aux = this->first;
            current = this->first->link;
            while (current != NULL && !found)
            {
                if (current->data != elemento)
                {
                    aux = current;
                    current = current->link;
                }
                else
                    found = true;
            }
            if (found)
            {
                aux->link = current->link;
                this->count--;
                if (this->last == current)
                    this->last = aux;
                delete current;
            }
            else
                cout << "El elemento a borrar no esta en la lista" << endl;
        }
    }*/
}

#endif

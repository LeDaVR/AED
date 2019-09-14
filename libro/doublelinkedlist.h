#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "linkedlist.h"

template <class T>
class doubleLinkedList : linkedList<T>{
	public:
		bool search(const T elemento) const;
		void insertFirst(const T item);
		void insertLast(const T item);
		void deleteNode(const T elemento)
		
};

template <class T>
bool ListaDesordenada<T>::search(const T elemento) const
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
void ListaDesordenada<T>::insertFirst(const T item)
{
    Nodo<T> *newNode;
    newNode = new Nodo<T>;
    newNode->data = item;
    newNode->link = this->first;
    this->first = newNode;
    this->count++;
    if (this->last == NULL)
        this->last = newNode;
}

template <class T>
void ListaDesordenada<T>::insertLast(const T item)
{
    Nodo<T> *newNode;
    newNode = new Nodo<T>;
    newNode->data = item;
    newNode->link = NULL;
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
void ListaDesordenada<T>::deleteNode(const T elemento)
{
    Nodo<T> *current;
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
    }
}

#endif

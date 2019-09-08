
#ifndef UNORDEREDLINKEDLIST_H
#define UNORDEREDLINKEDLIST_H

#include <iostream>
#include "linkedList.h"

using namespace std;

template <class T>
class unorderedLinkedList : public linkedListType<T>
{
public:
    bool search(const T elemento) const;
    void insertFirst(const T item);
    void insertLast(const T item);
    void deleteNode(const T deleteItem);
};

template <class T>
bool unorderedLinkedList<T>::search(const T elemento) const
{
    nodeType<T> *current;
    bool found = false;
    current = this->first;
    while (current != NULL && !found)
        if (current->info == elemento)
            found = true;
        else
            current = current->link;
    return found;
}

template <class T>
void unorderedLinkedList<T>::insertFirst(const T item)
{
    nodeType<T> *newNode;
    newNode = new nodeType<T>;
    newNode->info = item;
    newNode->link = this->first;
    this->first = newNode;
    this->count++;
    if (this->last == NULL)
        this->last = newNode;
}

template <class T>
void unorderedLinkedList<T>::insertLast(const T item)
{
    nodeType<T> *newNode;
    newNode = new nodeType<T>;
    newNode->info = item;
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
void unorderedLinkedList<T>::deleteNode(const T elemento)
{
    nodeType<T> *current;
    nodeType<T> *aux;
    bool found;
    if (this->first == NULL) // si esta vacia
        cout << "La lista esta vacia no se puede borrar" << endl;
    else
    {
        if (this->first->info == elemento)
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
                if (current->info != elemento)
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
#ifndef NODO_H
#define NODO_H

template <class T>
struct Nodo
{
    T data;
    Nodo<T> *link;
    Nodo<T> *prev_link;
};


#endif

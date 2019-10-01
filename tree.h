#include <iostream>
#include "abstract.cpp"
using namespace std;


template <class T>
class tree
{
    public:
        class iterator{
            public:
                iterator(){
                    current =nullptr;
                }
                iterator(Nodo<T>* node){
                    current = node;
                }
                const T & operator*() const{
                    return current->data;
                }
                iterator & operator++(){
                    if(current->link)
                    {
                        current = current->link;
                        while(current->left)
                        {
                            current = current->left;
                        }
                    }
                    else if (current->parent)
                    {
                        Nodo<T>* help = current->parent;
                        while(help->data < current-> data && help->parent)
                        {
                            help = help->parent;
                        }
                        if(help->data > current->data )
                            current = help;
                        else
                            current = nullptr;
                    }
                    return *this;
                }
                iterator & operator--()
                {
                    if(current->left)
                    {
                        current = current->left;
                        while(current->link)
                        {
                            current = current->link;
                        }
                    }
                    else if (current->parent)
                    {
                        Nodo<T>* help = current->parent;
                        while(current-> data < help->data && help->parent)
                        {
                            help = help->parent;
                        }
                        if ( help->data < current->data )
                            current = help;
                    }
                    return *this;
                }
                bool operator!=(iterator  other)
                {
                    return current != other.current;
                }
                bool operator==(iterator  other)
                {
                    return current == other.current;
                }
            private:
                Nodo<T>* current;
        };
        tree();
        void insert(T);
        void remove(T);
        bool search(T);
        Nodo<T>* findMin();
        Nodo<T>* findMax();
        iterator begin(){
            iterator temp(findMin(root));
            return temp;
        }
        iterator end(){
            iterator temp(nullptr);
            return temp;
        }
        ~tree();
    private:
        Nodo<T>* findMin(Nodo<T>*);
        Nodo<T>* findMax(Nodo<T>*);
        void insert(T,Nodo<T>*&);
        void remove(T,Nodo<T>*&);
        bool search(T,Nodo<T>*);
        void makeEmpty(Nodo<T>*&);
        Nodo<T>* root;
};

template <class T>
tree<T>::tree()
{
    root = nullptr;
}

template <class T>
void tree<T>::makeEmpty(Nodo<T>*& t){
    if( t != nullptr )
    {
        makeEmpty( t->left );
        makeEmpty( t->link );
        delete t;
    }
    t = nullptr; 
}

template <class T>
tree<T>::~tree()
{
    makeEmpty(root);
}

template <class T>
void tree<T>::insert(T newElement)
{  
    insert(newElement,root);
}

template <class T>
void tree<T>::remove(T data)
{  
    remove(data,root);
}

template <class T>
bool tree<T>::search(T data)
{
    return search(data,root);
}

template <class T>
Nodo<T>* tree<T>::findMin(Nodo<T>* current){
    if(!current)
        return nullptr;
    if(current->left )
    {
        return findMin(current->left);
    }
    else
    {
        return current;
    }
}

template <class T>
Nodo<T>* tree<T>::findMin()
{
    findMin(root);
}

template <class T>
Nodo<T>* tree<T>::findMax(Nodo<T>* current)
{
    if(!current)
        return nullptr;
    if(current->link)
    {
        return findMax(current->link);
    }
    else
    {
        return current;
    }
}

template <class T>
Nodo<T>* tree<T>::findMax()
{
    findMax(root);
}


template <class T>
void tree<T>::insert(T data,Nodo<T>*& current)
{
    if(!root)
    {
        current = new Nodo<T>{data,nullptr,nullptr,nullptr};
    }
    else if (data < current->data)
    {
        if (current->left)
            insert(data,current->left);
        else
            current->left = new Nodo<T>{data,nullptr,nullptr,current};
    }
    else if (data > current->data)
    {
        if (current->link)
            insert(data,current->link);
        else
        {
            current->link = new Nodo<T>{data,nullptr,nullptr,current};
        }
    }
    else
    {
        ;
    }
}


template <class T>
void tree<T>::remove(T data,Nodo<T>*& t)
{
    if(!t)
    {
        return;
    }
    else if (data < t->data)
    {
        remove(data,t->left);
    }
    else if (data > t->data)
    {
        remove(data,t->link);
    }
    if( t->left != nullptr && t->link != nullptr ) // Two children
    {
        t->data = findMax( t->left )->data;
        remove( t->data, t->left );
    }
    else
    {
        Nodo<T> *oldNode = t;
        t = ( t->left != nullptr ) ? t->left : t->link;
        delete oldNode;
    }  
}


template <class T>
bool tree<T>::search(T data,Nodo<T>* current)
{
    if (!current)
    {
        return false;
    }
    else if (data < current->data)
    {
        return search(data,current->left);
    }
    else if (data > current->data)
    {
        return search(data,current->link);
    }
    else
    {
        return true;
    }
}

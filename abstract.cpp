#include <iostream>
using namespace std;

template <class T>
struct Nodo
{
    T data;
    Nodo<T> *link;
};

template <class T>
class linkedListIterator
{
public:
    linkedListIterator();
    linkedListIterator(Nodo<T> *ptr);
    T operator*();
    linkedListIterator<T> operator++();
    bool operator==(const linkedListIterator<T> &right) const;
    bool operator!=(const linkedListIterator<T> &right) const;

private:
    Nodo<T> *current;
};

template <class T>
linkedListIterator<T>::linkedListIterator()
{
    current = NULL;
}

template <class T>
linkedListIterator<T>::linkedListIterator(Nodo<T> *ptr)
{
    current = ptr;
}

template <class T>
T linkedListIterator<T>::operator*()
{
    return current->data;
}

template <class T>
linkedListIterator<T> linkedListIterator<T>::operator++()
{
    current = current->link;
    return *this;
}

template <class T>
bool linkedListIterator<T>::operator==(const linkedListIterator<T> &other) const
{
    return (current == other.current);
}

template <class T>
bool linkedListIterator<T>::operator!=(const linkedListIterator<T> &other) const
{
    return (current != other.current);
}

template <class T>
class linkedList
{
public:
    const linkedList<T> &operator=(const linkedList<T> &);
    void initializeList();
    bool isEmptyList() const;
    void print() const;
    int length() const;
    void destroyList();
    T front() const;
    T back() const;
    virtual bool search(const T searchItem) const = 0;
    virtual void insertFirst(const T item) = 0;
    virtual void insertLast(const T item) = 0;
    virtual void deleteNode(const T deleteItem) = 0;
    linkedListIterator<T> begin();
    linkedListIterator<T> end();
    linkedList();
    linkedList(const linkedList<T> &otherList);
    ~linkedList();

protected:
    int count;
    Nodo<T> *first;
    Nodo<T> *last;
    void copyList(const linkedList<T> &otherList);
};

template <class T>
bool linkedList<T>::isEmptyList() const
{
    return (first == NULL);
}

template <class T>
linkedList<T>::linkedList()
{
    first = NULL;
    last = NULL;
    count = 0;
}

template <class T>
void linkedList<T>::destroyList()
{
    Nodo<T> *temp;
    while (first != NULL)
    {
        temp = first;
        first = first->link;
        delete temp;
    }
    last = NULL;
    count = 0;
}

template <class T>
void linkedList<T>::initializeList()
{
    destroyList();
}

template <class T>
void linkedList<T>::print() const
{
    Nodo<T> *current;
    current = first;
    while (current != NULL)
    {
        cout << current->data << " ";
        current = current->link;
    }
}

template <class T>
int linkedList<T>::length() const
{
    return count;
}

template <class T>
T linkedList<T>::front() const
{
    assert(first != NULL);
    return first->data;
}

template <class T>
T linkedList<T>::back() const
{
    assert(last != NULL);
    return last->data;
}

template <class T>
linkedListIterator<T> linkedList<T>::begin()
{
    linkedListIterator<T> temp(first);
    return temp;
}

template <class T>
linkedListIterator<T> linkedList<T>::end()
{
    linkedListIterator<T> temp(NULL);
    return temp;
}

template <class T>
void linkedList<T>::copyList(const linkedList<T> &otherList)
{
    Nodo<T> *newNode;
    Nodo<T> *current;
    if (first != NULL)
        destroyList();
    if (otherList.first == NULL)
    {
        first = NULL;
        last = NULL;
        count = 0;
    }
    else
    {
        current = otherList.first;
        count = otherList.count;
        first = new Nodo<T>;
        first->data = current->data;
        first->link = NULL;
        last = first;
        current = current->link;
        while (current != NULL)
        {
            newNode = new Nodo<T>;
            newNode->data = current->data;
            newNode->link = NULL;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
    }
}

template <class T>
linkedList<T>::~linkedList()
{
    destroyList();
}

template <class T>
linkedList<T>::linkedList(const linkedList<T> &otherList)
{
    first = NULL;
    copyList(otherList);
}

template <class T>
const linkedList<T> &linkedList<T>::operator=(const linkedList<T> &otherList)
{
    if (this != &otherList)
    {
        copyList(otherList);
    }
    return *this;
}

template <class T>
class ListaDesordenada : public linkedList<T>
{
public:
    bool search(const T elemento) const;
    void insertFirst(const T item);
    void insertLast(const T item);
    void deleteNode(const T deleteItem);
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

template <class T>
class ListaOrdenada : public linkedList<T>
{
public:
    bool search(const T elemento) const;
    void insert(const T item);
    void insertFirst(const T item);
    void insertLast(const T item);
    void deleteNode(const T deleteItem);
};

template <class T>
bool ListaOrdenada<T>::search(const T elemento) const
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
void ListaOrdenada<T>::insert(const T item)
{
    Nodo<T> *current;   
    Nodo<T> *aux;
    Nodo<T> *newNode;   
    bool found;
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
        current = this->first;
        found = false;
        while (current != NULL && !found) 
            if (current->data >= item)
                found = true;
            else
            {
                aux = current;
                current = current->link;
            }
        if (current == this->first) 
        {
            newNode->link = this->first;
            this->first = newNode;
            this->count++;
        }
        else 
        {
            aux->link = newNode;
            newNode->link = current;
            if (current == NULL)
                this->last = newNode;
            this->count++;
        }
    } 
}

template <class T>
void ListaOrdenada<T>::insertFirst(const T item){
    insert(item);
}
template <class T>
void ListaOrdenada<T>::insertLast(const T item){
    insert(item);
}


template <class T>
void ListaOrdenada<T>::deleteNode(const T elemento)
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

int main()
{
    ListaDesordenada<int> mylista;
    mylista.insertFirst(5);
    mylista.insertLast(10);
    mylista.deleteNode(5);
    mylista.print();
    mylista.search(10);

    cout<<"LISTA ORDENADA"<<endl;
    ListaOrdenada<int> orden;
    orden.insert(5);
    orden.insert(1);
    orden.print();
    return 0;
}
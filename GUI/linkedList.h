
#include <iostream>
using namespace std;



template <class T>
struct nodeType
{
    T info;
    nodeType<T> *link;
};

template <class T>
class linkedListIterator
{
public:
    linkedListIterator();
    linkedListIterator(nodeType<T> *ptr);
    T operator*();
    linkedListIterator<T> operator++();
    bool operator==(const linkedListIterator<T> &right) const;
    bool operator!=(const linkedListIterator<T> &right) const;

private:
    nodeType<T> *current;
};

template <class T>
linkedListIterator<T>::linkedListIterator()
{
    current = NULL;
}

template <class T>
linkedListIterator<T>::linkedListIterator(nodeType<T> *ptr)
{
    current = ptr;
}

template <class T>
T linkedListIterator<T>::operator*()
{
    return current->info;
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
class linkedListType
{
public:
    const linkedListType<T> &operator=(const linkedListType<T> &);
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
    linkedListType();
    linkedListType(const linkedListType<T> &otherList);
    ~linkedListType();

protected:
    int count;
    nodeType<T> *first;
    nodeType<T> *last;
    void copyList(const linkedListType<T> &otherList);
};

template <class T>
bool linkedListType<T>::isEmptyList() const
{
    return (first == NULL);
}

template <class T>
linkedListType<T>::linkedListType()
{
    first = NULL;
    last = NULL;
    count = 0;
}

template <class T>
void linkedListType<T>::destroyList()
{
    nodeType<T> *temp;
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
void linkedListType<T>::initializeList()
{
    destroyList();
}

template <class T>
void linkedListType<T>::print() const
{
    nodeType<T> *current;
    current = first;
    while (current != NULL)
    {
        cout << current->info << " ";
        current = current->link;
    }
}


template <class T>
int linkedListType<T>::length() const
{
    return count;
}

template <class T>
T linkedListType<T>::front() const
{
    assert(first != NULL);
    return first->info;
}

template <class T>
T linkedListType<T>::back() const
{
    assert(last != NULL);
    return last->info;
}

template <class T>
linkedListIterator<T> linkedListType<T>::begin()
{
    linkedListIterator<T> temp(first);
    return temp;
}

template <class T>
linkedListIterator<T> linkedListType<T>::end()
{
    linkedListIterator<T> temp(NULL);
    return temp;
}

template <class T>
void linkedListType<T>::copyList(const linkedListType<T> &otherList)
{
    nodeType<T> *newNode;
    nodeType<T> *current;
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
        first = new nodeType<T>;
        first->info = current->info;
        first->link = NULL;
        last = first;
        current = current->link;
        while (current != NULL)
        {
            newNode = new nodeType<T>;
            newNode->info = current->info;
            newNode->link = NULL;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
    }
}

template <class T>
linkedListType<T>::~linkedListType()
{
    destroyList();
}

template <class T>
linkedListType<T>::linkedListType(const linkedListType<T> &otherList)
{
    first = NULL;
    copyList(otherList);
}

template <class T>
const linkedListType<T> &linkedListType<T>::operator=(const linkedListType<T> &otherList)
{
    if (this != &otherList)
    {
        copyList(otherList);
    }
    return *this;
}

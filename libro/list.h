#include <iostream>
using namespace std;

template <class T>
struct Node{
    public:
        Node(){
            previus = nullptr;
            next = nullptr;
        }
        Node<T>* next;
        Node<T>* previus;
        T data;
};

template <class T>
class list{
    public:
        class iterator
        {
        public:
            friend class list<T>;
            iterator(){
                current =nullptr;
            }
            iterator(Node<T> *ptr){
                current = ptr;
            }
            T operator*(){
                return current->data;
            }
            iterator operator++(){
                current = current->next;
                return *this;
            }
            iterator operator+(int num){
                iterator temp=*this;
                for(int i=0;i<num;i++)
                    ++temp;
                return temp;
            }
            bool operator==(const iterator &right) const{
                return current == right.current;
            }
            bool operator!=(const iterator &right) const{
                return current != right.current;
            }
            iterator operator--(){
                current = current->previus;
                return *this;
            }

            iterator operator-(int num){
                iterator temp=*this;
                for(int i=0;i<num;i++)
                    --temp;
                return temp;
            }
        private:
            Node<T> *current;
        };
        list();
        void insert(T item);
        void insert(T item,list<T>::iterator p);
        void remove(iterator p);
        void print();
        iterator begin(){
            iterator temp(head);
            return temp;
        }
        ~list();
    private: 
        Node<T>* head;
        Node<T>* tail;
        int size;
};

template <class T>
list<T>::list(){
    size = 0;
    head = nullptr;
    tail = nullptr;
}

template <class T>
void list<T>::insert(T item){
    Node<T> *newNode;
    newNode = new Node<T>;
    newNode->data = item;
    newNode->next = nullptr;
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->previus = tail;
        tail = newNode;
    }
    size++;
}
template <class T>
void list<T>::insert(T item,list<T>::iterator p){
    Node<T>* newNode = new Node<T>;
    newNode->data = item;
    if(p==head){
        newNode->next = head->next;
        newNode->previus = head;
        head->next = newNode;
        if(size==1)
            tail = newNode;
    }
    else if(p==tail){
        p.current->next = newNode;
        newNode->previus = p.current;
        tail = newNode;
    }
    else{
        Node<T>* next = p.current->next;
        p.current->next = newNode;
        newNode->previus = p.current;
        newNode->next = next;
        next ->previus = newNode;
    }
    size++;
}

template <class T>
void list<T>::remove(list<T>::iterator p){
    if(p==head){
        head = head->next;
        head->previus =nullptr;
        delete p.current;
    }
    else if(p==tail){
        tail = tail->previus;
        delete p.current;
    }
    else{
        Node<T>* previus = p.current->previus;
        Node<T>* next = p.current->next;
        previus->next = next;
        next->previus = previus;
        delete p.current;
    }
    size--;
}

template <class T>
void list<T>::print(){
    Node<T>* aux = head;
    while(aux){
        cout << aux->data <<endl;
        aux = aux->next;
    }
}

template <class T>
void list<T>::remove(){
    while(current->next){
        current->data = (current->next)->data;
        current = current->next;
    }
    delete current;
}

template <class T>
void list<T>::push(T data){
    list<T>::iterator it(tail->next);
    Node<T>* newNode = new Node<T>;
    newNode->data = data;
    newNode->next = tail->next;
    tail->next = newNode;
    tail = newNode;
}

template <class T>
void list<T>::pop(){
    list<T>::iterator it(tail->next);
    Nodo<T>* aux = it.current;
    it.current  = it.current->next;
    last->next = it.current;
    delete aux;
}
void list<T>::push_fron(){

}

template <class T>
list<T>::~list(){
    Node<T>* aux = head ;
    while(aux->next){
        aux = head->next;
        delete head;
        head = aux;
    }
}
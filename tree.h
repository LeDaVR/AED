#include <iostream>
using namespace std;

template <class Comparable>
struct BinaryNode
{
    BinaryNode();
    Comparable element;
    BinaryNode<Comparable>* left;
    BinaryNode<Comparable>* right;
    bool active;
    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt ,bool ac)
    : element{ theElement }, left{ lt }, right{ rt },active{ ac } { }

    BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt,bool ac )
    : element{ std::move( theElement ) }, left{ lt }, right{ rt }, active{ ac} { }
};

template <class Comparable>
BinaryNode<Comparable>::BinaryNode(){
    left = nullptr;
    right = nullptr;
}

template <class Comparable>
class tree
{
    public:
        tree();
        void insert(Comparable);
        void remove(Comparable);
        bool search(Comparable);
        BinaryNode<Comparable>* findMin(BinaryNode<Comparable>*);
        BinaryNode<Comparable>* findMax(BinaryNode<Comparable>*);
        ~tree();
    private:
        BinaryNode<Comparable>* findMin(BinaryNode<Comparable>*,BinaryNode<Comparable>*);
        BinaryNode<Comparable>* findMax(BinaryNode<Comparable>*,BinaryNode<Comparable>*);
        void insert(Comparable,BinaryNode<Comparable>*&);
        void remove(Comparable,BinaryNode<Comparable>*&);
        bool search(Comparable,BinaryNode<Comparable>*);
        void makeEmpty(BinaryNode<Comparable>*&);
        BinaryNode<Comparable>* root;
};

template <class Comparable>
tree<Comparable>::tree()
{
    root = nullptr;
}

template <class Comparable>
void tree<Comparable>::makeEmpty(BinaryNode<Comparable>*& t){
    if( t != nullptr )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullptr; 
}

template <class Comparable>
tree<Comparable>::~tree()
{
    makeEmpty(root);
}

template <class Comparable>
void tree<Comparable>::insert(Comparable newElement)
{  
    insert(newElement,root);
}

template <class Comparable>
void tree<Comparable>::remove(Comparable element)
{  
    remove(element,root);
}

template <class Comparable>
bool tree<Comparable>::search(Comparable element)
{
    search(element,root);
}

template <class Comparable>
BinaryNode<Comparable>* tree<Comparable>::findMin(BinaryNode<Comparable>* current,BinaryNode<Comparable>* inactive){
    if(!current)
        return nullptr;
    if(current->left && current->left != inactive)
    {
        return findMin(current->left,inactive);
    }
    else if (!current->active)
    {
        return findMin(root,current);
    }
    else
    {
        return current;
    }
}

template <class Comparable>
BinaryNode<Comparable>* tree<Comparable>::findMin(BinaryNode<Comparable>* current)
{
    findMin(root,nullptr);
}

template <class Comparable>
BinaryNode<Comparable>* tree<Comparable>::findMax(BinaryNode<Comparable>* current, BinaryNode<Comparable>* inactive)
{
    if(!current)
        return nullptr;
    if(current->right && current->right != inactive)
    {
        return findMax(current->right,inactive);
    }
    else if (!current->active)
    {
        return findMax(root,current);
    }
    else
    {
        return current;
    }
    
}

template <class Comparable>
BinaryNode<Comparable>* tree<Comparable>::findMax(BinaryNode<Comparable>* current)
{
    findMax(root,nullptr);
}

template <class Comparable>
void tree<Comparable>::insert(Comparable element,BinaryNode<Comparable>*& current)
{
    if(!current)
    {
        current = new BinaryNode<Comparable>{element,nullptr,nullptr,true};
    }
    else if (element < current->element)
    {
        insert(element,current->left);
    }
    else if (element > current->element)
    {
        insert(element,current->right);
    }
    else if (!current->active)
    {
        cout << current->element << " is now active" << endl;
        current->active = true;
    }
}

template <class Comparable>
void tree<Comparable>::remove(Comparable element,BinaryNode<Comparable>*& current)
{
    if(!current)
    {
        return;
    }
    else if (element < current->element)
    {
        remove(element,current->left);
    }
    else if (element > current->element)
    {
        remove(element,current->right);
    }
    else
    {
        current->active = false;
    }    
}


template <class Comparable>
bool tree<Comparable>::search(Comparable element,BinaryNode<Comparable>* current)
{
    if (!current)
    {
        return false;
    }
    else if (element < current->element)
    {
        return search(element,current->left);
    }
    else if (element > current->element)
    {
        return search(element,current->right);
    }
    else
    {
        return current->active;
    }
}
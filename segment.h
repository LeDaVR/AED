
#include <iostream>
using namespace std;

struct Point
{
    int x;
    int y;
    Point(int _x = 0,int _y = 0) : x{_x},y{_y}{}
    bool operator ==(Point b)
    {
        return (x == b.x && y==b.y);
    }
};

template <class T>
class SegmentTree
{
public:
    struct Node
    {
        T sum;
        Point range;
        Node* left;
        Node* right;
        Node(T suma,Point rango,Node* _left,Node* _right) 
            : sum{suma},range{rango},left{_left},right{_right}{}
    };
    SegmentTree(T* arr,int size);
    void makeEmpty(Node*& node);
    T suma(int x,int y);
    ~SegmentTree();
private:
    T suma(Node* node,Point range);
    void createNode(Node*& node,T* arr,Point _range);
    void setValues(Node*& node);
    Node* root;
};

template <class T>
SegmentTree<T>::SegmentTree(T* arr,int size)
{
    createNode(root,arr,Point(0,size-1));
    setValues(root);
}

template <class T>
void SegmentTree<T>::createNode(Node*& node,T* arr,Point _range)
{
    node = new Node{0,_range,nullptr,nullptr};
    
    if(_range.x != _range.y)
    {
        createNode(node->left,arr,Point(_range.x,(_range.x+_range.y)/2));
        createNode(node->right,arr,Point((_range.x+_range.y)/2+1,_range.y));
    }
    else
    {
        node->sum = arr[_range.x];
    }
}

template <class T>
void SegmentTree<T>::setValues(Node*& node)
{
    if(node)
    {
        setValues(node->left);
        setValues(node->right);
        if( node->range.x != node->range.y )
            node->sum = node->left->sum + node->right->sum;
    }
}

template <class T>
T SegmentTree<T>::suma(int x,int y)
{
    Node* node = root;
    Point range(x,y);
    return suma(node,range);
}

bool between(Point a,int element)
{
    return (element >= a.x && element <= a.y);
}

template <class T>
T SegmentTree<T>::suma(Node* node,Point  range)
{
    if( node->range == range)
    {
        return node->sum;
    }
    else
    {
        int sumleft =0;
        int sumright =0;
        if( between(node->left->range,range.x) )
        {
            if ( between(node->left->range,range.y))
            {
                sumleft =  suma(node->left,range);
            }
            else
            {
                sumleft =  suma(node->left,Point(range.x,node->left->range.y));
            }
        }
        if( between(node->right->range,range.y))
        {
            if ( between(node->right->range,range.x))
            {
                sumright = suma(node->right,range);
            }
            else
            {
                sumright = suma(node->right,Point(node->right->range.x,range.y));
            }
            
        }
        return sumleft+sumright;
    }
}

template <class T>
void SegmentTree<T>::makeEmpty(Node*& node){
    if(node)
    {
        makeEmpty(node->left);
        makeEmpty(node->right);
        delete node;
        node = nullptr;
    }
}

template <class T>
SegmentTree<T>::~SegmentTree(){
    makeEmpty(root);
}

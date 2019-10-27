#include <iostream>

using namespace std;

template <class Comparable>
class alv
{
public:
    struct AvlNode
    {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable &ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{ele}, left{lt}, right{rt}, height{h} {}

        AvlNode(Comparable &&ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
    };

    alv(){
        root = nullptr;
    }

    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max(const int x,const int y){
        if (x > y)
            return x;
        return y;
    }

    void insert(const Comparable &x){
        insert(x,root);
    }

    void insert(const Comparable &x, AvlNode *&t)
    {
        if (t == nullptr)
            t = new AvlNode{x, nullptr, nullptr};
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        balance(t);
    }

    static const int ALLOWED_IMBALANCE = 1;

    void balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);

        t->height = max(height(t->left), height(t->right)) + 1;
    }

    void rotateWithLeftChild(AvlNode *&k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void doubleWithLeftChild(AvlNode *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void rotateWithRightChild(AvlNode *&k2)
    {
        AvlNode *k1 = k2->right;
        k2->right = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->right), k2->height) + 1;
        k2 = k1;
    }

    void doubleWithRightChild(AvlNode *&k3)
    {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }


    void remove(const Comparable &x)
    {
        remove(x,root);
    }

    AvlNode* findMin(AvlNode *t)
    {
        while(t->left)
        {
            t = t->left;
        }
        return t;
    }
    void remove(const Comparable &x, AvlNode *&t)
    {
        if (t == nullptr)
            return; 
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) 
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }

        balance(t);
    }

    void print(){
        print(root);
    }

    void print(AvlNode *node)
    {
        if(node)
        {
            cout << "Node " << node->element << " ";
            if(node->left)
                cout << "Left Children " << node->left->element << " ";
            if(node->right)
                cout << "Right Children " << node->right->element;
            cout << endl;
            print(node->left);
            print(node->right);
        }
    }

    void makeempty(AvlNode *t)
    {
        if(t)
        {
            makeempty(t->left);
            makeempty(t->right);
            delete t;
        }
    }

    ~alv()
    {
        makeempty(root);
    }
private:
    AvlNode *root;
};

int main()
{
    alv<int> numeros;
    numeros.insert(1);
    numeros.insert(2);
    numeros.insert(3);
    numeros.insert(4);
    numeros.remove(2);
    numeros.print();
    return 0;
}
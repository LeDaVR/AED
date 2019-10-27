#include <iostream>

using namespace std;

enum {
    RED,
    BLACK
};

template <class T>
class red_black{
    public:
        struct Node{
            bool color;
            Node* left;
            Node* right;
            Node* parent;
            T data;
            Node(){}
            Node(T _Data,Node*& _parent,bool _color) : data(_Data) , parent(_parent),color(_color)
            {
                
            }
        };
        red_black(){
            nullnode = new Node;
            nullnode->color = BLACK;
            root = nullnode;
        }
        void leftrotate(Node* node){
            Node* rightnode = node->right;
            node->right = rightnode->left;
            if(rightnode->left != nullnode)
                rightnode->left->parent = node;
            rightnode->parent = node->parent;
            if(node->parent == nullnode)
                root = rightnode;
            else if(node == node->parent->left)
                node->parent->left = node->right;
            else
                node->parent->left = node->right;
            rightnode->left = node;
            node->parent = rightnode;
        }

        void rightrotate(Node* node){
            Node* leftnode = node->left;
            node->left = leftnode->right;
            if(leftnode->right != nullnode)
                leftnode->right->parent = node;
            leftnode->parent = node->parent;
            if(node->parent == nullnode)
                root = leftnode;
            else if(node == node->parent->left)
                node->parent->left = node->left;
            else
                node->parent->left = node->left;
            leftnode->right = node;
            node->parent = leftnode;
        }

        void insert(T element){
            Node* father = nullnode;
            Node* current  = root;
            while(current != nullnode){
                father = current;
                if(element > current->data){
                    current = current->right;
                }
                else{
                    current = current->left;
                }    
            }
            current = new Node(element,father,RED);
            if(father == nullnode)
                root = current;
            current->left = nullnode;
            current->right = nullnode;
            if(father->data > current->data)
                father->left = current;
            else 
                father->right = current;
            fix(current);
        }

        void fix(Node* node){
            while(node->parent->color == RED){
                if (node->parent == node->parent->parent->left){
                    Node* y = node->parent->parent->right;
                    if(y->color == RED){
                        node->parent->color = BLACK;
                        y->color = BLACK;
                        node->parent->parent->color = RED;
                        node = node->parent->parent;
                    }
                    else {
                        if(node == node->parent->right){
                            node = node->parent;
                            leftrotate(node);
                        }
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        rightrotate(node->parent->parent);
                    }

                }
                else{
                    //mismo caso pero desde la derecha
                }
            }
            root->color = BLACK;
        }

        void print(Node* nodo){
            if(nodo != nullnode){
                cout <<nodo->data << " ";
                print(nodo->left);
                print(nodo->right);
            }
        }

        void print(){
            print(root);
        }
    private:
        Node* root;
        Node* nullnode;
};
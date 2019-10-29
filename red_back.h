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
                node->parent->left = rightnode;
            else
                node->parent->right = rightnode;
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
                node->parent->left = leftnode;
            else
                node->parent->right = leftnode;
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
                else if(element < current->data){
                    current = current->left;
                }
                else{
                    return;
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
                    Node* y = node->parent->parent->left;
                    if(y->color == RED){
                        node->parent->color = BLACK;
                        y->color = BLACK;
                        node->parent->parent->color = RED;
                        node = node->parent->parent;
                    }
                    else {
                        if(node == node->parent->left){
                            node = node->parent;
                            rightrotate(node);
                        }
                        node->parent->color = BLACK;
                        node->parent->parent->color = RED;
                        leftrotate(node->parent->parent);
                    }
                }
            }
            root->color = BLACK;
        }

        void print(Node* nodo){
            if(nodo != nullnode){
                cout << "DATOS DEL NODO " << nodo->data <<" COLOR : "<< nodo->color <<endl;
                if(nodo->parent == nullnode)
                    cout << "SU PADRE ES NULLNODE"<<endl;
                if(nodo->left == nullnode)
                    cout << "SU hijo izquierdo ES NULLNODE"<<endl;
                if(nodo->right == nullnode)
                    cout << "SU hijo derecho ES NULLNODE"<<endl;
                print(nodo->left);
                print(nodo->right);
            }
        }

        void transplant(Node* u,Node* v){
            if ( u->parent == nullnode)
                root = v;
            else if( u == u->parent->left)
                u->parent->left = v ;
            else
                u->parent->right = v;
            v->parent = u->parent;
        }

        void remove(T element){
            cout <<" called"<<endl;
            Node* node = root;
            cout <<root->data << node->data<<endl;
            if(node != nullnode)
                cout<<"asd";
            while(node != nullnode){
                cout << node->data;
                if( element <node->data)
                    node = node->left;
                else if (element > node->data)
                    node = node->right;
                else
                {
                    cout <<"entrando con el nodo"<<node->data;
                    remove(node);
                    break;
                }
            }
        }

        Node* minimo(Node* node){
            cout << node->data;
            Node* temp = node;
            while(temp->left != nullnode)
                temp = temp->left;
            return temp;
        }
        void remove(Node* node){
            Node* y = node;
            Node* x;
            bool  color_original = y->color;
            if(node->left == nullnode){
                x = node->right;
                transplant(node,node->right);
            }
            else if( node->right == nullnode){
                x = node->left;
                transplant(node,node->left);
            }
            else{
                cout << "ata ca"<<endl;
                y = minimo(node->right);
                cout << "paso"<<endl;
                color_original = y->color;
                x = y->right;
                if (y->parent == node)
                    x->parent = y;
                else{
                    transplant(y,y->right);
                    y->right = node->right;
                    y->right->parent = y;
                }
                transplant(node,y);
                y->left = node->left;
                y->left->parent =y;
                y->color = node->color;
                delete node;
            }
            if (color_original)
                delete_fix(x);
        }

        void delete_fix(Node* x){
            while (x != root && x->color){
                if(x == x->parent->left){
                    Node* w = x->parent->right;
                    if ( w->color == RED){
                        w->color = BLACK;
                        x->parent->color = RED;
                        leftrotate(x->parent);
                        w = x->parent->right;
                    }
                    if (w->left->color == BLACK && w->right->color == BLACK){
                        w->color =BLACK;
                        x =x->parent;
                    }
                    else {
                        if(w->right->color ==BLACK){
                            w->left->color = BLACK;
                            w->color = RED;
                            rightrotate(w);
                            w = x->parent->right;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->right->color = BLACK;
                        leftrotate(x->parent);
                        x = root;
                    }
                }
                else{
                    Node* w = x->parent->left;
                    if ( w->color == RED){
                        w->color = BLACK;
                        x->parent->color = RED;
                        leftrotate(x->parent);
                        w = x->parent->left;
                    }
                    if (w->right->color == BLACK && w->left->color == BLACK){
                        w->color =BLACK;
                        x =x->parent;
                    }
                    else {
                        if(w->left->color ==BLACK){
                            w->right->color = BLACK;
                            w->color = RED;
                            rightrotate(w);
                            w = x->parent->left;
                        }
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        w->left->color = BLACK;
                        leftrotate(x->parent);
                        x = root;
                    }
                }
            }

        }
        void print(){
            print(root);
        }

        void makeempty(Node*& node){
            if(node!=nullnode){
                makeempty(node->left);
                makeempty(node->right);
                delete node;
                node = nullptr;
            }
        }

        ~red_black(){
            makeempty(root);
            delete nullnode;
        }
private:
        Node* root;
        Node* nullnode;
};
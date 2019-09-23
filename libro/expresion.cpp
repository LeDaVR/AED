#include <iostream>

using namespace std; 

#define HEAD 1
#define TAIL 2

template <class T>
class Stack{
    private:
        static int doble;
        static T* saved;


        T* arr;
        int type;
        int size; 
    public:
        Stack(){
            if(!doble){
                size=0;
                arr = new T[size];
                saved = arr;
                doble=1;
                type=HEAD;
            }
            else{
                saved.push()
            }
        }
        void push{

        }
        void pop{

        }
};

template <class T>
T Stack::saved;
int Stack::doble = 0;

int main() 
{ 
     
} 
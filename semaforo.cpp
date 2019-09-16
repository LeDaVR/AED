#include <iostream>
using namespace std;
//-----------------------------NODO Y LISTA --------------------------------------------
template <class T>
class Nodo;

template <class T>
class Lista;

template<class T>
ostream& operator <<(ostream& o,Nodo<T>& a){
    o << a.data;
    return o;
}

template <class T>
class Nodo{
    private:
        friend class Lista<T>;
        T data;
        Nodo<T>* next;
    public:
        Nodo(){
            next=NULL;
        }
        friend ostream& operator << <>(ostream& o,Nodo<T>& a);

};

template <class T>
class Lista{
    public:
        class iterator{
            Nodo<T>* pos;
            public:
            iterator(Nodo<T>*_pos=NULL) : pos(_pos){}

            T& operator*(){ 
                return pos->data; 
            }
 
			bool operator!=(const iterator& it){ 
                return this->pos != it.pos; 
            }
 
			iterator operator++(int){ 
                pos = pos->next; 
                return *this; 
            }

            iterator& operator=(iterator a){
                this->pos=a.pos;
                return *this;
            }

            iterator operator+(int a){
                iterator temp;
                temp.pos=this->pos;
                for(int i=0;i<a;i++){
                    temp.pos=temp.pos->next;
                }
                return temp;
            }

            iterator& operator+=(int a){
                for(int i=0;i<a;i++){
                    this->pos=this->pos->next;
                }
                return *this;
            }
 
        };



        Lista(){
            first=NULL;
            size=0;
        }

        void add(T data){
            Nodo<T>* new_nodo=new Nodo<T>;
            new_nodo->data=data;
            Nodo<T>* aux1;
            Nodo<T>* aux2;
            aux1=first;
            while(aux1&&aux1->data<data){
                aux2=aux1;
                aux1=aux1->next;
            }
            if(first==aux1)
                first=new_nodo;
            else
            {
                aux2->next=new_nodo;
            }
            new_nodo->next=aux1;
            size++;
        }

        void search(T data){
            int pos=0;
            Nodo<T>* aux1=first;
            while(aux1->data!=data){
                aux1=aux1->next;
                pos++;
                if(!aux1)
                    break;
            }
            if(!aux1){
                cout<<"No se encontro el elemento"<<endl;
            }
            else{
                cout<<"ELEMENTO ENCONTRADO EN LA POSICION : "<< pos <<endl;
            }
        }

        void remove(T data){
            Nodo<T>* aux1=first;
            Nodo<T>* aux2=NULL;
            while(aux1->data!=data){
                aux2=aux1;
                aux1=aux1->next;
                if(!aux1)
                    break;
            }
            if(!aux2){
                first=aux1->next;
                delete aux1;
                size--;
                return;
            }
                
            if(!aux1)
                cout<<"No se encontro el elemento a eliminar"<<endl;
            else{
                aux2->next=aux1->next;
                delete aux1;
                size--;
            }
        }


        void printlist(){
            Nodo<T>* aux1=first;
            while(aux1){
                cout<<aux1->data<<" ";
                aux1=aux1->next;
            }
            cout<<endl;
        }

        int getSize(){
            return size;
        }

        const iterator begin() const {
            return iterator(first);
        }

        const iterator end() const {
            return iterator(NULL);
        }
        
        ~Lista(){
            Nodo<T>* aux1=first;
            Nodo<T>* aux2;
            while(aux1){
                aux2=aux1->next;
                delete aux1;
                aux1=aux2;
            }
        }

    private:
        Nodo<T>* first;
        int size;
};

class semaforo{
    int isgreen;
    int cycletime;
    int currenttime;
    static bool init;   
    bool ingreenrange(){
        if(!(currenttime/cycletime%2))
            if(currenttime%cycletime>=0 && currenttime%cycletime<cycletime-5)
                return true;
        return false; 
    }
    public:
        semaforo(){
            isgreen=true;
            init=true;
        }
        semaforo(int _cycletime) : cycletime(_cycletime){
            currenttime=0;
            isgreen=true;
            init=true;
        }
        void refresh(){
            currenttime++;
            isgreen = ingreenrange();
            if(!isgreen)
                init = false;
        }
        bool isGreen(){
            return isgreen;
        }
        bool operator<(semaforo other){
            return cycletime<other.cycletime;
        }
        int getCurrentTime(){
            return currenttime;
        }
        static bool Init(){
            return init;
        }
        friend ostream& operator<<(ostream& o,semaforo a);
};

ostream& operator<<(ostream& o,semaforo a){
    return o;
}
bool semaforo::init = true;


int sincronizeTime(int number){
    Lista<semaforo> semaforos;
    while(number){
        int input;
        cin>>input;
        semaforos.add(semaforo(input));
        number--;
    }
    semaforos.printlist();
    bool search=true;
    Lista<semaforo>::iterator begin = semaforos.begin();
    while(search){
        int cont=0;
        for(Lista<semaforo>::iterator it=semaforos.begin();it!=semaforos.end();it++){
            (*it).refresh();
            if((*it).isGreen())
                cont++;
            if((*it).getCurrentTime()>3600){
                cout<<"no tiene solucion"<<endl;
                return  0;
            }
        }
        if(cont==semaforos.getSize())
            search=false;
        if(semaforo::Init())
            search=true;
    }
    Lista<semaforo>::iterator it=semaforos.begin();
    return (*it).getCurrentTime();
}

int main(){
    int number;
    cin>>number;
    cout<<sincronizeTime(number);
}
#include<iostream>
#include<math.h> 
#include<string>
#include<random>
#include<cstdlib>
using namespace std;
//Establecer coordenadas


class Coordenada{
private:
    float lat;
    float lon;
    Coordenada* pointer;

public: 
    Coordenada(){
        lat = 0;
        lon = 0;
        pointer = NULL;
        
    }
    
    ~Coordenada(){
        
    }
    
    Coordenada(float x, float y){
        this-> lat = x;
        this-> lon = y;
        pointer = NULL;
    }

    //Getters
    
    float get_lat() {
        return lat;
    }

    float get_lon(){
        return lon;
    }


    Coordenada* get_next(){
        return pointer;
    }

    Coordenada get_coordenada(){
        return *this;
    }
    

    //Setters
    void set_lat(float x){
        lat = x;
    }

    void set_lon(float y){
        lon = y;
    }
    
    void set_next(Coordenada* p){
        pointer = p;
    }

    Coordenada& operator=(const Coordenada& f){
        set_lat(f.lat);
        set_lon(f.lon);
        return *this;
    }

    string to_string(){
        return "("+std::to_string(lat) + ", " + std::to_string(lon)+ ")";
    }
    
    friend std::ostream& operator<<(std::ostream& os, Coordenada& b){
        return os <<b.to_string();
    }

    
};

class Nodo{
  
  Coordenada* coor;
  Nodo* next;
  Nodo* prev;
  int size; 
  
public:
  
  Nodo(){
      coor = NULL;
      next = NULL;
      prev = NULL;
      size = 0;
  }
  
  ~Nodo(){
  }
  
  Nodo(Coordenada* c){
      coor = c;
      next = NULL;
      prev = NULL;
      size = 0;
  }
    
  Coordenada* get_dato(){
      return coor;
  }
  
  void set_dato(Coordenada* c){
      coor = c;
  }
  
  Nodo* get_next(){
      return next;
  }
  
  Nodo* get_prev(){
      return prev;
  }
  
  void set_next(Nodo* p){
      next = p;
  }
  
  void set_prev(Nodo* a){
      prev = a;
  }
  
  void push_back(float c , float p){
        
        if(size == 0){
            coor = new Coordenada(c,p);
            size++;
        }else{
            Coordenada* c_1 = coor;
            while(c_1->get_next() != NULL){
                c_1 = c_1->get_next();    
            }
            c_1->set_next(new Coordenada(c,p));
            size++;
        }
        
    }

    Coordenada* get(int i){
        if(i < size && i>=0){
            Coordenada* c = coor;
            for(int x = 0; x<i; x++){
                c = c->get_next();
            }
            return c;
        }else{
            if(size == 0){
                cout<<"La lista de personas está vacía";
            }else{
                cout<<"la posicion no existe";
            }
            return NULL;
        }

    }

    //hash
    /*
    string hash_function(Coordenada* c){
        string bit_lon;
        string bit_lat;
        float start = -90.0;
        float finish = 90.0;
        float iteration;
        for(int i = 0; i<13; i++){
            if(c->get_lat() < 0 && c->get_lat() > start){
                bit_lat.append("0");
            }
            if()
       }
    }
    */


    string to_string(){
        string s = "";
        Coordenada* c = coor;
        while(c != NULL){
            s.append(c->to_string());
            c = c->get_next();
        if (c != NULL) {
            s.append(">>");
        }
    }
        s.append("\n");
        return s;
    }

    friend std:: ostream& operator<<(std:: ostream& os, Nodo& b){
        return os <<b.to_string();
    }
    
};

class Lista{
    
    Nodo* ptr;
    int size;

public:  

    Lista(){
        ptr = NULL;
        size = 0;
    }
    
    ~Lista(){
        Nodo* t = ptr;
        Nodo* n;
        while(t->get_next() != NULL){
            n = t;
            t = t->get_next();
            delete n->get_dato(); // Delete Coordenada object
            delete n;
        }
        delete t->get_dato(); // Delete Coordenada object
        delete t;
    }
    
    void push_back(Coordenada* d){
        
        if(size == 0){
            ptr = new Nodo(d);
            size++;
        }else{
            Nodo* t = ptr;
            while(t->get_next() != NULL){
                t = t->get_next();    
            }
            t->set_next(new Nodo(d));
            size++;
        }
        cout<<endl;
        
    }
    
    int getSize(){
        return size;
    }
    
    void print(){
        if(size == 0){
            cout<<"La lista está vacía"<<endl;
        }else{
            Nodo* t = ptr;
            do{
                cout<<(*t);
                t = t->get_next();
                
            }while(t != NULL);
            cout<<endl;
        }
    }
    
    Nodo* get(int i){
        if(i < size && i>=0){
            Nodo* n = ptr;
            for(int x = 0; x<i;x++){
                n = n->get_next();
            }
            return n;
        }else{
            //throw invalid_argument("La posicion no existe");
            if(size == 0){
                cout<<"La lista está vacía";
            }else{
                cout<<"La posicion no existe";
            }
            return NULL;
        }
        
    }
    
    
    void insert(Coordenada* p, int pos){
        if(pos >= 0 && pos <= size){
            if(size == 0 || pos == size){ 
                push_back(p);
            }else{
                Nodo* n = new Nodo(p);
                if(pos == 0){
                    n->set_next(ptr);
                    ptr = n;
                }else{
                    Nodo* t = get(pos-1);
                    n->set_next(t->get_next());
                    t->set_next(n);
                }
                size++;
            }
        }else{
            cout<<"La posicion no existe"<<endl;
            
        }
        
    }
    
    void remove(int pos){
        
        if((pos >= 0 && pos <= size) && size > 0){
            if(pos == 0){ 
                Nodo* t = ptr;
                ptr = ptr->get_next();
                delete t;
            }else{
                Nodo* t = get(pos-1);
                Nodo* t2 = t->get_next();
                
                t->set_next(t2->get_next());
                delete t2;
            }
            size--;
        }else{
            cout<<"La posicion no existe o la lista está vacía"<<endl;
        }
        
    }
    
};


int main()
{

    srand(1234);// semilla

    //Rangos de latitud y longitud
    float lat_min = -90.0;
    float lat_max = 90.0;
    float lon_min = -180.0;
    float lon_max = 180.0;

    int numero_coordenadas = 10;
    Lista c = Lista();
    for (int i = 0; i < numero_coordenadas; i++) {
        //Establece las coordenadas aleatorias teniendo en cuenta los rangos de la latitud y longitud
        float lat = lat_min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (lat_max - lat_min));
        float lon = lon_min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (lon_max - lon_min));
        c.push_back(new Coordenada(lat,lon)); 
    }
    c.print();

   return 0;
}

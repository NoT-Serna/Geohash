include <iostream>
#include <cmath>
#include <string>
using namespace std;


//LAS CLASES NODO Y MAPA SE USAN SOLO PARA LA CONVERSION DE DECIMAL A BASE 32, LA CLASE NODO ES DE LA QUE SE CONFORMA EL MAPA, A DIFERENCIA DE NODE, QUE ES PARA EL ARBOL, Y EL MAPA SE USA PARA PODER USAR LA FUNCION GET Y A CADA NUMERO ASIGNARLE UNA LETRA
template <typename T, typename D>    
class Nodo{  
private:  
    pair<T,D>dato;  
    Nodo* next;  
   
public:  
   
    Nodo (T llave, D valor){  
        dato.first=llave;
        dato.second=valor;
        next=nullptr;  
    }  
       
    ~Nodo(){  
          
    }  
       
    void set_valor(D valor){  
        dato.second = valor;  
    }  
       
    pair<T,D> get_dato(){  
        return dato;  
    }  
       
    void set_next(Nodo* n){  
        next = n;  
    }  
       
    Nodo* get_next(){  
        return next;  
    }  
};  
   
template <typename T, typename D>  
class Mapa{  
private:  
    Nodo<T,D>* ptr;  
    int size=0;  
      
public:  
   
    Mapa(){  
        ptr=nullptr;  
        size = 0;  
    } 
    
    Mapa(char* valores, int n){
        Mapa();
        for (int i=0; i<(n*2)-1; i=i+2){
            add(valores[i],valores[i+1]);
        }
    }
      
    ~Mapa(){ 
        Nodo<T,D>* temp = ptr;  
        if(ptr!=nullptr){  
            Nodo<T,D>* temp_next = ptr->get_next();  
            while(temp_next!=nullptr){  
                delete temp;  
                temp = temp_next;  
                temp_next = temp -> get_next();  
            }  
            delete temp; //Borrar el ultimo nodo  
        } 
    }  
     
    int buscar (T elemento){  
        Nodo<T,D>* temp = ptr; 
        for(int i=0; i<size; i++){ 
            if (temp->get_dato().first == elemento){ 
                return i; 
            } 
            temp = temp -> get_next(); 
        } 
         
        return size; 
    } 
    
    D get(T llave){
        Nodo<T,D>* temp = ptr;
        int elemento = buscar(llave);
        for (int i=0; i<elemento; i++){
            temp = temp -> get_next(); 
        }
        return temp->get_dato().second;
    }
      
    void add(T llave, D valor){  
        Nodo<T,D>* nuevo_nodo = new Nodo<T,D>(llave, valor);  
          
        if (ptr==nullptr){//Mapa está vacio  
            ptr = nuevo_nodo;  
        }else{//Mapa no está vacio 
            Nodo<T,D>* temp = ptr;
            int elemento=buscar(llave);
            if (elemento>=size){
                while(temp->get_next()!=nullptr){  
                    temp = temp -> get_next();   
                }  
                temp->set_next(nuevo_nodo);  
            }else{
                for (int i=0; i<elemento; i++){
                    temp = temp -> get_next(); 
                }
                temp->set_valor(valor);
            }
        }  
        size++;  
    }  
      
    void print(){  
          
        if (ptr==nullptr){//Mapa está vacio  
            cout<<"El Mapa está vacio"<<endl;  
        }else{//Mapa no está vacio  
            Nodo<T,D>* temp = ptr;  
            while(temp!=nullptr){  
                cout<<temp->get_dato().first<<"\t"; 
                cout<<temp->get_dato().second<<"\t"<<endl;
                temp = temp -> get_next();  

            }  
            cout<<endl;  
        }  
          
    }  
      
};  

class Node {
private:
  string codigo;
  int data;
  Node* izq;
  Node* der;

public:
  Node() {
    codigo = "";
    data = 0;
    izq = NULL;
    der = NULL;
  }

  Node(int d, string c) {
    codigo = c;
    data = d;
    izq = NULL;
    der = NULL;
  }

  int getData() { 
      return data; 
      
  }
  
  string getCodigo(){
      return codigo;
  }

  Node* getIzq() { 
      return izq; 
      
  }

  Node* getDer() { 
      return der; 
      
  }

  void setIzq(Node* iz) {
      izq = iz; 
      
  }

  void setDer(Node* de) { 
      der = de; 
      
  }

  bool hasIzq() { 
      return izq != NULL; 
      
  }

  bool hasDer() { 
      return der != NULL; 
      
  }

  bool isHoja() {
    if (izq == NULL && der == NULL) {
      return true;
    }
    return false;
  }
};

class Tree {
  Node* root;
  
  //ELEMENTOS PARA CREAR HASH
  int digitos[8]={};
  char base_32[44]={10,'b',11,'c',12,'d',13,'e',14,'f',15,'g',16,'h',17,'j',18,'k',19,'m',20,'n',21,'p',22,'q',23,'r',24,'s',25,'t',26,'u',27,'v',28,'w',29,'x',30,'y',31,'z'};
  Mapa <int, char> convertir = Mapa <int, char> (base_32 , 22);
  
  //FUNCIONES PARA CONVERSION A HASH
  
  //CONVIERTE UNA COORDENADA A UN BINARIO
    basic_string<char> cord_a_binary(float cord, float izq, float der, int cont){
        float quepasa=cord;
        int contador=cont+1;
        string binario="";
        float medio=(izq+der)/2;
        basic_string<char> n_digito;
        if(contador<=20){
            if(cord<=medio){
                //cout<<quepasa<<" es menor a "<<medio<<endl;
                binario="0";
                n_digito=cord_a_binary(cord,izq,medio,contador);
            }else{
                //cout<<cord<<" es mayor a "<<medio<<endl;
                binario="1";
                n_digito=cord_a_binary(cord,medio,der,contador);
            }
        }
        return binario+n_digito;
    }
  //MEZCLA DOS COORDENADAS INTERCALANDOLAS
    string mix(string lat, string lon){
        string mixeado="";
        int indice=0;
        for(int i=1; i<=40; i++){
            if (i%2==1){
                mixeado+=lat[indice];
            }else{
                mixeado+=lon[indice];
                indice++;
            }
        }
        return mixeado;
    }
  //CONVIERTE UN PAQUETE DE 5 BITS BINARIOS A UN ENTERO DECIMAL ENTRE 0 Y 31
    int binario_a_decimal(string binario){
       int entero=0;
       for (int i=0; i<5; i++){
           if (binario[4-i]=='1'){
               entero+=pow(2,i);
           }
       }
       return entero;
    }
  //SEPARA EL BINARIO COMPLETO EN PAQUETES DE 5 BITS Y LOS CONVIERTE TODOS A DECIMALES
    void binario_a_decimales(string binario){
        string digito_1=binario.substr(0,5);
        string digito_2=binario.substr(5,5);
        string digito_3=binario.substr(10,5);
        string digito_4=binario.substr(15,5);
        string digito_5=binario.substr(20,5);
        string digito_6=binario.substr(25,5);
        string digito_7=binario.substr(30,5);
        string digito_8=binario.substr(35,5);
        
        digitos[0]=binario_a_decimal(digito_1);
        digitos[1]=binario_a_decimal(digito_2);
        digitos[2]=binario_a_decimal(digito_3);
        digitos[3]=binario_a_decimal(digito_4);
        digitos[4]=binario_a_decimal(digito_5);
        digitos[5]=binario_a_decimal(digito_6);
        digitos[6]=binario_a_decimal(digito_7);
        digitos[7]=binario_a_decimal(digito_8);
    }
  //CONVIERTE CADA UNO DE ESTOS ENTEROS DECIMALES A SUS SIMBOLOS RESPECTIVOS EN BASE 32 Y LOS CONCATENA PARA TENER EL NUMERO EN BASE 32
    string coordenadas_a_base32(float lat, float lon){
        string base_32="";
        string binario_lat = cord_a_binary(lat, -90, 90, 0);
        string binario_lon = cord_a_binary(lon, -180, 180, 0);
        
        string juntos=mix(binario_lat, binario_lon);
        
        binario_a_decimales(juntos);
        int* lista = digitos;
        
        for(int i=0; i<8; i++){
            if(lista[i]>=10)
                base_32+=convertir.get(lista[i]);
            else
                base_32+=to_string(lista[i]);
        }
        cout<<base_32<<endl;
        return base_32;
      }
  //CALCULA EL VALOR DEL CODIGO PARA USARLO DENTRO DEL ARBOL
    int valor_del_hash(string hashs){
        int entero=0;
        for (int iterador=0; iterador<8;iterador++){
            entero+=hashs[iterador]*pow(32,5-iterador);
        }
        return entero;
    }

public:
  //DEVUELVE LA ALTURA DE UN SUBARBOL DESDE UN NODO DADO
  int getHeight(Node* r) {
    if (r == NULL) {
      return 0;
    } else {
      return 1 + max(getHeight(r->getIzq()), getHeight(r->getDer()));
    }
  }
  //DEVUELVE LA ALTURA DEL ARBOL DESDE LA RAIZ
  int getHeight() { 
      return getHeight(root); 
      
  }
  //CALCULA SI UN SUBARBOL ESTÁ BALANCEADO DESDE UN NODO DADO
  bool isBalanced(Node* r) {
    return abs(getHeight(r->getIzq()) - getHeight(r->getDer())) <= 1;
  }
  //CALCULA SI EL ARBOL ESTÁ BALANCEADO DESDE LA RAIZ
  bool isBalanced() { 
      return isBalanced(root); 
      
  }
  //CALCULA SI UN SUBARBOL ESTÁ DESBALANCEADO HACIA LA IZQUIERDA DESDE UN NODO DADO
  bool isIzqHeavy(Node* r) {
    return getHeight(r->getIzq()) - getHeight(r->getDer()) > 1;
  }
  //CALCULA SI EL ARBOL COMPLETO ESTÁ DESBALANCEADO HACIA LA IZQUIERDA DESDE LA RAIZ
  bool isIzqHeavy() { 
      return isIzqHeavy(root);
      
  }
  //CALCULA SI UN SUBARBOL ESTÁ DESBALANCEADO HACIA LA DERECHA DESDE UN NODO DADO
  bool isDerHeavy(Node* r) {
    return getHeight(r->getIzq()) - getHeight(r->getDer()) < -1;
  }
  //CALCULA SI EL ARBOL COMPLETO ESTÁ DESBALANCEADO HACIA LA DERECHA DESDE LA RAIZ
  bool isDerHeavy() { 
      return isDerHeavy(root); 
      
  }
  //FUNCION DE LLAMADO Y DE CASO INICIAL PARA AÑADIR UN NODO
  void addr(float lon, float lat) {
    string codigo = coordenadas_a_base32(lon, lat);
    int d = valor_del_hash(codigo);
    if (root != NULL)
      addr(codigo, root, root);
    else
      root = new Node(d, codigo);
  }
  //FUNCION INTERNA PARA AÑADIR UN NODO
  void addr(string codigo, Node* t, Node* pt) {
    int d = valor_del_hash(codigo);
    if (t == NULL) {
      Node* n = new Node(d, codigo);
      if (d < pt->getData()) {
        pt->setIzq(n);
      } else {
        pt->setDer(n);
      }
    } else {
      if (d < t->getData()) {
        addr(codigo, t->getIzq(), t);
      } else {
        addr(codigo, t->getDer(), t);
      }

      if (!isBalanced(t)) {
        if (isIzqHeavy(t)) {
          if (isHijoIzq(d)) {
            Node* z = t->getIzq();
            Node* pt = parent(t->getData());
            t->setIzq(z->getDer());
            z->setDer(t);

            if (pt == NULL) {
              root = z;
            } else {
              pt->setIzq(z);
            }
          } else {
            Node* z = t->getIzq();
            Node* zd = z->getDer();
            Node* pt = parent(t->getData());

            z->setDer(zd->getIzq());
            zd->setIzq(z);
            t->setIzq(zd->getDer());
            zd->setDer(t);
            if (pt == NULL) {
              root = zd;
            } else {
              pt->setIzq(zd);
            }
          }
        } else if (isDerHeavy(t)) {
          if (isHijoDer(d)) {
            Node* z = t->getDer();
            Node* pt = parent(t->getData());
            t->setDer(z->getIzq());
            z->setIzq(t);

            if (pt == NULL) {
              root = z;
            } else {
              pt->setDer(z);
            }
          } else {
            Node* z = t->getDer();
            Node* zd = z->getIzq();
            Node* pt = parent(t->getData());

            z->setIzq(zd->getDer());
            zd->setDer(z);
            t->setDer(zd->getIzq());
            zd->setIzq(t);
            if (pt == NULL) {
              root = zd;
            } else {
              pt->setDer(zd);
            }
          }
        }
      }
    }
  }
  //RECIBE UN VALOR E INDICA CUAL ES EL PADRE DEL NODO CON ESE VALOR EVALUANDOLO DESDE UN NODO DADO
  Node* parent(int ch, Node* t) {
    if (t == NULL) {
      return NULL;
    } else {
      if (t->getData() == ch) {
        return NULL;
      } else {
        if (t->getData() > ch) {
          if (t->hasIzq()) {
            if (t->getIzq()->getData() == ch) {
              return t;
            } else {
              return parent(ch, t->getIzq());
            }
          } else {
            return NULL;
          }
        } else {
          if (t->hasDer()) {
            if (t->getDer()->getData() == ch) {
              return t;
            } else {
              return parent(ch, t->getDer());
            }
          } else {
            return NULL;
          }
        }
      }
    }
  }
  //RECIBE UN VALOR E INDICA CUAL ES EL PADRE DEL NODO CON ESE VALOR EVALUANDOLO DESDE LA RAIZ
  Node* parent(int ch) { 
      return parent(ch, root); 
      
  }
  //CALCULA SI UN NODO ES UN HIJO IZQUIERDO
  bool isHijoIzq(int ch) {
    Node* t = parent(ch);
    if (t->getIzq() != NULL) {
      return t->getIzq()->getData() == ch;
    } else {
      return false;
    }
  }
  //CALCULA SI UN NODO ES UN HIJO DERECHO
  bool isHijoDer(int ch) {
    Node* t = parent(ch);
    if (t->getDer() != NULL) {
      return t->getDer()->getData() == ch;
    } else {
      return false;
    }
  }
  //IMPRIME EL ARBOL DESDE LA RAIZ, PRIMERO IMPRIMIENDO LA RAIZ, LUEGO LOS QUE TIENE A LA IZQUIERDA Y LUEGO LOS QUE TIENE A LA DERECHA
  void preorder() { 
      preorder(root); 
  }
  //IMPRIME UN SUBARBOL DESDE UN NODO DADO, PRIMERO IMPRIMIENDO EL NODO, LUEGO LOS QUE TIENE A LA IZQUIERDA Y LUEGO LOS QUE TIENE A LA DERECHA
  void preorder(Node* r) {
    if (r != NULL) {
      cout << r->getCodigo() << "\t";
      preorder(r->getIzq());
      preorder(r->getDer());
    }
  }
  //IMPRIME EL ARBOL DESDE LA RAIZ, PRIMERO IMPRIMIENDO LOS NODOS QUE TIENE A LA IZQUIERDA, LUEGO LA RAIZ Y LUEGO LOS QUE TIENE A LA DERECHA
  void inorder() { 
      inorder(root); 
  }
  //IMPRIME UN SUBARBOL DESDE UN NODO DADO, PRIMERO IMPRIMIENDO LOS NODOS QUE TIENE A LA IZQUIERDA, LUEGO EL NODO DADO Y LUEGO LOS QUE TIENE A LA DERECHA
  void inorder(Node* n) {
    if (n != NULL){
    inorder(n->getIzq());
    cout << n->getCodigo() << "\t";
    inorder(n->getDer());
    }
  }
  //EVALUA SI UN NODO EXISTE BUSCANDOLO DESDE SU CODIGO HASH
  bool exists (string codigo) {
    int entero = valor_del_hash(codigo);
    Node* temp = root;
    while(temp!=NULL){
        if(entero==temp->getData()){
            return true;
        }else if(entero<temp->getData()){
            temp=temp->getIzq();
        }else{
            temp=temp->getDer();
        }
    }
    return false;
  }
  //IMPRIME DESDE LA RAIZ DEL ARBOL, LOS NODOS QUE COMPARTEN UN PREFIJO EN SU CODIGO CON UN CODIGO DADO SI ES QUE ESTE CODIGO EXISTE EN EL ARBOL
  void print_prefix(int digitos, string codigo){
    print_prefix(digitos, codigo, root);  
  }
  //IMPRIME DESDE UN NODO DADO, LOS NODOS QUE COMPARTEN UN PREFIJO EN SU CODIGO CON UN CODIGO DADO SI ES QUE ESTE CODIGO EXISTE EN EL ARBOL 
  void print_prefix(int digitos, string codigo, Node* n){
      if(exists(codigo) && n!=NULL){
        if (codigo.substr(0,digitos)==n->getCodigo().substr(0,digitos)){
            cout<<n->getCodigo()<<"\t";
        }
        print_prefix(digitos, codigo, n->getIzq());
        print_prefix(digitos, codigo, n->getDer());
      }
  }
  
};

int main() {
    
    srand(12345);// semilla

    //Rangos de latitud y longitud
    float lat_min = -90.0;
    float lat_max = 90.0;
    float lon_min = -180.0;
    float lon_max = 180.0;

    int numero_coordenadas = 10;


  Tree tree = Tree();
   
    for (int i = 0; i < numero_coordenadas; i++) {
        //Establece y añade las coordenadas aleatorias teniendo en cuenta los rangos de la latitud y longitud
        float lat = lat_min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (lat_max - lat_min));
        float lon = lon_min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (lon_max - lon_min));
        tree.addr(lat,lon);
    }
    
    tree.preorder();
    cout<<endl;
    tree.inorder();
    cout<<endl;
    
    tree.print_prefix(2,"k1mudwcr");
  return 0;
}

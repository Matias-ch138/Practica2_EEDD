#include <iostream>
using namespace std;
#include "Nodo.h"
#include "Iterador.h"

template<typename T>
class ListaDEnlazada{
    private:
        Nodo<T>* cabecera_;
        Nodo<T>* cola_;

        unsigned int tam_;
    public:
    /**
     * @brief constructor por defecto de una ListaDEnlazada vacia
     */
    ListaDEnlazada():cabecera_(0),cola_(0),tam_(0){}

    /**
     * @brief Constructor Copia de @class ListaDEnlazada
     * 
     * @param origen la lista que va a ser copiada
     */

    ListaDEnlazada(const ListaDEnlazada& origen) : cabecera_(0), cola_(0), tam_(0) {
        Nodo<T>* actual = origen.cabecera_;
        while (actual != 0) {
            insertaFin(actual->dato_);
            actual = actual->sig_;
        }
    }

    
    /**
     * @brief operador asignación de @class ListaDenlazada
     * @param origen lista enlazada que va a ser asignada
     */
    ListaDEnlazada &operator =(const ListaDEnlazada& origen){
        if(this!=&origen){
            while(cabecera_!=0){
                borraInicio();
            }
            Nodo<T>* actual=origen.cabecera_;
            while(actual!=0){
                insertaFin(actual->dato_);
                actual=actual->sig_;
            }
        }
        return *this;
    }
    
    /**
     * @brief devuelve el dato del inicio de la lista
     * 
     * @return T& el dato en la cabecera de la lista
     */
    T& inicio(){
        return cabecera_->dato_;
    }
    /**
     * @brief devuelve el dato del final de la lista
     * 
     * @return T& el dato en la cola de la lista
     */
    T& final(){
        return cola_->dato_;
    }
    /**
     * @brief un iterador a cabecera
     * 
     * @return Iterador<T> el iterador a cabecera
     */
    Iterador<T> iterador(){return Iterador<T> (cabecera_);}
    /**
     * @brief un iterador a cabcera
     * 
     * @return Iterador<T> el iterador a cabecera
     */
    Iterador<T> iteradorInicio() { return Iterador<T> (cabecera_) ; }
    /**
     * @brief un iterador a cola
     * 
     * @return Iterador<T> el iterador a cola
     */
    Iterador<T> iteradorFinal() { return Iterador<T>(cola_) ; }
    /**
     * @brief inserta en el final
     * 
     * @param dato el dato que queremos insertar
     */
    void insertaFin(const T& dato){
        Nodo<T>* nuevo;
        nuevo=new Nodo<T>(dato,cola_,0);
        if(cabecera_==0){
            cabecera_=nuevo;
        }
        if(cola_!=0){
            cola_->sig_=nuevo;
        }
        cola_=nuevo;
        tam_++;
    }
    /**
     * @brief inserta un dato en una posición intermedia
     * 
     * @param i iterador de la posición en el que queremos insertar el dato
     * @param dato es el dato que queremos insertar en esa posición
     */
    void inserta(Iterador &i, const T& dato){
        if(i.nodo_ == cabecera_) {
            insertaInicio(dato);
        }else{
            Nodo<T>* nuevo; 
            nuevo=new Nodo<T>(dato,i.nodo_->ant_,i.nodo_);
            i.nodo_->ant_->sig_=nuevo;
            i.nodo_->ant_=nuevo;
            tam_++;
        }
    }
    /**
     * @brief insercion al inicio
     * 
     * @param dato el dato que queremos insertar en el inicio
     */
    void insertaInicio(const T& dato){
        Nodo<T>* nuevo;
        nuevo=new Nodo<T>(dato,0,cabecera_);
        if(cola_==0){
            cola_=nuevo;
        }
        if(cabecera_!=0){
            cabecera_->ant_=nuevo;
        }
        cabecera_=nuevo;
        tam_++;
    }
    /**
     * @brief borra el primer dato de la lista
     * 
     */
    void borraInicio(){
        if(cabecera_==0) return;
            Nodo<T>* borrado=cabecera_;
            cabecera_=cabecera_->sig_;
            delete borrado;
            if(cabecera_!=0){
                cabecera_->ant_=0;
            }else{
                cola_=0;
            }
            tam_--;
    }
    /**
     * @brief borra el último dato de la lista
     * 
     */
    void borraFinal(){
        if(cola_==0) return;
        Nodo<T>* borrado = cola_;
        cola_ = cola_->ant_;
        delete borrado;
        if (cola_ != 0){
            cola_->sig_ = 0;
        }else{
            cabecera_ = 0;            }
            tam_--; 
    }
    /**
     * @brief borra un dato intermedio
     * 
     * @param i iterador apuntando al dato que queremos borrar
     */
    void borra(Iterador &i){
    if(i.nodo_ == 0) return;
    if(i.nodo_==cabecera_){
        borraInicio();
        }else if(i.nodo_==cola_){
        borraFinal();
        }else{
        Nodo<T>* borrado=i.nodo_;
        borrado->ant_->sig_=borrado->sig_;
        borrado->sig_->ant_=borrado->ant_;
        delete borrado;
        tam_--;
        }
    }
    /**
     * @brief devuelve el tamaño de la lista
     * 
     * @return unsigned int el tamaño de la lista
     */
    unsigned int tam(){
        return this->tam_;
    }
    /**
     * @brief concatena dos listas enlazadas
     * 
     * @param l es la lista que queremos concatenar
     * @return ListaDEnlazada<T>& es la lista resultado de la concatenación de las dos listas
     */
    ListaDEnlazada<T> &concatena(const ListaDEnlazada &l){
        ListaDEnlazada<T> resultado(*this);
        Nodo<T>* actual = l.cabecera_;
        while(actual !=0){
            resultado.instertaFin(actual->dato_);
            actual = actual->sig_;
        }
        return resultado;
    }
    /**
     * @brief concatena dos listas enlazadas
     * 
     * @param l es la lista que queremos concatenar
     * @return ListaDEnlazada<T>& es la lista resultado de la concatenación de las dos listas
     */
    ListaDEnlazada<T> &operator +(const ListaDEnlazada &l){
        return concatena(l);
    }
    /**
     * @brief borra una lista enlazada
     * 
     */
    ~ListaDEnlazada() {
        while (cabecera_ != 0) {
            borraInicio();
        }
    }
};
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
     * @brief constructor copia
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
     */
    ListaDEnlazada &operator =(const ListaDEnlazada<T>& origen){
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
    
    T& inicio(){
        return cabecera_->dato_;
    }

    T& final(){
        return cola_->dato_;
    }
    
    Iterador<T> iterador(){return Iterador<T> (cabecera_);}
    Iterador<T> iteradorInicio() { return Iterador<T> (cabecera_) ; }
    Iterador<T> iteradorFinal() { return Iterador<T>(cola_) ; }
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

    void inserta(Iterador<T> &i, const T& dato){
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
     * @brief 
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
     * @brief 
     * 
     * @param i 
     */
    void borra(Iterador<T> &i){
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
     * @brief 
     * 
     * @return unsigned int 
     */
    unsigned int tam(){
        return this->tam_;
    }
    /**
     * @brief 
     * 
     * @param l 
     * @return ListaDEnlazada<T>& 
     */
    ListaDEnlazada<T> &concatena(const ListaDEnlazada<T> &l){
        ListaDEnlazada<T> resultado(*this);
        Nodo<T>* actual = l.cabecera_;
        while(actual !=0){
            resultado.instertaFin(actual->dato_);
            actual = actual->sig_;
        }
        return resultado;
    }
    /**
     * @brief 
     * 
     * @param l 
     * @return ListaDEnlazada<T>& 
     */
    ListaDEnlazada<T> &operator +(const ListaDEnlazada<T> &l){
        return concatena(l);
    }
    /**
     * @brief Destroza
     * 
     */
    ~ListaDEnlazada() {
        while (cabecera_ != 0) {
            borraInicio();
        }
    }
};
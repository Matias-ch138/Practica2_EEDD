#ifndef LISTA_D_ENLAZADA_H
#define LISTA_D_ENLAZADA_H

#include <iostream>
#include <stdexcept>
using namespace std;
#include "Nodo.h"
#include "Iterador.h"

template<typename T>
class ListaDEnlazada {
private:
    Nodo<T>* cabecera_;
    Nodo<T>* cola_;
    unsigned int tam_;

public:
/**
 * @brief Constructor por defecto de ListaDEnlazada
 * 
 */
    ListaDEnlazada() : cabecera_(0), cola_(0), tam_(0) {}
/**
 * @brief Construct de copia de ListaDEnlazada
 * 
 * @param origen Objeto a copiar
 */
    ListaDEnlazada(const ListaDEnlazada& origen) : cabecera_(0), cola_(0), tam_(0) {
        Nodo<T>* actual = origen.cabecera_;
        while (actual != 0) {
            insertaFin(actual->dato_);
            actual = actual->sig_;
        }
    }
/**
 * @brief operador de asignación de ListaDEnlazada
 * 
 * @param origen objeto que se va a asignar
 * @return ListaDEnlazada& objeto asignado
 */
    ListaDEnlazada& operator=(const ListaDEnlazada& origen) {
        if (this != &origen) {
            while (cabecera_ != 0) {
                borraInicio();
            }
            Nodo<T>* actual = origen.cabecera_;
            while (actual != 0) {
                insertaFin(actual->dato_);
                actual = actual->sig_;
            }
        }
        return *this;
    }
/**
 * @brief obtener dato de la cabecera de la lista
 * 
 * @return T& el dato que hay en la cabecera
 * @throws out_of_range si la lista esta vacia
 */
    T& inicio() {
        if (cabecera_ == 0) {
            throw out_of_range("[ListaDEnlazada::inicio]: La lista esta vacia.");
        }
        return cabecera_->dato_;
    }
/**
 * @brief obtener dato de la cola de la lista
 * 
 * @return T& dato de la cola de la lista
 * @throws out_of_range si la lista esta vacia
 */
    T& Fin() {
        if (cola_ == 0) {
            throw out_of_range("[ListaDEnlazada::Fin]: La lista esta vacia.");
        }
        return cola_->dato_;
    }

    T& final() { return Fin(); }
/**
 * @brief constructor de iterador para la lista apuntando a la cabecera
 * 
 * @return Iterador<T> el iterador apuntando a la cabecera
 */
    Iterador<T> iterador() { return Iterador<T>(cabecera_); }
    /**
 * @brief constructor de iterador para la lista apuntando a la cabecera
 * 
 * @return Iterador<T> el iterador apuntando a la cabecera
 */
    Iterador<T> iteradorInicio() { return Iterador<T>(cabecera_); }
/**
 * @brief constructor de iterador para la lista apuntando a la cola
 * 
 * @return Iterador<T> el iterador apuntando a la cola
 */
    Iterador<T> iteradorFinal() { return Iterador<T>(cola_); }
/**
 * @brief insertar un dato al final de la lista
 * 
 * @param dato que insertamos al final de la lista
 */
    void insertaFin(const T& dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato, cola_, 0);
        if (cabecera_ == 0) {
            cabecera_ = nuevo;
        }
        if (cola_ != 0) {
            cola_->sig_ = nuevo;
        }
        cola_ = nuevo;
        tam_++;
    }
/**
 * @brief insertar un dato según la posición de un iterador en la lista
 * 
 * @param i el iterador apuntando a una posición de la lista 
 * @param dato que queremos almacenar en esa posición concreta de la lista
 */
    void inserta(Iterador<T>& i, const T& dato) {
        if (i.nodo_ == 0) {
            insertaFin(dato);
            return;
        }
        if (i.nodo_ == cabecera_) {
            insertaInicio(dato);
        } else {
            Nodo<T>* nuevo = new Nodo<T>(dato, i.nodo_->ant_, i.nodo_);
            i.nodo_->ant_->sig_ = nuevo;
            i.nodo_->ant_ = nuevo;
            tam_++;
        }
    }
/**
 * @brief insertar un dato al inicio de la lista
 * 
 * @param dato que queremos almacenar al inicio de la lista
 */
    void insertaInicio(const T& dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato, 0, cabecera_);
        if (cola_ == 0) {
            cola_ = nuevo;
        }
        if (cabecera_ != 0) {
            cabecera_->ant_ = nuevo;
        }
        cabecera_ = nuevo;
        tam_++;
    }
/**
 * @brief borrar el dato del inicio
 * @throws out_of_range si la lista esta vacia
 */
    void borraInicio() {
        if (cabecera_ == 0) {
            throw out_of_range("[ListaDEnlazada::borraInicio]: La lista esta vacia.");
        }

        Nodo<T>* borrado = cabecera_;
        cabecera_ = cabecera_->sig_;
        delete borrado;

        if (cabecera_ != 0) {
            cabecera_->ant_ = 0;
        } else {
            cola_ = 0;
        }
        tam_--;
    }
/**
 * @brief borrar el dato del final de la lista
 * @throws out_of_range si la lista esta vacia
 */
    void borraFinal() {
        if (cola_ == 0) {
            throw out_of_range("[ListaDEnlazada::borraFinal]: La lista esta vacia.");
        }

        Nodo<T>* borrado = cola_;
        cola_ = cola_->ant_;
        delete borrado;

        if (cola_ != 0) {
            cola_->sig_ = 0;
        } else {
            cabecera_ = 0;
        }
        tam_--;
    }
/**
 * @brief borrar un dato de la lista según la posición de un iterador en ella
 * 
 * @param i iterador apuntando a una posición de la lista
 * @throws out_of_range si la lista esta vacia
 */
    void borra(Iterador<T>& i) {
        if (i.nodo_ == 0) {
            throw out_of_range("[ListaDEnlazada::borra]: El iterador esta al final.");
        }
        Nodo<T>* siguiente = i.nodo_->sig_;

        if (i.nodo_ == cabecera_) {
            borraInicio();
        } else if (i.nodo_ == cola_) {
            borraFinal();
        } else {
            Nodo<T>* borrado = i.nodo_;
            borrado->ant_->sig_ = borrado->sig_;
            borrado->sig_->ant_ = borrado->ant_;
            delete borrado;
            tam_--;
        }
        i.nodo_ = siguiente;
    }
/**
 * @brief devuelve el tamaño de la lista
 * 
 * @return unsigned int el tamño de la lista
 */
    unsigned int tam() { return tam_; }
    /**
     * @brief concatena dos listas
     * 
     * @param l lista que vamos a concatenar 
     * @return ListaDEnlazada<T> lista concatenada 
     */
    ListaDEnlazada<T> concatena(const ListaDEnlazada& l) const {
        ListaDEnlazada<T> resultado(*this);
        Nodo<T>* actual = l.cabecera_;
        while (actual != 0) {
            resultado.insertaFin(actual->dato_);
            actual = actual->sig_;
        }
        return resultado;
    }
/**
 * @brief operador de concatenación
 * 
 * @param l lista que vamos a concatenar
 * @return ListaDEnlazada<T> lista concatenada
 */
    ListaDEnlazada<T> operator+(const ListaDEnlazada& l) const {
        return concatena(l);
    }
/**
 * @brief destructor de la lista
 * 
 */
    ~ListaDEnlazada() {
        while (cabecera_ != 0) {
            borraInicio();
        }
    }
};

#endif 
#ifndef ITERADOR_H
#define ITERADOR_H

#include <iostream>
#include <stdexcept>
using namespace std;
#include "Nodo.h"

template<typename T>
class ListaDEnlazada;

template<typename T>
class Iterador {
private:
    Nodo<T>* nodo_;
    template<typename U> friend class ListaDEnlazada;

public:
/**
 * @brief Constructor por defecto de un iterador
 * 
 */
    Iterador() : nodo_(0) {}
 /**
  * @brief Construct copia de un iterador
  * 
  * @param nodo objeto a copiar
  */
    Iterador(Nodo<T>* nodo) : nodo_(nodo) {}
/**
 * @brief ver si estamos en el último nodo de una estructura concreta
 * 
 * @return true si estamos en el ultimo nodo
 * @return false si no estamos en el ultimo nodo
 */
    bool fin() const { return nodo_ == 0; }
/**
 * @brief avanza un nodo
 * 
 */
    void avanza() {
        if (nodo_ == 0) {
            throw out_of_range("[Iterador::avanza]: El iterador esta al final.");
        }
        nodo_ = nodo_->sig_;
    }
/**
 * @brief obtiene el dato del nodo al que esta apuntando
 * 
 * @return T& el dato obtenido
 * @throws out_of_range si el iterador no apunta a nada
 */
    T& getdato() {
        if (nodo_ == 0) {
            throw out_of_range("[Iterador::getdato]: El iterador apunta a la cola.");
        }
        return nodo_->dato_;
    }
/**
 * @brief ver si tenemos un nodo anterior
 * 
 * @return true si si lo tenemos
 * @return false si no lo tenemos
 */
    bool hayAnterior() const { return nodo_ != 0 && nodo_->ant_ != 0; }
/**
 * @brief ver si tenemos un nodo siguiente
 * 
 * @return true si si lo tenemos
 * @return false si no lo tenemos
 */
    bool haySiguiente() const { return nodo_ != 0 && nodo_->sig_ != 0; }
/**
 * @brief apuntar al nodo anterior al actual
 * @throws out_of_range si no hay nodo anterior
 */
    void anterior() {
        if (nodo_ == 0 || nodo_->ant_ == 0) {
            throw out_of_range("[Iterador::anterior]: No hay elemento anterior.");
        }
        nodo_ = nodo_->ant_;
    }
/**
 * @brief apuntar al nodo siguiente al actual
 * @throws out_of_range si no hay elemento siguiente
 */
    void siguiente() {
        if (nodo_ == 0 || nodo_->sig_ == 0) {
            throw out_of_range("[Iterador::siguiente]: No hay elemento siguiente.");
        }
        nodo_ = nodo_->sig_;
    }
/**
 * @brief devuelve el dato que hay en el nodo al que el iterador esta apuntando
 * 
 * @return T& el dato que devuelve
 */
    T& dato() { return getdato(); }
};

#endif
#ifndef ITERADOR_H
#define ITERADOR_H

#include <iostream>
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
    Iterador() : nodo_(0) {}
    Iterador(Nodo<T>* nodo) : nodo_(nodo) {}

    bool fin() const { return nodo_ == 0; }
    void avanza() { nodo_ = nodo_->sig_; }
    T& getdato() { return nodo_->dato_; }

    bool hayAnterior() { return nodo_->ant_ != 0; }
    bool haySiguiente() { return nodo_->sig_ != 0; }
    void anterior() { nodo_ = nodo_->ant_; }
    void siguiente() { nodo_ = nodo_->sig_; }
    T& dato() { return nodo_->dato_; }
};

#endif
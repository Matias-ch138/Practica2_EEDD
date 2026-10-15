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
    Iterador() : nodo_(0) {}
    Iterador(Nodo<T>* nodo) : nodo_(nodo) {}

    bool fin() const { return nodo_ == 0; }
    void avanza() {
        if (nodo_ == 0) {
            throw out_of_range("[Iterador::avanza]: El iterador esta al final.");
        }
        nodo_ = nodo_->sig_;
    }

    T& getdato() {
        if (nodo_ == 0) {
            throw out_of_range("[Iterador::getdato]: El iterador esta al final.");
        }
        return nodo_->dato_;
    }

    bool hayAnterior() const { return nodo_ != 0 && nodo_->ant_ != 0; }
    bool haySiguiente() const { return nodo_ != 0 && nodo_->sig_ != 0; }

    void anterior() {
        if (nodo_ == 0 || nodo_->ant_ == 0) {
            throw out_of_range("[Iterador::anterior]: No hay elemento anterior.");
        }
        nodo_ = nodo_->ant_;
    }

    void siguiente() {
        if (nodo_ == 0 || nodo_->sig_ == 0) {
            throw out_of_range("[Iterador::siguiente]: No hay elemento siguiente.");
        }
        nodo_ = nodo_->sig_;
    }

    T& dato() { return getdato(); }
};

#endif
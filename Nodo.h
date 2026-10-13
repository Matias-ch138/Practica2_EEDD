#ifndef NODO_H
#define NODO_H

#include <iostream>

template<typename T>
class Nodo {
    public:
    T dato_;
    Nodo<T>* ant_;
    Nodo<T>* sig_;
    Nodo(const T& aDato, Nodo<T>* aAnt, Nodo<T>* aSig) : dato_(aDato), ant_(aAnt), sig_(aSig) {}
};

#endif
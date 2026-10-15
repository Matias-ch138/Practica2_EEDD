#ifndef NODO_H
#define NODO_H

#include <iostream>

template<typename T>
class Nodo {
    public:
    T dato_;
    Nodo<T>* ant_;
    Nodo<T>* sig_;
    /**
     * @brief Constructor parametrizado de un Nodo
     * 
     * @param aDato el dato que se guarda
     * @param aAnt puntero a nodo anterior
     * @param aSig puntero a nodo siguiente
     */
    Nodo(const T& aDato, Nodo<T>* aAnt, Nodo<T>* aSig) : dato_(aDato), ant_(aAnt), sig_(aSig) {}
};

#endif
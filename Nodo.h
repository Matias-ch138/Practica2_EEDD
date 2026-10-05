#include <iostream>
using namespace std;

template<typename T>
class Nodo{
    public:
    T dato_;
    Nodo* ant_;
    Nodo* sig_;
    Nodo(T& aDato, Nodo* aAnt, Nodo* aSig)dato_(aDato),ant_(aAnt),sig_(aSig){};
};
#ifndef PARQUE_H
#define PARQUE_H

#include <iostream>
#include <string>
#include "Especie.h"
#include "VDinamico.h"
using namespace std;


class Parque {
private:
    int cod_parque;
    string nbre_parque;
    VDinamico<Especie*> contains_;
public:
    Parque();
    Parque(int cod, string nombre);
    ~Parque();

    int get_cod_parque() const;
    void set_cod_parque(int cod);

    string get_nbre_parque() const;
    void set_nbre_parque(string nombre);
    VDinamico<Especie> get_especies() const;
    const VDinamico<Especie*>& get_contains() const;

    void insertarEspecie(Especie &esp);
    bool existeNbreCom(string ncomun);
    bool existeNbreCie(string ncient);
};

#endif
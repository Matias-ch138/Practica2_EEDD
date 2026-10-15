#ifndef CONTROLPARQUES_H
#define CONTROLPARQUES_H

#include <iostream>
#include <string>
using namespace std;

#include "Especie.h"
#include "Parque.h"
#include "VDinamico.h"
#include "ListaDEnlazada.h"
#include "Iterador.h"

class ControlParques {
private:
    VDinamico<Especie> varieties;
    ListaDEnlazada<Parque> parks;

public:
    ControlParques();
    ControlParques(const string& rutaEspecies, const string& rutaParques);

    void asignarEspecieParque(Especie &e, Parque &p);
    int contarEspecieParque(string ncomun);
    VDinamico<Especie> listadoEspecieSubNbre(string cadena);
    Parque* buscarParque(const string& nbre_parque);
    bool eliminarParque(string nombre);

    VDinamico<Especie>& get_varieties();
    const VDinamico<Especie>& get_varieties() const;
    ListaDEnlazada<Parque>& get_parks();
    const ListaDEnlazada<Parque>& get_parks() const;
    ListaDEnlazada<Parque>& get_nbre_parque();
    const ListaDEnlazada<Parque>& get_nbre_parque() const;
};

#endif
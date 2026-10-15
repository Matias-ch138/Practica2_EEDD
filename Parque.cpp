#include "Parque.h"

Parque::Parque() : cod_parque(0), nbre_parque("") {}

Parque::Parque(int cod, string nombre) : cod_parque(cod), nbre_parque(nombre) {}

Parque::~Parque() = default;

int Parque::get_cod_parque() const {
    return cod_parque;
}

void Parque::set_cod_parque(int cod) {
    cod_parque = cod;
}

string Parque::get_nbre_parque() const {
    return nbre_parque;
}   

void Parque::set_nbre_parque(string nombre) {
    nbre_parque = nombre;
}

VDinamico<Especie> Parque::get_especies() const {
    VDinamico<Especie> especies;
    for (unsigned int i = 0; i < contains_.gettLogico(); ++i) {
        especies.insertar(*contains_[i]);
    }
    return especies;
}

const VDinamico<Especie*>& Parque::get_contains()const{
    return contains_;
}

void Parque::insertarEspecie(Especie &esp){
    contains_.insertar(&esp);
}

bool Parque::existeNbreCom(string ncomun) {
    for (unsigned int i = 0; i < contains_.gettLogico(); ++i) {
        if (contains_[i]->getnombre_comun() == ncomun) {
            return true;
        }
    }
    return false;
}

bool Parque::existeNbreCie(string ncient) {
    for (unsigned int i = 0; i < contains_.gettLogico(); ++i) {
        if (contains_[i]->getnombre_cientifico() == ncient) {
            return true;
        }
    }
    return false;
}
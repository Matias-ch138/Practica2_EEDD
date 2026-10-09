#include "Parque.h"

Parque::Parque(int cod, string nombre):cod_parque(cod),nbre_parque(nombre){}
Parque::~Parque(){
    delete contains_;
}
void Parque::insertarEspecie(Especie &esp){
    this->contains_->insertar(esp);
}
bool Parque::existeNbreCom(string ncomun){
    for(int i=0; i<contains_->getLogico(); i++){
        if(contains_[i].getnombre_comun==ncomun){
            return true;
        }
    }
    return false;
}
bool Parque::existenNbreCie(string ncient){
    for(int i=0; i<contains_->getLogico(); i++){
        if(contains_[i].getnombre_cientifico==ncient){
            return true;
        }
    }
    return false;
}
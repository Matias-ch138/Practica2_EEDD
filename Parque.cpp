#include "Parque.h"
/**
 * @brief Constructor por defecto de un Parque
 * 
 */
Parque::Parque() : cod_parque(0), nbre_parque("") {}
/**
 * @brief Constructor parametrizado de un Parque
 * 
 * @param cod codigo del parque
 * @param nombre nombre del parque
 */
Parque::Parque(int cod, string nombre) : cod_parque(cod), nbre_parque(nombre) {}
/**
 * @brief Destructor de un Parque
 * 
 */
Parque::~Parque() = default;
/**
 * @brief obtener el codigo de un parque
 * 
 * @return int codigo obtenido del parque
 */
int Parque::get_cod_parque() const {
    return cod_parque;
}
/**
 * @brief establecer el codigo de un parque
 * 
 * @param cod codigo a establecer del parque
 */
void Parque::set_cod_parque(int cod) {
    cod_parque = cod;
}
/**
 * @brief obtener el nombre del parque
 * 
 * @return string nombre obtenido del parque
 */
string Parque::get_nbre_parque() const {
    return nbre_parque;
}   
/**
 * @brief establecer el nombre del parque
 * 
 * @param nombre nombre a establecer del parque
 */
void Parque::set_nbre_parque(string nombre) {
    nbre_parque = nombre;
}
/**
 * @brief Especies de un parque
 * 
 * @return VDinamico<Especie> especies obtenidas de un parque
 */
VDinamico<Especie> Parque::get_especies() const {
    VDinamico<Especie> especies;
    for (unsigned int i = 0; i < contains_.gettLogico(); ++i) {
        especies.insertar(*contains_[i]);
    }
    return especies;
}
/**
 * @brief Especies de un parque
 * 
 * @return VDinamico<Especie> especies obtenidas de un parque
 */
const VDinamico<Especie*>& Parque::get_contains()const{
    return contains_;
}
/**
 * @brief inserta una especie en un parque
 * 
 * @param esp especie que vamos a insertar
 */
void Parque::insertarEspecie(Especie &esp){
    contains_.insertar(&esp);
}
/**
 * @brief existe un nombre comun
 * 
 * @param ncomun el nombre comun
 * @return true si existe
 * @return false si no existe
 */
bool Parque::existeNbreCom(string ncomun) {
    for (unsigned int i = 0; i < contains_.gettLogico(); ++i) {
        if (contains_[i]->getnombre_comun() == ncomun) {
            return true;
        }
    }
    return false;
}
/**
 * @brief existe un nombre cient
 * 
 * @param ncient el nombre cient
 * @return true si existe
 * @return false si no existe
 */
bool Parque::existeNbreCie(string ncient) {
    for (unsigned int i = 0; i < contains_.gettLogico(); ++i) {
        if (contains_[i]->getnombre_cientifico() == ncient) {
            return true;
        }
    }
    return false;
}
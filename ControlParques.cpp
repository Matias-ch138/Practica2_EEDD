#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include "ControlParques.h"
#include "LectorCSV.h"
using namespace std;
static bool leerCampoCSV(const string& linea, size_t& posicion, string& campo) {
    campo.clear();
    bool entreComillas = posicion < linea.size() && linea[posicion] == '"';
    if (entreComillas) {
        ++posicion;
    }

    while (posicion < linea.size()) {
        char caracter = linea[posicion];
        if (entreComillas && caracter == '"') {
            if (posicion + 1 < linea.size() && linea[posicion + 1] == '"') {
                campo += '"';
                posicion += 2;
            } else {
                entreComillas = false;
                ++posicion;
            }
        } else if (!entreComillas && caracter == ',') {
            ++posicion;
            return true;
        } else {
            campo += caracter;
            ++posicion;
        }
    }

    return !entreComillas;
}
/**
 * @brief Constructor por defecto de ControlParques
 * 
 */
ControlParques::ControlParques(){
    
}
/**
 * @brief Constructor parametrizado de ControlParques
 * 
 * @param rutaEspecies ruta del archivo donde se guardan las Especies
 * @param rutaParques ruta del archivo donde se guardan los Parques
 */
ControlParques::ControlParques(const string& rutaEspecies, const string& rutaParques){
    LectorCSV lector;
    lector.cargar(varieties, rutaEspecies);
    varieties.ordenar();

    ifstream fichero(rutaParques);
    if (fichero.is_open()) {
        string linea;
        while (getline(fichero, linea)) {
            if (linea.empty()) continue;
            
            string cod_str, nombre_parque;
            size_t posicion = 0;

            if (leerCampoCSV(linea, posicion, cod_str) &&
                leerCampoCSV(linea, posicion, nombre_parque)) {
                try {
                    int cod = stoi(cod_str);
                    Parque p(cod, nombre_parque);
                    parks.insertaFin(p);
                } catch (const invalid_argument& e) {
                    continue;
                }
            }
        }
        fichero.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo de parques: " << rutaParques << endl;
    }
}
/**
 * @brief asigna una especie a un parque
 * 
 * @param e la especia a asignar
 * @param p el parque al que se le va a asignar la especie
 */
void ControlParques::asignarEspecieParque(Especie &e, Parque &p){
    p.insertarEspecie(e);
}
/**
 * @brief numero de especies con @param ncomun en un parque
 * 
 * @param ncomun nombre comun de la especie
 * @return int contador de especies con ese @ncomun
 */
int ControlParques::contarEspecieParque(string ncomun){
    int contador = 0;
    Iterador<Parque> it = parks.iteradorInicio();
    while(!it.fin()){
        if(it.getdato().existeNbreCom(ncomun)){
            contador++;
        }
        it.avanza();
    }
    return contador;
}
/**
 * @brief listado especies cuyo subnombre cientifico es @param cadena
 * 
 * @param cadena subnombre cientifico que buscamos
 * @return VDinamico<Especie> vector de especies con ese subnombre cientifico
 */
VDinamico<Especie> ControlParques::listadoEspecieSubNbre(string cadena){
    VDinamico<Especie> resultados;
    for(int i=0; i<varieties.gettLogico(); i++){
        if(varieties[i].getnombre_cientifico().find(cadena) != string::npos){
            resultados.insertar(varieties[i]);
        }
    }
    return resultados;
}
/**
 * @brief busca un parque cuyo nombre es @param nbre_parque
 * 
 * @param nbre_parque nombre del parque que estamos buscando
 * @return Parque* puntero a el parque que buscabamos
 */
Parque* ControlParques::buscarParque(const string& nbre_parque){
    Iterador<Parque> it = parks.iteradorInicio();
    while(!it.fin()){
        if(it.getdato().get_nbre_parque() == nbre_parque){
            return &it.getdato();
        }
      it.avanza();  
    }
    return nullptr;
}
/**
 * @brief elimina un parque cuyo nombre es @param nombre
 * 
 * @param nombre del parque a eliminar
 * @return true si se ha eliminado
 * @return false si no se ha eliminado
 */
bool ControlParques::eliminarParque(string nombre) {
    Iterador<Parque> it = parks.iteradorInicio();
    while (!it.fin()){
        if(it.getdato().get_nbre_parque()== nombre){
            parks.borra(it);
            return true;
        }
        it.avanza();
    }
    return false;
}
/**
 * @brief construye un vector dinamico con todas las variedades de especies de todos los parques
 * 
 * @return VDinamico<Especie>& vector dinamico con las variedades de especies de todos los parques
 */
VDinamico<Especie>& ControlParques::get_varieties(){
    return varieties;
}
/**
 * @brief construye un vector dinamico con todas las variedades de especies de todos los parques
 * 
 * @return VDinamico<Especie>& vector dinamico con las variedades de especies de todos los parques
 */
const VDinamico<Especie>& ControlParques::get_varieties() const{
    return varieties;
}
/**
 * @brief construye una ListaDEnlazada con todos los parques que hay en control de parques
 * 
 * @return ListaDEnlazada<Parque>& ListaDEnlazada con todos los parques que hay en control de parques
 */
ListaDEnlazada<Parque>& ControlParques::get_parks(){
    return parks;
}
/**
 * @brief construye una ListaDEnlazada con todos los parques que hay en control de parques
 * 
 * @return ListaDEnlazada<Parque>& ListaDEnlazada con todos los parques que hay en control de parques
 */
const ListaDEnlazada<Parque>& ControlParques::get_parks() const{
    return parks;  
}
/**
 * @brief onbtener una lista doblemente enlazada con todos los nombres de los parques
 * 
 * @return ListaDEnlazada<Parque>& lista doblemente enlazada con todos los nombre de los parques
 */
ListaDEnlazada<Parque>& ControlParques::get_nbre_parque(){
    return parks;
}
/**
 * @brief onbtener una lista doblemente enlazada con todos los nombres de los parques
 * 
 * @return ListaDEnlazada<Parque>& lista doblemente enlazada con todos los nombre de los parques
 */
const ListaDEnlazada<Parque>& ControlParques::get_nbre_parque() const{
    return parks;
}
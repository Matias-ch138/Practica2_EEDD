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

ControlParques::ControlParques(){
    
}
ControlParques::ControlParques(const string& rutaEspecies, const string& rutaParques){
// 1. Cargar el vector dinámico de especies usando la clase LectorCSV
    LectorCSV lector;
    lector.cargar(varieties, rutaEspecies);
    varieties.ordenar();

    // 2. Cargar la lista doblemente enlazada de parques desde el CSV
    ifstream fichero(rutaParques);
    if (fichero.is_open()) {
        string linea;
        // Leer línea a línea
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
                    // Si la primera fila son cabeceras, stoi fallará, la ignoramos.
                    continue;
                }
            }
        }
        fichero.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo de parques: " << rutaParques << endl;
    }
}

void ControlParques::asignarEspecieParque(Especie &e, Parque &p){
    p.insertarEspecie(e);
}
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

VDinamico<Especie> ControlParques::listadoEspecieSubNbre(string cadena){
    VDinamico<Especie> resultados;
    for(int i=0; i<varieties.gettLogico(); i++){
        if(varieties[i].getnombre_cientifico().find(cadena) != string::npos){
            resultados.insertar(varieties[i]);
        }
    }
    return resultados;
}

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

VDinamico<Especie>& ControlParques::get_varieties(){
    return varieties;
}
const VDinamico<Especie>& ControlParques::get_varieties() const{
    return varieties;
}
ListaDEnlazada<Parque>& ControlParques::get_parks(){
    return parks;
}
const ListaDEnlazada<Parque>& ControlParques::get_parks() const{
    return parks;  
}
ListaDEnlazada<Parque>& ControlParques::get_nbre_parque(){
    return parks;
}
const ListaDEnlazada<Parque>& ControlParques::get_nbre_parque() const{
    return parks;
}
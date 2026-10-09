#include <iostream>
using namespace std;
#include "Especie.h"
#include "Parque.h"
#include "VDinamico.h"
#include "ListaDEnlazada.h"

class ControlParques{
  private:
  
  public:
  void asignarEspecieParque(Especie &e,Parque &p);
  int contarEspecieParque(string ncomun);  
  Especie listadoEspecieSubNbre(string cadena);
  Parque buscarParque(string nbre_parque);
};
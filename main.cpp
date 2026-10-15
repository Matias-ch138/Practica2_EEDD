#include <iostream>

#include "ControlParques.h"
#include "LectorCSV.h"
#include "ListaDEnlazada.h"
#include "Parque.h"

template <class T>
void mostrarLista(ListaDEnlazada<T> l)
{
    for (Iterador<T> it = l.iterador(); !it.fin(); it.avanza())
    {
        std::cout << std::to_string(it.getdato()) << "  ";
    }
    cout << endl;
}


Iterador<Parque> buscaParque(ListaDEnlazada<Parque>& lista, string nombre)
{
    Iterador<Parque> it = lista.iterador();
    for (it; !it.fin(); it.avanza())
    {
        if (it.getdato().get_nbre_parque() == nombre)
        {
            return it;
        }
    }
    return it;
}

bool buscaEspecieNbrComun(const VDinamico<Especie*>& vector, string nombreComun)
{
    int n = vector.gettLogico();
    for (int i = 0; i < n; ++i)
    {
        if (vector[i]->get_nombre_comun() == nombreComun)
        {
            return true;
        }
    }
    return false;
}

bool buscaEspecieNbrCientif(const VDinamico<Especie*>& vector, string nombreCentif)
{
    int n = vector.gettLogico();
    for (int i = 0; i < n; ++i)
    {
        string s = vector[i]->get_nombre_cientifico();
        if (vector[i]->get_nombre_cientifico() == nombreCentif)
        {
            return true;
        }
    }
    return false;
}

const string RUTA_ESPECIES = "data/arbolado-especies.csv";
const string RUTA_PARQUES = "data/parques.csv";

int main()
{

    cout << "PROGRAMA DE PRUEBA 1" << endl;

    //Crear la lista vacía
    ListaDEnlazada<int> lista;

    cout<<"Insetar al final del 101 al 200"<<endl;

    for (int i = 101; i <= 200; ++i)
    {
        lista.insertaFin(i);
    }
    mostrarLista(lista);

    cout<<endl<<"Insertar por el comienzo del 1 al 98"<<endl;
    for (int i = 98; i >= 1; --i)
    {
        lista.insertaInicio(i);
    }
    mostrarLista(lista);

    cout<<endl<<"insertar el dato 100 delante del 101"<<endl;
    Iterador<int> itint = lista.iterador();
    while (!itint.fin() && itint.getdato() != 101)
    {
        itint.avanza();
    }
    if (!itint.fin())
    {
        lista.inserta(itint, 100);
    }
    mostrarLista(lista);

    itint = lista.iterador();
    while (!itint.fin() && itint.getdato() != 100)
    {
        itint.avanza();
    }
    if (!itint.fin())
    {
        lista.inserta(itint, 99);
    }
    mostrarLista(lista);

    cout<<endl<<"Borrar los 10 primeros y los 10 últimos"<<endl;
    for (int i = 0; i < 10; ++i)
    {
        lista.borraInicio();
        lista.borraFinal();
    }
    mostrarLista(lista);

    cout<<endl<<"Borrar de la lista todos los múltiplos de 10"<<endl;
    for (Iterador<int> it = lista.iterador(); !it.fin();)
    {
        if (it.getdato() % 10 == 0)
        {
            lista.borra(it);
            it = lista.iterador();
        }
        else
        {
            it.avanza();
        }
    }
    mostrarLista(lista);

    cout<<endl<<"PULSAR CUALQUIER TECLA PARA CONTINUAR"<<endl;
    std::cin.get();

    cout << "PROGRAMA DE PRUEBA 2" << endl;
    ControlParques cp(RUTA_ESPECIES, RUTA_PARQUES);

    //Variables fuera del bucle por eficiencia
    VDinamico<Especie>* especies = &cp.get_varieties();
    ListaDEnlazada<Parque>* parques = &cp.get_parks();

    for (int i = 0; i < especies->gettLogico(); ++i)
    {
        Iterador<Parque> it = parques->iterador();
        Especie& esp = (*especies)[i];
        int tipo = esp.get_tipo_planta();
        for (it; !it.fin(); it.avanza())
        {
            Parque& pq = it.getdato();
            int resto = pq.get_cod_parque() % 2;

            //parques con codigo par
            if ((tipo == ARBUSTO || tipo == CONIFERA || tipo == PALMACEA ||
                tipo == HERB_PERENNES || tipo == FRONDOSA) && (resto == 0))
            {
                pq.insertarEspecie(esp);
                //Parques con codigo impar
            }
            else if ((tipo == TAPIZANTE_TREPADORA || tipo == CACTACEA_SUCULENTA ||
                tipo == SUBTROPICAL_TROPICAL ||
                tipo == HERB_ANUAL || tipo == HERB_ANUALES) && (resto == 1))
            {
                pq.insertarEspecie(esp);
            }
        }
    }

    cout << endl << "ASIGNACIÓN DE ESPECIES A LOS PARQUES" << endl;
    for (Iterador<Parque> it = parques->iterador(); !it.fin(); it.avanza())
    {
        cout << "  Codigo: " << to_string(it.getdato().get_cod_parque()) << " nombre: " << it.getdato().
            get_nbre_parque() << " total especies: " << to_string(
                it.getdato().get_contains().gettLogico()) << endl;
    }


    cout << endl << "BUSCAR EN PARQUE PRINCESA LEONOR LOS NOMBRES COMUNES EUCALIPTO ROJO Y ARCE DE SIERRA" << endl;
    Parque& princLeonor = buscaParque(cp.get_parks(), "PARQUE PRINCESA LEONOR").getdato();
    //Debe estar
    if (buscaEspecieNbrComun(princLeonor.get_contains(), "Eucalipto rojo"))
    {
        cout << "  Encontrado Eucalipto rojo" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Eucalipto rojo" << endl;
    }

    //No debe estar
    if (buscaEspecieNbrComun(princLeonor.get_contains(), "Arce de sierra"))
    {
        cout << "  Encontrado Arce de sierra" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Arce de sierra" << endl;
    }

    cout << endl << "BUSCAR EN PARQUE MADRID RIO LOS NOMBRES CIENTÍFICOS HEBE FLORIBUNDA Y ANANAS COMOSA" << endl;
    Parque& madridRio = buscaParque(cp.get_parks(), "PARQUE MADRID RIO").getdato();
    //No debe estar
    if (buscaEspecieNbrCientif(madridRio.get_contains(), "Hebe floribunda"))
    {
        cout << "  Encontrado Hebe floribunda" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Hebe floribunda" << endl;
    }

    //No debe estar
    if (buscaEspecieNbrCientif(madridRio.get_contains(), "Ananas comosa"))
    {
        cout << "  Encontrado Ananas comosa" << endl;
    }
    else
    {
        cout << "  No se ha encontrado Ananas comosa" << endl;
    }

    cout << endl << "BUSCAR PARQUES JUAN CARLOS III Y VIVERO DE MIGAS CALIENTES" << endl;
    //No debe estar
    Iterador<Parque> it = buscaParque(cp.get_parks(), "PARQUE JUAN CARLOS III");
    if (it.fin())
    {
        cout << "  No se ha encontrado parque JUAN CARLOS III" << endl;
    }
    else
    {
        cout<<"  codigo: " << to_string(it.getdato().get_cod_parque()) <<" nombre: "<< it.getdato().get_nbre_parque()<< endl;
    }

    Iterador<Parque> it2 = buscaParque(cp.get_parks(), "VIVERO DE MIGAS CALIENTES");
    //Sí debe estar
    if (it2.fin())
    {
        cout << "  No se ha encontrado parque VIVERO DE MIGAS CALIENTES" << endl;
    }
    else
    {
        cout<<"  codigo: " << to_string(it2.getdato().get_cod_parque()) <<" nombre: "<< it2.getdato().get_nbre_parque()<< endl;
    }

    cout<< endl<<"BUSCAR ESPECIES CON LA SUBCADENA ROSA EN SU NOMBRE CIENTÍFICO"<<endl;
    for (int i =0; i < especies->gettLogico(); ++i)
    {
        string ncientif = (*especies)[i].get_nombre_cientifico();
        if (ncientif.find("rosa") != string::npos)
        {
            (*especies)[i].mostrarInfo();
        }
    }

    cout<< endl<<"CONTAR CUÁNTOS PARQUES TIENEN LA ESPECIE CON NOMBRE COMÚN ABETO"<<endl;
    int total = cp.contarEspecieParque("Abeto");
    cout<<"  Total: "<<total<<endl;
    cout<<"==========================="<<endl;
    cout<<"Parte Parejas: "<<endl;
    string parqueEliminar= "VIVERO DE MIGAS CALIENTES";
    if(cp.eliminarParque(parqueEliminar)){
        cout<<"Se ha borrado el parque cuyo nombre es: "<<parqueEliminar<<endl;
    }else cout<<"No se ha borrado ningún parque"<<endl;
    cout<<"Comprobación de que se ha eliminado el parque: "<<endl;
    Iterador<Parque> it3 = buscaParque(cp.get_parks(), "VIVERO DE MIGAS CALIENTES");
    if (it3.fin())
    {
        cout << "  No se ha encontrado parque VIVERO DE MIGAS CALIENTES" << endl;
    }
    else
    {
        cout<<"  codigo: " << to_string(it3.getdato().get_cod_parque()) <<" nombre: "<< it3.getdato().get_nbre_parque()<< endl;
    }


    return 0;
}

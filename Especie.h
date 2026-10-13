#ifndef ESPECIE_H
#define ESPECIE_H

#include <iostream>
#include <string>
using namespace std;

enum TipoPlanta {
    ARBUSTO,
    CONIFERA,
    PALMACEA,
    HERB_PERENNES,
    FRONDOSA,
    TAPIZANTE_TREPADORA,
    CACTACEA_SUCULENTA,
    SUBTROPICAL_TROPICAL,
    HERB_ANUAL,
    HERB_ANUALES,
    OTRO
};

class Especie {
private:
    string codigoEspecie_;
    string nombreComun_;
    string nombreCientifico_;
    string tipoPlanta_;

public:
    Especie() = default;
    Especie(string codigoEspecie, string nombreComun, string nombreCientifico, string tipoPlanta) {
        codigoEspecie_ = codigoEspecie;
        nombreComun_ = nombreComun;
        nombreCientifico_ = nombreCientifico;
        tipoPlanta_ = tipoPlanta;
    }

    // Getters y setters tradicionales
    string getcodigo_especie() const;
    void set_codigo_especie(string codigoEspecie);
    string getnombre_comun() const;
    void setNombreComun(string nombreComun);
    string getnombre_cientifico() const;
    void setNombreCientifico(string nombreCientifico);
    string gettipo_planta() const;
    void setTipoPlanta(string tipoPlanta);

    // Alias para que coincida con el uso de main.cpp REVISAR=======================================================
    string get_codigo_especie() const { return codigoEspecie_; }
    string get_nombre_comun() const { return nombreComun_; }
    string get_nombre_cientifico() const { return nombreCientifico_; }
    string get_tipo_planta_str() const { return tipoPlanta_; }

    int get_tipo_planta() const {
        if (tipoPlanta_ == "ARBUSTO") return ARBUSTO;
        if (tipoPlanta_ == "CONIFERA") return CONIFERA;
        if (tipoPlanta_ == "PALMACEA") return PALMACEA;
        if (tipoPlanta_ == "HERB_PERENNES") return HERB_PERENNES;
        if (tipoPlanta_ == "FRONDOSA") return FRONDOSA;
        if (tipoPlanta_ == "TAPIZANTE_TREPADORA") return TAPIZANTE_TREPADORA;
        if (tipoPlanta_ == "CACTACEA_SUCULENTA") return CACTACEA_SUCULENTA;
        if (tipoPlanta_ == "SUBTROPICAL_TROPICAL") return SUBTROPICAL_TROPICAL;
        if (tipoPlanta_ == "HERB_ANUAL") return HERB_ANUAL;
        if (tipoPlanta_ == "HERB_ANUALES") return HERB_ANUALES;
        return OTRO;
    }

    void mostrarInfo() const;
    bool operator<(const Especie& origen) const;
    bool operator==(const Especie& origen) const;
};

#endif
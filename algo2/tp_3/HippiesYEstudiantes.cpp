//
// Created by Matias on 25/11/2015.
//

#include "HippiesYEstudiantes.h"

namespace aed2{

    HippiesYEstudiantes::HippiesYEstudiantes() : _hippies(), _estudiantes() { }

    void HippiesYEstudiantes::DefinirHippie(String nombre, const Posicion& pos) {
        _hippies.Definir(nombre, pos);
    }

    void HippiesYEstudiantes::DefinirEstudiante(String nombre, const Posicion &pos) {
        _estudiantes.Definir(nombre, pos);
    }

    Posicion HippiesYEstudiantes::PosHippieYEstudiante(String nombre) const {
        if(EsEst(nombre)){
            return _estudiantes.Obtener(nombre);
        } else {
            return _hippies.Obtener(nombre);
        }
    }

    bool HippiesYEstudiantes::Esta(String nombre) const {
        return (_estudiantes.Def(nombre)) || (_hippies.Def(nombre));
    }

    bool HippiesYEstudiantes::EsEst(String nombre) const {
        return _estudiantes.Def(nombre);
    }

    bool HippiesYEstudiantes::EsHippie(String nombre) const {
        return _hippies.Def(nombre);
    }

    const Conj<String> HippiesYEstudiantes::Estudiantes() const {
        return _estudiantes.Claves();
    }

    const Conj<String> HippiesYEstudiantes::Hippies() const {
        return _hippies.Claves();
    }

    void HippiesYEstudiantes::Borrar(String nombre) {
        if(EsEst(nombre)){
            _estudiantes.Eliminar(nombre);
        } else {
            _hippies.Eliminar(nombre);
        }
    }

}

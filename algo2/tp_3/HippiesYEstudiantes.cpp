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

    bool HippiesYEstudiantes::Esta(String nombre) {
        return (_estudiantes.Def(nombre)) || (_hippies.Def(nombre));
    }

    bool HippiesYEstudiantes::EsEst(String nombre) {
        return _estudiantes.Def(nombre);
    }

    bool HippiesYEstudiantes::EsHippie(String nombre) {
        return _hippiess.Def(nombre);
    }

    const Conj<String>& HippiesYEstudiantes::Estudiantes() {
        return _estudiantes.Claves();
    }

    const Conj<String>& HippiesYEstudiantes::Hippies() {
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

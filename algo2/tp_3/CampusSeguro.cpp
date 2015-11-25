//
// Created by Matias on 25/11/2015.
//

#include "CampusSeguro.h"

namespace aed2 {

    CampusSeguro::CampusSeguro(const Campus& c, const Dicc<Nat, Posicion>& dA) : _campus(c.Filas(), c.Columnas()), _agentes(dA), _HipYEst(), _posOcupadasAgentes(c.Filas(), c.Columnas()), _posOcupadasEstudiantes(c.Filas(), c.Columnas()), _posOcupadasHippies(c.Filas(), c.Columnas()), _agentesOrdenados(dA.CantClaves()) {
        Agentes::Iterador itAgentes = _agentes.CrearIt();
        Nat i = 0;
        while(itAgentes.HaySiguiente()) {
            _posOcupadasAgentes.Definir(itAgentes.SiguienteDatos()._posicion, itAgentes);
            _agentesOrdenados.Definir(i, {itAgentes.SiguientePlaca(), itAgentes});
            i++;
            itAgentes.Avanzar();
        }

        Ordenar(_agentesOrdenados); //HACCER ALGUN SORT, NO IMPORTA LA COMPLEJIDAD
        //Los algoritmos no cambian, excepto moverAgente, que tiene que buscar el iterador del agente en _agentesOrdenados (busqueda binaria) en vez de en la matriz _posOcupadasAgentes
    }

    void CampusSeguro::IngresarEstudiante(String nombre, Posicion p){

    }

    void CampusSeguro::IngresarHippie(String nombre, Posicion p){

    }

    void CampusSeguro::MoverEstudiante(String nombre, Direccion dir){

    }

    void CampusSeguro::MoverHippie(String nombre)
}

    void CampusSeguro::MoverAgente(Nat placa){

    }

    const Campus& CampusSeguro::dameCampus(){

    }

    const Conj<String>& CampusSeguro::Estudiantes(){

    }

    const Conj<String>& CampusSeguro::CampusSeguro::Hippies(){

    }

    const Conj<Placa>& CampusSeguro::dameAgentes(){

    }

    const Posicion& CampusSeguro::PosHippieYEstudiante(String nombre){

    }

    const Posicion& CampusSeguro::PosAgente(Nat placa){

    }

    const Nat& CampusSeguro::CantSanciones(Nat placa){

    }

    const Nat& CampusSeguro::CantHippiesAtrapados(Nat placa){

    }

    Nat CampusSeguro::CantHippies(){

    }

    Nat CampusSeguro::CantEstudiantes(){

    }

    const Nat& CampusSeguro::MasVigilante(){

    }

    const Conj<Nat>& CampusSeguro::ConMismasSanciones(Nat placa){

    }

    const Conj<Nat>& CampusSeguro::ConKSanciones(Nat k){

    }

}
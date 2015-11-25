#ifndef TP_3_CAMPUSSEGURO_H
#define TP_3_CAMPUSSEGURO_H

#include "campus.h"
#include "Agentes.h"
#include "HippiesYEstudiantes.h"

namespace aed2{
    class CampusSeguro{
    public:
        CampusSeguro(const Campus& c, const Dicc<Nat,Posicion>& dA);

        void IngresarEstudiante(String nombre, Posicion p);
        void IngresarHippie(String nombre, Posicion p);

        void MoverEstudiante(String nombre, Direccion dir);
        void MoverHippie(String nombre);
        void MoverAgente(Nat placa);

        const Campus& dameCampus();

        const Conj<String>& Estudiantes();
        const Conj<String>& Hippies();
        const Conj<Nat>& dameAgentes();

        const Posicion& PosHippieYEstudiante(String nombre);
        const Posicion& PosAgente(Nat placa);

        const Nat& CantSanciones(Nat placa);
        const Nat& CantHippiesAtrapados(Nat placa);

        Nat CantHippies();
        Nat CantEstudiantes();

        const Nat& MasVigilante();
        const Conj<Nat>& ConMismasSanciones(Nat placa);
        const Conj<Nat>& ConKSanciones(Nat k);

    private:

        struct aOrdenadoItem {
            Nat _placa;
            Agentes::Iterador _itAgente;
        };

        Campus _campus;
        HippiesYEstudiantes _HipYEst;
        Agentes _agentes;
        Matriz<String> _posOcupadasHippies;
        Matriz<String> _posOcupadasEstudiantes;
        Matriz<Agentes::Iterador> _posOcupadasAgentes;

        Arreglo<aOrdenadoItem> _agentesOrdenados;
    };
}
#endif //TP_3_CAMPUSSEGURO_H

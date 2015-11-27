//
// Created by Matias on 25/11/2015.
//

#ifndef TP_3_HIPPIESYESTUDIANTES_H
#define TP_3_HIPPIESYESTUDIANTES_H

#include "DiccClavesRapidas.h"


namespace aed2{
    class HippiesYEstudiantes{
    public:

        HippiesYEstudiantes();

        void DefinirHippie(String nombre, const Posicion& pos);
        void DefinirEstudiante(String nombre, const Posicion& pos);

        Posicion PosHippieYEstudiante(String nombre) const;

        bool Esta(String nombre);

        bool EsHippie(String nombre);
        bool EsEst(String nombre);
        const Conj<String>& Estudiantes();
        const Conj<String>& Hippies();

        void Borrar(String nombre);

    private:
        DCR<Posicion> _estudiantes;
        DCR<Posicion> _hippies;
    };
}

#endif //TP_3_HIPPIESYESTUDIANTES_H

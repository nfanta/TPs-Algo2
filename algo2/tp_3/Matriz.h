#ifndef MATRIZ_H
#define MATRIZ_H

#include "Testing/aed2.h"
#include "Testing/Tipos.h"

namespace aed2 {

    template <class S>
    class Matriz {

    public:

        Matriz(const  Nat al, const Nat an);

        void Definir (const Posicion p, const S& s);

        bool Def (const Posicion p) const;

        S Obtener (const Posicion p) const;

        void Eliminar (const Posicion p);

        Conj Claves () const;

    private:


    };

    template<class S>
    Matriz NuevaMatriz (const  Nat al, const Nat an){
    }
}

#endif

#ifndef DICCCLAVESRAPIDAS_H
#define DICCCLAVESRAPIDAS_H

#include "Testing/aed2.h"
#include "Testing/Tipos.h"

namespace aed2 {

    template <class S>
    class DCR {

    public:

        DCR();

        ~DCR();

        void Definir (const String n, const S& s);

        bool Def (const String n) const;

        S Obtener (const String n) const;

        void Eliminar (const String n);

        Conj<String> Claves () const;

    private:

        struct Nodo {
            bool _definido;
            S _dato;
            Arreglo<Nodo*> _sig;
            typename Conj<String>::Iterador it;
        };

        Arreglo<Nodo*> _dicc;
        Conj<String> _claves;

    };

}

#endif

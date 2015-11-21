#ifndef MATRIZ_H
#define MATRIZ_H

#include "Testing/aed2.h"
#include "Testing/Tipos.h"

namespace aed2 {

    template <class S>
    class Matriz {

    public:

        Matriz(const  Nat al, const Nat an);

        ~Matriz();

        void Definir (const Posicion p, const S& s);

        bool Def (const Posicion p) const;

        S Obtener (const Posicion p) const;

        void Eliminar (const Posicion p);

        Conj Claves () const;

    private:

        struct info {
            bool _definido;
            S _significado;
            Conj::Iterador it;
        };

        Nat _alto;
        Nat _ancho;
        Conj _claves;
        Arreglo<Arreglo<info>> _tablero;

    };

    template <class S>
    Matriz<S>::Matriz(const  Nat al, const Nat an){
        _alto = al;
        _ancho = an;
        _claves = Conj();
        _tablero = Arreglo(al);
        for (int i = 0; i < al; ++i) {
            _tablero[i] = Arreglo(an);
        }
    }

    template <class S>
    Matriz<S>::~Matriz() {
        for (int i = 0; i < _alto; ++i) {
            delete _tablero[i];
        }

        delete _tablero;
    }

    template <class S>
    void Matriz<S>::Definir(const Posicion p, const S &s) {
        if (p.x < _alto && p.y < _ancho) {
            if (!_tablero[p.x][p.y]._definido) {
                Conj::Iterador temp;
                temp = _claves.AgregarRapido(p);
                _tablero[p.x][p.y].it = temp;
                _tablero[p.x][p.y]._definido = true;
                _tablero[p.x][p.y]._significado = s;
            } else {
                _tablero[p.x][p.y]._significado = s;
            }
        }
    }

    template <class S>
    bool Matriz::Def(const Posicion p) const {
        if (p.x > _alto || p.y > _ancho) {
            return false;
        } else {
            // Me aseguro de que haya sido definido con anterioridad (sino se puede romper)
            if (_tablero[p.x].Definido(p.y)) {
                return _tablero[p.x][p.y]._definido;
            } else {
                return false;
            }
        }
    }

    template <class S>
    S Matriz::Obtener(const Posicion p) const {
        assert(Def(p));

        return _tablero[p.x][p.y]._significado;
    }

    template <class S>
    void Matriz::Eliminar(const Posicion p) {
        _tablero[p.x][p.y].it.EliminarSiguiente();
        _tablero[p.x][p.y]._definido = false;
    }

    template <class S>
    Conj Matriz::Claves() const {
        return _claves;
    }
}

#endif

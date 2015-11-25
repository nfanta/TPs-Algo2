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

        Conj<Posicion> Claves () const;

    private:

        struct info {
            bool _definido;
            S _significado;
            typename Conj<Posicion>::Iterador it;
        };

        Nat _alto;
        Nat _ancho;
        Conj<Posicion> _claves;
        Arreglo<Arreglo<info> > _tablero;

    };

    template <class S>
    Matriz<S>::Matriz(const  Nat al, const Nat an){
        _alto = al;
        _ancho = an;
        _claves = Conj<Posicion>();
        _tablero = Arreglo<Arreglo<info> >(al);
        for (int i = 0; i < al; ++i) {
            _tablero.Definir(i, Arreglo<info>(an));
        }
    }

    template <class S>
    Matriz<S>::~Matriz() {
//        for (int i = 0; i < _alto-1; ++i) {
//            _tablero[i].~Arreglo();
//        }

//        _tablero.~Arreglo();
    }

    template <class S>
    void Matriz<S>::Definir(const Posicion p, const S &s) {
        if (p.x < _alto && p.y < _ancho) {
            if (!_tablero[p.x].Definido(p.y)) { // Se agrego  guarda para evitar que se indefina arreglo.
                info temp {true, s, _claves.AgregarRapido(p)};
                _tablero[p.x].Definir(p.y, temp);
            } else {
                if (!_tablero[p.x][p.y]._definido) { // Si el _definido esta en false (significa que ya se habia inici
                                                     // ado la posicion del arreglo, pero se borro el significado)
                    info temp {true, s, _claves.AgregarRapido(p)};
                    _tablero[p.x][p.y] = temp;
                } else { // si el _definido esta en true
                    _tablero[p.x][p.y]._significado = s;
                }
            }
        }
    }

    template <class S>
    bool Matriz<S>::Def(const Posicion p) const {
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
    S Matriz<S>::Obtener(const Posicion p) const {
        #ifdef DEBUG
        assert(Def(p));
        #endif

        return _tablero[p.x][p.y]._significado;
    }

    template <class S>
    void Matriz<S>::Eliminar(const Posicion p) {
        #ifdef DEBUG
        assert(Def(p));
        #endif

        _tablero[p.x][p.y].it.EliminarSiguiente();
        _tablero[p.x][p.y]._definido = false;
    }

    template <class S>
    Conj<Posicion> Matriz<S>::Claves() const {
        return _claves;
    }
}

#endif

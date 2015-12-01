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

        const Conj<String>& Claves () const;

    private:

        struct Nodo {
            bool _definido;
            S _dato;
            Arreglo<Nodo> _sig;
            typename Conj<String>::Iterador _it;
        };

        Arreglo<Nodo> _dicc;
        Conj<String> _claves;

        bool hayNodo (Nodo* n);

        Nodo* primerNodoDef (Nodo* n, Nat& pos);

    };


    template <class S>
    DCR<S>::DCR(){
        _dicc = Arreglo<Nodo>(256);
        _claves = Conj<String>();
    }

    template <class S>
    DCR<S>::~DCR() {
//        Nodo* cur;
//        Nodo* prev;
//
//        for (int i = 0; i < _dicc.Tamanho(); ++i) {
//            if (_dicc.Definido(i)){
//                cur = _dicc[i];
//
//                while (hayNodo(cur)) {
//                    Nat tmp = 0;
//
//                    while (hayNodo(cur)) {
//                        prev = cur;
//                        cur = primerNodoDef(cur, tmp);
//                    }
//
//                    if (cur == _dicc[i]) {
//                        break;
//                    } else {
//                        prev->_sig.Borrar(tmp);
//                        delete cur;
//                    }
//
//                    cur = _dicc[i];
//                }
//            }
//        }
    }

    template <class S>
    void DCR<S>::Definir(const String n, const S &s) {
        String str = n;
        Nodo* p;

        if ( !_dicc.Definido(str[0]) ) { // Si aun no se definio ningun string en _claves[x]...
            _dicc.Definir(str[0], Nodo{false, s, Arreglo<Nodo>(256), _claves.CrearIt()});
            p = &_dicc[str[0]];
            str.erase(0, 1);
        } else {
            p = &_dicc[str[0]];
            str.erase(0, 1);
        }
        while (str.length() > 0) { // Si poseia una longitud mas grande...
            if ( !p->_sig.Definido(str[0]) ) {
                p->_sig.Definir(str[0], Nodo{false, s, Arreglo<Nodo>(256), _claves.CrearIt()});
                p = &(p->_sig[str[0]]);
                str.erase(0, 1);
            } else {
                p = &(p->_sig[str[0]]);
                str.erase(0, 1);
            }
        }

        p->_definido = true;
        p->_it = _claves.AgregarRapido(n);
    }

    template <class S>
    bool DCR<S>::Def(const String n) const {
        String str = n;
        const Nodo* p;

        if ( !_dicc.Definido(str[0]) ) {\
            return false;
        } else {
            p = &_dicc[str[0]];
            str.erase(0, 1);
        }

        while (str.length() > 0) { // Si poseia una longitud mas grande...
            if ( !p->_sig.Definido(str[0]) ) {
                return false;
            } else {
                p = &(p->_sig[str[0]]);
                str.erase(0, 1);
            }
        }

        return p->_definido;
    }

    template <class S>
    S DCR<S>::Obtener(const String n) const {

        #ifdef DEBUG
        assert(Def(n));
        #endif

        String str = n;
        const Nodo* p;

        p = &_dicc[str[0]];
        str.erase(0, 1);

        while (str.length() > 0) { // Si poseia una longitud mas grande...
            p = &(p->_sig[str[0]]);
            str.erase(0, 1);
        }

        return p->_dato;
    }

    template <class S>
    void DCR<S>::Eliminar(const String n) {
        #ifdef DEBUG
        assert(Def(n));
        #endif

        String str = n;
        Nodo* p;

        p = &_dicc[str[0]];
        str.erase(0, 1);

        while (str.length() > 0) { // Si poseia una longitud mas grande...
            p = &(p->_sig[str[0]]);
            str.erase(0, 1);
        }

        p->_it.EliminarSiguiente();
        p->_definido = false;
    }

    template <class S>
    const Conj<String>& DCR<S>::Claves() const {
        return _claves;
    }

}

#endif

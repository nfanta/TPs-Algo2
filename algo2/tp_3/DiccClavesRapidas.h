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
            typename Conj<String>::Iterador _it;
        };

        Arreglo<Nodo*> _dicc;
        Conj<String> _claves;

    };


    template <class S>
    DCR<S>::DCR(){
        _dicc = Arreglo<Nodo*>(256);
        _claves = Conj<String>();
    }

    template <class S>
    DCR<S>::~DCR() {

    }

    template <class S>
    void DCR<S>::Definir(const String n, const S &s) {
        String str = n;
        Nodo* p;

        if ( !_dicc.Definido(str[0]) ) { // Si aun no se definio ningun string en _claves[x]...
            Nodo* tmp = new Nodo{false, s, Arreglo<Nodo*>(256), _claves.CrearIt()};

            _dicc.Definir(str[0], tmp);
            p = _dicc[str[0]];
            str.erase(0, 1);
        } else {
            p = _dicc[str[0]];
            str.erase(0, 1);
        }
        while (str.length() > 0) { // Si poseia una longitud mas grande...
            if ( !p->_sig.Definido(str[0]) ) {
                Nodo* tmp = new Nodo{false, s, Arreglo<Nodo*>(256), _claves.CrearIt()};

                p->_sig.Definir(str[0], tmp);
                p = p->_sig[str[0]];
                str.erase(0, 1);
            } else {
                p = p->_sig[str[0]];
                str.erase(0, 1);
            }
        }

        p->_definido = true;
        p->_it = _claves.AgregarRapido(n);

    }

    template <class S>
    bool DCR<S>::Def(const String n) const {
        String str = n;
        Nodo* p;

        if ( !_dicc.Definido(str[0]) ) {\
            return false;
        } else {
            p = _dicc[str[0]];
            str.erase(0, 1);
        }

        while (str.length() > 0) { // Si poseia una longitud mas grande...
            if ( !p->_sig.Definido(str[0]) ) {
                return false;
            } else {
                p = p->_sig[str[0]];
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
        Nodo* p;

        p = _dicc[str[0]];
        str.erase(0, 1);

        while (str.length() > 0) { // Si poseia una longitud mas grande...
            p = p->_sig[str[0]];
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

        p = _dicc[str[0]];
        str.erase(0, 1);

        while (str.length() > 0) { // Si poseia una longitud mas grande...
            p = p->_sig[str[0]];
            str.erase(0, 1);
        }

        p->_it.EliminarSiguiente();
        p->_definido = false;
    }

    template <class S>
    Conj<String> DCR<S>::Claves() const {
        return _claves;
    }

}

#endif

#ifndef DICCRAPIDO_H
#define DICCRAPIDO_H

#include "Testing/aed2.h"

namespace aed2 {

    template <class S>
    class DiccRapido {

    public:
        struct tuplaSignificado;

        class Iterador;
        class const_Iterador;

        DiccRapido(Nat maxClaves);
        ~DiccRapido();

        void Definir(Nat k, S& s);

        bool Def(Nat k) const;

        S& Obtener(Nat k);

        void Borrar(Nat k);

        const Conj<Nat>& Claves();

        Iterador CrearIt();
        const_Iterador CrearIt() const;

        class Iterador
        {
        public:

            Iterador();

            Iterador(const typename DiccRapido<S>::Iterador& otro);

            Iterador& operator = (const typename DiccRapido<S>::Iterador& otro);

            bool operator == (const typename DiccRapido<S>::Iterador&) const;

            bool HaySiguiente() const;
            bool HayAnterior() const;
            const Nat& SiguienteClave() const;
            S& SiguienteSignificado();
            const Nat& AnteriorClave() const;
            S& AnteriorSignificado();
            tuplaSignificado& Siguiente();
            tuplaSignificado& Anterior();
            void Avanzar();
            void Retroceder();
            void EliminarSiguiente();
            void EliminarAnterior();

        private:

            typename Conj<tuplaSignificado>::Iterador _it_tuplas;
            Nat _indice_act;

            Iterador(DiccRapido<S>* d);

            friend typename DiccRapido<S>::Iterador DiccRapido<S>::CrearIt();
            friend class DiccRapido<S>::const_Iterador;
        };

        class const_Iterador
        {
        public:

            const_Iterador();

            const_Iterador(const typename DiccRapido<S>::Iterador& otro);

            const_Iterador(const typename DiccRapido<S>::const_Iterador& otro);

            const_Iterador& operator = (const typename DiccRapido<S>::const_Iterador& otro);

            bool operator==(const typename DiccRapido<S>::const_Iterador&) const;

            bool HaySiguiente() const;
            bool HayAnterior() const;
            const Nat& SiguienteClave() const;
            const S& SiguienteSignificado() const;
            const Nat& AnteriorClave() const;
            const S& AnteriorSignificado() const;
            const tuplaSignificado& Siguiente() const;
            const tuplaSignificado& Anterior() const;
            void Avanzar();
            void Retroceder();

        private:

            typename Conj<tuplaSignificado>::const_Iterador _it_tuplas;
            Nat _indice_act;

            const_Iterador(const DiccRapido<S>* d);

            friend typename DiccRapido<S>::const_Iterador DiccRapido<S>::CrearIt() const;
        };

    private:
        struct tuplaSignificado{
            const Nat _key;
            S& _significado;
            tuplaSignificado(){};
            tuplaSignificado(Nat k, S& s) : _key(k), _significado(s) {};

            bool operator!=(const tuplaSignificado& tS) const {
                return !(_key == tS._key && _significado == tS._significado);
            }
        };

        Arreglo<Conj<tuplaSignificado>> _defs;
        Conj<Nat> _claves;

        Nat Hash(Nat k);

    };


    //IMPLEMENTACION DICCIONARIO

    template<class S>
    DiccRapido<S>::DiccRapido(Nat maxClaves){
        Nat i = 0;
        _claves = Conj<Nat>::Conj();
        _defs = typename Arreglo<Conj<DiccRapido<S>::tuplaSignificado>>::Arreglo(maxClaves);

        while (i < maxClaves) {
            _defs.Definir(i, typename Conj<DiccRapido<S>::tuplaSignificado>::Conj());
            i++;
        }
    }

    template<class S>
    DiccRapido<S>::~DiccRapido(){
        Nat i = 0;

        /*while (i < Tamanho(_defs)){
            Conj<DiccRapido<S>::tuplaSignificado>::Iterador itConj = _defs[i].CrearIt();
            while(itConj.HaySiguiente()){
                itConj.EliminarSiguiente();
                itConj.Avanzar();
            }
            i++;
        }*/
    }

    template<class S>
    void DiccRapido<S>::Definir(Nat k, S& s){
        Nat i = 0;
        Nat posArreglo;
        bool encontrado = false;

        posArreglo = Hash(k);
        typename Conj<DiccRapido<S>::tuplaSignificado>::Iterador itConjunto = _defs[posArreglo].CrearIt();

        while(itConjunto.HaySiguiente()){
            if (itConjunto.Siguiente()._key == k){
                encontrado = true;
                itConjunto.Siguiente()._significado = s;
            }
            itConjunto.Avanzar();
        }

        if (!encontrado) {
            _claves.AgregarRapido(k);
            //DiccRapido<S>::tuplaSignificado* tupla = new DiccRapido<S>::tuplaSignificado(k, s);
            _defs[posArreglo].Agregar(DiccRapido<S>::tuplaSignificado(k, s));
        }
    }

    template<class S>
    bool DiccRapido<S>::Def(Nat k) const{
        return _claves.Pertenece(k);
    }

    template<class S>
    S& DiccRapido<S>::Obtener(Nat k){
        #ifdef DEBUG
        assert(Def(k));
        #endif

        Nat i = 0;
        Nat posArreglo;
        //S& significado;

        posArreglo = Hash(k);
        typename Conj<DiccRapido<S>::tuplaSignificado>::Iterador itConjunto = _defs[posArreglo].CrearIt();

        while(itConjunto.HaySiguiente()){
            if (itConjunto.Siguiente()._key == k){
                return itConjunto.Siguiente()._significado;
            }
            itConjunto.Avanzar();
        }

        //return significado;
    }

    template<class S>
    void DiccRapido<S>::Borrar(Nat k){
        #ifdef DEBUG
        assert(Def(k));
        #endif

        Nat i = 0;
        Nat posArreglo;
        typename Conj<DiccRapido<S>::tuplaSignificado>::Iterador itConjunto;

        posArreglo = Hash(k);
        itConjunto = _defs[posArreglo].CrearIt();

        while(itConjunto.HaySiguiente()){
            if (itConjunto.Siguiente()._key == k){
                itConjunto.EliminarSiguiente();
            } else {
                itConjunto.Avanzar();
            }
        }

        _claves.Eliminar(k);
    }

    template<class S>
    const Conj<Nat>& DiccRapido<S>::Claves(){
        return _claves;
    }

    template<class S>
    Nat DiccRapido<S>::Hash(Nat k){
        Nat val = _defs.Tamanho();
        return k % val;
    }


    //IMPLEMENTACION ITERADOR
}



#endif
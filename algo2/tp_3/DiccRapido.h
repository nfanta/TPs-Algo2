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
//            bool HayAnterior() const;
            const Nat& SiguienteClave() const;
            S& SiguienteSignificado();
//            const Nat& AnteriorClave() const;
//            S& AnteriorSignificado();
            tuplaSignificado& Siguiente();
//            tuplaSignificado& Anterior();
            void Avanzar();
//            void Retroceder();
//            void EliminarSiguiente();
//            void EliminarAnterior();

        private:

            typename Conj<tuplaSignificado>::Iterador _it_tuplas;
            Nat _indice_act;
            Arreglo<Conj<tuplaSignificado>>* _dicc;

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
//            bool HayAnterior() const;
            const Nat& SiguienteClave() const;
            const S& SiguienteSignificado() const;
//            const Nat& AnteriorClave() const;
//            const S& AnteriorSignificado() const;
            const tuplaSignificado& Siguiente() const;
//            const tuplaSignificado& Anterior() const;
            void Avanzar();
//            void Retroceder();

        private:

            typename Conj<tuplaSignificado>::const_Iterador _it_tuplas;
            Nat _indice_act;
            Arreglo<Conj<tuplaSignificado>>* _dicc;

            const_Iterador(const DiccRapido<S>* d);

            friend typename DiccRapido<S>::const_Iterador DiccRapido<S>::CrearIt() const;
        };

        struct tuplaSignificado{
            const Nat _key;
            S& _significado;
            tuplaSignificado(){};
            tuplaSignificado(Nat k, S& s) : _key(k), _significado(s) {};

            bool operator!=(const tuplaSignificado& tS) const {
                return !(_key == tS._key && _significado == tS._significado);
            }
        };

    private:

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

    template<class S>
    typename DiccRapido<S>::Iterador DiccRapido<S>::CrearIt()
    {
        return Iterador(this);
    }

    template<class S>
    typename DiccRapido<S>::const_Iterador DiccRapido<S>::CrearIt() const
    {
        return const_Iterador(this);
    }


    //IMPLEMENTACION ITERADOR

    template<class S>
    DiccRapido<S>::Iterador::Iterador()
    {}

    template<class S>
    DiccRapido<S>::Iterador::Iterador(const typename DiccRapido<S>::Iterador& otro)
            : _it_tuplas(otro._it_tuplas), _indice_act(otro._indice_act)
    {}

    template<class S>
    typename DiccRapido<S>::Iterador& DiccRapido<S>::Iterador::operator = (const typename DiccRapido<S>::Iterador& otro)
    {
        _it_tuplas = otro._it_tuplas;
        _indice_act = otro._indice_act;

        return *this;
    }

    template<class S>
    bool DiccRapido<S>::Iterador::HaySiguiente() const
    {
        bool haySiguiente = _it_tuplas.HaySiguiente();

        /*Nat i = _indice_act + 1;

        while(!haySiguiente && i < _defs.Tamanho()){
            haySiguiente = !_defs[i].EsVacio();
            i++;
        }*/

        return haySiguiente;
    }

    /*template<class S>
    bool DiccRapido<S>::Iterador::HayAnterior() const
    {
        bool hayAnterior = _it_tuplas.HaySiguiente();

        Nat i = _indice_act - 1;

        while(!hayAnterior && i > 0){
            hayAnterior = !_defs[i].EsVacio();
            i--;
        }

        return hayAnterior;
    }*/

    template<class S>
    const Nat& DiccRapido<S>::Iterador::SiguienteClave() const
    {
        #ifdef DEBUG
        assert(HaySiguiente());
        #endif

        return _it_tuplas.Siguiente()._key;
    }

    template<class S>
    S& DiccRapido<S>::Iterador::SiguienteSignificado()
    {
        #ifdef DEBUG
        assert( HaySiguiente() );
        #endif

        return _it_tuplas.Siguiente()._significado;
    }

    template<class S>
    typename DiccRapido<S>::tuplaSignificado& DiccRapido<S>::Iterador::Siguiente()
    {
        #ifdef DEBUG
        assert( HaySiguiente() );
        #endif

        return _it_tuplas.Siguiente();
    }

    /*template<class S>
    const K& DiccRapido<S>::Iterador::AnteriorClave() const
    {
        #ifdef DEBUG
        assert( HayAnterior() );
        #endif

        return Anterior()._key;
    }

    template<class S>
    S& DiccRapido<S>::Iterador::AnteriorSignificado()
    {
        #ifdef DEBUG
        assert(HayAnterior());
        #endif

        return Anterior()._significado;
    }

    template<class S>
    typename DiccRapido<S>::tuplaSignificado& DiccRapido<S>::Iterador::Anterior()
    {
        #ifdef DEBUG
        assert(HayAnterior());
        #endif

        return _it_tuplas.Anterior(); //Rehacer si hace falta retroceder
    }*/

    template<class S>
    void DiccRapido<S>::Iterador::Avanzar()
    {
        #ifdef DEBUG
        assert(HaySiguiente());
        #endif

        _it_tuplas.Avanzar();

        while(!_it_tuplas.HaySiguiente() && _indice_act < _dicc->Tamanho() - 1){
            _indice_act++;
            _it_tuplas = (*_dicc)[_indice_act].CrearIt();
        }
    }

    /*template<class S>
    void DiccRapido<S>::Iterador::Retroceder()
    {
        #ifdef DEBUG
        assert(HayAnterior());
        #endif

        _it_tuplas.Retroceder();

        while(!_it_tuplas.HayAnterior() && _indice_act > 1){
            _indice_act--;
            _it_tuplas = _defs[_indice_act].CrearIt();

            while(_it_tuplas.HaySiguiente()){
                _it_tuplas.Avanzar();
            }
        }
    }*/

    template<class S>
    DiccRapido<S>::Iterador::Iterador(DiccRapido<S>* d) {
        _indice_act = 0;
        _dicc = &(d->_defs);
        _it_tuplas = (*_dicc)[0].CrearIt();

        while(!_it_tuplas.HaySiguiente() && _indice_act < _dicc->Tamanho() - 1){
            _indice_act++;
            _it_tuplas = (*_dicc)[_indice_act].CrearIt();
        }
    }

    /*template<class S>
    void DiccRapido<S>::Iterador::EliminarSiguiente()
    {
        #ifdef DEBUG
        assert( HaySiguiente() );
        #endif

        it_claves_.EliminarSiguiente();
        it_significados_.EliminarSiguiente();
    }*/

    /*template<class S>
    void DiccRapido<S>::Iterador::EliminarAnterior()
    {
        #ifdef DEBUG
        assert( HayAnterior() );
        #endif

        it_claves_.EliminarAnterior();
        it_significados_.EliminarAnterior();
    }*/

    
    //IMPLEMENTACION ITERADOR CONSTANTE

    template<class S>
    DiccRapido<S>::const_Iterador::const_Iterador()
    {}

    template<class S>
    DiccRapido<S>::const_Iterador::const_Iterador(const typename DiccRapido<S>::const_Iterador& otro)
            : _it_tuplas(otro._it_tuplas), _indice_act(otro._indice_act)
    {}

    template<class S>
    typename DiccRapido<S>::const_Iterador& DiccRapido<S>::const_Iterador::operator = (const typename DiccRapido<S>::const_Iterador& otro)
    {
        _it_tuplas = otro._it_tuplas;
        _indice_act = otro._indice_act;

        return *this;
    }

    template<class S>
    bool DiccRapido<S>::const_Iterador::HaySiguiente() const
    {
        bool haySiguiente = _it_tuplas.HaySiguiente();

        /*Nat i = _indice_act + 1;

        while(!haySiguiente && i < _defs.Tamanho()){
            haySiguiente = !_defs[i].EsVacio();
            i++;
        }*/

        return haySiguiente;
    }

    /*template<class S>
    bool DiccRapido<S>::const_Iterador::HayAnterior() const
    {
        bool hayAnterior = _it_tuplas.HaySiguiente();

        Nat i = _indice_act - 1;

        while(!hayAnterior && i > 0){
            hayAnterior = !_defs[i].EsVacio();
            i--;
        }

        return hayAnterior;
    }*/

    template<class S>
    const Nat& DiccRapido<S>::const_Iterador::SiguienteClave() const
    {
#ifdef DEBUG
        assert(HaySiguiente());
#endif

        return _it_tuplas.Siguiente()._key;
    }

    template<class S>
    const S& DiccRapido<S>::const_Iterador::SiguienteSignificado() const
    {
#ifdef DEBUG
        assert( HaySiguiente() );
#endif

        return _it_tuplas.Siguiente()._significado;
    }

    template<class S>
    const typename DiccRapido<S>::tuplaSignificado& DiccRapido<S>::const_Iterador::Siguiente() const
    {
#ifdef DEBUG
        assert( HaySiguiente() );
#endif

        return _it_tuplas.Siguiente();
    }

    /*template<class S>
    const K& DiccRapido<S>::const_Iterador::AnteriorClave() const
    {
        #ifdef DEBUG
        assert( HayAnterior() );
        #endif

        return Anterior()._key;
    }

    template<class S>
    S& DiccRapido<S>::const_Iterador::AnteriorSignificado()
    {
        #ifdef DEBUG
        assert(HayAnterior());
        #endif

        return Anterior()._significado;
    }

    template<class S>
    typename DiccRapido<S>::tuplaSignificado& DiccRapido<S>::const_Iterador::Anterior()
    {
        #ifdef DEBUG
        assert(HayAnterior());
        #endif

        return _it_tuplas.Anterior(); //Rehacer si hace falta retroceder
    }*/

    template<class S>
    void DiccRapido<S>::const_Iterador::Avanzar()
    {
#ifdef DEBUG
        assert(HaySiguiente());
#endif

        _it_tuplas.Avanzar();

        while(!_it_tuplas.HaySiguiente() && _indice_act < _dicc->Tamanho() - 1){
            _indice_act++;
            _it_tuplas = (*_dicc)[_indice_act].CrearIt();
        }
    }

    /*template<class S>
    void DiccRapido<S>::const_Iterador::Retroceder()
    {
        #ifdef DEBUG
        assert(HayAnterior());
        #endif

        _it_tuplas.Retroceder();

        while(!_it_tuplas.HayAnterior() && _indice_act > 1){
            _indice_act--;
            _it_tuplas = _defs[_indice_act].CrearIt();

            while(_it_tuplas.HaySiguiente()){
                _it_tuplas.Avanzar();
            }
        }
    }*/

    template<class S>
    DiccRapido<S>::const_Iterador::const_Iterador(const DiccRapido<S>* d) {
        _indice_act = 0;
        _dicc = &(d->_defs);
        _it_tuplas = (*_dicc)[0].CrearIt();

        while(!_it_tuplas.HaySiguiente() && _indice_act < _dicc->Tamanho() - 1){
            _indice_act++;
            _it_tuplas = (*_dicc)[_indice_act].CrearIt();
        }
    }

    /*template<class S>
    void DiccRapido<S>::const_Iterador::EliminarSiguiente()
    {
        #ifdef DEBUG
        assert( HaySiguiente() );
        #endif

        it_claves_.EliminarSiguiente();
        it_significados_.EliminarSiguiente();
    }*/

    /*template<class S>
    void DiccRapido<S>::const_Iterador::EliminarAnterior()
    {
        #ifdef DEBUG
        assert( HayAnterior() );
        #endif

        it_claves_.EliminarAnterior();
        it_significados_.EliminarAnterior();
    }*/
}



#endif
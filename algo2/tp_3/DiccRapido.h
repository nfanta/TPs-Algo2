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

        void Definir(Nat k, S s);

        bool Def(Nat k) const;

        S& Obtener(Nat k);
        const S& Obtener(Nat k) const;

        void Borrar(Nat k);

        const Conj<Nat>& Claves();

        Iterador Buscar(Nat c);
        Iterador CrearIt();
        const_Iterador CrearIt() const;
        const_Iterador Buscar(Nat c) const;

        class Iterador
        {
        public:

            Iterador();

            Iterador(const typename DiccRapido<S>::Iterador& otro);

            Iterador& operator = (const typename DiccRapido<S>::Iterador& otro);

            //bool operator == (const typename DiccRapido<S>::Iterador&) const;

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
        //AGREGADO para poder modificar desde un iterador el significado.
//            void DefinirSiguiente(S significado);

        private:

            typename Lista<tuplaSignificado>::Iterador _it_tuplas;
//            Lista<tuplaSignificado>* _conj_iterado; //Agregado para poder re-definir rapido
            Nat _indice_act;
            Arreglo<Lista<tuplaSignificado> >* _dicc;

            Iterador(DiccRapido<S>* d);

            friend typename DiccRapido<S>::Iterador DiccRapido<S>::CrearIt();
            friend typename DiccRapido<S>::Iterador DiccRapido<S>::Buscar(Nat c);
            friend class DiccRapido<S>::const_Iterador;
        };

        class const_Iterador
        {
        public:

            const_Iterador();

            const_Iterador(const typename DiccRapido<S>::Iterador& otro);

            const_Iterador(const typename DiccRapido<S>::const_Iterador& otro);

            const_Iterador& operator = (const typename DiccRapido<S>::const_Iterador& otro);

            //bool operator==(const typename DiccRapido<S>::const_Iterador&) const;

            bool HaySiguiente() const;
//            bool HayAnterior() const;
            const Nat& SiguienteClave() const;
            const S& SiguienteSignificado() const;
//            const Nat& AnteriorClave() const;
//            const S AnteriorSignificado() const;
            const tuplaSignificado& Siguiente() const;
//            const tuplaSignificado& Anterior() const;
            void Avanzar();
//            void Retroceder();

        private:

            typename Lista<tuplaSignificado>::const_Iterador _it_tuplas;
            Nat _indice_act;
            Arreglo<Lista<tuplaSignificado> >* _dicc;

            const_Iterador(const DiccRapido<S>* d);

            friend typename DiccRapido<S>::const_Iterador DiccRapido<S>::CrearIt() const;
            friend typename DiccRapido<S>::const_Iterador DiccRapido<S>::Buscar(Nat c) const;
        };

        struct tuplaSignificado{
            const Nat _key;
            S _significado;
            tuplaSignificado(){};
            tuplaSignificado(Nat k, S s) : _key(k), _significado(s) {};

            bool operator!=(const tuplaSignificado& tS) const {
                return !(_key == tS._key && _significado == tS._significado);
            }
        };

    private:

        Arreglo<Lista<tuplaSignificado> > _defs;
        Conj<Nat> _claves;

//        friend void typename DiccRapido<S>::Iterador::Avanzar();
//        friend void typename DiccRapido<S>::const_Iterador::Avanzar();

        Nat Hash(Nat k) const;

    };


    //IMPLEMENTACION DICCIONARIO

    template<class S>
    DiccRapido<S>::DiccRapido(Nat maxClaves){
        Nat i = 0;
        _claves = Conj<Nat>::Conj();
        _defs = typename Arreglo<Lista<DiccRapido<S>::tuplaSignificado> >::Arreglo(maxClaves);

        while (i < maxClaves) {
            _defs.Definir(i, typename Lista<DiccRapido<S>::tuplaSignificado>::Lista());
            i++;
        }
    }

    template<class S>
    DiccRapido<S>::~DiccRapido(){
    }

    template<class S>
    void DiccRapido<S>::Definir(Nat k, S s){
        Nat i = 0;
        Nat posArreglo;
        bool encontrado = false;

        posArreglo = Hash(k);
        typename Lista<DiccRapido<S>::tuplaSignificado>::Iterador itLista = _defs[posArreglo].CrearIt();

        while(itLista.HaySiguiente()){
            if (itLista.Siguiente()._key == k){
                encontrado = true;
                itLista.Siguiente()._significado = s;
            } else{
                itLista.Avanzar();
            }
        }

        if (!encontrado) {
            _claves.AgregarRapido(k);
            _defs[posArreglo].AgregarAtras(tuplaSignificado(k, s));
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

        posArreglo = Hash(k);
        typename Lista<DiccRapido<S>::tuplaSignificado>::Iterador itLista = _defs[posArreglo].CrearIt();

        while(itLista.HaySiguiente()){
            if (itLista.Siguiente()._key == k){
                return itLista.Siguiente()._significado;
            }
            itLista.Avanzar();
        }
    }

    template<class S>
    const S& DiccRapido<S>::Obtener(Nat k) const{
        #ifdef DEBUG
        assert(Def(k));
        #endif

        Nat i = 0;
        Nat posArreglo;

        posArreglo = Hash(k);
        typename Lista<DiccRapido<S>::tuplaSignificado>::const_Iterador itLista = _defs[posArreglo].CrearIt();

        while(itLista.HaySiguiente()){
            if (itLista.Siguiente()._key == k){
                return itLista.Siguiente()._significado;
            }
            itLista.Avanzar();
        }
    }

    template<class S>
    void DiccRapido<S>::Borrar(Nat k){
        #ifdef DEBUG
        assert(Def(k));
        #endif

        Nat i = 0;
        Nat posArreglo;
        typename Lista<DiccRapido<S>::tuplaSignificado>::Iterador itLista;

        posArreglo = Hash(k);
        itLista = _defs[posArreglo].CrearIt();

        while(itLista.HaySiguiente()){
            if (itLista.Siguiente()._key == k){
                itLista.EliminarSiguiente();
            } else {
                itLista.Avanzar();
            }
        }

        _claves.Eliminar(k);
    }

    template<class S>
    const Conj<Nat>& DiccRapido<S>::Claves(){
        return _claves;
    }

    template<class S>
    Nat DiccRapido<S>::Hash(Nat k) const{
        Nat val = _defs.Tamanho();
        return k % val;
    }

    // COMIENZA IMPLEMENTACION DE ITERADOR

    template<class S>
    typename DiccRapido<S>::Iterador DiccRapido<S>::Buscar(Nat c) {
        DiccRapido<S>::Iterador it = Iterador(this);
        while(it.HaySiguiente() && it.SiguienteClave() != c){
            it.Avanzar();
        }

        if (it.SiguienteClave() == c){
            return it;
        } else {
            return Iterador(this);
        }
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

    template<class S>
    typename DiccRapido<S>::const_Iterador DiccRapido<S>::Buscar(Nat c) const {
        DiccRapido<S>::Iterador it = Iterador(this);
        while(it.HaySiguiente() && it.SiguienteClave() != c){
            it.Avanzar();
        }

        if (it.SiguienteClave() == c){
            return it;
        } else {
            return Iterador(this);
        }
    }


    //IMPLEMENTACION ITERADOR

    template<class S>
    DiccRapido<S>::Iterador::Iterador()
    {}

    template<class S>
    DiccRapido<S>::Iterador::Iterador(const typename DiccRapido<S>::Iterador& otro)
            : _it_tuplas(otro._it_tuplas), _indice_act(otro._indice_act), _dicc(otro._dicc)
    {}

    template<class S>
    typename DiccRapido<S>::Iterador& DiccRapido<S>::Iterador::operator = (const typename DiccRapido<S>::Iterador& otro)
    {
        _it_tuplas = otro._it_tuplas;
        _indice_act = otro._indice_act;
        _dicc = otro._dicc;

        return *this;
    }

    template<class S>
    bool DiccRapido<S>::Iterador::HaySiguiente() const
    {
        return _it_tuplas.HaySiguiente();
    }

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

    template<class S>
    void DiccRapido<S>::Iterador::Avanzar() {
        #ifdef DEBUG
        assert(HaySiguiente());
        #endif

        _it_tuplas.Avanzar();

        Nat aux = _dicc->Tamanho();

        while(!_it_tuplas.HaySiguiente() && _indice_act < (aux - 1)){
            _indice_act++;
            _it_tuplas = (*_dicc)[_indice_act].CrearIt();
        }
    }

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

//    template<class S>
//    void DiccRapido<S>::Iterador::DefinirSiguiente(S significado) {
//        Nat clave = SiguienteClave();
//        _it_tuplas.EliminarSiguiente();
//        //_it_tuplas = _conj_iterado->AgregarRapido(tuplaSignificado(clave, significado));
//    }

    
    //IMPLEMENTACION ITERADOR CONSTANTE

    template<class S>
    DiccRapido<S>::const_Iterador::const_Iterador()
    {}

    template<class S>
    DiccRapido<S>::const_Iterador::const_Iterador(const typename DiccRapido<S>::const_Iterador& otro)
            : _it_tuplas(otro._it_tuplas), _indice_act(otro._indice_act), _dicc(otro._dicc)
    {}

    template<class S>
    typename DiccRapido<S>::const_Iterador& DiccRapido<S>::const_Iterador::operator = (const typename DiccRapido<S>::const_Iterador& otro)
    {
        _it_tuplas = otro._it_tuplas;
        _indice_act = otro._indice_act;
        _dicc = otro._dicc;

        return *this;
    }

    template<class S>
    bool DiccRapido<S>::const_Iterador::HaySiguiente() const
    {
        return _it_tuplas.HaySiguiente();
    }

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

    template<class S>
    void DiccRapido<S>::const_Iterador::Avanzar() {
        #ifdef DEBUG
        assert(HaySiguiente());
        #endif

        _it_tuplas.Avanzar();

        while(!_it_tuplas.HaySiguiente() && _indice_act < _dicc->Tamanho() - 1){
            _indice_act++;
            _it_tuplas = (*_dicc)[_indice_act].CrearIt();
        }
    }

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
}



#endif

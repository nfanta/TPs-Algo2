//
// Created by Matias on 22/11/2015.
//

#include "Agentes.h"

namespace aed2{

    Agentes::Agentes(Dicc<Nat, Posicion> &d) {
        Conj<Nat>::Iterador itAConjMismSanciones;
        Lista<itemMismSanciones>::Iterador itAMismSanciones;
        itDicc<Nat,Posicion>::Iterador itDicc;
        Nat i = 0;

        _as = DiccRapido<DatosAgente>::DiccRapido(d.CantClaves());
        _claves = Conj<Nat>::Conj();
        itDicc = d.CrearIt();

        /*while(itDicc.HaySiguiente()){
            _claves.AgregarRapido(itDicc.SiguienteClave());
            itDicc.Avanzar();
        }*/

        _masVig = 0;
        _capturas_masVig = 0;
        _mismSanciones = Lista<itemMismSanciones>::Lista();
        _mismSanciones.AgregarAtras( itemMismSanciones(Conj<Nat>::Conj(), 0) );
        itAMismSanciones = _mismSanciones.CrearIt();
        _kSanciones = Arreglo<tuplaK>::Arreglo(_claves.Cardinal());
        itDicc = d.CrearIt();

        while(itDicc.HaySiguiente()){

            //Modifico un poco el codigo para tener un iterador que asignar a la definicion del agente en el DiccRapido (error no encontrado durante la correccion)
            _claves.AgregarRapido(itDicc.SiguienteClave());
            itAConjMismSanciones = itAMismSanciones.Siguiente()._agentes.AgregarRapido(itDicc.SiguienteClave());

            if(_masVig == 0){
                _masVig = itDicc.SiguienteClave();
            }
            if(itDicc.SiguienteClave() < _masVig){
                _masVig = itDicc.SiguienteClave();
            }

            _as.Definir(itDicc.SiguienteClave(), DatosAgente(itDicc.SiguienteSignificado(), 0, 0, itAMismSanciones, itAConjMismSanciones));
            //En kSanciones voy a guardar tambien un iterador a Lista(itemMismSanciones)
            _kSanciones.Definir(i, tuplaK(itDicc.SiguienteClave(), 0, itAMismSanciones));
            i++;

            itDicc.Avanzar();
        }

        _huboSanciones = false;
    }

    const Conj<Nat>& Agentes::dameAgentes() {
        return _claves;
    }

    void Agentes::AgregarSancion(Nat placa) {
        Lista<itemMismSanciones>::Iterador itLista;
        Conj<Nat>::Iterador itConj;

        _as.Obtener(placa)._sanciones = _as.Obtener(placa)._sanciones + 1;

        itLista = _as.Obtener(placa)._conMismSanciones;
        itConj = _as.Obtener(placa)._itConjMismSanciones;

        itConj.EliminarSiguiente();

        if(itLista.Siguiente()._agentes.EsVacio()){
            itLista.EliminarSiguiente();
        } else {
            itLista.Avanzar();
        }

        if (! itLista.HaySiguiente()){
            //CAMBIOS ACA PARA AJUSTAR LA COMPLEJIDAD DE KSANCIONES (guardo tambien las sanciones en cada item de la lista conMismSanciones)
            itLista.AgregarComoSiguiente( itemMismSanciones(Conj<Nat>::Conj(), _as.Obtener(placa)._sanciones) );
            itConj = itLista.Siguiente()._agentes.AgregarRapido(placa);
        } else {
            //Cambio aca para no usar DameUno que no esta definido, uso un iterador para tomar el primero del conjunto.
            itConj = itLista.Siguiente()._agentes.CrearIt();
            //No se indefine el Siguiente porque nunca hay un Conj vacio en un item de la lista (lo borro mas arriba)
            if(_as.Obtener(itConj.Siguiente())._sanciones > _as.Obtener(placa)._sanciones){
                //CAMBIOS ACA PARA AJUSTAR LA COMPLEJIDAD DE KSANCIONES (guardo tambien las sanciones en cada item de la lista conMismSanciones)
                itLista.AgregarComoAnterior( itemMismSanciones(Conj<Nat>::Conj(), _as.Obtener(placa)._sanciones) );
                itConj = itLista.Anterior()._agentes.AgregarRapido(placa);
                itLista.Retroceder();
            } else {
                itConj = itLista.Siguiente()._agentes.AgregarRapido(placa);
            }
        }

        _as.Obtener(placa)._conMismSanciones = itLista;
        _as.Obtener(placa)._itConjMismSanciones = itConj;

        _huboSanciones = true;
    }

    void Agentes::CambiarPosicion(Nat placa, Posicion p) {
        _as.Obtener(placa)._posicion = p;
    }

    void Agentes::AgregarCaptura(Nat placa) {
        _as.Obtener(placa)._capturas = _as.Obtener(placa)._capturas + 1;
        if(_as.Obtener(placa)._capturas > _as.Obtener(_masVig)._capturas){
            _masVig = placa;
            _capturas_masVig = _as.Obtener(placa)._capturas; //Agregado para poder trabajar con iteradores
        } else {
            if(_as.Obtener(placa)._capturas == _as.Obtener(_masVig)._capturas){
                if(placa < _masVig){
                    _masVig = placa;
                    _capturas_masVig = _as.Obtener(placa)._capturas; //Agregado para poder trabajar con iteradores
                }
            }
        }
    }

    Posicion Agentes::PosAgente(Nat placa) const {
        return _as.Obtener(placa)._posicion;
    }

    Nat Agentes::SancionesAgente(Nat placa) const {
        return _as.Obtener(placa)._sanciones;
    }

    Nat Agentes::CapturasAgente(Nat placa) const {
        return _as.Obtener(placa)._capturas;
    }

    Nat Agentes::MasVigilante() const {
        return _masVig;
    }

    const Conj<Nat>& Agentes::ConMismasSanciones(Nat placa) {
        return _as.Obtener(placa)._conMismSanciones.Siguiente();
    }

    const Conj<Nat>& Agentes::ConKSanciones(Nat k) {
        //
        Nat i = 0;
        bool encontrado = false;

        Lista<itemMismSanciones>::Iterador itLista;
        Conj<Nat>::Iterador itConj;

        if(_huboSanciones){
            _huboSanciones = false;
            itLista = _mismSanciones.CrearIt();
            while(itLista.HaySiguiente()){
                itConj = itLista.Siguiente()._agentes;
                while(itConj.HaySiguiente()){
                    //Cambios para arreglar la complejidad
                    _kSanciones[i]._placa = itConj.Siguiente();                     //O(1)
                    _kSanciones[i]._sanciones = itLista.Siguiente()._sanciones;     //O(1)
                    _kSanciones[i]._conMismSanciones = itLista;                     //O(1)
                    itConj.Avanzar();
                    i++;
                }
                itLista.Avanzar();
            }
        }

        encontrado = BusquedaBinariaSanciones(k, _kSanciones, i);
        if(encontrado){
            return _kSanciones[i]._conMismSanciones;                                //O(1)
        } else {
            return Conj<Nat>::Conj();
        }
    }
    //Complejidad: Ahora la complejidad del caso promedio [O(Na) / O(log(Na))] es la complejidad del peor caso. (reemplaze los lugares donde habia un O(Na) por operaciones O(1) )

    bool Agentes::BusquedaBinariaSanciones(Nat k, Arreglo<tuplaK> arreglo, Nat &i) const {
        Nat iMin, iMax, iMed;
        iMin = 0;
        iMax = arreglo.Tamanho();
        bool res = false;

        while(iMin <= iMax){
            iMed = (iMin+iMax)/2;
            if(arreglo[iMed]._sanciones == k){
                i = iMed;
                res = true;
                iMin = iMax + 1;
            } else {
                if(arreglo[iMed]._sanciones < k) {
                    iMin = iMax + 1;
                } else{
                    iMax = iMed - 1;
                }
            }
        }
    }



    //Iterador


    Agentes::Iterador::Iterador()
    {}

    Agentes::Iterador::Iterador(const Agentes::Iterador& otro)
            : _it_as(otro._it_as)
    {}


    Agentes::Iterador& Agentes::Iterador::operator = (const Agentes::Iterador& otro) {
        _it_as = otro._it_as;
        return *this;
    }

    Agentes::Iterador Agentes::CrearIt() {
        return Iterador(this);
    }

    Agentes::Iterador Agentes::Buscar(Nat placa){
        return Iterador(this, placa);
    }

    Agentes::Iterador::Iterador(Agentes* as) {
        _it_as = as->_as.CrearIt();
    }

    Agentes::Iterador::Iterador(Agentes* as, Nat placa) {
        _it_as = as->_as.Buscar(placa);
    }

    bool Agentes::Iterador::HaySiguiente() const {
        return _it_as.HaySiguiente();
    }

    void Agentes::Iterador::Avanzar() {
        _it_as.Avanzar();
    }

    const Nat& Agentes::Iterador::SiguientePlaca() const {
        return _it_as.SiguienteClave();
    }

    DatosAgente& Agentes::Iterador::SiguienteDatos() {
        return _it_as.SiguienteSignificado();
    }


    //Funciones con overload de iterador

    void Agentes::AgregarSancion(Iterador agente) {
        Lista<itemMismSanciones>::Iterador itLista;
        Conj<Nat>::Iterador itConj;

        agente.SiguienteDatos()._sanciones = agente.SiguienteDatos()._sanciones + 1;

        itLista = agente.SiguienteDatos()._conMismSanciones;
        itConj = agente.SiguienteDatos()._itConjMismSanciones;

        itConj.EliminarSiguiente();

        if(itLista.Siguiente()._agentes.EsVacio()){
            itLista.EliminarSiguiente();
        } else {
            itLista.Avanzar();
        }

        if (! itLista.HaySiguiente()){
            //CAMBIOS ACA PARA AJUSTAR LA COMPLEJIDAD DE KSANCIONES (guardo tambien las sanciones en cada item de la lista conMismSanciones)
            itLista.AgregarComoSiguiente( itemMismSanciones(Conj<Nat>::Conj(), agente.SiguienteDatos()._sanciones) );
            itConj = itLista.Siguiente()._agentes.AgregarRapido(placa);
        } else {
            //Cambio aca para no usar DameUno que no esta definido, uso un iterador para tomar el primero del conjunto.
            itConj = itLista.Siguiente()._agentes.CrearIt();
            //No se indefine el Siguiente porque nunca hay un Conj vacio en un item de la lista (lo borro mas arriba)
            if(_as.Obtener(itConj.Siguiente())._sanciones > agente.SiguienteDatos()._sanciones){
                //CAMBIOS ACA PARA AJUSTAR LA COMPLEJIDAD DE KSANCIONES (guardo tambien las sanciones en cada item de la lista conMismSanciones)
                itLista.AgregarComoAnterior( itemMismSanciones(Conj<Nat>::Conj(), agente.SiguienteDatos()._sanciones) );
                itConj = itLista.Anterior()._agentes.AgregarRapido(placa);
                itLista.Retroceder();
            } else {
                itConj = itLista.Siguiente()._agentes.AgregarRapido(placa);
            }
        }

        agente.SiguienteDatos()._conMismSanciones = itLista;
        agente.SiguienteDatos()._itConjMismSanciones = itConj;

        _huboSanciones = true;
    }

    void Agentes::AgregarCaptura(Iterador agente) {
        agente.SiguienteDatos()._capturas = agente.SiguienteDatos()._capturas + 1;
        if(agente.SiguienteDatos()._capturas > _capturas_masVig){ //Reemplazado Obtener de masVig por _capturas_masVig para ser O(1) en peor caso
            _masVig = placa;
            _capturas_masVig = agente.SiguienteDatos()._capturas; //Agregado para poder trabajar con iteradores
        } else {
            if(agente.SiguienteDatos()._capturas == _capturas_masVig){ //Reemplazado Obtener de masVig por _capturas_masVig para ser O(1) en peor caso
                if(placa < _masVig){
                    _masVig = placa;
                    _capturas_masVig = agente.SiguienteDatos()._capturas; //Agregado para poder trabajar con iteradores
                }
            }
        }
    }

    void Agentes::CambiarPosicion(Iterador agente, Posicion p) {
        agente.SiguienteDatos()._posicion = p;
    }
}


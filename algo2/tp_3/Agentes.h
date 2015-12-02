#ifndef AGENTES_H
#define AGENTES_H

#include "Testing/aed2.h"
#include "Testing/Tipos.h"
#include "DiccRapido.h"

namespace aed2{
    class Agentes{
    public:

        struct DatosAgente;
        struct itemMismSanciones;

        class Iterador;

        Agentes();
        Agentes(const Dicc<Nat,Posicion>& d);

        const Conj<Nat>& dameAgentes() const;

        void AgregarSancion(Nat placa);
        void AgregarSancion(Iterador agente);
        void CambiarPosicion(Nat placa, const Posicion& p);
        void CambiarPosicion(Iterador agente, const Posicion& p);
        void AgregarCaptura(Nat placa);
        void AgregarCaptura(Iterador agente);

        const Posicion& PosAgente(Nat placa) const;
        const Nat& SancionesAgente(Nat placa) const;
        const Nat& CapturasAgente(Nat placa) const;

        Nat MasVigilante() const;
        const Conj<Nat>& ConMismasSanciones(Nat placa) const;
        const Conj<Nat>& ConKSanciones(Nat k);

        Iterador CrearIt();
        Iterador Buscar(Nat placa);

        struct DatosAgente{
            Posicion _posicion;
            Nat _sanciones;
            Nat _capturas;

            //Cambio el tipo de dato de Lista(Conj(Nat)) a Lista(Conj(itAgente)) para satisfacer la complejidad de KSanciones
            typename Lista<itemMismSanciones>::Iterador _conMismSanciones;
            typename Conj<Nat>::Iterador _itConjMismSanciones;

            DatosAgente(Posicion p, Nat s, Nat c, Lista<itemMismSanciones>::Iterador& conMS, Conj<Nat>::Iterador& itConMS) : _posicion(p), _sanciones(s), _capturas(c), _conMismSanciones(conMS), _itConjMismSanciones(itConMS){}
        };

        struct itemMismSanciones{
            Conj<Nat> _agentes;
            Nat _sanciones;

            itemMismSanciones(Conj<Nat> as, Nat s) : _agentes(as), _sanciones(s) {}
        };
    public:
        class Iterador {
        public:
            Iterador();
            Iterador(const typename Agentes::Iterador& otro);
            Iterador& operator = (const typename Agentes::Iterador& otro);

            //bool operator == (const typename Agentes::Iterador&) const;

            bool HaySiguiente() const;

            const Nat& SiguientePlaca() const;
            DatosAgente& SiguienteDatos();

            void Avanzar();
//            void DefinirSiguiente(DatosAgente datos);

        private:

            typename DiccRapido<DatosAgente>::Iterador _it_as;

            Iterador(Agentes* a);
            Iterador(Agentes* a, Nat placa);



            friend Agentes::Iterador Agentes::CrearIt();
            friend Agentes::Iterador Agentes::Buscar(Nat placa);
        };
    private:
        struct tuplaK{
            Nat _sanciones;
            Nat _placa;
            typename Lista<itemMismSanciones>::Iterador _conMismSanciones;

            tuplaK(Nat s, Nat p, Lista<itemMismSanciones>::Iterador& itConMS) : _sanciones(s), _placa(p), _conMismSanciones(itConMS) {}
        };

        DiccRapido<DatosAgente> _as;
        Conj<Nat> _claves;
        Nat _masVig;
        Nat _capturas_masVig; //Guardo las capturas para poder trabajar con iteradores y no tener que Obtener(_masVig) que tardaria O(Na) en
        bool _huboSanciones;
        Lista<itemMismSanciones> _mismSanciones;
        Arreglo<tuplaK> _kSanciones;



        bool BusquedaBinariaSanciones(Nat k, Arreglo<tuplaK>& arreglo, Nat& i) const;
    };
}

#endif //AGENTES_H

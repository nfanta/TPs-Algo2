#ifndef CAMPUS_SEGURO_CAMPSEG_H
#define CAMPUS_SEGURO_CAMPSEG_H
#endif //CAMPUS_SEGURO_CAMPSEG_H

#include <string>
#include <iostream>

#include "Matriz.h"
#include "Testing/aed2.h"
#include "Testing/Tipos.h"



namespace aed2 {
    class Campus {

    public:

        Campus(Nat al, Nat an);

        void AgregarObstaculo(Posicion p);

        Nat  Filas() const;

        Nat  Columnas() const;

        bool  Ocupada(Posicion p) const;

        bool  posValida(Posicion p)const;

        bool  esIngreso(Posicion p)const;

        bool  ingresoSuperior(Posicion p)const;

        bool  ingresoInferior(Posicion p)const;

        Conj<Posicion> Vecinos(Posicion p)const;

        Nat Distancia(Posicion p1,Posicion p2)const;

        Posicion ProxPosicion(Posicion p1,Direccion d)const;

        Conj<Posicion> IngresoMasCercano(Posicion p)const;

    private:

        Nat _Alto;
        Nat _Ancho;
        Matriz<bool> _obstaculos;


        };

    //ALGORITMOS!


    Campus::Campus(Nat al,  Nat an) : _Alto(al) , _Ancho(an) , _obstaculos(Matriz<bool>(al,an)){}



    void Campus::AgregarObstaculo(Posicion p) {
        _obstaculos.Definir(p, true);
    }

    Nat Campus::Columnas() const{
        Nat res = _Ancho;
        return res;
    }

    Nat Campus::Filas() const {
        Nat res = _Alto;
        return res;
    }

    bool Campus::Ocupada(Posicion p) const {
        bool res = _obstaculos.Def(p);
        return res;

    }

    Nat Campus::Distancia(Posicion p1, Posicion p2) const{
        Nat resParcialx;
        Nat resParcialy;
        if(p1.x >= p2.x){
             resParcialx = p1.x - p2.x;
        } else{
             resParcialx = p2.x - p1.x;
        }

        if(p1.y >= p2.y){
              resParcialy = p1.y - p2.y;
        } else{
             resParcialy = p2.y - p1.y;
        }
        Nat res = (resParcialx + resParcialy);
        return res;
    }

    bool Campus::posValida(Posicion p) const{
        bool res = true;

        if (p.y > _Alto || p.x > _Ancho) {
            res = false;
        }
        if(0>=p.y || 0>= p.x) {
            res = false;
        }
        return res;
    }

    Conj<Posicion> Campus::Vecinos(Posicion p) const{
        Conj<Posicion> res = Conj<Posicion>();

        Posicion v1,v2,v3,v4;

        v1 = {p.x -1,p.y};
        v2= {p.x +1,p.y};
        v3={p.x,p.y -1};
        v4={p.x,p.y +1};

        if(posValida(v1)) {
            res.Agregar(v1);
        }

        if(posValida(v2)) {
            res.Agregar(v2);
        }

        if(posValida(v3)) {
            res.Agregar(v3);
        }

        if(posValida(v4)) {
            res.Agregar(v4);
        }

        return res;
    }

    Posicion Campus::ProxPosicion(Posicion p1, Direccion d) const{
       Posicion res;
        if(d == izq){
            res = {p1.x-1,p1.y};
        }

        if(d == der){
            res = {p1.x+1,p1.y};
        }

        if(d == arriba){
            res = {p1.x,p1.y+1};
        }

        if(d == abajo){
            res = {p1.x,p1.y-1};
        }
        return res;
    }

    bool Campus ::ingresoSuperior(Posicion p) const{
    // No es al revez el superior el alto e inferior el 1 revisar!?
        return p.y == 1;
    }

    bool Campus::ingresoInferior(Posicion p) const{

        return p.y == _Alto;
    }

    bool Campus::esIngreso(Posicion p) const{
        return (ingresoInferior(p) || ingresoSuperior(p));
    }

    Conj<Posicion> Campus::IngresoMasCercano(Posicion p) const{
        Conj<Posicion> res = Conj<Posicion>();
        Posicion v1,v2;
        if( p.y-1 < _Alto - p.y ) {
            v1 = {p.x,1};
            res.Agregar(v1);
        }else {
            if( p.y-1 > _Alto - p.y) {
                v2 = {p.x,_Alto};
                res.Agregar(v2);
            }else {
                v1 = {p.x,1};
                res.Agregar(v1);
                v2 = {p.x,_Alto};
                res.Agregar(v2);
            }

        }
        return res;
    }

    };


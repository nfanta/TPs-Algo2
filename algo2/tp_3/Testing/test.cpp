#include "Driver.h"
#include "mini_test.h"
#include "../Matriz.h"
#include "../campus.h"
#include "../DiccClavesRapidas.h"
#include "../DiccRapido.h"
#include "../Agentes.h"
#include "../Agentes.cpp"
#include "../CampusSeguro.h"
#include "Tipos.h"
#include "aed2.h"

#include <string>
#include <iostream>

using namespace aed2;


// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de test, con llamadas a las rutinas de aserción 
 * definidas en mini_test.h
 */

// MATRIZ

void matriz_crear() {
    Matriz<Nat> mat(10,10);
    for (unsigned int i = 0; i < 10; ++i) {
        for (unsigned int j = 0; j < 10; ++j) {
            ASSERT(!mat.Def({i,j}));
        }
    }
}

void matriz_definirYdef() {
    Matriz<Nat> mat(10,10);
    ASSERT(!mat.Def({1,1}))
    mat.Definir({1,1},5);
    ASSERT(mat.Def({1,1}));
    mat.Definir({1,1},4);
    ASSERT(mat.Def({1,1}));
}

void matriz_obtener() {
    Matriz<Nat> mat(10,10);
    ASSERT(!mat.Def({1,1}))
    mat.Definir({1,1},1);
    ASSERT(mat.Def({1,1}));
    ASSERT_EQ(mat.Obtener({1,1}), 1);
    mat.Definir({1,1},4);
    ASSERT(mat.Def({1,1}));
    ASSERT_EQ(mat.Obtener({1,1}), 4);
    for (unsigned int i = 0; i < 10; ++i) {
        for (unsigned int j = 0; j < 10; ++j) {
            mat.Definir({i,j},7);
            ASSERT(mat.Def({i,j}));
            ASSERT_EQ(mat.Obtener({i,j}), 7);
        }
    }
}

void matriz_eliminar() {
    Matriz<Nat> mat(10,10);
    ASSERT(!mat.Def({1,1}))
    mat.Definir({1,1},1);
    ASSERT(mat.Def({1,1}));
    ASSERT_EQ(mat.Obtener({1,1}), 1);
    mat.Eliminar({1,1});
    ASSERT(!mat.Def({1,1}))
    mat.Definir({1,1},4);
    ASSERT(mat.Def({1,1}));
    ASSERT_EQ(mat.Obtener({1,1}), 4);
    mat.Eliminar({1,1});
    ASSERT(!mat.Def({1,1}))
    for (unsigned int i = 0; i < 10; ++i) {
        for (unsigned int j = 0; j < 10; ++j) {
            mat.Definir({i,j},7);
            ASSERT(mat.Def({i,j}));
            ASSERT_EQ(mat.Obtener({i,j}), 7);
            mat.Eliminar({i,j});
            ASSERT(!mat.Def({i,j}))
        }
    }
}

void matriz_claves() {
    Matriz<Nat> mat(10,10);
    ASSERT_EQ(mat.Claves().EsVacio(), true);
    mat.Definir({1,1},1);
    ASSERT_EQ(mat.Claves().EsVacio(), false);
    ASSERT_EQ(mat.Claves().Pertenece({1,1}), true);
    mat.Definir({1,2},1);
    mat.Definir({2,1},1);
    mat.Definir({2,2},1);
    ASSERT_EQ(mat.Claves().Pertenece({1,2}), true);
    ASSERT_EQ(mat.Claves().Pertenece({2,1}), true);
    ASSERT_EQ(mat.Claves().Pertenece({2,2}), true);
    ASSERT_EQ(mat.Claves().Pertenece({3,3}), false);
    mat.Eliminar({1,1});
    ASSERT_EQ(mat.Claves().Pertenece({1,1}), false);
    mat.Eliminar({1,2});
    ASSERT_EQ(mat.Claves().Pertenece({1,2}), false);
    mat.Eliminar({2,1});
    ASSERT_EQ(mat.Claves().Pertenece({2,1}), false);
    mat.Eliminar({2,2});
    ASSERT_EQ(mat.Claves().Pertenece({2,2}), false);
}

// DICCCLAVESRAPIDAS

void dcr_crear() {
    DCR<Nat> dcr = DCR<Nat>();
    ASSERT(!dcr.Def("a"));
    ASSERT(!dcr.Def("b"));
    ASSERT(!dcr.Def("algo"));
}

void dcr_definirYdef() {
    DCR<Nat> dcr = DCR<Nat>();
    dcr.Definir("a", 1);
    ASSERT(dcr.Def("a"));
    dcr.Definir("aa", 1);
    ASSERT(dcr.Def("aa"));
    dcr.Definir("b", 1);
    ASSERT(dcr.Def("b"));
    dcr.Definir("nico", 1);
    ASSERT(dcr.Def("nico"));
    dcr.Definir("tuVieja", 1);
    ASSERT(dcr.Def("tuVieja"));
    dcr.Definir("7uV!e)@", 1);
    ASSERT(dcr.Def("7uV!e)@"));
}

void dcr_obtener() {
    DCR<Nat> dcr = DCR<Nat>();
    dcr.Definir("a", 1);
    ASSERT_EQ(dcr.Obtener("a"),1);
    dcr.Definir("aa", 2);
    ASSERT_EQ(dcr.Obtener("aa"),2);
    dcr.Definir("b", 3);
    ASSERT_EQ(dcr.Obtener("b"),3);
    dcr.Definir("nico", 4);
    ASSERT_EQ(dcr.Obtener("nico"),4);
    dcr.Definir("tuVieja", 5);
    ASSERT_EQ(dcr.Obtener("tuVieja"),5);
    dcr.Definir("7uV!e)@", 6);
    ASSERT_EQ(dcr.Obtener("7uV!e)@"),6);
}

void dcr_eliminar() {
    DCR<Nat> dcr = DCR<Nat>();
    dcr.Definir("a", 1);
    ASSERT(dcr.Def("a"));
    dcr.Eliminar("a");
    ASSERT(!dcr.Def("a"));
    dcr.Definir("aa", 1);
    ASSERT(dcr.Def("aa"));
    dcr.Eliminar("aa");
    ASSERT(!dcr.Def("aa"));
    dcr.Definir("b", 1);
    ASSERT(dcr.Def("b"));
    dcr.Eliminar("b");
    ASSERT(!dcr.Def("b"));
    dcr.Definir("nico", 1);
    ASSERT(dcr.Def("nico"));
    dcr.Eliminar("nico");
    ASSERT(!dcr.Def("nico"));
    dcr.Definir("tuVieja", 1);
    ASSERT(dcr.Def("tuVieja"));
    dcr.Eliminar("tuVieja");
    ASSERT(!dcr.Def("tuVieja"));
    dcr.Definir("7uV!e)@", 1);
    ASSERT(dcr.Def("7uV!e)@"));
    dcr.Eliminar("7uV!e)@");
    ASSERT(!dcr.Def("7uV!e)@"));
}

void dcr_claves() {
    DCR<Nat> dcr = DCR<Nat>();
    dcr.Definir("a", 1);
    ASSERT(dcr.Def("a"));
    ASSERT_EQ(dcr.Claves().Cardinal(),1);
    dcr.Definir("aa", 1);
    ASSERT(dcr.Def("aa"));
    ASSERT_EQ(dcr.Claves().Cardinal(),2);
    dcr.Definir("b", 1);
    ASSERT(dcr.Def("b"));
    ASSERT_EQ(dcr.Claves().Cardinal(),3);
    dcr.Definir("nico", 1);
    ASSERT(dcr.Def("nico"));
    ASSERT_EQ(dcr.Claves().Cardinal(),4);
    dcr.Definir("tuVieja", 1);
    ASSERT(dcr.Def("tuVieja"));
    ASSERT_EQ(dcr.Claves().Cardinal(),5);
    dcr.Definir("7uV!e)@", 1);
    ASSERT(dcr.Def("7uV!e)@"));
    ASSERT_EQ(dcr.Claves().Cardinal(),6);

    ASSERT(dcr.Claves().Pertenece("a"));
    ASSERT(dcr.Claves().Pertenece("aa"));
    ASSERT(dcr.Claves().Pertenece("b"));
    ASSERT(dcr.Claves().Pertenece("nico"));
    ASSERT(dcr.Claves().Pertenece("tuVieja"));
    ASSERT(dcr.Claves().Pertenece("7uV!e)@"));

    dcr.Eliminar("a");
    ASSERT(!dcr.Def("a"));
    ASSERT_EQ(dcr.Claves().Cardinal(),5);
    ASSERT(!dcr.Claves().Pertenece("a"));
    dcr.Eliminar("aa");
    ASSERT(!dcr.Def("aa"));
    ASSERT_EQ(dcr.Claves().Cardinal(),4);
    ASSERT(!dcr.Claves().Pertenece("aa"));
    dcr.Eliminar("b");
    ASSERT(!dcr.Def("b"));
    ASSERT_EQ(dcr.Claves().Cardinal(),3);
    ASSERT(!dcr.Claves().Pertenece("b"));
    dcr.Eliminar("nico");
    ASSERT(!dcr.Def("nico"));
    ASSERT_EQ(dcr.Claves().Cardinal(),2);
    ASSERT(!dcr.Claves().Pertenece("nico"));
    dcr.Eliminar("tuVieja");
    ASSERT(!dcr.Def("tuVieja"));
    ASSERT_EQ(dcr.Claves().Cardinal(),1);
    ASSERT(!dcr.Claves().Pertenece("tuVieja"));
    dcr.Eliminar("7uV!e)@");
    ASSERT(!dcr.Def("7uV!e)@"));
    ASSERT_EQ(dcr.Claves().Cardinal(),0);
    ASSERT(!dcr.Claves().Pertenece("7uV!e)@"));
}

// CAMPUS

void campus_crear() {
    Campus c(10,5);
    ASSERT_EQ(c.Filas(),10);
    ASSERT_EQ(c.Columnas(),5);
    ASSERT(!c.Ocupada({1,1}));
}

void campus_agregarObstaculoYocupada() {
    Campus c(10,10);
    ASSERT(!c.Ocupada({1,1}));
    c.AgregarObstaculo({1,1});
    ASSERT(c.Ocupada({1,1}));
    ASSERT(!c.Ocupada({5,5}));
    c.AgregarObstaculo({5,5});
    ASSERT(c.Ocupada({5,5}));
    ASSERT(!c.Ocupada({3,7}));
    c.AgregarObstaculo({3,7});
    ASSERT(c.Ocupada({3,7}));
}

void campus_filas() {
    Campus c(10,10);
    ASSERT_EQ(c.Filas(),10);
    c = Campus(5,10);
    ASSERT_EQ(c.Filas(),5);
    c = Campus(17,10);
    ASSERT_EQ(c.Filas(),17);
    c = Campus(300,10);
    ASSERT_EQ(c.Filas(),300);
}

void campus_columnas() {
    Campus c(10,10);
    ASSERT_EQ(c.Columnas(),10);
    c = Campus(10,5);
    ASSERT_EQ(c.Columnas(),5);
    c = Campus(10,17);
    ASSERT_EQ(c.Columnas(),17);
    c = Campus(10,300);
    ASSERT_EQ(c.Columnas(),300);
}

void campus_posValida() {
    Campus c(10,10);
    ASSERT(c.posValida({1,1}));
    ASSERT(c.posValida({9,9}));
    ASSERT(!c.posValida({10,10}));
    ASSERT(!c.posValida({15,37}));
}

void campus_esIngreso(){
    Campus c(10,10);
    ASSERT(c.esIngreso({1,1}));
    ASSERT(c.esIngreso({1,5}));
    ASSERT(!c.esIngreso({5,1}));
    ASSERT(c.esIngreso({10,5}));
    ASSERT(!c.esIngreso({9,5}));
}

void campus_ingresoSuperior() {
    Campus c(10,10);
    ASSERT(c.ingresoSuperior({1,1}));
    ASSERT(c.ingresoSuperior({1,5}));
    ASSERT(!c.ingresoSuperior({5,1}));
    ASSERT(!c.ingresoSuperior({10,5}));
    ASSERT(!c.ingresoSuperior({9,5}));
}

void campus_ingresoInferior() {
    Campus c(10,10);
    ASSERT(!c.ingresoInferior({1,1}));
    ASSERT(!c.ingresoInferior({1,5}));
    ASSERT(!c.ingresoInferior({5,1}));
    ASSERT(c.ingresoInferior({10,5}));
    ASSERT(!c.ingresoInferior({9,5}));
}

void campus_vecinos() {
    Campus c(10,10);
    ASSERT(c.Vecinos({1,1}).Pertenece({1,2}));
    ASSERT(c.Vecinos({1,1}).Pertenece({2,1}));
    ASSERT(!c.Vecinos({1,1}).Pertenece({0,1}));
    ASSERT(!c.Vecinos({1,1}).Pertenece({1,0}));

    ASSERT(c.Vecinos({5,5}).Pertenece({6,5}));
    ASSERT(c.Vecinos({5,5}).Pertenece({5,6}));
    ASSERT(c.Vecinos({5,5}).Pertenece({5,4}));
    ASSERT(c.Vecinos({5,5}).Pertenece({4,5}));

    ASSERT(c.Vecinos({10,10}).Pertenece({9,10}));
    ASSERT(c.Vecinos({10,10}).Pertenece({10,9}));
    ASSERT(!c.Vecinos({10,10}).Pertenece({11,10}));
    ASSERT(!c.Vecinos({10,10}).Pertenece({10,11}));
}

void campus_distancia() {
    Campus c(10,10);
//    ASSERT_EQ(c.Distancia({1,1},{5,5}), c.Distancia({5,5},{1,1}));
    ASSERT_EQ(c.Distancia({1,5},{5,5}),4);
    ASSERT_EQ(c.Distancia({1,1},{3,7}),8);
    ASSERT_EQ(c.Distancia({9,2},{3,7}),11);
}

void campus_proxPosicion() {
    Campus c(10,10);
    Posicion p = c.ProxPosicion({1,1},arriba);
    ASSERT_EQ(p.x, 0);
    ASSERT_EQ(p.y, 1);

    p = c.ProxPosicion({1,1},abajo);
    ASSERT_EQ(p.x, 2);
    ASSERT_EQ(p.y, 1);

    p = c.ProxPosicion({1,1},der);
    ASSERT_EQ(p.x, 1);
    ASSERT_EQ(p.y, 2);

    p = c.ProxPosicion({1,1},izq);
    ASSERT_EQ(p.x, 1);
    ASSERT_EQ(p.y, 0);



    p = c.ProxPosicion({10,10},arriba);
    ASSERT_EQ(p.x, 9);
    ASSERT_EQ(p.y, 10);

    p = c.ProxPosicion({10,10},abajo);
    ASSERT_EQ(p.x, 11);
    ASSERT_EQ(p.y, 10);

    p = c.ProxPosicion({10,10},der);
    ASSERT_EQ(p.x, 10);
    ASSERT_EQ(p.y, 11);

    p = c.ProxPosicion({10,10},izq);
    ASSERT_EQ(p.x, 10);
    ASSERT_EQ(p.y, 9);
}

void campus_ingresoMasCercano() {
    Campus c(10,10);
    Conj<Posicion> tmp;
    tmp = c.IngresoMasCercano({3,7});
    ASSERT(tmp.Pertenece({1,7}));
    ASSERT(!tmp.Pertenece({3,1}));
    ASSERT(!tmp.Pertenece({3,10}));

    tmp = c.IngresoMasCercano({7,3});
    ASSERT(tmp.Pertenece({10,3}));
    ASSERT(!tmp.Pertenece({7,1}));
    ASSERT(!tmp.Pertenece({7,10}));
}

//Tests Dicc Rapido

void dr_Crear(){
    DiccRapido<String> dicc(15);
    ASSERT(!dicc.Def(1));
    ASSERT(!dicc.Def(5));
    ASSERT(!dicc.Def(15));
}

void dr_defYDefinido(){
    DiccRapido<String> dicc(15);
    dicc.Definir(1, "Alberto");
    dicc.Definir(5, "Jose");
    dicc.Definir(25, "Pedro");
    dicc.Definir(16, "Pepe");
    ASSERT(dicc.Def(1));
    ASSERT(dicc.Def(5));
    ASSERT(dicc.Def(25));
    ASSERT(dicc.Def(16));
    ASSERT(!dicc.Def(15));
}

void dr_Obtener(){
    DiccRapido<String> dicc(15);
    dicc.Definir(5, "Alberto");
    ASSERT_EQ(dicc.Obtener(5), "Alberto");
    dicc.Definir(7, "Jose");
    ASSERT_EQ(dicc.Obtener(7), "Jose");
    dicc.Definir(14, "Pedro");
    ASSERT_EQ(dicc.Obtener(14), "Pedro");
    dicc.Definir(64, "Pepe");
    ASSERT_EQ(dicc.Obtener(64), "Pepe");
}

void dr_Borrar(){
    DiccRapido<String> dicc(15);
    dicc.Definir(1, "Alberto");
    ASSERT(dicc.Def(1));
    dicc.Definir(5, "Jose");
    ASSERT(dicc.Def(5));
    dicc.Definir(25, "Pedro");
    ASSERT(dicc.Def(25));
    dicc.Definir(16, "Pepe");
    ASSERT(dicc.Def(16));
    ASSERT(!dicc.Def(15));

    dicc.Borrar(25);
    ASSERT(!dicc.Def(25));
}

void dr_Claves(){
    DiccRapido<String> dicc(15);

    dicc.Definir(1, "Alberto");
    ASSERT(dicc.Claves().Pertenece(1));
    ASSERT_EQ(dicc.Claves().Cardinal(), 1);
    dicc.Definir(5, "Jose");
    ASSERT(dicc.Claves().Pertenece(5));
    ASSERT_EQ(dicc.Claves().Cardinal(), 2);
    dicc.Definir(25, "Pedro");
    ASSERT(dicc.Claves().Pertenece(25));
    ASSERT_EQ(dicc.Claves().Cardinal(), 3);
    dicc.Definir(16, "Pepe");
    ASSERT(dicc.Claves().Pertenece(16));
    ASSERT_EQ(dicc.Claves().Cardinal(), 4);

    dicc.Borrar(1);
    ASSERT(!dicc.Claves().Pertenece(1));
    ASSERT_EQ(dicc.Claves().Cardinal(), 3);
    dicc.Borrar(5);
    ASSERT(!dicc.Claves().Pertenece(5));
    ASSERT_EQ(dicc.Claves().Cardinal(), 2);
    dicc.Borrar(25);
    ASSERT(!dicc.Claves().Pertenece(25));
    ASSERT_EQ(dicc.Claves().Cardinal(), 1);
    dicc.Borrar(16);
    ASSERT(!dicc.Claves().Pertenece(16));
    ASSERT_EQ(dicc.Claves().Cardinal(), 0);
}

void agentes_Crear(){
    Dicc<Nat,Posicion> agentes;
    agentes.Definir(1, {1, 4});
    agentes.Definir(5, {3, 3});
    agentes.Definir(9, {1, 1});
    agentes.Definir(13, {5, 2});
    agentes.Definir(17, {3, 2});

    Agentes as(agentes);
    ASSERT_EQ(as.dameAgentes().Cardinal(), 5);
    ASSERT(as.dameAgentes().Pertenece(1));
    ASSERT(as.dameAgentes().Pertenece(5));
    ASSERT(as.dameAgentes().Pertenece(9));
    ASSERT(as.dameAgentes().Pertenece(13));
    ASSERT(as.dameAgentes().Pertenece(17));
    ASSERT(!as.dameAgentes().Pertenece(20));
    ASSERT_EQ(as.PosAgente(1).x, 1);
    ASSERT_EQ(as.PosAgente(1).y, 4);
    ASSERT_EQ(as.PosAgente(5).x, 3);
    ASSERT_EQ(as.PosAgente(5).y, 3);
}

void agentes_AgregarYPedir(){
    Dicc<Nat,Posicion> agentes;
    agentes.Definir(1, {1, 4});
    agentes.Definir(5, {3, 3});
    agentes.Definir(9, {1, 1});
    agentes.Definir(13, {5, 2});
    agentes.Definir(17, {3, 2});

    Agentes as(agentes);

    ASSERT_EQ(as.SancionesAgente(1), 0);
    as.AgregarSancion(1);
    ASSERT_EQ(as.SancionesAgente(1), 1);
    as.AgregarSancion(1);
    ASSERT_EQ(as.SancionesAgente(1), 2);
    as.AgregarSancion(13);
    ASSERT_EQ(as.SancionesAgente(13), 1);

    as.AgregarCaptura(9);
    ASSERT_EQ(as.CapturasAgente(9), 1);
    as.AgregarCaptura(9);
    ASSERT_EQ(as.CapturasAgente(9), 2);
    as.AgregarCaptura(17);
    ASSERT_EQ(as.CapturasAgente(17), 1);

    as.CambiarPosicion(5, {1,3});
    ASSERT_EQ(as.PosAgente(5).x, 1);
    ASSERT_EQ(as.PosAgente(5).y, 3);
}

void agentes_MasVigilante() {
    Dicc<Nat, Posicion> agentes;
    agentes.Definir(1, {1, 4});
    agentes.Definir(5, {3, 3});
    agentes.Definir(9, {1, 1});
    agentes.Definir(13, {5, 2});
    agentes.Definir(17, {3, 2});

    Agentes as(agentes);

    ASSERT_EQ(as.MasVigilante(), 1);
    as.AgregarCaptura(1);
    ASSERT_EQ(as.MasVigilante(), 1);
    as.AgregarCaptura(13);
    ASSERT_EQ(as.MasVigilante(), 1);
    as.AgregarCaptura(13);
    ASSERT_EQ(as.MasVigilante(), 13);
    as.AgregarCaptura(9);
    ASSERT_EQ(as.MasVigilante(), 13);
    as.AgregarCaptura(9);
    ASSERT_EQ(as.MasVigilante(), 9);
    as.AgregarCaptura(13);
    ASSERT_EQ(as.MasVigilante(), 13);
}

void agentes_ConMismasSanciones() {
    Dicc<Nat, Posicion> agentes;
    agentes.Definir(1, {1, 4});
    agentes.Definir(5, {3, 3});
    agentes.Definir(9, {1, 1});
    agentes.Definir(13, {5, 2});
    agentes.Definir(17, {3, 2});

    Agentes as(agentes);
    ASSERT(as.ConMismasSanciones(1).Pertenece(1));
    ASSERT(as.ConMismasSanciones(1).Pertenece(5));
    ASSERT(as.ConMismasSanciones(1).Pertenece(9));
    ASSERT(as.ConMismasSanciones(1).Pertenece(13));
    ASSERT(as.ConMismasSanciones(1).Pertenece(17));
    as.AgregarSancion(1);
    ASSERT(as.ConMismasSanciones(1).Pertenece(1));
    ASSERT(!as.ConMismasSanciones(1).Pertenece(5));
    ASSERT(!as.ConMismasSanciones(1).Pertenece(9));
    ASSERT(!as.ConMismasSanciones(1).Pertenece(13));
    ASSERT(!as.ConMismasSanciones(1).Pertenece(17));
    as.AgregarSancion(1);
    as.AgregarSancion(5);
    ASSERT(!as.ConMismasSanciones(5).Pertenece(1));
    ASSERT(as.ConMismasSanciones(5).Pertenece(5));
    ASSERT(!as.ConMismasSanciones(5).Pertenece(9));
    ASSERT(!as.ConMismasSanciones(5).Pertenece(13));
    ASSERT(!as.ConMismasSanciones(5).Pertenece(17));
    as.AgregarSancion(5);
    ASSERT(as.ConMismasSanciones(5).Pertenece(1));
    ASSERT(as.ConMismasSanciones(5).Pertenece(5));
    ASSERT(!as.ConMismasSanciones(5).Pertenece(9));
    ASSERT(!as.ConMismasSanciones(5).Pertenece(13));
    ASSERT(!as.ConMismasSanciones(5).Pertenece(17));
}

void agentes_ConKSanciones() {
    Dicc<Nat, Posicion> agentes;
    agentes.Definir(1, {1, 4});
    agentes.Definir(5, {3, 3});
    agentes.Definir(9, {1, 1});
    agentes.Definir(13, {5, 2});
    agentes.Definir(17, {3, 2});

    Agentes as(agentes);
    ASSERT(as.ConKSanciones(0).Pertenece(1));
    ASSERT(as.ConKSanciones(0).Pertenece(5));
    ASSERT(as.ConKSanciones(0).Pertenece(9));
    ASSERT(as.ConKSanciones(0).Pertenece(13));
    ASSERT(as.ConKSanciones(0).Pertenece(17));
    as.AgregarSancion(1);
    ASSERT(as.ConKSanciones(1).Pertenece(1));
    ASSERT(!as.ConKSanciones(1).Pertenece(5));
    ASSERT(!as.ConKSanciones(1).Pertenece(9));
    ASSERT(!as.ConKSanciones(1).Pertenece(13));
    ASSERT(!as.ConKSanciones(1).Pertenece(17));
    as.AgregarSancion(1);
    as.AgregarSancion(5);
    ASSERT(!as.ConKSanciones(1).Pertenece(1));
    ASSERT(as.ConKSanciones(1).Pertenece(5));
    ASSERT(!as.ConKSanciones(1).Pertenece(9));
    ASSERT(!as.ConKSanciones(1).Pertenece(13));
    ASSERT(!as.ConKSanciones(1).Pertenece(17));
    as.AgregarSancion(5);
    ASSERT(as.ConKSanciones(2).Pertenece(1));
    ASSERT(as.ConKSanciones(2).Pertenece(5));
    ASSERT(!as.ConKSanciones(2).Pertenece(9));
    ASSERT(!as.ConKSanciones(2).Pertenece(13));
    ASSERT(!as.ConKSanciones(2).Pertenece(17));
}

int main(int argc, char **argv)
{
    std::cout << "Comenzando Tests de Matriz:\n\n";
    RUN_TEST(matriz_crear);
    RUN_TEST(matriz_definirYdef);
    RUN_TEST(matriz_obtener);
    RUN_TEST(matriz_eliminar);
    RUN_TEST(matriz_claves);
    std::cout << "\nFinalizados Tests de Matriz.\n\n";

    std::cout << "Comenzando Tests de DiccClavesRapidas:\n\n";
    RUN_TEST(dcr_crear);
    RUN_TEST(dcr_definirYdef);
    RUN_TEST(dcr_obtener);
    RUN_TEST(dcr_eliminar);
    RUN_TEST(dcr_claves);
    std::cout << "\nFinalizados Tests de DiccClavesRapidas.\n\n";

    std::cout << "Comenzando Tests de Campus:\n\n";
    RUN_TEST(campus_crear);
    RUN_TEST(campus_agregarObstaculoYocupada);
    RUN_TEST(campus_filas);
    RUN_TEST(campus_columnas);
    RUN_TEST(campus_posValida);
    RUN_TEST(campus_esIngreso);
    RUN_TEST(campus_ingresoSuperior);
    RUN_TEST(campus_ingresoInferior);
    RUN_TEST(campus_vecinos);
    RUN_TEST(campus_distancia);
    RUN_TEST(campus_proxPosicion);
    RUN_TEST(campus_ingresoMasCercano);
    std::cout << "\nFinalizados Tests de Campus.\n\n";

    std::cout << "Comenzando Tests de DiccRapido:\n\n";
    RUN_TEST(dr_Crear);
    RUN_TEST(dr_defYDefinido);
    RUN_TEST(dr_Obtener);
    RUN_TEST(dr_Borrar);
    RUN_TEST(dr_Claves);
    std::cout << "\nFinalizados Tests de DiccRapido.\n\n";

    std::cout << "Comenzando Tests de Agentes:\n\n";
    RUN_TEST(agentes_Crear);
    RUN_TEST(agentes_AgregarYPedir);
    RUN_TEST(agentes_MasVigilante);
    RUN_TEST(agentes_ConMismasSanciones);
    RUN_TEST(agentes_ConKSanciones);
    std::cout << "\nFinalizados Tests de Agentes.\n\n";

	return 0;
}

#include "Driver.h"
#include "mini_test.h"
#include "../Matriz.h"
#include "../campus.h"
#include "../DiccClavesRapidas.h"
#include "../DiccRapido.h"
#include "../Agentes.h"
#include "../Agentes.cpp"
#include "../CampusSeguro.h"
#include "../CampusSeguro.cpp"
#include "../HippiesYEstudiantes.cpp"
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
    for (unsigned int i = 1; i <= 10; ++i) {
        for (unsigned int j = 1; j <= 10; ++j) {
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
    for (unsigned int i = 1; i <= 10; ++i) {
        for (unsigned int j = 1; j <= 10; ++j) {
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
    for (unsigned int i = 1; i <= 10; ++i) {
        for (unsigned int j = 1; j <= 10; ++j) {
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
    ASSERT(c.posValida({10,10}));
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
    ASSERT(c.Vecinos({1,1}).Pertenece({0,1}));
    ASSERT(c.Vecinos({1,1}).Pertenece({1,0}));

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

// DICCRAPIDO

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

// AGENTES

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

void agentes_Iterador() {
    Dicc<Nat, Posicion> agentes;
    agentes.Definir(1, {1, 4});
    agentes.Definir(5, {3, 3});
    agentes.Definir(9, {1, 1});
    agentes.Definir(13, {5, 2});
    agentes.Definir(17, {3, 2});

    Agentes as(agentes);

    Nat i = 0;

    Agentes::Iterador itAs = as.CrearIt();

    while(itAs.HaySiguiente()){
        ASSERT(as.dameAgentes().Pertenece(itAs.SiguientePlaca()));
        ASSERT (itAs.SiguienteDatos()._posicion == as.PosAgente(itAs.SiguientePlaca()));
        ASSERT(itAs.SiguienteDatos()._capturas == as.CapturasAgente(itAs.SiguientePlaca()));
        ASSERT(itAs.SiguienteDatos()._sanciones == as.SancionesAgente(itAs.SiguientePlaca()));
        i++;
        itAs.Avanzar();
    }

    ASSERT_EQ(i, 5);
}

// HIPPIESYESTUDIANTES

void hyp_HippiesYEstudiantes() {
    HippiesYEstudiantes hyp = HippiesYEstudiantes();
}

void hyp_DefinirHippie_Esta_EsHippie() {
    HippiesYEstudiantes hyp = HippiesYEstudiantes();
    hyp.DefinirHippie("Alice",{1,1});
    ASSERT(hyp.EsHippie("Alice"));
    ASSERT(hyp.Esta("Alice"));
    ASSERT(!hyp.Esta("alice"));

    hyp.DefinirHippie("Bob",{5,5});
    ASSERT(hyp.EsHippie("Bob"));
    ASSERT(hyp.Esta("Bob"));
    ASSERT(!hyp.Esta("bob"));

    hyp.DefinirHippie("7uV13)@",{7,3});
    ASSERT(hyp.EsHippie("7uV13)@"));
    ASSERT(hyp.Esta("7uV13)@"));
    ASSERT(!hyp.Esta("tuV13)@"));
}

void hyp_DefinirEstudiante_Esta_EsEst() {
    HippiesYEstudiantes hyp = HippiesYEstudiantes();
    hyp.DefinirEstudiante("Alice",{1,1});
    ASSERT(!hyp.EsHippie("Alice"));
    ASSERT(hyp.EsEst("Alice"));
    ASSERT(hyp.Esta("Alice"));
    ASSERT(!hyp.Esta("alice"));

    hyp.DefinirEstudiante("Bob",{5,5});
    ASSERT(hyp.EsEst("Bob"));
    ASSERT(hyp.Esta("Bob"));
    ASSERT(!hyp.Esta("bob"));

    hyp.DefinirEstudiante("7uV13)@",{7,3});
    ASSERT(hyp.EsEst("7uV13)@"));
    ASSERT(hyp.Esta("7uV13)@"));
    ASSERT(!hyp.Esta("tuV13)@"));
}

void hyp_PosHippieYEstudiante() {
    HippiesYEstudiantes hyp = HippiesYEstudiantes();

    hyp.DefinirHippie("Alice",{1,1});
    ASSERT(hyp.EsHippie("Alice"));
    ASSERT(hyp.Esta("Alice"));
    ASSERT(!hyp.Esta("alice"));

    hyp.DefinirHippie("Bob",{5,5});
    ASSERT(hyp.EsHippie("Bob"));
    ASSERT(hyp.Esta("Bob"));
    ASSERT(!hyp.Esta("bob"));

    hyp.DefinirEstudiante("7uV13)@",{7,3});
    ASSERT(hyp.EsEst("7uV13)@"));
    ASSERT(hyp.Esta("7uV13)@"));
    ASSERT(!hyp.Esta("tuV13)@"));

    Posicion tmp = hyp.PosHippieYEstudiante("Alice");
    ASSERT_EQ(tmp.x, 1);
    ASSERT_EQ(tmp.y, 1);

    tmp = hyp.PosHippieYEstudiante("Bob");
    ASSERT_EQ(tmp.x, 5);
    ASSERT_EQ(tmp.y, 5);

    tmp = hyp.PosHippieYEstudiante("7uV13)@");
    ASSERT_EQ(tmp.x, 7);
    ASSERT_EQ(tmp.y, 3);
}

void hyp_Estudiantes() {
    HippiesYEstudiantes hyp = HippiesYEstudiantes();
    hyp.DefinirEstudiante("Alice",{1,1});
    hyp.DefinirEstudiante("Bob",{2,1});
    hyp.DefinirHippie("Laquonda",{6,3});
    hyp.DefinirHippie("Tristan",{3,4});

    ASSERT(hyp.Estudiantes().Pertenece("Alice"));
    ASSERT(hyp.Estudiantes().Pertenece("Bob"));
    ASSERT(!hyp.Estudiantes().Pertenece("Laquonda"));
    ASSERT(!hyp.Estudiantes().Pertenece("Tristan"));
}

void hyp_Hippies() {
    HippiesYEstudiantes hyp = HippiesYEstudiantes();
    hyp.DefinirEstudiante("Alice",{1,1});
    hyp.DefinirEstudiante("Bob",{2,1});
    hyp.DefinirHippie("Laquonda",{6,3});
    hyp.DefinirHippie("Tristan",{3,4});

    ASSERT(!hyp.Hippies().Pertenece("Alice"));
    ASSERT(!hyp.Hippies().Pertenece("Bob"));
    ASSERT(hyp.Hippies().Pertenece("Laquonda"));
    ASSERT(hyp.Hippies().Pertenece("Tristan"));
}

void hyp_Borrar() {
    HippiesYEstudiantes hyp = HippiesYEstudiantes();

    hyp.DefinirEstudiante("Alice",{1,1});
    hyp.DefinirEstudiante("Bob",{2,1});
    hyp.DefinirHippie("Laquonda",{6,3});

    ASSERT(hyp.Esta("Alice"));
    ASSERT(hyp.Esta("Bob"));
    ASSERT(hyp.Esta("Laquonda"));

    hyp.Borrar("Bob");

    ASSERT(hyp.Esta("Alice"));
    ASSERT(!hyp.Esta("Bob"));
    ASSERT(hyp.Esta("Laquonda"));

    hyp.Borrar("Laquonda");

    ASSERT(hyp.Esta("Alice"));
    ASSERT(!hyp.Esta("Bob"));
    ASSERT(!hyp.Esta("Laquonda"));
}

// CAMPUSSEGURO

CampusSeguro* crearCampusGenerico() {
    Campus c(10,10);
    c.AgregarObstaculo({1,1});
    c.AgregarObstaculo({5,5});
    c.AgregarObstaculo({3,7});
    c.AgregarObstaculo({7,3});

    Dicc<Nat, Posicion> d = Dicc<Nat, Posicion>();
    d.Definir(1,{2,9});
    d.Definir(5,{3,3});
    d.Definir(10,{4,4});
    d.Definir(20,{9,9});

    CampusSeguro* cs = new CampusSeguro(c, d);

    return cs;
}

CampusSeguro* crearCampusConEstYHippies() {
    CampusSeguro* cs = crearCampusGenerico();

    cs->IngresarEstudiante("Alice", {1,2});
    cs->IngresarEstudiante("Bob", {1,3});
    cs->IngresarEstudiante("Charlie", {1,4});
    cs->IngresarHippie("Alba", {9,1});
    cs->IngresarHippie("Brisa", {9,2});
    cs->IngresarHippie("Cielo", {9,3});

    return cs;
}

//CampusSeguro(const Campus& c, const Dicc<Nat,Posicion>& dA);
void cs_crear() {
    CampusSeguro* cs = crearCampusGenerico();
    delete cs;
}

//void IngresarEstudiante(String nombre, Posicion p);
void IngresarEstudiante() {
    CampusSeguro* cs = crearCampusGenerico();

    cs->IngresarEstudiante("Alice", {1,2});
    cs->IngresarEstudiante("Bob", {1,3});
    cs->IngresarEstudiante("Charlie", {1,4});

    Posicion tmp = cs->PosHippieYEstudiante("Alice");
    ASSERT_EQ(tmp.x, 1);
    ASSERT_EQ(tmp.y, 2);

    tmp = cs->PosHippieYEstudiante("Bob");
    ASSERT_EQ(tmp.x, 1);
    ASSERT_EQ(tmp.y, 3);

    tmp = cs->PosHippieYEstudiante("Charlie");
    ASSERT_EQ(tmp.x, 1);
    ASSERT_EQ(tmp.y, 4);

    delete cs;

}

//void IngresarHippie(String nombre, Posicion p);
void IngresarHippie() {
    CampusSeguro* cs = crearCampusGenerico();

    cs->IngresarHippie("Alice", {1,2});
    cs->IngresarHippie("Bob", {1,3});
    cs->IngresarHippie("Charlie", {1,4});

    Posicion tmp = cs->PosHippieYEstudiante("Alice");
    ASSERT_EQ(tmp.x, 1);
    ASSERT_EQ(tmp.y, 2);

    tmp = cs->PosHippieYEstudiante("Bob");
    ASSERT_EQ(tmp.x, 1);
    ASSERT_EQ(tmp.y, 3);

    tmp = cs->PosHippieYEstudiante("Charlie");
    ASSERT_EQ(tmp.x, 1);
    ASSERT_EQ(tmp.y, 4);

    delete cs;
}

//void MoverEstudiante(String nombre, Direccion dir);
void MoverEstudiante() {
    CampusSeguro* cs = crearCampusConEstYHippies();

    cs->MoverEstudiante("Alice", abajo);
    Posicion tmp = cs->PosHippieYEstudiante("Alice");
    ASSERT_EQ(tmp.x, 2);
    ASSERT_EQ(tmp.y, 2);

    cs->MoverEstudiante("Alice", der);
    tmp = cs->PosHippieYEstudiante("Alice");
    ASSERT_EQ(tmp.x, 2);
    ASSERT_EQ(tmp.y, 3);

    cs->MoverEstudiante("Bob", izq);
    tmp = cs->PosHippieYEstudiante("Bob");
    ASSERT_EQ(tmp.x, 1);
    ASSERT_EQ(tmp.y, 2);

    cs->MoverEstudiante("Alice", arriba);
    tmp = cs->PosHippieYEstudiante("Alice");
    ASSERT_EQ(tmp.x, 1);
    ASSERT_EQ(tmp.y, 3);

    delete cs;
}

//void MoverHippie(String nombre);
void MoverHippie() {
    CampusSeguro* cs = crearCampusConEstYHippies();
    Posicion tmp = cs->PosHippieYEstudiante("Brisa");

    ASSERT_EQ(tmp.x, 9);
    ASSERT_EQ(tmp.y, 2);
    cs->MoverHippie("Brisa");
    tmp = cs->PosHippieYEstudiante("Brisa");
    ASSERT_EQ(tmp.x, 8);
    ASSERT_EQ(tmp.y, 2);
    cs->MoverHippie("Brisa");
    tmp = cs->PosHippieYEstudiante("Brisa");
    ASSERT_EQ(tmp.x, 7);
    ASSERT_EQ(tmp.y, 2);
    cs->MoverHippie("Brisa");
    tmp = cs->PosHippieYEstudiante("Brisa");
    ASSERT_EQ(tmp.x, 6);
    ASSERT_EQ(tmp.y, 2);
    cs->MoverHippie("Brisa");
    tmp = cs->PosHippieYEstudiante("Brisa");
    ASSERT_EQ(tmp.x, 5);
    ASSERT_EQ(tmp.y, 2);

    cs->MoverHippie("Cielo");
    tmp = cs->PosHippieYEstudiante("Cielo");
    ASSERT_EQ(tmp.x, 8);
    ASSERT_EQ(tmp.y, 3);
    cs->MoverHippie("Cielo");
    tmp = cs->PosHippieYEstudiante("Cielo");
    //Estos tests fallan porque la posicion 7,3 tiene un obstaculo, y no sabemos para donde se va a mover.
//    ASSERT_EQ(tmp.x, 7);
//    ASSERT_EQ(tmp.y, 3);
//    cs->MoverHippie("Cielo");
//    tmp = cs->PosHippieYEstudiante("Cielo");
//    ASSERT_EQ(tmp.x, 6);
//    ASSERT_EQ(tmp.y, 3);
//    cs->MoverHippie("Cielo");
//    tmp = cs->PosHippieYEstudiante("Cielo");
//    ASSERT_EQ(tmp.x, 5);
//    ASSERT_EQ(tmp.y, 3);

    delete cs;
}

//void MoverAgente(Nat placa);
void MoverAgente() {
    CampusSeguro* cs = crearCampusConEstYHippies();
    Posicion tmp = cs->PosAgente(20);

    ASSERT_EQ(tmp.x, 9);
    ASSERT_EQ(tmp.y, 9);
    cs->MoverAgente(20);
    tmp = cs->PosAgente(20);
    ASSERT_EQ(tmp.x, 9);
    ASSERT_EQ(tmp.y, 8);
    cs->MoverAgente(20);
    tmp = cs->PosAgente(20);
    ASSERT_EQ(tmp.x, 9);
    ASSERT_EQ(tmp.y, 7);
    cs->MoverAgente(20);
    tmp = cs->PosAgente(20);
    ASSERT_EQ(tmp.x, 9);
    ASSERT_EQ(tmp.y, 6);
    cs->MoverAgente(20);
    tmp = cs->PosAgente(20);
    ASSERT_EQ(tmp.x, 9);
    ASSERT_EQ(tmp.y, 5);
    cs->MoverAgente(20);
    tmp = cs->PosAgente(20);
    ASSERT_EQ(tmp.x, 9);
    ASSERT_EQ(tmp.y, 4);

    tmp = cs->PosAgente(10);
    ASSERT_EQ(tmp.x, 4);
    ASSERT_EQ(tmp.y, 4);
    cs->MoverAgente(10);
    tmp = cs->PosAgente(10);
    ASSERT_EQ(tmp.x, 5);
    ASSERT_EQ(tmp.y, 4);
    cs->MoverAgente(10);
    tmp = cs->PosAgente(10);
    ASSERT_EQ(tmp.x, 6);
    ASSERT_EQ(tmp.y, 4);

    delete cs;
}

//const Campus& dameCampus();
void dameCampus() {
    CampusSeguro* cs = crearCampusConEstYHippies();
    Campus c = cs->dameCampus();
    Campus tmp(10,10);
    tmp.AgregarObstaculo({1,1});
    tmp.AgregarObstaculo({5,5});
    tmp.AgregarObstaculo({3,7});
    tmp.AgregarObstaculo({7,3});

    ASSERT_EQ(c.Ocupada({1,1}),tmp.Ocupada({1,1}));
    ASSERT_EQ(c.Ocupada({5,5}),tmp.Ocupada({5,5}));
    ASSERT_EQ(c.Ocupada({3,7}),tmp.Ocupada({3,7}));
    ASSERT_EQ(c.Ocupada({7,3}),tmp.Ocupada({7,3}));
    ASSERT_EQ(c.Ocupada({6,4}),tmp.Ocupada({6,4}));
    ASSERT_EQ(c.Ocupada({8,2}),tmp.Ocupada({8,2}));

    delete cs;
}

//const Conj<String>& Estudiantes();
void Estudiantes() {
    CampusSeguro* cs = crearCampusConEstYHippies();
    Conj<String>::const_Iterador est = cs->Estudiantes();

//    ASSERT(est.Pertenece("Alice"));
//    ASSERT(est.Pertenece("Bob"));
//    ASSERT(est.Pertenece("Charlie"));
//    ASSERT(!est.Pertenece("tuVieja"));

    delete cs;
}

//const Conj<String>& Hippies();
void Hippies() {
    CampusSeguro* cs = crearCampusConEstYHippies();
    Conj<String>::const_Iterador hip = cs->Hippies();

//    ASSERT(hip.Pertenece("Alba"));
//    ASSERT(hip.Pertenece("Brisa"));
//    ASSERT(hip.Pertenece("Cielo"));
//    ASSERT(!hip.Pertenece("tuVieja"));

    delete cs;
}

//const Conj<Nat>& dameAgentes();
void dameAgentes() {
    CampusSeguro* cs = crearCampusConEstYHippies();
    Conj<Nat>::const_Iterador as = cs->dameAgentes();

//    ASSERT(as.Pertenece(1));
//    ASSERT(as.Pertenece(5));
//    ASSERT(as.Pertenece(10));
//    ASSERT(as.Pertenece(20));
//    ASSERT(!as.Pertenece(3));

    delete cs;
}

//const Nat& CantSanciones(Nat placa);
void CantSanciones() {
    CampusSeguro* cs = crearCampusConEstYHippies();
    delete cs;
}

//const Nat& CantHippiesAtrapados(Nat placa);
void CantHippiesAtrapados() {
    CampusSeguro* cs = crearCampusConEstYHippies();
    delete cs;
}

//Nat CantHippies();
void CantHippies() {
    CampusSeguro* cs = crearCampusConEstYHippies();

    ASSERT_EQ(cs->CantHippies(),3);

    delete cs;
}

//Nat CantEstudiantes();
void CantEstudiantes() {
    CampusSeguro* cs = crearCampusConEstYHippies();

    ASSERT_EQ(cs->CantEstudiantes(),3);

    delete cs;
}

//const Nat& MasVigilante();
void MasVigilante() {
    CampusSeguro* cs = crearCampusConEstYHippies();
    delete cs;
}

//const Conj<Nat>& ConMismasSanciones(Nat placa);
void ConMismasSanciones() {
    CampusSeguro* cs = crearCampusConEstYHippies();
    delete cs;
}

//const Conj<Nat>& ConKSanciones(Nat k);
void ConKSanciones() {
    CampusSeguro* cs = crearCampusConEstYHippies();
    delete cs;
}

// Tests Completos

void testMatriz() {
    std::cout << "Comenzando Tests de Matriz:\n\n";
    RUN_TEST(matriz_crear);
    RUN_TEST(matriz_definirYdef);
    RUN_TEST(matriz_obtener);
    RUN_TEST(matriz_eliminar);
    RUN_TEST(matriz_claves);
    std::cout << "\nFinalizados Tests de Matriz.\n\n";
}

void testDCR() {
    std::cout << "Comenzando Tests de DiccClavesRapidas:\n\n";
    RUN_TEST(dcr_crear);
    RUN_TEST(dcr_definirYdef);
    RUN_TEST(dcr_obtener);
    RUN_TEST(dcr_eliminar);
    RUN_TEST(dcr_claves);
    std::cout << "\nFinalizados Tests de DiccClavesRapidas.\n\n";
}

void testCampus() {
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
}

void testDiccRapido() {
    std::cout << "Comenzando Tests de DiccRapido:\n\n";
    RUN_TEST(dr_Crear);
    RUN_TEST(dr_defYDefinido);
    RUN_TEST(dr_Obtener);
    RUN_TEST(dr_Borrar);
    RUN_TEST(dr_Claves);
    std::cout << "\nFinalizados Tests de DiccRapido.\n\n";
}

void testAgentes() {
    std::cout << "Comenzando Tests de Agentes:\n\n";
    RUN_TEST(agentes_Crear);
    RUN_TEST(agentes_AgregarYPedir);
    RUN_TEST(agentes_MasVigilante);
    RUN_TEST(agentes_ConMismasSanciones);
    RUN_TEST(agentes_ConKSanciones);
    RUN_TEST(agentes_Iterador);
    std::cout << "\nFinalizados Tests de Agentes.\n\n";
}

void testHypYEst(){
    std::cout << "Comenzando Tests de Hippies y Est:\n\n";
    RUN_TEST(hyp_HippiesYEstudiantes);
    RUN_TEST(hyp_DefinirHippie_Esta_EsHippie);
    RUN_TEST(hyp_DefinirEstudiante_Esta_EsEst);
    RUN_TEST(hyp_PosHippieYEstudiante);
    RUN_TEST(hyp_Estudiantes);
    RUN_TEST(hyp_Hippies);
    RUN_TEST(hyp_Borrar);
    std::cout << "\nFinalizados Tests de Hippies y Est.\n\n";
}

void testCampusSeguro(){
    std::cout << "Comenzando Tests de Campus Seguro:\n\n";
    RUN_TEST(cs_crear);
    RUN_TEST(IngresarEstudiante);
    RUN_TEST(IngresarHippie);
    RUN_TEST(MoverEstudiante);
    RUN_TEST(MoverHippie);
    RUN_TEST(MoverAgente);
    RUN_TEST(dameCampus);
    RUN_TEST(Estudiantes);
    RUN_TEST(Hippies);
    RUN_TEST(dameAgentes);

//    RUN_TEST(CantSanciones);
//    RUN_TEST(CantHippiesAtrapados);
    RUN_TEST(CantHippies);
    RUN_TEST(CantEstudiantes);
//    RUN_TEST(MasVigilante);
//    RUN_TEST(ConMismasSanciones);
//    RUN_TEST(ConKSanciones);

    std::cout << "\nFinalizados Tests de Campus Seguro.\n\n";
}

int main(int argc, char **argv)
{
    RUN_TEST(testMatriz);
    RUN_TEST(testDCR);
    RUN_TEST(testCampus);
    RUN_TEST(testDiccRapido);
    RUN_TEST(testAgentes);
    RUN_TEST(testHypYEst);
    RUN_TEST(testCampusSeguro);
    return 0;
}

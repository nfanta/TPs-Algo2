#include "Driver.h"
#include "mini_test.h"
#include "../Matriz.h"
#include "../DiccClavesRapidas.h"
#include "Tipos.h"

#include <string>
#include <iostream>

using namespace aed2;


// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de test, con llamadas a las rutinas de aserción 
 * definidas en mini_test.h
 */

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

int main(int argc, char **argv)
{
//    std::cout << "Comenzando Tests de Matriz:\n\n";
//    RUN_TEST(matriz_crear);
//    RUN_TEST(matriz_definirYdef);
//    RUN_TEST(matriz_obtener);
//    RUN_TEST(matriz_eliminar);
//    RUN_TEST(matriz_claves);
//    std::cout << "\nFinalizados Tests de Matriz.\n\n";

    std::cout << "Comenzando Tests de DiccClavesRapidas:\n\n";
    RUN_TEST(dcr_crear);
    RUN_TEST(dcr_definirYdef);
    RUN_TEST(dcr_obtener);
    RUN_TEST(dcr_eliminar);
    RUN_TEST(dcr_claves);
    std::cout << "\nFinalizados Tests de DiccClavesRapidas.\n\n";

	return 0;
}

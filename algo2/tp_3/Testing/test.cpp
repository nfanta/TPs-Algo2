#include "Driver.h"
#include "mini_test.h"
#include "../Matriz.h"
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

int main(int argc, char **argv)
{
    std::cout << "Comenzando Tests de Matriz:\n\n";
    RUN_TEST(matriz_crear);
    RUN_TEST(matriz_definirYdef);
    RUN_TEST(matriz_obtener);
    RUN_TEST(matriz_eliminar);
    RUN_TEST(matriz_claves);

	return 0;
}

cmake_minimum_required(VERSION 3.3)
project(tp_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        Testing/aed2/Arreglo.h
        Testing/aed2/Conj.h
        Testing/aed2/ConjAcotado.cpp
        Testing/aed2/ConjAcotado.h
        Testing/aed2/Dicc.h
        Testing/aed2/Lista.h
        Testing/aed2/TiposBasicos.h
        Testing/aed2/Vector.h
        Testing/aed2.h
        Testing/Driver.cpp
        Testing/Driver.h
        Testing/mini_test.h
        Testing/test.cpp
        Testing/Tipos.h
        DiccRapido.h Matriz.h)

add_executable(tp_3 ${SOURCE_FILES})
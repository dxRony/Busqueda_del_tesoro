cmake_minimum_required(VERSION 3.30)
project(Busqueda_del_tesoro)

set(CMAKE_CXX_STANDARD 11)

add_executable(Busqueda_del_tesoro main.cpp
        include/Casilla.h
        include/Jugador.h
        include/Tesoro.h
        include/Enemigo.h
        include/Trampa.h
        include/Pocima.h
        include/Pista.h
        src/Casilla.cpp
        src/Enemigo.cpp
        src/Jugador.cpp
        src/Pista.cpp
        src/Pocima.cpp
        src/Tesoro.cpp
        src/Trampa.cpp
        include/edd/Node.h
        include/edd/LinkedList.h
        include/edd/BST.h)

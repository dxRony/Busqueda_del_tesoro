//
// Created by ronyrojas on 27/03/25.
//

#ifndef PARTIDA_H
#define PARTIDA_H
#include "Enemigo.h"
#include "Trampa.h"
#include "edd/BST.h"
#include "edd/LinkedList.h"
#include "edd/ThreeDimensionalMatrix.h"
using namespace std;

class Partida {
private:
    ThreeDimensionalMatrix<Casilla> *tableroDeJuego;
    BST<Enemigo> *enemigosPartida;
    BST<Trampa> *trampasPartida;
    LinkedList<string> *registroTrayectoria;
    LinkedList<string> *registroEnemigosYTrampas;
    LinkedList<string> *registroPistas;
    LinkedList<string> *registroPocimas;

public:
    Partida();
};
#endif //PARTIDA_H

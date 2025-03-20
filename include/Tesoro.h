//
// Created by ronyrojas on 20/03/25.
//

#ifndef TESORO_H
#define TESORO_H
#include "Casilla.h"

class Tesoro : public Casilla {
private:
    int valor;

public:
    Tesoro();

    int getValor();

    void setValor(int valor);
};


#endif //TESORO_H

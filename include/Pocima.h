//
// Created by ronyrojas on 20/03/25.
//

#ifndef POCIMA_H
#define POCIMA_H
#include "Casilla.h"
class Pocima : public Casilla {
private:
    int curacion;

public:
    Pocima();

    int getCuracion();

    void setCuracion(int curacion);
};

#endif //POCIMA_H

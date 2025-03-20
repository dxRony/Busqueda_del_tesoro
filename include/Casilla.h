//
// Created by ronyrojas on 20/03/25.
//

#ifndef CASILLA_H
#define CASILLA_H
#include <string>

class Casilla {
private:
    int posicionX;
    int posicionY;
    int posicionZ;

public:
    Casilla();

    //getters y setters
    int getPosicionX() const;

    void setPosicionX(int posicion_x);

    int getPosicionY() const;

    void setPosicionY(int posicion_y);

    int getPosicionZ() const;

    void setPosicionZ(int posicion_z);
};
#endif //CASILLA_H

//
// Created by ronyrojas on 20/03/25.
//

#ifndef CASILLA_H
#define CASILLA_H
#include <iostream>
using namespace std;

class Casilla {
private:
    int posicionX;
    int posicionY;
    int posicionZ;
    string ubicacion;

public:
    Casilla();

    //getters y setters
    int getPosicionX() const;

    void setPosicionX(int posicion_x);

    int getPosicionY() const;

    void setPosicionY(int posicion_y);

    int getPosicionZ() const;

    void setPosicionZ(int posicion_z);

    string getUbicacion() const;

    void setUbicacion(string ubicacion);
};
#endif //CASILLA_H

//
// Created by ronyrojas on 20/03/25.
//

#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "Casilla.h"

class Enemigo : public Casilla {
private:
    bool nivelAlto;
    int vida;

public:
    Enemigo();

    bool isNivelAlto() const;

    void setIsNivelAlto(bool nivelAlto);

    int getVida() const;

    void setVida(int vida);
};
#endif //ENEMIGO_H

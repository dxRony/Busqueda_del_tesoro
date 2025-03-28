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

    // usando sobrecarga para la comparacion de enemigos por vida
    bool operator<(const Enemigo &enemigoACompararar) const {
        return this->vida < enemigoACompararar.getVida();
    }

    bool operator>(const Enemigo &enemigoACompararar) const {
        return this->vida > enemigoACompararar.getVida();
    }

    bool operator==(const Enemigo &enemigoACompararar) const {
        return this->vida == enemigoACompararar.getVida();
    }
};
#endif //ENEMIGO_H

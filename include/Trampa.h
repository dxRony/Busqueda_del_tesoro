//
// Created by ronyrojas on 20/03/25.
//

#ifndef TRAMPA_H
#define TRAMPA_H
#include "Casilla.h"

class Trampa : public Casilla {
private:
    int dano;

public:
    Trampa();

    int getDano() const;

    void setDano(int dano);

    //sobrecarga para la comparacion de trampas por dano
    bool operator<(const Trampa &trampaAComparar) const {
        return this->dano < trampaAComparar.getDano();
    }

    bool operator>(const Trampa &trampaAComparar) const {
        return this->dano > trampaAComparar.getDano();
    }

    bool operator==(const Trampa &trampaAComparar) const {
        return this->dano == trampaAComparar.getDano();
    }
};
#endif //TRAMPA_H

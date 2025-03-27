//
// Created by ronyrojas on 27/03/25.
//

#ifndef MOTORDEJUEGO_H
#define MOTORDEJUEGO_H

class MotorDeJuego {
public:
    void mostrarMenu();

private:
    void nuevaPartida();

    void verReportes();

    bool finalizarEjecucion = false;
};
#endif //MOTORDEJUEGO_H

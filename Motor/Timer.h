#include <SFML/Graphics.hpp>


#ifndef TIMER_H
#define TIMER_H


class Timer{
    private:
        float tiempoActual;
        float tiempoMaximo;
    public:
        Timer();
        Timer(float p_tiempoMaximo);
        float avanzar(float deltaTime);
        float reset();
        float getTiempoActual(){return tiempoActual;}
        float getMaximo(){return tiempoMaximo;}
        float setMaximo(float p_max);
};

#endif
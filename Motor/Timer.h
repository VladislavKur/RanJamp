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
        void reset();
        float getTiempoActual(){return tiempoActual;}
        float getMaximo(){return tiempoMaximo;}
        void setMaximo(float p_max);
};

#endif
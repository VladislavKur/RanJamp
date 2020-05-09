#include "Timer.h"

Timer::Timer(){
    tiempoMaximo=500;
    tiempoActual=500;
}

Timer::Timer(float p_tiempoMaximo){
    tiempoMaximo=p_tiempoMaximo;
    tiempoActual=p_tiempoMaximo;
}

float Timer::avanzar(float deltaTime){
    tiempoActual -= deltaTime;
    if(tiempoActual<0) tiempoActual=0;
    return tiempoActual;
}

void Timer::reset(){
    tiempoActual=tiempoMaximo;
}

void Timer::setMaximo(float p_max){
    tiempoMaximo=p_max;
}

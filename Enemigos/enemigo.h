#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Rectangulo/Rectangulo.h"
#include "../Motor/Motor.h"
#include "../Player/Player.h"
#include "../Cuerpo/Cuerpo.h"

#ifndef ENEMIGO_H
#define ENEMIGO_H

class Enemigo{
    public:
        ~Enemigo();
        virtual void update(Player* player, float deltaTime){}; ///player
        virtual void render(float porcentaje){};
        virtual void updateHitbox(){}
        bool muerto;
        Cuerpo* getCuerpo();
        bool comprobarColision(Cuerpo* cuerpo);

        int getVidas();
        void setVidas(int v);
        
    protected:
        Enemigo(float x, float y, int sizeWidth, int sizeHeight, 
            std::string fichero, float escala);
        void actualizarPosicion(float x, float y);

        Cuerpo* body;
        float velocidad;
        int modo;
        bool colision;
        int vidas;

        Rectangulo * coliAbajo;
        Rectangulo * coliArriba;
        Rectangulo * coliIzquierda;
        Rectangulo * coliDerecha;
       
};


#endif
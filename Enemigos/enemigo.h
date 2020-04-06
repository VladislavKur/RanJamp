#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Motor/Motor.h"
#include "../Player/Player.h"

#ifndef ENEMIGO_H
#define ENEMIGO_H

class Enemigo{
    public:
        virtual void update(Player* player, float deltaTime){}; ///player
        virtual void render(float porcentaje){};
        sf::RectangleShape getCuerpo(){return cuerpo;};
        ~Enemigo();
        bool colision;
        virtual void updateHitbox(){}
        sf::FloatRect coliAbajo;
        sf::FloatRect coliArriba;
        sf::FloatRect coliIzquierda;
        sf::FloatRect coliDerecha;
        void morir();
        int getVidas(){return vida;}
    protected:
        float posX, posY;
        float posXanterior, posYanterior;
        float diffX, diffY;
        float velocidad;
        int modo;
        int vida;
        Enemigo(float x, float y);
        //sf::FloatRect colision;
        sf::RectangleShape cuerpo;
        sf::Clock relojAnim;
        void actualizarPosicion(float x, float y);
       
};


#endif
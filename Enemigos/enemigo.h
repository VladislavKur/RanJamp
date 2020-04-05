#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Motor/Motor.h"


#ifndef ENEMIGO_H
#define ENEMIGO_H

class Enemigo{
    public:
        virtual void update(sf::RectangleShape& player, float delta){}; ///player
        virtual void render(float porcentaje){};
        ~Enemigo();

    protected:
        float posX, posY;
        float posXanterior, posYanterior;
        float diffX, diffY;
        float velocidad;
        int modo;
        int vida;
        Enemigo(float x, float y);
        
        sf::RectangleShape cuerpo;
        sf::Clock relojAnim;
        void actualizarPosicion(float x, float y);
        void morir();
        int getVidas(){return vida;}
};


#endif
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Motor/Motor.h"


#ifndef ENEMIGO_H
#define ENEMIGO_H

class Enemigo{
    public:
        virtual void update(sf::RectangleShape& player, float delta){}; ///player
        virtual void render( float porcentaje){};

    protected:
        float posX, posY;
        float posXanterior, posYanterior;
        float diffX, diffY;
        float velocidad;
        int modo;
        Enemigo(sf::Texture& tex,float x, float y);
        ~Enemigo();
        sf::Sprite cuerpo;
        sf::Clock relojAnim;
        void actualizarPosicion(float x, float y);
};


#endif
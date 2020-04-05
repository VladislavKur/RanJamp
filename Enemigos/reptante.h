#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemigo.h"
//#include "../Collider/Collider.h"

#ifndef REPTANTE_H
#define REPTANTE_H


class Reptante : public Enemigo{
    private:
        sf::RectangleShape esqIzq;
        sf::RectangleShape esqDcha;
       
        int direccion;
    public:
        Reptante(float x, float y);
        void update(Player* player, float delta);
        void render( float porcentaje);   
        //Collider getCollider(){return Collider(cuerpo);}
};

#endif

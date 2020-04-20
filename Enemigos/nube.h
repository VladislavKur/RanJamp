#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemigo.h"
#include "../Bullet/bullet.h"

#ifndef NUBE_H
#define NUBE_H

using namespace std;

class Nube : public Enemigo{
    private:
        int distanciaAtaque;
        int altura;
        int direccion = 0;
        bool shoot;
        float shootTime;
        
    public:
        Nube(float x, float y);
        ~Nube();
        void update(sf::RectangleShape& player, float deltaTime);
        void render(sf::RenderWindow &v, float porcentaje);
        Bullet* disparar();
};

#endif

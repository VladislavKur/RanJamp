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
        int direccion = 0;
        float shootTime;
        bool shoot;
        
    public:
        Nube(float x, float y);
        ~Nube();
        void update(Player* player, float deltaTime);
        void render( float porcentaje);
        Bullet* disparar();
        bool getShoot();
};

#endif

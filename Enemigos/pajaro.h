#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemigo.h"
//#include "../Collider/Collider.h"

#ifndef PAJARO_H
#define PAJARO_H


class Pajaro : public Enemigo{
    private:       
        int direccion;
        int alturaMax = 100;
        int alturaMaxRelativa;
        int alturaMinRelativa;
        float alturaActual;
        bool haPegado;

    public:
        Pajaro(float x, float y);
        ~Pajaro();
        void update(Player* player, float delta);
        void render( float porcentaje);
        
        void updateHitbox();
};

#endif

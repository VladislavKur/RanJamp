#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemigo.h"
//#include "../Collider/Collider.h"

#ifndef PAJARO_H
#define PAJARO_H


class Pajaro : public Enemigo{
    private:       
        int sizeWidth;
        int sizeHeight;
        int direccion;
        int alturaMax = 100;
        int alturaMaxRelativa;
        int alturaMinRelativa;
        float alturaActual;
        float tamanyoWidthEsquina;
        float tamanyoHeightEsquina;
        bool haPegado;

        void updateHitbox();
    public:
        Pajaro(float x, float y);
        void update(Player* player, float delta);
        void render( float porcentaje);
        
        //Collider getCollider(){return Collider(cuerpo);}
};

#endif

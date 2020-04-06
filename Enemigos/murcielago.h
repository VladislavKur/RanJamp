#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemigo.h"

#ifndef MURCIELAGO_H
#define MURCIELAGO_H

class Murcielago : public Enemigo{
    private:
        int distanciaAtaque;
        int altura;
        int direccion = 0;
        
    public:
        Murcielago(float x, float y);
        void update(Player* player, float delta);
        void render( float porcentaje);  
        bool haPegado; 
};

#endif

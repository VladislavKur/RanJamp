#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System.hpp>

#include "../Textura/Textura.h"
#include "../Motor/Motor.h"
using namespace sf;
using namespace std;

#ifndef BLOQUE_H
#define BLOQUE_H
class Bloque{
    public:
        Bloque(Textura * t);
        ~Bloque();
        void setTextureRect(int x, int y, int ancho, int largo);
        void setOrigin(float x, float y);
        void setPosition(float x , float y);
        void render();
        void setTextura(Textura * t);
    private:
        sf::Sprite * s;
        Motor * motor;
};
#endif
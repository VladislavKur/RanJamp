#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System.hpp>

#include "../Motor/Motor.h"
using namespace sf;
using namespace std;

#ifndef TEXTURA_H
#define TEXTURA_H
class Textura{
    friend class Bloque;
    public:
        Textura(string entrada);
        Textura(const char * entrada);
        ~Textura();
    protected:
        Texture * getTexture();
    private:
        Texture * t;
        Motor * motor;
};
#endif
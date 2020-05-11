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
    //friend class Bloque;
    public:
        //creas un objeto textura donde se almacena una textura de smfl (fachada)
        Textura(){};
        //constructor 2 que se le pasa el nombre de la textura directamente
        Textura(string entrada);
        ~Textura();
        Texture * getTexture();
        void setTexture(string entrada);
    protected:
        
    private:
        Texture * t;
        Motor * motor;
     
};
#endif
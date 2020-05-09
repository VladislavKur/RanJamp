#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Motor/Motor.h"

#ifndef ANIMACION_H
#define ANIMACION_H

class Animacion{

    private:
        //funciones
        void nextSprite();
        //variables objeto
        sf::Shape* body;
        Motor * motor;
        //variables basicas
        int tamX, tamY; //tamaño del sprite
        int posicionesX,posicionesY; //el numero de sprites que hay
        int numeroSpriteX, numeroSpriteY; //el numero ACTUAL del sprite
        float tiempoActual, tiempoAnterior, tiempoDuracionMax, tiempoDiff;
        bool cambiado;

    public:
        Animacion(){};
        Animacion(sf::Shape* cuerpo, float timeAnimation,
            int spriteSizeX, int spriteSizeY, int textureSizeX, int textureSizeY
            );
        ~Animacion();
        void update(float deltaTime);
        void render(float porcentaje);
        void setSprite(int spriteNumber);
        int getAnimationNumbers(){return posicionesX;};

};

#endif
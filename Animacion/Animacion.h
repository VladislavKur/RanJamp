#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Motor/Motor.h"

#ifndef ANIMACION_H
#define ANIMACION_H

class Animacion{

    private:
        //funciones

        //Pasa al siguiente paso de animación ya que va cambiando sprite cíclicamente.
        //Esta función pasa al siguiente sprite y lo recorta, dando sensación de dinamismo.
        void nextSprite();
        //variables objeto

        //Dirección de memoria a Rectangleshape de SFML.
        sf::Shape* body;
        //Direccion de memoria a motor.
        Motor * motor;
        //variables basicas
        
        //Tamaño del sprite.
        int tamX, tamY;
        //El número de sprites que hay.
        int posicionesX,posicionesY;
        //La posicion del sprite actual.
        int numeroSpriteX, numeroSpriteY;
        //Variables de tiempo interpolados.
        float tiempoActual, tiempoAnterior, tiempoDuracionMax, tiempoDiff;
        //Variable que nos permite saber si el sprite cambió o no
        bool cambiado;

    public:
        //Constructor de Animacion.
        //cuerpo: rectangle o circleshape asociado
        //timeAnimation: la duración máxima de la animación.
        //spriteSizeX: el tamaño del sprite en ancho.
        //spriteSzeY: el tamaño del sprite en alto.
        //textureSizeX: el tamaño de la textura en ancho.
        //textureSizeY: el tamaño de la textura en alto.
        Animacion(){};
        Animacion(sf::Shape* cuerpo, float timeAnimation,
            int spriteSizeX, int spriteSizeY, int textureSizeX, int textureSizeY
            );
        ~Animacion();
        //Update interpolado de la animacion.
        void update(float deltaTime);
        //Render interpolado de la animacion.
        //Permite el cambio entre un sprite u otro.
        void render(float porcentaje);
        //Cambiar el tiempo de la animación.
        void setTimeAnimacion(float entrada);
        //Cambiar de sprite.
        //Se hace desde el exterior.
        void setSprite(int spriteNumber);
        //Nos devuelve el valor de los paso de la animación.
        int getAnimationNumbers(){return posicionesX;};
        //Nos devuelve el valor del paso de animación.
        int getPosicionX(){return numeroSpriteX;};
        //Nos devuelve la duración de la animación.
        float getTimeAnimation(){return tiempoDuracionMax;}

};

#endif
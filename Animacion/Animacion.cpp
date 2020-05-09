#include "Animacion.h"
#include <SFML/Graphics.hpp>
#include <iostream>


Animacion::~Animacion(){
    body=NULL;
}

Animacion::Animacion(sf::Shape* cuerpo, float timeAnimation, int spriteSizeX, int spriteSizeY, int textureSizeX, int textureSizeY){

    motor = Motor::instance();
    
    body  = cuerpo;

    tiempoDuracionMax = timeAnimation;

    tamX = spriteSizeX;
    tamY = spriteSizeY;

    numeroSpriteX = 0;
    numeroSpriteY = 0;

    tiempoActual = tiempoDuracionMax;
    tiempoAnterior = tiempoDuracionMax;
    tiempoDiff = 0;
    cambiado = false;

}

void Animacion::update(float deltaTime){
    
    tiempoAnterior = tiempoActual;
    tiempoActual -= deltaTime;
    tiempoDiff = abs(tiempoActual - tiempoAnterior);

    if(tiempoActual < 0.0){
        tiempoActual += tiempoDuracionMax;
        cambiado = true;
    }
}

void Animacion::setSprite(int spriteNumber){

    if(numeroSpriteY < posicionesY){        
        numeroSpriteY = spriteNumber;
        motor->recorte(body, numeroSpriteX, numeroSpriteY, tamX, tamY);
    }
    else
        numeroSpriteY = 0;
}

void Animacion::nextSprite(){
    numeroSpriteX++;

    if(numeroSpriteX == posicionesX)
        numeroSpriteX = 0;

    motor->recorte(body, numeroSpriteX, numeroSpriteY, tamX, tamY);
}

void Animacion::render(float porcentaje){
    if(cambiado){
        int aux = tiempoAnterior - tiempoDiff*porcentaje;

        if(aux <= 0){
            cambiado = false;
            nextSprite();
        }
    }
}
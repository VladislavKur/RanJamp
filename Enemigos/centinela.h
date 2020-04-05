#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemigo.h"

#ifndef CENTINELA_H
#define CENTINELA_H

class Centinela : public Enemigo{
    private:
        int distanciaAtaque;
        int distanciaDisparo;
        void disparar(); //devuelve bala o nada ??????

    public:
        Centinela(float x, float y);
        void update(sf::RectangleShape& player, float delta);
        void render( float porcentaje);   
};

#endif

/*
class Centinela{

    public:
        Centinela(sf::Texture& tex);
        Centinela(sf::Texture& tex,int x, int y);
        void update(sf::RectangleShape& entrada, float deltaTime);
        void render(sf::RenderWindow& entrada, float porcentaje);
    private:
        void actualizarPosicion(float entradaX, float entradaY);
        float posX;
        float posY;
        float posXanterior;
        float posYanterior;
        float diffX;
        float diffY;
        float velocidad = 60;
        int modo;
        //modo: 0 quieto, modo: 1 caminar, modo: 2 matar
        sf::Sprite cuerpo;
        static const int distanciaAcercamiento = 600;
        static const int distanciaDisparo = 100;

};*/
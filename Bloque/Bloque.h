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
        //CONSTRUCTOR, AL CUAL SE LE PASA UN PUNTERO DE TEXTURA 
        //QUE CARGARA AL SPRITE INICIALIZADO
        Bloque(Textura * t);

        //DESTRUCTOR BLOQUE 
        ~Bloque();

        //LLAMA A MOTOR RECORTE CON LOS ATRIBUTOS PASADOS POR PAREMETRO QUE SON LA POSICION DE LA IMAGEN Y 
        //EL ANCHO Y ALTO
        void setTextureRect(int x, int y, int ancho, int largo);
       
        //LLAMA AL SET ORIGIN2 DE MOTOR QUE CAMBIA EL ORIGEN DEL SPRITE
        void setOrigin(float x, float y);

        //LLAMA A POSICIONAR DE MOTOR EL CUAL POSICIONA EL SPRITE EN LA POSICION PASADA POR PAREMETRO 
        void setPosition(float x , float y);

        //LLAMA A MOTOR DIBUJO DEL SPRITE Y LO RENDERIZA
        void render();

        //CAMBIA LA TEXTURA DEL SPRITE
        void setTextura(Textura * t);
    private:
        sf::Sprite * s;
        Motor * motor;
};
#endif
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Motor/Motor.h"
#include "../Animacion/Animacion.h"

#ifndef CUERPO_H
#define CUERPO_H

class Cuerpo{

    private:
        //variables objeto
        //Animacion* animacion;
        sf::Shape* body;
        //Motor* motor;
        sf::Texture* textura;
        //basicas
        //bool meMovi;
        float class_positionX, class_positionY;
        //float escalaCuerpo;
        float class_previousX,class_previousY;

    public:
        Cuerpo(float x_entrada, float y_entrada, int sizeHeight, int sizeWidth, 
            std::string fichero, float timeAnimacion, int escala);
        ~Cuerpo();
        void posicionamiento(float x_entrada,float y_entrada);
        std::vector<int> texturizar(std::string entrada, int sizeHeight, int sizeWidth);
        std::vector<float> getBounds();
        void update(float deltaTime);
        void render(float porcentaje);
        void setSpriteAnimacion(int entrada);
        void dinamizarSprite(float entrada, int sprite);
        void setNuevoFichero(std::string entrada,int spriteSizeX, int spriteSizeY, 
            int textureSizeX, int textureSizeY);
        bool colisiona(Cuerpo* entrada);
        std::vector<float> getPosicion();
        std::vector<float>getSize();

};

#endif
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Motor/Motor.h"
#include "../Animacion/Animacion.h"
#include "../Enumerador/typeBody.h"

#ifndef CUERPO_H
#define CUERPO_H

using namespace std;

class Cuerpo{

    private:
        //variables objeto
        Animacion* animacion;
        sf::Shape* body;
        Motor* motor;
        sf::Texture* class_textura;
        //basicas
        bool class_move;
        float class_positionX, class_positionY;
        float class_escala;
        float class_previousX, class_previousY;
        int class_width, class_height;
        int class_widthTexture, class_heightTexture;

    public:
        Cuerpo(float x_entrada, float y_entrada, int sizeWidth, int sizeHeight, 
            std::string fichero, float escala, typeBody tipoCuerpo); //cambiar tipo por enum (0: RS, 1:CS)
        ~Cuerpo();
        void posicionamiento(float x_entrada,float y_entrada);
        std::vector<int> texturizar(std::string entrada, int sizeWidth, int sizeHeight);
        std::vector<float> getBounds();
        void update(float deltaTime);
        void render(float porcentaje);
        void addAnimacion(float timeAnimacion);
        void setSpriteAnimacion(int entrada);
        bool colisiona(Cuerpo* entrada);
        std::vector<float> getPosicion();
        std::vector<float>getSize();

};

#endif
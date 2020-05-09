#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Rectangulo/Rectangulo.h"
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
        Rectangulo* rectangulo;
        sf::Texture* class_textura;
        //basicas
        bool class_move;
        float class_positionX, class_positionY;
        float class_escala;
        float class_previousX, class_previousY;
        int class_width, class_height;
        int class_widthTexture, class_heightTexture;
        int class_tipo;
    public:
        Cuerpo(float x_entrada, float y_entrada, int sizeWidth, int sizeHeight, 
            std::string fichero, float escala, typeBody tipoCuerpo); //cambiar tipo por enum (0: RS, 1:CS)
        Cuerpo(float x , float y, int sizeWidth , int sizeHeight);
        Cuerpo(float x , float y, int sizeWidth , int sizeHeight, int type);
        Cuerpo(float x_entrada, float y_entrada, int sizeWidth, int sizeHeight, 
            std::string fichero, float escala, int tipoCuerpo, int type);
        ~Cuerpo();
        void posicionamiento(float x_entrada,float y_entrada);
        std::vector<int> texturizar(std::string entrada, int sizeWidth, int sizeHeight);
        std::vector<float> getBounds();
        void update(float deltaTime);
        //Hola 
        void Origen(float, float);
        void Scalar(float, float);
        void render(float porcentaje);
        void render();
        void moverse(float x, float y);
        void addAnimacion(float timeAnimacion);
        void setSpriteAnimacion(int entrada);
        void setSize(float sizeX, float sizeY);
        bool colisiona(Cuerpo * entrada);
        void recorte(int x , int y);
        std::vector<float> getPosicion();
        std::vector<float>getSize();
        Rectangulo * getGlobalBounds();
        int getTipo();
        float getOriginY(){return body->getOrigin().y;};
};

#endif
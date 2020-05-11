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

        //Animación asignada al cuerpo.
        Animacion* animacion;
        //Shape de SFML asignado al cuerpo.
        sf::Shape* body;
        //Dirección de memoria que apunta al motor gráfico.
        Motor* motor;
        //Textura asignada al cuerpo.
        sf::Texture* class_textura;
        
        //Determina si el cuerpo se está moviendo o no.
        bool class_move;
        //Determina la posición del cuerpo en la ventana.
        float class_positionX, class_positionY;
        //Determina la escala del cuerpo.
        float class_escala;
        //Determina la posición anterior del cuerpo.
        //Esto nos sirve para calcular la interpolación.
        float class_previousX, class_previousY;
        //Anchura del cuerpo.
        int class_width;
        //Altura del cuerpo.
        int class_height;
        //Anchura de la textura asignada al cuerpo.
        int class_widthTexture;
        //Altura de la textura asignada al cuerpo.
        int class_heightTexture;
        //Precio del objeto en la tienda.
        int class_tipo;
    public:
        //Constructor del Cuerpo.
        //x_entrada: 
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
        void setTimeAnimacion(float entrada);
        void setSize(float sizeX, float sizeY);
        void setTipo(int x){class_tipo+=x;}
        bool colisiona(Cuerpo * entrada);
        void rotar(float angulo);
        void recorte(int x , int y);
        std::vector<float> getPosicion();
        std::vector<float>getSize();
        Rectangulo * getGlobalBounds();
        int getTipo();
        float getOriginY(){return body->getOrigin().y;};
        int getPosicionX(){return animacion->getPosicionX();};
        float getTimeAnimacion(){return animacion->getTimeAnimation();};

        void posicionamientoFijo(float x_entrada,float y_entrada);
};

#endif
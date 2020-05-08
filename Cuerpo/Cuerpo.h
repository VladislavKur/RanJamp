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

    public:
        //Se le asocia una posicion x e y, ademas se establece tanto el ancho como el alto del rectangle o circle shape, tambien el fichero de la textura
        //para ese cuerpo, y la escala que tendra. Por ultimo un enum para saber si es rectangleshape o circleshape.
        //En este metodo se llama a posicionamiento y texturizar. Se establece el tamanyo y la escala del cuerpo
        Cuerpo(float x_entrada, float y_entrada, int sizeWidth, int sizeHeight, 
            std::string fichero, float escala, typeBody tipoCuerpo); //cambiar tipo por enum (0: RS, 1:CS)
        Cuerpo(float x , float y, int sizeWidth , int sizeHeight);
        ~Cuerpo();
        
        //Se actualiza la posicion tanto actual como la anterior con las nuevas coordenadas, para la interpolacion
        void posicionamiento(float x_entrada,float y_entrada);
        //Se carga el fichero en la textura que se aplica al cuerpo, y se aplica el tamanyo de la misma, ademas del origen
        vector<int> texturizar(string entrada, int sizeWidth, int sizeHeight);
        //Se obtiene el globalBound del cuerpo
        vector<float> getBounds();
        //Si la variable class_move es true, es decir, el cuerpo se ha movido, entonces se llama al update de animacion para actualizar la imagen
        //y se actualiza tambien las variable de posicion anterior siendo esta ahora la actual
        void update(float deltaTime);
        //Hola 
        void Origen(float, float);
        void Scalar(float, float);
        void render(float porcentaje);
        void moverse(float x, float y);
        void addAnimacion(float timeAnimacion);
        //asocio a la animacion la posicion en la que se encuentra de toda la matriz textura
        void setSpriteAnimacion(int entrada);
        void setSize(float sizeX, float sizeY);
        bool colisiona(Cuerpo * entrada);
        std::vector<float> getPosicion();
        std::vector<float>getSize();
        Rectangulo * getGlobalBounds();
        float getOriginY(){return body->getOrigin().y;};
};

#endif
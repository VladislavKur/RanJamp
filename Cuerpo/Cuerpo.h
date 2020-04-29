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
        //Se le asocia una posicion x e y, ademas se establece tanto el ancho como el alto del rectangle o circle shape, tambien el fichero de la textura
        //para ese cuerpo, y la escala que tendra. Por ultimo un enum para saber si es rectangleshape o circleshape.
        //En este metodo se llama a posicionamiento y texturizar. Se establece el tamanyo y la escala del cuerpo
        Cuerpo(float x_entrada, float y_entrada, int sizeWidth, int sizeHeight, 
            string fichero, float escala, typeBody tipoCuerpo);
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
        //Se renderiza la animacion, y se cambia la poscion segun la posicion anterior y el porcentaje entre la poscicion anterior y actual
        void render(float porcentaje);
        //creo una nueva animacion
        void addAnimacion(float timeAnimacion);
        //asocio a la animacion la posicion en la que se encuentra de toda la matriz textura
        void setSpriteAnimacion(int entrada);
        //comprueba en el motor si ha habido alguna interseccion entre dos cuerpos
        bool colisiona(Cuerpo* entrada);
        //devuelve un vector con la posicion actual de x e y del cuerpo
        vector<float> getPosicion();
        //devuelve el tamanyo del cuerpo en x e y
        vector<float>getSize();

};

#endif
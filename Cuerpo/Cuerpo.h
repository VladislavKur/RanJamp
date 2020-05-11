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
        //x_entrada: Posicion en X del cuerpo inicial.
        //x_entrada: Posicion en X del cuerpo inicial.
        //sizeWidth: Tamaño del cuerpo en anchura.
        //sizeHeight: Tamaño del cuerpo en altura.
        //fichero: Nombre del fichero de la textura.
        //escala: Escalado del tamaño del cuerpo.
        //tipoCuerpo: Tipo de Shape.
        Cuerpo(float x_entrada, float y_entrada, int sizeWidth, int sizeHeight, 
            std::string fichero, float escala, typeBody tipoCuerpo); //cambiar tipo por enum (0: RS, 1:CS)
        //Constructor del Cuerpo.
        //x_entrada: Posicion en X del cuerpo inicial.
        //x_entrada: Posicion en X del cuerpo inicial.
        //sizeWidth: Tamaño del cuerpo en anchura.
        //sizeHeight: Tamaño del cuerpo en altura.
        Cuerpo(float x , float y, int sizeWidth , int sizeHeight);
        //Constructor del Cuerpo.
        //x_entrada: Posicion en X del cuerpo inicial.
        //x_entrada: Posicion en X del cuerpo inicial.
        //sizeWidth: Tamaño del cuerpo en anchura.
        //sizeHeight: Tamaño del cuerpo en altura.
        //tipo: valor del objeto en la tienda.
        Cuerpo(float x , float y, int sizeWidth , int sizeHeight, int type);
        //Constructor del Cuerpo.
        //x_entrada: Posicion en X del cuerpo inicial.
        //x_entrada: Posicion en X del cuerpo inicial.
        //sizeWidth: Tamaño del cuerpo en anchura.
        //sizeHeight: Tamaño del cuerpo en altura.
        //fichero: Nombre del fichero de la textura.
        //escala: Escalado del tamaño del cuerpo.
        //tipoCuerpo: Tipo de Shape.
        //type: valor del objeto en la tienda.
        Cuerpo(float x_entrada, float y_entrada, int sizeWidth, int sizeHeight, 
            std::string fichero, float escala, int tipoCuerpo, int type);
        //Destructor de clase Cuerpo.
        ~Cuerpo();
        //Posiciona el cuerpo en las posiciones indicadas.
        void posicionamiento(float x_entrada,float y_entrada);
        //Asigna la textura indicada al cuerpo.
        std::vector<int> texturizar(std::string entrada, int sizeWidth, int sizeHeight);
        //Se obtiene el rectángulo de colisión del cuerpo.
        std::vector<float> getBounds();
        //Se actualizan los valores del cuerpo.
        //En caso de poseer una animación, esta también se actualiza.
        void update(float deltaTime);
        //Situa el origen del cuerpo en esa posición.
        void Origen(float, float);
        //Se escala el cuerpo con los parámetros dados.
        void Scalar(float, float);
        //Se renderiza el cuerpo en la ventana.
        void render(float porcentaje);
        //Se renderiza el cuerpo en la ventana.
        void render();
        //Se mueve el cuerpo sumando su posición con los parámetros de entrada.
        void moverse(float x, float y);
        //Se añade una animación con tanto tiempo de fase.
        void addAnimacion(float timeAnimacion);
        //Se cambia de animación.
        void setSpriteAnimacion(int entrada);
        //Se cambia el tiempo de la animación.
        void setTimeAnimacion(float entrada);
        //Se cambia el tamaño de la animación.
        void setSize(float sizeX, float sizeY);
        //Se cambia el tipo del cuerpo.
        void setTipo(int x){class_tipo+=x;}
        //Comprueba si el cuerpo colisiona con otro.
        bool colisiona(Cuerpo * entrada);
        //Rota el cuerpo.
        void rotar(float angulo);
        //Se recorta la textura con los valores de entrada.
        void recorte(int x , int y);
        //Se obtiene la posición actual del cuerpo.
        std::vector<float> getPosicion();
        //Se obtiene e tamaño del cuerpo.
        std::vector<float>getSize();
        //Se obtiene el rectángulo de colisión del cuerpo.
        Rectangulo * getGlobalBounds();
        //Se obtiene el tipo del cuerpo.
        int getTipo();
        //Se obtiene el origen en Y.
        float getOriginY(){return body->getOrigin().y;};
        //Se obtiene el origen en X.
        int getPosicionX(){return animacion->getPosicionX();};
        //Se obtiene el tiempo de animación.
        float getTimeAnimacion(){return animacion->getTimeAnimation();};
        //Se posiciona el cuerpo en un sitio (evitando efecto de interpolación).
        void posicionamientoFijo(float x_entrada,float y_entrada);
};

#endif
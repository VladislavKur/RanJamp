#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemigo.h"

#ifndef MURCIELAGO_H
#define MURCIELAGO_H

class Murcielago : public Enemigo{
    private:
        int distanciaAtaque;
        int altura;
        int direccion = 0;
        float alturaInicial;
        
    public:
        //pasa a la clase padre su posicion en ambos ejes, junto con el tipo de cuerpo,
        //en este caso RectangleShape, el tamanyo del cuerpo, el fichero donde esta la textura
        //y el tamanyo de la escala. Ademas inicializa sus variables de caso a los valores predeterminados:
        //como la velocidad, altura de descenso, distancia de ataque y un bool para saber si ha colisionado con el jugador
        Murcielago(float x, float y);

        //Calcula la diferencia en los ejes x e y entre la posicion del enemigo y del jugador, sin tener en cuenta
        //el signo y por tanto en que lado se encuentra. Segun esa diferencia cambia a un modo u otro:
        //Modo 0: si esta mas lejos de su radio de ataque, entonces no se mueve
        //Modo 1: si esta en el radio de ataque entonces se mueve hacia el diagonalmente
        //Modo 2: si la diferencia entre la altura de ambos es minima (en este caso <= 3) entonces se mueve hacia el recto
        //Por ultimo comprueba si hay colisiones entre el cuerpo del jugador y del enemigo
        void update(Player* player, float delta);
        //Llama al render de Cuerpo donde se vuelve a posicionar y se dibuja
        void render( float porcentaje);
        //actualiza los FloatRect que detectan las colisiones (arriba, abajo, derecha, izquierda)
        void updateHitbox();
          
        bool haPegado; 
};

#endif

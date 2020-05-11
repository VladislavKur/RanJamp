#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemigo.h"
//#include "../Collider/Collider.h"

#ifndef PAJARO_H
#define PAJARO_H


class Pajaro : public Enemigo{
    private:       
        int direccion;
        int alturaMax = 100;
        int alturaMaxRelativa;
        int alturaMinRelativa;
        float alturaActual;
        bool haPegado;

    public:
        //pasa a la clase padre su posicion en ambos ejes, junto con el tipo de cuerpo,
        //en este caso RectangleShape, el tamanyo del cuerpo, el fichero donde esta la textura
        //y el tamanyo de la escala. Ademas inicializa sus variables de caso a los valores predeterminados:
        //la altura actual (de la cual parte), y la altura max y min relativa, en funcion su altura actual y la 
        //altura tope que se haya establecido. Tambien se incializa su velocidad, siempre la misma
        Pajaro(float x, float y);
        ~Pajaro();
        
        //El enemigo realiza un movimento de arriba a abajo avanzando hacia delante.
        //Tiene dos variables que determinan la altura maxima y minima hasta la que se desplaza
        //en funcion de ello se actualiza la direccion (1 (positivo eje y) => sube // -1 (negativo eje y) => baja)
        //Compruba si hay colisiones entre el cuerpo del jugador y el suyo, si es asi pone a true la varibel de haPegado
        //y actualiza el updatehitbox
        void update(Player* player, float delta);
         //Llama al render de Cuerpo donde se vuelve a posicionar y se dibuja
        void render( float porcentaje);
        //actualiza los FloatRect que detectan las colisiones (arriba, abajo, derecha, izquierda)
        void updateHitbox();
};

#endif

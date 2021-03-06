#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemigo.h"
#include "../Bullet/bullet.h"

#ifndef CENTINELA_H
#define CENTINELA_H

class Centinela : public Enemigo{
    private:
        int distanciaAtaque;
        int distanciaDisparo;
        int tipo;
        bool direccion;
        bool shoot;
        float shootTime;

    public:
        //pasa a la clase padre su posicion en ambos ejes, junto con el tipo de cuerpo,
        //en este caso el enum tipo es RectangleShape, el tamanyo del cuerpo, el fichero donde esta la textura
        //y el tamanyo de la escala. Ademas inicializa sus variables de caso a los valores predeterminados
        Centinela(float x, float y, int type);
        //Calcula la diferencia en el eje x entre la posicion del enemigo y del jugador, sin tener en cuenta
        //el signo y por tanto en que lado se encuentra. Segun esa diferencia cambia a un modo u otro.
        //Ademas hay dos tipos, el tipo 1 no se mueve tan solo dispara(modo 0 y modo 2),
        //el otro tipo tiene los tres modos
        //Los modos son los siguientes:
        //Modo 0: si esta mas lejos de su radio de ataque o disparo, entonces ni se mueve ni hace nada
        //Modo 1: si esta en el radio de ataque entonces se mueve hacia el
        //Modo 2: si esta en el radio de disparo entonces dispara en su direccion
        void update(Player* player, float delta);
        //Llama al render de Cuerpo donde se vuelve a posicionar y se dibuja,
        //ademas como llama al render de cuerpo tambien se renderiza la animacion.
        void render( float porcentaje);   
        //Si la variable shoot es cierta entonces devuelve una bala segun la posicion del enemigo, la direccion
        //es decir, izquierda/derecha o arriba/abajo, y un entero para saber si el lanzamiento es horizontal o vertical
        Bullet* disparar(); 
        //devuelve si ha disparado o no
        bool getShoot();
};

#endif

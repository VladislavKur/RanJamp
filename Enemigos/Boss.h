#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemigo.h"
#include "../Bullet/bullet.h"
#include "../Rectangulo/Rectangulo.h"

#ifndef BOSS_H
#define BOSS_H

class Boss : public Enemigo{
    private:
        //rango para golpear
        int distanciaAtaque;
        //rango para disparar 
        int distanciaDisparo;
        bool direccion;
        bool shoot;
        float shootTime;
        //sirve para saber si el enemigo puede golpear, es decir, si se encuentra en el frame de golpe entonces es true
        bool haPegado;
        //rectangulo de colision para la mano con la que golpea
        //Rectangulo * mano; 

    public:
        //pasa a la clase padre su posicion en ambos ejes, junto con el tipo de cuerpo, que en este caso es 1,
        //es decir, un RectangleShape, el tamanyo del cuerpo, el fichero donde esta la textura
        //y el tamanyo de la escala. Se crea la animacion y se asigna las vidas, y se inicializan los rangos, tanto
        //el de ataque(golpe) como el de disparo. Por ultimo se inicaliza haPegado a false, esta variable comprueba
        Boss(float x, float y);
        //Calcula la diferencia en el eje x entre la posicion del enemigo y del jugador, sin tener en cuenta
        //el signo y por tanto en que lado se encuentra. Segun esa diferencia cambia a un modo u otro.
        //setAnimacion establece la fila de la animacion que tiene que realizar.
        //Los modos son los siguientes:
        //Modo 0: no se mueve, espera
        //Modo 1: entra en el rango de disparo y comienza a lanzar balas
        //Modo 2: esta lo suficientemente cerca para intentar golpearle si colisiona con el entonces quita 2 vidas.
        void update(Player* player, float delta);
        //Llama al render de Cuerpo donde se vuelve a posicionar y se dibuja
        void render( float porcentaje);   
        //Si la variable shoot es cierta entonces devuelve una bala segun la posicion del enemigo, la direccion
        //es decir, izquierda/derecha o arriba/abajo, y un entero para saber si el lanzamiento es horizontal o vertical
        Bullet* disparar(); 
        //devuelve si ha disparado o no
        bool getShoot();
        //devuelve si ha pegado o no
        bool getPegado();
        //se actualiza el booleano de haPegado
        void setPegado(bool p);
};

#endif

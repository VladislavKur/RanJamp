#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "enemigo.h"
#include "../Bullet/bullet.h"

#ifndef NUBE_H
#define NUBE_H

using namespace std;

class Nube : public Enemigo{
    private:
        int distanciaAtaque;
        int direccion = 0;
        float shootTime;
        bool shoot;
        
    public:
        //Pasa a la clase padre su posicion en ambos ejes, junto con el tipo de cuerpo,
        //en este caso RectangleShape, el tamanyo del cuerpo, el fichero donde esta la textura
        //y el tamanyo de la escala. Ademas inicializa sus variables de caso a los valores predeterminados:
        //inicializa la distancia a la que atacara, el modo y su velocidad(no cambia), ademas del tiempo de disparo        
        Nube(float x, float y);
        ~Nube();
        
        //Calcula la diferencia en el eje x entre la posicion del enemigo y del jugador, sin tener en cuenta
        //el signo y por tanto en que lado se encuentra. Segun esa diferencia cambia a un modo u otro:
        //Modo 0: si esta mas lejos de su radio de ataque, entonces no se mueve
        //Modo 1: si esta en el radio de ataque entonces se mueve hacia el hasta llegar a la misma altura
        //Modo 2: si estoy a su altura mas o menos entonces le sigo y ademas disparo verticalmente desde arriba hacia el jugador
        //void update(Player* player, float deltaTime);
        void update(Player* player, float deltaTime);
        //Llama al render de Cuerpo donde se vuelve a posicionar y se dibuja
        void render( float porcentaje);   
        //Si la variable shoot es cierta entonces devuelve una bala segun la posicion del enemigo, la direccion
        //es decir, izquierda/derecha o arriba/abajo, y un entero para saber si el lanzamiento es horizontal o vertical
        Bullet* disparar(); 
        //devuelve si ha disparado o no
        bool getShoot();
};

#endif

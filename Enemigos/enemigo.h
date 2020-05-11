#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Rectangulo/Rectangulo.h"
#include "../Motor/Motor.h"
#include "../Player/Player.h"
#include "../Cuerpo/Cuerpo.h"

#ifndef ENEMIGO_H
#define ENEMIGO_H

class Enemigo{
    public:
        ~Enemigo();
        //este metodo es heredado por cada enemigo, y cada uno de ellos lo implementa a su manera
        virtual void update(Player* player, float deltaTime){}; ///player
        //se hereda, llama al render de cuerpo
        virtual void render(float porcentaje){};
        //se hereda, acualiza los rectangulos de las colisiones
        virtual void updateHitbox(){}
        bool muerto;
        //devuelve el cuerpo del enemigo
        Cuerpo* getCuerpo();
        //llama a la funcion de colisiona de cuerpo y comprueba sin ambos Cuerpos intersectan
        bool comprobarColision(Cuerpo* cuerpo);

        //devuelve el numero de vidas
        int getVidas();
        //actualiza el numero de vidas del enemigo al que recibe por parametro, y actualiza el bool de muerto si la vida es 0 o menor
        bool setVidas(int v);
        //quita una sola vida
        void restarVida(int i);
    protected:
        //se establece por defecto el modo de cada enemigo a 0(esta quieto) y se crea el cuerpo se pasa la posicion inicial, 
        //las dimensiones del sprite dentro de la textura, y se crea su animacion asociada. Ademas se crean 4 rectangulos, 
        //para detectar las colisiones, inicialmente a 0. 
        Enemigo(float x, float y, int sizeWidth, int sizeHeight, 
            std::string fichero, float escala);
        //se llama al metodo del cuerpo para establecer su posicon fija
        void actualizarPosicion(float x, float y);

        Cuerpo* body;
        float velocidad;
        int modo;
        bool colision;

        //colisiones 
        Rectangulo * coliAbajo;
        Rectangulo * coliArriba;
        Rectangulo * coliIzquierda;
        Rectangulo * coliDerecha;
        int vida;
       
};


#endif
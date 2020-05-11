#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Player/Player.h"
#include "../Enemigos/enemigo.h"
#include "../Enemigos/centinela.h"
#include "../Bullet/bullet.h"
#include "../Mundo/Mundo.h"
#include "../Objeto/Objeto.h"
#include "../Texto/texto.h"
#include "../Hud/hud.h"
#include "menu.h"
#include "../Rectangulo/Rectangulo.h"

#ifndef TUTORIAL_H
#define TUTORIAL_H

class Tutorial : public menu{
    private:
        Mundo * mundo;
        Player *jugador;
        Enemigo * enemigo;
        Objeto** objetos= NULL;
        Bullet* bulletPlayer[maxBullets];
        Bullet* bulletEnemies[maxBullets];

        int numObjetos;
        float timerObstaculos;
    public:
        Tutorial();
        ~Tutorial();
        void update(float deltaTime);
        void render(float porcentaje);

        void crearObjetos();
        void crearEnemigos();
        void disparar(float d);
        void destruirObjetos(Objeto*);
        void matarEnemigo();
        void terminar();

        void colisionBulletJugador();
        void colisionBulletEnemigo();
        void colisionPlayerMundo(float deltatime);
        void colisionPlayerObstaculos(float deltaTime);
        void colisionBulletMundo();
        void colisionMeleeEnemigo();

        void mostrarTexto();
        void cambiarTexto(const Font &f , int i, Color c, string s , Vector2f v, int posx , int posy);

        //static Juego *instance();

        sf::View view;
        Text* texto;
        //Font* font;
        static sf::Font* font;
        Cuerpo* dialogo;
        //m: moviendo, s: saltar, b: moneda, l:llave, d:disparo, ss:doble salto, t:fin
        char estado; 
        string titulo;
        string mensaje;
        
};



#endif
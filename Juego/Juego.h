#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Player/Player.h"
#include "../Enemigos/enemigo.h"
#include "../Enemigos/murcielago.h"
#include "../Enemigos/centinela.h"
#include "../Enemigos/reptante.h"
#include "../Bullet/bullet.h"
#include "../Mapa/mapa.h"
#include "../Objeto/Objeto.h"

#ifndef JUEGO_H
#define JUEGO_H

    class Juego{

        private:
            Player *jugador;
            Enemigo** enemies = NULL;
            Bullet* bulletPlayer[maxBullets];
            Bullet* bulletEnemies = NULL;
            static Juego* pinstance;
            int numEmenigos; 
        protected:
            Juego();

        public:
            static Juego *instance();
            void update(float deltaTime);
            void render(float porcentaje);            
            void colisionPlayerMundo(float deltaTime);
            void colisionBulletMundo(float deltaTime);

            void crearObjetos();
            void crearEnemigos();
            Player *getJugador(){return jugador;};
            void matarEnemigo(Enemigo* enem);
            void disparar(float deltaTime);
            void limpiarBalas();

            sf::View view;
    };

#endif
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Player/Player.h"
#include "../Enemigos/enemigo.h"
#include "../Bullet/bullet.h"
#include "../Mapa/mapa.h"

#ifndef JUEGO_H
#define JUEGO_H

    class Juego{

        private:
            Player jugador;
            Enemigo* enemies = NULL;
            Bullet* bulletPlayer = NULL;
            Bullet* bulletEnemies = NULL;
            static Juego* pinstance;

        protected:
            Juego();

        public:
            static Juego *instance();
            void update(float deltaTime);
            void render(float porcentaje);            
            void colisionPlayerMundo(float deltaTime);
            void crearObjetos();
    };

#endif
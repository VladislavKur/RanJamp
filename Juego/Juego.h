#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Player/Player.h"
#include "../Enemigos/enemigo.h"
#include "../Enemigos/murcielago.h"
#include "../Enemigos/centinela.h"
#include "../Enemigos/nube.h"
#include "../Enemigos/pajaro.h"
#include "../Bullet/bullet.h"
#include "../Mundo/Mundo.h"
#include "../Objeto/Objeto.h"
#include "../Texto/texto.h"
#include "../Musica/musica.h"
#include "../Hud/hud.h"
#include "../Rectagulo/Rectangulo.h"

#ifndef JUEGO_H
#define JUEGO_H

    class Juego{

        private:
            Player *jugador;
            Enemigo ** enemies = NULL;
            Objeto** objetos= NULL;
            Bullet* bulletPlayer[maxBullets];
            Bullet* bulletEnemies[maxBullets];
            Bullet* bulletNube[maxBullets];
            static Juego* pinstance;
            int numEmenigos; 
            //texto * t;
            musica * so;
            int numObjetos;
            Mundo * mundo;
            int nivel;
            string * niveles;
        protected:
            Juego();

        public:
            static Juego *instance();
            void update(float deltaTime);
            void render(float porcentaje);            

            void colisionBulletJugador();
            void colisionBulletEnemigo();
            void colisionPlayerMundo(float deltatime);
            void colisionBulletMundo();
            
            void cargarMusica();
            void crearObjetos();
            void destruirObjetos(Objeto*);
            void crearEnemigos();
            Player *getJugador(){return jugador;};
            void matarEnemigo(Enemigo* enem);
            void matarJugador();
            void disparar(float deltaTime);
            void dispararEnemigo(float deltaTime, float x, float y, bool direccion);
            void colisionEnemigoPlayer(Enemigo* enem, float deltaTime);
            void comprobarPasarNivel();
            sf::View view;

            void nextLevel();
            void inicializarNiveles();
    };

#endif
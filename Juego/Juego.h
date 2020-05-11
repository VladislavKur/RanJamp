#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Player/Player.h"
#include "../Enemigos/enemigo.h"
#include "../Enemigos/murcielago.h"
#include "../Enemigos/centinela.h"
#include "../Enemigos/nube.h"
#include "../Enemigos/pajaro.h"
#include "../Enemigos/Boss.h"
#include "../Bullet/bullet.h"
#include "../Mundo/Mundo.h"
#include "../Objeto/Objeto.h"
#include "../Texto/texto.h"
#include "../Musica/musica.h"
#include "../Hud/hud.h"
#include "../Rectangulo/Rectangulo.h"
#include "Manejador.h"

#ifndef JUEGO_H
#define JUEGO_H
   
    class Juego : public Estado{

        private:
            Player *jugador;
            Enemigo ** enemies = NULL;
            Objeto** objetos= NULL;
            Bullet* bulletPlayer[maxBullets];
            Bullet* bulletEnemies[maxBullets];
            Bullet* bulletNube[maxBullets];
            Bullet* bulletBoss[maxBullets];
            static Juego* pinstance;
            int numEmenigos; 
            musica ** so;
            int numObjetos;
            Mundo * mundo;
            int nivel;
            string * niveles;
            int maxniveles = 12;
            //obstaculos 
            float timerObstaculos;
            int transparenciaRoja;
            int angulo = 0;
            Cuerpo *portal;
            std::string nivelactual;
        protected:
            Juego();
            ~Juego();
        public:
            static Juego *instance();
            void update(float deltaTime);
            void render(float porcentaje);            

            void colisionBulletJugador();
            void colisionBulletEnemigo();
            void colisionPlayerMundo(float deltatime);
            void colisionPlayerObstaculos(float deltaTime);
            void colisionBulletMundo();
            void colisionMeleeEnemigo();
            
            void iniciarPantallaRoja();
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

            void pausa();
            void nivelSeleccionado(std::string);
            std::string nivelJuego(){return nivelactual;}
            
            void setVolumen(int i ,float x);
            float getVolumen(int i);
            void pausarMusica(int i);
            void reproducirMusica(int i);
            void ponerBucleMusica(int i);
            

            sf::View view;

            void nextLevel(int i);
            void inicializarNiveles();
    };

#endif
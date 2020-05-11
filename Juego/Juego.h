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
            Objeto** objetos= NULL; //power-ups y armas
            Bullet* bulletPlayer[maxBullets]; //balas lanzadas por el jugador
            Bullet* bulletEnemies[maxBullets]; //balas lanzadas por las centinelas
            Bullet* bulletNube[maxBullets]; //balas lanzadas por las nubes
            Bullet* bulletBoss[maxBullets]; //balas lanzadas por el jefe final
            static Juego* pinstance;
            int numEmenigos; //cantidad de enemigos en el mapa
            musica ** so;
            int numObjetos; //cantidad de objetos (powerups, armas)
            Mundo * mundo;
            int nivel; //nivel actual
            string * niveles;
            int maxniveles = 17; //numero maximo de niveles del juego
            //obstaculos 
            float timerObstaculos; //tiempo de retardo entre dos daños provocados por pinchos
            int angulo = 0; //angulo de movimiento rotatorio del portal
            Cuerpo *portal;
            std::string nivelactual; //el archivo
        protected:
            Juego();
            ~Juego();
        public:
            static Juego *instance();

            void update(float deltaTime);
            void render(float porcentaje);            
            
            //funciones que se llaman en el update y administran las colisiones
            void colisionBulletJugador();
            void colisionBulletEnemigo();
            void colisionPlayerMundo(float deltatime);
            void colisionPlayerObstaculos(float deltaTime);
            void colisionBulletMundo();
            void colisionMeleeEnemigo();
            void colisionEnemigoPlayer(Enemigo* enem, float deltaTime);
            
            //cargar los archivos de sonido
            void cargarMusica();
            //crear los objetos recogibles
            void crearObjetos();
            //eliminar el objeto
            void destruirObjetos(Objeto*);
            //crear los enemigos
            void crearEnemigos();
            //
            Player *getJugador(){return jugador;};
            //destruir al enemigo
            void matarEnemigo(Enemigo* enem);
            //destruir al jugador
            void matarJugador();
            //el mago lanza una bola de fuego
            void disparar(float deltaTime);
            //comprobar la colision del player con el fin de nivel y pasar al siguiente si procede
            void comprobarPasarNivel();
            //abrir el menu de pausa
            void pausa();
            //ir al nivel elegido desde el menu de niveles
            void nivelSeleccionado(std::string);
            //nombre del archivo .tmx
            std::string nivelJuego(){return nivelactual;}
            
            //poner el volumen del canal i al x%
            void setVolumen(int i ,float x);
            //devolver el volumen del canal i
            float getVolumen(int i);
            //detener la reproduccion de sonido del canal i
            void pausarMusica(int i);
            //reproducir el sonido del canal i
            void reproducirMusica(int i);
            //activar el bucle del canal i
            void ponerBucleMusica(int i);


            sf::View view;

            //ir al siguiente nivel
            void nextLevel(int i);
            //definir los niveles (sus nombres de archivo)
            void inicializarNiveles();
    };

#endif
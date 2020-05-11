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
        //carga el mapa del tutorial con todos sus objetos, jugador y enemigos
        Tutorial();
        ~Tutorial();
        //
        void update(float deltaTime);
        void render(float porcentaje);

        void crearObjetos();
        //en este caso crea un centinela que dispara
        void crearEnemigos();
        void disparar();
        void destruirObjetos(Objeto*);
        void matarEnemigo();
        void terminar();

        //Es igual que en juego, se comprueba si intersecta el cuerpo de la bala con el enemigo
        //si es asi le resta vida
        void colisionBulletEnemigo();
        void colisionPlayerMundo(float deltatime);
        //hace desaparecer las balas cuando colisionan
        void colisionBulletMundo();
        void colisionMeleeEnemigo();

        //recibe la fuente, el indice del texto, el color de la letra, el contenido del texto, su tamano y la posicion
        //actualiza la posicion con respecto a la del jugador, por un lado el texto y por otro
        //esta el fondo que siempre es el mismo y que tambien se actualiza con respecto del jugador
        void cambiarTexto(const Font &f , int i, Color c, string s , Vector2f v, int posx , int posy);

        sf::View view;
        //array con el titulo y el mensaje del cuadro de dialogo
        Text* texto;
        //Font* font;
        static sf::Font* font;
        //corresponde al fondo del cuadro de dialogo
        Cuerpo* dialogo;
        //el estado indica en que texto se encuentra y va cambiando por un orden establecido
        //1: mmovimiento izquierda, derecha 2.Saltar 3.Recoger moneda 4.recoger power up 5.disparar 6.terminar 
        //m: moviendo, s: saltar, b: moneda, r:powerup, d:disparo, t:fin
        char estado; 
        //corresponde al contendido texto que se asigna para el cuadro de dialogo se actualiza segun el estado
        string titulo;
        //corresponde al condenido de la explicacion del cuadro de dialogo se actualiza segun el estado
        string mensaje;
        
};



#endif
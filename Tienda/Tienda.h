#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//ANDRES : ESTE CODIGO ES PRACTICAMENTE IGUAL AL DE MI PENGO ASI QUE SI LO UTILIZAIS CAMBIARLOOO!!!!!!

#include "../Hud/hud.h"
#include "../Juego/Manejador.h"
#include "../Juego/Juego.h"
#include "../Motor/Motor.h"
#include "../Cuerpo/Cuerpo.h"

using namespace  sf;
using namespace std;

#define num_items 3
class Tienda : public Estado{
    public: 
        static Tienda* instance();

        // PINTAR EL MENU
        void render(float num); 

        // MOVERSE HACIA ARRIBA EN EL MENU 
        void moveUp(); 

        // MOVERSE HACIA ABAJO EN EL MENU 
        void moveDown();

        // RECOGER INPUT DE LAS TECLAS
        void update(float deltaTime);

        // DEVULVE LA OPCCION SELECCIONADA 
        int getItemPressed(); 
        
        //CAMBIA EL COLOR, TEXTO, Y POSICION DEL TEXTO[i] 
        void cambiarTexto(int i,  String s, float posx , float posy); 
    
    protected:
        Tienda(int i, int max); 
        // DESTRUCTOR
        ~Tienda();     
        
    private: 
    // CONTRUCTOR , PASANDOLE EL ALTO Y EL ANCHO
        int numOpciones;
        static Tienda* p_instance;
        int selectedItem = 0; 
        Cuerpo ** sprites;
        Font * font; 
        Text * texto;
        int maxTienda;
        int itemSeleccionado;
        float cooldown_mov;
        Textura *t; 
        Bloque * b;
};
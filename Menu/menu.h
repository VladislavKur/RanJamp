#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//ANDRES : ESTE CODIGO ES PRACTICAMENTE IGUAL AL DE MI PENGO ASI QUE SI LO UTILIZAIS CAMBIARLOOO!!!!!!

#include "../Juego/Juego.h"
#include "../Juego/Manejador.h"

using namespace  sf;
using namespace std;

#define num_items 3
class menu : public Estado{
    public: 
        //static menu* instancia();

        menu( Font fuente, int max); 
        // DESTRUCTOR
        ~menu(); 
        
        // PINTAR EL MENU
        void render(float num); 

        // MOVERSE HACIA ARRIBA EN EL MENU 
        void moveUp(); 

        // MOVERSE HACIA ABAJO EN EL MENU 
        void moveDown();

        // RECOGER INPUT DE LAS TECLAS
        virtual void update(float deltaTime){};

        // DEVULVE LA OPCCION SELECCIONADA 
        int getItemPressed(); 
        
        //CAMBIA EL COLOR, TEXTO, Y POSICION DEL TEXTO[i] 
        void cambiarTexto(int i, Color c, String s, float posx , float posy); 
        
    protected: 
    // CONTRUCTOR , PASANDOLE EL ALTO Y EL ANCHO
        int numOpciones;
        //static menu* p_instancia;
        int selectedItem; 
        Font font; 
        Text *texto;
        float cooldown_mov;
};
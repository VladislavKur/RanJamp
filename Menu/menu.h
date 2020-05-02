#include <SFML/Graphics.hpp>
#include <iostream>
//ANDRES : ESTE CODIGO ES PRACTICAMENTE IGUAL AL DE MI PENGO ASI QUE SI LO UTILIZAIS CAMBIARLOOO!!!!!!
#include "../Motor/Motor.h"

using namespace  sf;
using namespace std;

#define num_items 3
class menu{
    public: 
        // CONTRUCTOR , PASANDOLE EL ALTO Y EL ANCHO
        menu( Font fuente, int max); 

        // DESTRUCTRO 
        ~menu(); 
        
        // PINTAR EL MENU
        void render(); 

        // MOVERSE HACIA ARRIBA EN EL MENU 
        void moveUp(); 

        // MOVERSE HACIA ABAJO EN EL MENU 
        void moveDown();

        // DEVULVE LA OPCCION SELECCIONADA 
        int getItemPressed(); 
        
        //CAMBIA EL COLOR, TEXTO, Y POSICION DEL TEXTO[i] 
        void cambiarTexto(int i, Color c, String s, float posx , float posy); 
        
    private: 
        int numOpciones;
        int selectedItem; 
        Font font; 
        Text *texto;
};
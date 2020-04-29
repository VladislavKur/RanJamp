#include <SFML/Graphics.hpp>
#include <iostream>
//ANDRES : ESTE CODIGO ES PRACTICAMENTE IGUAL AL DE MI PENGO ASI QUE SI LO UTILIZAIS CAMBIARLOOO!!!!!!
#include "../Motor/Motor.h"

using namespace  sf;
using namespace std;

#define num_items 3
class menu{
    public: 
        menu( Font fuente, int max);
        ~menu();
        void render();
        void moveUp();
        void moveDown();
        int getItemPressed();
        void cambiarTexto(int i, Color c, String s, float posx , float posy);
    private: 
        int numOpciones;
        int selectedItem; 
        Font font; 
        Text *texto;
};
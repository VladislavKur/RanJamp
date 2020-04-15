#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Motor/Motor.h"

using namespace sf;
using namespace std; 

class hud{
    public: 
        static hud* instance(); 
        void setMarcador(int posX , int posY , int vidasPengo);// SE ACTUALIZAN LOS VALORES DEL HUD 
        //CAMBIA LOS VALORES Y POSICION DEL ARRAY DE TEXTO 
        void cambiarTexto(const Font &font , int i, Color c, string s , Vector2f v, int posx , int posy);
        void sumarPuntos(int suma){ puntos += suma;};
        void render();
    protected: 
        hud(int posPengo, int vidasPengo, int max);
    private:
        static hud* p_instancia; 
        RectangleShape * r;
        Font * font; 
        Text * texto;
        Sprite * sVidas;
        Texture * tVidas; 
        Sprite * sDobleSalto; 
        Texture * tDobleSalto; 
        Sprite * sVelocidad; 
        Texture * tVelocidad; 
        Sprite * sArma; 
        Texture * tArma; 
        
        Clock clockGlobal;

        int puntos = 500; 
};
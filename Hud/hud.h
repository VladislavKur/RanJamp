#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Motor/Motor.h"

using namespace sf;
using namespace std; 

class hud{
    public: 
        static hud* instance(); 
        ~hud();
        // SE ACTUALIZAN LOS VALORES DEL HUD
        void setMarcador(int posX , int posY , int vidasPengo,int monedas, vector<int> llaves);
       
        //CAMBIA LOS VALORES Y POSICION DEL ARRAY DE TEXTO 
        void cambiarTexto(const Font &font , int i, Color c, string s , Vector2f v, int posx , int posy);
        
        // SUMA LA CANTIDAD PASADA POR PARAMETRO A LA VARIABLE PUNTOS
        void sumarPuntos(int suma){ puntos += suma;}; 
        
        // RENDERIZA EL HUD 
        void render(); 

    protected: 
        hud(int posPengo, int vidasPengo, int max);
        
    private:
        static hud* p_instancia; 
        //RectangleShape * r;
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
        Texture * tMonedas;
        Sprite * sMonedas;
        Texture * tLlaves;
        Sprite * sLlaves;
        // Texture * tTiempo;
        // Sprite * sTiempo;
        // Texture * tPuntos;
        // Sprite * sPuntos;
        
        Clock clockGlobal;

        int puntos = 500; 
};
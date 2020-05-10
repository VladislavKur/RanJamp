#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Motor/Motor.h"
#include "../Cuerpo/Cuerpo.h"
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

        int getMonedero(){return monedero;}
        void setMonedero(int x){monedero -=x;}
        int getVidas(){return vidas;}
        void sumarVidas(){vidas++;}
        bool getDoblesalto(){return doblesalto;}
        void setDobleSalto(bool x){doblesalto = x;}
        bool getVelocidad(){return velocidad;}
        void setVelocidad(bool x){velocidad = x;}
        bool getSlow(){return slow;}
        void setSlow(bool x){slow =x;}
    protected: 
        hud(int posPengo, int vidasPengo, int max);
        
    private:
        static hud* p_instancia; 
        Font * font; 
        Text * texto;
        Sprite * sPuntos;
        Cuerpo ** sprites;
        Clock clockGlobal;
        int monedero = 10;
        int puntos = 0; 
        int vidas = 0; 
        bool doblesalto = false;
        bool velocidad = false;
        bool slow = false; 
};
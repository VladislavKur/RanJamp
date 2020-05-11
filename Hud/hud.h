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
        void setMarcador(int posX , int posY );
       
        //CAMBIA LOS VALORES Y POSICION DEL ARRAY DE TEXTO 
        void cambiarTexto(const Font &font , int i, Color c, string s , Vector2f v, int posx , int posy);
        
        // SUMA LA CANTIDAD PASADA POR PARAMETRO A LA VARIABLE PUNTOS
        void sumarPuntos(int suma){ puntos += suma;}; 
        
        // RENDERIZA EL HUD 
        void render(); 
        void renderMonedas();
        
        int getMonedero(){return monedero;}
        void setMonedero(int x){monedero -=x;}
        void sumarMonedas(){monedero++;}
        int getVidas(){return vidas;}
        void sumarVidas(){vidas++;}
        bool restarVidas();
        void restablecerVidas(){vidas = 5;}
        void quitarVidas(){vidas = 0;}
        bool getDoblesalto(){return doblesalto;}
        void setDobleSalto(bool x){doblesalto = x;}
        bool getVelocidad(){return velocidad;}
        void setVelocidad(bool x){velocidad = x;}
        int getIVelocidad(){return i_velocidad;}
        void setIVelocidad(int x){i_velocidad = x;}
        bool getSlow(){return slow;}
        void setSlow(bool x){slow =x;}
        bool getGodMode(){return godMode;}
        void setGodMode();
        int getPuntos(){return puntos;}
        void reiniciarTiempo();
        void setArma(int pos, int mejora);
        vector<int> getArma(){return arma;}
    protected: 
        hud(int posPengo, int vidasPengo, int max);
        
    private:
        static hud* p_instancia; 
        Font * font; 
        Text * texto;
        Sprite * sPuntos;
        Cuerpo ** sprites;
        Clock clockGlobal;
        int monedero;
        int puntos; 
        int vidas; 
        bool doblesalto;
        bool velocidad;
        bool slow; 
        int i_velocidad;
        bool godMode;
        vector<int> arma;
};
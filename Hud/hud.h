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

        //RENDERIZA LAS MONEDAS DE HUD
        void renderMonedas();
        
        //DEVUELVE EL VALOR DE LAS MONEDAS DE JUGADOR
        int getMonedero(){return monedero;}

        //RESTA EL VALOR DE MONEDERO PASADO POR PARAMETRO
        void setMonedero(int x){monedero -=x;}
        
        //SUMA UNA MONEDA AL MONEDERO
        void sumarMonedas(){monedero++;}
        
        //DEVUELVE LAS VIDAS DEL JUGADOR
        int getVidas(){return vidas;}
        
        //SUMAR UNO A VIDAS
        void sumarVidas(){vidas++;}

        //RESTA UNO A VIDAS Y SI ESTA A CERO DEVUELVE FALSE
        bool restarVidas();

        //VUELVE A  PONER LAS VIDAS DEL JUGADOR A 5
        void restablecerVidas(){vidas = 5;}
        
        //QUITA TODAS LA VIDAS DEL JUGADOR 
        void quitarVidas(){vidas = 0;}

        //DEVULVE EL VALOR DE DOBLE SALTO
        bool getDoblesalto(){return doblesalto;}

        //CAMBIA EL VALRO DEL DOBLE SALTO POR EL PASADO POR PARAMETRO
        void setDobleSalto(bool x){doblesalto = x;}

        //DEVULVE LA VELOCIDAD
        bool getVelocidad(){return velocidad;}
        
        //CAMBIA EL VALOR DE LA VELOCIDAD POR EL PASADO POR PARAMETRO
        void setVelocidad(bool x){velocidad = x;}
        
        //DEVUELVE EL VALOR ENTERO DE LA VELOCIDAD 
        int getIVelocidad(){return i_velocidad;}

        //CAMBIA EL VALOR DE LA VELOCIDAD POR EL PASADO POR PARAMETRO 
        void setIVelocidad(int x){i_velocidad = x;}

        //DEVUELVE EL VALOR DE SLOW
        bool getSlow(){return slow;}

        //CAMBIA EL VALOR DE SLOW POR QUE PASADO POR PARAMETRO
        void setSlow(bool x){slow =x;}

        //DEVUELVE EL VALOR DE GODMODE 
        bool getGodMode(){return godMode;}
        
        //CAMBIA EL VALOR DE GODMODE Y LO PONE AL CONTRARIO DEL QUE ESTABA 
        void setGodMode();

        //DEVUELVE EL VALOR DEL TIEMPO DEL JUEGO
        int getTiempo(){return clockGlobal.getElapsedTime().asSeconds();};
        
        //DEVUELVE EL VALOR DE LOS PUNTOS 
        int getPuntos(){return puntos;}

        //REINICA EL TIEMPO A 0 
        void reiniciarTiempo();

        //CAMBIA DE ARMA, MEJORANDOLO CON EL VALOR PASADO POR PARAMETRO
        void setArma(int pos, int mejora);

        //DEVUELVE LAS ARMAS DEL JUGADOR
        vector<int> getArma(){return arma;}

    protected: 

        //CONTRUCTOR AL CUAL SE LE PASAN LA POSICION DEL JUGADOR  EN Y SUS VIDAS Y EL MAXIMO
        hud(int pos, int vidasPengo, int max);
        
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
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//ANDRES : ESTE CODIGO ES PRACTICAMENTE IGUAL AL DE MI PENGO ASI QUE SI LO UTILIZAIS CAMBIARLOOO!!!!!!

#include "menu.h"
//#include "menu_inicial.h"
#include "../Juego/Juego.h"
class Juego;
class menu_controles : public menu {
    public:

        static menu_controles* instance();
       
        
        void update(float deltaTime);
        

    protected:
        menu_controles(sf::Font fuente, int max);
    private: 
        static sf::Font* fuente;
        static menu_controles* p_instance;
        
};
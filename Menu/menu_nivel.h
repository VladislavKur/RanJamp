#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//ANDRES : ESTE CODIGO ES PRACTICAMENTE IGUAL AL DE MI PENGO ASI QUE SI LO UTILIZAIS CAMBIARLOOO!!!!!!

#include "menu.h"
//#include "menu_inicial.h"
#include "../Juego/Juego.h"
class menu_nivel : public menu {
    public:

        static menu_nivel* instance();
       
        
        void update(float deltaTime);
        void seleccionarMundo(std::string mundo){ nivel = mundo;}

    protected:
        menu_nivel(sf::Font fuente, int max );
    private: 
        static sf::Font* fuente;
        static menu_nivel* p_instance;
        std::string nivel;
        
};
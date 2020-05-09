#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//ANDRES : ESTE CODIGO ES PRACTICAMENTE IGUAL AL DE MI PENGO ASI QUE SI LO UTILIZAIS CAMBIARLOOO!!!!!!

#include "menu.h"
#include "../Juego/Juego.h"

class menu_vol : public menu {
    public:

        static menu_vol* instance();
       
        
        void update(float deltaTime);
        

    protected:
        menu_vol(sf::Font fuente, int max);
    private: 
        static sf::Font* fuente;
        static menu_vol* p_instance;
        
};
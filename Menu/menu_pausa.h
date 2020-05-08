#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//ANDRES : ESTE CODIGO ES PRACTICAMENTE IGUAL AL DE MI PENGO ASI QUE SI LO UTILIZAIS CAMBIARLOOO!!!!!!

#include "menu.h"
#include "menu_controles.h"
#include "menu_vol.h"
#include "menu_inicial.h"
class menu_pausa : public menu {
    public:

        static menu_pausa* instance();
       
        
        void update(float deltaTime);
        

    protected:
        menu_pausa(sf::Font fuente, int max);
    private: 
        static sf::Font* fuente;
        static menu_pausa* p_instance;
        
};
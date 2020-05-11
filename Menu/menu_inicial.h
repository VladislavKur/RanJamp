#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//ANDRES : ESTE CODIGO ES PRACTICAMENTE IGUAL AL DE MI PENGO ASI QUE SI LO UTILIZAIS CAMBIARLOOO!!!!!!

#include "menu.h"
#include "menu_controles.h"
#include "menu_vol.h"
#include "../Tienda/Tienda.h"
#include "Tutorial.h"
class menu_inicial : public menu {
    public:

        static menu_inicial* instance();
       
        
        void update(float deltaTime);
        

    protected:
        menu_inicial(sf::Font fuente, int max);
    private: 
        static sf::Font* fuente;
        static menu_inicial* p_instance;
        bool noeslaprimeravezxd = false;
        
};
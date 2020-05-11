#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


#include "menu.h"
#include "menu_controles.h"
#include "menu_vol.h"
#include "menu_inicial.h"
class menu_pausa : public menu {
    public:

        static menu_pausa* instance();
       
        // seleccionar la opcion que quieres y cambias de estado
        void update(float deltaTime);
        

    protected:
        menu_pausa(sf::Font fuente, int max);
        ~menu_pausa(); 
    private: 
        static sf::Font* fuente;
        static menu_pausa* p_instance;
        
};
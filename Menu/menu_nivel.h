#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


#include "menu.h"

#include "../Juego/Juego.h"
class menu_nivel : public menu {
    public:

        static menu_nivel* instance();
       
        //seleccionas el nivel que quieres jugar y cambia de estado
        void update(float deltaTime);
        void seleccionarMundo(std::string mundo){ nivel = mundo;}

    protected:
        menu_nivel(sf::Font fuente, int max, int maxS);
        ~menu_nivel(); 
    private: 
        static sf::Font* fuente;
        static menu_nivel* p_instance;
        std::string nivel; // guarda el nombre del nivel
        
};
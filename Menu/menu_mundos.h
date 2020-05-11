#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


#include "menu.h"
#include "../Juego/Manejador.h"
#include "../Juego/Juego.h"
class menu_mundos : public menu {
    public:

        static menu_mundos* instance();
       
        
        void update(float deltaTime);
        

    protected:
     //si presiono "Enter" cada cierto tiempo vuelvo al estado anterior, en este caso al "Menu_Inicio"
        menu_mundos(sf::Font fuente, int max);
        ~menu_mundos(); 
    private: 
        static sf::Font* fuente;
        static menu_mundos* p_instance;
        
};
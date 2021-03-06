#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


#include "menu.h"

#include "../Juego/Juego.h"
class menu_controles : public menu {
    public:
        static menu_controles* instance();
        //si presiono "Enter" cada cierto tiempo vuelvo al estado anterior, en este caso al "Menu_Inicio"
        void update(float deltaTime);
    protected:
        // Imagen con los controles y creo un bloque que contendra la imagen para poder moverla luego sin smfl
        menu_controles(sf::Font fuente, int max);
        ~menu_controles(); 
    private: 
        static sf::Font* fuente;
        static menu_controles* p_instance;
        
};
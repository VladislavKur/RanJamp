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
       
        //si presiono "Enter" en una de las opciones seleccionadas cambio de estado a esa opcion
        void update(float deltaTime);
        

    protected:
     //si presiono "Enter" cada cierto tiempo vuelvo al estado anterior, en este caso al "Menu_Inicio"
        menu_inicial(sf::Font fuente, int max);
    private: 
        static sf::Font* fuente;
        static menu_inicial* p_instance;
        bool noeslaprimeravezxd = false; //esta variable comprueba si es la primera vez que entras en menu inicial, si es true, este cambia el texto 
};
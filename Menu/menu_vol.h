#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



#include "menu.h"
#include "../Juego/Juego.h"

class menu_vol : public menu {
    public:

        static menu_vol* instance();
       
        //puedes cambiar el volumen y vuelve al menu principal
        void update(float deltaTime);
        

    protected:
        menu_vol(sf::Font fuente, int max, int maxS, int aux);
        ~menu_vol(); 
    private: 
        static sf::Font* fuente;
        static menu_vol* p_instance;
        bool pausa;
        
        
};
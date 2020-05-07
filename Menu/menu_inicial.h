#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//ANDRES : ESTE CODIGO ES PRACTICAMENTE IGUAL AL DE MI PENGO ASI QUE SI LO UTILIZAIS CAMBIARLOOO!!!!!!

#include "menu.h"

class menu_inicial : public menu {
    public:
        menu_inicial( Font fuente, int max);
        ~menu_inicial(){};
        void update(float deltaTime);
};
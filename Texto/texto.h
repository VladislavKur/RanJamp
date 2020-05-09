#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Motor/Motor.h"
#pragma once

using namespace std;

class texto{
    public: 
      texto(int i, std::vector<sf::String> t , std::vector<sf::Vector2f> pos);
      void render();
      ~texto();
    private:
     sf::Font font; 
     sf::Text * text;
     int cantidad;
};
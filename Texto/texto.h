#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../Motor/Motor.h"
#pragma once

using namespace std;

class texto{
    public: 
      //fachada crea un texto de sfml
      texto(int i, std::vector<sf::String> t , std::vector<sf::Vector2f> pos);
      // renderiza el texto
      void render();
      ~texto();
    private:
     sf::Font font; 
     sf::Text * text;
     int cantidad;
};
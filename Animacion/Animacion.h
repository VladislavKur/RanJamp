#pragma once
#include <SFML/Graphics.hpp>
#include "../Motor/Motor.h"
//ALEJANDRO EL GUAPO ME HA DICHO QUE PONGA RELOJES DENTRO DE ANIMACION

class Animacion{

    public:
        Animacion(std::string fichero,sf::Vector2u cantidadImagenes, float SwitchTimeSprite,
            sf::Vector2f tamanyoCuerpo,sf::Vector2f tamanyoSprite);
        ~Animacion();
        void Update(float deltaTime);
        void setSprite(sf::Vector2u Sprites);
        
       
    private:
        sf::Vector2u cantidadImagenes;
        sf::Vector2u spriteActual;
        sf::RectangleShape body;
        

        float temporizador;
        float SwitchTimeSprite;

         
        sf::IntRect textureRect;

};
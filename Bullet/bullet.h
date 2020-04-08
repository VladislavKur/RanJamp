#pragma once
#include <SFML/Graphics.hpp>
#include "../Motor/Motor.h"

#define maxBullets 256

class Bullet
{
private:
    sf::CircleShape body;
    bool facing;
    float velocidad;
    
public:
    Bullet(float, float, bool, int);
    ~Bullet() {}

    float lifetime; //Contador que destruye la bala cuando llega a 0
    void update(float deltaTime);
    void render();

    sf::CircleShape getBody(){return body;};

};

#pragma once
#include <SFML/Graphics.hpp>
#include "../Motor/Motor.h"

#define maxBullets 64

class Bullet
{
private:
    sf::CircleShape body;
    bool facing;
    
public:
    Bullet(float, float, bool);
    ~Bullet() {}

    float lifetime; //Contador que destruye la bala cuando llega a 0
    void update(float deltaTime);
    void render();

    static Bullet* bullets[maxBullets];
    static void initBulletArray();
    static bool array_inicializado;
};
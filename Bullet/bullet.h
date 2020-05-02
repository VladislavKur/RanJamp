#pragma once
#include <SFML/Graphics.hpp>
#include "../Motor/Motor.h"
#include "../Enumerador/typeBody.h"
#include "../Enumerador/typeBullet.h"
#include "../Cuerpo/Cuerpo.h"
#include "../Rectangulo/Rectangulo.h"

#define maxBullets 256

class Bullet
{
private:
    Cuerpo * body;
    Rectangulo* hitbox;
    bool facing;
    float velocidad;
    int dir;
public:
    Bullet(float, float, bool, int);
    ~Bullet() {}

    float lifetime; //Contador que destruye la bala cuando llega a 0
    void update(float deltaTime);
    void render(float );

    Rectangulo* getHitbox(){return hitbox;}
    Cuerpo* getBody(){return body;};

};

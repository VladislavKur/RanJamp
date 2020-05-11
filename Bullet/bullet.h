#pragma once
#include <SFML/Graphics.hpp>
#include "../Motor/Motor.h"
#include "../Enumerador/typeBody.h"
#include "../Enumerador/typeBullet.h"
#include "../Cuerpo/Cuerpo.h"
#include "../Rectangulo/Rectangulo.h"

#define maxBullets 256

//Balas, tanto del jugador como de los enemigos. 
class Bullet
{
private:
    Cuerpo * body;
    Rectangulo* hitbox;

    bool facing; //false=izquierda, true=derecha.

    float velocidad;
    int dir; //permite atacar verticalmente
public:
    Bullet(float, float, bool, int, int);
    ~Bullet();

    //Contador que destruye la bala cuando llega a 0
    float lifetime; 
    //update
    void update(float deltaTime);
    //render
    void render(float );
    //recoloca el rectangulo de colision de la bala
    void updateHitbox();
    //GET
    Rectangulo* getHitbox(){return hitbox;}
    Cuerpo* getBody(){return body;};
    //SET
    void setVelocidad(float p_velocidad){velocidad=p_velocidad;}

};

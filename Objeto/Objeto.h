#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.h"
#include "../Enumerador/typeBody.h"
#include "../Cuerpo/Cuerpo.h"
#include "../Rectangulo/Rectangulo.h"

#ifndef OBJETO_H
#define OBJETO_H
//Objeto consiste en powerups y armas que se pueden recoger
class Objeto
{

    public:
        ~Objeto();//t --> tipo
        Objeto( float , float, int t);

        //
        void render(float );

        //GET
        Cuerpo* getBody();
        Rectangulo* getHitbox(){return hitbox;}
        int getTipo();
        //SET
        void setTipo(int t);
        //Eliminar un objeto
        void destroirObjeto(Objeto *);

        
    private:

        Cuerpo* body;
        Rectangulo* hitbox; //rectangulo de colision

        int tipo; //Los tipos son: 0 = powerup de velocdad, 1 = arma, 2 = powerup de doble salto, 3 = powerup de Slowhits(balas enemigas mas lentas)


};
#endif
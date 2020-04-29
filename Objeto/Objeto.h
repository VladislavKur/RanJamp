#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.h"
#include "../Enumerador/typeBody.h"
#include "../Cuerpo/Cuerpo.h"
#include "../Rectagulo/Rectangulo.h"



class Objeto
{

    public:
    ~Objeto();//t --> tipo
    Objeto( float , float, int t);

    void render(float );
    void update(Player &otherBody);
    Cuerpo* getBody();


    void recogido();
    int getTipo();
    void setTipo(int t);
    void destroirObjeto(Objeto *);
    Rectangulo* getHitbox(){return hitbox;}
    private:

    Cuerpo* body;
    Rectangulo* hitbox;

    int tipo;


};
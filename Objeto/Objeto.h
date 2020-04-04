#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.h"


class Objeto
{

    public:
    ~Objeto();//t --> tipo
    Objeto( sf::Vector2f Posicion, int t);

    void render();
    void update(Player &otherBody);
    sf::RectangleShape getBody();


    void recogido();
    int getTipo();
    void setTipo(int t);

    private:

    sf::RectangleShape body;

    int tipo;


};
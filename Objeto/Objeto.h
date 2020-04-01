#pragma once
#include <SFML/Graphics.hpp>
#include "../Player/Player.h"


class Objeto
{

    public:
    ~Objeto();//t --> tipo
    Objeto(sf::Texture* tex,sf::Vector2f size, sf::Vector2f Posicion,sf::Color color, int t);

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
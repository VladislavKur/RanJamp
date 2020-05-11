#pragma once
#include <SFML/Graphics.hpp>

class Rectangulo{

    public:
    ~Rectangulo();
    //CREAR LEFT TOP WIDTH HEIGHT
    Rectangulo( float , float,float , float);
    //POSICIONAR CORDENAS LEFT TOP
    void posicionar(float l, float f);
    //METODOS GET DEL FLOAT RECT
    sf::FloatRect getBody(){return body;};
    float getLeft(){return body.left;}
    float getWidth(){return body.width;}
    float getTop(){return body.top;}
    float getHeight(){return body.height;}
    //METODOS SET DEL FLOAT RECT
    void setLeft(float l){body.left = l;}
    void setWidth(float w){body.width = w;}
    void setTop(float t){body.top = t;}
    void setHeight(float h){body.height = h;}
    //GET DEL OBJETO RECTANGULO
    bool getIntersect(Rectangulo &);

    private:
    sf::FloatRect body;

};
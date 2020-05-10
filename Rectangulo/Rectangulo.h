#pragma once
#include <SFML/Graphics.hpp>

class Rectangulo{

    public:
    ~Rectangulo();
    Rectangulo( float , float,float , float);
    void posicionar(float l, float f);
   
    sf::FloatRect getBody(){return body;};
    float getLeft(){return body.left;}
    float getWidth(){return body.width;}
    float getTop(){return body.top;}
    float getHeight(){return body.height;}

    void setLeft(float l){body.left = l;}
    void setWidth(float w){body.width = w;}
    void setTop(float t){body.top = t;}
    void setHeight(float h){body.height = h;}

    bool getIntersect(Rectangulo &);

    private:
    sf::FloatRect body;

};
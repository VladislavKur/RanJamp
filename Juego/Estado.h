#include <SFML/Graphics.hpp>

#ifndef ESTADO_H
#define ESTADO_H

//Patron State. Clase base para los estados.
class Estado{
    protected:
    
    public:
        Estado();
        ~Estado();
    
        virtual void update(float deltaTime);
        virtual void render(float num);
};

#endif
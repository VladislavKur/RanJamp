#include <SFML/Graphics.hpp>

#ifndef ESTADO_H
#define ESTADO_H

//Patron State. Clase base para los estados.
class Estado{
    protected:
    
    public:
        Estado();
        ~Estado();

        //update base para cada estado
        virtual void update(float deltaTime);
        //render base para cada estado
        virtual void render(float num);
};

#endif
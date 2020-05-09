#include <SFML/Graphics.hpp>
#include "Estado.h"

#ifndef MANEJADOR_H
#define MANEJADOR_H

class Manejador{
private:
    static Manejador* p_instancia;
    Manejador();
    Estado* estado;
    Estado* anterior;
   

public:
    static Manejador* instancia();
    ~Manejador();
    void cambiarEstado(Estado* p_estado);
    void update(float deltaTime);
    void render(float num);

    void back();

    
};

#endif
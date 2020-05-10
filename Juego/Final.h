#include "Estado.h"
#include "../Cuerpo/Cuerpo.h"
#include "../Texto/texto.h"
using namespace sf;
#define numEstrellas 8

class Final : public Estado
{
private:
    Final();
    static Final* p_instancia;
    int graduaColor;
    bool dandoVueltas;
    bool modRadio;
    float angulos[numEstrellas];
    float radio;
    Cuerpo *estrellas[numEstrellas];
    Cuerpo *mago;
    sf::View* vista;
    Text *puntuacion;
    Text *the_end;
    Font *fuente;
    int vueltas;
public:
    static Final* instancia();
    ~Final();

    void reset();
    void update(float deltaTime);
    void render(float num);
    void cambiarTexto(int i , String s, float posx , float posy);
};

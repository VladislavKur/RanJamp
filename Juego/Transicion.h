#include "Estado.h"
#include "Cuerpo.h"
#include "../Texto/texto.h"
using namespace sf;

class Transicion : public Estado
{
private:
    Transicion();
    static Transicion* p_instancia;

    float angulo;
    float radio;
    Cuerpo *mago;
    Cuerpo *portal;
    sf::View* vista;
    Text *puntuacion;
    Font *fuente;
public:
    static Transicion* instancia();
    ~Transicion();

    void reset();
    void update(float deltaTime);
    void render(float num);
    void cambiarTexto(int i , String s, float posx , float posy);
};

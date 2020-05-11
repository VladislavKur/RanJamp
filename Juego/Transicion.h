#include "Estado.h"
#include "Cuerpo.h"
#include "../Texto/texto.h"
using namespace sf;

//Transicion entre niveles
class Transicion : public Estado
{
private:
    Transicion();
    static Transicion* p_instancia;

    float angulo; // se utiliza para que el mago de vueltas alrededor del portal
    float radio; // distancia entre el mago y el portal
    Cuerpo *mago;
    Cuerpo *portal;
    sf::View* vista;
    Text *puntuacion;
    Font *fuente;
public:
    static Transicion* instancia();
    ~Transicion();

    //Para volver a hacerla desde el principio.
    void reset();
    //
    void update(float deltaTime);
    void render(float num);
    //Similar a cambiarTexto de HUD. Coge el texto i, y cambia sus atributos.
    void cambiarTexto(int i , String s, float posx , float posy);
};

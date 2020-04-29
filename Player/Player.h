#pragma once
#include <SFML/Graphics.hpp>
#include "../Animacion/Animacion.h"
#include "../Mundo/Mundo.h"
#include "../Enumerador/typeBody.h"
#include "../Cuerpo/Cuerpo.h"
#include "../Rectagulo/Rectangulo.h"
class Player
{
private:
    sf::Vector2u textura;
    Cuerpo* body;
    
    float velocidad;
    int saltos;
    int arma;
    bool PU_saltoDoble; bool PU_velocidad; bool PU_slowhits; // Powerups, se pueden hacer un array mas adelante
    float jumpSpeed;
    float jumpHeight; //Constante (en principio)
    Animacion animacion;
    int vidas;
    float cooldownSalto;
    float cooldownDisparo;

    bool godMode;
    int vidasAnteriores;
    Rectangulo* hitbox;
    bool facing;

public:
    //CANON
    Player();
    Player(int x, int y);
    //Player(sf::Texture* textura, sf::Vector2u cantidadImagenes, float SwitchTimeSprite);
    ~Player() ;
    bool auxSaltos;

    //FUNCIONALIDAD
    void render(float );
    void update(float deltaTime , Mundo * mundo);
    void updateHitbox();

    void perderVida();
    
    void toggleGodMode();
    void saltar();

    void reset();

    //GET
    int getSaltos(){return saltos;}
    int getArma(){return arma;}
    
    bool getPU_SaltoDoble(){return PU_saltoDoble;}; 
    bool getPU_Velocidad(){return PU_velocidad;}; 
    bool getPU_Slowhits(){return PU_slowhits;};
    float getJumpSpeed(){return jumpSpeed;};
    Cuerpo* getBody(){return body;}
    Rectangulo* getHitbox(){return hitbox;}
    int getVidas(){return vidas;}
    float getCooldownSalto(){return cooldownSalto;};
    float getCooldownDisparo(){return cooldownDisparo;}
    float getVelocidad(){return velocidad;}
    bool getFacing(){return facing;}

    //SET
    void obtenerPU_SaltoDoble();
    void obtenerPU_Velocidad();
    void obtenerPU_Slowhits();

    void perderPU_SaltoDoble();
    void perderPU_Velocidad();
    void perderPU_Slowhits();

    void setJumpSpeed(float);
    
    void setSaltos(int);
    void avanzarCooldownDisparo(float deltaTime){cooldownDisparo-=deltaTime;};
    void setCooldownDisparo(float p_cooldown){cooldownDisparo=p_cooldown;}

    void setVelocidad(float);
    void setArma(int);
    bool setVidas(int);
    void setPosicion(float, float );

    void moveRight(float deltaTime, Mundo * mundo);
    void moveLeft(float deltaTime, Mundo * mundo);

    sf::FloatRect coliAbajo;
    sf::FloatRect coliArriba;
    sf::FloatRect coliIzquierda;
    sf::FloatRect coliDerecha;
};
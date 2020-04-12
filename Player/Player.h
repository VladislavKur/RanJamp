#pragma once
#include <SFML/Graphics.hpp>
#include "../Animacion/Animacion.h"



class Player
{
private:
    sf::Vector2u textura;
    sf::RectangleShape body;
    
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

public:
    //CANON
    Player();
    Player(int x, int y);
    //Player(sf::Texture* textura, sf::Vector2u cantidadImagenes, float SwitchTimeSprite);
    ~Player() ;
    bool auxSaltos;

    //FUNCIONALIDAD
    void render();
    void update(float deltaTime);
    void updateHitbox();
    
    void saltar();

    //GET
    int getSaltos(){return saltos;}
    int getArma(){return arma;}
    bool getPU_SaltoDoble(){return PU_saltoDoble;}; 
    bool getPU_Velocidad(){return PU_velocidad;}; 
    bool getPU_Slowhits(){return PU_slowhits;};
    float getJumpSpeed(){return jumpSpeed;};
    sf::RectangleShape getBody(){return body;}
    int getVidas(){return vidas;}
    float getCooldownSalto(){return cooldownSalto;};
    float getCooldownDisparo(){return cooldownDisparo;}

    //SET
    void obtenerPU_SaltoDoble();
    void obtenerPU_Velocidad(){PU_velocidad = true;}
    void obtenerPU_Slowhits(){PU_slowhits = true;}

    void perderPU_SaltoDoble();
    void perderPU_Velocidad();
    void perderPU_Slowhits();

    void setJumpSpeed(float);
    void setSaltos();
    void setSaltos(int);
    void avanzarCooldownDisparo(float deltaTime){cooldownDisparo-=deltaTime;};
    void setCooldownDisparo(float p_cooldown){cooldownDisparo=p_cooldown;}

    void setVelocidad();
    void setArma(int);
    void setVidas(int);
    void setPosicion(float, float );

    void moveRight(float deltaTime);
    void moveLeft(float deltaTime);

    void morir();

    sf::FloatRect coliAbajo;
    sf::FloatRect coliArriba;
    sf::FloatRect coliIzquierda;
    sf::FloatRect coliDerecha;
};
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

public:
    //CANON
    Player();
    Player(int x, int y);
    //Player(sf::Texture* textura, sf::Vector2u cantidadImagenes, float SwitchTimeSprite);
    ~Player() ;

    //FUNCIONALIDAD
    void render();
    void update(float deltaTime);
    
    void saltar();

    //GET
    int getSaltos(){return saltos;}
    int getArma(){return arma;}
    bool getPU_SaltoDoble(){return PU_saltoDoble;}; 
    bool getPU_Velocidad(){return PU_velocidad;}; 
    bool getPU_Slowhits(){return PU_slowhits;};
    float getJumpSpeed(){return jumpSpeed;};
    sf::RectangleShape getBody(){return body;}

    //SET
    void obtenerPU_SaltoDoble();
    void obtenerPU_Velocidad();
    void obtenerPU_Slowhits();

    void perderPU_SaltoDoble();
    void perderPU_Velocidad();
    void perderPU_Slowhits();

    void setSaltos();
    void setVelocidad();
    void setArma(int);

    void moveRight(float deltaTime);
    void moveLeft(float deltaTime);

    sf::FloatRect coliAbajo;
    sf::FloatRect coliArriba;
    sf::FloatRect coliIzquierda;
    sf::FloatRect coliDerecha;
};
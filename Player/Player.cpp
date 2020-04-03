
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
Player::~Player(){

}
Player::Player()
:animacion("sprites.png",
            sf::Vector2u(40,19),
            0.33f,
            sf::Vector2f(100.0f,100.0f),
            sf::Vector2f(75.0,75.0)
            ){

} 

Player::Player(int x, int y) 
: animacion("sprites.png",
            sf::Vector2u(40,19),
            0.33f,
            sf::Vector2f(100.0f,100.0f),
            sf::Vector2f(75.0,75.0)
            ){
    
    
    //body.setSize(sf::Vector2f(100.0f,100.0f));
    //body.setTexture(tex);
    
    //body.setOrigin(75 / 2, 75 / 2);  // 75 es el tamaño del sprite, cambiar
    //body.setPosition(x, y);//Quitar esto mas adelante

    //body.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
    saltos = 1;
    jumpSpeed=0;
    jumpHeight=75*2;
    arma=0;    
}

void Player::update(float deltaTime){
    Vector2f gp = body.getPosition();
    FloatRect gbb = body.getGlobalBounds();

    coliAbajo.left = gp.x - gbb.width/2 + 25;
    coliAbajo.top = gp.y + gbb.height/2;
    coliAbajo.width = gbb.width-50;
    coliAbajo.height = 6;
    
    coliIzquierda.left = gp.x - gbb.width/2+12;
    coliIzquierda.top = gp.y - gbb.height/2 + 25 ;
    coliIzquierda.width = gbb.width/2-15;
    coliIzquierda.height = gbb.height -25;

    coliDerecha.left = gp.x+5;
    coliDerecha.top = gp.y - gbb.height/2 +25;
    coliDerecha.width = gbb.width/2 -20;
    coliDerecha.height = gbb.height -25;

    coliArriba.left = gp.x - gbb.width/2 + 20;
    coliArriba.top = gp.y-gbb.height/2 +25;
    coliArriba.width = gbb.width - 40;
    coliArriba.height = 5;


    // //Moverse a la derecha si la plataforma lo permite
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
    //   if(!coliDerecha.intersects(plataforma.getBody().getGlobalBounds()))
    //     moveRight(deltaTime);
    //   }
    // //Moverse a la izquierda si la plataforma lo permite
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
    //   if(!coliIzquierda.intersects(plataforma.getBody().getGlobalBounds()))
    //     moveLeft(deltaTime);
    //   }

//Dejar de caer si toco plataforma
//  if(coliAbajo.intersects(plataforma.getBody().getGlobalBounds()) ||
//    coliAbajo.intersects(suelo.getBody().getGlobalBounds()) ){
//     saltos = PU_saltoDoble ? 2 : 1;
//     jumpSpeed=0;
  
//    } else 
//       jumpSpeed+=981.0f*deltaTime;

  //caer

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
        saltar();
    }

    // if(coliArriba.intersects(plataforma.getBody().getGlobalBounds())){
    //     jumpSpeed=10;
    // }
    
    //Caída constante
    body.move(0,jumpSpeed*deltaTime);
}

void Player::setSaltos(){
  
  //jumpHeight *= 2;
  saltos+= 100;
}




void Player::render(){
  Motor * motor = Motor::instance();
  motor->dibujo(body);
}
void Player::moveRight(float deltaTime){

      body.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
      //Escala por defecto
      body.setScale(1, 1);
      body.move(500*deltaTime, 0);

}
void Player::moveLeft(float deltaTime){

     body.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
     body.setScale(-1, 1);
     body.move(-500*deltaTime, 0);


}
void Player::saltar(){
  if(saltos!=0){
        
        jumpSpeed = -sqrtf(2.0f * 981.0f * jumpHeight);
        std::cout<< "Saltos: " << saltos<<std::endl;
        saltos--;
      }
}


void Player::obtenerPU_SaltoDoble(){
  PU_saltoDoble=true;
}

void Player::setArma(int p_arma){
  arma = p_arma;
}

void Player::setJumpSpeed(float p_speed){
  jumpSpeed=p_speed;
}
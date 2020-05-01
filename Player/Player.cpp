
#include "Player.h"

Player::~Player(){

}
Player::Player()
:animacion("/Imagenes/mago.png",
            sf::Vector2u(40,19),
            0.33f,
            sf::Vector2f(100.0f,100.0f),
            sf::Vector2f(75.0,75.0)
            ){//WIP fachada
    sf::Texture *text = new sf::Texture; //wip fachada

    saltos = 1;
    jumpSpeed=0;
    jumpHeight=30;
    arma=0;  
    vidas = 5; 
    velocidad=250;

    PU_saltoDoble=false;
    PU_slowhits=false;
    PU_velocidad=false;
    godMode=false;

    auxSaltos = true;
    cooldownSalto = 0;
    cooldownDisparo = 0;

    body.setSize(sf::Vector2f(100.0f,100.0f)); //wip fachada
    body.setPosition(100, 950); //wip fachada

    body.setOrigin(75/2 ,75/2); //wip fachada

    if(!text->loadFromFile("resources/Imagenes/mago.png")) cout << "sadasds"; //hacer un handle del error mejor
    
    body.setTexture(text); //wip fachada
    body.setTextureRect(sf::IntRect(0 , 0 , 128, 256)); //wip fachada

    /*PU_saltoDoble = true;
    PU_velocidad = true;
    arma=1;  */
    
} 

Player::Player(int x, int y) 
: animacion("/Imagenes/mago.png",
            sf::Vector2u(40,19),
            0.33f,
            sf::Vector2f(100.0f,100.0f),
            sf::Vector2f(75.0,75.0)
            ){ //lo mismo que lo del constructor de arriba, wip fachada y TERMINAR
    
    //body.setSize(sf::Vector2f(100.0f,100.0f));
    //body.setTexture(tex);
    
    //body.setOrigin(75 / 2, 75 / 2);  // 75 es el tamaño del sprite, cambiar
    //body.setPosition(x, y);//Quitar esto mas adelante

    //body.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
    saltos = 1;
    jumpSpeed=0;
    jumpHeight=75*2;
    arma=0;  
    vidas = 5;  
    velocidad=1;
    godMode=false;

    
}

void Player::update(float deltaTime , Mundo * mundo){
    
    updateHitbox(); //arreglar lo de update hitbox


    cooldownSalto-=deltaTime;
    if(cooldownSalto<=0){
      auxSaltos=true;
    }

    cooldownDisparo-=deltaTime;


  //caer

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){ //quitar esto de aqui
      if(auxSaltos==true && saltos > 0){
          saltar();
          cooldownSalto=15*deltaTime;
        }
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){ //esto no va asi
        moveRight(deltaTime , mundo);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){ //lo mismo que lo anterior WIP fachada
        moveLeft(deltaTime, mundo);
    }

  
    
    //Caída constante
    body.move(0,jumpSpeed*deltaTime); //wip fachada
}



bool Player::setVidas(int v){
  bool devolver = false; 
  if((godMode  == true && (v > vidas)) || godMode == false){
      vidas = v;
  }

  if(vidas == 0 && godMode == false){
    devolver = true; 
  }

  return devolver;
}

void Player::render(){
  Motor * motor = Motor::instance();
  motor->dibujo(body);
}
void Player::moveRight(float deltaTime , Mundo * mundo){
  bool puede = true;
  Cuerpo ** objetos = mundo->getObjetos();

  for( int i=0; i< mundo->getNumObjetos() ; i++){
  
    if(objetos[i]->getGlobalBounds().intersects( coliDerecha )){
        puede=false;
    }
  }

  if(puede){
    body.setTextureRect(sf::IntRect(0 , 0 , 128, 256));
    body.setScale(1, 1);
    body.move(velocidad*deltaTime, 0);
  }
}

void Player::moveLeft(float deltaTime , Mundo * mundo){
  bool puede=true;
  Cuerpo ** objetos = mundo->getObjetos();

  for(unsigned int i=0; i< mundo->getNumObjetos() ; i++){
  
    if(objetos[i]->getGlobalBounds().intersects( coliIzquierda )){
        puede=false;
    }
  }

  if(puede){
    body.setTextureRect(sf::IntRect(0 , 0 , 128, 256));
    body.setScale(-1, 1);
    body.move(-velocidad*deltaTime, 0);
  }
}
void Player::saltar(){
  if(saltos!=0){
        auxSaltos= false;
        jumpSpeed = -sqrtf(6.0f * 981.0f * jumpHeight);
        saltos--;
      }
}



void Player::setArma(int p_arma){
  arma = p_arma;
}

void Player::setJumpSpeed(float p_speed){
  jumpSpeed=p_speed;
}

void Player::setSaltos(int p_saltos){
  saltos=p_saltos;
}
void Player::setVelocidad(float vel){
  velocidad = vel;
}
void Player::setPosicion(float x, float y){
  sf::Vector2f pos;
  pos.x = x;
  pos.y = y;
  body.setPosition(pos); 
}

void Player::updateHitbox(){
    Vector2f gp = body.getPosition();
    FloatRect gbb = body.getGlobalBounds();

    coliAbajo.left = gp.x - gbb.width/2 + 25;
    coliAbajo.top = gp.y + gbb.height/2;
    coliAbajo.width = gbb.width/2;
    coliAbajo.height = 6;
    
    coliIzquierda.left = gp.x - gbb.width/2+12; //rojo
    coliIzquierda.top = gp.y - gbb.height/2 + 25 ;
    coliIzquierda.width = gbb.width/2-10;
    coliIzquierda.height = gbb.height -25;

    coliDerecha.left = gp.x+5;
    coliDerecha.top = gp.y - gbb.height/2 +25;
    coliDerecha.width = gbb.width/2 -20;
    coliDerecha.height = gbb.height -25;

    coliArriba.left = gp.x - gbb.width/2 + 20;
    coliArriba.top = gp.y-gbb.height/2 +25;
    coliArriba.width = gbb.width - 40;
    coliArriba.height = 5;
}
void Player::obtenerPU_SaltoDoble(){
  PU_saltoDoble=true;
}
void Player::obtenerPU_Velocidad(){
  PU_velocidad= true;
  velocidad = 350;
}
void Player::obtenerPU_Slowhits(){
  PU_slowhits= true;
}


// void Player::perderVida(){
//   if(!godMode){
//     vidas--;
//     if(vidas<=0){
//       morir();
//     }
//   }
// }

void Player::toggleGodMode(){
  if(godMode){
    godMode=false;
  } else{
    godMode=true;
    cout<<"MODO DIOS ACTIVADO !!!!!!!!!!!!!!!!"<<endl;
  }
}

void Player::reset(){
  sf::Texture *text = new sf::Texture; //wip fachada

    saltos = 1;
    jumpSpeed=0;
    jumpHeight=30;
    arma=0;  
    vidas = 5; 
    velocidad=250;

    PU_saltoDoble=false;
    PU_slowhits=false;
    PU_velocidad=false;
    godMode=false;

    auxSaltos = true;
    cooldownSalto = 0;
    cooldownDisparo = 0;

    body.setSize(sf::Vector2f(100.0f,100.0f)); //wip fachada
    body.setPosition(100, 1000); //wip fachada

    body.setOrigin(75/2 ,75/2); //wip fachada

    if(!text->loadFromFile("resources/Imagenes/mago.png")) cout << "sadasds"; //hacer un handle del error mejor
    
    body.setTexture(text); //wip fachada
    body.setTextureRect(sf::IntRect(0 , 0 , 128, 256)); //wip fachada
}
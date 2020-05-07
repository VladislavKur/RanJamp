
#include "Player.h"

Player::~Player(){

}
Player::Player(int x, int y){ 


  /*Cuerpo(float x_entrada, float y_entrada, int sizeHeight, int sizeWidth, 
            std::string fichero, float escala, typeBody tipoCuerpo){*/

    hitbox = new Rectangulo(100,100, x, y);
    saltos = 1;
    jumpSpeed=0;
    jumpHeight=25;
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
    body = new Cuerpo(x,y,128,256,"mago.png",1,RECTANGLE);
    body->setSize(100,100);
    body->addAnimacion(0.1);
    body->Origen(100/2,100/2);
    facing = true;
    //body->texturizar(text);
    
    //body->setTextureRect(sf::IntRect(0 , 0 , 128, 256)); //wip fachada // ESTO HAY QUE PONERLO
    
    coliAbajo = new Rectangulo(0,0,0,0);
    coliArriba = new Rectangulo(0,0,0,0);
    coliDerecha = new Rectangulo(0,0,0,0);
    coliIzquierda = new Rectangulo(0,0,0,0);
}

void Player::update(float deltaTime , Mundo * mundo){
    
    updateHitbox(); //arreglar lo de update hitbox

    if(body->getPosicion()[0]<0){
      body->posicionamiento(125, body->getPosicion()[1]);
      jumpSpeed=0;
    }

    if(body->getPosicion()[1]<0){
      body->posicionamiento(body->getPosicion()[0]+30, 1000);
      jumpSpeed=0;
    }

    cooldownSalto-=deltaTime;
    if(cooldownSalto<=0){
      auxSaltos=true;
    }

    cooldownDisparo-=deltaTime;


  //caer
    if(vidas!=0){
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){ //quitar esto de aqui
        if(auxSaltos==true && saltos > 0){
            saltar();
            cooldownSalto=15*deltaTime;
          }
      }
      
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){ //esto no va asi
          moveRight(deltaTime , mundo);
          facing = true;
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){ //lo mismo que lo anterior WIP fachada
          moveLeft(deltaTime, mundo);
          facing = false;
      }
    }
    

  
    float sadX = body->getPosicion()[0];
    float sadY = body->getPosicion()[1];
      
    body->moverse(0,jumpSpeed*deltaTime);
    //cout<<sadX<<"----"<<sadY<<endl;
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

void Player::render(float porcentaje){
  body->render(porcentaje);
}

void Player::moveRight(float deltaTime , Mundo * mundo){
  bool puede = true;
  Cuerpo ** objetos = mundo->getObjetos();

  for( int i=0; i< mundo->getNumObjetos() ; i++){
  
    if(objetos[i]->getGlobalBounds()->getIntersect(*coliDerecha)){
        puede=false;
    }
  }

  if(puede){
    body->Scalar(1.0f,1.0f);
    //body.setTextureRect(sf::IntRect(0 , 0 , 128, 256));
    body->moverse(velocidad*deltaTime,0);
  
  }
}

void Player::moveLeft(float deltaTime , Mundo * mundo){
  bool puede=true;
  Cuerpo ** objetos = mundo->getObjetos();

  for(unsigned int i=0; i< (unsigned)mundo->getNumObjetos() ; i++){
  
    if(objetos[i]->getGlobalBounds()->getIntersect(*coliIzquierda)){
        puede=false;
    }
  }

  if(puede){
    //body.setTextureRect(sf::IntRect(0 , 0 , 128, 256));
    
    body->Scalar(-1.0f,1.0f);
    body->moverse(-velocidad*deltaTime,0);
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


void Player::updateHitbox(){
   float gpx = body->getPosicion()[0];
   float gpy = body->getPosicion()[1];
   std::vector<float> gbb = body->getBounds();

    coliAbajo->setLeft(gpx - gbb[2]/2 + 25);
    coliAbajo->setTop(gpy + gbb[3]/2);
    coliAbajo->setWidth(gbb[2]/2);
    coliAbajo->setHeight(6);
    
    coliIzquierda->setLeft( gpx -  gbb[2]/2+12); //rojo
    coliIzquierda->setTop( gpy -  gbb[3]/2 + 25) ;
    coliIzquierda->setWidth( gbb[2]/2-10);
    coliIzquierda->setHeight(gbb[3] -25);

    coliDerecha->setLeft(gpx+5);
    coliDerecha->setTop(gpy -  gbb[3]/2 +25);
    coliDerecha->setWidth(gbb[2]/2 -20);
    coliDerecha->setHeight(gbb[3] -25);

    coliArriba->setLeft(gpx -  gbb[2]/2 + 20);
    coliArriba->setTop( gpy-  gbb[3]/2 +25);
    coliArriba->setWidth(gbb[2]- 40);
    coliArriba->setHeight(5);
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




void Player::toggleGodMode(){
  if(godMode){
    godMode=false;
  } else{
    godMode=true;
    cout<<"MODO DIOS ACTIVADO !!!!!!!!!!!!!!!!"<<endl;
  }
}

void Player::reset(){
  
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

    body->posicionamiento(100,1000);
    body->Origen(100/2,100/2);

}

void Player::setSize(float sizeX, float sizeY) {
  body->setSize(sizeX, sizeY);
}
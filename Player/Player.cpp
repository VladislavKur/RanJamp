
#include "Player.h"

Player::~Player(){

}
Player::Player(int x, int y) { 


  /*Cuerpo(float x_entrada, float y_entrada, int sizeHeight, int sizeWidth, 
            std::string fichero, float escala, typeBody tipoCuerpo){*/


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
    body = new Cuerpo(x,y,100,100,"mago.png",1,RECTANGLE);
    body->Origen(100/2,100/2);
    //body->texturizar(text);
    /*
    body.setTextureRect(sf::IntRect(0 , 0 , 128, 256)); //wip fachada*/ // ESTO HAY QUE PONERLO
    
    
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

  
    float sadX = body->getPosicion()[0];
    float sadY = body->getPosicion()[1];
      
    body->posicionamiento(0+sadX,sadY+jumpSpeed*deltaTime);
    
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
  RectangleShape ** objetos = mundo->getObjetos();

  for( int i=0; i< mundo->getNumObjetos() ; i++){
  
    if(objetos[i]->getGlobalBounds().intersects( coliDerecha )){
        puede=false;
    }
  }

  if(puede){
    body->Scalar(1.0f,1.0f);
    //body.setTextureRect(sf::IntRect(0 , 0 , 128, 256));
    body->posicionamiento(velocidad*deltaTime+body->getPosicion()[0],0+body->getPosicion()[1]);
  
  }
}

void Player::moveLeft(float deltaTime , Mundo * mundo){
  bool puede=true;
  RectangleShape ** objetos = mundo->getObjetos();

  for(unsigned int i=0; i< mundo->getNumObjetos() ; i++){
  
    if(objetos[i]->getGlobalBounds().intersects( coliIzquierda )){
        puede=false;
    }
  }

  if(puede){
    //body.setTextureRect(sf::IntRect(0 , 0 , 128, 256));
    
    body->Scalar(1.0f,1.0f);
    body->posicionamiento(-velocidad*deltaTime+body->getPosicion()[0],0+body->getPosicion()[1]);
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


    coliAbajo.left = gpx - gbb[2]/2 + 25;
    coliAbajo.top = gpy + gbb[3]/2;
    coliAbajo.width = gbb[2]/2;
    coliAbajo.height = 6;
    
    coliIzquierda.left = gpx -  gbb[2]/2+12; //rojo
    coliIzquierda.top = gpy -  gbb[3]/2 + 25 ;
    coliIzquierda.width =  gbb[2]/2-10;
    coliIzquierda.height =  gbb[3] -25;

    coliDerecha.left = gpx+5;
    coliDerecha.top = gpy -  gbb[3]/2 +25;
    coliDerecha.width =  gbb[2]/2 -20;
    coliDerecha.height =  gbb[3] -25;

    coliArriba.left = gpx -  gbb[2]/2 + 20;
    coliArriba.top = gpy-  gbb[3]/2 +25;
    coliArriba.width =  gbb[2]- 40;
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
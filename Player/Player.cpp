
#include "Player.h"

Player::~Player(){
    if(body != nullptr){
      delete body;
      body = nullptr;
    }
    if(hitbox != nullptr){
      delete hitbox;
      hitbox = nullptr;
    }

    if(coliAbajo != NULL){
      delete coliAbajo;
      coliAbajo = NULL;
    }
    if(coliArriba != NULL){
      delete coliArriba;
      coliArriba = NULL;
    }
    if(coliIzquierda != NULL){
      delete coliIzquierda;
      coliIzquierda = NULL;
    } 
    if(coliDerecha != NULL){
      delete coliDerecha;
      coliDerecha = NULL;
    }
    
}
Player::Player(int x, int y){ 


  /*Cuerpo(float x_entrada, float y_entrada, int sizeHeight, int sizeWidth, 
            std::string fichero, float escala, typeBody tipoCuerpo){*/

    hitbox = new Rectangulo(100,100, x, y);
    saltos = 1;
    jumpSpeed=0;
    jumpHeight=40; 

    hud * Hud = hud::instance();
    PU_saltoDoble= Hud->getDoblesalto();
    PU_slowhits= Hud->getSlow();
    PU_velocidad=Hud->getVelocidad();
    velocidad = Hud->getIVelocidad();
    vidas = Hud->getVidas();
    godMode = Hud->getGodMode();
    arma = 0;

    auxSaltos = true;
    cooldownSalto = 0;
    cooldownDisparo = 0;
    cooldownShift = 0;
    body = new Cuerpo(x,y,128,256,"Magos.png",1,RECTANGLE);
    body->setSize(100,100);
    body->addAnimacion(0);
    body->Origen(100/2,100/2);
    facing = true;
    atacando_melee=0;
    caida = true;
    caidaTiempo = 0.0;
    //body->texturizar(text);
    
    //body->setTextureRect(sf::IntRect(0 , 0 , 128, 256)); //wip fachada // ESTO HAY QUE PONERLO
    
    coliAbajo = new Rectangulo(0,0,0,0);
    coliArriba = new Rectangulo(0,0,0,0);
    coliDerecha = new Rectangulo(0,0,0,0);
    coliIzquierda = new Rectangulo(0,0,0,0);
    melee = new Rectangulo(0,0,0,0);

    monedas = 0;

}

void Player::caer(){

  caida = true;
  caidaTiempo = 0.0;

}

void Player::suelo(float posX, float posY){

  body->posicionamiento(posX,posY);
  caida  = false;
  jumpSpeed = 0.0;

}

void Player::update(float deltaTime , Mundo * mundo){
    hud * Hud = hud::instance();
    PU_saltoDoble= Hud->getDoblesalto();
    PU_slowhits= Hud->getSlow();
    PU_velocidad=Hud->getVelocidad();
    velocidad = Hud->getIVelocidad();
    vidas = Hud->getVidas();
    godMode = Hud->getGodMode();

    updateHitbox(); //arreglar lo de update hitbox
    GolpeMelee(deltaTime);

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
            
            body->setSpriteAnimacion(1);
            body->setTimeAnimacion(0.2);

            cooldownSalto=15*deltaTime;
          }
      }

     if(Keyboard::isKeyPressed(Keyboard::Num1) && cooldownShift<0){
        cooldownShift=2;
        if(Hud->getArma()[0] > 0)
          arma=1;
     }
     if(Keyboard::isKeyPressed(Keyboard::Num2) && cooldownShift<0){
        cooldownShift=2;
        if(Hud->getArma()[1] > 0)
          arma=2;
     }
      cooldownShift -= deltaTime;
      
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){ //esto no va asi
          moveRight(deltaTime , mundo);
          //cout<<body->getTimeAnimacion()<<" / CAIDA: "<<jumpSpeed<< " / DISPARO: "<<cooldownDisparo<<endl;
          if(jumpSpeed >= 0.0 && cooldownDisparo <= 0.0){
            body->setSpriteAnimacion(0);
          }
          if(body->getTimeAnimacion()<=0){
            body->setTimeAnimacion(0.2);
          }

          facing = true;
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){ //lo mismo que lo anterior WIP fachada
          moveLeft(deltaTime, mundo);
          
          if(jumpSpeed >= 0.0 && cooldownDisparo <= 0.0){
            body->setSpriteAnimacion(0);
          }
          if(body->getTimeAnimacion()<=0){
            body->setTimeAnimacion(0.2);
          }

          facing = false;
      }
      else if(jumpSpeed >= 0.0 && body->getTimeAnimacion() != 0.0 && cooldownDisparo <= 0.0){
        body->setSpriteAnimacion(0);
        body->setTimeAnimacion(0);
      }
      
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)){ //lo mismo que lo anterior WIP fachada
        if(atacando_melee < -5){
          atacando_melee=0.1;
        }
      }
    }
    //cout<<atacando_melee<<endl;

  
    if(caida){
      caidaTiempo += deltaTime;
      jumpSpeed += 8.91f*100*caidaTiempo;
    }
    body->moverse(0,jumpSpeed*deltaTime);
    body->update(deltaTime);
}

void Player::sumarMonedas(){
  monedas++;
}

void Player::cogerLlave(int i){
  llaves.push_back(i);
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
  Cuerpo ** puertas = mundo->getMonedasLlaves();
  for( int i=0; i< mundo->getNumObjetos() ; i++){
    if(objetos[i]->getGlobalBounds()->getIntersect(*coliDerecha)){
        puede=false;
    }
  }
  for( int i=0; i< mundo->getNumMonedasLlaves() ; i++){
    if(puertas[i]->getTipo() == 2){
      if(puertas[i]->getGlobalBounds()->getIntersect(*coliDerecha)){
        puede=false;
      }
    }
  }
  if(puede){
    body->Scalar(1.0f,1.0f);
    body->moverse(velocidad*deltaTime,0);

  
  }
}

void Player::moveLeft(float deltaTime , Mundo * mundo){
  
  bool puede=true;
  Cuerpo ** objetos = mundo->getObjetos();
  Cuerpo ** puertas = mundo->getMonedasLlaves();
  for(unsigned int i=0; i< (unsigned)mundo->getNumObjetos() ; i++){
  
    if(objetos[i]->getGlobalBounds()->getIntersect(*coliIzquierda)){
        puede=false;
    }
  }
  for( int i=0; i< mundo->getNumMonedasLlaves() ; i++){
    if(puertas[i]->getTipo() == 2){
      if(puertas[i]->getGlobalBounds()->getIntersect(*coliIzquierda)){
        puede=false;
      }
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
        //std::cout << "El jumpspeed es: " <<jumpSpeed <<"\n";
        
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

void Player::setCooldownDisparo(float p_cooldown){
  
  cooldownDisparo=p_cooldown;

  body->setSpriteAnimacion(3);
  body->setTimeAnimacion(0.2);

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

    coliArriba->setLeft(gpx - 15);
    coliArriba->setTop( gpy-  gbb[3]/2 +20);
    coliArriba->setWidth(30);
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
    
    hud * Hud = hud::instance();
    PU_saltoDoble= Hud->getDoblesalto();
    PU_slowhits= Hud->getSlow();
    PU_velocidad=Hud->getVelocidad();
    velocidad = Hud->getIVelocidad();
    vidas = Hud->getVidas();
    godMode = Hud->getGodMode();
    arma=0; 

    auxSaltos = true;
    cooldownSalto = 0;
    cooldownDisparo = 0;

    body->posicionamiento(100,1000);
    body->Origen(100/2,100/2);
    caida = true;
}

void Player::setSize(float sizeX, float sizeY) {
  body->setSize(sizeX, sizeY);
  /*
    if(!text->loadFromFile("resources/Imagenes/mago.png")) cout << "sadasds"; //hacer un handle del error mejor
    
    body.setTexture(text); //wip fachada
    body.setTextureRect(sf::IntRect(0 , 0 , 128, 256)); //wip fachada*/
}

bool Player::GolpeMelee(float deltaTime){

  
  vector<float> gp = body->getPosicion();
  Rectangulo gbb = *body->getGlobalBounds();

  float setleft=0;
  float settop=0;
  float setwidth=0;
  float setheight=0;

    if(facing){
      setleft = gp[0] - gbb.getWidth()/2;
      setwidth = gbb.getWidth() + 50;
      settop = gp[1] - 30;
      setheight = 60;
    }else{
      setleft = gp[0] + gbb.getWidth()/2;
      setwidth = -gbb.getWidth() - 50;
      settop = gp[1] - 30;
      setheight = 60;
    }
    melee->setLeft(setleft);
    melee->setTop(settop);
    melee->setWidth(setwidth);
    melee->setHeight(setheight);

    atacando_melee -= 3*deltaTime;

  return false;
}
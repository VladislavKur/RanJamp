#include "Juego.h"


Juego* Juego::pinstance = 0;

Juego::Juego(){
    mapa * mundo = mapa::instance(); 
    mundo->cargarmapa("Nivel1.tmx");
    mundo->crearSprites();
    mundo->cargarObjectGroups();
    mundo->crearObjetos();
    jugador = new Player();
    if(jugador == nullptr) printf("asdasd");
    crearObjetos();
    crearEnemigos();
    view.setSize(1024,720);
    
  for(int i = 0 ; i < maxBullets ; i++){
       bulletPlayer[i]=NULL;
    }

}

Juego* Juego::instance(){

    if(pinstance == 0){

        pinstance = new Juego();

    }

    return(pinstance);
}

void Juego::update(float deltaTime){ //wip // UPDATE FUNCIONANDO 
  Motor * m = Motor::instance();

  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
      disparar(deltaTime);
  }
    
    for(unsigned i = 0; i < maxBullets ;i++){
      if(bulletPlayer[i] == NULL) continue;
      if(bulletPlayer[i]->lifetime<=0){
        delete bulletPlayer[i];
        bulletPlayer[i]=NULL;
      }
      if(bulletPlayer[i] == NULL) continue; //POR SEGUNDA VEZ, porque puede que se haya destruido en la linea anterior si ha entrado al if
       bulletPlayer[i]->update(deltaTime);
    }

    for(unsigned i = 0; i < (sizeof(bulletEnemies)/sizeof(*bulletEnemies));i++){

      bulletEnemies[i].update(deltaTime);

    }
    
    colisionPlayerMundo(deltaTime);
    colisionBulletMundo(deltaTime);
    colisionBulletEnemigo(deltaTime);
    
    jugador->update(deltaTime);
  
    view.setCenter(jugador->getBody().getPosition());

    m->getVentana()->setView(view);


    for(unsigned i = 0; i < numEmenigos; i++){
      if(enemies[i]==NULL) continue;
      enemies[i]->update(jugador , deltaTime);

    }
    jugador->updateHitbox();

}

void Juego::colisionPlayerMundo(float deltaTime){// ESTO LO HACE VERMIAAA !!!!! -> interseccion player y rectangleshape 
    
    mapa * mundo = mapa::instance(); 
    RectangleShape ** objetos = mundo->getObjetos();
    // for(unsigned int i=0 ; i<sizeof(objetos) ; i++){
    //     std::cout<< "objeto " << i << "= [" << objetos[i]->getPosition().x <<  ", " << objetos[i]->getPosition().y << "]" << endl;   
    // }

    Vector2f posobj;
    bool pararse=false;
    bool aux = false;
    Vector2f posant;
    for(unsigned int i=0 ; i<  mundo->getNumObjetos(); i++){
      if(jugador->coliAbajo.intersects(objetos[i]->getGlobalBounds())){
        posobj = objetos[i]->getPosition();
        pararse=true;
      } 

      if(pararse){
        jugador->setSaltos( jugador->getPU_SaltoDoble() ? 2 : 1);

        if(aux == false){
          jugador->setPosicion(jugador->getBody().getPosition().x,posobj.y-55);
          jugador->updateHitbox();
          aux = true;
          posant = jugador->getBody().getPosition();
          
        } else if(posant != jugador->getBody().getPosition()){
          aux = false;
        }
        jugador->setJumpSpeed(0);

      }else{
        jugador->setJumpSpeed( jugador->getJumpSpeed() + 9.81f*5*deltaTime);
      }
      if(jugador->coliArriba.intersects(objetos[i]->getGlobalBounds())){
        jugador->setJumpSpeed(10);
      }
    }


}

void Juego::render(float porcentaje){ //wip

    Motor * m = Motor::instance();
    mapa * mundo = mapa::instance();
    mundo->render();
    for(unsigned i = 0; i < maxBullets;i++){
      if(bulletPlayer[i]==NULL) continue;
      bulletPlayer[i]->render();

    }
    for(unsigned i = 0; i < (sizeof(bulletEnemies)/sizeof(*bulletEnemies));i++){

     bulletEnemies[i].render();

    }

    jugador->render();
    
    int i = 0;
    while(enemies[i] != nullptr && i < numEmenigos){
      cout << " ENEMIGO " << i << endl;
      enemies[i]->render(porcentaje);
      i++;
    }
}


void Juego::crearObjetos(){ /// VlaDIS // LLAMARLO EN EL CONSTRUCTOR
  mapa * mundo = mapa::instance();
 
  sf::Vector2f pos;
 
  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(3);




  for(unsigned i = 0; i > posicion.size();i++){

    pos.x =posicion[i][0];
    pos.y = posicion[i][1];
    
    Objeto objeto1(pos ,posicion[i][2]);
  }
  
  

  // LLAMAR A OBJETO Y PASAR LOS PARAMETROS
}



void Juego::matarEnemigo(Enemigo* enem){
  for(unsigned i = 0; i <  (sizeof(enemies)/sizeof(*enemies));i++){

    if(enemies[i] == enem){
      delete[] enemies[i];
      break;
    }

  }
}
//CREARENEMIGOS FUNCIONE

void Juego::crearEnemigos(){ 
  mapa * mundo = mapa::instance();

  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(1);
  numEmenigos = posicion.size();
  enemies = new Enemigo *[posicion.size()]; 
  for(unsigned i = 0; i < posicion.size();i++){
    float posx =  posicion[i][0];
    float posy =  posicion[i][1];
    if(posicion[i][2] == 1){
        cout << "he añadido murcielago " << posx << ","  << posy  << endl;
        Murcielago * murcielago = new Murcielago(posx, posy);
        enemies[i] = (Enemigo *) murcielago;
    }else if(posicion[i][2] == 2){
        cout << "he añadido centinela" << endl;
        Centinela * centinela = new Centinela(posx, posy,1);
        enemies[i] = (Enemigo *) centinela;
    }else if(posicion[i][2] == 3){
        cout << "he añadido un centinela que se mueve"<< endl;
        Centinela* centinela = new Centinela(posx,posy,0);
        enemies[i] = (Enemigo *) centinela;
    }
    else if(posicion[i][2] == 4){
        cout << "he añadido reptante" << endl;
        Reptante * reptante = new Reptante(posx, posy);
        enemies[i] = (Enemigo *) reptante;
    }

  }
  
}

void Juego::disparar(float deltaTime){
  
        for(int i=0 ; i<maxBullets ; i++){
          if(bulletPlayer[i]==NULL && jugador->getCooldownDisparo()<=0 && jugador->getArma()==1){
            bulletPlayer[i]=new Bullet( jugador->getBody().getPosition().x , jugador->getBody().getPosition().y, (jugador->getBody().getScale().x > 0) );
            jugador->setCooldownDisparo(10*deltaTime);
            break;
          }
        }
    
}

void Juego::colisionBulletMundo(float deltaTime){
    mapa * mundo = mapa::instance(); 
    RectangleShape ** objetos = mundo->getObjetos();

  for(unsigned int i=0 ; i<maxBullets ; i++){
    for(unsigned int j=0 ; j<mundo->getNumObjetos(); j++){
      if(bulletPlayer[i]==NULL) continue;
      if(objetos[j]==NULL) continue;

      if(objetos[j]->getGlobalBounds().intersects( bulletPlayer[i]->getBody().getGlobalBounds() )){
        delete bulletPlayer[i];
        bulletPlayer[i]=NULL;
      }
    }
  }
}

void Juego::colisionBulletEnemigo(float deltaTime){
  for(unsigned int i=0 ; i<maxBullets ; i++){
    for(unsigned int j=0 ; j<numEmenigos ; j++){
      if(bulletPlayer[i]==NULL) continue;
      if(enemies[j]==NULL)      continue;

      if(enemies[j]->getCuerpo().getGlobalBounds().intersects( bulletPlayer[i]->getBody().getGlobalBounds() )){
          for (int index = j; index < numEmenigos; index++)
            enemies[index] = enemies[index+1];
          enemies[numEmenigos] = NULL;
          numEmenigos--;
      }
    }
  }
}

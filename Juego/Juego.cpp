#include "Juego.h"


Juego* Juego::pinstance = 0;

Juego::Juego(){
    mapa * mundo = mapa::instance(); 
    mundo->cargarmapa("MapaFinal.tmx");
    mundo->crearSprites();
    mundo->cargarObjectGroups();
    mundo->crearObjetos();
    jugador = new Player();
    if(jugador == nullptr) printf("asdasd");
    //crearObjetos();
    crearEnemigos();
}

Juego* Juego::instance(){

    if(pinstance == 0){

        pinstance = new Juego();

    }

    return(pinstance);
}

void Juego::update(float deltaTime){ //wip // UPDATE FUNCIONANDO 


    for(unsigned i = 0; i < (sizeof(bulletPlayer)/sizeof(*bulletPlayer));i++){

       bulletPlayer[i].update(deltaTime);

    }
    for(unsigned i = 0; i < (sizeof(bulletEnemies)/sizeof(*bulletEnemies));i++){

       bulletEnemies[i].update(deltaTime);

    }
    colisionPlayerMundo(deltaTime);
    
    jugador->update(deltaTime);
    RectangleShape rec = jugador->getBody();
    for(unsigned i = 0; i < (sizeof(enemies)/sizeof(*enemies));i++){

      //enemies[i]->update(rec, deltaTime); // POBAR QUE FUNCIONA ...

    }

}

void Juego::colisionPlayerMundo(float deltaTime){// ESTO LO HACE VERMIAAA !!!!! -> interseccion player y rectangleshape 
    
    mapa * mundo = mapa::instance(); 
    RectangleShape ** objetos = mundo->getObjetos();
    // for(unsigned int i=0 ; i<sizeof(objetos) ; i++){
    //     std::cout<< "objeto " << i << "= [" << objetos[i]->getPosition().x <<  ", " << objetos[i]->getPosition().y << "]" << endl;   
    // }
    bool pararse=false;
    for(unsigned int i=0 ; i<sizeof(objetos) ; i++){
      if(jugador->coliAbajo.intersects(objetos[i]->getGlobalBounds())){
        pararse=true;

      } 

      if(pararse){
        jugador->setSaltos( jugador->getPU_SaltoDoble() ? 2 : 1);
        jugador->setJumpSpeed(0);

      }else{
        jugador->setJumpSpeed( jugador->getJumpSpeed() + 9.81f*deltaTime);
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
    for(unsigned i = 0; i < (sizeof(bulletPlayer)/sizeof(*bulletPlayer));i++){

      bulletPlayer[i].render();

    }
    for(unsigned i = 0; i < (sizeof(bulletEnemies)/sizeof(*bulletEnemies));i++){

     bulletEnemies[i].render();

    }

    jugador->render();
    
    
    for(unsigned i = 0; i < (sizeof(enemies)/sizeof(*enemies));i++){

      enemies[i]->render(porcentaje);

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

//CREARENEMIGOS FUNCIONE

void Juego::crearEnemigos(){ 
  mapa * mundo = mapa::instance();

  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(1);
  enemies = new Enemigo *[posicion.size()]; 
  for(int i = 0; i < posicion.size();i++){
    float posx =  posicion[i][0];
    float posy =  posicion[i][1];
    if(posicion[i][2] == 1){
        cout << "he añadido murcielago" << endl;
        Murcielago * murcielago = new Murcielago(posx, posy);
        enemies[i] = (Enemigo *) murcielago;
    }else if(posicion[i][2] == 2){
        cout << "he añadido centinela" << endl;
        Centinela * centinela = new Centinela(posx, posy);
        enemies[i] = (Enemigo *) centinela;
    }else if(posicion[i][2] == 3){
        cout << "he añadido reptante" << endl;
        Reptante * reptante = new Reptante(posx, posy);
        enemies[i] = (Enemigo *) reptante;
    }

  }
  
}
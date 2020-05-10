#include "Juego.h"
#include "Manejador.h"
#include "../Menu/menu_inicial.h"

#include "../Menu/menu_pausa.h"

Juego* Juego::pinstance = 0;

Juego::Juego(){
    nivel = 0;
    inicializarNiveles();
    // cargarMusica();
    mundo = new Mundo();  
    mundo->cargarmapa(niveles[nivel].c_str());
    mundo->crearSprites();
    mundo->cargarObjectGroups();
    mundo->crearObjetos();
    mundo->cargarPosicionPlayer_Puerta(4);
    mundo->crearObstaculos();// Obstaculos
    mundo->crearMonedasLlaves();// Monedas y llaves
    vector<float> posP = mundo->cargarPosicionPlayer_Puerta(2);
    jugador = new Player(posP[0], posP[1]);
    crearObjetos();
    crearEnemigos();
    view.setSize(1080,720); 
    //view.setCenter(1080/2,720/2);
    view.setCenter(view.getSize().x/2,view.getSize().y/2);
    
  for(int i = 0 ; i < maxBullets ; i++){
       bulletPlayer[i]=NULL;
  }

  for(int i = 0; i < maxBullets;i++){
      bulletEnemies[i] = NULL;
  }

  for(int i = 0; i < maxBullets;i++){

      bulletNube[i] = NULL;

  }
  std::vector<sf::String> s; 
  s.push_back("SALTA");
  std::vector<Vector2f> pos;
  pos.push_back(Vector2f(10 , 1500));
}
Juego::~Juego(){
      if(jugador != nullptr){
        delete jugador;
        jugador = nullptr;
      }
      delete [] enemies;

      delete [] objetos;
      
      for(int i= 0; i < maxBullets; i++){
        if(bulletPlayer[i] != nullptr){
          delete bulletPlayer[i];
          bulletPlayer[i] = nullptr;
        }
        if(bulletEnemies[i] != nullptr){
          delete bulletEnemies[i];
          bulletEnemies[i] = nullptr;
        }
        if(bulletNube[i] != nullptr){
          delete bulletNube[i];
          bulletNube[i] = nullptr;
        }
      }
      if(so != nullptr){
        delete so;
        so = nullptr;
      }
      if(mundo != nullptr){
        delete mundo;
        mundo = nullptr;
      }
  
      delete[] niveles; 

}

Juego* Juego::instance(){

    if(pinstance == 0){

        pinstance = new Juego();

    }

    return(pinstance);
}

void Juego::update(float deltaTime){ //wip // UPDATE FUNCIONANDO 
  Motor * m = Motor::instance();
  hud * Hud = hud::instance();
  if(Hud->getVidas() == 0){
    matarJugador();
  }
  //std::cout << jugador->getBody()->getPosicion()[0] << ", " << jugador->getBody()->getPosicion()[1]<< std::endl; 
  pausa();
  vector<int> dimensiones = mundo->cargarPosicionBordes();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ //WIP FACHADA y LECTURA TECLADO
      disparar(deltaTime);
  }
  

  
    
    //el for de abajo, mejor en una función aparte, por claridad y organizacion
    for(unsigned i = 0; i < maxBullets ;i++){
      if(bulletPlayer[i] != NULL){
        

        if(bulletPlayer[i]->lifetime<=0){
          delete bulletPlayer[i];
          bulletPlayer[i]=NULL;
        }
        else
          bulletPlayer[i]->update(deltaTime);//revisar
      }
      if(bulletEnemies[i] != NULL){
        if(jugador->getPU_Slowhits()){
          bulletEnemies[i]->setVelocidad(300);
        } else bulletEnemies[i]->setVelocidad(600);
        if(bulletEnemies[i]->lifetime<=0){
          delete bulletEnemies[i];
          bulletEnemies[i] = NULL;
        }
        else
          bulletEnemies[i]->update(deltaTime);//revisar
      }
      if(bulletNube[i] != NULL){
        if(jugador->getPU_Slowhits()){
          bulletNube[i]->setVelocidad(300);
        } else bulletNube[i]->setVelocidad(600);
        if(bulletNube[i]->lifetime<=0){
          delete bulletNube[i];
          bulletNube[i] = NULL;
        }
        else
          bulletNube[i]->update(deltaTime);//revisar
      }
    }
    //puede que en alguna de estas funciones deltaTime NO sea necesario
    colisionPlayerMundo(deltaTime);
    colisionPlayerObstaculos(deltaTime);
    colisionBulletMundo();
    colisionBulletEnemigo();
    colisionBulletJugador();
    colisionMeleeEnemigo();
   // std::cout << deltaTime << std::endl;
    jugador->update(deltaTime , mundo); //revisar
    if(Keyboard::isKeyPressed(Keyboard::Num1)){
      if(Hud->getArma()[0] > 0){
        jugador->setArma(1);
      }
    }
    if(Keyboard::isKeyPressed(Keyboard::Num2)){
      if(Hud->getArma()[1] > 0){
        jugador->setArma(2);
      }
    }
    
    int j = 0;
    while(objetos[j] != nullptr && j < numObjetos){ //WIP FACHADA y LECTURA TECLADO y FUNCION APARTE (probablemente rehacer entero)
     
       //if( objetos[j]->getBody().getGlobalBounds().intersects(jugador->getBody().getGlobalBounds())) std::cout << objetos[j]->getTipo()<< std::endl;
      if( sf::Keyboard::isKeyPressed(sf::Keyboard::E) && 
      objetos[j]->getBody()->getGlobalBounds()->getIntersect(*jugador->getBody()->getGlobalBounds())){

            switch (objetos[j]->getTipo()){ //este switch en una funcion aparte, pero está bien
                case 0:
                    //jugador->obtenerPU_Velocidad();
                    Hud->setVelocidad(true);
                    Hud->setIVelocidad(350);
                    destruirObjetos(objetos[j]);
                    break;
                case 1:
                     jugador->setArma(1);
                     if(Hud->getArma()[0] == 0){
                      Hud->setArma(0,1);
                     }
                     destruirObjetos(objetos[j]);
                    break;

                case 2:
                    //jugador->obtenerPU_SaltoDoble();
                    Hud->setDobleSalto(true);
                    destruirObjetos(objetos[j]);
                    break;

                case 3:
                    //jugador->obtenerPU_Slowhits();
                    Hud->setSlow(true);
                    destruirObjetos(objetos[j]);
                    break;
                case 4: 
                    destruirObjetos(objetos[j]);
                    break;
            default:
                std:: cout <<"Default" << std::endl;
                break;
            } 

        }
      j++;
    }

    j = mundo->getNumMonedasLlaves() - 1 ;
    //cout << j << endl;
    while(mundo->getMonedasLlaves()[j] != nullptr && j >= 0){ //WIP FACHADA y LECTURA TECLADO y FUNCION APARTE (probablemente rehacer entero)
    
      if(mundo->getMonedasLlaves()[j]->getGlobalBounds()->getIntersect(*jugador->getBody()->getGlobalBounds())){

            switch (mundo->getMonedasLlaves()[j]->getTipo()){ //este switch en una funcion aparte, pero está bien
                case 0:
                    // jugador->sumarMonedas();
                    Hud->sumarMonedas();
                    mundo->EliminarMonedasLLaves(mundo->getMonedasLlaves()[j]);
                    break;
                case 1:
                    jugador->cogerLlave(1);
                    mundo->EliminarMonedasLLaves(mundo->getMonedasLlaves()[j]);// esto es la llave
                    mundo->EliminarMonedasLLaves(mundo->getMonedasLlaves()[j]);// esto es la puerta
                    break;
                default:
                    cout <<"Default" << endl;
                break;
            } 

        }
      j--;
    }
    
 
    float playerPosX = jugador->getBody()->getPosicion()[0];
    float playerPosY = jugador->getBody()->getPosicion()[1];

    view.setCenter(playerPosX,playerPosY); //WIP fachada
    ///////////////Esta zona es WIP fachada y funcion diferente
    if( playerPosX < view.getSize().x/2) {
      view.setCenter(view.getSize().x/2, playerPosY);
    }
    if( playerPosY > dimensiones[1]-view.getSize().y/2){
      view.setCenter(view.getCenter().x, dimensiones[1]-view.getSize().y/2);
    }
    if( playerPosX>dimensiones[3]-view.getSize().x/2) {
      view.setCenter(dimensiones[3]-view.getSize().x/2, view.getCenter().y);
    }
    if( playerPosY < view.getSize().y/2){
      view.setCenter(view.getCenter().x, view.getSize().y/2);
    }
    //////////////////

    m->getVentana()->setView(view); //wIP fachada
    Hud->setMarcador( view.getCenter().x , view.getCenter().y);
    for(int i = 0; i < numEmenigos; i++){
      if(enemies[i]==NULL) continue;
      enemies[i]->update(jugador , deltaTime);
      enemies[i]->updateHitbox(); //dentro de update de enemigo
      if(enemies[i]->muerto){ //dentro de update de enemigo
        matarEnemigo(enemies[i]);
      }
   
      //esto del casteo está bien hecho, pero en una funcion aparte
      if(enemies[i] != nullptr){
        Centinela* casteadoCent = dynamic_cast<Centinela*>(enemies[i]);
        Nube* casteadoNube = dynamic_cast<Nube*>(enemies[i]); 
      
        if(casteadoCent != nullptr){

          if(casteadoCent->getShoot()){

            for(int j = 0; j < maxBullets;j++){

              if(bulletEnemies[j] == NULL)
                bulletEnemies[j] = casteadoCent->disparar();

            }

          }

        }  

        if(casteadoNube != nullptr){

          if(casteadoNube->getShoot()){

            for(int j = 0; j < maxBullets;j++){

              if(bulletNube[j] == NULL)
                bulletNube[j] = casteadoCent->disparar();

            }

          }

        }
      }      
    }
    jugador->updateHitbox(); //dentro de update de jugador
    
    comprobarPasarNivel();

}

void Juego::colisionPlayerMundo(float deltaTime){//WIP FACHADA (a lo mejor esta funcion debería estar dentro de player.cpp)
    
    hud * Hud = hud::instance();
    Cuerpo ** objetos = mundo->getObjetos();//WIP FACHADA
    
    float posobjX;
    float posobjY; //WIP FACHADA
    bool pararse=false;
    bool aux = false;
    float posantX; //WIP FACHADA
    float posantY;
    for(int i=0 ; i<  mundo->getNumObjetos(); i++){
      if(jugador->getColiAbajo()->getIntersect(*objetos[i]->getGlobalBounds())){//WIP FACHADA
        posobjX = objetos[i]->getPosicion()[0];
        posobjY = objetos[i]->getPosicion()[1];
        pararse=true;
      } 
      
      if(pararse){
        //jugador->setSaltos( jugador->getPU_SaltoDoble() ? 2 : 1);
        jugador->setSaltos( Hud->getDoblesalto() ? 2 : 1);
        if(aux == false){
          jugador->getBody()->posicionamiento(jugador->getBody()->getPosicion()[0],posobjY - jugador->getBody()->getOriginY() - jugador->getColiAbajo()->getHeight() + 5); //WIP FACHADA y explicar que hace esto detalladamente pls
          jugador->updateHitbox(); //updateHitbox debería llamarse dentro de jugador setPosicion
          aux = true;
          posantX = jugador->getBody()->getPosicion()[0];
          posantY = jugador->getBody()->getPosicion()[1]; //WIP FACHADA
          
        } else if(posantX != jugador->getBody()->getPosicion()[0] && posantY != jugador->getBody()->getPosicion()[1]){ //WIP FACHADA
          aux = false;
        }
        jugador->setJumpSpeed(0);

      }else{
        //std::cout<< jugador->getJumpSpeed() + 9.81f*6*deltaTime << std::endl;
        jugador->setJumpSpeed( jugador->getJumpSpeed() + 9.81f*4*deltaTime);
      }
      if(jugador->getColiArriba()->getIntersect(*objetos[i]->getGlobalBounds())){ //WIP fachada
        jugador->setJumpSpeed(10);
      }
    }
}

void Juego::colisionPlayerObstaculos(float deltaTime){
    Cuerpo ** objetos = mundo->getObstaculos();
    hud * Hud = hud::instance();

    bool morir = false;
    timerObstaculos -= deltaTime;
    for(int i=0 ; i<  mundo->getNumObstaculos(); i++){
      if(objetos[i]!= nullptr)
      if(jugador->getColiAbajo()->getIntersect(*objetos[i]->getGlobalBounds())){
        if(objetos[i]->getTipo() == 1 && timerObstaculos <= 0){//pierde una vida
          if(jugador->getModoDios() == false){
            //morir = jugador->setVidas(jugador->getVidas()-1);
            morir = Hud->restarVidas();
            if(morir == true){
              matarJugador();
            }
          }
          //jugador->setSaltos( jugador->getPU_SaltoDoble() ? 2 : 1);
          jugador->setSaltos( Hud->getDoblesalto() ? 2 : 1);
          jugador->saltar(); 
       
          timerObstaculos = 1;
        }else if(objetos[i]->getTipo() == 2){//muere
          if(jugador->getModoDios() == false){
            matarJugador();
          }
        }
      } 
    }
}

void Juego::colisionMeleeEnemigo(){
    Rectangulo melee = jugador->getMelee();
    hud * Hud = hud::instance();
    if(jugador->getAtacandoMelee() > 0){
      for(int i=0 ; i<numEmenigos; i++){
        if(enemies[i]==NULL) continue;
        if(enemies[i]->getCuerpo()==NULL) continue;
        if( enemies[i]->getCuerpo()->getGlobalBounds()->getIntersect(melee) ){
          enemies[i]->restarVida(1);
          
          if(enemies[i]->muerto == true){
            matarEnemigo(enemies[i]);
            Hud->sumarPuntos(50);
          }
        }
      }
    }
    
}

void Juego::render(float porcentaje){ //WIP INTERPOLACION (¿y el render de player?)


    hud * Hud = hud::instance();
    mundo->render();
    for(unsigned i = 0; i < maxBullets;i++){
      if(bulletPlayer[i]==NULL) continue;
      bulletPlayer[i]->render(porcentaje); //interpolacion

    }

    
    
    for(unsigned i = 0; i < maxBullets;i++){

      
      if(bulletNube[i] != nullptr){bulletNube[i]->render(porcentaje);} //interpolacion
    }

    jugador->render(porcentaje);
    
    int i = 0;
    int j = 0;
    while(enemies[i] != nullptr && i < numEmenigos){
      enemies[i]->render(porcentaje);//esto está interpolado
      i++;
    }

    while(objetos[j] != nullptr && j < numObjetos){
     
      objetos[j]->render(porcentaje);
      j++;
    }
    
    j=0;
    while(mundo->getMonedasLlaves()[j] != nullptr && j < mundo->getNumMonedasLlaves()){
      mundo->getMonedasLlaves()[j]->render(porcentaje);
      j++;
    }

    mundo->render2();
    Hud->render();
    for(unsigned i = 0; i < maxBullets;i++){
      if(bulletEnemies[i] != nullptr){bulletEnemies[i]->render(porcentaje);} //interpolacion
    }
}


void Juego::crearObjetos(){ //WIP FACHADA
 
  
 
  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(3);
  //cout<< "POSICION DE LOS OBJETOS = " << posicion.size() <<endl;
  
  numObjetos = posicion.size();
  objetos = new Objeto *[posicion.size()]; 

  for(unsigned i = 0; i < posicion.size();i++){
    Objeto *objeto1 = new Objeto(posicion[i][0],posicion[i][1] ,posicion[i][2] );
    objetos[i] =  objeto1;
  }
}

void Juego::destruirObjetos(Objeto* enem){ //está nice
 for (int i = 0; i < numObjetos; i++){
    if(objetos[i] == enem){
      for(int j = i; j < numObjetos; j++){
        objetos[j] = objetos[j+1];        
      }
      objetos[numObjetos] = NULL;
      numObjetos--;
    }
  }

}


void Juego::crearEnemigos(){ //está nice

  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(1);
  numEmenigos = posicion.size();
  enemies = new Enemigo *[posicion.size()]; 
  for(unsigned i = 0; i < posicion.size();i++){
    float posx =  posicion[i][0];
    float posy =  posicion[i][1];
    if(posicion[i][2] == 1){
        Murcielago * murcielago = new Murcielago(posx, posy);
        enemies[i] = (Enemigo *) murcielago;
    }else if(posicion[i][2] == 2){
        Centinela * centinela = new Centinela(posx, posy,1);
        enemies[i] = (Enemigo *) centinela;
    }else if(posicion[i][2] == 3){
        Centinela* centinela = new Centinela(posx,posy,0);
        enemies[i] = (Enemigo *) centinela;
    }
    else if(posicion[i][2] == 4){
        Pajaro * pajaro = new Pajaro(posx, posy);
        enemies[i] = (Enemigo *) pajaro;
    }

  }
  
}

void Juego::matarEnemigo(Enemigo* enem){ //está nice
  hud * Hud = hud::instance();
  for (int i = 0; i < numEmenigos; i++){
    if(enemies[i] == enem){
      for(int j = i; j < numEmenigos; j++){
        if(j+1 < numEmenigos){
          enemies[j] = enemies[j+1]; 
        }       
      }
      enemies[numEmenigos] = NULL;
      numEmenigos--;
    }
  }
}

void Juego::matarJugador(){ //está nice
  hud * Hud = hud::instance();
  nivel = 0;
  delete mundo;
  mundo = new Mundo();
  mundo->cargarmapa(niveles[nivel].c_str());
  mundo->crearSprites();
  mundo->cargarObjectGroups();
  mundo->crearObjetos();
  mundo->cargarPosicionPlayer_Puerta(4);
  mundo->crearObstaculos();
  mundo->crearMonedasLlaves();
  vector<float> posP = mundo->cargarPosicionPlayer_Puerta(2);
  jugador = new Player(posP[0], posP[1]);
  Hud->setDobleSalto(false);
  Hud->setVelocidad(false);
  Hud->setIVelocidad(250);
  Hud->setSlow(false);
  Hud->restablecerVidas();
  Hud->reiniciarTiempo();
  if(jugador->getBody()->getPosicion()[1]<0){
    jugador->getBody()->posicionamiento(posP[0], posP[1]);
  }
  crearObjetos();
  crearEnemigos();
  view.setSize(1024,720);
    
  for(int i = 0 ; i < maxBullets ; i++){
       bulletPlayer[i]=NULL;
  }

  for(int i = 0; i < maxBullets;i++){

      bulletEnemies[i] = NULL;

  }
  for(int i = 0; i < maxBullets;i++){

      bulletNube[i] = NULL;

  }

}


void Juego::disparar(float deltaTime){ 
  hud * Hud = hud::instance();
  for(int i=0 ; i<maxBullets ; i++){
    if(bulletPlayer[i]==NULL && jugador->getCooldownDisparo()<=0 ){
      if(jugador->getArma() == 1){
          bulletPlayer[i]=new Bullet( jugador->getBody()->getPosicion()[0] , jugador->getBody()->getPosicion()[1], jugador->getFacing() , 1 , 0);
          jugador->setCooldownDisparo(1);
          break;
      }
      if(jugador->getArma() == 2){
          bulletPlayer[i]=new Bullet( jugador->getBody()->getPosicion()[0] , jugador->getBody()->getPosicion()[1], jugador->getFacing() , 1 , 0);
          jugador->setCooldownDisparo(0.2);
          break;
      }
       

    }
  }
    
}


void Juego::colisionBulletMundo(){//WIP fachada
    Cuerpo ** objetos = mundo->getObjetos(); // esto tiene que cambiar para que vaya la linea de abajo

  for(unsigned int i=0 ; i<maxBullets ; i++){
    for(int j=0 ; j<mundo->getNumObjetos(); j++){
      if(bulletPlayer[i]==NULL) continue;
      if(objetos[j]==NULL) continue;

      if(objetos[j]->getGlobalBounds()->getIntersect(*bulletPlayer[i]->getBody()->getGlobalBounds())){
        delete bulletPlayer[i];
        bulletPlayer[i]=NULL;
      }
    }
  }
}

void Juego::colisionBulletJugador(){ //WIP fachada
  hud * Hud = hud::instance();
  bool morir = false;
  for(unsigned int i = 0; i < maxBullets; i++){

    if(bulletEnemies[i] != NULL){

      if(jugador->getBody()->getGlobalBounds()->getIntersect(*bulletEnemies[i]->getBody()->getGlobalBounds())){

       //morir = jugador->setVidas(jugador->getVidas()-1);
        morir = Hud->restarVidas();
        //std::cout << "Vidas del jugador: " << jugador->getVidas() << "\n";
        delete bulletEnemies[i];
        bulletEnemies[i] = NULL;
        if(morir == true){
          matarJugador();
        }
      }
    }

    if(bulletNube[i] != NULL){

      if(jugador->getHitbox()->getIntersect(*bulletNube[i]->getHitbox())){

        //morir = jugador->setVidas(jugador->getVidas()-1);
        morir = Hud->restarVidas();
        //std::cout << "Vidas del jugador: " << jugador->getVidas() << "\n";
        delete bulletNube[i];
        bulletNube[i] = NULL;
        if(morir == true){
          matarJugador();
        }
      }
    }

  }
  
}

void Juego::colisionBulletEnemigo(){
  hud * Hud = hud::instance();
  for(unsigned int i=0 ; i < maxBullets ; i++){
    for(int j=0 ; j<numEmenigos ; j++){
      if(bulletPlayer[i]==NULL) continue;
      if(enemies[j]==NULL)      continue;

      if(enemies[j]->getCuerpo()->getGlobalBounds()->getIntersect( *bulletPlayer[i]->getHitbox() )){
        delete bulletPlayer[i];
        bulletPlayer[i]=NULL;
        
        if(jugador->getArma()-1 >= 0){
          enemies[j]->restarVida(Hud->getArma()[jugador->getArma()-1]);
        }
        
        if(enemies[j]->muerto == true){
          for (int index = j; index < numEmenigos; index++){
            enemies[index] = enemies[index+1];
          }
          enemies[numEmenigos] = NULL;
          numEmenigos--;
          Hud->sumarPuntos(50);
        }

      }
    }
  }
}


void Juego::cargarMusica(){
    sf::String ss = "resources/Sonidos/si-veo2.ogg";
    so = new musica(ss);
    so->reproducirMusica();
}

void Juego::comprobarPasarNivel(){
 if( mundo->getPuerta()->getGlobalBounds()->getIntersect(*jugador->getBody()->getGlobalBounds())){
   nextLevel(-1);
 }
}

void Juego::nextLevel(int n){
    if(n == -1){nivel++;} else nivel = n;
    delete mundo;
    hud * Hud = hud::instance();
    mundo = new Mundo();
    mundo->cargarmapa(niveles[nivel].c_str());
    mundo->crearSprites();
    mundo->cargarObjectGroups();
    mundo->crearObjetos();
    mundo->cargarPosicionPlayer_Puerta(4);//Puerta
    mundo->crearObstaculos();
    mundo->crearMonedasLlaves();
    vector<float> posP = mundo->cargarPosicionPlayer_Puerta(2);//Player
    jugador->getBody()->posicionamiento(posP[0], posP[1]);
    if(nivel % 4 == 0){
        Hud->setDobleSalto(false);
        Hud->setVelocidad(false);
        Hud->setIVelocidad(250);
        Hud->setSlow(false);
    }
    Hud->reiniciarTiempo();
    crearObjetos();
    crearEnemigos();
    view.setSize(1024,720);
      
    for(int i = 0 ; i < maxBullets ; i++){
        bulletPlayer[i]=NULL;
    }

    for(int i = 0; i < maxBullets;i++){
        bulletEnemies[i] = NULL;
    }

    for(int i = 0; i < maxBullets;i++){
        bulletNube[i] = NULL;
    }
}


void Juego::inicializarNiveles(){
  
  niveles = new string[maxniveles];
  niveles[0] = "Mundo1-1.tmx";
  niveles[1] = "Mundo1-2.tmx";
  niveles[2] = "Mundo1-3.tmx";
  niveles[3] = "Mundo1-4.tmx";
  niveles[4] = "Mundo3-1.tmx";
  niveles[5] = "Mundo3-2.tmx";
}
void Juego::nivelSeleccionado(string n){
  int aux = -1;
    for(int i = 0; i < maxniveles; i++){
      if(niveles[i].compare(n) == 0){
       
        aux = i;
        break;
      }
    }
    nextLevel(aux);
}

void Juego::pausa(){
  Manejador* man = Manejador::instancia();
  menu_pausa* menuPau = menu_pausa::instance();
  if( sf::Keyboard::isKeyPressed( sf::Keyboard::P )){
  man->cambiarEstado(menuPau);
  }
    
}
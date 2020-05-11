#include "Tutorial.h"

sf::Font* Tutorial::font = new Font();

Tutorial::Tutorial() : menu(*font, 3){
    mundo = new Mundo();
    mundo->cargarmapa("tutorial.tmx");
    mundo->crearSprites();
    mundo->cargarObjectGroups();
    mundo->crearObjetos();
    mundo->cargarPosicionPlayer_Puerta(4);
    mundo->crearObstaculos();
    mundo->crearMonedasLlaves();
    vector<float> posP = mundo->cargarPosicionPlayer_Puerta(2);
    jugador = new Player(posP[0], posP[1]);
    crearObjetos();
    crearEnemigos();
    view.setSize(1080,720); 
    view.setCenter(view.getSize().x/2,view.getSize().y/2);

    for(int i = 0 ; i < maxBullets ; i++){
       bulletPlayer[i]=NULL;
    }

    for(int i = 0; i < maxBullets;i++){
        bulletEnemies[i] = NULL;
    }

    texto = new Text[3];//max 3

    font = new Font[1];
    font->loadFromFile("resources/fuentes/PixelBug.otf");
    titulo = "Hola, bienvenido";
    mensaje = "Pulsa las teclas Izquierda y Derecha para moverte.";

    cambiarTexto(*font, 0, Color::White, titulo, Vector2f(0.8, 0.8), posP[0] - 150, posP[1] - 200);
    cambiarTexto(*font, 1, Color::White, mensaje, Vector2f(0.8, 0.8), posP[0]-150, posP[1]-150);
    estado = 'm';
}


void Tutorial::update(float deltaTime){
    Motor * m = Motor::instance();
    hud * Hud = hud::instance();

    vector<int> dimensiones = mundo->cargarPosicionBordes();

    vector<float> posP = jugador->getBody()->getPosicion();
        
    cambiarTexto(*font, 0, Color::White, titulo, Vector2f(0.8, 0.8), posP[0] - 150, posP[1] - 200);
    cambiarTexto(*font, 1, Color::White, mensaje, Vector2f(0.8, 0.8), posP[0]-150, posP[1]-150);


    if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && estado == 'm'){
        estado  = 's';
        
        titulo = "SALTA";
        mensaje = "Pulsa la tecla UP para saltar.";
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && estado == 's'){
        estado  = 'b';

        titulo = "RECOGER MONEDAS";
        mensaje = "Para recoger una moneda pasa por encima";
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ){ 
        disparar(deltaTime);
    }
    

    for(unsigned i = 0; i < maxBullets ;i++){
        if(bulletPlayer[i] != NULL){        
            if(bulletPlayer[i]->lifetime<=0){
                delete bulletPlayer[i];
                bulletPlayer[i]=NULL;
            }
            else
                bulletPlayer[i]->update(deltaTime);
        }

        if(bulletEnemies[i] != NULL){
            
            if(jugador->getPU_Slowhits()){
                bulletEnemies[i]->setVelocidad(300);
            } 
            else 
                bulletEnemies[i]->setVelocidad(600);

            if(bulletEnemies[i]->lifetime<=0){
                delete bulletEnemies[i];
                bulletEnemies[i] = NULL;
            }
            else
                bulletEnemies[i]->update(deltaTime);
        }
     
    }

    colisionPlayerMundo(deltaTime);
    colisionBulletMundo();
    colisionBulletEnemigo();
    colisionMeleeEnemigo();

    jugador->update(deltaTime , mundo);

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
    while(objetos[j] != nullptr && j < numObjetos){
        vector<float> posP = jugador->getBody()->getPosicion();
        
        if( sf::Keyboard::isKeyPressed(sf::Keyboard::E) && 
            objetos[j]->getBody()->getGlobalBounds()->getIntersect(*jugador->getBody()->getGlobalBounds())){
            

            switch (objetos[j]->getTipo()){ 
                case 0:
                    Hud->setVelocidad(true);
                    Hud->setIVelocidad(350);
                    destruirObjetos(objetos[j]);
                    break;
                case 1:
                    if(estado == 'r'){
                        estado = 'd';
                        titulo = "DISPARAR";
                        mensaje = "Busca un enemigo y pulsa SPACE para disparar.";
                    }
                     jugador->setArma(1);
                     if(Hud->getArma()[0] == 0){
                        Hud->setArma(0,1);
                     }
                     destruirObjetos(objetos[j]);
                    break;

                case 2:
                    Hud->setDobleSalto(true);
                    destruirObjetos(objetos[j]);
                    break;

                case 3:
                    Hud->setSlow(true);
                    destruirObjetos(objetos[j]);
                    break;
                case 4: 
                    destruirObjetos(objetos[j]);
                    break;
            default:
                break;
            } 

        }
      j++;
    }

    j = mundo->getNumMonedasLlaves() - 1 ;
    while(mundo->getMonedasLlaves()[j] != nullptr && j >= 0){
      if(mundo->getMonedasLlaves()[j]->getGlobalBounds()->getIntersect(*jugador->getBody()->getGlobalBounds())){
            if(estado == 'b'){
                estado = 'r';
                titulo = "RECOGER POWERUP";
                mensaje = "Situate sobre el y pulsa la E para recogerlo";
            }

            switch (mundo->getMonedasLlaves()[j]->getTipo()){ 
                case 0:
                    Hud->sumarMonedas();
                    mundo->EliminarMonedasLLaves(mundo->getMonedasLlaves()[j]);
                    break;
                case 1:
                    jugador->cogerLlave(1);
                    mundo->EliminarMonedasLLaves(mundo->getMonedasLlaves()[j]);
                    mundo->EliminarMonedasLLaves(mundo->getMonedasLlaves()[j]);
                    break;
                default:
                    
                break;
            } 

        }
      j--;
    }

    float playerPosX = jugador->getBody()->getPosicion()[0];
    float playerPosY = jugador->getBody()->getPosicion()[1];

    view.setCenter(playerPosX,playerPosY);
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
  
    m->getVentana()->setView(view); 
    Hud->setMarcador( view.getCenter().x , view.getCenter().y);
    
    if(enemigo!=NULL){
        enemigo->update(jugador , deltaTime);
        enemigo->updateHitbox(); 
        if(enemigo->muerto){ 
            matarEnemigo();
        }

      if(enemigo != nullptr){
        Centinela* casteadoCent = dynamic_cast<Centinela*>(enemigo);      
        if(casteadoCent != nullptr){
          if(casteadoCent->getShoot()){
            for(int j = 0; j < maxBullets;j++){
              if(bulletEnemies[j] == NULL)
                bulletEnemies[j] = casteadoCent->disparar();
            }
          }
        }  
      }      
    }
    jugador->updateHitbox(); //dentro de update de jugador

    terminar();
}

void Tutorial::colisionPlayerMundo(float deltaTime){
    hud * Hud = hud::instance();
    Cuerpo ** objetos = mundo->getObjetos();
  
    float posobjY;
    bool pararse=false;
    bool aux = false;

      for(int i=0 ; i<  mundo->getNumObjetos(); i++){
        if(jugador->getColiAbajo()->getIntersect(*objetos[i]->getGlobalBounds())){
          posobjY = objetos[i]->getPosicion()[1];
          jugador->suelo(
            jugador->getBody()->getPosicion()[0],
            posobjY - jugador->getBody()->getOriginY() - jugador->getColiAbajo()->getHeight() + 5
          );
          pararse=true;
          i = mundo->getNumObjetos(); 
          jugador->setSaltos( Hud->getDoblesalto() ? 2 : 1);
        } 
        
        if(!pararse){

          jugador->caer();
          if(jugador->getColiArriba()->getIntersect(*objetos[i]->getGlobalBounds())){ 
            jugador->setJumpSpeed(0);
          }
        }
    }
}



void Tutorial::colisionMeleeEnemigo(){
    Rectangulo melee = jugador->getMelee();
    hud * Hud = hud::instance();
    if(jugador->getAtacandoMelee() > 0){
        
        if(enemigo != NULL && enemigo->getCuerpo()!= NULL){
            if( enemigo->getCuerpo()->getGlobalBounds()->getIntersect(melee) ){
                enemigo->restarVida(1);            
                if(enemigo->muerto == true){
                    matarEnemigo();
                    Hud->sumarPuntos(50);
                }
            }
        }
    }
    
}

void Tutorial::render(float porcentaje){ //WIP INTERPOLACION (¿y el render de player?)
 
    hud * Hud = hud::instance();
    mundo->render();
    for(unsigned i = 0; i < maxBullets;i++){
      if(bulletPlayer[i]==NULL) continue;
        bulletPlayer[i]->render(porcentaje); //interpolacion
    }

    jugador->render(porcentaje);
    
    if(enemigo != NULL){
        enemigo->render(porcentaje);
    }
    
    int j = 0;
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
        if(bulletEnemies[i] != nullptr){bulletEnemies[i]->render(porcentaje);} //interpolacion centinelas
    }

    Motor * motor = Motor::instance();
    if(dialogo !=NULL)
        dialogo->render();
    
    for(int i = 0; i < 3; i++){
        motor->dibujo(texto[i]);
    }
}


void Tutorial::crearObjetos(){

  vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(3);
  
  numObjetos = posicion.size();
  objetos = new Objeto *[posicion.size()]; 

  for(unsigned i = 0; i < posicion.size();i++){
    Objeto *objeto1 = new Objeto(posicion[i][0],posicion[i][1] ,posicion[i][2] );
    objetos[i] =  objeto1;
  }
}

void Tutorial::crearEnemigos(){ //está nice

    vector<vector<int>>  posicion= mundo->cargarPosicionEnemigos_PowerUps(1);
    float posx =  posicion[0][0];
    float posy =  posicion[0][1];
    if(posicion[0][2] == 2){
        Centinela * centinela = new Centinela(posx, posy,1);
        enemigo = (Enemigo *) centinela;
    }  
}

void Tutorial::destruirObjetos(Objeto* enem){ //está nice
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

void Tutorial::matarEnemigo(){ //está nice
    enemigo = NULL;
    if(estado == 'd'){
        titulo = "PASAR AL SIGUIENTE NIVEL";
        mensaje = "Busca la puerta para pasar al siguiente nivel";
        estado = 'f';
    }
}

void Tutorial::disparar(float deltaTime){ 
  
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

void Tutorial::colisionBulletMundo(){
    Cuerpo ** objetos = mundo->getObjetos();

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

void Tutorial::colisionBulletEnemigo(){
  bool morir = false;
  
    for(unsigned int i=0 ; i < maxBullets ; i++){
            
        if(bulletPlayer[i] != NULL && enemigo != NULL){
            if(enemigo->getCuerpo()->getGlobalBounds()->getIntersect( *bulletPlayer[i]->getHitbox() )){
                delete bulletPlayer[i];
                bulletPlayer[i]=NULL;
                matarEnemigo();
            }
        }
    }
}

void Tutorial::terminar(){
    if( mundo->getPuerta()->getGlobalBounds()->getIntersect(*jugador->getBody()->getGlobalBounds())){
        Manejador* man = Manejador::instancia();
        man->back();
    }
}


void Tutorial::cambiarTexto(const Font &f , int i, Color c, string s , Vector2f v, int posx , int posy){

    texto[i].setFont(f);
    texto[i].setColor(c);
    texto[i].setString(s);
    texto[i].setScale(v);
    texto[i].setPosition(posx , posy);
    vector<float> pos = jugador->getBody()->getPosicion();
    dialogo = new Cuerpo(pos[0] , pos[1] - 80, 350,250,"madera.png",1, 0,-1);
    dialogo->recorte(25,25);
    dialogo->setSize(700, 100);

}





Tutorial::~Tutorial(){
    if(jugador != nullptr){
        delete jugador;
        jugador = nullptr;
    }
    
    if(enemigo != nullptr){
        delete enemigo;
        enemigo = nullptr;
    }

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
    }
    
    if(mundo != nullptr){
        delete mundo;
        mundo = nullptr;
    }

    if(dialogo != nullptr)
        delete dialogo;
    dialogo = nullptr;
    
    if(texto != nullptr){
        delete texto;
        texto = nullptr;
    }
    if(font != nullptr){
        delete font;
        font = nullptr;
    }
}
#include "Tienda.h"

Tienda* Tienda::p_instance = 0;


Tienda* Tienda::instance(){
    if(p_instance == 0){
        p_instance = new Tienda(8, 9);
    }
    return(p_instance);
}

Tienda::Tienda(int i, int max){
    numOpciones = max;
    maxTienda = i;
    itemSeleccionado = -1;
    sprites = new Cuerpo *[i];
    monedas = new Cuerpo *[i];

    sprites[0] = new Cuerpo(300 , 100,300,300,"ObjetosTienda.png",1, 0,2);
    sprites[0]->Scalar(0.2, 0.2);
    sprites[1] = new Cuerpo(300 , 200,300,300,"ObjetosTienda.png",1, 0,10);
    sprites[1]->recorte(0,300);
    sprites[1]->Scalar(0.2, 0.2);
    sprites[2] = new Cuerpo(300 , 400,300,300,"ObjetosTienda.png",1, 0,10);
    sprites[2]->recorte(0,600);
    sprites[2]->Scalar(0.2, 0.2);
    sprites[3] = new Cuerpo(300, 500,300,300,"ObjetosTienda.png",1, 0,10);
    sprites[3]->recorte(0,900);
    sprites[3]->Scalar(0.2, 0.2);
    sprites[4] = new Cuerpo(600, 100,300,300,"ObjetosTienda.png",1, 0,50);
    sprites[4]->recorte(0,1200);
    sprites[4]->Scalar(0.2, 0.2);
    sprites[5] = new Cuerpo(600, 200,300,300,"ObjetosTienda.png",1, 0,5);
    sprites[5]->recorte(0,1500);
    sprites[5]->Scalar(0.2, 0.2);
    sprites[6] = new Cuerpo(600, 300,300,300,"ObjetosTienda.png",1, 0,15);
    sprites[6]->recorte(0,1800);
    sprites[6]->Scalar(0.2, 0.2);
    sprites[7] = new Cuerpo(600, 400,300,300,"ObjetosTienda.png",1, 0,30);
    sprites[7]->recorte(0,2100);
    sprites[7]->Scalar(0.2, 0.2);

    
   

    for(int j = 0; j < maxTienda; j++){
        monedas[j] = new Cuerpo(300,  100,100,100,"Moneda.png",1, 0,-1);
        monedas[j]->Scalar(0.2, 0.2);
    }
    font = new Font[1];

    texto = new Text[max];
    precios = new Text[i];
    aviso = new Text[1];
    font->loadFromFile("resources/fuentes/PixelBug.otf");

    
    cambiarTexto(0, "P1" , 0 , 0);
    cambiarTexto(1, "P2" , 0 , 100);
    cambiarTexto(2, "P3" , 0 , 200);
    cambiarTexto(3, "P4" , 0 , 300);
    cambiarTexto(4, "P5" , 0 , 0);
    cambiarTexto(5, "P6" , 0 , 100);
    cambiarTexto(6, "P7" , 0 , 200);
    cambiarTexto(7, "P8" , 0 , 300);
    cambiarTexto(8, "Back" , 256 , 640);

    cambiarPrecios(0, to_string(sprites[0]->getTipo()) , 0 , 0);
    cambiarPrecios(1, to_string(sprites[1]->getTipo()) , 0 , 100);
    cambiarPrecios(2, to_string(sprites[2]->getTipo()) , 0 , 200);
    cambiarPrecios(3, to_string(sprites[3]->getTipo()) , 0 , 300);
    cambiarPrecios(4, to_string(sprites[4]->getTipo()) , 0 , 0);
    cambiarPrecios(5, to_string(sprites[5]->getTipo()) , 0 , 100);
    cambiarPrecios(6, to_string(sprites[6]->getTipo()) , 0 , 200);
    cambiarPrecios(7, to_string(sprites[7]->getTipo()) , 0 , 300);

    cambiarAviso(0,"", 100 , 640);
  
    t = new Textura("resources/Imagenes/MenuTienda.png");
    b = new Bloque(t);
}

void Tienda::moveUp(){
    if(selectedItem - 1 >= 0 ){
        texto[selectedItem].setColor(Color::White);
        if(selectedItem < 4){
        sprites[selectedItem]->recorte(0,300*(selectedItem));
        }
        selectedItem--;
        texto[selectedItem].setColor(Color::Red);
        if(selectedItem <4){
        sprites[selectedItem]->recorte(300,300*(selectedItem));
        }
    }else if(selectedItem - 1 < 0){
        texto[selectedItem].setColor(Color::White);
        if(selectedItem < 4){
        sprites[selectedItem]->recorte(0,300*(selectedItem));
        }
        selectedItem = numOpciones-1;
        texto[selectedItem].setColor(Color::Red);
        if(selectedItem <4){
        sprites[selectedItem]->recorte(300,300*(selectedItem));
        }
    }
}

void Tienda::moveDown(){
    if(selectedItem + 1 < numOpciones ){
        texto[selectedItem].setColor(Color::White);
        if(selectedItem < 4){
        sprites[selectedItem]->recorte(0,300*(selectedItem));
        }
        selectedItem++;
        texto[selectedItem].setColor(Color::Red);
        if(selectedItem < 4 ){
        sprites[selectedItem]->recorte(300,300*(selectedItem));
        }
    }else if(selectedItem + 1 >= numOpciones){
        texto[selectedItem].setColor(Color::White);
        if(selectedItem < 4){
        sprites[selectedItem]->recorte(0,300*(selectedItem));
        }
        selectedItem = 0;
        texto[selectedItem].setColor(Color::Red);
        if(selectedItem < 4 ){
        sprites[selectedItem]->recorte(300,300*(selectedItem));
        }
    }
}

int Tienda::getItemPressed(){
    return selectedItem;
}

void Tienda::cambiarPrecios(int i , String s, float posx , float posy){
  precios[i].setFont(*font);
  precios[i].setString(s);
  precios[i].setPosition(posx , posy);
}

void Tienda::cambiarTexto(int i , String s, float posx , float posy){
  texto[i].setFont(*font);
  texto[i].setString(s);
  texto[i].setPosition(posx , posy);
}

void Tienda::cambiarAviso(int i , String s, float posx , float posy){
  aviso[i].setFont(*font);
  aviso[i].setString(s);
  aviso[i].setPosition(posx , posy);
}

void Tienda::update(float deltaTime){
    timer += deltaTime;
    texto[selectedItem].setColor(Color::Red);
    cooldown_mov-=deltaTime;
    hud * hud = hud::instance();
    Manejador * man = Manejador::instancia();
    Juego * juego = Juego::instance();
    
    monedas[0]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3-25, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarPrecios(0, to_string(sprites[0]->getTipo()) , juego->view.getCenter().x-juego->view.getSize().x/3, juego->view.getCenter().y-juego->view.getSize().y/4-25);
    sprites[0]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3, juego->view.getCenter().y-juego->view.getSize().y/4+50);
    cambiarTexto(0, "VIDA", juego->view.getCenter().x-juego->view.getSize().x/3-25, juego->view.getCenter().y-juego->view.getSize().y/4+75);
    
    monedas[1]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+175, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarPrecios(1, to_string(sprites[1]->getTipo()) , juego->view.getCenter().x-juego->view.getSize().x/3+200, juego->view.getCenter().y-juego->view.getSize().y/4-25);
    sprites[1]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+200, juego->view.getCenter().y-juego->view.getSize().y/4+50);
    cambiarTexto(1, "SLOW", juego->view.getCenter().x-juego->view.getSize().x/3+175, juego->view.getCenter().y-juego->view.getSize().y/4+75);
    
    monedas[2]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+375, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarPrecios(2, to_string(sprites[2]->getTipo()) , juego->view.getCenter().x-juego->view.getSize().x/3+400, juego->view.getCenter().y-juego->view.getSize().y/4-25);
    sprites[2]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+400, juego->view.getCenter().y-juego->view.getSize().y/4+50);
    cambiarTexto(2, "DOBLE SALTO", juego->view.getCenter().x-juego->view.getSize().x/3+350, juego->view.getCenter().y-juego->view.getSize().y/4+75);
    
    monedas[3]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+575, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarPrecios(3, to_string(sprites[3]->getTipo()) , juego->view.getCenter().x-juego->view.getSize().x/3+600, juego->view.getCenter().y-juego->view.getSize().y/4-25);
    sprites[3]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+600, juego->view.getCenter().y-juego->view.getSize().y/4+50);
    cambiarTexto(3, "VELOCIDAD", juego->view.getCenter().x-juego->view.getSize().x/3+575, juego->view.getCenter().y-juego->view.getSize().y/4+75);

    monedas[4]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3-25, juego->view.getCenter().y-juego->view.getSize().y/4+200);
    cambiarPrecios(4, to_string(sprites[4]->getTipo()) , juego->view.getCenter().x-juego->view.getSize().x/3, juego->view.getCenter().y-juego->view.getSize().y/4+175);
    sprites[5]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3, juego->view.getCenter().y-juego->view.getSize().y/4+250);
    cambiarTexto(4, "ARMA 1", juego->view.getCenter().x-juego->view.getSize().x/3-25, juego->view.getCenter().y-juego->view.getSize().y/4+275);
    
    monedas[5]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+175, juego->view.getCenter().y-juego->view.getSize().y/4+200);
    cambiarPrecios(5, to_string(sprites[5]->getTipo()) , juego->view.getCenter().x-juego->view.getSize().x/3+200, juego->view.getCenter().y-juego->view.getSize().y/4+175);
    sprites[4]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+200, juego->view.getCenter().y-juego->view.getSize().y/4+250);
    cambiarTexto(5, "ARMA 2", juego->view.getCenter().x-juego->view.getSize().x/3+175, juego->view.getCenter().y-juego->view.getSize().y/4+275);
    
    monedas[6]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+375, juego->view.getCenter().y-juego->view.getSize().y/4+200);
    cambiarPrecios(6, to_string(sprites[6]->getTipo()) , juego->view.getCenter().x-juego->view.getSize().x/3+400, juego->view.getCenter().y-juego->view.getSize().y/4+175);
    sprites[6]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+400, juego->view.getCenter().y-juego->view.getSize().y/4+250);
    cambiarTexto(6, "MEJORA ARMA 1", juego->view.getCenter().x-juego->view.getSize().x/3+325, juego->view.getCenter().y-juego->view.getSize().y/4+275);
    
    monedas[7]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+575, juego->view.getCenter().y-juego->view.getSize().y/4+200);
    cambiarPrecios(7, to_string(sprites[7]->getTipo()) , juego->view.getCenter().x-juego->view.getSize().x/3+600, juego->view.getCenter().y-juego->view.getSize().y/4+175);
    sprites[7]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+600, juego->view.getCenter().y-juego->view.getSize().y/4+250);
    cambiarTexto(7, "MEJORA ARMA 2", juego->view.getCenter().x-juego->view.getSize().x/3+575, juego->view.getCenter().y-juego->view.getSize().y/4+275);
    
    cambiarTexto(8, "BACK", juego->view.getCenter().x+juego->view.getSize().x/2-300, juego->view.getCenter().y+juego->view.getSize().y/2-100);
   
    if(timer  >=  2){
        avisoTexto = "";
        timer = 0;
    }   
    b->setPosition(juego->view.getCenter().x-juego->view.getSize().x/2, juego->view.getCenter().y-juego->view.getSize().y/2);
    b->setTextureRect(0,0,1080,720);

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && cooldown_mov<0 ){
         if(selectedItem == 8){
        moveUp();
        }else if(selectedItem >= 0 && selectedItem < 4){
            moveUp();moveUp();moveUp();moveUp();moveUp();
        }else if(selectedItem >= 4 && selectedItem < 7){
            moveUp();moveUp();moveUp();moveUp();
        }
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && cooldown_mov<0){
        if(selectedItem == 8){
        moveDown();
        }else
        if(selectedItem == 7){
        moveDown();
        }else if(selectedItem >= 0 && selectedItem < 4){
            moveDown();moveDown();moveDown();moveDown();
        }else if(selectedItem >= 4 && selectedItem < 7){
            moveDown();moveDown();moveDown();moveDown();moveDown();
        }
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && cooldown_mov<0 && selectedItem != 8){
        moveDown();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && cooldown_mov<0 && selectedItem != 8){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return )&& cooldown_mov<0 ){
        cooldown_mov = 0.35;
        if(selectedItem == numOpciones-1){
            man->back();
        }else{
            if(hud->getMonedero() >= sprites[selectedItem]->getTipo()){
                switch (selectedItem){
                case 0:
                    if(hud->getVidas() < 5){
                        avisoTexto =  "HAS COMPRADO UNA VIDA";
                        hud->sumarVidas();
                        hud->setMonedero(sprites[selectedItem]->getTipo());
                        sprites[selectedItem]->setTipo(2);
                    }else{
                        avisoTexto =  "YA TIENES TODAS LAS VIDAS";
                    }
                    break;
                case 1:
                    if(hud->getSlow() == false){
                       avisoTexto =  "HAS COMPRADO SLOW";
                        hud->setSlow(true);
                        hud->setMonedero(sprites[selectedItem]->getTipo());
                        sprites[selectedItem]->setTipo(10);
                    }else{
                       avisoTexto =  "YA TIENES SLOW";
                    }
                    break;
                case 2:
                    if(hud->getDoblesalto() == false){
                        avisoTexto =  "HAS COMPRADO DOBLE SALTO";
                        hud->setDobleSalto(true);
                        hud->setMonedero(sprites[selectedItem]->getTipo());
                        sprites[selectedItem]->setTipo(10);
                    }else{
                        avisoTexto =  "YA TIENES DOBLE SALTO";
                    }
                    break;
                case 3:
                    if(hud->getVelocidad() == false){
                        avisoTexto =  "HAS COMPRADO VELOCIDAD";
                        hud->setVelocidad(true);
                        hud->setIVelocidad(350);
                        hud->setMonedero(sprites[selectedItem]->getTipo());
                        sprites[selectedItem]->setTipo(10);
                    }else{
                       avisoTexto = "YA TIENES VELOCIDAD";
                    }
                    break;
                case 4:
                    if(hud->getArma()[0] == 0){
                        avisoTexto =  "HAS COMPRADO ARMA 1";
                        hud->setArma(0,1);
                        hud->setMonedero(sprites[selectedItem]->getTipo());
                    }else{
                       avisoTexto = "YA TIENES EL ARMA 1";
                    }
                    break;
                case 5:
                    if(hud->getArma()[1] == 0){
                        avisoTexto = "HAS COMPRADO EL ARMA 2";
                        hud->setArma(1,1);
                        hud->setMonedero(sprites[selectedItem]->getTipo());
                        sprites[selectedItem]->setTipo(30);
                    }else{
                        avisoTexto =  "YA TIENES ARMA 2";
                    }
                    break;
                case 6:
                    if(hud->getArma()[1] > 0){
                        avisoTexto =  "HAS COMPRADO MEJORA DEL ARMA 1";
                        hud->setArma(0,1);
                        hud->setMonedero(sprites[selectedItem]->getTipo());
                        sprites[selectedItem]->setTipo(10);
                    }else{
                       avisoTexto = "NO TIENES ESTA ARMA";
                    }
                    break;
                case 7:
                    if(hud->getArma()[1] > 0){
                        avisoTexto = "HAS COMPRADO MEJORA DEL ARMA 2";
                        hud->setArma(0,1);
                        hud->setMonedero(sprites[selectedItem]->getTipo());
                        sprites[selectedItem]->setTipo(30);
                    }else{
                       avisoTexto =  "NO TIENES ESTA ARMA";
                    }
                    break;
                default:
                    break;
                }
            }else{
                avisoTexto =  "NO TIENES DINERO SUFICIENTE";
            }
        }
    }
    cambiarAviso(0, avisoTexto, juego->view.getCenter().x+juego->view.getSize().x/3-500, juego->view.getCenter().y+juego->view.getSize().y/4);
    hud->setMarcador(juego->view.getCenter().x+200, juego->view.getCenter().y+600);
}

void Tienda::render(float deltaTime){
    Motor * motor = Motor::instance();
    hud * hud = hud::instance();
    if(b != nullptr){
        b->render();
    }
    for(int i = 0; i < maxTienda; i++){
        motor->dibujo(precios[i]);
    }
    for(int i = 0; i < maxTienda; i++){
        sprites[i]->render();
        monedas[i]->render();
    }
    for(int i = 0; i < numOpciones; i++){
      motor->dibujo(texto[i]);
    }

    motor->dibujo(aviso[0]);
    
    hud->renderMonedas();
    
}


Tienda::~Tienda(){
    delete[] sprites;
    delete[] texto;
    if(font != nullptr){
        delete font;
        font = nullptr;
    }
    if(t != nullptr){
        delete t; 
        t = nullptr;
    }
    if(b != nullptr){    
        delete b;
        b =nullptr;
    }
    delete [] aviso;
}
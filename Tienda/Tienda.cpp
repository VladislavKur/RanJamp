#include "Tienda.h"

Tienda* Tienda::p_instance = 0;


Tienda* Tienda::instance(){
    if(p_instance == 0){
        p_instance = new Tienda(9, 10);
    }
    return(p_instance);
}

Tienda::Tienda(int i, int max){
    numOpciones = max;
    maxTienda = i;
    itemSeleccionado = -1;
    sprites = new Cuerpo *[9];
    sprites[0] = new Cuerpo(50 , 0,32,32,"powerup1.png",1, 0,-1);
    sprites[0]->recorte(25,25);
    sprites[1] = new Cuerpo(50 , 100,160,32,"vidas.png",1, 0,-1);
    sprites[1]->recorte(0,5*32);
    sprites[2] = new Cuerpo(50 , 200,32,32,"saltos.png",1, 0,-1);
    sprites[3] = new Cuerpo(50, 300,32,32,"velocidad.png",1, 0,-1);
    sprites[4] = new Cuerpo(50, 400,32,32,"powerup3.png",1, 0,-1);
    sprites[5] = new Cuerpo(50, 500,100,100,"Moneda.png",1, 0,-1);
    sprites[5]->Scalar(0.2, 0.2);
    sprites[6] = new Cuerpo(50 , 600,100,100,"Llave.png",1, 0,-1);
    sprites[6]->Scalar(0.2, 0.2);
    sprites[7] = new Cuerpo(50 , 700,100,100,"tiempo.png",1, 0,-1);
    sprites[7]->Scalar(0.2, 0.2);
    sprites[8] = new Cuerpo(50 , 800,100,100,"estrella.png",1, 0,-1);
    sprites[8]->Scalar(0.2, 0.2);

    font = new Font[1];

    texto = new Text[max];

    font->loadFromFile("resources/fuentes/PixelBug.otf");

    
    cambiarTexto(0, "Back" , 256 , 640);
    cambiarTexto(1, "P1" , 0 , 0);
    cambiarTexto(2, "P2" , 0 , 100);
    cambiarTexto(3, "P3" , 0 , 200);
    cambiarTexto(4, "P4" , 0 , 300);
    cambiarTexto(5, "P5" , 0 , 400);
    cambiarTexto(6, "P6" , 0 , 500);
    cambiarTexto(7, "P7" , 0 , 600);
    cambiarTexto(8, "P8" , 0 , 700);
    cambiarTexto(9, "P9" , 0 , 800);
}

void Tienda::moveUp(){
    if(selectedItem - 1 >= 0 ){
        texto[selectedItem].setColor(Color::White);
        selectedItem--;
        texto[selectedItem].setColor(Color::Red);
    }
}

void Tienda::moveDown(){
    if(selectedItem + 1 < numOpciones ){
        texto[selectedItem].setColor(Color::White);
        selectedItem++;
        texto[selectedItem].setColor(Color::Red);
    }
}

int Tienda::getItemPressed(){
    return selectedItem;
}

void Tienda::cambiarTexto(int i , String s, float posx , float posy){
  texto[i].setFont(*font);
  texto[i].setString(s);
  texto[i].setPosition(posx , posy);
}

void Tienda::update(float deltaTime){
    texto[selectedItem].setColor(Color::Red);
    cooldown_mov-=deltaTime;
    hud * hud = hud::instance();
    Manejador * man = Manejador::instancia();
    Juego * juego = Juego::instance();

    sf::Vector2i position = sf::Mouse::getPosition();

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && cooldown_mov<0){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && cooldown_mov<0){
        moveDown();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return )&& cooldown_mov<0){
        cooldown_mov = 0.35;
        if(selectedItem == 0){
            man->back();
        }else{
            if(hud->getMonedero() > sprites[selectedItem-1]->getTipo()){
                cout<<"he comprado el item "<< selectedItem << endl;
            }
        }
    }
}

void Tienda::render(float num){
  Motor * motor = Motor::instance();
 
  for(int i = 0; i < 9; i++){
    sprites[i]->render();
  }
  for(int i = 0; i < 10; i++){
    motor->dibujo(texto[i]);
  }
}


Tienda::~Tienda(){
    delete[] sprites;
    delete[] texto;
    if(font != nullptr){
        delete font;
        font = nullptr;
    }
}
#include "hud.h"

hud * hud::p_instancia = 0;// o null

hud * hud::instance(){
  if(p_instancia == 0){
    p_instancia = new hud(1540, 5, 6);
  }

  return p_instancia;
}

hud::hud(int posY, int vidasPlayer, int max){ 
    r = new RectangleShape[1];
    tVidas = new Texture[1];
    tDobleSalto = new Texture[1];
    tVidas = new Texture[1];
    tArma = new Texture[1];
    tVelocidad = new Texture[1];
    sVidas = new Sprite[1];
    sDobleSalto = new Sprite[1];
    sVelocidad = new Sprite[1];
    sArma = new Sprite[1];
    font = new Font[1];

    r->setSize(Vector2f(1024,120));
    r->setFillColor(Color(0, 0, 0));
    r->setPosition(0 , posY - 660);
    
    tVidas->loadFromFile("resources/Imagenes/vidas.png"); 
    sVidas->setTexture(*tVidas);
    sVidas->setTextureRect(IntRect(0,5*32,160,32));
    sVidas->setPosition(128 , posY - 600);
    tDobleSalto->loadFromFile("resources/Imagenes/saltos.png"); 
    sDobleSalto->setTexture(*tDobleSalto);
    sDobleSalto->setTextureRect(IntRect(0,0,32,32));
    sDobleSalto->setPosition(638 , posY - 600);
    tVelocidad->loadFromFile("resources/Imagenes/velocidad.png"); 
    sVelocidad->setTexture(*tVelocidad); 
    sVelocidad->setTextureRect(IntRect(0,0,32,32));
    sVelocidad->setPosition(672 , posY - 600);
    tArma->loadFromFile("resources/Imagenes/powerup3.png");  
    sArma->setTexture(*tArma);  
    sArma->setTextureRect(IntRect(0,0,32,32));
    sArma->setPosition(704, posY - 600);
    texto = new Text[max];

    font->loadFromFile("resources/fuentes/PixelBug.otf");

  
    cambiarTexto(*font , 0 , Color::Blue , "PUNTUACION:" , Vector2f(0.8, 0.8), 32 , posY - 640);
    cambiarTexto(*font , 1 , Color::Blue , "0" , Vector2f(0.8, 0.8), 256 , posY - 640);
    cambiarTexto(*font , 2 , Color::Blue , "VIDAS:" , Vector2f(0.8, 0.8), 32 , posY - 600);
    cambiarTexto(*font , 3 , Color::Blue , "TIEMPO:" , Vector2f(0.8, 0.8), 512 , posY - 640);
    cambiarTexto(*font , 4 , Color::Blue , to_string(clockGlobal.getElapsedTime().asSeconds()) , Vector2f(0.8, 0.8), 640 , posY - 640);
    cambiarTexto(*font , 5 , Color::Blue , "POWER UPS:" , Vector2f(0.8, 0.8), 512 , posY - 600);

}

void hud::cambiarTexto(const Font &f , int i, Color c, string s , Vector2f v, int posx , int posy){

  texto[i].setFont(f);
  texto[i].setColor(c);
  texto[i].setString(s);
  texto[i].setScale(v);
  texto[i].setPosition(posx , posy);

}

void hud::setMarcador(int posX , int posY, int vidasPlayer){
  r->setPosition(posX - 512 , posY - 360);
  sVidas->setTextureRect(IntRect(0, 32 *(vidasPlayer), 160, 32));
  sVidas->setPosition(posX - 384 , posY - 300);
  sArma->setPosition(posX + 192, posY - 300);
  sDobleSalto->setPosition( posX + 126 , posY - 300);
  sVelocidad->setPosition( posX + 160 , posY - 300);

  texto[0].setPosition( posX - 480 , posY - 340);
  texto[1].setPosition( posX - 256 , posY - 340);
  texto[1].setString(to_string(puntos));
  texto[2].setPosition( posX - 480 , posY - 300);
  texto[3].setPosition( posX , posY - 340);
  texto[4].setPosition( posX + 128, posY - 340);
  texto[4].setString(to_string(int(clockGlobal.getElapsedTime().asSeconds())));
  texto[5].setPosition(posX , posY - 300);
}


void hud::render(){
  Motor * motor = Motor::instance();
  motor->dibujo(*r);
  motor->dibujo(*sVidas);
  motor->dibujo(*sArma);
  motor->dibujo(*sDobleSalto);
  motor->dibujo(*sVelocidad);
  for(int i = 0; i < 6; i++){
    //motor->dibujo(texto[i]);
  }
}
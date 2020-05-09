#include "hud.h"

hud * hud::p_instancia = 0;// o null

hud * hud::instance(){
  if(p_instancia == 0){
    p_instancia = new hud(1540, 5, 3);
  }

  return p_instancia;
}

hud::hud(int posY, int vidasPlayer, int max){ 
    tVidas = new Texture[1];
    tDobleSalto = new Texture[1];
    tVidas = new Texture[1];
    tArma = new Texture[1];
    tVelocidad = new Texture[1];
    sVidas = new Sprite[1];
    sDobleSalto = new Sprite[1];
    sVelocidad = new Sprite[1];
    sArma = new Sprite[1];
    tMonedas = new Texture[1];
    sMonedas = new Sprite[1];
    tLlaves = new Texture[1];
    sLlaves = new Sprite[1];
    // tTiempo = new Texture[1];
    // sTiempo = new Sprite[1];
    // tPuntos = new Texture[1];
    // sPuntos = new Sprite[1];
    font = new Font[1];


    
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
    tMonedas->loadFromFile("resources/Imagenes/Moneda.png");
    sMonedas->setTexture(*tMonedas);
    sMonedas->setTextureRect(IntRect(0,0,100,100));
    sMonedas->scale(0.2, 0.2);
    sMonedas->setPosition(704, posY - 520);
    tLlaves->loadFromFile("resources/Imagenes/Llave.png");
    sLlaves->setTexture(*tLlaves);
    sLlaves->setTextureRect(IntRect(0,0,100,100));
    sLlaves->scale(0.2, 0.2);
    sLlaves->setPosition(672, posY - 520);
    // tTiempo->loadFromFile("resources/Imagenes/tiempo.png");
    // sTiempo->setTexture(*tMonedas);
    // sTiempo->setTextureRect(IntRect(0,0,100,100));
    // sTiempo->scale(0.2, 0.2);
    // sTiempo->setPosition(704, posY - 520);
    // tPuntos->loadFromFile("resources/Imagenes/estrella.png");
    // sPuntos->setTexture(*tLlaves);
    // sPuntos->setTextureRect(IntRect(0,0,100,100));
    // sPuntos->scale(0.2, 0.2);
    // sPuntos->setPosition(672, posY - 520);

    texto = new Text[max];

    font->loadFromFile("resources/fuentes/PixelBug.otf");

  
    cambiarTexto(*font , 0 , Color::Blue , "0" , Vector2f(0.8, 0.8), 256 , posY - 640);
    cambiarTexto(*font , 1 , Color::Blue , to_string(clockGlobal.getElapsedTime().asSeconds()) , Vector2f(0.8, 0.8), 640 , posY - 640);
    cambiarTexto(*font , 2 , Color::Blue , "0" , Vector2f(0.8, 0.8), 512 , posY - 600);
}

void hud::cambiarTexto(const Font &f , int i, Color c, string s , Vector2f v, int posx , int posy){

  texto[i].setFont(f);
  texto[i].setColor(c);
  texto[i].setString(s);
  texto[i].setScale(v);
  texto[i].setPosition(posx , posy);

}

void hud::setMarcador(int posX , int posY, int vidasPlayer, int monedas, vector<int> llaves){
 // r->setPosition(posX - 512 , posY - 360);
  sVidas->setTextureRect(IntRect(0, 32 *(vidasPlayer), 160, 32));
  sVidas->setPosition(posX - 384 , posY - 300);
  sArma->setPosition(posX + 192, posY - 300);
  sDobleSalto->setPosition( posX + 126 , posY - 300);
  sVelocidad->setPosition( posX + 160 , posY - 300);

  texto[0].setPosition( posX - 256 , posY - 340);
  texto[0].setString(to_string(puntos));
  texto[1].setPosition( posX + 128, posY - 340);
  texto[1].setString(to_string(int(clockGlobal.getElapsedTime().asSeconds())));
  texto[2].setPosition(posX + 350 , posY - 300);
  texto[2].setString(to_string(monedas));
}


void hud::render(){
  Motor * motor = Motor::instance();
  motor->dibujo(*sVidas);
  motor->dibujo(*sArma);
  motor->dibujo(*sDobleSalto);
  motor->dibujo(*sVelocidad);
  motor->dibujo(*sMonedas);
  motor->dibujo(*sLlaves);
  // motor->dibujo(*sTiempo);
  // motor->dibujo(*sPuntos);
  // for(int i = 0; i < 3; i++){
  //   motor->dibujo(texto[i]);
  // }
}

hud::~hud(){
  if(sVidas != NULL){
    delete sVidas;
    sVidas = NULL;
  }
  if(sArma != NULL){
    delete sArma;
    sArma = NULL;
  }
  if(sDobleSalto != NULL){
    delete sDobleSalto;
    sDobleSalto =NULL;
  }
  if(sVelocidad != NULL){
    delete sVelocidad;
    sVelocidad = NULL;
  }
  if(sMonedas != NULL){
    delete sMonedas;
    sMonedas = NULL;
  }
  if(sLlaves != NULL){
    delete sLlaves;
  }
  // delete sTiempo;
  // delete sPuntos;
  if(tLlaves != NULL){
   delete tLlaves;
   tLlaves = NULL;
  }
  // delete tPuntos;
  // delete tTiempo;
  if(tVidas != NULL){
    delete tVidas;
    tVidas = NULL;
  }
  if(tArma != NULL){
    delete tArma;
    tArma = NULL;
  }
  if(tDobleSalto != NULL){
    delete tDobleSalto;
    tDobleSalto = nullptr;
  }
  if(tVelocidad != nullptr){
    delete tVelocidad;
    tVelocidad = nullptr;
  }
  if(tMonedas != nullptr){
    delete tMonedas;
    tMonedas = nullptr;
  }
  delete[] texto;
  if(font != nullptr){
    delete font;
    font = nullptr;
  }
}
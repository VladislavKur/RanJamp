#include "hud.h"

hud * hud::p_instancia = 0;// o null

hud * hud::instance(){
  if(p_instancia == 0){
    p_instancia = new hud(1540, 5, 3);
  }

  return p_instancia;
}

hud::hud(int posY, int vidasPlayer, int max){ 
    monedero = 10;
    puntos = 0; 
    vidas = 5; 
     doblesalto = false;
     velocidad = false;
     slow = false; 
    i_velocidad = 250;
     godMode = false;


    sprites = new Cuerpo *[9];
    sprites[0] = new Cuerpo(100 , posY - 600,350,250,"madera.png",1, 0,-1);
    sprites[0]->recorte(25,25);
    sprites[1] = new Cuerpo(128 , posY - 600,160,32,"vidas.png",1, 0,-1);
    sprites[1]->recorte(0,5*32);
    sprites[2] = new Cuerpo(638 , posY - 600,32,32,"saltos.png",1, 0,-1);
    sprites[3] = new Cuerpo(672, posY - 600,32,32,"velocidad.png",1, 0,-1);
    sprites[4] = new Cuerpo(704, posY - 600,32,32,"powerup3.png",1, 0,-1);
    sprites[5] = new Cuerpo(704, posY - 520,100,100,"Moneda.png",1, 0,-1);
    sprites[5]->Scalar(0.2, 0.2);
    sprites[6] = new Cuerpo(128 , posY - 600,100,100,"Llave.png",1, 0,-1);
    sprites[6]->Scalar(0.2, 0.2);
    sprites[7] = new Cuerpo(128 , posY - 600,100,100,"tiempo.png",1, 0,-1);
    sprites[7]->Scalar(0.2, 0.2);
    sprites[8] = new Cuerpo(128 , posY - 600,100,100,"estrella.png",1, 0,-1);
    sprites[8]->Scalar(0.2, 0.2);
    font = new Font[1];

    texto = new Text[max];

    font->loadFromFile("resources/fuentes/PixelBug.otf");

  
    cambiarTexto(*font , 0 , Color::Blue , "0" , Vector2f(0.8, 0.8), 256 , posY - 640);
    cambiarTexto(*font , 1 , Color::Blue , to_string(clockGlobal.getElapsedTime().asSeconds()) , Vector2f(0.8, 0.8), 640 , posY - 640);
    cambiarTexto(*font , 2 , Color::Blue , "0" , Vector2f(0.8, 0.8), 512 , posY - 600);

    arma.push_back(0);//arma 1 
    arma.push_back(0);// arma 2
}

void hud::cambiarTexto(const Font &f , int i, Color c, string s , Vector2f v, int posx , int posy){

  texto[i].setFont(f);
  texto[i].setColor(c);
  texto[i].setString(s);
  texto[i].setScale(v);
  texto[i].setPosition(posx , posy);

}

void hud::setMarcador(int posX , int posY){
  sprites[0]->posicionamientoFijo(posX - 300 , posY - 400);
  sprites[1]->posicionamientoFijo(posX - 384 , posY - 300);
  sprites[1]->recorte(0, 32 *(vidas));
  sprites[2]->posicionamientoFijo(posX - 250 , posY - 300);
  sprites[3]->posicionamientoFijo(posX - 220 , posY - 300);
  sprites[4]->posicionamientoFijo(posX - 190, posY - 300);
  sprites[5]->posicionamientoFijo(posX - 200 , posY - 340);
  sprites[6]->posicionamientoFijo(posX - 150 , posY - 300);
  sprites[7]->posicionamientoFijo(posX - 450 , posY - 340);
  sprites[8]->posicionamientoFijo(posX - 340 , posY - 340);
  texto[0].setPosition( posX - 300 , posY - 355);
  texto[0].setString(to_string(puntos));
  texto[1].setPosition( posX - 400 , posY - 355);
  texto[1].setString(to_string(int(clockGlobal.getElapsedTime().asSeconds())));
  texto[2].setPosition(posX - 150 , posY - 355);
  texto[2].setString(to_string(monedero));
  
}


void hud::render(){
  Motor * motor = Motor::instance();
 
  for(int i = 0; i < 9; i++){
    sprites[i]->render();
  }
  for(int i = 0; i < 3; i++){
    motor->dibujo(texto[i]);
  }
}

hud::~hud(){
  delete[] sprites;
  delete[] texto;
  if(font != nullptr){
    delete font;
    font = nullptr;
  }
}

bool hud::restarVidas(){
  bool devolver = false;
  if(godMode == false){
      vidas--;
  }

  if(vidas == 0 && godMode == false){
    devolver = true; 
  }
  return devolver;
}

void hud::setGodMode(){
  if(godMode){
    godMode=false;
  } else{
    godMode=true;
    cout<<"MODO DIOS ACTIVADO !!!!!!!!!!!!!!!!"<<endl;
  }
}

void hud::reiniciarTiempo(){
  clockGlobal.restart();
}

void hud::setArma(int pos, int mejora){
  arma[pos] += mejora;
}
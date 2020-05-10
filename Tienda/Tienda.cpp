#include "Tienda.h"

Tienda* Tienda::p_instance = 0;


Tienda* Tienda::instance(){
    if(p_instance == 0){
        p_instance = new Tienda(4, 5);
    }
    return(p_instance);
}

Tienda::Tienda(int i, int max){
    numOpciones = max;
    maxTienda = i;
    itemSeleccionado = -1;
    sprites = new Cuerpo *[i];
    sprites[0] = new Cuerpo(300 , 100,300,300,"ObjetosTienda.png",1, 0,2);
    sprites[0]->Scalar(0.2, 0.2);
    sprites[1] = new Cuerpo(300 , 200,300,300,"ObjetosTienda.png",1, 0,1);
    sprites[1]->recorte(0,300);
    sprites[1]->Scalar(0.2, 0.2);
    sprites[2] = new Cuerpo(300 , 400,300,300,"ObjetosTienda.png",1, 0,1);
    sprites[2]->recorte(0,600);
    sprites[2]->Scalar(0.2, 0.2);
    sprites[3] = new Cuerpo(300, 500,300,300,"ObjetosTienda.png",1, 0,3);
    sprites[3]->recorte(0,900);
    sprites[3]->Scalar(0.2, 0.2);

    font = new Font[1];

    texto = new Text[max];

    font->loadFromFile("resources/fuentes/PixelBug.otf");

    
    cambiarTexto(0, "Back" , 256 , 640);
    cambiarTexto(1, "P1" , 0 , 0);
    cambiarTexto(2, "P2" , 0 , 100);
    cambiarTexto(3, "P3" , 0 , 200);
    cambiarTexto(4, "P4" , 0 , 300);
}

void Tienda::moveUp(){
    if(selectedItem - 1 >= 0 ){
        texto[selectedItem].setColor(Color::White);
        if(selectedItem > 0){
        sprites[selectedItem-1]->recorte(0,300*(selectedItem-1));
        }
        selectedItem--;
        texto[selectedItem].setColor(Color::Red);
        if(selectedItem > 0){
        sprites[selectedItem-1]->recorte(300,300*(selectedItem-1));
        }
    }
}

void Tienda::moveDown(){
    if(selectedItem + 1 < numOpciones ){
        texto[selectedItem].setColor(Color::White);
        if(selectedItem > 0){
        sprites[selectedItem-1]->recorte(0,300*(selectedItem-1));
        }
        selectedItem++;
        texto[selectedItem].setColor(Color::Red);
        if(selectedItem > 0){
        sprites[selectedItem-1]->recorte(300,300*(selectedItem-1));
        }
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
    sprites[0]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarTexto(1, "P1", juego->view.getCenter().x-juego->view.getSize().x/3-25, juego->view.getCenter().y-juego->view.getSize().y/4+25);
    sprites[1]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+100, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarTexto(2, "P2", juego->view.getCenter().x-juego->view.getSize().x/3+75, juego->view.getCenter().y-juego->view.getSize().y/4+25);
    sprites[2]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+200, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarTexto(3, "P3", juego->view.getCenter().x-juego->view.getSize().x/3+175, juego->view.getCenter().y-juego->view.getSize().y/4+25);
    sprites[3]->posicionamiento(juego->view.getCenter().x-juego->view.getSize().x/3+300, juego->view.getCenter().y-juego->view.getSize().y/4);
    cambiarTexto(4, "P4", juego->view.getCenter().x-juego->view.getSize().x/3+275, juego->view.getCenter().y-juego->view.getSize().y/4+25);
    cambiarTexto(0, "BACK", juego->view.getCenter().x+juego->view.getSize().x/3+100, juego->view.getCenter().y+juego->view.getSize().y/4-100);

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
            if(hud->getMonedero() >= sprites[selectedItem-1]->getTipo()){
                switch (selectedItem){
                case 1:
                    if(hud->getVidas() < 5){
                        cout << "HE COMPRADO VIDA" <<endl;
                        hud->sumarVidas();
                        hud->setMonedero(sprites[selectedItem-1]->getTipo());
                    }else{
                        cout << "ya tengo todas mis vidas" <<endl;
                    }
                    break;
                case 2:
                    if(hud->getSlow() == false){
                        cout << "HE COMPRADO SLOW" <<endl;
                        hud->setSlow(true);
                        hud->setMonedero(sprites[selectedItem-1]->getTipo());
                    }else{
                        cout << "ya tengo slow" <<endl;
                    }
                    break;
                case 3:
                    if(hud->getDoblesalto() == false){
                        cout << "HE COMPRADO saltos" <<endl;
                        hud->setDobleSalto(true);
                        hud->setMonedero(sprites[selectedItem-1]->getTipo());
                    }else{
                        cout << "ya tengo saltos" <<endl;
                    }
                    break;
                case 4:
                    if(hud->getVelocidad() == false){
                        cout <<"HE COMPRADO VELOCIDAD" <<endl;
                        hud->setVelocidad(true);
                        hud->setMonedero(sprites[selectedItem-1]->getTipo());
                    }else{
                        cout << "ya tengo velocidad"<<endl;
                    }
                    break;
                default:
                    break;
                }
            }else{
                cout << "ya NO TENGO DINERO " << hud->getMonedero() <<endl;
            }
        }
    }
}

void Tienda::render(float num){
  Motor * motor = Motor::instance();
 
  for(int i = 0; i < maxTienda; i++){
    sprites[i]->render();
  }
  for(int i = 0; i < numOpciones; i++){
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
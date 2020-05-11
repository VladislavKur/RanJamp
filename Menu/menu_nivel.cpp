#include "menu_nivel.h"

menu_nivel* menu_nivel::p_instance = 0;
sf::Font* menu_nivel::fuente = new Font();

menu_nivel* menu_nivel::instance(){
     if(p_instance == 0){
        fuente->loadFromFile("resources/fuentes/AnotherRound.otf");
        
        p_instance = new menu_nivel(*fuente, 5 , 4 );

    }

    return(p_instance);
}

menu_nivel::menu_nivel( Font fuen, int max  ,int maxS) : menu(fuen, max){
    t = new Textura("resources/Imagenes/MenuControles.png");
    b = new Bloque(t);
    maxSprites = maxS;
    sprites = new Cuerpo * [maxSprites];

    sprites[0] = new Cuerpo(300 , 100,350,300,"TODOSNIVELES.png",0.5, 0,-1);
    sprites[1] = new Cuerpo(300 , 100,350,300,"TODOSNIVELES.png",0.5, 0,-1);
    sprites[2] = new Cuerpo(300 , 100,350,300,"TODOSNIVELES.png",0.5, 0,-1);
    sprites[3] = new Cuerpo(300 , 100,350,300,"TODOSNIVELES.png",0.5, 0,-1);

}



void menu_nivel::update(float deltaTime){
    cooldown_mov-=deltaTime;
    Manejador* man = Manejador::instancia();
    Juego* juego = Juego::instance();
    

    sprites[0]->posicionamiento( juego->view.getCenter().x-juego->view.getSize().x/3-50, juego->view.getCenter().y-juego->view.getSize().y/4+125);
    cambiarTexto(0, "Nivel 1", juego->view.getCenter().x-juego->view.getSize().x/3-100, juego->view.getCenter().y-juego->view.getSize().y/4);
    sprites[1]->posicionamiento(  juego->view.getCenter().x, juego->view.getCenter().y-juego->view.getSize().y/4+125);
    cambiarTexto(1, "Nivel 2", juego->view.getCenter().x-50, juego->view.getCenter().y-juego->view.getSize().y/4);
    sprites[2]->posicionamiento( juego->view.getCenter().x+juego->view.getSize().x/3+50, juego->view.getCenter().y-juego->view.getSize().y/4+125);
    cambiarTexto(2, "Nivel 3", juego->view.getCenter().x+juego->view.getSize().x/3, juego->view.getCenter().y-juego->view.getSize().y/4);
    sprites[3]->posicionamiento(  juego->view.getCenter().x-juego->view.getSize().x/5, juego->view.getCenter().y+125);
    cambiarTexto(3, "Nivel 4", juego->view.getCenter().x-juego->view.getSize().x/5-50, juego->view.getCenter().y);
    cambiarTexto(4, "BACK", juego->view.getCenter().x+juego->view.getSize().x/2-300, juego->view.getCenter().y+juego->view.getSize().y/2-100);

   
    
    cout<<"ESTE ES EL NIVEL = "<< nivel<<endl;
    if(nivel.compare("Mundo1-")){
        t->setTexture("resources/Imagenes/MenuBosque.png");
        b->setTextura(t);
        sprites[0]->recorte(0,0);
        sprites[1]->recorte(0,300);
        sprites[2]->recorte(0,600);
        sprites[3]->recorte(0,900);
    }else if(nivel.compare("Mundo2-")){
        t->setTexture("resources/Imagenes/MenuAntartida.png");
        b->setTextura(t);
        sprites[0]->recorte(0,1200);
        sprites[1]->recorte(0,1500);
        sprites[2]->recorte(0,1800);
        sprites[3]->recorte(0,2100);
    }else if(nivel.compare("Mundo3-")){
        t->setTexture("resources/Imagenes/MenuInfierno.png");
        b->setTextura(t);
        sprites[0]->recorte(0,2400);
        sprites[1]->recorte(0,2700);
        sprites[2]->recorte(0,3000);
        sprites[3]->recorte(0,3300);
    }else if(nivel.compare("Mundo4-")){
        t->setTexture("resources/Imagenes/MenuApocalipsis.png");
        b->setTextura(t);
        sprites[0]->recorte(0,3500);
        sprites[1]->recorte(0,3800);
        sprites[2]->recorte(0,4100);
        sprites[3]->recorte(0,4400);
    }

    b->setPosition(juego->view.getCenter().x-juego->view.getSize().x/2, juego->view.getCenter().y-juego->view.getSize().y/2);

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && cooldown_mov<0){
        moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && cooldown_mov<0){
        moveDown();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && cooldown_mov<0 && selectedItem == 0){
        moveDown();moveDown();moveDown();
        cooldown_mov = 0.25;
    }
   if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && cooldown_mov<0 && selectedItem == 3 ){
        moveUp();moveUp();moveUp();
        cooldown_mov = 0.25;
    }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return )&& cooldown_mov<0 ){
        cooldown_mov = 0.5;
        switch(selectedItem){

            case 0:
                nivel += "1.tmx"; 
                juego->nivelSeleccionado(nivel);
                man->cambiarEstado(juego);
                resetSelectedItem();
            break;
            case 1:
                nivel += "2.tmx"; 
                juego->nivelSeleccionado(nivel);
                man->cambiarEstado(juego);
                resetSelectedItem();
            break;
            case 2:
                nivel += "3.tmx"; 
                
               juego->nivelSeleccionado(nivel);
                man->cambiarEstado(juego);
                resetSelectedItem();
            break;
            case 3:
                nivel += "4.tmx"; 
                juego->nivelSeleccionado(nivel);
                man->cambiarEstado(juego);
                resetSelectedItem();
            break;
            case 4:
                man->back();
                resetSelectedItem();
            break;
        }
    }
}
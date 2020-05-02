#include "Cuerpo.h"

Cuerpo:: Cuerpo(float x_entrada, float y_entrada, int sizeHeight, int sizeWidth, 
            std::string fichero, float escala, typeBody tipoCuerpo){

    motor = Motor::instance();

    class_positionX = x_entrada;
    class_positionY = y_entrada;

    class_previousX = x_entrada;
    class_previousY = y_entrada;

    if(tipoCuerpo == RECTANGLE)
        body = new sf::RectangleShape();
    else if(tipoCuerpo == CIRCLE)
        body = new sf::CircleShape();

    class_textura = new sf::Texture();

    class_escala = escala;

    class_width = sizeWidth;
    class_height = sizeHeight;
    
    class_move = false;

    posicionamiento(x_entrada, y_entrada);

    vector<int> aux = texturizar(fichero, sizeWidth, sizeHeight);

    class_widthTexture = aux[0];
    class_heightTexture = aux[1];

    motor->setTamanyoCuerpo(body, sf::Vector2f(sizeWidth, sizeHeight));

    motor->setScale(body, escala, escala);

}

Cuerpo::Cuerpo(float x_entrada , float y_entrada, int sizeWidth , int sizeHeight){
     motor = Motor::instance();

    class_positionX = x_entrada;
    class_positionY = y_entrada;

    body = new sf::RectangleShape();

    class_width = sizeWidth;
    class_height = sizeHeight;
    
    motor->posicionar(body, x_entrada, y_entrada);

    motor->setTamanyoCuerpo(body, sf::Vector2f(sizeWidth, sizeHeight));

}

Rectangulo * Cuerpo::getGlobalBounds(){
    
    sf::FloatRect aux = body->getGlobalBounds();

    Rectangulo * R = new Rectangulo(aux.width,aux.height,aux.left,aux.top);
   return R;
}

void Cuerpo::posicionamiento(float x_entrada,float y_entrada){
    
    class_previousX = class_positionX;
    class_previousY = class_positionY;

    class_positionX = x_entrada;
    class_positionY = y_entrada;

    class_move = true;

    motor->posicionar(body, class_previousX, class_previousY);
}

vector<int> Cuerpo::texturizar(std::string entrada, int sizeWidth, int sizeHeight){
    vector<int> devuelvo;

    bool cargado = motor->cargarSprite(*class_textura, entrada);

    if(!cargado){
        cerr<<"No se ha cargado la textura " << entrada<<endl;
        exit(0);
    }
    
    devuelvo.push_back(class_textura->getSize().x);
    devuelvo.push_back(class_textura->getSize().y);

    motor->setTextura(body, class_textura);

    motor->posicionarOrigen(body, sizeWidth, sizeHeight);

    motor->recorte(body, 0, 0, sizeWidth, sizeHeight);

    return devuelvo;
}

void Cuerpo::addAnimacion(float timeAnimacion){
    animacion = new Animacion(body, timeAnimacion, class_width, class_height,
        class_widthTexture, class_heightTexture);
    
}

bool Cuerpo::colisiona(Cuerpo* entrada){
    bool devuelvo = false;

    devuelvo = motor->compararColision(body, entrada->body);
}

void Cuerpo::setSpriteAnimacion(int entrada){
    animacion->setSprite(entrada);
}

std::vector<float> Cuerpo::getBounds(){
    std::vector<float> devolver;

    sf::FloatRect aux = body->getGlobalBounds();

    devolver.push_back(aux.left);
    devolver.push_back(aux.top);
    devolver.push_back(aux.width);
    devolver.push_back(aux.height);

    return devolver;
}

std::vector<float> Cuerpo::getPosicion(){
    return vector<float>(class_positionX, class_positionY);
}

std::vector<float> Cuerpo::getSize(){
    sf::RectangleShape* casteadoRect = dynamic_cast<sf::RectangleShape*>(body);

    vector<float> devolver;

    if(casteadoRect != NULL){
        devolver.push_back(casteadoRect->getSize().x);
        devolver.push_back(casteadoRect->getSize().y);
    }

    return devolver;
}

void Cuerpo::update(float deltaTime){
    if(this != NULL){
        animacion->update(deltaTime);
        if(class_move){
            class_previousX = class_positionX;
            class_previousY = class_positionY;
        }
        else
            class_move = false;
    }
}

void Cuerpo::render(float porcentaje){
    if(this != NULL){
        animacion->render(porcentaje);

        motor->posicionar(body, 
        class_previousX + (class_positionX-class_previousX)*porcentaje,
        class_previousY + (class_positionY-class_previousY)*porcentaje);

        motor->dibujo(body);
    }
}

Cuerpo::~Cuerpo(){
    if(animacion!=NULL){
        delete animacion;
        animacion = NULL;
    }

    if(body != NULL){
        delete body; 
        body = NULL;
    }

    if(class_textura != NULL){
        delete class_textura; 
        class_textura = NULL;
    }
}

void Cuerpo::Origen(float x, float y){
    body->setOrigin(x,y);
}
void Cuerpo::Scalar(float x, float y){
    body->setScale(x,y);
}


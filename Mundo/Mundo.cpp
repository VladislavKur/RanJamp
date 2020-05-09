#include "Mundo.h"

Mundo::Mundo(){

}


void Mundo::cargarmapa(const char * f){
  
  doc.LoadFile(f);
  map = new TiXmlElement("mapa");
  map = doc.FirstChildElement("map");
  if (map == nullptr) cout << "sadsad" <<  endl;
  map->QueryIntAttribute("width", &_width);
  map->QueryIntAttribute("height", &_height);
  map->QueryIntAttribute("tilewidth", &_tileWidth);
  map->QueryIntAttribute("tileheight", &_tileHeight);

  TiXmlElement * tileset = map->FirstChildElement("tileset");

  while(tileset){
     _numTilesets++;
    tileset = tileset->NextSiblingElement("tileset");
  }

  cout << endl;
  cout <<"numtileset =  " <<_numTilesets<<endl;

  imagenes = new TiXmlElement *[_numTilesets]; 
  _imgwidth = new int[_numTilesets];
  _imgheight = new int[_numTilesets];
  cambio = new int[_numTilesets];
  _tilesetTexture = new Textura *[_numTilesets];
  
  tileset = map->FirstChildElement("tileset");
  int num = 0;
  while(tileset){
    cout << "entro en el primer while"<<endl;
    tileset->QueryIntAttribute("tilecount", &cambio[num]);
    cout << " cambio " << cambio[num] << "  num " << num << endl;
    imagenes[num] =  tileset->FirstChildElement("image");
    tileset = tileset->NextSiblingElement("tileset");
    num++;
  }

  for(int i = 0; i < _numTilesets; i++){
    imagenes[i]->QueryIntAttribute("width", &_imgwidth[i]);
    imagenes[i]->QueryIntAttribute("height", &_imgheight[i]);
    string s = imagenes[i]->Attribute("source");
    _tilesetTexture[i] = new Textura(s);
    
  }

  TiXmlElement *layer = map->FirstChildElement("layer");
  if(layer == NULL){
      cout<<" ERRRORRRRR 2"<<endl;
  }else{
      cout<<"tengo algo 2" << endl;
  }
  
  while(layer){
    _numLayers++;
    layer = layer->NextSiblingElement("layer");
  }

  //reservar memoria
  _tilemap = new int **[_numLayers];
  for(int i = 0; i < _numLayers; i++){
    _tilemap[i] = new int * [_height];
  }
  for(int i = 0; i < _numLayers; i++){
    for(int j = 0; j < _height; j++){
      _tilemap[i][j] = new int [_width];
    }
  }

    //reservar memoria
  _tilemapSprite = new Bloque ***[_numLayers];
  for(int i = 0; i < _numLayers; i++){
    _tilemapSprite[i] = new Bloque ** [_height];
  }
  for(int i = 0; i < _numLayers; i++){
    for(int j = 0; j < _height; j++){
      _tilemapSprite[i][j] = new Bloque * [_width];
    }
  }

  TiXmlElement * layer2;
  TiXmlElement * data;
  cout<< "NUMERO DE CAPAS = " << _numLayers<< endl; 
  for(int l=0; l<_numLayers; l++){
    if( l == 0 ){
        layer2 = map->FirstChildElement("layer");
        data = layer2->FirstChildElement("data")->FirstChildElement("tile");
    }else{
        data = layer2->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
        layer2 = layer2->NextSiblingElement("layer");
        if(data != nullptr){
          cout<< "NUIDNSUONSIDN" << endl;
        }
    }
    for(int y=0; y<_height; y++){
      for(int x=0; x<_width; x++){ 
        data->QueryIntAttribute("gid", &_tilemap[l][y][x]);
        data = data->NextSiblingElement("tile");
      }
    }
  }

}

void Mundo::crearSprites(){

  for(int l=0; l<_numLayers; l++){
    // cout << "layers sprites: " << l << endl;
    for(int y=0; y<_height; y++){
     
      for(int x=0; x<_width; x++){
        // cout<<"X: " << x << "Y: " << y<<endl;
      int imagen = 0;
      bool pintada = false;
        for(int k = 0; k< _numTilesets && !pintada; k++){
          int gid = _tilemap[l][y][x];
          
          if(imagen != 0){
             
            gid = gid - cambio[k-1];
          }
          if(gid <=  cambio[k]){
           
            if(gid > cambio[k]){
              cout << "Error, gid at (l,x,y)= (" << l << "," << x << "," 
              << y << ") :" << gid << " fuera del rango del tileset (" 
              << _width*_height << ")" << endl;
            }else if(gid > 0){
              _tilemapSprite[l][y][x] = new Bloque(_tilesetTexture[k]);
              
              int Tcolumnas = _imgwidth[k] / _tileWidth; 
              int fila = (gid / Tcolumnas);
              int columna = (gid % Tcolumnas);
              if(columna == 0){
                fila = fila - 1;
                columna = Tcolumnas -1 ;
              }else{
                columna = columna - 1;
              }
              if(columna < 0){
                columna = 0;
              }
              _tilemapSprite[l][y][x]->setTextureRect(columna*32, fila*32, 32, 32);
              _tilemapSprite[l][y][x]->setPosition(x*_tileWidth, y*_tileHeight);
              pintada = true;
               
            }else{
              _tilemapSprite[l][y][x] = NULL;
            }
          }else{
            imagen++;
          }
        }
      }
    }
  }

}


 Cuerpo ** Mundo::getObjetos(){
   return objetos;
 }

Cuerpo ** Mundo::getObstaculos(){
   return objetos2;
}

Cuerpo ** Mundo::getMonedasLlaves(){
   return objetos3;
}

void Mundo::EliminarMonedasLLaves(Cuerpo * c){// hay que borrarlo y redimensionar el array
 
  for (int i = 0; i < _numObjects3; i++){
    if(objetos3[i] == c){
      for(int j = i; j < _numObjects3; j++){
        objetos3[j] = objetos3[j+1];        
      }
      objetos3[_numObjects3] = NULL;
      _numObjects3--;
    }
  }

}

void Mundo::crearObjetos(){

    TiXmlElement * object = objectgroups[0]->FirstChildElement("object");
    _numObjects = 0;
    while(object){
        object = object->NextSiblingElement("object");
        _numObjects++;
    }
    cout<< "numObjects " << _numObjects<< endl;
    objects = new TiXmlElement * [_numObjects];
    objetos = new Cuerpo * [_numObjects];
    
    object = objectgroups[0]->FirstChildElement("object");
    
    cout<<"object " << object->Attribute("id")<<endl;
    int num = 0; 
    while(object){
        objects[num] = object;
        object = object->NextSiblingElement("object");
        num++;
    }
    cout<< "num" << num <<endl; 
    
    for(int i=0; i < _numObjects; i++){
        objects[i]->QueryIntAttribute("width", &_widthObject);
        objects[i]->QueryIntAttribute("height", &_heightObject);
        objects[i]->QueryIntAttribute("x", &_x);
        objects[i]->QueryIntAttribute("y", &_y);
        objetos[i] = new Cuerpo(_x,_y, _widthObject,_heightObject);
        if(objetos[i] != nullptr ){
         cout<< "TENGOO ALGO" <<endl;
        }
    }
}
 


void Mundo::crearObstaculos(){
    TiXmlElement * object = objectgroups[6]->FirstChildElement("object");
    _numObjects2 = 0;
    while(object){
        object = object->NextSiblingElement("object");
        _numObjects2++;
    }
    cout<< "numObjects " << _numObjects2 << endl;
    objects2 = new TiXmlElement * [_numObjects2 ];
    objetos2 = new Cuerpo * [_numObjects2 ];
    
    object = objectgroups[6]->FirstChildElement("object");
    
    int num = 0; 
    while(object){
        objects2[num] = object;
        object = object->NextSiblingElement("object");
        num++;
    }
    cout<< "num" << num <<endl; 
    
    for(int i=0; i < _numObjects2; i++){
        objects2[i]->QueryIntAttribute("width", &_widthObject2);
        objects2[i]->QueryIntAttribute("height", &_heightObject2);
        objects2[i]->QueryIntAttribute("type", &_tipo2);
        objects2[i]->QueryIntAttribute("x", &_x2);
        objects2[i]->QueryIntAttribute("y", &_y2);
        objetos2[i] = new Cuerpo(_x2,_y2, _widthObject2,_heightObject2, _tipo2);//PASAR POR PARAMETRO EL TIPO AL CUERPO
        if(objetos2[i] != nullptr ){
         cout<< "TENGOO ALGO" <<endl;
        }
    }
}

void Mundo::crearMonedasLlaves(){
    TiXmlElement * object = objectgroups[7]->FirstChildElement("object");
    _numObjects3 = 0;
    while(object){
        object = object->NextSiblingElement("object");
        _numObjects3++;
    }
    cout<< "numObjects " << _numObjects3 << endl;
    objects3 = new TiXmlElement * [_numObjects3 ];
    objetos3 = new Cuerpo * [_numObjects3 ];
    
    object = objectgroups[7]->FirstChildElement("object");
    
    int num = 0; 
    while(object){
        objects3[num] = object;
        object = object->NextSiblingElement("object");
        num++;
    }
    cout<< "num" << num <<endl; 
    
    for(int i=0; i < _numObjects3; i++){
        objects3[i]->QueryIntAttribute("width", &_widthObject3);
        objects3[i]->QueryIntAttribute("height", &_heightObject3);
        objects3[i]->QueryIntAttribute("type", &_tipo3);
        objects3[i]->QueryIntAttribute("x", &_x3);
        objects3[i]->QueryIntAttribute("y", &_y3);
        if(_tipo3 == 0){
          objetos3[i] = new Cuerpo(_x3,_y3, _widthObject3,_heightObject3,"Moneda.png" , 0.2,1 , _tipo3);//PASAR POR PARAMETRO EL TIPO AL CUERPO
          objetos3[i]->addAnimacion(0.1);
        }else{
          objetos3[i] = new Cuerpo(_x3,_y3, _widthObject3,_heightObject3,"Llave.png" , 0.5, 0, _tipo3);
          objetos3[i]->addAnimacion(0.1);
        }
        if(objetos3[i] != nullptr ){
         cout<< "TENGOO ALGO" <<endl;
        }
    }
}

void Mundo::cargarObjectGroups(){
    TiXmlElement * objectgroup = map->FirstChildElement("objectgroup");
    int _numObjectgroups = 0;
    while(objectgroup){ // vemos cuantos hay
        objectgroup = objectgroup->NextSiblingElement("objectgroup");
        _numObjectgroups++;
    }
    objectgroups = new TiXmlElement * [_numObjectgroups];// reservamos memoria
    

    objectgroup = map->FirstChildElement("objectgroup");  // volvemos al primero
    int num = 0; 
    while(objectgroup){
        objectgroups[num] = objectgroup; // guardamos cada uno
        objectgroup = objectgroup->NextSiblingElement("objectgroup");
        num++;
    }
}

vector<vector<int>>  Mundo::cargarPosicionEnemigos_PowerUps(int i){
    vector<vector<int>> posiciones;
  
    TiXmlElement * object = objectgroups[i]->FirstChildElement("object"); // entramos en el primer object del segundo elemento de objectgroups 
    while(object){
        vector<int> dentro; 
        object->QueryIntAttribute("x" , &_posX);
        object->QueryIntAttribute("y" , &_posY);
        object->QueryIntAttribute("type", &_tipo);
        dentro.push_back(_posX);
        dentro.push_back(_posY);
        dentro.push_back(_tipo);
        posiciones.push_back(dentro);
        object = object->NextSiblingElement("object");
    }
    return posiciones;
}

vector<int>  Mundo::cargarPosicionBordes(){
    vector<int> posiciones;
  
    TiXmlElement * object = objectgroups[5]->FirstChildElement("object"); // entramos en el primer object del segundo elemento de objectgroups 
    int i = 0;
    while(object){
        object->QueryIntAttribute("x" , &_X);
        object->QueryIntAttribute("y" , &_Y);
        object->QueryIntAttribute("height" , &_Height);
        if(i == 0){
          int alto = _X; 
          int bajo = _X + _Height; 
          posiciones.push_back(alto);
          posiciones.push_back(bajo); 
          posiciones.push_back(alto);// izquierda
        }else if(i == 1){
          int derecha = _X; 
          posiciones.push_back(derecha); // derecha
        }
        object = object->NextSiblingElement("object");
        i++;
    }
    return posiciones;
}


vector<float> Mundo::cargarPosicionPlayer_Puerta(int i){
    vector<float> pos;
    TiXmlElement * object = objectgroups[i]->FirstChildElement("object"); // entramos en el primer object del segundo elemento de objectgroups 
    if(object){
        object->QueryIntAttribute("x" , &_posX);
        object->QueryIntAttribute("y" , &_posY);
        object->QueryIntAttribute("width" , &_widthP);
        object->QueryIntAttribute("height" , &_heightP);
        pos.push_back(_posX);
        pos.push_back(_posY);
    }
    if(i == 4){
      puerta = new Cuerpo(_posX,_posY, _widthP,_heightP);
    }
    return pos;
}

void Mundo::render(){

  for(int l=0; l<_numLayers-1; l++){
    for(int y=0; y<_height; y++){
      for(int x=0; x<_width; x++){
      int imagen = 0;
      bool pintada = false;
        for(int k = 0; k< _numTilesets && !pintada; k++){
          int gid = _tilemap[l][y][x];
          if(imagen != 0){
            gid = gid - cambio[k-1];
          }
          if(gid <=  cambio[k]){
            if(gid > cambio[k]){
              cout << "Error, gid at (l,x,y)= (" << l << "," << x << "," 
              << y << ") :" << gid << " fuera del rango del tileset (" 
              << _width*_height << ")" << endl;
            }else if(gid > 0){
              _tilemapSprite[l][y][x]->render(); 
              pintada = true;
            }else{
              _tilemapSprite[l][y][x] = NULL;
            }
          }else{
            imagen++;
          }
        }
      }
    }
  }
}

void Mundo::render2(){

  for(int l=_numLayers-1; l<_numLayers; l++){
    for(int y=0; y<_height; y++){
      for(int x=0; x<_width; x++){
      int imagen = 0;
      bool pintada = false;
        for(int k = 0; k< _numTilesets && !pintada; k++){
          int gid = _tilemap[l][y][x];
          if(imagen != 0){
            gid = gid - cambio[k-1];
          }
          if(gid <=  cambio[k]){
            if(gid > cambio[k]){
              cout << "Error, gid at (l,x,y)= (" << l << "," << x << "," 
              << y << ") :" << gid << " fuera del rango del tileset (" 
              << _width*_height << ")" << endl;
            }else if(gid > 0){
              _tilemapSprite[l][y][x]->render(); 
              pintada = true;
            }else{
              _tilemapSprite[l][y][x] = NULL;
            }
          }else{
            imagen++;
          }
        }
      }
    }
  }
}

int Mundo::getNumObjetos(){
  return _numObjects;
}

int Mundo::getNumObstaculos(){
  return _numObjects2;
}

int Mundo::getNumMonedasLlaves(){
  return _numObjects3;
}


Mundo::~Mundo(){ 
    //liberar memoria
    for(int i = 0; i < _numLayers; i++)
    {
        for(int j = 0; j < _height; j++)
        {
            delete[] _tilemap[i][j];
        }
        delete[] _tilemap[i];
    }
    delete[] _tilemap;

    delete[] _tilesetTexture;
    
    delete[] objetos;
    delete[] objetos2;
    delete[] objetos3;

    for(int i = 0; i < _numLayers; i++)
    {
        for(int j = 0; j < _height; j++)
        {
            delete[] _tilemapSprite[i][j];
        }
        delete[] _tilemapSprite[i];
    }
    delete[] _tilemapSprite;
    
    delete[] _imgwidth;
    delete[] _imgheight;
    delete[]  cambio;  
    delete puerta;
}

Cuerpo * Mundo::getPuerta(){
  return puerta;
}
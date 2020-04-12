#include "mapa.h"

mapa* mapa::pinstance=NULL;

mapa::mapa(){
  cargado = false;
}

mapa* mapa::instance(){

    if(pinstance == 0){

        pinstance = new mapa();

    }

    return(pinstance);
}

void mapa::setCargado(bool cambio){
  cargado = cambio;
}

void mapa::cargarmapa(const char * f){
  if(cargado == false){
    if(!doc.LoadFile(f)){
      cout<< "ERROR AL CARGAR EL DOCUMENTO"<<endl;
    }else{
      cout << "LO HE CARGADO" << endl;
      cargado = true;
    }
  }
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
  _tilesetTexture = new Texture[_numTilesets];
  
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
    const char *filename = imagenes[i]->Attribute("source");
    if(filename == NULL){
      cout<<" ERRRORRRRR file" << i<<endl;
    }else{
      cout<<"tengo algo file " << i << endl;
    }
    imagenes[i]->QueryIntAttribute("width", &_imgwidth[i]);
    imagenes[i]->QueryIntAttribute("height", &_imgheight[i]);

    if(!_tilesetTexture[i].loadFromFile(filename)){
      cout<<"NO SE CARGA LA TEXTURA = " << i <<endl;
    }else{
      cout<< "TENGO TEXTURA = " << i <<endl;
    }
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
  _tilemapSprite = new Sprite ***[_numLayers];
  for(int i = 0; i < _numLayers; i++){
    _tilemapSprite[i] = new Sprite ** [_height];
  }
  for(int i = 0; i < _numLayers; i++){
    for(int j = 0; j < _height; j++){
      _tilemapSprite[i][j] = new Sprite * [_width];
    }
  }

  TiXmlElement * data;
  for(int l=0; l<_numLayers; l++){
    if( l == 0 ){
        data = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    }else{
        data = map->NextSiblingElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    }
    for(int y=0; y<_height; y++){
      for(int x=0; x<_width; x++){ 
        data->QueryIntAttribute("gid", &_tilemap[l][y][x]);
        data = data->NextSiblingElement("tile");
      }
    }
  }

}

void mapa::crearSprites(){

  for(int l=0; l<_numLayers; l++){
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
              _tilemapSprite[l][y][x] = new Sprite(_tilesetTexture[k]);
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
              _tilemapSprite[l][y][x]->setTextureRect(IntRect(columna*32, fila*32, 32, 32));
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

 RectangleShape ** mapa::getObjetos(){
   return objetos;
 }

void mapa::crearObjetos(){

    // TiXmlElement * objectgroup = map->FirstChildElement("objectgroup");
    TiXmlElement * object = objectgroups[0]->FirstChildElement("object");
    _numObjects = 0;
    while(object){
        object = object->NextSiblingElement("object");
        _numObjects++;
    }
    cout<< "numObjects " << _numObjects<< endl;
    objects = new TiXmlElement * [_numObjects];
    objetos = new RectangleShape * [_numObjects];
    
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
        //cout << "OBJETO  ID = " << objects[i]->Attribute("id") << endl;
        objects[i]->QueryIntAttribute("width", &_widthObject);
        //cout << "width " << _widthObject<<endl;
        objects[i]->QueryIntAttribute("height", &_heightObject);
        //cout << "height " << _heightObject<<endl;
        objects[i]->QueryIntAttribute("x", &_x);
        //cout << "x " << _x<<endl;
        objects[i]->QueryIntAttribute("y", &_y);
        //cout << "y " << _y << endl;
        objetos[i] = new RectangleShape(Vector2f(_widthObject, _heightObject));
        if(objetos[i] != nullptr ){
         cout<< "TENGOO ALGO" <<endl;
        }
        objetos[i]->setPosition(_x,_y);
        objetos[i]->setFillColor(Color(255, 0 , 0));

        
    }
}

void mapa::cargarObjectGroups(){
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

vector<vector<int>>  mapa::cargarPosicionEnemigos_PowerUps(int i){
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

vector<int>  mapa::cargarPosicionBordes(){
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


Vector2f mapa::cargarPosicionPlayer_Puerta(int i){
    Vector2f pos;
    TiXmlElement * object = objectgroups[i]->FirstChildElement("object"); // entramos en el primer object del segundo elemento de objectgroups 
    if(object){
        object->QueryIntAttribute("x" , &_posX);
        object->QueryIntAttribute("y" , &_posY);
        pos.x = _posX;
        pos.y = _posY;
    }
    return pos;
}
void mapa::render(){

  Motor * motor = Motor::instance();
  for(int l=0; l<_numLayers; l++){
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
              motor->dibujo(*_tilemapSprite[l][y][x]);
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
  
   
  // for(int i=0; i < _numObjects; i++){
  //   motor->dibujo(*objetos[i]);
  // }
}


int mapa::getNumObjetos(){
  return _numObjects;
}


void mapa::liberar(){
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

    // int j = 0;
    // while (imagenes[j] != nullptr){
    //  delete[] imagenes[j];
    //  j++;
    // }
    delete[] imagenes;

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
    delete  map;
    delete[] _tilesetTexture;

    // for(int i = 0; i < _numTilesets; i++){
    //   delete[] objetos[i];
    // }
    delete[] objetos;
    
    // for(int i = 0; i < _numTilesets; i++){
    //   delete[] objects[i];
    // }
    delete[] objects;

    // for(int i = 0; i < _numTilesets; i++){
    //   delete[] objectgroups[i];
    // }
    delete[] objectgroups;
    
    //delete doc;
}
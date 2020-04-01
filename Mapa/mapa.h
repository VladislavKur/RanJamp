#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/System.hpp>
#include "tinyxml.h"

using namespace sf;
using namespace std;

class mapa{

    public:
       
        void cargarmapa(const char * f ); 
        void crearSprites();
        void crearObjetos();
        vector<Vector2f> cargarPosicionEnemigos_PowerUps(int i);
        void cargarObjectGroups();
        Vector2f cargarPosicionPlayer_Puerta(int i);
        void render(RenderWindow * ventana);
        static mapa *instance();
        RectangleShape ** getObjetos();
        
    protected:
            mapa();

    private:
      
        static mapa* pinstance;
        TiXmlDocument doc;
        TiXmlElement * map;
        VertexArray m_vertices;
        Texture m_tileset;
        int _activeLayer;
        int _width;
        int _height;
        int *_imgwidth;
        int *_imgheight;
        int * cambio;
        int _tileWidth;
        int _tileHeight;
        int _numLayers = 0;
        int _numTilesets = 0;
        int ***_tilemap;
        Sprite ****_tilemapSprite;
        Texture *_tilesetTexture;
        Sprite **_tilesetSprite;
        TiXmlElement ** imagenes;



        //objetos

        int _widthObject;
        int _heightObject;
        int _x;
        int _y;
        int _numObjects = 0;
        RectangleShape ** objetos;
        TiXmlElement ** objects;

        //enemigos
        int _posX;
        int _posY;
         TiXmlElement ** objectgroups;
};
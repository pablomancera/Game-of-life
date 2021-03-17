#include "cell.h"

// Constructor de la clase, inicializa su vida a falso.
cell::cell()
{
    live = false;
    tempLive = false;
}

/**
 * Actualiza la posición, tamaño y color de la célula con los parámetros dados.
 *
 * @brief cell::update
 * @param _x Posición x de la célula en pantalla.
 * @param _y Posición y de la célula en pantalla.
 * @param _width Ancho de la célula.
 * @param _height Alto de la célula.
 * @param _color Color de la célula.
 */
void cell::update(int _x, int _y, int _width, int _height, ofColor _color)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    color = _color;
}

/**
 * Dibuja la célula cada vez que se llama.
 *
 * @brief cell::draw
 */
void cell::draw()
{
    if (live) {
        ofSetColor(color);
    } else {
        ofSetColor(32);
    }
    ofDrawRectangle(x, y, width, height);
}
// Creo que el resto de funciones se explican solas.
int cell::getWidth()
{
    return width;
}
int cell::getHeight()
{
    return height;
}
int cell::getX()
{
    return x;
}
int cell::getY()
{
    return y;
}
void cell::kill()
{
    tempLive = false;
}
void cell::revive()
{
    tempLive = true;
}
void cell::toggleLife()
{
    tempLive = !tempLive;
}
void cell::updateStatus()
{
    live = tempLive;
}
bool cell::isAlive()
{
    return live;
}

#include "cell.h"

cell::cell()
{
    live = false;
    tempLive = false;
}
void cell::setup()
{

}
void cell::update(int _x, int _y, int _width, int _height, ofColor _color)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    color = _color;
}
void cell::draw()
{
    if (live) {
        ofSetColor(color);
    } else {
        ofSetColor(32);
    }
    ofDrawRectangle(x, y, width, height);
}
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

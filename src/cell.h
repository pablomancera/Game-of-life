#ifndef CELL_H
#define CELL_H

#include "ofMain.h"

class cell
{
public:

    void setup();
    void update(int _x, int _y, int _width, int _height, ofColor _color);
    void draw();
    int getWidth();
    int getHeight();
    int getX();
    int getY();
    void kill();
    void revive();
    void toggleLife();
    void updateStatus();
    void select();
    void deselect();
    bool isSelected();
    bool isAlive();
    cell();

private:
    bool live;
    bool tempLive;
    ofColor color;
    bool selected;
    int x;
    int y;
    int width;
    int height;
};

#endif // CELL_H

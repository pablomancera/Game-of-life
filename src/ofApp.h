#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "cell.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    bool frameLimiter(int frames);
    void updateCells();
    void randomizer();
    void resetOffset();
    int checkNeighbours(glm::vec2 cellVec);
    ofColor getRGB();
    int colores[3];
    vector<vector<cell>> cells;
    glm::vec2 prevColRow;
    glm::vec2 offsetXY;
    glm::vec2 prevOffsetXY;
    glm::vec2 mouseClickPos;
    void cellsSetup();
    ofxToggle pause;
    ofxIntSlider frames;
    ofxIntSlider cellSize;
    ofxIntSlider cellNumCol;
    ofxIntSlider cellNumRow;
    ofxToggle gamerMode;
    ofxButton randomize;
    ofxButton clearbtn;
    ofxButton resetOffsetbtn;
    ofxPanel gui;

};

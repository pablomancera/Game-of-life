#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "cell.h"
#include "filepatternparser.h"

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
    void switchCurrentPattern(const void * _ofBool, bool & value);
    void computeCellsEvents(glm::vec2 mousePos);
    glm::vec2 hoveredCellIndex;
    ofColor getRGB();
    int colores[3];
    string currentPattern;
    vector<vector<cell>> cells;
    vector<string> patternKeys;
    map<string, tuple<glm::vec2, glm::vec2, vector<glm::vec2>>> patterns;
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
    ofxIntSlider randomRange;
    ofxToggle gamerMode;
    ofxButton randomize;
    ofxButton clearbtn;
    ofxButton resetOffsetbtn;
    ofxPanel gui;
    ofxGuiGroup guiPatterns;
    vector<ofxToggle> togglesPattern;
    ofEvent<glm::vec2> cellMouseIn;
    ofEvent<glm::vec2> cellMouseOut;
    void onCellMouseIn(glm::vec2 & _cellIndex);
    void onCellMouseOut(glm::vec2 & _cellIndex);
    bool switchingPatterns;
    void selectCells();
    void deselectCells();
    void selected2alive();
};

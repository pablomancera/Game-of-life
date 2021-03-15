#include "ofApp.h"
#define CELL_SIZE 25
#define NUM_COL_CELLS 25
#define NUM_ROW_CELLS 25

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    gui.setup();
    gui.add(frames.setup("FPS", 60, 1, 60));
    gui.add(cellSize.setup("Tamano de celdas", CELL_SIZE, 10, 50));
    gui.add(cellNumRow.setup("Numero de columnas", NUM_ROW_CELLS, 10, 100));
    gui.add(cellNumCol.setup("Numero de filas", NUM_COL_CELLS, 10, 100));
    gui.add(gamerMode.setup("Modo geimer", false, 25, 25));
    prevColRow = glm::vec2(NUM_ROW_CELLS, NUM_COL_CELLS);
    offsetXY = glm::vec2(0, 0);
    prevOffsetXY = glm::vec2(0, 0);
    mouseClickPos = glm::vec2(0, 0);
    colores[0] = 255;
    colores[1] = 0;
    colores[2] = 0;
    cellsSetup();
}

//--------------------------------------------------------------
void ofApp::update(){
    if (cellNumRow != prevColRow.x || cellNumCol != prevColRow.y) {
        cellsSetup();
        prevColRow.x = cellNumRow;
        prevColRow.y = cellNumCol;
    }
    if (frameLimiter(frames)) {
        for (int i = 0; i < cells.size(); i++) {
            for (int j = 0; j < cells[i].size(); j++) {
                glm::vec2 cellPos(i, j);
                if (!pause) {
                    int neighbours = checkNeighbours(cellPos);
                    if (neighbours < 2 || neighbours > 3) {
                        cells[i][j].kill();
                    } else if (neighbours == 3) {
                        cells[i][j].revive();
                    }
    //                std::cout << "la cell " << i << " " << j << " tiene " << state << " vecinos." << endl;
                }
            }
        }
        updateCells();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofColor geimer = gamerMode ? getRGB() : ofColor(255);
    int hOffset = (ofGetHeight()/2-(cellNumCol*(cellSize+5)/2)) + offsetXY.y;
    int wOffset = (ofGetWidth()/2-(cellNumRow*(cellSize+5)/2)) + offsetXY.x;
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j].update(i*(cellSize+5)+wOffset, j*(cellSize+5)+hOffset, cellSize, cellSize, geimer);
            cells[i][j].draw();
        }
    }
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 32) {
        pause = !pause;
    }
    if (key == 'r') {
        randomizer();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if (button == OF_MOUSE_BUTTON_RIGHT) {
        offsetXY.x = prevOffsetXY.x + (x - mouseClickPos.x);
        offsetXY.y = prevOffsetXY.y + (y - mouseClickPos.y);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (button == OF_MOUSE_BUTTON_LEFT) {
        for (int i = 0; i < cells.size(); i++) {
            for (int j = 0; j < cells[i].size(); j++) {
                glm::vec2 mousePos(x, y);
                glm::vec2 distanceTopLeft(cells[i][j].getX(), cells[i][j].getY());
                glm::vec2 distanceBotRight(cells[i][j].getX()+cellSize, cells[i][j].getY()+cellSize);

                if (mousePos.x > distanceTopLeft.x &&
                        mousePos.y > distanceTopLeft.y &&
                        mousePos.x < distanceBotRight.x &&
                        mousePos.y < distanceBotRight.y) {
                    cells[i][j].toggleLife();
                }
            }
        }
    }
    if (button == OF_MOUSE_BUTTON_RIGHT) {
        prevOffsetXY = glm::vec2(offsetXY);
        mouseClickPos = glm::vec2(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (button == OF_MOUSE_BUTTON_RIGHT) {
        offsetXY.x = prevOffsetXY.x + (x - mouseClickPos.x);
        offsetXY.y = prevOffsetXY.y + (y - mouseClickPos.y);
        prevOffsetXY = glm::vec2(offsetXY);
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
int ofApp::checkNeighbours(glm::vec2 cellVec)
{
    int neighbours = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if ((i == 0 && j == 0) ||
                    cellVec.x + i < 0 ||
                    cellVec.x + i > cells.size()-1 ||
                    cellVec.y + j < 0 ||
                    cellVec.y + j > cells[cellVec.y].size()-1) {
                continue;
            }
            if (cells[cellVec.x+i][cellVec.y+j].isAlive()) {
                neighbours++;
            }
        }
    }
    return neighbours;
}

void ofApp::updateCells()
{
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j].updateStatus();
        }
    }
}

bool ofApp::frameLimiter(int frames)
{
    if (pause || ofGetFrameNum() % (60/frames) == 0) {
        return true;
    } else {
        return false;
    }
}

void ofApp::cellsSetup()
{
    pause = true;
    cells.clear();
    for (int i = 0; i < cellNumRow; i++) {
        vector<cell> rowCells;
        for (int j = 0; j < cellNumCol; j++) {
            cell tempCell;
            rowCells.push_back(tempCell);
        }
        cells.push_back(rowCells);
    }
}

ofColor ofApp::getRGB()
{
    ofColor geimer;
    for (int color = 0; color < 3; color++) {
        int anterior = 2;
        if (color > 0) {
            anterior = color - 1;
        }
        if (colores[color] == 255) {
            colores[color] = -colores[color];
        }
        if (colores[anterior] < 0) {
            colores[color]++;
            colores[anterior]++;
        }
    }
    geimer.r = abs(colores[0]);
    geimer.g = abs(colores[1]);
    geimer.b = abs(colores[2]);

    return geimer;
}

void ofApp::randomizer()
{
    cellsSetup();
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            int rnd = (int) ofRandom(0, 2);
            if (rnd == 1) {
                cells[i][j].revive();
            }
        }
    }
}

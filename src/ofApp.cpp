/*
 * En esta clase se corre la mayoría de la lógica del programa.
 */

#include "ofApp.h" //Se incluye este header necesario para el funcionamiento de OF.

// Constantes para el tamaño predeterminado de celdas, número de columnas y filas respectivamente.
#define CELL_SIZE 25
#define NUM_COL_CELLS 25
#define NUM_ROW_CELLS 25

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

    // Inicializamos los controles gráficos
    gui.setup();
    gui.add(frames.setup("FPS", 60, 1, 60));
    gui.add(cellSize.setup("Tamano de celdas", CELL_SIZE, 5, 50));
    gui.add(cellNumRow.setup("Numero de columnas", NUM_ROW_CELLS, 5, 100));
    gui.add(cellNumCol.setup("Numero de filas", NUM_COL_CELLS, 5, 100));
    gui.add(gamerMode.setup("Modo geimer", false));
    gui.add(randomize.setup("Randomizar"));
    gui.add(clearbtn.setup("Limpiar"));
    gui.add(resetOffsetbtn.setup("Resetear camara"));
    gui.add(pause.setup("Pausa ||", true));
    randomize.addListener(this, &ofApp::randomizer);
    clearbtn.addListener(this, &ofApp::cellsSetup);
    resetOffsetbtn.addListener(this, &ofApp::resetOffset);

    // Inicializamos variables del programa.
    prevColRow = glm::vec2(NUM_ROW_CELLS, NUM_COL_CELLS);
    offsetXY = glm::vec2(0, 0);
    prevOffsetXY = glm::vec2(0, 0);
    mouseClickPos = glm::vec2(0, 0);
    // Variables para el RGB, sólo una puede estar a 255, las otras tienen que estar en 0.
    colores[0] = 255;
    colores[1] = 0;
    colores[2] = 0;

    cellsSetup();
}

//--------------------------------------------------------------
void ofApp::update(){

    // Revisa si se ha cambiado el número de celdas para resetearlas.
    if (cellNumRow != prevColRow.x || cellNumCol != prevColRow.y) {
        cellsSetup();
        prevColRow.x = cellNumRow;
        prevColRow.y = cellNumCol;
    }

    // Calcula y cambia el estado de las celdas con la frecuencia que se pase a la variable frames.
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
                }
            }
        }
        updateCells();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofColor geimer = gamerMode ? getRGB() : ofColor(255); // Define el color de las celdas en función de la variable geimer.

    // Hacemos los cálculos para desplazar las celdas la cantidad que necesitemos, usualmente para centrarlas.
    int hOffset = (ofGetHeight()/2-(cellNumCol*(cellSize+5)/2)) + offsetXY.y;
    int wOffset = (ofGetWidth()/2-(cellNumRow*(cellSize+5)/2)) + offsetXY.x;

    // Actualiza posición, tamaño y color de las celdas y las dibuja.
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j].update(i*(cellSize+5)+wOffset, j*(cellSize+5)+hOffset, cellSize, cellSize, geimer);
            cells[i][j].draw();
        }
    }

    // Dibuja los controles gráficos
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // Alterna la pausa con la tecla espacio.
    if (key == 32) {
        pause = !pause;
    }

    // Activa el generador aleatorio con la tecla 'r'.
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

    // La mitad del "movimiento de cámara".
    // Calcula la distancia del mouse desde que se hizo click hasta su posición actual, y mueve las células.
    if (button == OF_MOUSE_BUTTON_RIGHT) {
        offsetXY.x = prevOffsetXY.x + (x - mouseClickPos.x);
        offsetXY.y = prevOffsetXY.y + (y - mouseClickPos.y);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    // Da vida a la celda a la que se le hace click.
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

    // Empieza el "movimiento de cámara", que en realidad mueve las células.
    // Guarda el offset actual de las células, y la posición actual del mouse.
    if (button == OF_MOUSE_BUTTON_RIGHT) {
        prevOffsetXY = glm::vec2(offsetXY);
        mouseClickPos = glm::vec2(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // Parte final del "movimiento de cámara".
    // Aplica los cambios.
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
/**
 * Devuelve la cantidad de vecinos que rodean a una célula.
 *
 * @brief ofApp::checkNeighbours
 * @param cellVec La posición del vector de células en la que se encuentra la célula a consultar.
 * @return Número de células que rodean a la célula.
 */
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

/**
 * Aplica los cambios en las células dependiendo de si deberían estar vivas o no.
 *
 * @brief ofApp::updateCells
 */
void ofApp::updateCells()
{
    for (int i = 0; i < cells.size(); i++) {
        for (int j = 0; j < cells[i].size(); j++) {
            cells[i][j].updateStatus();
        }
    }
}

/**
 * Limita la velocidad con la que se da una nueva generación de células.
 *
 * @brief ofApp::frameLimiter
 * @param frames La cantidad de frames por segundo, o generaciones por segundo.
 * @return Si debería ejecutarse el código o no.
 */
bool ofApp::frameLimiter(int frames)
{
    // Obtenemos la cantidad de frames que se han generado desde que iniciamos el programa
    // y da verdadero cuando debería dejar ejecutar el código.
    if (pause || ofGetFrameNum() % (60/frames) == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * Resetea las celdas. Las elimina todas y las vuelve a crear.
 *
 * @brief ofApp::cellsSetup
 */
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

/**
 * Obtiene un color del espectro RGB con un patrón cíclico cada vez que se llama.
 *
 * @brief ofApp::getRGB
 * @return Un color del espectro RGB similar al anterior devuelto.
 */
ofColor ofApp::getRGB() // Posiblemente esta función podría realizarse de una mejor manera.
{
    ofColor geimer;

    //Se calcula cada color con relación al anterior devuelto por la fución.
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

/**
 * Define el estado de cada celda aleatoriamente, posiblemente en una probabilidad de 50/50.
 *
 * @brief ofApp::randomizer
 */
void ofApp::randomizer()
{
    // TODO: hacer que la probabilidad sea dada por el usuario.
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

/**
 * Resetea la "cámara" de modo que las celdas aparezcan centradas.
 *
 * @brief ofApp::resetOffset
 */
void ofApp::resetOffset()
{
    offsetXY = glm::vec2(0, 0);
    prevOffsetXY = glm::vec2(0, 0);
}

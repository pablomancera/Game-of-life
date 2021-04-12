#ifndef FILEPATTERNPARSER_H
#define FILEPATTERNPARSER_H

#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>
#include "ofMain.h"

class filePatternParser
{
public:
    filePatternParser(std::string dir = "");
    void parse(std::string dir);
    map<string, tuple<glm::vec2, glm::vec2, vector<glm::vec2>>> getParsedData(void);
    vector<string> getKeys(void);
private:
    map<string, tuple<glm::vec2, glm::vec2, vector<glm::vec2>>> parsedData;
    vector<string> keys;
};

#endif // FILEPATTERNPARSER_H

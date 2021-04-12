#include "filepatternparser.h"

using namespace std;

filePatternParser::filePatternParser(string dir)
{
    if (dir != "") {
        parse(dir);
    }
}

map<string, tuple<glm::vec2, glm::vec2, vector<glm::vec2>>> filePatternParser::getParsedData()
{
    map<string, tuple<glm::vec2, glm::vec2, vector<glm::vec2>>> _info = parsedData;
    return _info;
}

vector<string> filePatternParser::getKeys()
{
    vector<string> _keys = keys;
    return _keys;
}

void filePatternParser::parse(string dir)
{
    std::ifstream file;
    file.open(dir);
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        char * cLine = (char*) line.c_str();
        char * word = strtok(cLine, " ");
        if (word != NULL && string(word) == "startp") {
            string patternName = std::string(strtok(NULL, " "));
            keys.push_back(patternName);
            tuple<glm::vec2, glm::vec2, vector<glm::vec2>> params;
            getline(file, line);
            while (line != "endp") {
                char * cLine = (char*) line.c_str();
                const char exclude[] = {'\t', ' ', '='};
                char * word = strtok(cLine, exclude);

                if (word != NULL && (string(word) == "size" || string(word) == "mousepos")) {
                    int i = 0;
                    int xy[2] = {0, 0};
                    string patternProp = string(word);
                    word = strtok(NULL, exclude);
                    while (word != NULL) {
                        xy[i] = stoi(string(word));
                        i++;
                        word = strtok(NULL, exclude);
                    }
                    glm::vec2 pos(xy[0], xy[1]);
                    patternProp == "size" ? get<0>(params) = pos : get<1>(params) = pos;
                }

                if (word != NULL && string(word) == "startcell") {
                    vector<glm::vec2> pos;
                    getline(file, line);

                    while (word != NULL && string(word) != "endcell") {
                        char * cLine = (char*) line.c_str();
                        const char exclude[] = {'\t', ' '};
                        char * word = strtok(cLine, exclude);

                        int xy[2] = {0, 0};

                        xy[0] = stoi(string(word));

                        word = strtok(NULL, exclude);
                        xy[1] = stoi(string(word));

                        pos.push_back(glm::vec2(xy[0], xy[1]));
                        getline(file, line);
                    }
                    get<2>(params) = pos;
                }
                getline(file, line);
            }
            parsedData[patternName] = params;
        }
    }

    file.close();

//    for (auto it = parsedData.begin(); it != parsedData.end(); it++) {
//        cout << it->first << endl;
//        cout << '\t' << "size: " << get<0>(it->second) << endl;
//        cout << '\t' << "mousepos: " << get<1>(it->second) << endl;
//        cout << '\t' << "startcell" << endl;
//        for (auto it2 = get<2>(it->second).begin(); it2 != get<2>(it->second).end(); it2++) {
//            cout << '\t' << '\t' << *it2 << endl;
//        }
//    }
}

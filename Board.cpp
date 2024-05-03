#include "Board.h"
#include <random>
#include <fstream>

mt19937 random_mt;

int Random(int min, int max){
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);}


Board::Board() {

    fstream boardConfig("files/config.cfg");

    string columnInfoString;
    getline(boardConfig,columnInfoString);
    this->columns = stoi(columnInfoString);

    string rowInfoString;
    getline(boardConfig,rowInfoString);
    this->rows= stoi(rowInfoString);

    this->tiles=(this->rows)*(this->columns);

    string mineCountInfoString;
    getline(boardConfig,mineCountInfoString);
    this->mines = stoi(mineCountInfoString);

    this->flags = mines;

    this->is_debugMode = false;
    this->is_paused = false;
    this->leaderBoard = false;
    this->l = false;
    this->w = false;

    for (unsigned i = 0; i < rows; i++) {
        vector<Tile*> *a = new vector<Tile *>;
        for (unsigned j = 0; j < columns; j++) {
            Tile *tempPointer = new Tile(j, i);
            a->push_back(tempPointer);
        }
        dsc.push_back(a);
    }

    for (int i = 0; i < this->mines; i++) {

        int randomRow = Random(0, rows - 1);
        int randomColumn = Random(0, columns - 1);

        if (dsc.at(randomRow)->at(randomColumn)->mineexists)
        {
            i --;
        }
        else {
            dsc.at(randomRow)->at(randomColumn)->mineexists = true;
        }
    }

    for (int i = 0; i < dsc.size(); i++) {
        for (int j = 0; j < dsc.at(i)->size(); j++) {

            if (j - 1 >= 0) {
                dsc.at(i)->at(j)->tilepoint.push_back(dsc.at(i)->at(j - 1));
            }

            if ((i - 1 >= 0) && (j - 1 >= 0)) {
                dsc.at(i)->at(j)->tilepoint.push_back(dsc.at(i - 1)->at(j - 1));
            }

            if (i - 1 >= 0) {
                dsc.at(i)->at(j)->tilepoint.push_back(dsc.at(i - 1)->at(j));
            }

            if ((i - 1 >= 0) && (j + 1 <= columns - 1)) {
                dsc.at(i)->at(j)->tilepoint.push_back(dsc.at(i - 1)->at(j + 1));
            }

            if (j + 1 <= columns - 1) {
                dsc.at(i)->at(j)->tilepoint.push_back(dsc.at(i)->at(j + 1));
            }

            if ((i + 1 <= rows - 1) && (j + 1 <= columns - 1)) {
                dsc.at(i)->at(j)->tilepoint.push_back(dsc.at(i + 1)->at(j + 1));
            }

            if (i + 1 <= rows - 1) {
                dsc.at(i)->at(j)->tilepoint.push_back(dsc.at(i + 1)->at(j));
            }

            if ((i + 1 <= rows - 1) && (j - 1 >= 0)) {
                dsc.at(i)->at(j)->tilepoint.push_back(dsc.at(i + 1)->at(j - 1));\

            }


            if (!dsc.at(i)->at(j)->mineexists) {
                for (unsigned int k = 0; k < dsc.at(i)->at(j)->tilepoint.size(); k++) {
                    if (dsc.at(i)->at(j)->tilepoint.at(k)->mineexists)
                        dsc.at(i)->at(j)->mines ++;
                }
            }
        }
    }
}

void Board::draw(RenderWindow& window) {
    for (unsigned i=0; i < dsc.size(); i++){
        for (unsigned j=0; j < dsc.at(i)->size(); j++){
            dsc.at(i)->at(j)->draw(window, this->is_debugMode, this-> is_paused, this->leaderBoard, this->l, this->w);
        }
    }
}

void Board::debugswitch() {
    if (is_debugMode)
        is_debugMode= false;
    else if (!is_debugMode)
        is_debugMode= true;
}

void Board::pauseswitch() {
    if (is_paused)
        is_paused= false;
    else if (!is_paused)
        is_paused= true;
}

void Board::lbswitch() {
    if(leaderBoard)
        leaderBoard= false;
    else if(!leaderBoard)
        leaderBoard= true;
}

void Board::hidetiles() {
    for (unsigned i=0; i < dsc.size(); i++){
        for (unsigned j=0; j < dsc.at(i)->size(); j++){
            dsc.at(i)->at(j)->showed= false;}
    }
}

void Board::showtiles() {
    for (unsigned i=0; i < dsc.size(); i++){
        for (unsigned j=0; j < dsc.at(i)->size(); j++){
            dsc.at(i)->at(j)->showed= true;}
    }
}

void Board::show(RenderWindow& window,Tile* tile) {
    if(tile->flaggedTile)
        return;

    tile->showed= true;

    if (tile->mines == 0 && tile->turnOn) {
        for (unsigned int i=0; i<tile->tilepoint.size();i++) {
            if (!tile->tilepoint.at(i)->showed&&tile->tilepoint.at(i)->turnOn)
                show(window, tile->tilepoint.at(i));
        }
    }
}

bool Board::wcheck() {
    short count=0;
    for (unsigned i=0; i < dsc.size(); i++){
        for (unsigned j=0; j < dsc.at(i)->size(); j++) {
            if (!dsc.at(i)->at(j)->mineexists && dsc.at(i)->at(j)->showed) {
                count++;
                if(count == (tiles - mines))
                    return true;
            }
        }
    }
    return false;
}

void Board::clear() {
    for (unsigned i = 0; i < dsc.size(); i++) {
        vector<Tile*>* a = dsc.at(i);
        for (unsigned j = 0; j < a->size(); j++){
            delete a->at(j);}
        delete a;
    }
}

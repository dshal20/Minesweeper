#pragma once
#include "Tile.h"

struct Board {

    // main board structure
    int rows;
    int columns;
    int tiles;

    // minesweeper game components
    int flags;
    int mines;

    vector<vector<Tile*>*> dsc;


    bool is_debugMode;

    bool is_paused;

    bool leaderBoard;

    bool l;
    bool w;

    Board();

    void draw(RenderWindow& window);

    void debugswitch();
    void pauseswitch();
    void lbswitch();
    void hidetiles();
    void showtiles();

    void show(RenderWindow& window,Tile* tile);
    bool wcheck();
    void clear();

};

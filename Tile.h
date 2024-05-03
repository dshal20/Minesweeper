#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

using namespace sf;

class Tile {
    Texture hiddenTileTexture;
    Texture revealedTileTexture;
    Texture mineTexture;
    Texture flagTexture;
    Texture OneTexture;
    Texture TwoTexture;
    Texture ThreeTexture;
    Texture FourTexture;
    Texture FiveTexture;
    Texture SixTexture;
    Texture SevenTexture;
    Texture EightTexture;

public:
    Sprite sprite;
    vector<Tile*> tilepoint;

    bool mineexists;
    bool flaggedTile;
    bool turnOn;
    bool showed;
    int mines;

    Tile(int x, int y);
    void draw(RenderWindow& window, bool is_debugMode, bool is_paused,bool leaderBoard, bool loser, bool winner);



    void toggleFlag();
};

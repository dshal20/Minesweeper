#include "Tile.h"

Tile::Tile( int x, int y) {
    hiddenTileTexture.loadFromFile("files/images/tile_hidden.png");
    revealedTileTexture.loadFromFile("files/images/tile_revealed.png");
    mineTexture.loadFromFile("files/images/mine.png");
    flagTexture.loadFromFile("files/images/flag.png");
    OneTexture.loadFromFile("files/images/number_1.png");
    TwoTexture.loadFromFile("files/images/number_2.png");
    ThreeTexture.loadFromFile("files/images/number_3.png");
    FourTexture.loadFromFile("files/images/number_4.png");
    FiveTexture.loadFromFile("files/images/number_5.png");
    SixTexture.loadFromFile("files/images/number_6.png");
    SevenTexture.loadFromFile("files/images/number_7.png");
    EightTexture.loadFromFile("files/images/number_8.png");

    this->mines = 0;

    this->sprite.setPosition(x * 32, y * 32);

    flaggedTile = false;
    mineexists = false;
    showed = false;
    turnOn= true;
}

void Tile::draw(RenderWindow& window, bool is_debugMode, bool is_paused, bool leaderBoard, bool loser, bool winner) {
    if (is_debugMode && mineexists) {
        this->sprite.setTexture(hiddenTileTexture);
        window.draw(this->sprite);

        if(flaggedTile){
            this->sprite.setTexture(flagTexture);
            window.draw(this->sprite);}

        this->sprite.setTexture(mineTexture);
        window.draw(this->sprite);}
    else if (is_debugMode && !mineexists) {
        if(!showed && !flaggedTile){
            this->sprite.setTexture(hiddenTileTexture);
            window.draw(this->sprite);}
        else if(!showed && flaggedTile){
            this->sprite.setTexture(hiddenTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(flagTexture);
            window.draw(this->sprite);}
        else if (showed && mines==0) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);}
        else if (showed && mines==1) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(OneTexture);
            window.draw(this->sprite);}
        else if (showed && mines==2) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(TwoTexture);
            window.draw(this->sprite);}
        else if (showed && mines==3) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(ThreeTexture);
            window.draw(this->sprite);}
        else if (showed && mines==4) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(FourTexture);
            window.draw(this->sprite);}
        else if (showed && mines==5) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(FiveTexture);
            window.draw(this->sprite);}
        else if (showed && mines==6) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(SixTexture);
            window.draw(this->sprite);}
        else if (showed && mines==7) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(SevenTexture);
            window.draw(this->sprite);}
        else if (showed && mines==8) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(EightTexture);
            window.draw(this->sprite);}
    }
    else if (loser && mineexists) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);
        if (flaggedTile){
            this->sprite.setTexture(flagTexture);
            window.draw(this->sprite);}
        this->sprite.setTexture(mineTexture);
        window.draw(this->sprite);}
    else if (winner && mineexists) {
        this->sprite.setTexture(hiddenTileTexture);
        window.draw(this->sprite);
        this->sprite.setTexture(flagTexture);
        window.draw(this->sprite);
    }
    else if (loser && !mineexists) {
        if(!showed){
            this->sprite.setTexture(hiddenTileTexture);
            window.draw(this->sprite);}
        else if (showed && mines==0) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);}
        else if (showed && mines==1) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(OneTexture);
            window.draw(this->sprite);}
        else if (showed && mines==2) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(TwoTexture);
            window.draw(this->sprite);}
        else if (showed && mines==3) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(ThreeTexture);
            window.draw(this->sprite);}
        else if (showed && mines==4) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(FourTexture);
            window.draw(this->sprite);}
        else if (showed && mines==5) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(FiveTexture);
            window.draw(this->sprite);}
        else if (showed && mines==6) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(SixTexture);
            window.draw(this->sprite);}
        else if (showed && mines==7) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(SevenTexture);
            window.draw(this->sprite);}
        else if (showed && mines==8) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(EightTexture);
            window.draw(this->sprite);}
    }
    else if (winner && !mineexists) {
        if(mines==0){
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
        }
        else if (mines==1) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(OneTexture);
            window.draw(this->sprite);}
        else if (mines==2) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(TwoTexture);
            window.draw(this->sprite);}
        else if (mines==3) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(ThreeTexture);
            window.draw(this->sprite);}
        else if (mines==4) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(FourTexture);
            window.draw(this->sprite);}
        else if (mines==5) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(FiveTexture);
            window.draw(this->sprite);}
        else if (mines==6) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(SixTexture);
            window.draw(this->sprite);}
        else if (mines==7) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(SevenTexture);
            window.draw(this->sprite);}
        else if (mines==8) {
            this->sprite.setTexture(revealedTileTexture);
            window.draw(this->sprite);
            this->sprite.setTexture(EightTexture);
            window.draw(this->sprite);}
    }
    else if (!showed && !flaggedTile && turnOn) {
        this->sprite.setTexture(hiddenTileTexture);
        window.draw(this->sprite);}
    else if(!showed && flaggedTile) {
        this->sprite.setTexture(hiddenTileTexture);
        window.draw(this->sprite);
        this->sprite.setTexture(flagTexture);
        window.draw(this->sprite);
    }
    else if (showed && mines==0 && !mineexists) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);}
    else if (showed && mines == 1 && turnOn && !mineexists) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);
        this->sprite.setTexture(OneTexture);
        window.draw(this->sprite);}
    else if (showed && mines==2 && turnOn && !mineexists) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);
        this->sprite.setTexture(TwoTexture);
        window.draw(this->sprite);}
    else if (showed && mines==3 && turnOn && !mineexists) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);
        this->sprite.setTexture(ThreeTexture);
        window.draw(this->sprite);}
    else if (showed && mines==4 && turnOn && !mineexists) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);
        this->sprite.setTexture(FourTexture);
        window.draw(this->sprite);}
    else if (showed && mines==5 && turnOn && !mineexists) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);
        this->sprite.setTexture(FiveTexture);
        window.draw(this->sprite);}
    else if (showed && mines==6 && turnOn && !mineexists) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);
        this->sprite.setTexture(SixTexture);
        window.draw(this->sprite);}
    else if (showed && mines==7 && turnOn && !mineexists) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);
        this->sprite.setTexture(SevenTexture);
        window.draw(this->sprite);}
    else if (showed && mines==8 && turnOn && !mineexists) {
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);
        this->sprite.setTexture(EightTexture);
        window.draw(this->sprite);}
    if (is_paused){
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);}
    if (leaderBoard &&!winner){
        this->sprite.setTexture(revealedTileTexture);
        window.draw(this->sprite);}
}
void Tile::toggleFlag() {
    if (this->flaggedTile)
        this->flaggedTile=false;

    else if (!this->flaggedTile)
        this->flaggedTile=true;
}

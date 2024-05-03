#include <SFML/Graphics.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include "Board.h"

#include <cctype>
#include <sstream>
using namespace std; using namespace sf;


struct player {

    short gameTime;
    string name;




};

void textPos(Text &string, float x, float y) {
    FloatRect textRect = string.getLocalBounds();

    string.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    string.setPosition(Vector2f(x, y));
}

Text textInfo(const string& tstring, Font& font, short s, Color c, float x, float y) {
    Text text(tstring, font,s);

    text.setFillColor(c);

    textPos(text,x,y);

    return text;
}


class timer {
    Clock gameClock;
    Time gameTime;
    bool pause = false;
public:
    timer() {
        gameTime=Time::Zero;
        gameClock.restart();
    }

    void start() {
        if (pause) {
            gameClock.restart();
            pause = false;
        }
    }

    void stop() {
        if (!pause){
            gameTime += gameClock.getElapsedTime();
            pause = true;
        }
    }

    void restart() {
        gameTime = Time::Zero;
        gameClock.restart();
    }

    Time getElapsedTime(){
        if (!pause)
            return gameTime + gameClock.getElapsedTime();
        else
            return gameTime;
    }

    bool isPaused(){
        return pause;}
};

int main() {

    Board minesweeper;
    int width = minesweeper.columns * 32;
    int height = minesweeper.rows * 32 + 100;
    int lbwidth = minesweeper.columns * 16;
    int lbheight = minesweeper.rows * 16 + 50;

    // FOR FONT
    Font font;

    fstream fontFile("files/font.ttf");


    if (!font.loadFromFile("files/font.ttf"))
        cout << "font not loaded";

    String name;
    Text pname;

    RenderWindow welcome(VideoMode(width, height), "Minesweeper");
    while (welcome.isOpen()) {
        Event event;

        // "WELCOME TO MINESWEEPER!" BOLD UNDERLINED COLOR WHITE 24PX width/2 - height/2 - 150
        Text wtext=textInfo("WELCOME TO MINESWEEPER!",font, 24,Color::White,width / 2.0f,(height / 2.0f) - 150);
        wtext.setStyle(Text::Bold| Text::Underlined);
        // "ENTER YOUR NAME BOLD COLOR WHITE 20 PX WIDTH/2 HEIGHT/2 - 75
        Text inputName=textInfo("Enter your name:",font, 20,Color::White,width / 2.0f,(height / 2.0f) - 75);
        inputName.setStyle(Text::Bold);




        while (welcome.pollEvent(event)) {

            if (event.type == Event::Closed) {
                welcome.close();
                return 0;
            }


            else if (event.type == Event::TextEntered) {

                if (isalpha(event.text.unicode) &&name.getSize() < 10) {

                    if (name.getSize()==0){
                        char a=static_cast<char>(event.text.unicode);
                        a = toupper(a);
                        name += a;
                    }

                    else {
                        char a = static_cast<char>(event.text.unicode);
                        a = tolower(a);
                        name += a;
                    }
                    // user typed name BOLD YELLOW 18 PX WIDTH/2 HEIGHT/2 - 45
                    pname = textInfo(name+"|", font, 18, Color::Yellow, width / 2.0f,(height / 2.0f) - 45);
                    pname.setStyle(Text::Bold);


                }
            }
            else if (event.type == Event::KeyPressed &&event.key.code == Keyboard::Enter&&name.getSize() != 0) {
                welcome.close();
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::BackSpace &&name.getSize() > 0) {
                name.erase((name.getSize() - 1));
                pname = textInfo(name+"|", font, 18, Color::Yellow, width / 2.0f, (height / 2.0f) - 45);
                pname.setStyle(Text::Bold);
            }
        }





        welcome.clear(Color::Blue);
        welcome.draw(wtext);
        welcome.draw(inputName);
        welcome.draw(pname);
        welcome.display();
    }

    Sprite faceSprite;
    faceSprite.setPosition((((minesweeper.columns) / 2) * 32) - 32,32 * (minesweeper.rows + 0.5));
    Texture faceTexture;
    faceTexture.loadFromFile("files/images/face_happy.png");
    faceSprite.setTexture(faceTexture);
    Sprite debugSprite;
    debugSprite.setPosition(((minesweeper.columns) * 32) - 304,32 * (minesweeper.rows + 0.5));
    Texture debugTexture;
    debugTexture.loadFromFile("files/images/debug.png");
    debugSprite.setTexture(debugTexture);
    bool debugOn = true;
    Sprite pauseSprite;
    pauseSprite.setPosition(((minesweeper.columns) * 32) - 240,32 * (minesweeper.rows + 0.5));
    Texture pauseTexture;
    pauseTexture.loadFromFile("files/images/pause.png");
    pauseSprite.setTexture(pauseTexture);
    bool pauseOn = true;
    Sprite leaderboardSprite;
    leaderboardSprite.setPosition(((minesweeper.columns) * 32) - 176,32 * (minesweeper.rows + 0.5));
    Texture leaderboardTexture;
    leaderboardTexture.loadFromFile("files/images/leaderboard.png");
    leaderboardSprite.setTexture(leaderboardTexture);

    Sprite digitsSprite[11];
    Texture digitsTexture;
    digitsTexture.loadFromFile("files/images/digits.png");
    for (unsigned int i=0;i<11;i++){
        digitsSprite[i].setTexture(digitsTexture);
        digitsSprite[i].setTextureRect(IntRect (i*21,0,21,32));
    }

    timer gameClock;
    vector<player> topfive;
    vector<player> topall;

    int newWinnerPosition=-1;

    string tempLine;
    fstream highscoreFile("files/leaderboard.txt", ios_base::in);


    while(getline(highscoreFile, tempLine)) {
        player p1;
        stringstream ss(tempLine);

        string highscoreMinString;
        getline(ss, highscoreMinString, ':');
        int highScoreMin = stoi(highscoreMinString);

        string highscoreSecString;
        getline(ss, highscoreSecString, ',');
        int highScoreSec = stoi(highscoreSecString);

        highScoreSec += (highScoreMin *60);
        p1.gameTime = highScoreSec;

        getline(ss, p1.name);

        topall.push_back(p1);
    }
    highscoreFile.open("files/leaderboard.txt", ios_base::in);
    for(unsigned int i=0; i<5&&getline(highscoreFile, tempLine); i++) {
        player p1;
        stringstream ss(tempLine);

        string hstring;
        getline(ss, hstring, ':');
        int highScoreMin = stoi(hstring);

        string highscoreSecString;
        getline(ss, highscoreSecString, ',');
        int highScoreSec = stoi(highscoreSecString);

        highScoreSec += (highScoreMin *60);
        p1.gameTime = highScoreSec;

        getline(ss, p1.name);

        topfive.push_back(p1);
    }
    highscoreFile.close();

    RenderWindow gameWindow(VideoMode(width, height), "Minesweeper");
    while (gameWindow.isOpen()) {
        gameWindow.clear(Color::White);
        minesweeper.draw(gameWindow);
        int min = gameClock.getElapsedTime().asSeconds() / 60;
        int sec = ((int)gameClock.getElapsedTime().asSeconds()) % 60;

        if (minesweeper.flags < 0){
            digitsSprite[10].setPosition(12, (32*(minesweeper.rows+0.5))+16);
            gameWindow.draw(digitsSprite[10]);
        }

        if (minesweeper.flags >= 0){
            int mchund = minesweeper.flags / 100;
            digitsSprite[mchund].setPosition(33, (32 * (minesweeper.rows + 0.5)) + 16);
            gameWindow.draw(digitsSprite[mchund]);
            int mcten = (minesweeper.flags - (mchund * 100)) / 10;
            digitsSprite[mcten].setPosition(54, (32 * (minesweeper.rows + 0.5 )) + 16);
            gameWindow.draw(digitsSprite[mcten]);
            int mcsing = minesweeper.flags - (mchund * 100) - (mcten * 10);
            digitsSprite[mcsing].setPosition(75, (32 * (minesweeper.rows + 0.5)) + 16);
            gameWindow.draw(digitsSprite[mcsing]);
        }

        else if (minesweeper.flags < 0) {
            minesweeper.flags = abs(minesweeper.flags);
            int mchund = minesweeper.flags / 100;
            digitsSprite[mchund].setPosition(33, (32*(minesweeper.rows + 0.5 )) + 16);
            gameWindow.draw(digitsSprite[mchund]);

            int mcten = (minesweeper.flags - (mchund * 100)) / 10;
            digitsSprite[mcten].setPosition(54, (32*(minesweeper.rows + 0.5)) + 16);
            gameWindow.draw(digitsSprite[mcten]);

            int mcsing =minesweeper.flags - (mchund * 100) - (mcten * 10);
            digitsSprite[mcsing].setPosition(75, (32 * (minesweeper.rows + 0.5)) + 16);
            gameWindow.draw(digitsSprite[mcsing]);

            minesweeper.flags *= -1;
        }
        digitsSprite[min/10].setPosition((minesweeper.columns* 32 ) - 97,(32 * (minesweeper.rows+ 0.5)) + 16);
        gameWindow.draw(digitsSprite[min/10]);
        digitsSprite[min%10].setPosition((minesweeper.columns * 32) - 76,(32 * (minesweeper.rows+ 0.5)) + 16);
        gameWindow.draw(digitsSprite[min%10]);


        digitsSprite[sec/10].setPosition((minesweeper.columns * 32) - 54,(32 * (minesweeper.rows+ 0.5)) + 16);
        gameWindow.draw(digitsSprite[sec/10]);
        digitsSprite[sec%10].setPosition((minesweeper.columns * 32)-33,(32 * (minesweeper.rows+ 0.5)) + 16);
        gameWindow.draw(digitsSprite[sec%10]);

        Event gEvent;
        auto gameWindowClickPosition = Mouse::getPosition(gameWindow);
        auto gameWindowClick = gameWindow.mapPixelToCoords(Mouse::getPosition(gameWindow));

        gameWindow.draw(faceSprite);
        gameWindow.draw(debugSprite);
        gameWindow.draw(pauseSprite);
        gameWindow.draw(leaderboardSprite);
        gameWindow.display();

        while (gameWindow.pollEvent(gEvent)) {

            if (minesweeper.leaderBoard) {
                RenderWindow leaderboardWindow(VideoMode(lbwidth, lbheight),"Leaderboard");
                while (leaderboardWindow.isOpen()) {
                    leaderboardWindow.clear(Color::Blue);
                    Text leaderBoardText = textInfo("LEADERBOARD", font, 20, Color::White, lbwidth / 2.0f,(lbheight / 2.0f) - 120);
                    leaderBoardText.setStyle(Text::Bold | Text::Underlined);
                    string hstext = "";
                    for (unsigned int i=0; i < topfive.size(); i++) {
                        short tempsec = topfive.at(i).gameTime;
                        int tempmin = tempsec / 60;
                        string tempminstr;
                        if (tempmin < 10) {
                            tempminstr = ((string) "0") + to_string(tempmin);
                        }
                        else {
                            tempminstr = to_string(tempmin);
                        }
                        int secInt =tempsec%60;
                        string tempUserSecStr;
                        if (secInt<10) {
                            tempUserSecStr = ((string) "0") + to_string(secInt);
                        }
                        else {
                            tempUserSecStr = to_string(secInt);
                        }
                        string tempUserTime = tempminstr + " : " + tempUserSecStr;
                        string tempUserName =topfive.at(i).name;

                        if (newWinnerPosition>=0) {
                            if (i==newWinnerPosition) {
                                tempUserName += "*";
                            }
                        }

                        if (i == 0) {
                            hstext += to_string(i + 1) + "\t" + tempUserTime + "\t" + tempUserName;
                        }
                        else {
                            hstext += (string) "\n\n" + to_string(i + 1) + "\t" + tempUserTime + "\t" + tempUserName;
                        }
                    }

                    Text highscoreText = textInfo(hstext, font, 18, Color::White, lbwidth / 2.0f,(lbheight / 2.0f) + 20);
                    highscoreText.setStyle(Text::Bold);

                    Event leaderBoardEvent;
                    while (leaderboardWindow.pollEvent(leaderBoardEvent)) {
                        if (leaderBoardEvent.type == Event::Closed) {
                            minesweeper.leaderBoard = false;
                            if(!minesweeper.is_paused && !minesweeper.l && !minesweeper.w){
                                minesweeper.showtiles();
                                gameClock.start();}

                            leaderboardWindow.close();}
                    }
                    leaderboardWindow.draw(leaderBoardText);
                    leaderboardWindow.draw(highscoreText);

                    leaderboardWindow.display();
                }
            }

            if (gEvent.type == Event::Closed) {
                minesweeper.clear();
                gameWindow.close();
                return 0;
            }

            if (gEvent.type == Event::MouseButtonPressed &&!minesweeper.leaderBoard) {
                if (gEvent.mouseButton.button == sf::Mouse::Left) {
                    for (unsigned i = 0; i < minesweeper.dsc.size(); i++) {
                        for (unsigned j = 0; j < minesweeper.dsc.at(i)->size(); j++) {
                            if (minesweeper.dsc.at(i)->at(j)->sprite.getGlobalBounds().contains(gameWindowClick) && minesweeper.dsc.at(i)->at(j)->turnOn) {
                                if (!minesweeper.is_paused && !minesweeper.is_debugMode && !minesweeper.leaderBoard && !minesweeper.dsc.at(i)->at(j)->mineexists && !minesweeper.dsc.at(i)->at(j)->flaggedTile) {
                                    minesweeper.show(gameWindow, minesweeper.dsc.at(i)->at(j));
                                }
                                else if (minesweeper.dsc.at(i)->at(j)->mineexists && minesweeper.dsc.at(i)->at(j)->turnOn && !minesweeper.dsc.at(i)->at(j)->flaggedTile) {
                                    faceTexture.loadFromFile("files/images/face_lose.png");
                                    gameClock.stop();
                                    minesweeper.l = true;
                                    minesweeper.hidetiles();
                                    debugOn = false;
                                    pauseOn = false;
                                }
                            }
                        }
                    }
                    if (faceSprite.getGlobalBounds().contains(gameWindowClick)) {
                        if (minesweeper.l)
                            minesweeper.l = false;

                        if (minesweeper.w)
                            minesweeper.w = false;

                        Board minesweepercopy;
                        minesweeper.clear();
                        minesweeper = minesweepercopy;
                        faceTexture.loadFromFile("files/images/face_happy.png");
                        gameClock.restart();
                        gameClock.start();
                        pauseOn = true;
                        debugOn = true;
                    }

                    if (debugSprite.getGlobalBounds().contains(gameWindowClick) && debugOn) {
                        minesweeper.debugswitch();
                        if (minesweeper.is_debugMode)
                            minesweeper.hidetiles();
                        else if(!minesweeper.is_debugMode)
                            minesweeper.showtiles();
                    }

                    if (pauseSprite.getGlobalBounds().contains(gameWindowClick) && pauseOn) {
                        if (gameClock.isPaused()) {
                            gameClock.start();
                        }
                        else {
                            gameClock.stop();
                        }
                        minesweeper.pauseswitch();
                        if (minesweeper.is_paused) {
                            gameClock.stop();
                            minesweeper.hidetiles();
                            debugOn = false;
                            pauseTexture.loadFromFile("files/images/play.png");
                        }

                        else if (!minesweeper.is_paused){
                            minesweeper.showtiles();
                            debugOn = true;
                            gameClock.start();
                            pauseTexture.loadFromFile("files/images/pause.png");
                        }
                    }
                    if (leaderboardSprite.getGlobalBounds().contains(gameWindowClick) &&!minesweeper.leaderBoard) {
                        gameClock.stop();
                        minesweeper.hidetiles();
                        minesweeper.lbswitch();
                    }
                }
                else if (gEvent.mouseButton.button == sf::Mouse::Right) {
                    for (unsigned i = 0; i < minesweeper.dsc.size(); i++) {
                        for (unsigned k = 0; k < minesweeper.dsc.at(i)->size(); k++) {
                            if (minesweeper.dsc.at(i)->at(k)->sprite.getGlobalBounds().contains(gameWindowClick) && !minesweeper.is_paused && !minesweeper.is_debugMode && !minesweeper.l && !minesweeper.w) {
                                if (!minesweeper.dsc.at(i)->at(k)->flaggedTile && !minesweeper.dsc.at(i)->at(k)->showed) {
                                    minesweeper.flags--;
                                    minesweeper.dsc.at(i)->at(k)->toggleFlag();
                                }


                                else if (minesweeper.dsc.at(i)->at(k)->flaggedTile && !minesweeper.dsc.at(i)->at(k)->showed && minesweeper.flags < minesweeper.mines) {
                                    minesweeper.flags++;
                                    minesweeper.dsc.at(i)->at(k)->toggleFlag();
                                }
                            }
                        }
                    }
                }
            }
        }

        if(minesweeper.wcheck()) {
            gameClock.stop();
            minesweeper.flags = 0;

            if (!minesweeper.w) {
                minesweeper.leaderBoard = true;
                newWinnerPosition = -1;
                player fifthPlacePlayer = topfive.back();
                player lastPlacePlayer = topall.back();

                player p1;
                p1.name = name;
                p1.gameTime = sec + (min * 60);
                if (p1.gameTime<fifthPlacePlayer.gameTime) {
                    topfive.pop_back();

                    for (auto iter = topfive.begin(); iter != topfive.end(); iter++) {
                        newWinnerPosition++;
                        if (p1.gameTime < iter->gameTime) {
                            topfive.insert(iter, p1);
                            break;
                        }
                    }
                    if (topfive.size() < 5) {
                        newWinnerPosition++;
                        topfive.push_back(p1);
                    }
                }

                for (auto iter = topall.begin(); iter != topall.end(); iter++) {
                    if (p1.gameTime< iter->gameTime) {
                        topall.insert(iter, p1);
                        break;
                    }
                }

                if (p1.gameTime >= lastPlacePlayer.gameTime)
                    topall.push_back(p1);

                highscoreFile.open("files/leaderboard.txt", std::ios::out | std::ios::trunc);
                string mstr;
                string sstr;
                for (auto iter = topall.begin(); iter != topall.end(); iter++) {
                    short tempFileMins = (iter->gameTime) / 60;
                    short tempFileSecs = (iter->gameTime) % 60;
                    if(tempFileMins >= 10)
                        mstr = to_string(tempFileMins);
                    else if (tempFileMins < 10)
                        mstr = "0" + to_string(tempFileMins);
                    if(tempFileSecs>=10)
                        sstr = to_string(tempFileSecs);
                    else if (tempFileSecs<10)
                        sstr = "0" + to_string(tempFileSecs);

                    highscoreFile<<mstr +":" + sstr + "," + iter->name <<endl;
                }
                highscoreFile.close();

            }
            minesweeper.w = true;
            faceTexture.loadFromFile("files/images/face_win.png");
            minesweeper.hidetiles();
            debugOn = false;
            pauseOn = false;
        }
    }
    return 0;}

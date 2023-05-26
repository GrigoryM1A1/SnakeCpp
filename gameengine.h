//
// Created by User on 15.05.2023.
//

#ifndef CPPGAME_GAMEENGINE_H
#define CPPGAME_GAMEENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>
#include <deque>
#include "snakesection.h"
#include "apple.h"
#include "wall.h"
#include <fstream>


class GameEngine {
private:
    sf::Vector2i resolution;
    sf::RenderWindow window;
    std::vector<SnakeSection> python;
    std::deque<int> movesQueue;
    int direction;
    int speed;
    int sectionToAdd;

    sf::Time lastMoveTime;
    Apple apple;

    std::vector<Wall> walls;
    int currLevel;
    int maxLevel;
    std::vector<std::string> levels;
    int applesEatenTotal;
    int applesEatenCurrLvl;
    unsigned long long int score;

    int currGameState;
    int lastGameState;
    const unsigned int fpsLimit = 60;
    static const sf::Time TimePerFrame;
    sf::Text titleText;
    sf::Text applesEatenText;
    sf::Text currLvlText;
    sf::Font mainFont;
    sf::Text scoreText;

public:
    enum Direction {
        UP,
        RIGHT,
        LEFT,
        DOWN
    };

    enum GameState {
        RUNNING,
        PAUSED,
        GAMEOVER
    };

    GameEngine();

    void addDirection(int newDir);

    void update();

    void drawGame();

    void runGame();

    void eventInput();

    void newSnake();

    void growSnake();

    void moveApple();

    void togglePause();

    void startGame();

    void checkLevelFiles();

    void loadLevel(int levelNo);

    void launchNextLevel();

    static void setWindowText(sf::Text *text, const sf::Font &font, const std::string &value, int size, sf::Color color);
};


#endif //CPPGAME_GAMEENGINE_H

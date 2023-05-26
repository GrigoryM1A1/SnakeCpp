//
// Created by User on 15.05.2023.
//

#include <iostream>
#include "gameengine.h"

const sf::Time GameEngine::TimePerFrame = sf::seconds(1.f/60.f);

GameEngine::GameEngine() {
    resolution = sf::Vector2i(800, 600);
    window.create(
            sf::VideoMode(resolution.x, resolution.y),
            "Ssssnake",
            sf::Style::Default
            );
    window.setFramerateLimit(fpsLimit);
    maxLevel = 0;
    checkLevelFiles();
    startGame();

    if (!mainFont.loadFromFile("assets/fonts/slant_regular.ttf")) {
        std::cout<<"Error!"<<std::endl;
    }
    setWindowText(&titleText, mainFont, "Sssnake", 28, sf::Color::Black);
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setPosition(sf::Vector2f(resolution.x / 2 - titleBounds.width / 2, -9));

    setWindowText(&currLvlText, mainFont, "Level 1", 28, sf::Color::Black);
    currLvlText.setPosition(sf::Vector2f(15, -9));
    sf::FloatRect currLvlTextBounds = currLvlText.getGlobalBounds();

    setWindowText(&applesEatenText, mainFont, "Apples 0", 28, sf::Color::Black);
    applesEatenText.setPosition(
            sf::Vector2f(currLvlTextBounds.left + currLvlTextBounds.width + 20, -9)
            );

    setWindowText(&scoreText, mainFont, std::to_string(score), 28, sf::Color::Black);
    sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(sf::Vector2f(resolution.x - scoreTextBounds.width - 15, -9));
}

void GameEngine::drawGame() {
    window.clear(sf::Color::Black);

    for (auto & w: walls) {
        window.draw(w.getShape());
    }

    window.draw(apple.getApple());
    // Drawing our python
    for (auto & ss: python) {
        window.draw(ss.getShape());
    }

    window.draw(titleText);
    window.draw(currLvlText);
    window.draw(applesEatenText);
    window.draw(scoreText);

    window.display();
}

void GameEngine::runGame() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();

        if (currGameState == GameState::PAUSED || currGameState == GameState::GAMEOVER) {
            eventInput();   // If game is paused

            if (currGameState == GameState::GAMEOVER) {
                drawGame();
            }

            sf::sleep(sf::milliseconds(2));
            continue;
        }

        lastMoveTime += dt;
        eventInput();
        update();
        drawGame();
    }
}

// Initial snake
void GameEngine::newSnake() {
    python.clear();
    python.emplace_back(sf::Vector2f(40, 40), sf::Color::Blue);
}

void GameEngine::growSnake() {
    sf::Vector2f newSectionPos = python[python.size() - 1].getPosition();

    if (python.size() % 2 == 0) {
        python.emplace_back(newSectionPos, sf::Color::Blue);
    } else {
        python.emplace_back(newSectionPos, sf::Color::Yellow);
    }
}

void GameEngine::addDirection(int newDir) {
    if (movesQueue.empty()) {
        movesQueue.emplace_back(newDir);
    } else {
        if (movesQueue.back() != newDir) {
            movesQueue.emplace_back(newDir);
        }
    }
}

void GameEngine::eventInput() {
    sf::Event event{};

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            if (event.key.code == sf::Keyboard::Space) {
                togglePause();
            }

            if (currGameState == GameState::GAMEOVER) {
                if (event.key.code == sf::Keyboard::Enter) {
                    startGame();
                }
            }
        }
    }

    if (event.key.code == sf::Keyboard::Up) {
        addDirection(Direction::UP);
    } else if (event.key.code == sf::Keyboard::Right) {
        addDirection(Direction::RIGHT);
    } else if (event.key.code == sf::Keyboard::Left) {
        addDirection(Direction::LEFT);
    } else if (event.key.code == sf::Keyboard::Down) {
        addDirection(Direction::DOWN);
    }
}

void GameEngine::update() {
    if (lastMoveTime.asSeconds() >= sf::seconds(1.f / float(speed)).asSeconds()) {
        sf::Vector2f currSec = python[0].getPosition();
        sf::Vector2f lastSec = currSec;

        if (!movesQueue.empty()) {
            switch (direction) {
                case Direction::UP:
                    if (movesQueue.front() != Direction::DOWN) {
                        direction = movesQueue.front();
                    }
                    break;

                case Direction::DOWN:
                    if (movesQueue.front() != Direction::UP) {
                        direction = movesQueue.front();
                    }
                    break;

                case Direction::LEFT:
                    if (movesQueue.front() != Direction::RIGHT) {
                        direction = movesQueue.front();
                    }
                    break;

                case Direction::RIGHT:
                    if (movesQueue.front() != Direction::LEFT) {
                        direction = movesQueue.front();
                    }
                    break;
            }
            movesQueue.pop_front();
        }

        score += python.size() + (applesEatenTotal + 1);
        scoreText.setString(std::to_string(score));
        sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
        scoreText.setPosition(sf::Vector2f(resolution.x - scoreTextBounds.width - 15, -9));

        if (sectionToAdd) {
            growSnake();
            sectionToAdd--;
        }

        switch (direction) {
            case Direction::RIGHT:
                python[0].setPosition(sf::Vector2f(currSec.x + 20, currSec.y));
                break;

            case Direction::DOWN:
                python[0].setPosition(sf::Vector2f(currSec.x, currSec.y + 20));
                break;

            case Direction::LEFT:
                python[0].setPosition(sf::Vector2f(currSec.x - 20, currSec.y));
                break;

            case Direction::UP:
                python[0].setPosition(sf::Vector2f(currSec.x, currSec.y - 20));
                break;
        }

        for (int i = 1; i < python.size(); i++) {
            currSec = python[i].getPosition();
            python[i].setPosition(lastSec);
            lastSec = currSec;
        }

        for (auto & ss: python) {
            ss.update();
        }

        if (python[0].getShape().getGlobalBounds().intersects(apple.getApple().getGlobalBounds())) {
            applesEatenCurrLvl++;
            applesEatenTotal++;
            applesEatenText.setString("Apples " + std::to_string(applesEatenTotal));
            sf::FloatRect currLvlTextBounds = currLvlText.getGlobalBounds();
            applesEatenText.setPosition(
                    sf::Vector2f(currLvlTextBounds.left + currLvlTextBounds.width + 20, -9)
            );

            bool startNewLvl = false;
            if (applesEatenCurrLvl >= 7) {
                if (currLevel < maxLevel) {
                    startNewLvl = true;
                    launchNextLevel();
                }
            }

            if (!startNewLvl) {
                sectionToAdd++;
                speed++;
                moveApple();
            }
        }

        for (int ss = 1; ss < python.size(); ss++) {
            if (python[0].getShape().getGlobalBounds().intersects(python[ss].getShape().getGlobalBounds())) {
                currGameState = GameState::GAMEOVER;
            }
        }

        for (auto & w: walls) {
            if (python[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds())) {
                currGameState = GameState::GAMEOVER;
            }
        }

        lastMoveTime = sf::Time::Zero;
    }
}

void GameEngine::moveApple() {
    sf::Vector2f appleRes = sf::Vector2f(resolution.x / 20 - 2, resolution.y / 20 - 2 );
    sf::Vector2f newAppleLoc;
    bool invalidLoc = false;

    srand(time(nullptr));

    do {
        invalidLoc = false;
        newAppleLoc.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleRes.x)) * 20;
        newAppleLoc.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleRes.y)) * 20;

        for (auto & ss: python) {
            if (ss.getShape().getGlobalBounds().intersects(
                    sf::Rect<float>(newAppleLoc.x, newAppleLoc.y, 20, 20))
                    ) {
                invalidLoc = true;
                break;
            }
        }
        for (auto & w: walls) {
            if (w.getShape().getGlobalBounds().intersects(
                    sf::Rect<float>(newAppleLoc.x, newAppleLoc.y, 20, 20)
                    )) {
                invalidLoc = true;
                break;
            }
        }
    } while (invalidLoc);
    apple.setPosition(newAppleLoc);
}

void GameEngine::togglePause() {
    if (currGameState == GameState::RUNNING) {
        lastGameState = currGameState;
        currGameState = GameState::PAUSED;
    } else if (currGameState == GameState::PAUSED) {
        currGameState = lastGameState;
    }
}

void GameEngine::startGame() {
    score = 0;
    speed = 2;
    direction = Direction::RIGHT;
    lastMoveTime = sf::Time::Zero;
    sectionToAdd = 0;
    movesQueue.clear();
    walls.clear();
    applesEatenCurrLvl = 0;
    applesEatenTotal = 0;
    currLevel = 1;
    loadLevel(currLevel);
    currGameState = GameState::RUNNING;
    lastGameState = currGameState;
    currLvlText.setString("Level " + std::to_string(currLevel));
    applesEatenText.setString("Apples " + std::to_string(applesEatenTotal));
    sf::FloatRect currLvlTextBounds = currLvlText.getGlobalBounds();
    applesEatenText.setPosition(
            sf::Vector2f(currLvlTextBounds.left + currLvlTextBounds.width + 20, -9)
    );
    scoreText.setString(std::to_string(score));
    sf::FloatRect scoreTextBounds = scoreText.getLocalBounds();
    scoreText.setPosition(sf::Vector2f(resolution.x - scoreTextBounds.width - 15, -9));
    newSnake();
    moveApple();
}

void GameEngine::checkLevelFiles() {
    std::ifstream levelsList ("assets/levels/levels_list.txt");
    std::ifstream testFile;

    for (std::string levelLine; std::getline(levelsList, levelLine);) {
        testFile.open("assets/levels/" + levelLine);
        if (testFile.is_open()) {
            levels.emplace_back("assets/levels/" + levelLine);
            testFile.close();
            maxLevel++;
        }
    }
}

void GameEngine::loadLevel(int levelNo) {
    std::string levelFile = levels[levelNo - 1];
    std::ifstream level (levelFile);

    std::string line;
    if (level.is_open()) {
        for (int y = 0; y < 30; y++) {
            std::getline(level, line);
            for (int x = 0; x < 40; x++) {
                if (line[x] == 'x') {
                    walls.emplace_back(Wall(sf::Vector2f(x * 20, y * 20), sf::Vector2f(20, 20)));
                }
            }
        }
    }
    level.close();
}

void
GameEngine::setWindowText(sf::Text *text, const sf::Font &font, const std::string &value, int size, sf::Color color) {
    text->setFont(font);
    text->setString(value);
    text->setCharacterSize(size);
    text->setFillColor(color);
}

void GameEngine::launchNextLevel() {
    currLevel++;
    walls.clear();
    movesQueue.clear();
    speed = 2;
    direction = Direction::RIGHT;
    sectionToAdd = 0;
    applesEatenCurrLvl = 0;

    loadLevel(currLevel);
    newSnake();
    moveApple();
    currLvlText.setString("Level " + std::to_string(currLevel));
    sf::FloatRect currLvlTextBounds = currLvlText.getGlobalBounds();
    applesEatenText.setPosition(
            sf::Vector2f(currLvlTextBounds.left + currLvlTextBounds.width + 20, -9)
            );
}

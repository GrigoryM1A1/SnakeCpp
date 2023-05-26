//
// Created by User on 15.05.2023.
//

#ifndef CPPGAME_SNAKESECTION_H
#define CPPGAME_SNAKESECTION_H

#include "SFML/Graphics.hpp"

class SnakeSection {
private:
    sf::Vector2f position;
    sf::RectangleShape section;

public:
    SnakeSection(sf::Vector2f startPos, sf::Color color);

    sf::Vector2f getPosition();

    void setPosition(sf::Vector2f newPos);

    sf::RectangleShape getShape();

    void update();
};


#endif //CPPGAME_SNAKESECTION_H

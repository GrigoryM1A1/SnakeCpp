//
// Created by User on 15.05.2023.
//

#include "snakesection.h"

SnakeSection::SnakeSection(sf::Vector2f startPos, sf::Color color) {
    section.setSize(sf::Vector2f(20, 20));
    section.setFillColor(color);
    section.setPosition(startPos);
    position = startPos;
}

sf::Vector2f SnakeSection::getPosition() {
    return position;
}

void SnakeSection::setPosition(sf::Vector2f newPos) {
    position = newPos;
}

sf::RectangleShape SnakeSection::getShape() {
    return section;
}

void SnakeSection::update() {
    section.setPosition(position);
}

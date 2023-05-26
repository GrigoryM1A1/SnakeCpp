//
// Created by User on 15.05.2023.
//

#include <iostream>
#include "apple.h"

Apple::Apple() {
    sf::Vector2f startPosition(400, 300);
    sprite.setSize(sf::Vector2f(20, 20));
    sprite.setFillColor(sf::Color::Red);
    sprite.setPosition(startPosition);
}

void Apple::setPosition(sf::Vector2f newPos) {
    sprite.setPosition(newPos);
}

sf::RectangleShape Apple::getApple() {
    return sprite;
}

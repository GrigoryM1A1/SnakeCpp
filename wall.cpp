//
// Created by User on 16.05.2023.
//

#include "wall.h"

Wall::Wall(sf::Vector2f position, sf::Vector2f size) {
    wallShape.setSize(size);
    wallShape.setFillColor(sf::Color::Green);
    wallShape.setPosition(position);
}

sf::RectangleShape Wall::getShape() {
    return wallShape;
}

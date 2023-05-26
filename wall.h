//
// Created by User on 16.05.2023.
//

#ifndef CPPGAME_WALL_H
#define CPPGAME_WALL_H

#include <SFML/Graphics.hpp>

class Wall {
private:
    sf::RectangleShape wallShape;

public:
    Wall(sf::Vector2f position, sf::Vector2f size);

    sf::RectangleShape getShape();
};


#endif //CPPGAME_WALL_H

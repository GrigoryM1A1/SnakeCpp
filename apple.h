//
// Created by User on 15.05.2023.
//

#ifndef CPPGAME_APPLE_H
#define CPPGAME_APPLE_H

#include <SFML/Graphics.hpp>

class Apple {
private:
    sf::RectangleShape sprite;

public:
    Apple();

    void setPosition(sf::Vector2f newPos);

    sf::RectangleShape getApple();
};


#endif //CPPGAME_APPLE_H

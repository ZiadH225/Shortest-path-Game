#include "Player.h"
#include <iostream>
Player::Player(int x, int y) : x(x), y(y) {
    if (!texture.loadFromFile("Materials/player.png")) {
        std::cout<<"Error: No player texture found"<<std::endl;
    }
    sprite.setTexture(texture);
    setPosition(x, y);
}

void Player::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
    sprite.setPosition(x, y);
}

sf::Sprite& Player::getSprite() {
    return sprite;
}

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}

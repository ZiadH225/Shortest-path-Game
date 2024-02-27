#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    int x, y;
public:
    Player(int x, int y);
    void setPosition(int x, int y);
    sf::Sprite& getSprite();
    int getX() const;
    int getY() const;
};

#endif // PLAYER_H

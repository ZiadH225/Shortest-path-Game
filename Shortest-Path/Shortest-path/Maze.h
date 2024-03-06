#ifndef MAZE_H
#define MAZE_H
#include "Player.h"
#include <SFML/Graphics.hpp>
#include<vector>
#include<iostream>
using namespace std;
const int windowsize = 70;
const int rows = 10;
const int cols = 10;
class Maze {
private:
    sf::RenderWindow* window;
    sf::Event ev;
    sf::Texture grass;
    sf::Texture wall;
    sf::Texture gate;
    sf::Texture pathh;
    sf::Sprite maze[rows][cols];
    char arr[rows][cols];
    std::vector<std::vector<bool>> adj_matrix;
    std::pair<int, int> start;
    std::pair<int, int> target;
    std::vector<std::pair<int, int>> path;
    bool isPathSet = false;
    Player player;

    void initGrass(sf::Texture& grss);
    void initWall(sf::Texture& wll);
    void initGate(sf::Texture& gate);
    void initPath(sf::Texture& setpath);
    void initTexture(sf::Texture& grass);
    void initPlayer(int x, int y);
    void renderTexture();
    void initMatrix();
    bool bfs(std::pair<int, int> start, std::pair<int, int> target);
    void movePlayer();
    void setPath();
    void pollEvents();
    void handleMouseClick(sf::Mouse::Button button, sf::Vector2i mousePosition);
    void runBFS();
    void handleKeyPress(sf::Keyboard::Key key);


public:
    Maze();
    const bool isRunning() const;
    void update();
    void render();
    virtual ~Maze();
};


#endif // MAZE_H

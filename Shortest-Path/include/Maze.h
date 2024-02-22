#ifndef MAZE_H
#define MAZE_H
#include <SFML/Graphics.hpp>
#include<vector>
#include<iostream>
using namespace std;
const int windowsize = 70;
const int rows = 10;
const int cols = 10;
class Maze
{
    private :
        sf::RenderWindow* window;
        sf::Event ev;
        sf::Texture playertex;
        sf::Texture grass;
        sf::Texture wall;
        sf::Texture pathh;
        sf::Texture gate;
        int playerx,playery;
        int playeri, playerj;
        sf::Sprite player;
        sf::Sprite maze[rows][cols];
        char arr[rows][cols];
        vector<vector<bool>>adj_matrix;
        pair<int,int>start;
        pair<int,int>target;
        vector<pair<int, int>> path;
        void initChars(char arr[][cols]);
        void initGrass(sf::Texture& grss);
        void initWall(sf::Texture& wll);
        void initGate(sf::Texture& gate);
        void initPath(sf::Texture& setpath);
        void handleMouseClick(sf::Event::MouseButtonEvent& event);
        void handleKeyPress(sf::Event::KeyEvent& event);
        void initTexture(sf::Sprite maze[][cols],int& playerx, int& playery,sf::Texture& grass,sf::Texture& wall,sf::Texture& gate);
        void initPlayer(int x,int y);
        void renderTexure(sf::Sprite maze[][cols],sf::Sprite player);
        void initMatrix(char arr[rows][cols]);
        bool bfs(vector<vector<bool>>& adj_matrix, pair<int, int> start, pair<int, int> target);
        void movePlayer();
        void setPath();
    public:
        Maze();
        const bool isRunning() const;
        void pollEvents();
        void update();
        void render();
        virtual ~Maze();
};

#endif // MAZE_H

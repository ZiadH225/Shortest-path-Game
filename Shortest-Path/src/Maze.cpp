#include "Maze.h"
#include<iostream>
#include <fstream>
#include<vector>
#include<queue>
#include <chrono>
#include <thread>
#include <SFML/System.hpp>
using namespace std;

Maze::Maze() {
    window = nullptr;
    window = new sf::RenderWindow(sf::VideoMode(windowsize*10, windowsize*10), "Shortest Path Maze");
    window->setFramerateLimit(60);
    adj_matrix = vector<vector<bool>>(rows, vector<bool>(cols));
    initChars(arr);
    initTexture(maze, playerx, playery, grass, wall, gate);
    initPath(pathh);
    initMatrix(arr);
    initPlayer(playerx, playery);

    if (!bfs(adj_matrix, start, target)) {
        sf::Font font;
        if (!font.loadFromFile("Materials/ARIAL.TTF")) {
            cout << "Font file not found!" << endl;
            exit(1);
        }

        sf::Text text;
        text.setFont(font);
        text.setString("No path found.");
        text.setCharacterSize(60);
        text.setFillColor(sf::Color::Red);
        text.setPosition(window->getSize().x / 2 - text.getGlobalBounds().width / 2, window->getSize().y / 2 - text.getGlobalBounds().height / 2);

        renderTexure(maze, player);

        window->draw(text);

        window->display();

        sf::sleep(sf::seconds(5));

        window->close();
        return;
    }
    setPath();
    movePlayer();
}


void Maze::initChars(char arr[][cols]){
std::ifstream sin;
    sin.open("materials/Maze.txt");

    for (int i =0; i<rows; i++) {
        for (int j=0; j<cols; j++) {

            sin >> arr[i][j];
}}}
void Maze::initGrass(sf::Texture& grss){
if(!grss.loadFromFile("Materials/Grass.png")){
    cout<<"error no grass texture found";
}
}
void Maze::initWall(sf::Texture& wll){
if(!wll.loadFromFile("Materials/Wall.png")){
    cout<<"error no wall texture found";
}
}
void Maze::initGate(sf::Texture& gate){
if(!gate.loadFromFile("Materials/Gate.png")){
    cout<<"error no gate texture found";
}
}
void Maze::initMatrix(char arr[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] == 'w') {
                adj_matrix[i][j] = false;
            }
            else if (arr[i][j] == 'g' || arr[i][j] == 's' || arr[i][j] == 'e') {
                adj_matrix[i][j] = true;
            }
        }
    }
}
void Maze::initTexture(sf::Sprite maze[][cols],int& playerx, int& playery,sf::Texture& grass,sf::Texture& wall,sf::Texture& gate){
    initGrass(grass);
    initWall(wall);
    initGate(gate);
     for (int i =0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
                if (arr[i][j] == 'w'){
                maze[i][j].setTexture(wall);
                maze[i][j].setPosition(j*(window->getSize().x/10), i*(window->getSize().y/10));
            }
            else if(arr[i][j] == 'e'){
                target.first=i;
                target.second=j;
            }

            else{
                if (arr[i][j] == 's') {
                start.first=i;
                start.second=j;
                    playerx=i;
                    playery=j;
                }

                maze[i][j].setTexture(grass);
                maze[i][j].setPosition(j*(window->getSize().x/10),i*(window->getSize().y/10));

            }
}}}
bool Maze::bfs(vector<vector<bool>>& adj_matrix, pair<int, int> start, pair<int, int> target) {
    int rows = adj_matrix.size();
    int cols = adj_matrix[0].size();

    int startNode = start.first * cols + start.second;
    int targetNode = target.first * cols + target.second;

    queue<int> q;
    vector<bool> visited(rows * cols, false);
    vector<int> parent(rows * cols, -1);
    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if (curr == targetNode) {
            int node =targetNode;
            while (node != startNode) {
                int row = node / cols;
                int col = node % cols;
                path.push_back({ row, col });
                node = parent[node];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());

            cout << "Shortest Path: ";
            for (const auto& p : path) {
                cout << "(" << p.first << ", " << p.second << ") ";
            }
            cout << endl;
            return true;
        }
        int currRow = curr / cols;
        int currCol = curr % cols;
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };
        for (int i = 0; i < 4; i++) {
            int newRow = currRow + dx[i];
            int newCol = currCol + dy[i];
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                adj_matrix[newRow][newCol] && !visited[newRow * cols + newCol]) {
                int newNode = newRow * cols + newCol;
                q.push(newNode);
                visited[newNode] = true;
                parent[newNode] = curr;
            }
        }
    }

    return false;
}
void Maze::initPlayer(int x,int y){
        playeri=x;
        playerj=y;
        playertex.loadFromFile("Materials/player.png");

        player.setTexture(playertex);
        player.setPosition(playerj*(window->getSize().x/10+3), playeri*(window->getSize().y/10)+7);

}
void Maze::renderTexure(sf::Sprite maze[][cols], sf::Sprite player) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            window->draw(maze[i][j]);
        }
    }
    window->draw(player);
}
const bool Maze::isRunning() const {
    return window->isOpen();
}
void Maze::pollEvents() {
    while (window->pollEvent(ev)) {
        switch (ev.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape) window->close();
            break;
        }
    }
}
void Maze::movePlayer() {
    for (const auto& p : path) {
        playeri = p.first;
        playerj = p.second;
        player.setPosition(playerj * (window->getSize().x / 10 + 1), playeri * (window->getSize().y / 10) + 7);
        render();
        pollEvents();
        sleep(sf::milliseconds(500));
    }

}
void Maze::initPath(sf::Texture& setpath){
    setpath.loadFromFile("Materials/path.png");
}
void Maze::setPath(){
    for (const auto& p : path) {
       maze[p.first][p.second].setTexture(pathh);
    }
    maze[target.first][target.second].setTexture(gate);
    maze[target.first][target.second].setPosition(target.second*(window->getSize().x/10), target.first*(window->getSize().y/10));
}
void Maze::update() {
    pollEvents();
}
void Maze::render() {
    window->clear();
    renderTexure(maze,player);
    window->display();
}
Maze::~Maze()
{
    delete window;
}

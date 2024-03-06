#include "Maze.h"
#include<iostream>
#include <fstream>
#include<vector>
#include<queue>
#include <chrono>
#include <thread>
#include <SFML/System.hpp>
using namespace std;

Maze::Maze() : player(start.first, start.second) {
    window = nullptr;
    window = new sf::RenderWindow(sf::VideoMode(windowsize * 10, windowsize * 10), "Shortest Path Maze");
    window->setFramerateLimit(60);
    initGrass(grass);
    initWall(wall);
    initGate(gate);
    initPath(pathh);
    initTexture(grass);
    initMatrix();
    initPlayer(start.first, start.second);
}

void Maze::initGrass(sf::Texture& grss) {
    if (!grss.loadFromFile("Materials/Grass.png")) {
        std::cout << "Error: No grass texture found" << std::endl;
    }
}

void Maze::initWall(sf::Texture& wll) {
    if (!wll.loadFromFile("Materials/Wall.png")) {
        std::cout << "Error: No wall texture found" << std::endl;
    }
}

void Maze::initGate(sf::Texture& gat) {
    if (!gat.loadFromFile("Materials/Gate.png")) {
        std::cout << "Error: No gate texture found" << std::endl;
    }
}

void Maze::initPath(sf::Texture& setpath) {
    if (!setpath.loadFromFile("Materials/path.png")) {
        std::cout << "Error: No path texture found" << std::endl;
    }
}

void Maze::initTexture(sf::Texture& grass) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            maze[i][j].setTexture(grass);
            maze[i][j].setPosition(j * (window->getSize().x / 10), i * (window->getSize().y / 10));
        }
    }
}

void Maze::initPlayer(int x, int y) {
    player.setPosition(y * (window->getSize().x / 10 + 3), x * (window->getSize().y / 10) + 7);
}

void Maze::initMatrix() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = ' ';
        }
        adj_matrix.push_back(std::vector<bool>(cols, true));
    }
}

bool Maze::bfs(std::pair<int, int> start, std::pair<int, int> target) {
    int startNode = start.first * cols + start.second;
    int targetNode = target.first * cols + target.second;

    std::queue<int> q;
    std::vector<bool> visited(rows * cols, false);
    std::vector<int> parent(rows * cols, -1);
    visited[startNode] = true;
    q.push(startNode);

    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        if (curr == targetNode) {
            int node = targetNode;
            while (node != startNode) {
                int row = node / cols;
                int col = node % cols;
                path.push_back({ row, col });
                node = parent[node];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return true;
        }
        int currRow = curr / cols;
        int currCol = curr % cols;
        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };
        for (int i = 0; i < 4; ++i) {
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

void Maze::movePlayer() {
    for (const auto& p : path) {
        int playeri = p.first;
        int playerj = p.second;
        player.setPosition(playerj * (window->getSize().x / 10 + 1), playeri * (window->getSize().y / 10) + 7);
        render();
        pollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}


void Maze::setPath() {
    for (const auto& p : path) {
        maze[p.first][p.second].setTexture(pathh);
    }
    maze[target.first][target.second].setTexture(gate);
    maze[target.first][target.second].setPosition(target.second * (window->getSize().x / 10), target.first * (window->getSize().y / 10));
}
void Maze::handleKeyPress(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::R) {
        runBFS();
    }
    else if (key == sf::Keyboard::C) {
        arr[0][0] = 's';
        start = { 0,0 };
        target = { 0,0 };
        adj_matrix.clear();
        path.clear();
        initMatrix();
        initTexture(grass);
        initPlayer(start.first, start.second);
    }
}

void Maze::pollEvents() {
    while (window->pollEvent(ev)) {
        switch (ev.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            handleKeyPress(ev.key.code);
            if (ev.key.code == sf::Keyboard::Escape) window->close();
            break;
        case sf::Event::MouseButtonPressed:
            handleMouseClick(ev.mouseButton.button, sf::Mouse::getPosition(*window));
            break;
        }
    }
}

void Maze::handleMouseClick(sf::Mouse::Button button, sf::Vector2i mousePosition) {
    int col = mousePosition.x / (window->getSize().x / cols);
    int row = mousePosition.y / (window->getSize().y / rows);

    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        if (button == sf::Mouse::Right) {
            if (arr[row][col] == 'w') {
                arr[row][col] = ' ';
                adj_matrix[row][col] = true;
                maze[row][col].setTexture(grass);
            }
            else {
                arr[row][col] = 'w';
                adj_matrix[row][col] = false;
                maze[row][col].setTexture(wall);
            }
            isPathSet = false;
        }
        else if (button == sf::Mouse::Left) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                if (arr[row][col] != 'w') {
                    start = { row, col };
                    arr[row][col] = 's';
                    initPlayer(row, col);
                    isPathSet = false;
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                bool endPointAlreadySet = false;
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        if (arr[i][j] == 'e') {
                            endPointAlreadySet = true;
                            break;
                        }
                    }
                    if (endPointAlreadySet) break;
                }
                if (!endPointAlreadySet && arr[row][col] != 'w') {
                    target = { row, col };
                    arr[row][col] = 'e';
                    maze[row][col].setTexture(gate);
                    maze[row][col].setPosition(col * (window->getSize().x / cols), row * (window->getSize().y / rows));
                    isPathSet = false;
                }
            }
        }
    }
}

void Maze::runBFS() {
    if (!isPathSet) {
        if (!bfs(start, target)) {
            sf::Font font;
            if (!font.loadFromFile("Materials/ARIAL.TTF")) {
                cout << "Font file not found!" << endl;
                exit(1);
            }

            sf::Text text;
            text.setFont(font);
            text.setString("No path found.");
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);
            text.setOutlineColor(sf::Color::Black);
            text.setOutlineThickness(5);
            text.setCharacterSize(60);
            text.setPosition(window->getSize().x / 2 - text.getGlobalBounds().width / 2, window->getSize().y / 2 - text.getGlobalBounds().height / 2);

            renderTexture();

            window->draw(text);

            window->display();

            sf::sleep(sf::seconds(2));

            window->close();
            return;
        }
        setPath();
        isPathSet = true;
        movePlayer();
    }
}

const bool Maze::isRunning() const {
    return window->isOpen();
}

void Maze::update() {
    pollEvents();
}

void Maze::render() {
    window->clear();
    renderTexture();
    window->display();
}

void Maze::renderTexture() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            window->draw(maze[i][j]);
        }
    }
    window->draw(player.getSprite());
}

Maze::~Maze() {
    delete window;
}

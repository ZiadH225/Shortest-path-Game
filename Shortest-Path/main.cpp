#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <Maze.h>
int main()
{
    Maze maze;
    while (maze.isRunning()) {
        maze.update();
        maze.render();
    }


    return 0;
}

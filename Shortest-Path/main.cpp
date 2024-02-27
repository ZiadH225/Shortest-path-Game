#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <Maze.h>
using namespace std;
int main()
{
    Maze maze;
    cout<<"Left-mouse-click + S to change the player position."<<endl;
    cout<<endl;
    cout<<"Left-mouse-click + E to set the end point."<<endl;
    cout<<endl;
    cout<<"Right-mouse-click to add a wall."<<endl;
    cout<<endl;
    cout<<"Right-mouse-click on a wall to remove a wall cell."<<endl;
    cout<<endl;
    cout<<"Press R to run the game after modifying the maze."<<endl;
    while (maze.isRunning())
    {
        maze.update();
        maze.render();
    }


    return 0;
}

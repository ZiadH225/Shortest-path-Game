## Shortest Path Game using BFS Algorithm with SFML Library (C++)

This project implements a Shortest Path Game using the Breadth-First Search (BFS) algorithm in C++, utilizing the SFML (Simple and Fast Multimedia Library) for graphics and user interaction.

### Description

The Shortest Path Game is a simple application where the user navigates a character through a maze to reach a goal while finding the shortest path. The application visualizes the maze and the character movement using SFML graphics.

### Features

- **BFS Algorithm**: The application utilizes the Breadth-First Search algorithm to find the shortest path from the starting point to the goal within the maze.
- **SFML Graphics**: SFML library is used to provide interactive graphics, enhancing the user experience.
- **Customizable Mazes**: Users can create and customize their own maze layouts by modifying the maze matrix file.
- **Static Maze Modification**: To modify the maze, you must edit the matrix located at `Materials/Maze.txt`. Each character in the matrix represents a specific element:
  - `(w)` represents a wall
  - `(g)` represents grass
  - `(s)` represents the starting point
  - `(e)` represents the ending point

### Requirements

- C++ compiler
- SFML library

### Acknowledgements

This project was inspired by the desire to explore graph algorithms and interactive applications using C++ and SFML.

Feel free to contribute to this project by adding new features, fixing bugs, or providing suggestions for improvement!

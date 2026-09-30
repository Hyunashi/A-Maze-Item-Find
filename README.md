# A* Maze Solver

# Overview:

This project is a C++ command-line application that generates random mazes and solves them using the A* search algorithm.

Users can generate a maze, select a goal position and use A* to find a path from the starting position to the goal. The maze generator uses randomised depth-first search (DFS) to ensure that all open cells are connected.

# Features:

Random maze generation using depth-first search (DFS).
A* search algorithm for finding a path through the maze.
Manhattan distance heuristic for estimating the distance to the goal.
Four-directional movement (up, down, left and right).
Interactive command-line menu.
User-selected goal positions.
Displays the maze and the calculated solution.
Allows users to generate new mazes and solve them repeatedly.
Algorithms
Maze Generation: Randomised Depth-First Search

Pathfinding: A*

A* is used to find a path from the starting position to the user's selected goal.

The algorithm uses the following cost function:

f(n) = g(n) + h(n)

g(n): The cost of travelling from the starting position to the current node.
h(n): The estimated cost from the current node to the goal, calculated using Manhattan distance.
f(n): The estimated total cost of a path through the current node.

A priority queue is used to process nodes with the lowest estimated total cost first. The algorithm continues until it reaches the goal or determines that no path exists.

# Maze Representation:

The maze is represented as a two-dimensional vector of integers.

Value	Meaning
0	Open cell
1	Wall

The maze is displayed in the command line using the following symbols:


(S)Starting position

(F)Goal position

(-)Solution path

(.)Open cell

(#)Wall


# Project Structure:

main.cpp: Handles the command-line menu, user input and program flow.
AStar.cpp: Implements the A* pathfinding algorithm.
AStar.h: Declares the A* function.
Maze.cpp: Implements randomised DFS maze generation.
Maze.h: Declares the maze generation function.
Node.h: Defines the node structure used by A*.

# Requirements:

C++ compiler supporting C++11 or later.
Visual Studio 2022 or another compatible C++ development environment.

# How to Run:

Clone or download this repository.
Open the project in Visual Studio 2022.
Build the project.
Run the compiled application.

# How to Use:

Run the program.
Select the option to generate a new maze.
Choose an open cell as the goal/finish.
Select the option to solve the maze using A*.
View the resulting path displayed in the maze.
Generate another maze or select another goal as needed.

# Technologies:

C++
Standard Template Library (STL)
Visual Studio 2022
Git and GitHub

Author:

Clayton Cheung

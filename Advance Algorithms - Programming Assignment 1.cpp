// Advance Algorithms - Programming Assignment 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Node.h"
#include <cstdlib>
#include "AStar.h"
#include <random>
#include "Maze.h"

int main() {
    //std::vector<std::vector<int>> maze = {
    //    {0, 0, 0, 1, 0, 0, 0},
    //    {1, 1, 0, 1, 0, 1, 0},
    //    {0, 0, 0, 0, 0, 1, 0},
    //    {0, 1, 1, 1, 0, 0, 0}
    //}; //hardcoded starting maze

    const int rows = 10;
    const int cols = 10;

	std::vector<std::vector<int>> maze = generateMaze(rows, cols); //generate a random maze with the specified number of rows and columns
    
    Node start{ 0, 0, 0, 0, 0, -1, -1 }; //initialize start node with row, col, g, h, f values
    Node goal{ 3, 6, 0, 0, 0, -1, -1 }; //initialize goal node with row, col, g, h, f values

	maze[start.row][start.col] = 0; //ensure that the starting position in the maze is a path (0) and not a wall (1)
	maze[goal.row][goal.col] = 0; //ensure that the goal position in the maze is a path (0) and not a wall (1)

	start.h = std::abs(start.row - goal.row) + std::abs(start.col - goal.col); //formula for calculating heuristic value (h) using Manhattan distance
	start.f = start.g + start.h; //calculate the f value (total cost) for the start node

	std::vector<Node> path = aStar(maze, start, goal); //call the aStar function to find the path from start to goal

	while (path.empty()) { //if the path vector is empty, indicating that no path was found, generate a new maze and try again
		maze = generateMaze(rows, cols);  //generate a new random maze with the specified number of rows and columns   

		maze[start.row][start.col] = 0; //ensure that the starting position in the maze is a path (0) and not a wall (1)
		maze[goal.row][goal.col] = 0; //ensure that the goal position in the maze is a path (0) and not a wall (1)

		path = aStar(maze, start, goal); //call the aStar function again to find the path from start to goal in the new maze
    }

	if (path.empty()) { //check if the path vector is empty, indicating that no path was found
        std::cout << "No path found!\n";
        return 0;
    }

	std::vector<std::vector<bool>> pathGrid(maze.size(), std::vector<bool>(maze[0].size(), false)); //create a 2D vector to store the path grid with the same dimensions as the maze, initialized to false

    for (const Node& node : path) {
        pathGrid[node.row][node.col] = true;
    }

	//std::cout << "\nPath:\n"; //print the path found by the A* algorithm

	//for (Node& node : path) { //loop through each node in the path vector and print its row and column indices
    //    std::cout << "(" << node.row << ", " << node.col << ")\n";
    //}

	for (int row = 0; row < maze.size(); row++) { //loop through each row of the maze
		for (int col = 0; col < maze[row].size(); col++) { //loop through each column of the maze
			if (row == start.row && col == start.col) //check if the current position is the starting node
                std::cout << "S ";
			else if (row == goal.row && col == goal.col) //check if the current position is the goal node
                std::cout << "F ";
			else if (pathGrid[row][col]) //check if the current position is part of the path found by the A* algorithm
                std::cout << "* ";
			else if (maze[row][col] == 0) //check if the current position is a path (0) or a wall (1)
                std::cout << ". ";
			else 
                std::cout << "# ";
        }
		std::cout << "\n"; //newline after each row of the maze
    }

    return 0;
}
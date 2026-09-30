// Advance Algorithms - Programming Assignment 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Node.h"
#include <cstdlib>
#include "AStar.h"
#include <random>
#include "Maze.h"

void displayMaze(const std::vector<std::vector<int>>& maze, const std::vector<Node>& path, const Node& start, const Node& goal, const bool goalSelected) { //function to display the maze, path, start and goal positions
    
    std::vector<std::vector<bool>> pathGrid(maze.size(), std::vector<bool>(maze[0].size(), false));

	for (const Node& node : path) { //loop through each node in the path vector and mark its position in the pathGrid as true
        pathGrid[node.row][node.col] = true;
    }

	for (int row = 0; row < maze.size(); row++) { //loop through each row of the maze
		for (int col = 0; col < maze[row].size(); col++) { //loop through each column of the maze
			if (row == start.row && col == start.col) //Starting node print s
                std::cout << "S ";
            else if (goalSelected && row == goal.row && col == goal.col) //finish/goal node print F only if there is a selected goal
                std::cout << "F ";
			else if (pathGrid[row][col]) //if the node is part of the path, print -
                std::cout << "- ";
			else if (maze[row][col] == 0) //if the node is open, print .
                std::cout << ". ";
            else
				std::cout << "# "; //if the node is a wall, print #
        }
        std::cout << "\n";
    }
}

int main() {
    const int rows = 20; //initialise the size of the maze
    const int cols = 20;

	std::vector<std::vector<int>> maze; //create a 2D vector to store the maze
	std::vector<Node> path; //create a vector to store the path from start to goal

	Node start{ 0, 0, 0, 0, 0, -1, -1 }; //initialize start node 
    Node goal{ 3, 6, 0, 0, 0, -1, -1 }; //default goal node

	bool mazeGenerated = false; //flag to indicate if a maze has been generated
	bool goalSelected = false; //flag to indicate if a goal has been selected

    int choice;

    do {
        std::cout << "\n";
        std::cout << "\n============================\n";
		std::cout << "           MAZE\n";
        if (mazeGenerated) {
            displayMaze(maze, path, start, goal, goalSelected);
        }
        std::cout << "\n============================\n";

        std::cout << "\n============================\n";
        std::cout << "      A* MAZE OPTIONS\n";
        std::cout << "============================\n";
        std::cout << "1. Generate new maze\n";
        std::cout << "2. Choose goal\n";
        std::cout << "3. Solve maze with A*\n";
        std::cout << "4. Exit\n";
        std::cout << "============================\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) {
		    case 1: // Generate new maze if user inputs 1
			    maze = generateMaze(rows, cols); //generate a random maze with the specified number of rows and columns
			    maze[start.row][start.col] = 0; //ensure that the starting position in the maze is a path (0) and not a wall (1)
			    mazeGenerated = true; //set mazeGenerated to true to indicate that a maze has been generated
			    path.clear(); //clear the path vector to remove any previous paths
			    goalSelected = false; //reset goalSelected to false since a new maze has been generated
			    std::cout << "MESSAGE: New maze generated!\n"; //display message to indicate that a new maze has been generated
                break;

		    case 2: // Choose goal if user inputs 2 
			    if (!mazeGenerated) { //check if a maze has been generated before allowing the user to choose a goal
                    std::cout << "Generate a maze first!\n";
                    break;
                }

                std::cout << "Enter goal row (0-19): ";
                std::cin >> goal.row;
                std::cout << "Enter goal column (0-19): ";
                std::cin >> goal.col;

                if (goal.row < 0 || goal.row >= rows || goal.col < 0 || goal.col >= cols) { //check if the goal position is within the bounds of the maze
                    std::cout << "MESSAGE: Invalid goal position!\n";
                    break;
                }

                if (maze[goal.row][goal.col] == 1) { //check if the goal position in the maze is a wall(1)
                    std::cout << "MESSAGE: That position is a wall!\n";
                    break;
                }

			    goalSelected = true; //set goalSelected to true to indicate that a goal has been chosen
			    path.clear(); //clear the path vector to remove any previous paths
			    std::cout << "MESSAGE: Goal selected!\n"; //display message to indicate that a goal has been selected
                break;

		    case 3: // Solve maze with A* if user inputs 3
			    if (!mazeGenerated) { //check if a maze has been generated before allowing the user to solve the maze
                    std::cout << "MESSAGE: Generate a maze first!\n";
                    break;
                }

			    if (!goalSelected) { //check if a goal has been selected before allowing the user to solve the maze
                    std::cout << "MESSAGE: Choose a goal first!\n";
                    break;
                }

			    start.g = 0; //initialize g value for the start node
			    start.h = std::abs(start.row - goal.row) + std::abs(start.col - goal.col); //calculate the heuristic value (h) for the start node using Manhattan distance
			    start.f = start.g + start.h; //calculate the f value (total cost) for the start node

			    path = aStar(maze, start, goal); //call the aStar function to find the path from start to goal

			    if (path.empty()) { //check if the path vector is empty, indicating that no path was found
                    std::cout << "MESSAGE: No path found! Regenerate maze or choose new goal\n";
                }
			    else { //if the path was found
                    std::cout << "MESSAGE: Path found!\n";
                    std::cout << "MESSAGE: Path length: " << path.size() - 1 << "\n";
                }
                break;
		    case 4: // Exit if user inputs 4
                std::cout << "Exiting A* Maze Solver...\n";
                break;

		    default: // Handle invalid option if user inputs an option other than 1, 2, 3, or 4
                std::cout << "MESSAGE: Invalid option. Try again.\n";
        }
    } 
    
	while (choice != 4); //loop until the user chooses to exit the program by inputting 4

    return 0;
}

/*
int main() {
    //std::vector<std::vector<int>> maze = {
    //    {0, 0, 0, 1, 0, 0, 0},
    //    {1, 1, 0, 1, 0, 1, 0},
    //    {0, 0, 0, 0, 0, 1, 0},
    //    {0, 1, 1, 1, 0, 0, 0}
    //}; //hardcoded starting maze

    int goalRow, goalCol;

    Node goal{goalRow, goalCol, 0, 0, 0, -1, -1 };

    const int rows = 10;
    const int cols = 10;

    if (goal.row < 0 || goal.row >= rows || goal.col < 0 || goal.col >= cols) { //check if the goal position is within the bounds of the maze
        std::cout << "Invalid goal position!\n";
        return 0;
    }

	std::vector<std::vector<int>> maze = generateMaze(rows, cols); //generate a random maze with the specified number of rows and columns
    
    Node start{ 0, 0, 0, 0, 0, -1, -1 }; //initialize start node with row, col, g, h, f values

	maze[start.row][start.col] = 0; //ensure that the starting position in the maze is a path (0) and not a wall (1)
	
	if (maze[goal.row][goal.col] == 1) { //check if the goal position in the maze is a wall (1)
        std::cout << "That position is a wall!\n";
        return 0;
    }

	start.h = std::abs(start.row - goal.row) + std::abs(start.col - goal.col); //formula for calculating heuristic value (h) using Manhattan distance
	start.f = start.g + start.h; //calculate the f value (total cost) for the start node

	std::vector<Node> path = aStar(maze, start, goal); //call the aStar function to find the path from start to goal

	while (path.empty()) { //if the path vector is empty, indicating that no path was found, generate a new maze and try again
		maze = generateMaze(rows, cols);  //generate a new random maze with the specified number of rows and columns   

		maze[start.row][start.col] = 0; //ensure that the starting position in the maze is a path (0) and not a wall (1)
		maze[goal.row][goal.col] = 0; //ensure that the goal position in the maze is a path (0) doesn't turn into a wall (1) in the new maze

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
*/
// Advance Algorithms - Programming Assignment 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Node.h"
#include <cstdlib>

int main() {
    std::vector<std::vector<int>> maze = {
        {0, 0, 0, 1, 0, 0, 0},
        {1, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0, 0, 0}
    }; //hardcoded starting maze

	Node start{ 0, 0, 0, 0, 0 }; //initialize start node with row, col, g, h, f values
	Node goal{ 3, 6, 0, 0, 0 }; //initialize goal node with row, col, g, h, f values

	goal.h = std::abs(start.row - goal.row) + std::abs(start.col - goal.col); //formula for calculating heuristic value (h) using Manhattan distance

    for (int row = 0; row < maze.size(); row++) {
        for (int col = 0; col < maze[row].size(); col++) {
            if (row == start.row && col == start.col)
                std::cout << "S ";
            else if (row == goal.row && col == goal.col)
                std::cout << "F ";
            else if (maze[row][col] == 0)
                std::cout << ". ";
            else
                std::cout << "# ";
        }
        std::cout << "\n";
    }

    return 0;
}
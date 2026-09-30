#include "Maze.h"
#include <random>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> generateMaze(int rows, int cols)
{
    // Start with every cell as a wall.
    std::vector<std::vector<int>> maze(rows, std::vector<int>(cols, 1));

    if (rows <= 0 || cols <= 0) {
        return maze;
    }

	std::random_device rd; // Seed for random number generator
	std::mt19937 gen(rd()); // Initialize random number generator with the seed

    std::vector<std::pair<int, int>> stack;// Store the cells we are currently exploring.

    maze[0][0] = 0; 
    stack.push_back({ 0, 0 }); // Start at the top-left corner.

    const int dr[] = { -2, 2, 0, 0 }; // Directions: up, down, left, right.
    const int dc[] = { 0, 0, -2, 2 };

    while (!stack.empty()) {
		int row = stack.back().first; // Get the current cell's row and column.
        int col = stack.back().second;
        
        std::vector<int> neighbours; // Find unvisited neighbours two cells away.

		for (int i = 0; i < 4; i++) { // Loop through the four possible directions (up, down, left, right).
			int newRow = row + dr[i]; // Calculate the new row and column indices based on the current cell's position and the direction of movement.
			int newCol = col + dc[i];

			if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && maze[newRow][newCol] == 1) { // Check if the new position is within bounds and is a wall (1).
				neighbours.push_back(i); // If it is, add the direction to the list of unvisited neighbours.
            }
        }

		if (neighbours.empty()) { // If there are no unvisited neighbours, backtrack by popping the current cell from the stack.
            stack.pop_back();
        }
		else { // There are unvisited neighbours, so choose one at random and carve a path to it.
            
            std::uniform_int_distribution<> dist(0, static_cast<int>(neighbours.size()) - 1); // Pick a random unvisited neighbour.

			int direction = neighbours[dist(gen)]; // Get the direction of the chosen neighbour.

			int newRow = row + dr[direction]; // Calculate the new row and column indices based on the current cell's position and the direction of movement.
			int newCol = col + dc[direction];

            maze[row + dr[direction] / 2][col + dc[direction] / 2] = 0; // Open the wall between the current cell and the neighbour.

            maze[newRow][newCol] = 0; // Open the neighbour.

            stack.push_back({ newRow, newCol }); // Continue exploring from the neighbour.
        }
    }

    //	std::vector<std::vector<int>> maze(rows, std::vector<int>(cols, 0)); //create a 10 by 10 grid for a maze to be made
    //
    //	std::random_device rd; //seed for random number generator
    //	std::mt19937 gen(rd()); //initialize random number generator with the seed
    //	std::uniform_int_distribution<> dist(0, 99); //create a uniform distribution to generate random numbers between 0 and 99
    //
    //	for (int row = 0; row < rows; row++) { //loop through each row of the maze
    //		for (int col = 0; col < cols; col++) { //loop through each column of the maze
    //			if (dist(gen) < 30) { //30% chance of generating a wall (1) in the maze
    //				maze[row][col] = 1; //set the current position in the maze to a wall (1)
    //			}
    //		}
    //	}

    return maze;
}
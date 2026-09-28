#include "Maze.h"
#include <random>

std::vector<std::vector<int>> generateMaze(int rows, int cols) {
	std::vector<std::vector<int>> maze(rows, std::vector<int>(cols, 0)); //create a 10 by 10 grid for a maze to be made

	std::random_device rd; //seed for random number generator
	std::mt19937 gen(rd()); //initialize random number generator with the seed
	std::uniform_int_distribution<> dist(0, 99); //create a uniform distribution to generate random numbers between 0 and 99

	for (int row = 0; row < rows; row++) { //loop through each row of the maze
		for (int col = 0; col < cols; col++) { //loop through each column of the maze
			if (dist(gen) < 30) { //30% chance of generating a wall (1) in the maze
				maze[row][col] = 1; //set the current position in the maze to a wall (1)
			}
		}
	}

	return maze;
}
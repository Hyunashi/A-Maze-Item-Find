#include "AStar.h"
#include "Node.h"
#include <queue>
#include <vector>
#include <cmath>

struct CompareNode {
    bool operator()(const Node& a, const Node& b) const {
        return a.f > b.f;
    }
};

std::vector<Node> aStar(const std::vector<std::vector<int>>& maze, Node start, Node goal) {
	std::priority_queue<Node, std::vector<Node>, CompareNode> openList; //create a priority queue to store nodes to be evaluated
    
	openList.push(start); //push first starting node into the priority queue

	while (!openList.empty()) { //loop while there are still nodes in the open list
		Node current = openList.top(); //get the node with the lowest f value from the priority queue
		openList.pop(); //remove the node from the priority queue

        if (current.row == goal.row && current.col == goal.col) {
            
        }

		int rowChange[] = { -1, 1, 0, 0 }; //Store the different row and column changes for moving up, down, left, and right in the maze
        int colChange[] = { 0, 0, -1, 1 };

		for (int i = 0; i < 4; i++) { //loop through the four possible directions (up, down, left, right)
			int newRow = current.row + rowChange[i]; //calculate the new row and column indices based on the current node's position and the direction of movement
            int newCol = current.col + colChange[i];
            
			if (newRow < 0 || newRow >= maze.size() || newCol < 0 || newCol >= maze[0].size()) { //check if the new position is out of bounds
                continue;
            }

			if (maze[newRow][newCol] == 1) { //check if the new position is a wall
                continue;
            }
        }
    }

    return {};
}
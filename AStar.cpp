#include "AStar.h"
#include "Node.h"
#include <queue>
#include <vector>
#include <cmath>
#include <climits>

struct CompareNode {
    bool operator()(const Node& a, const Node& b) const {
        return a.f > b.f;
    }
};

std::vector<Node> aStar(const std::vector<std::vector<int>>& maze, Node start, Node goal) {

	std::vector<std::vector<int>> gScore(maze.size(), std::vector<int>(maze[0].size(), INT_MAX)); //create a 2D vector to store the g values for each node in the maze, initialise as infinintty 

	gScore[start.row][start.col] = 0; //set the g value of the starting node to 0

	std::vector<std::vector<std::pair<int, int>>> parent(maze.size(), std::vector<std::pair<int, int>>(maze[0].size(), { -1, -1 })); //create a 2D vector to store the parent node of each node in the maze, to return the path

	std::priority_queue<Node, std::vector<Node>, CompareNode> openList; //create a priority queue to store nodes to be evaluated
    
	openList.push(start); //push first starting node into the priority queue

	while (!openList.empty()) { //loop while there are still nodes in the open list
		Node current = openList.top(); //get the node with the lowest f value from the priority queue
		openList.pop(); //remove the node from the priority queue

        if (current.row == goal.row && current.col == goal.col) { //if the current node is the goal node, reconstruct the path by following the parent nodes back to the start node
			std::vector<Node> path; //create a vector to store the path from start to goal

            int row = current.row;
			int col = current.col; //initialize row and col variables to the current node's position

			while (row != start.row || col != start.col) { //loop until the current node is the starting node
				path.push_back(Node{ row, col, 0, 0, 0, -1, -1 }); //add the current node to the path vector

				int parentRow = parent[row][col].first; //get the row index of the parent node from the parent vector
				int parentCol = parent[row][col].second; //get the column index of the parent node from the parent vector

				row = parentRow; //update the row and column indices to the parent node's position
                col = parentCol;
            }

			path.push_back(Node{ start.row, start.col, 0, 0, 0, -1, -1 }); //add the starting node to the path vector since the loop ends before the starting node is added

			std::reverse(path.begin(), path.end()); //reverse the path vector so that it goes from start to goal

			return path; //return the path vector
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

			int newG = current.g + 1; //calculate the new g value (cost from start to current node (Current distance))

			if (newG < gScore[newRow][newCol]) { //check if the new g value is less than the previously recorded g value for this node
                gScore[newRow][newCol] = newG;

				parent[newRow][newCol] = { current.row, current.col }; //record in the parent node where the current node came from (to reconstruct the path later)

                int newH = std::abs(newRow - goal.row) + std::abs(newCol - goal.col);  //calculate the new h value (Estimated distance to the goal)

                int newF = newG + newH; //calculate the new f value (total cost) g + h

                Node neighbor{
                    newRow,
                    newCol,
                    newG,
                    newH,
                    newF,
                    current.row,
                    current.col
				}; //create a new neighbor node with the updated values

				openList.push(neighbor); //add the neighbor node to the priority queue
            }
        }
    }

    return {};
}
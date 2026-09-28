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
    }

    return {};
}
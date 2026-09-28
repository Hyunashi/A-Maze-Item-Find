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
    return {};
}
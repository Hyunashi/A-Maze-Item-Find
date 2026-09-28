#pragma once

#include <vector>
#include "Node.h"

std::vector<Node> aStar(
    const std::vector<std::vector<int>>& maze,
    Node start,
    Node goal
);
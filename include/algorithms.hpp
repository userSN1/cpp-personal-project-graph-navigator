#pragma once
#include "graph.hpp"
#include <string>
#include <vector>

struct PathResult {
    std::vector<std::string> path;
    double cost = 0.0;
    bool found = false;
    int visitedNodes = 0;
};

PathResult dijkstra(const Graph& graph, const std::string& start, const std::string& goal);
PathResult aStar(const Graph& graph, const std::string& start, const std::string& goal);
PathResult bfsMinHops(const Graph& graph, const std::string& start, const std::string& goal);

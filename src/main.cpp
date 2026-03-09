#include "algorithms.hpp"
#include "parser.hpp"
#include <iomanip>
#include <iostream>
#include <string>

namespace {
    void printUsage() {
        std::cout << "Usage: ./graph_navigator <graph_file> <start> <goal> <algorithm>\n";
        std::cout << "Algorithms: dijkstra | astar | bfs\n";
    }

    void printResult(const PathResult& result) {
        if (!result.found) {
            std::cout << "No path found.\n";
            return;
        }

        std::cout << "Path found\n";
        std::cout << "Visited nodes: " << result.visitedNodes << "\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Cost: " << result.cost << "\n";
        std::cout << "Route: ";
        for (size_t i = 0; i < result.path.size(); ++i) {
            std::cout << result.path[i];
            if (i + 1 < result.path.size()) std::cout << " -> ";
        }
        std::cout << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printUsage();
        return 1;
    }

    try {
        std::string file = argv[1];
        std::string start = argv[2];
        std::string goal = argv[3];
        std::string algorithm = argv[4];

        Graph graph = parseGraphFromFile(file);
        PathResult result;

        if (algorithm == "dijkstra") {
            result = dijkstra(graph, start, goal);
        } else if (algorithm == "astar") {
            result = aStar(graph, start, goal);
        } else if (algorithm == "bfs") {
            result = bfsMinHops(graph, start, goal);
        } else {
            std::cerr << "Unknown algorithm: " << algorithm << "\n";
            printUsage();
            return 1;
        }

        printResult(result);
        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
}

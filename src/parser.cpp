#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

Graph parseGraphFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    Graph graph;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }

        std::istringstream iss(line);
        std::string from, to;
        double weight, x1, y1, x2, y2;

        if (!(iss >> from >> to >> weight >> x1 >> y1 >> x2 >> y2)) {
            throw std::runtime_error("Invalid line in graph file: " + line);
        }

        if (!graph.hasNode(from)) graph.addNode(from, x1, y1);
        if (!graph.hasNode(to)) graph.addNode(to, x2, y2);
        graph.addEdge(from, to, weight, true);
    }

    return graph;
}

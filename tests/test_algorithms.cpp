#include "algorithms.hpp"
#include "parser.hpp"
#include <cassert>
#include <iostream>

int main() {
    Graph graph = parseGraphFromFile("data/sample_graph.txt");

    auto dijkstraResult = dijkstra(graph, "Paris", "Nice");
    assert(dijkstraResult.found);
    assert(!dijkstraResult.path.empty());
    assert(dijkstraResult.path.front() == "Paris");
    assert(dijkstraResult.path.back() == "Nice");

    auto aStarResult = aStar(graph, "Paris", "Nice");
    assert(aStarResult.found);
    assert(aStarResult.path.front() == "Paris");
    assert(aStarResult.path.back() == "Nice");

    auto bfsResult = bfsMinHops(graph, "Paris", "Nice");
    assert(bfsResult.found);

    std::cout << "All tests passed.\n";
    return 0;
}

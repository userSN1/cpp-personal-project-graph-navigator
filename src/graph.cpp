#include "graph.hpp"
#include <stdexcept>

void Graph::addNode(const std::string& name, double x, double y) {
    nodes_[name] = Node{name, x, y};
    adjacency_.try_emplace(name, std::vector<Edge>{});
}

void Graph::addEdge(const std::string& from, const std::string& to, double weight, bool bidirectional) {
    if (!hasNode(from) || !hasNode(to)) {
        throw std::runtime_error("Cannot add edge: missing node.");
    }
    adjacency_[from].push_back(Edge{to, weight});
    if (bidirectional) {
        adjacency_[to].push_back(Edge{from, weight});
    }
}

bool Graph::hasNode(const std::string& name) const {
    return nodes_.find(name) != nodes_.end();
}

const Node& Graph::getNode(const std::string& name) const {
    auto it = nodes_.find(name);
    if (it == nodes_.end()) {
        throw std::runtime_error("Node not found: " + name);
    }
    return it->second;
}

const std::vector<Edge>& Graph::neighbors(const std::string& name) const {
    auto it = adjacency_.find(name);
    if (it == adjacency_.end()) {
        throw std::runtime_error("Neighbors not found for node: " + name);
    }
    return it->second;
}

std::vector<std::string> Graph::nodeNames() const {
    std::vector<std::string> names;
    names.reserve(nodes_.size());
    for (const auto& [name, _] : nodes_) {
        names.push_back(name);
    }
    return names;
}

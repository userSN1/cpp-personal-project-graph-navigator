#pragma once
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
    std::string name;
    double x = 0.0;
    double y = 0.0;
};

struct Edge {
    std::string to;
    double weight = 0.0;
};

class Graph {
public:
    void addNode(const std::string& name, double x, double y);
    void addEdge(const std::string& from, const std::string& to, double weight, bool bidirectional = true);

    bool hasNode(const std::string& name) const;
    const Node& getNode(const std::string& name) const;
    const std::vector<Edge>& neighbors(const std::string& name) const;
    std::vector<std::string> nodeNames() const;

private:
    std::unordered_map<std::string, Node> nodes_;
    std::unordered_map<std::string, std::vector<Edge>> adjacency_;
};

#include "algorithms.hpp"
#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>
#include <queue>
#include <stdexcept>
#include <unordered_map>

namespace {
    std::vector<std::string> reconstructPath(
        const std::unordered_map<std::string, std::string>& previous,
        const std::string& start,
        const std::string& goal
    ) {
        std::vector<std::string> path;
        if (start == goal) {
            return {start};
        }
        auto it = previous.find(goal);
        if (it == previous.end()) {
            return {};
        }

        std::string current = goal;
        while (current != start) {
            path.push_back(current);
            current = previous.at(current);
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
        return path;
    }

    double heuristic(const Graph& graph, const std::string& a, const std::string& b) {
        const auto& na = graph.getNode(a);
        const auto& nb = graph.getNode(b);
        double dx = na.x - nb.x;
        double dy = na.y - nb.y;
        return std::sqrt(dx * dx + dy * dy);
    }
}

PathResult dijkstra(const Graph& graph, const std::string& start, const std::string& goal) {
    if (!graph.hasNode(start) || !graph.hasNode(goal)) {
        throw std::runtime_error("Start or goal node not found.");
    }

    using PQEntry = std::pair<double, std::string>;
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<>> pq;

    std::unordered_map<std::string, double> dist;
    std::unordered_map<std::string, std::string> prev;

    for (const auto& name : graph.nodeNames()) {
        dist[name] = std::numeric_limits<double>::infinity();
    }

    dist[start] = 0.0;
    pq.push({0.0, start});
    int visited = 0;

    while (!pq.empty()) {
        auto [currentDist, current] = pq.top();
        pq.pop();
        visited++;

        if (current == goal) {
            return {reconstructPath(prev, start, goal), currentDist, true, visited};
        }

        if (currentDist > dist[current]) {
            continue;
        }

        for (const auto& edge : graph.neighbors(current)) {
            double candidate = currentDist + edge.weight;
            if (candidate < dist[edge.to]) {
                dist[edge.to] = candidate;
                prev[edge.to] = current;
                pq.push({candidate, edge.to});
            }
        }
    }

    return {{}, 0.0, false, visited};
}

PathResult aStar(const Graph& graph, const std::string& start, const std::string& goal) {
    if (!graph.hasNode(start) || !graph.hasNode(goal)) {
        throw std::runtime_error("Start or goal node not found.");
    }

    using PQEntry = std::pair<double, std::string>;
    std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<>> openSet;

    std::unordered_map<std::string, double> gScore;
    std::unordered_map<std::string, double> fScore;
    std::unordered_map<std::string, std::string> prev;

    for (const auto& name : graph.nodeNames()) {
        gScore[name] = std::numeric_limits<double>::infinity();
        fScore[name] = std::numeric_limits<double>::infinity();
    }

    gScore[start] = 0.0;
    fScore[start] = heuristic(graph, start, goal);
    openSet.push({fScore[start], start});
    int visited = 0;

    while (!openSet.empty()) {
        auto [_, current] = openSet.top();
        openSet.pop();
        visited++;

        if (current == goal) {
            return {reconstructPath(prev, start, goal), gScore[goal], true, visited};
        }

        for (const auto& edge : graph.neighbors(current)) {
            double tentative = gScore[current] + edge.weight;
            if (tentative < gScore[edge.to]) {
                prev[edge.to] = current;
                gScore[edge.to] = tentative;
                fScore[edge.to] = tentative + heuristic(graph, edge.to, goal);
                openSet.push({fScore[edge.to], edge.to});
            }
        }
    }

    return {{}, 0.0, false, visited};
}

PathResult bfsMinHops(const Graph& graph, const std::string& start, const std::string& goal) {
    if (!graph.hasNode(start) || !graph.hasNode(goal)) {
        throw std::runtime_error("Start or goal node not found.");
    }

    std::queue<std::string> q;
    std::unordered_map<std::string, bool> visitedMap;
    std::unordered_map<std::string, std::string> prev;

    q.push(start);
    visitedMap[start] = true;
    int visited = 0;

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();
        visited++;

        if (current == goal) {
            auto path = reconstructPath(prev, start, goal);
            return {path, static_cast<double>(path.size() - 1), true, visited};
        }

        for (const auto& edge : graph.neighbors(current)) {
            if (!visitedMap[edge.to]) {
                visitedMap[edge.to] = true;
                prev[edge.to] = current;
                q.push(edge.to);
            }
        }
    }

    return {{}, 0.0, false, visited};
}

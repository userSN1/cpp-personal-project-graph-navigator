# cpp-personal-project-graph-navigator
C++ personal project (Graph Navigator)
## Features

- Load a graph from a text file
- Compute shortest path by distance using Dijkstra
- Compute heuristic-guided shortest path using A*
- Compute minimum-hop path using BFS
- Print both total cost and full path
- Includes a sample city graph

## Project structure

```text
include/
  graph.hpp
  algorithms.hpp
  parser.hpp
src/
  graph.cpp
  algorithms.cpp
  parser.cpp
  main.cpp
tests/
  test_algorithms.cpp
data/
  sample_graph.txt
```

## Build

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o graph_navigator
```

Run:

```bash
./graph_navigator data/sample_graph.txt Paris Nice dijkstra
./graph_navigator data/sample_graph.txt Paris Nice astar
./graph_navigator data/sample_graph.txt Paris Nice bfs
```

Run tests:

```bash
g++ -std=c++17 -Iinclude tests/test_algorithms.cpp src/graph.cpp src/algorithms.cpp src/parser.cpp -o tests_runner
./tests_runner
```

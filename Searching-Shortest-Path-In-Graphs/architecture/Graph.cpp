#pragma once
#include <vector>
#include <map>

// Класс для хранения графа.
class Graph {
public:
    // Список смежности графа.
    std::map<int, std::vector<std::pair<int, int>>> adjacency_list;
    // Количество вершин в графе.
    int number_of_vertex{};
    // Количество рёбер в графе.
    int number_of_edges{};
    Graph() = default;
    Graph(int number_of_vertex) : number_of_vertex(number_of_vertex) {
    };
    ~Graph() = default;
};
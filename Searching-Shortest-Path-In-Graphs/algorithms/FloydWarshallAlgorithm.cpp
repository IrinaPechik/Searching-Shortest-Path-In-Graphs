#include <iostream>
#include "../architecture/Graph.cpp"

class FloydWarshallAlgorithm {
public:
    // Ищет кратчайшее расстояние от вершины 0 до заданной вершины.
    static int64_t findShortestWay(const Graph& graph, int to_vertex_number) {
        int n = graph.number_of_vertex;
        auto adjacency_list = graph.adjacency_list;
        // Инициализируем матрицу расстояний.
        std::vector<std::vector<int64_t>> dist(n, std::vector<int64_t>(n, INT64_MAX));

        // Заполняем матрицу расстояний из списка смежности.
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
            for (const auto& neighbor : adjacency_list[i]) {
                int first = neighbor.first;
                int second = neighbor.second;
                dist[i][first] = second;
            }
        }

        // Алгоритм Флойда-Уоршелла.
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][k] != INT64_MAX && dist[k][j] != INT64_MAX) {
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        if (to_vertex_number >= n || to_vertex_number < 0 || dist[0][to_vertex_number] == INT64_MAX) {
            return -1;
        } else {
            return dist[0][to_vertex_number];
        }
    }
};
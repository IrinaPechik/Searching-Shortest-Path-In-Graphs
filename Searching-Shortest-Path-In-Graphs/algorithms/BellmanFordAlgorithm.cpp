#include <iostream>
#include "../architecture/Graph.cpp"

class BellmanFordAlgorithm {
public:
    // Ищет кратчайшее расстояние от вершины 0 до заданной вершины.
    static int64_t findShortestWay(const Graph& graph, int to_vertex_number) {
        int n = graph.number_of_vertex;
        auto adjacency_list = graph.adjacency_list;
        // Вектор расстояний. Храним расстояние + количество релаксаций.
        // Соответственно, если количество релаксаций превышает количество возможных проходов,
        // то у нас цикл.
        std::vector<std::pair<int64_t, int>> d(n, std::make_pair(INT64_MAX, 0));

        // Расстояние до стартовой вершины.
        d[0].first = 0;

        int i = 1;
        // Путь - максимум n - 1 рёбер.
        // Но для поиска релаксация будем проходиться в цикле n раз.
        // Нумерация начинается с 1.
        for (; i <= n + n; ++i) {
            bool any = false;
            // Проходим по всем вершинам графа.
            for (const auto& pair : adjacency_list) {
                auto from = pair.first;
                for (const auto& edge : pair.second) {
                    int64_t to = edge.first;
                    int64_t weight = edge.second;
                    if (d[from].second > n - 1) {
                        d[to].second = d[from].second;
                        any = true;
                    } else {
                        if (d[from].first < INT64_MAX) {
                            if (d[to].first > d[from].first + weight) {
                                d[to].first = d[from].first + weight;
                                d[to].second = i;
                                any = true;
                            }
                        }
                    }
                }
            }
            if (!any) {
                break;
            }
        }
        if (to_vertex_number >= n || to_vertex_number < 0 || d[to_vertex_number].second > n - 1
            || (d[to_vertex_number].first == INT64_MAX)) {
            return -1;
        } else {
            return d[to_vertex_number].first;
        }
    }
};
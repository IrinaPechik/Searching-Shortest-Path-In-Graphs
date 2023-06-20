#include <iostream>
#include <set>
#include "../architecture/Graph.cpp"

class DijkstraAlgorithm {
public:
    // Ищет кратчайшее расстояние от вершины 0 до заданной вершины.
    static int64_t findShortestWay(const Graph& graph, int to_vertex_number) {
        int n = graph.number_of_vertex;
        auto adjacency_list = graph.adjacency_list;

        std::vector<int64_t> d(n, INT64_MAX);
        // Расстояние до вершин.
        d[0] = 0;

        // Храним расстояние и номер вершины.
        // Причём расстояние - первым для автоматической сортировки по нему.
        std::set<std::pair<int, int>> q;
        q.insert(std::make_pair(d[0], 0));
        while (!q.empty()) {
            // Запоминаем номер вершины, которая сейчас весит меньше всех.
            int cur_v = q.begin()->second;
            // Удаляем её.
            q.erase(q.begin());
            // Для каждой вершины, в которую ведёт текущая-минимальная, смотрим наименьший вес.
            for (size_t j = 0; j < adjacency_list[cur_v].size(); ++j) {
                int to = adjacency_list[cur_v][j].first;
                int weight = adjacency_list[cur_v][j].second;
                // Если можем получить вес меньше - меняем.
                if (d[cur_v] + weight < d[to]) {
                    q.erase(std::make_pair(d[to], to));
                    d[to] = d[cur_v] + weight;
                    q.insert(std::make_pair(d[to], to));
                }
            }
        }
        if (to_vertex_number >= n || to_vertex_number < 0 || d[to_vertex_number] == INT64_MAX) {
            return -1;
        } else {
            return d[to_vertex_number];
        }
    }
};
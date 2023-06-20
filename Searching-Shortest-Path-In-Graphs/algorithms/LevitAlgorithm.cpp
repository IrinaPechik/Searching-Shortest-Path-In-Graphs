#include <iostream>
#include "../architecture/Graph.cpp"
#include <queue>

class LevitAlgorithm {
public:
    // Ищет кратчайшее расстояние от вершины 0 до заданной вершины.
    static int64_t findShortestWay(const Graph& graph, int to_vertex_number) {
        int n = graph.number_of_vertex;
        auto adjacency_list = graph.adjacency_list;
        std::vector<int64_t> d(n, INT64_MAX);
        std::vector<int> p(n, -1);
        d[0] = 0;
        std::deque<int> queue;
        std::vector<int> id(n);
        queue.push_back(0);
        while (!queue.empty())
        {
            int v = queue.front();
            queue.pop_front();
            id[v] = 1;

            // Проходим по всем смежным вершинам
            for (const auto& edge : adjacency_list[v])
            {
                int to = edge.first;
                int64_t len = edge.second;

                int64_t relaxed_distance = d[v] + len;
                if (relaxed_distance < d[to])
                {
                    d[to] = relaxed_distance;
                    if (id[to] == 0) {
                        queue.push_back(to);
                    } else if (id[to] == 1) {
                        queue.push_front(to);
                    }
                    p[to] = v;
                    id[to] = 1;
                }
            }
        }

        if (to_vertex_number >= n || to_vertex_number < 0 || d[to_vertex_number] == INT64_MAX) {
            return -1;
        }
        // Возвращаем расстояние до заданной вершины
        return d[to_vertex_number];
    }
};


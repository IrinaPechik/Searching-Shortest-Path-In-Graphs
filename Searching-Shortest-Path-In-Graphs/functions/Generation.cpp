#include <random>
#include <algorithm>
#include <unordered_set>
#include "../architecture/Graph.cpp"

class Generation {
public:
    static std::vector<Graph> generate(int flag) {
        std::vector<Graph> graphs;
        if (flag == 0) {
            for (int i = 10; i <= 1010; i += 50) {
                // Генерируем полный граф c количеством вершин i и добавляем его к результату генерации.
                graphs.push_back(generateCompleteGraph(i));
            }
        } else if (flag == 1) {
            for (int i = 10; i <= 1010; i += 50) {
                // Генерируем связный граф c количеством вершин i и коэффициентом
                // плотности приблизительно 0.4-0.5.
                graphs.push_back(generateConnectedGraphWithDensity(i));
            }
        } else {
            for (int i = 10; i <= 1010; i += 50) {
                // Генерируем разреженный граф c количеством вершин i.
                graphs.push_back(generateSparseGraph(i));
            }
        }
        return graphs;
    }

private:
    // Генерируем полный граф с заданным количеством вершин.
    static Graph generateCompleteGraph(int number_of_vertex) {
        int number_of_edges = 0;
        Graph graph = Graph(number_of_vertex);
        std::mt19937 rng(time(nullptr));
        std::uniform_int_distribution<int> uniform_dist(1, 10);
        for (int i = 0; i < number_of_vertex; ++i) {
            for (int j = i + 1; j < number_of_vertex; ++j) {
                int weight = uniform_dist(rng);
                graph.adjacency_list[i].push_back(std::make_pair(j, weight));
                graph.adjacency_list[j].push_back(std::make_pair(i, weight));
                number_of_edges++;
            }
        }
        graph.number_of_edges = number_of_edges;
        return graph;
    }

    // Генерируем связный разреженный граф (дерево).
    static Graph generateSparseGraph(int number_of_vertex) {
        int number_of_edges = 0;
        Graph graph = Graph(number_of_vertex);
        std::mt19937 rng(time(nullptr));
        std::uniform_int_distribution<int> uniform_dist(1, 10);
        for (int i = 1; i < number_of_vertex; i++) {
            // Генерируем предка для текущей вершины.
            int parent = std::uniform_int_distribution<int>(0, i - 1)(rng);
            int weight = uniform_dist(rng);
            graph.adjacency_list[i].push_back(std::make_pair(parent, weight));
            graph.adjacency_list[parent].push_back(std::make_pair(i, weight));
            number_of_edges++;
        }
        graph.number_of_edges = number_of_edges;
        return graph;
    }

    // Генерируем связный граф с коэффициентом плотности ~0.4-0.5.
    static Graph generateConnectedGraphWithDensity(int number_of_vertex) {
        // Генерируем полный связный граф.
        Graph graph = generateCompleteGraph(number_of_vertex);
        std::mt19937 rng(time(nullptr));

        // Вершины, которые будут включены в конечный граф с заданным коэффициентом плотности.
        std::vector<int> vertex(number_of_vertex);
        // Заполняем вектор номерами вершин [0, number_of_vertex).
        std::iota(vertex.begin(), vertex.end(), 0);
        // Случайным образом перетасовываем вершины.
        std::shuffle(vertex.begin(), vertex.end(), rng);

        int new_size = std::floor(0.45 * number_of_vertex);
        std::unordered_set<int> vertexSet(vertex.begin(), vertex.begin() + new_size);

        for (int j = 0; j < number_of_vertex; ++j) {
            if (vertexSet.find(j) == vertexSet.end()) {
                graph.adjacency_list.erase(j);
                for (auto& adjacencyList : graph.adjacency_list) {
                    auto& edges = adjacencyList.second;
                    edges.erase(std::remove_if(edges.begin(), edges.end(), [j](const std::pair<int, int>& edge) {
                        return edge.first == j;
                    }), edges.end());
                    graph.number_of_edges--;
                }
            }
        }
        return graph;
    }
};
#include <fstream>
#include <chrono>
#include "algorithms/BellmanFordAlgorithm.cpp"
#include "algorithms/FloydWarshallAlgorithm.cpp"
#include "algorithms/DijkstraAlgorithm.cpp"
#include "algorithms/LevitAlgorithm.cpp"
#include "functions/Generation.cpp"


int main() {
    // Алгоритмы.
    std::string algorithms_names[4]{"Dijkstra", "Floyd–Warshall", "Bellman–Ford", "Levit"};
    // Названия файлов: 0 - Полные графы, 1 - Связные графы, 2 - Разреженные графы.
    std::string file_names[3] {"../files/complete_graphs.csv", "../files/connected_graphs.csv",
                               "../files/sparse_graphs.csv"};

    // Объявляем тип указателя на функцию псевдонимом.
    typedef int64_t (*findShortestWayFunctions)(const Graph& graph, int to_vertex_number);
    findShortestWayFunctions all_functions[4]{DijkstraAlgorithm::findShortestWay,
                                              FloydWarshallAlgorithm::findShortestWay,
                                              BellmanFordAlgorithm::findShortestWay,
                                              LevitAlgorithm::findShortestWay};

    // Все графы. В каждом индексе лежат по 21 графу с числом вершин от 10 до 1010 (шаг 50).
    // 0 - Полные графы,
    // 1 - Связные графы,
    // 2 - Разреженные графы.
    std::vector<std::vector<Graph>> graphs(3);

    // Генерируем все тестовые данные.
    // Передаём генератору тип графа (0, 1 или 2).
    // Помещаем в graphs для каждого типа 21 сгенерированный граф.
    for (int i = 0; i < 3; ++i) {
        graphs[i] = Generation::generate(i);
    }
    // Результат замера в наносекундах.
    long long nanoseconds;
    // Создаём поток вывода в файл.
    std::ofstream my_file;

    // Для каждого файла выводим замеры в него.
    for (int file_counter = 0; file_counter < 3; ++file_counter) {
        // Открываем очередной файл.
        my_file.open(file_names[file_counter]);
        // Делаем шапку для таблицы текущего файла.
        my_file << "number of vertex" << ',';
        my_file << "number of edges" << ',';
        // Названия алгоритмов.
        for (const auto& algorithm_name : algorithms_names) {
            my_file << algorithm_name << ',';
        }
        // Заканчиваем делать шапку.
        my_file << std::endl;

        int number_of_vertex = 10;
        // Проходимся по всем 21 графам с разным количеством вершин для текущего типа графа.
        for (const auto& graph : graphs[file_counter]) {
            // Записываем в первый столбец количество вершин.
            my_file << number_of_vertex << ',';
            my_file << graph.number_of_edges << ',';
            // Вызываем для каждого графа три алгоритма.
            for (int algorithm_type = 0; algorithm_type < 4; ++algorithm_type) {
                /* Задаём вершину, расстояние до которой будем искать.
                Делаю это для того, чтобы в случае чего можно было пользователю давать возможность
                находить расстояние до нужной ему вершины. */
                int to_vertex = 8;
                // Начинаем замер времени.
                auto start = std::chrono::high_resolution_clock::now();
                // Запускаем алгоритм для графа.
                all_functions[algorithm_type](graph, to_vertex);
                // Заканчиваем замер времени.
                auto elapsed = std::chrono::high_resolution_clock::now() - start;
                nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
                // Записываем количество затраченного времени
                my_file << nanoseconds << ',';
            }
            number_of_vertex += 50;
            // Переходим к следующей строке таблицы.
            my_file << std::endl;
        }
        // Закрываем текущий файл.
        my_file.close();
    }
    return 0;
}

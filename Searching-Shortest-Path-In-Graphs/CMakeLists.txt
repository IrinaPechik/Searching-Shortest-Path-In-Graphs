cmake_minimum_required(VERSION 3.21)
project(CHT_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(CHT_3 main.cpp architecture/Graph.cpp functions/Generation.cpp algorithms/DijkstraAlgorithm.cpp algorithms/FloydWarshallAlgorithm.cpp algorithms/BellmanFordAlgorithm.cpp algorithms/LevitAlgorithm.cpp)

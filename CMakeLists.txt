cmake_minimum_required(VERSION 3.27)
project(DA_FirstProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA_FirstProject main.cpp
        src/App.cpp
        src/Graph.cpp
        src/FileParse.cpp
        src/Vertex.cpp
        src/Edge.cpp
        src/UI.cpp
        src/City.cpp
        src/Station.cpp
        src/Reservoir.cpp
        src/Node.cpp)

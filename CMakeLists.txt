cmake_minimum_required(VERSION 3.27)
project(DA_FirstProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
set(ENV{ASAN_OPTIONS} "verbosity=1")


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

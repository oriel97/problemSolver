cmake_minimum_required(VERSION 3.15)
project(evenDereh2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(evenDereh2 main.cpp server.h ClientHandler.h SerialServer.cpp SerialServer.h Solver.h
        MyClientHandler.h Matrix.cpp Matrix.h Cell.cpp Cell.h State.h Searcheable.h
        MyParallelServer.cpp MyParallelServer.h BestFirstSearch.h BFS.h DFS.h OA.h PriorityQueue.h Searcher.h nameSpace.cpp nameSpace.h
        CachManager.h)
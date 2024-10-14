cmake_minimum_required(VERSION 3.27)
project(Projeto2AED)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projeto2AED main.cpp
        Menu.cpp
        Menu.h
        ReadFiles.cpp
        ReadFiles.h
        Airport.cpp
        Airport.h
        Airline.cpp
        Airline.h
        Graph.h
        Flight.cpp
        Graph.cpp
        Management.cpp)

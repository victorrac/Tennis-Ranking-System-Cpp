cmake_minimum_required(VERSION 3.27)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled2 main.cpp
        Menu+Functionalities.cpp
        TournamentHelpFunctions.cpp
        RankingFunctions.cpp
        WTA1000.cpp
        WTA500.cpp
        WTA250.cpp)

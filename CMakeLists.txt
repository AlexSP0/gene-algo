cmake_minimum_required(VERSION 3.5)

project(genetic_algo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core)

set(SOURCES
        main.cpp
        mainwindow.h
        mainwindow.cpp
        mainwindow.ui
        genome.h genome.cpp
        bobtheresercher.h
        bobtheresercher.cpp
        bobsmap.h bobsmap.cpp
        testmap.h
)

add_executable(genetic_algo ${SOURCES})
target_link_libraries(genetic_algo PRIVATE Qt5::Widgets Qt5::Core)


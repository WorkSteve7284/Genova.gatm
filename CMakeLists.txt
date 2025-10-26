cmake_minimum_required(VERSION 3.20)

project(Genova LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Genova
    src/main.cpp
)

target_sources(Genova
PRIVATE
    src/Genova.cpp
    src/Tools.cpp
    src/Variables.cpp
)

target_include_directories(Genova PRIVATE include)
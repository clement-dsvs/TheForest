cmake_minimum_required(VERSION 3.26)
project(TheForest)

set(CMAKE_CXX_STANDARD 23)

add_executable(TheForest src/main.cpp)

target_include_directories(TheForest PRIVATE include)

find_package(imgui CONFIG REQUIRED)
find_package(raylib REQUIRED)
find_package(CMakeRC CONFIG REQUIRED)
cmrc_add_resource_library(TheForest-resources ALIAS TheForest::rc NAMESPACE TheForest)

target_link_libraries(TheForest PRIVATE
        imgui::imgui
        raylib
        TheForest::rc
)
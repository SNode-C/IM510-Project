cmake_minimum_required(VERSION 3.5)

project(IM510-Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
    snodec COMPONENTS express net-in core-legacy
)

add_executable(IM510-Project main.cpp WebServer.cpp)
target_link_libraries(IM510-Project PRIVATE snodec::express snodec::core-legacy snodec::net-in)


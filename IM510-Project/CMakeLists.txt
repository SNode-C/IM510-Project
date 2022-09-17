cmake_minimum_required(VERSION 3.5)

project(IM510-Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
    snodec COMPONENTS express net-in core-legacy db-mariadb
)

find_package(PkgConfig REQUIRED)

pkg_check_modules(MARIADB mariadb)

if(MARIADB_FOUND)

    add_executable(IM510-Project main.cpp WebServer.cpp Database.cpp)
    target_link_libraries(IM510-Project PRIVATE snodec::express snodec::core-legacy snodec::net-in snodec::db-mariadb)

    target_include_directories(
        IM510-Project
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${MARIADB_INCLUDE_DIRS}
               "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
               "$<INSTALL_INTERFACE:include/snode.c>"
    )
    install(TARGETS IM510-Project RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

endif(MARIADB_FOUND)

cmake_minimum_required(VERSION 3.22)

project(netsim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion)

include_directories(include)

set(SOURCE_FILES
        src/package.cpp
        src/storage_types.cpp
        src/helpers.cpp
        src/nodes.cpp
        src/factory.cpp
        src/simulation.cpp
        src/reports.cpp
        )

add_executable(netsim ${SOURCE_FILES} main.cpp)



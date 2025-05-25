cmake_minimum_required(VERSION 3.15)
project(StringSorts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/sorting
    ${PROJECT_SOURCE_DIR}/environment
)

set(SORTING_SOURCES
    sorting/merge.cpp
    sorting/quick_radix.cpp
    sorting/quick.cpp
    sorting/radix.cpp
    sorting/str_merge.cpp
    sorting/str_quick.cpp
)

set(SOURCES
    environment/main.cpp
    ${SORTING_SOURCES}
)

add_executable(StringSorts ${SOURCES})

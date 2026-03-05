cmake_minimum_required(VERSION 3.20)
project(calc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(calc_math
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/../calc-math
)
FetchContent_MakeAvailable(calc_math)

add_executable(calc
    src/main.cpp
    src/runner.cpp
    src/parser.cpp
    src/checker.cpp
    src/calculator.cpp
    src/printer.cpp
)

target_include_directories(calc PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(calc PRIVATE calc_math)

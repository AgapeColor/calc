cmake_minimum_required(VERSION 3.20)
project(calc LANGUAGES CXX)

# Compiling settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project options
option(ENABLE_CLANG_TIDY "Run clang-tidy during build" ON)
option(ENABLE_CLANG_FORMAT "Add clang-format target" ON)

# Dependencies
include(FetchContent)
FetchContent_Declare(
    calc_math
    GIT_REPOSITORY https://github.com/AgapeColor/calc-math.git
    GIT_TAG main
)
FetchContent_MakeAvailable(calc_math)

# clang-tidy
if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if(CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
    else()
        message(WARNING "clang-tidy not found")
    endif()
endif()

# clang-format
if(ENABLE_CLANG_FORMAT)
    find_program(CLANG_FORMAT_EXE NAMES clang-format)
    if(CLANG_FORMAT_EXE)
        file(GLOB_RECURSE FORMAT_FILES CONFIGURE_DEPENDS
            ${CMAKE_SOURCE_DIR}/src/*.cpp
            ${CMAKE_SOURCE_DIR}/include/*.h
            ${CMAKE_SOURCE_DIR}/include/*.hpp
        )

        add_custom_target(format
            COMMAND ${CLANG_FORMAT_EXE} -i ${FORMAT_FILES}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Running clang-format"
            VERBATIM
        )
    else()
        message(WARNING "clang-format not found")
    endif()
endif()


# Targets
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

# Install
include(GNUInstallDirs)
install(TARGETS calc RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

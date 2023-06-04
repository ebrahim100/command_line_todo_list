cmake_minimum_required(VERSION 3.24)
project(todo)
set(CXX_STANDARD 17)
add_subdirectory(src)
add_executable(todo main.cpp sqlite3.c)
target_link_libraries(todo model)
target_compile_options(todo PRIVATE -Wall -O2)
include_directories(todo PUBLIC /include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


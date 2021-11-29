cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wall -std=c++17")

project(sqlite)

add_executable(
  sqlite
  src/main.cpp
  src/database.cpp
)

include_directories(/usr/include)
link_directories(/usr/lib)
target_link_libraries(sqlite sqlite3)

set(EXECUTABLE_OUTPUT_PATH "bin")
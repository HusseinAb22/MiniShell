cmake_minimum_required(VERSION 3.10)
project(minishell)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)

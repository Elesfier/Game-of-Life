
cmake_minimum_required(VERSION 2.6)

project (Life)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
set(MAIN_SOURCE_DIR ${Life_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

subdirs ( src/main src/game src/matrix )

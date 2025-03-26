cmake_minimum_required(VERSION 3.10)
project(OmegaNumTest)
add_executable(OmegaNumTest test.c)

target_link_libraries(OmegaNumTest m)

file(COPY tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

project(OmegaNum)
add_library(OmegaNum SHARED omeganum.c)

cmake_minimum_required(VERSION 3.0)
project(project)
add_compile_options(-Wall)
include_directories(headers)

file(GLOB SOURCES "src/*.cpp")

add_executable(project ${SOURCES})
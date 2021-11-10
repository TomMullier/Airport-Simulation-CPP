cmake_minimum_required(VERSION 3.20.5)
project(project_cir)

include_directories(headers)

file(GLOB SOURCES "src/*.cpp")

add_executable(project ${SOURCES})

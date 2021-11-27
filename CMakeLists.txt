cmake_minimum_required(VERSION 3.0)
project(project)
add_compile_options(-Wall)
include_directories(headers)

file(GLOB SOURCES "src/*.cpp")
find_package(nlohmann_json 3.2.0 REQUIRED)
FIND_PACKAGE(SFML 2 REQUIRED graphics network audio window system)

target_link_libraries(nlohmann_json::nlohmann_json)

add_executable(project ${SOURCES})


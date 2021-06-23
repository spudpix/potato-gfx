cmake_minimum_required(VERSION 3.10)

project(firsttriangle LANGUAGES CXX)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

add_subdirectory(depends/glfw/)
add_subdirectory(depends/glad/)

include_directories(vendor/glfw/include/
                    include/)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} glad glfw)

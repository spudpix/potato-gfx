cmake_minimum_required(VERSION 3.10)

project(potato-gfx LANGUAGES CXX)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

add_subdirectory(depends/glfw/)
add_subdirectory(depends/glad/)
add_subdirectory(src/)

include_directories(vendor/glfw/include/
                    include/)

target_link_libraries(${PROJECT_NAME} glad glfw)

cmake_minimum_required(VERSION 3.7...3.20)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

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

configure_file("shaders/vertex.glsl" "src/" COPYONLY)
configure_file("shaders/fragment.glsl" "src/" COPYONLY)
configure_file("textures/container.jpg" "src/" COPYONLY)

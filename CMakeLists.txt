cmake_minimum_required(VERSION 3.7...3.20)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(potato-gfx LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

add_subdirectory(extern/glfw/)
add_subdirectory(extern/glad/)
add_subdirectory(extern/glm/)

add_subdirectory(src/)

include_directories(vendor/glfw/include/
                    include/)

target_link_libraries(${PROJECT_NAME} glad glfw glm)

configure_file("shaders/vertex.glsl" "src/" COPYONLY)
configure_file("shaders/fragment.glsl" "src/" COPYONLY)
configure_file("textures/container.jpg" "src/" COPYONLY)
configure_file("textures/awesomeface.png" "src/" COPYONLY)
configure_file("textures/PixelPotato512.png" "src/" COPYONLY)

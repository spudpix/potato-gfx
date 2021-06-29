cmake_minimum_required(VERSION 3.7...3.20)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(SOURCE_FILES main.cpp shader.h shader.cpp stb_image.h stb_image.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

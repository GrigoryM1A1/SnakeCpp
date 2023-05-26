cmake_minimum_required(VERSION 3.24)
project(CppGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(CppGame main.cpp gameengine.cpp gameengine.h snakesection.cpp snakesection.h apple.cpp apple.h wall.cpp wall.h)
include_directories(C:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

find_package(SFML REQUIRED system window graphics)


if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(CppGame ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()
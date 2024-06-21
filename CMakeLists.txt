cmake_minimum_required(VERSION 3.10)
project(C++game)

find_package(X11)

add_executable(C++game main.cpp)

target_link_libraries(C++game
        ${X11_LIBRARIES}
        )
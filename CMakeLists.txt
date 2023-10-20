cmake_minimum_required(VERSION 3.26)
project(CapstoneProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static")

add_executable(CapstoneProject main.cpp
        src/client.cpp
        include/client.h
        src/server.cpp
        include/server.h
        src/encrypt.cpp
        include/encrypt.h)

target_link_libraries(CapstoneProject wsock32 ws2_32)


cmake_minimum_required(VERSION 3.26)
project(CapstoneProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(CapstoneProject main.cpp
        src/client.cpp
        include/client.h
        src/server.cpp
        include/server.h)

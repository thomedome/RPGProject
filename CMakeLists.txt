cmake_minimum_required(VERSION 4.0)
project(RPGProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(RPGProject
        RPG.cpp
        Player.cpp
        Enemy.cpp
        Shop.cpp
)
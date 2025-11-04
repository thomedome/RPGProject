cmake_minimum_required(VERSION 4.0)
project(RPGProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(RPGProject
        RPG.cpp
        RPGHeaders/Player.cpp
        RPGHeaders/Enemy.cpp
        RPGHeaders/Shop.cpp
)
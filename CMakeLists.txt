cmake_minimum_required(VERSION 4.0)
project(RPGProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(RPGProject
        RPG.cpp
        RPGClasses/Player.cpp
        RPGClasses/Enemy.cpp
        RPGClasses/Shop.cpp
        RPGClasses/Spell.cpp
        RPGClasses/Spell.h
)
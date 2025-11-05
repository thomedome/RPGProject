# RPGProject
This is a bare bones CLI RPG. 
I started this project to learn more about C++ Game Development, and the general basics of C++. (Yes I took inspiration from LOL for item names... sue me ;D )

## Contents
- Turn based combat
- Modular classes
- Shop system with items
- Save and load function
- Simple enemy AI
- CMake Build Config

## Build + Reqs
- C++17 or later
- CMake (3.10+ recommended)

g++ -std=c++17 RPG.cpp RPGHeaders/Player.cpp RPGHeaders/Enemy.cpp RPGHeaders/Shop.cpp -o RPGProject

or just use the release... ;)

## FYI:
This is not an official Riot-affiliated project, it is free for anyone to play / mess with, and all references to League of Legends IP belong to Riot Games.
Also, saves are stored in /gameSaves/ (created automatically.) All save files are plain-text.
Any suggestions, create an issue, or email me (email below)

## Things that don't work at the moment:
 - Grievous Wounds debuff from the Thornmail item.
 - Casting doesn't do anything.
 - Balancing is sub-par... 

## If you want to contact me for any reason, email me!
thomedome@gmail.com

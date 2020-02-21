cmake_minimum_required(VERSION 3.15)
project(NewHaven)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(NewHaven
        Building.cpp
        Building.h
        CMakeLists.txt
        GBMap.cpp
        GBMap.h
        GBMapLoader.cpp
        GBMapLoader.h
        Graph.cpp
        Graph.h
        Hand.cpp
        Hand.h
        Harvest.cpp
        Harvest.h
        Main.cpp
        Node.cpp
        Node.h
        Player.cpp
        Player.h
        Resources.cpp
        Resources.h
        TileNode.cpp
        TileNode.h
        VGMapLoader.cpp
        VGMapLoader.h)

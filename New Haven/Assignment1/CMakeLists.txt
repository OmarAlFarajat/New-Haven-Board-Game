cmake_minimum_required(VERSION 3.15)
project(NewHaven VERSION 1.0
    DESCRIPTION "A playable version of the board game New Haven" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

file(GLOB driver Main.cpp)

file(GLOB resources Resources.cpp Resources.h)
file(GLOB building Building.cpp Building.h)
file(GLOB harvest Harvest.cpp Harvest.h)
file(GLOB player Player.cpp Player.h Hand.cpp Hand.h)

file(GLOB node Node.cpp Node.h TileNode.cpp TileNode.h)
file(GLOB graph Graph.cpp Graph.h)
file(GLOB GBmap GBmap.cpp GBmap.h GBMapLoader.cpp GBMapLoader.h)
file(GLOB VGMap VGMap.cpp VGMap.h VGMapLoader.cpp VGMapLoader.h)

file(GLOB Graphic CImg.h DrawDisplay.h MapDrawer.cpp MapDrawer.h)
file(GLOB GameObservers GameObservers.cpp GameObservers.h)
file(GLOB control Game.cpp Game.h)

add_executable(NewHaven ${graph} ${Graphic} ${GameObservers} ${control} ${node}
    ${building} ${harvest} ${resources} ${player} ${GBMap} ${VGMap} ${driver})

install(TARGETS NewHaven)

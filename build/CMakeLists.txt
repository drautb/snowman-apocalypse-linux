cmake_minimum_required(VERSION 2.8)

project(snowman-apocalypse-linux)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin)
set(CMAKE_BUILD_TYPE Debug)

add_definitions("-Wall")
add_definitions("-std=c++0x")

# FMod?

include_directories(${CMAKE_SOURCE_DIR}/../inc)

add_executable(snowman-apocalypse-linux 
               ${CMAKE_SOURCE_DIR}/../src/main.cpp
               ${CMAKE_SOURCE_DIR}/../src/Calvin.cpp
               ${CMAKE_SOURCE_DIR}/../src/Camera.cpp
               ${CMAKE_SOURCE_DIR}/../src/Flag.cpp
               ${CMAKE_SOURCE_DIR}/../src/FlameParticleEmitter.cpp
               ${CMAKE_SOURCE_DIR}/../src/Fort.cpp
               ${CMAKE_SOURCE_DIR}/../src/Keyboard.cpp
               ${CMAKE_SOURCE_DIR}/../src/Message.cpp
               ${CMAKE_SOURCE_DIR}/../src/MessageManager.cpp
               ${CMAKE_SOURCE_DIR}/../src/Mouse.cpp
               ${CMAKE_SOURCE_DIR}/../src/MovingObject.cpp
               ${CMAKE_SOURCE_DIR}/../src/Object.cpp
               ${CMAKE_SOURCE_DIR}/../src/Particle.cpp
               ${CMAKE_SOURCE_DIR}/../src/RenderManager.cpp
               ${CMAKE_SOURCE_DIR}/../src/SnowSplashEmitter.cpp
               ${CMAKE_SOURCE_DIR}/../src/Snowball.cpp
               ${CMAKE_SOURCE_DIR}/../src/SnowfallParticleEmitter.cpp
               ${CMAKE_SOURCE_DIR}/../src/Snowman.cpp
               ${CMAKE_SOURCE_DIR}/../src/SnowmanManager.cpp
               ${CMAKE_SOURCE_DIR}/../src/StatusBar.cpp
               ${CMAKE_SOURCE_DIR}/../src/SteamEmitter.cpp
               ${CMAKE_SOURCE_DIR}/../src/Window.cpp
               ${CMAKE_SOURCE_DIR}/../src/World.cpp)

target_link_libraries(snowman-apocalypse-linux GL GLU glfw)
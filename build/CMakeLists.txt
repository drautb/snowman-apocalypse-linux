cmake_minimum_required(VERSION 2.8)

project(snowman-apocalypse-linux)

set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin/${CMAKE_BUILD_TYPE})

add_definitions("-Wall")
add_definitions("-std=c++0x")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW glfw3)

find_package(DevIL)

include_directories(${CMAKE_SOURCE_DIR}/../inc)

add_executable(snowman-apocalypse-linux 
               ${CMAKE_SOURCE_DIR}/../src/main.cpp
               ${CMAKE_SOURCE_DIR}/../src/Calvin.cpp
               ${CMAKE_SOURCE_DIR}/../src/Camera.cpp
               ${CMAKE_SOURCE_DIR}/../src/Flag.cpp;
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

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()

target_link_libraries(snowman-apocalypse-linux 
                      GLU
                      ${GLFW_STATIC_LIBRARIES} 
                      ${IL_LIBRARIES}
                      ${ILU_LIBRARIES}
                      ${ILUT_LIBRARIES}
                      /usr/local/lib/FMOD/libfmodex64.so)

cmake_minimum_required(VERSION 3.16)
project(pocket_engine)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH} )
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS} "-pthread")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(LuaJIT REQUIRED)

include_directories(pocket_engine ${SDL_INCLUDE_DIRS})
include_directories(pocket_engine ${OPENGL_INCLUDE_DIRS})
#include_directories(pocket_engine ${LUA_INCLUDE_DIR})

# include_directories(pocket_engine "src/framework")
include_directories(pocket_engine "src")
include_directories(pocket_engine "third_party")
# aux_source_directory("src/framework" FRAMEWORK_SRC)

set(PK_SRCS
        src/main.cpp

        src/pocket/window.cpp
        src/pocket/engine.cpp
        src/pocket/world.cpp

        src/pocket/game/character.cpp
        src/pocket/game/entity.cpp
        src/pocket/game/tilemap.cpp

        src/pocket/graphics/batch.cpp
        src/pocket/graphics/graphics.cpp
        src/pocket/graphics/shader.cpp
        src/pocket/graphics/sprite.cpp
        src/pocket/graphics/texture.cpp

        src/pocket/input/input.cpp

        src/pocket/IO/pkfile.cpp

        src/pocket/json/deserializer.cpp
        src/pocket/json/parser.cpp
        src/pocket/json/readfile.cpp

        src/pocket/math/constants.cpp
        src/pocket/math/matmath.cpp
        src/pocket/math/vecmath.cpp

        src/pocket/components/player_controller.cpp
        src/pocket/components/sprite.cpp
        src/pocket/components/tilemap.cpp
	)

file(GLOB LIBRARIES_SRC third_party/glad/glad.c)

add_executable(pocket_engine ${PK_SRCS} ${LIBRARIES_SRC})
target_link_libraries(pocket_engine ${SDL2_LIBRARIES})
target_link_libraries(pocket_engine ${OPENGL_LIBRARIES})
target_link_libraries(pocket_engine ${CMAKE_DL_LIBS})

#target_link_libraries(pocket_engine ${LUA_LIBRARY})

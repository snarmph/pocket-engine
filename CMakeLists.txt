cmake_minimum_required(VERSION 3.18)
project(pocket_engine)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH} )
set(CMAKE_C_STANDARD 11)
#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(LuaJIT REQUIRED)

include_directories(pocket_engine ${SDL_INCLUDE_DIRS}) 
include_directories(pocket_engine ${OPENGL_INCLUDE_DIRS})
#include_directories(pocket_engine ${LUA_INCLUDE_DIR}) 

include_directories(pocket_engine "src/framework")
aux_source_directory("src/framework" FRAMEWORK_SRC)

add_executable(pocket_engine src/main ${FRAMEWORK_SRC})
target_link_libraries(pocket_engine ${SDL2_LIBRARIES})
target_link_libraries(pocket_engine ${OPENGL_LIBRARIES})
#target_link_libraries(pocket_engine ${LUA_LIBRARY})
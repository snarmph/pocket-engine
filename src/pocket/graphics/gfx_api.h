#pragma once

#ifdef __linux__ 
#include <SDL2/SDL.h>
#elif _WIN32
#include <sdl2/include/SDL.h>
#include <windows.h>
#else
#error "PLATFORM NOT SUPPORTED"
#endif

#include <glad/glad.h>
#include <GL/gl.h>
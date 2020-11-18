#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <SDL2/SDL_opengl.h>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow(
        "Pocket Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        500, 500,
        SDL_WINDOW_OPENGL
    );

    while(true) {
        SDL_Event e;

        while(SDL_PollEvent(&e)) {
            switch(e.type) {
            case SDL_QUIT:
                goto out_of_loop;
                break;
            }
        }
    }

out_of_loop:
    SDL_DestroyWindow(window);
    SDL_Quit();
}
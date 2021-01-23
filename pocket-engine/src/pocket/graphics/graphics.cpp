#include "graphics.hpp"

#include <glad/glad.h>

namespace gfx {
    shader_t basic_shader;

    void init() {
        glClearColor(0.1f, 0.1f, 0.1f, 0.f);
//        glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_LESS);
        // cull backfaces
        // (everything is actually drawn on the opposite face
        // this way y++ actually goes down)
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CW);
        glCullFace(GL_BACK);
        // enable blending for transparent textures
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        basic_shader.load("shaders/basic.vert", "shaders/basic.frag");
    }
} // namespace gfx
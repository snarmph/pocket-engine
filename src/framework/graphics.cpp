#include "graphics.hpp"

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "crash.hpp"
#include "matmath.hpp"

namespace gfx {
    shader_t basic_shader;
    mat3     projection;

    void init() {
        glClearColor(0.1f, 0.1f, 0.1f, 0.f);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);
        glEnable(GL_CULL_FACE);

        basic_shader.load("shaders/basic.vert", "shaders/basic.frag");
        math::viewport(projection, 160, 144);
    }
} // namespace gfx
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "types.hpp"
#include "shader.hpp"
#include "mat.hpp"

namespace gfx {
    extern shader_t basic_shader;
    extern mat3     projection;

    void init();
} // namespace gfx


#endif

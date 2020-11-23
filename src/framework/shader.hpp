#ifndef SHADER_HPP
#define SHADER_HPP

#include <cstdio>

#include <glad/glad.h>
#include <GL/gl.h>

// #include <cglm/types.h>

#include "types.hpp"
#include "vec.hpp"
#include "mat.hpp"

namespace gfx {
    struct shader_t {
        u32 id;

        shader_t();
        shader_t(const char *vpath, const char *fpath);

        void load(const char *vpath, const char *fpath);

        void use();

        template<typename T>
        void set(const char *name, T value);   
    };

    template<>
    inline void shader_t::set<int>(const char *name, int value) {
        glUniform1i(glGetUniformLocation(id, name), value);
    }

    template<>
    inline void shader_t::set<float>(const char *name, float value) {
        glUniform1f(glGetUniformLocation(id, name), value);
    }


    template<>
    inline void shader_t::set<vec2f>(const char *name, vec2f value) {
        glUniform2fv(glGetUniformLocation(id, name), 1, value.v);
    }

    template<>
    inline void shader_t::set<vec3f>(const char *name, vec3f value) {
        glUniform3fv(glGetUniformLocation(id, name), 1, value.v);
    }

    // template<>
    // inline void shader_t::set<vec4f>(const char *name, vec4f value) {
    //     glUniform4fv(glGetUniformLocation(id, name), 1, value);
    // }


    template<>
    inline void shader_t::set<mat2>(const char *name, mat2 value) {
        glUniformMatrix2fv(glGetUniformLocation(id, name), 1, GL_FALSE, value[0]);
    }

    template<>
    inline void shader_t::set<mat3>(const char *name, mat3 value) {
        glUniformMatrix3fv(glGetUniformLocation(id, name), 1, GL_FALSE, value[0]);
    }

    // template<>
    // inline void shader_t::set<mat4>(const char *name, mat4 value) {
    //     glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, value[0]);
    // }
} // namespace gfx

#endif
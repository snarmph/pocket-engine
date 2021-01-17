#include "shader.hpp"

#include <pocket/IO/pkfile.hpp>

namespace gfx {
    shader_t::shader_t() {
        id = 0;
    }

    shader_t::shader_t(const char *vpath, const char *fpath) {
        load(vpath, fpath);
    }

    void shader_t::load(const char *vpath, const char *fpath) {
        pk::file vertf, fragf;
        vertf.open(vpath);
        fragf.open(fpath);

        const char *vsource = vertf.read_whole();
        const char *fsource = fragf.read_whole();

        u32 vertex, fragment;
        i32 success;
        char info_log[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vsource, NULL);
        glCompileShader(vertex);
        glGet3Shaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertex, 512, NULL, info_log);
            printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %s\n", info_log);
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fsource, NULL);
        glCompileShader(fragment);
        glGet3Shaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fragment, 512, NULL, info_log);
            printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED %s\n", info_log);
        }

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        glGet3Shaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(id, 512, NULL, info_log);
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED %s\n", info_log);
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        free(const_cast<char*>(vsource));
        free(const_cast<char*>(fsource));
    }

    void shader_t::use() {
        glUseProgram(id);
    }
} // namespace gfx
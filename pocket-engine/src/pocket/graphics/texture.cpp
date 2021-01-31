#include "texture.hpp"

#include "gfx_api.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <pocket/util/crash.hpp>

namespace gfx {

    texture_t::texture_t() {
        id = 0;
    }

    texture_t::texture_t(const char *fname) {
        //load(fname);
    }

    void texture_t::load(const char *fname) {
        i32 channels;
        byte *data = stbi_load(fname, &size.x, &size.y, &channels, 0);
        
        if(!data) {
            crash(data_error, "couldn't load image [ %s ]", fname);
        }
        else {
            
            GLenum format = (channels==4) ? GL_RGBA : GL_RGB;
            
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, data);

            glBindTexture(GL_TEXTURE_2D, 0);

            printf("loaded [ %s ]\n", fname);
        }

data_error:
        stbi_image_free(data);
    }
//
//    void texture_t::bind() {
//        glBindTexture(GL_TEXTURE_2D, id);
//    }
//
//    void texture_t::unbind() {
//        glBindTexture(GL_TEXTURE_2D, 0);
//    }
} // namespace gfx
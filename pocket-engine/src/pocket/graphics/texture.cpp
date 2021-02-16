#include "texture.hpp"

#include <stb/stb_image.h>

#include <pocket/util/crash.hpp>

namespace gfx {

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
            sg_image_desc desc{};

            desc.width = size.x;
            desc.height = size.y;
            desc.pixel_format = SG_PIXELFORMAT_RGBA8;
            desc.content.subimage[0][0].ptr = data;
            desc.content.subimage[0][0].size = size.x * size.y * channels;

            image_id = sg_make_image(desc);

            /*
            GLenum format = (channels==4) ? GL_RGBA : GL_RGB;
            
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, data);

            glBindTexture(GL_TEXTURE_2D, 0);
            */
            printf("loaded [ %s ]\n", fname);
        }

data_error:
        stbi_image_free(data);
    }

    void load_from_memory(byte *data) {

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
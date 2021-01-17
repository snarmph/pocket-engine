#include "tilemap.hpp"

#include <pocket/json/json.hpp>


namespace pk {
    void tilemap::render(gfx::batcher &batch) {
        for(u8 i = 0; i<layers.size(); i++) {
            batch.set_layer((gfx::layers)i);
            batch.set_texture(texture);
            for(size_t j=0; j<layers[i].frames.size(); j++)
                batch.rect(layers[i].frames[j], layers[i].texcoords[j]);
        }
    }

    void tilemap::load(const char *fname) {
        json::Parser p;
        auto map = p.parse(json::fromFile(fname));

        texture.load(map["tileset"]["filename"].as_string().c_str());
        tile_size = (f32) map["tileset"]["tilesize"].as_number();

        u32 tex_cols = texture.size.x / 16;

        vec2f tex_step {
            tile_size / texture.size.x,
            tile_size / texture.size.y
        };

        width = (u32) map["width"].as_number();
        height = (u32) map["height"].as_number();

        assert(map["layers"].as_array().size() <= 3 && "too many layers in tilemap");

        for(size_t i=0; i<map["layers"].as_array().size(); i++) {
            const auto &data = map["layers"][i].as_array();
            //if(i)
            //    layers[i].z_pos = layers[i-1].z_pos + 1.f;
            for(size_t j=0; j<data.size(); j++) {
                u32 num = ((u32)data[j].as_number());
                if(num == 0)
                    continue;
                num--;
                f32 x = (j % width) * tile_size;
                f32 y = (j / width) * tile_size;
                u32 tx = num % tex_cols;
                u32 ty = num / tex_cols;
                layers[i].frames.emplace_back(
                    vec2f{x, y},
                    vec2f{tile_size}
                );
                layers[i].texcoords.emplace_back(
                    tx * tex_step.x, ty * tex_step.y,
                    tex_step.x, tex_step.y
                );
            }
        }
    }
} // namespace pk 
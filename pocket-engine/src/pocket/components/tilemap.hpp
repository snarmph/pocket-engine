#pragma once

#include <pocket/core/world.hpp>
#include <pocket/math/rect.hpp>
#include <pocket/graphics/texture.hpp>
#include <pocket/containers/containers.hpp>

#include <pocket/generated/tileset_data_fromjson.hpp>

namespace pk {

    enum terrain_mask : u8 {
        none        = 0b0000'0000,
        collision   = 0b0000'0001,
        water       = 0b0000'0010,
        ledge       = 0b0000'0100
    };

    struct tilemap : public component {
        virtual void render(gfx::batcher &batch);

        void load(const char *fname);

        i32 position_to_index(const vec2f &pos);
        inline bool is_colliding(u32 index);

        inline rectf get_bounds();

        struct layer {
            vector<rectf> frames;
            vector<rectf> texcoords;
        };

        gfx::texture_t texture;
        array<layer, 3> layers;
        bitvector collisions;
        f32 tile_size = 16;
        u32 width = 0;
        u32 height = 0;

    private:
        void load_from_json(string &fname);
        void load_from_struct(pocket::tilemap *data);
    };

    rectf tilemap::get_bounds() {
        return {
            position.x, position.y,
            width * tile_size, height * tile_size
        };
    }
    
    bool tilemap::is_colliding(u32 index) {
        return collisions[index];
    }


} // namespace pk 
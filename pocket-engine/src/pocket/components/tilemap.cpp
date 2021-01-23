#include "tilemap.hpp"

#include <filesystem>
#include <pocket/debug/benchmark.hpp>

#include "tilemap_animator.hpp"

namespace fs = std::filesystem;

namespace pk {
    void tilemap::render(gfx::batcher &batch) {
        batch.push_matrix(mat3x2::from_position(position));
        for(u8 i = 0; i<layers.size(); i++) {
            batch.set_layer((gfx::layers)i);
            batch.set_texture(texture);
            batch.rect_vec(layers[i].frames, layers[i].texcoords);
        }
        batch.pop_matrix();
    }

    void tilemap::load(const char *fname) {
        // 240'000 vs 25'000
        string binary_data_fname = string(fname) + ".pocket";
        pocket::tilemap tilemap_data;

        if (fs::exists(binary_data_fname.cstr())) {
            printf("bin file exists\n");
            pocket::read_tilemap(&tilemap_data, binary_data_fname.cstr());
            load_from_struct(&tilemap_data);
        }
        else {
            printf("bin file doesn't exists\n");
            json::Parser p;
            string json_data_fname = string(fname) + ".json";
            auto map = p.parse(json::fromFile(json_data_fname.stdstr()));
            pocket::json_to_tilemap(map, &tilemap_data);
            pocket::write_tilemap(&tilemap_data, binary_data_fname.cstr());
            load_from_struct(&tilemap_data);
        }

        auto animator = get<tilemap_animator>();
        animator->load(&tilemap_data, this);
    }

    void tilemap::load_from_json(string &fname) {
        json::Parser p;
        auto map = p.parse(json::fromFile(fname.stdstr()));

        texture.load(map["tileset"]["filename"].as_string().c_str());
        tile_size = (f32)map["tileset"]["tilesize"].as_number();

        u32 tex_cols = texture.size.x / (u32)tile_size;

        vec2f tex_step{
            tile_size / texture.size.x,
            tile_size / texture.size.y
        };

        width = (u32)map["width"].as_number();
        height = (u32)map["height"].as_number();

        assert(map["layers"].as_array().size() <= 4 && "too many layers in tilemap");

        for (size_t i = 0; i < 3; i++) {
            const auto &data = map["layers"][i].as_array();
            for (size_t j = 0; j < data.size(); j++) {
                u32 num = ((u32)data[j].as_number());
                if (num == 0)
                    continue;
                num--;
                f32 x = (j % width) * tile_size;
                f32 y = (j / width) * tile_size;
                u32 tx = num % tex_cols;
                u32 ty = num / tex_cols;
                layers[i].frames.emplace_back(
                    vec2f{ x, y },
                    vec2f{ tile_size }
                );
                layers[i].texcoords.emplace_back(
                    tx * tex_step.x, ty * tex_step.y,
                    tex_step.x, tex_step.y
                );
            }
        }

        auto &collision_layer = map["layers"][3].as_array();
        for (u32 i = 0; i < collision_layer.size(); i++) {
            auto numb = (i32)collision_layer[i].as_number();
            collisions.emplace_back((bool)numb);
        }
    }

    void tilemap::load_from_struct(pocket::tilemap *data) {
        texture.load(data->tileset.filename.cstr());
        tile_size = data->tileset.tilesize;
        
        u32 tex_cols = texture.size.x / (u32)tile_size;

        vec2f tex_step{
            tile_size / texture.size.x,
            tile_size / texture.size.y
        };

        width = data->width;
        height = data->height;

        assert(data->layers.size() == 4 && "wrong number of layers in tilemap");

        for (size_t i = 0; i < 3; i++) {
            auto &layer = data->layers[i];
            for (size_t j = 0; j < layer.size(); j++) {
                if (layer[j] == 0)
                    continue;
                layer[j]--;
                f32 x = (j % width) * tile_size;
                f32 y = (j / width) * tile_size;
                u32 tx = layer[j] % tex_cols;
                u32 ty = layer[j] / tex_cols;
                layers[i].frames.emplace_back(
                    vec2f{ x, y },
                    vec2f{ tile_size }
                );
                layers[i].texcoords.emplace_back(
                    tx * tex_step.x, ty * tex_step.y,
                    tex_step.x, tex_step.y
                );
            }
        }

        for (auto &collision : data->layers[3])
            collisions.emplace_back((bool)collision);
    }

    i32 tilemap::position_to_index(const vec2f &pos) {
        if(!get_bounds().contains(pos))
            return -1;
        
        i32 x = i32(pos.x - position.x) / 16;
        i32 y = i32(pos.y - position.y) / 16;

        return (y * width) + x;
    }

} // namespace pk 
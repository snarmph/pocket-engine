#include "tilemap_animator.hpp"

#include <pocket/core/time.hpp>

#include <pocket/generated/tileset_data.hpp>

namespace pk {
	void tilemap_animator::load(pocket::tilemap *data, tilemap *map) {
		u32 tex_cols = map->texture.size.x / (u32)map->tile_size;
		vec2f tex_step{
			map->tile_size / map->texture.size.x,
			map->tile_size / map->texture.size.y
		};

		int counter = 0;
		for (auto &anim_data : data->animations) {
			printf("counter: %d\n", counter++);
			animations.emplace_back();
			auto &anim = animations.back();
			
			for (auto &index_data : anim_data.index_data) {
				for (auto &index : index_data.indices)
					anim.texcoords_refs.emplace_back(
						&map->layers[index_data.layer].texcoords[index]
					);
			}

			for (auto &anim_info : anim_data.animation) {
				u32 tx = anim_info.index % tex_cols;
				u32 ty = anim_info.index / tex_cols;

				anim.durations.emplace_back((f32)anim_info.duration);
				anim.tex_coords.emplace_back(
					tx * tex_step.x, ty * tex_step.y,
					tex_step.x, tex_step.y
				);
			}
		}
	}

	void tilemap_animator::update() {
		for (auto &anim : animations) {
			anim.counter += time::dt;
			//printf("c > %f, d > %f\n", anim.counter, anim.durations[anim.frame]);
			while (anim.counter >= anim.durations[anim.frame]) {
				anim.counter -= anim.durations[anim.frame];
				if (++anim.frame == anim.durations.size())
					anim.frame = 0;
				for (auto *tc : anim.texcoords_refs)
					(*tc) = anim.tex_coords[anim.frame];
			}
		}
	}

} // namespace pk
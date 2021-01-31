#include "animator.hpp"

#include <pocket/core/time.hpp>
#include <pocket/util/pkassert.h>

#include "sprite.hpp"

namespace pk {
	void animator::add_animation(const string &name, const vector<pair<u32, f32>> &data, const vec2i &cell_size, bool repeat) {
		str_to_index[name] = (u32)animations.size();
		animations.emplace_back();
		auto &anim = animations.back();
		anim.repeat = repeat;

		auto &texture = get<sprite>()->texture;
		
		vec2f tex_step {
			(f32)cell_size.x / texture.size.x,
			(f32)cell_size.y / texture.size.y
		};

		u32 rows = texture.size.x / cell_size.x;

		for (const auto &d : data) {
			const u32 &index = d.first;
			const f32 &duration = d.second;

			f32 tx = (index % rows) * tex_step.x;
			f32 ty = (index / rows) * tex_step.y;

			rectf tc{
				tx, ty, 
				tex_step.x, tex_step.y
			};

			anim.frames.emplace_back(tc, duration);
		}
	}

	void animator::add_animation(const string &name, animation &anim) {
		u32 id = (u32)animations.size();
		animations.emplace_back(anim);
		str_to_index[name] = id;
	}

	void animator::play(const string &animation_name) {
		auto found = str_to_index.find(animation_name);
		pkassert(found != str_to_index.end(), "animation not found");
		u32 was = anim_index;
		anim_index = found->second;
		auto &anim = animations[anim_index];
		if (anim_index != was) {
			f32 dur = anim.frames[anim.frame_index].duration;

			if (anim.frame_counter >= (dur / 2.f)) {
				anim.frame_index++;
				if (anim.frame_index == anim.frames.size())
					anim.frame_index = 0;
			}
			anim.frame_counter = 0.f;
		}
		
		update_sprite(anim);
	}

	void animator::update() {
		auto &anim = animations[anim_index];
		auto &current = anim.frames[anim.frame_index];
		anim.frame_counter += time::dt;

		while (anim.frame_counter >= current.duration) {
			anim.frame_counter -= current.duration;
			if (++anim.frame_index == anim.frames.size())
				anim.frame_index = anim.repeat ? 0 : (u32)(anim.frames.size() - 1);
			update_sprite(anim);
		}
	}

	void animator::update_sprite(animation &anim) {
		get<sprite>()->tex_coords = anim.frames[anim.frame_index].tex_coords;
	}
} // namespace pk
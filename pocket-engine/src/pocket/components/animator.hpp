#pragma once

#include <pocket/core/world.hpp>
#include <pocket/graphics/texture.hpp>
#include <pocket/containers/containers.hpp>

namespace pk {
	struct anim_frame {
		rectf tex_coords;
		f32 duration = 0.f;

		anim_frame() = default;
		anim_frame(const rectf &tc, const f32 &dur)
			: tex_coords(tc), duration(dur) {}
	};

	struct animation {
		vector<anim_frame> frames;
		u32 frame_index = 0;
		f32 frame_counter = 0.f;
		bool repeat = false;
	};

	struct animator : public component {
		void add_animation(const string &name, const vector<pair<u32, f32>> &data, const vec2i &cell_size, bool repeat = false);
		void add_animation(const string &name, animation &anim);
		void play(const string &anim);

		void update() override;
		//void render(gfx::batcher &batch) override;

		//gfx::texture_t texture;
		//rectf frame;
		//vec2f offset = vec2f::zero();
		vector<animation> animations;
		map<string, u32> str_to_index;
		u32 anim_index = 0;

	private:
		void update_sprite(animation &anim);
	};
} // namespace pk


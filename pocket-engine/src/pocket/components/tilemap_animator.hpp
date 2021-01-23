#pragma once

#include <pocket/core/world.hpp>
#include <pocket/graphics/texture.hpp>
#include <pocket/containers/containers.hpp>

#include "tilemap.hpp"

namespace pocket {
	struct tilemap;
}

namespace pk {

	/*
	for anim in animations:
		anim.counter += timed::dt
		while(anim.counter >= anim.duration[frame]):
			anim.counter -= anim.duration[frame];
			if(++anim.frame == anim.durations.size()):
				anim.frame = 0
	*/
	struct tilemap_animation {
		//u32 index;
		u32 frame = 0;
		f32 counter = 0.f;

		vector<rectf *> texcoords_refs;

		vector<f32> durations;
		vector<rectf> tex_coords;
	};

	struct tilemap_animator : public component {
		void load(pocket::tilemap *data, tilemap *map);
		void update() override;

	private:
		vector<tilemap_animation> animations;
	};

} // namespace pk 
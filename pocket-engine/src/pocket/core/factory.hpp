#pragma once

#include "world.hpp"

namespace pk {
	struct factory {
		static entity *new_tilemap(const char *fname);
		static entity *new_player(const char *fname);
		static entity *new_gameobject(const vec2f &position);

		inline static world &get_world();

	private:
		static world w;
	};


	inline world &factory::get_world() {
		return w;
	}
} // namespace pk


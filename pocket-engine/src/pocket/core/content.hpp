#pragma once

#include <pocket/graphics/texture.hpp>

struct content {
	static bool load(const char *fname, gfx::texture_t &dest);
};
#pragma once
#include <pocket/core/types.hpp>
#include <pocket/containers/containers.hpp>

namespace pocket {
	struct animation_data {
		u32 index;
		f32 duration;
	};

	struct animation_index {
		u32 layer;
		vector<u32> indices;
	};

	struct animation_t {
		vector<animation_index> index_data;
		vector<animation_data> animation;
	};

	struct tileset_t {
		string filename;
		f32 tilesize;
	};

	struct tilemap {
		vector<animation_t> animations;
		vector<vector<u32>> layers;
		tileset_t tileset;
		u32 width;
		u32 height;
	};

	void read_tilemap(tilemap *data, const char *fname);
	void write_tilemap(tilemap *data, const char *fname);
 } // namespace pocket

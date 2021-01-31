#pragma once

#include <pocket/core/world.hpp>
#include <pocket/graphics/texture.hpp>
#include <pocket/containers/containers.hpp>

#include "tilemap.hpp"

// -*, bugprone-*, google-*, misc-*, modernize-*, performance-*, portability-*,  readability-*, -google-readability-braces-around-statements,-google-readability-namespace-comments, -google-runtime-references, -misc-non-private-member-variables-in-classes, -modernize-return-braced-init-list, -modernize-use-trailing-return-type, -modernize-avoid-c-arrays, -performance-move-const-arg, -readability-braces-around-statements, -readability-magic-numbers, -readability-named-parameter, -readability-redundant-declaration

namespace pocket {
	struct tilemap;
}

namespace pk {
	struct tilemap_animation {
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
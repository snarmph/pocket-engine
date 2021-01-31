#pragma once
#include <pocket/core/world.hpp>

namespace pk {
	struct collider : public component {
		rectf get_rect();
		rectf box;
	};

	inline rectf collider::get_rect() {
		return box + position;
	}
} // namespace pk
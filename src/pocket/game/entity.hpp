#pragma once

#include <pocket/graphics/batch.hpp>
#include <pocket/types.hpp>

namespace game {
	struct entity {
		virtual void input() {};
		virtual void update(f32 dt) {};
		virtual void render(gfx::batcher &b) {};
		virtual void interact(entity *from) {};
	};
} // namespace game

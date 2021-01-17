// #include "character.hpp"
// #include <SDL2/SDL.h>

// #include <pocket/input/input.hpp>
// #include <pocket/math/vecmath.hpp>

// // Precise method, which guarantees v = v1 when t = 1. This method is monotonic only when v0 * v1 < 0. Lerping between same values might not produce the same value
// f32 lerp(f32 v0, f32 v1, f32 tt) {
// 	f32 t = tt;
// 	return (1 - t) * v0 + t * v1;
// }

// vec2f move_towards(const vec2f &current, const vec2f &target, f32 max_dist_dt) {
// 	vec2f a = target - current;
// 	f32 mag = math::mag(a);
// 	if (mag <= max_dist_dt || mag == 0.f)
// 		return target;
// 	return current + a / mag * max_dist_dt;
// }

// namespace game {
// 	character::character() {
// 		spr.texture.load("assets/walking_basic.png");
// 		spr.frame = { 0.f, 0.f, 17.f, 26.f };
// 		spr.tex_coords = { 0.f, 0.f, 1 / 12.f, 1.f };
// 		spr.offset_center = (vec2i)spr.frame.size() / 2;//{ 8.f, 10.f };

// 		pos.x = 8.f;
// 		pos.y = 19.f;

// 		old_pos = pos;
// 		new_pos = pos;
// 	}

// 	void character::input() {
// 		mov_dir.x = input::is_key_down(SDL_SCANCODE_RIGHT) - input::is_key_down(SDL_SCANCODE_LEFT);
// 		mov_dir.y = input::is_key_down(SDL_SCANCODE_DOWN) - input::is_key_down(SDL_SCANCODE_UP);
// 		if (!is_moving) {
// 			is_moving = mov_dir.x || mov_dir.y;
// 			if (is_moving) {
// 				mov_dir.x = (mov_dir.y) ? 0 : mov_dir.x;
// 				old_pos = pos;
// 				new_pos = pos + (mov_dir * 16);
// 			}
// 		}
// 	}

// 	void character::update(f32 dt) {
// 		if (is_moving) {
// 			t += dt * speed;
// 			if (t >= 1.f) {
// 				t = 0.f;
// 				is_moving = mov_dir.x || mov_dir.y;
// 				if (is_moving) {
// 					mov_dir.x = (mov_dir.y) ? 0 : mov_dir.x;
// 					pos = new_pos;
// 					old_pos = new_pos;
// 					new_pos = new_pos + (mov_dir * 16);
// 				}
// 				else {
// 					pos = new_pos;
// 				}
// 			}
// 			else {
// 				pos.x = lerp(old_pos.x, new_pos.x, t);
// 				pos.y = lerp(old_pos.y, new_pos.y, t);
// 			}
// 		}
// 	}

// 	void character::render(gfx::batcher &b) {
// 		b.push_matrix(mat3x2::from_position(pos));
// 			b.set_texture(spr.texture);
// 			b.rect(spr.frame - spr.offset_center, spr.tex_coords);
// 		b.pop_matrix();
// 	}
// } // namespace game
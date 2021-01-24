#include "factory.hpp"

#include "types.hpp"
#include <pocket/math/vec.hpp>

#include <pocket/components/animator.hpp>
#include <pocket/components/movement.hpp>
#include <pocket/components/player_controller.hpp>
#include <pocket/components/sprite.hpp>
#include <pocket/components/tilemap.hpp>
#include <pocket/components/tilemap_animator.hpp>
#include <pocket/components/map_manager.hpp>

#include <pocket/containers/containers.hpp>

#include <pocket/json/json.hpp>

namespace pk {
	world factory::w = world();

	entity *factory::new_tilemap(const char *fname) {
		auto e = w.new_entity();
		auto m = e->add<map_manager>();
		m->load(fname);
		//auto tm_anim = e->add<tilemap_animator>();
		//auto tm = e->add<tilemap>();
		//tm->load(fname);


		return e;
	}

	entity *factory::new_player(const char *fname) {
		auto e = w.new_entity();

		json::Parser p;
		auto file = p.parse(json::fromFile(fname));

		vec2i cell_size{
			(i32)file["size"]["x"].as_number(),
			(i32)file["size"]["y"].as_number()
		};

		auto spr = e->add<sprite>();
		spr->texture.load(file["texture"].as_string().c_str());
		spr->frame = { 0.f, 0.f, (f32) cell_size.x, (f32) cell_size.y };
		auto anim = e->add<animator>();
		//anim->texture.load(file["texture"].as_string().c_str());
		
		auto &animations = file["animations"].as_array();
		
		for (auto &a : animations) {
			vector<pair<u32,f32>> data;
			auto &frames = a["frames"].as_array();
			for (auto &f : frames) {
				auto &current = f.as_array();
				data.emplace_back(
					(u32)current[0].as_number(),
					(f32)current[1].as_number()
				);
			}

			anim->add_animation(
				a["name"].as_string(),
				data,
				cell_size,
				a["repeat"].as_bool()
			);
		}

		printf("initial state: %s\n", file["initial-state"].as_string().c_str());
		anim->play(file["initial-state"].as_string());

		e->add<movement>();
		e->add<player_controller>();
		return e;
	}

	entity *factory::new_gameobject(const vec2f &position) {
		auto e = w.new_entity();

		auto spr = e->add<sprite>();
		e->add<movement>();

		spr->texture.load("data/sprites/red.png");
		f32 tw = spr->texture.size.x;
		f32 th = spr->texture.size.y;
		//spr->frame.w = 16.f;
		//spr->frame.h = 24.f;
		spr->position = position;
		spr->frame = {0.f, 0.f, 16.f, 24.f};
		spr->tex_coords = { 0.f, 0.f, 16.f / tw, 24.f / th };
		spr->offset.y = 8.f;
		//spr->offset_center = (vec2i)spr->frame.size() / 2;
		//spr->frame.x = position.x - spr->offset_center.x;
		//spr->frame.y = position.y - spr->offset_center.y;

		return e;
	}

} // namespace pk
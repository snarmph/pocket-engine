#pragma once
#include "tileset_data.hpp"
#include <pocket/json/json.hpp>
#include <type_traits>

namespace pocket {
	inline void json_to_tilemap(json::Value &src, tilemap *dest);
	inline void tilemap_to_json(tilemap *src, json::Value &dest);

	namespace {		
		/*********
		*  READ  *
		**********/

		template<typename T>
		inline void read_value(T &v, json::Value &j) {
			v = j.cast<T>();
		}

		template<typename T>
		inline void read_value(vector<T> &vec, json::Value &v) {
			auto &arr = v.as_array();
			for (auto &val : arr) {
				vec.emplace_back();
				read_value(vec.back(), val);
			}
		}

		template<>
		inline void read_value(string &str, json::Value &j) {
			str = j.as_string();
		}
		
		template<>
		inline void read_value(animation_data &data, json::Value &j) {
			read_value(data.index, j["index"]);
			read_value(data.duration, j["duration"]);
		};

		template<>
		inline void read_value(animation_index &data, json::Value &j) {
			read_value(data.layer, j["layer"]);
			read_value(data.indices, j["indices"]);
		};

		template<>
		inline void read_value(animation_t &data, json::Value &j) {
			read_value(data.index_data, j["index_data"]);
			read_value(data.animation, j["animation"]);
		};

		template<>
		inline void read_value(tileset_t &data, json::Value &j) {
			read_value(data.filename, j["filename"]);
			read_value(data.tilesize, j["tilesize"]);
		};

		
		/**********
		*  WRITE  *
		***********/
		template<typename T>
		inline void write_value(T &v, json::Value &j) {
			j = v;
		}

		template<typename T>
		inline void write_value(vector<T> &vec, json::Value &j) {
			j = json::Array();
			auto &arr = j.as_array();
			for (size_t i = 0; i < vec.size(); i++) {
				arr.emplace_back();
				write_value(vec[i], arr.back());
			}
		}

		template<>
		inline void write_value(string &str, json::Value &j) {
			j = str.stdstr();
		}
		
		template<>
		inline void write_value(animation_data &data, json::Value &j) {
			j = json::Object();
		write_value(data.index, j["index"]);
		write_value(data.duration, j["duration"]);
		};

		template<>
		inline void write_value(animation_index &data, json::Value &j) {
			j = json::Object();
		write_value(data.layer, j["layer"]);
		write_value(data.indices, j["indices"]);
		};

		template<>
		inline void write_value(animation_t &data, json::Value &j) {
			j = json::Object();
		write_value(data.index_data, j["index_data"]);
		write_value(data.animation, j["animation"]);
		};

		template<>
		inline void write_value(tileset_t &data, json::Value &j) {
			j = json::Object();
		write_value(data.filename, j["filename"]);
		write_value(data.tilesize, j["tilesize"]);
		};

	} // namespace

	inline void json_to_tilemap(json::Value &src, tilemap *dest) {
			read_value(dest->animations, src["animations"]);
			read_value(dest->layers, src["layers"]);
			read_value(dest->tileset, src["tileset"]);
			read_value(dest->width, src["width"]);
			read_value(dest->height, src["height"]);
	}

	inline void tilemap_to_json(tilemap *src, json::Value &dest) {
		dest = json::Object();
		write_value(src->animations, dest["animations"]);
		write_value(src->layers, dest["layers"]);
		write_value(src->tileset, dest["tileset"]);
		write_value(src->width, dest["width"]);
		write_value(src->height, dest["height"]);
	}
} // namespace pocket
#include "tileset_data.hpp"
#include <fstream>

namespace pocket {
	/*********
	*  READ  *
	**********/

	template<typename T>
	void read_from_file(T &data, std::ifstream &f) {
		f.read((char *)&data, sizeof(T));
	}

	template<typename T>
	void read_from_file(vector<T> &vec, std::ifstream &f) {
		size_t len;
		f.read((char *)&len, sizeof(len));
		vec.resize(len);
		vec._size = len;
		for (size_t i = 0; i < len; i++)
			read_from_file(vec[i], f);
	}

	template<>
	void read_from_file(string &str, std::ifstream &f) {
		size_t len;
		f.read((char *)&len, sizeof(len));
		str.reserve(len);
		str.sz = len;
		f.read(str.buf, len);
	}

	template<>
	void read_from_file(animation_data &data, std::ifstream &f) {
		read_from_file(data.index, f);
		read_from_file(data.duration, f);
	};

	template<>
	void read_from_file(animation_index &data, std::ifstream &f) {
		read_from_file(data.layer, f);
		read_from_file(data.indices, f);
	};

	template<>
	void read_from_file(animation_t &data, std::ifstream &f) {
		read_from_file(data.index_data, f);
		read_from_file(data.animation, f);
	};

	template<>
	void read_from_file(tileset_t &data, std::ifstream &f) {
		read_from_file(data.filename, f);
		read_from_file(data.tilesize, f);
	};

	template<>
	void read_from_file(tilemap &data, std::ifstream &f) {
		read_from_file(data.animations, f);
		read_from_file(data.layers, f);
		read_from_file(data.tileset, f);
		read_from_file(data.width, f);
		read_from_file(data.height, f);
	};

	/**********
	*  WRITE  *
	***********/

	template<typename T>
	void write_to_file(T &data, std::ofstream &f) {
		f.write((char *)&data, sizeof(T));
	}

	template<typename T>
	void write_to_file(vector<T> &vec, std::ofstream &f) {
		size_t len = vec.size();
		f.write((char *)&len, sizeof(len));
		for (size_t i = 0; i < len; i++)
			write_to_file(vec[i], f);
	}

	template<>
	void write_to_file(string &str, std::ofstream &f) {
		size_t len = str.size();
		f.write((char *)&len, sizeof(len));
		f.write((char *)str.data(), len);
	}
	template<>
	void write_to_file(animation_data &data, std::ofstream &f) {
		write_to_file(data.index, f);
		write_to_file(data.duration, f);
	};

	template<>
	void write_to_file(animation_index &data, std::ofstream &f) {
		write_to_file(data.layer, f);
		write_to_file(data.indices, f);
	};

	template<>
	void write_to_file(animation_t &data, std::ofstream &f) {
		write_to_file(data.index_data, f);
		write_to_file(data.animation, f);
	};

	template<>
	void write_to_file(tileset_t &data, std::ofstream &f) {
		write_to_file(data.filename, f);
		write_to_file(data.tilesize, f);
	};

	template<>
	void write_to_file(tilemap &data, std::ofstream &f) {
		write_to_file(data.animations, f);
		write_to_file(data.layers, f);
		write_to_file(data.tileset, f);
		write_to_file(data.width, f);
		write_to_file(data.height, f);
	};

	//////////////////

	void read_tilemap(tilemap *data, const char *fname) {
		std::ifstream f(fname, std::ios::binary);

		read_from_file(data->animations, f);
		read_from_file(data->layers, f);
		read_from_file(data->tileset, f);
		read_from_file(data->width, f);
		read_from_file(data->height, f);
	}

	void write_tilemap(tilemap *data, const char *fname) {
		std::ofstream f(fname, std::ios::binary);

		write_to_file(data->animations, f);
		write_to_file(data->layers, f);
		write_to_file(data->tileset, f);
		write_to_file(data->width, f);
		write_to_file(data->height, f);
	}

} // namespace pocket
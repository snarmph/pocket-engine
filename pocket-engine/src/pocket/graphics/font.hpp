#pragma once

#include <stb/stb_truetype.h>

namespace pk {
	struct font {
		font() = default;
		~font();

		stbtt_fontinfo info;
		void load(const char *fname);
	};

	void load_font(const char *fname, font &dest);
} // namespace pk
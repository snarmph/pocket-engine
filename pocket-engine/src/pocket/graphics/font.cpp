#include "font.hpp"

#include <cstdio>
#include <cstdlib>

#include <pocket/core/types.hpp>

namespace pk {
	void load_font(const char *fname, font &dest) {
		FILE *fontfile = fopen(fname, "rb");
		if (!fontfile) {
			fprintf(stderr, "couldn't find %s\n", fname);
			exit(1);
		}
		
		fseek(fontfile, 0, SEEK_END);
		long size = ftell(fontfile);
		fseek(fontfile, 0, SEEK_SET);

		byte *buf = (byte*) malloc(size);
	
		fread(buf, size, 1, fontfile);
		fclose(fontfile);

		if (!stbtt_InitFont(&dest.info, buf, 0)) {
			fprintf(stderr, "failed to initialize font\n");
			exit(1);
		}
	}
} // namespace pk
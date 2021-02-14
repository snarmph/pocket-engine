#pragma once

#include <lua/lua.hpp>

namespace pk {
	struct script_manager {
		script_manager();
		void update();

		void dofile(const char *fname);
		void dostring(const char *script);

	private:
		lua_State *L;
	};
} // namespace pk
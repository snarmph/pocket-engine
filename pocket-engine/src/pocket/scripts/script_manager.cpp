#include "script_manager.hpp"

#include <cstdlib>

#include <pocket/core/types.hpp>
#include <pocket/core/time.hpp>

static void lua_stack_dump(lua_State *L);

namespace pk {
	script_manager::script_manager() {
		L = luaL_newstate();
		luaL_openlibs(L);

        dofile("data/scripts/main.lua");
    }

	void script_manager::update() {
        lua_getglobal(L, "main");
        lua_pushnumber(L, time::dt);
        int ret = lua_resume(L, 1);
        if (ret == 2) {
            lua_stack_dump(L);
            exit(1);
        }
    }

    void script_manager::dofile(const char *fname) {
        if (luaL_dofile(L, fname)) {
            printf("file error: %s\n", lua_tostring(L, -1));
            exit(1);
        }
    }
    void script_manager::dostring(const char *script) {
        if (luaL_dostring(L, script)) {
            printf("string error: %s\n", lua_tostring(L, -1));
            exit(1);
        }
    }
} // namespace pk

static void lua_stack_dump(lua_State *L) {
    int i;
    int top = lua_gettop(L);
    printf("--------------- STACK ---------------\n");
    for (i = top; i >= 1; i--) {
        int t = lua_type(L, i);
        printf("[%2d - %8s] : ", i, lua_typename(L, t));
        switch (t) {
        case LUA_TSTRING:
            printf("%s", lua_tostring(L, i));
            break;
        case LUA_TBOOLEAN:
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;
        case LUA_TNUMBER:
            printf("%g", lua_tonumber(L, i));
            break;
        case LUA_TNIL:
            printf("nil");
            break;
        case LUA_TNONE:
            printf("none");
            break;
        case LUA_TFUNCTION:
            printf("<function %p>", lua_topointer(L, i));
            break;
        case LUA_TTABLE:
            printf("<table %p>", lua_topointer(L, i));
            break;
        case LUA_TTHREAD:
            printf("<thread %p>", lua_topointer(L, i));
            break;
        case LUA_TUSERDATA:
            printf("<userdata %p>", lua_topointer(L, i));
            break;
        case LUA_TLIGHTUSERDATA:
            printf("<lightuserdata %p>", lua_topointer(L, i));
            break;
        default:
            printf("unknown %s", lua_typename(L, t));
            break;
        }
        printf("\n");
    }
    printf("-------------------------------------\n");
}

#define LUA_LIB

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
#include "lx_api.h"
#include "lx_math.h"
#include "lx_vector2.h"

InternString intern_string_x = { .a = 0, .b = 0 };
InternString intern_string_y = { .a = 0, .b = 0 };
InternString intern_string_z = { .a = 0, .b = 0 };

#include "lxlib_math.c"
#include "lxlib_table.c"
#include "lxlib_util.c"
#include "lxlib_vector2.c"


LUA_API void luaopen_lxt(lua_State* L)
{
    lx_intern_string(L, "x", &intern_string_x);
    lx_intern_string(L, "y", &intern_string_y);
    lx_intern_string(L, "z", &intern_string_z);

    lx_reg_lib_table(L);
    lx_reg_lib_util(L);
    lxlib_reg_math(L);
    lx_reg_lib_vector2(L);
}
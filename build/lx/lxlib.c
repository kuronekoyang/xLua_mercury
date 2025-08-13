
#define LUA_LIB

#include "lauxlib.h"
#include "lua.h"
#include "lx_api.h"
#include "lx_math.h"

InternString intern_string_x = {.a = 0, .b = 0};
InternString intern_string_y = {.a = 0, .b = 0};
InternString intern_string_z = {.a = 0, .b = 0};
InternString *intern_string_1 = &intern_string_x;
InternString *intern_string_2 = &intern_string_y;
InternString *intern_string_3 = &intern_string_z;

#include "lxlib_math.c"
#include "lxlib_table.c"
#include "lxlib_util.c"
#include "lxlib_vector2.c"
#include "lxlib_vector3.c"

LUA_API void luaopen_lxt(lua_State *L)
{
    lx_intern_string(L, "x", &intern_string_x);
    lx_intern_string(L, "y", &intern_string_y);
    lx_intern_string(L, "z", &intern_string_z);

    lxlib_reg_table(L);
    lxlib_reg_util(L);
    lxlib_reg_math(L);
    lxlib_reg_vec2(L);
    lxlib_reg_vec3(L);
}
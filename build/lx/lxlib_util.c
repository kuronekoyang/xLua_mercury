#include "lauxlib.h"
#include "lua.h"
#include "lx_api.h"

static int util_is_empty_func(lua_State *L)
{
    const int r = lx_is_empty_func(L, 1);
    lua_pushboolean(L, r);
    return 1;
}

static int util_raw_integer(lua_State *L)
{
    const lua_Integer r = lx_raw_integer(L, 1);
    lua_pushinteger(L, r);
    return 1;
}

static int util_is_callable(lua_State *L)
{
    const int r = lx_is_callable(L, 1);
    lua_pushboolean(L, r);
    return 1;
}

static const luaL_Reg lxlib_util[] = {{"is_empty_func", util_is_empty_func},
                                      {"raw_integer", util_raw_integer},
                                      {"is_callable", util_is_callable},
                                      {NULL, NULL}};

static void lxlib_reg_util(lua_State *L)
{
    luaL_newlib(L, lxlib_util);
    lua_setglobal(L, "lx_util");
}
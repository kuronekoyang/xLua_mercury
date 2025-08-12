#include "lauxlib.h"
#include "lua.h"
#include "lx_math.h"

static int math_clamp(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TNUMBER);
    luaL_checktype(L, 2, LUA_TNUMBER);
    luaL_checktype(L, 3, LUA_TNUMBER);

    if (lua_isinteger(L, 1) && lua_isinteger(L, 2) && lua_isinteger(L, 3))
    {
        const lua_Integer value = lua_tointeger(L, 1);
        const lua_Integer minimum = lua_tointeger(L, 2);
        const lua_Integer maximum = lua_tointeger(L, 3);
        lua_pushinteger(L, lx_math_clamp(value, minimum, maximum));
    }
    else
    {
        const lua_Number value = lua_tonumber(L, 1);
        const lua_Number minimum = lua_tonumber(L, 2);
        const lua_Number maximum = lua_tonumber(L, 3);
        lua_pushnumber(L, lx_math_clamp(value, minimum, maximum));
    }
    return 1;
}

static int math_clamp01(lua_State *L)
{
    const lua_Number value = luaL_checknumber(L, 1);
    lua_pushnumber(L, lx_math_clamp01(value));
    return 1;
}

static int math_lerp_unclamped(lua_State *L)
{
    const lua_Number value1 = luaL_checknumber(L, 1);
    const lua_Number value2 = luaL_checknumber(L, 2);
    const lua_Number t = luaL_checknumber(L, 3);
    lua_pushnumber(L, lx_math_lerp_unclamped(value1, value2, t));
    return 1;
}

static int math_lerp(lua_State *L)
{
    const lua_Number value1 = luaL_checknumber(L, 1);
    const lua_Number value2 = luaL_checknumber(L, 2);
    const lua_Number t = luaL_checknumber(L, 3);
    lua_pushnumber(L, lx_math_lerp(value1, value2, t));
    return 1;
}

static int math_next_pow2(lua_State *L)
{
    const lua_Integer value = luaL_checkinteger(L, 1);
    lua_pushinteger(L, lx_math_next_pow2(value));
    return 1;
}

static int math_integer(lua_State *L)
{
    const lua_Integer n = lua_tointeger(L, 1);
    lua_pushinteger(L, n);
    return 1;
}

static int math_round(lua_State *L)
{
    if (lua_isinteger(L, 1))
    {
        lua_pushvalue(L, 1);
        return 1;
    }
    const lua_Number f = luaL_checknumber(L, 1);
    const lua_Number n = (lua_Number)lx_math_round(f);
    lua_pushnumber(L, n);
    return 1;
}

static int math_sign(lua_State *L)
{
    const lua_Number a = luaL_checknumber(L, 1);
    lua_pushinteger(L, lx_math_sign(a));
    return 1;
}

static int math_approx(lua_State *L)
{
    const lua_Number a = luaL_checknumber(L, 1);
    const lua_Number b = luaL_checknumber(L, 2);
    lua_Number epsilon;
    if (lua_isnumber(L, 3))
        epsilon = lua_tonumber(L, 3);
    else
        epsilon = lx_epsilon;
    lua_pushboolean(L, lx_math_abs(a - b) <= epsilon);
    return 1;
}

static int math_distance_2d(lua_State *L)
{
    const lua_Number x1 = luaL_checknumber(L, 1);
    const lua_Number y1 = luaL_checknumber(L, 2);
    const lua_Number x2 = luaL_checknumber(L, 3);
    const lua_Number y2 = luaL_checknumber(L, 4);

    const lua_Number dist = lx_math_sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    lua_pushnumber(L, dist);
    return 1;
}

static int math_sqr_distance_2d(lua_State *L)
{
    const lua_Number x1 = luaL_checknumber(L, 1);
    const lua_Number y1 = luaL_checknumber(L, 2);
    const lua_Number x2 = luaL_checknumber(L, 3);
    const lua_Number y2 = luaL_checknumber(L, 4);

    const lua_Number dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    lua_pushnumber(L, dist);
    return 1;
}

static int math_distance_3d(lua_State *L)
{
    const lua_Number x1 = luaL_checknumber(L, 1);
    const lua_Number y1 = luaL_checknumber(L, 2);
    const lua_Number z1 = luaL_checknumber(L, 3);
    const lua_Number x2 = luaL_checknumber(L, 4);
    const lua_Number y2 = luaL_checknumber(L, 5);
    const lua_Number z2 = luaL_checknumber(L, 6);

    const lua_Number dist = lx_math_sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
    lua_pushnumber(L, dist);
    return 1;
}

static int math_sqr_distance_3d(lua_State *L)
{
    const lua_Number x1 = luaL_checknumber(L, 1);
    const lua_Number y1 = luaL_checknumber(L, 2);
    const lua_Number z1 = luaL_checknumber(L, 3);
    const lua_Number x2 = luaL_checknumber(L, 4);
    const lua_Number y2 = luaL_checknumber(L, 5);
    const lua_Number z2 = luaL_checknumber(L, 6);

    const lua_Number dist = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2);
    lua_pushnumber(L, dist);
    return 1;
}

static const luaL_Reg lxlib_math[] = {{"clamp", math_clamp},
                                      {"clamp01", math_clamp01},
                                      {"lerp_unclamped", math_lerp_unclamped},
                                      {"lerp", math_lerp},
                                      {"next_pow2", math_next_pow2},
                                      {"integer", math_integer},
                                      {"round", math_round},
                                      {"sign", math_sign},
                                      {"approx", math_approx},
                                      {"distance_2d", math_distance_2d},
                                      {"sqr_distance_2d", math_sqr_distance_2d},
                                      {"distance_3d", math_distance_3d},
                                      {"sqr_distance_3d", math_sqr_distance_3d},

                                      {NULL, NULL}};

static void lxlib_reg_math(lua_State *L)
{
    luaL_newlib(L, lxlib_math);
    lua_setglobal(L, "lx_math");
}
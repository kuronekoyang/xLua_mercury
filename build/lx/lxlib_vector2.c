#include "lauxlib.h"
#include "lua.h"
#include "lx_api.h"
#include "lx_vector2.h"
#include "lxlib_vector.h"

extern InternString intern_string_x;
extern InternString intern_string_y;
extern InternString intern_string_z;

static Vector2 lx_checkvec2(lua_State *L, int idx)
{
    idx = lua_absindex(L, idx);
    Vector2 v;
    const int type = lua_type(L, idx);
    switch (type)
    {
    case LUA_TTABLE:
        lx_push_intern_string(L, &intern_string_x);
        lua_rawget(L, idx);
        v.x = luaL_checknumber(L, -1);
        lua_pop(L, 1);
        lx_push_intern_string(L, &intern_string_y);
        lua_rawget(L, idx);
        v.y = luaL_checknumber(L, -1);
        lua_pop(L, 1);
        break;
    case LUA_TUSERDATA:
        lx_push_intern_string(L, &intern_string_x);
        lua_gettable(L, idx);
        v.x = luaL_checknumber(L, -1);
        lua_pop(L, 1);
        lx_push_intern_string(L, &intern_string_y);
        lua_gettable(L, idx);
        v.y = luaL_checknumber(L, -1);
        lua_pop(L, 1);
        break;
    default:
        luaL_typeerror(L, idx, "table or userdata");
        v = lx_vec2_zero;
        break;
    }
    return v;
}

static void lx_setvec2(lua_State *L, int idx, Vector2 v)
{
    idx = lua_absindex(L, idx);
    const int type = lua_type(L, idx);
    switch (type)
    {
    case LUA_TTABLE:
        lx_push_intern_string(L, &intern_string_x);
        lua_pushnumber(L, v.x);
        lua_rawset(L, idx);
        lx_push_intern_string(L, &intern_string_y);
        lua_pushnumber(L, v.y);
        lua_rawset(L, idx);
        break;
    case LUA_TUSERDATA:
        lx_push_intern_string(L, &intern_string_x);
        lua_pushnumber(L, v.x);
        lua_settable(L, idx);
        lx_push_intern_string(L, &intern_string_y);
        lua_pushnumber(L, v.y);
        lua_settable(L, idx);
        break;
    default:
        luaL_typeerror(L, idx, "table or userdata");
        break;
    }
}

static void lx_pushvec2(lua_State *L, Vector2 v)
{
    lua_newtable(L);
    lx_push_intern_string(L, &intern_string_x);
    lua_pushnumber(L, v.x);
    lua_rawset(L, -3);
    lx_push_intern_string(L, &intern_string_y);
    lua_pushnumber(L, v.y);
    lua_rawset(L, -3);
}

#define lx_setvec2_smartidx(L, idx, v)                                                                                    \
    {                                                                                                                  \
        int __idx = lx_is_table_or_userdata(L, idx) ? idx : 1;                                                         \
        lx_setvec2(L, __idx, v);                                                                                       \
    }
#define lx_pushvec2_dummyidx(L, idx, v) lx_pushvec2(L, v)
#define lua_pushnumber_dummyidx(L, idx, v) lua_pushnumber(L, v)

static int vec2_clear(lua_State *L)
{
    Vector2 v;
    v.x = 0;
    v.y = 0;
    lx_setvec2(L, 1, v);
    return 0;
}

static int vec2_set(lua_State *L)
{
    Vector2 v;
    v.x = luaL_checknumber(L, 2);
    v.y = luaL_checknumber(L, 3);
    lx_setvec2(L, 1, v);
    return 0;
}

#define lxlib_vec2_op_a_xy_impl(name, op, func_stack, ret_value)                                                       \
    static int vec2_##name(lua_State *L)                                                                               \
    {                                                                                                                  \
        Vector2 a = lx_checkvec2(L, 1);                                                                                \
        a.x op## = luaL_checknumber(L, 2);                                                                             \
        a.y op## = luaL_checknumber(L, 3);                                                                             \
        func_stack(L, 4, a);                                                                                           \
        return ret_value;                                                                                              \
    }
#define lxlib_vec2_op_a_xy(name, op)                                                                                   \
    lxlib_vec2_op_a_xy_impl(name, op, lx_setvec2_smartidx, 0);                                                       \
    lxlib_vec2_op_a_xy_impl(name##_alloc, op, lx_pushvec2_dummyidx, 1);

lxlib_vec_op_a(2, normalize);

lxlib_vec_op_a_b(2, add, +);
lxlib_vec_op_a_b(2, sub, -);
lxlib_vec_op_a_b(2, mul, *);
lxlib_vec_op_a_b(2, div, /);

lxlib_vec2_op_a_xy(add_xy, +);
lxlib_vec2_op_a_xy(sub_xy, -);
lxlib_vec2_op_a_xy(mul_xy, *);
lxlib_vec2_op_a_xy(div_xy, /);

lxlib_vec_func_a_b_n_rv(2, lerp);
lxlib_vec_func_a_b_n_rv(2, lerp_unclamped);

lxlib_vec_func_a_rn(magnitude, 2);
lxlib_vec_func_a_rn(sqr_magnitude, 2);

lxlib_vec_func_a_b_rn(2, dot);
lxlib_vec_func_a_b_rn(2, cross);
lxlib_vec_func_a_b_rn(2, distance);
lxlib_vec_func_a_b_rn(2, angle_rad);
lxlib_vec_func_a_b_rn(2, angle_rad_ccw);

lxlib_vec_func_a_b_rv(2, reflect);
lxlib_vec_func_a_b_rv(2, project);
lxlib_vec_func_a_b_rv(2, project_on_plane);

#define lxlib_pair(name) {#name, vec2_##name}
#define lxlib_pair_full(name) lxlib_pair(name), lxlib_pair(name##_alloc)

static const luaL_Reg lxlib_vec2[] = {lxlib_vec_reg_pair(2, clear),
                                      lxlib_vec_reg_pair(2, set),
                                      lxlib_vec_reg_pair(2, magnitude),
                                      lxlib_vec_reg_pair(2, sqr_magnitude),
                                      lxlib_vec_reg_pair(2, dot),
                                      lxlib_vec_reg_pair(2, cross),
                                      lxlib_vec_reg_pair(2, distance),
                                      lxlib_vec_reg_pair(2, angle_rad),
                                      lxlib_vec_reg_pair(2, angle_rad_ccw),

                                      lxlib_vec_reg_pair_full(2, add),
                                      lxlib_vec_reg_pair_full(2, sub),
                                      lxlib_vec_reg_pair_full(2, mul),
                                      lxlib_vec_reg_pair_full(2, div),
                                      lxlib_vec_reg_pair_full(2, add_xy),
                                      lxlib_vec_reg_pair_full(2, sub_xy),
                                      lxlib_vec_reg_pair_full(2, mul_xy),
                                      lxlib_vec_reg_pair_full(2, div_xy),
                                      lxlib_vec_reg_pair_full(2, normalize),
                                      lxlib_vec_reg_pair_full(2, lerp),
                                      lxlib_vec_reg_pair_full(2, lerp_unclamped),

                                      {NULL, NULL}};

static void lxlib_reg_vec2(lua_State *L)
{
    luaL_newlib(L, lxlib_vec2);
    lua_setglobal(L, "lx_vec2");
}
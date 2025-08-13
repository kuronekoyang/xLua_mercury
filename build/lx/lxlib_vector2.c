#include "lauxlib.h"
#include "lua.h"
#include "lx_api.h"
#include "lx_vector2.h"
#include "lxlib_vector.h"

extern InternString *intern_string_1;
extern InternString *intern_string_2;
extern InternString *intern_string_3;

lx_vec_check(2);
lx_vec_update(2);
#define lx_return_updatevec2(L, idx, v) lx_return_updatevec(2, L, idx, v)
#define lx_return_updatevec2_smartidx(L, idx, v) lx_return_updatevec_smartidx(2, L, idx, v)

lx_vec_push(2);
#define lx_return_pushvec2_dummyidx(L, idx, v) lx_return_pushvec_dummyidx(2, L, idx, v)

lxlib_vec_clear(2);
lxlib_vec_set(2);
lxlib_vec_copy(2);

lxlib_vec_op_a(2, normalize);

lxlib_vec_op_a_b(2, add, +);
lxlib_vec_op_a_b(2, sub, -);
lxlib_vec_op_a_b(2, mul, *);
lxlib_vec_op_a_b(2, div, /);

lxlib_vec_op_a_xyzw(2, add_xy, +);
lxlib_vec_op_a_xyzw(2, sub_xy, -);
lxlib_vec_op_a_xyzw(2, mul_xy, *);
lxlib_vec_op_a_xyzw(2, div_xy, /);

lxlib_vec_func_a_b_n_rv(2, lerp);
lxlib_vec_func_a_b_n_rv(2, lerp_unclamped);

lxlib_vec_func_a_rn(2, magnitude);
lxlib_vec_func_a_rn(2, sqr_magnitude);

lxlib_vec_func_a_b_rn(2, dot);
lxlib_vec_func_a_b_rn(2, cross);
lxlib_vec_func_a_b_rn(2, distance);
lxlib_vec_func_a_b_rn(2, angle_rad);
lxlib_vec_func_a_b_rn(2, angle_deg);
lxlib_vec_func_a_b_rn(2, signed_angle_rad);
lxlib_vec_func_a_b_rn(2, signed_angle_deg);

lxlib_vec_func_a_n_rv(2, rotate_rad);
lxlib_vec_func_a_n_rv(2, rotate_deg);

lxlib_vec_func_a_b_rv(2, direction);
lxlib_vec_func_a_b_rv(2, reflect);
lxlib_vec_func_a_b_rv(2, project);
lxlib_vec_func_a_b_rv(2, project_on_plane);

static const luaL_Reg lxlib_vec2[] = {lxlib_vec_reg_pair(2, clear),
                                      lxlib_vec_reg_pair(2, set),
                                      lxlib_vec_reg_pair(2, magnitude),
                                      lxlib_vec_reg_pair(2, sqr_magnitude),
                                      lxlib_vec_reg_pair(2, dot),
                                      lxlib_vec_reg_pair(2, cross),
                                      lxlib_vec_reg_pair(2, distance),
                                      lxlib_vec_reg_pair(2, angle_rad),
                                      lxlib_vec_reg_pair(2, angle_deg),
                                      lxlib_vec_reg_pair(2, signed_angle_rad),
                                      lxlib_vec_reg_pair(2, signed_angle_deg),

                                      lxlib_vec_reg_pair_full(2, copy),
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
                                      lxlib_vec_reg_pair_full(2, direction),
                                      lxlib_vec_reg_pair_full(2, reflect),
                                      lxlib_vec_reg_pair_full(2, project),
                                      lxlib_vec_reg_pair_full(2, project_on_plane),
                                      lxlib_vec_reg_pair_full(2, rotate_rad),
                                      lxlib_vec_reg_pair_full(2, rotate_deg),

                                      {NULL, NULL}};

static void lxlib_reg_vec2(lua_State *L)
{
    luaL_newlib(L, lxlib_vec2);
    lua_setglobal(L, "lx_vec2");
}
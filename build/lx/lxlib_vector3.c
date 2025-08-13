#include "lauxlib.h"
#include "lua.h"
#include "lx_api.h"
#include "lx_vector3.h"
#include "lxlib_vector.h"

extern InternString *intern_string_1;
extern InternString *intern_string_2;
extern InternString *intern_string_3;

lx_vec_check(3);
lx_vec_update(3);
#define lx_return_updatevec3(L, idx, v) lx_return_updatevec(3, L, idx, v)
#define lx_return_updatevec3_smartidx(L, idx, v) lx_return_updatevec_smartidx(3, L, idx, v)

lx_vec_push(3);
#define lx_return_pushvec3_dummyidx(L, idx, v) lx_return_pushvec_dummyidx(3, L, idx, v)

lxlib_vec_clear(3);
lxlib_vec_set(3);
lxlib_vec_copy(3);

lxlib_vec_op_a(3, normalize);

lxlib_vec_op_a_b(3, add, +);
lxlib_vec_op_a_b(3, sub, -);
lxlib_vec_op_a_b(3, mul, *);
lxlib_vec_op_a_b(3, div, /);

lxlib_vec_op_a_xyzw(3, add_xyz, +);
lxlib_vec_op_a_xyzw(3, sub_xyz, -);
lxlib_vec_op_a_xyzw(3, mul_xyz, *);
lxlib_vec_op_a_xyzw(3, div_xyz, /);

lxlib_vec_func_a_b_n_rv(3, lerp);
lxlib_vec_func_a_b_n_rv(3, lerp_unclamped);
lxlib_vec_func_a_b_n_rv(3, move_towards);

lxlib_vec_func_a_b_n1_n2_rv(3, rotate_towards_rad);

lxlib_vec_func_a_rn(3, magnitude);
lxlib_vec_func_a_rn(3, sqr_magnitude);

lxlib_vec_func_a_b_rn(3, dot);
lxlib_vec_func_a_b_rn(3, distance);
lxlib_vec_func_a_b_rn(3, angle_rad);
lxlib_vec_func_a_b_rn(3, angle_deg);
lxlib_vec_func_a_b_c_rn(3, signed_angle_rad);
lxlib_vec_func_a_b_c_rn(3, signed_angle_deg);

lxlib_vec_func_a_n_rv(3, rotate_around_axis_y_rad);
lxlib_vec_func_a_n_rv(3, rotate_around_axis_y_deg);

lxlib_vec_func_a_b_rv(3, direction);
lxlib_vec_func_a_b_rv(3, cross);
lxlib_vec_func_a_b_rv(3, reflect);
lxlib_vec_func_a_b_rv(3, project);
lxlib_vec_func_a_b_rv(3, project_on_plane);

static const luaL_Reg lxlib_vec3[] = {lxlib_vec_reg_pair(3, clear),
                                      lxlib_vec_reg_pair(3, set),
                                      lxlib_vec_reg_pair(3, magnitude),
                                      lxlib_vec_reg_pair(3, sqr_magnitude),
                                      lxlib_vec_reg_pair(3, dot),
                                      lxlib_vec_reg_pair(3, distance),
                                      lxlib_vec_reg_pair(3, angle_rad),
                                      lxlib_vec_reg_pair(3, angle_deg),
                                      lxlib_vec_reg_pair(3, signed_angle_rad),
                                      lxlib_vec_reg_pair(3, signed_angle_deg),

                                      lxlib_vec_reg_pair_full(3, copy),
                                      lxlib_vec_reg_pair_full(3, add),
                                      lxlib_vec_reg_pair_full(3, sub),
                                      lxlib_vec_reg_pair_full(3, mul),
                                      lxlib_vec_reg_pair_full(3, div),
                                      lxlib_vec_reg_pair_full(3, add_xyz),
                                      lxlib_vec_reg_pair_full(3, sub_xyz),
                                      lxlib_vec_reg_pair_full(3, mul_xyz),
                                      lxlib_vec_reg_pair_full(3, div_xyz),
                                      lxlib_vec_reg_pair_full(3, normalize),
                                      lxlib_vec_reg_pair_full(3, lerp),
                                      lxlib_vec_reg_pair_full(3, lerp_unclamped),
                                      lxlib_vec_reg_pair_full(3, move_towards),
                                      lxlib_vec_reg_pair_full(3, rotate_towards_rad),
                                      lxlib_vec_reg_pair_full(3, direction),
                                      lxlib_vec_reg_pair_full(3, cross),
                                      lxlib_vec_reg_pair_full(3, reflect),
                                      lxlib_vec_reg_pair_full(3, project),
                                      lxlib_vec_reg_pair_full(3, project_on_plane),
                                      lxlib_vec_reg_pair_full(3, rotate_around_axis_y_rad),
                                      lxlib_vec_reg_pair_full(3, rotate_around_axis_y_deg),

                                      {NULL, NULL}};

static void lxlib_reg_vec3(lua_State *L)
{
    luaL_newlib(L, lxlib_vec3);
    lua_setglobal(L, "lx_vec3");
}
#ifndef __LXLIB_VECTOR_H__
#define __LXLIB_VECTOR_H__

#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
#include "lx_api.h"
#include "lx_vector.h"
#include "lxlib.h"

#define lx_vec_check_impl(dim, func)                                                                                   \
    lx_push_intern_string(L, intern_string_##dim);                                                                     \
    func(L, idx);                                                                                                      \
    v.lx_vec_dim_##dim = luaL_checknumber(L, -1);                                                                      \
    lua_pop(L, 1)
#define lx_vec_check(dim)                                                                                              \
    static Vector##dim lx_checkvec##dim(lua_State *L, int idx)                                                         \
    {                                                                                                                  \
        idx = lua_absindex(L, idx);                                                                                    \
        Vector##dim v;                                                                                                 \
        const int type = lua_type(L, idx);                                                                             \
        switch (type)                                                                                                  \
        {                                                                                                              \
        case LUA_TTABLE:                                                                                               \
            lx_vec_exp_##dim(lx_vec_check_impl, ;, lua_rawget);                                                        \
            break;                                                                                                     \
        case LUA_TUSERDATA:                                                                                            \
            lx_vec_exp_##dim(lx_vec_check_impl, ;, lua_gettable);                                                      \
            break;                                                                                                     \
        default:                                                                                                       \
            luaL_typeerror(L, idx, "table or userdata");                                                               \
            lx_vec_clear(dim, &v);                                                                                     \
            break;                                                                                                     \
        }                                                                                                              \
        return v;                                                                                                      \
    }

#define lx_vec_update_impl(dim, func)                                                                                  \
    lx_push_intern_string(L, intern_string_##dim);                                                                     \
    lua_pushnumber(L, v.lx_vec_dim_##dim);                                                                             \
    lua_rawset(L, idx)
#define lx_vec_update(dim)                                                                                             \
    static void lx_updatevec##dim(lua_State *L, int idx, Vector##dim v)                                                \
    {                                                                                                                  \
        idx = lua_absindex(L, idx);                                                                                    \
        const int type = lua_type(L, idx);                                                                             \
        switch (type)                                                                                                  \
        {                                                                                                              \
        case LUA_TTABLE:                                                                                               \
            lx_vec_exp_##dim(lx_vec_update_impl, ;, lua_rawset);                                                       \
            break;                                                                                                     \
        case LUA_TUSERDATA:                                                                                            \
            lx_vec_exp_##dim(lx_vec_update_impl, ;, lua_settable);                                                     \
            break;                                                                                                     \
        default:                                                                                                       \
            luaL_typeerror(L, idx, "table or userdata");                                                               \
            break;                                                                                                     \
        }                                                                                                              \
    }

#define lx_return_updatevec(dim, L, idx, v)                                                                            \
    lx_updatevec##dim(L, idx, v);                                                                                      \
    return 0
#define lx_return_updatevec_smartidx(dim, L, idx, v)                                                                   \
    {                                                                                                                  \
        int __idx = lx_is_table_or_userdata(L, idx) ? idx : 1;                                                         \
        lx_updatevec##dim(L, __idx, v);                                                                                \
    }                                                                                                                  \
    return 0

#define lx_vec_push_impl(dim, _)                                                                                       \
    lx_push_intern_string(L, intern_string_##dim);                                                                     \
    lua_pushnumber(L, v.lx_vec_dim_##dim);                                                                             \
    lua_rawset(L, -3)
#define lx_vec_push(dim)                                                                                               \
    static void lx_pushvec##dim(lua_State *L, Vector##dim v)                                                           \
    {                                                                                                                  \
        lua_newtable(L);                                                                                               \
        lx_vec_exp_##dim(lx_vec_push_impl, ;);                                                                         \
    }

#define lx_return_pushvec_dummyidx(dim, L, _, v)                                                                       \
    lx_pushvec##dim(L, v);                                                                                             \
    return 1
#define lx_return_pushnumber_dummyidx(L, idx, v)                                                                       \
    lua_pushnumber(L, v);                                                                                              \
    return 1

#define lxlib_vec_clear(dim)                                                                                           \
    static int vec##dim##_clear(lua_State *L)                                                                          \
    {                                                                                                                  \
        Vector##dim v;                                                                                                 \
        lx_vec_clear(dim, &v);                                                                                         \
        lx_updatevec##dim(L, 1, v);                                                                                    \
        return 0;                                                                                                      \
    }

#define lxlib_vec_set_impl(dim, func) v.lx_vec_dim_##dim = luaL_checknumber(L, (dim + 1))
#define lxlib_vec_set(dim)                                                                                             \
    static int vec##dim##_set(lua_State *L)                                                                            \
    {                                                                                                                  \
        Vector##dim v;                                                                                                 \
        lx_vec_exp_##dim(lxlib_vec_set_impl, ;);                                                                       \
        lx_updatevec##dim(L, 1, v);                                                                                    \
        return 0;                                                                                                      \
    }

#define lxlib_vec_copy_impl(dim, name, func_ret)                                                                       \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        Vector##dim a = lx_checkvec##dim(L, 1);                                                                        \
        func_ret(L, 2, a);                                                                                             \
    }
#define lxlib_vec_copy(dim)                                                                                            \
    lxlib_vec_copy_impl(dim, copy, lx_return_updatevec##dim);                                                          \
    lxlib_vec_copy_impl(dim, copy_alloc, lx_return_pushvec##dim##_dummyidx);

#define lxlib_vec_op_a_impl(dim, name, func_core, func_ret)                                                            \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        Vector##dim a = lx_checkvec##dim(L, 1);                                                                        \
        func_core##_r(&a, &a);                                                                                         \
        func_ret(L, 2, a);                                                                                             \
    }
#define lxlib_vec_op_a(dim, name)                                                                                      \
    lxlib_vec_op_a_impl(dim, name, lx_vec##dim##_##name, lx_return_updatevec##dim##_smartidx);                         \
    lxlib_vec_op_a_impl(dim, name##_alloc, lx_vec##dim##_##name, lx_return_pushvec##dim##_dummyidx);

#define lxlib_vec_op_a_b_impl(dim, name, op, func_ret)                                                                 \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        Vector##dim a = lx_checkvec##dim(L, 1);                                                                        \
        if (lua_type(L, 2) == LUA_TNUMBER)                                                                             \
        {                                                                                                              \
            const double b = lua_tonumber(L, 2);                                                                       \
            lx_vec_op_a_n_r(dim, &a, b, op, &a);                                                                       \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            const Vector##dim b = lx_checkvec##dim(L, 2);                                                              \
            lx_vec_op_a_b_r(dim, &a, &b, op, &a);                                                                      \
        }                                                                                                              \
        func_ret(L, 3, a);                                                                                             \
    }
#define lxlib_vec_op_a_b(dim, name, op)                                                                                \
    lxlib_vec_op_a_b_impl(dim, name, op, lx_return_updatevec##dim##_smartidx);                                         \
    lxlib_vec_op_a_b_impl(dim, name##_alloc, op, lx_return_pushvec##dim##_dummyidx);

#define lxlib_vec_op_a_xyzw_impl_impl(dim, a, op) a.lx_vec_dim_##dim op## = luaL_checknumber(L, (dim + 1))
#define lxlib_vec_op_a_xyzw_impl(dim, name, op, func_ret)                                                              \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        Vector##dim a = lx_checkvec##dim(L, 1);                                                                        \
        lx_vec_exp_##dim(lxlib_vec_op_a_xyzw_impl_impl, ;, a, op);                                                     \
        func_ret(L, (dim + 2), a);                                                                                     \
    }
#define lxlib_vec_op_a_xyzw(dim, name, op)                                                                             \
    lxlib_vec_op_a_xyzw_impl(dim, name, op, lx_return_updatevec##dim##_smartidx);                                      \
    lxlib_vec_op_a_xyzw_impl(dim, name##_alloc, op, lx_return_pushvec##dim##_dummyidx);

#define lxlib_vec_func_a_r_impl(dim, name, type_r, func_core, func_ret)                                                \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        const Vector##dim a = lx_checkvec##dim(L, 1);                                                                  \
        const type_r r = func_core(&a);                                                                                \
        func_ret(L, 2, r);                                                                                             \
    }
#define lxlib_vec_func_a_rn(dim, name)                                                                                 \
    lxlib_vec_func_a_r_impl(dim, name, double, lx_vec##dim##_##name, lx_return_pushnumber_dummyidx);
#define lxlib_vec_func_a_rv(dim, name)                                                                                 \
    lxlib_vec_func_a_r_impl(dim, name, Vector##dim, lx_vec##dim##_##name, lx_return_updatevec##dim##_smartidx);        \
    lxlib_vec_func_a_r_impl(dim, name##_alloc, Vector##dim, lx_vec##dim##_##name, lx_return_pushvec##dim##_dummyidx);

#define lxlib_vec_func_a_n_r_impl(dim, name, type_r, func_core, func_ret)                                              \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        const Vector##dim a = lx_checkvec##dim(L, 1);                                                                  \
        const double b = luaL_checknumber(L, 2);                                                                       \
        const type_r r = func_core(&a, b);                                                                             \
        func_ret(L, 3, r);                                                                                             \
    }
#define lxlib_vec_func_a_n_rn(dim, name)                                                                               \
    lxlib_vec_func_a_n_r_impl(dim, name, double, lx_vec##dim##_##name, lx_return_pushnumber_dummyidx);
#define lxlib_vec_func_a_n_rv(dim, name)                                                                               \
    lxlib_vec_func_a_n_r_impl(dim, name, Vector##dim, lx_vec##dim##_##name, lx_return_updatevec##dim##_smartidx);      \
    lxlib_vec_func_a_n_r_impl(dim, name##_alloc, Vector##dim, lx_vec##dim##_##name, lx_return_pushvec##dim##_dummyidx);

#define lxlib_vec_func_a_b_r_impl(dim, name, type_r, func_core, func_ret)                                              \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        const Vector##dim a = lx_checkvec##dim(L, 1);                                                                  \
        const Vector##dim b = lx_checkvec##dim(L, 2);                                                                  \
        const type_r r = func_core(&a, &b);                                                                            \
        func_ret(L, 3, r);                                                                                             \
    }
#define lxlib_vec_func_a_b_rn(dim, name)                                                                               \
    lxlib_vec_func_a_b_r_impl(dim, name, double, lx_vec##dim##_##name, lx_return_pushnumber_dummyidx);
#define lxlib_vec_func_a_b_rv(dim, name)                                                                               \
    lxlib_vec_func_a_b_r_impl(dim, name, Vector##dim, lx_vec##dim##_##name, lx_return_updatevec##dim##_smartidx);      \
    lxlib_vec_func_a_b_r_impl(dim, name##_alloc, Vector##dim, lx_vec##dim##_##name, lx_return_pushvec##dim##_dummyidx);

#define lxlib_vec_func_a_b_c_r_impl(dim, name, type_r, func_core, func_ret)                                            \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        const Vector##dim a = lx_checkvec##dim(L, 1);                                                                  \
        const Vector##dim b = lx_checkvec##dim(L, 2);                                                                  \
        const Vector##dim c = lx_checkvec##dim(L, 3);                                                                  \
        const type_r r = func_core(&a, &b, &c);                                                                        \
        func_ret(L, 4, r);                                                                                             \
    }
#define lxlib_vec_func_a_b_c_rn(dim, name)                                                                             \
    lxlib_vec_func_a_b_c_r_impl(dim, name, double, lx_vec##dim##_##name, lx_return_pushnumber_dummyidx);
#define lxlib_vec_func_a_b_c_rv(dim, name)                                                                             \
    lxlib_vec_func_a_b_c_r_impl(dim, name, Vector##dim, lx_vec##dim##_##name, lx_return_updatevec##dim##_smartidx);    \
    lxlib_vec_func_a_b_c_r_impl(dim, name##_alloc, Vector##dim, lx_vec##dim##_##name,                                  \
                                lx_return_pushvec##dim##_dummyidx);

#define lxlib_vec_func_a_b_n_r_impl(dim, name, type_r, func_core, func_ret)                                            \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        const Vector##dim a = lx_checkvec##dim(L, 1);                                                                  \
        const Vector##dim b = lx_checkvec##dim(L, 2);                                                                  \
        const double c = luaL_checknumber(L, 3);                                                                       \
        const type_r r = func_core(&a, &b, c);                                                                         \
        func_ret(L, 4, r);                                                                                             \
    }
#define lxlib_vec_func_a_b_n_rv(dim, name)                                                                             \
    lxlib_vec_func_a_b_n_r_impl(dim, name, Vector##dim, lx_vec##dim##_##name, lx_return_updatevec##dim##_smartidx);    \
    lxlib_vec_func_a_b_n_r_impl(dim, name##_alloc, Vector##dim, lx_vec##dim##_##name,                                  \
                                lx_return_pushvec##dim##_dummyidx);

#define lxlib_vec_func_a_b_n1_n2_r_impl(dim, name, type_r, func_core, func_ret)                                        \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        const Vector##dim a = lx_checkvec##dim(L, 1);                                                                  \
        const Vector##dim b = lx_checkvec##dim(L, 2);                                                                  \
        const double c = luaL_checknumber(L, 3);                                                                       \
        const double d = luaL_checknumber(L, 4);                                                                       \
        const type_r r = func_core(&a, &b, c, d);                                                                      \
        func_ret(L, 5, r);                                                                                             \
    }
#define lxlib_vec_func_a_b_n1_n2_rv(dim, name)                                                                         \
    lxlib_vec_func_a_b_n1_n2_r_impl(dim, name, Vector##dim, lx_vec##dim##_##name,                                      \
                                    lx_return_updatevec##dim##_smartidx);                                              \
    lxlib_vec_func_a_b_n1_n2_r_impl(dim, name##_alloc, Vector##dim, lx_vec##dim##_##name,                              \
                                    lx_return_pushvec##dim##_dummyidx);

#define lxlib_vec_reg_pair(dim, name) lxlib_reg_pair(vec##dim, name)
#define lxlib_vec_reg_pair_full(dim, name) lxlib_vec_reg_pair(dim, name), lxlib_vec_reg_pair(dim, name##_alloc)

#endif
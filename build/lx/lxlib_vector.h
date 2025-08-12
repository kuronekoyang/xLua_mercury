#ifndef __LXLIB_VECTOR_H__
#define __LXLIB_VECTOR_H__

#define lxlib_vec_op_a_impl(dim, name, func_core, func_stack, ret_value)                                               \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        Vector##dim a = lx_checkvec##dim(L, 1);                                                                        \
        func_core##_r(&a, &a);                                                                                         \
        func_stack(L, 2, a);                                                                                           \
        return ret_value;                                                                                              \
    }
#define lxlib_vec_op_a(dim, name)                                                                                      \
    lxlib_vec_op_a_impl(dim, name, lx_vec##dim##_##name, lx_setvec##dim##_smartidx, 0);                                \
    lxlib_vec_op_a_impl(dim, name##_alloc, lx_vec##dim##_##name, lx_pushvec##dim##_dummyidx, 1);

#define lxlib_vec_op_a_b_impl(dim, name, op, func_stack, ret_value)                                                    \
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
        func_stack(L, 3, a);                                                                                           \
        return ret_value;                                                                                              \
    }
#define lxlib_vec_op_a_b(dim, name, op)                                                                                \
    lxlib_vec_op_a_b_impl(dim, name, op, lx_setvec##dim##_smartidx, 0);                                                \
    lxlib_vec_op_a_b_impl(dim, name##_alloc, op, lx_pushvec##dim##_dummyidx, 1);

#define lxlib_vec_func_a_r_impl(name, dim, type_r, func_core, func_stack, ret_value)                                   \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        const Vector##dim a = lx_checkvec##dim(L, 1);                                                                  \
        const type_r r = func_core(&a);                                                                                \
        func_stack(L, 2, r);                                                                                           \
        return ret_value;                                                                                              \
    }
#define lxlib_vec_func_a_rn(name, dim)                                                                                 \
    lxlib_vec_func_a_r_impl(name, dim, double, lx_vec##dim##_##name, lua_pushnumber_dummyidx, 1);
#define lxlib_vec_func_a_rv(name, dim)                                                                                 \
    lxlib_vec_func_a_r_impl(name, dim, Vector##dim, lx_vec##dim##_##name, lx_setvec##dim##_smartidx, 0);               \
    lxlib_vec_func_a_r_impl(name##_alloc, dim, Vector##dim, lx_vec##dim##_##name, lx_pushvec##dim##_dummyidx, 1);

#define lxlib_vec_func_a_b_r_impl(dim, name, type_r, func_core, func_stack, ret_value)                                 \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        const Vector##dim a = lx_checkvec##dim(L, 1);                                                                  \
        const Vector##dim b = lx_checkvec##dim(L, 2);                                                                  \
        const type_r r = func_core(&a, &b);                                                                            \
        func_stack(L, 3, r);                                                                                           \
        return ret_value;                                                                                              \
    }
#define lxlib_vec_func_a_b_rn(dim, name)                                                                               \
    lxlib_vec_func_a_b_r_impl(dim, name, double, lx_vec##dim##_##name, lua_pushnumber_dummyidx, 1);
#define lxlib_vec_func_a_b_rv(dim, name)                                                                               \
    lxlib_vec_func_a_b_r_impl(dim, name, Vector##dim, lx_vec##dim##_##name, lx_setvec##dim##_smartidx, 0);             \
    lxlib_vec_func_a_b_r_impl(dim, name##_alloc, Vector##dim, lx_vec##dim##_##name, lx_pushvec##dim##_dummyidx, 1);

#define lxlib_vec_func_a_b_n_r_impl(dim, name, type_r, func_core, func_stack, ret_value)                               \
    static int vec##dim##_##name(lua_State *L)                                                                         \
    {                                                                                                                  \
        const Vector##dim a = lx_checkvec##dim(L, 1);                                                                  \
        const Vector##dim b = lx_checkvec##dim(L, 2);                                                                  \
        const double c = luaL_checknumber(L, 3);                                                                       \
        const type_r r = func_core(&a, &b, c);                                                                         \
        func_stack(L, 4, r);                                                                                           \
        return ret_value;                                                                                              \
    }
#define lxlib_vec_func_a_b_n_rv(dim, name)                                                                             \
    lxlib_vec_func_a_b_n_r_impl(dim, name, Vector##dim, lx_vec##dim##_##name, lx_setvec##dim##_smartidx, 0);           \
    lxlib_vec_func_a_b_n_r_impl(dim, name##_alloc, Vector##dim, lx_vec##dim##_##name, lx_pushvec##dim##_dummyidx, 1);

#define lxlib_vec_reg_pair(dim, name) {#name, vec##dim##_##name}
#define lxlib_vec_reg_pair_full(dim, name) lxlib_vec_reg_pair(dim, name), lxlib_vec_reg_pair(dim, name##_alloc)

#endif
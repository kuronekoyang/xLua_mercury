#ifndef __LX_VECTOR_H__
#define __LX_VECTOR_H__

#include "lx_math.h"

#define lx_vec_dim_1 x
#define lx_vec_dim_2 y
#define lx_vec_dim_3 z
#define lx_vec_comma ,

#define lx_vec_exp_1(exp, sep, ...) exp(1, __VA_ARGS__)
#define lx_vec_exp_2(exp, sep, ...) exp(1, __VA_ARGS__) sep exp(2, __VA_ARGS__)
#define lx_vec_exp_3(exp, sep, ...)                                                                                    \
    exp(1, __VA_ARGS__) sep exp(2, __VA_ARGS__)                                                                        \
    sep exp(3, __VA_ARGS__)

#define lx_vec_wrap_alloc(dim, exp, ...)                                                                               \
    ({                                                                                                                 \
        Vector##dim __vec_op_t;                                                                                        \
        exp(dim, __VA_ARGS__, &__vec_op_t);                                                                            \
        __vec_op_t;                                                                                                    \
    })

#define lx_vec_wrap_r_impl(dim, r, exp, ...) (r)->lx_vec_dim_##dim = exp(dim, __VA_ARGS__)
#define lx_vec_wrap_r(dim, r, exp, ...) lx_vec_exp_##dim(lx_vec_wrap_r_impl, ;, r, exp, __VA_ARGS__)

#define lx_vec_new_impl(dim, exp, ...) .lx_vec_dim_##dim = exp(dim, __VA_ARGS__)
#define lx_vec_new(dim, exp, ...) ((Vector##dim){lx_vec_exp_##dim(lx_vec_new_impl, lx_vec_comma, exp, __VA_ARGS__)})

#define lx_vec_combine(dim, op, exp, ...) lx_vec_exp_##dim(exp, op, __VA_ARGS__)

#define lx_vec_op_a_b_n_impl(dim, a, b, c, op, op2) (a)->lx_vec_dim_##dim op(b) -> lx_vec_dim_##dim op2 c
#define lx_vec_op_a_b_impl(dim, a, b, op) (a)->lx_vec_dim_##dim op(b) -> lx_vec_dim_##dim
#define lx_vec_op_a_n_impl(dim, a, b, op) (a)->lx_vec_dim_##dim op(b)
#define lx_vec_a_b_impl(dim, a, b, f) f((a)->lx_vec_dim_##dim, (b)->lx_vec_dim_##dim)
#define lx_vec_a_n_impl(dim, a, b, f) f((a)->lx_vec_dim_##dim, (b))
#define lx_vec_a_b_n_impl(dim, a, b, c, f) f((a)->lx_vec_dim_##dim, (b)->lx_vec_dim_##dim, (c))

#define lx_vec_op_a_b_n_r(dim, a, b, c, op, op2, r) lx_vec_wrap_r(dim, r, lx_vec_op_a_b_n_impl, a, b, c, op, op2)
#define lx_vec_op_a_b_n(dim, a, b, c, op, op2) lx_vec_new(dim, lx_vec_op_a_b_n_impl, a, b, c, op, op2)

#define lx_vec_op_a_b_r(dim, a, b, op, r) lx_vec_wrap_r(dim, r, lx_vec_op_a_b_impl, a, b, op)
#define lx_vec_op_a_b(dim, a, b, op) lx_vec_new(dim, lx_vec_op_a_b_impl, a, b, op)

#define lx_vec_op_a_n_r(dim, a, b, op, r) lx_vec_wrap_r(dim, r, lx_vec_op_a_n_impl, a, b, op)
#define lx_vec_op_a_n(dim, a, b, op) lx_vec_new(dim, lx_vec_op_a_n_impl, a, b, op)

#define lx_vec_a_b_r(dim, a, b, f, r) lx_vec_wrap_r(dim, r, lx_vec_a_b_impl, a, b, f)
#define lx_vec_a_b(dim, a, b, f) lx_vec_new(dim, lx_vec_a_b_impl, a, b, f)

#define lx_vec_a_b_n_r(dim, a, b, c, f, r) lx_vec_wrap_r(dim, r, lx_vec_a_b_n_impl, a, b, c, f)
#define lx_vec_a_b_n(dim, a, b, c, f) lx_vec_new(dim, lx_vec_a_b_n_impl, a, b, c, f)

#define lx_vec_add_r(dim, a, b, r) lx_vec_op_a_b_r(dim, a, b, +, r)
#define lx_vec_sub_r(dim, a, b, r) lx_vec_op_a_b_r(dim, a, b, -, r)
#define lx_vec_mul_r(dim, a, b, r) lx_vec_op_a_b_r(dim, a, b, *, r)
#define lx_vec_div_r(dim, a, b, r) lx_vec_op_a_b_r(dim, a, b, /, r)
#define lx_vec_add(dim, a, b) lx_vec_op_a_b(dim, a, b, +)
#define lx_vec_sub(dim, a, b) lx_vec_op_a_b(dim, a, b, -)
#define lx_vec_mul(dim, a, b) lx_vec_op_a_b(dim, a, b, *)
#define lx_vec_div(dim, a, b) lx_vec_op_a_b(dim, a, b, /)

#define lx_vec_add_num_r(dim, a, b, r) lx_vec_op_a_n_r(dim, a, b, +, r)
#define lx_vec_sub_num_r(dim, a, b, r) lx_vec_op_a_n_r(dim, a, b, -, r)
#define lx_vec_mul_num_r(dim, a, b, r) lx_vec_op_a_n_r(dim, a, b, *, r)
#define lx_vec_div_num_r(dim, a, b, r) lx_vec_op_a_n_r(dim, a, b, /, r)
#define lx_vec_add_num(dim, a, b) lx_vec_op_a_n(dim, a, b, +)
#define lx_vec_sub_num(dim, a, b) lx_vec_op_a_n(dim, a, b, -)
#define lx_vec_mul_num(dim, a, b) lx_vec_op_a_n(dim, a, b, *)
#define lx_vec_div_num(dim, a, b) lx_vec_op_a_n(dim, a, b, /)

#define lx_vec_min_r(dim, a, b, r) lx_vec_a_b_r(dim, a, b, lx_math_min, r)
#define lx_vec_max_r(dim, a, b, r) lx_vec_a_b_r(dim, a, b, lx_math_max, r)
#define lx_vec_min(dim, a, b) lx_vec_a_b(dim, a, b, lx_math_min)
#define lx_vec_max(dim, a, b) lx_vec_a_b(dim, a, b, lx_math_max)

#define lx_vec_lerp_r(dim, a, b, t, r) lx_vec_a_b_n_r(dim, a, b, t, lx_math_lerp, r)
#define lx_vec_lerp_unclamped_r(dim, a, b, t, r) lx_vec_a_b_n_r(dim, a, b, t, lx_math_lerp_unclamped, r)
#define lx_vec_lerp(dim, a, b, t) lx_vec_a_b_n(dim, a, b, t, lx_math_lerp)
#define lx_vec_lerp_unclamped(dim, a, b, t) lx_vec_a_b_n(dim, a, b, t, lx_math_lerp_unclamped)

#define lx_vec_dot(dim, a, b) lx_vec_combine(dim, +, lx_vec_op_a_b_impl, a, b, *)
#define lx_vec_sqr_magnitude(dim, v) lx_vec_combine(dim, +, lx_vec_op_a_b_impl, v, v, *)
#define lx_vec_magnitude(dim, v) lx_math_sqrt(lx_vec##dim##_sqr_magnitude(v))

#define lx_vec_normalize_r(dim, a, r)                                                                                  \
    {                                                                                                                  \
        const double __lx_vec_m = lx_vec_magnitude(dim, a);                                                            \
        if (__lx_vec_m > lx_epsilon)                                                                                   \
        {                                                                                                              \
            lx_vec_op_a_n_r(dim, a, __lx_vec_m, /, r);                                                                 \
        }                                                                                                              \
        else if ((r) != (a))                                                                                           \
        {                                                                                                              \
            *(r) = *(a);                                                                                               \
        }                                                                                                              \
    }
#define lx_vec_normalize(dim, a) lx_vec_new(dim, lx_vec_normalize_r, a)

#define lx_vec_distance(dim, a, b)                                                                                     \
    ({                                                                                                                 \
        Vector##dim __lx_vec_t = lx_vec_sub(dim, a, b);                                                                \
        lx_vec_magnitude(dim, &__lx_vec_t);                                                                            \
    })

#define lx_vec_reflect_r(dim, a, b, r)                                                                                 \
    {                                                                                                                  \
        const double __lx_vec_s = -2 * lx_vec_dot(dim, a, b);                                                          \
        lx_vec_op_a_b_n_r(dim, a, b, __lx_vec_s, +, *, r);                                                             \
    }
#define lx_vec_reflect(dim, a, b) lx_vec_wrap_alloc(dim, lx_vec_reflect_r, a, b)

#define lx_vec_project_r(dim, a, b, r)                                                                                 \
    {                                                                                                                  \
        const double __lx_vec_sm = lx_vec_sqr_magnitude(dim, b);                                                       \
        if (__lx_vec_sm > lx_sqr_epsilon)                                                                              \
        {                                                                                                              \
            const double __lx_vec_d = lx_vec_dot(dim, a, b) / __lx_vec_sm;                                             \
            lx_vec_op_a_n_r(dim, b, __lx_vec_d, *, r);                                                                 \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            *(r) = lx_vec##dim##_zero;                                                                                 \
        }                                                                                                              \
    }
#define lx_vec_project(dim, a, b) lx_vec_wrap_alloc(dim, lx_vec_project_r, a, b)

#define lx_vec_project_on_plane_r(dim, a, b, r)                                                                        \
    {                                                                                                                  \
        const Vector##dim __lx_vec_p = lx_vec_project(dim, a, b);                                                      \
        lx_vec_op_a_b_r(dim, a, &__lx_vec_p, -, r);                                                                    \
    }
#define lx_vec_project_on_plane(dim, a, b) lx_vec_wrap_alloc(dim, lx_vec_project_on_plane_r, a, b)

#endif

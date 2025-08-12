#ifndef __LX_VECTOR3_H__
#define __LX_VECTOR3_H__

#include "lx_math.h"

typedef struct
{
    double x;
    double y;
    double z;
} Vector3;

#define lx_vec3_op_a_b(a, b, op) ((Vector3){.x = (a)->x op(b)->x, .y = (a)->y op(b)->y, .z = (a)->z op(b)->z})
#define lx_vec3_op_a_b_r(a, b, r, op)                                                                                  \
    {                                                                                                                  \
        (r)->x = (a)->x op(b)->x;                                                                                      \
        (r)->y = (a)->y op(b)->y;                                                                                      \
        (r)->z = (a)->z op(b)->z;                                                                                      \
    }
#define lx_vec3_op_a_n(a, b, op) ((Vector3){.x = (a)->x op(b), .y = (a)->y op(b), .z = (a)->z op(b)})
#define lx_vec3_op_a_n_r(a, b, r, op)                                                                                  \
    {                                                                                                                  \
        (r)->x = (a)->x op(b);                                                                                         \
        (r)->y = (a)->y op(b);                                                                                         \
        (r)->z = (a)->z op(b);                                                                                         \
    }
#define lx_vec3_a_b(a, b, f) ((Vector3){.x = f((a)->x, (b)->x), .y = f((a)->y, (b)->y), .z = f((a)->z, (b)->z})
#define lx_vec3_a_b_r(a, b, r, f)                                                                                      \
    {                                                                                                                  \
        (r)->x = f((a)->x, (b)->x);                                                                                    \
        (r)->y = f((a)->y, (b)->y);                                                                                    \
        (r)->z = f((a)->z, (b)->z);                                                                                    \
    }
#define lx_vec3_a_b_n(a, b, n, f)                                                                                      \
    ((Vector3){.x = f((a)->x, (b)->x, n), .y = f((a)->y, (b)->y, n), .z = f((a)->z, (b)->z, n)})
#define lx_vec3_a_b_n_r(a, b, n, r, f)                                                                                 \
    {                                                                                                                  \
        (r)->x = f((a)->x, (b)->x, n);                                                                                 \
        (r)->y = f((a)->y, (b)->y, n);                                                                                 \
        (r)->z = f((a)->z, (b)->z, n);                                                                                 \
    }

#define lx_vec3_zero ((Vector3){.x = 0, .y = 0, .z = 0})

#define lx_vec3_add(a, b) lx_vec3_op_a_b(a, b, +)
#define lx_vec3_sub(a, b) lx_vec3_op_a_b(a, b, -)
#define lx_vec3_mul(a, b) lx_vec3_op_a_b(a, b, *)
#define lx_vec3_div(a, b) lx_vec3_op_a_b(a, b, /)
#define lx_vec3_add_r(a, b, r) lx_vec3_op_a_b_r(a, b, r, +)
#define lx_vec3_sub_r(a, b, r) lx_vec3_op_a_b_r(a, b, r, -)
#define lx_vec3_mul_r(a, b, r) lx_vec3_op_a_b_r(a, b, r, *)
#define lx_vec3_div_r(a, b, r) lx_vec3_op_a_b_r(a, b, r, /)

#define lx_vec3_add_num(a, b) lx_vec3_op_a_n(a, b, +)
#define lx_vec3_sub_num(a, b) lx_vec3_op_a_n(a, b, -)
#define lx_vec3_mul_num(a, b) lx_vec3_op_a_n(a, b, *)
#define lx_vec3_div_num(a, b) lx_vec3_op_a_n(a, b, /)
#define lx_vec3_add_num_r(a, b, r) lx_vec3_op_a_n_r(a, b, r, +)
#define lx_vec3_sub_num_r(a, b, r) lx_vec3_op_a_n_r(a, b, r, -)
#define lx_vec3_mul_num_r(a, b, r) lx_vec3_op_a_n_r(a, b, r, *)
#define lx_vec3_div_num_r(a, b, r) lx_vec3_op_a_n_r(a, b, r, /)

#define lx_vec3_min(a, b) lx_vec3_a_b(a, b, lx_math_min)
#define lx_vec3_max(a, b) lx_vec3_a_b(a, b, lx_math_max)
#define lx_vec3_min_r(a, b, r) lx_vec3_a_b_r(a, b, r, lx_math_min)
#define lx_vec3_max_r(a, b, r) lx_vec3_a_b_r(a, b, r, lx_math_max)

#define lx_vec3_lerp(a, b, t) lx_vec3_a_b_n(a, b, t, lx_math_lerp)
#define lx_vec3_lerp_unclamped(a, b, t) lx_vec3_a_b_n(a, b, t, lx_math_lerp_unclamped)
#define lx_vec3_lerp_r(a, b, t, r) lx_vec3_a_b_n_r(a, b, t, r, lx_math_lerp)
#define lx_vec3_lerp_unclamped_r(a, b, t, r) lx_vec3_a_b_n_r(a, b, t, r, lx_math_lerp_unclamped)

#define lx_vec3_dot(a, b) ((a)->x * (b)->x + (a)->y * (b)->y + (a)->z * (b)->z)
#define lx_vec3_cross(a, b)                                                                                            \
    ((Vector3){.x = (a)->y * (b)->z - (a)->z * (b)->y,                                                                 \
               .y = (a)->z * (b)->x - (a)->x * (b)->z,                                                                 \
               .z = (a)->x * (b)->y - (a)->y * (b)->x})
#define lx_vec3_sqr_magnitude(v) ((v)->x * (v)->x + (v)->y * (v)->y + (v)->z * (v)->z)
#define lx_vec3_magnitude(v) lx_math_sqrt(lx_vec3_sqr_magnitude(v))

#define lx_vec3_normalize(v)                                                                                           \
    {                                                                                                                  \
        double __lx_vec3_m = lx_vec3_magnitude(v);                                                                     \
        if (__lx_vec3_m > lx_epsilon)                                                                                  \
        {                                                                                                              \
            (v)->x /= __lx_vec3_m;                                                                                     \
            (v)->y /= __lx_vec3_m;                                                                                     \
            (v)->z /= __lx_vec3_m;                                                                                     \
        }                                                                                                              \
    }
#define lx_vec3_normalized(v)                                                                                          \
    ({                                                                                                                 \
        Vector3 __lx_vec3_t = *(v);                                                                                    \
        lx_vec3_normalize(&__lx_vec3_t);                                                                               \
        __lx_vec3_t;                                                                                                   \
    })
#define lx_vec3_distance(a, b)                                                                                         \
    ({                                                                                                                 \
        Vector3 __lx_vec3_t = lx_vec3_sub(a, b);                                                                       \
        lx_vec3_magnitude(&__lx_vec3_t);                                                                               \
    })
#define lx_vec3_reflect(a, b)                                                                                          \
    ({                                                                                                                 \
        double __lx_vec3_s = -2 * lx_vec3_dot(a, b);                                                                   \
        (Vector3){.x = (a)->x + __lx_vec3_s * (b)->x,                                                                  \
                  .y = (a)->y - __lx_vec3_s * (b)->y,                                                                  \
                  .z = (a)->z - __lx_vec3_s * (b)->z};                                                                 \
    })
#define lx_vec3_project(a, b)                                                                                          \
    ({                                                                                                                 \
        double __lx_vec3_sm = lx_vec3_sqr_magnitude(b);                                                                \
        Vector3 __lx_vec3_v;                                                                                           \
        if (__lx_vec3_sm > lx_sqr_epsilon)                                                                             \
        {                                                                                                              \
            double __lx_vec3_d = lx_vec3_dot(a, b) / __lx_vec3_sm;                                                     \
            __lx_vec3_v.x = __lx_vec3_d * (b)->x;                                                                      \
            __lx_vec3_v.y = __lx_vec3_d * (b)->y;                                                                      \
            __lx_vec3_v.z = __lx_vec3_d * (b)->z;                                                                      \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            __lx_vec3_v.x = 0;                                                                                         \
            __lx_vec3_v.y = 0;                                                                                         \
            __lx_vec3_v.z = 0;                                                                                         \
        }                                                                                                              \
        __lx_vec3_v;                                                                                                   \
    })
#define lx_vec3_project_on_plane(a, b)                                                                                 \
    ({                                                                                                                 \
        Vector3 __lx_vec3_p = lx_vec3_project(a, b);                                                                   \
        __lx_vec3_p.x = (a)->x - __lx_vec3_p.x;                                                                        \
        __lx_vec3_p.y = (a)->y - __lx_vec3_p.y;                                                                        \
        __lx_vec3_p.z = (a)->z - __lx_vec3_p.z;                                                                        \
        __lx_vec3_p;                                                                                                   \
    })

double lx_vec3_angle_rad(const Vector3 *a, const Vector3 *b);

#endif

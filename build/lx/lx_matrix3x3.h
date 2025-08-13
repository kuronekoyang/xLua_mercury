#ifndef __LX_MATRIX3X3_H__
#define __LX_MATRIX3X3_H__

#include "lx_math.h"
#include "lx_vector3.h"

typedef struct
{
    Vector3 x;
    Vector3 y;
    Vector3 z;
} Matrix3x3;

#define lx_matrix3x3_mul_matrix3x3_r_impl(dim, a, b, r)                                                                \
    {                                                                                                                  \
        const Vector3 v = {                                                                                            \
            .x = lx_vec_get_dim(&lx_vec_get_dim(a, 1), dim),                                                           \
            .y = lx_vec_get_dim(&lx_vec_get_dim(a, 2), dim),                                                           \
            .z = lx_vec_get_dim(&lx_vec_get_dim(a, 3), dim),                                                           \
        };                                                                                                             \
        lx_vec_get_dim(&lx_vec_get_dim(r, 1), dim) = lx_vec3_dot(&v, &lx_vec_get_dim(b, 1));                           \
        lx_vec_get_dim(&lx_vec_get_dim(r, 2), dim) = lx_vec3_dot(&v, &lx_vec_get_dim(b, 2));                           \
        lx_vec_get_dim(&lx_vec_get_dim(r, 3), dim) = lx_vec3_dot(&v, &lx_vec_get_dim(b, 3));                           \
    }
#define lx_matrix3x3_mul_matrix3x3_r(a, b, r) lx_vec_exp_3(lx_matrix3x3_mul_matrix3x3_r_impl, lx_vec_space, a, b, r)

#define lx_matrix3x3_mul_matrix3x3(a, b)                                                                               \
    ({                                                                                                                 \
        Matrix3x3 __mat_t;                                                                                             \
        lx_matrix3x3_mul_matrix3x3_r(a, b, &__mat_t);                                                                  \
        __mat_t;                                                                                                       \
    })

#define lx_vec3_mul_matrix3x3_r(a, b, r)                                                                               \
    {                                                                                                                  \
        const double __x = (b)->x.x * (a)->x + (b)->y.x * (a)->y + (b)->z.x * (a)->z;                                  \
        const double __y = (b)->x.y * (a)->x + (b)->y.y * (a)->y + (b)->z.y * (a)->z;                                  \
        const double __z = (b)->x.z * (a)->x + (b)->y.z * (a)->y + (b)->z.z * (a)->z;                                  \
        (r)->x = __x;                                                                                                  \
        (r)->y = __y;                                                                                                  \
        (r)->z = __z;                                                                                                  \
    }
#define lx_vec3_mul_matrix3x3(a, b)                                                                                    \
    ({                                                                                                                 \
        Vector3 __vec_t;                                                                                               \
        lx_vec3_mul_matrix3x3_r(a, b, &__vec_t);                                                                       \
        __vec_t;                                                                                                       \
    })

void lx_matrix3x3_axis_angle_rad_to_matrix_r(const Vector3 *axis, double angle, Matrix3x3 *r);
#define lx_matrix3x3_axis_angle_rad_to_matrix(axis, angle)                                                             \
    ({                                                                                                                 \
        Matrix3x3 __mat_t;                                                                                             \
        lx_matrix3x3_axis_angle_rad_to_matrix_r(axis, angle, &__mat_t);                                                \
        __mat_t;                                                                                                       \
    })

#endif

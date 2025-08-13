#ifndef __LX_VECTOR3_H__
#define __LX_VECTOR3_H__

#include "lx_math.h"
#include "lx_vector.h"

typedef struct
{
    double x;
    double y;
    double z;
} Vector3;

#define lx_vec3_zero lx_vec_zero(3)
#define lx_vec3_clear(a) lx_vec_clear(3, a)

#define lx_vec3_add(a, b) lx_vec_add(3, a, b)
#define lx_vec3_sub(a, b) lx_vec_sub(3, a, b)
#define lx_vec3_mul(a, b) lx_vec_mul(3, a, b)
#define lx_vec3_div(a, b) lx_vec_div(3, a, b)
#define lx_vec3_add_r(a, b, r) lx_vec_add_r(3, a, b, r)
#define lx_vec3_sub_r(a, b, r) lx_vec_sub_r(3, a, b, r)
#define lx_vec3_mul_r(a, b, r) lx_vec_mul_r(3, a, b, r)
#define lx_vec3_div_r(a, b, r) lx_vec_div_r(3, a, b, r)

#define lx_vec3_add_num(a, b) lx_vec_add_num(3, a, b)
#define lx_vec3_sub_num(a, b) lx_vec_sub_num(3, a, b)
#define lx_vec3_mul_num(a, b) lx_vec_mul_num(3, a, b)
#define lx_vec3_div_num(a, b) lx_vec_div_num(3, a, b)
#define lx_vec3_add_num_r(a, b, r) lx_vec_add_num_r(3, a, b, r)
#define lx_vec3_sub_num_r(a, b, r) lx_vec_sub_num_r(3, a, b, r)
#define lx_vec3_mul_num_r(a, b, r) lx_vec_mul_num_r(3, a, b, r)
#define lx_vec3_div_num_r(a, b, r) lx_vec_div_num_r(3, a, b, r)

#define lx_vec3_min(a, b) lx_vec_min(3, a, b)
#define lx_vec3_max(a, b) lx_vec_max(3, a, b)
#define lx_vec3_min_r(a, b, r) lx_vec_min_r(3, a, b, r)
#define lx_vec3_max_r(a, b, r) lx_vec_max_r(3, a, b, r)

#define lx_vec3_lerp(a, b, t) lx_vec_lerp(3, a, b, t)
#define lx_vec3_lerp_unclamped(a, b, t) lx_vec_lerp_unclamped(3, a, b, t)
#define lx_vec3_lerp_r(a, b, t, r) lx_vec_lerp_r(3, a, b, t, r)
#define lx_vec3_lerp_unclamped_r(a, b, t, r) lx_vec_lerp_unclamped_r(3, a, b, t, r)

#define lx_vec3_dot(a, b) lx_vec_dot(3, a, b)
#define lx_vec3_sqr_magnitude(v) lx_vec_sqr_magnitude(3, v)
#define lx_vec3_magnitude(v) lx_vec_magnitude(3, v)

#define lx_vec3_normalize(v) lx_vec_normalize(3, v)
#define lx_vec3_normalize_r(v, r) lx_vec_normalize_r(3, v, r)

#define lx_vec3_distance(a, b) lx_vec_distance(3, a, b)
#define lx_vec3_direction(a, b) lx_vec_direction(3, a, b)
#define lx_vec3_reflect(a, b) lx_vec_reflect(3, a, b)
#define lx_vec3_project(a, b) lx_vec_project(3, a, b)
#define lx_vec3_project_on_plane(a, b) lx_vec_project_on_plane(3, a, b)

#define lx_vec3_cross(a, b)                                                                                            \
    ((Vector3){.x = (a)->y * (b)->z - (a)->z * (b)->y,                                                                 \
               .y = (a)->z * (b)->x - (a)->x * (b)->z,                                                                 \
               .z = (a)->x * (b)->y - (a)->y * (b)->x})

#define lx_vec3_angle_rad(a, b) lx_vec_angle_rad(3, a, b)
#define lx_vec3_angle_deg(a, b) (lx_vec3_angle_rad(a, b)) * lx_rad2deg
double lx_vec3_signed_angle_rad(const Vector3 *from, const Vector3 *to, const Vector3 *axis);
#define lx_vec3_signed_angle_deg(a, b, axis) lx_vec3_signed_angle_rad(a, b, axis) * lx_rad2deg
#define lx_vec3_rotate_around_axis_y_rad(a, angle)                                                                     \
    ({                                                                                                                 \
        double __r = -(angle);                                                                                         \
        double __sin = lx_math_sin(__r);                                                                               \
        double __cos = lx_math_cos(__r);                                                                               \
        ((Vector3){.x = __cos * (a)->x - __sin * (a)->z, .y = (a)->y, .z = __sin * (a)->x + __cos * (a)->z});          \
    })
#define lx_vec3_rotate_around_axis_y_deg(a, angle) lx_vec3_rotate_around_axis_y_rad(a, angle *lx_rad2deg)

Vector3 lx_vec3_rotate_towards_rad(const Vector3 *lhs, const Vector3 *rhs, double angleMoveRad, double magnitudeMove);
#define lx_vec3_rotate_towards_rad_r(a, b, c, d, r) *(r) = lx_vec3_rotate_towards_rad(a, b, c, d)
Vector3 lx_vec3_move_towards(const Vector3 *lhs, const Vector3 *rhs, double clampedDistance);
#define lx_vec3_move_towards_r(a, b, c, r) *(r) = lx_vec3_move_towards(a, b, c)

#endif

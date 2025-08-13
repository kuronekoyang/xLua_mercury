#ifndef __LX_VECTOR2_H__
#define __LX_VECTOR2_H__

#include "lx_math.h"
#include "lx_vector.h"

typedef struct
{
    double x;
    double y;
} Vector2;

#define lx_vec2_zero lx_vec_zero(2)
#define lx_vec2_clear(a) lx_vec_clear(2, a)

#define lx_vec2_add(a, b) lx_vec_add(2, a, b)
#define lx_vec2_sub(a, b) lx_vec_sub(2, a, b)
#define lx_vec2_mul(a, b) lx_vec_mul(2, a, b)
#define lx_vec2_div(a, b) lx_vec_div(2, a, b)
#define lx_vec2_add_r(a, b, r) lx_vec_add_r(2, a, b, r)
#define lx_vec2_sub_r(a, b, r) lx_vec_sub_r(2, a, b, r)
#define lx_vec2_mul_r(a, b, r) lx_vec_mul_r(2, a, b, r)
#define lx_vec2_div_r(a, b, r) lx_vec_div_r(2, a, b, r)

#define lx_vec2_add_num(a, b) lx_vec_add_num(2, a, b)
#define lx_vec2_sub_num(a, b) lx_vec_sub_num(2, a, b)
#define lx_vec2_mul_num(a, b) lx_vec_mul_num(2, a, b)
#define lx_vec2_div_num(a, b) lx_vec_div_num(2, a, b)
#define lx_vec2_add_num_r(a, b, r) lx_vec_add_num_r(2, a, b, r)
#define lx_vec2_sub_num_r(a, b, r) lx_vec_sub_num_r(2, a, b, r)
#define lx_vec2_mul_num_r(a, b, r) lx_vec_mul_num_r(2, a, b, r)
#define lx_vec2_div_num_r(a, b, r) lx_vec_div_num_r(2, a, b, r)

#define lx_vec2_min(a, b) lx_vec_min(2, a, b)
#define lx_vec2_max(a, b) lx_vec_max(2, a, b)
#define lx_vec2_min_r(a, b, r) lx_vec_min_r(2, a, b, r)
#define lx_vec2_max_r(a, b, r) lx_vec_max_r(2, a, b, r)

#define lx_vec2_lerp(a, b, t) lx_vec_lerp(2, a, b, t)
#define lx_vec2_lerp_unclamped(a, b, t) lx_vec_lerp_unclamped(2, a, b, t)
#define lx_vec2_lerp_r(a, b, t, r) lx_vec_lerp_r(2, a, b, t, r)
#define lx_vec2_lerp_unclamped_r(a, b, t, r) lx_vec_lerp_unclamped_r(2, a, b, t, r)

#define lx_vec2_dot(a, b) lx_vec_dot(2, a, b)
#define lx_vec2_sqr_magnitude(v) lx_vec_sqr_magnitude(2, v)
#define lx_vec2_magnitude(v) lx_vec_magnitude(2, v)

#define lx_vec2_normalize(v) lx_vec_normalize(2, v)
#define lx_vec2_normalize_r(v, r) lx_vec_normalize_r(2, v, r)

#define lx_vec2_distance(a, b) lx_vec_distance(2, a, b)
#define lx_vec2_direction(a, b) lx_vec_direction(2, a, b)
#define lx_vec2_reflect(a, b) lx_vec_reflect(2, a, b)
#define lx_vec2_project(a, b) lx_vec_project(2, a, b)
#define lx_vec2_project_on_plane(a, b) lx_vec_project_on_plane(2, a, b)

#define lx_vec2_cross(a, b) ((a)->x * (b)->y - (a)->y * (b)->x)

#define lx_vec2_angle_rad(a, b) lx_vec_angle_rad(2, a, b)
#define lx_vec2_angle_deg(a, b) (lx_vec2_angle_rad(a, b)) * lx_rad2deg
double lx_vec2_signed_angle_rad(const Vector2 *a, const Vector2 *b);
#define lx_vec2_signed_angle_deg(a, b) lx_vec2_signed_angle_rad(a, b) * lx_rad2deg
#define lx_vec2_rotate_rad(a, angle)                                                                                   \
    ({                                                                                                                 \
        double __r = -(angle);                                                                                           \
        double __sin = lx_math_sin(__r);                                                                               \
        double __cos = lx_math_cos(__r);                                                                               \
        ((Vector2){.x = __cos * (a)->x - __sin * (a)->y, .y = __sin * (a)->x + __cos * (a)->y});                       \
    })
#define lx_vec2_rotate_deg(a, angle) lx_vec2_rotate_rad(a, angle * lx_rad2deg)

#endif

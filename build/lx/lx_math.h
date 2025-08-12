#ifndef __LX_MATH_H__
#define __LX_MATH_H__

#include <math.h>
#include <stdint.h>

#define lx_pi 3.14159274
#define lx_half_pi 1.57079637
#define lx_two_pi 6.28318548
#define lx_rad2deg 57.29578
#define lx_deg2rad 0.0174532924
#define lx_half_deg2rad 0.0087266462599716
#define lx_epsilon 1e-4
#define lx_sqr_epsilon 1e-8
#define lx_sqrt_two 1.4142135623730950488016887242097
#define lx_half_sqrt_two 0.70710678118654752440084436210485

#define lx_math_min(a, b) ((a) < (b) ? (a) : (b))
#define lx_math_max(a, b) ((a) > (b) ? (a) : (b))
#define lx_math_abs(x) (((x) < 0) ? -(x) : (x))
#define lx_math_sqrt(x) sqrt((double)(x))
#define lx_math_floor(x) floor((double)(x))
#define lx_math_ceil(x) ceil((double)(x))
#define lx_math_round(x) round((double)(x))
#define lx_math_sin(x) sin((double)(x))
#define lx_math_cos(x) cos((double)(x))
#define lx_math_asin(x) asin((double)(x))
#define lx_math_acos(x) acos((double)(x))
#define lx_math_atan2(y, x) atan2((double)(y), (double)(x))

#define lx_math_clamp(v, min, max) ((v) < (min) ? (min) : ((v) > (max) ? (max) : (v)))
#define lx_math_clamp01(v) lx_math_clamp(v, 0, 1)
#define lx_math_lerp_unclamped(a, b, t) ((a) + ((b) - (a)) * (t))
#define lx_math_lerp(a, b, t) lx_math_lerp_unclamped(a, b, lx_math_clamp01(t))
#define lx_math_sign(value) ((value) < 0 ? -1 : ((value) > 0 ? 1 : 0))

int64_t lx_math_next_pow2(int64_t val);

#endif

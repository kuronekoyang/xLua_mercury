#include "lx_vector2.h"

double lx_vec2_angle_rad(const Vector2 *a, const Vector2 *b)
{
    Vector2 na = lx_vec2_normalized(a);
    Vector2 nb = lx_vec2_normalized(b);
    double d = lx_vec2_dot(&na, &nb);
    d = lx_math_clamp(d, -1, 1);
    return lx_math_acos(d);
}

double lx_vec2_angle_rad_ccw(const Vector2 *a, const Vector2 *b)
{
    Vector2 na = lx_vec2_normalized(a);
    Vector2 nb = lx_vec2_normalized(b);
    double d = lx_vec2_dot(&na, &nb);
    if (lx_math_abs(d - 1) <= lx_epsilon)
        return 0;
    if (lx_math_abs(d + 1) <= lx_epsilon)
        return lx_pi;
    double angle = lx_math_acos(d);
    if (lx_vec2_cross(&na, &nb) < 0)
        return -angle;
    return angle;
}
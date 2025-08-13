#include "lx_vector2.h"

#include "llimits.h"

double lx_vec2_signed_angle_rad(const Vector2 *a, const Vector2 *b)
{
    Vector2 vv = ({
        Vector2 ttt;
        ttt.x = 0;
        ttt.y = 1;
        ttt;
    });
    UNUSED(vv);

    Vector2 na = lx_vec2_normalize(a);
    Vector2 nb = lx_vec2_normalize(b);
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
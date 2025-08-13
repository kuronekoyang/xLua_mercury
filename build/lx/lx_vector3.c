#include "lx_vector3.h"
#include "lx_matrix3x3.h"

static double ClampedMove(double lhs, double rhs, double clampedDelta)
{
    double delta = rhs - lhs;
    if (delta > 0.0)
        return lhs + lx_math_min(delta, clampedDelta);
    return lhs - lx_math_min(-delta, clampedDelta);
}

static Vector3 OrthoNormalVectorFast(const Vector3 *v)
{
    Vector3 r;
    if (lx_math_abs(v->z) > lx_half_sqrt_two)
    {
        // choose p in y-z plane
        const double a = v->y * v->y + v->z * v->z;
        const double k = 1.0 / lx_math_sqrt(a);
        r.x = 0.0;
        r.y = -v->z * k;
        r.z = v->y * k;
    }
    else
    {
        // choose p in x-y plane
        const double a = v->x * v->x + v->y * v->y;
        const double k = 1.0 / lx_math_sqrt(a);
        r.x = -v->y * k;
        r.y = v->x * k;
        r.z = 0.0;
    }
    return r;
}

double lx_vec3_signed_angle_rad(const Vector3 *from, const Vector3 *to, const Vector3 *axis)
{
    const Vector3 projectFrom = lx_vec3_project_on_plane(from, axis);
    const Vector3 projectTo = lx_vec3_project_on_plane(to, axis);
    double angle = lx_vec3_angle_rad(&projectFrom, &projectTo);
    const Vector3 cross = lx_vec3_cross(&projectFrom, &projectTo);
    if (lx_vec3_dot(axis, &cross) < 0)
        angle = -angle;
    return angle;
}

Vector3 lx_vec3_rotate_towards_rad(const Vector3 *lhs, const Vector3 *rhs, double angleMoveRad, double magnitudeMove)
{
    double lhsMag = lx_vec3_magnitude(lhs);
    double rhsMag = lx_vec3_magnitude(rhs);

    // both vectors are non-zero
    if (lhsMag > lx_epsilon && rhsMag > lx_epsilon)
    {
        Vector3 lhsNorm = lx_vec3_div_num(lhs, lhsMag);
        Vector3 rhsNorm = lx_vec3_div_num(rhs, rhsMag);

        double dot = lx_vec3_dot(&lhsNorm, &rhsNorm);
        // direction is almost the same
        if (dot > 1.0 - lx_epsilon)
        {
            return lx_vec3_move_towards(lhs, rhs, magnitudeMove);
        }
        // directions are almost opposite
        else if (dot < -1.0 + lx_epsilon)
        {
            Vector3 axis = OrthoNormalVectorFast(&lhsNorm);
            Matrix3x3 m = lx_matrix3x3_axis_angle_rad_to_matrix(&axis, angleMoveRad);
            Vector3 rotated = lx_vec3_mul_matrix3x3(&lhsNorm, &m);
            double clampedMove = ClampedMove(lhsMag, rhsMag, magnitudeMove);
            lx_vec3_mul_num_r(&rotated, clampedMove, &rotated);
            return rotated;
        }
        // normal case
        else
        {
            double angle = lx_math_acos(dot);
            Vector3 axis = lx_vec3_cross(&lhsNorm, &rhsNorm);
            lx_vec3_normalize_r(&axis, &axis);
            Matrix3x3 m = lx_matrix3x3_axis_angle_rad_to_matrix(&axis, lx_math_min(angleMoveRad, angle));
            Vector3 rotated = lx_vec3_mul_matrix3x3(&lhsNorm, &m);
            double clampedMove = ClampedMove(lhsMag, rhsMag, magnitudeMove);
            lx_vec3_mul_num_r(&rotated, clampedMove, &rotated);
            return rotated;
        }
    }
    // at least one of the vectors is almost zero
    else
    {
        return lx_vec3_move_towards(lhs, rhs, magnitudeMove);
    }
}

Vector3 lx_vec3_move_towards(const Vector3 *lhs, const Vector3 *rhs, double clampedDistance)
{
    Vector3 delta = lx_vec3_sub(lhs, rhs);
    const double sqrDelta = lx_vec3_sqr_magnitude(&delta);
    const double sqrClampedDistance = clampedDistance * clampedDistance;
    if (sqrDelta > sqrClampedDistance)
    {
        const double deltaMag = lx_math_sqrt(sqrDelta);
        if (deltaMag > lx_epsilon)
        {
            lx_vec3_div_num_r(&delta, clampedDistance / deltaMag, &delta);
            lx_vec3_add_r(&delta, lhs, &delta);
            return delta;
        }

        return *lhs;
    }

    return *rhs;
}
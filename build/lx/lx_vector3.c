#include "lx_vector3.h"

Vector3 lx_vec3_project(const Vector3 *vector, const Vector3 *onNormal)
{
    Vector3 result;
    double num = lx_vec3_sqr_magnitude(onNormal);
    if (num <= lx_sqr_epsilon)
    {
        result.x = 0;
        result.y = 0;
        result.z = 0;
    }
    else
    {
        double s = lx_vec3_dot(vector, onNormal) / num;
        result.x = onNormal->x * s;
        result.y = onNormal->y * s;
        result.z = onNormal->z * s;
    }
    return result;
}
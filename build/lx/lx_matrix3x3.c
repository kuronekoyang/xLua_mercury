#include "lx_matrix3x3.h"


void GetRotMatrixNormVec(double* out, const double* inVec, double radians);

void lx_matrix3x3_axis_angle_rad_to_matrix_r(const Vector3* axis, double angle, Matrix3x3* r)
{
    GetRotMatrixNormVec((double*)r, (double*)axis, angle);
}

//===========================================================================

#define __LX_MATRIX_EPSILON 0.000001

#define __LX_MATRIX_CROSS(dest, v1, v2)                                                                                            \
    {                                                                                                                  \
        dest[0] = v1[1] * v2[2] - v1[2] * v2[1];                                                                       \
        dest[1] = v1[2] * v2[0] - v1[0] * v2[2];                                                                       \
        dest[2] = v1[0] * v2[1] - v1[1] * v2[0];                                                                       \
    }

#define __LX_MATRIX_DOT(v1, v2) (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2])

#define __LX_MATRIX_SUB(dest, v1, v2)                                                                                              \
    {                                                                                                                  \
        dest[0] = v1[0] - v2[0];                                                                                       \
        dest[1] = v1[1] - v2[1];                                                                                       \
        dest[2] = v1[2] - v2[2];                                                                                       \
    }

/*
 * A function for creating a rotation matrix that rotates a vector called
 * "from" into another vector called "to".
 * Input : from[3], to[3] which both must be *normalized* non-zero vectors
 * Output: mtx[3][3] -- a 3x3 matrix in colum-major form
 * Author: Tomas M�ller, 1999
 */
void fromToRotation(const double from[3], const double to[3], double mtx[3][3])
{
    double v[3];
    double e, h;
    __LX_MATRIX_CROSS(v, from, to);
    e = __LX_MATRIX_DOT(from, to);
    if (e > 1.0 - __LX_MATRIX_EPSILON) /* "from" almost or equal to "to"-vector? */
    {
        /* return identity */
        mtx[0][0] = 1.0;
        mtx[0][1] = 0.0;
        mtx[0][2] = 0.0;
        mtx[1][0] = 0.0;
        mtx[1][1] = 1.0;
        mtx[1][2] = 0.0;
        mtx[2][0] = 0.0;
        mtx[2][1] = 0.0;
        mtx[2][2] = 1.0;
    }
    else if (e < -1.0 + __LX_MATRIX_EPSILON) /* "from" almost or equal to negated "to"? */
    {
        double up[3], left[3];
        double invlen;
        double fxx, fyy, fzz, fxy, fxz, fyz;
        double uxx, uyy, uzz, uxy, uxz, uyz;
        double lxx, lyy, lzz, lxy, lxz, lyz;
        /* left=CROSS(from, (1,0,0)) */
        left[0] = 0.0;
        left[1] = from[2];
        left[2] = -from[1];
        if (__LX_MATRIX_DOT(left, left) < __LX_MATRIX_EPSILON) /* was left=CROSS(from,(1,0,0)) a good choice? */
        {
            /* here we now that left = CROSS(from, (1,0,0)) will be a good choice */
            left[0] = -from[2];
            left[1] = 0.0;
            left[2] = from[0];
        }
        /* normalize "left" */
        invlen = 1.0f / sqrt(__LX_MATRIX_DOT(left, left));
        left[0] *= invlen;
        left[1] *= invlen;
        left[2] *= invlen;
        __LX_MATRIX_CROSS(up, left, from);
        /* now we have a coordinate system, i.e., a basis;    */
        /* M=(from, up, left), and we want to rotate to:      */
        /* N=(-from, up, -left). This is done with the matrix:*/
        /* N*M^T where M^T is the transpose of M              */
        fxx = -from[0] * from[0];
        fyy = -from[1] * from[1];
        fzz = -from[2] * from[2];
        fxy = -from[0] * from[1];
        fxz = -from[0] * from[2];
        fyz = -from[1] * from[2];

        uxx = up[0] * up[0];
        uyy = up[1] * up[1];
        uzz = up[2] * up[2];
        uxy = up[0] * up[1];
        uxz = up[0] * up[2];
        uyz = up[1] * up[2];

        lxx = -left[0] * left[0];
        lyy = -left[1] * left[1];
        lzz = -left[2] * left[2];
        lxy = -left[0] * left[1];
        lxz = -left[0] * left[2];
        lyz = -left[1] * left[2];
        /* symmetric matrix */
        mtx[0][0] = fxx + uxx + lxx;
        mtx[0][1] = fxy + uxy + lxy;
        mtx[0][2] = fxz + uxz + lxz;
        mtx[1][0] = mtx[0][1];
        mtx[1][1] = fyy + uyy + lyy;
        mtx[1][2] = fyz + uyz + lyz;
        mtx[2][0] = mtx[0][2];
        mtx[2][1] = mtx[1][2];
        mtx[2][2] = fzz + uzz + lzz;
    }
    else /* the most common case, unless "from"="to", or "from"=-"to" */
    {
        /* ...otherwise use this hand optimized version (9 mults less) */
        double hvx, hvz, hvxy, hvxz, hvyz;
        h = (1.0 - e) / __LX_MATRIX_DOT(v, v);
        hvx = h * v[0];
        hvz = h * v[2];
        hvxy = hvx * v[1];
        hvxz = hvx * v[2];
        hvyz = hvz * v[1];
        mtx[0][0] = e + hvx * v[0];
        mtx[0][1] = hvxy - v[2];
        mtx[0][2] = hvxz + v[1];
        mtx[1][0] = hvxy + v[2];
        mtx[1][1] = e + h * v[1] * v[1];
        mtx[1][2] = hvyz - v[0];
        mtx[2][0] = hvxz - v[1];
        mtx[2][1] = hvyz + v[0];
        mtx[2][2] = e + hvz * v[2];
    }
}

void GetRotMatrixNormVec(double *out, const double *inVec, double radians)
{
    /* This function contributed by Erich Boleyn (erich@uruk.org) */
    /* This function used from the Mesa OpenGL code (matrix.c)  */
    double s, c;
    double vx, vy, vz, xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

    s = sin(radians);
    c = cos(radians);

    vx = inVec[0];
    vy = inVec[1];
    vz = inVec[2];

#define M(row, col) out[row * 3 + col]
    /*
     *     Arbitrary axis rotation matrix.
     *
     *  This is composed of 5 matrices, Rz, Ry, T, Ry', Rz', multiplied
     *  like so:  Rz * Ry * T * Ry' * Rz'.  T is the final rotation
     *  (which is about the X-axis), and the two composite transforms
     *  Ry' * Rz' and Rz * Ry are (respectively) the rotations necessary
     *  from the arbitrary axis to the X-axis then back.  They are
     *  all elementary rotations.
     *
     *  Rz' is a rotation about the Z-axis, to bring the axis vector
     *  into the x-z plane.  Then Ry' is applied, rotating about the
     *  Y-axis to bring the axis vector parallel with the X-axis.  The
     *  rotation about the X-axis is then performed.  Ry and Rz are
     *  simply the respective inverse transforms to bring the arbitrary
     *  axis back to its original orientation.  The first transforms
     *  Rz' and Ry' are considered inverses, since the data from the
     *  arbitrary axis gives you info on how to get to it, not how
     *  to get away from it, and an inverse must be applied.
     *
     *  The basic calculation used is to recognize that the arbitrary
     *  axis vector (x, y, z), since it is of unit length, actually
     *  represents the sines and cosines of the angles to rotate the
     *  X-axis to the same orientation, with theta being the angle about
     *  Z and phi the angle about Y (in the order described above)
     *  as follows:
     *
     *  cos ( theta ) = x / sqrt ( 1 - z^2 )
     *  sin ( theta ) = y / sqrt ( 1 - z^2 )
     *
     *  cos ( phi ) = sqrt ( 1 - z^2 )
     *  sin ( phi ) = z
     *
     *  Note that cos ( phi ) can further be inserted to the above
     *  formulas:
     *
     *  cos ( theta ) = x / cos ( phi )
     *  sin ( theta ) = y / cos ( phi )
     *
     *  ...etc.  Because of those relations and the standard trigonometric
     *  relations, it is pssible to reduce the transforms down to what
     *  is used below.  It may be that any primary axis chosen will give the
     *  same results (modulo a sign convention) using thie method.
     *
     *  Particularly nice is to notice that all divisions that might
     *  have caused trouble when parallel to certain planes or
     *  axis go away with care paid to reducing the expressions.
     *  After checking, it does perform correctly under all cases, since
     *  in all the cases of division where the denominator would have
     *  been zero, the numerator would have been zero as well, giving
     *  the expected result.
     */

    xx = vx * vx;
    yy = vy * vy;
    zz = vz * vz;
    xy = vx * vy;
    yz = vy * vz;
    zx = vz * vx;
    xs = vx * s;
    ys = vy * s;
    zs = vz * s;
    one_c = 1.0 - c;

    M(0, 0) = (one_c * xx) + c;
    M(1, 0) = (one_c * xy) - zs;
    M(2, 0) = (one_c * zx) + ys;

    M(0, 1) = (one_c * xy) + zs;
    M(1, 1) = (one_c * yy) + c;
    M(2, 1) = (one_c * yz) - xs;

    M(0, 2) = (one_c * zx) - ys;
    M(1, 2) = (one_c * yz) + xs;
    M(2, 2) = (one_c * zz) + c;

#undef M
}
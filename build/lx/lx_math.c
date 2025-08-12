#include "lx_math.h"

int64_t lx_math_next_pow2(int64_t n)
{
    if (n <= 0)
        return 1;
    if (n >= 0x3FFFFFFFFFFFFFFFll)
        return n;
    --n;
    int64_t shift = 1;
    while (shift < 63)
    {
        n |= n >> shift;
        shift <<= 1;
    }
    return n + 1;
}

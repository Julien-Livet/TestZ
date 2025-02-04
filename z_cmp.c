#include "z_cmp.h"

int z_cmp_uc(z_t lhs, unsigned char rhs)
{
    z_t other = z_from_uc(rhs);

    int cmp = z_cmp_z(lhs, other);

    z_free(&other);

    return cmp;
}

int z_cmp_ui(z_t lhs, unsigned int rhs)
{
    z_t other = z_from_ui(rhs);

    int cmp = z_cmp_z(lhs, other);

    z_free(&other);

    return cmp;
}

int z_cmp_ul(z_t lhs, unsigned long rhs)
{
    z_t other = z_from_ul(rhs);

    int cmp = z_cmp_z(lhs, other);

    z_free(&other);

    return cmp;
}

int z_cmp_ull(z_t lhs, unsigned long long rhs)
{
    z_t other = z_from_ull(rhs);

    int cmp = z_cmp_z(lhs, other);

    z_free(&other);

    return cmp;
}

int z_cmp_us(z_t lhs, unsigned short rhs)
{
    z_t other = z_from_us(rhs);

    int cmp = z_cmp_z(lhs, other);

    z_free(&other);

    return cmp;
}

int z_cmp_c(z_t lhs, char rhs)
{
    z_t other = z_from_c(rhs);

    int cmp = z_cmp_z(lhs, other);

    z_free(&other);

    return cmp;
}

int z_cmp_i(z_t lhs, int rhs)
{
    z_t other = z_from_i(rhs);

    int cmp = z_cmp_z(lhs, other);

    z_free(&other);

    return cmp;
}

int z_cmp_l(z_t lhs, long rhs)
{
    z_t other = z_from_l(rhs);

    int cmp = z_cmp_z(lhs, other);

    z_free(&other);

    return cmp;
}

int z_cmp_ll(z_t lhs, long long rhs)
{
    z_t other = z_from_ll(rhs);

    int cmp = z_cmp_z(lhs, other);

    z_free(&other);

    return cmp;
}

int z_cmp_s(z_t lhs, short rhs)
{
    z_t other = z_from_s(rhs);

    int cmp = z_cmp_z(lhs, other);

    z_free(&other);

    return cmp;
}

int z_cmp_z(z_t lhs, z_t rhs)
{
    if (z_is_nan(lhs) && z_is_nan(rhs))
        return 0;
    else if (z_is_nan(lhs) || z_is_nan(rhs))
        return 2;
    else if (z_is_infinity(rhs))
    {
        if (z_is_infinity(lhs))
        {
            if (z_is_positive(rhs) == z_is_positive(lhs))
                return 0;
            else if (z_is_positive(rhs) && !z_is_positive(lhs))
                return -1;
            else
                return 1;
        }
        else if (z_is_positive(rhs))
            return -1;
        else
            return 1;
    }
    else if (z_is_infinity(lhs))
    {
        if (z_is_infinity(rhs))
        {
            if (z_is_positive(rhs) == z_is_positive(lhs))
                return 0;
            else if (z_is_positive(lhs) && !z_is_positive(rhs))
                return 1;
            else
                return -1;
        }
        else if (z_is_positive(lhs))
            return 1;
        else
            return -1;
    }

    if (lhs.size != rhs.size)
    {
        if (lhs.size > rhs.size)
        {
            for (size_t i = 0; i < lhs.size - rhs.size; ++i)
            {
                if (lhs.bits[i])
                    return z_is_positive(lhs);
            }
        }
        else
        {
            for (size_t i = 0; i < rhs.size - lhs.size; ++i)
            {
                if (rhs.bits[i])
                    return -z_is_positive(rhs);
            }
        }
    }

    size_t i1 = lhs.size - MIN(lhs.size, rhs.size);
    size_t i2 = rhs.size - MIN(lhs.size, rhs.size);

    for (size_t i = 0; i < MIN(lhs.size, rhs.size); ++i)
    {
        if (z_is_positive(lhs) && z_is_positive(rhs))
        {
            if (lhs.bits[i1] > rhs.bits[i2])
                return 1;
            else if (lhs.bits[i1] < rhs.bits[i2])
                return -1;
        }
        else if (!z_is_positive(lhs) && !z_is_positive(rhs))
        {
            if (lhs.bits[i1] > rhs.bits[i2])
                return -1;
            else if (lhs.bits[i1] < rhs.bits[i2])
                return 1;
        }
        else if (z_is_positive(lhs) && !z_is_positive(rhs))
        {
            if (lhs.bits[i1] != rhs.bits[i2])
                return 1;
        }
        else if (!z_is_positive(lhs) && z_is_positive(rhs))
        {
            if (lhs.bits[i1] != rhs.bits[i2])
                return -1;
        }

        ++i1;
        ++i2;
    }

    return 0;
}

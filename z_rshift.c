#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "z_rshift.h"

void z_rshift_uc(z_t* lhs, unsigned char rhs)
{
    assert(lhs);

    z_t other = z_from_uc(rhs);

    z_rshift_z(lhs, other);

    z_free(&other);
}

void z_rshift_ui(z_t* lhs, unsigned int rhs)
{
    assert(lhs);

    z_t other = z_from_ui(rhs);

    z_rshift_z(lhs, other);

    z_free(&other);
}

void z_rshift_ul(z_t* lhs, unsigned long rhs)
{
    assert(lhs);

    z_t other = z_from_ul(rhs);

    z_rshift_z(lhs, other);

    z_free(&other);
}

void z_rshift_ull(z_t* lhs, unsigned long long rhs)
{
    assert(lhs);

    z_t other = z_from_ull(rhs);

    z_rshift_z(lhs, other);

    z_free(&other);
}

void z_rshift_us(z_t* lhs, unsigned short rhs)
{
    assert(lhs);

    z_t other = z_from_us(rhs);

    z_rshift_z(lhs, other);

    z_free(&other);
}

void z_rshift_c(z_t* lhs, char rhs)
{
    assert(lhs);

    z_t other = z_from_c(rhs);

    z_rshift_z(lhs, other);

    z_free(&other);
}

void z_rshift_i(z_t* lhs, int rhs)
{
    assert(lhs);

    z_t other = z_from_i(rhs);

    z_rshift_z(lhs, other);

    z_free(&other);
}

void z_rshift_l(z_t* lhs, long rhs)
{
    assert(lhs);

    z_t other = z_from_l(rhs);

    z_rshift_z(lhs, other);

    z_free(&other);
}

void z_rshift_ll(z_t* lhs, long long rhs)
{
    assert(lhs);

    z_t other = z_from_ll(rhs);

    z_rshift_z(lhs, other);

    z_free(&other);
}

void z_rshift_s(z_t* lhs, short rhs)
{
    assert(lhs);

    z_t other = z_from_s(rhs);

    z_rshift_z(lhs, other);

    z_free(&other);
}

void z_rshift_z(z_t* lhs, z_t rhs)
{
    assert(lhs);

    assert(z_cmp_c(rhs, 0) >= 0);

    if (!z_cmp_c(*lhs, 0) || !z_cmp_c(rhs, 0))
        return;
    else if (z_is_nan(*lhs) || z_is_nan(rhs) || z_is_infinity(*lhs))
    {
        z_set_nan(lhs);

        return;
    }
    else if (z_is_infinity(rhs))
    {
        if (z_is_negative(rhs))
            z_set_nan(lhs);
        else
            z_set_from_c(lhs, 0);

        return;
    }

    unsigned short const us = sizeof(z_type) * 8;
    z_t n = z_div_q_us(rhs, us);

    if (lhs->size < z_to_ull(n))
    {
        z_set_from_c(lhs, 0);

        z_free(&n);

        return;
    }

    {
        z_type* bits = malloc((lhs->size - z_to_ull(n)) * sizeof(z_type));
        memcpy(bits, lhs->bits, (lhs->size - z_to_ull(n)) * sizeof(z_type));
        free(lhs->bits);
        lhs->bits = bits;
        lhs->size -= z_to_ull(n);
    }

    z_t other = z_copy(rhs);
    z_t nTmp = z_copy(n);
    z_mul_us(&nTmp, us);
    z_sub_z(&other, nTmp);
    z_free(&nTmp);

    unsigned long long const shift = z_to_ull(other);

    if (shift)
    {
        for (size_t i = 0; i < lhs->size; ++i)
        {
            size_t j = lhs->size - 1 - i;

            lhs->bits[j] >>= shift;

            longest_type one = 1;

            if (j && (lhs->bits[j - 1] & ((one << shift) - 1)))
                lhs->bits[j] |= (lhs->bits[j - 1] & ((one << shift) - 1)) << (sizeof(z_type) * 8 - shift);
        }
    }

    if (!lhs->size)
        z_set_from_c(lhs, 0);

    z_free(&n);
    z_free(&other);

    if (z_is_auto_adjust(*lhs))
        z_adjust(lhs);
}

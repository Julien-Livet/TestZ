#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "z_xor.h"

void z_xor_uc(z_t* lhs, unsigned char rhs)
{
    assert(lhs);

    z_t other = z_from_uc(rhs);

    z_xor_z(lhs, other);

    z_free(&other);
}

void z_xor_ui(z_t* lhs, unsigned int rhs)
{
    assert(lhs);

    z_t other = z_from_ui(rhs);

    z_xor_z(lhs, other);

    z_free(&other);
}

void z_xor_ul(z_t* lhs, unsigned long rhs)
{
    assert(lhs);

    z_t other = z_from_ul(rhs);

    z_xor_z(lhs, other);

    z_free(&other);
}

void z_xor_ull(z_t* lhs, unsigned long long rhs)
{
    assert(lhs);

    z_t other = z_from_ull(rhs);

    z_xor_z(lhs, other);

    z_free(&other);
}

void z_xor_us(z_t* lhs, unsigned short rhs)
{
    assert(lhs);

    z_t other = z_from_us(rhs);

    z_xor_z(lhs, other);

    z_free(&other);
}

void z_xor_c(z_t* lhs, char rhs)
{
    assert(lhs);

    z_t other = z_from_c(rhs);

    z_xor_z(lhs, other);

    z_free(&other);
}

void z_xor_i(z_t* lhs, int rhs)
{
    assert(lhs);

    z_t other = z_from_i(rhs);

    z_xor_z(lhs, other);

    z_free(&other);
}

void z_xor_l(z_t* lhs, long rhs)
{
    assert(lhs);

    z_t other = z_from_l(rhs);

    z_xor_z(lhs, other);

    z_free(&other);
}

void z_xor_ll(z_t* lhs, long long rhs)
{
    assert(lhs);

    z_t other = z_from_ll(rhs);

    z_xor_z(lhs, other);

    z_free(&other);
}

void z_xor_s(z_t* lhs, short rhs)
{
    assert(lhs);

    z_t other = z_from_s(rhs);

    z_xor_z(lhs, other);

    z_free(&other);
}

void z_xor_z(z_t* lhs, z_t rhs)
{
    assert(lhs);

    if (lhs->size < rhs.size)
    {
        z_type* bits = lhs->bits;
        lhs->bits = malloc(rhs.size * sizeof(z_type));
        memset(lhs->bits, 0, (rhs.size - lhs->size) * sizeof(z_type));
        memcpy((void*)(lhs->bits) + (rhs.size - lhs->size) * sizeof(z_type), bits, lhs->size * sizeof(z_type));
        lhs->size = rhs.size;
        free(bits);
    }
    else if (lhs->size > rhs.size)
    {
        for (size_t i = 0; i < lhs->size - rhs.size; ++i)
            lhs->bits[i] ^= 0;
    }

    for (size_t i = 0; i < MIN(lhs->size, rhs.size); ++i)
        lhs->bits[lhs->size - 1 - i] ^= rhs.bits[rhs.size - 1 - i];

    if (z_is_auto_adjust(*lhs))
        z_adjust(lhs);
}

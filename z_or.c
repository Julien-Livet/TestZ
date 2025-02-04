#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "z_or.h"

void z_or_uc(z_t* lhs, unsigned char rhs)
{
    assert(lhs);

    z_t other = z_from_uc(rhs);

    z_or_z(lhs, other);

    z_free(&other);
}

void z_or_ui(z_t* lhs, unsigned int rhs)
{
    assert(lhs);

    z_t other = z_from_ui(rhs);

    z_or_z(lhs, other);

    z_free(&other);
}

void z_or_ul(z_t* lhs, unsigned long rhs)
{
    assert(lhs);

    z_t other = z_from_ul(rhs);

    z_or_z(lhs, other);

    z_free(&other);
}

void z_or_ull(z_t* lhs, unsigned long long rhs)
{
    assert(lhs);

    z_t other = z_from_ull(rhs);

    z_or_z(lhs, other);

    z_free(&other);
}

void z_or_us(z_t* lhs, unsigned short rhs)
{
    assert(lhs);

    z_t other = z_from_us(rhs);

    z_or_z(lhs, other);

    z_free(&other);
}

void z_or_c(z_t* lhs, char rhs)
{
    assert(lhs);

    z_t other = z_from_c(rhs);

    z_or_z(lhs, other);

    z_free(&other);
}

void z_or_i(z_t* lhs, int rhs)
{
    assert(lhs);

    z_t other = z_from_i(rhs);

    z_or_z(lhs, other);

    z_free(&other);
}

void z_or_l(z_t* lhs, long rhs)
{
    assert(lhs);

    z_t other = z_from_l(rhs);

    z_or_z(lhs, other);

    z_free(&other);
}

void z_or_ll(z_t* lhs, long long rhs)
{
    assert(lhs);

    z_t other = z_from_ll(rhs);

    z_or_z(lhs, other);

    z_free(&other);
}

void z_or_s(z_t* lhs, short rhs)
{
    assert(lhs);

    z_t other = z_from_s(rhs);

    z_or_z(lhs, other);

    z_free(&other);
}

void z_or_z(z_t* lhs, z_t rhs)
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

    for (size_t i = 0; i < MIN(lhs->size, rhs.size); ++i)
        lhs->bits[lhs->size - 1 - i] |= rhs.bits[rhs.size - 1 - i];

    if (z_is_auto_adjust(*lhs))
        z_adjust(lhs);
}

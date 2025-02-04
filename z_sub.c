#include <assert.h>

#include "z_sub.h"

void z_sub_uc(z_t* lhs, unsigned char rhs)
{
    assert(lhs);

    z_t other = z_from_uc(rhs);

    z_sub_z(lhs, other);

    z_free(&other);
}

void z_sub_ui(z_t* lhs, unsigned int rhs)
{
    assert(lhs);

    z_t other = z_from_ui(rhs);

    z_sub_z(lhs, other);

    z_free(&other);
}

void z_sub_ul(z_t* lhs, unsigned long rhs)
{
    assert(lhs);

    z_t other = z_from_ul(rhs);

    z_sub_z(lhs, other);

    z_free(&other);
}

void z_sub_ull(z_t* lhs, unsigned long long rhs)
{
    assert(lhs);

    z_t other = z_from_ull(rhs);

    z_sub_z(lhs, other);

    z_free(&other);
}

void z_sub_us(z_t* lhs, unsigned short rhs)
{
    assert(lhs);

    z_t other = z_from_us(rhs);

    z_sub_z(lhs, other);

    z_free(&other);
}

void z_sub_c(z_t* lhs, char rhs)
{
    assert(lhs);

    z_t other = z_from_c(rhs);

    z_sub_z(lhs, other);

    z_free(&other);
}

void z_sub_i(z_t* lhs, int rhs)
{
    assert(lhs);

    z_t other = z_from_i(rhs);

    z_sub_z(lhs, other);

    z_free(&other);
}

void z_sub_l(z_t* lhs, long rhs)
{
    assert(lhs);

    z_t other = z_from_l(rhs);

    z_sub_z(lhs, other);

    z_free(&other);
}

void z_sub_ll(z_t* lhs, long long rhs)
{
    assert(lhs);

    z_t other = z_from_ll(rhs);

    z_sub_z(lhs, other);

    z_free(&other);
}

void z_sub_s(z_t* lhs, short rhs)
{
    assert(lhs);

    z_t other = z_from_s(rhs);

    z_sub_z(lhs, other);

    z_free(&other);
}

void z_sub_z(z_t* lhs, z_t rhs)
{
    assert(lhs);

    z_t other = z_copy(rhs);
    z_neg(&other);

    z_add_z(lhs, other);

    z_free(&other);
}

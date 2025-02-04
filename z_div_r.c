#include <stdlib.h>

#include "z_div_r.h"

z_t z_div_r_uc(z_t lhs, unsigned char rhs)
{
    z_t other = z_from_uc(rhs);

    z_t r = z_div_r_z(lhs, other);

    z_free(&other);

    return r;
}

z_t z_div_r_ui(z_t lhs, unsigned int rhs)
{
    z_t other = z_from_ui(rhs);

    z_t r = z_div_r_z(lhs, other);

    z_free(&other);

    return r;
}

z_t z_div_r_ul(z_t lhs, unsigned long rhs)
{
    z_t other = z_from_ul(rhs);

    z_t r = z_div_r_z(lhs, other);

    z_free(&other);

    return r;
}

z_t z_div_r_ull(z_t lhs, unsigned long long rhs)
{
    z_t other = z_from_ull(rhs);

    z_t r = z_div_r_z(lhs, other);

    z_free(&other);

    return r;
}

z_t z_div_r_us(z_t lhs, unsigned short rhs)
{
    z_t other = z_from_us(rhs);

    z_t r = z_div_r_z(lhs, other);

    z_free(&other);

    return r;
}

z_t z_div_r_c(z_t lhs, char rhs)
{
    z_t other = z_from_c(rhs);

    z_t r = z_div_r_z(lhs, other);

    z_free(&other);

    return r;
}

z_t z_div_r_i(z_t lhs, int rhs)
{
    z_t other = z_from_i(rhs);

    z_t r = z_div_r_z(lhs, other);

    z_free(&other);

    return r;
}

z_t z_div_r_l(z_t lhs, long rhs)
{
    z_t other = z_from_l(rhs);

    z_t r = z_div_r_z(lhs, other);

    z_free(&other);

    return r;
}

z_t z_div_r_ll(z_t lhs, long long rhs)
{
    z_t other = z_from_ll(rhs);

    z_t r = z_div_r_z(lhs, other);

    z_free(&other);

    return r;
}

z_t z_div_r_s(z_t lhs, short rhs)
{
    z_t other = z_from_s(rhs);

    z_t r = z_div_r_z(lhs, other);

    z_free(&other);

    return r;
}

z_t z_div_r_z(z_t lhs, z_t rhs)
{
    z_t q = z_from_c(0);
    z_t r = z_from_c(0);

    z_div_qr_z(lhs, rhs, &q, &r);

    z_free(&q);

    return r;
}

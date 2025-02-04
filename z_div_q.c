#include "z_div_q.h"

z_t z_div_q_uc(z_t lhs, unsigned char rhs)
{
    z_t other = z_from_uc(rhs);

    z_t q = z_div_q_z(lhs, other);

    z_free(&other);

    return q;
}

z_t z_div_q_ui(z_t lhs, unsigned int rhs)
{
    z_t other = z_from_ui(rhs);

    z_t q = z_div_q_z(lhs, other);

    z_free(&other);

    return q;
}

z_t z_div_q_ul(z_t lhs, unsigned long rhs)
{
    z_t other = z_from_ul(rhs);

    z_t q = z_div_q_z(lhs, other);

    z_free(&other);

    return q;
}

z_t z_div_q_ull(z_t lhs, unsigned long long rhs)
{
    z_t other = z_from_ull(rhs);

    z_t q = z_div_q_z(lhs, other);

    z_free(&other);

    return q;
}

z_t z_div_q_us(z_t lhs, unsigned short rhs)
{
    z_t other = z_from_us(rhs);

    z_t q = z_div_q_z(lhs, other);

    z_free(&other);

    return q;
}

z_t z_div_q_c(z_t lhs, char rhs)
{
    z_t other = z_from_c(rhs);

    z_t q = z_div_q_z(lhs, other);

    z_free(&other);

    return q;
}

z_t z_div_q_i(z_t lhs, int rhs)
{
    z_t other = z_from_i(rhs);

    z_t q = z_div_q_z(lhs, other);

    z_free(&other);

    return q;
}

z_t z_div_q_l(z_t lhs, long rhs)
{
    z_t other = z_from_l(rhs);

    z_t q = z_div_q_z(lhs, other);

    z_free(&other);

    return q;
}

z_t z_div_q_ll(z_t lhs, long long rhs)
{
    z_t other = z_from_ll(rhs);

    z_t q = z_div_q_z(lhs, other);

    z_free(&other);

    return q;
}

z_t z_div_q_s(z_t lhs, short rhs)
{
    z_t other = z_from_s(rhs);

    z_t q = z_div_q_z(lhs, other);

    z_free(&other);

    return q;
}

z_t z_div_q_z(z_t lhs, z_t rhs)
{
    z_t q = z_from_c(0);
    z_t r = z_from_c(0);

    z_div_qr_z(lhs, rhs, &q, &r);

    if (z_cmp_c(lhs, 0) < 0 && z_cmp_c(rhs, 0) < 0)
    {
        if (z_cmp_c(r, 0))
            z_sub_c(&q, 1);
    }
    else if (z_cmp_c(lhs, 0) > 0 && z_cmp_c(rhs, 0) < 0)
    {
        if (z_cmp_c(r, 0))
            z_add_c(&q, 1);
    }
    else if (z_cmp_c(lhs, 0) < 0 && z_cmp_c(rhs, 0) > 0)
    {
        if (z_cmp_c(r, 0))
            z_add_c(&q, 1);
    }

    z_free(&r);

    return q;
}

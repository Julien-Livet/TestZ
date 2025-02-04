#include "z_fits.h"

bool z_fits_c(z_t z)
{
    char c = z_to_c(z);

    return !z_cmp_c(z, c);
}

bool z_fits_i(z_t z)
{
    int i = z_to_i(z);

    return !z_cmp_i(z, i);
}

bool z_fits_l(z_t z)
{
    long l = z_to_l(z);

    return !z_cmp_l(z, l);
}

bool z_fits_ll(z_t z)
{
    long ll = z_to_ll(z);

    return !z_cmp_ll(z, ll);
}

bool z_fits_s(z_t z)
{
    short s = z_to_s(z);

    return !z_cmp_s(z, s);
}

bool z_fits_uc(z_t z)
{
    unsigned char uc = z_to_uc(z);

    return !z_cmp_uc(z, uc);
}

bool z_fits_ui(z_t z)
{
    unsigned int ui = z_to_ui(z);

    return !z_cmp_ui(z, ui);
}

bool z_fits_ul(z_t z)
{
    unsigned long ul = z_to_ul(z);

    return !z_cmp_ul(z, ul);
}

bool z_fits_ull(z_t z)
{
    unsigned long long ull = z_to_ull(z);

    return !z_cmp_ull(z, ull);
}

bool z_fits_us(z_t z)
{
    unsigned short us = z_to_us(z);

    return !z_cmp_us(z, us);
}

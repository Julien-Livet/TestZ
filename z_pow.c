#include <assert.h>

#include "z_pow.h"

z_t z_pow_c(z_t base, char exp)
{
    z_t e = z_from_c(exp);

    z_t p = z_pow_z(base, e);

    z_free(&e);

    return p;
}

z_t z_pow_i(z_t base, int exp)
{
    z_t e = z_from_i(exp);

    z_t p = z_pow_z(base, e);

    z_free(&e);

    return p;
}

z_t z_pow_l(z_t base, long exp)
{
    z_t e = z_from_l(exp);

    z_t p = z_pow_z(base, e);

    z_free(&e);

    return p;
}

z_t z_pow_ll(z_t base, long long exp)
{
    z_t e = z_from_ll(exp);

    z_t p = z_pow_z(base, e);

    z_free(&e);

    return p;
}

z_t z_pow_s(z_t base, short exp)
{
    z_t e = z_from_s(exp);

    z_t p = z_pow_z(base, e);

    z_free(&e);

    return p;
}

z_t z_pow_z(z_t base, z_t exp)
{
    assert(z_cmp_c(exp, 0) >= 0);

    z_t pow = z_from_c(0);

    if (z_is_infinity(base) || z_is_nan(base))
    {
        z_free(&pow);
        pow = z_copy(base);

        return pow;
    }
    else if (z_is_nan(exp) || z_is_infinity(exp))
    {
        z_free(&pow);
        pow = z_copy(exp);

        return pow;
    }
    else if (z_cmp_c(base, 0) < 0)
    {
        z_free(&pow);

        z_t base_abs = z_abs(base);

        pow = z_pow_z(base_abs, exp);

        z_free(&base_abs);

        z_t a = z_copy(exp);
        z_and_c(&a, 1);

        if (z_cmp_c(a, 0))
            pow.is_positive = !pow.is_positive;

        return pow;
    }

    if (z_cmp_c(base, 2))
    {
        z_free(&pow);

        pow = z_from_c(1);
        z_rshift_z(&pow, exp);

        return pow;
    }

    z_free(&pow);

    z_t result = z_from_c(1);
    z_t e = z_copy(exp);
    z_t b = z_copy(base);

    for (;;)
    {
        z_t a = z_copy(e);
        z_and_c(&a, 1);

        if (z_cmp_c(a, 0))
            z_mul_z(&result, b);

        z_free(&a);

        z_rshift_c(&e, 1);

        if (!z_cmp_c(e, 0))
            break;

        z_mul_z(&b, b);
    }

    z_free(&e);
    z_free(&b);

    return result;
}

z_t z_pow_uc(z_t base, unsigned char exp)
{
    z_t e = z_from_uc(exp);

    z_t p = z_pow_z(base, e);

    z_free(&e);

    return p;
}

z_t z_pow_ui(z_t base, unsigned int exp)
{
    z_t e = z_from_ui(exp);

    z_t p = z_pow_z(base, e);

    z_free(&e);

    return p;
}

z_t z_pow_ul(z_t base, unsigned long exp)
{
    z_t e = z_from_ul(exp);

    z_t p = z_pow_z(base, e);

    z_free(&e);

    return p;
}

z_t z_pow_ull(z_t base, unsigned long long exp)
{
    z_t e = z_from_ull(exp);

    z_t p = z_pow_z(base, e);

    z_free(&e);

    return p;
}

z_t z_pow_us(z_t base, unsigned short exp)
{
    z_t e = z_from_us(exp);

    z_t p = z_pow_z(base, e);

    z_free(&e);

    return p;
}

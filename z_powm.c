#include <assert.h>

#include "z_powm.h"

z_t z_powm_c(z_t base, char exp, char mod)
{
    z_t e = z_from_c(exp);
    z_t m = z_from_c(mod);

    z_t p = z_powm_z(base, e, m);

    z_free(&e);
    z_free(&m);

    return p;
}

z_t z_powm_i(z_t base, int exp, int mod)
{
    z_t e = z_from_i(exp);
    z_t m = z_from_i(mod);

    z_t p = z_powm_z(base, e, m);

    z_free(&e);
    z_free(&m);

    return p;
}

z_t z_powm_l(z_t base, long exp, long mod)
{
    z_t e = z_from_l(exp);
    z_t m = z_from_l(mod);

    z_t p = z_powm_z(base, e, m);

    z_free(&e);
    z_free(&m);

    return p;
}

z_t z_powm_ll(z_t base, long long exp, long long mod)
{
    z_t e = z_from_ll(exp);
    z_t m = z_from_ll(mod);

    z_t p = z_powm_z(base, e, m);

    z_free(&e);
    z_free(&m);

    return p;
}

z_t z_powm_s(z_t base, short exp, short mod)
{
    z_t e = z_from_s(exp);
    z_t m = z_from_s(mod);

    z_t p = z_powm_z(base, e, m);

    z_free(&e);
    z_free(&m);

    return p;
}

z_t z_powm_z(z_t base, z_t exp, z_t mod)
{
    assert(z_cmp_c(exp, 0) >= 0);

    z_t result = z_from_c(1);
    z_t base_mod = z_div_r_z(base, mod);
    z_t e = z_copy(exp);

    while (z_cmp_c(exp, 0) > 0)
    {
        z_t a = z_copy(e);
        z_and_c(&a, 1);

        if (!z_cmp_c(a, 1))
        {
            z_mul_z(&result, base_mod);

            z_t r = z_div_r_z(result, mod);

            z_free(&result);
            result = r;
        }

        z_free(&a);

        z_mul_z(&base_mod, base_mod);

        z_t r = z_div_r_z(base_mod, mod);

        z_free(&base_mod);
        base_mod = r;

        z_rshift_c(&e, 1);
    }

    z_free(&base_mod);
    z_free(&e);

    return result;
}

z_t z_powm_uc(z_t base, unsigned char exp, unsigned char mod)
{
    z_t e = z_from_uc(exp);
    z_t m = z_from_uc(mod);

    z_t p = z_powm_z(base, e, m);

    z_free(&e);
    z_free(&m);

    return p;
}

z_t z_powm_ui(z_t base, unsigned int exp, unsigned int mod)
{
    z_t e = z_from_ui(exp);
    z_t m = z_from_ui(mod);

    z_t p = z_powm_z(base, e, m);

    z_free(&e);
    z_free(&m);

    return p;
}

z_t z_powm_ul(z_t base, unsigned long exp, unsigned long mod)
{
    z_t e = z_from_ul(exp);
    z_t m = z_from_ul(mod);

    z_t p = z_powm_z(base, e, m);

    z_free(&e);
    z_free(&m);

    return p;
}

z_t z_powm_ull(z_t base, unsigned long long exp, unsigned long long mod)
{
    z_t e = z_from_ull(exp);
    z_t m = z_from_ull(mod);

    z_t p = z_powm_z(base, e, m);

    z_free(&e);
    z_free(&m);

    return p;
}

z_t z_powm_us(z_t base, unsigned short exp, unsigned short mod)
{
    z_t e = z_from_us(exp);
    z_t m = z_from_us(mod);

    z_t p = z_powm_z(base, e, m);

    z_free(&e);
    z_free(&m);

    return p;
}

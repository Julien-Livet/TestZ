#include <assert.h>
#include <stdlib.h>

#include "z_div_qr.h"

void z_div_qr_uc(z_t lhs, unsigned char rhs, z_t* q, z_t* r)
{
    assert(q && r);

    z_t other = z_from_uc(rhs);

    z_div_qr_z(lhs, other, q, r);

    z_free(&other);
}

void z_div_qr_ui(z_t lhs, unsigned int rhs, z_t* q, z_t* r)
{
    assert(q && r);

    z_t other = z_from_ui(rhs);

    z_div_qr_z(lhs, other, q, r);

    z_free(&other);
}

void z_div_qr_ul(z_t lhs, unsigned long rhs, z_t* q, z_t* r)
{
    assert(q && r);

    z_t other = z_from_ul(rhs);

    z_div_qr_z(lhs, other, q, r);

    z_free(&other);
}

void z_div_qr_ull(z_t lhs, unsigned long long rhs, z_t* q, z_t* r)
{
    assert(q && r);

    z_t other = z_from_ull(rhs);

    z_div_qr_z(lhs, other, q, r);

    z_free(&other);
}

void z_div_qr_us(z_t lhs, unsigned short rhs, z_t* q, z_t* r)
{
    assert(q && r);

    z_t other = z_from_us(rhs);

    z_div_qr_z(lhs, other, q, r);

    z_free(&other);
}

void z_div_qr_c(z_t lhs, char rhs, z_t* q, z_t* r)
{
    assert(q && r);

    z_t other = z_from_c(rhs);

    z_div_qr_z(lhs, other, q, r);

    z_free(&other);
}

void z_div_qr_i(z_t lhs, int rhs, z_t* q, z_t* r)
{
    assert(q && r);

    z_t other = z_from_i(rhs);

    z_div_qr_z(lhs, other, q, r);

    z_free(&other);
}

void z_div_qr_l(z_t lhs, long rhs, z_t* q, z_t* r)
{
    assert(q && r);

    z_t other = z_from_l(rhs);

    z_div_qr_z(lhs, other, q, r);

    z_free(&other);
}

void z_div_qr_ll(z_t lhs, long long rhs, z_t* q, z_t* r)
{
    assert(q && r);

    z_t other = z_from_ll(rhs);

    z_div_qr_z(lhs, other, q, r);

    z_free(&other);
}

void z_div_qr_s(z_t lhs, short rhs, z_t* q, z_t* r)
{
    assert(q && r);

    z_t other = z_from_s(rhs);

    z_div_qr_z(lhs, other, q, r);

    z_free(&other);
}

void inner1(z_t* a_digits, z_t x, z_t L, z_t R, z_t n)
{
    z_t l = z_copy(L);
    z_add_c(&l, 1);

    if (!z_cmp_z(l, R))
    {
        z_free(&a_digits[z_to_ull(L)]);
        a_digits[z_to_ull(L)] = z_copy(x);

        z_free(&l);

        return;
    }

    z_free(&l);

    z_t mid = z_copy(L);
    z_add_z(&mid, R);
    z_rshift_c(&mid, 1);

    z_t shift = z_copy(mid);
    z_sub_z(&shift, L);
    z_mul_z(&shift, n);

    z_t upper = z_copy(x);
    z_rshift_z(&upper, shift);

    z_t lower = z_copy(upper);
    z_lshift_z(&lower, shift);
    z_xor_z(&lower, x);

    inner1(a_digits, lower, L, mid, n);
    inner1(a_digits, upper, mid, R, n);

    z_free(&mid);
    z_free(&shift);
    z_free(&upper);
    z_free(&lower);
}

void _int2digits(z_t a, z_t n, z_t** a_digits, size_t* a_size)
{
    assert(a_digits && a_size);

    assert(z_cmp_c(a, 0) >= 0);

    z_t number = z_number(a);
    z_add_z(&number, n);
    z_sub_c(&number, 1);

    *a_size = z_to_ull(number) / z_to_ull(n);
    *a_digits = malloc(*a_size * sizeof(z_t));

    for (size_t i = 0; i < *a_size; ++i)
        (*a_digits)[i] = z_from_c(0);

    z_free(&number);

    if (z_cmp_c(a, 0))
    {
        z_t zero = z_from_c(0);
        z_t s = z_from_ull(*a_size);

        inner1(*a_digits, a, zero, s, n);

        z_free(&zero);
        z_free(&s);
    }
}

z_t inner2(z_t const* digits, z_t L, z_t R, z_t n)
{
    z_t l = z_copy(L);
    z_add_c(&l, 1);

    if (!z_cmp_z(l, R))
    {
        z_free(&l);

        return digits[z_to_ull(L)];
    }

    z_free(&l);

    z_t mid = z_copy(L);
    z_add_z(&mid, R);
    z_rshift_c(&mid, 1);

    z_t shift = z_copy(mid);
    z_sub_z(&shift, L);
    z_mul_z(&shift, n);

    z_t i1 = inner2(digits, mid, R, n);
    z_lshift_z(&i1, shift);
    z_t i2 = inner2(digits, L, mid, n);
    z_add_z(&i1, i2);

    z_free(&mid);
    z_free(&shift);
    z_free(&i2);

    return i1;
};

z_t _digits2int(z_t const* digits, z_t n, size_t digits_size)
{
    if (!digits_size)
        return z_from_c(0);

    z_t zero = z_from_c(0);
    z_t s = z_from_ull(digits_size);

    z_t i = inner2(digits, zero, s, n);

    z_free(&zero);
    z_free(&s);

    return i;
}

void _div3n2n(z_t a12, z_t a3, z_t b, z_t b1, z_t b2, z_t n, z_t* q, z_t* r);

void _div2n1n(z_t a, z_t b, z_t n, z_t* q, z_t* r)
{
    if (z_fits_ull(a) && z_fits_ull(b))
    {
        z_free(q);
        z_set_from_ull(q, z_to_ull(a) / z_to_ull(b));
        z_free(r);
        z_set_from_ull(r, z_to_ull(a) % z_to_ull(b));

        return;
    }

    z_t pad = z_copy(n);
    z_and_c(&pad, 1);

    z_t aTmp = z_copy(a);
    z_t bTmp = z_copy(b);
    z_t nTmp = z_copy(n);

    if (z_cmp_c(pad, 0))
    {
        z_lshift_c(&aTmp, 1);
        z_lshift_c(&bTmp, 1);
        z_add_c(&nTmp, 1);
    }

    z_t half_n = z_copy(nTmp);
    z_rshift_c(&half_n, 1);

    z_t mask = z_from_c(1);
    z_lshift_z(&mask, half_n);
    z_sub_c(&mask, 1);

    z_t b1 = z_copy(bTmp);
    z_rshift_z(&b1, half_n);

    z_t b2 = z_copy(bTmp);
    z_and_z(&b2, mask);

    z_t q1 = z_from_c(0);
    z_t q2 = z_from_c(0);

    z_t a1 = z_copy(aTmp);
    z_rshift_z(&a1, nTmp);

    z_t a2 = z_copy(aTmp);
    z_rshift_z(&a2, half_n);
    z_and_z(&a2, mask);

    z_t a3 = z_copy(aTmp);
    z_and_z(&a3, mask);

    _div3n2n(a1, a2, bTmp, b1, b2, half_n, &q1, r);
    _div3n2n(*r, a3, bTmp, b1, b2, half_n, &q2, r);

    if (z_cmp_c(pad, 0))
        z_rshift_c(r, 1);

    z_free(&pad);
    z_free(&aTmp);
    z_free(&bTmp);
    z_free(&nTmp);

    z_set_from_z(q, q1);
    z_lshift_z(q, half_n);
    z_or_z(q, q2);

    z_free(&half_n);
    z_free(&mask);
    z_free(&b1);
    z_free(&b2);
    z_free(&q1);
    z_free(&q2);
    z_free(&a1);
    z_free(&a2);
    z_free(&a3);
}

void _div3n2n(z_t a12, z_t a3, z_t b, z_t b1, z_t b2, z_t n, z_t* q, z_t* r)
{
    z_t a12Tmp = z_copy(a12);
    z_rshift_z(&a12Tmp, n);

    if (!z_cmp_z(a12Tmp, b1))
    {
        z_free(q);
        z_set_from_c(q, 1);
        z_lshift_z(q, n);
        z_sub_c(q, 1);

        z_free(r);
        z_set_from_z(r, b1);
        z_lshift_z(r, n);
        z_neg(r);
        z_add_z(r, a12);
        z_add_z(r, b1);
    }
    else
        _div2n1n(a12, b1, n, q, r);

    z_lshift_z(r, n);
    z_or_z(r, a3);

    z_t tmp = z_copy(*q);
    z_mul_z(&tmp, b2);
    z_sub_z(r, tmp);

    z_free(&tmp);

    while (z_cmp_c(*r, 0) < 0)
    {
        z_sub_c(q, 1);
        z_add_z(r, b);
    }
}

void z_div_qr_z(z_t lhs, z_t rhs, z_t* q, z_t* r)
{
    assert(q && r);

    if (!z_cmp_c(lhs, 0))
    {
        z_free(q);
        z_set_nan(q);
        z_free(r);
        z_set_nan(r);

        return;
    }
    else if (!z_cmp_c(rhs, 0))
    {
        z_free(q);
        z_set_from_c(q, 0);
        z_free(r);
        z_set_from_c(r, 0);

        return;
    }
    else if (z_is_nan(lhs))
    {
        z_free(q);
        *q = z_copy(lhs);
        z_free(r);
        *r = z_copy(lhs);

        return;
    }
    else if (z_is_nan(rhs))
    {
        z_free(q);
        *q = z_copy(rhs);
        z_free(r);
        *r = z_copy(rhs);

        return;
    }
    else if (z_is_infinity(lhs) || z_is_infinity(rhs))
    {
        z_free(q);
        z_set_nan(q);
        z_free(r);
        z_set_nan(r);

        return;
    }

    z_t lhs_abs = z_abs(lhs);
    z_t rhs_abs = z_abs(rhs);

    if (z_cmp_z(rhs_abs, lhs_abs) > 0)
    {
        z_free(q);
        z_set_from_c(q, 0);
        z_free(r);
        z_set_from_z(r, lhs);

        z_free(&lhs_abs);
        z_free(&rhs_abs);

        return;
    }
    else if (!z_cmp_c(rhs_abs, 1))
    {
        z_free(q);
        z_set_from_z(q, lhs);
        z_mul_i(q, z_sign(rhs));
        z_free(r);
        z_set_from_c(r, 0);

        z_free(&lhs_abs);
        z_free(&rhs_abs);

        return;
    }

    z_free(&lhs_abs);
    z_free(&rhs_abs);

    if (z_cmp_c(lhs, 0) < 0 && z_cmp_c(rhs, 0) < 0)
    {
        z_t dividend = z_copy(lhs);
        z_neg(&dividend);
        z_t divisor = z_copy(rhs);
        z_neg(&divisor);

        z_div_qr_z(dividend, divisor, q, r);

        z_free(&dividend);
        z_free(&divisor);

        if (z_cmp_c(*r, 0))
        {
            z_add_c(q, 1);
            z_add_z(r, rhs);
        }

        return;
    }
    else if (z_cmp_c(lhs, 0) > 0 && z_cmp_c(rhs, 0) < 0)
    {
        z_t divisor = z_copy(rhs);
        z_neg(&divisor);

        z_div_qr_z(lhs, divisor, q, r);

        z_free(&divisor);

        z_neg(q);

        if (z_cmp_c(*r, 0))
        {
            z_sub_c(q, 1);
            z_add_z(r, rhs);
        }

        return;
    }
    else if (z_cmp_c(lhs, 0) < 0 && z_cmp_c(rhs, 0) > 0)
    {
        z_t dividend = z_copy(lhs);
        z_neg(&dividend);

        z_div_qr_z(dividend, rhs, q, r);

        z_free(&dividend);

        z_neg(q);

        if (z_cmp_c(*r, 0))
        {
            z_sub_c(q, 1);
            z_neg(r);
            z_add_z(r, rhs);
        }

        return;
    }
    else if (z_fits_ull(lhs) && z_fits_ull(rhs))
    {
        z_free(q);
        *q = z_from_ull(z_to_ull(lhs) / z_to_ull(rhs));
        z_free(r);
        *r = z_from_ull(z_to_ull(lhs) % z_to_ull(rhs));

        return;
    }

    z_t n = z_number(rhs);
    z_t* a_digits = 0;
    size_t a_digits_size = 0;
    _int2digits(lhs, n, &a_digits, &a_digits_size);

    z_t* q_digits = malloc(a_digits_size * sizeof(z_t));

    for (size_t i = 0; i < a_digits_size; ++i)
    {
        z_t q_digit = z_from_c(0);

        z_t rTmp = z_copy(*r);
        z_lshift_z(&rTmp, n);

        z_add_z(&rTmp, a_digits[a_digits_size - 1 - i]);

        _div2n1n(rTmp, rhs, n, &q_digit, r);

        q_digits[i] = q_digit;

        z_free(&rTmp);
    }

    for (size_t i = 0; i < a_digits_size / 2; ++i)
    {
        z_t tmp = q_digits[i];
        q_digits[i] = q_digits[a_digits_size - 1 - i];
        q_digits[a_digits_size - 1 - i] = tmp;
    }

    z_free(q);
    *q = _digits2int(q_digits, n, a_digits_size);

    free(a_digits);
    free(q_digits);
}

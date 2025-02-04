#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "z_t.h"

void test_add();
void test_cmp();
void test_div_qr();
void test_fits();
void test_mul();
void test_pow();
void test_primes();
void test_set_from();
void test_shift();
void test_sqrt();

int main()
{
    test_add();
    test_cmp();
    test_div_qr();
    test_fits();
    test_mul();
    test_pow();
    test_primes();
    test_set_from();
    test_shift();
    test_sqrt();

    return 0;
}

void test_add()
{
    {
        z_t a = z_from_ll(0);
        z_t b = z_from_ll(-0);

        z_add_z(&a, b);

        assert(!z_cmp_ll(a, 0));

        z_free(&a);
        z_free(&b);
    }

    {
        z_t a = z_from_ll(0);
        z_t b = z_from_ll(-1);

        z_add_z(&a, b);

        assert(!z_cmp_ll(a, -1));

        z_free(&a);
        z_free(&b);
    }

    {
        z_t a = z_from_ll(1);
        z_t b = z_from_ll(0);

        z_add_z(&a, b);

        assert(!z_cmp_ll(a, 1));

        z_free(&a);
        z_free(&b);
    }
}

void test_cmp()
{
    {
        z_t a = z_from_ll(0);
        z_t b = z_from_ll(-0);

        assert(!z_cmp_z(a, b));

        z_free(&a);
        z_free(&b);
    }

    {
        z_t a = z_from_ll(1);
        z_t b = z_from_ll(0);

        assert(z_cmp_z(a, b) == 1);

        z_free(&a);
        z_free(&b);
    }

    {
        z_t a = z_from_ll(0);
        z_t b = z_from_ll(1);

        assert(z_cmp_z(a, b) == -1);

        z_free(&a);
        z_free(&b);
    }

    {
        z_t a = z_from_ll(0);
        z_t b = z_from_ll(-1);

        assert(z_cmp_z(a, b) == 1);

        z_free(&a);
        z_free(&b);
    }

    {
        z_t a = z_from_ll(-1);
        z_t b = z_from_ll(0);

        assert(z_cmp_z(a, b) == -1);

        z_free(&a);
        z_free(&b);
    }

    {
        z_t a = z_from_ull(1654);
        z_t b = z_from_ull(0);
        free(b.bits);
        b.bits = malloc(2 * sizeof(z_type));
        b.bits[0] = 0;
        b.bits[1] = 55;
        b.size = 2;

        assert(z_cmp_z(a, b) == 1);

        z_free(&a);
        z_free(&b);
    }

    {
        z_t a = z_from_ull(0);
        free(a.bits);
        a.bits = malloc(2 * sizeof(z_type));
        a.bits[0] = 56;
        a.bits[1] = 13;
        a.size = 2;
        z_t b = z_from_ull(168764);

        assert(z_cmp_z(a, b) == 1);

        z_free(&a);
        z_free(&b);
    }

    {
        z_t a = z_from_ull(1654);
        z_t b = z_from_ull(0);
        free(b.bits);
        b.bits = malloc(2 * sizeof(z_type));
        b.bits[0] = 165;
        b.bits[1] = 55;
        b.size = 2;

        assert(z_cmp_z(a, b) == -1);

        z_free(&a);
        z_free(&b);
    }
}

void test_div_qr()
{
    {
        unsigned char const a[2] = {61, 42}; //61*2^8 + 42*2^0
        unsigned char const b[2] = {46, 32}; //46*2^8 + 32*2^0
        unsigned char const c[1] = {1}; //1*2^0
        unsigned char const d[2] = {15, 10}; //15*2^8 + 10*2^0

        z_t az = z_from_data(a, 2);
        z_t bz = z_from_data(b, 2);
        z_t cz = z_from_data(c, 1);
        z_t dz = z_from_data(d, 2);

        z_t q = z_from_c(0);
        z_t r = z_from_c(0);

        z_div_qr_z(az, bz, &q, &r);

        assert(!z_cmp_z(q, cz));
        assert(!z_cmp_z(r, dz));

        z_free(&az);
        z_free(&bz);
        z_free(&cz);
        z_free(&dz);
        z_free(&q);
        z_free(&r);
    }

    {
        unsigned char const a[4] = {113, 15, 46, 32};
        unsigned char const b[4] = {12, 42, 61, 42};
        unsigned char const c[1] = {9};
        unsigned char const d[4] = {3, 147, 7, 166};

        z_t az = z_from_data(a, 4);
        z_t bz = z_from_data(b, 4);
        z_t cz = z_from_data(c, 1);
        z_t dz = z_from_data(d, 4);

        z_t q = z_from_c(0);
        z_t r = z_from_c(0);

        z_div_qr_z(az, bz, &q, &r);

        assert(!z_cmp_z(q, cz));
        assert(!z_cmp_z(r, dz));

        z_free(&az);
        z_free(&bz);
        z_free(&cz);
        z_free(&dz);
        z_free(&q);
        z_free(&r);
    }

    {
        z_t z = z_from_c(0);
        free(z.bits);
        z.bits = malloc(2 * sizeof(z_type));
        z.bits[0] = 2;
        z.bits[1] = 3;
        //z = 2*2^64 + 3*2^0;
        z.size = 2;

        z_t q = z_from_c(0);
        z_t r = z_from_c(0);

        z_div_qr_ull(z, 10000000000000000000ull, &q, &r);

        assert(!z_cmp_ull(q, 3));
        assert(!z_cmp_ull(r, 6893488147419103235ull));

        z_free(&z);
        z_free(&q);
        z_free(&r);
    }
}

void test_fits()
{
    {
        z_t z = z_from_i(257);

        assert(!z_fits_c(z));
        assert(z_fits_i(z));
        assert(z_fits_l(z));
        assert(!z_fits_uc(z));
        assert(z_fits_ui(z));
        assert(z_fits_ul(z));
    }
}

void test_mul()
{
    {
        z_t a = z_from_c(0);
        free(a.bits);
        a.bits = malloc(3 * sizeof(z_type));
        a.size = 3;
        a.bits[0] = 2;
        a.bits[1] = 17316620476856118468ull;
        a.bits[2] = 6873995514006732800ull;

        z_t b = z_from_c(3);

        z_mul_z(&a, b);

        z_free(&a);
        z_free(&b);
    }

    {
        unsigned char const a[2] = {46, 32}; //46*2^8 + 32*2^0
        unsigned char const b[2] = {61, 42}; //61*2^8 + 42*2^0
        unsigned char const c[4] = {11, 5, 49, 64}; //11*2^24 + 5*2^16 + 49*2^8 + 64*2^0

        z_t az = z_from_data(a, 2);
        z_t bz = z_from_data(b, 2);
        z_t cz = z_from_data(c, 4);

        z_t d = z_copy(az);
        z_mul_z(&d, bz);

        assert(!z_cmp_z(d, cz));

        z_free(&az);
        z_free(&bz);
        z_free(&cz);
        z_free(&d);
    }

    {
        unsigned char const a[4] = {113, 15, 46, 32};
        unsigned char const b[4] = {12, 42, 61, 42};
        unsigned char const c[8] = {5, 95, 93, 170, 59, 187, 49, 64};

        z_t az = z_from_data(a, 4);
        z_t bz = z_from_data(b, 4);
        z_t cz = z_from_data(c, 8);

        z_t d = z_copy(az);
        z_mul_z(&d, bz);

        assert(!z_cmp_z(d, cz));

        z_free(&az);
        z_free(&bz);
        z_free(&cz);
        z_free(&d);
    }
}

void test_pow()
{
    {
        z_t a = z_from_c(2);
        z_t b = z_pow_c(a, 2);

        assert(!z_cmp_c(b, 4));

        z_free(&a);
        z_free(&b);
    }

    {
        z_t a = z_from_c(-2);
        z_t b = z_pow_c(a, 3);

        assert(!z_cmp_c(b, -8));

        z_free(&a);
        z_free(&b);
    }
}

void test_primes()
{
    {
        z_t z = z_from_c(2);

        assert(z_is_prime(z, 50) == 2);

        z_free(&z);
    }

    {
        z_t z = z_from_c(4);

        assert(z_is_prime(z, 50) == 0);

        z_free(&z);
    }

    {
        z_t z = z_from_c(3);

        assert(z_is_prime(z, 50) == 2);

        z_free(&z);
    }

    {
        z_t z = z_from_c(3);
        z_t a = z_next_prime(z);

        assert(!z_cmp_c(a, 5));

        z_free(&z);
        z_free(&a);
    }

    {
        z_t z = z_from_c(4);
        z_t a = z_next_prime(z);

        assert(!z_cmp_c(a, 5));

        z_free(&z);
        z_free(&a);
    }

    {
        z_t z = z_from_c(5);
        z_t a = z_next_prime(z);

        assert(!z_cmp_c(a, 7));

        z_free(&z);
        z_free(&a);
    }

    {
        z_t z = z_from_c(10);
        z_t a = z_next_prime(z);

        assert(!z_cmp_c(a, 11));

        z_free(&z);
        z_free(&a);
    }

    {
        z_t z = z_from_c(13);
        z_t a = z_previous_prime(z);

        assert(!z_cmp_c(a, 11));

        z_free(&z);
        z_free(&a);
    }

    {
        z_t z = z_from_c(12);
        z_t a = z_previous_prime(z);

        assert(!z_cmp_c(a, 11));

        z_free(&z);
        z_free(&a);
    }

    {
        z_t z = z_from_c(11);
        z_t a = z_previous_prime(z);

        assert(!z_cmp_c(a, 7));

        z_free(&z);
        z_free(&a);
    }


    {
        z_t z = z_from_c(31);

        assert(z_is_prime(z, 50) == 2);

        z_free(&z);
    }

    {
        z_t z = z_from_str("1'299'709", 0); //100'000th prime

        assert(z_is_prime(z, 50));

        z_free(&z);
    }

    {
        z_t z = z_from_str("15'482'009", 0);

        assert(!z_is_prime(z, 50));

        z_free(&z);
    }

    {
        z_t z = z_from_str("13'359'555'403", 0); //600'000'000th prime

        assert(z_is_prime(z, 50));

        z_free(&z);
    }

    {
        z_t z = z_from_str("4113101149215104800030529537915953170486139623539759933135949994882770404074832568499", 0);

        assert(z_is_prime(z, 1));

        z_free(&z);
    }
}

void test_set_from()
{
    {
        z_t z = z_from_c(1);

        z_printf_bytes(z);
        printf("\n");

        for (size_t i = 0; i < z.size; ++i)
            printf("%llu ", z.bits[i]);
        printf("\n");
    }

    {
        z_t z = z_from_c(127);

        assert(z_to_c(z) == 127);
        assert(z_to_uc(z) == 127);
        assert(z_to_i(z) == 127);
        assert(z_to_ui(z) == 127);
        assert(z_to_s(z) == 127);
        assert(z_to_us(z) == 127);
        assert(z_to_l(z) == 127);
        assert(z_to_ul(z) == 127);
        assert(z_to_ll(z) == 127);
        assert(z_to_ull(z) == 127);
    }

    {
        z_t z = z_from_str("13'359'555'403", 0);
        char* s = z_to_str(z, 10);

        assert(!strcmp(s, "13359555403"));

        free(s);
        z_free(&z);
    }

    {
        z_t z = z_from_c(0);
        free(z.bits);
        z.bits = malloc(2 * sizeof(z_type));
        z.bits[0] = 2;
        z.bits[1] = 3;
        //z = 2*2^64 + 3*2^0;
        z.size = 2;

        char* s = z_to_str(z, 10);

        assert(!strcmp(s, "36893488147419103235"));

        free(s);
        z_free(&z);
    }

    {
        z_t z = z_from_str("100'000'000'000'000'000'000'003", 0);
        char* s = z_to_str(z, 10);

        assert(!strcmp(s, "100000000000000000000003"));

        free(s);
        z_free(&z);
    }
}

void test_shift()
{
    {
        z_t z = z_from_c(1);
        z_rshift_c(&z, 1);

        assert(!z_cmp_c(z, 0));

        z_free(&z);
    }

    {
        z_t z = z_from_c(3);
        z_rshift_c(&z, 1);

        assert(!z_cmp_c(z, 1));

        z_free(&z);
    }

    {
        z_t z = z_from_c(1);
        z_lshift_c(&z, 1);

        assert(!z_cmp_c(z, 2));

        z_free(&z);
    }

    {
        z_t z = z_from_ull(1878050631);
        z_lshift_c(&z, 31);

        assert(!z_cmp_ull(z, 4033083020188581888ull));

        z_free(&z);
    }

    {
        z_t z = z_from_ull(1800090071576084480ull);
        z_rshift_c(&z, 21);

        assert(!z_cmp_ull(z, 858349834240ull));

        z_free(&z);
    }
}

void test_sqrt()
{
    z_t z = z_from_c(4);
    z_t sqrt = z_sqrt(z);

    assert(!z_cmp_c(sqrt, 2));

    z_free(&z);
    z_free(&sqrt);
}

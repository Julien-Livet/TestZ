#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "z_set_from.h"

void z_set_from_c(z_t* z, char n)
{
    assert(z);

    z->is_positive = (n >= 0);

    size_t size = sizeof(char) / sizeof(z_type);

    if (sizeof(char) % sizeof(z_type))
        ++size;

    if (size > z->size)
    {
        z->size = size;
        free(z->bits);
        z->bits = malloc(z->size * sizeof(z_type));
    }

    z->is_nan = false;
    z->is_infinity = false;

    if (n < 0)
        n = -n;

    assert(z->bits);

    size_t const s = sizeof(char);

    memset((void*)(z->bits) + s, 0, z->size * sizeof(z_type) - s);
    memcpy(z->bits, &n, s);
}

void z_set_from_data(z_t* z, void const* data, size_t size)
{
    assert(z);

    assert(data);

    z->is_positive = true;

    size_t s = size / sizeof(z_type);

    if (size % sizeof(z_type))
        ++s;

    if (s > z->size)
    {
        z->size = s;
        free(z->bits);
        z->bits = malloc(z->size * sizeof(z_type));
    }

    z->is_nan = false;
    z->is_infinity = false;

    if (size)
        assert(z->bits);

    memset((void*)(z->bits) + size, 0, z->size * sizeof(z_type) - size);
    memcpy(z->bits, data, size);

    for (size_t i = 0; i < size / 2; ++i)
    {
        char tmp = *((char*)(z->bits) + size - 1 - i);
        *((char*)(z->bits) + size - 1 - i) = *((char*)(z->bits) + i);
        *((char*)(z->bits) + i) = tmp;
    }
}

void z_set_from_i(z_t* z, int n)
{
    assert(z);

    z->is_positive = (n >= 0);

    size_t size = sizeof(int) / sizeof(z_type);

    if (sizeof(int) % sizeof(z_type))
        ++size;

    if (size > z->size)
    {
        z->size = size;
        free(z->bits);
        z->bits = malloc(z->size * sizeof(z_type));
    }

    z->is_nan = false;
    z->is_infinity = false;

    if (n < 0)
        n = -n;

    assert(z->bits);

    size_t const s = sizeof(int);

    memset((void*)(z->bits) + s, 0, z->size * sizeof(z_type) - s);
    memcpy(z->bits, &n, s);
}

void z_set_from_l(z_t* z, long n)
{
    assert(z);

    z->is_positive = (n >= 0);

    size_t size = sizeof(long) / sizeof(z_type);

    if (sizeof(long) % sizeof(z_type))
        ++size;

    if (size > z->size)
    {
        z->size = size;
        free(z->bits);
        z->bits = malloc(z->size * sizeof(z_type));
    }

    z->is_nan = false;
    z->is_infinity = false;

    if (n < 0)
        n = -n;

    assert(z->bits);

    size_t const s = sizeof(long);

    memset((void*)(z->bits) + s, 0, z->size * sizeof(z_type) - s);
    memcpy(z->bits, &n, s);
}

void z_set_from_ll(z_t* z, long long n)
{
    assert(z);

    z->is_positive = (n >= 0);

    size_t size = sizeof(long long) / sizeof(z_type);

    if (sizeof(long long) % sizeof(z_type))
        ++size;

    if (size > z->size)
    {
        z->size = size;
        free(z->bits);
        z->bits = malloc(z->size * sizeof(z_type));
    }

    z->is_nan = false;
    z->is_infinity = false;

    if (n < 0)
        n = -n;

    assert(z->bits);

    size_t const s = sizeof(long long);

    memset((void*)(z->bits) + s, 0, z->size * sizeof(z_type) - s);
    memcpy(z->bits, &n, s);
}

void z_set_from_s(z_t* z, short n)
{
    assert(z);

    z->is_positive = (n >= 0);

    size_t size = sizeof(short) / sizeof(z_type);

    if (sizeof(short) % sizeof(z_type))
        ++size;

    if (size > z->size)
    {
        z->size = size;
        free(z->bits);
        z->bits = malloc(z->size * sizeof(z_type));
    }

    z->is_nan = false;
    z->is_infinity = false;

    if (n < 0)
        n = -n;

    assert(z->bits);

    size_t const s = sizeof(short);

    memset((void*)(z->bits) + s, 0, z->size * sizeof(z_type) - s);
    memcpy(z->bits, &n, s);
}

void z_set_from_str(z_t* z, char const* n, size_t base)
{
    assert(z);

    z_free(z);

    *z = z_from_str(n, base);
}

void z_set_from_uc(z_t* z, unsigned char n)
{
    assert(z);

    z->is_positive = true;

    size_t size = sizeof(unsigned char) / sizeof(z_type);

    if (sizeof(unsigned char) % sizeof(z_type))
        ++size;

    if (size > z->size)
    {
        z->size = size;
        free(z->bits);
        z->bits = malloc(z->size * sizeof(z_type));
    }

    z->is_nan = false;
    z->is_infinity = false;

    if (n < 0)
        n = -n;

    assert(z->bits);

    size_t const s = sizeof(unsigned char);

    memset((void*)(z->bits) + s, 0, z->size * sizeof(z_type) - s);
    memcpy(z->bits, &n, s);
}

void z_set_from_ui(z_t* z, unsigned int n)
{
    assert(z);

    z->is_positive = true;

    size_t size = sizeof(unsigned int) / sizeof(z_type);

    if (sizeof(unsigned int) % sizeof(z_type))
        ++size;

    if (size > z->size)
    {
        z->size = size;
        free(z->bits);
        z->bits = malloc(z->size * sizeof(z_type));
    }

    z->is_nan = false;
    z->is_infinity = false;

    if (n < 0)
        n = -n;

    assert(z->bits);

    size_t const s = sizeof(unsigned int);

    memset((void*)(z->bits) + s, 0, z->size * sizeof(z_type) - s);
    memcpy(z->bits, &n, s);
}

void z_set_from_ul(z_t* z, unsigned long n)
{
    assert(z);

    z->is_positive = true;

    size_t size = sizeof(unsigned long) / sizeof(z_type);

    if (sizeof(unsigned long) % sizeof(z_type))
        ++size;

    if (size > z->size)
    {
        z->size = size;
        free(z->bits);
        z->bits = malloc(z->size * sizeof(z_type));
    }

    z->is_nan = false;
    z->is_infinity = false;

    if (n < 0)
        n = -n;

    assert(z->bits);

    size_t const s = sizeof(unsigned long);

    memset((void*)(z->bits) + s, 0, z->size * sizeof(z_type) - s);
    memcpy(z->bits, &n, s);
}

void z_set_from_ull(z_t* z, unsigned long long n)
{
    assert(z);

    z->is_positive = true;

    size_t size = sizeof(unsigned long long) / sizeof(z_type);

    if (sizeof(unsigned long long) % sizeof(z_type))
        ++size;

    if (size > z->size)
    {
        z->size = size;
        free(z->bits);
        z->bits = malloc(z->size * sizeof(z_type));
    }

    z->is_nan = false;
    z->is_infinity = false;

    if (n < 0)
        n = -n;

    assert(z->bits);

    size_t const s = sizeof(unsigned long long);

    memset((void*)(z->bits) + s, 0, z->size * sizeof(z_type) - s);
    memcpy(z->bits, &n, s);
}

void z_set_from_us(z_t* z, unsigned short n)
{
    assert(z);

    z->is_positive = true;

    size_t size = sizeof(unsigned short) / sizeof(z_type);

    if (sizeof(unsigned short) % sizeof(z_type))
        ++size;

    if (size > z->size)
    {
        z->size = size;
        free(z->bits);
        z->bits = malloc(z->size * sizeof(z_type));
    }

    z->is_nan = false;
    z->is_infinity = false;

    if (n < 0)
        n = -n;

    assert(z->bits);

    size_t const s = sizeof(unsigned short);

    memset((void*)(z->bits) + s, 0, z->size * sizeof(z_type) - s);
    memcpy(z->bits, &n, s);
}

void z_set_from_z(z_t* z, z_t n)
{
    assert(z);

    z->is_positive = n.is_positive;
    free(z->bits);
    z->bits = malloc(n.size * sizeof(z_type));
    memcpy(z->bits, n.bits, n.size * sizeof(z_type));
    z->size = n.size;
    z->is_nan = n.is_nan;
    z->is_infinity = n.is_infinity;
    z->is_auto_adjust = n.is_auto_adjust;
}

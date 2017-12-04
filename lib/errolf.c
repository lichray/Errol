#include <assert.h>
#include <float.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "errol.h"
#include "itoa_c.h"

/*
 * floating point format definitions
 */

static inline float fpnext(float val)
{
	errolf_bits_t bits = { val };
	bits.i++;
	return bits.d;
}

static inline float fpprev(float val)
{
	errolf_bits_t bits = { val };
	bits.i--;
	return bits.d;
}

#define ERROL0F_EPSILON	0.0000001


/**
 * Errol0 float to ASCII conversion, guaranteed correct but possibly not
 * optimal. Useful for embedded systems.
 *   @val: The value.
 *   @buf: The output buffer.
 *   &returns: The exponent.
 */

int errol0f_ftoa(float val, char *buf)
{
	double ten;
	int exp;
	double mid, inhi, inlo;

	ten = 1.0;
	exp = 1;

	/* normalize the midpoint */

	mid = val;

	while ((mid > 10.0) && (exp < 38))
		exp++, mid /= 10.0, ten /= 10.0;

	while ((mid < 1.0) && (exp > -37))
		exp--, mid *= 10.0, ten *= 10.0;

	inhi = mid + (fpnext(val) - val) * ten / (2.0 + ERROL0F_EPSILON);
	inlo = mid + (fpprev(val) - val) * ten / (2.0 + ERROL0F_EPSILON);

	/* normalized boundaries */

	while (inhi > 10.0)
		exp++, inhi /= 10.0, inlo /= 10.0;

	while (inhi < 1.0)
		exp--, inhi *= 10.0, inlo *= 10.0;

	/* digit generation */

	while (inhi != 0.0)
	{
		uint8_t ldig, hdig = 0;

		hdig = (uint8_t)(inhi);
		ldig = (uint8_t)(inlo);

		if (ldig != hdig)
			break;

		*buf++ = hdig + '0';

		inhi -= hdig;
		inhi *= 10.0;

		inlo -= ldig;
		inlo *= 10.0;
	}

	double mdig = (inhi + inlo) / 2.0 + 0.5;
	*buf++ = (uint8_t)(mdig) + '0';
	*buf = '\0';

	return exp;
}

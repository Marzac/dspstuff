#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

/*****************************************************************************/
#include "fastexp2f.h"
const FastExp2f<32> fexp2f;

/*****************************************************************************/
int main(int argc, char * argv[])
{
/** Floating point version */
	for (int i = -1000; i < 1000; i++) {
		float f = 32.0f * (i / 1000.0f);
		float e1 = exp2f(f);
		float e2 = fexp2f(f);
		float err = 100.0f * (e1 - e2) / e1;
		printf("Input %f / math %f / fast %f / error %f\n", f, e1, e2, err);
	}
	return 0;
}

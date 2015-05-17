// from: https://en.wikipedia.org/wiki/Multiply-with-carry

#include <limits.h>
#include <math.h>

#include "rng.h"

#define PI 3.1415926535
#define PHI 0x9e3779b9
 
static uint32_t Q[4096], c = 362436;


static uint32_t rand_cmwc(void)
{
	static uint32_t i = 4095;
	uint64_t t;
 
	i = (i + 1) & 4095;
	t = (18705ULL * Q[i]) + c;
	c = t >> 32;
	Q[i] = 0xfffffffe - t;
 
	return Q[i];
}

void RNG_init(uint32_t x)
{
	int i;
 
	Q[0] = x;
	Q[1] = x + PHI;
	Q[2] = x + PHI + PHI;
 
	for (i = 3; i < 4096; i++)
		Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;

	for (i=0; i<10000; i++)
		rand_cmwc();
}

uint32_t RNG_u() {
    return rand_cmwc();
}

float RNG_f() {
    return (float)(RNG_u()) / UINT_MAX;
}

double RNG_d() {
    return (double)(RNG_u()) / UINT_MAX;
}

//static float Z0, Z1;
//static bool use_other = false;

float RNG_norm() {
    float u1 = RNG_f(), u2 = RNG_f();
    //Z0 = sqrt(-2*log(u1)) * cos(2*PI*u2);
    //Z1 = sqrt(-2*log(u1)) * sin(2*PI*u2);
    return sqrt(-2*log(u1)) * cos(2*PI*u2);
}

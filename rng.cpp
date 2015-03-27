// from: https://en.wikipedia.org/wiki/Multiply-with-carry

#include <limits.h>
#include <math.h>

#include "rng.hpp"
#include "globals.hpp"
 
#define PHI 0x9e3779b9
 
static uint32_t Q[4096], c = 362436;
 
static void init_rand(uint32_t x)
{
	int i;
 
	Q[0] = x;
	Q[1] = x + PHI;
	Q[2] = x + PHI + PHI;
 
	for (i = 3; i < 4096; i++)
		Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
}
 
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

void RNG::init(uint32_t x) {
    init_rand(x);
}

uint32_t RNG::u() {
    return rand_cmwc();
}

float RNG::f() {
    return (float)(u()) / UINT_MAX;
}

double RNG::d() {
    return (double)(u()) / UINT_MAX;
}

//static float Z0, Z1;
//static bool use_other = false;

float RNG::norm() {
    float u1 = f(), u2 = f();
    //Z0 = sqrt(-2*log(u1)) * cos(2*PI*u2);
    //Z1 = sqrt(-2*log(u1)) * sin(2*PI*u2);
    return sqrt(-2*log(u1)) * cos(2*PI*u2);
}

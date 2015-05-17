#ifndef __RNG_H__
#define __RNG_H__

#include <stdint.h>

void		RNG_init(uint32_t x);
uint32_t	RNG_u();
float		RNG_f();
double		RNG_d();
float		RNG_norm();

#endif /* __RNG_H__ */

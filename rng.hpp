#ifndef __RNG_HPP__
#define __RNG_HPP__

#include <stdint.h>

class RNG
{
public:
    static void init(uint32_t x = 0x0f1e2d3c);

    static uint32_t u();
    static float f();
    static double d();
    static float norm();
};

#endif /* __RNG_HPP__ */

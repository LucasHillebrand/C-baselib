#ifndef simplemath_h
#define simplemath_h

#include "./basetypes.h"

enum numtype {
    hex=16,
    dec=10,
    bin=2
};

usize m_len(usize num, enum numtype type);
usize m_power(usize num, usize n);

#endif
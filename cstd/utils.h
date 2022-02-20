#ifndef UTILS_H
#define UTILS_H

#include "def.h"

// faster way than `%`
inline bool
is_power_of_2(size_t num)
{
    return (num & (num - 1)) == 0;
}

#endif // UTILS_H
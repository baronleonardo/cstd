#ifndef __ARENA__H
#define __ARENA__H

#include "../../def.h"
#include "../../utils.h"

#include <assert.h>

/*
 * adapt the memory pointer address according to the align
 * by pushing the ptr alittle bit forward
 */
inline uptr
__forward_align__(uptr mem_addr, size_t align)
{
    assert(is_power_of_2(align));

    uptr new_position = mem_addr;

    // Same as (new_position % align) but faster as 'align' is a power of two
	uptr missing_alignment = (uptr)new_position & ((uptr)align - 1);

    if(missing_alignment != 0)
    {
        new_position += align - missing_alignment;
    }

    return new_position;
}

#endif // __ARENA__H
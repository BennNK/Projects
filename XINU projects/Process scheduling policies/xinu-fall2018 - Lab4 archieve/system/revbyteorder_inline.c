#include <xinu.h>

long revbyteorder_inline(long t)
{
asm("bswap %0;"
: "=r" (t)
: "0" (t));

}


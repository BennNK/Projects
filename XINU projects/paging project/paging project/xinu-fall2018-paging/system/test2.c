//test2.c chen2240 lab5
#include <xinu.h>

void test2()
{
    char * test2=vgetmem(6000);
  
  kprintf("\n test2 address %d\n",test2);
 
    return;
    
}
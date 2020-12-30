//Lab5_test2.c
#include <xinu.h>

void Lab5_test2()
{
    int k;
    asm("\t movl %%cr3,%0" : "=r"(k));   
    kprintf("page directory address %d, it should be %d\n", k, (FRAME0 + 7) * NBPG);
    return;
    
}
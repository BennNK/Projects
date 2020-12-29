//Lab5 chen2240
//hooks
#include <xinu.h>

#define HOOKON

#ifdef HOOKON

void hook_ptable_create(unsigned int pagenum)

{

   
    kprintf("Created page table %d\n\n", pagenum);



}

void hook_ptable_delete(unsigned int pagenum)
{

    
    kprintf("Deleted page table %d\n\n", pagenum);

}

void hook_pfault(unsigned long addr)
{


    
    kprintf("Page fault for address %d\n\n", addr);

}

uint32  pfnum;// number of page fault


int get_faults()
{


kprintf("\npfnum %d\n",pfnum);
return pfnum;
    

}

#endif
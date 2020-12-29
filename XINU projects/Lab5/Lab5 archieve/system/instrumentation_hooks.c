//Lab5
//lei48
//instrumentation_hooks.c
#include <xinu.h>

#define HOOK_ACTIVATE

uint32  pf_counter;

void hook_ptable_create(unsigned int pagenum)

{
#ifdef HOOK_ACTIVATE
    kprintf("Created page table %d\n\n", pagenum);

#endif

}

void hook_ptable_delete(unsigned int pagenum)
{
#ifdef HOOK_ACTIVATE
    kprintf("Deleted page table %d\n\n", pagenum);
#endif
}

void hook_pfault(char *addr)
{

#ifdef HOOK_ACTIVATE
    kprintf("Page fault for address %d\n\n", addr);
#endif
}

void hook_pswap_out(unsigned int pagenum, int framenb)
{
#ifdef HOOK_ACTIVATE
    kprintf("Replacing frame number %d, virtual page %d\n\n",framenb, pagenum);
#endif
}


int get_faults()
{
#ifdef HOOK_ACTIVATE

    kprintf("\npf_counter %d\n",pf_counter);
    return pf_counter;
    
#endif
}
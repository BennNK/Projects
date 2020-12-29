#include <xinu.h>

char myfuncA(
int input
        )
{

struct	procent *present_proc;
present_proc = &proctab[getpid()];




//Lab1 5.3 only, comment the below are if doing 5.4
//
// register int a asm("esp");
//     int* esp_=a;
//     kprintf("in myfuncA() the address of the top of the run-time stack after myfuncA() is called is 0x%8x\n",(esp_)); 
//     kprintf(" in myfuncA() the content of the top of the run-time stack after myfuncA() is called is 0x%8x\n",*(esp_));
//end of 5.3


//Lab1 5.4 only
// kprintf("myfuncA base is  0X%8x\n",present_proc->prstkbase);
// kprintf("myfuncA size is  %d\n",present_proc->prstkbase-present_proc->prstkptr);
// kprintf("myfuncA limit is  %d\n",present_proc->prstklen);
// kprintf("myfuncA stack pointer is  0X%8x\n",present_proc->prstkptr);
// kprintf("myfuncA pid is  %d\n",getpid());
// kprintf("myfuncA parent pid  %d\n",present_proc->prparent);
//end of 5.4


//Lab1 6

//stacktrace(currpid);

// kprintf("myfuncA base is  0X%8x\n",present_proc->prstkbase);
// kprintf("myfuncA size is  %d\n",present_proc->prstkbase-present_proc->prstkptr);
// kprintf("myfuncA limit is  %d\n",present_proc->prstklen);
// kprintf("myfuncA stack pointer is  0X%8x\n",present_proc->prstkptr);
// kprintf("myfuncA pid is  %d\n",getpid());
// kprintf("myfuncA parent pid  %d\n",present_proc->prparent);
// kprintf("---------------------------\n");
//
// int(*fptr)()=&malware;
//
//
// kprintf("\n&malware=0x%8x\n",fptr);
//
//
// register int j asm("ebp");
// kprintf("\nebp of my func is 0x%8x\n",j);
// int* ret_add=j+4*16*16+4;
//
// //kprintf("\nstack frame of ret_add of my prog after calc in myfuncA is 0x%8x\n",ret_add);
// //kprintf("\nret_add of of my prog after calc in myfuncA is 0x%8x\n",*ret_add);
//
//
// *ret_add=fptr;

////end of Lab1 6


//Lab 1 Bonus

//  int(*fptr)()=&malwareB;

// register int j asm("ebp");
// int* ret_add=j+4;

// kprintf("\nstack frame of ret_add of myfuncA is 0x%8x\n",ret_add);
// kprintf("\nret_add of myfuncA is 0x%8x\n",*ret_add);

// *ret_add=fptr;


////end of Lab1 Bonus

    char b=input;

    return b;
}
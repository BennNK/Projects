#include <xinu.h>



int myProgA()
{

    int a=10;
    char b;
    
    
    struct	procent *present_proc;
   present_proc = &proctab[getpid()];
    
    ////Lab1 5.3 only
    

//     register int a_ asm("esp");
//     int* esp_=a_;
//
//   
//    
//     kprintf(" the address of the top of the run-time stack after myprogA() is created but before myfuncA() is called inside myprogA()is 0x%8x\n",esp_); 
//     kprintf(" the content of the top of the run-time stack after myprogA() is created but before myfuncA() is called inside myprogA()is 0x%8x\n",*esp_);   
//   
//  b=myfuncA(a);
//    
   // //end of 5.3
    
    

    ////Lab1 5.4 only
// kprintf("myProgA base is  0X%8x\n",present_proc->prstkbase);
// kprintf("myProgA size is  %d\n",present_proc->prstkbase-present_proc->prstkptr);
// kprintf("myProgA limit is  %d\n",present_proc->prstklen);
// kprintf("myProgA stack pointer is  0X%8x\n",present_proc->prstkptr);
// kprintf("myProgA pid is  %d\n",getpid());
// kprintf("myProgA parent pid  %d\n",present_proc->prparent);
//end of 5.4

////Lab1 6
//kprintf("myProgA base is  0X%8x\n",present_proc->prstkbase);
// kprintf("myProgA size is  %d\n",present_proc->prstkbase-present_proc->prstkptr);
// kprintf("myProgA limit is  %d\n",present_proc->prstklen);
// kprintf("myProgA stack pointer is  0X%8x\n",present_proc->prstkptr);
// kprintf("myProgA pid is  %d\n",getpid());
// kprintf("myProgA parent pid  %d\n",present_proc->prparent);
// kprintf("---------------------------\n");
//
//
// resume(create(myfuncA,1024,20,"myfuncA",0));
//
// sleepms(3000);
//
// register int j asm("ebp");
// kprintf("\nebp of my prog is 0x%8x\n",j);
// int* ret_add=j+4;
//
// // kprintf("\nstack frame of ret_add of myprog is 0x%8x\n",ret_add);
// // kprintf("\nret_add of myprog is 0x%8x\n",*ret_add);
//
//
// kprintf("myProgA base is  0X%8x\n",present_proc->prstkbase);
// kprintf("myProgA size is  %d\n",present_proc->prstkbase-present_proc->prstkptr);
// kprintf("myProgA limit is  %d\n",present_proc->prstklen);
// kprintf("myProgA stack pointer is  0X%8x\n",present_proc->prstkptr);
// kprintf("myProgA pid is  %d\n",getpid());
// kprintf("myProgA parent pid  %d\n",present_proc->prparent);
// kprintf("---------------------------\n");

////end of Lab1 6

    

    return a;
}



#include <xinu.h>
//Lab4 3 (username:lei48, date modified: 10/24/2018)
void myrcv(void)

{


struct procent *prptr;
prptr = &proctab[currpid];

if (prptr->prhasmsg == 0)//no message to receive

{   kprintf("\npid %d\n", currpid);
    kprintf("clktimemilli %d\n", clktimemilli);
    kprintf("process has no message, SYSERR\n");
    kprintf("prptr->prmsg %d\n",prptr->prmsg);
    return;
}



    //else print out information
    kprintf("\nclktimemilli %d\n", clktimemilli);
    kprintf("pid %d\n", currpid);
    kprintf("process has message, msg=%d\n",prptr->prmsg);
 
    
    
prptr->prhasmsg=0;//clean message flag


return;
}
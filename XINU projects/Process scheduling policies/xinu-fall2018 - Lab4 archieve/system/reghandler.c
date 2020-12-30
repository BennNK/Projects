//Lab4 3 (username:lei48, date modified: 10/24/2018)
#include <xinu.h>


syscall reghandler( void (* func) (void) )

{


intmask	mask;
mask = disable();

struct procent *prptr;
prptr = &proctab[currpid];

      if (isbadpid(currpid))//bad pid
      {
         kprintf("currpid %d\n", currpid);
         kprintf("isbadpid(currpid) %d\n", isbadpid(currpid));
         kprintf(" failed\n");
         
         return SYSERR;
         
      } 
      
        
         prptr->func_address=func;//update proctab entry and register call back function
         prptr->hasfunc=1;//flag of having call bac function
        
         






restore(mask);

return OK;

}
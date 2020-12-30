//signalreg.c
//Lab4 4 (username:lei48, date modified: 10/24/2018)
#include <xinu.h>


syscall signalreg( uint16 nsig, int (* func) (void), uint32 oarg )

{


intmask	mask;
mask = disable();

struct procent *prptr;
prptr = &proctab[currpid];

      if (isbadpid(currpid))//bad pid
      {
         kprintf("currpid %d\n", currpid);
         kprintf("isbadpid(currpid) %d\n", isbadpid(currpid));
         kprintf("reg failed\n");
         
         return SYSERR;
         
      } 
      
      if(nsig==SIGXCPU&&oarg<currproctime+prptr->pgrosscpu)
      {
          return SYSERR;
      
      }
      
        
        prptr->prsig[nsig].regyes=1;//registration succeed
        prptr->prsig[nsig].fnt=func;//address of call back function 
        prptr->prsig[nsig].optarg=oarg;






restore(mask);

return OK;

}
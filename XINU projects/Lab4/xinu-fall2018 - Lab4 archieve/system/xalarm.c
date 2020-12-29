//xalarm.c
//Lab4 4 (username:lei48, date modified: 10/24/2018)
#include <xinu.h>

syscall	xalarm(
	  int32	deadline
	)
 
 {
    struct procent *prptr;
prptr = &proctab[currpid];
     if(deadline<clktimemilli)//the alarm time attempted to regster is in the past
     {
       kprintf("\npid %d\n",currpid);
       kprintf("\nclktimemilli %d\n",clktimemilli);
       kprintf("deadline<clktimemilli\n");
       return SYSERR;
     
     }
     
     prptr->xalarm_time=deadline;//record alarm time 
     return OK;
 
 
 
 
 }
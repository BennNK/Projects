/* wakeup.c - wakeup */
//Lab3 modified (username:lei48, date modified: 10/03/2018)
#include <xinu.h>


void	wakeup(void)
{
	/* Awaken all processes that have no more time to sleep */
 
 
 
 if (XINUSCHED!=2)//normal wakeup legacy code
 {
 	resched_cntl(DEFER_START);
	while (nonempty(sleepq) && (firstkey(sleepq) <= 0)) {
		ready(dequeue(sleepq));
	}

	resched_cntl(DEFER_STOP);
	return;
 }
 
 
 
 //Lab3 3.2  (username:lei48, date modified: 10/03/2018)
 else//CFS wakeup 
 {
   resched_cntl(DEFER_START);
   
   while (nonempty(sleepq) && (firstkey(sleepq) <= 0)) {
   
   
   struct	procent	*prptr;
 pid32 pid=dequeue(sleepq);
 prptr = &proctab[pid];
 
 
 
 struct procent *prprcpt;

 uint32 gross_time_temp=MAXPRIO;
 
 qid16 tail=queuetail(readylist);
 
 if(nonempty(readylist))
 {
 
 qid16 curr = firstid(readylist);
  while(curr!=tail)
  {
  if (curr==0)//null process should be excluded
  {
  curr=queuetab[curr].qnext;
  continue;
  }
  
  prprcpt = &proctab[curr];
  if (prprcpt->pgrosscpu<gross_time_temp)
  {
  gross_time_temp=prprcpt->pgrosscpu;
  
  }
  curr=queuetab[curr].qnext;
  
  }
 
 }
 //compare with current process
 struct	procent	*curptr;
 curptr = &proctab[currpid];
 
 
 if (curptr->pgrosscpu+currproctime<gross_time_temp)
  {
  gross_time_temp=curptr->pgrosscpu+currproctime;
  
  }
 
 prptr->pvirtcpu=gross_time_temp;
 prptr->prprio=MAXPRIO-prptr->pvirtcpu;
 
 ready(pid);
 
 }

   resched_cntl(DEFER_STOP);
	return;

}
//end of Lab3 3.2


}













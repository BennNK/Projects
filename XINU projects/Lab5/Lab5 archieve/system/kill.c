/* kill.c - kill */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  kill  -  Kill a process and remove it from the system
 *------------------------------------------------------------------------
 */
syscall	kill(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	int32	i;			/* number into descriptors	*/

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1) {		/* Last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);
	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
 
 

 
 //Lab5 (lei48 11/09/2018)
 wait(pgft_sem);
	for (i = NUM_PAGES_FOR_PD_PT; i < NFRAMES; i++) //free pages occupied by the process
  {
		if (ipagetab[i].used == 1 && ipagetab[i].pid == pid && ipagetab[i].type == PAGE) {
			 
			ipagetab[i].used = 0;
      }
   }
   
   
  for (i = 5; i < NUM_PAGES_FOR_PD_PT; i++) //free page dir and tables of the process
  {
		if (ipagetab[i].used == 1 && ipagetab[i].pid == pid && ipagetab[i].type != PAGE) 
    {
			ipagetab[i].used = 0;

			if (ipagetab[i].type == PAGETABLE) 
      {
				hook_ptable_delete(ipagetab[i].frame_number);
			}
		}

	}
 
 signal(pgft_sem);
 
 
 
 //end of Lab5
 
 
 
 
 
 
 
	freestk(prptr->prstkbase, prptr->prstklen);

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE;	/* Suicide */
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		getitem(pid);		/* Remove from queue */
		/* Fall through */

	default:
		prptr->prstate = PR_FREE;
	}

	restore(mask);
	return OK;
}

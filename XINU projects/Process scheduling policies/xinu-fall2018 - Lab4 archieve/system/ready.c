/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
 
 //Lab2 3.3 (username:lei48, date modified: 09/25/2018)
 prptr->pstartwait=clktimemilli; //when a new process is put to ready queue it needs to become waiting
 prptr->pwaitcount++;
 //end of 3.3 (username:lei48, date modified: 09/25/2018)
 
 
 
 
 
	insert(pid, readylist, prptr->prprio);
	resched();

	return OK;
}

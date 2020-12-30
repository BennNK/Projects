/* resched.c - resched, resched_cntl */

#include <xinu.h>

struct	defer	Defer;

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* Assumes interrupts are disabled	*/
{

	struct procent *ptold;	/* Ptr to table entry for old process	*/
	struct procent *ptnew;	/* Ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];
 
// struct procent *pm;
//pm = &proctab[3];
//kprintf("\npm->prprio, %d\n", pm->prprio);

 ////////Lab2 5.4 R3 mode (username:lei48, date modified: 09/25/2018)
  if (XINUSCHED==1&&ptold->prstate == PR_CURR&&preempt==QUANTUM&&currproctime==QUANTUM&&currpid!=0) //if R3 mode is on and the state of the process is current and it has depleted its timeslice
 {
 ptold->prprio=INITPRIO;
 }
 ////////end of Lab2 5.4 R3 mode (username:lei48, date modified: 09/25/2018)
 

//kprintf("\npm->prprio, %d\n", pm->prprio);

	if (ptold->prstate == PR_CURR) {  /* Process remains eligible */
		if (ptold->prprio > firstkey(readylist)) {
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		insert(currpid, readylist, ptold->prprio);
   
 
   
 //Lab2 3.3 (username:lei48, date modified: 09/25/2018)
 ptold->pstartwait=clktimemilli;
 ptold->pwaitcount++;
 //end of 3.3 (username:lei48, date modified: 09/25/2018)
   

   
	}
 
 
 
  ////////Lab2 5.4 R3 mode (username:lei48, date modified: 09/25/2018)
  if(XINUSCHED==1&&ptold->prstate == PR_SLEEP)//if R3 mode is on and the state of a process is put to PR_SLEEP by sleepms() who calls resched right afterwards
 {
 ptold->prprio=IOPRIO;
 
 }
/////////////end of Lab2 5.4  R3 mode (username:lei48, date modified: 09/25/2018)
 
 
 
 
 

	/* Force context switch to highest priority ready process */

 
 
 
 //Lab2 3.2 (username:lei48, date modified: 09/25/2018)
  ptold->pgrosscpu +=currproctime;
  currproctime=0;
  //end of Lab2 3.2 (username:lei48, date modified: 09/25/2018)
  

 
 
	currpid = dequeue(readylist);
 

 
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
 
 //Lab2 3.3 (username:lei48, date modified: 09/25/2018)
 ptnew->pwaittime+=clktimemilli-ptnew->pstartwait;//calculate waittime of the process that is about to be context-switched in
 //end of Labs 3.3 (username:lei48, date modified: 09/25/2018)
 
 
//Lab3 4.3 (username:lei48, date modified: 10/03/2018)
if (ptnew->prrms==1)//the new process is real-time process

{
 preempt_rms = RMSQUANTUM;		/* Reset time slice for real-time process	*/


}

 
 
 if (ptnew->prrms==0)//the new process is non-real-time process
{
	preempt = QUANTUM;		/* Reset time slice for non-real-time process	*/
 
 }

 
	
 
 
 
//end f Lab3 4.3 





//Lab4 4 (username:lei48, date modified: 10/24/2018)

struct procent *prptr=ptnew;
if(prptr->prsig[SIGTIME].regyes==1&&prptr->xalarm_time<=clktimemilli&&prptr->jump_do_shandler==0)//the receiving process has a call back function registered through signalreg and its stack has previously 
                                                                                                 //   not been modified to jump to do_shandler when the process is scheduled to run next.
                                                                 

 {
     prptr->jump_do_shandler=1;
     
     int* _esp=prptr->prstkptr;//locate stack pointer

    _esp=prptr->prstkptr;

     int* ptr_ret_add=_esp+10;//location where return address is stored
     int* ptr_ret_add_add_1=_esp+11;//location one stack frame above the return address frame
     
 
     *ptr_ret_add_add_1=*ptr_ret_add;//copy return address one frame above
 
     *ptr_ret_add=&do_shandler;//overide return address with do_handler's address
     
 

 
 
 
 
 }







 
 
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
 }
 




/*------------------------------------------------------------------------
 *  resched_cntl  -  Control whether rescheduling is deferred or allowed
 *------------------------------------------------------------------------
 */
status	resched_cntl(		/* Assumes interrupts are disabled	*/
	  int32	defer		/* Either DEFER_START or DEFER_STOP	*/
	)
{
	switch (defer) {

	    case DEFER_START:	/* Handle a deferral request */

		if (Defer.ndefers++ == 0) {
			Defer.attempt = FALSE;
		}
		return OK;

	    case DEFER_STOP:	/* Handle end of deferral */
		if (Defer.ndefers <= 0) {
			return SYSERR;
		}
		if ( (--Defer.ndefers == 0) && Defer.attempt ) {
			resched();
		}
		return OK;

	    default:
		return SYSERR;
	}
}

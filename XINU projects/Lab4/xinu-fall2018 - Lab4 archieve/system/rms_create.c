//rms_create.c
//Lab3 4.1(username:lei48, date modified: 10/03/2018)

#include <xinu.h>

local	int newpid();


pid32	rms_create(
	  void		*funcaddr,	/* Address of the function	*/
	  uint32	ssize,		/* Stack size in bytes		*/
	  rmsparam_t* rmsptr,	/* rms parameters 0		*/
	  char		*name,		/* Name (for debugging)		*/
	  uint32	nargs,		/* Number of args that follow	*/
	  ...
	)
{

//old part from create including variable diclaration and disabling interrup
	uint32		savsp, *pushsp;
	intmask 	mask;    	/* Interrupt mask		*/
	pid32		pid;		/* Stores new process id	*/
	struct	procent	*prptr;		/* Pointer to proc. table entry */
	int32		i;
	uint32		*a;		/* Points to list of args	*/
	uint32		*saddr;		/* Stack address		*/

	mask = disable();

struct procent *prprcpt;//temperary process table entry pointer





//Admission control

//confine 20 <= rms_period <= 1000 


if (rmsptr->rms_period>1000||rmsptr->rms_period<20)
{

 return SYSERR;
 }


float sum=(rmsptr->rms_ct)*1.00/(rmsptr->rms_period);





//traverse process table to add up the sum of prprcpt->prct*1.00/prprcpt->prperiod of all real-time processes
int ii;

for (ii = 0; ii < NPROC; ii++) {
		prprcpt = &proctab[ii];
		if (prprcpt->prstate == PR_FREE||prprcpt->prrms==0) {  /* skip unused slots	and non-real-time processes*/
			continue;
		}
   
   
   
		sum+=prprcpt->prct*1.00/prprcpt->prperiod;
	}

 


 
 
 //compare sum with 0.5
 if (sum>=RMSBOUND)
 {
 
  return SYSERR;
 }

 //end of admission control


 
 
 
 //update priority of the created rms process
 pri16 priority=30000 - rmsptr->rms_period;


 
 
 
	if (ssize < MINSTK)
		ssize = MINSTK;
	ssize = (uint32) roundmb(ssize);
	if ( (priority < 1) || ((pid=newpid()) == SYSERR) ||
	     ((saddr = (uint32 *)getstk(ssize)) == (uint32 *)SYSERR) ) {
		restore(mask);
		return SYSERR;
	}
 
 
 
 
 

	prcount++;
	prptr = &proctab[pid];

	/* Initialize process table entry for new process */
 
 
 //update process table of the rms process
 
 
  //update rms fields
prptr->prrms=1;
prptr->prct=rmsptr->rms_ct;
prptr->prperiod=rmsptr->rms_period;
 
 //end of rms fields update
 


 //Lab2 3.2
 prptr->pgrosscpu = 0;//initialize the cpu usage of a process
 //end of Lab2 3.2
 
 //Lab2 3.3
 prptr->pwaittime=0;
 prptr->pwaitcount=0;
 prptr->pstartwait=0;
 //end of Lab2 3.3
 
 
	prptr->prstate = PR_SUSP;	/* Initial state is suspended	*/
	prptr->prprio = priority;
 
 

 
	prptr->prstkbase = (char *)saddr;
	prptr->prstklen = ssize;
	prptr->prname[PNMLEN-1] = NULLCH;
	for (i=0 ; i<PNMLEN-1 && (prptr->prname[i]=name[i])!=NULLCH; i++)
		;
	prptr->prsem = -1;
	prptr->prparent = (pid32)getpid();
	prptr->prhasmsg = FALSE;

	/* Set up stdin, stdout, and stderr descriptors for the shell	*/
	prptr->prdesc[0] = CONSOLE;
	prptr->prdesc[1] = CONSOLE;
	prptr->prdesc[2] = CONSOLE;

	/* Initialize stack as if the process was called		*/

	*saddr = STACKMAGIC;
	savsp = (uint32)saddr;

	/* Push arguments */
	a = (uint32 *)(&nargs + 1);	/* Start of args		*/
	a += nargs -1;			/* Last argument		*/
	for ( ; nargs > 0 ; nargs--)	/* Machine dependent; copy args	*/
		*--saddr = *a--;	/* onto created process's stack	*/
	*--saddr = (long)INITRET;	/* Push on return address	*/

	/* The following entries on the stack must match what ctxsw	*/
	/*   expects a saved process state to contain: ret address,	*/
	/*   ebp, interrupt mask, flags, registers, and an old SP	*/

	*--saddr = (long)funcaddr;	/* Make the stack look like it's*/
					/*   half-way through a call to	*/
					/*   ctxsw that "returns" to the*/
					/*   new process		*/
	*--saddr = savsp;		/* This will be register ebp	*/
					/*   for process exit		*/
	savsp = (uint32) saddr;		/* Start of frame for ctxsw	*/
	*--saddr = 0x00000200;		/* New process runs with	*/
					/*   interrupts enabled		*/

	/* Basically, the following emulates an x86 "pushal" instruction*/

	*--saddr = 0;			/* %eax */
	*--saddr = 0;			/* %ecx */
	*--saddr = 0;			/* %edx */
	*--saddr = 0;			/* %ebx */
	*--saddr = 0;			/* %esp; value filled in below	*/
	pushsp = saddr;			/* Remember this location	*/
	*--saddr = savsp;		/* %ebp (while finishing ctxsw)	*/
	*--saddr = 0;			/* %esi */
	*--saddr = 0;			/* %edi */
	*pushsp = (unsigned long) (prptr->prstkptr = (char *)saddr);
	restore(mask);
	return pid;
}

/*------------------------------------------------------------------------
 *  newpid  -  Obtain a new (free) process ID
 *------------------------------------------------------------------------
 */
local	pid32	newpid(void)
{
	uint32	i;			/* Iterate through all processes*/
	static	pid32 nextpid = 1;	/* Position in table to try or	*/
					/*   one beyond end of table	*/

	/* Check all NPROC slots */

	for (i = 0; i < NPROC; i++) {
		nextpid %= NPROC;	/* Wrap around to beginning */
		if (proctab[nextpid].prstate == PR_FREE) {
			return nextpid++;
		} else {
			nextpid++;
		}
	}
	return (pid32) SYSERR;
}
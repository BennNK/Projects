/* create.c - create, newpid */

#include <xinu.h>

local	int newpid();

/*------------------------------------------------------------------------
 *  create  -  Create a process to start running a function on x86
 *------------------------------------------------------------------------
 */
pid32	create(
	  void		*funcaddr,	/* Address of the function	*/
	  uint32	ssize,		/* Stack size in bytes		*/
	  pri16		priority,	/* Process priority > 0		*/
	  char		*name,		/* Name (for debugging)		*/
	  uint32	nargs,		/* Number of args that follow	*/
	  ...
	)
{



	uint32		savsp, *pushsp;
	intmask 	mask;    	/* Interrupt mask		*/
	pid32		pid;		/* Stores new process id	*/
	struct	procent	*prptr;		/* Pointer to proc. table entry */
	int32		i;
	uint32		*a;		/* Points to list of args	*/
	uint32		*saddr;		/* Stack address		*/
 
 

	mask = disable();
 
 
 
 //Lab3 4.3 (username:lei48, date modified: 10/03/2018)

if (priority>=29000)//non-real-time processes should have lower priority than real-time processes
{
  return SYSERR;
}
//end of Lab3 4.3
 
 
 
 
 
 
 
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
 
 
 //Lab3 4.3
  //update process table of the non-real-time process
 
 //update rms fields
prptr->prrms=0;
prptr->prct=0;
prptr->prperiod=0;
 
 
 
 //end of rms fields update
 

 
 
 
 //end of Lab3 4.3
 
 
 
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
 
 //Lab4 3 (username:lei48, date modified: 10/24/2018)
  prptr->hasfunc=0; // no call back function registered through reghandler when created
 //end of Lab4 3
 
 //Lab4 4 (username:lei48, date modified: 10/24/2018)
 for (int j=0; j<=2;j++)
 {
        prptr->prsig[j].regyes=0;//initializing signal register flag
 }
 prptr->xalarm_time=99999999;//initialize alarm time to besufficiently large
 prptr->jump_do_shandler=0;//does not jump to do_shandler when context switched in
 
 //end of Lab4 4
 
 
 //Lab3 3.2 (username:lei48, date modified: 10/03/2018)
 
 
 

 
 if(XINUSCHED==2)
 {
 
 
 struct procent *prprcpt;

 uint32 gross_time_temp=0;
 
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
  
  

  
  if (prprcpt->pgrosscpu>gross_time_temp)
  {
  gross_time_temp=prprcpt->pgrosscpu;
  
  }
  curr=queuetab[curr].qnext;
  
  }

 
 
 }
 
 //compare with current process
 struct	procent	*curptr;
 curptr = &proctab[currpid];
 
 
 if (curptr->pgrosscpu+currproctime>gross_time_temp)
  {
  gross_time_temp=curptr->pgrosscpu+currproctime;
  
  }
 
 prptr->pvirtcpu=gross_time_temp;

 prptr->prprio=MAXPRIO-prptr->pvirtcpu;

 
 
 
 }
 
//end of Lab3 3.2
 
 
  
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

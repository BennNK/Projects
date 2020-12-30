/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	send(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg		/* Contents of message		*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process's table entry	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->prhasmsg) {
		restore(mask);
   
   kprintf("\nclktimemilli %d\n", clktimemilli);
   kprintf("pid %d cannot send message\n", currpid);
   
   
		return SYSERR;
	}
 

 
	prptr->prmsg = msg;		/* Deliver message		*/
	prptr->prhasmsg = TRUE;		/* Indicate message is waiting	*/
 
//Lab4 3 (username:lei48, date modified: 10/24/2018)
 
 
////the following part is for debug only
//// int*_espm;
//// 
//// struct	procent *prptr_m;
//// prptr_m = &proctab[3];
//// 
//// _espm=prptr_m->prstkptr;
//// for (int i=1;i<20;i++) 
////{
////
////
////kprintf("0X%08x,     0X%08x\n", _espm, *_espm);
////_espm+=1;
//// 
//// 
//// }
//// end of debugging code
 
 

 
 if (prptr->hasfunc==1)//the receiving process has a call back function registered through reghandler
 {
 
 int* _esp=prptr->prstkptr;//locate stack pointer

_esp=prptr->prstkptr;

 int* ptr_ret_add=_esp+10;//location where return address is stored
 int* ptr_ret_add_add_1=_esp+11;//location one stack frame above the return address frame
 int* ptr_ret_add_add_2=_esp+12;//location of first argument passed to ctxsw
 
 *ptr_ret_add_add_1=*ptr_ret_add;//copy return address one frame above
 
 *ptr_ret_add=&do_handler;//overide return address with do_handler's address
 *ptr_ret_add_add_2=prptr->func_address;//store the address of the call back func
 
 
 
 }

 
 

 
 //end of Lab4 3
 
 
 //Lab4 4 (username:lei48, date modified: 10/24/2018)
 if (prptr->prsig[SIGRECV].regyes==1&&prptr->jump_do_shandler==0)//the receiving process has a call back function registered through signalreg and its stack has previously not been modified to jump to
                                                                 //do_shandler when the process is scheduled to run next.
 {
 
     prptr->jump_do_shandler=1;
    int* _esp=prptr->prstkptr;//locate stack pointer

    _esp=prptr->prstkptr;

     int* ptr_ret_add=_esp+10;//location where return address is stored
     int* ptr_ret_add_add_1=_esp+11;//location one stack frame above the return address frame
     
 
     *ptr_ret_add_add_1=*ptr_ret_add;//copy return address one frame above
 
     *ptr_ret_add=&do_shandler;//overide return address with do_handler's address
     
  

 }

 //end of Lab4 4
 


	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid);
	}
 
 
 
 
 
 
	restore(mask);		/* Restore interrupts */




	kprintf("\nclktimemilli %d\n", clktimemilli);
	kprintf("pid %d can send message to pid %d, msg=%d\n", currpid,pid,msg);
	return OK;
}

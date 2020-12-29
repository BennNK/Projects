/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{


//(username:lei48, date modified: 10/03/2018)
struct procent *prprcpt;
prprcpt = &proctab[currpid];
//(username:lei48, date modified: 10/03/2018)


//Lab2 3.1 and 3.2 (username:lei48, date modified: 09/25/2018) 
static	uint32	count1 = 1;	/* Count to 1 ms	*/
/* Decrement the counter*/

	if((--count1) <= 0) {

		

		clktimemilli++;
    currproctime++;
    
   

		/* Reset the counter*/

		count1 = 1;
	}
 
 
 
//end of Lab2 3.1 and 3.2 (username:lei48, date modified: 09/25/2018)
















//Lab3 3.2 (username:lei48, date modified: 10/03/2018)
if (XINUSCHED==2)
{

if(prprcpt->prprio--<0){prprcpt->prprio=0;}
}

//end of Lab3 3.2







	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			wakeup();
		}
	}


//Lab3 4.3 (username:lei48, date modified: 10/03/2018)


if (prprcpt->prrms==1)//time slice of real-time process counts down from RMSQUANTUM

{
 if((--preempt_rms) <= 0) {
		preempt_rms = RMSQUANTUM;
		resched();
	}


}
	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */
 

 if (prprcpt->prrms==0)//time slice of non-real-time process counts down from QUANTUM
{
	if((--preempt) <= 0) {
		preempt = QUANTUM;
		resched();
	}
 
 }
 
 //end of Lab3 4.3
 
 
 
 
//Lab4 4 (username:lei48, date modified: 10/24/2018)
struct procent *prptr;
prptr = &proctab[currpid];

if(prptr->prsig[SIGXCPU].regyes==1)//SIGXCPU handler
{ 

  if (prptr->pgrosscpu + currproctime>=prptr->prsig[SIGXCPU].optarg)//process reaches the saved cpu usage 
  {

        prptr->prsig[SIGXCPU].regyes=0;//reset registration flag, since one registred call back function can only run once
        typedef void(*pfun)(void);
        pfun xcpu_fun=prptr->prsig[SIGXCPU].fnt;
        
        //restore interrupt
        asm ( 
      "sti;"
          :    //empty
          ://empty
          :       //empty
             );
        xcpu_fun();//call call back function through its address
        //disable interrupt
        asm ( 
      "cli;"
          :    //empty
          ://empty
          :       //empty
            );
    
    

   }
   
 
}





if(prptr->prsig[SIGTIME].regyes==1&&prptr->xalarm_time==clktimemilli)//process registered alarmhandler and has reached the alarm time
{ 


        prptr->prsig[SIGTIME].regyes=0;//reset registration flag
        
       
        
        typedef void(*pfun)(void);
        pfun xtime_fun=prptr->prsig[SIGTIME].fnt;
         
         //restore interrupt
        asm ( 
      "sti;"
          :    //empty
          ://empty
          :       //empty
             );
        xtime_fun();//call call back function through its address
        //disable interrupt
        asm ( 
      "cli;"
          :    //empty
          ://empty
          :       //empty
            );
    
    

   
   
 
}
//end of Lab4 4
 
 

 
 
 
 
 
}

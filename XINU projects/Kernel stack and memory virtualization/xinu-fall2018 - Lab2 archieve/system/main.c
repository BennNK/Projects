/*  main.c  - main */

#include <xinu.h>

process	main(void)
{


//start of declarations of variables for Lab2  (username:lei48, date modified: 09/25/2018)
long proc_time;
struct procent *prprcpt;
prprcpt = &proctab[currpid];
struct procent *null_user_ent;
null_user_ent = &proctab[0];
///end of declarations  (username:lei48, date modified: 09/25/2018)

     
//// (username:lei48, date modified: 09/25/2018) disable the welcome message
//extern void welcome(void);/*put the welcome window in an external location which is welcome.c*/
//welcome();
//// (username:lei48, date modified: 09/25/2018)




//Lab2 3.1 (username:lei48, date modified: 09/25/2018)


//syscalls
sleepms(0);
kprintf("\nmiliseconds since boot:");


//computation
int a=1;
int b=1;
int c;
c=a+b;
    
   //print time 
   kprintf("%d\n",clktimemilli);
   kprintf("seconds since boot: %d\n",clktime);
//end of Lab2 3.1 (username:lei48, date modified: 09/25/2018)
  
    
    

    

////Lab2 3.2, 3.3 (username:lei48, date modified: 09/25/2018)

//printing parameters for main
kprintf("\n\nmain() gains control of the cpu");
kprintf("\nmiliseconds since boot: %d",clktimemilli);
kprintf("\ncurrproctime is %d",currproctime);
proc_time=currproctime+(prprcpt->pgrosscpu);
kprintf("\ngross ms of main() running on cpu is %d",proc_time);
kprintf("\nstart waiting time of main() is %d",prprcpt->pstartwait);
kprintf("\npwaittime of main() is %d",prprcpt->pwaittime);
kprintf("\npwaitcount of main() is %d",prprcpt->pwaitcount);
kprintf("\naverage waiting time of main() is %d",(prprcpt->pwaittime)/(prprcpt->pwaitcount));

//creating test case process (in Lab2_test_fun_1.c)
resume(create(Lab2_test_fun_1,1024,60,"Lab2_test_fun_1",1,currpid));


//printing parameters for main
kprintf("\n\nmain() gains control of the cpu");
kprintf("\nmiliseconds since boot: %d",clktimemilli);
kprintf("\ncurrproctime is %d",currproctime);
proc_time=currproctime+(prprcpt->pgrosscpu);
kprintf("\ngross ms of main() running on cpu is %d",proc_time);
kprintf("\nstart waiting time of main() is %d",prprcpt->pstartwait);
kprintf("\npwaittime of main() is %d",prprcpt->pwaittime);
kprintf("\npwaitcount of main() is %d",prprcpt->pwaitcount);
kprintf("\naverage waiting time of main() is %d",(prprcpt->pwaittime)/(prprcpt->pwaitcount));
////end of Lab2 3.2, 3.3 (username:lei48, date modified: 09/25/2018)

   
  
////Lab2 5.5 (username:lei48, date modified: 09/25/2018)
int i;

for (i=0; i<4; i++ )
{
resume(create(appR3test,1024,INITPRIO,"appR3test",1,0));

}

for (i=0; i<4; i++ )
{
resume(create(appR3test,1024,INITPRIO,"appR3test",1,1));

}

////end of 5.5 (username:lei48, date modified: 09/25/2018)
 
   
   
   
//Lab2 4   (username:lei48, date modified: 09/25/2018)
   
int z;
z=igetpid();    //the wrapper function
kprintf("pid %d", z);
  
  
//end of Lab2 4  (username:lei48, date modified: 09/25/2018)
    
 
    
 /////////////   disable the shell for a clear display of question outputs
    
	/* Run the Xinu shell */
// recvclr();
//	 resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	/* Wait for shell to exit and recreate it */
////////////


	while (TRUE) {
   
   
   ////(username:lei48, date modified: 09/25/2018) disable the shell for a clear display of question outputs
//		receive(); 
//    
//		sleepms(200);
//   
// 		kprintf("\n\nMain process recreating shell\n\n");
//    
//    
//    
//		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
   //(username:lei48, date modified: 09/25/2018) end of disabling shell
   
   
  
   
	}
 

 
 
	return OK;
    
}

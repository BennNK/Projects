/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
//
//
////start of declarations of variables for Lab2  (username:lei48, date modified: 09/25/2018)
//long proc_time;
//struct procent *prprcpt;
//prprcpt = &proctab[currpid];
//struct procent *null_user_ent;
//null_user_ent = &proctab[0];
/////end of declarations  (username:lei48, date modified: 09/25/2018)
//
//     
////// (username:lei48, date modified: 09/25/2018) disable the welcome message
////extern void welcome(void);/*put the welcome window in an external location which is welcome.c*/
////welcome();
////// (username:lei48, date modified: 09/25/2018)
//
//
//
//
////Lab2 3.1 (username:lei48, date modified: 09/25/2018)
//
//
////syscalls
//sleepms(0);
//kprintf("\nmiliseconds since boot:");
//
//
////computation
//int a=1;
//int b=1;
//int c;
//c=a+b;
//    
//   //print time 
//   kprintf("%d\n",clktimemilli);
//   kprintf("seconds since boot: %d\n",clktime);
////end of Lab2 3.1 (username:lei48, date modified: 09/25/2018)
//  
//    
//    
//
//    
//
//////Lab2 3.2, 3.3 (username:lei48, date modified: 09/25/2018)
//
////printing parameters for main
//kprintf("\n\nmain() gains control of the cpu");
//kprintf("\nmiliseconds since boot: %d",clktimemilli);
//kprintf("\ncurrproctime is %d",currproctime);
//proc_time=currproctime+(prprcpt->pgrosscpu);
//kprintf("\ngross ms of main() running on cpu is %d",proc_time);
//kprintf("\nstart waiting time of main() is %d",prprcpt->pstartwait);
//kprintf("\npwaittime of main() is %d",prprcpt->pwaittime);
//kprintf("\npwaitcount of main() is %d",prprcpt->pwaitcount);
//kprintf("\naverage waiting time of main() is %d",(prprcpt->pwaittime)/(prprcpt->pwaitcount));
//
////creating test case process (in Lab2_test_fun_1.c)
//resume(create(Lab2_test_fun_1,1024,60,"Lab2_test_fun_1",1,currpid));
//
//
////printing parameters for main
//kprintf("\n\nmain() gains control of the cpu");
//kprintf("\nmiliseconds since boot: %d",clktimemilli);
//kprintf("\ncurrproctime is %d",currproctime);
//proc_time=currproctime+(prprcpt->pgrosscpu);
//kprintf("\ngross ms of main() running on cpu is %d",proc_time);
//kprintf("\nstart waiting time of main() is %d",prprcpt->pstartwait);
//kprintf("\npwaittime of main() is %d",prprcpt->pwaittime);
//kprintf("\npwaitcount of main() is %d",prprcpt->pwaitcount);
//kprintf("\naverage waiting time of main() is %d",(prprcpt->pwaittime)/(prprcpt->pwaitcount));
//////end of Lab2 3.2, 3.3 (username:lei48, date modified: 09/25/2018)
//
//   
//  
//////Lab2 5.5 (username:lei48, date modified: 09/25/2018)
//int i;
//
//for (i=0; i<4; i++ )
//{
//resume(create(appR3test,1024,INITPRIO,"appR3test",1,0));
//
//}
//
//for (i=0; i<4; i++ )
//{
//resume(create(appR3test,1024,INITPRIO,"appR3test",1,1));
//
//}
//
//////end of 5.5 (username:lei48, date modified: 09/25/2018)
// 
//   
//   
//   
////Lab2 4   (username:lei48, date modified: 09/25/2018)
//   
//int z;
//z=igetpid();    //the wrapper function
//kprintf("pid %d", z);
//  
//  
////end of Lab2 4  (username:lei48, date modified: 09/25/2018)
//    
// 
//    
// /////////////   disable the shell for a clear display of question outputs
//    
//	/* Run the Xinu shell */
//// recvclr();
////	 resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
//	/* Wait for shell to exit and recreate it */
//////////////







////Lab3 3.2 (username:lei48, date modified: 10/03/2018)
//
//int i;
//
//for (i=0; i<4; i++ )
//{
//resume(create(appR3test,1024,INITPRIO,"appR3test",1,0));
////sleepms(500);
//
//}
//
//for (i=0; i<4; i++ )
//{
//resume(create(appR3test,1024,INITPRIO,"appR3test",1,1));
//sleepms(500);
//}


//end of Lab3 3.2 




//Lab3 4.3 debug (username:lei48, date modified: 10/03/2018)
//int i;
//
//rmsparam_t* rmsptr;
//rmsptr->rms_ct=20;
//rmsptr->rms_period=50;
//
//
//for(i=0; i<4; i++)
//{
//resume(rms_create(rms_debug,1024,rmsptr,"rms_debug",0));
////kprintf("\ni= %d\n",i);
//}
//end of debug



////Lab3 4.4 (username:lei48, date modified: 10/03/2018)
//
//

//rmsparam_t* rmsptr;
//uint32 x=499;
//uint32 y=1000;
//rmsptr->rms_ct=x;
//rmsptr->rms_period=y;
//resume(rms_create(rms_app,1024,rmsptr,"rms_app",2,x,y));


//end of Lab3 4.4 debug



////Lab3 4.5 (username:lei48, date modified: 10/03/2018)
//
////creating real-time processes
//struct procent *prprcpt;
//prprcpt = &proctab[currpid];
//
//prprcpt->prprio=29999;
//
//uint32 x=50;
//uint32 y=800;
//
//rmsparam_t *rmsptr;
//rmsptr->rms_ct=x;
//rmsptr->rms_period=y;
//
//int i;
//
//
//for (i=0; i<4; i++ )
//
//     {
//      resume(rms_create(rms_app,1024,rmsptr,"rms_app",2,x,y));
//      x+=25;
//      y+=50;
//      rmsptr->rms_ct=x;
//      rmsptr->rms_period=y;
//     } 
//
////creating CPU-bound processes
//int ii;
//
//for (ii=0; ii<4; ii++ )
//{
//resume(create(appR3test,1024,INITPRIO,"appR3test",1,0));
//}
//
//
//
//
//
//
//
////end of Lab3 4.5




//Lab4 3 (username:lei48, date modified: 10/24/2018)

//Lab4 3 declaration, comment it if testing problem 4
//struct procent *prptr;
//prptr = &proctab[currpid];
//prptr->prprio=2000;
//end of Lab4 3 declaration

//case 3 (comment it if running other cases in Lab 4)
//resume(create(Lab4_3_debug,1024,20,"Lab4_3_debug",1,1));
//end of case 3

//Lab4 3 registration function, comment it if testing problem 4
//if (reghandler(&myrcv) != OK) {
//      kprintf("recv handler registration failed\n");
//      return SYSERR;
//   }
//end of Lab4 3 registration function

//case 1 (comment it if running other cases in Lab 4)
//resume(create(Lab4_3_debug,1024,20,"Lab4_3_debug",1,1));
//end of case 1

//case 2 (comment it if running other cases in Lab 4)
//resume(create(Lab4_3_debug,1024,20,"Lab4_3_debug",1,1));
//resume(create(Lab4_3_debug,1024,20,"Lab4_3_debug",1,2));
//sleepms(500);
//end of case 2


//end of Lab4 3



//Lab4 4 (username:lei48, date modified: 10/24/2018)

//Lab4 4 declaration, comment it if testing problem 3
//struct procent *prptr;
//prptr = &proctab[currpid];
//prptr->prprio=2000;
//end of Lab4 3 declaration

////xcpu register
// if (signalreg(SIGXCPU,&userhandler,2500) != OK) {
//      kprintf("xcpu handler registration failed\n");
//      return SYSERR;
//   }

////message receive register
//if (signalreg(SIGRECV,&myrcv,0) != OK) {
//      kprintf("rcv handler registration failed\n");
//      return SYSERR;
//   }
   
////alarm register
//if (signalreg(SIGTIME,&useralarm,0) != OK) {
//      kprintf("alarm handler registration failed\n");
//      return SYSERR;
//   }
//   
   

//Testing three cases on SIGXCPU

//case1 (comment it if running other cases in Lab 4)
//nothing
//end of case 1

//case2 (comment it if running other cases in Lab 4)
//sleepms(500);
//end of case 2

//case3 (comment it if running other cases in Lab 4)
//resume(create(Lab4_4_XCPU,1024,INITPRIO,"Lab4_4_XCPU",0));
//end of case 3

//end of Testing three cases on SIGXCPU




//Testing SIGTIME

//case1 (comment it if running other cases in Lab 4)
//   xalarm(500);
//end of case 1

//case2 (comment it if running other cases in Lab 4)
//   xalarm(500);
//sleepms(5000);
//end of case 2

//case3 (comment it if running other cases in Lab 4)
//   xalarm(500);
//resume(create(Lab4_4_XCPU,1024,INITPRIO,"Lab4_4_XCPU",0));
//end of case 3
//end of Testing SIGTIME



//Testing concurrent processes (comment it if running other cases in Lab 4)
 
//resume(create(Lab4_3_debug,1024,INITPRIO,"Lab4_3_debug",1,1));
//resume(create(Lab4_4_conc_1,1024,INITPRIO,"Lab4_4_conc_1",0));
//resume(create(Lab4_4_conc_2,1024,INITPRIO,"Lab4_4_conc_2",0));

//end of Testing concurrent processes




//end of Lab4 4







//(username: lei48, date modified: 10/03/2018)  
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

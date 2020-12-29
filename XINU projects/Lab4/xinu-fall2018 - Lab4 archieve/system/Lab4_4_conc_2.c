//Lab4_4_conc_2.c
//Lab4 4 (username:lei48, date modified: 10/24/2018)
#include <xinu.h>

void Lab4_4_conc_2()
{


   
  //alarm register
if (signalreg(SIGTIME,&useralarm,0) != OK) {
      kprintf("alarm handler registration failed\n");
      return SYSERR;
   }
   
   xalarm(5000); 
   
   
while(1)

{



}




}












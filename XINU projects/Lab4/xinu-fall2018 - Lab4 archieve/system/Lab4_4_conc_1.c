//Lab4_4_conc_1.c
//Lab4 4 (username:lei48, date modified: 10/24/2018)
#include <xinu.h>

void Lab4_4_conc_1()
{

   //xcpu register
 if (signalreg(SIGXCPU,&userhandler,500) != OK) {
      kprintf("xcpu handler registration failed\n");
      return SYSERR;
   }


   
  
   
   
while(1)

{



}




}
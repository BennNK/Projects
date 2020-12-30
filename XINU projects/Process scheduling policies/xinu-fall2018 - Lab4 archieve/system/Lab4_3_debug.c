//Lab4_3_debug.c
//Lab4 3 (username:lei48, date modified: 10/24/2018)
#include <xinu.h>

void Lab4_3_debug(int32 msg)
{


struct procent *prptr;
prptr = &proctab[currpid];
struct procent *prptr_main;
prptr_main = &proctab[3];

   
  
   kprintf("\nclktimemilli %d\n", clktimemilli);
   kprintf("pid %d\n", currpid);
   kprintf("sending message to main(), msg=%d\n", msg);
   send(3,msg);//send message to main()
   
   
   
while(1)

{



}

return;



}
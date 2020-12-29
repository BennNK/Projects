//do_shandler.c
//Lab4 4 (username:lei48, date modified: 10/24/2018)
#include <xinu.h>

void do_shandler(void)
{
struct	procent *prptr;
prptr = &proctab[currpid];

int* _esp=prptr->prstkptr;//locate stack pointer
_esp=prptr->prstkptr;

int* ptr_ret_add_add_2=_esp+12;//location of first argument passed to ctxsw

    

if (prptr->prsig[SIGRECV].regyes==1&&prptr->prhasmsg == TRUE)
{
*ptr_ret_add_add_2=prptr->prsig[SIGRECV].fnt;//store the address of the call back func

//call call back function through its assdress
asm ( 
      "sti;"
      "call * 8(%%ebp);"
      "cli;"



          :    //empty
          ://empty
          :       //empty
);



}



if (prptr->prsig[SIGTIME].regyes==1&&prptr->xalarm_time<=clktimemilli)
{

 prptr->prsig[SIGTIME].regyes=0;
*ptr_ret_add_add_2=prptr->prsig[SIGTIME].fnt;//store the address of the call back func



//call call back function through its assdress
asm ( 
      "sti;"
      "call * 8(%%ebp);"
      "cli;"



          :    //empty
          ://empty
          :       //empty
);



}

prptr->jump_do_shandler=0;//mark this flag 0, since the process can jump back into do_shandler in the future again
return;


}
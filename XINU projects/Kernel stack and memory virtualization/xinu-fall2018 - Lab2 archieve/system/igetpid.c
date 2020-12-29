//(username:lei48, date modified: 09/25/2018)

#include <xinu.h>

int igetpid()
{


int ipid;//variable receiving eax returning value
asm ( "movl $3, %%eax;" //interruption number
"int $33;"//dispatcher number
          :"=a"(ipid)    //return eax content to ipid
          ://empty
          :       //empty
);

return ipid;

}





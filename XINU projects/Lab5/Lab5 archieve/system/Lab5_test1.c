//Lab5_test1.c
#include <xinu.h>

void Lab5_test1()
{



  char * a=vgetmem(4096*2);
  kprintf("\na %d\n",a);
  
  
  
  
  
  	char		*blockptr=4097*4096;
	uint32	size_in_bytes=4096;
  
  vfreemem(blockptr,size_in_bytes);
  
  
  get_faults();
  
 
  
  
  
  
  
  
  

    
    return;
    
}
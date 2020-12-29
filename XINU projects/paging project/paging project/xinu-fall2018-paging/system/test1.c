//test1.c chen2240 lab5

#include <xinu.h>

void test1()
{

for(int i=0;i<3;i++)
{
  char * test1 =vgetmem(2000);// test vgetmem
  
  kprintf("\ntest1 address %d\n",test1);
}
  

    
  
    
}
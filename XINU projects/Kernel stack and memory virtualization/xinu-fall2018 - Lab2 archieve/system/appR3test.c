
//(username:lei48, date modified: 09/25/2018)
#include <xinu.h>


void appR3test(int proctype)
{

struct procent *prprcpt;
prprcpt = &proctab[currpid];

int i;
int j;
int LOOP1;
int LOOP2;

if (proctype==0)
{
LOOP1=10;
LOOP2=2000000;
}
if (proctype==1)
{
LOOP1=150;
LOOP2=50000;
}



for (i=0; i<LOOP1; i++)
{
   for (j=0; j<LOOP2; j++){}


if(proctype == 1) // I/O-bound process: IOSLEEP determines blocking to computation ratio.

sleepms(IOSLEEP);

}


kprintf("\n\npid %d\n",currpid);
kprintf("proctype %d\n", proctype);
kprintf("clktimemilli %d\n", clktimemilli);
kprintf("gross cpu usage %d ms\n",currproctime+prprcpt->pgrosscpu);
kprintf("average waiting time %d ms\n\n",prprcpt->pwaittime/prprcpt->pwaitcount);



}
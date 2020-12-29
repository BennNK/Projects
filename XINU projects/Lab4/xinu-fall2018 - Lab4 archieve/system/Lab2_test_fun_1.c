//Lab2_test_fun_1.c


#include <xinu.h>

void Lab2_test_fun_1()
{
long proc_time;
struct procent *prprcpt;
prprcpt = &proctab[currpid];
struct procent *p_parent;
p_parent = &proctab[prprcpt->prparent];


//printing out status of main() and this test process
kprintf("\n\nLab2_test_fun_1() gains control of the cpu");
kprintf("\nmiliseconds since boot: %d",clktimemilli);
kprintf("\ncurrproctime is %d",currproctime);
proc_time=currproctime+(prprcpt->pgrosscpu);
kprintf("\ngross ms of Lab2_test_fun_1() is %d",proc_time);
kprintf("\nstart waiting time of Lab2_test_fun_1() is %d",prprcpt->pstartwait);
kprintf("\npwaittime of Lab2_test_fun_1() is %d",prprcpt->pwaittime);
kprintf("\npwaitcount of Lab2_test_fun_1() is %d",prprcpt->pwaitcount);
kprintf("\naverage waiting time of Lab2_test_fun_1() is %d",(prprcpt->pwaittime)/(prprcpt->pwaitcount));



kprintf("\ngross ms of main() is %d\n",p_parent->pgrosscpu);
kprintf("\nstart waiting time of main() is %d",p_parent->pstartwait);
kprintf("\npwaitcount of main() is %d",p_parent->pwaitcount);







//some calculations and syscalls
int a=1;
int b=2;
int c;
c=a+b;
kprintf("\n\nthis is a syscall\n\n");



//printing out status again


kprintf("\n\nafter calculations and syscalls in Lab2_test_fun_1()");
kprintf("\nmiliseconds since boot: %d",clktimemilli);
kprintf("\ncurrproctime is %d",currproctime);
proc_time=currproctime+(prprcpt->pgrosscpu);
kprintf("\ngross ms of Lab2_test_fun_1() is %d",proc_time);
kprintf("\nstart waiting time of Lab2_test_fun_1() is %d",prprcpt->pstartwait);
kprintf("\npwaittime of Lab2_test_fun_1() is %d",prprcpt->pwaittime);
kprintf("\npwaitcount of Lab2_test_fun_1() is %d",prprcpt->pwaitcount);
kprintf("\naverage waiting time of Lab2_test_fun_1() is %d",(prprcpt->pwaittime)/(prprcpt->pwaitcount));


kprintf("\ngross ms of main() is %d",p_parent->pgrosscpu);
kprintf("\nstart waiting time of main() is %d",p_parent->pstartwait);
kprintf("\npwaitcount of main() is %d",p_parent->pwaitcount);

return;

}
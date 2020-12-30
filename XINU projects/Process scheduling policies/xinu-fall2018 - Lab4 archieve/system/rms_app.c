//
// Lab3 4.4(username:lei48, date modified: 10/03/2018)
//

#include <xinu.h>

void rms_app(uint32 x, uint32 y)
{
struct procent *prprcpt;
prprcpt = &proctab[currpid];
int period_number=0;
int outer_loop=20;
uint32 comp_temp;
    
    while (outer_loop--)//outer loop
    {
    uint32 period_start=clktimemilli;
    uint32 grosscpu_start=prprcpt->pgrosscpu;
    uint32 comp_received=0;
    period_number++;
    comp_temp=0;
         
         while(1)//inner loop
         { 
         
         if (currproctime!=0)
            {
            comp_temp=currproctime;
            }
            
         if (currproctime==0)
         {
           comp_received+=comp_temp;
           comp_temp=0;
           
         }

         
         //comp_received=prprcpt->pgrosscpu+currproctime-grosscpu_start;
         
         
            if(clktimemilli - period_start < y&&comp_received + currproctime>=x)
            {
            
            
            //PID, x, y, period number, clktimemilli, and y - (clktimemilli - period_start)
            
            
               kprintf("\npid %d\n", currpid);
               kprintf("x=%d\n", x);
               kprintf("y=%d\n", y);
               kprintf("period number %d\n", period_number);
               
             //  kprintf("period_start %d\n", period_start);
               
               
               
               kprintf("clktimemilli %d\n", clktimemilli);
               kprintf("y - (clktimemilli - period_start) %d\n", y - (clktimemilli - period_start));
               
              // kprintf("comp_received %d\n", comp_received);
               //kprintf("currproctime %d\n", currproctime);
               
               sleepms(y - (clktimemilli - period_start));
               
               break;
            }
         
            if(clktimemilli - period_start > y&&comp_received + currproctime<x)
            {
            
            //PID, x, y, period number, clktimemilli, and y - (clktimemilli - period_start)
               kprintf("\npid %d\n", currpid);
               kprintf("x=%d\n", x);
               kprintf("y=%d\n", y);
               kprintf("period number %d\n", period_number);
               kprintf("clktimemilli %d\n", clktimemilli);
               kprintf("y - (clktimemilli - period_start) %d\n", y - (clktimemilli - period_start));
               
               kprintf("deadline violation");
               return;
            }
         
         
         }
    
    
    }
    return;
    
}

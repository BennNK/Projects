//Lab5 chen2240
//pfhandler.c

#include <xinu.h>

unsigned long temp1;
// get the faulted address

unsigned long get_cr2(void) 
{

  unsigned long temp2;
 
  
  asm("cli");
  asm("push %eax");
  asm("mov %cr2, %eax");
  asm("mov %eax, temp1");
  asm("pop %eax");
  temp2 = temp1;
  asm("sti");
  return temp2;
}




void pfhandler(void) 
{
        wait(vmem_sem);
        
        pt_t * pt;
        int t=-1;
        int i;
        unsigned long a,p,q;
        int vp;
       
        
        pd_t* pd = (pd_t*) ((FRAME0 + proctab[currpid].pdb_frame) * 4096);// current PAGE DIRECTORY
        
        
         a=get_cr2(); // Get the faulted address from cr2.
        
        //hook_pfault(a);

         pfnum++;// inrease page fault num
         //int hookpfnum= get_faults();


        
         vp=a>>12;// faulted pagenum
        
        

        if (vp-4096>proctab[currpid].vheapsize) // check vp is valid
        {
                signal(vmem_sem);
                kill(currpid);
                return;
        }
        // upper ten bits of a.
        p = a>>22;
        
        // bits [21:12] of a.
        
        q = (a>>12)&0x3FF;
       
        
        if (pd[p].pd_pres) // if page table present, 
        {
        
           pt =(pt_t *)(pd[p].pd_base*4096);
        
        }
        else  // if not obtain a new frame
        {
             
                if ((t = findfframe(1))!=SYSERR) 
                {
                invert_ptab[t].pid = currpid;
                invert_ptab[t].used = 1;
                invert_ptab[t].type = 1;
                pd[p].pd_pres = 1;
                pd[p].pd_base = FRAME0 + t;
                pt = (pt_t *) (pd[p].pd_base * 4096);

                for (i = 0; i < 1024; i++) 
                      {
                        pt[i].pt_pres = 0;
                        pt[i].pt_write = 1;
                        pt[i].pt_user = 0;
                        pt[i].pt_pwt = 0;
                        pt[i].pt_pcd = 0;
                        pt[i].pt_acc = 0;
                        pt[i].pt_dirty = 0;
                        pt[i].pt_mbz = 0;
                        pt[i].pt_global = 0;
                        pt[i].pt_avail = 0;
                        pt[i].pt_base = 0;
                      }

                hook_ptable_create(pd[p].pd_base - FRAME0);
                
                }
                else
                {
                        signal(vmem_sem);
                        return;
                }
        }

      
    
    
     
 int nf = pd[p].pd_base-1024;// num of frame for the page table
        
        invert_ptab[nf].pagecount++;

   // new frame for page 
        int f;
        if ((f= findfframe(0))!=SYSERR) 
        
        {
        
        invert_ptab[f].used = 1;
        invert_ptab[f].type = 0;
        invert_ptab[f].pid = currpid;
       
       // set the page base
        pt[q].pt_pres = 1;
        pt[q].pt_base = FRAME0 + f;

        signal(vmem_sem);
        
        //kprintf("pagecount is %d, pid is %d\n",invert_ptab[nf].pagecount,currpid);
        
        return;
        
        
        
        }

        
        else {//if no page present, this page table is no longer useful
                if (t!= -1) 
                {
                        invert_ptab[t].used = 0;
                        pd[p].pd_pres = 0;
                }
                signal(vmem_sem);
                return;
        }
        
        
        
        
        
        
        

     
        
}
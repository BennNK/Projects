//Lab5
//pf_handler.c

#include <xinu.h>

unsigned long _cr2;

void pf_handler(void) {
        
        wait(pgft_sem);
        
        pt_t * p_tab;
        
        pf_counter++;//used for get_fautlt()
  
        unsigned long a;
        
        //reading cr2

        asm(
        "cli;"
        "push %%ebp;" 
        "mov %%esp, %%ebp;"
        "push %%eax;"
        "mov %%cr2, %%eax;"
        "mov %%eax, _cr2;"
        "pop %%eax;"
        "mov %%ebp, %%esp;"
        "pop %%ebp;"
        "sti;"
         : //empty
          ://empty
          :       //empty
  
        );
        

        a = _cr2;
        
        hook_pfault((char*) a);

        // a, vp etc. are variables whose usage are described in the handout
        int vp = a>>12;

        //reading cr3
        int _pdbr;
        asm("\t movl %%cr3,%0" : "=r"(_pdbr));
        pd_t * p_dir = (pd_t *) _pdbr;
        
        // if vp is valid or not
        if (vp<4096||vp>4096+proctab[currpid].hsize) 
        {
                signal(pgft_sem);
                kill(currpid);
                return;
        }
        
        int p = a >> 22;
        int q = a >> 12 & 1023;
        
        int ff;
        if (p_dir[p].pd_pres == 0) {//page table not present
                
                //finding a new frame from 1024-2023 to hold the missing page table
                ff=findfframe();
                if (ff == SYSERR) 
                {
                        signal(pgft_sem);
                        return;
                }
                
                p_dir[p].pd_pres = 1;
                p_dir[p].pd_base = FRAME0 + ff;
                
                hook_ptable_create(p_dir[p].pd_base);
                
                p_tab = (pt_t *) (p_dir[p].pd_base * NBPG);
                
                ipagetab[ff].used = 1;
                ipagetab[ff].type = PAGETABLE;
                ipagetab[ff].pid = currpid;
                ipagetab[ff].ref_count = 0;

                
               int i;
               //setup the new page table
                for (i = 0; i < PAGETABSIZE; i++)
                 {
                        p_tab[i].pt_pres = 0;
                        p_tab[i].pt_write = 1;
                        p_tab[i].pt_user = 0;
                        p_tab[i].pt_pwt = 0;
                        p_tab[i].pt_pcd = 0;
                        p_tab[i].pt_acc = 0;
                        p_tab[i].pt_dirty = 0;
                        p_tab[i].pt_mbz = 0;
                        p_tab[i].pt_global = 0;
                        p_tab[i].pt_avail = 0;
                        p_tab[i].pt_base = 0;
                }


                
        }
        
        //pt points to the address in bytes of the new page table
       p_tab = (pt_t *) (p_dir[p].pd_base * NBPG);
    

        int fp=findfpage();
        if (fp == SYSERR)
         {
                if (ff != SYSERR) //an empty page table has been installed but no free frame to map the page
                {
                        ipagetab[ff].used = 0;
                        p_dir[p].pd_pres = 0;
                        
                        hook_ptable_delete(ipagetab[ff].frame_number);
                }
                signal(pgft_sem);
                return;
        }
        else 
        {
            ipagetab[p_dir[p].pd_base - FRAME0].ref_count++;//this page table succeeded in mapping a new page, thus ref_count++.

        //obtained frame f to hold the page
        p_tab[q].pt_pres = 1;
        p_tab[q].pt_base = FRAME0 + fp;
        ipagetab[fp].used = 1;
        ipagetab[fp].type = PAGE;
        ipagetab[fp].virtual_page_number = vp;
        ipagetab[fp].pid = currpid;
        }



        
        signal(pgft_sem);
        //kprintf("ipagetab[m].ref_count %d, currpid %d\n",ipagetab[m].ref_count,currpid);
        
        return;

        
}
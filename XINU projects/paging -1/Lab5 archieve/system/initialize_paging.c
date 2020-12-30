//initialize_paging.c
//Lab5 (lei48 11/09/2018)

#include <xinu.h>

unsigned long p;

 void initialize_paging()
{


	// initialize inverted_frame_table structure
	int i, j;
	for(i = 0; i < NFRAMES; i++) 
  {
		ipagetab[i].frame_number = i;
		ipagetab[i].virtual_page_number = -1;
		ipagetab[i].type = -1;
    ipagetab[i].used = 0;
	}

	

	// create 5 page tables and map pages 0 through 4095 and pages above 0x90000000
	for (i = 0; i < 5; i++) 
  {
		pt_t * p_tab = (pt_t *) ((FRAME0 + i) * NBPG);
		ipagetab[i].used = 1;
		ipagetab[i].type = PAGETABLE;
    ipagetab[i].pid = 0;
		ipagetab[i].ref_count = PAGETABSIZE;
		for (j = 0; j < PAGETABSIZE; j++) 
    {
			p_tab[j].pt_pres = 1;
			p_tab[j].pt_write = 1;
			p_tab[j].pt_user = 0;
			p_tab[j].pt_pwt = 0;
			p_tab[j].pt_pcd = 0;
			p_tab[j].pt_acc = 0;
			p_tab[j].pt_dirty = 0;
			p_tab[j].pt_mbz = 0;
			p_tab[j].pt_global = 0;
			p_tab[j].pt_avail = 0;
			p_tab[j].pt_base = (i * PAGETABSIZE + j);
      if (i==4)
      {
         p_tab[j].pt_base = (0x90000000 + j * NBPG) / NBPG;
      }
      
		}
   
    //hook_ptable_create(ipagetab[i].frame_number+FRAME0);
	}



	// Setup page direcory for null process
	pd_t * p_dir = (pd_t *) ((FRAME0 + ipagetab[5].frame_number) * NBPG);

	ipagetab[5].used = 1;
	ipagetab[5].type = PAGEDIRECTORY;
  ipagetab[i].pid = 0;
	for(i = 0; i < PAGEDIRSIZE; i++) {
		p_dir[i].pd_pres = 0;
		p_dir[i].pd_write = 1;
		p_dir[i].pd_user = 0;
		p_dir[i].pd_pwt = 0;
		p_dir[i].pd_pcd = 0;
		p_dir[i].pd_acc = 0;
		p_dir[i].pd_fmb = 0;
		p_dir[i].pd_mbz = 0;
		p_dir[i].pd_global = 0;
		p_dir[i].pd_avail = 0;
		p_dir[i].pd_base = 0;
		if (i < 4) 
    {
			p_dir[i].pd_pres = 1;
			p_dir[i].pd_base = FRAME0 + ipagetab[i].frame_number;
		}
		if (i == 576)  
    {
			p_dir[i].pd_pres = 1;
			p_dir[i].pd_base = FRAME0 + ipagetab[4].frame_number;
		}
		
	}


	// Set the cr3 register
 p=(1024+ipagetab[5].frame_number)*NBPG;
asm ( 
      "cli;"
      "push %%ebp;" 
      "mov %%esp, %%ebp;"
      "push %%eax;" 
      "mov p, %%eax;"
      "mov %%eax, %%cr3;"
      "pop %%eax;"
      "mov %%ebp, %%esp;"
      "pop %%ebp;"
      "sti;"
          : //empty
          ://empty
          :       //empty
);
 


	// set exception vector 14 to be page fault service routine
	set_evec(14, (unsigned int) pfisr);
 
 
 //set cr0 register bit and enable paging
asm ( 
      "cli;"
      "push %%ebp;" 
      "mov %%esp, %%ebp;"
      "or $0x80000000, %%eax;"
      "mov %%eax, %%cr0;"
      "mov %%ebp, %%esp;"
      "pop %%ebp;"
      "sti;"
          : //empty
          ://empty
          :       //empty
);
 

	return;
}
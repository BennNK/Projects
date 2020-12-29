//chen 2240 lab 5 initialize_paging.c


#include <xinu.h>

unsigned long temp;

void write_pdbr(long address) 
{
  asm("cli");
  temp = address;
  asm("push %eax");
  asm("mov temp, %eax");		
  asm("mov %eax, %cr3");
  asm("pop %eax");
  asm("sti");

}

void enable_paging() {
  
  asm("cli");
  asm("push %ebp");
  asm("mov %esp, %ebp");
  asm("mov %cr0, %eax");
  asm("or $0x80000000, %eax");
  asm("mov %eax, %cr0");
  asm("mov %ebp, %esp");
  asm("pop %ebp");
  asm("sti");

}





sid32	vmem_sem;
frame_tab	invert_ptab[NFRAMES];
uint32 pfnum;



 void initialize_paging()
{
		int i, j;
	
  
  vmem_sem = semcreate(1);
  pfnum = 0;
	// initiaize inverted page table
  for(i = 0; i < NFRAMES; i++) {
		invert_ptab[i].f_id = i;
		invert_ptab[i].used = 0;
		invert_ptab[i].pid = -1;
		invert_ptab[i].type = -1;
		invert_ptab[i].pagecount= 0;
	
	}



	// map global 16MB.
	 for (i = 0; i < 4; i++) 
   {
    invert_ptab[i].used = 1;
		invert_ptab[i].type = 1;
	  invert_ptab[i].pagecount= 1024;
    invert_ptab[i].pid = 0;
    
       
   	pt_t * pagetab = (pt_t *) ((FRAME0 + i) * 4096);
		for (j = 0; j < 1024; j++) 
    {
			pagetab[j].pt_pres = 1;
			pagetab[j].pt_write = 1;
			pagetab[j].pt_user = 0;
			pagetab[j].pt_pwt = 0;
			pagetab[j].pt_pcd = 0;
			pagetab[j].pt_acc = 0;
			pagetab[j].pt_dirty = 0;
			pagetab[j].pt_mbz = 0;
			pagetab[j].pt_global = 0;
			pagetab[j].pt_avail = 0;
			pagetab[j].pt_base = (i * 1024 + j);
			 
		}
	}

	// map device memory

	invert_ptab[4].used = 1;
	invert_ptab[4].type = 1;
	invert_ptab[4].pagecount= 1024;
  invert_ptab[i].pid = 0;
 	pt_t * pagetab = (pt_t *) ((FRAME0 + invert_ptab[4].f_id) * 4096);
  
	for (j = 0; j < 1024; j++) 
  {
		pagetab[j].pt_pres = 1;
		pagetab[j].pt_write = 1;
		pagetab[j].pt_user = 0;
		pagetab[j].pt_pwt = 0;
		pagetab[j].pt_pcd = 0;
		pagetab[j].pt_acc = 0;
		pagetab[j].pt_dirty = 0;
		pagetab[j].pt_mbz = 0;
		pagetab[j].pt_global = 0;
		pagetab[j].pt_avail = 0;
		pagetab[j].pt_base = (0x90000000 + j * 4096) / 4096;
		
	}

	
	


	invert_ptab[5].used = 1;// page directory for the NULL process.
	invert_ptab[5].type = 2;
  pd_t * pagedir = (pd_t *) ((FRAME0 + 5) * 4096);
	
	for(i = 0; i <1024; i++) {
		pagedir[i].pd_pres = 0;
		pagedir[i].pd_write = 1;
		pagedir[i].pd_user = 0;
		pagedir[i].pd_pwt = 0;
		pagedir[i].pd_pcd = 0;
		pagedir[i].pd_acc = 0;
	  pagedir[i].pd_mbz = 0;
   	pagedir[i].pd_fmb = 0;
		pagedir[i].pd_global = 0;
		pagedir[i].pd_avail = 0;
		pagedir[i].pd_base = 0;
   }
		for(i = 0; i <4; i++) 
    {
			pagedir[i].pd_pres = 1;
			pagedir[i].pd_base = FRAME0+i;
		}
	
			pagedir[576].pd_pres = 1;
			pagedir[576].pd_base = FRAME0+4;

	// Set the PDBR register 
	write_pdbr(1029*4096);

	
	set_evec(14, (unsigned int) pfisr);

	enable_paging();
	
	return;
}



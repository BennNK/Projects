//vfreemem.c
//Lab5 (lei48 11/09/2018)

#include <xinu.h>

syscall	vfreemem(
	char		*blockptr,	/* Pointer to memory block	*/
	uint32	size_in_bytes		/* Size of block in bytes	*/
)
{
	
	//the vfreemem follows freemem scheme
	struct	memblk	*virtual_memlist, *next, *prev, *block;
	uint32	top;

	
	if ((size_in_bytes == 0) || ((uint32) blockptr < (uint32) (4096 * NBPG))
	|| ((uint32) blockptr > (uint32) (proctab[currpid].hsize + 4096) * NBPG)) {
		
		return SYSERR;
	}

	size_in_bytes = (uint32) roundmb(size_in_bytes);	/* Use memblk multiples	*/
	block = (struct memblk *)blockptr;

	virtual_memlist = &proctab[currpid].virtual_memlist;
	prev = virtual_memlist;
	next = virtual_memlist->mnext;
	while ((next != NULL) && (next < block)) {
		prev = next;
		next = next->mnext;
	}

	if (prev == virtual_memlist) {		/* Compute top of previous block*/
		top = (uint32) NULL;
	} else {
		top = (uint32) prev + prev->mlength;
	}

	/* Ensure new block does not overlap previous or next blocks	*/

	if (((prev != virtual_memlist && (uint32) block < top)
	|| ((next != NULL)	&& (uint32) block+size_in_bytes>(uint32)next))) {
		
	
		return SYSERR;
	}

	virtual_memlist->mlength += size_in_bytes;

	/* Either coalesce with previous block or add to free list */

	if (top == (uint32) block) { 	/* Coalesce with previous block	*/
		prev->mlength += size_in_bytes;
		block = prev;
	} else {			/* Link into list as new node	*/
		block->mnext = next;
		block->mlength = size_in_bytes;
		prev->mnext = block;
	}

	/* Coalesce with next block if adjacent */

	if (((uint32) block + block->mlength) == (uint32) next) {
		block->mlength += next->mlength;
		block->mnext = next->mnext;
	}
 
 //block is now a pointer pointing to the new node in the free list
 
 
// the following code check if there are pages that are entirely freed from the above operation

wait(pgft_sem);
int it= (int)block;
 float blka_pl8=(float)it+8.0;
 
 
 int vpg_ad=((int)(blka_pl8/4096.0)+1 )*  NBPG;//find the first virtual page above the block address that has nothing to do with the block node

 
 int free_space=(int)block+block->mlength-vpg_ad+1;//how many free bytes are there in this block beyond the vpg_ad

 
 float f=(float)free_space;
 int num_pg_to_free=(int)(f/4096.0);//number of physical pages to be marked unused
 
 int _pdbr;
 asm("\t movl %%cr3,%0" : "=r"(_pdbr));//read cr3
 
 pd_t * pd = (pd_t *) _pdbr;
 
 //find the address of each physical page to free and mark them as unused
 for(int k=0;k<num_pg_to_free;k++)
 {
 
      
     int p =(int) ((float)vpg_ad/(4096.0*1024.0));
     
     int q= (vpg_ad/NBPG)%1024;
     
     pt_t * pt = (pt_t *) (pd[p].pd_base * NBPG);
     
     if(ipagetab[pt[q].pt_base-FRAME0].used==1)//if the page is marked used, delete it
     {
     
     ipagetab[pt[q].pt_base-FRAME0].used=0;
     ipagetab[pd[p].pd_base-FRAME0].ref_count--;
     
        if(ipagetab[pd[p].pd_base-FRAME0].ref_count<=0)
        {
           ipagetab[pd[p].pd_base-FRAME0].used=0;//delete the page table if all of its pages are deleted
           hook_ptable_delete(ipagetab[pd[p].pd_base-FRAME0].frame_number);
        }
        
        
     }
     
     
     
     vpg_ad+=NBPG;
 
 
 
 }
 
 signal(pgft_sem);
 
	
 

 
 
	return OK;

}

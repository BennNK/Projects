//vgetmem.c
//Lab5 (lei48 11/09/2018)


#include <xinu.h>

char  	*vgetmem(//return the starting address of the allocated virtual pages
	uint32	nbytes		/* Size of memory requested	*/
)
{
 
	struct	memblk		*virtual_memlist, *prev, *curr, *leftover;
  struct	procent *prptr;
  prptr=&proctab[currpid];

 if (nbytes>prptr->hsize*NBPG)
 {
   return (char *) SYSERR;
   
 }

	if (nbytes == 0) 
  {

		kprintf("nbytes = 0\n");

		return (char *)SYSERR;
	}

	nbytes = (uint32) roundmb(nbytes);	/* Use memblk multiples	*/

	//initializing the free list of the process's virtual heap, this will incur a page fault
	virtual_memlist = &proctab[currpid].virtual_memlist;
 
	if (virtual_memlist->mnext == (struct memblk *)NULL) 
  {
		virtual_memlist = (struct memblk *) (4096 * NBPG);
		virtual_memlist->mlength = proctab[currpid].hsize * NBPG;
		prev = virtual_memlist;
		curr = virtual_memlist;
   
	} else {
		prev = virtual_memlist;
		curr = virtual_memlist->mnext;
   
	}
	while (curr != NULL) {			/* Search free list	*/
		if (curr->mlength == nbytes) 
    {	/* Block is exact match	*/
			prev->mnext = curr->mnext;
			virtual_memlist->mlength -= nbytes;
      proctab[currpid].virtual_memlist=*virtual_memlist;//update the proctab entry
			
      
      
			return (char *)(curr);

		} else if (curr->mlength > nbytes) {/* Split big block	*/
			leftover = (struct memblk *)((uint32) curr + nbytes);
      
			prev->mnext = leftover;
			leftover->mnext = curr->mnext;
			leftover->mlength = curr->mlength - nbytes;
			virtual_memlist->mlength -= nbytes;
       proctab[currpid].virtual_memlist=*virtual_memlist;//update the proctab entry
			
         
			return (char *)(curr);
		} else {			/* Move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}


	return (char *)SYSERR;

}

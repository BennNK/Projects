//lab 5 chen2240 vgetmem


#include <xinu.h>

char  	*vgetmem(uint32	nbytes)
{


  	struct	memblk		*vfreelist, *prev, *curr, *leftover;


  if ((nbytes == 0) ||((nbytes/4096)>proctab[currpid].vheapsize) ) 
  {

		kprintf("nbytes Error\n");

		return (char *)SYSERR;
	}

	nbytes = (uint32) roundmb(nbytes);	/* Use memblk multiples	*/

	// chen2240: initializing vitual page free list

	 vfreelist = &proctab[currpid].vfreelist;// vfreelist is of the struct memblk
 
	  if (vfreelist->mnext == (struct memblk *)NULL) {
		vfreelist = (struct memblk *) (4096 * 4096);
		vfreelist->mlength = proctab[currpid].vheapsize * 4096; // if not initialize, initialize with heap size
		prev = vfreelist;
		curr = vfreelist;
 
	} else 
  {
		prev = vfreelist;
		curr = vfreelist->mnext;

	}
 // search the free list
	  while (curr != NULL) {			/* Search free list	*/
		if (curr->mlength == nbytes) {	/* Block is exact match	*/
			prev->mnext = curr->mnext;
			vfreelist->mlength -= nbytes;
      proctab[currpid].vfreelist=*vfreelist;
		
			return (char *)(curr);

		} else if (curr->mlength > nbytes) { 
			leftover = (struct memblk *)((uint32) curr + nbytes);
     
			prev->mnext = leftover; // calculate the leftover
			leftover->mnext = curr->mnext;
			leftover->mlength = curr->mlength - nbytes;
			vfreelist->mlength -= nbytes;
      proctab[currpid].vfreelist=*vfreelist;// split the block 
		
			return (char *)(curr);
		
    
    } else {			
			prev = curr;
			curr = curr->mnext;
		}
	}


	return (char *)SYSERR;

}

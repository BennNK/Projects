
// chen2240 lab 5 vfreemem modified from freemem

#include <xinu.h>

syscall	vfreemem(
	char		*blockptr,	/* Pointer to memory block	*/
	uint32	size_in_bytes		/* Size of block in bytes	*/
)
{
	
	intmask	mask;			/* Saved interrupt mask		*/
	struct	memblk	*vfreelist, *next, *prev, *block;
	uint32	top;

	mask = disable();
	if ((size_in_bytes == 0) || ((uint32) blockptr < (uint32) (4096 * 4096)) 
  || ((uint32) blockptr > (uint32) (proctab[currpid].vheapsize + 4096) * 4096)) {
		restore(mask);
	
		return SYSERR;
	}

	size_in_bytes = (uint32) roundmb(size_in_bytes);	/* Use memblk multiples	*/
	block = (struct memblk *)blockptr;

	vfreelist = &proctab[currpid].vfreelist; //set the ptr to t vitual memory list
	prev = vfreelist;
	next = vfreelist->mnext;
 
	while ((next != NULL) && (next < block)) {
		prev = next;
		next = next->mnext;
	}

	if (prev == vfreelist) {		/* Compute top of previous block*/
		top = (uint32) NULL;
	} else {
		top = (uint32) prev + prev->mlength;
	}

	/* Ensure new block does not overlap previous or next blocks	*/

	if (((prev != vfreelist && (uint32) block < top)
	|| ((next != NULL)	&& (uint32) block+size_in_bytes>(uint32)next))) {
		restore(mask);
	
		return SYSERR;
	}

	vfreelist->mlength += size_in_bytes;


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
	restore(mask);
 
 
 
 
	return OK;

}

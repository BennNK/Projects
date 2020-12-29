README

1.The functionality impelemented.
Part 1 provide support for paging without backing store. The funtionality reated to part 1 in description are
Process
a process creation:
b process destruction:
c context switching
d null process and initialization

Page fault handling
a page fault process
b obtain a frame frame

2.Functionality not implemented.
Those related to backing store.eg age eviction and replacement

3.Files that were modified or created.
modified:
xinu.h
paging.h
prototype.h
initialize.c
creat.c
kill.c
main.c
resched.c

created:
vcreate.c
vfreemem.c
vgetmem.c
hook.c
pfisr.S
pfhandler.c
initialize_paging.c
test1.c
test2.c



4 The logic for the functionalities e.g., how you address page fault, how you get a free frame, for page directories and page table, for system initialization etc.

Process
d.null process and initialization:
I first create a inverted table for the 3072 physical frames and initialize it. (inclding the frame id, if is it used, page type in this frame etc). And then use 4 frame to store the 4 page tables and map it to the 4096 global frame, 
use 4th frame to store page table which map to the device memory. Use 5th frame to store the page directory. Map the first 4 entry and 576 entry to the previous page tables.set the pdbr to the page directory of the null process and 
enable paging.(initialize_paging.c)
  
a.process creation:
 For all process, I use findfframe to get a frame to store the page directory and initialize as before, and save the address of the frame in the process table . For create(), the vitual heapsize is set to 0, for vcreate(), 
it is set as requested. In vgetmem(), if nbytes request is larger than heapsize, it will return syserror and not cause page fault. So create() process will not get page fault if we use we vgetmem.
vgetem() will initialize a free memory list from above 4096 frame and then look for space that is the size requested, and then return the base address.
vfreemem() will do as freemem() to update the free memmory list after free of a certain size of the memory.

b.process destruction:
In function kill(), I set the frame used by that process to be free again (by setting "used"=0)

c context switching
 In resched(), I write pdbr with new prcess's pdb before the ctsw.



Page fault handling
a page fault process
 I follow the logics in description, get the faulted address check if its valid and find p as the pagetable number, if it is not present,find a frame and record this in page directory and initialize this page table , else find a frame
for this new page and record it in the page table. We also need to mark the status of frame in inverted page table(frame table).

b obtain a frame frame
Look through the inverted page table (frame table ) for a frame which is not used. Noted that if it is for page table/directrory, we will only look at 1000 kernel frames,if it is for page, we will look at 1000-3071 frames.



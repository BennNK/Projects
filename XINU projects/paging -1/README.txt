

1. functionality impelemented: paging system without backing store support, vgetmem and vfreemem, on-demand paging, per-process virtual memory management.

2. Functionality not implemented: backing store memory mapping, page replacement policy, page eviction

3. Files that were modified or created:
initialize.c
initialize_paging.c
paging.h
main.c
vfreemem.c
vcreate.c
create.c
process.h
xinu.h
kill.c
vgetmem.c
obtain_free_frame.c
pfisr.S
instrumentation_hooks.c
pf_handler.c
Lab5_test1.c
Lab5_test2.c
ctxsw.S


4. The logic for the functionalities
Four page tables mapping the first 16 MB physical memory is placed from frame 1024 to frame 1027. A page table mapping the 1024 device memory pages is placed at frame 1028. The page directory of the null process is placed in frame 1029. The above mentioned frames are unchanged for all implementations of the XINU. Page fault is triggered when an instruction is r/w a virtual address. The device will raise exception 14 which executes the pf_handler I set up at system initialization. pf_handler first reads the cr2 register and calculate the falted page number, and install a page table for it if there is none and there is free frame availale from frame 1024 to 2023. It then maps an unused page to the virtual page and returns to the process who is trying to access the virtual address. A page fault semaphore guarantees that only one process is modifying the memory of the system at any givent moment.  

Getting free frame is simple: traverse the inverted page table and find frames that are not used. 

vgetmem() is ensentially the same as getmem except it triggers page fault when being able to initialize the freelist of the virtual space.
vfreemem() is a little different from freemem() since you have to free up the physical pages which was mapped to the freed virtual pages. Please refer to the comments of the code for detail.

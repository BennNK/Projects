/*Lab1 4.2 getppid*/


#include <xinu.h>

syscall getppid(
        
                ) {

    intmask		mask;		/* Saved interrupt mask		*/
    mask = disable();
    
    struct	procent *prptr;
    prptr = &proctab[getpid()];//current process entry


    if (isbadpid(prptr->prparent))//bad parent pid means parent is terminated
    {
    printf("prpid is -1");
        restore(mask);
        return -1;
    
}
    else
    {
       printf("prpid is  ");
        printf(prptr->prparent);
        restore(mask);
    return prptr->prparent;
    }



}
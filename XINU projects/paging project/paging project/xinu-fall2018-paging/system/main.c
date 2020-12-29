/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{
    
 //char * testm =vgetmem(2000);
 //kprintf("\ntestm address %d\n",testm);
    
  resume(vcreate((void *)test1, INITSTK, 12, 25, "test1", 0, NULL));
     //sleepms(200);
    
   //resume(vcreate((void *)test2, INITSTK, 12, 25, "test2", 0));

    
    
    
    
//////////////////////////////////////////////////////////////


	/* Start the network */
	/* DO NOT REMOVE OR COMMENT THIS CALL */
	//netstart();

	/* Initialize the page server */
	/* DO NOT REMOVE OR COMMENT THIS CALL */
	//psinit();

//	kprintf("\n...creating a shell\n");
//	recvclr();
//	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
//
//	/* Wait for shell to exit and recreate it */
//
//	while (TRUE) {
//		receive();
//		sleepms(200);
//		kprintf("\n\nMain process recreating shell\n\n");
//		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
//	}
//////////////////////////////////////////////////////////////
















   while(1){;}










	return OK;
}

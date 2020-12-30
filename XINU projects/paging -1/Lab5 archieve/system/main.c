/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{
    
////test case 1: test the system initialization
//    int k;
//    asm("\t movl %%cr3,%0" : "=r"(k));   
//    pd_t * page_directory = (pd_t *) k;
//  
//    int i;
//    for(i=0;i<1024;i++){
//    
//      if (page_directory[i].pd_pres==1)
//      {
//      kprintf("\n entry address : %d  pd base %d\n", &page_directory[i], page_directory[i].pd_base);
//      }
//      
//      }
//    
//    
////end of test case 1


////test case 2: test process destruction
//resume(vcreate((void *)Lab5_test2, INITSTK, 1, 50, "p2", 0, NULL));
//resume(vcreate((void *)Lab5_test2, INITSTK, 1, 50, "p2", 0, NULL));
////end of test case 2


//test case 3: vgetmem and vfreemem
resume(vcreate((void *)Lab5_test1, INITSTK, 10, 50, "p1", 0, NULL));
//end 

    
    
    

    //kprintf("page_directory %d, should be %d\n", k, (FRAME0 + 6) * NBPG);
    

    //resume(vcreate((void *)Lab5_test1, INITSTK, 10, 10, "p2", 0, NULL));
//    resume(vcreate((void *)Lab5_test2, INITSTK, 1, 10, "p2", 0, NULL));
    //sleep(5);
    //kprintf("\npf_count %d\n", pf_count);
//    resume(vcreate((void *)Lab5_test2, INITSTK, 1, 20, "p3", 0, NULL));
    
//    int* pt=4096*NBPG;
//    *pt=10;
//    pt=4096*NBPG+4;
//    *pt=11;
//    kprintf("pt %d\n",*pt);
//    
//    
//    
//    
//    
//    
//    
//    
    
    
//    int a=10, b=6, c=5, d=4;
//    int e=a/b, f=a/c, g=a/d;
//    
//    kprintf("\n a/b %d\n",e);
//    kprintf("\n a/c %d\n",f);
//    kprintf("\n a/d %d\n",g);
//    
//    float h=1.2, i=1.5, j=1.8;
//    
//    kprintf("\n h %d\n",(int) h);
//    kprintf("\n i %d\n",(int) i);
//    kprintf("\n j %d\n",(int) j);
//    
    
    
    
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

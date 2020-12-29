/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
    
    	
     
     
//Lab1 3.2
extern void welcome(void);/*put the welcome window in an external location which is welcome.c*/
welcome();
//end of 3.2



////Lab1 5.1
// long text=0x12345678;
// long text3=0x12345678;
// long text2;
// long text4;
//
// text4=revbyteorder_inline(text3);//inline assembly  code in revbyteorder_inline.c
// kprintf("inline assembly %x\n",text4);
//
//
// kprintf(".c function %x\n",revbyteorderc(text));//.c function in revbyteorderc.c
//
// text2=revbyteorder(text);//assembly code in revbyteorder.S
// kprintf("assembly code %x\n",text2);
////end of Lab 1 5.1




////Lab1 5.2
//printsegaddress();



 
 //Lab1 5.3 only
// register int a asm("esp");
//     int* esp_=a;
//    
//     kprintf("in main(), the address of the top of the run-time stack before myProgA() is create/resumed is 0x%8x\n",(esp_)); 
//     kprintf("in main(), the content of the top of the run-time stack before myProgA() is create/resumed is 0x%8x\n",*esp_);
//    
// resume(create(myProgA,1024,21,"myProgA_",0));
//
// register int b asm("esp");
//     esp_=b;
// 
//     kprintf("in main(), the address of the top of the run-time stack after myProgA() is create/resumed is 0x%8x\n",esp_); 
//     kprintf("in main(), the content of the top of the run-time stack after myProgA() is create/resumed is 0x%8x\n",*esp_);
//end of Lab1 5.3


//Lab1 5.4    only
// resume(create(myProgA,1024,21,"myProgA_",0));
// resume(create(myfuncA,1024,21,"myfuncA_",0));
//end of Lab 5.4


//Lab1 6
//resume(create(myProgA,1024,21,"myProgA_",0));

//end of 6
    
    
	/* Run the Xinu shell */
 	recvclr();
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	/* Wait for shell to exit and recreate it */
 
 
 
 
 

	while (TRUE) {
    
		receive(); 
   //Lab1 4.1
   xminsec_t *p;
   p->upmin=0;
   p->upsec=0;
   xuptime(p);
   //end of Lab1 4.1
   
   /*Lab1 4.2*/
   
   getppid();
   //end of Lab1 4.2
   
   
		sleepms(200);
		kprintf("\n\nMain process recreating shell\n\n");
		resume(create(shell, 4096, 20, "shell", 1, CONSOLE));
   
	}
 

 
 
	return OK;
    
}

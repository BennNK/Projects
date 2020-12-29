//findfframe lab 5 chen2240

#include <xinu.h>



int findfframe(int type){

       int i;
       
      if(type ==1) // page table and page diretory in the first 1000 frame
       { 
       for (i = 0; i <1000; i++) 
       {
       if (invert_ptab[i].used == 0) 
                        {
                        return invert_ptab[i].f_id;
                        
                        }
       }
       }
                        
                        
       else if(type ==0)
       { 
       for (i = 1000; i <3072; i++) // page in the next 2072 frames
       {
                if (invert_ptab[i].used == 0) 
                {
                        
                        return invert_ptab[i].f_id;
                        }
                }
       }
        
         else return SYSERR;
        
}
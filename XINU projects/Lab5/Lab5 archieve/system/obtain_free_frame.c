//obtainfreeframe.c
//Lab5 (lei48 11/09/2018)

#include <xinu.h>



int findfframe()
{

        
        for (int i = 0; i < NUM_PAGES_FOR_PD_PT; i++) 
        {
                if (ipagetab[i].used == 0)
                 { 
                        
                        return ipagetab[i].frame_number;
                }
        }
                        
                        return SYSERR;

        
}




int findfpage()
{
        
        

        for (int i = NUM_PAGES_FOR_PD_PT; i < NFRAMES; i++) 
        {
                if (ipagetab[i].used == 0) 
                {
                        
                         
                        return ipagetab[i].frame_number;
                }
        }
        
        
        return SYSERR;


        
}
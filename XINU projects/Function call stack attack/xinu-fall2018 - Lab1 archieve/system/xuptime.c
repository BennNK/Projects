/*Lab1 4.1 xuptime*/
/* xuptime.c - xuptime */
#include <xinu.h>



syscall xuptime(
    xminsec_t *p
  )

        {
        intmask		mask;		/* Saved interrupt mask		*/
        mask = disable();
        
        
        p->upmin=clktime/60;//clktime is a global variable recording seconds after boot
        p->upsec=clktime-60*p->upmin;
        
        printf("\n\nuptime since bootrap\n");
        printf(" %d second(s) ", p->upsec);
        printf(" %d min(m)\n\n ", p->upmin); 
        

restore(mask);


    return;

        }
#pfisr.S
#Lab5 (lei48 11/09/2018)


    .text
		.globl	pfisr		# page fault interrupt service routine
    
    pfisr:
                
                pushal			
                pushfl
                call	pf_handler	
                popfl
                popal			
                add $4, %esp    # restore error code
                iret			

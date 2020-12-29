
    .text
		.globl	pfisr	
    
    pfisr:
                pushl %ebp
                movl %esp, %ebp
                pushal			
                pushfl
                call	pfhandler	# Call handler
                popfl
                popal			
                movl  %ebp,%esp
                popl %ebp
                add $0x4, %esp         
                iret			 

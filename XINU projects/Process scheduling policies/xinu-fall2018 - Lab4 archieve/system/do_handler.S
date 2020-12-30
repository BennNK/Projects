#Lab4 3 (username:lei48, date modified: 10/24/2018)

.text
.globl do_handler
do_handler:

    #save ebp and esp

    pushl	%ebp
		movl	%esp,%ebp	
		
   #call back function
   sti
   
   call * 8(%ebp)
   cli
   
    #rstore ebp and esp
		movl	%ebp,%esp	
		popl %ebp
   
   #restore esp and return address to where it was when ctxsw returns
	  pushl (%esp)
     
   #return
		ret
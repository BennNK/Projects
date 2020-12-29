

.text
.globl revbyteorder
revbyteorder:
push %esp
mov %esp, %ebp

mov 8(%ebp), %eax
bswap %eax
mov %ebp, %esp
pop %ebp

ret

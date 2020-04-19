	.text
	.globl bitrev
	.type bitrev, @function

mask1: .quad 0x5555555555555555
mask2: .quad 0xAAAAAAAAAAAAAAAA

bitrev:              
	xor %eax, %eax

	movq %rdi, %rdx
	andq mask1, %rdi
	andq mask2, %rdx
	salq %rdi
	sarq %rdx
	orq %rdi, %rax
	orq %rdx, %rax
	ret

.size bitrev, .-bitrev

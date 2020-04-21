	.section .text
	.global addsb

var: .quad 0x5555555555555555

addsb:
	xor %eax, %eax
	
	movq %rdi, %rax
	andq var, %rdi
	andq var1, %rax
	sarq %rdi
	salq %rax
	andq %rdi, %rax

	ret

	.size addsb, .-addsb

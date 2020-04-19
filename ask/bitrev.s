.globl bitrev

bitrev:              
	xorl %eax, %eax
	rorq $32, %rdi
	movq $0xFFFF, %rsi
	movq $0xFFFF0000, %rdx
	andq %rdi, %rsi
	andq %rdi, %rdx
	salq $16, %rsi
	sarq $16, %rdx
	orq %rsi, %rax
	orq %rdx, %rax
	movq %rdi, %rax

	ret

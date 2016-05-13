	.file	"conway.c"
	.text
.globl update
	.type	update, @function
update:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$52, %esp
	movl	12(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, -12(%ebp)
	movl	$0, -36(%ebp)
	jmp	.L2
.L3:
	movl	-36(%ebp), %eax
	sall	$2, %eax
	movl	%eax, %ebx
	addl	-12(%ebp), %ebx
	movl	16(%ebp), %eax
	sall	$2, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, (%ebx)
	addl	$1, -36(%ebp)
.L2:
	movl	-36(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	.L3
	movl	$0, -36(%ebp)
	jmp	.L4
.L7:
	movl	$0, -32(%ebp)
	jmp	.L5
.L6:
	movl	-36(%ebp), %eax
	sall	$2, %eax
	addl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	sall	$2, %edx
	leal	(%eax,%edx), %edx
	movl	-36(%ebp), %eax
	sall	$2, %eax
	addl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %ecx
	sall	$2, %ecx
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	%eax, (%edx)
	addl	$1, -32(%ebp)
.L5:
	movl	-32(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	.L6
	addl	$1, -36(%ebp)
.L4:
	movl	-36(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	.L7
	movl	$0, -36(%ebp)
	jmp	.L8
.L22:
	movl	$0, -32(%ebp)
	jmp	.L9
.L21:
	movl	$0, -20(%ebp)
	cmpl	$0, -36(%ebp)
	jle	.L10
	movl	-36(%ebp), %eax
	subl	$1, %eax
	sall	$2, %eax
	addl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	addl	%eax, -20(%ebp)
	cmpl	$0, -32(%ebp)
	jle	.L11
	movl	-36(%ebp), %eax
	subl	$1, %eax
	sall	$2, %eax
	addl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	subl	$1, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	addl	%eax, -20(%ebp)
.L11:
	movl	12(%ebp), %eax
	subl	$1, %eax
	cmpl	-32(%ebp), %eax
	jle	.L10
	movl	-36(%ebp), %eax
	subl	$1, %eax
	sall	$2, %eax
	addl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	addl	$1, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	addl	%eax, -20(%ebp)
.L10:
	movl	16(%ebp), %eax
	subl	$1, %eax
	cmpl	-36(%ebp), %eax
	jle	.L12
	movl	-36(%ebp), %eax
	addl	$1, %eax
	sall	$2, %eax
	addl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	addl	%eax, -20(%ebp)
	cmpl	$0, -32(%ebp)
	jle	.L13
	movl	-36(%ebp), %eax
	addl	$1, %eax
	sall	$2, %eax
	addl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	subl	$1, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	addl	%eax, -20(%ebp)
.L13:
	movl	12(%ebp), %eax
	subl	$1, %eax
	cmpl	-32(%ebp), %eax
	jle	.L12
	movl	-36(%ebp), %eax
	addl	$1, %eax
	sall	$2, %eax
	addl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	addl	$1, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	addl	%eax, -20(%ebp)
.L12:
	cmpl	$0, -32(%ebp)
	jle	.L14
	movl	-36(%ebp), %eax
	sall	$2, %eax
	addl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	subl	$1, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	addl	%eax, -20(%ebp)
.L14:
	movl	12(%ebp), %eax
	subl	$1, %eax
	cmpl	-32(%ebp), %eax
	jle	.L15
	movl	-36(%ebp), %eax
	sall	$2, %eax
	addl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	addl	$1, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	addl	%eax, -20(%ebp)
.L15:
	movl	-36(%ebp), %eax
	sall	$2, %eax
	addl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	cmpl	$1, %eax
	jne	.L16
	cmpl	$2, -20(%ebp)
	je	.L17
	cmpl	$3, -20(%ebp)
	jne	.L18
.L17:
	movl	-36(%ebp), %eax
	sall	$2, %eax
	addl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	$1, (%eax)
	nop
	jmp	.L20
.L18:
	movl	-36(%ebp), %eax
	sall	$2, %eax
	addl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	$0, (%eax)
	jmp	.L20
.L16:
	cmpl	$3, -20(%ebp)
	jne	.L20
	movl	-36(%ebp), %eax
	sall	$2, %eax
	addl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	-32(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	$1, (%eax)
.L20:
	addl	$1, -32(%ebp)
.L9:
	movl	-32(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	.L21
	addl	$1, -36(%ebp)
.L8:
	movl	-36(%ebp), %eax
	cmpl	16(%ebp), %eax
	jl	.L22
	movl	$0, %eax
	addl	$52, %esp
	popl	%ebx
	popl	%ebp
	ret

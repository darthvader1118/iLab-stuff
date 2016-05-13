	.file	"mystery.c"
	.text
.globl bar
	.type	bar, @function
bar:
	pushl	%ebp		#push ebp onto stack
	movl	%esp, %ebp	#move stack pointer to base pointer
	subl	$16, %esp	# esp = esp -16 esp =-16 allocates space to stack
	cmpl	$1, 8(%ebp)	# first input = 1?
	jg	.L2		# if greater then 1 jmp to .L2
	movl	$0, %eax	# eax = 0 reutrns 0 if first input is <=1
	jmp	.L3		# jmp .L3
.L2:
	movl	$2, -4(%ebp)    #  put 2 in stack at 4 bits below base pointer
	jmp	.L4		# jmp to .L4
.L6:
	movl	8(%ebp), %eax	# put value of input into eax
	movl	%eax, %edx	# copy value of first input to edx
	sarl	$31, %edx	# gets the first bit
	idivl	-4(%ebp)	# eax/2
	movl	%edx, %eax	#copy value of edx to eax	
	testl	%eax, %eax	# cheacks to see if remainder of eax/2 is 1
	jne	.L5    		# jmps to .L5 if eax != 0
	movl	$0, %eax	# copy 0 to eax	
	jmp	.L3		# returns 0 
.L5:
	addl	$1, -4(%ebp)	# increments the value at 4 bytes below the base pointer
.L4:
	movl	-4(%ebp), %eax	# eax = 2
	cmpl	8(%ebp), %eax	# first input copare to 2
	jl	.L6		# jmp to .L6 if input > 2
	movl	$1, %eax	# copy value of 1 to eax.... returns 1
.L3:
	leave
	ret
	.size	bar, .-bar
.globl foo
	.type	foo, @function
foo:
	pushl	%ebp		#set up stack	
	movl	%esp, %ebp	#set up stack
	pushl	%ebx		# push ebx
	subl	$36, %esp	#allocate space on stack
	movl	$0, -12(%ebp)	# copy value of 0 to 12 below ebp
	movl	$0, -12(%ebp)
	jmp	.L9
.L14:
	movl	-12(%ebp), %eax		#eax = 0
	addl	8(%ebp), %eax		# eax = eax + input
	movzbl	(%eax), %eax		# %eax = 0x000000
	cmpb	$126, %al		# compare 126 to 00
	je	.L16
.L10:
	movl	-12(%ebp), %eax		#eax = input
	movl	%eax, %edx		# edx =eax
	sarl	$31, %edx		# 
	shrl	$31, %edx
	addl	%edx, %eax
	andl	$1, %eax
	subl	%edx, %eax
	cmpl	$1, %eax
	jne	.L12
	movl	-12(%ebp), %eax
	movl	%eax, %ebx
	addl	8(%ebp), %ebx
	movl	-12(%ebp), %eax
	addl	8(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, (%esp)
	call	toupper
	movb	%al, (%ebx)
.L12:
	movl	-12(%ebp), %eax
	addl	$1, %eax
	movl	%eax, (%esp)
	call	bar
	testl	%eax, %eax
	je	.L13
	movl	-12(%ebp), %eax
	movl	%eax, %ebx
	addl	8(%ebp), %ebx
	movl	-12(%ebp), %eax
	addl	8(%ebp), %eax
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	movl	%eax, (%esp)
	call	tolower
	movb	%al, (%ebx)
.L13:
	addl	$1, -12(%ebp)
.L9:
	movl	-12(%ebp), %ebx #put 0 in ebx
	movl	8(%ebp), %eax	#first input in eax
	movl	%eax, (%esp)	#put the address of eax to where stack pointer is 
	call	strlen		# get the length of string
	cmpl	%eax, %ebx	# compare eax to 0
	jb	.L14
	jmp	.L15
.L16:
	nop			# does nothing
.L15:
	addl	$36, %esp
	popl	%ebx
	popl	%ebp
	ret
	.size	foo, .-foo
	.section	.rodata
	.align 4
.LC0:
	.string	"Incorrect number of command line arguments given"
.LC1:
	.string	"Input:%s"
	.align 4
.LC2:
	.string	"Incorrect format for command line argument"
.LC3:
	.string	"Output: \"%s\"\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp		#;push base pointer on the stack
	movl	%esp, %ebp	#;move stack pointer to base pointer
	andl	$-16, %esp	#; esp = -16 && esp 
	subl	$32, %esp	#; esp =  esp - 32
	cmpl	$2, 8(%ebp)	#; first input = 2?
	je	.L18		#; if equal to 0 jmp to .L18
	movl	$.LC0, (%esp)
	call	puts
	movl	$1, %eax
	jmp	.L19
.L18:
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	strlen
	movl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	movl	%eax, (%esp)
	call	malloc
	movl	%eax, 28(%esp)
	movl	$.LC1, %edx
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	28(%esp), %ecx
	movl	%ecx, 8(%esp)
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	__isoc99_sscanf
	cmpl	$1, %eax
	je	.L20
	movl	$.LC2, (%esp)
	call	puts
	movl	$1, %eax
	jmp	.L19
.L20:
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	foo
	movl	$.LC3, %eax
	movl	28(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	free
	jmp	.L17
.L19:
.L17:
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.7 20120313 (Red Hat 4.4.7-4)"
	.section	.note.GNU-stack,"",@progbits

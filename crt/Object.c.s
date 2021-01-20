	.file	"Object.c"
	.text
.Ltext0:
	.type	stringlen, @function
stringlen:
.LFB5:
	.file 1 "/home/xiaodo/c++/colang/src/internal/String.h"
	.loc 1 55 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	.loc 1 56 0
	movq	-24(%rbp), %rax
	subq	$1, %rax
	movzbl	(%rax), %eax
	movb	%al, -1(%rbp)
	.loc 1 57 0
	movzbl	-1(%rbp), %eax
	andl	$7, %eax
	cmpl	$4, %eax
	ja	.L2
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L4(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L4(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	#.section	.rodata
	.align 4
	.align 4
.L4:
	.long	.L3-.L4
	.long	.L5-.L4
	.long	.L6-.L4
	.long	.L7-.L4
	.long	.L8-.L4
	.text
.L3:
	.loc 1 59 0
	movzbl	-1(%rbp), %eax
	shrb	$3, %al
	movzbl	%al, %eax
	jmp	.L9
.L5:
	.loc 1 61 0
	movq	-24(%rbp), %rax
	subq	$3, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	jmp	.L9
.L6:
	.loc 1 63 0
	movq	-24(%rbp), %rax
	subq	$5, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	jmp	.L9
.L7:
	.loc 1 65 0
	movq	-24(%rbp), %rax
	subq	$9, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	jmp	.L9
.L8:
	.loc 1 67 0
	movq	-24(%rbp), %rax
	subq	$17, %rax
	movq	(%rax), %rax
	jmp	.L9
.L2:
	.loc 1 69 0
	movl	$0, %eax
.L9:
	.loc 1 70 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	stringlen, .-stringlen
	.globl	member_insert_or_update
	.type	member_insert_or_update, @function
member_insert_or_update:
.LFB12:
	.file 2 "/home/xiaodo/c++/colang/src/internal/Object.c"
	.loc 2 16 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
.L16:
	.loc 2 21 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jne	.L11
	.loc 2 22 0
	movq	-32(%rbp), %rax
	movq	40(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 40(%rax)
.L11:
	.loc 2 24 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jnb	.L12
	.loc 2 24 0 is_stmt 0 discriminator 1
	movq	-24(%rbp), %rax
	addq	$8, %rax
	jmp	.L13
.L12:
	.loc 2 24 0 discriminator 2
	movq	-24(%rbp), %rax
	addq	$16, %rax
.L13:
	.loc 2 24 0 discriminator 4
	movq	%rax, -8(%rbp)
	.loc 2 26 0 is_stmt 1 discriminator 4
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -40(%rbp)
	je	.L18
	.loc 2 30 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 2 21 0
	jmp	.L16
.L18:
	.loc 2 27 0
	nop
	.loc 2 33 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, (%rax)
	.loc 2 34 0
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 2 35 0
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 2 36 0
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 2 37 0
	movq	-32(%rbp), %rax
	movb	$1, 48(%rax)
	.loc 2 38 0
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	member_insert_or_update, .-member_insert_or_update
	.globl	member_find
	.type	member_find, @function
member_find:
.LFB13:
	.loc 2 39 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	.loc 2 42 0
	movq	$0, -16(%rbp)
	.loc 2 43 0
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L21
	cmpq	$3, %rax
	jg	.L22
	cmpq	$1, %rax
	jl	.L20
	jmp	.L23
.L22:
	cmpq	$4, %rax
	jne	.L20
.L23:
	.loc 2 47 0
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L20
.L21:
	.loc 2 49 0
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	stringlen
	movq	%rax, %rdx
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	hash_key@PLT
	movl	%eax, %eax
	movq	%rax, -16(%rbp)
	.loc 2 50 0
	nop
.L20:
	.loc 2 52 0
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 2 53 0
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 2 55 0
	jmp	.L24
.L29:
	.loc 2 57 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -16(%rbp)
	je	.L25
	.loc 2 58 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -16(%rbp)
	jnb	.L26
	.loc 2 58 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	jmp	.L27
.L26:
	.loc 2 58 0 discriminator 2
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
.L27:
	.loc 2 58 0 discriminator 4
	movq	%rax, -8(%rbp)
	.loc 2 59 0 is_stmt 1 discriminator 4
	jmp	.L24
.L25:
	.loc 2 61 0
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jne	.L24
	.loc 2 62 0
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	jmp	.L28
.L24:
	.loc 2 55 0
	movq	-8(%rbp), %rax
	cmpq	-24(%rbp), %rax
	jne	.L29
	.loc 2 65 0
	movl	$0, %eax
.L28:
	.loc 2 66 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	member_find, .-member_find
	.globl	member_insert
	.type	member_insert, @function
member_insert:
.LFB14:
	.loc 2 68 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 70 0
	movl	$56, %edi
	call	gc_malloc@PLT
	movq	%rax, -16(%rbp)
	.loc 2 71 0
	movq	$0, -8(%rbp)
	.loc 2 72 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L32
	cmpq	$3, %rax
	jg	.L33
	cmpq	$1, %rax
	jl	.L31
	jmp	.L34
.L33:
	cmpq	$4, %rax
	jne	.L31
.L34:
	.loc 2 76 0
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L31
.L32:
	.loc 2 78 0
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	stringlen
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	hash_key@PLT
	movl	%eax, %eax
	movq	%rax, -8(%rbp)
.L31:
	.loc 2 80 0
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	.loc 2 81 0
	movq	-16(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 32(%rax)
	.loc 2 82 0
	movq	-16(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 40(%rax)
	.loc 2 83 0
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	rbtree_insert@PLT
	.loc 2 84 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	member_insert, .-member_insert
#	.section	.rodata
	.align 8
.LC0:
	.string	"[object_create] failed to create\n"
	.text
	.globl	object_create
	.type	object_create, @function
object_create:
.LFB15:
	.loc 2 89 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	.loc 2 90 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 91 0
	cmpq	$0, -8(%rbp)
	jne	.L36
	.loc 2 92 0
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 2 93 0
	movl	$0, %eax
	jmp	.L37
.L36:
	.loc 2 96 0
	movl	$24, %edi
	call	gc_malloc@PLT
	movq	%rax, -16(%rbp)
	.loc 2 97 0
	movl	$56, %edi
	call	gc_malloc@PLT
	movq	%rax, -24(%rbp)
	.loc 2 98 0
	movq	-24(%rbp), %rax
	movb	$0, 48(%rax)
	movq	-16(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-16(%rbp), %rax
	leaq	member_insert_or_update(%rip), %rdx
	movq	%rdx, 16(%rax)
	.loc 2 100 0
	movl	$24, %edi
	call	gc_malloc@PLT
	movq	%rax, -32(%rbp)
	.loc 2 101 0
	movl	$56, %edi
	call	gc_malloc@PLT
	movq	%rax, -40(%rbp)
	.loc 2 102 0
	movq	-40(%rbp), %rax
	movb	$0, 48(%rax)
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-32(%rbp), %rax
	leaq	member_insert_or_update(%rip), %rdx
	movq	%rdx, 16(%rax)
	.loc 2 104 0
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	.loc 2 105 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 2 107 0
	movq	-8(%rbp), %rax
.L37:
	.loc 2 108 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	object_create, .-object_create
	.globl	object_member_update
	.type	object_member_update, @function
object_member_update:
.LFB16:
	.loc 2 110 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 112 0
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	newobject@PLT
	movq	%rax, -8(%rbp)
	.loc 2 113 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	.loc 2 114 0
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	-40(%rbp), %rdx
	movq	-8(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	member_insert
	.loc 2 115 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	object_member_update, .-object_member_update
	#.section	.rodata
	.align 8
.LC1:
	.string	"object_get] not find the memeber:%d value\n"
	.text
	.globl	object_member_get
	.type	object_member_get, @function
object_member_get:
.LFB17:
	.loc 2 116 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	.loc 2 117 0
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	newobject@PLT
	movq	%rax, -8(%rbp)
	.loc 2 118 0
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	.loc 2 119 0
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	member_find
	movq	%rax, -24(%rbp)
	.loc 2 120 0
	cmpq	$0, -24(%rbp)
	jne	.L40
	.loc 2 121 0
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 2 122 0
	movl	$0, %esi
	movl	$0, %edi
	call	newobject@PLT
	jmp	.L41
.L40:
	.loc 2 124 0
	movq	-24(%rbp), %rax
.L41:
	.loc 2 125 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	object_member_get, .-object_member_get
#	.section	.rodata
	.align 8
.LC2:
	.string	" [object-uop] probably wrong at there! object:%p rhs:%p\n"
	.text
	.globl	object_unary_operator
	.type	object_unary_operator, @function
object_unary_operator:
.LFB18:
	.loc 2 126 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	%rcx, -48(%rbp)
	.loc 2 127 0
	cmpq	$0, -32(%rbp)
	je	.L43
	.loc 2 127 0 is_stmt 0 discriminator 1
	cmpq	$0, -48(%rbp)
	jne	.L44
.L43:
	.loc 2 128 0 is_stmt 1
	movq	-48(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 2 129 0
	jmp	.L42
.L44:
	.loc 2 131 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	object_member_get
	movq	%rax, -8(%rbp)
	.loc 2 132 0
	movq	-48(%rbp), %rdx
	movq	-8(%rbp), %rcx
	movl	-20(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	operator_switch@PLT
	movq	%rax, -16(%rbp)
	.loc 2 133 0
	movq	-16(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	object_member_update
.L42:
	.loc 2 134 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	object_unary_operator, .-object_unary_operator
	.globl	object_func_add
	.type	object_func_add, @function
object_func_add:
.LFB19:
	.loc 2 135 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 137 0
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	newobject@PLT
	movq	%rax, -8(%rbp)
	.loc 2 138 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	.loc 2 139 0
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	-40(%rbp), %rdx
	movq	-8(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	member_insert
	.loc 2 140 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	object_func_add, .-object_func_add
#	.section	.rodata
.LC3:
	.string	"[object-func] func not exist\n"
	.text
	.globl	object_func_addr
	.type	object_func_addr, @function
object_func_addr:
.LFB20:
	.loc 2 141 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	.loc 2 142 0
	movq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	newobject@PLT
	movq	%rax, -8(%rbp)
	.loc 2 143 0
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	.loc 2 144 0
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	member_find
	movq	%rax, -24(%rbp)
	.loc 2 145 0
	cmpq	$0, -24(%rbp)
	jne	.L48
	.loc 2 146 0
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L48:
	.loc 2 148 0
	movq	-24(%rbp), %rax
	.loc 2 149 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	object_func_addr, .-object_func_addr
.Letext0:
	.file 3 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h"
	.file 4 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 5 "/usr/include/x86_64-linux-gnu/bits/libio.h"
	.file 6 "/usr/include/stdio.h"
	.file 7 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
	.file 8 "/usr/include/x86_64-linux-gnu/sys/types.h"
	.file 9 "/usr/include/unistd.h"
	.file 10 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h"
	.file 11 "/usr/include/time.h"
	.file 12 "/home/xiaodo/c++/colang/src/gc/Hugmem.h"
	.file 13 "/home/xiaodo/c++/colang/src/gc/gc.h"
	.file 14 "/home/xiaodo/c++/colang/src/internal/Value.h"
	.file 15 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h"
	.file 16 "/home/xiaodo/c++/colang/src/internal/Map.h"
	.file 17 "/home/xiaodo/c++/colang/src/internal/Object.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xc25
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF155
	.byte	0xc
	.long	.LASF156
	.long	.LASF157
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF0
	.byte	0x3
	.byte	0xd8
	.long	0x38
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.long	.LASF1
	.byte	0x4
	.byte	0x1e
	.long	0x4a
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF3
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF4
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF5
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x2
	.long	.LASF7
	.byte	0x4
	.byte	0x25
	.long	0x4a
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF8
	.uleb128 0x2
	.long	.LASF9
	.byte	0x4
	.byte	0x27
	.long	0x51
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.long	.LASF10
	.byte	0x4
	.byte	0x29
	.long	0x58
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF11
	.uleb128 0x2
	.long	.LASF12
	.byte	0x4
	.byte	0x2c
	.long	0x38
	.uleb128 0x2
	.long	.LASF13
	.byte	0x4
	.byte	0x8c
	.long	0x95
	.uleb128 0x2
	.long	.LASF14
	.byte	0x4
	.byte	0x8d
	.long	0x95
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0xc5
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF15
	.uleb128 0x7
	.long	0xc5
	.uleb128 0x8
	.long	.LASF45
	.byte	0xd8
	.byte	0x5
	.byte	0xf5
	.long	0x251
	.uleb128 0x9
	.long	.LASF16
	.byte	0x5
	.byte	0xf6
	.long	0x83
	.byte	0
	.uleb128 0x9
	.long	.LASF17
	.byte	0x5
	.byte	0xfb
	.long	0xbf
	.byte	0x8
	.uleb128 0x9
	.long	.LASF18
	.byte	0x5
	.byte	0xfc
	.long	0xbf
	.byte	0x10
	.uleb128 0x9
	.long	.LASF19
	.byte	0x5
	.byte	0xfd
	.long	0xbf
	.byte	0x18
	.uleb128 0x9
	.long	.LASF20
	.byte	0x5
	.byte	0xfe
	.long	0xbf
	.byte	0x20
	.uleb128 0x9
	.long	.LASF21
	.byte	0x5
	.byte	0xff
	.long	0xbf
	.byte	0x28
	.uleb128 0xa
	.long	.LASF22
	.byte	0x5
	.value	0x100
	.long	0xbf
	.byte	0x30
	.uleb128 0xa
	.long	.LASF23
	.byte	0x5
	.value	0x101
	.long	0xbf
	.byte	0x38
	.uleb128 0xa
	.long	.LASF24
	.byte	0x5
	.value	0x102
	.long	0xbf
	.byte	0x40
	.uleb128 0xa
	.long	.LASF25
	.byte	0x5
	.value	0x104
	.long	0xbf
	.byte	0x48
	.uleb128 0xa
	.long	.LASF26
	.byte	0x5
	.value	0x105
	.long	0xbf
	.byte	0x50
	.uleb128 0xa
	.long	.LASF27
	.byte	0x5
	.value	0x106
	.long	0xbf
	.byte	0x58
	.uleb128 0xa
	.long	.LASF28
	.byte	0x5
	.value	0x108
	.long	0x289
	.byte	0x60
	.uleb128 0xa
	.long	.LASF29
	.byte	0x5
	.value	0x10a
	.long	0x28f
	.byte	0x68
	.uleb128 0xa
	.long	.LASF30
	.byte	0x5
	.value	0x10c
	.long	0x83
	.byte	0x70
	.uleb128 0xa
	.long	.LASF31
	.byte	0x5
	.value	0x110
	.long	0x83
	.byte	0x74
	.uleb128 0xa
	.long	.LASF32
	.byte	0x5
	.value	0x112
	.long	0xa7
	.byte	0x78
	.uleb128 0xa
	.long	.LASF33
	.byte	0x5
	.value	0x116
	.long	0x51
	.byte	0x80
	.uleb128 0xa
	.long	.LASF34
	.byte	0x5
	.value	0x117
	.long	0x5f
	.byte	0x82
	.uleb128 0xa
	.long	.LASF35
	.byte	0x5
	.value	0x118
	.long	0x295
	.byte	0x83
	.uleb128 0xa
	.long	.LASF36
	.byte	0x5
	.value	0x11c
	.long	0x2a5
	.byte	0x88
	.uleb128 0xa
	.long	.LASF37
	.byte	0x5
	.value	0x125
	.long	0xb2
	.byte	0x90
	.uleb128 0xa
	.long	.LASF38
	.byte	0x5
	.value	0x12d
	.long	0xbd
	.byte	0x98
	.uleb128 0xa
	.long	.LASF39
	.byte	0x5
	.value	0x12e
	.long	0xbd
	.byte	0xa0
	.uleb128 0xa
	.long	.LASF40
	.byte	0x5
	.value	0x12f
	.long	0xbd
	.byte	0xa8
	.uleb128 0xa
	.long	.LASF41
	.byte	0x5
	.value	0x130
	.long	0xbd
	.byte	0xb0
	.uleb128 0xa
	.long	.LASF42
	.byte	0x5
	.value	0x132
	.long	0x2d
	.byte	0xb8
	.uleb128 0xa
	.long	.LASF43
	.byte	0x5
	.value	0x133
	.long	0x83
	.byte	0xc0
	.uleb128 0xa
	.long	.LASF44
	.byte	0x5
	.value	0x135
	.long	0x2ab
	.byte	0xc4
	.byte	0
	.uleb128 0xb
	.long	.LASF158
	.byte	0x5
	.byte	0x9a
	.uleb128 0x8
	.long	.LASF46
	.byte	0x18
	.byte	0x5
	.byte	0xa0
	.long	0x289
	.uleb128 0x9
	.long	.LASF47
	.byte	0x5
	.byte	0xa1
	.long	0x289
	.byte	0
	.uleb128 0x9
	.long	.LASF48
	.byte	0x5
	.byte	0xa2
	.long	0x28f
	.byte	0x8
	.uleb128 0x9
	.long	.LASF49
	.byte	0x5
	.byte	0xa6
	.long	0x83
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x258
	.uleb128 0x6
	.byte	0x8
	.long	0xd1
	.uleb128 0xc
	.long	0xc5
	.long	0x2a5
	.uleb128 0xd
	.long	0x38
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x251
	.uleb128 0xc
	.long	0xc5
	.long	0x2bb
	.uleb128 0xd
	.long	0x38
	.byte	0x13
	.byte	0
	.uleb128 0xe
	.long	.LASF159
	.uleb128 0xf
	.long	.LASF50
	.byte	0x5
	.value	0x13f
	.long	0x2bb
	.uleb128 0xf
	.long	.LASF51
	.byte	0x5
	.value	0x140
	.long	0x2bb
	.uleb128 0xf
	.long	.LASF52
	.byte	0x5
	.value	0x141
	.long	0x2bb
	.uleb128 0x6
	.byte	0x8
	.long	0xcc
	.uleb128 0x7
	.long	0x2e4
	.uleb128 0x10
	.long	.LASF53
	.byte	0x6
	.byte	0x87
	.long	0x28f
	.uleb128 0x10
	.long	.LASF54
	.byte	0x6
	.byte	0x88
	.long	0x28f
	.uleb128 0x10
	.long	.LASF55
	.byte	0x6
	.byte	0x89
	.long	0x28f
	.uleb128 0x10
	.long	.LASF56
	.byte	0x7
	.byte	0x1a
	.long	0x83
	.uleb128 0xc
	.long	0x2ea
	.long	0x326
	.uleb128 0x11
	.byte	0
	.uleb128 0x7
	.long	0x31b
	.uleb128 0x10
	.long	.LASF57
	.byte	0x7
	.byte	0x1b
	.long	0x326
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF58
	.uleb128 0x2
	.long	.LASF59
	.byte	0x8
	.byte	0x21
	.long	0x3f
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF60
	.uleb128 0xf
	.long	.LASF61
	.byte	0x9
	.value	0x222
	.long	0x35b
	.uleb128 0x6
	.byte	0x8
	.long	0xbf
	.uleb128 0x10
	.long	.LASF62
	.byte	0xa
	.byte	0x24
	.long	0xbf
	.uleb128 0x10
	.long	.LASF63
	.byte	0xa
	.byte	0x32
	.long	0x83
	.uleb128 0x10
	.long	.LASF64
	.byte	0xa
	.byte	0x37
	.long	0x83
	.uleb128 0x10
	.long	.LASF65
	.byte	0xa
	.byte	0x3b
	.long	0x83
	.uleb128 0xc
	.long	0xbf
	.long	0x39d
	.uleb128 0xd
	.long	0x38
	.byte	0x1
	.byte	0
	.uleb128 0x10
	.long	.LASF66
	.byte	0xb
	.byte	0x9f
	.long	0x38d
	.uleb128 0x10
	.long	.LASF67
	.byte	0xb
	.byte	0xa0
	.long	0x83
	.uleb128 0x10
	.long	.LASF68
	.byte	0xb
	.byte	0xa1
	.long	0x95
	.uleb128 0x10
	.long	.LASF69
	.byte	0xb
	.byte	0xa6
	.long	0x38d
	.uleb128 0x10
	.long	.LASF70
	.byte	0xb
	.byte	0xae
	.long	0x83
	.uleb128 0x10
	.long	.LASF71
	.byte	0xb
	.byte	0xaf
	.long	0x95
	.uleb128 0x8
	.long	.LASF72
	.byte	0x18
	.byte	0xc
	.byte	0x7
	.long	0x410
	.uleb128 0x9
	.long	.LASF73
	.byte	0xc
	.byte	0x9
	.long	0xbd
	.byte	0
	.uleb128 0x9
	.long	.LASF74
	.byte	0xc
	.byte	0xa
	.long	0x83
	.byte	0x8
	.uleb128 0x9
	.long	.LASF75
	.byte	0xc
	.byte	0xb
	.long	0x410
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x3df
	.uleb128 0x2
	.long	.LASF76
	.byte	0xc
	.byte	0xc
	.long	0x3df
	.uleb128 0x8
	.long	.LASF77
	.byte	0x8
	.byte	0xc
	.byte	0xe
	.long	0x43a
	.uleb128 0x9
	.long	.LASF78
	.byte	0xc
	.byte	0xf
	.long	0x43a
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x416
	.uleb128 0x2
	.long	.LASF79
	.byte	0xc
	.byte	0x10
	.long	0x421
	.uleb128 0x2
	.long	.LASF80
	.byte	0xd
	.byte	0x12
	.long	0x38
	.uleb128 0x12
	.byte	0x10
	.byte	0xd
	.byte	0x54
	.long	0x477
	.uleb128 0x9
	.long	.LASF81
	.byte	0xd
	.byte	0x55
	.long	0x83
	.byte	0
	.uleb128 0x9
	.long	.LASF82
	.byte	0xd
	.byte	0x56
	.long	0xbd
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF83
	.byte	0xd
	.byte	0x57
	.long	0x456
	.uleb128 0x13
	.byte	0x8
	.byte	0xd
	.byte	0x5a
	.long	0x4a1
	.uleb128 0x14
	.long	.LASF84
	.byte	0xd
	.byte	0x5b
	.long	0x4a1
	.uleb128 0x14
	.long	.LASF85
	.byte	0xd
	.byte	0x5c
	.long	0x58
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x4a
	.uleb128 0x8
	.long	.LASF86
	.byte	0x30
	.byte	0xd
	.byte	0x59
	.long	0x514
	.uleb128 0x15
	.string	"ref"
	.byte	0xd
	.byte	0x5d
	.long	0x482
	.byte	0
	.uleb128 0x9
	.long	.LASF87
	.byte	0xd
	.byte	0x5e
	.long	0x514
	.byte	0x8
	.uleb128 0x9
	.long	.LASF88
	.byte	0xd
	.byte	0x5f
	.long	0x51a
	.byte	0x10
	.uleb128 0x9
	.long	.LASF89
	.byte	0xd
	.byte	0x60
	.long	0x51a
	.byte	0x18
	.uleb128 0x9
	.long	.LASF90
	.byte	0xd
	.byte	0x61
	.long	0x58
	.byte	0x20
	.uleb128 0x9
	.long	.LASF91
	.byte	0xd
	.byte	0x62
	.long	0x58
	.byte	0x24
	.uleb128 0x9
	.long	.LASF92
	.byte	0xd
	.byte	0x63
	.long	0x58
	.byte	0x28
	.uleb128 0x9
	.long	.LASF93
	.byte	0xd
	.byte	0x64
	.long	0x58
	.byte	0x2c
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x477
	.uleb128 0x6
	.byte	0x8
	.long	0x4a7
	.uleb128 0x8
	.long	.LASF94
	.byte	0x38
	.byte	0xd
	.byte	0x69
	.long	0x58d
	.uleb128 0x9
	.long	.LASF95
	.byte	0xd
	.byte	0x6b
	.long	0x44b
	.byte	0
	.uleb128 0x9
	.long	.LASF96
	.byte	0xd
	.byte	0x6e
	.long	0x4a1
	.byte	0x8
	.uleb128 0x9
	.long	.LASF97
	.byte	0xd
	.byte	0x71
	.long	0x4a1
	.byte	0x10
	.uleb128 0x9
	.long	.LASF98
	.byte	0xd
	.byte	0x74
	.long	0x58
	.byte	0x18
	.uleb128 0x9
	.long	.LASF99
	.byte	0xd
	.byte	0x77
	.long	0x58
	.byte	0x1c
	.uleb128 0x9
	.long	.LASF100
	.byte	0xd
	.byte	0x7a
	.long	0x51a
	.byte	0x20
	.uleb128 0x9
	.long	.LASF101
	.byte	0xd
	.byte	0x7d
	.long	0x58d
	.byte	0x28
	.uleb128 0x9
	.long	.LASF102
	.byte	0xd
	.byte	0x7e
	.long	0x58d
	.byte	0x30
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x520
	.uleb128 0x10
	.long	.LASF103
	.byte	0xd
	.byte	0x80
	.long	0x58d
	.uleb128 0x10
	.long	.LASF104
	.byte	0xd
	.byte	0x8c
	.long	0x58
	.uleb128 0x10
	.long	.LASF105
	.byte	0xd
	.byte	0xa5
	.long	0xbd
	.uleb128 0x10
	.long	.LASF106
	.byte	0xd
	.byte	0xb2
	.long	0x440
	.uleb128 0x8
	.long	.LASF107
	.byte	0x10
	.byte	0xe
	.byte	0x17
	.long	0x5e4
	.uleb128 0x9
	.long	.LASF108
	.byte	0xe
	.byte	0x19
	.long	0x95
	.byte	0
	.uleb128 0x9
	.long	.LASF109
	.byte	0xe
	.byte	0x1a
	.long	0xbd
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF110
	.byte	0xe
	.byte	0x1b
	.long	0x5bf
	.uleb128 0x10
	.long	.LASF111
	.byte	0x1
	.byte	0x5
	.long	0x2e4
	.uleb128 0x2
	.long	.LASF112
	.byte	0xf
	.byte	0x18
	.long	0x66
	.uleb128 0x2
	.long	.LASF113
	.byte	0xf
	.byte	0x19
	.long	0x78
	.uleb128 0x2
	.long	.LASF114
	.byte	0xf
	.byte	0x1a
	.long	0x8a
	.uleb128 0x2
	.long	.LASF115
	.byte	0xf
	.byte	0x1b
	.long	0x9c
	.uleb128 0x2
	.long	.LASF116
	.byte	0x1
	.byte	0xb
	.long	0xbf
	.uleb128 0x7
	.long	0x626
	.uleb128 0xc
	.long	0xc5
	.long	0x645
	.uleb128 0x16
	.long	0x38
	.byte	0
	.uleb128 0x8
	.long	.LASF117
	.byte	0x3
	.byte	0x1
	.byte	0x13
	.long	0x682
	.uleb128 0x15
	.string	"len"
	.byte	0x1
	.byte	0x14
	.long	0x5fa
	.byte	0
	.uleb128 0x9
	.long	.LASF118
	.byte	0x1
	.byte	0x15
	.long	0x5fa
	.byte	0x1
	.uleb128 0x9
	.long	.LASF81
	.byte	0x1
	.byte	0x16
	.long	0x4a
	.byte	0x2
	.uleb128 0x15
	.string	"buf"
	.byte	0x1
	.byte	0x17
	.long	0x636
	.byte	0x3
	.byte	0
	.uleb128 0x8
	.long	.LASF119
	.byte	0x5
	.byte	0x1
	.byte	0x19
	.long	0x6bf
	.uleb128 0x15
	.string	"len"
	.byte	0x1
	.byte	0x1a
	.long	0x605
	.byte	0
	.uleb128 0x9
	.long	.LASF118
	.byte	0x1
	.byte	0x1b
	.long	0x605
	.byte	0x2
	.uleb128 0x9
	.long	.LASF81
	.byte	0x1
	.byte	0x1c
	.long	0x4a
	.byte	0x4
	.uleb128 0x15
	.string	"buf"
	.byte	0x1
	.byte	0x1d
	.long	0x636
	.byte	0x5
	.byte	0
	.uleb128 0x8
	.long	.LASF120
	.byte	0x9
	.byte	0x1
	.byte	0x1f
	.long	0x6fc
	.uleb128 0x15
	.string	"len"
	.byte	0x1
	.byte	0x20
	.long	0x610
	.byte	0
	.uleb128 0x9
	.long	.LASF118
	.byte	0x1
	.byte	0x21
	.long	0x610
	.byte	0x4
	.uleb128 0x9
	.long	.LASF81
	.byte	0x1
	.byte	0x22
	.long	0x4a
	.byte	0x8
	.uleb128 0x15
	.string	"buf"
	.byte	0x1
	.byte	0x23
	.long	0x636
	.byte	0x9
	.byte	0
	.uleb128 0x8
	.long	.LASF121
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.long	0x739
	.uleb128 0x15
	.string	"len"
	.byte	0x1
	.byte	0x26
	.long	0x61b
	.byte	0
	.uleb128 0x9
	.long	.LASF118
	.byte	0x1
	.byte	0x27
	.long	0x61b
	.byte	0x8
	.uleb128 0x9
	.long	.LASF81
	.byte	0x1
	.byte	0x28
	.long	0x4a
	.byte	0x10
	.uleb128 0x15
	.string	"buf"
	.byte	0x1
	.byte	0x29
	.long	0x636
	.byte	0x11
	.byte	0
	.uleb128 0x2
	.long	.LASF122
	.byte	0x10
	.byte	0x6
	.long	0x2d
	.uleb128 0x2
	.long	.LASF123
	.byte	0x10
	.byte	0x7
	.long	0x2d
	.uleb128 0x2
	.long	.LASF124
	.byte	0x10
	.byte	0x9
	.long	0x75a
	.uleb128 0x8
	.long	.LASF125
	.byte	0x38
	.byte	0x10
	.byte	0xb
	.long	0x7b7
	.uleb128 0x15
	.string	"key"
	.byte	0x10
	.byte	0xc
	.long	0x739
	.byte	0
	.uleb128 0x9
	.long	.LASF126
	.byte	0x10
	.byte	0xd
	.long	0x7b7
	.byte	0x8
	.uleb128 0x9
	.long	.LASF127
	.byte	0x10
	.byte	0xe
	.long	0x7b7
	.byte	0x10
	.uleb128 0x9
	.long	.LASF128
	.byte	0x10
	.byte	0xf
	.long	0x7b7
	.byte	0x18
	.uleb128 0x15
	.string	"k"
	.byte	0x10
	.byte	0x10
	.long	0x7bd
	.byte	0x20
	.uleb128 0x15
	.string	"v"
	.byte	0x10
	.byte	0x11
	.long	0x7bd
	.byte	0x28
	.uleb128 0x9
	.long	.LASF129
	.byte	0x10
	.byte	0x12
	.long	0x33d
	.byte	0x30
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x74f
	.uleb128 0x6
	.byte	0x8
	.long	0x5e4
	.uleb128 0x2
	.long	.LASF130
	.byte	0x10
	.byte	0x16
	.long	0x7ce
	.uleb128 0x8
	.long	.LASF131
	.byte	0x18
	.byte	0x10
	.byte	0x1a
	.long	0x7ff
	.uleb128 0x9
	.long	.LASF78
	.byte	0x10
	.byte	0x1b
	.long	0x7b7
	.byte	0
	.uleb128 0x9
	.long	.LASF132
	.byte	0x10
	.byte	0x1c
	.long	0x7b7
	.byte	0x8
	.uleb128 0x9
	.long	.LASF133
	.byte	0x10
	.byte	0x1d
	.long	0x7ff
	.byte	0x10
	.byte	0
	.uleb128 0x2
	.long	.LASF134
	.byte	0x10
	.byte	0x18
	.long	0x80a
	.uleb128 0x6
	.byte	0x8
	.long	0x810
	.uleb128 0x17
	.long	0x825
	.uleb128 0x18
	.long	0x7b7
	.uleb128 0x18
	.long	0x7b7
	.uleb128 0x18
	.long	0x7b7
	.byte	0
	.uleb128 0x12
	.byte	0x10
	.byte	0x11
	.byte	0xe
	.long	0x846
	.uleb128 0x9
	.long	.LASF135
	.byte	0x11
	.byte	0xf
	.long	0x846
	.byte	0
	.uleb128 0x9
	.long	.LASF136
	.byte	0x11
	.byte	0x10
	.long	0x846
	.byte	0x8
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x7c3
	.uleb128 0x2
	.long	.LASF137
	.byte	0x11
	.byte	0x11
	.long	0x825
	.uleb128 0x19
	.long	.LASF142
	.byte	0x2
	.byte	0x8d
	.long	0xbd
	.quad	.LFB20
	.quad	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.long	0x8bb
	.uleb128 0x1a
	.long	.LASF138
	.byte	0x2
	.byte	0x8d
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1b
	.string	"k"
	.byte	0x2
	.byte	0x8d
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1c
	.string	"key"
	.byte	0x2
	.byte	0x8e
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1c
	.string	"c"
	.byte	0x2
	.byte	0x8f
	.long	0x8bb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1d
	.long	.LASF139
	.byte	0x2
	.byte	0x90
	.long	0xbd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x84c
	.uleb128 0x1e
	.long	.LASF140
	.byte	0x2
	.byte	0x87
	.quad	.LFB19
	.quad	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.long	0x921
	.uleb128 0x1a
	.long	.LASF138
	.byte	0x2
	.byte	0x87
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1b
	.string	"k"
	.byte	0x2
	.byte	0x87
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1a
	.long	.LASF82
	.byte	0x2
	.byte	0x87
	.long	0xbd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1c
	.string	"key"
	.byte	0x2
	.byte	0x89
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1c
	.string	"c"
	.byte	0x2
	.byte	0x8a
	.long	0x8bb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x1e
	.long	.LASF141
	.byte	0x2
	.byte	0x7e
	.quad	.LFB18
	.quad	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.long	0x991
	.uleb128 0x1b
	.string	"opt"
	.byte	0x2
	.byte	0x7e
	.long	0x83
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1a
	.long	.LASF138
	.byte	0x2
	.byte	0x7e
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1b
	.string	"k"
	.byte	0x2
	.byte	0x7e
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1a
	.long	.LASF73
	.byte	0x2
	.byte	0x7e
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1c
	.string	"key"
	.byte	0x2
	.byte	0x83
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1c
	.string	"ret"
	.byte	0x2
	.byte	0x84
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x19
	.long	.LASF143
	.byte	0x2
	.byte	0x74
	.long	0x7bd
	.quad	.LFB17
	.quad	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0x9f5
	.uleb128 0x1a
	.long	.LASF138
	.byte	0x2
	.byte	0x74
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1b
	.string	"k"
	.byte	0x2
	.byte	0x74
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1c
	.string	"key"
	.byte	0x2
	.byte	0x75
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1c
	.string	"c"
	.byte	0x2
	.byte	0x76
	.long	0x8bb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1d
	.long	.LASF73
	.byte	0x2
	.byte	0x77
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x19
	.long	.LASF144
	.byte	0x2
	.byte	0x6e
	.long	0x7bd
	.quad	.LFB16
	.quad	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0xa57
	.uleb128 0x1a
	.long	.LASF138
	.byte	0x2
	.byte	0x6e
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1b
	.string	"k"
	.byte	0x2
	.byte	0x6e
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1b
	.string	"v"
	.byte	0x2
	.byte	0x6e
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1c
	.string	"key"
	.byte	0x2
	.byte	0x70
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1c
	.string	"c"
	.byte	0x2
	.byte	0x71
	.long	0x8bb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x19
	.long	.LASF145
	.byte	0x2
	.byte	0x59
	.long	0x8bb
	.quad	.LFB15
	.quad	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0xacc
	.uleb128 0x1a
	.long	.LASF74
	.byte	0x2
	.byte	0x59
	.long	0x83
	.uleb128 0x3
	.byte	0x91
	.sleb128 -68
	.uleb128 0x1c
	.string	"c"
	.byte	0x2
	.byte	0x5a
	.long	0x8bb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1d
	.long	.LASF135
	.byte	0x2
	.byte	0x60
	.long	0x846
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1d
	.long	.LASF146
	.byte	0x2
	.byte	0x61
	.long	0x7b7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1d
	.long	.LASF136
	.byte	0x2
	.byte	0x64
	.long	0x846
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1d
	.long	.LASF147
	.byte	0x2
	.byte	0x65
	.long	0x7b7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.byte	0
	.uleb128 0x1e
	.long	.LASF148
	.byte	0x2
	.byte	0x43
	.quad	.LFB14
	.quad	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0xb2f
	.uleb128 0x1a
	.long	.LASF149
	.byte	0x2
	.byte	0x43
	.long	0x846
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1b
	.string	"key"
	.byte	0x2
	.byte	0x43
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1a
	.long	.LASF73
	.byte	0x2
	.byte	0x43
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1d
	.long	.LASF150
	.byte	0x2
	.byte	0x46
	.long	0x7b7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1c
	.string	"hk"
	.byte	0x2
	.byte	0x47
	.long	0x744
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x19
	.long	.LASF151
	.byte	0x2
	.byte	0x27
	.long	0x7bd
	.quad	.LFB13
	.quad	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0xb96
	.uleb128 0x1a
	.long	.LASF152
	.byte	0x2
	.byte	0x27
	.long	0x846
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1b
	.string	"key"
	.byte	0x2
	.byte	0x27
	.long	0x7bd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1d
	.long	.LASF150
	.byte	0x2
	.byte	0x28
	.long	0x7b7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1d
	.long	.LASF132
	.byte	0x2
	.byte	0x28
	.long	0x7b7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1c
	.string	"hk"
	.byte	0x2
	.byte	0x2a
	.long	0x744
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x1f
	.long	.LASF153
	.byte	0x2
	.byte	0xf
	.quad	.LFB12
	.quad	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.long	0xbea
	.uleb128 0x1a
	.long	.LASF154
	.byte	0x2
	.byte	0xf
	.long	0x7b7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1a
	.long	.LASF150
	.byte	0x2
	.byte	0xf
	.long	0x7b7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1a
	.long	.LASF132
	.byte	0x2
	.byte	0xf
	.long	0x7b7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1c
	.string	"p"
	.byte	0x2
	.byte	0x11
	.long	0xbea
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x7b7
	.uleb128 0x20
	.long	.LASF160
	.byte	0x1
	.byte	0x37
	.long	0x2d
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1b
	.string	"s"
	.byte	0x1
	.byte	0x37
	.long	0x631
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1d
	.long	.LASF81
	.byte	0x1
	.byte	0x38
	.long	0x4a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -17
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x17
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF13:
	.string	"__off_t"
.LASF96:
	.string	"first_address"
.LASF29:
	.string	"_chain"
.LASF91:
	.string	"szidx"
.LASF143:
	.string	"object_member_get"
.LASF0:
	.string	"size_t"
.LASF35:
	.string	"_shortbuf"
.LASF116:
	.string	"string"
.LASF7:
	.string	"__uint8_t"
.LASF151:
	.string	"member_find"
.LASF108:
	.string	"type"
.LASF52:
	.string	"_IO_2_1_stderr_"
.LASF23:
	.string	"_IO_buf_base"
.LASF140:
	.string	"object_func_add"
.LASF60:
	.string	"long long unsigned int"
.LASF123:
	.string	"rbtree_key_int_t"
.LASF130:
	.string	"rbtree_t"
.LASF82:
	.string	"addr"
.LASF94:
	.string	"arena_object"
.LASF141:
	.string	"object_unary_operator"
.LASF142:
	.string	"object_func_addr"
.LASF75:
	.string	"next"
.LASF138:
	.string	"object"
.LASF68:
	.string	"__timezone"
.LASF58:
	.string	"long long int"
.LASF6:
	.string	"signed char"
.LASF136:
	.string	"funcs"
.LASF104:
	.string	"maxarenas"
.LASF76:
	.string	"ListNode"
.LASF30:
	.string	"_fileno"
.LASF122:
	.string	"rbtree_key_t"
.LASF128:
	.string	"parent"
.LASF98:
	.string	"nfreepools"
.LASF154:
	.string	"temp"
.LASF11:
	.string	"long int"
.LASF100:
	.string	"freepools"
.LASF16:
	.string	"_flags"
.LASF121:
	.string	"stringhdr64"
.LASF24:
	.string	"_IO_buf_end"
.LASF155:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -fno-builtin"
.LASF111:
	.string	"LSTRING_NOINIT"
.LASF32:
	.string	"_old_offset"
.LASF37:
	.string	"_offset"
.LASF93:
	.string	"maxnextoffset"
.LASF85:
	.string	"count"
.LASF10:
	.string	"__uint32_t"
.LASF71:
	.string	"timezone"
.LASF125:
	.string	"rbtree_node_s"
.LASF124:
	.string	"rbtree_node_t"
.LASF73:
	.string	"value"
.LASF46:
	.string	"_IO_marker"
.LASF133:
	.string	"insert"
.LASF83:
	.string	"block"
.LASF5:
	.string	"unsigned int"
.LASF113:
	.string	"uint16_t"
.LASF97:
	.string	"pool_address"
.LASF2:
	.string	"long unsigned int"
.LASF159:
	.string	"_IO_FILE_plus"
.LASF21:
	.string	"_IO_write_ptr"
.LASF70:
	.string	"daylight"
.LASF56:
	.string	"sys_nerr"
.LASF48:
	.string	"_sbuf"
.LASF109:
	.string	"data"
.LASF74:
	.string	"size"
.LASF4:
	.string	"short unsigned int"
.LASF72:
	.string	"link_list"
.LASF135:
	.string	"members"
.LASF25:
	.string	"_IO_save_base"
.LASF157:
	.string	"/home/xiaodo/c++/colang/tests/src/internal"
.LASF53:
	.string	"stdin"
.LASF101:
	.string	"nextarena"
.LASF150:
	.string	"node"
.LASF36:
	.string	"_lock"
.LASF31:
	.string	"_flags2"
.LASF127:
	.string	"right"
.LASF54:
	.string	"stdout"
.LASF156:
	.string	"/home/xiaodo/c++/colang/src/internal/Object.c"
.LASF50:
	.string	"_IO_2_1_stdin_"
.LASF79:
	.string	"List"
.LASF137:
	.string	"Class"
.LASF18:
	.string	"_IO_read_end"
.LASF90:
	.string	"arenaindex"
.LASF62:
	.string	"optarg"
.LASF1:
	.string	"__u_char"
.LASF95:
	.string	"address"
.LASF63:
	.string	"optind"
.LASF117:
	.string	"stringhdr8"
.LASF131:
	.string	"rbtree_s"
.LASF87:
	.string	"freeblock"
.LASF17:
	.string	"_IO_read_ptr"
.LASF59:
	.string	"u_char"
.LASF115:
	.string	"uint64_t"
.LASF102:
	.string	"prevarena"
.LASF160:
	.string	"stringlen"
.LASF158:
	.string	"_IO_lock_t"
.LASF45:
	.string	"_IO_FILE"
.LASF152:
	.string	"rbtree"
.LASF61:
	.string	"__environ"
.LASF80:
	.string	"Co_uintptr_t"
.LASF12:
	.string	"__uint64_t"
.LASF43:
	.string	"_mode"
.LASF147:
	.string	"funcs_sentinel"
.LASF49:
	.string	"_pos"
.LASF153:
	.string	"member_insert_or_update"
.LASF57:
	.string	"sys_errlist"
.LASF28:
	.string	"_markers"
.LASF103:
	.string	"arenas"
.LASF89:
	.string	"prevpool"
.LASF3:
	.string	"unsigned char"
.LASF107:
	.string	"core_value"
.LASF134:
	.string	"rbtree_insert_pt"
.LASF8:
	.string	"short int"
.LASF146:
	.string	"members_sentinel"
.LASF34:
	.string	"_vtable_offset"
.LASF69:
	.string	"tzname"
.LASF51:
	.string	"_IO_2_1_stdout_"
.LASF99:
	.string	"ntotalpools"
.LASF144:
	.string	"object_member_update"
.LASF67:
	.string	"__daylight"
.LASF65:
	.string	"optopt"
.LASF148:
	.string	"member_insert"
.LASF114:
	.string	"uint32_t"
.LASF92:
	.string	"nextoffset"
.LASF129:
	.string	"color"
.LASF15:
	.string	"char"
.LASF139:
	.string	"func"
.LASF9:
	.string	"__uint16_t"
.LASF64:
	.string	"opterr"
.LASF118:
	.string	"alloc"
.LASF47:
	.string	"_next"
.LASF14:
	.string	"__off64_t"
.LASF33:
	.string	"_cur_column"
.LASF19:
	.string	"_IO_read_base"
.LASF27:
	.string	"_IO_save_end"
.LASF106:
	.string	"Hugmem"
.LASF105:
	.string	"sp_start"
.LASF38:
	.string	"__pad1"
.LASF39:
	.string	"__pad2"
.LASF40:
	.string	"__pad3"
.LASF41:
	.string	"__pad4"
.LASF42:
	.string	"__pad5"
.LASF84:
	.string	"_padding"
.LASF22:
	.string	"_IO_write_end"
.LASF44:
	.string	"_unused2"
.LASF55:
	.string	"stderr"
.LASF86:
	.string	"pool_header"
.LASF145:
	.string	"object_create"
.LASF149:
	.string	"tree"
.LASF110:
	.string	"Value"
.LASF120:
	.string	"stringhdr32"
.LASF112:
	.string	"uint8_t"
.LASF26:
	.string	"_IO_backup_base"
.LASF81:
	.string	"flags"
.LASF77:
	.string	"list"
.LASF132:
	.string	"sentinel"
.LASF66:
	.string	"__tzname"
.LASF88:
	.string	"nextpool"
.LASF20:
	.string	"_IO_write_base"
.LASF126:
	.string	"left"
.LASF119:
	.string	"stringhdr16"
.LASF78:
	.string	"root"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

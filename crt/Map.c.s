	.file	"Map.c"
	.text
.Ltext0:
	.type	rbtree_min, @function
rbtree_min:
.LFB5:
	.file 1 "/home/xiaodo/c++/colang/src/internal/Map.h"
	.loc 1 69 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	.loc 1 70 0
	jmp	.L2
.L3:
	.loc 1 71 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
.L2:
	.loc 1 70 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -16(%rbp)
	jne	.L3
	.loc 1 74 0
	movq	-8(%rbp), %rax
	.loc 1 75 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	rbtree_min, .-rbtree_min
	.type	stringlen, @function
stringlen:
.LFB6:
	.file 2 "/home/xiaodo/c++/colang/src/internal/String.h"
	.loc 2 55 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	.loc 2 56 0
	movq	-24(%rbp), %rax
	subq	$1, %rax
	movzbl	(%rax), %eax
	movb	%al, -1(%rbp)
	.loc 2 57 0
	movzbl	-1(%rbp), %eax
	andl	$7, %eax
	cmpl	$4, %eax
	ja	.L6
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L8(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L8(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
#	.section	.rodata
	.align 4
	.align 4
.L8:
	.long	.L7-.L8
	.long	.L9-.L8
	.long	.L10-.L8
	.long	.L11-.L8
	.long	.L12-.L8
	.text
.L7:
	.loc 2 59 0
	movzbl	-1(%rbp), %eax
	shrb	$3, %al
	movzbl	%al, %eax
	jmp	.L13
.L9:
	.loc 2 61 0
	movq	-24(%rbp), %rax
	subq	$3, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	jmp	.L13
.L10:
	.loc 2 63 0
	movq	-24(%rbp), %rax
	subq	$5, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	jmp	.L13
.L11:
	.loc 2 65 0
	movq	-24(%rbp), %rax
	subq	$9, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	jmp	.L13
.L12:
	.loc 2 67 0
	movq	-24(%rbp), %rax
	subq	$17, %rax
	movq	(%rax), %rax
	jmp	.L13
.L6:
	.loc 2 69 0
	movl	$0, %eax
.L13:
	.loc 2 70 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	stringlen, .-stringlen
	.globl	map_insert_or_update
	.type	map_insert_or_update, @function
map_insert_or_update:
.LFB12:
	.file 3 "/home/xiaodo/c++/colang/src/internal/Map.c"
	.loc 3 10 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
.L21:
	.loc 3 15 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jne	.L15
	.loc 3 16 0
	movq	-24(%rbp), %rax
	movq	40(%rax), %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	40(%rax), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jne	.L15
	.loc 3 17 0
	movq	-32(%rbp), %rax
	movq	40(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, 40(%rax)
	.loc 3 18 0
	jmp	.L14
.L15:
	.loc 3 21 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jnb	.L17
	.loc 3 21 0 is_stmt 0 discriminator 1
	movq	-24(%rbp), %rax
	addq	$8, %rax
	jmp	.L18
.L17:
	.loc 3 21 0 discriminator 2
	movq	-24(%rbp), %rax
	addq	$16, %rax
.L18:
	.loc 3 21 0 discriminator 4
	movq	%rax, -8(%rbp)
	.loc 3 23 0 is_stmt 1 discriminator 4
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -40(%rbp)
	je	.L23
	.loc 3 27 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 3 15 0
	jmp	.L21
.L23:
	.loc 3 24 0
	nop
	.loc 3 30 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, (%rax)
	.loc 3 31 0
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 3 32 0
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 3 33 0
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 3 34 0
	movq	-32(%rbp), %rax
	movb	$1, 48(%rax)
.L14:
	.loc 3 35 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	map_insert_or_update, .-map_insert_or_update
	.globl	hash_key
	.type	hash_key, @function
hash_key:
.LFB13:
	.loc 3 36 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 3 38 0
	movl	$0, -8(%rbp)
	.loc 3 39 0
	movl	$0, -4(%rbp)
	jmp	.L25
.L26:
	.loc 3 40 0 discriminator 3
	movl	-8(%rbp), %edx
	movl	%edx, %eax
	sall	$5, %eax
	subl	%edx, %eax
	movl	%eax, %ecx
	movl	-4(%rbp), %edx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	addl	%ecx, %eax
	movl	%eax, -8(%rbp)
	.loc 3 39 0 discriminator 3
	addl	$1, -4(%rbp)
.L25:
	.loc 3 39 0 is_stmt 0 discriminator 1
	movl	-4(%rbp), %eax
	cmpq	%rax, -32(%rbp)
	ja	.L26
	.loc 3 42 0 is_stmt 1
	movl	-8(%rbp), %eax
	.loc 3 43 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	hash_key, .-hash_key
	.globl	map_create
	.type	map_create, @function
map_create:
.LFB14:
	.loc 3 45 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	.loc 3 46 0
	movl	$24, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 3 47 0
	movl	$56, %edi
	call	gc_malloc@PLT
	movq	%rax, -16(%rbp)
	.loc 3 48 0
	movq	-16(%rbp), %rax
	movb	$0, 48(%rax)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	movq	-8(%rbp), %rax
	leaq	map_insert_or_update(%rip), %rdx
	movq	%rdx, 16(%rax)
	.loc 3 49 0
	movq	-8(%rbp), %rax
	.loc 3 50 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	map_create, .-map_create
	.globl	map_insert
	.type	map_insert, @function
map_insert:
.LFB15:
	.loc 3 52 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	.loc 3 54 0
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	.loc 3 55 0
	movl	$56, %edi
	call	gc_malloc@PLT
	movq	%rax, -24(%rbp)
	.loc 3 56 0
	movq	$0, -8(%rbp)
	.loc 3 57 0
	movq	-48(%rbp), %rax
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
	.loc 3 61 0
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L31
.L32:
	.loc 3 63 0
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	stringlen
	movq	%rax, %rdx
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	hash_key
	movl	%eax, %eax
	movq	%rax, -8(%rbp)
.L31:
	.loc 3 65 0
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	.loc 3 66 0
	movq	-24(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, 32(%rax)
	.loc 3 67 0
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rdx, 40(%rax)
	.loc 3 68 0
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	rbtree_insert
	.loc 3 69 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	map_insert, .-map_insert
	.globl	map_find
	.type	map_find, @function
map_find:
.LFB16:
	.loc 3 70 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	.loc 3 71 0
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 3 74 0
	movq	$0, -16(%rbp)
	.loc 3 75 0
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L37
	cmpq	$3, %rax
	jg	.L38
	cmpq	$1, %rax
	jl	.L36
	jmp	.L39
.L38:
	cmpq	$4, %rax
	jne	.L36
.L39:
	.loc 3 79 0
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L36
.L37:
	.loc 3 81 0
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	stringlen
	movq	%rax, %rdx
	movq	-48(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	hash_key
	movl	%eax, %eax
	movq	%rax, -16(%rbp)
	.loc 3 82 0
	nop
.L36:
	.loc 3 84 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 3 85 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -32(%rbp)
	.loc 3 87 0
	jmp	.L40
.L45:
	.loc 3 89 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -16(%rbp)
	je	.L41
	.loc 3 90 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -16(%rbp)
	jnb	.L42
	.loc 3 90 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	jmp	.L43
.L42:
	.loc 3 90 0 discriminator 2
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
.L43:
	.loc 3 90 0 discriminator 4
	movq	%rax, -8(%rbp)
	.loc 3 91 0 is_stmt 1 discriminator 4
	jmp	.L40
.L41:
	.loc 3 93 0
	movq	-8(%rbp), %rax
	movq	32(%rax), %rax
	movq	(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jne	.L40
	.loc 3 94 0
	movq	-8(%rbp), %rax
	movq	40(%rax), %rax
	jmp	.L44
.L40:
	.loc 3 87 0
	movq	-8(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jne	.L45
	.loc 3 97 0
	movl	$0, %eax
.L44:
	.loc 3 98 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	map_find, .-map_find
	.globl	rbtree_insert
	.type	rbtree_insert, @function
rbtree_insert:
.LFB17:
	.loc 3 102 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	.loc 3 107 0
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	.loc 3 108 0
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	.loc 3 110 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -16(%rbp)
	jne	.L47
	.loc 3 111 0
	movq	-48(%rbp), %rax
	movq	$0, 24(%rax)
	.loc 3 112 0
	movq	-48(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 3 113 0
	movq	-48(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 3 114 0
	movq	-48(%rbp), %rax
	movb	$0, 48(%rax)
	.loc 3 115 0
	movq	-8(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, (%rax)
	.loc 3 117 0
	jmp	.L46
.L47:
	.loc 3 120 0
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	(%rdx), %rcx
	movq	-16(%rbp), %rdx
	movq	-48(%rbp), %rsi
	movq	%rcx, %rdi
	call	*%rax
.LVL0:
	.loc 3 124 0
	jmp	.L49
.L57:
	.loc 3 126 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	cmpq	%rax, %rdx
	jne	.L50
	.loc 3 127 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 3 129 0
	movq	-24(%rbp), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	je	.L51
	.loc 3 130 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movb	$0, 48(%rax)
	.loc 3 131 0
	movq	-24(%rbp), %rax
	movb	$0, 48(%rax)
	.loc 3 132 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	24(%rax), %rax
	movb	$1, 48(%rax)
	.loc 3 133 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	24(%rax), %rax
	movq	%rax, -48(%rbp)
	jmp	.L49
.L51:
	.loc 3 136 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rax
	cmpq	%rax, -48(%rbp)
	jne	.L53
	.loc 3 137 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -48(%rbp)
	.loc 3 138 0
	movq	-48(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	rbtree_left_rotate
.L53:
	.loc 3 141 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movb	$0, 48(%rax)
	.loc 3 142 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	24(%rax), %rax
	movb	$1, 48(%rax)
	.loc 3 143 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	24(%rax), %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	rbtree_right_rotate
	jmp	.L49
.L50:
	.loc 3 147 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 3 149 0
	movq	-24(%rbp), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	je	.L54
	.loc 3 150 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movb	$0, 48(%rax)
	.loc 3 151 0
	movq	-24(%rbp), %rax
	movb	$0, 48(%rax)
	.loc 3 152 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	24(%rax), %rax
	movb	$1, 48(%rax)
	.loc 3 153 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	24(%rax), %rax
	movq	%rax, -48(%rbp)
	jmp	.L49
.L54:
	.loc 3 156 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -48(%rbp)
	jne	.L55
	.loc 3 157 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -48(%rbp)
	.loc 3 158 0
	movq	-48(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	rbtree_right_rotate
.L55:
	.loc 3 161 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movb	$0, 48(%rax)
	.loc 3 162 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	24(%rax), %rax
	movb	$1, 48(%rax)
	.loc 3 163 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	24(%rax), %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	rbtree_left_rotate
.L49:
	.loc 3 124 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -48(%rbp)
	je	.L56
	.loc 3 124 0 is_stmt 0 discriminator 1
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	jne	.L57
.L56:
	.loc 3 168 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movb	$0, 48(%rax)
.L46:
	.loc 3 169 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	rbtree_insert, .-rbtree_insert
	.globl	rbtree_insert_value
	.type	rbtree_insert_value, @function
rbtree_insert_value:
.LFB18:
	.loc 3 175 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
.L63:
	.loc 3 180 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, %rdx
	jnb	.L59
	.loc 3 180 0 is_stmt 0 discriminator 1
	movq	-24(%rbp), %rax
	addq	$8, %rax
	jmp	.L60
.L59:
	.loc 3 180 0 discriminator 2
	movq	-24(%rbp), %rax
	addq	$16, %rax
.L60:
	.loc 3 180 0 discriminator 4
	movq	%rax, -8(%rbp)
	.loc 3 182 0 is_stmt 1 discriminator 4
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -40(%rbp)
	je	.L65
	.loc 3 186 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 3 180 0
	jmp	.L63
.L65:
	.loc 3 183 0
	nop
	.loc 3 189 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, (%rax)
	.loc 3 190 0
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 3 191 0
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 3 192 0
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 3 193 0
	movq	-32(%rbp), %rax
	movb	$1, 48(%rax)
	.loc 3 194 0
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	rbtree_insert_value, .-rbtree_insert_value
	.globl	rbtree_insert_timer_value
	.type	rbtree_insert_timer_value, @function
rbtree_insert_timer_value:
.LFB19:
	.loc 3 200 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
.L69:
	.loc 3 214 0
	movq	-24(%rbp), %rax
	addq	$16, %rax
	movq	%rax, -8(%rbp)
	.loc 3 217 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -40(%rbp)
	je	.L71
	.loc 3 221 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 3 214 0
	jmp	.L69
.L71:
	.loc 3 218 0
	nop
	.loc 3 224 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, (%rax)
	.loc 3 225 0
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 3 226 0
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 3 227 0
	movq	-32(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 3 228 0
	movq	-32(%rbp), %rax
	movb	$1, 48(%rax)
	.loc 3 229 0
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	rbtree_insert_timer_value, .-rbtree_insert_timer_value
	.globl	rbtree_delete
	.type	rbtree_delete, @function
rbtree_delete:
.LFB20:
	.loc 3 234 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	.loc 3 240 0
	movq	-56(%rbp), %rax
	movq	%rax, -32(%rbp)
	.loc 3 241 0
	movq	-56(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -40(%rbp)
	.loc 3 243 0
	movq	-64(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -40(%rbp)
	jne	.L73
	.loc 3 244 0
	movq	-64(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -16(%rbp)
	.loc 3 245 0
	movq	-64(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L74
.L73:
	.loc 3 247 0
	movq	-64(%rbp), %rax
	movq	16(%rax), %rax
	cmpq	%rax, -40(%rbp)
	jne	.L75
	.loc 3 248 0
	movq	-64(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -16(%rbp)
	.loc 3 249 0
	movq	-64(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L74
.L75:
	.loc 3 252 0
	movq	-64(%rbp), %rax
	movq	16(%rax), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	rbtree_min
	movq	%rax, -8(%rbp)
	.loc 3 253 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -16(%rbp)
.L74:
	.loc 3 256 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -8(%rbp)
	jne	.L76
	.loc 3 257 0
	movq	-32(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, (%rax)
	.loc 3 258 0
	movq	-16(%rbp), %rax
	movb	$0, 48(%rax)
	.loc 3 261 0
	movq	-64(%rbp), %rax
	movq	$0, 8(%rax)
	.loc 3 262 0
	movq	-64(%rbp), %rax
	movq	$0, 16(%rax)
	.loc 3 263 0
	movq	-64(%rbp), %rax
	movq	$0, 24(%rax)
	.loc 3 264 0
	movq	-64(%rbp), %rax
	movq	$0, (%rax)
	.loc 3 266 0
	jmp	.L72
.L76:
	.loc 3 269 0
	movq	-8(%rbp), %rax
	movzbl	48(%rax), %eax
	movzbl	%al, %eax
	movl	%eax, -44(%rbp)
	.loc 3 271 0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -8(%rbp)
	jne	.L78
	.loc 3 272 0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 8(%rax)
	jmp	.L79
.L78:
	.loc 3 275 0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 16(%rax)
.L79:
	.loc 3 278 0
	movq	-8(%rbp), %rax
	cmpq	-64(%rbp), %rax
	jne	.L80
	.loc 3 280 0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 24(%rax)
	jmp	.L81
.L80:
	.loc 3 284 0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	cmpq	%rax, -64(%rbp)
	jne	.L82
	.loc 3 285 0
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 24(%rax)
	jmp	.L83
.L82:
	.loc 3 288 0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 24(%rax)
.L83:
	.loc 3 291 0
	movq	-64(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 3 292 0
	movq	-64(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	.loc 3 293 0
	movq	-64(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 24(%rax)
	.loc 3 294 0
	movq	-64(%rbp), %rax
	movzbl	48(%rax), %edx
	movq	-8(%rbp), %rax
	movb	%dl, 48(%rax)
	.loc 3 296 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -64(%rbp)
	jne	.L84
	.loc 3 297 0
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	jmp	.L85
.L84:
	.loc 3 300 0
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -64(%rbp)
	jne	.L86
	.loc 3 301 0
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	jmp	.L85
.L86:
	.loc 3 303 0
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 16(%rax)
.L85:
	.loc 3 307 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -40(%rbp)
	je	.L87
	.loc 3 308 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 24(%rax)
.L87:
	.loc 3 311 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	cmpq	%rax, -40(%rbp)
	je	.L81
	.loc 3 312 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 24(%rax)
.L81:
	.loc 3 317 0
	movq	-64(%rbp), %rax
	movq	$0, 8(%rax)
	.loc 3 318 0
	movq	-64(%rbp), %rax
	movq	$0, 16(%rax)
	.loc 3 319 0
	movq	-64(%rbp), %rax
	movq	$0, 24(%rax)
	.loc 3 320 0
	movq	-64(%rbp), %rax
	movq	$0, (%rax)
	.loc 3 322 0
	cmpl	$0, -44(%rbp)
	jne	.L100
	.loc 3 328 0
	jmp	.L89
.L99:
	.loc 3 330 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -16(%rbp)
	jne	.L90
	.loc 3 331 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 3 333 0
	movq	-24(%rbp), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	je	.L91
	.loc 3 334 0
	movq	-24(%rbp), %rax
	movb	$0, 48(%rax)
	.loc 3 335 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movb	$1, 48(%rax)
	.loc 3 336 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	rbtree_left_rotate
	.loc 3 337 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rax
	movq	%rax, -24(%rbp)
.L91:
	.loc 3 340 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	jne	.L92
	.loc 3 340 0 is_stmt 0 discriminator 1
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	jne	.L92
	.loc 3 341 0 is_stmt 1
	movq	-24(%rbp), %rax
	movb	$1, 48(%rax)
	.loc 3 342 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L89
.L92:
	.loc 3 345 0
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	jne	.L94
	.loc 3 346 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movb	$0, 48(%rax)
	.loc 3 347 0
	movq	-24(%rbp), %rax
	movb	$1, 48(%rax)
	.loc 3 348 0
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	rbtree_right_rotate
	.loc 3 349 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rax
	movq	%rax, -24(%rbp)
.L94:
	.loc 3 352 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movzbl	48(%rax), %edx
	movq	-24(%rbp), %rax
	movb	%dl, 48(%rax)
	.loc 3 353 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movb	$0, 48(%rax)
	.loc 3 354 0
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movb	$0, 48(%rax)
	.loc 3 355 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	rbtree_left_rotate
	.loc 3 356 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L89
.L90:
	.loc 3 360 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 3 362 0
	movq	-24(%rbp), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	je	.L95
	.loc 3 363 0
	movq	-24(%rbp), %rax
	movb	$0, 48(%rax)
	.loc 3 364 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movb	$1, 48(%rax)
	.loc 3 365 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	rbtree_right_rotate
	.loc 3 366 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
.L95:
	.loc 3 369 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	jne	.L96
	.loc 3 369 0 is_stmt 0 discriminator 1
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	jne	.L96
	.loc 3 370 0 is_stmt 1
	movq	-24(%rbp), %rax
	movb	$1, 48(%rax)
	.loc 3 371 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L89
.L96:
	.loc 3 374 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	jne	.L97
	.loc 3 375 0
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	movb	$0, 48(%rax)
	.loc 3 376 0
	movq	-24(%rbp), %rax
	movb	$1, 48(%rax)
	.loc 3 377 0
	movq	-24(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	rbtree_left_rotate
	.loc 3 378 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
.L97:
	.loc 3 381 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movzbl	48(%rax), %edx
	movq	-24(%rbp), %rax
	movb	%dl, 48(%rax)
	.loc 3 382 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rax
	movb	$0, 48(%rax)
	.loc 3 383 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movb	$0, 48(%rax)
	.loc 3 384 0
	movq	-16(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	rbtree_right_rotate
	.loc 3 385 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
.L89:
	.loc 3 328 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -16(%rbp)
	je	.L98
	.loc 3 328 0 is_stmt 0 discriminator 1
	movq	-16(%rbp), %rax
	movzbl	48(%rax), %eax
	testb	%al, %al
	je	.L99
.L98:
	.loc 3 390 0 is_stmt 1
	movq	-16(%rbp), %rax
	movb	$0, 48(%rax)
	jmp	.L72
.L100:
	.loc 3 323 0
	nop
.L72:
	.loc 3 391 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	rbtree_delete, .-rbtree_delete
	.type	rbtree_left_rotate, @function
rbtree_left_rotate:
.LFB21:
	.loc 3 397 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 3 400 0
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 3 401 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, 16(%rax)
	.loc 3 403 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -32(%rbp)
	je	.L102
	.loc 3 404 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 24(%rax)
.L102:
	.loc 3 407 0
	movq	-40(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 24(%rax)
	.loc 3 409 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -40(%rbp)
	jne	.L103
	.loc 3 410 0
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	jmp	.L104
.L103:
	.loc 3 412 0
	movq	-40(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -40(%rbp)
	jne	.L105
	.loc 3 413 0
	movq	-40(%rbp), %rax
	movq	24(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
	jmp	.L104
.L105:
	.loc 3 416 0
	movq	-40(%rbp), %rax
	movq	24(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 16(%rax)
.L104:
	.loc 3 419 0
	movq	-8(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 3 420 0
	movq	-40(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 3 421 0
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	rbtree_left_rotate, .-rbtree_left_rotate
	.type	rbtree_right_rotate, @function
rbtree_right_rotate:
.LFB22:
	.loc 3 427 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 3 430 0
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 3 431 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 3 433 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	cmpq	%rax, -32(%rbp)
	je	.L107
	.loc 3 434 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 24(%rax)
.L107:
	.loc 3 437 0
	movq	-40(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 24(%rax)
	.loc 3 439 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -40(%rbp)
	jne	.L108
	.loc 3 440 0
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	jmp	.L109
.L108:
	.loc 3 442 0
	movq	-40(%rbp), %rax
	movq	24(%rax), %rax
	movq	16(%rax), %rax
	cmpq	%rax, -40(%rbp)
	jne	.L110
	.loc 3 443 0
	movq	-40(%rbp), %rax
	movq	24(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 16(%rax)
	jmp	.L109
.L110:
	.loc 3 446 0
	movq	-40(%rbp), %rax
	movq	24(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 8(%rax)
.L109:
	.loc 3 449 0
	movq	-8(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 3 450 0
	movq	-40(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 3 451 0
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	rbtree_right_rotate, .-rbtree_right_rotate
	.globl	rbtree_next
	.type	rbtree_next, @function
rbtree_next:
.LFB23:
	.loc 3 456 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	.loc 3 459 0
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 3 461 0
	movq	-48(%rbp), %rax
	movq	16(%rax), %rax
	cmpq	%rax, -8(%rbp)
	je	.L112
	.loc 3 462 0
	movq	-48(%rbp), %rax
	movq	16(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	rbtree_min
	jmp	.L113
.L112:
	.loc 3 465 0
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
.L116:
	.loc 3 468 0
	movq	-48(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -24(%rbp)
	.loc 3 470 0
	movq	-48(%rbp), %rax
	cmpq	-16(%rbp), %rax
	jne	.L114
	.loc 3 471 0
	movl	$0, %eax
	jmp	.L113
.L114:
	.loc 3 474 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	%rax, -48(%rbp)
	jne	.L115
	.loc 3 475 0
	movq	-24(%rbp), %rax
	jmp	.L113
.L115:
	.loc 3 478 0
	movq	-24(%rbp), %rax
	movq	%rax, -48(%rbp)
	.loc 3 468 0
	jmp	.L116
.L113:
	.loc 3 480 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	rbtree_next, .-rbtree_next
.Letext0:
	.file 4 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h"
	.file 5 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 6 "/usr/include/x86_64-linux-gnu/bits/libio.h"
	.file 7 "/usr/include/stdio.h"
	.file 8 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
	.file 9 "/usr/include/x86_64-linux-gnu/sys/types.h"
	.file 10 "/usr/include/unistd.h"
	.file 11 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h"
	.file 12 "/usr/include/time.h"
	.file 13 "/home/xiaodo/c++/colang/src/gc/Hugmem.h"
	.file 14 "/home/xiaodo/c++/colang/src/gc/gc.h"
	.file 15 "/home/xiaodo/c++/colang/src/internal/Value.h"
	.file 16 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xd4f
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
	.byte	0x4
	.byte	0xd8
	.long	0x38
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.long	.LASF1
	.byte	0x5
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
	.uleb128 0x2
	.long	.LASF5
	.byte	0x5
	.byte	0x20
	.long	0x63
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF6
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF7
	.uleb128 0x2
	.long	.LASF8
	.byte	0x5
	.byte	0x25
	.long	0x4a
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF9
	.uleb128 0x2
	.long	.LASF10
	.byte	0x5
	.byte	0x27
	.long	0x51
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.long	.LASF11
	.byte	0x5
	.byte	0x29
	.long	0x63
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF12
	.uleb128 0x2
	.long	.LASF13
	.byte	0x5
	.byte	0x2c
	.long	0x38
	.uleb128 0x2
	.long	.LASF14
	.byte	0x5
	.byte	0x8c
	.long	0xa0
	.uleb128 0x2
	.long	.LASF15
	.byte	0x5
	.byte	0x8d
	.long	0xa0
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0xd0
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF16
	.uleb128 0x7
	.long	0xd0
	.uleb128 0x8
	.long	.LASF46
	.byte	0xd8
	.byte	0x6
	.byte	0xf5
	.long	0x25c
	.uleb128 0x9
	.long	.LASF17
	.byte	0x6
	.byte	0xf6
	.long	0x8e
	.byte	0
	.uleb128 0x9
	.long	.LASF18
	.byte	0x6
	.byte	0xfb
	.long	0xca
	.byte	0x8
	.uleb128 0x9
	.long	.LASF19
	.byte	0x6
	.byte	0xfc
	.long	0xca
	.byte	0x10
	.uleb128 0x9
	.long	.LASF20
	.byte	0x6
	.byte	0xfd
	.long	0xca
	.byte	0x18
	.uleb128 0x9
	.long	.LASF21
	.byte	0x6
	.byte	0xfe
	.long	0xca
	.byte	0x20
	.uleb128 0x9
	.long	.LASF22
	.byte	0x6
	.byte	0xff
	.long	0xca
	.byte	0x28
	.uleb128 0xa
	.long	.LASF23
	.byte	0x6
	.value	0x100
	.long	0xca
	.byte	0x30
	.uleb128 0xa
	.long	.LASF24
	.byte	0x6
	.value	0x101
	.long	0xca
	.byte	0x38
	.uleb128 0xa
	.long	.LASF25
	.byte	0x6
	.value	0x102
	.long	0xca
	.byte	0x40
	.uleb128 0xa
	.long	.LASF26
	.byte	0x6
	.value	0x104
	.long	0xca
	.byte	0x48
	.uleb128 0xa
	.long	.LASF27
	.byte	0x6
	.value	0x105
	.long	0xca
	.byte	0x50
	.uleb128 0xa
	.long	.LASF28
	.byte	0x6
	.value	0x106
	.long	0xca
	.byte	0x58
	.uleb128 0xa
	.long	.LASF29
	.byte	0x6
	.value	0x108
	.long	0x294
	.byte	0x60
	.uleb128 0xa
	.long	.LASF30
	.byte	0x6
	.value	0x10a
	.long	0x29a
	.byte	0x68
	.uleb128 0xa
	.long	.LASF31
	.byte	0x6
	.value	0x10c
	.long	0x8e
	.byte	0x70
	.uleb128 0xa
	.long	.LASF32
	.byte	0x6
	.value	0x110
	.long	0x8e
	.byte	0x74
	.uleb128 0xa
	.long	.LASF33
	.byte	0x6
	.value	0x112
	.long	0xb2
	.byte	0x78
	.uleb128 0xa
	.long	.LASF34
	.byte	0x6
	.value	0x116
	.long	0x51
	.byte	0x80
	.uleb128 0xa
	.long	.LASF35
	.byte	0x6
	.value	0x117
	.long	0x6a
	.byte	0x82
	.uleb128 0xa
	.long	.LASF36
	.byte	0x6
	.value	0x118
	.long	0x2a0
	.byte	0x83
	.uleb128 0xa
	.long	.LASF37
	.byte	0x6
	.value	0x11c
	.long	0x2b0
	.byte	0x88
	.uleb128 0xa
	.long	.LASF38
	.byte	0x6
	.value	0x125
	.long	0xbd
	.byte	0x90
	.uleb128 0xa
	.long	.LASF39
	.byte	0x6
	.value	0x12d
	.long	0xc8
	.byte	0x98
	.uleb128 0xa
	.long	.LASF40
	.byte	0x6
	.value	0x12e
	.long	0xc8
	.byte	0xa0
	.uleb128 0xa
	.long	.LASF41
	.byte	0x6
	.value	0x12f
	.long	0xc8
	.byte	0xa8
	.uleb128 0xa
	.long	.LASF42
	.byte	0x6
	.value	0x130
	.long	0xc8
	.byte	0xb0
	.uleb128 0xa
	.long	.LASF43
	.byte	0x6
	.value	0x132
	.long	0x2d
	.byte	0xb8
	.uleb128 0xa
	.long	.LASF44
	.byte	0x6
	.value	0x133
	.long	0x8e
	.byte	0xc0
	.uleb128 0xa
	.long	.LASF45
	.byte	0x6
	.value	0x135
	.long	0x2b6
	.byte	0xc4
	.byte	0
	.uleb128 0xb
	.long	.LASF158
	.byte	0x6
	.byte	0x9a
	.uleb128 0x8
	.long	.LASF47
	.byte	0x18
	.byte	0x6
	.byte	0xa0
	.long	0x294
	.uleb128 0x9
	.long	.LASF48
	.byte	0x6
	.byte	0xa1
	.long	0x294
	.byte	0
	.uleb128 0x9
	.long	.LASF49
	.byte	0x6
	.byte	0xa2
	.long	0x29a
	.byte	0x8
	.uleb128 0x9
	.long	.LASF50
	.byte	0x6
	.byte	0xa6
	.long	0x8e
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x263
	.uleb128 0x6
	.byte	0x8
	.long	0xdc
	.uleb128 0xc
	.long	0xd0
	.long	0x2b0
	.uleb128 0xd
	.long	0x38
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x25c
	.uleb128 0xc
	.long	0xd0
	.long	0x2c6
	.uleb128 0xd
	.long	0x38
	.byte	0x13
	.byte	0
	.uleb128 0xe
	.long	.LASF159
	.uleb128 0xf
	.long	.LASF51
	.byte	0x6
	.value	0x13f
	.long	0x2c6
	.uleb128 0xf
	.long	.LASF52
	.byte	0x6
	.value	0x140
	.long	0x2c6
	.uleb128 0xf
	.long	.LASF53
	.byte	0x6
	.value	0x141
	.long	0x2c6
	.uleb128 0x6
	.byte	0x8
	.long	0xd7
	.uleb128 0x7
	.long	0x2ef
	.uleb128 0x10
	.long	.LASF54
	.byte	0x7
	.byte	0x87
	.long	0x29a
	.uleb128 0x10
	.long	.LASF55
	.byte	0x7
	.byte	0x88
	.long	0x29a
	.uleb128 0x10
	.long	.LASF56
	.byte	0x7
	.byte	0x89
	.long	0x29a
	.uleb128 0x10
	.long	.LASF57
	.byte	0x8
	.byte	0x1a
	.long	0x8e
	.uleb128 0xc
	.long	0x2f5
	.long	0x331
	.uleb128 0x11
	.byte	0
	.uleb128 0x7
	.long	0x326
	.uleb128 0x10
	.long	.LASF58
	.byte	0x8
	.byte	0x1b
	.long	0x331
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF59
	.uleb128 0x2
	.long	.LASF60
	.byte	0x9
	.byte	0x21
	.long	0x3f
	.uleb128 0x2
	.long	.LASF61
	.byte	0x9
	.byte	0x23
	.long	0x58
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF62
	.uleb128 0xf
	.long	.LASF63
	.byte	0xa
	.value	0x222
	.long	0x371
	.uleb128 0x6
	.byte	0x8
	.long	0xca
	.uleb128 0x10
	.long	.LASF64
	.byte	0xb
	.byte	0x24
	.long	0xca
	.uleb128 0x10
	.long	.LASF65
	.byte	0xb
	.byte	0x32
	.long	0x8e
	.uleb128 0x10
	.long	.LASF66
	.byte	0xb
	.byte	0x37
	.long	0x8e
	.uleb128 0x10
	.long	.LASF67
	.byte	0xb
	.byte	0x3b
	.long	0x8e
	.uleb128 0xc
	.long	0xca
	.long	0x3b3
	.uleb128 0xd
	.long	0x38
	.byte	0x1
	.byte	0
	.uleb128 0x10
	.long	.LASF68
	.byte	0xc
	.byte	0x9f
	.long	0x3a3
	.uleb128 0x10
	.long	.LASF69
	.byte	0xc
	.byte	0xa0
	.long	0x8e
	.uleb128 0x10
	.long	.LASF70
	.byte	0xc
	.byte	0xa1
	.long	0xa0
	.uleb128 0x10
	.long	.LASF71
	.byte	0xc
	.byte	0xa6
	.long	0x3a3
	.uleb128 0x10
	.long	.LASF72
	.byte	0xc
	.byte	0xae
	.long	0x8e
	.uleb128 0x10
	.long	.LASF73
	.byte	0xc
	.byte	0xaf
	.long	0xa0
	.uleb128 0x8
	.long	.LASF74
	.byte	0x18
	.byte	0xd
	.byte	0x7
	.long	0x426
	.uleb128 0x9
	.long	.LASF75
	.byte	0xd
	.byte	0x9
	.long	0xc8
	.byte	0
	.uleb128 0x9
	.long	.LASF76
	.byte	0xd
	.byte	0xa
	.long	0x8e
	.byte	0x8
	.uleb128 0x9
	.long	.LASF77
	.byte	0xd
	.byte	0xb
	.long	0x426
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x3f5
	.uleb128 0x2
	.long	.LASF78
	.byte	0xd
	.byte	0xc
	.long	0x3f5
	.uleb128 0x8
	.long	.LASF79
	.byte	0x8
	.byte	0xd
	.byte	0xe
	.long	0x450
	.uleb128 0x9
	.long	.LASF80
	.byte	0xd
	.byte	0xf
	.long	0x450
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x42c
	.uleb128 0x2
	.long	.LASF81
	.byte	0xd
	.byte	0x10
	.long	0x437
	.uleb128 0x2
	.long	.LASF82
	.byte	0xe
	.byte	0x12
	.long	0x38
	.uleb128 0x12
	.byte	0x10
	.byte	0xe
	.byte	0x54
	.long	0x48d
	.uleb128 0x9
	.long	.LASF83
	.byte	0xe
	.byte	0x55
	.long	0x8e
	.byte	0
	.uleb128 0x9
	.long	.LASF84
	.byte	0xe
	.byte	0x56
	.long	0xc8
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF85
	.byte	0xe
	.byte	0x57
	.long	0x46c
	.uleb128 0x13
	.byte	0x8
	.byte	0xe
	.byte	0x5a
	.long	0x4b7
	.uleb128 0x14
	.long	.LASF86
	.byte	0xe
	.byte	0x5b
	.long	0x4b7
	.uleb128 0x14
	.long	.LASF87
	.byte	0xe
	.byte	0x5c
	.long	0x63
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x4a
	.uleb128 0x8
	.long	.LASF88
	.byte	0x30
	.byte	0xe
	.byte	0x59
	.long	0x52a
	.uleb128 0x15
	.string	"ref"
	.byte	0xe
	.byte	0x5d
	.long	0x498
	.byte	0
	.uleb128 0x9
	.long	.LASF89
	.byte	0xe
	.byte	0x5e
	.long	0x52a
	.byte	0x8
	.uleb128 0x9
	.long	.LASF90
	.byte	0xe
	.byte	0x5f
	.long	0x530
	.byte	0x10
	.uleb128 0x9
	.long	.LASF91
	.byte	0xe
	.byte	0x60
	.long	0x530
	.byte	0x18
	.uleb128 0x9
	.long	.LASF92
	.byte	0xe
	.byte	0x61
	.long	0x63
	.byte	0x20
	.uleb128 0x9
	.long	.LASF93
	.byte	0xe
	.byte	0x62
	.long	0x63
	.byte	0x24
	.uleb128 0x9
	.long	.LASF94
	.byte	0xe
	.byte	0x63
	.long	0x63
	.byte	0x28
	.uleb128 0x9
	.long	.LASF95
	.byte	0xe
	.byte	0x64
	.long	0x63
	.byte	0x2c
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x48d
	.uleb128 0x6
	.byte	0x8
	.long	0x4bd
	.uleb128 0x8
	.long	.LASF96
	.byte	0x38
	.byte	0xe
	.byte	0x69
	.long	0x5a3
	.uleb128 0x9
	.long	.LASF97
	.byte	0xe
	.byte	0x6b
	.long	0x461
	.byte	0
	.uleb128 0x9
	.long	.LASF98
	.byte	0xe
	.byte	0x6e
	.long	0x4b7
	.byte	0x8
	.uleb128 0x9
	.long	.LASF99
	.byte	0xe
	.byte	0x71
	.long	0x4b7
	.byte	0x10
	.uleb128 0x9
	.long	.LASF100
	.byte	0xe
	.byte	0x74
	.long	0x63
	.byte	0x18
	.uleb128 0x9
	.long	.LASF101
	.byte	0xe
	.byte	0x77
	.long	0x63
	.byte	0x1c
	.uleb128 0x9
	.long	.LASF102
	.byte	0xe
	.byte	0x7a
	.long	0x530
	.byte	0x20
	.uleb128 0x9
	.long	.LASF103
	.byte	0xe
	.byte	0x7d
	.long	0x5a3
	.byte	0x28
	.uleb128 0x9
	.long	.LASF104
	.byte	0xe
	.byte	0x7e
	.long	0x5a3
	.byte	0x30
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x536
	.uleb128 0x10
	.long	.LASF105
	.byte	0xe
	.byte	0x80
	.long	0x5a3
	.uleb128 0x10
	.long	.LASF106
	.byte	0xe
	.byte	0x8c
	.long	0x63
	.uleb128 0x10
	.long	.LASF107
	.byte	0xe
	.byte	0xa5
	.long	0xc8
	.uleb128 0x10
	.long	.LASF108
	.byte	0xe
	.byte	0xb2
	.long	0x456
	.uleb128 0x8
	.long	.LASF109
	.byte	0x10
	.byte	0xf
	.byte	0x17
	.long	0x5fa
	.uleb128 0x9
	.long	.LASF110
	.byte	0xf
	.byte	0x19
	.long	0xa0
	.byte	0
	.uleb128 0x9
	.long	.LASF111
	.byte	0xf
	.byte	0x1a
	.long	0xc8
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF112
	.byte	0xf
	.byte	0x1b
	.long	0x5d5
	.uleb128 0x2
	.long	.LASF113
	.byte	0x1
	.byte	0x6
	.long	0x2d
	.uleb128 0x2
	.long	.LASF114
	.byte	0x1
	.byte	0x7
	.long	0x2d
	.uleb128 0x2
	.long	.LASF115
	.byte	0x1
	.byte	0x9
	.long	0x626
	.uleb128 0x8
	.long	.LASF116
	.byte	0x38
	.byte	0x1
	.byte	0xb
	.long	0x683
	.uleb128 0x15
	.string	"key"
	.byte	0x1
	.byte	0xc
	.long	0x605
	.byte	0
	.uleb128 0x9
	.long	.LASF117
	.byte	0x1
	.byte	0xd
	.long	0x683
	.byte	0x8
	.uleb128 0x9
	.long	.LASF118
	.byte	0x1
	.byte	0xe
	.long	0x683
	.byte	0x10
	.uleb128 0x9
	.long	.LASF119
	.byte	0x1
	.byte	0xf
	.long	0x683
	.byte	0x18
	.uleb128 0x15
	.string	"k"
	.byte	0x1
	.byte	0x10
	.long	0x689
	.byte	0x20
	.uleb128 0x15
	.string	"v"
	.byte	0x1
	.byte	0x11
	.long	0x689
	.byte	0x28
	.uleb128 0x9
	.long	.LASF120
	.byte	0x1
	.byte	0x12
	.long	0x348
	.byte	0x30
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x61b
	.uleb128 0x6
	.byte	0x8
	.long	0x5fa
	.uleb128 0x2
	.long	.LASF121
	.byte	0x1
	.byte	0x16
	.long	0x69a
	.uleb128 0x8
	.long	.LASF122
	.byte	0x18
	.byte	0x1
	.byte	0x1a
	.long	0x6cb
	.uleb128 0x9
	.long	.LASF80
	.byte	0x1
	.byte	0x1b
	.long	0x683
	.byte	0
	.uleb128 0x9
	.long	.LASF123
	.byte	0x1
	.byte	0x1c
	.long	0x683
	.byte	0x8
	.uleb128 0x9
	.long	.LASF124
	.byte	0x1
	.byte	0x1d
	.long	0x6cb
	.byte	0x10
	.byte	0
	.uleb128 0x2
	.long	.LASF125
	.byte	0x1
	.byte	0x18
	.long	0x6d6
	.uleb128 0x6
	.byte	0x8
	.long	0x6dc
	.uleb128 0x16
	.long	0x6f1
	.uleb128 0x17
	.long	0x683
	.uleb128 0x17
	.long	0x683
	.uleb128 0x17
	.long	0x683
	.byte	0
	.uleb128 0x10
	.long	.LASF126
	.byte	0x2
	.byte	0x5
	.long	0x2ef
	.uleb128 0x2
	.long	.LASF127
	.byte	0x10
	.byte	0x18
	.long	0x71
	.uleb128 0x2
	.long	.LASF128
	.byte	0x10
	.byte	0x19
	.long	0x83
	.uleb128 0x2
	.long	.LASF129
	.byte	0x10
	.byte	0x1a
	.long	0x95
	.uleb128 0x2
	.long	.LASF130
	.byte	0x10
	.byte	0x1b
	.long	0xa7
	.uleb128 0x2
	.long	.LASF131
	.byte	0x2
	.byte	0xb
	.long	0xca
	.uleb128 0x7
	.long	0x728
	.uleb128 0xc
	.long	0xd0
	.long	0x747
	.uleb128 0x18
	.long	0x38
	.byte	0
	.uleb128 0x8
	.long	.LASF132
	.byte	0x3
	.byte	0x2
	.byte	0x13
	.long	0x784
	.uleb128 0x15
	.string	"len"
	.byte	0x2
	.byte	0x14
	.long	0x6fc
	.byte	0
	.uleb128 0x9
	.long	.LASF133
	.byte	0x2
	.byte	0x15
	.long	0x6fc
	.byte	0x1
	.uleb128 0x9
	.long	.LASF83
	.byte	0x2
	.byte	0x16
	.long	0x4a
	.byte	0x2
	.uleb128 0x15
	.string	"buf"
	.byte	0x2
	.byte	0x17
	.long	0x738
	.byte	0x3
	.byte	0
	.uleb128 0x8
	.long	.LASF134
	.byte	0x5
	.byte	0x2
	.byte	0x19
	.long	0x7c1
	.uleb128 0x15
	.string	"len"
	.byte	0x2
	.byte	0x1a
	.long	0x707
	.byte	0
	.uleb128 0x9
	.long	.LASF133
	.byte	0x2
	.byte	0x1b
	.long	0x707
	.byte	0x2
	.uleb128 0x9
	.long	.LASF83
	.byte	0x2
	.byte	0x1c
	.long	0x4a
	.byte	0x4
	.uleb128 0x15
	.string	"buf"
	.byte	0x2
	.byte	0x1d
	.long	0x738
	.byte	0x5
	.byte	0
	.uleb128 0x8
	.long	.LASF135
	.byte	0x9
	.byte	0x2
	.byte	0x1f
	.long	0x7fe
	.uleb128 0x15
	.string	"len"
	.byte	0x2
	.byte	0x20
	.long	0x712
	.byte	0
	.uleb128 0x9
	.long	.LASF133
	.byte	0x2
	.byte	0x21
	.long	0x712
	.byte	0x4
	.uleb128 0x9
	.long	.LASF83
	.byte	0x2
	.byte	0x22
	.long	0x4a
	.byte	0x8
	.uleb128 0x15
	.string	"buf"
	.byte	0x2
	.byte	0x23
	.long	0x738
	.byte	0x9
	.byte	0
	.uleb128 0x8
	.long	.LASF136
	.byte	0x11
	.byte	0x2
	.byte	0x25
	.long	0x83b
	.uleb128 0x15
	.string	"len"
	.byte	0x2
	.byte	0x26
	.long	0x71d
	.byte	0
	.uleb128 0x9
	.long	.LASF133
	.byte	0x2
	.byte	0x27
	.long	0x71d
	.byte	0x8
	.uleb128 0x9
	.long	.LASF83
	.byte	0x2
	.byte	0x28
	.long	0x4a
	.byte	0x10
	.uleb128 0x15
	.string	"buf"
	.byte	0x2
	.byte	0x29
	.long	0x738
	.byte	0x11
	.byte	0
	.uleb128 0x19
	.long	.LASF147
	.byte	0x3
	.value	0x1c7
	.long	0x683
	.quad	.LFB23
	.quad	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.long	0x8a9
	.uleb128 0x1a
	.long	.LASF137
	.byte	0x3
	.value	0x1c7
	.long	0x8a9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1a
	.long	.LASF138
	.byte	0x3
	.value	0x1c7
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1b
	.long	.LASF80
	.byte	0x3
	.value	0x1c9
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1b
	.long	.LASF123
	.byte	0x3
	.value	0x1c9
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1b
	.long	.LASF119
	.byte	0x3
	.value	0x1c9
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x68f
	.uleb128 0x1c
	.long	.LASF140
	.byte	0x3
	.value	0x1a9
	.quad	.LFB22
	.quad	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.long	0x90a
	.uleb128 0x1a
	.long	.LASF80
	.byte	0x3
	.value	0x1a9
	.long	0x90a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1a
	.long	.LASF123
	.byte	0x3
	.value	0x1a9
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1a
	.long	.LASF138
	.byte	0x3
	.value	0x1aa
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1b
	.long	.LASF139
	.byte	0x3
	.value	0x1ac
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x683
	.uleb128 0x1c
	.long	.LASF141
	.byte	0x3
	.value	0x18b
	.quad	.LFB21
	.quad	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.long	0x96b
	.uleb128 0x1a
	.long	.LASF80
	.byte	0x3
	.value	0x18b
	.long	0x90a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1a
	.long	.LASF123
	.byte	0x3
	.value	0x18b
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1a
	.long	.LASF138
	.byte	0x3
	.value	0x18c
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1b
	.long	.LASF139
	.byte	0x3
	.value	0x18e
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1d
	.long	.LASF143
	.byte	0x3
	.byte	0xe9
	.quad	.LFB20
	.quad	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.long	0x9f9
	.uleb128 0x1e
	.long	.LASF137
	.byte	0x3
	.byte	0xe9
	.long	0x8a9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x1e
	.long	.LASF138
	.byte	0x3
	.byte	0xe9
	.long	0x683
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x1f
	.string	"red"
	.byte	0x3
	.byte	0xeb
	.long	0x353
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x20
	.long	.LASF80
	.byte	0x3
	.byte	0xec
	.long	0x90a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x20
	.long	.LASF123
	.byte	0x3
	.byte	0xec
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x20
	.long	.LASF142
	.byte	0x3
	.byte	0xec
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x20
	.long	.LASF139
	.byte	0x3
	.byte	0xec
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1f
	.string	"w"
	.byte	0x3
	.byte	0xec
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x21
	.long	.LASF144
	.byte	0x3
	.byte	0xc6
	.quad	.LFB19
	.quad	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.long	0xa4d
	.uleb128 0x1e
	.long	.LASF139
	.byte	0x3
	.byte	0xc6
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1e
	.long	.LASF138
	.byte	0x3
	.byte	0xc6
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1e
	.long	.LASF123
	.byte	0x3
	.byte	0xc7
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1f
	.string	"p"
	.byte	0x3
	.byte	0xc9
	.long	0x90a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x21
	.long	.LASF145
	.byte	0x3
	.byte	0xad
	.quad	.LFB18
	.quad	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.long	0xaa1
	.uleb128 0x1e
	.long	.LASF139
	.byte	0x3
	.byte	0xad
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1e
	.long	.LASF138
	.byte	0x3
	.byte	0xad
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1e
	.long	.LASF123
	.byte	0x3
	.byte	0xae
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1f
	.string	"p"
	.byte	0x3
	.byte	0xb0
	.long	0x90a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1d
	.long	.LASF146
	.byte	0x3
	.byte	0x65
	.quad	.LFB17
	.quad	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0xb05
	.uleb128 0x1e
	.long	.LASF137
	.byte	0x3
	.byte	0x65
	.long	0x8a9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1e
	.long	.LASF138
	.byte	0x3
	.byte	0x65
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x20
	.long	.LASF80
	.byte	0x3
	.byte	0x67
	.long	0x90a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x20
	.long	.LASF139
	.byte	0x3
	.byte	0x67
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.long	.LASF123
	.byte	0x3
	.byte	0x67
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x22
	.long	.LASF148
	.byte	0x3
	.byte	0x46
	.long	0x689
	.quad	.LFB16
	.quad	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0xb7a
	.uleb128 0x23
	.string	"map"
	.byte	0x3
	.byte	0x46
	.long	0x689
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x23
	.string	"key"
	.byte	0x3
	.byte	0x46
	.long	0x689
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x20
	.long	.LASF149
	.byte	0x3
	.byte	0x47
	.long	0x8a9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.long	.LASF138
	.byte	0x3
	.byte	0x48
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x20
	.long	.LASF123
	.byte	0x3
	.byte	0x48
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1f
	.string	"hk"
	.byte	0x3
	.byte	0x4a
	.long	0x610
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x1d
	.long	.LASF150
	.byte	0x3
	.byte	0x33
	.quad	.LFB15
	.quad	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0xbec
	.uleb128 0x23
	.string	"map"
	.byte	0x3
	.byte	0x33
	.long	0x689
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x23
	.string	"key"
	.byte	0x3
	.byte	0x33
	.long	0x689
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1e
	.long	.LASF75
	.byte	0x3
	.byte	0x33
	.long	0x689
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x20
	.long	.LASF137
	.byte	0x3
	.byte	0x36
	.long	0x8a9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x20
	.long	.LASF138
	.byte	0x3
	.byte	0x37
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1f
	.string	"hk"
	.byte	0x3
	.byte	0x38
	.long	0x610
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x24
	.long	.LASF151
	.byte	0x3
	.byte	0x2d
	.long	0x8a9
	.quad	.LFB14
	.quad	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0xc2a
	.uleb128 0x20
	.long	.LASF137
	.byte	0x3
	.byte	0x2e
	.long	0x8a9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x20
	.long	.LASF123
	.byte	0x3
	.byte	0x2f
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x25
	.long	.LASF152
	.byte	0x3
	.byte	0x24
	.long	0x353
	.quad	.LFB13
	.quad	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0xc82
	.uleb128 0x1e
	.long	.LASF111
	.byte	0x3
	.byte	0x24
	.long	0xc82
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x23
	.string	"len"
	.byte	0x3
	.byte	0x24
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1f
	.string	"i"
	.byte	0x3
	.byte	0x25
	.long	0x353
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x1f
	.string	"key"
	.byte	0x3
	.byte	0x25
	.long	0x353
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x348
	.uleb128 0x21
	.long	.LASF153
	.byte	0x3
	.byte	0x9
	.quad	.LFB12
	.quad	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.long	0xcdc
	.uleb128 0x1e
	.long	.LASF139
	.byte	0x3
	.byte	0x9
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1e
	.long	.LASF138
	.byte	0x3
	.byte	0x9
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1e
	.long	.LASF123
	.byte	0x3
	.byte	0x9
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1f
	.string	"p"
	.byte	0x3
	.byte	0xb
	.long	0x90a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x26
	.long	.LASF160
	.byte	0x2
	.byte	0x37
	.long	0x2d
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0xd18
	.uleb128 0x23
	.string	"s"
	.byte	0x2
	.byte	0x37
	.long	0x733
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.long	.LASF83
	.byte	0x2
	.byte	0x38
	.long	0x4a
	.uleb128 0x2
	.byte	0x91
	.sleb128 -17
	.byte	0
	.uleb128 0x27
	.long	.LASF154
	.byte	0x1
	.byte	0x44
	.long	0x683
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x1e
	.long	.LASF138
	.byte	0x1
	.byte	0x44
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1e
	.long	.LASF123
	.byte	0x1
	.byte	0x44
	.long	0x683
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
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
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x21
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
	.uleb128 0x5
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
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1b
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.uleb128 0x21
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
	.uleb128 0x22
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
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
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
.LASF14:
	.string	"__off_t"
.LASF30:
	.string	"_chain"
.LASF145:
	.string	"rbtree_insert_value"
.LASF0:
	.string	"size_t"
.LASF36:
	.string	"_shortbuf"
.LASF131:
	.string	"string"
.LASF8:
	.string	"__uint8_t"
.LASF110:
	.string	"type"
.LASF93:
	.string	"szidx"
.LASF53:
	.string	"_IO_2_1_stderr_"
.LASF24:
	.string	"_IO_buf_base"
.LASF62:
	.string	"long long unsigned int"
.LASF114:
	.string	"rbtree_key_int_t"
.LASF121:
	.string	"rbtree_t"
.LASF147:
	.string	"rbtree_next"
.LASF111:
	.string	"data"
.LASF96:
	.string	"arena_object"
.LASF77:
	.string	"next"
.LASF134:
	.string	"stringhdr16"
.LASF66:
	.string	"opterr"
.LASF70:
	.string	"__timezone"
.LASF59:
	.string	"long long int"
.LASF7:
	.string	"signed char"
.LASF156:
	.string	"/home/xiaodo/c++/colang/src/internal/Map.c"
.LASF148:
	.string	"map_find"
.LASF106:
	.string	"maxarenas"
.LASF78:
	.string	"ListNode"
.LASF31:
	.string	"_fileno"
.LASF19:
	.string	"_IO_read_end"
.LASF119:
	.string	"parent"
.LASF100:
	.string	"nfreepools"
.LASF139:
	.string	"temp"
.LASF12:
	.string	"long int"
.LASF102:
	.string	"freepools"
.LASF17:
	.string	"_flags"
.LASF136:
	.string	"stringhdr64"
.LASF25:
	.string	"_IO_buf_end"
.LASF155:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -fno-builtin"
.LASF126:
	.string	"LSTRING_NOINIT"
.LASF33:
	.string	"_old_offset"
.LASF38:
	.string	"_offset"
.LASF95:
	.string	"maxnextoffset"
.LASF87:
	.string	"count"
.LASF11:
	.string	"__uint32_t"
.LASF73:
	.string	"timezone"
.LASF116:
	.string	"rbtree_node_s"
.LASF115:
	.string	"rbtree_node_t"
.LASF75:
	.string	"value"
.LASF47:
	.string	"_IO_marker"
.LASF124:
	.string	"insert"
.LASF85:
	.string	"block"
.LASF6:
	.string	"unsigned int"
.LASF128:
	.string	"uint16_t"
.LASF99:
	.string	"pool_address"
.LASF2:
	.string	"long unsigned int"
.LASF159:
	.string	"_IO_FILE_plus"
.LASF22:
	.string	"_IO_write_ptr"
.LASF72:
	.string	"daylight"
.LASF57:
	.string	"sys_nerr"
.LASF49:
	.string	"_sbuf"
.LASF108:
	.string	"Hugmem"
.LASF76:
	.string	"size"
.LASF4:
	.string	"short unsigned int"
.LASF74:
	.string	"link_list"
.LASF26:
	.string	"_IO_save_base"
.LASF157:
	.string	"/home/xiaodo/c++/colang/tests/src/internal"
.LASF54:
	.string	"stdin"
.LASF103:
	.string	"nextarena"
.LASF138:
	.string	"node"
.LASF37:
	.string	"_lock"
.LASF32:
	.string	"_flags2"
.LASF118:
	.string	"right"
.LASF55:
	.string	"stdout"
.LASF109:
	.string	"core_value"
.LASF150:
	.string	"map_insert"
.LASF51:
	.string	"_IO_2_1_stdin_"
.LASF81:
	.string	"List"
.LASF91:
	.string	"prevpool"
.LASF92:
	.string	"arenaindex"
.LASF64:
	.string	"optarg"
.LASF1:
	.string	"__u_char"
.LASF97:
	.string	"address"
.LASF65:
	.string	"optind"
.LASF132:
	.string	"stringhdr8"
.LASF122:
	.string	"rbtree_s"
.LASF89:
	.string	"freeblock"
.LASF18:
	.string	"_IO_read_ptr"
.LASF60:
	.string	"u_char"
.LASF130:
	.string	"uint64_t"
.LASF61:
	.string	"u_int"
.LASF104:
	.string	"prevarena"
.LASF160:
	.string	"stringlen"
.LASF158:
	.string	"_IO_lock_t"
.LASF46:
	.string	"_IO_FILE"
.LASF149:
	.string	"rbtree"
.LASF63:
	.string	"__environ"
.LASF82:
	.string	"Co_uintptr_t"
.LASF13:
	.string	"__uint64_t"
.LASF44:
	.string	"_mode"
.LASF50:
	.string	"_pos"
.LASF58:
	.string	"sys_errlist"
.LASF29:
	.string	"_markers"
.LASF105:
	.string	"arenas"
.LASF84:
	.string	"addr"
.LASF140:
	.string	"rbtree_right_rotate"
.LASF3:
	.string	"unsigned char"
.LASF146:
	.string	"rbtree_insert"
.LASF125:
	.string	"rbtree_insert_pt"
.LASF9:
	.string	"short int"
.LASF98:
	.string	"first_address"
.LASF35:
	.string	"_vtable_offset"
.LASF71:
	.string	"tzname"
.LASF52:
	.string	"_IO_2_1_stdout_"
.LASF101:
	.string	"ntotalpools"
.LASF69:
	.string	"__daylight"
.LASF67:
	.string	"optopt"
.LASF152:
	.string	"hash_key"
.LASF94:
	.string	"nextoffset"
.LASF143:
	.string	"rbtree_delete"
.LASF120:
	.string	"color"
.LASF16:
	.string	"char"
.LASF10:
	.string	"__uint16_t"
.LASF153:
	.string	"map_insert_or_update"
.LASF142:
	.string	"subst"
.LASF154:
	.string	"rbtree_min"
.LASF133:
	.string	"alloc"
.LASF48:
	.string	"_next"
.LASF15:
	.string	"__off64_t"
.LASF34:
	.string	"_cur_column"
.LASF20:
	.string	"_IO_read_base"
.LASF28:
	.string	"_IO_save_end"
.LASF144:
	.string	"rbtree_insert_timer_value"
.LASF107:
	.string	"sp_start"
.LASF39:
	.string	"__pad1"
.LASF40:
	.string	"__pad2"
.LASF41:
	.string	"__pad3"
.LASF42:
	.string	"__pad4"
.LASF43:
	.string	"__pad5"
.LASF86:
	.string	"_padding"
.LASF23:
	.string	"_IO_write_end"
.LASF45:
	.string	"_unused2"
.LASF56:
	.string	"stderr"
.LASF88:
	.string	"pool_header"
.LASF113:
	.string	"rbtree_key_t"
.LASF137:
	.string	"tree"
.LASF112:
	.string	"Value"
.LASF135:
	.string	"stringhdr32"
.LASF127:
	.string	"uint8_t"
.LASF27:
	.string	"_IO_backup_base"
.LASF83:
	.string	"flags"
.LASF141:
	.string	"rbtree_left_rotate"
.LASF151:
	.string	"map_create"
.LASF79:
	.string	"list"
.LASF123:
	.string	"sentinel"
.LASF68:
	.string	"__tzname"
.LASF90:
	.string	"nextpool"
.LASF21:
	.string	"_IO_write_base"
.LASF117:
	.string	"left"
.LASF5:
	.string	"__u_int"
.LASF129:
	.string	"uint32_t"
.LASF80:
	.string	"root"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

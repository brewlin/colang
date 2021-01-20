	.file	"malloc.c"
	.text
.Ltext0:
	.globl	list_head
	.data
	#.bss
	.align 8
	.type	list_head, @object
	.size	list_head, 8
list_head:
	.zero	8
	.text
	.globl	free
	.type	free, @function
free:
.LFB0:
	.file 1 "/home/xiaodo/c++/colang/src/crt/malloc.c"
	.loc 1 21 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	.loc 1 22 0
	movq	-24(%rbp), %rax
	subq	$32, %rax
	movq	%rax, -8(%rbp)
	.loc 1 23 0
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$-842150451, %eax
	jne	.L6
	.loc 1 28 0
	movq	-8(%rbp), %rax
	movl	$-1414812757, (%rax)
	.loc 1 29 0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	testq	%rax, %rax
	je	.L4
	.loc 1 29 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movl	(%rax), %eax
	cmpl	$-1414812757, %eax
	jne	.L4
	.loc 1 32 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	16(%rdx), %rdx
	movq	%rdx, 16(%rax)
	.loc 1 33 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	je	.L5
	.loc 1 34 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	24(%rdx), %rdx
	movq	%rdx, 24(%rax)
.L5:
	.loc 1 35 0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rcx
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	addq	%rcx, %rdx
	movq	%rdx, 8(%rax)
	.loc 1 37 0
	movq	-8(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -8(%rbp)
.L4:
	.loc 1 40 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	je	.L1
	.loc 1 40 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movl	(%rax), %eax
	cmpl	$-1414812757, %eax
	jne	.L1
	.loc 1 43 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	8(%rax), %rax
	addq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 1 44 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	jmp	.L1
.L6:
	.loc 1 25 0
	nop
.L1:
	.loc 1 46 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	free, .-free
	.globl	realloc
	.type	realloc, @function
realloc:
.LFB1:
	.loc 1 48 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 1 49 0
	cmpq	$0, -24(%rbp)
	jne	.L8
	.loc 1 54 0
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	malloc
	jmp	.L9
.L8:
	.loc 1 60 0
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -8(%rbp)
	.loc 1 61 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	.loc 1 62 0
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free
	.loc 1 63 0
	movq	-8(%rbp), %rax
.L9:
	.loc 1 64 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	realloc, .-realloc
	.globl	malloc
	.type	malloc, @function
malloc:
.LFB2:
	.loc 1 66 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	.loc 1 68 0
	cmpq	$0, -24(%rbp)
	jne	.L11
	.loc 1 70 0
	movl	$0, %eax
	jmp	.L12
.L11:
	.loc 1 73 0
	movq	list_head(%rip), %rax
	movq	%rax, -8(%rbp)
	.loc 1 74 0
	jmp	.L13
.L17:
	.loc 1 76 0
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$-842150451, %eax
	jne	.L14
	.loc 1 78 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 1 79 0
	jmp	.L13
.L14:
	.loc 1 82 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rdx
	addq	$32, %rdx
	cmpq	%rdx, %rax
	jbe	.L15
	.loc 1 83 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rdx
	addq	$64, %rdx
	cmpq	%rdx, %rax
	ja	.L15
	.loc 1 85 0
	movq	-8(%rbp), %rax
	movl	$-842150451, (%rax)
.L15:
	.loc 1 88 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	-24(%rbp), %rdx
	addq	$64, %rdx
	cmpq	%rdx, %rax
	jbe	.L16
.LBB2:
	.loc 1 91 0
	movq	-24(%rbp), %rax
	leaq	32(%rax), %rdx
	movq	-8(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
	.loc 1 92 0
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 24(%rax)
	.loc 1 93 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 16(%rax)
	.loc 1 94 0
	movq	-16(%rbp), %rax
	movl	$-1414812757, (%rax)
	.loc 1 95 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	subq	-24(%rbp), %rax
	leaq	32(%rax), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 1 96 0
	movq	-8(%rbp), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, 16(%rax)
	.loc 1 97 0
	movq	-24(%rbp), %rax
	leaq	32(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 1 98 0
	movq	-8(%rbp), %rax
	movl	$-842150451, (%rax)
	.loc 1 99 0
	movq	-8(%rbp), %rax
	addq	$32, %rax
	jmp	.L12
.L16:
.LBE2:
	.loc 1 101 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -8(%rbp)
.L13:
	.loc 1 74 0
	cmpq	$0, -8(%rbp)
	jne	.L17
	.loc 1 104 0
	movl	$0, %eax
.L12:
	.loc 1 105 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	malloc, .-malloc
	.type	brk, @function
brk:
.LFB3:
	.loc 1 110 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	.loc 1 111 0
	movq	$0, -8(%rbp)
	.loc 1 115 0
#APP
# 115 "/home/xiaodo/c++/colang/src/colib/malloc.c" 1
	movq $45, %rax   
	movq -24(%rbp), %rbx  
	int $0x80		
	movq %rax,%rax  
	
# 0 "" 2
#NO_APP
	movq	%rax, -8(%rbp)
	.loc 1 120 0
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	brk, .-brk
	.globl	mini_crt_init_heap
	.type	mini_crt_init_heap, @function
mini_crt_init_heap:
.LFB4:
	.loc 1 128 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	.loc 1 129 0
	movq	$0, -8(%rbp)
	.loc 1 130 0
	movq	$0, -16(%rbp)
	.loc 1 132 0
	movq	$33554432, -24(%rbp)
	.loc 1 142 0
	movl	$0, %edi
	call	brk
	movq	%rax, -8(%rbp)
	.loc 1 143 0
	movq	-8(%rbp), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -32(%rbp)
	.loc 1 144 0
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	brk
	movq	%rax, -32(%rbp)
	.loc 1 145 0
	cmpq	$0, -32(%rbp)
	jne	.L20
	.loc 1 147 0
	movl	$0, %eax
	jmp	.L21
.L20:
	.loc 1 151 0
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	.loc 1 153 0
	movq	-16(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 1 154 0
	movq	-16(%rbp), %rax
	movl	$-1414812757, (%rax)
	.loc 1 155 0
	movq	-16(%rbp), %rax
	movq	$0, 16(%rax)
	.loc 1 156 0
	movq	-16(%rbp), %rax
	movq	$0, 24(%rax)
	.loc 1 158 0
	movq	-16(%rbp), %rax
	movq	%rax, list_head(%rip)
	.loc 1 159 0
	movl	$1, %eax
.L21:
	.loc 1 160 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	mini_crt_init_heap, .-mini_crt_init_heap
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x247
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF17
	.byte	0xc
	.long	.LASF18
	.long	.LASF19
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.byte	0x7
	.byte	0x4
	.long	0x5b
	.byte	0x1
	.byte	0x6
	.long	0x5b
	.uleb128 0x4
	.long	.LASF2
	.long	0xabababab
	.uleb128 0x4
	.long	.LASF3
	.long	0xcdcdcdcd
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF4
	.uleb128 0x5
	.long	.LASF20
	.byte	0x20
	.byte	0x1
	.byte	0x4
	.long	0x9f
	.uleb128 0x6
	.long	.LASF5
	.byte	0x1
	.byte	0x9
	.long	0x3b
	.byte	0
	.uleb128 0x6
	.long	.LASF6
	.byte	0x1
	.byte	0xa
	.long	0x9f
	.byte	0x8
	.uleb128 0x6
	.long	.LASF7
	.byte	0x1
	.byte	0xb
	.long	0xa6
	.byte	0x10
	.uleb128 0x6
	.long	.LASF8
	.byte	0x1
	.byte	0xc
	.long	0xa6
	.byte	0x18
	.byte	0
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF9
	.uleb128 0x7
	.byte	0x8
	.long	0x62
	.uleb128 0x8
	.long	.LASF21
	.byte	0x1
	.byte	0xd
	.long	0x62
	.uleb128 0x9
	.long	.LASF22
	.byte	0x1
	.byte	0x12
	.long	0xcc
	.uleb128 0x9
	.byte	0x3
	.quad	list_head
	.uleb128 0x7
	.byte	0x8
	.long	0xac
	.uleb128 0xa
	.long	.LASF23
	.byte	0x1
	.byte	0x7f
	.long	0x2d
	.quad	.LFB4
	.quad	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.long	0x12c
	.uleb128 0xb
	.long	.LASF10
	.byte	0x1
	.byte	0x81
	.long	0x12c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xb
	.long	.LASF11
	.byte	0x1
	.byte	0x82
	.long	0xcc
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xb
	.long	.LASF12
	.byte	0x1
	.byte	0x84
	.long	0x9f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xc
	.string	"end"
	.byte	0x1
	.byte	0x8f
	.long	0x12c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0xd
	.byte	0x8
	.uleb128 0xe
	.string	"brk"
	.byte	0x1
	.byte	0x6d
	.long	0x2d
	.quad	.LFB3
	.quad	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x16c
	.uleb128 0xf
	.long	.LASF13
	.byte	0x1
	.byte	0x6d
	.long	0x12c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xc
	.string	"ret"
	.byte	0x1
	.byte	0x6f
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x10
	.long	.LASF14
	.byte	0x1
	.byte	0x41
	.long	0x12c
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x1ca
	.uleb128 0xf
	.long	.LASF6
	.byte	0x1
	.byte	0x41
	.long	0x9f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xb
	.long	.LASF11
	.byte	0x1
	.byte	0x43
	.long	0xcc
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x11
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.uleb128 0xb
	.long	.LASF7
	.byte	0x1
	.byte	0x5b
	.long	0xcc
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.byte	0
	.uleb128 0x12
	.long	.LASF15
	.byte	0x1
	.byte	0x30
	.long	0x12c
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x214
	.uleb128 0x13
	.string	"p"
	.byte	0x1
	.byte	0x30
	.long	0x12c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xf
	.long	.LASF16
	.byte	0x1
	.byte	0x30
	.long	0x9f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xc
	.string	"new"
	.byte	0x1
	.byte	0x3c
	.long	0x12c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x14
	.long	.LASF24
	.byte	0x1
	.byte	0x14
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x13
	.string	"ptr"
	.byte	0x1
	.byte	0x14
	.long	0x12c
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xb
	.long	.LASF11
	.byte	0x1
	.byte	0x16
	.long	0xcc
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
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
	.uleb128 0x3
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x9
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 0xd
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0xf
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
	.uleb128 0x10
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
	.uleb128 0x11
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
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
.LASF16:
	.string	"nbytes"
.LASF4:
	.string	"unsigned int"
.LASF21:
	.string	"heap_header"
.LASF11:
	.string	"header"
.LASF2:
	.string	"HEAP_BLOCK_FREE"
.LASF24:
	.string	"free"
.LASF13:
	.string	"end_data_segment"
.LASF9:
	.string	"long unsigned int"
.LASF22:
	.string	"list_head"
.LASF12:
	.string	"heap_size"
.LASF10:
	.string	"base"
.LASF5:
	.string	"type"
.LASF1:
	.string	"unsigned char"
.LASF6:
	.string	"size"
.LASF15:
	.string	"realloc"
.LASF0:
	.string	"long int"
.LASF19:
	.string	"/home/xiaodo/c++/colang/tests/src/crt"
.LASF20:
	.string	"_heap_header"
.LASF3:
	.string	"HEAP_BLOCK_USED"
.LASF17:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -g -fno-builtin"
.LASF8:
	.string	"prev"
.LASF18:
	.string	"/home/xiaodo/c++/colang/src/crt/malloc.c"
.LASF23:
	.string	"mini_crt_init_heap"
.LASF14:
	.string	"malloc"
.LASF7:
	.string	"next"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

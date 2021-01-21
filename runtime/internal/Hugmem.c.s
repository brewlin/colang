	.file	"Hugmem.c"
	.text
.Ltext0:
	.globl	push
	.type	push, @function
push:
.LFB5:
	.file 1 "/home/xiaodo/c++/colang/src/gc/Hugmem.c"
	.loc 1 6 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, -36(%rbp)
	.loc 1 7 0
	movl	$24, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 1 8 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, (%rax)
	.loc 1 9 0
	movq	-8(%rbp), %rax
	movl	-36(%rbp), %edx
	movl	%edx, 8(%rax)
	.loc 1 10 0
	movq	-8(%rbp), %rax
	movq	$0, 16(%rax)
	.loc 1 11 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L2
	.loc 1 12 0
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	.loc 1 13 0
	jmp	.L1
.L2:
	.loc 1 15 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	.loc 1 16 0
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
.L1:
	.loc 1 17 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	push, .-push
	.globl	mark
	.type	mark, @function
mark:
.LFB6:
	.loc 1 18 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	.loc 1 19 0
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 1 20 0
	jmp	.L5
.L10:
	.loc 1 21 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -48(%rbp)
	jne	.L6
.LBB2:
	.loc 1 22 0
	movq	-48(%rbp), %rax
	subq	$8, %rax
	movq	%rax, -24(%rbp)
	.loc 1 23 0
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	orl	$2, %eax
	movl	%eax, %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
.LBB3:
	.loc 1 24 0
	movq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
	jmp	.L7
.L8:
	.loc 1 25 0 discriminator 3
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	gc_mark@PLT
	.loc 1 24 0 discriminator 3
	addq	$1, -16(%rbp)
.L7:
	.loc 1 24 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	cltq
	leaq	-8(%rax), %rdx
	movq	-48(%rbp), %rax
	addq	%rdx, %rax
	cmpq	%rax, -16(%rbp)
	jb	.L8
.LBE3:
	.loc 1 28 0 is_stmt 1
	jmp	.L4
.L6:
.LBE2:
	.loc 1 30 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -8(%rbp)
.L5:
	.loc 1 20 0
	cmpq	$0, -8(%rbp)
	jne	.L10
.L4:
	.loc 1 32 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	mark, .-mark
	.globl	del
	.type	del, @function
del:
.LFB7:
	.loc 1 34 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 1 35 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L19
	.loc 1 35 0 is_stmt 0 discriminator 1
	cmpq	$0, -32(%rbp)
	je	.L19
	.loc 1 37 0 is_stmt 1
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	.loc 1 38 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	%rax, -32(%rbp)
	jne	.L16
	.loc 1 39 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, (%rax)
	.loc 1 40 0
	jmp	.L11
.L18:
	.loc 1 43 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	(%rax), %rax
	cmpq	%rax, -32(%rbp)
	jne	.L17
	.loc 1 44 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	16(%rax), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 16(%rax)
	.loc 1 45 0
	jmp	.L11
.L17:
	.loc 1 47 0
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	movq	%rax, -8(%rbp)
.L16:
	.loc 1 42 0
	cmpq	$0, -8(%rbp)
	je	.L11
	.loc 1 42 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	16(%rax), %rax
	testq	%rax, %rax
	jne	.L18
	jmp	.L11
.L19:
	.loc 1 35 0 is_stmt 1
	nop
.L11:
	.loc 1 50 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	del, .-del
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h"
	.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 4 "/usr/include/x86_64-linux-gnu/bits/libio.h"
	.file 5 "/usr/include/stdio.h"
	.file 6 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
	.file 7 "/home/xiaodo/c++/colang/src/gc/Hugmem.h"
	.file 8 "/usr/include/unistd.h"
	.file 9 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h"
	.file 10 "/usr/include/time.h"
	.file 11 "/home/xiaodo/c++/colang/src/gc/gc.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x69a
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF103
	.byte	0xc
	.long	.LASF104
	.long	.LASF105
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF7
	.byte	0x2
	.byte	0xd8
	.long	0x38
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.long	.LASF8
	.byte	0x3
	.byte	0x8c
	.long	0x69
	.uleb128 0x2
	.long	.LASF9
	.byte	0x3
	.byte	0x8d
	.long	0x69
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0x8e
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF10
	.uleb128 0x7
	.long	0x8e
	.uleb128 0x8
	.long	.LASF40
	.byte	0xd8
	.byte	0x4
	.byte	0xf5
	.long	0x21a
	.uleb128 0x9
	.long	.LASF11
	.byte	0x4
	.byte	0xf6
	.long	0x62
	.byte	0
	.uleb128 0x9
	.long	.LASF12
	.byte	0x4
	.byte	0xfb
	.long	0x88
	.byte	0x8
	.uleb128 0x9
	.long	.LASF13
	.byte	0x4
	.byte	0xfc
	.long	0x88
	.byte	0x10
	.uleb128 0x9
	.long	.LASF14
	.byte	0x4
	.byte	0xfd
	.long	0x88
	.byte	0x18
	.uleb128 0x9
	.long	.LASF15
	.byte	0x4
	.byte	0xfe
	.long	0x88
	.byte	0x20
	.uleb128 0x9
	.long	.LASF16
	.byte	0x4
	.byte	0xff
	.long	0x88
	.byte	0x28
	.uleb128 0xa
	.long	.LASF17
	.byte	0x4
	.value	0x100
	.long	0x88
	.byte	0x30
	.uleb128 0xa
	.long	.LASF18
	.byte	0x4
	.value	0x101
	.long	0x88
	.byte	0x38
	.uleb128 0xa
	.long	.LASF19
	.byte	0x4
	.value	0x102
	.long	0x88
	.byte	0x40
	.uleb128 0xa
	.long	.LASF20
	.byte	0x4
	.value	0x104
	.long	0x88
	.byte	0x48
	.uleb128 0xa
	.long	.LASF21
	.byte	0x4
	.value	0x105
	.long	0x88
	.byte	0x50
	.uleb128 0xa
	.long	.LASF22
	.byte	0x4
	.value	0x106
	.long	0x88
	.byte	0x58
	.uleb128 0xa
	.long	.LASF23
	.byte	0x4
	.value	0x108
	.long	0x252
	.byte	0x60
	.uleb128 0xa
	.long	.LASF24
	.byte	0x4
	.value	0x10a
	.long	0x258
	.byte	0x68
	.uleb128 0xa
	.long	.LASF25
	.byte	0x4
	.value	0x10c
	.long	0x62
	.byte	0x70
	.uleb128 0xa
	.long	.LASF26
	.byte	0x4
	.value	0x110
	.long	0x62
	.byte	0x74
	.uleb128 0xa
	.long	.LASF27
	.byte	0x4
	.value	0x112
	.long	0x70
	.byte	0x78
	.uleb128 0xa
	.long	.LASF28
	.byte	0x4
	.value	0x116
	.long	0x46
	.byte	0x80
	.uleb128 0xa
	.long	.LASF29
	.byte	0x4
	.value	0x117
	.long	0x54
	.byte	0x82
	.uleb128 0xa
	.long	.LASF30
	.byte	0x4
	.value	0x118
	.long	0x25e
	.byte	0x83
	.uleb128 0xa
	.long	.LASF31
	.byte	0x4
	.value	0x11c
	.long	0x26e
	.byte	0x88
	.uleb128 0xa
	.long	.LASF32
	.byte	0x4
	.value	0x125
	.long	0x7b
	.byte	0x90
	.uleb128 0xa
	.long	.LASF33
	.byte	0x4
	.value	0x12d
	.long	0x86
	.byte	0x98
	.uleb128 0xa
	.long	.LASF34
	.byte	0x4
	.value	0x12e
	.long	0x86
	.byte	0xa0
	.uleb128 0xa
	.long	.LASF35
	.byte	0x4
	.value	0x12f
	.long	0x86
	.byte	0xa8
	.uleb128 0xa
	.long	.LASF36
	.byte	0x4
	.value	0x130
	.long	0x86
	.byte	0xb0
	.uleb128 0xa
	.long	.LASF37
	.byte	0x4
	.value	0x132
	.long	0x2d
	.byte	0xb8
	.uleb128 0xa
	.long	.LASF38
	.byte	0x4
	.value	0x133
	.long	0x62
	.byte	0xc0
	.uleb128 0xa
	.long	.LASF39
	.byte	0x4
	.value	0x135
	.long	0x274
	.byte	0xc4
	.byte	0
	.uleb128 0xb
	.long	.LASF106
	.byte	0x4
	.byte	0x9a
	.uleb128 0x8
	.long	.LASF41
	.byte	0x18
	.byte	0x4
	.byte	0xa0
	.long	0x252
	.uleb128 0x9
	.long	.LASF42
	.byte	0x4
	.byte	0xa1
	.long	0x252
	.byte	0
	.uleb128 0x9
	.long	.LASF43
	.byte	0x4
	.byte	0xa2
	.long	0x258
	.byte	0x8
	.uleb128 0x9
	.long	.LASF44
	.byte	0x4
	.byte	0xa6
	.long	0x62
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x221
	.uleb128 0x6
	.byte	0x8
	.long	0x9a
	.uleb128 0xc
	.long	0x8e
	.long	0x26e
	.uleb128 0xd
	.long	0x38
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x21a
	.uleb128 0xc
	.long	0x8e
	.long	0x284
	.uleb128 0xd
	.long	0x38
	.byte	0x13
	.byte	0
	.uleb128 0xe
	.long	.LASF107
	.uleb128 0xf
	.long	.LASF45
	.byte	0x4
	.value	0x13f
	.long	0x284
	.uleb128 0xf
	.long	.LASF46
	.byte	0x4
	.value	0x140
	.long	0x284
	.uleb128 0xf
	.long	.LASF47
	.byte	0x4
	.value	0x141
	.long	0x284
	.uleb128 0x6
	.byte	0x8
	.long	0x95
	.uleb128 0x7
	.long	0x2ad
	.uleb128 0x10
	.long	.LASF48
	.byte	0x5
	.byte	0x87
	.long	0x258
	.uleb128 0x10
	.long	.LASF49
	.byte	0x5
	.byte	0x88
	.long	0x258
	.uleb128 0x10
	.long	.LASF50
	.byte	0x5
	.byte	0x89
	.long	0x258
	.uleb128 0x10
	.long	.LASF51
	.byte	0x6
	.byte	0x1a
	.long	0x62
	.uleb128 0xc
	.long	0x2b3
	.long	0x2ef
	.uleb128 0x11
	.byte	0
	.uleb128 0x7
	.long	0x2e4
	.uleb128 0x10
	.long	.LASF52
	.byte	0x6
	.byte	0x1b
	.long	0x2ef
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF53
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF54
	.uleb128 0x8
	.long	.LASF55
	.byte	0x18
	.byte	0x7
	.byte	0x7
	.long	0x33e
	.uleb128 0x9
	.long	.LASF56
	.byte	0x7
	.byte	0x9
	.long	0x86
	.byte	0
	.uleb128 0x9
	.long	.LASF57
	.byte	0x7
	.byte	0xa
	.long	0x62
	.byte	0x8
	.uleb128 0x9
	.long	.LASF58
	.byte	0x7
	.byte	0xb
	.long	0x33e
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x30d
	.uleb128 0x2
	.long	.LASF59
	.byte	0x7
	.byte	0xc
	.long	0x30d
	.uleb128 0x8
	.long	.LASF60
	.byte	0x8
	.byte	0x7
	.byte	0xe
	.long	0x368
	.uleb128 0x9
	.long	.LASF61
	.byte	0x7
	.byte	0xf
	.long	0x368
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x344
	.uleb128 0x2
	.long	.LASF62
	.byte	0x7
	.byte	0x10
	.long	0x34f
	.uleb128 0xf
	.long	.LASF63
	.byte	0x8
	.value	0x222
	.long	0x385
	.uleb128 0x6
	.byte	0x8
	.long	0x88
	.uleb128 0x10
	.long	.LASF64
	.byte	0x9
	.byte	0x24
	.long	0x88
	.uleb128 0x10
	.long	.LASF65
	.byte	0x9
	.byte	0x32
	.long	0x62
	.uleb128 0x10
	.long	.LASF66
	.byte	0x9
	.byte	0x37
	.long	0x62
	.uleb128 0x10
	.long	.LASF67
	.byte	0x9
	.byte	0x3b
	.long	0x62
	.uleb128 0xc
	.long	0x88
	.long	0x3c7
	.uleb128 0xd
	.long	0x38
	.byte	0x1
	.byte	0
	.uleb128 0x10
	.long	.LASF68
	.byte	0xa
	.byte	0x9f
	.long	0x3b7
	.uleb128 0x10
	.long	.LASF69
	.byte	0xa
	.byte	0xa0
	.long	0x62
	.uleb128 0x10
	.long	.LASF70
	.byte	0xa
	.byte	0xa1
	.long	0x69
	.uleb128 0x10
	.long	.LASF71
	.byte	0xa
	.byte	0xa6
	.long	0x3b7
	.uleb128 0x10
	.long	.LASF72
	.byte	0xa
	.byte	0xae
	.long	0x62
	.uleb128 0x10
	.long	.LASF73
	.byte	0xa
	.byte	0xaf
	.long	0x69
	.uleb128 0x2
	.long	.LASF74
	.byte	0xb
	.byte	0x12
	.long	0x38
	.uleb128 0x12
	.byte	0x10
	.byte	0xb
	.byte	0x54
	.long	0x435
	.uleb128 0x9
	.long	.LASF75
	.byte	0xb
	.byte	0x55
	.long	0x62
	.byte	0
	.uleb128 0x9
	.long	.LASF76
	.byte	0xb
	.byte	0x56
	.long	0x86
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF77
	.byte	0xb
	.byte	0x57
	.long	0x414
	.uleb128 0x13
	.byte	0x8
	.byte	0xb
	.byte	0x5a
	.long	0x45f
	.uleb128 0x14
	.long	.LASF78
	.byte	0xb
	.byte	0x5b
	.long	0x45f
	.uleb128 0x14
	.long	.LASF79
	.byte	0xb
	.byte	0x5c
	.long	0x4d
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x3f
	.uleb128 0x8
	.long	.LASF80
	.byte	0x30
	.byte	0xb
	.byte	0x59
	.long	0x4d2
	.uleb128 0x15
	.string	"ref"
	.byte	0xb
	.byte	0x5d
	.long	0x440
	.byte	0
	.uleb128 0x9
	.long	.LASF81
	.byte	0xb
	.byte	0x5e
	.long	0x4d2
	.byte	0x8
	.uleb128 0x9
	.long	.LASF82
	.byte	0xb
	.byte	0x5f
	.long	0x4d8
	.byte	0x10
	.uleb128 0x9
	.long	.LASF83
	.byte	0xb
	.byte	0x60
	.long	0x4d8
	.byte	0x18
	.uleb128 0x9
	.long	.LASF84
	.byte	0xb
	.byte	0x61
	.long	0x4d
	.byte	0x20
	.uleb128 0x9
	.long	.LASF85
	.byte	0xb
	.byte	0x62
	.long	0x4d
	.byte	0x24
	.uleb128 0x9
	.long	.LASF86
	.byte	0xb
	.byte	0x63
	.long	0x4d
	.byte	0x28
	.uleb128 0x9
	.long	.LASF87
	.byte	0xb
	.byte	0x64
	.long	0x4d
	.byte	0x2c
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x435
	.uleb128 0x6
	.byte	0x8
	.long	0x465
	.uleb128 0x8
	.long	.LASF88
	.byte	0x38
	.byte	0xb
	.byte	0x69
	.long	0x54b
	.uleb128 0x9
	.long	.LASF89
	.byte	0xb
	.byte	0x6b
	.long	0x409
	.byte	0
	.uleb128 0x9
	.long	.LASF90
	.byte	0xb
	.byte	0x6e
	.long	0x45f
	.byte	0x8
	.uleb128 0x9
	.long	.LASF91
	.byte	0xb
	.byte	0x71
	.long	0x45f
	.byte	0x10
	.uleb128 0x9
	.long	.LASF92
	.byte	0xb
	.byte	0x74
	.long	0x4d
	.byte	0x18
	.uleb128 0x9
	.long	.LASF93
	.byte	0xb
	.byte	0x77
	.long	0x4d
	.byte	0x1c
	.uleb128 0x9
	.long	.LASF94
	.byte	0xb
	.byte	0x7a
	.long	0x4d8
	.byte	0x20
	.uleb128 0x9
	.long	.LASF95
	.byte	0xb
	.byte	0x7d
	.long	0x54b
	.byte	0x28
	.uleb128 0x9
	.long	.LASF96
	.byte	0xb
	.byte	0x7e
	.long	0x54b
	.byte	0x30
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x4de
	.uleb128 0x10
	.long	.LASF97
	.byte	0xb
	.byte	0x80
	.long	0x54b
	.uleb128 0x10
	.long	.LASF98
	.byte	0xb
	.byte	0x8c
	.long	0x4d
	.uleb128 0x10
	.long	.LASF99
	.byte	0xb
	.byte	0xa5
	.long	0x86
	.uleb128 0x10
	.long	.LASF100
	.byte	0xb
	.byte	0xb2
	.long	0x36e
	.uleb128 0x16
	.string	"del"
	.byte	0x1
	.byte	0x21
	.quad	.LFB7
	.quad	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x5c3
	.uleb128 0x17
	.long	.LASF60
	.byte	0x1
	.byte	0x21
	.long	0x5c3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x18
	.string	"v"
	.byte	0x1
	.byte	0x21
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x19
	.string	"tmp"
	.byte	0x1
	.byte	0x25
	.long	0x368
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x36e
	.uleb128 0x1a
	.long	.LASF101
	.byte	0x1
	.byte	0x12
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0x64d
	.uleb128 0x17
	.long	.LASF60
	.byte	0x1
	.byte	0x12
	.long	0x5c3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x18
	.string	"v"
	.byte	0x1
	.byte	0x12
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x19
	.string	"cur"
	.byte	0x1
	.byte	0x13
	.long	0x368
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1b
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.uleb128 0x19
	.string	"hdr"
	.byte	0x1
	.byte	0x16
	.long	0x4d2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1b
	.quad	.LBB3
	.quad	.LBE3-.LBB3
	.uleb128 0x19
	.string	"p"
	.byte	0x1
	.byte	0x18
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1c
	.long	.LASF108
	.byte	0x1
	.byte	0x5
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x17
	.long	.LASF60
	.byte	0x1
	.byte	0x5
	.long	0x5c3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x18
	.string	"v"
	.byte	0x1
	.byte	0x5
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x17
	.long	.LASF57
	.byte	0x1
	.byte	0x5
	.long	0x62
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x1d
	.long	.LASF102
	.byte	0x1
	.byte	0x7
	.long	0x368
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
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x1c
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
.LASF65:
	.string	"optind"
.LASF64:
	.string	"optarg"
.LASF94:
	.string	"freepools"
.LASF51:
	.string	"sys_nerr"
.LASF22:
	.string	"_IO_save_end"
.LASF5:
	.string	"short int"
.LASF7:
	.string	"size_t"
.LASF32:
	.string	"_offset"
.LASF68:
	.string	"__tzname"
.LASF16:
	.string	"_IO_write_ptr"
.LASF11:
	.string	"_flags"
.LASF81:
	.string	"freeblock"
.LASF74:
	.string	"Co_uintptr_t"
.LASF46:
	.string	"_IO_2_1_stdout_"
.LASF63:
	.string	"__environ"
.LASF23:
	.string	"_markers"
.LASF56:
	.string	"value"
.LASF73:
	.string	"timezone"
.LASF89:
	.string	"address"
.LASF108:
	.string	"push"
.LASF86:
	.string	"nextoffset"
.LASF84:
	.string	"arenaindex"
.LASF4:
	.string	"signed char"
.LASF88:
	.string	"arena_object"
.LASF50:
	.string	"stderr"
.LASF72:
	.string	"daylight"
.LASF53:
	.string	"long long int"
.LASF100:
	.string	"Hugmem"
.LASF55:
	.string	"link_list"
.LASF70:
	.string	"__timezone"
.LASF31:
	.string	"_lock"
.LASF69:
	.string	"__daylight"
.LASF6:
	.string	"long int"
.LASF62:
	.string	"List"
.LASF76:
	.string	"addr"
.LASF28:
	.string	"_cur_column"
.LASF47:
	.string	"_IO_2_1_stderr_"
.LASF77:
	.string	"block"
.LASF107:
	.string	"_IO_FILE_plus"
.LASF44:
	.string	"_pos"
.LASF96:
	.string	"prevarena"
.LASF78:
	.string	"_padding"
.LASF15:
	.string	"_IO_write_base"
.LASF83:
	.string	"prevpool"
.LASF29:
	.string	"_vtable_offset"
.LASF27:
	.string	"_old_offset"
.LASF1:
	.string	"unsigned char"
.LASF93:
	.string	"ntotalpools"
.LASF18:
	.string	"_IO_buf_base"
.LASF45:
	.string	"_IO_2_1_stdin_"
.LASF85:
	.string	"szidx"
.LASF59:
	.string	"ListNode"
.LASF91:
	.string	"pool_address"
.LASF75:
	.string	"flags"
.LASF54:
	.string	"long long unsigned int"
.LASF103:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -g -fno-builtin"
.LASF97:
	.string	"arenas"
.LASF101:
	.string	"mark"
.LASF3:
	.string	"unsigned int"
.LASF41:
	.string	"_IO_marker"
.LASF30:
	.string	"_shortbuf"
.LASF13:
	.string	"_IO_read_end"
.LASF71:
	.string	"tzname"
.LASF39:
	.string	"_unused2"
.LASF66:
	.string	"opterr"
.LASF102:
	.string	"node"
.LASF19:
	.string	"_IO_buf_end"
.LASF10:
	.string	"char"
.LASF40:
	.string	"_IO_FILE"
.LASF98:
	.string	"maxarenas"
.LASF60:
	.string	"list"
.LASF42:
	.string	"_next"
.LASF33:
	.string	"__pad1"
.LASF34:
	.string	"__pad2"
.LASF35:
	.string	"__pad3"
.LASF36:
	.string	"__pad4"
.LASF37:
	.string	"__pad5"
.LASF95:
	.string	"nextarena"
.LASF2:
	.string	"short unsigned int"
.LASF80:
	.string	"pool_header"
.LASF0:
	.string	"long unsigned int"
.LASF17:
	.string	"_IO_write_end"
.LASF9:
	.string	"__off64_t"
.LASF104:
	.string	"/home/xiaodo/c++/colang/src/gc/Hugmem.c"
.LASF25:
	.string	"_fileno"
.LASF24:
	.string	"_chain"
.LASF57:
	.string	"size"
.LASF8:
	.string	"__off_t"
.LASF79:
	.string	"count"
.LASF105:
	.string	"/home/xiaodo/c++/colang/tests/src/gc"
.LASF21:
	.string	"_IO_backup_base"
.LASF48:
	.string	"stdin"
.LASF92:
	.string	"nfreepools"
.LASF26:
	.string	"_flags2"
.LASF38:
	.string	"_mode"
.LASF14:
	.string	"_IO_read_base"
.LASF99:
	.string	"sp_start"
.LASF82:
	.string	"nextpool"
.LASF20:
	.string	"_IO_save_base"
.LASF52:
	.string	"sys_errlist"
.LASF67:
	.string	"optopt"
.LASF43:
	.string	"_sbuf"
.LASF12:
	.string	"_IO_read_ptr"
.LASF90:
	.string	"first_address"
.LASF61:
	.string	"root"
.LASF49:
	.string	"stdout"
.LASF58:
	.string	"next"
.LASF106:
	.string	"_IO_lock_t"
.LASF87:
	.string	"maxnextoffset"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

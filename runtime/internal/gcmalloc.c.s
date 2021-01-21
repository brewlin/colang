	.file	"gcmalloc.c"
	.text
.Ltext0:
	.globl	newobject
	.type	newobject, @function
newobject:
.LFB12:
	.file 1 "/home/xiaodo/c++/colang/src/internal/gcmalloc.c"
	.loc 1 9 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 1 10 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 1 25 0
	cmpl	$8, -20(%rbp)
	ja	.L2
	movl	-20(%rbp), %eax
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
	.long	.L9-.L4
	.long	.L10-.L4
	.long	.L11-.L4
	.long	.L12-.L4
	.text
.L5:
	.loc 1 27 0
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 1 28 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 1 29 0
	jmp	.L13
.L6:
	.loc 1 31 0
	movq	-8(%rbp), %rax
	movq	$2, (%rax)
	.loc 1 32 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 1 33 0
	jmp	.L13
.L7:
	.loc 1 35 0
	movq	-8(%rbp), %rax
	movq	$3, (%rax)
	.loc 1 36 0
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	stringnew@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 1 37 0
	jmp	.L13
.L8:
	.loc 1 39 0
	movq	-8(%rbp), %rax
	movq	$4, (%rax)
	.loc 1 40 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 1 41 0
	jmp	.L13
.L9:
	.loc 1 43 0
	movq	-8(%rbp), %rax
	movq	$5, (%rax)
	.loc 1 44 0
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rdx
	movq	%rdx, 8(%rax)
	.loc 1 45 0
	jmp	.L13
.L3:
	.loc 1 47 0
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
	.loc 1 48 0
	movq	-8(%rbp), %rax
	movq	$0, 8(%rax)
	.loc 1 49 0
	jmp	.L13
.L10:
	.loc 1 51 0
	movq	-8(%rbp), %rax
	movq	$6, (%rax)
	.loc 1 52 0
	movl	$8, %esi
	movl	$8, %edi
	call	array_create@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 1 53 0
	movq	-8(%rbp), %rax
	jmp	.L14
.L11:
	.loc 1 55 0
	movq	-8(%rbp), %rax
	movq	$7, (%rax)
	.loc 1 56 0
	movl	$0, %eax
	call	map_create@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 1 57 0
	movq	-8(%rbp), %rax
	jmp	.L14
.L12:
	.loc 1 59 0
	movq	-8(%rbp), %rax
	movq	$8, (%rax)
	.loc 1 60 0
	movq	-32(%rbp), %rax
	movl	%eax, %edi
	call	object_create@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 1 61 0
	movq	-8(%rbp), %rax
	jmp	.L14
.L2:
	.loc 1 64 0
	movq	-8(%rbp), %rax
	movq	$0, (%rax)
.L13:
	.loc 1 66 0
	movq	-8(%rbp), %rax
.L14:
	.loc 1 67 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	newobject, .-newobject
	.globl	get_object_value
	.type	get_object_value, @function
get_object_value:
.LFB13:
	.loc 1 72 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	.loc 1 73 0
	cmpq	$0, -8(%rbp)
	jne	.L16
	.loc 1 73 0 is_stmt 0 discriminator 1
	movl	$0, %eax
	jmp	.L17
.L16:
	.loc 1 75 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	subq	$1, %rax
	cmpq	$5, %rax
	ja	.L18
	.loc 1 82 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	jmp	.L17
.L18:
	.loc 1 84 0
	movl	$0, %eax
.L17:
	.loc 1 85 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	get_object_value, .-get_object_value
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h"
	.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 4 "/usr/include/x86_64-linux-gnu/bits/libio.h"
	.file 5 "/usr/include/stdio.h"
	.file 6 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
	.file 7 "/usr/include/unistd.h"
	.file 8 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h"
	.file 9 "/usr/include/time.h"
	.file 10 "/home/xiaodo/c++/colang/src/gc/Hugmem.h"
	.file 11 "/home/xiaodo/c++/colang/src/gc/gc.h"
	.file 12 "/home/xiaodo/c++/colang/src/internal/Value.h"
	.file 13 "/home/xiaodo/c++/colang/src/internal/String.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x633
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF106
	.byte	0xc
	.long	.LASF107
	.long	.LASF108
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
	.long	.LASF109
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
	.long	.LASF110
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
	.uleb128 0xf
	.long	.LASF55
	.byte	0x7
	.value	0x222
	.long	0x319
	.uleb128 0x6
	.byte	0x8
	.long	0x88
	.uleb128 0x10
	.long	.LASF56
	.byte	0x8
	.byte	0x24
	.long	0x88
	.uleb128 0x10
	.long	.LASF57
	.byte	0x8
	.byte	0x32
	.long	0x62
	.uleb128 0x10
	.long	.LASF58
	.byte	0x8
	.byte	0x37
	.long	0x62
	.uleb128 0x10
	.long	.LASF59
	.byte	0x8
	.byte	0x3b
	.long	0x62
	.uleb128 0xc
	.long	0x88
	.long	0x35b
	.uleb128 0xd
	.long	0x38
	.byte	0x1
	.byte	0
	.uleb128 0x10
	.long	.LASF60
	.byte	0x9
	.byte	0x9f
	.long	0x34b
	.uleb128 0x10
	.long	.LASF61
	.byte	0x9
	.byte	0xa0
	.long	0x62
	.uleb128 0x10
	.long	.LASF62
	.byte	0x9
	.byte	0xa1
	.long	0x69
	.uleb128 0x10
	.long	.LASF63
	.byte	0x9
	.byte	0xa6
	.long	0x34b
	.uleb128 0x10
	.long	.LASF64
	.byte	0x9
	.byte	0xae
	.long	0x62
	.uleb128 0x10
	.long	.LASF65
	.byte	0x9
	.byte	0xaf
	.long	0x69
	.uleb128 0x8
	.long	.LASF66
	.byte	0x18
	.byte	0xa
	.byte	0x7
	.long	0x3ce
	.uleb128 0x9
	.long	.LASF67
	.byte	0xa
	.byte	0x9
	.long	0x86
	.byte	0
	.uleb128 0x9
	.long	.LASF68
	.byte	0xa
	.byte	0xa
	.long	0x62
	.byte	0x8
	.uleb128 0x9
	.long	.LASF69
	.byte	0xa
	.byte	0xb
	.long	0x3ce
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x39d
	.uleb128 0x2
	.long	.LASF70
	.byte	0xa
	.byte	0xc
	.long	0x39d
	.uleb128 0x8
	.long	.LASF71
	.byte	0x8
	.byte	0xa
	.byte	0xe
	.long	0x3f8
	.uleb128 0x9
	.long	.LASF72
	.byte	0xa
	.byte	0xf
	.long	0x3f8
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x3d4
	.uleb128 0x2
	.long	.LASF73
	.byte	0xa
	.byte	0x10
	.long	0x3df
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
	.long	0x3fe
	.uleb128 0x8
	.long	.LASF101
	.byte	0x10
	.byte	0xc
	.byte	0x17
	.long	0x5a2
	.uleb128 0x9
	.long	.LASF102
	.byte	0xc
	.byte	0x19
	.long	0x69
	.byte	0
	.uleb128 0x9
	.long	.LASF103
	.byte	0xc
	.byte	0x1a
	.long	0x86
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF104
	.byte	0xc
	.byte	0x1b
	.long	0x57d
	.uleb128 0x10
	.long	.LASF105
	.byte	0xd
	.byte	0x5
	.long	0x2ad
	.uleb128 0x6
	.byte	0x8
	.long	0x5a2
	.uleb128 0x16
	.long	.LASF111
	.byte	0x1
	.byte	0x48
	.long	0x69
	.quad	.LFB13
	.quad	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0x5ee
	.uleb128 0x17
	.string	"obj"
	.byte	0x1
	.byte	0x48
	.long	0x5b8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x18
	.long	.LASF112
	.byte	0x1
	.byte	0x8
	.long	0x5b8
	.quad	.LFB12
	.quad	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x19
	.long	.LASF102
	.byte	0x1
	.byte	0x8
	.long	0x62
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x19
	.long	.LASF103
	.byte	0x1
	.byte	0x8
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1a
	.string	"ret"
	.byte	0x1
	.byte	0xa
	.long	0x5b8
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
	.uleb128 0x17
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
	.uleb128 0x18
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
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1a
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
.LASF57:
	.string	"optind"
.LASF56:
	.string	"optarg"
.LASF27:
	.string	"_old_offset"
.LASF29:
	.string	"_vtable_offset"
.LASF87:
	.string	"maxnextoffset"
.LASF111:
	.string	"get_object_value"
.LASF94:
	.string	"freepools"
.LASF105:
	.string	"LSTRING_NOINIT"
.LASF51:
	.string	"sys_nerr"
.LASF22:
	.string	"_IO_save_end"
.LASF17:
	.string	"_IO_write_end"
.LASF5:
	.string	"short int"
.LASF7:
	.string	"size_t"
.LASF32:
	.string	"_offset"
.LASF60:
	.string	"__tzname"
.LASF54:
	.string	"long long unsigned int"
.LASF16:
	.string	"_IO_write_ptr"
.LASF11:
	.string	"_flags"
.LASF74:
	.string	"Co_uintptr_t"
.LASF18:
	.string	"_IO_buf_base"
.LASF55:
	.string	"__environ"
.LASF106:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -fno-builtin"
.LASF23:
	.string	"_markers"
.LASF67:
	.string	"value"
.LASF65:
	.string	"timezone"
.LASF64:
	.string	"daylight"
.LASF58:
	.string	"opterr"
.LASF86:
	.string	"nextoffset"
.LASF4:
	.string	"signed char"
.LASF50:
	.string	"stderr"
.LASF53:
	.string	"long long int"
.LASF100:
	.string	"Hugmem"
.LASF66:
	.string	"link_list"
.LASF62:
	.string	"__timezone"
.LASF31:
	.string	"_lock"
.LASF61:
	.string	"__daylight"
.LASF6:
	.string	"long int"
.LASF73:
	.string	"List"
.LASF76:
	.string	"addr"
.LASF28:
	.string	"_cur_column"
.LASF47:
	.string	"_IO_2_1_stderr_"
.LASF77:
	.string	"block"
.LASF110:
	.string	"_IO_FILE_plus"
.LASF44:
	.string	"_pos"
.LASF96:
	.string	"prevarena"
.LASF78:
	.string	"_padding"
.LASF83:
	.string	"prevpool"
.LASF43:
	.string	"_sbuf"
.LASF40:
	.string	"_IO_FILE"
.LASF104:
	.string	"Value"
.LASF1:
	.string	"unsigned char"
.LASF93:
	.string	"ntotalpools"
.LASF36:
	.string	"__pad4"
.LASF85:
	.string	"szidx"
.LASF70:
	.string	"ListNode"
.LASF91:
	.string	"pool_address"
.LASF75:
	.string	"flags"
.LASF89:
	.string	"address"
.LASF101:
	.string	"core_value"
.LASF102:
	.string	"type"
.LASF30:
	.string	"_shortbuf"
.LASF3:
	.string	"unsigned int"
.LASF41:
	.string	"_IO_marker"
.LASF45:
	.string	"_IO_2_1_stdin_"
.LASF13:
	.string	"_IO_read_end"
.LASF15:
	.string	"_IO_write_base"
.LASF39:
	.string	"_unused2"
.LASF12:
	.string	"_IO_read_ptr"
.LASF19:
	.string	"_IO_buf_end"
.LASF112:
	.string	"newobject"
.LASF69:
	.string	"next"
.LASF108:
	.string	"/home/xiaodo/c++/colang/tests/src/internal"
.LASF10:
	.string	"char"
.LASF98:
	.string	"maxarenas"
.LASF71:
	.string	"list"
.LASF42:
	.string	"_next"
.LASF33:
	.string	"__pad1"
.LASF34:
	.string	"__pad2"
.LASF35:
	.string	"__pad3"
.LASF63:
	.string	"tzname"
.LASF37:
	.string	"__pad5"
.LASF95:
	.string	"nextarena"
.LASF103:
	.string	"data"
.LASF2:
	.string	"short unsigned int"
.LASF80:
	.string	"pool_header"
.LASF0:
	.string	"long unsigned int"
.LASF88:
	.string	"arena_object"
.LASF107:
	.string	"/home/xiaodo/c++/colang/src/internal/gcmalloc.c"
.LASF9:
	.string	"__off64_t"
.LASF8:
	.string	"__off_t"
.LASF24:
	.string	"_chain"
.LASF68:
	.string	"size"
.LASF79:
	.string	"count"
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
.LASF97:
	.string	"arenas"
.LASF20:
	.string	"_IO_save_base"
.LASF52:
	.string	"sys_errlist"
.LASF59:
	.string	"optopt"
.LASF25:
	.string	"_fileno"
.LASF81:
	.string	"freeblock"
.LASF90:
	.string	"first_address"
.LASF72:
	.string	"root"
.LASF49:
	.string	"stdout"
.LASF46:
	.string	"_IO_2_1_stdout_"
.LASF109:
	.string	"_IO_lock_t"
.LASF84:
	.string	"arenaindex"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

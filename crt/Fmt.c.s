	.file	"Fmt.c"
	.text
.Ltext0:
	#.section	.rodata
.LC0:
	.string	"null\n"
.LC1:
	.string	"%ld"
.LC2:
	.string	"%s"
.LC3:
	.string	"undefine"
.LC4:
	.string	"\n"
	.text
	.globl	println
	.type	println, @function
println:
.LFB11:
	.file 1 "/home/xiaodo/c++/colang/src/internal/Fmt.c"
	.loc 1 8 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$240, %rsp
	movq	%rdi, -232(%rbp)
	movq	%rsi, -168(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -152(%rbp)
	movq	%r8, -144(%rbp)
	movq	%r9, -136(%rbp)
	testb	%al, %al
	je	.L16
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm1, -112(%rbp)
	movaps	%xmm2, -96(%rbp)
	movaps	%xmm3, -80(%rbp)
	movaps	%xmm4, -64(%rbp)
	movaps	%xmm5, -48(%rbp)
	movaps	%xmm6, -32(%rbp)
	movaps	%xmm7, -16(%rbp)
.L16:
	.loc 1 13 0
	movl	$8, -216(%rbp)
	movl	$48, -212(%rbp)
	leaq	16(%rbp), %rax
	movq	%rax, -208(%rbp)
	leaq	-176(%rbp), %rax
	movq	%rax, -200(%rbp)
	.loc 1 15 0
	movq	-232(%rbp), %rax
	movq	8(%rax), %rax
	movl	%eax, -184(%rbp)
	.loc 1 17 0
	movl	$0, -180(%rbp)
	jmp	.L3
.L14:
	.loc 1 18 0
	movl	-216(%rbp), %eax
	cmpl	$47, %eax
	ja	.L4
	movq	-200(%rbp), %rax
	movl	-216(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-216(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -216(%rbp)
	jmp	.L5
.L4:
	movq	-208(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -208(%rbp)
.L5:
	movq	(%rax), %rax
	movq	%rax, -192(%rbp)
	.loc 1 19 0
	cmpq	$0, -192(%rbp)
	jne	.L6
	.loc 1 20 0
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 21 0
	jmp	.L7
.L6:
	.loc 1 23 0
	movq	-192(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$6, %rax
	ja	.L8
	leaq	0(,%rax,4), %rdx
	leaq	.L10(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L10(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	#.section	.rodata
	.align 4
	.align 4
.L10:
	.long	.L8-.L10
	.long	.L9-.L10
	.long	.L9-.L10
	.long	.L11-.L10
	.long	.L9-.L10
	.long	.L8-.L10
	.long	.L12-.L10
	.text
.L9:
	.loc 1 27 0
	movq	-192(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 28 0
	jmp	.L13
.L11:
	.loc 1 30 0
	movq	-192(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 31 0
	jmp	.L13
.L12:
	.loc 1 33 0
	movq	-192(%rbp), %rax
	movq	%rax, %rdi
	call	arr_tostring@PLT
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 34 0
	jmp	.L13
.L8:
	.loc 1 36 0
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L13:
	.loc 1 38 0
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L7:
	.loc 1 17 0 discriminator 2
	addl	$1, -180(%rbp)
.L3:
	.loc 1 17 0 is_stmt 0 discriminator 1
	movl	-180(%rbp), %eax
	cmpl	-184(%rbp), %eax
	jl	.L14
	.loc 1 42 0 is_stmt 1
	movl	-184(%rbp), %eax
	.loc 1 44 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	println, .-println
#	.section	.rodata
.LC5:
	.string	"null"
	.text
	.globl	print
	.type	print, @function
print:
.LFB12:
	.loc 1 45 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$240, %rsp
	movq	%rdi, -232(%rbp)
	movq	%rsi, -168(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -152(%rbp)
	movq	%r8, -144(%rbp)
	movq	%r9, -136(%rbp)
	testb	%al, %al
	je	.L31
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm1, -112(%rbp)
	movaps	%xmm2, -96(%rbp)
	movaps	%xmm3, -80(%rbp)
	movaps	%xmm4, -64(%rbp)
	movaps	%xmm5, -48(%rbp)
	movaps	%xmm6, -32(%rbp)
	movaps	%xmm7, -16(%rbp)
.L31:
	.loc 1 50 0
	movl	$8, -216(%rbp)
	movl	$48, -212(%rbp)
	leaq	16(%rbp), %rax
	movq	%rax, -208(%rbp)
	leaq	-176(%rbp), %rax
	movq	%rax, -200(%rbp)
	.loc 1 52 0
	movq	-232(%rbp), %rax
	movq	8(%rax), %rax
	movl	%eax, -184(%rbp)
	.loc 1 54 0
	movl	$0, -180(%rbp)
	jmp	.L19
.L29:
	.loc 1 55 0
	movl	-216(%rbp), %eax
	cmpl	$47, %eax
	ja	.L20
	movq	-200(%rbp), %rax
	movl	-216(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-216(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -216(%rbp)
	jmp	.L21
.L20:
	movq	-208(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -208(%rbp)
.L21:
	movq	(%rax), %rax
	movq	%rax, -192(%rbp)
	.loc 1 56 0
	cmpq	$0, -192(%rbp)
	jne	.L22
	.loc 1 57 0
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 58 0
	jmp	.L23
.L22:
	.loc 1 60 0
	movq	-192(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$6, %rax
	ja	.L24
	leaq	0(,%rax,4), %rdx
	leaq	.L26(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L26(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
	#.section	.rodata
	.align 4
	.align 4
.L26:
	.long	.L24-.L26
	.long	.L25-.L26
	.long	.L25-.L26
	.long	.L27-.L26
	.long	.L25-.L26
	.long	.L24-.L26
	.long	.L28-.L26
	.text
.L25:
	.loc 1 64 0
	movq	-192(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 65 0
	jmp	.L23
.L27:
	.loc 1 67 0
	movq	-192(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 68 0
	jmp	.L23
.L28:
	.loc 1 70 0
	movq	-192(%rbp), %rax
	movq	%rax, %rdi
	call	arr_tostring@PLT
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 1 71 0
	jmp	.L23
.L24:
	.loc 1 73 0
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L23:
	.loc 1 54 0 discriminator 2
	addl	$1, -180(%rbp)
.L19:
	.loc 1 54 0 is_stmt 0 discriminator 1
	movl	-180(%rbp), %eax
	cmpl	-184(%rbp), %eax
	jl	.L29
	.loc 1 77 0 is_stmt 1
	movl	-184(%rbp), %eax
	.loc 1 79 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	print, .-print
.Letext0:
	.file 2 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h"
	.file 3 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 4 "/usr/include/x86_64-linux-gnu/bits/libio.h"
	.file 5 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h"
	.file 6 "<built-in>"
	.file 7 "/usr/include/stdio.h"
	.file 8 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
	.file 9 "/usr/include/unistd.h"
	.file 10 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h"
	.file 11 "/usr/include/time.h"
	.file 12 "/home/xiaodo/c++/colang/src/gc/Hugmem.h"
	.file 13 "/home/xiaodo/c++/colang/src/gc/gc.h"
	.file 14 "/home/xiaodo/c++/colang/src/internal/Value.h"
	.file 15 "/home/xiaodo/c++/colang/src/internal/String.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x6f9
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF114
	.byte	0xc
	.long	.LASF115
	.long	.LASF116
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF8
	.byte	0x2
	.byte	0xd8
	.long	0x38
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF0
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF1
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x5
	.byte	0x8
	.long	0x5f
	.uleb128 0x6
	.long	0x4d
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF2
	.uleb128 0x6
	.long	0x58
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF3
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF4
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF5
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF6
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF7
	.uleb128 0x2
	.long	.LASF9
	.byte	0x3
	.byte	0x8c
	.long	0x80
	.uleb128 0x2
	.long	.LASF10
	.byte	0x3
	.byte	0x8d
	.long	0x80
	.uleb128 0x7
	.byte	0x8
	.uleb128 0x5
	.byte	0x8
	.long	0x58
	.uleb128 0x8
	.long	.LASF41
	.byte	0xd8
	.byte	0x4
	.byte	0xf5
	.long	0x225
	.uleb128 0x9
	.long	.LASF11
	.byte	0x4
	.byte	0xf6
	.long	0x46
	.byte	0
	.uleb128 0x9
	.long	.LASF12
	.byte	0x4
	.byte	0xfb
	.long	0x9f
	.byte	0x8
	.uleb128 0x9
	.long	.LASF13
	.byte	0x4
	.byte	0xfc
	.long	0x9f
	.byte	0x10
	.uleb128 0x9
	.long	.LASF14
	.byte	0x4
	.byte	0xfd
	.long	0x9f
	.byte	0x18
	.uleb128 0x9
	.long	.LASF15
	.byte	0x4
	.byte	0xfe
	.long	0x9f
	.byte	0x20
	.uleb128 0x9
	.long	.LASF16
	.byte	0x4
	.byte	0xff
	.long	0x9f
	.byte	0x28
	.uleb128 0xa
	.long	.LASF17
	.byte	0x4
	.value	0x100
	.long	0x9f
	.byte	0x30
	.uleb128 0xa
	.long	.LASF18
	.byte	0x4
	.value	0x101
	.long	0x9f
	.byte	0x38
	.uleb128 0xa
	.long	.LASF19
	.byte	0x4
	.value	0x102
	.long	0x9f
	.byte	0x40
	.uleb128 0xa
	.long	.LASF20
	.byte	0x4
	.value	0x104
	.long	0x9f
	.byte	0x48
	.uleb128 0xa
	.long	.LASF21
	.byte	0x4
	.value	0x105
	.long	0x9f
	.byte	0x50
	.uleb128 0xa
	.long	.LASF22
	.byte	0x4
	.value	0x106
	.long	0x9f
	.byte	0x58
	.uleb128 0xa
	.long	.LASF23
	.byte	0x4
	.value	0x108
	.long	0x2be
	.byte	0x60
	.uleb128 0xa
	.long	.LASF24
	.byte	0x4
	.value	0x10a
	.long	0x2c4
	.byte	0x68
	.uleb128 0xa
	.long	.LASF25
	.byte	0x4
	.value	0x10c
	.long	0x46
	.byte	0x70
	.uleb128 0xa
	.long	.LASF26
	.byte	0x4
	.value	0x110
	.long	0x46
	.byte	0x74
	.uleb128 0xa
	.long	.LASF27
	.byte	0x4
	.value	0x112
	.long	0x87
	.byte	0x78
	.uleb128 0xa
	.long	.LASF28
	.byte	0x4
	.value	0x116
	.long	0x3f
	.byte	0x80
	.uleb128 0xa
	.long	.LASF29
	.byte	0x4
	.value	0x117
	.long	0x72
	.byte	0x82
	.uleb128 0xa
	.long	.LASF30
	.byte	0x4
	.value	0x118
	.long	0x2ca
	.byte	0x83
	.uleb128 0xa
	.long	.LASF31
	.byte	0x4
	.value	0x11c
	.long	0x2da
	.byte	0x88
	.uleb128 0xa
	.long	.LASF32
	.byte	0x4
	.value	0x125
	.long	0x92
	.byte	0x90
	.uleb128 0xa
	.long	.LASF33
	.byte	0x4
	.value	0x12d
	.long	0x9d
	.byte	0x98
	.uleb128 0xa
	.long	.LASF34
	.byte	0x4
	.value	0x12e
	.long	0x9d
	.byte	0xa0
	.uleb128 0xa
	.long	.LASF35
	.byte	0x4
	.value	0x12f
	.long	0x9d
	.byte	0xa8
	.uleb128 0xa
	.long	.LASF36
	.byte	0x4
	.value	0x130
	.long	0x9d
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
	.long	0x46
	.byte	0xc0
	.uleb128 0xa
	.long	.LASF39
	.byte	0x4
	.value	0x135
	.long	0x2e0
	.byte	0xc4
	.byte	0
	.uleb128 0x2
	.long	.LASF40
	.byte	0x5
	.byte	0x28
	.long	0x230
	.uleb128 0xb
	.long	.LASF117
	.long	0x239
	.uleb128 0xc
	.long	0x249
	.long	0x249
	.uleb128 0xd
	.long	0x38
	.byte	0
	.byte	0
	.uleb128 0x8
	.long	.LASF42
	.byte	0x18
	.byte	0x6
	.byte	0
	.long	0x286
	.uleb128 0x9
	.long	.LASF43
	.byte	0x6
	.byte	0
	.long	0x6b
	.byte	0
	.uleb128 0x9
	.long	.LASF44
	.byte	0x6
	.byte	0
	.long	0x6b
	.byte	0x4
	.uleb128 0x9
	.long	.LASF45
	.byte	0x6
	.byte	0
	.long	0x9d
	.byte	0x8
	.uleb128 0x9
	.long	.LASF46
	.byte	0x6
	.byte	0
	.long	0x9d
	.byte	0x10
	.byte	0
	.uleb128 0xe
	.long	.LASF118
	.byte	0x4
	.byte	0x9a
	.uleb128 0x8
	.long	.LASF47
	.byte	0x18
	.byte	0x4
	.byte	0xa0
	.long	0x2be
	.uleb128 0x9
	.long	.LASF48
	.byte	0x4
	.byte	0xa1
	.long	0x2be
	.byte	0
	.uleb128 0x9
	.long	.LASF49
	.byte	0x4
	.byte	0xa2
	.long	0x2c4
	.byte	0x8
	.uleb128 0x9
	.long	.LASF50
	.byte	0x4
	.byte	0xa6
	.long	0x46
	.byte	0x10
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.long	0x28d
	.uleb128 0x5
	.byte	0x8
	.long	0xa5
	.uleb128 0xc
	.long	0x58
	.long	0x2da
	.uleb128 0xd
	.long	0x38
	.byte	0
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.long	0x286
	.uleb128 0xc
	.long	0x58
	.long	0x2f0
	.uleb128 0xd
	.long	0x38
	.byte	0x13
	.byte	0
	.uleb128 0xf
	.long	.LASF119
	.uleb128 0x10
	.long	.LASF51
	.byte	0x4
	.value	0x13f
	.long	0x2f0
	.uleb128 0x10
	.long	.LASF52
	.byte	0x4
	.value	0x140
	.long	0x2f0
	.uleb128 0x10
	.long	.LASF53
	.byte	0x4
	.value	0x141
	.long	0x2f0
	.uleb128 0x2
	.long	.LASF54
	.byte	0x7
	.byte	0x2e
	.long	0x225
	.uleb128 0x11
	.long	.LASF55
	.byte	0x7
	.byte	0x87
	.long	0x2c4
	.uleb128 0x11
	.long	.LASF56
	.byte	0x7
	.byte	0x88
	.long	0x2c4
	.uleb128 0x11
	.long	.LASF57
	.byte	0x7
	.byte	0x89
	.long	0x2c4
	.uleb128 0x11
	.long	.LASF58
	.byte	0x8
	.byte	0x1a
	.long	0x46
	.uleb128 0xc
	.long	0x53
	.long	0x35b
	.uleb128 0x12
	.byte	0
	.uleb128 0x6
	.long	0x350
	.uleb128 0x11
	.long	.LASF59
	.byte	0x8
	.byte	0x1b
	.long	0x35b
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF60
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF61
	.uleb128 0x10
	.long	.LASF62
	.byte	0x9
	.value	0x222
	.long	0x385
	.uleb128 0x5
	.byte	0x8
	.long	0x9f
	.uleb128 0x11
	.long	.LASF63
	.byte	0xa
	.byte	0x24
	.long	0x9f
	.uleb128 0x11
	.long	.LASF64
	.byte	0xa
	.byte	0x32
	.long	0x46
	.uleb128 0x11
	.long	.LASF65
	.byte	0xa
	.byte	0x37
	.long	0x46
	.uleb128 0x11
	.long	.LASF66
	.byte	0xa
	.byte	0x3b
	.long	0x46
	.uleb128 0xc
	.long	0x9f
	.long	0x3c7
	.uleb128 0xd
	.long	0x38
	.byte	0x1
	.byte	0
	.uleb128 0x11
	.long	.LASF67
	.byte	0xb
	.byte	0x9f
	.long	0x3b7
	.uleb128 0x11
	.long	.LASF68
	.byte	0xb
	.byte	0xa0
	.long	0x46
	.uleb128 0x11
	.long	.LASF69
	.byte	0xb
	.byte	0xa1
	.long	0x80
	.uleb128 0x11
	.long	.LASF70
	.byte	0xb
	.byte	0xa6
	.long	0x3b7
	.uleb128 0x11
	.long	.LASF71
	.byte	0xb
	.byte	0xae
	.long	0x46
	.uleb128 0x11
	.long	.LASF72
	.byte	0xb
	.byte	0xaf
	.long	0x80
	.uleb128 0x8
	.long	.LASF73
	.byte	0x18
	.byte	0xc
	.byte	0x7
	.long	0x43a
	.uleb128 0x9
	.long	.LASF74
	.byte	0xc
	.byte	0x9
	.long	0x9d
	.byte	0
	.uleb128 0x9
	.long	.LASF75
	.byte	0xc
	.byte	0xa
	.long	0x46
	.byte	0x8
	.uleb128 0x9
	.long	.LASF76
	.byte	0xc
	.byte	0xb
	.long	0x43a
	.byte	0x10
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.long	0x409
	.uleb128 0x2
	.long	.LASF77
	.byte	0xc
	.byte	0xc
	.long	0x409
	.uleb128 0x8
	.long	.LASF78
	.byte	0x8
	.byte	0xc
	.byte	0xe
	.long	0x464
	.uleb128 0x9
	.long	.LASF79
	.byte	0xc
	.byte	0xf
	.long	0x464
	.byte	0
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.long	0x440
	.uleb128 0x2
	.long	.LASF80
	.byte	0xc
	.byte	0x10
	.long	0x44b
	.uleb128 0x2
	.long	.LASF81
	.byte	0xd
	.byte	0x12
	.long	0x38
	.uleb128 0x13
	.byte	0x10
	.byte	0xd
	.byte	0x54
	.long	0x4a1
	.uleb128 0x9
	.long	.LASF82
	.byte	0xd
	.byte	0x55
	.long	0x46
	.byte	0
	.uleb128 0x9
	.long	.LASF83
	.byte	0xd
	.byte	0x56
	.long	0x9d
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF84
	.byte	0xd
	.byte	0x57
	.long	0x480
	.uleb128 0x14
	.byte	0x8
	.byte	0xd
	.byte	0x5a
	.long	0x4cb
	.uleb128 0x15
	.long	.LASF85
	.byte	0xd
	.byte	0x5b
	.long	0x4cb
	.uleb128 0x15
	.long	.LASF86
	.byte	0xd
	.byte	0x5c
	.long	0x6b
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.long	0x64
	.uleb128 0x8
	.long	.LASF87
	.byte	0x30
	.byte	0xd
	.byte	0x59
	.long	0x53e
	.uleb128 0x16
	.string	"ref"
	.byte	0xd
	.byte	0x5d
	.long	0x4ac
	.byte	0
	.uleb128 0x9
	.long	.LASF88
	.byte	0xd
	.byte	0x5e
	.long	0x53e
	.byte	0x8
	.uleb128 0x9
	.long	.LASF89
	.byte	0xd
	.byte	0x5f
	.long	0x544
	.byte	0x10
	.uleb128 0x9
	.long	.LASF90
	.byte	0xd
	.byte	0x60
	.long	0x544
	.byte	0x18
	.uleb128 0x9
	.long	.LASF91
	.byte	0xd
	.byte	0x61
	.long	0x6b
	.byte	0x20
	.uleb128 0x9
	.long	.LASF92
	.byte	0xd
	.byte	0x62
	.long	0x6b
	.byte	0x24
	.uleb128 0x9
	.long	.LASF93
	.byte	0xd
	.byte	0x63
	.long	0x6b
	.byte	0x28
	.uleb128 0x9
	.long	.LASF94
	.byte	0xd
	.byte	0x64
	.long	0x6b
	.byte	0x2c
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.long	0x4a1
	.uleb128 0x5
	.byte	0x8
	.long	0x4d1
	.uleb128 0x8
	.long	.LASF95
	.byte	0x38
	.byte	0xd
	.byte	0x69
	.long	0x5b7
	.uleb128 0x9
	.long	.LASF96
	.byte	0xd
	.byte	0x6b
	.long	0x475
	.byte	0
	.uleb128 0x9
	.long	.LASF97
	.byte	0xd
	.byte	0x6e
	.long	0x4cb
	.byte	0x8
	.uleb128 0x9
	.long	.LASF98
	.byte	0xd
	.byte	0x71
	.long	0x4cb
	.byte	0x10
	.uleb128 0x9
	.long	.LASF99
	.byte	0xd
	.byte	0x74
	.long	0x6b
	.byte	0x18
	.uleb128 0x9
	.long	.LASF100
	.byte	0xd
	.byte	0x77
	.long	0x6b
	.byte	0x1c
	.uleb128 0x9
	.long	.LASF101
	.byte	0xd
	.byte	0x7a
	.long	0x544
	.byte	0x20
	.uleb128 0x9
	.long	.LASF102
	.byte	0xd
	.byte	0x7d
	.long	0x5b7
	.byte	0x28
	.uleb128 0x9
	.long	.LASF103
	.byte	0xd
	.byte	0x7e
	.long	0x5b7
	.byte	0x30
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.long	0x54a
	.uleb128 0x11
	.long	.LASF104
	.byte	0xd
	.byte	0x80
	.long	0x5b7
	.uleb128 0x11
	.long	.LASF105
	.byte	0xd
	.byte	0x8c
	.long	0x6b
	.uleb128 0x11
	.long	.LASF106
	.byte	0xd
	.byte	0xa5
	.long	0x9d
	.uleb128 0x11
	.long	.LASF107
	.byte	0xd
	.byte	0xb2
	.long	0x46a
	.uleb128 0x8
	.long	.LASF108
	.byte	0x10
	.byte	0xe
	.byte	0x17
	.long	0x60e
	.uleb128 0x9
	.long	.LASF109
	.byte	0xe
	.byte	0x19
	.long	0x80
	.byte	0
	.uleb128 0x9
	.long	.LASF110
	.byte	0xe
	.byte	0x1a
	.long	0x9d
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF111
	.byte	0xe
	.byte	0x1b
	.long	0x5e9
	.uleb128 0x11
	.long	.LASF112
	.byte	0xf
	.byte	0x5
	.long	0x4d
	.uleb128 0x17
	.long	.LASF120
	.byte	0x1
	.byte	0x2d
	.long	0x46
	.quad	.LFB12
	.quad	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.long	0x68f
	.uleb128 0x18
	.long	.LASF86
	.byte	0x1
	.byte	0x2d
	.long	0x68f
	.uleb128 0x3
	.byte	0x91
	.sleb128 -248
	.uleb128 0x19
	.uleb128 0x1a
	.string	"ap"
	.byte	0x1
	.byte	0x2f
	.long	0x319
	.uleb128 0x3
	.byte	0x91
	.sleb128 -232
	.uleb128 0x1a
	.string	"i"
	.byte	0x1
	.byte	0x30
	.long	0x46
	.uleb128 0x3
	.byte	0x91
	.sleb128 -196
	.uleb128 0x1b
	.long	.LASF113
	.byte	0x1
	.byte	0x30
	.long	0x46
	.uleb128 0x3
	.byte	0x91
	.sleb128 -200
	.uleb128 0x1a
	.string	"var"
	.byte	0x1
	.byte	0x31
	.long	0x68f
	.uleb128 0x3
	.byte	0x91
	.sleb128 -208
	.byte	0
	.uleb128 0x5
	.byte	0x8
	.long	0x60e
	.uleb128 0x1c
	.long	.LASF121
	.byte	0x1
	.byte	0x8
	.long	0x46
	.quad	.LFB11
	.quad	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x18
	.long	.LASF86
	.byte	0x1
	.byte	0x8
	.long	0x68f
	.uleb128 0x3
	.byte	0x91
	.sleb128 -248
	.uleb128 0x19
	.uleb128 0x1a
	.string	"ap"
	.byte	0x1
	.byte	0xa
	.long	0x319
	.uleb128 0x3
	.byte	0x91
	.sleb128 -232
	.uleb128 0x1a
	.string	"i"
	.byte	0x1
	.byte	0xb
	.long	0x46
	.uleb128 0x3
	.byte	0x91
	.sleb128 -196
	.uleb128 0x1b
	.long	.LASF113
	.byte	0x1
	.byte	0xb
	.long	0x46
	.uleb128 0x3
	.byte	0x91
	.sleb128 -200
	.uleb128 0x1a
	.string	"var"
	.byte	0x1
	.byte	0xc
	.long	0x68f
	.uleb128 0x3
	.byte	0x91
	.sleb128 -208
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
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
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
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0xf
	.uleb128 0x13
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x11
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
	.uleb128 0x12
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
	.uleb128 0x18
	.byte	0
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
	.uleb128 0x1b
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
.LASF9:
	.string	"__off_t"
.LASF86:
	.string	"count"
.LASF12:
	.string	"_IO_read_ptr"
.LASF97:
	.string	"first_address"
.LASF24:
	.string	"_chain"
.LASF92:
	.string	"szidx"
.LASF8:
	.string	"size_t"
.LASF30:
	.string	"_shortbuf"
.LASF43:
	.string	"gp_offset"
.LASF54:
	.string	"va_list"
.LASF109:
	.string	"type"
.LASF53:
	.string	"_IO_2_1_stderr_"
.LASF18:
	.string	"_IO_buf_base"
.LASF61:
	.string	"long long unsigned int"
.LASF83:
	.string	"addr"
.LASF120:
	.string	"print"
.LASF95:
	.string	"arena_object"
.LASF76:
	.string	"next"
.LASF69:
	.string	"__timezone"
.LASF60:
	.string	"long long int"
.LASF5:
	.string	"signed char"
.LASF105:
	.string	"maxarenas"
.LASF77:
	.string	"ListNode"
.LASF25:
	.string	"_fileno"
.LASF13:
	.string	"_IO_read_end"
.LASF99:
	.string	"nfreepools"
.LASF7:
	.string	"long int"
.LASF101:
	.string	"freepools"
.LASF11:
	.string	"_flags"
.LASF117:
	.string	"__builtin_va_list"
.LASF19:
	.string	"_IO_buf_end"
.LASF55:
	.string	"stdin"
.LASF114:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -fno-builtin"
.LASF112:
	.string	"LSTRING_NOINIT"
.LASF27:
	.string	"_old_offset"
.LASF32:
	.string	"_offset"
.LASF94:
	.string	"maxnextoffset"
.LASF72:
	.string	"timezone"
.LASF74:
	.string	"value"
.LASF47:
	.string	"_IO_marker"
.LASF84:
	.string	"block"
.LASF4:
	.string	"unsigned int"
.LASF98:
	.string	"pool_address"
.LASF45:
	.string	"overflow_arg_area"
.LASF0:
	.string	"long unsigned int"
.LASF119:
	.string	"_IO_FILE_plus"
.LASF16:
	.string	"_IO_write_ptr"
.LASF58:
	.string	"sys_nerr"
.LASF49:
	.string	"_sbuf"
.LASF110:
	.string	"data"
.LASF75:
	.string	"size"
.LASF1:
	.string	"short unsigned int"
.LASF73:
	.string	"link_list"
.LASF20:
	.string	"_IO_save_base"
.LASF116:
	.string	"/home/xiaodo/c++/colang/tests/src/internal"
.LASF102:
	.string	"nextarena"
.LASF31:
	.string	"_lock"
.LASF113:
	.string	"total"
.LASF26:
	.string	"_flags2"
.LASF38:
	.string	"_mode"
.LASF56:
	.string	"stdout"
.LASF108:
	.string	"core_value"
.LASF51:
	.string	"_IO_2_1_stdin_"
.LASF80:
	.string	"List"
.LASF90:
	.string	"prevpool"
.LASF91:
	.string	"arenaindex"
.LASF63:
	.string	"optarg"
.LASF96:
	.string	"address"
.LASF64:
	.string	"optind"
.LASF40:
	.string	"__gnuc_va_list"
.LASF88:
	.string	"freeblock"
.LASF17:
	.string	"_IO_write_end"
.LASF103:
	.string	"prevarena"
.LASF118:
	.string	"_IO_lock_t"
.LASF41:
	.string	"_IO_FILE"
.LASF62:
	.string	"__environ"
.LASF68:
	.string	"__daylight"
.LASF81:
	.string	"Co_uintptr_t"
.LASF50:
	.string	"_pos"
.LASF59:
	.string	"sys_errlist"
.LASF23:
	.string	"_markers"
.LASF104:
	.string	"arenas"
.LASF3:
	.string	"unsigned char"
.LASF6:
	.string	"short int"
.LASF29:
	.string	"_vtable_offset"
.LASF70:
	.string	"tzname"
.LASF52:
	.string	"_IO_2_1_stdout_"
.LASF121:
	.string	"println"
.LASF46:
	.string	"reg_save_area"
.LASF100:
	.string	"ntotalpools"
.LASF115:
	.string	"/home/xiaodo/c++/colang/src/internal/Fmt.c"
.LASF66:
	.string	"optopt"
.LASF71:
	.string	"daylight"
.LASF93:
	.string	"nextoffset"
.LASF2:
	.string	"char"
.LASF65:
	.string	"opterr"
.LASF48:
	.string	"_next"
.LASF10:
	.string	"__off64_t"
.LASF28:
	.string	"_cur_column"
.LASF14:
	.string	"_IO_read_base"
.LASF22:
	.string	"_IO_save_end"
.LASF107:
	.string	"Hugmem"
.LASF106:
	.string	"sp_start"
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
.LASF85:
	.string	"_padding"
.LASF39:
	.string	"_unused2"
.LASF57:
	.string	"stderr"
.LASF87:
	.string	"pool_header"
.LASF111:
	.string	"Value"
.LASF21:
	.string	"_IO_backup_base"
.LASF44:
	.string	"fp_offset"
.LASF82:
	.string	"flags"
.LASF78:
	.string	"list"
.LASF67:
	.string	"__tzname"
.LASF89:
	.string	"nextpool"
.LASF15:
	.string	"_IO_write_base"
.LASF42:
	.string	"__va_list_tag"
.LASF79:
	.string	"root"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

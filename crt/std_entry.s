	.file	"entry.c"
	.text
.Ltext0:
	.type	crt_fatal_error, @function
crt_fatal_error:
.LFB0:
	.file 1 "/home/xiaodo/c++/colang/src/crt/entry.c"
	.loc 1 12 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	.loc 1 14 0
	movl	$1, %edi
	call	exit
	.loc 1 15 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	crt_fatal_error, .-crt_fatal_error
#	.section	.rodata
.LC0:
	.string	"heap initalize failed"
.LC1:
	.string	"IO initalize failed"
	.text
	.globl	mini_crt_entry
	.type	mini_crt_entry, @function
mini_crt_entry:
.LFB1:
	.loc 1 18 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	.loc 1 56 0
	movq	$0, -8(%rbp)
	.loc 1 58 0
#APP
# 58 "/home/xiaodo/c++/colang/src/crt/entry.c" 1
	movq %rbp,%rax 

# 0 "" 2
#NO_APP
	movq	%rax, -8(%rbp)
	.loc 1 60 0
	movq	-8(%rbp), %rax
	movq	4(%rax), %rax
	movq	%rax, -16(%rbp)
	.loc 1 61 0
	movq	-8(%rbp), %rax
	addq	$8, %rax
	movq	%rax, -24(%rbp)
	.loc 1 65 0
	movl	$0, %eax
	call	mini_crt_init_heap@PLT
	testq	%rax, %rax
	jne	.L3
	.loc 1 67 0
	leaq	.LC0(%rip), %rdi
	call	crt_fatal_error
.L3:
	.loc 1 70 0
	movl	$0, %eax
	call	mini_crt_init_io@PLT
	testq	%rax, %rax
	jne	.L4
	.loc 1 72 0
	leaq	.LC1(%rip), %rdi
	call	crt_fatal_error
.L4:
	.loc 1 75 0
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	main@PLT
	cltq
	movq	%rax, -32(%rbp)
	.loc 1 76 0
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	exit
	.loc 1 77 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	mini_crt_entry, .-mini_crt_entry
	.globl	exit
	.type	exit, @function
exit:
.LFB2:
	.loc 1 80 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	.loc 1 85 0
#APP
# 85 "/home/xiaodo/c++/colang/src/crt/entry.c" 1
	movq -8(%rbp),%rbx 
	movq $1,%rax 
	int $0x80		
	hlt    
	
# 0 "" 2
	.loc 1 90 0
#NO_APP
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	exit, .-exit
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x104
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF9
	.byte	0xc
	.long	.LASF10
	.long	.LASF11
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
	.long	.LASF2
	.byte	0x1
	.byte	0x4f
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x67
	.uleb128 0x4
	.long	.LASF8
	.byte	0x1
	.byte	0x4f
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x5
	.long	.LASF3
	.byte	0x1
	.byte	0x11
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0xbd
	.uleb128 0x6
	.string	"ret"
	.byte	0x1
	.byte	0x13
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x7
	.long	.LASF4
	.byte	0x1
	.byte	0x36
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x7
	.long	.LASF5
	.byte	0x1
	.byte	0x37
	.long	0xbd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x7
	.long	.LASF6
	.byte	0x1
	.byte	0x38
	.long	0xc3
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x8
	.byte	0x8
	.long	0xc3
	.uleb128 0x8
	.byte	0x8
	.long	0xc9
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF7
	.uleb128 0x9
	.long	0xc9
	.uleb128 0xa
	.long	.LASF12
	.byte	0x1
	.byte	0xb
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0x101
	.uleb128 0xb
	.string	"msg"
	.byte	0x1
	.byte	0xb
	.long	0x101
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x8
	.byte	0x8
	.long	0xd0
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
	.uleb128 0x4
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
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
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
.LASF8:
	.string	"exitCode"
.LASF1:
	.string	"unsigned char"
.LASF2:
	.string	"exit"
.LASF10:
	.string	"/home/xiaodo/c++/colang/src/crt/entry.c"
.LASF3:
	.string	"mini_crt_entry"
.LASF5:
	.string	"argv"
.LASF12:
	.string	"crt_fatal_error"
.LASF11:
	.string	"/home/xiaodo/c++/colang/tests/src/crt"
.LASF0:
	.string	"long int"
.LASF6:
	.string	"ebp_reg"
.LASF7:
	.string	"char"
.LASF4:
	.string	"argc"
.LASF9:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -g -fno-builtin"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

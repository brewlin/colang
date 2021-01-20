	.file	"stdio.c"
	.text
.Ltext0:
	.globl	mini_crt_init_io
	.type	mini_crt_init_io, @function
mini_crt_init_io:
.LFB0:
	.file 1 "/home/xiaodo/c++/colang/src/crt/stdio.c"
	.loc 1 5 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	.loc 1 6 0
	movl	$1, %eax
	.loc 1 7 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	mini_crt_init_io, .-mini_crt_init_io
	.type	open, @function
open:
.LFB1:
	.loc 1 84 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 1 85 0
	movq	$0, -8(%rbp)
	.loc 1 86 0
#APP
# 86 "/home/xiaodo/c++/colang/src/crt/stdio.c" 1
	movq $5,%rax		
	movq -24(%rbp),%rbx	
	movq -32(%rbp),%rcx 
	movq -40(%rbp),%rdx 
	int $0x80  
	movq %rax,-8(%rbp) 
	
# 0 "" 2
	.loc 1 94 0
#NO_APP
	movq	-8(%rbp), %rax
	.loc 1 95 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	open, .-open
	.type	read, @function
read:
.LFB2:
	.loc 1 98 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 1 99 0
	movq	$0, -8(%rbp)
	.loc 1 100 0
#APP
# 100 "/home/xiaodo/c++/colang/src/crt/stdio.c" 1
	movq $3,%rax 
	movq -24(%rbp),%rbx 
	movq -32(%rbp),%rcx 
	movq -40(%rbp), %rdx 
	int $0x80  
	movq %rax,-8(%rbp)  
	
# 0 "" 2
	.loc 1 107 0
#NO_APP
	movq	-8(%rbp), %rax
	.loc 1 108 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	read, .-read
	.globl	write
	.type	write, @function
write:
.LFB3:
	.loc 1 111 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 1 112 0
	movq	$0, -8(%rbp)
	.loc 1 113 0
#APP
# 113 "/home/xiaodo/c++/colang/src/crt/stdio.c" 1
	movq $4,%rax  
	movq -24(%rbp),%rbx 
	movq -32(%rbp),%rcx  
	movq -40(%rbp),%rdx 
	int $0x80  
	movq %rax,-8(%rbp) 
	
# 0 "" 2
	.loc 1 121 0
#NO_APP
	movq	-8(%rbp), %rax
	.loc 1 122 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	write, .-write
	.type	close, @function
close:
.LFB4:
	.loc 1 125 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	.loc 1 126 0
	movq	$0, -8(%rbp)
	.loc 1 127 0
#APP
# 127 "/home/xiaodo/c++/colang/src/crt/stdio.c" 1
	movq $6,%rax  
	movq -24(%rbp),%rbx  
	int $0x80  
	movq %rax,-8(%rbp) 
	
# 0 "" 2
	.loc 1 133 0
#NO_APP
	movq	-8(%rbp), %rax
	.loc 1 134 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	close, .-close
	.type	seek, @function
seek:
.LFB5:
	.loc 1 137 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 1 138 0
	movq	$0, -8(%rbp)
	.loc 1 139 0
#APP
# 139 "/home/xiaodo/c++/colang/src/crt/stdio.c" 1
	movq $19,%rax  
	movq -24(%rbp),%rbx 
	movq -32(%rbp),%rcx  
	movq -40(%rbp),%rdx 
	int $0x80  
	movq %rax,-8(%rbp) 
	
# 0 "" 2
	.loc 1 147 0
#NO_APP
	movq	-8(%rbp), %rax
	.loc 1 148 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	seek, .-seek
#	.section	.rodata
.LC0:
	.string	"w"
.LC1:
	.string	"w+"
.LC2:
	.string	"r"
.LC3:
	.string	"r+"
	.text
	.globl	fopen
	.type	fopen, @function
fopen:
.LFB6:
	.loc 1 151 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	.loc 1 152 0
	movq	$-1, -16(%rbp)
	.loc 1 153 0
	movq	$0, -8(%rbp)
	.loc 1 154 0
	movq	$448, -24(%rbp)
	.loc 1 165 0
	movq	-48(%rbp), %rax
	leaq	.LC0(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testq	%rax, %rax
	jne	.L14
	.loc 1 167 0
	orq	$577, -8(%rbp)
.L14:
	.loc 1 170 0
	movq	-48(%rbp), %rax
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testq	%rax, %rax
	jne	.L15
	.loc 1 172 0
	orq	$578, -8(%rbp)
.L15:
	.loc 1 175 0
	movq	-48(%rbp), %rax
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testq	%rax, %rax
	.loc 1 180 0
	movq	-48(%rbp), %rax
	leaq	.LC3(%rip), %rsi
	movq	%rax, %rdi
	call	strcmp@PLT
	testq	%rax, %rax
	jne	.L17
	.loc 1 182 0
	orq	$66, -8(%rbp)
.L17:
	.loc 1 185 0
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	open
	movq	%rax, -16(%rbp)
	.loc 1 186 0
	movq	-16(%rbp), %rax
	.loc 1 187 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	fopen, .-fopen
	.globl	fread
	.type	fread, @function
fread:
.LFB7:
	.loc 1 190 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	.loc 1 191 0
	movq	-16(%rbp), %rax
	imulq	-24(%rbp), %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	read
	.loc 1 192 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	fread, .-fread
	.globl	fwrite
	.type	fwrite, @function
fwrite:
.LFB8:
	.loc 1 194 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	%rcx, -32(%rbp)
	.loc 1 195 0
	movq	-16(%rbp), %rax
	imulq	-24(%rbp), %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	write
	.loc 1 196 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	fwrite, .-fwrite
	.globl	fclose
	.type	fclose, @function
fclose:
.LFB9:
	.loc 1 199 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	.loc 1 200 0
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	close
	.loc 1 201 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	fclose, .-fclose
	.globl	fseek
	.type	fseek, @function
fseek:
.LFB10:
	.loc 1 204 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	.loc 1 205 0
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	seek
	.loc 1 206 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	fseek, .-fseek
.Letext0:
	.file 2 "/home/xiaodo/c++/colang/src/crt/minicrt.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x3be
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF23
	.byte	0xc
	.long	.LASF24
	.long	.LASF25
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF26
	.byte	0x2
	.byte	0x2e
	.long	0x38
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x4
	.long	.LASF3
	.byte	0x1
	.byte	0xcb
	.long	0x38
	.quad	.LFB10
	.quad	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.long	0x91
	.uleb128 0x5
	.string	"fp"
	.byte	0x1
	.byte	0xcb
	.long	0x91
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x6
	.long	.LASF2
	.byte	0x1
	.byte	0xcb
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x5
	.string	"set"
	.byte	0x1
	.byte	0xcb
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x7
	.byte	0x8
	.long	0x2d
	.uleb128 0x4
	.long	.LASF4
	.byte	0x1
	.byte	0xc6
	.long	0x38
	.quad	.LFB9
	.quad	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.long	0xc6
	.uleb128 0x5
	.string	"fp"
	.byte	0x1
	.byte	0xc6
	.long	0x91
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x4
	.long	.LASF5
	.byte	0x1
	.byte	0xc1
	.long	0x38
	.quad	.LFB8
	.quad	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0x120
	.uleb128 0x6
	.long	.LASF6
	.byte	0x1
	.byte	0xc1
	.long	0x120
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x6
	.long	.LASF7
	.byte	0x1
	.byte	0xc1
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x6
	.long	.LASF8
	.byte	0x1
	.byte	0xc1
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x6
	.long	.LASF9
	.byte	0x1
	.byte	0xc1
	.long	0x91
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x7
	.byte	0x8
	.long	0x126
	.uleb128 0x8
	.uleb128 0x4
	.long	.LASF10
	.byte	0x1
	.byte	0xbd
	.long	0x38
	.quad	.LFB7
	.quad	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x181
	.uleb128 0x6
	.long	.LASF6
	.byte	0x1
	.byte	0xbd
	.long	0x181
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x6
	.long	.LASF7
	.byte	0x1
	.byte	0xbd
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x6
	.long	.LASF8
	.byte	0x1
	.byte	0xbd
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x6
	.long	.LASF9
	.byte	0x1
	.byte	0xbd
	.long	0x91
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.uleb128 0x4
	.long	.LASF11
	.byte	0x1
	.byte	0x96
	.long	0x91
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0x1ea
	.uleb128 0x6
	.long	.LASF12
	.byte	0x1
	.byte	0x96
	.long	0x1ea
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x6
	.long	.LASF13
	.byte	0x1
	.byte	0x96
	.long	0x1ea
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0xa
	.string	"fd"
	.byte	0x1
	.byte	0x98
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xb
	.long	.LASF14
	.byte	0x1
	.byte	0x99
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xb
	.long	.LASF15
	.byte	0x1
	.byte	0x9a
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x7
	.byte	0x8
	.long	0x1f7
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF16
	.uleb128 0xc
	.long	0x1f0
	.uleb128 0xd
	.long	.LASF17
	.byte	0x1
	.byte	0x88
	.long	0x38
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.long	0x255
	.uleb128 0x5
	.string	"fd"
	.byte	0x1
	.byte	0x88
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x6
	.long	.LASF2
	.byte	0x1
	.byte	0x88
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x6
	.long	.LASF13
	.byte	0x1
	.byte	0x88
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0xa
	.string	"ret"
	.byte	0x1
	.byte	0x8a
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xd
	.long	.LASF18
	.byte	0x1
	.byte	0x7c
	.long	0x38
	.quad	.LFB4
	.quad	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.long	0x292
	.uleb128 0x5
	.string	"fd"
	.byte	0x1
	.byte	0x7c
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xa
	.string	"ret"
	.byte	0x1
	.byte	0x7e
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xe
	.long	.LASF19
	.byte	0x1
	.byte	0x6e
	.long	0x38
	.quad	.LFB3
	.quad	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x2eb
	.uleb128 0x5
	.string	"fd"
	.byte	0x1
	.byte	0x6e
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x6
	.long	.LASF6
	.byte	0x1
	.byte	0x6e
	.long	0x120
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x6
	.long	.LASF7
	.byte	0x1
	.byte	0x6e
	.long	0x2eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0xa
	.string	"ret"
	.byte	0x1
	.byte	0x70
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF20
	.uleb128 0xd
	.long	.LASF21
	.byte	0x1
	.byte	0x61
	.long	0x38
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x34b
	.uleb128 0x5
	.string	"fd"
	.byte	0x1
	.byte	0x61
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x6
	.long	.LASF6
	.byte	0x1
	.byte	0x61
	.long	0x181
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x6
	.long	.LASF7
	.byte	0x1
	.byte	0x61
	.long	0x2eb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0xa
	.string	"ret"
	.byte	0x1
	.byte	0x63
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xd
	.long	.LASF22
	.byte	0x1
	.byte	0x53
	.long	0x38
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x3a4
	.uleb128 0x6
	.long	.LASF12
	.byte	0x1
	.byte	0x53
	.long	0x1ea
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x6
	.long	.LASF14
	.byte	0x1
	.byte	0x53
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x6
	.long	.LASF13
	.byte	0x1
	.byte	0x53
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0xa
	.string	"fd"
	.byte	0x1
	.byte	0x55
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xf
	.long	.LASF27
	.byte	0x1
	.byte	0x4
	.long	0x38
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
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
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
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
	.uleb128 0xe
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
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0
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
.LASF22:
	.string	"open"
.LASF24:
	.string	"/home/xiaodo/c++/colang/src/crt/stdio.c"
.LASF13:
	.string	"mode"
.LASF14:
	.string	"flags"
.LASF4:
	.string	"fclose"
.LASF20:
	.string	"long unsigned int"
.LASF27:
	.string	"mini_crt_init_io"
.LASF10:
	.string	"fread"
.LASF2:
	.string	"offset"
.LASF19:
	.string	"write"
.LASF11:
	.string	"fopen"
.LASF1:
	.string	"unsigned char"
.LASF16:
	.string	"char"
.LASF9:
	.string	"stream"
.LASF8:
	.string	"count"
.LASF0:
	.string	"long int"
.LASF18:
	.string	"close"
.LASF25:
	.string	"/home/xiaodo/c++/colang/tests/src/crt"
.LASF21:
	.string	"read"
.LASF26:
	.string	"FILE"
.LASF17:
	.string	"seek"
.LASF7:
	.string	"size"
.LASF23:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -g -fno-builtin"
.LASF12:
	.string	"filename"
.LASF5:
	.string	"fwrite"
.LASF6:
	.string	"buffer"
.LASF15:
	.string	"access"
.LASF3:
	.string	"fseek"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

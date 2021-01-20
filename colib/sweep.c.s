	.file	"sweep.c"
	.text
.Ltext0:
	.globl	gc_mark
	.type	gc_mark, @function
gc_mark:
.LFB5:
	.file 1 "/home/xiaodo/c++/colang/src/gc/sweep.c"
	.loc 1 11 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	.loc 1 12 0
	cmpq	$0, -40(%rbp)
	jne	.L2
	.loc 1 12 0 is_stmt 0 discriminator 1
	movl	$1, %eax
	jmp	.L3
.L2:
	.loc 1 16 0 is_stmt 1
	movq	-40(%rbp), %rax
	andq	$-4096, %rax
	movq	%rax, -16(%rbp)
	.loc 1 17 0
	movq	arenas(%rip), %rax
	movq	(%rax), %rdx
	movq	-16(%rbp), %rax
	cmpq	%rax, %rdx
	ja	.L4
	.loc 1 17 0 is_stmt 0 discriminator 1
	movq	arenas(%rip), %rax
	movq	(%rax), %rax
	leaq	262144(%rax), %rdx
	movq	-16(%rbp), %rax
	cmpq	%rax, %rdx
	jnb	.L5
.L4:
	.loc 1 19 0 is_stmt 1
	movl	$10, %eax
	jmp	.L3
.L5:
	.loc 1 21 0
	movq	-16(%rbp), %rax
	movl	32(%rax), %edx
	movl	maxarenas(%rip), %eax
	cmpl	%eax, %edx
	jnb	.L6
	.loc 1 21 0 is_stmt 0 discriminator 1
	movq	-40(%rbp), %rdx
	movq	arenas(%rip), %rcx
	movq	-16(%rbp), %rax
	movl	32(%rax), %eax
	movl	%eax, %esi
	movq	%rsi, %rax
	salq	$3, %rax
	subq	%rsi, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cmpq	$262143, %rax
	ja	.L6
	.loc 1 21 0 discriminator 2
	movq	arenas(%rip), %rdx
	movq	-16(%rbp), %rax
	movl	32(%rax), %eax
	movl	%eax, %ecx
	movq	%rcx, %rax
	salq	$3, %rax
	subq	%rcx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L7
.L6:
	.loc 1 23 0 is_stmt 1
	movl	$10, %eax
	jmp	.L3
.L7:
	.loc 1 27 0
	movq	-16(%rbp), %rax
	movl	36(%rax), %eax
	addl	$1, %eax
	sall	$3, %eax
	movl	%eax, -20(%rbp)
	.loc 1 29 0
	movq	-40(%rbp), %rax
	subq	$8, %rax
	movq	%rax, -32(%rbp)
	.loc 1 31 0
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jle	.L8
	.loc 1 31 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$3, %eax
	jle	.L9
.L8:
	.loc 1 32 0 is_stmt 1
	movl	$1, %eax
	jmp	.L3
.L9:
	.loc 1 34 0
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L10
	.loc 1 36 0
	movl	$1, %eax
	jmp	.L3
.L10:
	.loc 1 38 0
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L11
	.loc 1 40 0
	movl	$1, %eax
	jmp	.L3
.L11:
	.loc 1 44 0
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	orl	$2, %eax
	movl	%eax, %edx
	movq	-32(%rbp), %rax
	movl	%edx, (%rax)
.LBB2:
	.loc 1 47 0
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L12
.L14:
	.loc 1 50 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	gc_mark
	cmpl	$10, %eax
	jne	.L13
	.loc 1 51 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	Hugmem(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	mark@PLT
.L13:
	.loc 1 47 0 discriminator 2
	addq	$1, -8(%rbp)
.L12:
	.loc 1 47 0 is_stmt 0 discriminator 1
	movl	-20(%rbp), %eax
	leaq	-8(%rax), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	cmpq	%rax, -8(%rbp)
	jb	.L14
.LBE2:
	.loc 1 54 0 is_stmt 1
	movl	$1, %eax
.L3:
	.loc 1 55 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	gc_mark, .-gc_mark
	.globl	gc_sweep
	.type	gc_sweep, @function
gc_sweep:
.LFB6:
	.loc 1 60 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	.loc 1 62 0
	movq	arenas(%rip), %rax
	movq	%rax, -24(%rbp)
	.loc 1 64 0
	movl	$0, -28(%rbp)
.LBB3:
	.loc 1 67 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -8(%rbp)
	jmp	.L16
.L21:
.LBB4:
	.loc 1 69 0
	movq	-8(%rbp), %rax
	movq	%rax, -40(%rbp)
	.loc 1 70 0
	movq	-40(%rbp), %rax
	movl	36(%rax), %eax
	addl	$1, %eax
	sall	$3, %eax
	movl	%eax, -28(%rbp)
	.loc 1 71 0
	movq	-8(%rbp), %rax
	addq	$48, %rax
	movq	%rax, -48(%rbp)
	.loc 1 72 0
	movq	-8(%rbp), %rax
	addq	$4096, %rax
	movq	%rax, -56(%rbp)
.LBB5:
	.loc 1 73 0
	movq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
	jmp	.L17
.L20:
.LBB6:
	.loc 1 75 0
	movq	-16(%rbp), %rax
	movq	%rax, -64(%rbp)
	.loc 1 77 0
	movq	-64(%rbp), %rax
	movl	(%rax), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L18
	.loc 1 79 0
	movq	-64(%rbp), %rax
	movl	(%rax), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L19
	.loc 1 82 0
	movq	-64(%rbp), %rax
	movl	(%rax), %eax
	andl	$-3, %eax
	movl	%eax, %edx
	movq	-64(%rbp), %rax
	movl	%edx, (%rax)
	jmp	.L18
.L19:
	.loc 1 87 0
	movq	-64(%rbp), %rax
	movl	(%rax), %eax
	andl	$-2, %eax
	movl	%eax, %edx
	movq	-64(%rbp), %rax
	movl	%edx, (%rax)
	.loc 1 88 0
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	Free@PLT
.L18:
.LBE6:
	.loc 1 73 0 discriminator 2
	movl	-28(%rbp), %eax
	addq	%rax, -16(%rbp)
.L17:
	.loc 1 73 0 is_stmt 0 discriminator 1
	movq	-16(%rbp), %rax
	cmpq	-56(%rbp), %rax
	jb	.L20
.LBE5:
.LBE4:
	.loc 1 67 0 is_stmt 1 discriminator 2
	addq	$4096, -8(%rbp)
.L16:
	.loc 1 67 0 is_stmt 0 discriminator 1
	movq	-24(%rbp), %rax
	movq	16(%rax), %rax
	cmpq	%rax, -8(%rbp)
	jb	.L21
.LBE3:
	.loc 1 96 0 is_stmt 1
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	gc_sweep, .-gc_sweep
	.globl	tell_is_stackarg
	.type	tell_is_stackarg, @function
tell_is_stackarg:
.LFB7:
	.loc 1 97 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	.loc 1 98 0
	movl	$0, %eax
	call	get_sp@PLT
	movq	%rax, -8(%rbp)
	.loc 1 99 0
	movq	sp_start(%rip), %rax
	cmpq	%rax, -24(%rbp)
	jnb	.L24
	.loc 1 99 0 is_stmt 0 discriminator 1
	movq	-24(%rbp), %rax
	cmpq	-8(%rbp), %rax
	jbe	.L24
	.loc 1 100 0 is_stmt 1
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	gc_mark
	cmpl	$10, %eax
	jne	.L24
	.loc 1 101 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movq	Hugmem(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	mark@PLT
.L24:
	.loc 1 104 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	tell_is_stackarg, .-tell_is_stackarg
	.globl	scan_register
	.type	scan_register, @function
scan_register:
.LFB8:
	.loc 1 109 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	.loc 1 112 0
	movl	$0, %eax
	call	get_sp@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L26
	.loc 1 112 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	tell_is_stackarg
.L26:
	.loc 1 113 0 is_stmt 1
	movl	$0, %eax
	call	get_bp@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L27
	.loc 1 113 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	tell_is_stackarg
.L27:
	.loc 1 114 0 is_stmt 1
	movl	$0, %eax
	call	get_di@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L28
	.loc 1 114 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	tell_is_stackarg
.L28:
	.loc 1 115 0 is_stmt 1
	movl	$0, %eax
	call	get_si@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L29
	.loc 1 115 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	tell_is_stackarg
.L29:
	.loc 1 116 0 is_stmt 1
	movl	$0, %eax
	call	get_dx@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L30
	.loc 1 116 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	tell_is_stackarg
.L30:
	.loc 1 117 0 is_stmt 1
	movl	$0, %eax
	call	get_cx@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L31
	.loc 1 117 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	tell_is_stackarg
.L31:
	.loc 1 118 0 is_stmt 1
	movl	$0, %eax
	call	get_r8@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L32
	.loc 1 118 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	tell_is_stackarg
.L32:
	.loc 1 119 0 is_stmt 1
	movl	$0, %eax
	call	get_r9@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L33
	.loc 1 119 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	tell_is_stackarg
.L33:
	.loc 1 120 0 is_stmt 1
	movl	$0, %eax
	call	get_ax@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L34
	.loc 1 120 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	tell_is_stackarg
.L34:
	.loc 1 121 0 is_stmt 1
	movl	$0, %eax
	call	get_bx@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L36
	.loc 1 121 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	tell_is_stackarg
.L36:
	.loc 1 122 0 is_stmt 1
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	scan_register, .-scan_register
	#.section	.rodata
	.align 8
.LC0:
	.string	"/home/xiaodo/c++/colang/src/gc/sweep.c"
.LC1:
	.string	"sp_start >= cur_sp"
	.text
	.globl	scan_stack
	.type	scan_stack, @function
scan_stack:
.LFB9:
	.loc 1 132 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	.loc 1 134 0
	movl	$0, %eax
	call	get_sp@PLT
	movq	%rax, -8(%rbp)
	.loc 1 136 0
	movq	sp_start(%rip), %rax
	cmpq	%rax, -8(%rbp)
	jbe	.L39
	.loc 1 136 0 is_stmt 0 discriminator 1
	leaq	__PRETTY_FUNCTION__.3377(%rip), %rcx
	movl	$136, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	call	__assert_fail@PLT
.L48:
.LBB7:
	.loc 1 140 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	.loc 1 141 0
	movq	-16(%rbp), %rax
	movq	%rax, -24(%rbp)
	.loc 1 142 0
	movq	-16(%rbp), %rax
	subq	$8, %rax
	movq	%rax, -32(%rbp)
	.loc 1 145 0
	movq	-16(%rbp), %rax
	andq	$-4096, %rax
	movq	%rax, -40(%rbp)
	.loc 1 146 0
	movq	arenas(%rip), %rax
	movq	(%rax), %rdx
	movq	-40(%rbp), %rax
	cmpq	%rax, %rdx
	ja	.L49
	.loc 1 146 0 is_stmt 0 discriminator 1
	movq	arenas(%rip), %rax
	movq	(%rax), %rax
	leaq	262144(%rax), %rdx
	movq	-40(%rbp), %rax
	cmpq	%rax, %rdx
	jb	.L49
	.loc 1 155 0 is_stmt 1
	movq	-40(%rbp), %rax
	movl	32(%rax), %edx
	movl	maxarenas(%rip), %eax
	cmpl	%eax, %edx
	jnb	.L50
	.loc 1 155 0 is_stmt 0 discriminator 1
	movq	-16(%rbp), %rdx
	movq	arenas(%rip), %rcx
	movq	-40(%rbp), %rax
	movl	32(%rax), %eax
	movl	%eax, %esi
	movq	%rsi, %rax
	salq	$3, %rax
	subq	%rsi, %rax
	salq	$3, %rax
	addq	%rcx, %rax
	movq	(%rax), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	cmpq	$262143, %rax
	ja	.L50
	.loc 1 155 0 discriminator 2
	movq	arenas(%rip), %rdx
	movq	-40(%rbp), %rax
	movl	32(%rax), %eax
	movl	%eax, %ecx
	movq	%rcx, %rax
	salq	$3, %rax
	subq	%rcx, %rax
	salq	$3, %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L50
	.loc 1 160 0 is_stmt 1
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jle	.L45
	.loc 1 160 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movl	(%rax), %eax
	cmpl	$3, %eax
	jle	.L46
.L45:
.LBB8:
	.loc 1 161 0 is_stmt 1
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	stringmark@PLT
	.loc 1 162 0
	jmp	.L42
.L46:
.LBE8:
	.loc 1 165 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L47
.LBB9:
	.loc 1 167 0
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	stringmark@PLT
.L47:
.LBE9:
	.loc 1 171 0
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	gc_mark
	cmpl	$10, %eax
	jne	.L42
	.loc 1 172 0
	movq	Hugmem(%rip), %rax
	movq	-16(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	mark@PLT
	jmp	.L42
.L49:
	.loc 1 147 0
	nop
	jmp	.L42
.L50:
	.loc 1 156 0
	nop
.L42:
.LBE7:
	.loc 1 139 0
	addq	$2, -8(%rbp)
.L39:
	.loc 1 139 0 is_stmt 0 discriminator 1
	movq	sp_start(%rip), %rax
	cmpq	%rax, -8(%rbp)
	jb	.L48
	.loc 1 175 0 is_stmt 1
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	scan_stack, .-scan_stack
	.globl	gc
	.type	gc, @function
gc:
.LFB10:
	.loc 1 180 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	.loc 1 182 0
	movl	$0, %eax
	call	scan_register
	.loc 1 183 0
	movl	$0, %eax
	call	scan_stack
	.loc 1 186 0
	call	gc_sweep
	.loc 1 187 0
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	gc, .-gc
	#.section	.rodata
	.align 8
	.type	__PRETTY_FUNCTION__.3377, @object
	.size	__PRETTY_FUNCTION__.3377, 11
__PRETTY_FUNCTION__.3377:
	.string	"scan_stack"
	.text
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
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x871
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF118
	.byte	0xc
	.long	.LASF119
	.long	.LASF120
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
	.long	.LASF121
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
	.long	.LASF122
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
	.uleb128 0x2
	.long	.LASF88
	.byte	0xb
	.byte	0x66
	.long	0x4d8
	.uleb128 0x8
	.long	.LASF89
	.byte	0x38
	.byte	0xb
	.byte	0x69
	.long	0x556
	.uleb128 0x9
	.long	.LASF90
	.byte	0xb
	.byte	0x6b
	.long	0x409
	.byte	0
	.uleb128 0x9
	.long	.LASF91
	.byte	0xb
	.byte	0x6e
	.long	0x45f
	.byte	0x8
	.uleb128 0x9
	.long	.LASF92
	.byte	0xb
	.byte	0x71
	.long	0x45f
	.byte	0x10
	.uleb128 0x9
	.long	.LASF93
	.byte	0xb
	.byte	0x74
	.long	0x4d
	.byte	0x18
	.uleb128 0x9
	.long	.LASF94
	.byte	0xb
	.byte	0x77
	.long	0x4d
	.byte	0x1c
	.uleb128 0x9
	.long	.LASF95
	.byte	0xb
	.byte	0x7a
	.long	0x4d8
	.byte	0x20
	.uleb128 0x9
	.long	.LASF96
	.byte	0xb
	.byte	0x7d
	.long	0x556
	.byte	0x28
	.uleb128 0x9
	.long	.LASF97
	.byte	0xb
	.byte	0x7e
	.long	0x556
	.byte	0x30
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x4e9
	.uleb128 0x10
	.long	.LASF98
	.byte	0xb
	.byte	0x80
	.long	0x556
	.uleb128 0x10
	.long	.LASF99
	.byte	0xb
	.byte	0x8c
	.long	0x4d
	.uleb128 0x10
	.long	.LASF100
	.byte	0xb
	.byte	0xa5
	.long	0x86
	.uleb128 0x10
	.long	.LASF101
	.byte	0xb
	.byte	0xb2
	.long	0x588
	.uleb128 0x6
	.byte	0x8
	.long	0x3fe
	.uleb128 0x8
	.long	.LASF102
	.byte	0x10
	.byte	0x1
	.byte	0x7c
	.long	0x5b3
	.uleb128 0x9
	.long	.LASF103
	.byte	0x1
	.byte	0x7e
	.long	0x69
	.byte	0
	.uleb128 0x9
	.long	.LASF104
	.byte	0x1
	.byte	0x7f
	.long	0x86
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF105
	.byte	0x1
	.byte	0x80
	.long	0x58e
	.uleb128 0x16
	.string	"gc"
	.byte	0x1
	.byte	0xb3
	.quad	.LFB10
	.quad	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x17
	.long	.LASF110
	.byte	0x1
	.byte	0x84
	.quad	.LFB9
	.quad	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.long	0x6aa
	.uleb128 0x18
	.long	.LASF106
	.byte	0x1
	.byte	0x86
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x19
	.long	.LASF108
	.long	0x6ba
	.uleb128 0x9
	.byte	0x3
	.quad	__PRETTY_FUNCTION__.3377
	.uleb128 0x1a
	.quad	.LBB7
	.quad	.LBE7-.LBB7
	.uleb128 0x1b
	.string	"ptr"
	.byte	0x1
	.byte	0x8c
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1b
	.string	"v"
	.byte	0x1
	.byte	0x8d
	.long	0x6bf
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1b
	.string	"hdr"
	.byte	0x1
	.byte	0x8e
	.long	0x4d2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x18
	.long	.LASF107
	.byte	0x1
	.byte	0x8f
	.long	0x4de
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1c
	.long	.LASF68
	.byte	0x1
	.byte	0x90
	.long	0x4d
	.uleb128 0x1d
	.quad	.LBB8
	.quad	.LBE8-.LBB8
	.long	0x689
	.uleb128 0x1e
	.long	.LASF109
	.byte	0x1
	.byte	0xa1
	.long	0x62
	.uleb128 0x1f
	.byte	0
	.byte	0
	.uleb128 0x1a
	.quad	.LBB9
	.quad	.LBE9-.LBB9
	.uleb128 0x1e
	.long	.LASF109
	.byte	0x1
	.byte	0xa1
	.long	0x62
	.uleb128 0x1f
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xc
	.long	0x95
	.long	0x6ba
	.uleb128 0xd
	.long	0x38
	.byte	0xa
	.byte	0
	.uleb128 0x7
	.long	0x6aa
	.uleb128 0x6
	.byte	0x8
	.long	0x5b3
	.uleb128 0x17
	.long	.LASF111
	.byte	0x1
	.byte	0x6c
	.quad	.LFB8
	.quad	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0x6f1
	.uleb128 0x1b
	.string	"reg"
	.byte	0x1
	.byte	0x6f
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x20
	.long	.LASF112
	.byte	0x1
	.byte	0x61
	.quad	.LFB7
	.quad	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x72b
	.uleb128 0x21
	.string	"arg"
	.byte	0x1
	.byte	0x61
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1b
	.string	"top"
	.byte	0x1
	.byte	0x62
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x20
	.long	.LASF113
	.byte	0x1
	.byte	0x3b
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0x800
	.uleb128 0x18
	.long	.LASF114
	.byte	0x1
	.byte	0x3e
	.long	0x556
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x18
	.long	.LASF107
	.byte	0x1
	.byte	0x3f
	.long	0x4de
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x18
	.long	.LASF68
	.byte	0x1
	.byte	0x40
	.long	0x4d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x1a
	.quad	.LBB3
	.quad	.LBE3-.LBB3
	.uleb128 0x1b
	.string	"p"
	.byte	0x1
	.byte	0x43
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1a
	.quad	.LBB4
	.quad	.LBE4-.LBB4
	.uleb128 0x18
	.long	.LASF115
	.byte	0x1
	.byte	0x47
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x18
	.long	.LASF116
	.byte	0x1
	.byte	0x48
	.long	0x86
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x1a
	.quad	.LBB5
	.quad	.LBE5-.LBB5
	.uleb128 0x1b
	.string	"pp"
	.byte	0x1
	.byte	0x49
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1a
	.quad	.LBB6
	.quad	.LBE6-.LBB6
	.uleb128 0x1b
	.string	"obj"
	.byte	0x1
	.byte	0x4b
	.long	0x4d2
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x22
	.long	.LASF117
	.byte	0x1
	.byte	0xa
	.long	0x62
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x21
	.string	"ptr"
	.byte	0x1
	.byte	0xa
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x18
	.long	.LASF107
	.byte	0x1
	.byte	0xe
	.long	0x4de
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x18
	.long	.LASF68
	.byte	0x1
	.byte	0xf
	.long	0x4d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1b
	.string	"hdr"
	.byte	0x1
	.byte	0x1d
	.long	0x4d2
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1a
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.uleb128 0x1b
	.string	"p"
	.byte	0x1
	.byte	0x2f
	.long	0x86
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
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
	.byte	0
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
	.uleb128 0x2116
	.uleb128 0x19
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
	.uleb128 0x19
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.uleb128 0x21
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
.LASF30:
	.string	"_shortbuf"
.LASF121:
	.string	"_IO_lock_t"
.LASF50:
	.string	"stderr"
.LASF115:
	.string	"start_addr"
.LASF19:
	.string	"_IO_buf_end"
.LASF59:
	.string	"optopt"
.LASF75:
	.string	"flags"
.LASF17:
	.string	"_IO_write_end"
.LASF3:
	.string	"unsigned int"
.LASF69:
	.string	"next"
.LASF100:
	.string	"sp_start"
.LASF89:
	.string	"arena_object"
.LASF11:
	.string	"_flags"
.LASF23:
	.string	"_markers"
.LASF91:
	.string	"first_address"
.LASF62:
	.string	"__timezone"
.LASF88:
	.string	"poolp"
.LASF71:
	.string	"list"
.LASF120:
	.string	"/home/xiaodo/c++/colang/tests/src/gc"
.LASF44:
	.string	"_pos"
.LASF49:
	.string	"stdout"
.LASF22:
	.string	"_IO_save_end"
.LASF58:
	.string	"opterr"
.LASF79:
	.string	"count"
.LASF54:
	.string	"long long unsigned int"
.LASF82:
	.string	"nextpool"
.LASF112:
	.string	"tell_is_stackarg"
.LASF52:
	.string	"sys_errlist"
.LASF21:
	.string	"_IO_backup_base"
.LASF32:
	.string	"_offset"
.LASF105:
	.string	"GCValue"
.LASF51:
	.string	"sys_nerr"
.LASF67:
	.string	"value"
.LASF25:
	.string	"_fileno"
.LASF92:
	.string	"pool_address"
.LASF7:
	.string	"size_t"
.LASF14:
	.string	"_IO_read_base"
.LASF48:
	.string	"stdin"
.LASF42:
	.string	"_next"
.LASF109:
	.string	"stringmark"
.LASF95:
	.string	"freepools"
.LASF10:
	.string	"char"
.LASF86:
	.string	"nextoffset"
.LASF38:
	.string	"_mode"
.LASF61:
	.string	"__daylight"
.LASF63:
	.string	"tzname"
.LASF41:
	.string	"_IO_marker"
.LASF12:
	.string	"_IO_read_ptr"
.LASF104:
	.string	"data"
.LASF114:
	.string	"area"
.LASF85:
	.string	"szidx"
.LASF96:
	.string	"nextarena"
.LASF15:
	.string	"_IO_write_base"
.LASF45:
	.string	"_IO_2_1_stdin_"
.LASF53:
	.string	"long long int"
.LASF46:
	.string	"_IO_2_1_stdout_"
.LASF20:
	.string	"_IO_save_base"
.LASF70:
	.string	"ListNode"
.LASF118:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -fno-builtin"
.LASF68:
	.string	"size"
.LASF57:
	.string	"optind"
.LASF78:
	.string	"_padding"
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
.LASF107:
	.string	"pool"
.LASF29:
	.string	"_vtable_offset"
.LASF56:
	.string	"optarg"
.LASF87:
	.string	"maxnextoffset"
.LASF65:
	.string	"timezone"
.LASF101:
	.string	"Hugmem"
.LASF72:
	.string	"root"
.LASF102:
	.string	"gc_value"
.LASF13:
	.string	"_IO_read_end"
.LASF74:
	.string	"Co_uintptr_t"
.LASF5:
	.string	"short int"
.LASF6:
	.string	"long int"
.LASF97:
	.string	"prevarena"
.LASF83:
	.string	"prevpool"
.LASF93:
	.string	"nfreepools"
.LASF73:
	.string	"List"
.LASF55:
	.string	"__environ"
.LASF77:
	.string	"block"
.LASF117:
	.string	"gc_mark"
.LASF122:
	.string	"_IO_FILE_plus"
.LASF106:
	.string	"cur_sp"
.LASF31:
	.string	"_lock"
.LASF116:
	.string	"end_addr"
.LASF0:
	.string	"long unsigned int"
.LASF90:
	.string	"address"
.LASF27:
	.string	"_old_offset"
.LASF40:
	.string	"_IO_FILE"
.LASF99:
	.string	"maxarenas"
.LASF66:
	.string	"link_list"
.LASF103:
	.string	"type"
.LASF1:
	.string	"unsigned char"
.LASF60:
	.string	"__tzname"
.LASF43:
	.string	"_sbuf"
.LASF16:
	.string	"_IO_write_ptr"
.LASF110:
	.string	"scan_stack"
.LASF76:
	.string	"addr"
.LASF80:
	.string	"pool_header"
.LASF64:
	.string	"daylight"
.LASF8:
	.string	"__off_t"
.LASF98:
	.string	"arenas"
.LASF4:
	.string	"signed char"
.LASF2:
	.string	"short unsigned int"
.LASF113:
	.string	"gc_sweep"
.LASF108:
	.string	"__PRETTY_FUNCTION__"
.LASF94:
	.string	"ntotalpools"
.LASF81:
	.string	"freeblock"
.LASF24:
	.string	"_chain"
.LASF111:
	.string	"scan_register"
.LASF26:
	.string	"_flags2"
.LASF119:
	.string	"/home/xiaodo/c++/colang/src/gc/sweep.c"
.LASF28:
	.string	"_cur_column"
.LASF47:
	.string	"_IO_2_1_stderr_"
.LASF9:
	.string	"__off64_t"
.LASF39:
	.string	"_unused2"
.LASF18:
	.string	"_IO_buf_base"
.LASF84:
	.string	"arenaindex"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

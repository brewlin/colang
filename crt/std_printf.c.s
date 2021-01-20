	.file	"printf.c"
	.text
.Ltext0:
	.globl	__fputc_tmp_val__
	#.bss
	.data
	.type	__fputc_tmp_val__, @object
	.size	__fputc_tmp_val__, 1
__fputc_tmp_val__:
	.zero	1
	.text
	.globl	fputc
	.type	fputc, @function
fputc:
.LFB0:
	.file 1 "/home/xiaodo/c++/colang/src/crt/printf.c"
	.loc 1 5 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, %eax
	movq	%rsi, -16(%rbp)
	movb	%al, -4(%rbp)
	.loc 1 7 0
	movzbl	-4(%rbp), %eax
	movb	%al, __fputc_tmp_val__(%rip)
	.loc 1 8 0
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	movl	$1, %edx
	movl	$1, %esi
	leaq	__fputc_tmp_val__(%rip), %rdi
	call	fwrite@PLT
	cmpq	$1, %rax
	je	.L2
	.loc 1 10 0
	movq	$-1, %rax
	jmp	.L3
.L2:
	.loc 1 14 0
	movsbq	-4(%rbp), %rax
.L3:
	.loc 1 16 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	fputc, .-fputc
	.globl	putchar
	.type	putchar, @function
putchar:
.LFB1:
	.loc 1 17 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	.loc 1 18 0
	movl	-4(%rbp), %eax
	movsbl	%al, %eax
	movl	$1, %esi
	movl	%eax, %edi
	call	fputc
	.loc 1 19 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	putchar, .-putchar
	.globl	puts
	.type	puts, @function
puts:
.LFB2:
	.loc 1 20 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	.loc 1 21 0
	movq	-8(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	fputs
	.loc 1 22 0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	puts, .-puts
	.globl	__fputs_tmp_array__
	#.bss
	.data
	.align 32
	.type	__fputs_tmp_array__, @object
	.size	__fputs_tmp_array__, 256
__fputs_tmp_array__:
	.zero	256
	.globl	__fputs_tmp_size__
	.data
	.align 4
	.type	__fputs_tmp_size__, @object
	.size	__fputs_tmp_size__, 4
__fputs_tmp_size__:
	.long	256
	.text
	.globl	fputs
	.type	fputs, @function
fputs:
.LFB3:
	.loc 1 27 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 1 30 0
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, -8(%rbp)
	.loc 1 31 0
	movl	__fputs_tmp_size__(%rip), %eax
	cltq
	cmpq	%rax, -8(%rbp)
	jl	.L7
	.loc 1 32 0
	movq	$-1, %rax
	jmp	.L8
.L7:
	.loc 1 33 0
	movq	-24(%rbp), %rax
	movq	%rax, %rsi
	leaq	__fputs_tmp_array__(%rip), %rdi
	call	strcpy@PLT
	.loc 1 34 0
	movq	-32(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	movq	%rax, %rdx
	movl	$1, %esi
	leaq	__fputs_tmp_array__(%rip), %rdi
	call	fwrite@PLT
	cmpq	%rax, -8(%rbp)
	je	.L9
	.loc 1 36 0
	movq	$-1, %rax
	jmp	.L8
.L9:
	.loc 1 40 0
	movq	-8(%rbp), %rax
.L8:
	.loc 1 42 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	fputs, .-fputs
	.globl	vfprintf
	.type	vfprintf, @function
vfprintf:
.LFB4:
	.loc 1 47 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	.loc 1 48 0
	movq	$0, -8(%rbp)
	.loc 1 49 0
	movq	$0, -16(%rbp)
	.loc 1 50 0
	movq	$0, -24(%rbp)
	.loc 1 51 0
	movq	-64(%rbp), %rax
	movq	%rax, -24(%rbp)
	jmp	.L11
.L31:
	.loc 1 53 0
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	cmpl	$100, %eax
	je	.L13
	cmpl	$115, %eax
	je	.L14
	cmpl	$37, %eax
	jne	.L32
	.loc 1 56 0
	cmpq	$0, -8(%rbp)
	jne	.L16
	.loc 1 58 0
	movq	$1, -8(%rbp)
	.loc 1 69 0
	jmp	.L20
.L16:
	.loc 1 62 0
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movl	$37, %edi
	call	fputc
	testq	%rax, %rax
	jns	.L18
	.loc 1 64 0
	movq	$-1, %rax
	jmp	.L19
.L18:
	.loc 1 66 0
	addq	$1, -16(%rbp)
	.loc 1 67 0
	movq	$0, -8(%rbp)
	.loc 1 69 0
	jmp	.L20
.L13:
	.loc 1 72 0
	cmpq	$0, -8(%rbp)
	je	.L21
.LBB2:
	.loc 1 75 0
	movq	$0, -8(%rbp)
	.loc 1 76 0
	addq	$8, -72(%rbp)
	movq	-72(%rbp), %rax
	subq	$8, %rax
	movq	(%rax), %rax
	leaq	-48(%rbp), %rcx
	movl	$10, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	itoa@PLT
	.loc 1 77 0
	movq	-56(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fputs
	testq	%rax, %rax
	jns	.L22
	.loc 1 79 0
	movq	$-1, %rax
	jmp	.L19
.L22:
	.loc 1 81 0
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
.LBE2:
	.loc 1 91 0
	jmp	.L20
.L21:
	.loc 1 83 0
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movl	$100, %edi
	call	fputc
	testq	%rax, %rax
	jns	.L24
	.loc 1 85 0
	movq	$-1, %rax
	jmp	.L19
.L24:
	.loc 1 89 0
	addq	$1, -16(%rbp)
	.loc 1 91 0
	jmp	.L20
.L14:
	.loc 1 94 0
	cmpq	$0, -8(%rbp)
	je	.L25
.LBB3:
	.loc 1 96 0
	addq	$8, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	-8(%rax), %rax
	movq	%rax, -32(%rbp)
	.loc 1 98 0
	movq	$0, -8(%rbp)
	.loc 1 99 0
	movq	-56(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fputs
	testq	%rax, %rax
	jns	.L26
	.loc 1 101 0
	movq	$-1, %rax
	jmp	.L19
.L26:
	.loc 1 103 0
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	addq	%rdx, %rax
	movq	%rax, -16(%rbp)
.LBE3:
	.loc 1 114 0
	jmp	.L20
.L25:
	.loc 1 105 0
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movl	$115, %edi
	call	fputc
	testq	%rax, %rax
	jns	.L28
	.loc 1 107 0
	movq	$-1, %rax
	jmp	.L19
.L28:
	.loc 1 111 0
	addq	$1, -16(%rbp)
	.loc 1 114 0
	jmp	.L20
.L32:
	.loc 1 117 0
	cmpq	$0, -8(%rbp)
	je	.L29
	.loc 1 119 0
	movq	$0, -8(%rbp)
.L29:
	.loc 1 121 0
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movq	-56(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fputc
	testq	%rax, %rax
	jns	.L30
	.loc 1 123 0
	movq	$-1, %rax
	jmp	.L19
.L30:
	.loc 1 127 0
	addq	$1, -16(%rbp)
	.loc 1 130 0
	nop
.L20:
	.loc 1 51 0 discriminator 2
	addq	$1, -24(%rbp)
.L11:
	.loc 1 51 0 is_stmt 0 discriminator 1
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L31
	.loc 1 133 0 is_stmt 1
	movq	-16(%rbp), %rax
.L19:
	.loc 1 134 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	vfprintf, .-vfprintf
	.globl	_vsnprintf
	.type	_vsnprintf, @function
_vsnprintf:
.LFB5:
	.loc 1 143 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%rdx, -88(%rbp)
	.loc 1 144 0
	movq	$0, -8(%rbp)
	.loc 1 145 0
	movq	$0, -16(%rbp)
	.loc 1 146 0
	movq	$0, -24(%rbp)
	.loc 1 147 0
	movl	$0, -28(%rbp)
	.loc 1 148 0
	movq	-80(%rbp), %rax
	movq	%rax, -24(%rbp)
	jmp	.L34
.L48:
	.loc 1 150 0
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	cmpl	$100, %eax
	je	.L36
	cmpl	$115, %eax
	je	.L37
	cmpl	$37, %eax
	jne	.L50
	.loc 1 153 0
	cmpq	$0, -8(%rbp)
	jne	.L39
	.loc 1 155 0
	movq	$1, -8(%rbp)
	.loc 1 163 0
	jmp	.L41
.L39:
	.loc 1 159 0
	movl	-28(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -28(%rbp)
	movslq	%eax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movb	$37, (%rax)
	.loc 1 160 0
	addq	$1, -16(%rbp)
	.loc 1 161 0
	movq	$0, -8(%rbp)
	.loc 1 163 0
	jmp	.L41
.L36:
	.loc 1 166 0
	cmpq	$0, -8(%rbp)
	je	.L42
.LBB4:
	.loc 1 169 0
	movq	$0, -8(%rbp)
	.loc 1 170 0
	addq	$8, -88(%rbp)
	movq	-88(%rbp), %rax
	subq	$8, %rax
	movq	(%rax), %rax
	leaq	-64(%rbp), %rcx
	movl	$10, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	itoa@PLT
	.loc 1 171 0
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, -48(%rbp)
	.loc 1 172 0
	leaq	-64(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
	.loc 1 173 0
	movl	-48(%rbp), %eax
	addl	%eax, -28(%rbp)
	.loc 1 174 0
	movl	-48(%rbp), %eax
	cltq
	addq	%rax, -16(%rbp)
.LBE4:
	.loc 1 180 0
	jmp	.L41
.L42:
	.loc 1 177 0
	movl	-28(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -28(%rbp)
	movslq	%eax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movb	$100, (%rax)
	.loc 1 178 0
	addq	$1, -16(%rbp)
	.loc 1 180 0
	jmp	.L41
.L37:
	.loc 1 183 0
	cmpq	$0, -8(%rbp)
	je	.L44
.LBB5:
	.loc 1 185 0
	addq	$8, -88(%rbp)
	movq	-88(%rbp), %rax
	movq	-8(%rax), %rax
	movq	%rax, -40(%rbp)
	.loc 1 187 0
	movq	$0, -8(%rbp)
	.loc 1 188 0
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	strlen@PLT
	movl	%eax, -44(%rbp)
	.loc 1 189 0
	movq	-40(%rbp), %rdx
	movq	-72(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat@PLT
	.loc 1 190 0
	movl	-44(%rbp), %eax
	addl	%eax, -28(%rbp)
	.loc 1 192 0
	movl	-44(%rbp), %eax
	cltq
	addq	%rax, -16(%rbp)
.LBE5:
	.loc 1 199 0
	jmp	.L41
.L44:
	.loc 1 195 0
	movl	-28(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -28(%rbp)
	movslq	%eax, %rdx
	movq	-72(%rbp), %rax
	addq	%rdx, %rax
	movb	$115, (%rax)
	.loc 1 196 0
	addq	$1, -16(%rbp)
	.loc 1 199 0
	jmp	.L41
.L50:
	.loc 1 202 0
	cmpq	$0, -8(%rbp)
	je	.L46
	.loc 1 204 0
	movq	$0, -8(%rbp)
	.loc 1 211 0
	jmp	.L51
.L46:
	.loc 1 207 0
	movl	-28(%rbp), %eax
	leal	1(%rax), %edx
	movl	%edx, -28(%rbp)
	movslq	%eax, %rdx
	movq	-72(%rbp), %rax
	addq	%rax, %rdx
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, (%rdx)
	.loc 1 208 0
	addq	$1, -16(%rbp)
.L51:
	.loc 1 211 0
	nop
.L41:
	.loc 1 148 0 discriminator 2
	addq	$1, -24(%rbp)
.L34:
	.loc 1 148 0 is_stmt 0 discriminator 1
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L48
	.loc 1 214 0 is_stmt 1
	movq	-16(%rbp), %rax
	.loc 1 215 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	_vsnprintf, .-_vsnprintf
	.globl	printf
	.type	printf, @function
printf:
.LFB6:
	.loc 1 217 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movq	%rdi, -200(%rbp)
	movq	%rsi, -168(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -152(%rbp)
	movq	%r8, -144(%rbp)
	movq	%r9, -136(%rbp)
	testb	%al, %al
	je	.L55
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm1, -112(%rbp)
	movaps	%xmm2, -96(%rbp)
	movaps	%xmm3, -80(%rbp)
	movaps	%xmm4, -64(%rbp)
	movaps	%xmm5, -48(%rbp)
	movaps	%xmm6, -32(%rbp)
	movaps	%xmm7, -16(%rbp)
.L55:
	.loc 1 219 0
#APP
# 219 "/home/xiaodo/c++/colang/src/crt/printf.c" 1
	movq %rbp,%rax
# 0 "" 2
#NO_APP
	movq	%rax, -184(%rbp)
	.loc 1 220 0
	subq	$168, -184(%rbp)
	.loc 1 221 0
	movq	-184(%rbp), %rdx
	movq	-200(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	vfprintf
	.loc 1 222 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	printf, .-printf
	.globl	vsnprintf
	.type	vsnprintf, @function
vsnprintf:
.LFB7:
	.loc 1 224 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movq	%rdi, -200(%rbp)
	movq	%rsi, -208(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -152(%rbp)
	movq	%r8, -144(%rbp)
	movq	%r9, -136(%rbp)
	testb	%al, %al
	je	.L59
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm1, -112(%rbp)
	movaps	%xmm2, -96(%rbp)
	movaps	%xmm3, -80(%rbp)
	movaps	%xmm4, -64(%rbp)
	movaps	%xmm5, -48(%rbp)
	movaps	%xmm6, -32(%rbp)
	movaps	%xmm7, -16(%rbp)
.L59:
	.loc 1 226 0
#APP
# 226 "/home/xiaodo/c++/colang/src/crt/printf.c" 1
	movq %rbp,%rax
# 0 "" 2
#NO_APP
	movq	%rax, -184(%rbp)
	.loc 1 227 0
	subq	$160, -184(%rbp)
	.loc 1 228 0
	movq	-184(%rbp), %rdx
	movq	-208(%rbp), %rcx
	movq	-200(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	_vsnprintf
	.loc 1 229 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	vsnprintf, .-vsnprintf
	.globl	fprintf
	.type	fprintf, @function
fprintf:
.LFB8:
	.loc 1 232 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movq	%rdi, -200(%rbp)
	movq	%rsi, -208(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -152(%rbp)
	movq	%r8, -144(%rbp)
	movq	%r9, -136(%rbp)
	testb	%al, %al
	je	.L63
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm1, -112(%rbp)
	movaps	%xmm2, -96(%rbp)
	movaps	%xmm3, -80(%rbp)
	movaps	%xmm4, -64(%rbp)
	movaps	%xmm5, -48(%rbp)
	movaps	%xmm6, -32(%rbp)
	movaps	%xmm7, -16(%rbp)
.L63:
	.loc 1 234 0
#APP
# 234 "/home/xiaodo/c++/colang/src/crt/printf.c" 1
	movq %rbp,%rax
# 0 "" 2
#NO_APP
	movq	%rax, -184(%rbp)
	.loc 1 235 0
	subq	$168, -184(%rbp)
	.loc 1 236 0
	movq	-184(%rbp), %rdx
	movq	-208(%rbp), %rcx
	movq	-200(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	vfprintf
	.loc 1 237 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	fprintf, .-fprintf
.Letext0:
	.file 2 "/home/xiaodo/c++/colang/src/crt/minicrt.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x430
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF20
	.byte	0xc
	.long	.LASF21
	.long	.LASF22
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF23
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
	.long	.LASF4
	.byte	0x1
	.byte	0x3
	.long	0x5b
	.uleb128 0x9
	.byte	0x3
	.quad	__fputc_tmp_val__
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF2
	.uleb128 0x5
	.long	0x5b
	.uleb128 0x6
	.long	0x5b
	.long	0x77
	.uleb128 0x7
	.long	0x77
	.byte	0xff
	.byte	0
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF3
	.uleb128 0x4
	.long	.LASF5
	.byte	0x1
	.byte	0x18
	.long	0x67
	.uleb128 0x9
	.byte	0x3
	.quad	__fputs_tmp_array__
	.uleb128 0x4
	.long	.LASF6
	.byte	0x1
	.byte	0x19
	.long	0xa8
	.uleb128 0x9
	.byte	0x3
	.quad	__fputs_tmp_size__
	.uleb128 0x8
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x9
	.long	.LASF9
	.byte	0x1
	.byte	0xe7
	.long	0x38
	.quad	.LFB8
	.quad	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0xff
	.uleb128 0xa
	.long	.LASF7
	.byte	0x1
	.byte	0xe7
	.long	0xff
	.uleb128 0x3
	.byte	0x91
	.sleb128 -216
	.uleb128 0xa
	.long	.LASF8
	.byte	0x1
	.byte	0xe7
	.long	0x105
	.uleb128 0x3
	.byte	0x91
	.sleb128 -224
	.uleb128 0xb
	.uleb128 0xc
	.long	.LASF12
	.byte	0x1
	.byte	0xe9
	.long	0x10b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -200
	.byte	0
	.uleb128 0xd
	.byte	0x8
	.long	0x2d
	.uleb128 0xd
	.byte	0x8
	.long	0x62
	.uleb128 0xd
	.byte	0x8
	.long	0x5b
	.uleb128 0x9
	.long	.LASF10
	.byte	0x1
	.byte	0xdf
	.long	0x38
	.quad	.LFB7
	.quad	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x161
	.uleb128 0xa
	.long	.LASF11
	.byte	0x1
	.byte	0xdf
	.long	0x10b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -216
	.uleb128 0xa
	.long	.LASF8
	.byte	0x1
	.byte	0xdf
	.long	0x105
	.uleb128 0x3
	.byte	0x91
	.sleb128 -224
	.uleb128 0xb
	.uleb128 0xc
	.long	.LASF12
	.byte	0x1
	.byte	0xe1
	.long	0x10b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -200
	.byte	0
	.uleb128 0x9
	.long	.LASF13
	.byte	0x1
	.byte	0xd8
	.long	0x38
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0x1a2
	.uleb128 0xa
	.long	.LASF8
	.byte	0x1
	.byte	0xd8
	.long	0x105
	.uleb128 0x3
	.byte	0x91
	.sleb128 -216
	.uleb128 0xb
	.uleb128 0xc
	.long	.LASF12
	.byte	0x1
	.byte	0xda
	.long	0x10b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -200
	.byte	0
	.uleb128 0x9
	.long	.LASF14
	.byte	0x1
	.byte	0x8e
	.long	0x38
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.long	0x286
	.uleb128 0xa
	.long	.LASF11
	.byte	0x1
	.byte	0x8e
	.long	0x10b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0xa
	.long	.LASF8
	.byte	0x1
	.byte	0x8e
	.long	0x105
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0xa
	.long	.LASF12
	.byte	0x1
	.byte	0x8e
	.long	0x10b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0xc
	.long	.LASF15
	.byte	0x1
	.byte	0x90
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xe
	.string	"ret"
	.byte	0x1
	.byte	0x91
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xe
	.string	"p"
	.byte	0x1
	.byte	0x92
	.long	0x105
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xe
	.string	"i"
	.byte	0x1
	.byte	0x93
	.long	0xa8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0xf
	.quad	.LBB4
	.quad	.LBE4-.LBB4
	.long	0x257
	.uleb128 0xe
	.string	"buf"
	.byte	0x1
	.byte	0xa8
	.long	0x286
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0xe
	.string	"len"
	.byte	0x1
	.byte	0xab
	.long	0xa8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.uleb128 0x10
	.quad	.LBB5
	.quad	.LBE5-.LBB5
	.uleb128 0xe
	.string	"str"
	.byte	0x1
	.byte	0xb9
	.long	0x105
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0xe
	.string	"len"
	.byte	0x1
	.byte	0xbc
	.long	0xa8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.byte	0
	.byte	0
	.uleb128 0x6
	.long	0x5b
	.long	0x296
	.uleb128 0x7
	.long	0x77
	.byte	0xf
	.byte	0
	.uleb128 0x9
	.long	.LASF16
	.byte	0x1
	.byte	0x2e
	.long	0x38
	.quad	.LFB4
	.quad	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.long	0x351
	.uleb128 0xa
	.long	.LASF7
	.byte	0x1
	.byte	0x2e
	.long	0xff
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0xa
	.long	.LASF8
	.byte	0x1
	.byte	0x2e
	.long	0x105
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0xa
	.long	.LASF12
	.byte	0x1
	.byte	0x2e
	.long	0x10b
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0xc
	.long	.LASF15
	.byte	0x1
	.byte	0x30
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0xe
	.string	"ret"
	.byte	0x1
	.byte	0x31
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0xe
	.string	"p"
	.byte	0x1
	.byte	0x32
	.long	0x105
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xf
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.long	0x330
	.uleb128 0xe
	.string	"buf"
	.byte	0x1
	.byte	0x4a
	.long	0x286
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.byte	0
	.uleb128 0x10
	.quad	.LBB3
	.quad	.LBE3-.LBB3
	.uleb128 0xe
	.string	"str"
	.byte	0x1
	.byte	0x60
	.long	0x105
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.byte	0
	.byte	0
	.uleb128 0x9
	.long	.LASF17
	.byte	0x1
	.byte	0x1a
	.long	0x38
	.quad	.LFB3
	.quad	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x39d
	.uleb128 0x11
	.string	"str"
	.byte	0x1
	.byte	0x1a
	.long	0x105
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xa
	.long	.LASF7
	.byte	0x1
	.byte	0x1a
	.long	0xff
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0xe
	.string	"len"
	.byte	0x1
	.byte	0x1e
	.long	0x38
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x9
	.long	.LASF18
	.byte	0x1
	.byte	0x14
	.long	0x38
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x3cd
	.uleb128 0x11
	.string	"str"
	.byte	0x1
	.byte	0x14
	.long	0x105
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x9
	.long	.LASF19
	.byte	0x1
	.byte	0x11
	.long	0x38
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x3fb
	.uleb128 0x11
	.string	"c"
	.byte	0x1
	.byte	0x11
	.long	0xa8
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x12
	.long	.LASF24
	.byte	0x1
	.byte	0x4
	.long	0x38
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x11
	.string	"c"
	.byte	0x1
	.byte	0x4
	.long	0x5b
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0xa
	.long	.LASF7
	.byte	0x1
	.byte	0x4
	.long	0xff
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
	.uleb128 0x5
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0xb
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0xd
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x10
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x11
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
.LASF18:
	.string	"puts"
.LASF6:
	.string	"__fputs_tmp_size__"
.LASF10:
	.string	"vsnprintf"
.LASF24:
	.string	"fputc"
.LASF9:
	.string	"fprintf"
.LASF19:
	.string	"putchar"
.LASF3:
	.string	"long unsigned int"
.LASF14:
	.string	"_vsnprintf"
.LASF21:
	.string	"/home/xiaodo/c++/colang/src/crt/printf.c"
.LASF17:
	.string	"fputs"
.LASF11:
	.string	"dstr"
.LASF1:
	.string	"unsigned char"
.LASF2:
	.string	"char"
.LASF7:
	.string	"stream"
.LASF4:
	.string	"__fputc_tmp_val__"
.LASF0:
	.string	"long int"
.LASF16:
	.string	"vfprintf"
.LASF22:
	.string	"/home/xiaodo/c++/colang/tests/src/crt"
.LASF5:
	.string	"__fputs_tmp_array__"
.LASF8:
	.string	"format"
.LASF23:
	.string	"FILE"
.LASF13:
	.string	"printf"
.LASF20:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -g -fno-builtin"
.LASF12:
	.string	"arglist"
.LASF15:
	.string	"translating"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

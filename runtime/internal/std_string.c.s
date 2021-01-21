	.file	"string.c"
	.text
.Ltext0:
	.globl	itoa
	.type	itoa, @function
itoa:
.LFB0:
	.file 1 "/home/xiaodo/c++/colang/src/crt/string.c"
	.loc 1 3 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%rdx, -88(%rbp)
	.loc 1 4 0
	movabsq	$3978425819141910832, %rax
	movabsq	$5063528411713059128, %rdx
	movq	%rax, -64(%rbp)
	movq	%rdx, -56(%rbp)
	movabsq	$5642249794417674311, %rax
	movabsq	$6220971177122287695, %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$1515804759, -32(%rbp)
	movb	$0, -28(%rbp)
	.loc 1 5 0
	movq	-80(%rbp), %rax
	movq	%rax, -8(%rbp)
	.loc 1 6 0
	movq	-80(%rbp), %rax
	movq	%rax, -16(%rbp)
	.loc 1 7 0
	cmpq	$0, -8(%rbp)
	je	.L2
	.loc 1 7 0 is_stmt 0 discriminator 1
	cmpq	$1, -88(%rbp)
	jle	.L2
	.loc 1 7 0 discriminator 2
	cmpq	$36, -88(%rbp)
	jle	.L3
.L2:
	.loc 1 9 0 is_stmt 1
	movq	-8(%rbp), %rax
	jmp	.L12
.L3:
	.loc 1 12 0
	cmpq	$10, -88(%rbp)
	je	.L5
	.loc 1 12 0 is_stmt 0 discriminator 1
	cmpq	$0, -72(%rbp)
	jns	.L5
	.loc 1 14 0 is_stmt 1
	movq	-8(%rbp), %rax
	jmp	.L12
.L5:
	.loc 1 17 0
	cmpq	$0, -72(%rbp)
	jne	.L6
	.loc 1 19 0
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movb	$48, (%rax)
	.loc 1 20 0
	movq	-8(%rbp), %rax
	movb	$0, (%rax)
	.loc 1 21 0
	movq	-8(%rbp), %rax
	jmp	.L12
.L6:
	.loc 1 24 0
	cmpq	$10, -88(%rbp)
	jne	.L8
	.loc 1 24 0 is_stmt 0 discriminator 1
	cmpq	$0, -72(%rbp)
	jns	.L8
	.loc 1 26 0 is_stmt 1
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movb	$45, (%rax)
	.loc 1 27 0
	negq	-72(%rbp)
	.loc 1 30 0
	jmp	.L8
.L9:
	.loc 1 32 0
	movq	-72(%rbp), %rax
	cqto
	idivq	-88(%rbp)
	movq	%rdx, %rcx
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movzbl	-64(%rbp,%rcx), %edx
	movb	%dl, (%rax)
	.loc 1 33 0
	movq	-72(%rbp), %rax
	cqto
	idivq	-88(%rbp)
	movq	%rax, -72(%rbp)
.L8:
	.loc 1 30 0
	cmpq	$0, -72(%rbp)
	jne	.L9
	.loc 1 36 0
	movq	-8(%rbp), %rax
	movb	$0, (%rax)
	.loc 1 37 0
	subq	$1, -8(%rbp)
	jmp	.L10
.L11:
.LBB2:
	.loc 1 39 0 discriminator 3
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -17(%rbp)
	.loc 1 40 0 discriminator 3
	movq	-8(%rbp), %rax
	movzbl	(%rax), %edx
	movq	-16(%rbp), %rax
	movb	%dl, (%rax)
	.loc 1 41 0 discriminator 3
	movq	-8(%rbp), %rax
	movzbl	-17(%rbp), %edx
	movb	%dl, (%rax)
.LBE2:
	.loc 1 37 0 discriminator 3
	addq	$1, -16(%rbp)
	subq	$1, -8(%rbp)
.L10:
	.loc 1 37 0 is_stmt 0 discriminator 1
	movq	-16(%rbp), %rax
	cmpq	-8(%rbp), %rax
	jb	.L11
	.loc 1 44 0 is_stmt 1
	movq	-80(%rbp), %rax
.L12:
	.loc 1 45 0 discriminator 1
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	itoa, .-itoa
	.globl	strcmp
	.type	strcmp, @function
strcmp:
.LFB1:
	.loc 1 48 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	.loc 1 49 0
	movq	$0, -8(%rbp)
	.loc 1 50 0
	movq	-40(%rbp), %rax
	movq	%rax, -16(%rbp)
	.loc 1 51 0
	movq	-48(%rbp), %rax
	movq	%rax, -24(%rbp)
	.loc 1 53 0
	jmp	.L14
.L16:
	.loc 1 54 0
	addq	$1, -16(%rbp)
	addq	$1, -24(%rbp)
.L14:
	.loc 1 53 0
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %edx
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	cltq
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L15
	.loc 1 53 0 is_stmt 0 discriminator 1
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L16
.L15:
	.loc 1 55 0 is_stmt 1
	cmpq	$0, -8(%rbp)
	jns	.L17
	.loc 1 57 0
	movq	$-1, -8(%rbp)
	jmp	.L18
.L17:
	.loc 1 59 0
	cmpq	$0, -8(%rbp)
	jle	.L18
	.loc 1 61 0
	movq	$1, -8(%rbp)
.L18:
	.loc 1 64 0
	movq	-8(%rbp), %rax
	.loc 1 65 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	strcmp, .-strcmp
	.globl	strchr
	.type	strchr, @function
strchr:
.LFB2:
	.loc 1 73 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -72(%rbp)
	movl	%esi, -76(%rbp)
	.loc 1 79 0
	movl	-76(%rbp), %eax
	movb	%al, -17(%rbp)
	.loc 1 83 0
	movq	-72(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L21
.L25:
	.loc 1 86 0
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, -17(%rbp)
	jne	.L22
	.loc 1 87 0
	movq	-8(%rbp), %rax
	jmp	.L23
.L22:
	.loc 1 88 0
	movq	-8(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L24
	.loc 1 89 0
	movl	$0, %eax
	jmp	.L23
.L24:
	.loc 1 85 0
	addq	$1, -8(%rbp)
.L21:
	.loc 1 84 0 discriminator 1
	movq	-8(%rbp), %rax
	andl	$7, %eax
	.loc 1 83 0 discriminator 1
	testq	%rax, %rax
	jne	.L25
	.loc 1 91 0
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
.LBB3:
	.loc 1 96 0
	movabsq	$9151031864016699135, %rax
	movq	%rax, -32(%rbp)
	nop
.LBE3:
	.loc 1 102 0
	movzbl	-17(%rbp), %eax
	movzbl	-17(%rbp), %edx
	sall	$8, %edx
	orl	%edx, %eax
	cltq
	movq	%rax, -40(%rbp)
	.loc 1 103 0
	movq	-40(%rbp), %rax
	salq	$16, %rax
	orq	%rax, -40(%rbp)
	.loc 1 106 0
	movq	-40(%rbp), %rax
	salq	$32, %rax
	orq	%rax, -40(%rbp)
.L43:
	.loc 1 114 0
	movq	-16(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -16(%rbp)
	movq	(%rax), %rax
	movq	%rax, -48(%rbp)
	.loc 1 117 0
	movq	-48(%rbp), %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	.loc 1 120 0
	movq	-48(%rbp), %rax
	notq	%rax
	xorq	%rax, %rdx
	.loc 1 125 0
	movq	-32(%rbp), %rax
	notq	%rax
	andq	%rdx, %rax
	.loc 1 117 0
	testq	%rax, %rax
	jne	.L26
	.loc 1 128 0
	movq	-48(%rbp), %rax
	xorq	-40(%rbp), %rax
	movq	%rax, %rdx
	movq	-32(%rbp), %rax
	addq	%rax, %rdx
	movq	-48(%rbp), %rax
	xorq	-40(%rbp), %rax
	notq	%rax
	xorq	%rax, %rdx
	.loc 1 129 0
	movq	-32(%rbp), %rax
	notq	%rax
	andq	%rdx, %rax
	.loc 1 125 0
	testq	%rax, %rax
	je	.L43
.L26:
.LBB4:
	.loc 1 134 0
	movq	-16(%rbp), %rax
	subq	$8, %rax
	movq	%rax, -56(%rbp)
	.loc 1 136 0
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, -17(%rbp)
	jne	.L28
	.loc 1 137 0
	movq	-56(%rbp), %rax
	jmp	.L23
.L28:
	.loc 1 138 0
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L29
	.loc 1 139 0
	movl	$0, %eax
	jmp	.L23
.L29:
	.loc 1 140 0
	addq	$1, -56(%rbp)
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, -17(%rbp)
	jne	.L30
	.loc 1 141 0
	movq	-56(%rbp), %rax
	jmp	.L23
.L30:
	.loc 1 142 0
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L31
	.loc 1 143 0
	movl	$0, %eax
	jmp	.L23
.L31:
	.loc 1 144 0
	addq	$1, -56(%rbp)
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, -17(%rbp)
	jne	.L32
	.loc 1 145 0
	movq	-56(%rbp), %rax
	jmp	.L23
.L32:
	.loc 1 146 0
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L33
	.loc 1 147 0
	movl	$0, %eax
	jmp	.L23
.L33:
	.loc 1 148 0
	addq	$1, -56(%rbp)
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, -17(%rbp)
	jne	.L34
	.loc 1 149 0
	movq	-56(%rbp), %rax
	jmp	.L23
.L34:
	.loc 1 150 0
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L35
	.loc 1 151 0
	movl	$0, %eax
	jmp	.L23
.L35:
	.loc 1 154 0
	addq	$1, -56(%rbp)
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, -17(%rbp)
	jne	.L36
	.loc 1 155 0
	movq	-56(%rbp), %rax
	jmp	.L23
.L36:
	.loc 1 156 0
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L37
	.loc 1 157 0
	movl	$0, %eax
	jmp	.L23
.L37:
	.loc 1 158 0
	addq	$1, -56(%rbp)
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, -17(%rbp)
	jne	.L38
	.loc 1 159 0
	movq	-56(%rbp), %rax
	jmp	.L23
.L38:
	.loc 1 160 0
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L39
	.loc 1 161 0
	movl	$0, %eax
	jmp	.L23
.L39:
	.loc 1 162 0
	addq	$1, -56(%rbp)
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, -17(%rbp)
	jne	.L40
	.loc 1 163 0
	movq	-56(%rbp), %rax
	jmp	.L23
.L40:
	.loc 1 164 0
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L41
	.loc 1 165 0
	movl	$0, %eax
	jmp	.L23
.L41:
	.loc 1 166 0
	addq	$1, -56(%rbp)
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, -17(%rbp)
	jne	.L42
	.loc 1 167 0
	movq	-56(%rbp), %rax
	jmp	.L23
.L42:
	.loc 1 168 0
	movq	-56(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L43
	.loc 1 169 0
	movl	$0, %eax
.L23:
.LBE4:
	.loc 1 175 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	strchr, .-strchr
	.globl	strcpy
	.type	strcpy, @function
strcpy:
.LFB3:
	.loc 1 177 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 1 178 0
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	.loc 1 179 0
	jmp	.L45
.L46:
	.loc 1 181 0
	movq	-32(%rbp), %rdx
	leaq	1(%rdx), %rax
	movq	%rax, -32(%rbp)
	movq	-24(%rbp), %rax
	leaq	1(%rax), %rcx
	movq	%rcx, -24(%rbp)
	movzbl	(%rdx), %edx
	movb	%dl, (%rax)
.L45:
	.loc 1 179 0
	movq	-32(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L46
	.loc 1 183 0
	movq	-24(%rbp), %rax
	movb	$0, (%rax)
	.loc 1 184 0
	movq	-8(%rbp), %rax
	.loc 1 186 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	strcpy, .-strcpy
	.globl	memcpy
	.type	memcpy, @function
memcpy:
.LFB4:
	.loc 1 195 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -56(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	.loc 1 196 0
	movq	-56(%rbp), %rax
	movq	%rax, -8(%rbp)
	.loc 1 197 0
	movq	-64(%rbp), %rax
	movq	%rax, -16(%rbp)
	.loc 1 202 0
	cmpq	$15, -72(%rbp)
	jbe	.L49
	.loc 1 205 0
	movq	-8(%rbp), %rax
	negq	%rax
	andl	$7, %eax
	subq	%rax, -72(%rbp)
.LBB5:
	.loc 1 206 0
	movq	-8(%rbp), %rax
	negq	%rax
	andl	$7, %eax
	movq	%rax, -24(%rbp)
	jmp	.L50
.L51:
.LBB6:
	.loc 1 206 0 is_stmt 0 discriminator 3
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -37(%rbp)
	addq	$1, -16(%rbp)
	subq	$1, -24(%rbp)
	movq	-8(%rbp), %rax
	movzbl	-37(%rbp), %edx
	movb	%dl, (%rax)
	addq	$1, -8(%rbp)
.L50:
.LBE6:
	.loc 1 206 0 discriminator 1
	cmpq	$0, -24(%rbp)
	jne	.L51
.LBE5:
.LBB7:
	.loc 1 217 0 is_stmt 1
	movq	-72(%rbp), %rax
	shrq	$2, %rax
	movq	%rax, %rcx
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, %rsi
#APP
# 217 "/home/xiaodo/c++/colang/src/colib/string.c" 1
	cld
rep
movsl
# 0 "" 2
#NO_APP
	movq	%rsi, %rax
	movq	%rdi, %rdx
	movq	%rdx, -8(%rbp)
	movq	%rax, -16(%rbp)
	movl	%ecx, -36(%rbp)
	andq	$3, -72(%rbp)
.L49:
.LBE7:
.LBB8:
	.loc 1 223 0
	movq	-72(%rbp), %rax
	movq	%rax, -32(%rbp)
	jmp	.L52
.L53:
.LBB9:
	.loc 1 223 0 is_stmt 0 discriminator 3
	movq	-16(%rbp), %rax
	movzbl	(%rax), %eax
	movb	%al, -38(%rbp)
	addq	$1, -16(%rbp)
	subq	$1, -32(%rbp)
	movq	-8(%rbp), %rax
	movzbl	-38(%rbp), %edx
	movb	%dl, (%rax)
	addq	$1, -8(%rbp)
.L52:
.LBE9:
	.loc 1 223 0 discriminator 1
	cmpq	$0, -32(%rbp)
	jne	.L53
.LBE8:
	.loc 1 225 0 is_stmt 1
	movq	-56(%rbp), %rax
	.loc 1 226 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	memcpy, .-memcpy
	.globl	memmove
	.type	memmove, @function
memmove:
.LFB5:
	.loc 1 228 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$80, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -88(%rbp)
	movq	%rsi, -96(%rbp)
	movq	%rdx, -104(%rbp)
	.loc 1 230 0
	movq	-88(%rbp), %rbx
	.loc 1 231 0
	movq	-88(%rbp), %rax
	cmpq	-96(%rbp), %rax
	jnb	.L56
.LBB10:
	.loc 1 236 0
	movq	-104(%rbp), %rax
	movq	%rax, -128(%rbp)
	movq	$0, -120(%rbp)
	movq	%rax, %rdx
	subq	$1, %rdx
	movq	%rdx, -72(%rbp)
	movq	%rax, -144(%rbp)
	movq	$0, -136(%rbp)
	movq	%rax, -160(%rbp)
	movq	$0, -152(%rbp)
	.loc 1 238 0
	movq	-104(%rbp), %rax
	movq	%rax, -176(%rbp)
	movq	$0, -168(%rbp)
	movq	%rax, %rdx
	subq	$1, %rdx
	movq	%rdx, -80(%rbp)
	movq	%rax, -192(%rbp)
	movq	$0, -184(%rbp)
	movq	%rax, -208(%rbp)
	movq	$0, -200(%rbp)
	.loc 1 232 0
	movq	-88(%rbp), %r9
	movq	-104(%rbp), %rax
	movq	-96(%rbp), %rdx
	movq	-96(%rbp), %r8
	movq	%rbx, %rdi
	movq	%rax, %rcx
	movq	%rdx, %rsi
#APP
# 232 "/home/xiaodo/c++/colang/src/colib/string.c" 1
	cld
	rep; movsb
# 0 "" 2
#NO_APP
.LBE10:
	jmp	.L57
.L56:
.LBB11:
	.loc 1 245 0
	movq	-104(%rbp), %rax
	movq	%rax, -224(%rbp)
	movq	$0, -216(%rbp)
	movq	%rax, %rdx
	subq	$1, %rdx
	movq	%rdx, -64(%rbp)
	movq	%rax, -240(%rbp)
	movq	$0, -232(%rbp)
	movq	%rax, %r14
	movl	$0, %r15d
	.loc 1 248 0
	movq	-104(%rbp), %rax
	movq	%rax, %r12
	movl	$0, %r13d
	movq	%rax, %rdx
	subq	$1, %rdx
	movq	%rdx, -56(%rbp)
	movq	%rax, %r10
	movl	$0, %r11d
	movq	%rax, %r8
	movl	$0, %r9d
	.loc 1 246 0
	movq	-104(%rbp), %rax
	leaq	-1(%rax), %rdx
	movq	-96(%rbp), %rax
	addq	%rax, %rdx
	.loc 1 247 0
	movq	-104(%rbp), %rax
	subq	$1, %rax
	leaq	(%rbx,%rax), %rcx
	.loc 1 240 0
	movq	-88(%rbp), %r9
	movq	-104(%rbp), %rax
	movq	-96(%rbp), %r8
	movq	%rcx, %rdi
	movq	%rax, %rcx
	movq	%rdx, %rsi
#APP
# 240 "/home/xiaodo/c++/colang/src/colib/string.c" 1
	std
	rep; movsb
	cld
# 0 "" 2
#NO_APP
.L57:
.LBE11:
	.loc 1 249 0
	movq	-88(%rbp), %rax
	.loc 1 250 0
	addq	$80, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	memmove, .-memmove
	.globl	memcmp
	.type	memcmp, @function
memcmp:
.LFB6:
	.loc 1 252 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movq	%rdi, -72(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%rdx, -88(%rbp)
	.loc 1 265 0
	movq	-88(%rbp), %rax
	movq	%rax, -112(%rbp)
	movq	$0, -104(%rbp)
	movq	%rax, %rdx
	subq	$1, %rdx
	movq	%rdx, -56(%rbp)
	movq	%rax, %r14
	movl	$0, %r15d
	movq	%rax, %r12
	movl	$0, %r13d
	.loc 1 266 0
	movq	-88(%rbp), %rax
	movq	%rax, %r10
	movl	$0, %r11d
	movq	%rax, %rdx
	subq	$1, %rdx
	movq	%rdx, -64(%rbp)
	movq	%rax, %r8
	movl	$0, %r9d
	movq	%rax, %rcx
	movl	$0, %ebx
	.loc 1 255 0
	movl	$0, %eax
	movq	-72(%rbp), %rdx
	movq	-80(%rbp), %rsi
	movq	-88(%rbp), %rcx
	movq	-72(%rbp), %r8
	movq	-80(%rbp), %r9
	movq	%rsi, %rdi
	movq	%rdx, %rsi
#APP
# 255 "/home/xiaodo/c++/colang/src/colib/string.c" 1
	cld
	test %rcx,%rcx
	repe; cmpsb
	je	1f
	sbb	%eax,%eax
	or	$1,%eax
1:
# 0 "" 2
#NO_APP
	movl	%eax, %ebx
	.loc 1 268 0
	movl	%ebx, %eax
	.loc 1 269 0
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	memcmp, .-memcmp
	.globl	strlen
	.type	strlen, @function
strlen:
.LFB7:
	.loc 1 271 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	.loc 1 272 0
	movq	$0, -8(%rbp)
	.loc 1 273 0
	cmpq	$0, -24(%rbp)
	jne	.L64
	.loc 1 274 0
	movl	$0, %eax
	jmp	.L63
.L65:
	.loc 1 277 0 discriminator 2
	addq	$1, -8(%rbp)
	.loc 1 275 0 discriminator 2
	addq	$1, -24(%rbp)
.L64:
	.loc 1 275 0 is_stmt 0 discriminator 1
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L65
	.loc 1 280 0 is_stmt 1
	movq	-8(%rbp), %rax
.L63:
	.loc 1 281 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	strlen, .-strlen
	.globl	memset
	.type	memset, @function
memset:
.LFB8:
	.loc 1 283 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 1 285 0
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	.loc 1 291 0
	movl	-28(%rbp), %eax
	movzbl	%al, %eax
	.loc 1 294 0
#APP
# 294 "/home/xiaodo/c++/colang/src/colib/string.c" 1
	cld
# 0 "" 2
	.loc 1 297 0
#NO_APP
	cmpq	$11, -40(%rbp)
	jbe	.L67
	.loc 1 300 0
	movq	%rax, %rdx
	salq	$8, %rdx
	orq	%rdx, %rax
	.loc 1 301 0
	movq	%rax, %rdx
	salq	$16, %rdx
	orq	%rdx, %rax
	.loc 1 304 0
	movq	-8(%rbp), %rdx
	negq	%rdx
	andl	$7, %edx
	subq	%rdx, -40(%rbp)
	.loc 1 313 0
	movq	-8(%rbp), %rdx
	negq	%rdx
	movq	%rdx, %rcx
	andl	$7, %ecx
	.loc 1 310 0
	movq	-8(%rbp), %rdx
	movq	%rdx, %rdi
#APP
# 310 "/home/xiaodo/c++/colang/src/colib/string.c" 1
	rep
stosb
# 0 "" 2
#NO_APP
	movq	%rdi, %rdx
	movq	%rdx, -8(%rbp)
	movl	%ecx, -12(%rbp)
	.loc 1 320 0
	movq	-40(%rbp), %rdx
	movq	%rdx, %rcx
	shrq	$3, %rcx
	.loc 1 317 0
	movq	-8(%rbp), %rdx
	movq	%rdx, %rdi
#APP
# 317 "/home/xiaodo/c++/colang/src/colib/string.c" 1
	rep
stosl
# 0 "" 2
#NO_APP
	movq	%rdi, %rdx
	movq	%rdx, -8(%rbp)
	movl	%ecx, -12(%rbp)
	.loc 1 322 0
	andq	$7, -40(%rbp)
.L67:
	.loc 1 326 0
	movq	-8(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movq	%rdx, %rdi
#APP
# 326 "/home/xiaodo/c++/colang/src/colib/string.c" 1
	rep
stosb
# 0 "" 2
#NO_APP
	movl	%ecx, %eax
	movq	%rdi, %rdx
	movq	%rdx, -8(%rbp)
	movl	%eax, -12(%rbp)
	.loc 1 332 0
	movq	-24(%rbp), %rax
	.loc 1 333 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	memset, .-memset
	.globl	tolower
	.type	tolower, @function
tolower:
.LFB9:
	.loc 1 336 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	.loc 1 337 0
	cmpl	$64, -4(%rbp)
	jbe	.L70
	.loc 1 337 0 is_stmt 0 discriminator 1
	cmpl	$90, -4(%rbp)
	ja	.L70
	.loc 1 337 0 discriminator 2
	movl	-4(%rbp), %eax
	addl	$32, %eax
	jmp	.L71
.L70:
	.loc 1 338 0 is_stmt 1
	movl	-4(%rbp), %eax
.L71:
	.loc 1 339 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	tolower, .-tolower
	.globl	toupper
	.type	toupper, @function
toupper:
.LFB10:
	.loc 1 342 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	.loc 1 343 0
	cmpl	$96, -4(%rbp)
	jbe	.L73
	.loc 1 343 0 is_stmt 0 discriminator 1
	cmpl	$122, -4(%rbp)
	ja	.L73
	.loc 1 343 0 discriminator 2
	movl	-4(%rbp), %eax
	subl	$32, %eax
	jmp	.L74
.L73:
	.loc 1 344 0 is_stmt 1
	movl	-4(%rbp), %eax
.L74:
	.loc 1 345 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	toupper, .-toupper
	.globl	strcat
	.type	strcat, @function
strcat:
.LFB11:
	.loc 1 354 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	.loc 1 355 0
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	.loc 1 356 0
	movq	-48(%rbp), %rax
	movq	%rax, -16(%rbp)
.L76:
	.loc 1 361 0 discriminator 1
	movq	-8(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -8(%rbp)
	movzbl	(%rax), %eax
	movb	%al, -17(%rbp)
	.loc 1 362 0 discriminator 1
	cmpb	$0, -17(%rbp)
	jne	.L76
	.loc 1 366 0
	subq	$2, -8(%rbp)
.L77:
	.loc 1 370 0 discriminator 1
	movq	-16(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, -16(%rbp)
	movzbl	(%rax), %eax
	movb	%al, -17(%rbp)
	.loc 1 371 0 discriminator 1
	addq	$1, -8(%rbp)
	movq	-8(%rbp), %rax
	movzbl	-17(%rbp), %edx
	movb	%dl, (%rax)
	.loc 1 373 0 discriminator 1
	cmpb	$0, -17(%rbp)
	jne	.L77
	.loc 1 375 0
	movq	-40(%rbp), %rax
	.loc 1 376 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	strcat, .-strcat
.Letext0:
	.file 2 "/home/xiaodo/c++/colang/src/crt/minicrt.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x76e
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF43
	.byte	0xc
	.long	.LASF44
	.long	.LASF45
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF0
	.uleb128 0x3
	.long	.LASF46
	.byte	0x2
	.byte	0x5d
	.long	0x3f
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x4
	.long	0x3f
	.uleb128 0x5
	.long	.LASF4
	.byte	0x1
	.value	0x161
	.long	0xb5
	.quad	.LFB11
	.quad	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.long	0xb5
	.uleb128 0x6
	.long	.LASF2
	.byte	0x1
	.value	0x161
	.long	0xb5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x7
	.string	"src"
	.byte	0x1
	.value	0x161
	.long	0xc7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x8
	.string	"s1"
	.byte	0x1
	.value	0x163
	.long	0xb5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x8
	.string	"s2"
	.byte	0x1
	.value	0x164
	.long	0xc7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x8
	.string	"c"
	.byte	0x1
	.value	0x165
	.long	0xbb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -33
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0xbb
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF3
	.uleb128 0x4
	.long	0xbb
	.uleb128 0x9
	.byte	0x8
	.long	0xc2
	.uleb128 0x5
	.long	.LASF5
	.byte	0x1
	.value	0x155
	.long	0xfd
	.quad	.LFB10
	.quad	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.long	0xfd
	.uleb128 0x7
	.string	"c"
	.byte	0x1
	.value	0x155
	.long	0xfd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF6
	.uleb128 0x5
	.long	.LASF7
	.byte	0x1
	.value	0x14f
	.long	0xfd
	.quad	.LFB9
	.quad	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.long	0x134
	.uleb128 0x7
	.string	"c"
	.byte	0x1
	.value	0x14f
	.long	0xfd
	.uleb128 0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x5
	.long	.LASF8
	.byte	0x1
	.value	0x11a
	.long	0x1ab
	.quad	.LFB8
	.quad	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.long	0x1ab
	.uleb128 0x6
	.long	.LASF9
	.byte	0x1
	.value	0x11a
	.long	0x1ab
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x7
	.string	"c"
	.byte	0x1
	.value	0x11a
	.long	0x1ad
	.uleb128 0x2
	.byte	0x91
	.sleb128 -44
	.uleb128 0x7
	.string	"len"
	.byte	0x1
	.value	0x11a
	.long	0x1b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x8
	.string	"d0"
	.byte	0x1
	.value	0x11c
	.long	0x1ad
	.uleb128 0x2
	.byte	0x91
	.sleb128 -28
	.uleb128 0xa
	.long	.LASF10
	.byte	0x1
	.value	0x11d
	.long	0x1b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x8
	.string	"x"
	.byte	0x1
	.value	0x121
	.long	0x1b4
	.uleb128 0x1
	.byte	0x50
	.byte	0
	.uleb128 0xb
	.byte	0x8
	.uleb128 0xc
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF11
	.uleb128 0x4
	.long	0x1b4
	.uleb128 0x5
	.long	.LASF12
	.byte	0x1
	.value	0x10e
	.long	0x1b4
	.quad	.LFB7
	.quad	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.long	0x201
	.uleb128 0x7
	.string	"str"
	.byte	0x1
	.value	0x10e
	.long	0xc7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x8
	.string	"cnt"
	.byte	0x1
	.value	0x110
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xd
	.long	.LASF13
	.byte	0x1
	.byte	0xfb
	.long	0x1ad
	.quad	.LFB6
	.quad	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.long	0x2a6
	.uleb128 0xe
	.long	.LASF14
	.byte	0x1
	.byte	0xfb
	.long	0x2a6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0xe
	.long	.LASF15
	.byte	0x1
	.byte	0xfb
	.long	0x2a6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0xf
	.string	"__n"
	.byte	0x1
	.byte	0xfb
	.long	0x1b4
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0x10
	.long	.LASF16
	.byte	0x1
	.byte	0xfd
	.long	0x1b4
	.uleb128 0x10
	.long	.LASF17
	.byte	0x1
	.byte	0xfd
	.long	0x1b4
	.uleb128 0x10
	.long	.LASF18
	.byte	0x1
	.byte	0xfd
	.long	0x1b4
	.uleb128 0x11
	.long	.LASF19
	.byte	0x1
	.byte	0xfe
	.long	0x1ad
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x12
	.byte	0x1
	.value	0x109
	.long	0x293
	.uleb128 0x13
	.string	"__x"
	.byte	0x1
	.value	0x109
	.long	0x2ad
	.byte	0
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.value	0x10a
	.uleb128 0x13
	.string	"__x"
	.byte	0x1
	.value	0x10a
	.long	0x2c1
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x2ac
	.uleb128 0x15
	.uleb128 0x16
	.long	0xbb
	.long	0x2c1
	.uleb128 0x17
	.long	0x1b4
	.uleb128 0x4
	.byte	0x91
	.sleb128 -72
	.byte	0x6
	.byte	0
	.uleb128 0x16
	.long	0xbb
	.long	0x2d5
	.uleb128 0x17
	.long	0x1b4
	.uleb128 0x4
	.byte	0x91
	.sleb128 -80
	.byte	0x6
	.byte	0
	.uleb128 0xd
	.long	.LASF20
	.byte	0x1
	.byte	0xe3
	.long	0x1ab
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.long	0x3c2
	.uleb128 0xe
	.long	.LASF21
	.byte	0x1
	.byte	0xe3
	.long	0x1ab
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0xe
	.long	.LASF22
	.byte	0x1
	.byte	0xe3
	.long	0x2a6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0xf
	.string	"__n"
	.byte	0x1
	.byte	0xe3
	.long	0x1b4
	.uleb128 0x3
	.byte	0x91
	.sleb128 -120
	.uleb128 0x10
	.long	.LASF16
	.byte	0x1
	.byte	0xe5
	.long	0x1b4
	.uleb128 0x10
	.long	.LASF17
	.byte	0x1
	.byte	0xe5
	.long	0x1b4
	.uleb128 0x10
	.long	.LASF18
	.byte	0x1
	.byte	0xe5
	.long	0x1b4
	.uleb128 0x11
	.long	.LASF23
	.byte	0x1
	.byte	0xe6
	.long	0x1ab
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x18
	.quad	.LBB10
	.quad	.LBE10-.LBB10
	.long	0x38b
	.uleb128 0x19
	.byte	0x1
	.byte	0xec
	.long	0x37a
	.uleb128 0x1a
	.string	"__x"
	.byte	0x1
	.byte	0xec
	.long	0x3c2
	.byte	0
	.byte	0
	.uleb128 0x1b
	.byte	0x1
	.byte	0xee
	.uleb128 0x1a
	.string	"__x"
	.byte	0x1
	.byte	0xee
	.long	0x3d6
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1c
	.quad	.LBB11
	.quad	.LBE11-.LBB11
	.uleb128 0x19
	.byte	0x1
	.byte	0xf5
	.long	0x3b0
	.uleb128 0x1a
	.string	"__x"
	.byte	0x1
	.byte	0xf5
	.long	0x3ea
	.byte	0
	.byte	0
	.uleb128 0x1b
	.byte	0x1
	.byte	0xf8
	.uleb128 0x1a
	.string	"__x"
	.byte	0x1
	.byte	0xf8
	.long	0x3fe
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x16
	.long	0xbb
	.long	0x3d6
	.uleb128 0x17
	.long	0x1b4
	.uleb128 0x4
	.byte	0x91
	.sleb128 -88
	.byte	0x6
	.byte	0
	.uleb128 0x16
	.long	0xbb
	.long	0x3ea
	.uleb128 0x17
	.long	0x1b4
	.uleb128 0x4
	.byte	0x91
	.sleb128 -96
	.byte	0x6
	.byte	0
	.uleb128 0x16
	.long	0xbb
	.long	0x3fe
	.uleb128 0x17
	.long	0x1b4
	.uleb128 0x4
	.byte	0x91
	.sleb128 -80
	.byte	0x6
	.byte	0
	.uleb128 0x16
	.long	0xbb
	.long	0x412
	.uleb128 0x17
	.long	0x1b4
	.uleb128 0x4
	.byte	0x91
	.sleb128 -72
	.byte	0x6
	.byte	0
	.uleb128 0xd
	.long	.LASF24
	.byte	0x1
	.byte	0xc2
	.long	0x1ab
	.quad	.LFB4
	.quad	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.long	0x525
	.uleb128 0xe
	.long	.LASF9
	.byte	0x1
	.byte	0xc2
	.long	0x1ab
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0xe
	.long	.LASF25
	.byte	0x1
	.byte	0xc2
	.long	0x2a6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0xf
	.string	"len"
	.byte	0x1
	.byte	0xc2
	.long	0x1b4
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x11
	.long	.LASF10
	.byte	0x1
	.byte	0xc4
	.long	0x1b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x11
	.long	.LASF26
	.byte	0x1
	.byte	0xc5
	.long	0x1b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x18
	.quad	.LBB5
	.quad	.LBE5-.LBB5
	.long	0x4c0
	.uleb128 0x11
	.long	.LASF27
	.byte	0x1
	.byte	0xce
	.long	0x1b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1c
	.quad	.LBB6
	.quad	.LBE6-.LBB6
	.uleb128 0x1d
	.string	"__x"
	.byte	0x1
	.byte	0xce
	.long	0x34
	.uleb128 0x2
	.byte	0x91
	.sleb128 -53
	.byte	0
	.byte	0
	.uleb128 0x18
	.quad	.LBB7
	.quad	.LBE7-.LBB7
	.long	0x4e4
	.uleb128 0x11
	.long	.LASF16
	.byte	0x1
	.byte	0xd9
	.long	0x1ad
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.byte	0
	.uleb128 0x1c
	.quad	.LBB8
	.quad	.LBE8-.LBB8
	.uleb128 0x11
	.long	.LASF27
	.byte	0x1
	.byte	0xdf
	.long	0x1b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1c
	.quad	.LBB9
	.quad	.LBE9-.LBB9
	.uleb128 0x1d
	.string	"__x"
	.byte	0x1
	.byte	0xdf
	.long	0x34
	.uleb128 0x2
	.byte	0x91
	.sleb128 -54
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xd
	.long	.LASF28
	.byte	0x1
	.byte	0xb0
	.long	0xb5
	.quad	.LFB3
	.quad	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.long	0x571
	.uleb128 0xe
	.long	.LASF2
	.byte	0x1
	.byte	0xb0
	.long	0xb5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0xf
	.string	"src"
	.byte	0x1
	.byte	0xb0
	.long	0xc7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1d
	.string	"ret"
	.byte	0x1
	.byte	0xb2
	.long	0xb5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0xd
	.long	.LASF29
	.byte	0x1
	.byte	0x48
	.long	0xb5
	.quad	.LFB2
	.quad	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.long	0x657
	.uleb128 0xf
	.string	"s"
	.byte	0x1
	.byte	0x48
	.long	0xc7
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0xe
	.long	.LASF30
	.byte	0x1
	.byte	0x48
	.long	0x1ad
	.uleb128 0x3
	.byte	0x91
	.sleb128 -92
	.uleb128 0x11
	.long	.LASF31
	.byte	0x1
	.byte	0x4a
	.long	0x657
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x11
	.long	.LASF32
	.byte	0x1
	.byte	0x4b
	.long	0x65d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x11
	.long	.LASF33
	.byte	0x1
	.byte	0x4c
	.long	0x1b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x11
	.long	.LASF34
	.byte	0x1
	.byte	0x4c
	.long	0x1b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x11
	.long	.LASF35
	.byte	0x1
	.byte	0x4c
	.long	0x1b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1d
	.string	"c"
	.byte	0x1
	.byte	0x4d
	.long	0x3f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -33
	.uleb128 0x18
	.quad	.LBB3
	.quad	.LBE3-.LBB3
	.long	0x623
	.uleb128 0x1e
	.long	.LASF36
	.byte	0x1
	.byte	0x62
	.long	0x1ad
	.uleb128 0x1f
	.byte	0
	.byte	0
	.uleb128 0x20
	.long	0x636
	.uleb128 0x1e
	.long	.LASF36
	.byte	0x1
	.byte	0x62
	.long	0x1ad
	.uleb128 0x1f
	.byte	0
	.byte	0
	.uleb128 0x1c
	.quad	.LBB4
	.quad	.LBE4-.LBB4
	.uleb128 0x1d
	.string	"cp"
	.byte	0x1
	.byte	0x86
	.long	0x657
	.uleb128 0x3
	.byte	0x91
	.sleb128 -72
	.byte	0
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x46
	.uleb128 0x9
	.byte	0x8
	.long	0x1bb
	.uleb128 0xd
	.long	.LASF37
	.byte	0x1
	.byte	0x2f
	.long	0x2d
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x6c9
	.uleb128 0xf
	.string	"src"
	.byte	0x1
	.byte	0x2f
	.long	0xc7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0xf
	.string	"dst"
	.byte	0x1
	.byte	0x2f
	.long	0xc7
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x1d
	.string	"ret"
	.byte	0x1
	.byte	0x31
	.long	0x2d
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1d
	.string	"p1"
	.byte	0x1
	.byte	0x32
	.long	0x6c9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1d
	.string	"p2"
	.byte	0x1
	.byte	0x33
	.long	0x6c9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x9
	.byte	0x8
	.long	0x3f
	.uleb128 0xd
	.long	.LASF38
	.byte	0x1
	.byte	0x2
	.long	0xb5
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0x765
	.uleb128 0xf
	.string	"n"
	.byte	0x1
	.byte	0x2
	.long	0x2d
	.uleb128 0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0xf
	.string	"str"
	.byte	0x1
	.byte	0x2
	.long	0xb5
	.uleb128 0x3
	.byte	0x91
	.sleb128 -96
	.uleb128 0xe
	.long	.LASF39
	.byte	0x1
	.byte	0x2
	.long	0x2d
	.uleb128 0x3
	.byte	0x91
	.sleb128 -104
	.uleb128 0x11
	.long	.LASF40
	.byte	0x1
	.byte	0x4
	.long	0x765
	.uleb128 0x3
	.byte	0x91
	.sleb128 -80
	.uleb128 0x1d
	.string	"p"
	.byte	0x1
	.byte	0x5
	.long	0xb5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x11
	.long	.LASF41
	.byte	0x1
	.byte	0x6
	.long	0xb5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1c
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.uleb128 0x11
	.long	.LASF42
	.byte	0x1
	.byte	0x27
	.long	0xbb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -33
	.byte	0
	.byte	0
	.uleb128 0x21
	.long	0xbb
	.uleb128 0x22
	.long	0x1b4
	.byte	0x24
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
	.uleb128 0x4
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x8
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xb
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0x14
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x18
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
	.uleb128 0x19
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
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
	.uleb128 0x1b
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0x1d
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
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
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
.LASF20:
	.string	"memmove"
.LASF29:
	.string	"strchr"
.LASF13:
	.string	"memcmp"
.LASF44:
	.string	"/home/xiaodo/c++/colang/src/crt/string.c"
.LASF21:
	.string	"__dest"
.LASF40:
	.string	"digit"
.LASF39:
	.string	"radix"
.LASF46:
	.string	"byte"
.LASF34:
	.string	"magic_bits"
.LASF12:
	.string	"strlen"
.LASF2:
	.string	"dest"
.LASF1:
	.string	"unsigned char"
.LASF25:
	.string	"srcpp"
.LASF22:
	.string	"__src"
.LASF11:
	.string	"long unsigned int"
.LASF38:
	.string	"itoa"
.LASF26:
	.string	"srcp"
.LASF4:
	.string	"strcat"
.LASF33:
	.string	"longword"
.LASF8:
	.string	"memset"
.LASF41:
	.string	"head"
.LASF6:
	.string	"unsigned int"
.LASF31:
	.string	"char_ptr"
.LASF42:
	.string	"temp"
.LASF45:
	.string	"/home/xiaodo/c++/colang/tests/src/crt"
.LASF3:
	.string	"char"
.LASF14:
	.string	"__s1"
.LASF15:
	.string	"__s2"
.LASF10:
	.string	"dstp"
.LASF43:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -g -fno-builtin"
.LASF30:
	.string	"c_in"
.LASF35:
	.string	"charmask"
.LASF37:
	.string	"strcmp"
.LASF16:
	.string	"__d0"
.LASF17:
	.string	"__d1"
.LASF18:
	.string	"__d2"
.LASF24:
	.string	"memcpy"
.LASF27:
	.string	"__nbytes"
.LASF5:
	.string	"toupper"
.LASF7:
	.string	"tolower"
.LASF28:
	.string	"strcpy"
.LASF23:
	.string	"__tmp"
.LASF0:
	.string	"long int"
.LASF9:
	.string	"dstpp"
.LASF36:
	.string	"abort"
.LASF32:
	.string	"longword_ptr"
.LASF19:
	.string	"__res"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits

	.file	"Value.c"
	.text
.Ltext0:
	.type	stringlen, @function
stringlen:
.LFB5:
	.file 1 "/home/xiaodo/c++/colang/src/internal/String.h"
	.loc 1 55 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	.loc 1 56 0
	movq	-24(%rbp), %rax
	subq	$1, %rax
	movzbl	(%rax), %eax
	movb	%al, -1(%rbp)
	.loc 1 57 0
	movzbl	-1(%rbp), %eax
	andl	$7, %eax
	cmpl	$4, %eax
	ja	.L2
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L4(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L4(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
#	.section	.rodata
	.align 4
	.align 4
.L4:
	.long	.L3-.L4
	.long	.L5-.L4
	.long	.L6-.L4
	.long	.L7-.L4
	.long	.L8-.L4
	.text
.L3:
	.loc 1 59 0
	movzbl	-1(%rbp), %eax
	shrb	$3, %al
	movzbl	%al, %eax
	jmp	.L9
.L5:
	.loc 1 61 0
	movq	-24(%rbp), %rax
	subq	$3, %rax
	movzbl	(%rax), %eax
	movzbl	%al, %eax
	jmp	.L9
.L6:
	.loc 1 63 0
	movq	-24(%rbp), %rax
	subq	$5, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	jmp	.L9
.L7:
	.loc 1 65 0
	movq	-24(%rbp), %rax
	subq	$9, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	jmp	.L9
.L8:
	.loc 1 67 0
	movq	-24(%rbp), %rax
	subq	$17, %rax
	movq	(%rax), %rax
	jmp	.L9
.L2:
	.loc 1 69 0
	movl	$0, %eax
.L9:
	.loc 1 70 0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	stringlen, .-stringlen
	.globl	value_plus
	.type	value_plus, @function
value_plus:
.LFB12:
	.file 2 "/home/xiaodo/c++/colang/src/internal/Value.c"
	.loc 2 15 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 2 16 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 17 0
	cmpq	$0, -24(%rbp)
	jne	.L11
	.loc 2 18 0
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	.loc 2 19 0
	movq	-8(%rbp), %rax
	jmp	.L12
.L11:
	.loc 2 22 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L13
	.loc 2 22 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L14
.L13:
	.loc 2 23 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$3, (%rax)
	.loc 2 24 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_string_plus@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 25 0
	movq	-8(%rbp), %rax
	jmp	.L12
.L14:
	.loc 2 28 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L15
	.loc 2 28 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	jne	.L16
.L15:
	.loc 2 29 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 30 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_int_plus@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 31 0
	movq	-8(%rbp), %rax
	jmp	.L12
.L16:
	.loc 2 33 0
	movl	$1, %edi
	call	exit@PLT
.L12:
	.loc 2 34 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	value_plus, .-value_plus
	.globl	value_minus
	.type	value_minus, @function
value_minus:
.LFB13:
	.loc 2 41 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 2 42 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 43 0
	cmpq	$0, -24(%rbp)
	jne	.L18
	.loc 2 44 0
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	.loc 2 45 0
	movq	-8(%rbp), %rax
	jmp	.L19
.L18:
	.loc 2 48 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L20
	.loc 2 48 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L21
.L20:
	.loc 2 49 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$3, (%rax)
	.loc 2 50 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_string_minus@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 51 0
	movq	-8(%rbp), %rax
	jmp	.L19
.L21:
	.loc 2 54 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L22
	.loc 2 54 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	jne	.L23
.L22:
	.loc 2 55 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 56 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_int_minus@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 57 0
	movq	-8(%rbp), %rax
	jmp	.L19
.L23:
	.loc 2 59 0
	movl	$1, %edi
	call	exit@PLT
.L19:
	.loc 2 60 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	value_minus, .-value_minus
	.globl	value_mul
	.type	value_mul, @function
value_mul:
.LFB14:
	.loc 2 67 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 2 68 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 69 0
	cmpq	$0, -24(%rbp)
	jne	.L25
	.loc 2 70 0
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	.loc 2 71 0
	movq	-8(%rbp), %rax
	jmp	.L26
.L25:
	.loc 2 74 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L27
	.loc 2 74 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L28
.L27:
	.loc 2 75 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$3, (%rax)
	.loc 2 76 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_string_mul@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 77 0
	movq	-8(%rbp), %rax
	jmp	.L26
.L28:
	.loc 2 80 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L29
	.loc 2 80 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	jne	.L30
.L29:
	.loc 2 81 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 82 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_int_mul@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 83 0
	movq	-8(%rbp), %rax
	jmp	.L26
.L30:
	.loc 2 85 0
	movl	$1, %edi
	call	exit@PLT
.L26:
	.loc 2 86 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE14:
	.size	value_mul, .-value_mul
	.globl	value_div
	.type	value_div, @function
value_div:
.LFB15:
	.loc 2 93 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 2 94 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 95 0
	cmpq	$0, -24(%rbp)
	jne	.L32
	.loc 2 96 0
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	.loc 2 97 0
	movq	-8(%rbp), %rax
	jmp	.L33
.L32:
	.loc 2 100 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L34
	.loc 2 100 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L35
.L34:
	.loc 2 101 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 102 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_string_div@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 103 0
	movq	-8(%rbp), %rax
	jmp	.L33
.L35:
	.loc 2 106 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L36
	.loc 2 106 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	jne	.L37
.L36:
	.loc 2 107 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 108 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_int_div@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 109 0
	movq	-8(%rbp), %rax
	jmp	.L33
.L37:
	.loc 2 111 0
	movl	$1, %edi
	call	exit@PLT
.L33:
	.loc 2 112 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE15:
	.size	value_div, .-value_div
	.globl	value_bitand
	.type	value_bitand, @function
value_bitand:
.LFB16:
	.loc 2 119 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 2 120 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 121 0
	cmpq	$0, -24(%rbp)
	jne	.L39
	.loc 2 122 0
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	.loc 2 123 0
	movq	-8(%rbp), %rax
	jmp	.L40
.L39:
	.loc 2 126 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L41
	.loc 2 126 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L42
.L41:
	.loc 2 127 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 128 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_string_bitand@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 129 0
	movq	-8(%rbp), %rax
	jmp	.L40
.L42:
	.loc 2 132 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L43
	.loc 2 132 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	jne	.L44
.L43:
	.loc 2 133 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 134 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_int_bitand@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 135 0
	movq	-8(%rbp), %rax
	jmp	.L40
.L44:
	.loc 2 137 0
	movl	$1, %edi
	call	exit@PLT
.L40:
	.loc 2 138 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE16:
	.size	value_bitand, .-value_bitand
	.globl	value_bitor
	.type	value_bitor, @function
value_bitor:
.LFB17:
	.loc 2 145 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 2 146 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 147 0
	cmpq	$0, -24(%rbp)
	jne	.L46
	.loc 2 148 0
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	.loc 2 149 0
	movq	-8(%rbp), %rax
	jmp	.L47
.L46:
	.loc 2 152 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L48
	.loc 2 152 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L49
.L48:
	.loc 2 153 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 154 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_string_bitor@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 155 0
	movq	-8(%rbp), %rax
	jmp	.L47
.L49:
	.loc 2 158 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L50
	.loc 2 158 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	jne	.L51
.L50:
	.loc 2 159 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 160 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_int_bitor@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 161 0
	movq	-8(%rbp), %rax
	jmp	.L47
.L51:
	.loc 2 163 0
	movl	$1, %edi
	call	exit@PLT
.L47:
	.loc 2 164 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE17:
	.size	value_bitor, .-value_bitor
	.globl	value_shift_left
	.type	value_shift_left, @function
value_shift_left:
.LFB18:
	.loc 2 171 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 2 172 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 173 0
	cmpq	$0, -24(%rbp)
	jne	.L53
	.loc 2 174 0
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	.loc 2 175 0
	movq	-8(%rbp), %rax
	jmp	.L54
.L53:
	.loc 2 178 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L55
	.loc 2 178 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L56
.L55:
	.loc 2 179 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 180 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_string_shift_left@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 181 0
	movq	-8(%rbp), %rax
	jmp	.L54
.L56:
	.loc 2 184 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L57
	.loc 2 184 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	jne	.L58
.L57:
	.loc 2 185 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 186 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_int_shift_left@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 187 0
	movq	-8(%rbp), %rax
	jmp	.L54
.L58:
	.loc 2 189 0
	movl	$1, %edi
	call	exit@PLT
.L54:
	.loc 2 190 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE18:
	.size	value_shift_left, .-value_shift_left
	.globl	value_shift_right
	.type	value_shift_right, @function
value_shift_right:
.LFB19:
	.loc 2 197 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 2 198 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 199 0
	cmpq	$0, -24(%rbp)
	jne	.L60
	.loc 2 200 0
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rax
	movl	$16, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	.loc 2 201 0
	movq	-8(%rbp), %rax
	jmp	.L61
.L60:
	.loc 2 204 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L62
	.loc 2 204 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L63
.L62:
	.loc 2 205 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 206 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_string_shift_right@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 207 0
	movq	-8(%rbp), %rax
	jmp	.L61
.L63:
	.loc 2 210 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L64
	.loc 2 210 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	jne	.L65
.L64:
	.loc 2 211 0 is_stmt 1
	movq	-8(%rbp), %rax
	movq	$1, (%rax)
	.loc 2 212 0
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_int_shift_right@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 213 0
	movq	-8(%rbp), %rax
	jmp	.L61
.L65:
	.loc 2 215 0
	movl	$1, %edi
	call	exit@PLT
.L61:
	.loc 2 216 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE19:
	.size	value_shift_right, .-value_shift_right
	.globl	value_equal
	.type	value_equal, @function
value_equal:
.LFB20:
	.loc 2 223 0
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
	.loc 2 224 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 225 0
	movq	-8(%rbp), %rax
	movq	$4, (%rax)
	.loc 2 226 0
	movq	-8(%rbp), %rax
	movq	$0, 8(%rax)
	.loc 2 228 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L67
	.loc 2 228 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L68
.L67:
	.loc 2 229 0 is_stmt 1
	movl	-36(%rbp), %edx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_string_equal@PLT
	cltq
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 230 0
	movq	-8(%rbp), %rax
	jmp	.L69
.L68:
	.loc 2 233 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L70
	.loc 2 233 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	jne	.L71
.L70:
	.loc 2 234 0 is_stmt 1
	movl	-36(%rbp), %edx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_int_equal@PLT
	cltq
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
.L71:
	.loc 2 236 0
	movq	-8(%rbp), %rax
.L69:
	.loc 2 237 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE20:
	.size	value_equal, .-value_equal
	.globl	value_lowerthan
	.type	value_lowerthan, @function
value_lowerthan:
.LFB21:
	.loc 2 245 0
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
	.loc 2 246 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 247 0
	movq	-8(%rbp), %rax
	movq	$4, (%rax)
	.loc 2 249 0
	movq	-8(%rbp), %rax
	movq	$1, 8(%rax)
	.loc 2 251 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L73
	.loc 2 251 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L74
.L73:
	.loc 2 252 0 is_stmt 1
	movl	-36(%rbp), %edx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_string_lowerthan@PLT
	cltq
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 253 0
	movq	-8(%rbp), %rax
	jmp	.L75
.L74:
	.loc 2 256 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L76
	.loc 2 256 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	jne	.L77
.L76:
	.loc 2 257 0 is_stmt 1
	movl	-36(%rbp), %edx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_int_lowerthan@PLT
	cltq
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
.L77:
	.loc 2 259 0
	movq	-8(%rbp), %rax
.L75:
	.loc 2 260 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE21:
	.size	value_lowerthan, .-value_lowerthan
	.globl	value_greaterthan
	.type	value_greaterthan, @function
value_greaterthan:
.LFB22:
	.loc 2 268 0
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
	.loc 2 269 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 270 0
	movq	-8(%rbp), %rax
	movq	$4, (%rax)
	.loc 2 272 0
	movq	-8(%rbp), %rax
	movq	$1, 8(%rax)
	.loc 2 274 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L79
	.loc 2 274 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	jne	.L80
.L79:
	.loc 2 275 0 is_stmt 1
	movl	-36(%rbp), %edx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_string_greaterthan@PLT
	cltq
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 276 0
	movq	-8(%rbp), %rax
	jmp	.L81
.L80:
	.loc 2 279 0
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L82
	.loc 2 279 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	jne	.L83
.L82:
	.loc 2 280 0 is_stmt 1
	movl	-36(%rbp), %edx
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_int_greaterthan@PLT
	cltq
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
.L83:
	.loc 2 282 0
	movq	-8(%rbp), %rax
.L81:
	.loc 2 283 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE22:
	.size	value_greaterthan, .-value_greaterthan
	.globl	value_logand
	.type	value_logand, @function
value_logand:
.LFB23:
	.loc 2 291 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 2 292 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 293 0
	movq	-8(%rbp), %rax
	movq	$4, (%rax)
	.loc 2 294 0
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	isTrue
	testl	%eax, %eax
	je	.L85
	.loc 2 294 0 is_stmt 0 discriminator 1
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	isTrue
	testl	%eax, %eax
	je	.L85
	.loc 2 294 0 discriminator 3
	movl	$1, %eax
	jmp	.L86
.L85:
	.loc 2 294 0 discriminator 4
	movl	$0, %eax
.L86:
	.loc 2 294 0 discriminator 6
	cltq
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 295 0 is_stmt 1 discriminator 6
	movq	-8(%rbp), %rax
	.loc 2 296 0 discriminator 6
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE23:
	.size	value_logand, .-value_logand
	.globl	value_logor
	.type	value_logor, @function
value_logor:
.LFB24:
	.loc 2 297 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	.loc 2 298 0
	movl	$16, %edi
	call	gc_malloc@PLT
	movq	%rax, -8(%rbp)
	.loc 2 299 0
	movq	-8(%rbp), %rax
	movq	$4, (%rax)
	.loc 2 300 0
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	isTrue
	testl	%eax, %eax
	jne	.L89
	.loc 2 300 0 is_stmt 0 discriminator 2
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	isTrue
	testl	%eax, %eax
	je	.L90
.L89:
	.loc 2 300 0 discriminator 3
	movl	$1, %eax
	jmp	.L91
.L90:
	.loc 2 300 0 discriminator 4
	movl	$0, %eax
.L91:
	.loc 2 300 0 discriminator 6
	cltq
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, 8(%rax)
	.loc 2 301 0 is_stmt 1 discriminator 6
	movq	-8(%rbp), %rax
	.loc 2 302 0 discriminator 6
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE24:
	.size	value_logor, .-value_logor
#	.section	.rodata
	.align 8
.LC0:
	.string	"[kv_update] arr or map is invalid ,probably something wrong\n"
	.text
	.globl	kv_update
	.type	kv_update, @function
kv_update:
.LFB25:
	.loc 2 311 0
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
	.loc 2 312 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$6, %rax
	jne	.L94
	.loc 2 313 0
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	arr_updateone@PLT
	jmp	.L93
.L94:
	.loc 2 315 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$7, %rax
	jne	.L96
	.loc 2 316 0
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	map_insert@PLT
	jmp	.L93
.L96:
	.loc 2 318 0
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L93:
	.loc 2 319 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE25:
	.size	kv_update, .-kv_update
#	.section	.rodata
	.align 8
.LC1:
	.string	"[kv_get] arr or map is invalid ,probably something wrong\n"
	.text
	.globl	kv_get
	.type	kv_get, @function
kv_get:
.LFB26:
	.loc 2 326 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	.loc 2 327 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$6, %rax
	jne	.L98
	.loc 2 328 0
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	arr_get@PLT
	jmp	.L97
.L98:
	.loc 2 330 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$7, %rax
	jne	.L100
	.loc 2 331 0
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	map_find@PLT
	jmp	.L97
.L100:
	.loc 2 333 0
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L97:
	.loc 2 334 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE26:
	.size	kv_get, .-kv_get
	.globl	isTrue
	.type	isTrue, @function
isTrue:
.LFB27:
	.loc 2 340 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$8, %rsp
	movq	%rdi, -8(%rbp)
	.loc 2 341 0
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$5, %rax
	ja	.L102
	leaq	0(,%rax,4), %rdx
	leaq	.L104(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L104(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
#	.section	.rodata
	.align 4
	.align 4
.L104:
	.long	.L103-.L104
	.long	.L105-.L104
	.long	.L106-.L104
	.long	.L107-.L104
	.long	.L108-.L104
	.long	.L109-.L104
	.text
.L105:
	.loc 2 343 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	setne	%al
	movzbl	%al, %eax
	jmp	.L110
.L106:
	.loc 2 345 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	setne	%al
	movzbl	%al, %eax
	jmp	.L110
.L107:
	.loc 2 347 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, %rdi
	call	stringlen
	jmp	.L110
.L108:
	.loc 2 349 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	jmp	.L110
.L109:
	.loc 2 351 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	setne	%al
	movzbl	%al, %eax
	jmp	.L110
.L103:
	.loc 2 353 0
	movl	$0, %eax
	jmp	.L110
.L102:
	.loc 2 355 0
	movl	$0, %eax
.L110:
	.loc 2 357 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE27:
	.size	isTrue, .-isTrue
#	.section	.#rodata
.LC2:
	.string	" [unary-op] unkown op:%d\n"
	.text
	.globl	operator_switch
	.type	operator_switch, @function
operator_switch:
.LFB28:
	.loc 2 364 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 366 0
	movl	-20(%rbp), %eax
	subl	$7, %eax
	cmpl	$28, %eax
	ja	.L112
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L114(%rip), %rax
	movl	(%rdx,%rax), %eax
	movslq	%eax, %rdx
	leaq	.L114(%rip), %rax
	addq	%rdx, %rax
	jmp	*%rax
#	.section	.rodata
	.align 4
	.align 4
.L114:
	.long	.L113-.L114
	.long	.L115-.L114
	.long	.L112-.L114
	.long	.L112-.L114
	.long	.L113-.L114
	.long	.L115-.L114
	.long	.L116-.L114
	.long	.L117-.L114
	.long	.L116-.L114
	.long	.L117-.L114
	.long	.L118-.L114
	.long	.L119-.L114
	.long	.L112-.L114
	.long	.L120-.L114
	.long	.L121-.L114
	.long	.L122-.L114
	.long	.L123-.L114
	.long	.L124-.L114
	.long	.L125-.L114
	.long	.L126-.L114
	.long	.L127-.L114
	.long	.L128-.L114
	.long	.L129-.L114
	.long	.L112-.L114
	.long	.L130-.L114
	.long	.L126-.L114
	.long	.L127-.L114
	.long	.L128-.L114
	.long	.L129-.L114
	.text
.L130:
	.loc 2 368 0
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
	jmp	.L131
.L126:
	.loc 2 372 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_plus
	movq	%rax, -8(%rbp)
	jmp	.L131
.L127:
	.loc 2 375 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_minus
	movq	%rax, -8(%rbp)
	jmp	.L131
.L128:
	.loc 2 378 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_mul
	movq	%rax, -8(%rbp)
	jmp	.L131
.L129:
	.loc 2 381 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_div
	movq	%rax, -8(%rbp)
	jmp	.L131
.L113:
	.loc 2 384 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_bitand
	movq	%rax, -8(%rbp)
	jmp	.L131
.L115:
	.loc 2 387 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_bitor
	movq	%rax, -8(%rbp)
	jmp	.L131
.L116:
	.loc 2 390 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_shift_left
	movq	%rax, -8(%rbp)
	jmp	.L131
.L117:
	.loc 2 393 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_shift_right
	movq	%rax, -8(%rbp)
	jmp	.L131
.L124:
	.loc 2 395 0
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_lowerthan
	movq	%rax, -8(%rbp)
	jmp	.L131
.L125:
	.loc 2 397 0
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_lowerthan
	movq	%rax, -8(%rbp)
	jmp	.L131
.L123:
	.loc 2 399 0
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_greaterthan
	movq	%rax, -8(%rbp)
	jmp	.L131
.L122:
	.loc 2 401 0
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_greaterthan
	movq	%rax, -8(%rbp)
	jmp	.L131
.L120:
	.loc 2 403 0
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movl	$1, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_equal
	movq	%rax, -8(%rbp)
	jmp	.L131
.L121:
	.loc 2 405 0
	movq	-40(%rbp), %rcx
	movq	-32(%rbp), %rax
	movl	$0, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	value_equal
	movq	%rax, -8(%rbp)
	jmp	.L131
.L118:
	.loc 2 407 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_logand
	movq	%rax, -8(%rbp)
	jmp	.L131
.L119:
	.loc 2 409 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	value_logor
	movq	%rax, -8(%rbp)
	jmp	.L131
.L112:
	.loc 2 411 0
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 2 412 0
	movq	-40(%rbp), %rax
	movq	%rax, -8(%rbp)
.L131:
	.loc 2 414 0
	movq	-8(%rbp), %rax
	.loc 2 415 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE28:
	.size	operator_switch, .-operator_switch
#	.section	.rodata
	.align 8
.LC3:
	.string	" [unary-op] probably wrong at there! lhs:%p rhs:%p\n"
	.text
	.globl	unary_operator
	.type	unary_operator, @function
unary_operator:
.LFB29:
	.loc 2 424 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 425 0
	cmpq	$0, -32(%rbp)
	je	.L134
	.loc 2 425 0 is_stmt 0 discriminator 1
	cmpq	$0, -40(%rbp)
	jne	.L135
.L134:
	.loc 2 426 0 is_stmt 1
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 2 427 0
	jmp	.L133
.L135:
	.loc 2 429 0
	movq	-32(%rbp), %rax
	movq	(%rax), %rcx
	movq	-40(%rbp), %rdx
	movl	-20(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	operator_switch
	movq	%rax, -8(%rbp)
	.loc 2 431 0
	movq	-32(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
.L133:
	.loc 2 432 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE29:
	.size	unary_operator, .-unary_operator
	#.section	.rodata
	.align 8
.LC4:
	.string	" [binary-op] probably wrong at there! lhs:%p rhs:%p\n"
.LC5:
	.string	"some erro"
	.text
	.globl	binary_operator
	.type	binary_operator, @function
binary_operator:
.LFB30:
	.loc 2 440 0
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	.loc 2 441 0
	cmpq	$0, -32(%rbp)
	je	.L138
	.loc 2 441 0 is_stmt 0 discriminator 1
	cmpq	$0, -40(%rbp)
	jne	.L139
.L138:
	.loc 2 442 0 is_stmt 1
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	.loc 2 443 0
	movl	$0, %eax
	jmp	.L140
.L139:
	.loc 2 445 0
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rcx
	movl	-20(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	operator_switch
	movq	%rax, -8(%rbp)
	.loc 2 446 0
	movq	-8(%rbp), %rax
	movq	8(%rax), %rax
	cmpq	$1, %rax
	jne	.L141
	.loc 2 446 0 is_stmt 0 discriminator 1
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	cmpq	$3, %rax
	je	.L142
.L141:
	.loc 2 446 0 discriminator 3
	movabsq	$140737353797776, %rax
	cmpq	%rax, -8(%rbp)
	jne	.L143
.L142:
	.loc 2 447 0 is_stmt 1
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
.L143:
	.loc 2 449 0
	movq	-8(%rbp), %rax
.L140:
	.loc 2 450 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE30:
	.size	binary_operator, .-binary_operator
.Letext0:
	.file 3 "/usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h"
	.file 4 "/usr/include/x86_64-linux-gnu/bits/types.h"
	.file 5 "/usr/include/x86_64-linux-gnu/bits/libio.h"
	.file 6 "/usr/include/stdio.h"
	.file 7 "/usr/include/x86_64-linux-gnu/bits/sys_errlist.h"
	.file 8 "/usr/include/unistd.h"
	.file 9 "/usr/include/x86_64-linux-gnu/bits/getopt_core.h"
	.file 10 "/usr/include/time.h"
	.file 11 "/home/xiaodo/c++/colang/src/gc/Hugmem.h"
	.file 12 "/home/xiaodo/c++/colang/src/gc/gc.h"
	.file 13 "/home/xiaodo/c++/colang/src/internal/Value.h"
	.file 14 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h"
	.file 15 "/home/xiaodo/c++/colang/src/internal/../ast/Token.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xedb
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF207
	.byte	0xc
	.long	.LASF208
	.long	.LASF209
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF5
	.byte	0x3
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
	.uleb128 0x2
	.long	.LASF6
	.byte	0x4
	.byte	0x25
	.long	0x3f
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF7
	.uleb128 0x2
	.long	.LASF8
	.byte	0x4
	.byte	0x27
	.long	0x46
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.long	.LASF9
	.byte	0x4
	.byte	0x29
	.long	0x4d
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF10
	.uleb128 0x2
	.long	.LASF11
	.byte	0x4
	.byte	0x2c
	.long	0x38
	.uleb128 0x2
	.long	.LASF12
	.byte	0x4
	.byte	0x8c
	.long	0x8a
	.uleb128 0x2
	.long	.LASF13
	.byte	0x4
	.byte	0x8d
	.long	0x8a
	.uleb128 0x5
	.byte	0x8
	.uleb128 0x6
	.byte	0x8
	.long	0xba
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF14
	.uleb128 0x7
	.long	0xba
	.uleb128 0x8
	.long	.LASF44
	.byte	0xd8
	.byte	0x5
	.byte	0xf5
	.long	0x246
	.uleb128 0x9
	.long	.LASF15
	.byte	0x5
	.byte	0xf6
	.long	0x78
	.byte	0
	.uleb128 0x9
	.long	.LASF16
	.byte	0x5
	.byte	0xfb
	.long	0xb4
	.byte	0x8
	.uleb128 0x9
	.long	.LASF17
	.byte	0x5
	.byte	0xfc
	.long	0xb4
	.byte	0x10
	.uleb128 0x9
	.long	.LASF18
	.byte	0x5
	.byte	0xfd
	.long	0xb4
	.byte	0x18
	.uleb128 0x9
	.long	.LASF19
	.byte	0x5
	.byte	0xfe
	.long	0xb4
	.byte	0x20
	.uleb128 0x9
	.long	.LASF20
	.byte	0x5
	.byte	0xff
	.long	0xb4
	.byte	0x28
	.uleb128 0xa
	.long	.LASF21
	.byte	0x5
	.value	0x100
	.long	0xb4
	.byte	0x30
	.uleb128 0xa
	.long	.LASF22
	.byte	0x5
	.value	0x101
	.long	0xb4
	.byte	0x38
	.uleb128 0xa
	.long	.LASF23
	.byte	0x5
	.value	0x102
	.long	0xb4
	.byte	0x40
	.uleb128 0xa
	.long	.LASF24
	.byte	0x5
	.value	0x104
	.long	0xb4
	.byte	0x48
	.uleb128 0xa
	.long	.LASF25
	.byte	0x5
	.value	0x105
	.long	0xb4
	.byte	0x50
	.uleb128 0xa
	.long	.LASF26
	.byte	0x5
	.value	0x106
	.long	0xb4
	.byte	0x58
	.uleb128 0xa
	.long	.LASF27
	.byte	0x5
	.value	0x108
	.long	0x27e
	.byte	0x60
	.uleb128 0xa
	.long	.LASF28
	.byte	0x5
	.value	0x10a
	.long	0x284
	.byte	0x68
	.uleb128 0xa
	.long	.LASF29
	.byte	0x5
	.value	0x10c
	.long	0x78
	.byte	0x70
	.uleb128 0xa
	.long	.LASF30
	.byte	0x5
	.value	0x110
	.long	0x78
	.byte	0x74
	.uleb128 0xa
	.long	.LASF31
	.byte	0x5
	.value	0x112
	.long	0x9c
	.byte	0x78
	.uleb128 0xa
	.long	.LASF32
	.byte	0x5
	.value	0x116
	.long	0x46
	.byte	0x80
	.uleb128 0xa
	.long	.LASF33
	.byte	0x5
	.value	0x117
	.long	0x54
	.byte	0x82
	.uleb128 0xa
	.long	.LASF34
	.byte	0x5
	.value	0x118
	.long	0x28a
	.byte	0x83
	.uleb128 0xa
	.long	.LASF35
	.byte	0x5
	.value	0x11c
	.long	0x29a
	.byte	0x88
	.uleb128 0xa
	.long	.LASF36
	.byte	0x5
	.value	0x125
	.long	0xa7
	.byte	0x90
	.uleb128 0xa
	.long	.LASF37
	.byte	0x5
	.value	0x12d
	.long	0xb2
	.byte	0x98
	.uleb128 0xa
	.long	.LASF38
	.byte	0x5
	.value	0x12e
	.long	0xb2
	.byte	0xa0
	.uleb128 0xa
	.long	.LASF39
	.byte	0x5
	.value	0x12f
	.long	0xb2
	.byte	0xa8
	.uleb128 0xa
	.long	.LASF40
	.byte	0x5
	.value	0x130
	.long	0xb2
	.byte	0xb0
	.uleb128 0xa
	.long	.LASF41
	.byte	0x5
	.value	0x132
	.long	0x2d
	.byte	0xb8
	.uleb128 0xa
	.long	.LASF42
	.byte	0x5
	.value	0x133
	.long	0x78
	.byte	0xc0
	.uleb128 0xa
	.long	.LASF43
	.byte	0x5
	.value	0x135
	.long	0x2a0
	.byte	0xc4
	.byte	0
	.uleb128 0xb
	.long	.LASF210
	.byte	0x5
	.byte	0x9a
	.uleb128 0x8
	.long	.LASF45
	.byte	0x18
	.byte	0x5
	.byte	0xa0
	.long	0x27e
	.uleb128 0x9
	.long	.LASF46
	.byte	0x5
	.byte	0xa1
	.long	0x27e
	.byte	0
	.uleb128 0x9
	.long	.LASF47
	.byte	0x5
	.byte	0xa2
	.long	0x284
	.byte	0x8
	.uleb128 0x9
	.long	.LASF48
	.byte	0x5
	.byte	0xa6
	.long	0x78
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x24d
	.uleb128 0x6
	.byte	0x8
	.long	0xc6
	.uleb128 0xc
	.long	0xba
	.long	0x29a
	.uleb128 0xd
	.long	0x38
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x246
	.uleb128 0xc
	.long	0xba
	.long	0x2b0
	.uleb128 0xd
	.long	0x38
	.byte	0x13
	.byte	0
	.uleb128 0xe
	.long	.LASF211
	.uleb128 0xf
	.long	.LASF49
	.byte	0x5
	.value	0x13f
	.long	0x2b0
	.uleb128 0xf
	.long	.LASF50
	.byte	0x5
	.value	0x140
	.long	0x2b0
	.uleb128 0xf
	.long	.LASF51
	.byte	0x5
	.value	0x141
	.long	0x2b0
	.uleb128 0x6
	.byte	0x8
	.long	0xc1
	.uleb128 0x7
	.long	0x2d9
	.uleb128 0x10
	.long	.LASF52
	.byte	0x6
	.byte	0x87
	.long	0x284
	.uleb128 0x10
	.long	.LASF53
	.byte	0x6
	.byte	0x88
	.long	0x284
	.uleb128 0x10
	.long	.LASF54
	.byte	0x6
	.byte	0x89
	.long	0x284
	.uleb128 0x10
	.long	.LASF55
	.byte	0x7
	.byte	0x1a
	.long	0x78
	.uleb128 0xc
	.long	0x2df
	.long	0x31b
	.uleb128 0x11
	.byte	0
	.uleb128 0x7
	.long	0x310
	.uleb128 0x10
	.long	.LASF56
	.byte	0x7
	.byte	0x1b
	.long	0x31b
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF57
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF58
	.uleb128 0x12
	.long	.LASF212
	.byte	0x7
	.byte	0x4
	.long	0x4d
	.byte	0xf
	.byte	0x1b
	.long	0x4cb
	.uleb128 0x13
	.long	.LASF59
	.byte	0
	.uleb128 0x13
	.long	.LASF60
	.byte	0x1
	.uleb128 0x13
	.long	.LASF61
	.byte	0x2
	.uleb128 0x13
	.long	.LASF62
	.byte	0x3
	.uleb128 0x13
	.long	.LASF63
	.byte	0x4
	.uleb128 0x13
	.long	.LASF64
	.byte	0x5
	.uleb128 0x13
	.long	.LASF65
	.byte	0x6
	.uleb128 0x13
	.long	.LASF66
	.byte	0x7
	.uleb128 0x13
	.long	.LASF67
	.byte	0x8
	.uleb128 0x13
	.long	.LASF68
	.byte	0x9
	.uleb128 0x13
	.long	.LASF69
	.byte	0xa
	.uleb128 0x13
	.long	.LASF70
	.byte	0xb
	.uleb128 0x13
	.long	.LASF71
	.byte	0xc
	.uleb128 0x13
	.long	.LASF72
	.byte	0xd
	.uleb128 0x13
	.long	.LASF73
	.byte	0xe
	.uleb128 0x13
	.long	.LASF74
	.byte	0xf
	.uleb128 0x13
	.long	.LASF75
	.byte	0x10
	.uleb128 0x13
	.long	.LASF76
	.byte	0x11
	.uleb128 0x13
	.long	.LASF77
	.byte	0x12
	.uleb128 0x13
	.long	.LASF78
	.byte	0x13
	.uleb128 0x13
	.long	.LASF79
	.byte	0x14
	.uleb128 0x13
	.long	.LASF80
	.byte	0x15
	.uleb128 0x13
	.long	.LASF81
	.byte	0x16
	.uleb128 0x13
	.long	.LASF82
	.byte	0x17
	.uleb128 0x13
	.long	.LASF83
	.byte	0x18
	.uleb128 0x13
	.long	.LASF84
	.byte	0x19
	.uleb128 0x13
	.long	.LASF85
	.byte	0x1a
	.uleb128 0x13
	.long	.LASF86
	.byte	0x1b
	.uleb128 0x13
	.long	.LASF87
	.byte	0x1c
	.uleb128 0x13
	.long	.LASF88
	.byte	0x1d
	.uleb128 0x13
	.long	.LASF89
	.byte	0x1e
	.uleb128 0x13
	.long	.LASF90
	.byte	0x1f
	.uleb128 0x13
	.long	.LASF91
	.byte	0x20
	.uleb128 0x13
	.long	.LASF92
	.byte	0x21
	.uleb128 0x13
	.long	.LASF93
	.byte	0x22
	.uleb128 0x13
	.long	.LASF94
	.byte	0x23
	.uleb128 0x13
	.long	.LASF95
	.byte	0x24
	.uleb128 0x13
	.long	.LASF96
	.byte	0x25
	.uleb128 0x13
	.long	.LASF97
	.byte	0x26
	.uleb128 0x13
	.long	.LASF98
	.byte	0x27
	.uleb128 0x13
	.long	.LASF99
	.byte	0x28
	.uleb128 0x13
	.long	.LASF100
	.byte	0x29
	.uleb128 0x13
	.long	.LASF101
	.byte	0x2a
	.uleb128 0x13
	.long	.LASF102
	.byte	0x2b
	.uleb128 0x13
	.long	.LASF103
	.byte	0x2c
	.uleb128 0x13
	.long	.LASF104
	.byte	0x2d
	.uleb128 0x13
	.long	.LASF105
	.byte	0x2e
	.uleb128 0x13
	.long	.LASF106
	.byte	0x2f
	.uleb128 0x13
	.long	.LASF107
	.byte	0x30
	.uleb128 0x13
	.long	.LASF108
	.byte	0x31
	.uleb128 0x13
	.long	.LASF109
	.byte	0x32
	.uleb128 0x13
	.long	.LASF110
	.byte	0x33
	.uleb128 0x13
	.long	.LASF111
	.byte	0x34
	.uleb128 0x13
	.long	.LASF112
	.byte	0x35
	.uleb128 0x13
	.long	.LASF113
	.byte	0x36
	.uleb128 0x13
	.long	.LASF114
	.byte	0x37
	.uleb128 0x13
	.long	.LASF115
	.byte	0x38
	.uleb128 0x13
	.long	.LASF116
	.byte	0x39
	.uleb128 0x13
	.long	.LASF117
	.byte	0x3a
	.uleb128 0x13
	.long	.LASF118
	.byte	0x3b
	.uleb128 0x13
	.long	.LASF119
	.byte	0x3c
	.uleb128 0x13
	.long	.LASF120
	.byte	0x3d
	.uleb128 0x13
	.long	.LASF121
	.byte	0x3e
	.uleb128 0x13
	.long	.LASF122
	.byte	0x3f
	.byte	0
	.uleb128 0xf
	.long	.LASF123
	.byte	0x8
	.value	0x222
	.long	0x4d7
	.uleb128 0x6
	.byte	0x8
	.long	0xb4
	.uleb128 0x10
	.long	.LASF124
	.byte	0x9
	.byte	0x24
	.long	0xb4
	.uleb128 0x10
	.long	.LASF125
	.byte	0x9
	.byte	0x32
	.long	0x78
	.uleb128 0x10
	.long	.LASF126
	.byte	0x9
	.byte	0x37
	.long	0x78
	.uleb128 0x10
	.long	.LASF127
	.byte	0x9
	.byte	0x3b
	.long	0x78
	.uleb128 0xc
	.long	0xb4
	.long	0x519
	.uleb128 0xd
	.long	0x38
	.byte	0x1
	.byte	0
	.uleb128 0x10
	.long	.LASF128
	.byte	0xa
	.byte	0x9f
	.long	0x509
	.uleb128 0x10
	.long	.LASF129
	.byte	0xa
	.byte	0xa0
	.long	0x78
	.uleb128 0x10
	.long	.LASF130
	.byte	0xa
	.byte	0xa1
	.long	0x8a
	.uleb128 0x10
	.long	.LASF131
	.byte	0xa
	.byte	0xa6
	.long	0x509
	.uleb128 0x10
	.long	.LASF132
	.byte	0xa
	.byte	0xae
	.long	0x78
	.uleb128 0x10
	.long	.LASF133
	.byte	0xa
	.byte	0xaf
	.long	0x8a
	.uleb128 0x8
	.long	.LASF134
	.byte	0x18
	.byte	0xb
	.byte	0x7
	.long	0x58c
	.uleb128 0x9
	.long	.LASF135
	.byte	0xb
	.byte	0x9
	.long	0xb2
	.byte	0
	.uleb128 0x9
	.long	.LASF136
	.byte	0xb
	.byte	0xa
	.long	0x78
	.byte	0x8
	.uleb128 0x9
	.long	.LASF137
	.byte	0xb
	.byte	0xb
	.long	0x58c
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x55b
	.uleb128 0x2
	.long	.LASF138
	.byte	0xb
	.byte	0xc
	.long	0x55b
	.uleb128 0x8
	.long	.LASF139
	.byte	0x8
	.byte	0xb
	.byte	0xe
	.long	0x5b6
	.uleb128 0x9
	.long	.LASF140
	.byte	0xb
	.byte	0xf
	.long	0x5b6
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x592
	.uleb128 0x2
	.long	.LASF141
	.byte	0xb
	.byte	0x10
	.long	0x59d
	.uleb128 0x2
	.long	.LASF142
	.byte	0xc
	.byte	0x12
	.long	0x38
	.uleb128 0x14
	.byte	0x10
	.byte	0xc
	.byte	0x54
	.long	0x5f3
	.uleb128 0x9
	.long	.LASF143
	.byte	0xc
	.byte	0x55
	.long	0x78
	.byte	0
	.uleb128 0x9
	.long	.LASF144
	.byte	0xc
	.byte	0x56
	.long	0xb2
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF145
	.byte	0xc
	.byte	0x57
	.long	0x5d2
	.uleb128 0x15
	.byte	0x8
	.byte	0xc
	.byte	0x5a
	.long	0x61d
	.uleb128 0x16
	.long	.LASF146
	.byte	0xc
	.byte	0x5b
	.long	0x61d
	.uleb128 0x16
	.long	.LASF147
	.byte	0xc
	.byte	0x5c
	.long	0x4d
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x3f
	.uleb128 0x8
	.long	.LASF148
	.byte	0x30
	.byte	0xc
	.byte	0x59
	.long	0x690
	.uleb128 0x17
	.string	"ref"
	.byte	0xc
	.byte	0x5d
	.long	0x5fe
	.byte	0
	.uleb128 0x9
	.long	.LASF149
	.byte	0xc
	.byte	0x5e
	.long	0x690
	.byte	0x8
	.uleb128 0x9
	.long	.LASF150
	.byte	0xc
	.byte	0x5f
	.long	0x696
	.byte	0x10
	.uleb128 0x9
	.long	.LASF151
	.byte	0xc
	.byte	0x60
	.long	0x696
	.byte	0x18
	.uleb128 0x9
	.long	.LASF152
	.byte	0xc
	.byte	0x61
	.long	0x4d
	.byte	0x20
	.uleb128 0x9
	.long	.LASF153
	.byte	0xc
	.byte	0x62
	.long	0x4d
	.byte	0x24
	.uleb128 0x9
	.long	.LASF154
	.byte	0xc
	.byte	0x63
	.long	0x4d
	.byte	0x28
	.uleb128 0x9
	.long	.LASF155
	.byte	0xc
	.byte	0x64
	.long	0x4d
	.byte	0x2c
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x5f3
	.uleb128 0x6
	.byte	0x8
	.long	0x623
	.uleb128 0x8
	.long	.LASF156
	.byte	0x38
	.byte	0xc
	.byte	0x69
	.long	0x709
	.uleb128 0x9
	.long	.LASF157
	.byte	0xc
	.byte	0x6b
	.long	0x5c7
	.byte	0
	.uleb128 0x9
	.long	.LASF158
	.byte	0xc
	.byte	0x6e
	.long	0x61d
	.byte	0x8
	.uleb128 0x9
	.long	.LASF159
	.byte	0xc
	.byte	0x71
	.long	0x61d
	.byte	0x10
	.uleb128 0x9
	.long	.LASF160
	.byte	0xc
	.byte	0x74
	.long	0x4d
	.byte	0x18
	.uleb128 0x9
	.long	.LASF161
	.byte	0xc
	.byte	0x77
	.long	0x4d
	.byte	0x1c
	.uleb128 0x9
	.long	.LASF162
	.byte	0xc
	.byte	0x7a
	.long	0x696
	.byte	0x20
	.uleb128 0x9
	.long	.LASF163
	.byte	0xc
	.byte	0x7d
	.long	0x709
	.byte	0x28
	.uleb128 0x9
	.long	.LASF164
	.byte	0xc
	.byte	0x7e
	.long	0x709
	.byte	0x30
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x69c
	.uleb128 0x10
	.long	.LASF165
	.byte	0xc
	.byte	0x80
	.long	0x709
	.uleb128 0x10
	.long	.LASF166
	.byte	0xc
	.byte	0x8c
	.long	0x4d
	.uleb128 0x10
	.long	.LASF167
	.byte	0xc
	.byte	0xa5
	.long	0xb2
	.uleb128 0x10
	.long	.LASF168
	.byte	0xc
	.byte	0xb2
	.long	0x5bc
	.uleb128 0x8
	.long	.LASF169
	.byte	0x10
	.byte	0xd
	.byte	0x17
	.long	0x760
	.uleb128 0x9
	.long	.LASF170
	.byte	0xd
	.byte	0x19
	.long	0x8a
	.byte	0
	.uleb128 0x9
	.long	.LASF171
	.byte	0xd
	.byte	0x1a
	.long	0xb2
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.long	.LASF172
	.byte	0xd
	.byte	0x1b
	.long	0x73b
	.uleb128 0x10
	.long	.LASF173
	.byte	0x1
	.byte	0x5
	.long	0x2d9
	.uleb128 0x2
	.long	.LASF174
	.byte	0xe
	.byte	0x18
	.long	0x5b
	.uleb128 0x2
	.long	.LASF175
	.byte	0xe
	.byte	0x19
	.long	0x6d
	.uleb128 0x2
	.long	.LASF176
	.byte	0xe
	.byte	0x1a
	.long	0x7f
	.uleb128 0x2
	.long	.LASF177
	.byte	0xe
	.byte	0x1b
	.long	0x91
	.uleb128 0x2
	.long	.LASF178
	.byte	0x1
	.byte	0xb
	.long	0xb4
	.uleb128 0x7
	.long	0x7a2
	.uleb128 0xc
	.long	0xba
	.long	0x7c1
	.uleb128 0x18
	.long	0x38
	.byte	0
	.uleb128 0x8
	.long	.LASF179
	.byte	0x3
	.byte	0x1
	.byte	0x13
	.long	0x7fe
	.uleb128 0x17
	.string	"len"
	.byte	0x1
	.byte	0x14
	.long	0x776
	.byte	0
	.uleb128 0x9
	.long	.LASF180
	.byte	0x1
	.byte	0x15
	.long	0x776
	.byte	0x1
	.uleb128 0x9
	.long	.LASF143
	.byte	0x1
	.byte	0x16
	.long	0x3f
	.byte	0x2
	.uleb128 0x17
	.string	"buf"
	.byte	0x1
	.byte	0x17
	.long	0x7b2
	.byte	0x3
	.byte	0
	.uleb128 0x8
	.long	.LASF181
	.byte	0x5
	.byte	0x1
	.byte	0x19
	.long	0x83b
	.uleb128 0x17
	.string	"len"
	.byte	0x1
	.byte	0x1a
	.long	0x781
	.byte	0
	.uleb128 0x9
	.long	.LASF180
	.byte	0x1
	.byte	0x1b
	.long	0x781
	.byte	0x2
	.uleb128 0x9
	.long	.LASF143
	.byte	0x1
	.byte	0x1c
	.long	0x3f
	.byte	0x4
	.uleb128 0x17
	.string	"buf"
	.byte	0x1
	.byte	0x1d
	.long	0x7b2
	.byte	0x5
	.byte	0
	.uleb128 0x8
	.long	.LASF182
	.byte	0x9
	.byte	0x1
	.byte	0x1f
	.long	0x878
	.uleb128 0x17
	.string	"len"
	.byte	0x1
	.byte	0x20
	.long	0x78c
	.byte	0
	.uleb128 0x9
	.long	.LASF180
	.byte	0x1
	.byte	0x21
	.long	0x78c
	.byte	0x4
	.uleb128 0x9
	.long	.LASF143
	.byte	0x1
	.byte	0x22
	.long	0x3f
	.byte	0x8
	.uleb128 0x17
	.string	"buf"
	.byte	0x1
	.byte	0x23
	.long	0x7b2
	.byte	0x9
	.byte	0
	.uleb128 0x8
	.long	.LASF183
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.long	0x8b5
	.uleb128 0x17
	.string	"len"
	.byte	0x1
	.byte	0x26
	.long	0x797
	.byte	0
	.uleb128 0x9
	.long	.LASF180
	.byte	0x1
	.byte	0x27
	.long	0x797
	.byte	0x8
	.uleb128 0x9
	.long	.LASF143
	.byte	0x1
	.byte	0x28
	.long	0x3f
	.byte	0x10
	.uleb128 0x17
	.string	"buf"
	.byte	0x1
	.byte	0x29
	.long	0x7b2
	.byte	0x11
	.byte	0
	.uleb128 0x6
	.byte	0x8
	.long	0x760
	.uleb128 0x19
	.long	.LASF184
	.byte	0x2
	.value	0x1b7
	.long	0x8b5
	.quad	.LFB30
	.quad	.LFE30-.LFB30
	.uleb128 0x1
	.byte	0x9c
	.long	0x91a
	.uleb128 0x1a
	.string	"opt"
	.byte	0x2
	.value	0x1b7
	.long	0x78
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1a
	.string	"lhs"
	.byte	0x2
	.value	0x1b7
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1a
	.string	"rhs"
	.byte	0x2
	.value	0x1b7
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1b
	.string	"ret"
	.byte	0x2
	.value	0x1bd
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1c
	.long	.LASF190
	.byte	0x2
	.value	0x1a7
	.quad	.LFB29
	.quad	.LFE29-.LFB29
	.uleb128 0x1
	.byte	0x9c
	.long	0x975
	.uleb128 0x1a
	.string	"opt"
	.byte	0x2
	.value	0x1a7
	.long	0x78
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1a
	.string	"lhs"
	.byte	0x2
	.value	0x1a7
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1a
	.string	"rhs"
	.byte	0x2
	.value	0x1a7
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1b
	.string	"ret"
	.byte	0x2
	.value	0x1ad
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x19
	.long	.LASF185
	.byte	0x2
	.value	0x16c
	.long	0x8b5
	.quad	.LFB28
	.quad	.LFE28-.LFB28
	.uleb128 0x1
	.byte	0x9c
	.long	0x9d4
	.uleb128 0x1a
	.string	"opt"
	.byte	0x2
	.value	0x16c
	.long	0x78
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1a
	.string	"lhs"
	.byte	0x2
	.value	0x16c
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1a
	.string	"rhs"
	.byte	0x2
	.value	0x16c
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -56
	.uleb128 0x1b
	.string	"ret"
	.byte	0x2
	.value	0x16d
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x19
	.long	.LASF186
	.byte	0x2
	.value	0x154
	.long	0x78
	.quad	.LFB27
	.quad	.LFE27-.LFB27
	.uleb128 0x1
	.byte	0x9c
	.long	0xa06
	.uleb128 0x1d
	.long	.LASF187
	.byte	0x2
	.value	0x154
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x19
	.long	.LASF188
	.byte	0x2
	.value	0x146
	.long	0x8b5
	.quad	.LFB26
	.quad	.LFE26-.LFB26
	.uleb128 0x1
	.byte	0x9c
	.long	0xa47
	.uleb128 0x1d
	.long	.LASF140
	.byte	0x2
	.value	0x146
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1d
	.long	.LASF189
	.byte	0x2
	.value	0x146
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.uleb128 0x1c
	.long	.LASF191
	.byte	0x2
	.value	0x136
	.quad	.LFB25
	.quad	.LFE25-.LFB25
	.uleb128 0x1
	.byte	0x9c
	.long	0xa93
	.uleb128 0x1d
	.long	.LASF140
	.byte	0x2
	.value	0x136
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.uleb128 0x1d
	.long	.LASF189
	.byte	0x2
	.value	0x136
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x1a
	.string	"var"
	.byte	0x2
	.value	0x136
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x19
	.long	.LASF192
	.byte	0x2
	.value	0x129
	.long	0x8b5
	.quad	.LFB24
	.quad	.LFE24-.LFB24
	.uleb128 0x1
	.byte	0x9c
	.long	0xae3
	.uleb128 0x1a
	.string	"lhs"
	.byte	0x2
	.value	0x129
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1a
	.string	"rhs"
	.byte	0x2
	.value	0x129
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1e
	.long	.LASF193
	.byte	0x2
	.value	0x12a
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x19
	.long	.LASF194
	.byte	0x2
	.value	0x123
	.long	0x8b5
	.quad	.LFB23
	.quad	.LFE23-.LFB23
	.uleb128 0x1
	.byte	0x9c
	.long	0xb33
	.uleb128 0x1a
	.string	"lhs"
	.byte	0x2
	.value	0x123
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1a
	.string	"rhs"
	.byte	0x2
	.value	0x123
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1e
	.long	.LASF193
	.byte	0x2
	.value	0x124
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x19
	.long	.LASF195
	.byte	0x2
	.value	0x10b
	.long	0x8b5
	.quad	.LFB22
	.quad	.LFE22-.LFB22
	.uleb128 0x1
	.byte	0x9c
	.long	0xb92
	.uleb128 0x1a
	.string	"lhs"
	.byte	0x2
	.value	0x10b
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x1a
	.string	"rhs"
	.byte	0x2
	.value	0x10b
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1d
	.long	.LASF196
	.byte	0x2
	.value	0x10b
	.long	0x78
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x1e
	.long	.LASF193
	.byte	0x2
	.value	0x10d
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1f
	.long	.LASF197
	.byte	0x2
	.byte	0xf4
	.long	0x8b5
	.quad	.LFB21
	.quad	.LFE21-.LFB21
	.uleb128 0x1
	.byte	0x9c
	.long	0xbec
	.uleb128 0x20
	.string	"lhs"
	.byte	0x2
	.byte	0xf4
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.string	"rhs"
	.byte	0x2
	.byte	0xf4
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x21
	.long	.LASF196
	.byte	0x2
	.byte	0xf4
	.long	0x78
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x22
	.long	.LASF193
	.byte	0x2
	.byte	0xf6
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1f
	.long	.LASF198
	.byte	0x2
	.byte	0xdf
	.long	0x8b5
	.quad	.LFB20
	.quad	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.long	0xc46
	.uleb128 0x20
	.string	"lhs"
	.byte	0x2
	.byte	0xdf
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.string	"rhs"
	.byte	0x2
	.byte	0xdf
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x21
	.long	.LASF196
	.byte	0x2
	.byte	0xdf
	.long	0x78
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x22
	.long	.LASF193
	.byte	0x2
	.byte	0xe0
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1f
	.long	.LASF199
	.byte	0x2
	.byte	0xc5
	.long	0x8b5
	.quad	.LFB19
	.quad	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.long	0xc92
	.uleb128 0x20
	.string	"lhs"
	.byte	0x2
	.byte	0xc5
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.string	"rhs"
	.byte	0x2
	.byte	0xc5
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x22
	.long	.LASF193
	.byte	0x2
	.byte	0xc6
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1f
	.long	.LASF200
	.byte	0x2
	.byte	0xab
	.long	0x8b5
	.quad	.LFB18
	.quad	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.long	0xcde
	.uleb128 0x20
	.string	"lhs"
	.byte	0x2
	.byte	0xab
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.string	"rhs"
	.byte	0x2
	.byte	0xab
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x22
	.long	.LASF193
	.byte	0x2
	.byte	0xac
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1f
	.long	.LASF201
	.byte	0x2
	.byte	0x91
	.long	0x8b5
	.quad	.LFB17
	.quad	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.long	0xd2a
	.uleb128 0x20
	.string	"lhs"
	.byte	0x2
	.byte	0x91
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.string	"rhs"
	.byte	0x2
	.byte	0x91
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x22
	.long	.LASF193
	.byte	0x2
	.byte	0x92
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1f
	.long	.LASF202
	.byte	0x2
	.byte	0x77
	.long	0x8b5
	.quad	.LFB16
	.quad	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.long	0xd76
	.uleb128 0x20
	.string	"lhs"
	.byte	0x2
	.byte	0x77
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.string	"rhs"
	.byte	0x2
	.byte	0x77
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x22
	.long	.LASF193
	.byte	0x2
	.byte	0x78
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1f
	.long	.LASF203
	.byte	0x2
	.byte	0x5d
	.long	0x8b5
	.quad	.LFB15
	.quad	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.long	0xdc2
	.uleb128 0x20
	.string	"lhs"
	.byte	0x2
	.byte	0x5d
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.string	"rhs"
	.byte	0x2
	.byte	0x5d
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x22
	.long	.LASF193
	.byte	0x2
	.byte	0x5e
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1f
	.long	.LASF204
	.byte	0x2
	.byte	0x43
	.long	0x8b5
	.quad	.LFB14
	.quad	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.long	0xe0e
	.uleb128 0x20
	.string	"lhs"
	.byte	0x2
	.byte	0x43
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.string	"rhs"
	.byte	0x2
	.byte	0x43
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x22
	.long	.LASF193
	.byte	0x2
	.byte	0x44
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1f
	.long	.LASF205
	.byte	0x2
	.byte	0x29
	.long	0x8b5
	.quad	.LFB13
	.quad	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.long	0xe5a
	.uleb128 0x20
	.string	"lhs"
	.byte	0x2
	.byte	0x29
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.string	"rhs"
	.byte	0x2
	.byte	0x29
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x22
	.long	.LASF193
	.byte	0x2
	.byte	0x2a
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x1f
	.long	.LASF206
	.byte	0x2
	.byte	0xf
	.long	0x8b5
	.quad	.LFB12
	.quad	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.long	0xea6
	.uleb128 0x20
	.string	"lhs"
	.byte	0x2
	.byte	0xf
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x20
	.string	"rhs"
	.byte	0x2
	.byte	0xf
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x22
	.long	.LASF193
	.byte	0x2
	.byte	0x10
	.long	0x8b5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x23
	.long	.LASF213
	.byte	0x1
	.byte	0x37
	.long	0x2d
	.quad	.LFB5
	.quad	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0x20
	.string	"s"
	.byte	0x1
	.byte	0x37
	.long	0x7ad
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x22
	.long	.LASF143
	.byte	0x1
	.byte	0x38
	.long	0x3f
	.uleb128 0x2
	.byte	0x91
	.sleb128 -17
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
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0x13
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x14
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x1b
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
	.uleb128 0x5
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
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.uleb128 0x21
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
	.uleb128 0x22
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
	.uleb128 0x23
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
.LASF34:
	.string	"_shortbuf"
.LASF12:
	.string	"__off_t"
.LASF16:
	.string	"_IO_read_ptr"
.LASF158:
	.string	"first_address"
.LASF28:
	.string	"_chain"
.LASF153:
	.string	"szidx"
.LASF188:
	.string	"kv_get"
.LASF5:
	.string	"size_t"
.LASF60:
	.string	"TK_VAR"
.LASF101:
	.string	"TK_LBRACKET"
.LASF177:
	.string	"uint64_t"
.LASF178:
	.string	"string"
.LASF6:
	.string	"__uint8_t"
.LASF170:
	.string	"type"
.LASF51:
	.string	"_IO_2_1_stderr_"
.LASF205:
	.string	"value_minus"
.LASF58:
	.string	"long long unsigned int"
.LASF79:
	.string	"TK_EQ"
.LASF117:
	.string	"KW_EXTERN"
.LASF144:
	.string	"addr"
.LASF156:
	.string	"arena_object"
.LASF106:
	.string	"KW_ELSE"
.LASF137:
	.string	"next"
.LASF181:
	.string	"stringhdr16"
.LASF103:
	.string	"TK_DOT"
.LASF130:
	.string	"__timezone"
.LASF57:
	.string	"long long int"
.LASF4:
	.string	"signed char"
.LASF195:
	.string	"value_greaterthan"
.LASF166:
	.string	"maxarenas"
.LASF138:
	.string	"ListNode"
.LASF29:
	.string	"_fileno"
.LASF76:
	.string	"TK_LOGAND"
.LASF187:
	.string	"cond"
.LASF17:
	.string	"_IO_read_end"
.LASF212:
	.string	"Token"
.LASF93:
	.string	"TK_MUL_AGN"
.LASF108:
	.string	"KW_FALSE"
.LASF50:
	.string	"_IO_2_1_stdout_"
.LASF10:
	.string	"long int"
.LASF162:
	.string	"freepools"
.LASF80:
	.string	"TK_NE"
.LASF183:
	.string	"stringhdr64"
.LASF23:
	.string	"_IO_buf_end"
.LASF32:
	.string	"_cur_column"
.LASF97:
	.string	"TK_LPAREN"
.LASF207:
	.string	"GNU C11 7.5.0 -mtune=generic -march=x86-64 -g -fno-builtin"
.LASF173:
	.string	"LSTRING_NOINIT"
.LASF71:
	.string	"TK_BITOR_AGN"
.LASF31:
	.string	"_old_offset"
.LASF36:
	.string	"_offset"
.LASF155:
	.string	"maxnextoffset"
.LASF198:
	.string	"value_equal"
.LASF192:
	.string	"value_logor"
.LASF147:
	.string	"count"
.LASF9:
	.string	"__uint32_t"
.LASF87:
	.string	"TK_MUL"
.LASF194:
	.string	"value_logand"
.LASF82:
	.string	"TK_GE"
.LASF201:
	.string	"value_bitor"
.LASF133:
	.string	"timezone"
.LASF40:
	.string	"__pad4"
.LASF41:
	.string	"__pad5"
.LASF110:
	.string	"KW_FOR"
.LASF135:
	.string	"value"
.LASF64:
	.string	"LIT_DOUBLE"
.LASF196:
	.string	"equal"
.LASF45:
	.string	"_IO_marker"
.LASF52:
	.string	"stdin"
.LASF145:
	.string	"block"
.LASF119:
	.string	"KW_GO"
.LASF175:
	.string	"uint16_t"
.LASF115:
	.string	"KW_CONTINUE"
.LASF159:
	.string	"pool_address"
.LASF99:
	.string	"TK_LBRACE"
.LASF88:
	.string	"TK_DIV"
.LASF0:
	.string	"long unsigned int"
.LASF104:
	.string	"TK_COLON"
.LASF211:
	.string	"_IO_FILE_plus"
.LASF204:
	.string	"value_mul"
.LASF20:
	.string	"_IO_write_ptr"
.LASF160:
	.string	"nfreepools"
.LASF132:
	.string	"daylight"
.LASF55:
	.string	"sys_nerr"
.LASF47:
	.string	"_sbuf"
.LASF184:
	.string	"binary_operator"
.LASF171:
	.string	"data"
.LASF136:
	.string	"size"
.LASF2:
	.string	"short unsigned int"
.LASF124:
	.string	"optarg"
.LASF199:
	.string	"value_shift_right"
.LASF134:
	.string	"link_list"
.LASF24:
	.string	"_IO_save_base"
.LASF209:
	.string	"/home/xiaodo/c++/colang/tests/src/internal"
.LASF163:
	.string	"nextarena"
.LASF121:
	.string	"KW_PACKAGE"
.LASF35:
	.string	"_lock"
.LASF30:
	.string	"_flags2"
.LASF42:
	.string	"_mode"
.LASF53:
	.string	"stdout"
.LASF92:
	.string	"TK_MINUS_AGN"
.LASF85:
	.string	"TK_PLUS"
.LASF169:
	.string	"core_value"
.LASF89:
	.string	"TK_MOD"
.LASF49:
	.string	"_IO_2_1_stdin_"
.LASF141:
	.string	"List"
.LASF151:
	.string	"prevpool"
.LASF152:
	.string	"arenaindex"
.LASF122:
	.string	"TK_DELREF"
.LASF157:
	.string	"address"
.LASF125:
	.string	"optind"
.LASF179:
	.string	"stringhdr8"
.LASF65:
	.string	"LIT_CHAR"
.LASF149:
	.string	"freeblock"
.LASF21:
	.string	"_IO_write_end"
.LASF120:
	.string	"KW_CLASS"
.LASF91:
	.string	"TK_PLUS_AGN"
.LASF59:
	.string	"INVALID"
.LASF164:
	.string	"prevarena"
.LASF213:
	.string	"stringlen"
.LASF210:
	.string	"_IO_lock_t"
.LASF44:
	.string	"_IO_FILE"
.LASF105:
	.string	"KW_IF"
.LASF123:
	.string	"__environ"
.LASF129:
	.string	"__daylight"
.LASF142:
	.string	"Co_uintptr_t"
.LASF11:
	.string	"__uint64_t"
.LASF190:
	.string	"unary_operator"
.LASF111:
	.string	"KW_NULL"
.LASF48:
	.string	"_pos"
.LASF56:
	.string	"sys_errlist"
.LASF81:
	.string	"TK_GT"
.LASF27:
	.string	"_markers"
.LASF165:
	.string	"arenas"
.LASF70:
	.string	"TK_BITAND_AGN"
.LASF203:
	.string	"value_div"
.LASF1:
	.string	"unsigned char"
.LASF200:
	.string	"value_shift_left"
.LASF107:
	.string	"KW_TRUE"
.LASF69:
	.string	"TK_BITNOT"
.LASF7:
	.string	"short int"
.LASF75:
	.string	"TK_SHIFTR_AGN"
.LASF100:
	.string	"TK_RBRACE"
.LASF114:
	.string	"KW_BREAK"
.LASF33:
	.string	"_vtable_offset"
.LASF131:
	.string	"tzname"
.LASF185:
	.string	"operator_switch"
.LASF161:
	.string	"ntotalpools"
.LASF112:
	.string	"KW_FUNC"
.LASF61:
	.string	"TK_EOF"
.LASF109:
	.string	"KW_WHILE"
.LASF127:
	.string	"optopt"
.LASF176:
	.string	"uint32_t"
.LASF154:
	.string	"nextoffset"
.LASF86:
	.string	"TK_MINUS"
.LASF98:
	.string	"TK_RPAREN"
.LASF116:
	.string	"KW_NEW"
.LASF14:
	.string	"char"
.LASF77:
	.string	"TK_LOGOR"
.LASF3:
	.string	"unsigned int"
.LASF90:
	.string	"TK_ASSIGN"
.LASF8:
	.string	"__uint16_t"
.LASF189:
	.string	"index"
.LASF126:
	.string	"opterr"
.LASF180:
	.string	"alloc"
.LASF197:
	.string	"value_lowerthan"
.LASF46:
	.string	"_next"
.LASF13:
	.string	"__off64_t"
.LASF95:
	.string	"TK_MOD_AGN"
.LASF18:
	.string	"_IO_read_base"
.LASF26:
	.string	"_IO_save_end"
.LASF168:
	.string	"Hugmem"
.LASF167:
	.string	"sp_start"
.LASF113:
	.string	"KW_RETURN"
.LASF63:
	.string	"LIT_STR"
.LASF37:
	.string	"__pad1"
.LASF38:
	.string	"__pad2"
.LASF39:
	.string	"__pad3"
.LASF66:
	.string	"TK_BITAND"
.LASF68:
	.string	"TK_BITXOR"
.LASF146:
	.string	"_padding"
.LASF62:
	.string	"LIT_INT"
.LASF43:
	.string	"_unused2"
.LASF54:
	.string	"stderr"
.LASF94:
	.string	"TK_DIV_AGN"
.LASF148:
	.string	"pool_header"
.LASF206:
	.string	"value_plus"
.LASF191:
	.string	"kv_update"
.LASF96:
	.string	"TK_COMMA"
.LASF186:
	.string	"isTrue"
.LASF172:
	.string	"Value"
.LASF182:
	.string	"stringhdr32"
.LASF15:
	.string	"_flags"
.LASF174:
	.string	"uint8_t"
.LASF25:
	.string	"_IO_backup_base"
.LASF74:
	.string	"TK_SHIFTL_AGN"
.LASF143:
	.string	"flags"
.LASF72:
	.string	"TK_SHIFTL"
.LASF118:
	.string	"KW_IMPORT"
.LASF83:
	.string	"TK_LT"
.LASF73:
	.string	"TK_SHIFTR"
.LASF84:
	.string	"TK_LE"
.LASF67:
	.string	"TK_BITOR"
.LASF208:
	.string	"/home/xiaodo/c++/colang/src/internal/Value.c"
.LASF202:
	.string	"value_bitand"
.LASF139:
	.string	"list"
.LASF102:
	.string	"TK_RBRACKET"
.LASF128:
	.string	"__tzname"
.LASF150:
	.string	"nextpool"
.LASF19:
	.string	"_IO_write_base"
.LASF22:
	.string	"_IO_buf_base"
.LASF193:
	.string	"result"
.LASF78:
	.string	"TK_LOGNOT"
.LASF140:
	.string	"root"
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
